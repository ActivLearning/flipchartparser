// Implements the AsLineRes class.
// $Author: Paul Wareing.

#include "aslineres.h"



AsLineRes::AsLineRes( AsFactory *pAsFactory ) : AsResource( pAsFactory )
{
    asSetType( AsObject::AS_OBJECT_LINERES );
}

AsLineRes::AsLineRes( const AsLineRes& res ) : AsResource( res )
{
    this->asCopy( res );
}

void AsLineRes::operator= ( const AsLineRes& res )
{
    AsResource::operator = ( res );
    this->asCopy( res );
}

void AsLineRes::asCopy( const AsLineRes& res )
{
    this->m_Line = res.asGetLine();
}

AsLineRes::~AsLineRes()
{

}

QHash<QString, quint16>& AsLineRes::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
      //  HashProperties.insert( "asDateTimeCreated", ( quint16 )AsLineRes::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
       // HashProperties.insert( "asOriginalType", AsLineRes::AS_PROPERTY_ORIGINALTYPE );
      //  HashProperties.insert( "asOriginalFilename", AsLineRes::AS_PROPERTY_ORIGINALFILENAME );

        // From AsAnnotationRes...
        HashProperties.insert( "asLine", AsLineRes::AS_PROPERTY_LINE );
    }

    return HashProperties;
}

void AsLineRes::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const QByteArray& AsLineRes::asGetHashData( void )
{
    return m_HashData;
}

bool AsLineRes::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsLineRes::asComputeHashData( void )
{
    m_HashData.clear();
    m_HashData.append( this->asGetTypeName() );
    m_HashData.append( m_Line.asToByteArray() );
    m_bHashDataDirty = false;
}

const AsPointFArray AsLineRes::asGetLine( void ) const
{
    return m_Line;
}

void AsLineRes::asSetLine( AsPointFArray& line )
{
    m_Line = line;
    m_bHashDataDirty = true;

}

QString AsLineRes::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsLineRes::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}
