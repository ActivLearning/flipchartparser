// Defintion of the AsFileIO class.
// (c) 2006 Promethean Technologies Group Ltd.

#ifndef ASFILEIO_H
#define ASFILEIO_H

#include <QString>
#include <QFile>
#include "../objects/asflipchart.h"
#include "../objects/asvirtualfolder.h"

class AsObject;
class AsNode;
class AsFactory;
class AsObjectStreamer;
class AsVirtualFolder;

class AsFileIO
{


public:

    enum AsEnumFileType
    {
        ASFILETYPE_UNKNOWN = 0,
        ASFILETYPE_V2,
        ASFILETYPE_INSPIRE
    };

    AsFileIO( AsNode *flipchartNode );
    AsFileIO(AsFlipchart *flipchart);
    AsFileIO( AsFactory *factory );
    ~AsFileIO();

    // Interface - General AsObject Pattern - Load/Save whole node tree & objects...

    AsNode * asLoadObjectTree( const QString& sPath );



    bool asFindIndexFilename( AsVirtualFolder * pFolder, QString & indexFilename );
    void asLoadObjectsUsingNodeTree( AsVirtualFolder *pFolder, AsNode * pIndexNode );

    // Interface - Specific file IO
    AsNode * asLoadPage( AsNode *page);


    AsNode * asLoadNodeTree( const QString& );
    AsNode * asLoadNodeTree( QByteArray& );
    AsNode * asLoadObjectTree( AsVirtualFolder * );
    AsObject * asLoadObject( const QString& );
    AsObject * asLoadObject( QByteArray& );

    bool asLoadPageThumbnail( AsNode *pPageNode, QPixmap& thumbnail );
    bool asSaveObject( AsObject *object, const QString& path = 0, const QString& filename = 0 );
    bool asSaveObject( AsObject *object, AsVirtualFolder *, const QString& filename = 0 );

    // File Types.
    static AsEnumFileType asGetFileType( const QString& ){return ASFILETYPE_UNKNOWN;}




    bool asSetupFlipchartPointer();

private:
    void asFileReportedOnPageLoad( const QString&, const QByteArray& );

private:

    bool asWriteObjectFile( AsObject *, const QString& path, const QString& filename = 0 );
    bool asWriteObjectFile( AsObject *, AsVirtualFolder *, const QString& filename = 0 );
    bool asWriteNodeTreeFile( AsNode *, const QString& path, int maxGenerations = 0 );
    bool asWriteNodeTreeFile( AsNode *, AsVirtualFolder *, int maxGenerations = 0, const QString& filePath = 0 );

    AsVirtualFolder * asUnzipPage( const QString& pagefile );
    void asUnzipPageToExisting( const QString& pagefile, AsVirtualFolder* pFolder );


    AsNode *m_pFlipchartNode;
    AsFlipchart *m_pFlipchart;

    AsFactory *m_pFactory;
    QFile * m_pCurrentFile;
    AsObjectStreamer * m_pStreamer;

    // Cache to Structured Storage pointers...
    AsVirtualFolder *m_pTempVirtualPageFolder;

};

#endif // ASFILEIO_H
