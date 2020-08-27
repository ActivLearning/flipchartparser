// Implements the AsActionOnObject class.
// (c) 2006 Promethean Technologies Group Ltd

#include "asactiononobject.h"


#include "asactionopenexternal.h"
#include "asrenderable.h"
#include "asobject.h"
#include "../asfactory.h"
#include "../objects/astext.h"



AsActionOnObject::AsActionOnObject( AsFactory *pAsFactory ) : AsAction( pAsFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_ACTIONONOBJECT );

    m_nTranslucency = 0;
    m_Action = AsActionOnObject::AS_ACTION_NONE;
}

AsActionOnObject::AsActionOnObject( const AsActionOnObject& actionOnObject ) : AsAction( actionOnObject )
{
    this->asCopy( actionOnObject );
}

AsActionOnObject::~AsActionOnObject()
{

}

void AsActionOnObject::operator= ( const AsActionOnObject& actionOnObject )
{
    AsAction::operator =( actionOnObject );
    this->asCopy( actionOnObject );
}

void AsActionOnObject::asCopy( const AsActionOnObject& actionOnObject )
{
    this->m_pTargetNode = actionOnObject.asGetTargetNode();
    this->m_Action = actionOnObject.asGetAction();
    this->m_nTranslucency = actionOnObject.asGetTranslucency();
}

QHash<QString, quint16>& AsActionOnObject::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsActionOnObject::AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
	  //  HashProperties.insert( "asActionFeatureType", ( quint16 )AsActionOnObject::AS_PROPERTY_ACTIONFEATURETYPE );

        // From AsActionOnObject...
	 //   HashProperties.insert( "actionTargetNode", ( quint16 )AsActionOnObject::AS_PROPERTY_ACTIONONOBJ_TARGET );
        HashProperties.insert( "actionType", ( quint16 )AsActionOnObject::AS_PROPERTY_ACTIONONOBJ_ACTION );
        HashProperties.insert( "translucency", ( quint16 )AsActionOnObject::AS_PROPERTY_ACTIONONOBJ_TRANSLUCENCY );
    }

    return HashProperties;
}

