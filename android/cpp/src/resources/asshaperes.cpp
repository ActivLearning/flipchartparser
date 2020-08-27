// Implements the AsShapeRes class.
// $Author: Paul Wareing.

#include "asshaperes.h"




AsShapeRes::AsShapeRes( AsFactory *pAsFactory ) : AsResource( pAsFactory )
{
    asSetType( AsObject::AS_OBJECT_SHAPERES );

    // Initialise our properties.
    m_Shapes.clear();
}

AsShapeRes::AsShapeRes( const AsShapeRes& res ) : AsResource( res )
{
    this->asCopy( res );
}

void AsShapeRes::operator= ( const AsShapeRes& res )
{
    AsResource::operator = ( res );
    this->asCopy( res );
}

void AsShapeRes::asCopy( const AsShapeRes& res )
{
    this->m_Shapes = res.asGetShapes();
}

AsShapeRes::~AsShapeRes()
{

}

QHash<QString, quint16>& AsShapeRes::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsShapeRes::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
        HashProperties.insert( "originalType", AsShapeRes::AS_PROPERTY_ORIGINALTYPE );
        HashProperties.insert( "originalFilename", AsShapeRes::AS_PROPERTY_ORIGINALFILENAME );

        // From AsAnnotationRes...
        HashProperties.insert( "shapes", AsShapeRes::AS_PROPERTY_SHAPES );
    }

    return HashProperties;
}

void AsShapeRes::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const QByteArray& AsShapeRes::asGetHashData( void )
{
    return m_HashData;
}

bool AsShapeRes::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsShapeRes::asComputeHashData( void )
{
    m_HashData.clear();
    m_HashData.append( this->asGetTypeName() );
    m_HashData.append( m_Shapes.asToByteArray() );
    m_bHashDataDirty = false;
}

const AsPointFArrayArray& AsShapeRes::asGetShapes( void ) const
{
    return m_Shapes;
}

const AsPointFArray& AsShapeRes::asGetShape( int idx ) 
{
    return m_Shapes.at( idx );
}

void AsShapeRes::asSetShapes( AsPointFArrayArray& shapes )
{
    m_Shapes = shapes;
    m_bHashDataDirty = true;

}

void AsShapeRes::asAddShape( AsPointFArray& shape )
{
    m_Shapes.append( shape );
    m_bHashDataDirty = true;

}

void AsShapeRes::asClearShapes( void )
{
    m_Shapes.clear();
    m_bHashDataDirty = true;

}
