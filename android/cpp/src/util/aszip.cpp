//
// Created by admin on 2019-08-22.
//

#include "aszip.h"

#include <QString>
#include <QFile>
#include <QDataStream>

#include "commonlog.h"
#include "../global/asdefines.h"
#include "aszipfileinfo.h"
#include "zlib.h"
namespace
{
    const int MaxAllocSize = INT_MAX;
    typedef QTypedArrayData<char> Data;
    struct QByteArrayDataDeleter
    {
        static inline void cleanup(QTypedArrayData<char> *d)
        { if (d) QTypedArrayData<char>::deallocate(d); }
    };
    static QByteArray invalidCompressedData()
    {
        return QByteArray();
    }
    QByteArray qUncompress(const uchar* data, int nbytes)
    {
        if (!data) {
            return QByteArray();
        }
        if (nbytes <= 4) {
            if (nbytes < 4 || (data[0]!=0 || data[1]!=0 || data[2]!=0 || data[3]!=0))
            return QByteArray();
        }
        ulong expectedSize = uint((data[0] << 24) | (data[1] << 16) |
                                  (data[2] <<  8) | (data[3]      ));
        ulong len = qMax(expectedSize, 1ul);
        const ulong maxPossibleSize = MaxAllocSize - sizeof(Data);
        if (Q_UNLIKELY(len >= maxPossibleSize)) {
            // QByteArray does not support that huge size anyway.
            return invalidCompressedData();
        }

        QScopedPointer<Data, QByteArrayDataDeleter> d(Data::allocate(expectedSize + 1));
        if (Q_UNLIKELY(d.data() == nullptr))
            return invalidCompressedData();

        d->size = expectedSize;
        forever {
            ulong alloc = len;

            int res = ::uncompress((uchar*)d->data(), &len,
                                   data+4, nbytes-4);

            switch (res) {
                case Z_OK:
                    Q_ASSERT(len <= alloc);
                    Q_UNUSED(alloc);
                    d->size = len;
                    d->data()[len] = 0;
                    {
                        QByteArrayDataPtr dataPtr = { d.take() };
                        return QByteArray(dataPtr);
                    }

                case Z_MEM_ERROR:
                    return QByteArray();

                case Z_BUF_ERROR:
                    len *= 2;
                    if (Q_UNLIKELY(len >= maxPossibleSize)) {
                        // QByteArray does not support that huge size anyway.
                        return invalidCompressedData();
                    } else {
                        // grow the block
                        Data *p = Data::reallocateUnaligned(d.data(), len + 1);
                        if (Q_UNLIKELY(p == nullptr))
                            return invalidCompressedData();
                        d.take();   // don't free
                        d.reset(p);
                    }
                    continue;

                case Z_DATA_ERROR:
                    return QByteArray();
            }
        }
    }
}

AsZip::AsZip()
{

}

AsZip::~AsZip()
{

}


void AsZip::bindAsReportFile(std::function<void(const QString&, const QByteArray&)> func)
{
    asReportFile = func;
}


