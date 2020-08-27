// Implements the AsActionNavigate class.
// $Author: Paul Ellis.

#include "asactionnavigate.h"
#include "../io/asnode.h"
#include "../asfactory.h"
#include "aspage.h"
#include "asflipchart.h"


namespace
{
    const int INVALID_PAGE_ID = 0;
    const int INVALID_PAGE_NUMBER = 0;
}

const int AsActionNavigate::FLP_FIRST_PASS_PAGE_NUMBER_MODIFIER = 10000000;

AsActionNavigate::AsActionNavigate( AsFactory *pAsFactory )
    : AsAction( pAsFactory ),
      m_NavigateType( AsActionNavigate::ASNAVIGATE_NEXTPAGE ),
	  m_nDestinationPageId( INVALID_PAGE_ID ),
      m_nDestinationPageNumber( INVALID_PAGE_NUMBER ),
      m_nDestinationPageVar( INVALID_PAGE_ID )  // or = INVALID_PAGE_NUMBER
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_NAVIGATEACTION );
}

AsActionNavigate::AsActionNavigate( const AsActionNavigate& actionNavigate ) : AsAction( actionNavigate )
{
    this->asCopy( actionNavigate );
}

AsActionNavigate::~AsActionNavigate()
{
}

void AsActionNavigate::operator= ( const AsActionNavigate& actionNavigate )
{
    AsAction::operator = ( actionNavigate );
    asCopy( actionNavigate );
}

void AsActionNavigate::asCopy( const AsActionNavigate& actionNavigate )
{
    m_NavigateType = actionNavigate.m_NavigateType;
    m_nDestinationPageId = actionNavigate.m_nDestinationPageId;
    m_nDestinationPageNumber = actionNavigate.m_nDestinationPageNumber;
    m_nDestinationPageVar = actionNavigate.m_nDestinationPageVar;
}

QHash<QString, quint16>& AsActionNavigate::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsActionNavigate::AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
	   // HashProperties.insert( "asActionFeatureType", ( quint16 )AsActionNavigate::AS_PROPERTY_ACTIONFEATURETYPE );

        // From AsActionNavigate...
	    HashProperties.insert( "navigateType", ( quint16 )AsActionNavigate::AS_PROPERTY_NAVIGATETYPE );
        HashProperties.insert( "destinationPage", ( quint16 )AsActionNavigate::AS_PROPERTY_GOTOPAGENUMBER );
    }

    return HashProperties;
}

void AsActionNavigate::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

void AsActionNavigate::asSetDestinationPageVar(int dest)
{
    // Store the property value
    if ( dest > FLP_FIRST_PASS_PAGE_NUMBER_MODIFIER )
    {
        // dest value is a page number
        m_nDestinationPageNumber = dest;
        m_nDestinationPageId = INVALID_PAGE_ID;
    }
    else
    {
        // dest value is a page id
        m_nDestinationPageNumber = INVALID_PAGE_NUMBER;
        m_nDestinationPageId = dest;
    }
    

    m_nDestinationPageVar = dest;
}

int AsActionNavigate::asGetDestinationPageVar() const
{

    return m_nDestinationPageVar;
}

void AsActionNavigate::asSetDestinationPageNumber( int pageNumber )
{
    if ( pageNumber > FLP_FIRST_PASS_PAGE_NUMBER_MODIFIER )
    {
        // First stage import of an flp and dest is a modified page number
        m_nDestinationPageNumber = pageNumber;
        m_nDestinationPageId = INVALID_PAGE_ID;
        m_nDestinationPageVar = m_nDestinationPageNumber;

    }
    else
    {
        // dest is a standard page number so convert to page id
        m_nDestinationPageNumber = INVALID_PAGE_NUMBER;
        m_nDestinationPageId = asGetPageId( pageNumber );
        m_nDestinationPageVar = m_nDestinationPageId;

    }
}

int AsActionNavigate::asGetDestinationPageNumber() const
{
    int pageNumber = m_nDestinationPageNumber;

    if (pageNumber <= FLP_FIRST_PASS_PAGE_NUMBER_MODIFIER)
    {
        pageNumber = asGetPageNumber(m_nDestinationPageId);
    }


    return pageNumber;
}

