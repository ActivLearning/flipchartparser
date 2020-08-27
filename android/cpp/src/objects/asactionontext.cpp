/****************************************************************************
** Copyright 2006 Promethean Technologies Group Limited
****************************************************************************/

#include "asactionontext.h"


#include "../io/asnode.h"
#include "asrenderable.h"
#include "asobject.h"
#include "../asfactory.h"

#include "astext.h"
#include "../resources/asresourcemanager.h"



#include <QFile>
#include <QTextStream>



AsActionOnText::AsActionOnText( AsFactory *pAsFactory ) : AsAction( pAsFactory )	
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_ACTIONONTEXT );
    m_sText= "";
    m_Action = AsActionOnText::AS_ACTION_NONE;
}


AsActionOnText::AsActionOnText( const AsActionOnText& actionOnText ) : AsAction( actionOnText )
{
    this->asCopy( actionOnText );
}


AsActionOnText::~AsActionOnText()
{

}


void AsActionOnText::operator= ( const AsActionOnText& actionOnText )
{
    AsAction::operator =( actionOnText );
    this->asCopy( actionOnText );
}

void AsActionOnText::asCopy( const AsActionOnText& actionOnText )
{
    this->m_pTargetNode = actionOnText.asGetTargetNode();
    this->m_Action = actionOnText.asGetAction();
    this->m_sText = actionOnText.asGetText();
}


QHash<QString, quint16>& AsActionOnText::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsActionOnText::AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
	HashProperties.insert( "asActionFeatureType", ( quint16 )AsActionOnText::AS_PROPERTY_ACTIONFEATURETYPE );

        // From AsActionOnObject...
        HashProperties.insert( "asActionSourceNode", ( quint16 )AsActionOnText::AS_PROPERTY_ACTIONONTEXT_SOURCE );
	HashProperties.insert( "asActionTargetNode", ( quint16 )AsActionOnText::AS_PROPERTY_ACTIONONTEXT_TARGET );
        HashProperties.insert( "asAction", ( quint16 )AsActionOnText::AS_PROPERTY_ACTIONONTEXT_ACTION );
        HashProperties.insert( "asText", ( quint16 )AsActionOnText::AS_PROPERTY_ACTIONONTEXT_TEXT );
    }

    return HashProperties;
}


