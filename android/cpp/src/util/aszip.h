//
// Created by admin on 2019-08-22.
//

#ifndef FLIPCHARTQUICK_ASZIP_H
#define FLIPCHARTQUICK_ASZIP_H

#include <functional>
#include <QtGlobal>
#include <QString>
#include <string>


using std::string;

class AsZip {

public:
    AsZip();
    ~AsZip();

public:
    void bindAsReportFile(std::function<void(const QString&, const QByteArray&)> func);

    bool asReportFiles( const std::string& filename );


    enum ZipError
    {
        NO_ERROR = 0,
        ERROR_CANNOT_OPEN_TARGET_FILE_FOR_READING,
        ERROR_CANNOT_OPEN_TARGET_FILE_FOR_WRITING,
        ERROR_CANNOT_OPEN_TEMPORARY_FILE_FOR_WRITING,
        ERROR_COPYING_TEMPORARY_FILE_TO_TARGET,
        ERROR_FLIPCHART_FILE_DOES_NOT_EXIST,
        ERROR_NOT_A_FLIPCHART_FILE,
        ERROR_OPENING_FILE_FOR_READING,
        ERROR_OUT_OF_MEMORY_READING_FILE,
        ERROR_READING_FILE,
        ERROR_OPENING_FILE_FOR_WRITING,
        ERROR_WRITING_FILE,
        ERROR_INCORRECT_VERSION,
        ERROR_INCORRECT_STREAMER_VERSION,
        ERROR_PATH_DOES_NOT_EXIST,
        ERROR_FAILED_TO_REMOVE_EXISTING_TARGET_FILE,
        ERROR_CORRUPT_FLIPCHART_FILE
    };


private:

    std::function<void(const QString&, const QByteArray&)> asReportFile;

    std::function<void(int nPercent)> asPercentDone;

private:
    quint16 m_nLastError;
    QString m_sWorkingPath;
    QString m_sVersion;
    QString m_sTempFolder;
    QString m_sFilename;
    QString m_sComment;

    quint16 m_nFileEncryption;
    quint16 m_nStringEncoding;

    quint32 asReadHeader( QDataStream& inStream,
                          QString& sExistingVersion,
                          QString& sExistingComment );

    // Returns false if error
    bool asReadByteArray( QDataStream &inStream, int nCount, QByteArray & aData );

    QString asReadStringUTF16( QDataStream& inStream );

    void asFormatFilename( QString &sFilename );

};


#endif //FLIPCHARTQUICK_ASZIP_H