bool AsZip::asReportFiles( const std::string& filename )
{
    // First, we must check that we can open the file for reading.
    bool noError = true;
    QString sFlipChartFilename = QString::fromStdString( filename );
    asFormatFilename( sFlipChartFilename );

    QFile inFile( sFlipChartFilename );
    QDataStream inStream( &inFile );
    inStream.setByteOrder( QDataStream::LittleEndian );
    if( !inFile.open( QIODevice::ReadOnly ) )
    {
        m_nLastError = (quint16)ERROR_OPENING_FILE_FOR_READING;
        return false;
    }

    // Next, we must check that the file is a flipchart file by attempting
    // to read the header.
    qint64 nBytesRead = 0;
    nBytesRead = asReadHeader( inStream, m_sVersion, m_sComment );
    if ( nBytesRead == 0 )
    {
        m_nLastError = (quint16)ERROR_NOT_A_FLIPCHART_FILE;
        return false;
    }

    // Get the total number of bytes to read and signal that we are at the start.
    qint64 nBytesToRead = inFile.size();
    if(asPercentDone != NULL)
    {
        asPercentDone(0);
    }

    // Now we extract the files.
    // We loop through each file in the bundle.
    while ( !inStream.atEnd() )
    {
        AsZipFileInfo  *pFileInfo = new AsZipFileInfo;
        if ( !pFileInfo->asReadFileInfo( inStream ) )
        {
            delete pFileInfo;
            return false;
        }
        qint64 nFileSize = pFileInfo->asGetUncompressedSize();
        if ( pFileInfo->asGetCompressed() )
        {
            nFileSize = pFileInfo->asGetCompressedSize();
        }

        bool readError = false;
        if( inStream.atEnd() )
        {
            readError = true;
        }
        QByteArray inFileData;
        if( asReadByteArray( inStream, nFileSize, inFileData ) )
        {
            // UnCompress the file if compressed in flip chart file.
            QByteArray rawFile = inFileData;
            if( !readError )
            {
                if ( pFileInfo->asGetCompressed() )
                {
                    rawFile = ::qUncompress( reinterpret_cast<const uchar *>( inFileData.data() ),inFileData.size() );
                }
            }
            else
            {
                rawFile.clear();
            }

            QString sFilename = pFileInfo->asGetFilename();

            if(asReportFile != NULL)
            {
                asReportFile(sFilename,rawFile);
            }

            // Update the progress indication counter.
            nBytesRead += pFileInfo->asGetFileInfoSize();
            nBytesRead += nFileSize;
            double fPercent = ( ( double )nBytesRead / ( double )nBytesToRead ) * 100;

            if(asPercentDone != NULL)
            {
                asPercentDone(( int )fPercent);
            }
        }
        else
        {
            noError = false;
        }
        delete pFileInfo;
    }

    inFile.close();
    return true;
}


/******* private methods ********/

quint32 AsZip::asReadHeader( QDataStream& inStream,
                      QString& sExistingVersion,
                      QString& sExistingComment )
{
    quint32 nBytesRead = 0;

    // We must first check that the file we are attempting to read is
    // a flipchart file.
    quint64 nFirst8Bytes;
    inStream >> ( quint64& ) nFirst8Bytes;
    if ( nFirst8Bytes != FILEHEADER_FLIPCHART )
    {
        m_nLastError = (quint16)ERROR_NOT_A_FLIPCHART_FILE;
        return 0;
    }
    nBytesRead += sizeof( quint64 );

    // Ok, we have a flipchart file.  What version of the streamer was
    // it streamed with??  If it is Qt_4_0 or earlier then we will
    // set our version to it.  If it is later then we cannot handle
    // it??
    qint16 nStreamVersion;
    inStream >> ( qint16& ) nStreamVersion;
    inStream.setVersion( nStreamVersion );
    nBytesRead += sizeof( qint16 );

    // Read in the version string.
    sExistingVersion = asReadStringUTF16( inStream );
    nBytesRead += sizeof( qint32 ) + ( sExistingVersion.size() * 2 );

    // Read in the comment.
    sExistingComment = asReadStringUTF16( inStream );
    nBytesRead += sizeof( qint32 ) + ( sExistingComment.size() * 2 );

    // Read in the file encrytion level.
    inStream >> ( qint16& ) m_nFileEncryption;
    nBytesRead += sizeof( qint16 );

    // Read in the string encoding.
    inStream >> ( qint16& ) m_nStringEncoding;
    nBytesRead += sizeof( qint16 );

    return nBytesRead;
}

bool AsZip::asReadByteArray( QDataStream &inStream, int nCount, QByteArray & aData )
{
    char *buffer = ( char* ) ::malloc( nCount );

    if( !buffer )
    {
        return false;
    }

    inStream.readRawData( buffer, nCount );
    QByteArray tempData( buffer, nCount );
    ::free ( buffer );
    aData = tempData;
    return true;
}


QString AsZip::asReadStringUTF16( QDataStream &inStream )
{
    QString sString;
    inStream >> sString;
    return sString;
}

void AsZip::asFormatFilename( QString &sFilename )
{
    sFilename.replace( "\\", "/" );
}
