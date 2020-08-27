// Implements the AsResource class.
// $Author: Paul Wareing.

#include "asresource.h"



AsResource::AsResource( AsFactory *pAsFactory ) : AsObject( pAsFactory ),
                                                  m_bHashDataDirty( true )
{
    m_nOriginalType = AsResource::AS_RESOURCETYPE_NONE;
    m_sOriginalFilename = "";
}

AsResource::AsResource( const AsResource& res ) : AsObject( res )
{
    this->asCopy( res );
}

void AsResource::operator= ( const AsResource& res )
{
    AsObject::operator = ( res );
    this->asCopy( res );
}

void AsResource::asCopy( const AsResource& res )
{
    this->m_nOriginalType = res.asGetOriginalType();
    this->m_sOriginalFilename = res.asGetOriginalFilename();
    this->m_sOriginalFilePath = res.asGetOriginalFilePath();
}

AsResource::~AsResource()
{

}

bool AsResource::asUsesDataFile( void )
{
    // By default, resources store their data within the res object.
    // This method must be overridden for resource types such as images that keep their data in a separate file.
    return false;
}

bool AsResource::asCommitToFile(const QString & path) const
{
    Q_UNUSED(path);
    return false;
}

AsResource::AsEnumResourceType AsResource::asGetOriginalType( void ) const
{
    return m_nOriginalType;
}

void AsResource::asSetOriginalType( AsResource::AsEnumResourceType n )
{
    m_nOriginalType = n;
}

const QString& AsResource::asGetOriginalFilename( void ) const
{
    return m_sOriginalFilename;
}

void AsResource::asSetOriginalFilename( const QString& sName )
{
    m_sOriginalFilename = sName;
}

const QString& AsResource::asGetOriginalFilePath( void ) const
{
    return m_sOriginalFilePath;
}

void AsResource::asSetOriginalFilePath( const QString& sPath )
{
    m_sOriginalFilePath = sPath;
}
