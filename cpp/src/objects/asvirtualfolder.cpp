// Implements the AsVirtualFolder class.
// (c) 2009 - Promethean Ltd
// Paul Wareing

#include <QDir>

#include "asvirtualfolder.h"
#include "../asfactory.h"
#include "../io/asfileio.h"
#include "../util/commonlog.h"


//-------------------------------- Debug Macros -------------------------------
// Uncomment line below for event debug output
//#define AS_USE_VIRTUALFOLDER_DEBUG
//#if defined( AS_USE_VIRTUALFOLDER_DEBUG )
//static int debugCounter = 0;
//    #define AS_VIRTUALFOLDER_DEBUG() qDebug() << "[" << debugCounter++ << "]" << __FUNCTION__
//    #define AS_VIRTUALFOLDER_DEBUG1(arg1) qDebug() << "[" << debugCounter++ << "]" << __FUNCTION__ << arg1
//#else
//#define AS_VIRTUALFOLDER_DEBUG()
//#define AS_VIRTUALFOLDER_DEBUG1(arg1)
//#endif
//-----------------------------------------------------------------------------


AsVirtualFolder::AsVirtualFolder( AsFactory *pFactory ) : AsObject( pFactory )
{
//    AS_VIRTUALFOLDER_DEBUG();
    m_FolderId = 0;
}

AsVirtualFolder::~AsVirtualFolder()
{
//    AS_VIRTUALFOLDER_DEBUG();
    if(m_File.isOpen())
    {
        LOGDEBUG("file is close","");
        m_File.close();
    }
    if( QFile::exists( m_FilePath ))
    {
        bool removeRes = QFile::remove( m_FilePath );
//        As::logAndAssert( removeRes, "AsVirtualFolder", "Destructor", qPrintable("Failed to remove virtual folder: " + m_FilePath) );
    }
}

const AsVirtualFolderIndex& AsVirtualFolder::asGetIndex( void ) const
{
//    AS_VIRTUALFOLDER_DEBUG();
    return m_Index;
}

void AsVirtualFolder::asSetIndex( const AsVirtualFolderIndex& idx )
{
//    AS_VIRTUALFOLDER_DEBUG();
    m_Index = idx;
}

void AsVirtualFolder::asCloseVirtualFolderFile()
{
//    AS_VIRTUALFOLDER_DEBUG();
    if(m_File.isOpen())
    {
        m_File.close();
    }
}

void AsVirtualFolder::asOpenVirtualFolderFile()
{
//    AS_VIRTUALFOLDER_DEBUG();
    if(m_File.exists())
    {
        bool res = m_File.open( QIODevice::ReadWrite );
        if( !res )
        {
//            AS_VIRTUALFOLDER_DEBUG1( "FAILED: Could not open filename: " << m_File.fileName() << " - " << m_File.errorString() );
//            As::logAndAssert( res, "AsVirtualFolder", "asOpenVirtualFolderFile", qPrintable("Failed to open virtual folder: " + m_File.fileName()) );
        }
    }
}


void AsVirtualFolder::asInitialise( const QString& path, int id, const QString& filename  )
{
//    AS_VIRTUALFOLDER_DEBUG1( "Path: " << path << " id: " << id << " filename: " << filename );
    QString file = filename;
    if ( file.isEmpty() && id == 0 )
    {
        int i = 1;
        bool finished = false;
        while ( !finished )
        {
            file = QString::number( i ) + ".if";
            QString filePath = path + QDir::separator() + file;
            m_File.setFileName( filePath );
            if ( !m_File.exists() )
            {
                finished = true;
            }
            else
            {
                ++i;
            }
        }
    }
    else if ( !filename.isEmpty() )
    {
        file += ".if";
    }
    else
    {
        file = QString::number( id ) + ".if";
    }

    m_FolderId = id;
    QString filePath = path + QDir::separator() + file;
    m_File.setFileName( filePath );
    bool res = false;
    int count=0;
    while(res=m_File.open( QIODevice::ReadWrite ),!res){
        count++;
        LOGDEBUG("try times is %d",count);
    }
    if( !res )
    {

        int  err= m_File.error();
        LOGDEBUG("%s id is:%d","open file error!",err);
        LOGDEBUG("%s",filePath.toStdString().data());
//        AS_VIRTUALFOLDER_DEBUG1( "FAILED: Could not open filePath: " << filePath << " - " << m_File.errorString() );
//        As::logAndAssert( res, "AsVirtualFolder", "asInitialise", qPrintable("Failed to open virtual folder: " + m_File.fileName()) );
    }
    m_FilePath = filePath;
    m_Path = path;
}

void AsVirtualFolder::asRepair( AsVirtualFolderIndex *pIndex, const QString& filePath, int id )
{
//    AS_VIRTUALFOLDER_DEBUG();
    this->asSetIndex( *pIndex );
    m_FolderId = id;
    m_FilePath = filePath;
    QFileInfo info( filePath );
    m_Path = info.path();
    m_File.setFileName( filePath );
    m_File.open( QIODevice::ReadWrite );
}

quint32 AsVirtualFolder::asGetFolderId( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
    return m_FolderId;
}

const QString& AsVirtualFolder::asGetPath( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
    return m_Path;
}

const QString& AsVirtualFolder::asGetFilePath( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
    return m_FilePath;
}

