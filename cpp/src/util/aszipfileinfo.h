#ifndef ASZIPFILEINFO_H
#define ASZIPFILEINFO_H

#include <QString>
#include <QDateTime>
#include <QDataStream>

class AsZipFileInfo
{
    public:
        AsZipFileInfo();
        ~AsZipFileInfo();

        // Interface.
        bool asReadFileInfo( QDataStream& inStream );
        bool asWriteFileInfo( QDataStream& outStream );
        QString asFormatFileInfo( void );

        // Properties.
        QString& asGetFilename( void );
        QString& asGetDateCreated( void );
        QString& asGetDateModified( void );
        QString& asGetDateAccessed( void );
        qint64 asGetUncompressedSize( void );
        qint64 asGetCompressedSize( void );
        bool asGetCompressed( void );
        qint64 asGetFileInfoSize( void );

    private:
        QString m_sFilename;
        QString m_sDateCreated;
        QString m_sDateModified;
        QString m_sDateAccessed;
        qint64 m_nUncompressedSize;
        bool m_bCompressed;
        qint64 m_nCompressedSize;

        void asWriteStringUTF16( QDataStream& outStream, const QString& sString );
        QString asReadStringUTF16( QDataStream& inStream );
};

#endif // ASZIPFILEINFO_H
