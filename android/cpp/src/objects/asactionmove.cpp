// Implements the AsActionMove class.
// $Author: Paul Ellis.

#include "asactionmove.h"
#include "../resources/asresourcemanager.h"
#include "../asfactory.h"
#include "../resources/asmotion.h"



#include "asrenderablegroup.h"



AsActionMove::AsActionMove( AsFactory *pAsFactory ) : AsAction( pAsFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_MOVEACTION );
    this->m_pMotion = NULL;
    this->m_nResource = 0;
}

AsActionMove::AsActionMove( const AsActionMove& actionMove ) : AsAction( actionMove )
{
    this->asCopy( actionMove );
}

AsActionMove::~AsActionMove()
{
    if ( m_pMotion != 0 )
    {
      //  this->m_pAsFactory->asGetResourceManager()->asUnloadResource( m_pMotion );
    }
}

void AsActionMove::operator= ( const AsActionMove& actionMove )
{
    AsAction::operator = ( actionMove );
    this->asCopy( actionMove );
}

void AsActionMove::asCopy( const AsActionMove& actionMove )
{
    this->m_nResource = actionMove.asGetResource();
    this->m_pMotion = 0;
}

QHash<QString, quint16>& AsActionMove::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsActionMove::AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
	//HashProperties.insert( "actionFeatureType", ( quint16 )AsActionMove::AS_PROPERTY_ACTIONFEATURETYPE );
        
	// From AsActionMove...
	HashProperties.insert( "resource", ( quint16 )AsActionMove::AS_PROPERTY_RESOURCE );
    }

    return HashProperties;
}