void AsActionOnText::asRun( AsUser *pUser, QPointF pos )
{
//    As::writeErrorLog( "AsActionOnText", "asRun", qPrintable( QString::number( m_Action ) ), As::LOGLEVEL_CRASHSUPPORT );
//	qDebug( "[ AsActionOnText ] - asRun." );
//
//	AsNode *pTargetNode = 0;
//
//    pTargetNode = m_pTargetNode.asGetNode();
//	bool bValidTarget = asVerifyTarget(pTargetNode);
//
//	//if the action itself has no target parameter get a text object from the old marquee select
//	if (bValidTarget == false)
//	{
//		AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//		if( pSelectTool )
//		{
//			QList< AsNode * > oldNodes = pSelectTool->asGetOldSelectedObjects( pUser );
//			if ( oldNodes.count() > 0 )
//			{
//				foreach (AsNode *pOldNode, oldNodes)
//				{
//					bValidTarget = asVerifyTarget(pOldNode);
//
//					if (bValidTarget)
//					{
//						pTargetNode = pOldNode;
//					}
//
//					break;
//				}
//			}
//		}
//	}
//
//	//if nothing in the old marquee, target the object itself
//	if (bValidTarget == false)
//	{
//	    QList< AsNode * >nodes = pUser->asGetObjectsAtUserCursor();
//	    if ( nodes.count() > 0 )
//	    {
//			AsNode *pCurrentNode = nodes.at(0);
//			bValidTarget = asVerifyTarget(pCurrentNode);
//
//			if (bValidTarget)
//			{
//				pTargetNode = pCurrentNode;
//			}
//		}
//    }
//
//	if (bValidTarget == false)
//	{
//		if (m_Action != AsActionOnText::AS_ACTION_NEW_TEXT_OBJECT)
//		{
//			qDebug( "[ AsActionOnObject ] - Failed to find target object!" );
//			As::writeErrorLog( "AsActionOnObject", "asRun", "Failed to find target object!", As::LOGLEVEL_ERROR );
//			return;
//		}
//    }
//
//    switch ( m_Action )
//    {
//    case AsActionOnText::AS_ACTION_NEW_TEXT_OBJECT:
//        {
//            // create new text object
//            AsNode *pPageNode = AsNode::asGetAscendant(m_pSourceNode.asGetNode(), AsObject::AS_OBJECT_PAGE );
//            AsNode * pNode  = this->m_pAsFactory->asBuildText( pPageNode, m_sText, AsTextRes::AS_INSPIRE_PLAIN, pos );
//
//            // create an undo step for the new object
//	        AsUndoController *pUndo = this->m_pAsFactory->asGetUndoController();
//			int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_NEW_TEXT) );
//            pUndo->asAddToUndoNewObject( undoId, pNode );
//            pUndo->asCommitUndoStep( undoId );
//
//            AsStudio::asInstance()->asFireObjectNew(pNode);
//        }
//        break;
//
//    case AsActionOnText::AS_ACTION_APPEND_TEXT:
//        {
//            AsText * pText = (AsText *) pTargetNode->asGetAsObjectReference();
//			AsTextRes * pTextRes = (AsTextRes *)pText->asGetResourcePointer();
//
//            if( pTextRes->asGetTextType() == AsTextRes::AS_INSPIRE_QT4_HTML )
//            {
//                // create undo step, we are going to edit the resource.
//    	        AsUndoController *pUndo = this->m_pAsFactory->asGetUndoController();
//				int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_EDIT_TEXT) );
//                pUndo->asAddToUndoEditObject( undoId, pTargetNode );
//
//				// get text in html format
//                QString sText = pTextRes->asGetText();
//
//				pText->asEdit();
//
//                // We now have the original text in html and the text to be appended as plain text.
//                // Use QTextCursor to merge both and return the combined text in html format
//                QTextEdit textEdit;
//                textEdit.setHtml(sText);
//                QTextCursor cursor = textEdit.textCursor();
//
//                // move to the end of current text
//                cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
//                int nPos = cursor.position();
//
//                // move back 1 space to remove CR
//                if( nPos > 0 )
//				{
//					cursor.setPosition( nPos - 1, QTextCursor::KeepAnchor );
//					QChar para(QChar::ParagraphSeparator);
//
//					if( cursor.selectedText().at(0) == para )
//					{
//						cursor.setPosition( nPos - 1, QTextCursor::MoveAnchor );
//					}
//					else
//					{
//						cursor.setPosition( nPos, QTextCursor::MoveAnchor );
//					}
//				}
//
//                // append new text
//                cursor.insertText(m_sText);
//				QString sHtml = textEdit.toHtml();
//
//                pText->asCommit(sHtml);
//
//                pUndo->asCommitUndoStep( undoId );
//
//                //tell the app weve changed
//				AsStudio::asInstance()->asFireObjectEdited( pTargetNode );
//				AsStudio::asInstance()->asPageUpdate( AsStudio::AS_PAGEUPDATE_CANVAS | AsStudio::AS_PAGEUPDATE_THUMBNAIL );
//            }
//        }
//        break;
//
//    case AsActionOnText::AS_ACTION_CHANGE_TEXT_VALUE:
//        {
//            AsText * pText = (AsText *) pTargetNode->asGetAsObjectReference();
//            AsTextRes * pTextRes = (AsTextRes *)pText->asGetResourcePointer();
//
//            if( pTextRes->asGetTextType() == AsTextRes::AS_INSPIRE_QT4_HTML )
//            {
//                // create undo step, we are going to edit the resource.
//    	        AsUndoController *pUndo = this->m_pAsFactory->asGetUndoController();
//				int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_CHANGE_TEXT_VALUE) );
//                pUndo->asAddToUndoEditObject( undoId, pTargetNode );
//
//				// get text in html format
//                QString sText = pTextRes->asGetText();
//
//				pText->asEdit();
//
//                QTextEdit textEdit;
//                textEdit.setHtml(sText);
//
//                // If the current text and action parameter text are both numeric then we add
//                // the parameter value to the current text value.
//                // Otherwise we simply replace the current value with the parameter value.
//                QString sPlainText = textEdit.toPlainText();
//                bool currentIsNumeric;
//                double current = sPlainText.toDouble( &currentIsNumeric );
//
//                bool valueIsNumeric;
//                double value = m_sText.toDouble( &valueIsNumeric );
//
//                QString sNew;
//                if (( currentIsNumeric ) && ( valueIsNumeric ))
//                {
//                    sNew = QString::number( current + value );
//                }
//                else
//                {
//                    sNew = m_sText;
//                }
//
//                // Use QTextCursor to merge both and return the combined text in html format
//                QTextCursor cursor = textEdit.textCursor();
//
//                // move to the end of current text
//                cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
//                cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
//
//                QTextCharFormat fmt = cursor.charFormat();
//
//                cursor.removeSelectedText();
//
//                cursor.setPosition(0, QTextCursor::MoveAnchor);
//
//                // insert new text
//                cursor.insertText(sNew,fmt);
//				QString sHtml = textEdit.toHtml();
//
//                pText->asCommit(sHtml);
//
//                pUndo->asCommitUndoStep( undoId );
//
//                AsStudio::asInstance()->asFireObjectEdited(pTargetNode);
//				AsStudio::asInstance()->asPageUpdate( AsStudio::AS_PAGEUPDATE_CANVAS | AsStudio::AS_PAGEUPDATE_THUMBNAIL );
//            }
//        }
//        break;
//
//    case AsActionOnText::AS_ACTION_DECONSTRUCT_TEXT: // used to de-construct text from source object
//        {
//            // first check if the source is a text object.
//            AsNode *pSourceNode = m_pSourceNode.asGetNode();
//            if ( pSourceNode == NULL )
//            {
//	            qDebug( "[ AsActionOnText ] - Failed to find source object!" );
//                As::writeErrorLog( "AsActionOnText", "asRun", "Failed to find source object!", As::LOGLEVEL_ERROR );
//                return;
//            }
//
//            AsText * pText = (AsText *) pSourceNode->asGetAsObjectReference();
//            if( pText->asGetType() != AsObject::AS_OBJECT_TEXT )
//            {
//                qDebug( "[ AsActionOnText ] - DeConstructText - source is not a text object!" );
//                As::writeErrorLog( "AsActionOnText", "asRun", "DeConstructText - source is not a text object!", As::LOGLEVEL_ERROR );
//                return;
//            }
//
//			// edit text before extract, work around for text from Firefox
//			// NN: remove this workaround once Qt issue is fixed
//			pUser->asDummyTextEdtit(pSourceNode);
//
//            AsTextRes * pTextRes = (AsTextRes *)pText->asGetResourcePointer();
//
//            AsTransform * pTransform = pText->asGetTransformPointer();
//
//            if( pTextRes->asGetTextType() == AsTextRes::AS_INSPIRE_QT4_HTML )
//            {
//                // FIXME: This call isn't reliable, due to the line spacing differences between V2 & V3 text,
//                // it may end up selecting the word on the previous line. The line spacing is greater in V3 (QTextEdit)
//                QString sHtml = pTextRes->asGetWordAtPosition( pText->asLastInvertedHitPos() );
//
//                if( sHtml.isEmpty() )
//                    return;
//
//                // create new text object
//                AsNode *pPageNode = AsNode::asGetAscendant(m_pSourceNode.asGetNode(), AsObject::AS_OBJECT_PAGE );
//                AsNode * pNode  = this->m_pAsFactory->asBuildText( pPageNode, sHtml, AsTextRes::AS_INSPIRE_QT4_HTML, pText->asLastInvertedHitPos() + pTransform->asGetTranslate() );
//
//                // create an undo step for the new object
//	            AsUndoController *pUndo = this->m_pAsFactory->asGetUndoController();
//				int undoId = pUndo->asAddUndoStep( AsLocale::asGetString(AsLocale::AS_STRING_DECONSTRUCT_TEXT) );
//                pUndo->asAddToUndoNewObject( undoId, pNode );
//                pUndo->asCommitUndoStep( undoId );
//
//                AsStudio::asInstance()->asFireObjectNew(pNode);
//            }
//        }
//        break;
//
//	default:
//		//Do Nothing
//		break;
//    }
}


