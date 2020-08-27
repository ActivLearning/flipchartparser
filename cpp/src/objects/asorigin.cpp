// Implements the AsOrigin class.
// $Author: Paul Wareing.

#include "asorigin.h"




AsOrigin::AsOrigin( AsFactory *pFactory ) : AsObject( pFactory ),
                                            m_Origin( 0, 0 )
{
    this->asSetType( AsObject::AS_OBJECT_ORIGIN );
}

AsOrigin::AsOrigin() : m_Origin( 0, 0 )
{
    this->asSetType( AsObject::AS_OBJECT_ORIGIN );
}

AsOrigin::AsOrigin( const AsOrigin& origin ) : AsObject( origin )
{
    this->asCopy( origin );
}

AsOrigin::~AsOrigin()
{

}

void AsOrigin::operator= ( const AsOrigin& origin )
{
    AsObject::operator =( origin );
    this->asCopy( origin );
}

bool AsOrigin::operator== ( const AsOrigin& o )
{
    if ( m_Origin != o.asGetOrigin() )
    {
        return false;
    }
    return true;
}

void AsOrigin::asCopy( const AsOrigin& origin )
{
    m_Origin = origin.asGetOrigin();
}

// Properties.
QHash<QString, quint16>& AsOrigin::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsOrigin::AS_PROPERTY_DATETIMECREATED );

        // From AsOrigin...
        HashProperties.insert( "origin", ( quint16 )AsOrigin::AS_PROPERTY_ORIGIN );
    }

    return HashProperties;
}

void AsOrigin::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const QPointF& AsOrigin::asGetOrigin( void ) const
{
    return m_Origin;
}

void AsOrigin::asSetOrigin( QPointF& origin )
{
    m_Origin = origin;
}

void AsOrigin::asSetXY (qreal x , qreal y )
{
    QPointF orig( x , y);
    this->asSetOrigin( orig );
}

qreal AsOrigin::asGetX( void ) const
{
    return( this->m_Origin.x() );
}

qreal AsOrigin::asGetY( void ) const
{
    return( this->m_Origin.y() );
}

QString AsOrigin::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsOrigin::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsOrigin::typeName()
{
    return "orgin";
}

Json::Value &AsOrigin::serialized()
{
    Variant var = this->property(AsOrigin::AS_PROPERTY_ORIGIN);
    if(var.type==VariableType::Q_POINT_F&&var.value){
        QPointF * point = static_cast<QPointF*>(var.value);
        jsonObj["x"]=point->x();
        jsonObj["y"]=point->y();

    }
    return jsonObj;
}
