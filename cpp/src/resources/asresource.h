// Defines the AsResource class.
// $Author: Paul Wareing.

#ifndef ASRESOURCE_H
#define ASRESOURCE_H

#include <QString>

#include "../objects/asobject.h"

class AsFactory;

/**
 * An abstract base class for Resource objects in a flipchart
 */
class AsResource : public AsObject
{


public:
    enum AsEnumResourceType
    {
        AS_RESOURCETYPE_NONE,
        AS_RESOURCETYPE_AO2,
        AS_RESOURCETYPE_BMP,
        AS_RESOURCETYPE_JPEG,
        AS_RESOURCETYPE_MPEG3,
        AS_RESOURCETYPE_WMV
        // Add further types here...
    };

    // Construction / Destruction...
    AsResource( AsFactory * );
    virtual ~AsResource();

    AsResource( const AsResource& );
    void operator= ( const AsResource& );

    // Interface...
    inline virtual const QByteArray& asGetHashData( void ) { return m_HashData;}
    inline virtual bool asIsHashDataDirty( void ) { return false;}
    inline virtual void asComputeHashData( void ) {}

    // How is the resource data kept on disk.
    virtual bool asUsesDataFile( void );
    virtual bool asCommitToFile(const QString & path) const;

    // Properties...
    AsEnumResourceType asGetOriginalType( void ) const;
    void asSetOriginalType( AsEnumResourceType );

    const QString& asGetOriginalFilename( void ) const;
    void asSetOriginalFilename( const QString& );

    const QString& asGetOriginalFilePath( void ) const;
    void asSetOriginalFilePath( const QString& );

protected:
    QByteArray m_HashData;
    bool m_bHashDataDirty;

private:
    void asCopy( const AsResource& );

    AsEnumResourceType m_nOriginalType;
    QString m_sOriginalFilename;
    QString m_sOriginalFilePath;
};

#endif // ASRESOURCE_H