void AsActionMove::asRun( AsUser *pUser, QPointF )
{
    qDebug( "[ AsActionMove ] - asRun." );

    // For the move action we build a temporary list of AsMotions.  
    // If a target is specified when the action was authored then the list will contain 1 motion.
    // If a NULL target was specified and a marquee selection exists then the list will contain motions for the selected items
    // If a NULL target was specified and no marquee selection exists then the action works on the object itself.
//    QList <AsMotion *> motions;
//
//    AsMotion *pMotion = new AsMotion( * ( AsMotion * )this->asGetResourcePointer() );
//    motions.append( pMotion );
//
//    pMotion->asSetReason( AsMotion::AS_REASON_ACTION );
//    AsNode *pTargetNode = pMotion->asGetObjectToMoveNode().asGetNode();
//    if ( pTargetNode == NULL )
//    {
//		AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//		if(pSelectTool)
//		{
//			QList< AsNode * >nodes = pSelectTool->asGetOldSelectedObjects( pUser );
//			asVerifyTargets(nodes);
//			if ( nodes.count() > 0 )
//			{
//				// Handle all nodes in old selection...
//				pTargetNode = nodes.at( 0 );
//				pMotion->asSetObjectToMoveNode( AsPointer( pTargetNode ) );
//
//                AsObject *pObj = pTargetNode->asGetAsObjectReference();
//
//                if(pObj != NULL)
//                {
//                    AsRenderable *pRend = qobject_cast<AsRenderable *>(pObj);
//                    if(pRend != NULL)
//                    {
//                        pObj->asSetMotion(pMotion);
//                        pMotion->asSetMovingObjRenderable(pRend);
//                    }
//                    else
//                    {
//                        motions.removeAll ( pMotion );
//                        delete pMotion;
//                        pMotion = NULL;
//                    }
//
//                }
//                else
//                {
//                    motions.removeAll ( pMotion );
//                    delete pMotion;
//                    pMotion = NULL;
//                }
//
//				if ( nodes.count() > 1 )
//				{
//                    if (pMotion != NULL)
//                    {
//					    pMotion->asSetOverrideOrigin( true );
//					    pMotion->asSetOrigin( pSelectTool->asGetOldMarqueeCentre( pUser ) );
//                    }
//
//					for ( int i=1 ; i<nodes.count() ; ++i  )
//					{
//						AsMotion *pMotion = new AsMotion( * ( AsMotion * ) this->asGetResourcePointer() );
//						pMotion->asSetReason( AsMotion::AS_REASON_ACTION );
//						pMotion->asSetObjectToMoveNode( AsPointer( nodes.at( i ) ) );
//						pMotion->asSetOverrideOrigin( true );
//						pMotion->asSetOrigin( pSelectTool->asGetOldMarqueeCentre( pUser ) );
//
//						AsObject *pObj = nodes.at( i )->asGetAsObjectReference();
//						if(pObj == NULL)
//						{
//							delete pMotion;
//							continue;
//						}
//						AsRenderable *pRend = qobject_cast<AsRenderable *>(pObj);
//						if(pRend == NULL)
//						{
//							delete pMotion;
//							continue;
//						}
//
//                        pMotion->asSetMotion(pMotion);
//						pMotion->asSetMovingObjRenderable(pRend);
//
//						motions.append( pMotion );
//					}
//				}
//			}
//			else
//			{
//				QList< AsNode * >nodes = pUser->asGetObjectsAtUserCursor();
//				if ( nodes.count() > 0 )
//				{
//					// Will only be 1 node in current selection if we get to here!...
//					pTargetNode = nodes.at( 0 );
//					pMotion->asSetObjectToMoveNode( AsPointer( pTargetNode ) );
//					AsObject *pObj = pTargetNode->asGetAsObjectReference();
//					AsRenderable *pRend = qobject_cast<AsRenderable *>(pObj);
//					if(pRend == NULL)
//					{
//						qDebug( "[ AsActionMove ] - Failed to find target object!" );
//						As::writeErrorLog( "AsActionMove", "asRun", "Failed to find target object!", As::LOGLEVEL_ERROR );
//						delete pMotion;
//						return;
//					}
//
//                    pMotion->asSetMotion(pMotion);
//					pMotion->asSetMovingObjRenderable(pRend);
//				}
//				else
//				{
//					qDebug( "[ AsActionMove ] - Failed to find target object!" );
//					As::writeErrorLog( "AsActionMove", "asRun", "Failed to find target object!", As::LOGLEVEL_ERROR );
//					delete pMotion;
//					return;
//				}
//			}
//		}
//    }
//	else
//	{
//			AsObject *pObj = pTargetNode->asGetAsObjectReference();
//			AsRenderable *pRend = qobject_cast<AsRenderable *>(pObj);
//			if(pRend == NULL)
//			{
//				qDebug( "[ AsActionMove ] - Failed to find target object!" );
//				As::writeErrorLog( "AsActionMove", "asRun", "Failed to find target object!", As::LOGLEVEL_ERROR );
//				delete pMotion;
//				return;
//			}
//            pMotion->asSetMotion(pMotion);
//			pMotion->asSetMovingObjRenderable(pRend);
//	}
//
//	if(pTargetNode->asGetAsObjectReference() == NULL)
//	{
//		// there is no target object to complete this action
//		return;
//	}
//
//	AsRenderableGroup *pRendGroup = qobject_cast< AsRenderableGroup * >( pTargetNode->asGetAsObjectReference() );
//	if (pTargetNode->asGetAsObjectReference()->asGetResourcePointer() == NULL && pRendGroup == NULL)
//	{
//		// there is no target resource to complete this action
//		return;
//	}
//
//	if (pRendGroup)
//	{
//		if (pRendGroup->asGetV2Group())
//		{
//			pRendGroup->asGetTransformedBoundingRect();
//		}
//	}
//
//	AsUndoController *pUndo = this->m_pAsFactory->asGetUndoController();
//	int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_MOVE_OBJECT) );
//	foreach( AsMotion *pMotion, motions )
//		pUndo->asAddToUndoEditObject( undoId, pMotion->asGetObjectToMoveNode().asGetNode() );
//
//    AsMotionController *pMotionController = this->m_pAsFactory->asGetMotionController();
//	foreach( AsMotion *pMotion, motions )
//		pMotionController->asAddMotionItem( pMotion );
//
//    if ( pMotionController->asResolveMotionList(AsMotionController::AS_REASON_ACTION) )
//    {
//		AsStudio::asInstance()->asPageUpdate( AsStudio::AS_PAGEUPDATE_CANVAS | AsStudio::AS_PAGEUPDATE_THUMBNAIL | AsStudio::AS_PAGEUPDATE_PROPERTYBROWSER );
//        pUndo->asCommitUndoStep( undoId );
//    }
//    else
//    {
//        pUndo->asCancelUndoStep( undoId );
//    }
//
//	pMotionController->asClearMotionList();
//	// do not delete motions as they will be deleted in the corresponding object destructor
//    motions.clear();
}

