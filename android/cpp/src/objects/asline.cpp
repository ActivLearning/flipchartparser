// Implements the AsLine class.
// $Author: Paul Wareing.

#include "asline.h"
#include "../resources/asresourcemanager.h"

#include "../util/asutil.h"
#include "../asfactory.h"
#include "asrenderable.h"




AsLine::AsLine( AsFactory *pAsFactory ) : AsRenderable( pAsFactory )

{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_LINE );

    // Initialise the properties with primitive types.
    m_nResource = 0;
    m_pAsLineRes = 0;
    m_nEndCapA = AsLine::AS_ENDCAP_NONE;
    m_nEndCapB = AsLine::AS_ENDCAP_NONE;
    m_bPainterPathDirty = true;
}

AsLine::AsLine( const AsLine& line ) : AsRenderable( line )
{
    this->asCopy( line );
}

AsLine::~AsLine()
{


}


void AsLine::operator= ( const AsLine& line )
{
    AsRenderable::operator =( line );
    this->asCopy( line );
}

bool AsLine::operator== ( const AsLine& line )
{
    if ( !AsRenderable::operator ==( line ) )
    {
        return false;
    }

    if (( m_nResource != line.asGetResource() ) ||
        ( m_nEndCapA != line.asGetEndCapA() ) ||
        ( m_nEndCapB != line.asGetEndCapB() ))
    {
        return false;
    }
    return true;
}

void AsLine::asCopy( const AsLine& line )
{
    this->m_nResource = line.asGetResource();
    this->m_nEndCapA = line.asGetEndCapA();
    this->m_nEndCapB = line.asGetEndCapB();
    this->m_pAsLineRes = 0;


    this->m_bPainterPathDirty = true;
}

QHash<QString, quint16>& AsLine::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsLine::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsLine::AS_PROPERTY_TRANSFORM );
    //    HashProperties.insert( "asTwips", ( quint16 )AsLine::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsLine::AS_PROPERTY_NAME );
     //   HashProperties.insert( "asKeywords", ( quint16 )AsLine::AS_PROPERTY_KEYWORDS );
     //   HashProperties.insert( "asVisible", ( quint16 )AsLine::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsLine::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsLine::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsLine::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsLine::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsLine::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsLine::AS_PROPERTY_ROTATEORIGIN );
        HashProperties.insert( "moveType", ( quint16 )AsLine::AS_PROPERTY_CANMOVE );
//        HashProperties.insert( "asCanSize", ( quint16 )AsLine::AS_PROPERTY_CANSIZE );
//        HashProperties.insert( "asCanRotate", ( quint16 )AsLine::AS_PROPERTY_CANROTATE );
//        HashProperties.insert( "asCanBlock", ( quint16 )AsLine::AS_PROPERTY_CANBLOCK );
//        HashProperties.insert( "asCanSnap", ( quint16 )AsLine::AS_PROPERTY_CANSNAP );
       HashProperties.insert( "locked", ( quint16 )AsLine::AS_PROPERTY_LOCKED );
//        HashProperties.insert( "asSnapback", ( quint16 )AsLine::AS_PROPERTY_SNAPBACK );
//        HashProperties.insert( "asPathPointer", ( quint16 )AsLine::AS_PROPERTY_PATHPOINTER );
//        HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsLine::AS_PROPERTY_ROTATEABOUTPOINTER );
//        HashProperties.insert( "asRotatePoint", ( quint16 )AsLine::AS_PROPERTY_ROTATEPOINT );
//        HashProperties.insert( "asRotateAbout", ( quint16 )AsLine::AS_PROPERTY_ROTATEABOUT );
//        HashProperties.insert( "asRotateStep", ( quint16 )AsLine::AS_PROPERTY_ROTATESTEP );
//        HashProperties.insert( "asSnapToPointer", ( quint16 )AsLine::AS_PROPERTY_SNAPTOPOINTER );
//        HashProperties.insert( "asSnapPoint", ( quint16 )AsLine::AS_PROPERTY_SNAPPOINT );
   //     HashProperties.insert( "asSnapTo", ( quint16 )AsLine::AS_PROPERTY_SNAPTO );
    //    HashProperties.insert( "asCanContain", ( quint16 )AsLine::AS_PROPERTY_CANCONTAIN );
     //   HashProperties.insert( "asContainPointer", ( quint16 )AsLine::AS_PROPERTY_CONTAINPOINTER );
    //    HashProperties.insert( "asContainWords", ( quint16 )AsLine::AS_PROPERTY_CONTAINWORDS );
    //    HashProperties.insert( "asContainRule", ( quint16 )AsLine::AS_PROPERTY_CONTAINRULE );
    //    HashProperties.insert( "asV2Type", ( quint16 )AsLine::AS_PROPERTY_V2TYPE );
     //   HashProperties.insert( "asConnectorList", ( quint16 )AsLine::AS_PROPERTY_CONNECTORLIST );
    //    HashProperties.insert( "asLabel", ( quint16 )AsLine::AS_PROPERTY_LABEL );
     //   HashProperties.insert( "asQuestionItem", ( quint16 )AsLine::AS_PROPERTY_QUESTIONITEM );
     //   HashProperties.insert( "asQuestionItemID", ( quint16 )AsLine::AS_PROPERTY_QUESTIONITEMID );
      //  HashProperties.insert( "asQuestionTag", ( quint16 )AsLine::AS_PROPERTY_QUESTIONTAG );
     //   HashProperties.insert( "asAllowSnapback", ( quint16 )AsLine::AS_PROPERTY_ALLOWSNAPBACK );
    //    HashProperties.insert( "asDragACopy", ( quint16 )AsLine::AS_PROPERTY_DRAGACOPY );
    //    HashProperties.insert( "asRewardSound", ( quint16 )AsLine::AS_PROPERTY_REWARD_SOUND );
     //   HashProperties.insert( "asRewardSoundLocation", ( quint16 )AsLine::AS_PROPERTY_REWARD_SOUND_LOCATION );
	//	HashProperties.insert( "asAsyncTestTag", ( quint16 )AsLine::AS_PROPERTY_ASYNCTESTTAG );
    //    HashProperties.insert( "asInteractMode", ( quint16 )AsLine::AS_PROPERTY_INTERACTMODE );

        // From AsLine...
        HashProperties.insert( "resource", ( quint16 )AsLine::AS_PROPERTY_RESOURCE );
        HashProperties.insert( "endCapA", ( quint16 )AsLine::AS_PROPERTY_ENDCAPA );
        HashProperties.insert( "endCapB", ( quint16 )AsLine::AS_PROPERTY_ENDCAPB );
    }

    return HashProperties;
}

