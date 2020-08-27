// Implementation of the AsFileIO class.
// (c) 2006 Promethean Technologies Group Ltd.

#include "asfileio.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>


#include "asobjectstreamer.h"
#include "asnode.h"
#include "../objects/asobject.h"
#include "../util/asutil.h"
#include "../util/asfileutils.h"
#include "../objects/asvirtualfolder.h"

#include "../asfactory.h"
#include "../util/aszip.h"
#include "../util/commonlog.h"


// Cache to Structured Storage pointers...
AsVirtualFolder *m_pTempVirtualPageFolder;

AsFileIO::AsFileIO( AsNode *pFlipchartNode ) : m_pFlipchartNode(pFlipchartNode),
                                              m_pFlipchart(NULL),
                                               m_pFactory(NULL),
                                               m_pCurrentFile(NULL),
                                               m_pStreamer(NULL)
{

    if ( m_pFlipchartNode != 0 )
    {
        m_pFactory = m_pFlipchartNode->asGetFactoryPointer();
        if ( m_pFactory != 0 )
        {
             m_pFlipchart = m_pFactory->asGetFlipchart();
        }
        else
        {
            m_pFlipchart = (AsFlipchart*)m_pFlipchartNode->asGetAsObjectReference();
        }
    }

}

AsFileIO::AsFileIO( AsFlipchart *pFlipchart ) : m_pFlipchartNode(NULL),
                                                m_pFlipchart(pFlipchart),
                                                m_pFactory(NULL),
                                                m_pCurrentFile(NULL),
                                                m_pStreamer(NULL)
{

    if ( m_pFlipchart )
    {
        m_pFactory = m_pFlipchart->asGetFactoryPointer();
    }
}

AsFileIO::AsFileIO( AsFactory *pFactory ) : m_pFlipchartNode(NULL),
                                            m_pFlipchart(NULL),
                                            m_pFactory(pFactory),
                                            m_pCurrentFile(NULL),
                                            m_pStreamer(NULL)
{
    if(m_pFactory != NULL)
    {
        m_pFlipchart = m_pFactory->asGetFlipchart();
        // if( m_pFlipchart != NULL )
        // {
        //     m_pFlipchartNode = m_pFlipchart->asGetReferences().at( 0 );
        // }
    }
}

AsFileIO::~AsFileIO()
{
    delete m_pCurrentFile;
    m_pCurrentFile = NULL;
    delete m_pStreamer;
    m_pStreamer = NULL;
}

bool AsFileIO::asSetupFlipchartPointer()
{
   return true;
}

AsNode * AsFileIO::asLoadPage( AsNode *pPageNode)
{
//    return new AsNode;
//    AS_DEBUG("");

    quint32 idNo = pPageNode->asGetID();
    QString idStr = "Loading page with id: " + QString::number( idNo );

    if( !asSetupFlipchartPointer() )
        return NULL;

    AsVirtualFolder *pFolder = NULL;
    AsFactory *pFactory = pPageNode->asGetFactoryPointer();
    if ( pFactory->asHasVirtualFolder( pPageNode->asGetID() ) )
    {
        pFolder = pFactory->asGetVirtualFolder( pPageNode->asGetID() );
    }
    else
    {
        LOGDEBUG("###:%s",m_pFlipchart->asGetFlipchartWorkingPath().toUtf8().data());
        // Is there an fpg to work with...
        QString sPageFile = m_pFlipchart->asGetFlipchartWorkingPath() + QDir::separator() + QString::number( pPageNode->asGetID()) + ".fpg";
//        QFile file( sPageFile );
//        if ( !file.exists() )
//        {
//            sPageFile.clear();
//            if (( AsStudio::asInstance()->asGetDefaults()->asIsDefault( ASDEFAULT_ONIMPORTSIGNALPAGEPROGRESS ))
//                && ( m_pFlipchart->asGetV2Reader() != NULL ))
//            {
//                int nPageNumber = pPageNode->asGetMyChildPosition();
//                AsApp::asInstance()->asGetFlipchartManager().asImportV2Page( nPageNumber );
//                sPageFile = m_pFlipchart->asGetFlipchartWorkingPath() + QDir::separator() + QString::number( pPageNode->asGetID()) + ".fpg";
//            }
//        }

        if ( sPageFile.isEmpty() )
            return NULL;

        pFolder = asUnzipPage( sPageFile );
    }

    if ( pFolder == NULL )
        return NULL;

    AsNode* loadedNode = asLoadObjectTree( pFolder );

    if( loadedNode == NULL )
    {
    }
    return loadedNode;
}



