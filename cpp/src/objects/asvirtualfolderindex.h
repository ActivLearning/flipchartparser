// Defines the AsVirtualFolderIndex class.
// $Author: Paul Wareing.

#ifndef ASVIRTUALFOLDERINDEX_H
#define ASVIRTUALFOLDERINDEX_H

#include <QMetaType>
#include <QHash>

#include "asobject.h"

struct AsFileInfo
{
    QString m_sFilename;
    qint64 m_pos;
    qint64 m_size;
};

typedef QHash< QString, AsFileInfo > AsFolderIndex;

//Q_DECLARE_METATYPE( AsFolderIndex )

class AsVirtualFolderIndex : public AsObject
{
//Q_OBJECT
//Q_PROPERTY( AsFolderIndex asFolderIndex READ asGetFolderIndex WRITE asSetFolderIndex )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResourceRegister...
        AS_PROPERTY_FOLDERINDEX,
    };

    // Construction and destruction.
    AsVirtualFolderIndex();
    AsVirtualFolderIndex( AsFactory * );
    AsVirtualFolderIndex( const AsVirtualFolderIndex& );
    virtual ~AsVirtualFolderIndex();

    void operator= ( const AsVirtualFolderIndex& );

    // Interface.
    void asResetPropertyIndex( void );

    void asSetFolderIndex( const AsFolderIndex& );
    const AsFolderIndex& asGetFolderIndex( void ) const;
    AsFolderIndex * asGetFolderIndexPointer( void );

private:
    // Property hash table.
    static QHash<QString, quint16>& m_lProperties( void );

    // Properties.
    AsFolderIndex   m_Index;
};
#endif // ASVIRTUALFOLDERINDEX_H
