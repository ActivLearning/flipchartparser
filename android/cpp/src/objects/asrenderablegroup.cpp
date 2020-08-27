// Implements the AsRenderableGroup class.
// $Author: Paul Wareing.

#include "asrenderablegroup.h"
#include "../io/asnode.h"
#include "../util/asutil.h"
#include <QtDebug>
AsRenderableGroup::AsRenderableGroup( AsFactory *pAsFactory ) : AsRenderable( pAsFactory ),
                                                                m_bV2Group( false )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_ASRENDERABLEGROUP );
}

AsRenderableGroup::AsRenderableGroup( const AsRenderableGroup& renderableGroup ) : AsRenderable( renderableGroup )
{
    this->asCopy( renderableGroup );
}

AsRenderableGroup::~AsRenderableGroup()
{

}

void AsRenderableGroup::operator= ( const AsRenderableGroup& renderableGroup )
{
    AsRenderable::operator = ( renderableGroup );
    this->asCopy( renderableGroup );
}

bool AsRenderableGroup::operator== ( const AsRenderableGroup& renderableGroup )
{
    if ( !( AsRenderable::operator ==( renderableGroup ) ) )
    {
        return false;
    }

    // TODO.. Look through the group objects.

    return true;
}

void AsRenderableGroup::asCopy( const AsRenderableGroup& rg )
{
    //...
    this->m_Node = rg.asGetNode();
    this->m_bV2Group = rg.asGetV2Group();
}

QHash<QString, quint16>& AsRenderableGroup::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsRenderableGroup::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsRenderableGroup::AS_PROPERTY_TRANSFORM );
     //   HashProperties.insert( "asTwips", ( quint16 )AsRenderableGroup::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsRenderableGroup::AS_PROPERTY_NAME );
      //  HashProperties.insert( "asKeywords", ( quint16 )AsRenderableGroup::AS_PROPERTY_KEYWORDS );
      //  HashProperties.insert( "asVisible", ( quint16 )AsRenderableGroup::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsRenderableGroup::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsRenderableGroup::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsRenderableGroup::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsRenderableGroup::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsRenderableGroup::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsRenderableGroup::AS_PROPERTY_ROTATEORIGIN );
        HashProperties.insert( "moveType", ( quint16 )AsRenderableGroup::AS_PROPERTY_CANMOVE );
//        HashProperties.insert( "asCanSize", ( quint16 )AsRenderableGroup::AS_PROPERTY_CANSIZE );
//        HashProperties.insert( "asCanRotate", ( quint16 )AsRenderableGroup::AS_PROPERTY_CANROTATE );
//        HashProperties.insert( "asCanBlock", ( quint16 )AsRenderableGroup::AS_PROPERTY_CANBLOCK );
//        HashProperties.insert( "asCanSnap", ( quint16 )AsRenderableGroup::AS_PROPERTY_CANSNAP );
        HashProperties.insert( "locked", ( quint16 )AsRenderableGroup::AS_PROPERTY_LOCKED );
//        HashProperties.insert( "asSnapback", ( quint16 )AsRenderableGroup::AS_PROPERTY_SNAPBACK );
//        HashProperties.insert( "asPathPointer", ( quint16 )AsRenderableGroup::AS_PROPERTY_PATHPOINTER );
//        HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsRenderableGroup::AS_PROPERTY_ROTATEABOUTPOINTER );
//        HashProperties.insert( "asRotatePoint", ( quint16 )AsRenderableGroup::AS_PROPERTY_ROTATEPOINT );
//        HashProperties.insert( "asRotateAbout", ( quint16 )AsRenderableGroup::AS_PROPERTY_ROTATEABOUT );
//        HashProperties.insert( "asRotateStep", ( quint16 )AsRenderableGroup::AS_PROPERTY_ROTATESTEP );
//        HashProperties.insert( "asSnapToPointer", ( quint16 )AsRenderableGroup::AS_PROPERTY_SNAPTOPOINTER );
//        HashProperties.insert( "asSnapPoint", ( quint16 )AsRenderableGroup::AS_PROPERTY_SNAPPOINT );
//        HashProperties.insert( "asSnapTo", ( quint16 )AsRenderableGroup::AS_PROPERTY_SNAPTO );
//        HashProperties.insert( "asCanContain", ( quint16 )AsRenderableGroup::AS_PROPERTY_CANCONTAIN );
//        HashProperties.insert( "asContainPointer", ( quint16 )AsRenderableGroup::AS_PROPERTY_CONTAINPOINTER );
//        HashProperties.insert( "asContainWords", ( quint16 )AsRenderableGroup::AS_PROPERTY_CONTAINWORDS );
//        HashProperties.insert( "asContainRule", ( quint16 )AsRenderableGroup::AS_PROPERTY_CONTAINRULE );
//        HashProperties.insert( "asV2Type", ( quint16 )AsRenderableGroup::AS_PROPERTY_V2TYPE );
//        HashProperties.insert( "asConnectorList", ( quint16 )AsRenderableGroup::AS_PROPERTY_CONNECTORLIST );
//        HashProperties.insert( "asLabel", ( quint16 )AsRenderableGroup::AS_PROPERTY_LABEL );
//        HashProperties.insert( "asQuestionTag", ( quint16 )AsRenderableGroup::AS_PROPERTY_QUESTIONTAG );
//        HashProperties.insert( "asAllowSnapback", ( quint16 )AsRenderableGroup::AS_PROPERTY_ALLOWSNAPBACK );
//		HashProperties.insert( "asAsyncTestTag", ( quint16 )AsRenderableGroup::AS_PROPERTY_ASYNCTESTTAG );
//        HashProperties.insert( "asInteractMode", ( quint16 )AsRenderableGroup::AS_PROPERTY_INTERACTMODE );

        // From AsRenderableGroup...
      //  HashProperties.insert( "node", ( quint16 )AsRenderableGroup::AS_PROPERTY_NODE );
        HashProperties.insert( "v2Group", ( quint16 )AsRenderableGroup::AS_PROPERTY_V2GROUP );
    }

    return HashProperties;
}