void AsActionOnText::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}


void AsActionOnText::asSetSourceNode( AsPointer pSourceNode )
{
	m_pSourceNode = pSourceNode;
}


const AsPointer AsActionOnText::asGetSourceNode( void ) const
{
	return m_pSourceNode;
}

void AsActionOnText::asSetTargetNode( AsPointer pTargetNode )
{
	m_pTargetNode = pTargetNode;
}


const AsPointer AsActionOnText::asGetTargetNode( void ) const
{
	return m_pTargetNode;
}

void AsActionOnText::asSetAction( AsActionOnText::AsEnumAction action )
{
    m_Action = action;
}

AsActionOnText::AsEnumAction AsActionOnText::asGetAction( void ) const
{
    return m_Action;
}

void AsActionOnText::asSetText( QString & sText )
{
    m_sText = sText;
}

const QString & AsActionOnText::asGetText( void ) const
{
    return m_sText;
}

bool AsActionOnText::asVerifyTarget(AsNode *pTargetNode)
{
	//target must...
	//1. Be an AsText
	//2. Still exist on the page
	bool isValid = false;

//	if (pTargetNode != 0)
//	{
//		AsNode *pPageNode = AsApp::asInstance()->asGetCurrentPage();
//		QList<AsNode *> nodeList = pPageNode->asGetChildren();
//
//		for (int i = 0; i < nodeList.size(); i++)
//		{
//			if (pTargetNode == nodeList.at(i))
//			{
//				//target still exists - OK
//				AsObject *pObject = pTargetNode->asGetAsObjectReference();
//				AsRenderable *pText = qobject_cast<AsText *>(pObject);
//
//				if (pText != 0)
//				{
//					//target is text - OK
//					isValid = true;
//				}
//			}
//		}
//	}

	return isValid;
}

QString AsActionOnText::typeName()
{
    return "actionOnText";
}