void AsActionOnObject::asRun( AsUser *pUser, QPointF )
{

//	qDebug( "[ AsActionOnObject ] - asRun." );
//
//	// For the action on objects we build a temporary list of target objects.
//	// If a target is specified when the action was authored then the list will contain 1 object.
//	// If a NULL target was specified and a marquee selection exists then the list will contain the selected objects
//	// If a NULL target was specified and no marquee selection exists then the action works on the object itself.
//	QList < AsNode * > targets;
//
//    AsNode *pTargetNode = m_pTargetNode.asGetNode();
//    if ( pTargetNode != NULL )
//    {
//        targets.append( pTargetNode );
//        asVerifyTargets(targets);
//    }
//
//	if (targets.isEmpty())
//	{
//		AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//	    if( pSelectTool )
//	    {
//		    QList< AsNode * >nodes = pSelectTool->asGetOldSelectedObjects( pUser );
//		    if ( nodes.count() > 0 )
//		    {
//                targets = nodes;
//				//in some cases, the old selected objects may have been deleted...
//				asVerifyTargets(targets);
//		    }
//			else
//			{
//				QList< AsNode * >nodeList = pSelectTool->asGetSelectedObjects( pUser );
//				if ( nodeList.count() > 0 )
//				{
//					targets = nodeList;
//					asVerifyTargets(targets);
//				}
//			}
//		}
//	}
//
//	if (targets.isEmpty())
//	{
//		//the marquee select is in a halfway house at this stage
//		//there is nothing in the currentselection so use this instead
//		targets.append(pUser->asGetObjectsAtUserCursor().at(0));
//	}
//
//    if (targets.isEmpty())
//    {
//	    qDebug( "[ AsActionOnObject ] - Failed to find target object!" );
//	    As::writeErrorLog( "AsActionOnObject", "asRun", "Failed to find target object!", As::LOGLEVEL_ERROR );
//	    return;
//    }
//
//    switch ( m_Action )
//    {
//    case AsActionOnObject::AS_ACTION_SHOW:
//        {
//            AsStudio::asInstance()->asVisibility( targets, true, -1, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_HIDE:
//        {
//            AsStudio::asInstance()->asVisibility( targets, false, -1, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_TRANSLUCENCY:
//        {
//            AsStudio::asInstance()->asTranslucency( targets, ( int )( 255 - m_nTranslucency ), true, -1, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_MORETRANSLUCENCY:
//        {
//            AsObjectEdit editor;
//			AsUndoController *pUndo = targets.at(0)->asGetFactoryPointer()->asGetUndoController();
//			int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_SET_TRANSLUCENCY) );
//
//			foreach ( AsNode *pTargetNode, targets )
//            {
//                int translucency = editor.asGetProperty( pTargetNode, "asInk.asBrushColor.alpha" ).toInt();
//                translucency -= m_nTranslucency;
//                if ( translucency < 0 )
//                {
//                    translucency = 0;
//                }
//				QList<AsNode *> transNodes;
//				transNodes.append(pTargetNode);
//                AsStudio::asInstance()->asTranslucency( transNodes, ( int )( translucency ), true, undoId, false );
//            }
//
//			pUndo->asCommitUndoStep( undoId );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_LESSTRANSLUCENCY:
//        {
//			AsObjectEdit editor;
//			AsUndoController *pUndo = targets.at(0)->asGetFactoryPointer()->asGetUndoController();
//			int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_SET_TRANSLUCENCY) );
//
//			foreach ( AsNode *pTargetNode, targets )
//            {
//                int translucency = editor.asGetProperty( pTargetNode, "asInk.asBrushColor.alpha" ).toInt();
//                translucency += m_nTranslucency;
//                if ( translucency > 255 )
//                {
//                    translucency = 255;
//                }
//				QList<AsNode *> transNodes;
//				transNodes.append(pTargetNode);
//                AsStudio::asInstance()->asTranslucency( transNodes, ( int )( translucency ), true, undoId, false );
//            }
//
//			pUndo->asCommitUndoStep( undoId );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_TOFRONT:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asBringToFront(targets);
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_TOBACK:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asSendToBack(targets);
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_TOBACKLAYER:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asToBottomLayer(targets);
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_TOMIDDLELAYER:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asToMiddleLayer(targets);
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_TOFRONTLAYER:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asToTopLayer(targets);
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_LOCK:
//        {
//            AsStudio::asInstance()->asLocked( targets, true, -1, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_UNLOCK:
//        {
//            AsStudio::asInstance()->asLocked( targets, false, -1, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_REFLECT:
//        {
//            AsStudio::asInstance()->asReflect( targets, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_INVERT:
//        {
//            AsStudio::asInstance()->asInvert( targets, false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_FLIPINX:
//        {
//            AsStudio::asInstance()->asFlipInX( targets, false, QPointF(), false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_FLIPINY:
//        {
//            AsStudio::asInstance()->asFlipInY( targets, false, QPointF(), false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_MIRRORINX:
//        {
//            AsStudio::asInstance()->asMirrorInX( targets, false, QPointF(), false );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_MIRRORINY:
//        {
//            AsStudio::asInstance()->asMirrorInY( targets, false, QPointF(), false );
//        }
//        break;
//
//	case AsActionOnObject::AS_ACTION_DUPLICATE:
//		{
//            AsStudio::asInstance()->asDuplicate( targets );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_IMAGEFITTOWIDTH:
//		{
//			AsStudio::asInstance()->asFitImageToCurrentWidth( targets );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_IMAGEFITTOHEIGHT:
//		{
//			AsStudio::asInstance()->asFitImageToCurrentHeight( targets );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_IMAGEFITTOPAGE:
//		{
//			AsStudio::asInstance()->asFitImageToPage( targets );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_RESETSIZE:
//		{
//			AsStudio::asInstance()->asResetRenderableSize( targets );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_RESETCOLOURS:
//		{
//			AsStudio::asInstance()->asResetImageColours( targets );
//		}
//		break;
//
//    case AsActionOnObject::AS_ACTION_COPYOBJECT:
//        {
//            AsStudio::asInstance()->asCopyObjectsToClipboard( targets );
//        }
//        break;
//
//    case AsActionOnObject::AS_ACTION_CUTOBJECT:
//        {
//			QList<AsNode *> nodesAtCursor = pUser->asGetObjectsAtUserCursor();
//			bool bClearSelection = asCheckClearSelection(targets, nodesAtCursor);
//
//            AsStudio::asInstance()->asCutObjectsToClipboard(targets, pUser);
//
//			if (bClearSelection)
//			{
//				pUser->asClearSelection();
//
//				//we clean up dangling pointers here otherwise all hell breaks loose
//				AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//				if( pSelectTool )
//				{
//					//the select tool will try and select the deleted object after the action has run
//					pSelectTool->asClearCurrentNode(pUser);
//				}
//			}
//        }
//        break;
//
//	case AsActionOnObject::AS_ACTION_BRINGFORWARDS:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asBringForwards(targets);
//        }
//        break;
//
//	case AsActionOnObject::AS_ACTION_SENDBACKWARDS:
//        {
//            AsReorderManager reorderManager;
//            reorderManager.asSendBackwards(targets);
//        }
//        break;
//
//	case AsActionOnObject::AS_ACTION_ALIGN:
//		{
//			AsObject::AsEnumObjectType type = this->asGetFeatureType();
//			AsStudio::asInstance()->asAlignRenderables( targets, type );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNLEFT:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNLEFT );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNCENTREX:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNCENTREX );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNRIGHT:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNRIGHT );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNTOP:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNTOP );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNCENTREY:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNCENTREY );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNBOTTOM:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNBOTTOM );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNWIDTH:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNWIDTH );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNHEIGHT:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNHEIGHT );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNANGLE:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNANGLE );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_ALIGNCOMPLETE:
//		{
//			AsStudio::asInstance()->asAlignRenderables( targets, AsObject::AS_OBJECT_COMMAND_ALIGNCOMPLETE );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_DELETE:
//		{
//			//we need to check if we are deleting the action object itself
//			QList<AsNode *> selectedNodes = pUser->asGetObjectsAtUserCursor();
//
//            foreach ( AsNode *pTargetNode, targets )
//			{
//                if(pTargetNode == selectedNodes.at(0) && pTargetNode != AsApp::asInstance()->asGetCurrentPage() )
//			    {
//				    pUser->asClearSelection();
//
//				    //we clean up dangling pointers here otherwise all hell breaks loose
//				    AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//				    if( pSelectTool )
//				    {
//					    //the select tool will try and select the deleted object after the action has run
//					    pSelectTool->asClearCurrentNode(pUser);
//				    }
//			    }
//            }
//
//            pUser->asContextDelete( targets );
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_TOGGLEHIDDEN:
//		{
//			AsStudio::asInstance()->asToggleHidden(targets, false);
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_TOGGLELOCKED:
//		{
//			AsStudio::asInstance()->asToggleLocked(targets, false);
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_TOGGLEGROUPED:
//		{
//			AsStudio::asInstance()->asToggleGrouped(targets);
//		}
//		break;
//
//	case AsActionOnObject::AS_ACTION_EDITTEXT:
//		{
//			foreach ( AsNode *pTargetNode, targets )
//			{
//				AsObject *pObject = pTargetNode->asGetAsObjectReference();
//				AsText *pText = qobject_cast<AsText *>(pObject);
//				if (pText)
//				{
//					AsStudio::asInstance()->asEditText(pTargetNode);
//					break; // we can only edit a single text object at a time
//				}
//			}
//		}
//		break;
//
//	default:
//		//Do Nothing
//		break;
//    }
}