AsNode * AsFileIO::asLoadObjectTree( const QString& sPath )
{
    LOGDEBUG("sPath: %s", sPath.toUtf8().data());

    if ( m_pFactory == NULL )
    {
        return NULL;
    }

    QDir path( sPath );
    std::string pathstd= sPath.toStdString();
    if ( !path.exists() )
    {
        QString sFile = sPath + ".fpg";
        QFile file( sFile );
        if ( !file.exists() )
        {
            QString msg = "Page file doesn't exist: " + sFile;
            return 0;
        }

        if ( !asUnzipPage( sFile ))
        {
            return 0;
        }

        if ( !path.exists() )
        {

            return 0;
        }
    }

    // First, load node trees (in) and objects collections (ic)
    AsNode *pNode = 0;
    QFileInfoList fileInfos = path.entryInfoList();
    //foreach( QFileInfo fileInfo, fileInfos )
    int sz = fileInfos.size();
    int i = 0;

    while( i<sz )
    {
        const QFileInfo & fileInfo = fileInfos[ i ];

        std::string str=fileInfo.fileName().toStdString();
        if ( fileInfo.suffix() == "in" )
        {
            pNode = asLoadNodeTree( fileInfo.filePath() );
        }
        else if ( fileInfo.suffix() == "ic" )
        {
            asLoadObject( fileInfo.filePath() );
        }
        ++i;
    }

    // Then load objects deltas (io)
    //foreach( QFileInfo fileInfo, fileInfos )
    i = 0;
    while( i<sz )
    {
        const QFileInfo & fileInfo = fileInfos[ i ];
        if ( fileInfo.suffix() == "io" )
        {
            AsObject* pObj = asLoadObject( fileInfo.filePath() );

        }
        ++i;
    }

    return pNode;
}

AsNode * AsFileIO::asLoadObjectTree( AsVirtualFolder *pFolder )
{
//    AS_DEBUG("pFolder->asGetFilePath(): " << pFolder->asGetFilePath());
//    As::logAndAssert( m_pFactory != 0, "AsFileIO", "asLoadObjectTree(AsVirtualFolder)", "m_pFactory is NULL" );
    if ( m_pFactory == NULL )
    {
        return NULL;
    }

//    As::logAndAssert( pFolder != 0, "AsFileIO", "asLoadObjectTree(AsVirtualFolder)", "pFolder is NULL" );
    if( pFolder == NULL )
    {
        return NULL;
    }

    AsNode *pNode = NULL;

    pFolder->asResetIndexIterator();
    bool finished = false;
    while( !finished )
    {
        QByteArray file;
        QString filename;

        bool ok = pFolder->asReadNextFile( filename, file );
        if ( ok )
        {
            QFileInfo info( filename );
            if ( info.suffix() == "in" )
            {
                pNode = asLoadNodeTree( file );
//                As::logAndAssert( (pNode != NULL), "AsFileIO", "asLoadObjectTree(AsVirtualFolder)", qPrintable("asLoadNodeTree returned NULL: " + filename ));
            }
            else if ( info.suffix() == "io" )
            {
                AsObject* pObj = asLoadObject( file );
//                As::logAndAssert( (pObj != NULL), "AsFileIO", "asLoadObjectTree(AsVirtualFolder)", qPrintable("asLoadObject returned NULL: " + filename ));
            }
        }
        else
        {
            finished = true;
        }
    }

    return pNode;
}