void AsLine::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

AsLine::AsEnumLineEnd AsLine::asCheckHitEnd( const QPointF & worldPos )
{
    AsEnumLineEnd result;
	return result;
}

bool AsLine::asCheckHit(  const QPointF & worldPos )
{
	//Note: this function relies on knowledge of how a line is drawn, it that changes then so must this method
	bool hit = false;
	AsRectF tbRect = this->asGetTransformedBoundingRect( true );
	if( tbRect.contains( worldPos ) )
	{
        if ( m_pAsLineRes == NULL )
        {
            this->asGetResourcePointer();
        }

		AsPointFArray line = m_pAsLineRes->asGetLine();
		unsigned int ow = this->asGetInk().asGetPenWidth();

		if( ow <= 1 )
		{
			ow = 2;
		}

		//TODO: The test on the main line needs shortening for solid arrow lines
		for(int p = 0 ; p < line.size() ; ++p)
		{
			qreal px = line.at( p ).x();
			qreal py = line.at( p ).y();

			QPointF tempPnt( px, py );
			this->asTransformPoint( tempPnt );
	        
			line[ p ].setX( tempPnt.x() );
			line[ p ].setY( tempPnt.y() );
		}    
		//Look on the main line

	}
    return hit;
}

AsPointFArray AsLine::asGetPoints( void )
{
    AsLineRes *pRes = ( AsLineRes * )this->asGetResourcePointer();
    return  pRes->asGetLine();
}

bool AsLine::asIsResourcePointerValid( void )
{
	return asGetResourcePointer() == NULL ? false : true;
}



void AsLine::asSetResource( unsigned int nResource )
{
    m_nResource = nResource;
}

AsResource * AsLine::asGetResourcePointer( void )
{
    if ( m_pAsLineRes == 0 )
    {
        m_pAsLineRes = dynamic_cast<AsLineRes*>(m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_LINERES, asGetResource()));
        if( m_pAsLineRes != 0 )
        {

        }
        m_bPainterPathDirty = true;
    }

    return m_pAsLineRes;
}

void AsLine::asSetResource( AsResource *pResource )
{
    m_pAsLineRes = dynamic_cast< AsLineRes * >( pResource );
    if ( m_pAsLineRes != NULL )
    {
        m_nResource = m_pAsLineRes->asGetID();
        m_bPainterPathDirty = true;
    }
    else
    {
        m_nResource = 0;
    }
    this->asSetDirtyForWrite( true );
}

AsLine::AsEnumEndCap AsLine::asGetEndCapA( void ) const
{
    return m_nEndCapA;
}

void AsLine::asSetEndCapA( AsLine::AsEnumEndCap nEndCap )
{
    m_nEndCapA = nEndCap;
}

AsLine::AsEnumEndCap AsLine::asGetEndCapB( void ) const
{
    return m_nEndCapB;
}

void AsLine::asSetEndCapB( AsLine::AsEnumEndCap nEndCap )
{
    m_nEndCapB = nEndCap;
}

void AsLine::asLineResChanged( AsLineRes *pLineRes )
{
    if ( m_pAsLineRes == pLineRes )
    {
        m_bPainterPathDirty = true;
    }
}

void AsLine::asBuildPainterPath( void )
{

}

QString AsLine::getPropertyNameById(int nID) {
    return m_lProperties().key(nID);
}

int AsLine::getPropertyIdByName(QString name) const {
    return m_lProperties().value(name);
}

QString AsLine::typeName()
{
    return "line";
}

const Json::Value &AsLine::asResourceSerialized()
{
    asGetResourcePointer();
    if(m_pAsLineRes){
       Variant var = m_pAsLineRes->property(AsLineRes::AS_PROPERTY_LINE);
       if(var.value && var.type == VariableType::ASPOINTFARRAY){
           m_resourceJsonObject << var;
       }
    }
    return m_resourceJsonObject;

}

Json::Value &AsLine::serialized()
{
    Json::Value &jsonObject = AsRenderable::serialized();
    return  jsonObject;
}


