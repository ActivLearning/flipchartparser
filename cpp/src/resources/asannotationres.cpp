// Implements the AsAnnotationRes class.
// $Author: Paul Wareing.

#include "asannotationres.h"
#include <QTime>
#include <QDebug>



AsAnnotationRes::AsAnnotationRes( AsFactory *pAsFactory ) : AsResource( pAsFactory )
{
    asSetType( AsObject::AS_OBJECT_ANNOTATIONRES );

    // Initialise our properties.
    m_Points.clear();
    m_TimePoints.clear();
    //adding a zero for the first time point, all other timepoints will be added after
    m_TimePoints.append(0);
    m_time.start();
}

AsAnnotationRes::AsAnnotationRes( const AsAnnotationRes& res ) : AsResource( res )
{
    this->asCopy( res );
}

void AsAnnotationRes::operator= ( const AsAnnotationRes& res )
{
    AsResource::operator = ( res );
    this->asCopy( res );
}

void AsAnnotationRes::asCopy( const AsAnnotationRes& res )
{
    this->m_Points = res.asGetPoints();
}

AsAnnotationRes::~AsAnnotationRes()
{

}

QHash<QString, quint16>& AsAnnotationRes::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsAnnotationRes::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
        HashProperties.insert( "asOriginalType", AsAnnotationRes::AS_PROPERTY_ORIGINALTYPE );
        HashProperties.insert( "asOriginalFilename", AsAnnotationRes::AS_PROPERTY_ORIGINALFILENAME );

        // From AsAnnotationRes...
        HashProperties.insert( "asPoints", AsAnnotationRes::AS_PROPERTY_POINTS );
    }

    return HashProperties;
}

void AsAnnotationRes::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const AsPointFArray& AsAnnotationRes::asGetPoints( void ) const
{
    return m_Points;
}

QVector<int>& AsAnnotationRes::asGetTimePoints( void )
{
    return m_TimePoints;
}

void AsAnnotationRes::asSetPoints( AsPointFArray& points )
{
    m_Points = points;
    m_bHashDataDirty = true;
}

void AsAnnotationRes::asAddPoint( QPointF& point )
{
    if (m_Points.isEmpty() || m_Points.first() != point)
    {
        m_TimePoints.prepend( m_time.elapsed() );
        m_Points.prepend( point );
        m_bHashDataDirty = true;
    }
}

void AsAnnotationRes::asClearPoints( void )
{
    m_TimePoints.clear();
    m_Points.clear();
    m_bHashDataDirty = true;
}

const QByteArray& AsAnnotationRes::asGetHashData( void )
{
    return m_HashData;
}

bool AsAnnotationRes::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsAnnotationRes::asComputeHashData( void )
{
    m_HashData.clear();
    m_HashData.append( this->asGetTypeName() );
    m_HashData.append( this->m_Points.asToByteArray() );
    m_bHashDataDirty = false;
}
