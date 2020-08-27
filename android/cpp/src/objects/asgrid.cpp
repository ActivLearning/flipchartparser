// Implements the AsGrid class.
// $Author: Paul Wareing.

#include "asgrid.h"
#include "../io/asnode.h"


AsGrid::AsGrid( AsFactory *pAsFactory ) : AsRenderable( pAsFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_GRID );

    // Initialise the properties with primitive types.
    m_dThumbNailScale = 1.0;
    m_dDefaultScale = 1.0;
    m_dScaleStep = 0.5;
    m_bAllowSnap = false;
    m_bOnTop = false;
    m_bLevelEditor = false;

    // Revisit ATE
    QString sName = "Grid";
    this->asSetName( sName );
}

AsGrid::AsGrid( const AsGrid& grid ) : AsRenderable( grid )
{
    this->asCopy( grid );
}

AsGrid::~AsGrid()
{

}

void AsGrid::operator= ( const AsGrid& grid )
{
    AsRenderable::operator =( grid );
    this->asCopy( grid );
}

void AsGrid::asCopy( const AsGrid& grid )
{
    this->m_dThumbNailScale = grid.asGetThumbNailScale();
    this->m_dDefaultScale = grid.asGetDefaultScale();
    this->m_dScaleStep = grid.asGetScaleStep();
    this->m_bAllowSnap = grid.asGetAllowSnap();
    this->m_bOnTop = grid.asGetOnTop();
    this->m_bLevelEditor = grid.asGetLevelEditor();
}

QHash<QString, quint16>& AsGrid::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "dateTimeCreated", ( quint16 )AsGrid::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsGrid::AS_PROPERTY_TRANSFORM );
        HashProperties.insert( "twips", ( quint16 )AsGrid::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsGrid::AS_PROPERTY_NAME );
        HashProperties.insert( "keywords", ( quint16 )AsGrid::AS_PROPERTY_KEYWORDS );
        HashProperties.insert( "visible", ( quint16 )AsGrid::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsGrid::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsGrid::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsGrid::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsGrid::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsGrid::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsGrid::AS_PROPERTY_ROTATEORIGIN );

        // From AsGrid...
        HashProperties.insert( "asThumbNailScale", ( quint16 )AsGrid::AS_PROPERTY_THUMBNAILSCALE );
        HashProperties.insert( "defaultScale", ( quint16 )AsGrid::AS_PROPERTY_DEFAULTSCALE );
        HashProperties.insert( "scaleStep", ( quint16 )AsGrid::AS_PROPERTY_SCALESTEP );
        HashProperties.insert( "allowSnap", ( quint16 )AsGrid::AS_PROPERTY_ALLOWSNAP );
        HashProperties.insert( "onTop", ( quint16 )AsGrid::AS_PROPERTY_ONTOP );
        HashProperties.insert( "levelEditor", ( quint16 )AsGrid::AS_PROPERTY_LEVELEDITOR );
    }

    return HashProperties;
}

void AsGrid::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

bool AsGrid::asCheckHit(  const QPointF & /*worldPos*/ )
{
    return false;
}


double AsGrid::asGetThumbNailScale( void ) const
{
    return m_dThumbNailScale;
}

void AsGrid::asSetThumbNailScale( double d )
{
    m_dThumbNailScale = d;
}

double AsGrid::asGetDefaultScale( void ) const
{
    return m_dDefaultScale;
}

void AsGrid::asSetDefaultScale( double d )
{
    m_dDefaultScale = d;
}

double AsGrid::asGetScaleStep( void ) const
{
    return m_dScaleStep;
}

void AsGrid::asSetScaleStep( double d )
{
    m_dScaleStep = d;
}

bool AsGrid::asGetAllowSnap( void ) const
{
    return m_bAllowSnap;
}

void AsGrid::asSetAllowSnap( bool bAllowSnap )
{
    m_bAllowSnap = bAllowSnap;
}

bool AsGrid::asGetOnTop() const
{
    return m_bOnTop;
}

void AsGrid::asSetOnTop(bool bOnTop)
{
    m_bOnTop = bOnTop;
}

bool AsGrid::asGetLevelEditor() const
{
    return m_bLevelEditor;
}

void AsGrid::asSetLevelEditor(bool bLevelEditor)
{
    m_bLevelEditor = bLevelEditor;
}

QPointF AsGrid::asGetNearestPoint( AsNode *pGridNode, const QPointF& point )
{

    return QPointF();
}

bool AsGrid::asIsSelectable( void )
{
    return false;
}

QString AsGrid::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsGrid::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsGrid::typeName()
{
    return "grid";
}