void AsActionOnObject::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

void AsActionOnObject::asSetTargetNode( AsPointer pTargetNode )
{
	m_pTargetNode = pTargetNode;
}

const AsPointer AsActionOnObject::asGetTargetNode( void ) const
{
	return m_pTargetNode;
}

void AsActionOnObject::asSetAction( AsActionOnObject::AsEnumAction action )
{
    m_Action = action;
}

AsActionOnObject::AsEnumAction AsActionOnObject::asGetAction( void ) const
{
    return m_Action;
}

void AsActionOnObject::asSetTranslucency( int translucency )
{
    m_nTranslucency = translucency;
}

int AsActionOnObject::asGetTranslucency( void ) const
{
    return m_nTranslucency;
}

void AsActionOnObject::asVerifyTargets(QList<AsNode *> &targetNodes)
{
	//targets must...
	//1. Be an AsRenderable
	//2. Still exist on the page
//	QList<AsNode *> validNodes;
//
//	AsNode *pPageNode = AsApp::asInstance()->asGetCurrentPage();
//	QList<AsNode *> nodeList = pPageNode->asGetChildren();
//
//	for (int i = 0; i < targetNodes.size(); i++)
//	{
//		for (int j = 0; j < nodeList.size(); j++)
//		{
//			if (targetNodes.at(i) == nodeList.at(j))
//			{
//				//target still exists - OK
//				AsNode *pTargetNode = targetNodes.at(i);
//				AsObject *pObject = pTargetNode->asGetAsObjectReference();
//				AsRenderable *pRenderable = qobject_cast<AsRenderable *>(pObject);
//
//				if (pRenderable != 0)
//				{
//					//target is a renderable - OK
//					validNodes.append(pTargetNode);
//				}
//
//				break;
//			}
//		}
//	}
//
//	targetNodes = validNodes;
}

bool AsActionOnObject::asCheckClearSelection(QList <AsNode *> targetNodes, QList <AsNode *> nodesAtCursor)
{
	//we need to check if we are deleting the action object itself
	//or a group its a member of
//	QList<AsNode *> selectedNodes = nodesAtCursor;
//	AsApp::asInstance()->asRollUpGroups(nodesAtCursor);
//	foreach (AsNode *pNode, nodesAtCursor)
//	{
//		if (selectedNodes.contains(pNode) == false)
//		{
//			selectedNodes.append(pNode);
//		}
//	}
//
//	foreach ( AsNode *pTargetNode, targetNodes )
//	{
//		foreach ( AsNode *pSelectedNode, selectedNodes )
//		{
//			if(pTargetNode == pSelectedNode)
//			{
//				return true;
//			}
//		}
//	}

	return false;
}

QString AsActionOnObject::typeName()
{
    return "actionOnObject";
}

QString AsActionOnObject::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsActionOnObject::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

bool AsActionOnObject::isAction()
{
    return true;
}