bool AsFileIO::asWriteObjectFile( AsObject *pObject, const QString& sDir, const QString& sName )
{
//	AS_DEBUG("sName: " << sName);  // see below
    // Write the file.
    QFile fOut;
    QString sFilename;
    if ( sName.isNull() )
    {
        sFilename = AsFileUtils::asGetObjectFilename( pObject );
//        As::writeErrorLog( "AsFileIO", "asWriteObjectFile (dir version)", "passed name blank", As::LOGLEVEL_TRACING );
    }
    else
    {
        sFilename = sName;
    }

//    AS_DEBUG("sFilename: " << sFilename << ", sDir:" << sDir );

    QString filePath = sDir + QDir::separator() + sFilename;
    fOut.setFileName( filePath );
//    As::writeErrorLog("AsFileIO", "asWriteObjectFile (dir)", qPrintable("writing to: " + filePath ),As::LOGLEVEL_TRACING);

    if ( fOut.exists() )
    {
        bool result = QFile::remove( filePath );
//        As::logAndAssert( result, "AsFileIO", "asWriteObjectFile", qPrintable("Qt reports failure to remove file: " + filePath ));
    }

    bool openres = fOut.open( QIODevice::WriteOnly );
//    As::logAndAssert( openres, "AsFileIO", "asWriteObjectFile", qPrintable("Qt reports failure to open file: " + filePath ));

    if( !openres )
    {
        return false;
    }

    AsObjectStreamer streamer( &fOut );
    if( !streamer.asWriteHeader() )
    {
        return false;
    }

    if( !streamer.asWriteObject( pObject ) )
    {
        return false;
    }
    fOut.close();

    return true;
}

bool AsFileIO::asWriteObjectFile( AsObject *pObject, AsVirtualFolder *pFolder, const QString& sName )
{
//	AS_DEBUG("sName: " << sName);  // See below
    QString sFilename;
    if ( sName.isNull() )
    {
        sFilename = AsFileUtils::asGetObjectFilename( pObject );
//        As::writeErrorLog( "AsFileIO", "asWriteObjectFile (vir folder version)", "passed name blank", As::LOGLEVEL_TRACING );
    }
    else
    {
        sFilename = sName;
    }
//    AS_DEBUG("pFolder->asGetFilePath(): " << pFolder->asGetFilePath() << ", sFilename:" << sFilename)

//    As::writeErrorLog("AsFileIO", "asWriteObjectFile (virtual folder)", qPrintable("writing to: " + sFilename ), As::LOGLEVEL_TRACING);

    QByteArray arr;
    QBuffer buffer( &arr );
    bool openres = buffer.open( QIODevice::WriteOnly );
//    As::logAndAssert( openres, "AsFileIO", "asWriteObjectFile", qPrintable("Qt reports failure to open buffer saving file: " + sFilename ));
    if( !openres )
    {
        return false;
    }

    AsObjectStreamer streamer( &buffer );
    if( !streamer.asWriteHeader() )
    {
        return false;
    }
    if( !streamer.asWriteObject( pObject ) )
    {
        return false;
    }

    buffer.close();

    pFolder->asAddFile( sFilename, arr );

    return true;
}

bool AsFileIO::asWriteNodeTreeFile( AsNode *pNode, const QString& sDir, int nMaxGenerations )
{
//	AS_DEBUG("sDir: " << sDir);  // see below
    QFile fOut;
    QString sFilename = AsFileUtils::asGetNodeTreeFilename( pNode );
    QString filePath = sDir + QDir::separator() + sFilename;
    fOut.setFileName( filePath );

//    AS_DEBUG("sFilename:" << sFilename << ", filePath:" << filePath );

    if ( fOut.exists() )
    {
        bool result = QFile::remove( filePath );
//        As::logAndAssert( result, "AsFileIO", "asWriteNodeTreeFile", qPrintable("Qt reports failure to remove file: " + filePath ));
    }
//    As::writeErrorLog("AsFileIO", "asWriteNodeTreeFile (dir)", qPrintable("writing to: " + filePath ), As::LOGLEVEL_TRACING);

    bool openres = fOut.open( QIODevice::WriteOnly );
//    As::logAndAssert( openres, "AsFileIO", "asWriteNodeTreeFile", qPrintable("Qt reports failure to open file: " + filePath ));
    if( !openres )
    {
        return false;
    }
    AsObjectStreamer outStream( &fOut );
    if( !outStream.asWriteAsNodes( pNode, nMaxGenerations ) )
    {
        return false;
    }
    fOut.close();

    return true;
}