int AsActionNavigate::asGetDestinationPageId() const
{

    return m_nDestinationPageId;
}

void AsActionNavigate::asSetDestinationPageId( int pageId )
{
    m_nDestinationPageNumber = INVALID_PAGE_NUMBER;
    m_nDestinationPageId = pageId;
    m_nDestinationPageVar = pageId;

}

void AsActionNavigate::asSetNavigateType( AsActionNavigate::AsEnumNavigate type )
{
	this->m_NavigateType = type;
}

AsActionNavigate::AsEnumNavigate AsActionNavigate::asGetNavigateType( void ) const
{
	return this->m_NavigateType;
}

void AsActionNavigate::asRun( AsUser*, QPointF )
{
//    As::writeErrorLog( "AsActionNavigate", "asRun", qPrintable( QString::number( m_NavigateType ) ), As::LOGLEVEL_CRASHSUPPORT );
//
//	AsNode *pPageNode = AsApp::asInstance()->asGetCurrentPage();
//
////	AsNode* pFlipchartNode = AsApp::asInstance()->asGetCurrentFlipchart();
//    AsFlipchart * pFlipchart = AsApp::asInstance()->asGetFlipchartManager().asGetCurrentFlipchart();
//
//    // Enable page turn effects for all navigations via actions.
//    AsGuiController* pGuiController = AsStudio::asInstance()->asGetGuiControllerPointer();
//    pGuiController->asEnableTransitionEffects();
//    qDebug() << "[ AsActionNavigate::asRun ] - called asEnableTransitionEffects";
//
//	switch( this->m_NavigateType )
//	{
//	case AsActionNavigate::ASNAVIGATE_NEXTPAGE:
//		{
//			qDebug( "[ AsActionNavigate ] - asRun() - Next Page." );
//
//			//Get AsApp to change the page
//			if( pFlipchart->asSetNextPage() )
//			{
//				//Add current page to delete later list
//				AsFactory *pFactory = this->asGetFactoryPointer();
//				pFactory->asDeleteLater( pPageNode );
//			}
//		}
//		break;
//
//	case AsActionNavigate::ASNAVIGATE_PREVIOUSPAGE:
//		{
//			qDebug( "[ AsActionNavigate ] - asRun() - Previous Page." );
//
//			//Get AsApp to change the page
//			if( pFlipchart->asSetPreviousPage() )
//			{
//				//Add current page to delete later list
//				AsFactory *pFactory = this->asGetFactoryPointer();
//				pFactory->asDeleteLater( pPageNode );
//			}
//		}
//		break;
//
//	case AsActionNavigate::ASNAVIGATE_FIRSTPAGE:
//		{
//			qDebug( "[ AsActionNavigate ] - asRun() - First Page." );
//
//			//Get AsApp to change the page
//			if( pFlipchart->asSetFirstPage() )
//			{
//				//Add current page to delete later list
//				AsFactory *pFactory = this->asGetFactoryPointer();
//				pFactory->asDeleteLater( pPageNode );
//			}
//		}
//		break;
//
//	case AsActionNavigate::ASNAVIGATE_LASTPAGE:
//		{
//			qDebug( "[ AsActionNavigate ] - asRun() - Last Page." );
//
//			if( pFlipchart->asSetLastPage() )
//			{
//				//Add current page to delete later list
//				AsFactory *pFactory = this->asGetFactoryPointer();
//				pFactory->asDeleteLater( pPageNode );
//			}
//		}
//		break;
//
//	case AsActionNavigate::ASNAVIGATE_ANOTHERPAGE:
//		{
//            AsNode * pNewPageNode = pFlipchart->asSetPageById(m_nDestinationPageId);
//
//			if (pNewPageNode != 0 && pNewPageNode != pPageNode)
//			{
//				AsFactory * pFactory = asGetFactoryPointer();
//				pFactory->asDeleteLater(pPageNode);
//			}
//		}
//		break;
//
//	case AsActionNavigate::ASNAVIGATE_NEXTPAGEINHISTORY:
//		{
//			qDebug( "[ AsActionNavigate ] - asRun() - Next Page In History." );
//
//			//Get AsApp to change the page
//			if( pFlipchart->asSetNextPageInHistory() )
//			{
//				//Add current page to delete later list
//				AsFactory *pFactory = this->asGetFactoryPointer();
//				pFactory->asDeleteLater( pPageNode );
//			}
//		}
//		break;
//
//	case AsActionNavigate::ASNAVIGATE_PREVIOUSPAGEINHISTORY:
//		{
//			qDebug( "[ AsActionNavigate ] - asRun() - Previous Page In History." );
//
//			//Get AsApp to change the page
//			if( pFlipchart->asSetPrevPageInHistory() )
//			{
//				//Add current page to delete later list
//				AsFactory *pFactory = this->asGetFactoryPointer();
//				pFactory->asDeleteLater( pPageNode );
//			}
//		}
//		break;
//	}
}

