#include "aszipfileinfo.h"



AsZipFileInfo::AsZipFileInfo()
{
    m_sFilename.clear();
    m_sDateCreated.clear();
    m_sDateModified.clear();
    m_sDateAccessed.clear();
    m_nUncompressedSize = 0;
    m_bCompressed = false;
    m_nCompressedSize = 0;
}

AsZipFileInfo::~AsZipFileInfo()
{

}

bool AsZipFileInfo::asReadFileInfo( QDataStream& inStream )
{
    m_sFilename = asReadStringUTF16( inStream );

    // Get the date and time the file was created.
    m_sDateCreated = asReadStringUTF16( inStream );

    // Get the date and time the file was last modified.
    m_sDateModified = asReadStringUTF16( inStream );

    // Get the date and time the file was last accessed.
    m_sDateAccessed = asReadStringUTF16( inStream );

    // Then we get the uncompressed file size.
	inStream >> ( qint64& )m_nUncompressedSize;

    // Then we read in whether this file is compressed or not.
    inStream >> ( bool& ) m_bCompressed;
    if ( m_bCompressed )
    {
        inStream >> ( qint64& ) m_nCompressedSize;
    }

    return true;
}

qint64  AsZipFileInfo::asGetFileInfoSize( void )
{
    qint64 nSize = 0;

    // Filename.
    nSize += sizeof( qint32 );
    nSize += m_sFilename.size() * 2;

    // Date Created.
    nSize += sizeof( qint32 );
    nSize += m_sDateCreated.size() * 2;

    // Date Modified.
    nSize += sizeof( qint32 );
    nSize += m_sDateModified.size() * 2;

    // Date Accessed.
    nSize += sizeof( qint32 );
    nSize += m_sDateAccessed.size() * 2;
    
    // Uncompressed File Size.
    nSize += sizeof( qint64 );      

    // Compressed.
    nSize += sizeof( bool );

    // CompressedFileSize.
    if ( m_bCompressed )
    {
        nSize += sizeof( qint64 );
    }

    return nSize;
}

bool AsZipFileInfo::asWriteFileInfo( QDataStream& outStream )
{
    asWriteStringUTF16( outStream, m_sFilename );
    asWriteStringUTF16( outStream, m_sDateCreated );
    asWriteStringUTF16( outStream, m_sDateModified );
    asWriteStringUTF16( outStream, m_sDateAccessed );
    outStream << ( qint64 ) m_nUncompressedSize;
    outStream << ( bool ) m_bCompressed;
    if ( m_bCompressed )
    {
        outStream << ( qint64 ) m_nCompressedSize;
    }
    return true;
}

QString AsZipFileInfo::asFormatFileInfo( void )
{
    //TODO - Implement full version.
    return m_sFilename;
}

qint64 AsZipFileInfo::asGetUncompressedSize( void )
{
    return m_nUncompressedSize;
}

qint64 AsZipFileInfo::asGetCompressedSize( void )
{
    return m_nCompressedSize;
}

bool AsZipFileInfo::asGetCompressed( void )
{
    return m_bCompressed;
}

QString& AsZipFileInfo::asGetFilename( void )
{
    return m_sFilename;
}

QString& AsZipFileInfo::asGetDateCreated( void )
{
    return m_sDateCreated;
}

QString& AsZipFileInfo::asGetDateModified( void )
{
    return m_sDateModified;
}

QString& AsZipFileInfo::asGetDateAccessed( void )
{
    return m_sDateAccessed;
}

QString AsZipFileInfo::asReadStringUTF16( QDataStream& inStream )
{
    QString sString;
    inStream >> sString;
    return sString;
}

void AsZipFileInfo::asWriteStringUTF16( QDataStream& outStream, const QString& sString )
{
    outStream << sString;
}