bool AsFileIO::asWriteNodeTreeFile( AsNode *pNode, AsVirtualFolder *pFolder, int maxGenerations, const QString& filePath )
{
//    AS_DEBUG("pFolder->asGetFilePath(): " << pFolder->asGetFilePath() << ", filePath: " << filePath);
    QString sFilename = filePath;
    if ( sFilename.isEmpty() )
    {
        sFilename = AsFileUtils::asGetNodeTreeFilename( pNode );
    }

//    As::writeErrorLog("AsFileIO", "asWriteNodeTreeFile (virtual folder)", qPrintable("writing to: " + sFilename ), As::LOGLEVEL_TRACING);

    QByteArray arr;
    QBuffer buffer( &arr );
    bool openres = buffer.open( QIODevice::WriteOnly );
//    As::logAndAssert( openres, "AsFileIO", "asWriteNodeTreeFile(3)", qPrintable("Qt reports failure to open buffer for file: " + sFilename ));
    if( !openres )
    {
        return false;
    }
    AsObjectStreamer outStream( &buffer );
    if( !outStream.asWriteAsNodes( pNode, maxGenerations ) )
    {
        return false;
    }
    buffer.close();

    pFolder->asAddFile( sFilename, arr );

    return true;
}


AsVirtualFolder * AsFileIO::asUnzipPage( const QString& sPageFile )
{
    LOGDEBUG("sPageFile: %s", sPageFile.toUtf8().data());

    QFileInfo pagefile( sPageFile );
    if ( !pagefile.exists() )
    {
        return NULL;
    }

    bool ok;
    int id = pagefile.baseName().toInt( &ok );
    if ( !ok )
    {
        return NULL;
    }

    LOGDEBUG("sPageFile id: %d", id);

   m_pTempVirtualPageFolder = m_pFlipchart->asGetFactoryPointer()->asGetVirtualFolder( id );
    if ( m_pTempVirtualPageFolder == NULL )
    {
        return NULL;
    }

    AsZip *pZip = new AsZip();
    pZip->bindAsReportFile([this](const QString& path, const QByteArray& mes){
        asFileReportedOnPageLoad(path, mes);
    });
    bool result = pZip->asReportFiles( sPageFile.toUtf8().data() );
    delete pZip;

    return m_pTempVirtualPageFolder;
}




AsNode * AsFileIO::asLoadNodeTree( const QString& sNodeTreeFilePath )
{
    LOGDEBUG("sNodeTreeFilePath: %s", sNodeTreeFilePath.toUtf8().data());

    if ( m_pFactory == 0 )
    {
        return 0;
    }

    QFile fIn;
    AsObjectStreamer inStream( &fIn );
    fIn.setFileName( sNodeTreeFilePath );
    fIn.open( QIODevice::ReadOnly );

    AsNode *pNode = inStream.asReadAsNodes( m_pFactory );
    fIn.close();
    return pNode;
}

AsNode * AsFileIO::asLoadNodeTree( QByteArray& file )
{
    if ( m_pFactory == NULL )
    {
//        As::logAndAssert( false, "AsFileIO", "asLoadNodeTree(file)", "m_pFactory is null" );
        return NULL;
    }
//    As::writeErrorLog("AsFileIO", "asLoadNodeTree (bytearray)", "", As::LOGLEVEL_TRACING);

    QBuffer buffer( &file );
    AsObjectStreamer inStream( &buffer );
    bool openres = buffer.open( QIODevice::ReadOnly );
//    As::logAndAssert( openres, "AsFileIO", "asLoadNodeTree(file)", "Qt reports failure to open bytearray buffer" );
    AsNode *pNode = inStream.asReadAsNodes( m_pFactory );
    buffer.close();
    return pNode;
}