void AsActionMove::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

bool AsActionMove::asIsResourcePointerValid( void )
{
	return asGetResourcePointer() == NULL ? false : true;
}



void AsActionMove::asSetResource( unsigned int nResource )
{
    m_nResource = nResource;
}

AsResource * AsActionMove::asGetResourcePointer( void )
{
    if ( m_pMotion == 0 )
    {
       m_pMotion = dynamic_cast<AsMotion*>(m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_MOTIONRES, asGetResource() ));
    }

    return Q_NULLPTR;
}

void AsActionMove::asSetResource( AsResource *pResource )
{

    if ( m_pMotion != NULL )
    {
        m_nResource = m_pMotion->asGetID();
    }
    else
    {
        m_nResource = 0;
    }
    this->asSetDirtyForWrite( true );
}

void AsActionMove::asVerifyTargets(QList<AsNode *> &targetNodes)
{

}

QString AsActionMove::typeName()
{
    return "actionMove";
}

QString AsActionMove::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsActionMove::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}



bool AsActionMove::isAction()
{
    return true;
}

Json::Value &AsActionMove::serialized()
{
    asGetResourcePointer();
    if(m_pMotion){
        Variant var = m_pMotion->property(AsMotion::AS_PROPERTY_ANGLE);
        if( var.type == VariableType::DOUBLE && var.value){
            m_resourceJsonObject["angle"] = *static_cast<double *>(var.value);
        }
        var = m_pMotion->property(AsMotion::AS_PROPERTY_DOANGLE);
        if(var.type == VariableType::BOOL && var.value)
        {
            m_resourceJsonObject["rotate2Angle"]=*static_cast<bool*>(var.value);
        }
        var = m_pMotion->property(AsMotion::AS_PROPERTY_INC_ANGLE);
        if(var.type == VariableType::BOOL && var.value)
        {
            m_resourceJsonObject["rotateStep"]=*static_cast<bool*>(var.value);
        }
        var = m_pMotion->property(AsMotion::AS_PROPERTY_POSITION);
        if(var.type == VariableType::INT && var.value)
        {
            m_resourceJsonObject["positionChangeType"]=*static_cast<int*>(var.value);
        }
        var = m_pMotion->property(AsMotion::AS_PROPERTY_SIZE);
        if(var.type == VariableType::INT && var.value)
        {
            m_resourceJsonObject["sizeChangeType"]=*static_cast<int*>(var.value);
        }
        var = m_pMotion->property(AsMotion::AS_PROPERTY_STRETCH);
        if(var.type == VariableType::INT && var.value)
        {
            m_resourceJsonObject["strenchChangeType"]=*static_cast<int*>(var.value);
        }
        var = m_pMotion->property(AsMotion::AS_PROPERTY_TRANS);
        if(var.type == VariableType::Q_POINT_F && var.value)
        {
            Json::Value jsonObject;
            jsonObject << *static_cast<QPointF*>(var.value);
            m_resourceJsonObject["translate"]=jsonObject;
        }
    }
    Json::Value &qJsonObject = AsObject::serialized();
    qJsonObject["property"]= m_resourceJsonObject;
    return qJsonObject;
}
