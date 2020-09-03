#include "FlipChartController.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QPointF>
#include <QThread>

#include "util/aszip.h"
#include "asfactory.h"
#include "io/asfileio.h"
#include "io/asnode.h"

#include "objects/asflipchart.h"
#include "resources/asresourcemanager.h"
#include <json/json.h>

FlipChartController::FlipChartController()
        : m_flipChartPath(""), m_uncompressPath(""), m_pFactory(new AsFactory()),
          m_flipchartNode(nullptr) {
}

FlipChartController::~FlipChartController() {
    if (m_pFactory)
        delete m_pFactory;

}

std::string FlipChartController::openFlipchart(const std::string &flipChartPath,
                                               const std::string &uncompressPath) {
    LOGDEBUG("open file Thread is %d", QThread::currentThreadId());
    m_flipChartPath = QString::fromStdString(flipChartPath);

    QFileInfo fileInfo(m_flipChartPath);
    QString baseName = fileInfo.baseName();
    LOGDEBUG("baseName:%s", baseName.toUtf8().data());

    m_uncompressPath = QString::fromStdString(uncompressPath) + "/" + baseName;
    QDir dir(m_uncompressPath);

    LOGDEBUG("m_uncompressPath:%s", m_uncompressPath.toUtf8().data());

    //deleteDirectory(m_uncompressPath);
    //  dispose();

    if (!dir.exists()) {
        dir.mkdir(m_uncompressPath);
    } else {
        clearTempFiles(m_uncompressPath);
    }
    //生成解压flipchart page 的缓存目录
    QString virtualfolderPath = m_uncompressPath + "/pageTemp";
    if (!dir.exists(virtualfolderPath)) {
        if (!dir.mkdir(virtualfolderPath)) {
            LOGDEBUG("creat page temp error %s", virtualfolderPath.toStdString().data());
        }
    }
    m_pTempVirtualFolder = m_pFactory->asGetVirtualFolder(AsFactory::AS_ID_VIRTUALRESOURCEFOLDER,
                                                          virtualfolderPath);

    AsZip *zip = new AsZip();
    zip->bindAsReportFile([this](const QString &path, const QByteArray &mes) {
        asReportFileDelegate(path, mes);
    });

    bool result = zip->asReportFiles(flipChartPath);
    delete zip;

    if (!result) {
        return "错误";
    }

    string qString = asLoadOpenFlipchart(m_uncompressPath, false, baseName);
    LOGDEBUG("PageIds:%s", qString.data());

    return qString;
}

void FlipChartController::clearTempFiles(const QString &temp_path) {
    QDir dir(temp_path);
    if (dir.isEmpty()) {
        return;
    }
    QStringList filter; //过滤器
    filter.append("*");
    QDirIterator it(temp_path, filter, QDir::Files | QDir::Dirs, QDirIterator::Subdirectories);
    while (it.hasNext()) { //若容器中还有成员，继续执行删除操作
        dir.remove(it.next());
    }
}


string FlipChartController::loadPage(const int pageNumber) {

    LOGDEBUG("load page Thread is %d", QThread::currentThreadId());
    AsNode *pNode = m_flipchart->asLoadPageObjects(pageNumber);
    if (!pNode) {
        return "";
    }
    AsObject *pObj = pNode->asGetAsObjectReference();
    if (!pObj) {
        return "";
    }
    auto objectCount = pNode->asGetChildCount();
    LOGDEBUG("page %d,children count: %d", pageNumber, objectCount);
    Json::Value res = pObj->serialized();
    Json::Value objectsArray(Json::arrayValue);
    Json::Value actionsArray(Json::arrayValue);
    for (int i = 0; i < objectCount; i++) {
        AsNode *node = pNode->asGetChildAt(i);
        AsObject *object = node->asGetAsObjectReference();
        if (object != nullptr) {
            Json::Value &json = object->serialized();
            if (json && !json.empty()) {
                if (object->typeName() == "background") {
                    res["background"] = json;
                } else if (!object->isAction()) {
                    objectsArray.append(json);
                } else {
                    actionsArray.append(json);
                }

            }

        }

    }
    res["objects"] = objectsArray;
    res["actions"] = actionsArray;
    res["version"] = "0.0.0";

    Json::StreamWriterBuilder wbuilder;
    return Json::writeString(wbuilder, res);
}