quint32 AsActionNavigate::asGetPageId(int nPageNumber) const
{
    quint32 nPageId = INVALID_PAGE_ID;

//    AsApp * pApplication = AsApp::asInstance();
//
//    if (0 == pApplication) return nPageId;
//
//    const AsNode * pFlipchartNode = pApplication->asGetFlipchartManager().asGetCurrentFlipchartNode();
//    if (0 == pFlipchartNode) return nPageId;
//
//    int nPages = pFlipchartNode->asGetChildCount();
//
//    if (0 == nPages) return nPageId;
//
//    if (nPageNumber > nPages) return nPageId;
//
//    const AsNode * pPageNode = pFlipchartNode->asGetChildAt(nPageNumber - 1);
//
//    if (0 == pPageNode) return nPageId;
//
//    const AsObject * pObject = pPageNode->asGetAsObjectReference();
//
//    if (0 == pObject) return nPageId;
//
//    const AsPage * pPage = qobject_cast<const AsPage *>(pObject);
//
//    if (0 == pPage) return nPageId;
//
//    nPageId = pPage->asGetID();

    return nPageId;
}

int AsActionNavigate::asGetPageNumber(quint32 nPageId) const
{
    int nPageNumber = INVALID_PAGE_NUMBER;

//    AsApp * pApplication = AsApp::asInstance();
//
//    if (0 == pApplication) return nPageNumber;
//
//    AsNode * pFlipchartNode = pApplication->asGetFlipchartManager().asGetCurrentFlipchartNode();
//
//    if (0 == pFlipchartNode) return nPageNumber;
//
//    int nPages = pFlipchartNode->asGetChildCount();
//
//    for (int i=0; i<nPages; ++i)
//    {
//        AsNode * pPageNode = pFlipchartNode->asGetChildAt(i);
//
//        if (pPageNode != 0)
//        {
//            AsObject * pObject = pPageNode->asGetAsObjectReference();
//
//            if (pObject != 0)
//            {
//                AsPage * pPage = qobject_cast<AsPage *>(pObject);
//
//                if (pPage != 0)
//                {
//                    quint32 nCurrentPageId = pPage->asGetID();
//
//                    if (nCurrentPageId == nPageId)
//                    {
//                        nPageNumber = i+1;
//                        break;
//                    }
//                }
//            }
//        }
//    }

    return nPageNumber;
}

QString AsActionNavigate::typeName()
{
    return "actionNavigate";
}

QString AsActionNavigate::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsActionNavigate::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

bool AsActionNavigate::isAction()
{
    return true;
}

Json::Value &AsActionNavigate::serialized() {
    Json::Value& jsonObject= AsObject::serialized();
    Json::Value property;
    Variant var = this->property(AsActionNavigate::AS_PROPERTY_GOTOPAGENUMBER);

    if(var.value&&var.type==VariableType::INT)
      property["destinationPageId"]=*static_cast<int*>(var.value)+1;

    var = this->property(AsActionNavigate::AS_PROPERTY_NAVIGATETYPE);

    if(var.value&&var.type==VariableType::INT)
        property["navigateType"]=*static_cast<int*>(var.value);
    jsonObject["property"]=property;
    return jsonObject;
}
