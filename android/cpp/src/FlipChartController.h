//
// Created by admin on 2019-08-22.
//

#ifndef FLIPCHARTQUICK_FLIPCHARTCONTROLLER_H
#define FLIPCHARTQUICK_FLIPCHARTCONTROLLER_H

#include <iostream>

#include <QString>
#include <string>

class AsNode;
class AsObject;
class AsFactory;
class AsFlipchart;
class AsVirtualFolder;


class FlipChartController
{

public:
    FlipChartController();
    ~FlipChartController();

public:
    std::string openFlipchart(const std::string& flipChartPath, const std::string& uncompressPath);

    std::string loadPage(const int pageNumber);
    void dispose();
    void clear();
private:
    bool deleteDirectory(const QString &path);

    void asReportFileDelegate(const QString& path, const QByteArray& mes);

    std::string asLoadOpenFlipchart(const QString& flipPath, bool recover,  const QString& orgFilePathAndName );

//    const char *objectTypeToChar(AsObject::AsEnumObjectType type);
private:
    AsFactory* m_pFactory;
    QString m_flipChartPath;
    QString m_uncompressPath;
    AsVirtualFolder *m_pTempVirtualFolder;
    AsNode *m_flipchartNode;
    AsFlipchart *m_flipchart;

    void clearTempFiles(const QString &temp_path);
    int getUniquePathNumber();
};


#endif //FLIPCHARTQUICK_FLIPCHARTCONTROLLER_H