AsObject * AsFileIO::asLoadObject( const QString& sPathAndFilename )
{
    LOGDEBUG("sNodeTreeFilePath: %s", sPathAndFilename.toUtf8().data());

    if ( m_pFactory == 0 )
    {
        return 0;
    }


    QFile fIn;
    fIn.setFileName( sPathAndFilename );
    fIn.open( QIODevice::ReadOnly );

    AsObjectStreamer inStream( &fIn );
    AsObject *pObject = inStream.asReadObjects( m_pFactory );
    fIn.close();
    return pObject;
}

AsObject * AsFileIO::asLoadObject( QByteArray& file )
{
    if ( m_pFactory == 0 )
    {
//        As::logAndAssert( false, "AsFileIO", "asLoadObject(file)", "m_pFactory is null" );
        return 0;
    }

//    As::writeErrorLog("AsFileIO", "asLoadObject (bytearray)", "", As::LOGLEVEL_TRACING);
    QBuffer buffer( &file );
    AsObjectStreamer inStream( &buffer );
    bool openres = buffer.open( QIODevice::ReadOnly );
//    As::logAndAssert( openres, "AsFileIO", "asLoadObject(file)", "Qt reports failure to open bytearray buffer" );
    AsObject *pObject = inStream.asReadObjects( m_pFactory );
    buffer.close();
    return pObject;
}

bool AsFileIO::asSaveObject( AsObject *pObject, const QString& sPath, const QString& sFilename )
{
//    AS_DEBUG("pObject->asGetID():" << pObject->asGetID() << ", sPath:" << sPath << ", sFilename:" << sFilename);
//    As::logAndAssert( pObject != 0, "AsFileIO", "asSaveObject", "pObject is NULL" );
    if ( pObject == 0 )
    {
        return false;
    }
    QString msg = QString("pObject id: %1, type %2, path: %3 file: %4").arg( pObject->asGetID() ).arg( pObject->asGetTypeName() ).arg( sPath ).arg( sFilename );
//    As::writeErrorLog( "AsFileIO", "asSaveObject", qPrintable(msg), As::LOGLEVEL_TRACING );

    QString sTargetPath;
    if ( sPath.isNull() )
    {
        if( !asSetupFlipchartPointer() )
            return false;

        // Get the temp path.
        sTargetPath = m_pFlipchart->asGetFlipchartWorkingPath();
    }
    else
    {
        sTargetPath = sPath;
    }

//    As::writeErrorLog( "AsFileIO", "asSaveObject", qPrintable("sTargetPath = " + sTargetPath + "/" + sFilename), As::LOGLEVEL_TRACING );

    // Write the object.
    if( !asWriteObjectFile( pObject, sTargetPath, sFilename ) )
    {
        return false;
    }

    return true;
}

bool AsFileIO::asSaveObject( AsObject *pObject, AsVirtualFolder *pFolder, const QString& filename )
{
//    AS_DEBUG("pFolder->asGetFilePath(): " << pFolder->asGetFilePath() << ", filename:" << filename);
    QString msg = QString("filename: %1, obj id: %2, obj type: %3, folder path: %4").arg(filename).arg( pObject->asGetID()).arg(pObject->asGetTypeName()).arg(pFolder->asGetFilePath());
//    As::writeErrorLog( "AsFileIO", "asSaveObject(3)", qPrintable(msg), As::LOGLEVEL_TRACING );

//    As::logAndAssert( pObject != 0, "AsFileIO", "asSaveObject(3)", "pObject is NULL" );
    if ( pObject == 0 )
        return false;

//    As::logAndAssert( pFolder != 0, "AsFileIO", "asSaveObject(3)", "pFolder is NULL" );
    if ( pFolder == NULL )
        return false;

    if( !asWriteObjectFile( pObject, pFolder, filename ) )
    {
        return false;
    }

    return true;
}

void AsFileIO::asFileReportedOnPageLoad(const QString& path, const QByteArray& data)
{
    LOGDEBUG("asFileReportedOnPageLoad filename:%s", path.toUtf8().data());

    QString newFilename = AsFileUtils::asCleanPath(path);
    QFileInfo info( newFilename );
    m_pTempVirtualPageFolder->asAddFile( info.fileName(), data, newFilename );
}