bool FlipChartController::deleteDirectory(const QString &path) {
    if (path.isEmpty()) {
        return false;
    }

    QDir dir(path);
    if (!dir.exists()) {
        return true;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
            foreach (QFileInfo fi, fileList) {
            if (fi.isFile()) {
                fi.dir().remove(fi.fileName());
            } else {
                deleteDirectory(fi.absoluteFilePath());
            }
        }
    return dir.rmpath(dir.absolutePath());
}

void
FlipChartController::asReportFileDelegate(const QString &fileName, const QByteArray &fileData) {
    LOGDEBUG("path-->%s", fileName.toUtf8().data());

    QString sFullPathFilename = m_uncompressPath + QDir::separator() + fileName;

    QFileInfo info(fileName);
    if (info.suffix() == "ir") {
        LOGDEBUG("%s", "ir 处理");
        //        AsVirtualFolder
        //        Q_ASSERT( m_pTempVirtualFolder );

        m_pTempVirtualFolder->asAddFile(info.fileName(), fileData);
    } else {
        QFileInfo fFullPathFilename = sFullPathFilename;
        QDir dFullPath = fFullPathFilename.path();

        if (!dFullPath.exists()) {
            dFullPath.mkpath(dFullPath.path());
        }

        // Now we can save the file to the desired path.
        QFile outFile(sFullPathFilename);

        if (!outFile.open(QIODevice::WriteOnly)) {
            return;
        }

        outFile.write(fileData);

        if (outFile.error()) {
            outFile.close();
            return;
        }

        outFile.close();
    }
}

std::string FlipChartController::asLoadOpenFlipchart(const QString &flipPath, bool recover,
                                                     const QString &orgFilePathAndName) {
    AsFileIO fileIO(m_pFactory);

    m_flipchartNode = fileIO.asLoadObjectTree(flipPath);
    m_flipchart = (AsFlipchart *) m_flipchartNode->asGetAsObjectReference();

    m_flipchart->asSetFlipchartWorkingPath(m_uncompressPath);
    m_flipchart->asAddReference(m_flipchartNode);

    m_pFactory->setResourceManager(new AsResourceManager());

    int pageCount = m_flipchartNode->asGetChildCount();
    LOGDEBUG("children count:%d", pageCount);
    LOGDEBUG("flipchart workpath1:%s", m_flipchart->asGetFlipchartWorkingPath().toUtf8().data());

    Json::Value jsonArray; //= new QJsonArray();
    Json::Value pageInfoObject;
    for (auto i = 0; i < pageCount; i++) {
        int id = static_cast<qint32 >(m_flipchartNode->asGetChildAt(i)->asGetID());
        pageInfoObject["id"] = id;
        pageInfoObject["thumbnailUrl"] = (flipPath.toUtf8() + "/" + QString::number(id) +
                                          ".thm").toStdString();
        jsonArray.append(pageInfoObject);
    }
    Json::Value jsonObject;
    // jsonObject["pageIds"] = jsonArray;
    jsonObject["pageInfos"] = jsonArray;
    jsonObject["cacheDir"] = flipPath.toUtf8().data();


    Json::StreamWriterBuilder wbuilder;
    return Json::writeString(wbuilder, jsonObject);
}

void FlipChartController::clear() {
    clearTempFiles(m_uncompressPath);
}

void FlipChartController::dispose() {
    clearTempFiles(m_uncompressPath);
    QDir dir(m_uncompressPath);
    dir.cdUp();
    deleteDirectory(dir.path());
}

int FlipChartController::getUniquePathNumber() {
    QDir dir(m_uncompressPath);
    dir.cdUp();
    deleteDirectory(dir.path());
    return 0;
}


