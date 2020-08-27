// Defines the AsVirtualFolder class.
// (c) 2009 - Promethean Ltd
// Paul Wareing

#ifndef ASVIRTUALFOLDER_H
#define ASVIRTUALFOLDER_H

#include <QFile>
#include <QString>
#include <QHash>
#include <QMetaType>

#include "asobject.h"
#include "asvirtualfolderindex.h"

class AsFactory;

class AsVirtualFolder : public AsObject
{

public:
    AsVirtualFolder( AsFactory * );
    virtual ~AsVirtualFolder();

    void asInitialise( const QString& path, int id = 0, const QString& filename = QString() );
    void asCloseVirtualFolderFile();
    void asOpenVirtualFolderFile();
//    void asResetPropertyIndex( void ){}

    quint32 asGetFolderId( void );
    const QString& asGetPath( void );
    const QString& asGetFilePath( void );

    void asAddFile( const QString&, const QByteArray&, const QString& sFilePath = QString() );
    void asRemoveFile( const QString& );
    int asCount( void );

    void asResetIndexIterator( void );
    bool asReadNextFile( QString&, QByteArray& );
    bool asReadFile( const QString&, QByteArray& );

    QStringList asGetSubFilesAndFolders( const QString& path );
    QStringList asListFiles( void ) ;

    void asClear( void );

    // For Repair...
    void asWriteIndex( void );
    void asRepair( AsVirtualFolderIndex *, const QString& filePath, int id );
    const AsVirtualFolderIndex& asGetIndex( void ) const;
    void asSetIndex( const AsVirtualFolderIndex& );

private:
    quint32 m_FolderId;
    QFile m_File;
    QString m_FilePath;
    QString m_Path;
    AsVirtualFolderIndex m_Index;
    QHash< QString, AsFileInfo >::const_iterator m_IndexIterator;
    QHash< QString, QString> m_FilePathInfo;

};

#endif // ASVIRTUALFOLDER_H