void AsRenderableGroup::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const AsPointer& AsRenderableGroup::asGetNode( void ) const
{
    return m_Node;
}

void AsRenderableGroup::asSetNode( const AsPointer& ptr )
{
    m_Node = ptr;
}

bool AsRenderableGroup::asGetV2Group( void ) const
{
    return m_bV2Group;
}
void AsRenderableGroup::asSetV2Group( bool v2 )
{
    m_bV2Group = v2;
}

bool AsRenderableGroup::asCheckHit(  const QPointF & /*worldPos*/ )
{
    return false;
}

const AsRectF& AsRenderableGroup::asCompileGroupData( void )
{
    // This method takes the tranformed bounding rect of all the items within the group and...
    //   .unites them 
    AsNode *pNode = m_Node.asGetNode();
    if ( pNode == NULL )
    {
        qDebug( "[ AsRenderableGroup ] - Unable to compile group bounding rect and translate.  Node not set!" );
        return asGetBoundingRect();
    }

	AsRectF &boundingRect = const_cast<AsRectF&>(asGetBoundingRect());
    
    bool first = true;
    return boundingRect;
}

QPointF AsRenderableGroup::asGetRotateCentre( void )
{   
    this->asGetTransformedBoundingRect();
    return this->m_TransformedBoundingRect.center();
}

QString AsRenderableGroup::asGetNewObjectName(quint32 nIndex)
{
    QString strNextName;
 //   strNextName = AsLocale::asGetString(AsLocale::AS_STRING_GROUP) + AsLocale::asInstance()->asGetLocale().toString(nIndex);
    return strNextName;
}

void AsRenderableGroup::asTranslateTo(const QPointF& pos, bool forceDirty)
{

}

void AsRenderableGroup::asReturnToDragStart( bool forceDirty )
{

}

void AsRenderableGroup::asTranslateBy( const QPointF& diff, bool forceDirty )
{
    QPointF currentGroupPos = asGetTransform().asGetTranslate();
	asTranslateTo(currentGroupPos + diff, forceDirty);
}

void AsRenderableGroup::asSetDragStartPosition(const QPointF& point)
{

}

QString AsRenderableGroup::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsRenderableGroup::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

Json::Value &AsRenderableGroup::serialized()
{
    Json::Value &jsonObject =  AsObject::serialized();
    Json::Value softChildIdArry(Json::arrayValue);
    Json::Value softParentArry(Json::arrayValue);
   AsNode *node;
   Variant var = property(AsRenderableGroup::AS_PROPERTY_NODE);
   if (var.value != Q_NULLPTR && var.type == VariableType::ASPOINTER) {
       AsPointer *pointer = static_cast<AsPointer*>(var.value);
       node = pointer->asGetNode();
   }
   for (AsNode * child : node->asGetSoftChildren()) {
       AsObject *object = child->asGetAsObjectReference();
        softChildIdArry.append((int)object->asGetID());
   }
    for (AsNode * child : node->asGetSoftParents()) {
        AsObject *object = child->asGetAsObjectReference();
        softParentArry.append((int)object->asGetID());
    }
   jsonObject["softChildIds"]= softChildIdArry;
   jsonObject["softParentIds"]= softParentArry;
   return jsonObject;

}

QString AsRenderableGroup::typeName()
{
    return "renderableGroup";
}