void AsVirtualFolder::asAddFile( const QString& filename, const QByteArray& file, const QString& sNewFilePath )
{
//    AS_VIRTUALFOLDER_DEBUG1( "filename: " << filename << "sNewFilePath: " << sNewFilePath );
    /** NN: this is to fix the flipchart corruption issue in case of Test / Response node.
    When the flipchart is corrupted we landed up in a scenarion where 2 test / response node trees are present in
    the virtual folder and actual fpg (e.g.(1) 108.in (2) i08.in/108.in).
    This was leading to random crash and unknown behaviour.This fix will make sure that we do not have 2 test node entries
    and will repair any broken flipcharts
    note:this is just a patch and should be removed when we move to new file format*/
    if(m_FilePathInfo.contains(filename))
    {
        QString sOrgFilePath = m_FilePathInfo.value(filename);

        if(sOrgFilePath != sNewFilePath)
        {
            QString sTempPath = filename + QDir::separator() + filename;

            if(sTempPath == sOrgFilePath)
            {
                return;
            }
        }
    }

    // Remove old entry from index, if one exists...
    m_Index.asGetFolderIndexPointer()->remove( filename );

    m_FilePathInfo.insert(filename,sNewFilePath);


    // Add new index entry...
    AsFileInfo info;
    info.m_sFilename = filename;
    info.m_pos = m_File.size();
    info.m_size = file.size();
    m_Index.asGetFolderIndexPointer()->insert( filename, info );

    // Write the file...
    m_File.seek( m_File.size() );
    qint64 bytes = m_File.write( file );

    if( bytes != info.m_size)
    {
//        AS_VIRTUALFOLDER_DEBUG1( "FAILED: write error" << "filename: " << filename);
//        As::logAndAssert( false, "AsVirtualFolder", "asAddFile", qPrintable("Bytes written doesn't equal info size: " + filename ));
    }
    m_File.flush();
}

void AsVirtualFolder::asRemoveFile( const QString& filename )
{
//    AS_VIRTUALFOLDER_DEBUG1( "filename: " << filename );
    // To remove a file we simply remove its entry from the index. 
    // For the future, we could also remove its section from the file.  Beware performance...
    AsFolderIndex* pFolderIndex = m_Index.asGetFolderIndexPointer();
    bool res = pFolderIndex->remove( filename );
    if( !res )
    {
//        AS_VIRTUALFOLDER_DEBUG1( "FAILED: Could not remove file" << "filename: " << filename);
//        As::writeErrorLog( "AsVirtualFolder", "asRemoveFile", qPrintable("Failed to remove file: " + filename), As::LOGLEVEL_WARNING );
    }
}

int AsVirtualFolder::asCount( void )
{
//    AS_VIRTUALFOLDER_DEBUG1( "count: " << m_Index.asGetFolderIndexPointer()->count() );
    return m_Index.asGetFolderIndexPointer()->count();
}

void AsVirtualFolder::asResetIndexIterator( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
    m_IndexIterator = m_Index.asGetFolderIndexPointer()->constBegin();
}

bool AsVirtualFolder::asReadNextFile( QString& filename, QByteArray& file )
{
//    AS_VIRTUALFOLDER_DEBUG();
    if ( m_IndexIterator == m_Index.asGetFolderIndexPointer()->constEnd() )
        return false;

    AsFileInfo info = m_IndexIterator.value();
    m_File.seek( info.m_pos );
    file = m_File.read( info.m_size );
    filename = info.m_sFilename;
    m_IndexIterator++;

//    AS_VIRTUALFOLDER_DEBUG1( "filename: " << filename );
    return true;
}

bool AsVirtualFolder::asReadFile( const QString& filename, QByteArray& file )
{
//    AS_VIRTUALFOLDER_DEBUG1( "filename: " << filename );
    if ( !m_Index.asGetFolderIndexPointer()->contains( filename ) )
    {
//        AS_VIRTUALFOLDER_DEBUG1( "FAILED: Could not find filename: " << filename );
        return false;
    }

    AsFileInfo info = m_Index.asGetFolderIndexPointer()->value( filename );
    m_File.seek( info.m_pos );
    file = m_File.read( info.m_size );
    return true;
}

QStringList AsVirtualFolder::asGetSubFilesAndFolders( const QString& root )
{
//    AS_VIRTUALFOLDER_DEBUG1( "root: " << root );
    QStringList list;
    QHash< QString, AsFileInfo >::const_iterator iterator = m_Index.asGetFolderIndexPointer()->constBegin();
    while( iterator != m_Index.asGetFolderIndexPointer()->constEnd() )
    {
        QString path = iterator.key();
        if ( path.startsWith( root ))
        {
            int start = root.length();
            if ( path.at( start ) == QDir::separator() )
                start++;

            int pos = path.indexOf( QDir::separator(), start );
            QString sub = path.left( pos );
            if ( !list.contains( sub ))
                list.append( sub );
        }
        ++iterator;
    }
    return list;
}

void AsVirtualFolder::asClear( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
    m_File.close();
    QFile::remove( m_FilePath );
    m_File.open( QIODevice::ReadWrite );
    m_Index.asGetFolderIndexPointer()->clear();
}

QStringList AsVirtualFolder::asListFiles( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
    QStringList files;
    QList< AsFileInfo > infos = m_Index.asGetFolderIndexPointer()->values();
    for( int i=0 ; i<m_Index.asGetFolderIndexPointer()->count() ; ++i )
    {
        AsFileInfo info = infos.at( i );
        files.append( info.m_sFilename );
    }
    return files;
}

void AsVirtualFolder::asWriteIndex( void )
{
//    AS_VIRTUALFOLDER_DEBUG();
//    As::writeErrorLog( "AsVirtualFolder", "asWriteIndex", "", As::LOGLEVEL_TRACING );
//    AsFileIO fileIO( m_pAsFactory );
//    fileIO.asSaveObject( &( this->m_Index ), m_Path, QString( "index" ) );
}
