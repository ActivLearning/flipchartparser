/** @file aspage.cpp
 * Represents a page on the flipchart
 * Copyright (C) 2006-2009 Promethean Limited. All Rights Reserved.
 */

#include "aspage.h"
#include "../asfactory.h"
#include "../io/asfileio.h"
#include "asflipchart.h"
#include "../resources/asresourcemanager.h"
#include "astext.h"
#include <limits>
#include "asvirtualfolder.h"
#include "../util/asutil.h"
#include <QRectF>


const qreal TWO_PI = 6.28318530717959;

AsPage::AsPage(AsFactory * pAsFactory) : AsObject(pAsFactory), m_pGrid( AsPointer(0)), m_pBackground(0), m_bPageIsDirtyForNavigate(false)
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_PAGE );

    // Primitives.
    m_sName = "";
    m_sDescription = "";
    m_sTeacherNotes = "";
    m_RevealerMode = AsPage::AS_REVEALERMODE_FULL;
    m_nRevealedDistance = 0;
    m_nQuestionID = 0;
    m_nAsyncTestID = 0;
    m_bGridVisible = false;
    m_bOverlayBackground = false;
    m_bThumbnailDirty = false;

    m_SpotlightMode = AsPage::AS_SPOTLIGHTMODE_CIRCLE;


    m_nNextAnnotationNumber = 0;
    m_nNextImageNumber = 0;
    m_nNextActivityNumber = 0;
    m_nNextTextNumber = 0;
    m_nNextConnectorNumber = 0;
    m_nNextMediaContainerNumber = 0;
    m_nNextShapeNumber = 0;
    m_nNextGroupNumber = 0;
    m_nextMathMLNumber = 0;
    m_nextVerTextNumber = 0;
    m_PageFrameSize = QSizeF( 0.0f, 0.0f );

    m_pageToolMode = AsPage::AS_PAGE_TOOL_MODE_AS_BEFORE;
    m_bPageResetDataDirty = false;


    /* initialize the page size to screen size by default
    if the page size is different it will be update through property controller in setpagesize */




    m_Transition = AsPage::AS_PER_PAGE_TRANSITION_NONE;

    m_bPageIsExtended = false;
}

AsPage::AsPage( const AsPage& page ) : AsObject( page )
{
    this->asCopy( page );
}

AsPage::~AsPage()
{
    // Delete the nodes below m_Background.
//    AsFactory *pAsFactory = AsObject::asGetFactoryPointer();
}

void AsPage::operator= ( const AsPage& page )
{
    AsObject::operator = ( page );
    this->asCopy( page );
}

void AsPage::asCopy( const AsPage& page )
{
    this->m_sName = page.asGetName();
    this->m_sDescription = page.asGetDescription();
    this->m_Keywords = page.asGetKeywords();
    this->m_sTeacherNotes = page.asGetTeacherNotes();
    this->m_PageSize = page.asGetPageSize();
    this->m_PageFrameSize = page.asGetPageFrameSize();
    m_pBackground = page.m_pBackground;
    this->m_RevealerMode = page.asGetRevealerMode();
    this->m_nRevealedDistance = page.asGetRevealedDistance();
    this->m_nQuestionID = page.asGetQuestionID();
    this->m_bThumbnailDirty = page.asIsThumbnailDirty(); //TODO: Should this be hardcoded to true/false?
    this->m_SpotlightMode = page.asGetSpotlightMode();

    this->m_nNextAnnotationNumber = page.asGetNextAnnotationNumber();
    this->m_nNextImageNumber = page.asGetNextImageNumber();
    this->m_nNextTextNumber = page.asGetNextTextNumber();
    this->m_nNextConnectorNumber = page.asGetNextConnectorNumber();
    this->m_nNextMediaContainerNumber = page.asGetNextMediaContainerNumber();
    this->m_nNextShapeNumber = page.asGetNextShapeNumber();
    this->m_nNextGroupNumber = page.asGetNextGroupNumber();
    m_nextMathMLNumber = page.asGetNextMathMLNumber();
    m_nextVerTextNumber = page.asGetNextVerTextNumber();
    this->m_pageToolMode = page.asGetPageToolMode();
    this->m_nAsyncTestID = page.asGetAsyncTestID();

    this->m_Transition = page.asGetPerPageTransition();
    this->m_bPageIsDirtyForNavigate = page.asGetPageIsDirtyForNavigate();
    this->m_v2PageNavigationLinks = page.m_v2PageNavigationLinks;
}

QHash<QString, quint16>& AsPage::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "dateTimeCreated", ( quint16 )AsPage::AS_PROPERTY_DATETIMECREATED );

        // From AsPage...
        HashProperties.insert( "name", ( quint16 )AsPage::AS_PROPERTY_NAME );
      //  HashProperties.insert( "description", ( quint16 )AsPage::AS_PROPERTY_DESCRIPTION );
     //   HashProperties.insert( "keywords", ( quint16 )AsPage::AS_PROPERTY_KEYWORDS );
     //   HashProperties.insert( "teacherNotes", ( quint16 )AsPage::AS_PROPERTY_TEACHERNOTES );
        HashProperties.insert( "pageSize", ( quint16 )AsPage::AS_PROPERTY_PAGESIZE );
        HashProperties.insert( "pageFrameSize", ( quint16 )AsPage::AS_PROPERTY_PAGEFRAMESIZE );
     //   HashProperties.insert( "background", ( quint16 )AsPage::AS_PROPERTY_BACKGROUND );
        HashProperties.insert( "revealerMode", ( quint16 )AsPage::AS_PROPERTY_REVEALERMODE );
        HashProperties.insert( "revealedDistance", ( quint16 )AsPage::AS_PROPERTY_REVEALEDDISTANCE );
       // HashProperties.insert( "gridPointer", ( quint16 )AsPage::AS_PROPERTY_GRIDPOINTER );
      //  HashProperties.insert( "questionID", ( quint16 )AsPage::AS_PROPERTY_QUESTIONID );
        //HashProperties.insert( "spotlightMode", ( quint16 )AsPage::AS_PROPERTY_SPOTLIGHTMODE );
        HashProperties.insert( "gridVisible", ( quint16 )AsPage::AS_PROPERTY_GRIDVISIBLE );
      //  HashProperties.insert( "spotlightBounds", ( quint16 )AsPage::AS_PROPERTY_SPOTLIGHTBOUNDS );
     //   HashProperties.insert( "nextAnnotationNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTANNOTATIONNUMBER );
     //   HashProperties.insert( "nextImageNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTIMAGENUMBER );
     //   HashProperties.insert( "nextTextNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTTEXTNUMBER );
     //   HashProperties.insert( "nextConnectorNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTCONNECTORNUMBER );
     //   HashProperties.insert( "nextMediaContainerNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTMEDIACONTAINERNUMBER );
     //   HashProperties.insert( "nextShapeNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTSHAPENUMBER );
    //    HashProperties.insert( "nextGroupNumber", ( quint16 )AsPage::AS_PROPERTY_NEXTGROUPNUMBER );
        HashProperties.insert( "overlayBackground", ( quint16 )AsPage::AS_PROPERTY_OVERLAYBACKGROUND );
    //    HashProperties.insert( "pageToolMode", ( quint16 )AsPage::AS_PROPERTY_PAGE_TOOL_MODE );
    //    HashProperties.insert( "asyncTestID", ( quint16 )AsPage::AS_PROPERTY_ASYNCTESTID );
        HashProperties.insert( "originPoint", ( quint16 )AsPage::AS_PROPERTY_XYORIGIN );
        HashProperties.insert( "perPageTransition", ( quint16 )AsPage::AS_PROPERTY_TRANSITION );
    }

    return HashProperties;
}

void AsPage::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const QString& AsPage::asGetName( void ) const
{
    return m_sName;
}

void AsPage::asSetName( const QString& sName )
{
    m_sName = sName;
}

const QString& AsPage::asGetDescription( void ) const
{
    return m_sDescription;
}

void AsPage::asSetDescription( QString& sDescription )
{
    m_sDescription = sDescription;
}

const QStringList& AsPage::asGetKeywords( void ) const
{
    return m_Keywords;
}

void AsPage::asSetKeywords( QStringList& keywords )
{
    QStringList oldKeywords;
    QStringList tempKeywords;

    foreach( QString keyword, keywords )
    {
        keyword = keyword.remove('\"');
        keyword = keyword.remove(',');
        tempKeywords.append( keyword );
    }

    if( m_Keywords != tempKeywords )
    {
        oldKeywords = m_Keywords;
        m_Keywords = tempKeywords;
    }

    QStringListIterator i( oldKeywords );
    while( i.hasNext() )
    {
        if( !m_Keywords.contains( i.next() ) )
        {
            //keyword has been removed/edited

        }
    }
    QStringListIterator j( m_Keywords );
    while( j.hasNext() )
    {
        QString keyword = j.next();
        if( !oldKeywords.contains( keyword ) )
        {
            //keyword has been added/edited


        }
    }
}

void AsPage::asAppendKeyword( QString& sKeyword )
{
    m_Keywords.append( sKeyword );
}

void AsPage::asClearKeywords( void )
{
    m_Keywords.clear();
}

const QString& AsPage::asGetTeacherNotes( void ) const
{
    return m_sTeacherNotes;
}

void AsPage::asSetTeacherNotes( QString& sTeacherNotes )
{
    m_sTeacherNotes = sTeacherNotes;
}

void AsPage::asResetTeacherNotes()
{
    m_sTeacherNotes = "";
}

const QSizeF& AsPage::asGetPageSize( void ) const
{
    return m_PageSize;
}

void AsPage::asSetPageSize( const QSizeF& pageSize, AsNode * pPageNode )
{
    qreal w = pageSize.width();
    qreal h = pageSize.height();

    if( w < 0.0f ) { w = 0.0f; }
    if( h < 0.0f ) { h = 0.0f; }

    m_PageSize = QSizeF( w, h );




}

const QSizeF& AsPage::asGetPageFrameSize( void ) const
{
    return m_PageFrameSize;
}

void AsPage::asSetPageFrameSize( QSizeF& pageFrameSize )
{
    // Older flipcharts might have -1.0f set for width and height.
    // Also this value realy should be an int but is out there as a float.
    int w = ( int )( pageFrameSize.width() );
    int h = ( int )( pageFrameSize.height() );

    if( w < 0 ) { w = 0; }
    if( h < 0 ) { h = 0; }

    m_PageFrameSize = QSizeF( w, h );
}

void AsPage::asSetBackgroundPointer( AsPointer background )
{
    m_pBackground = background;
}

AsPointer AsPage::asGetBackgroundPointer( void )
{
    return m_pBackground;
}

void AsPage::asSetPerPageTransition( AsPage::AsPerPageTransition effect )
{
    m_Transition = effect;
}

AsPage::AsPerPageTransition AsPage::asGetPerPageTransition( void ) const
{
    return m_Transition;
}

AsPage::AsSpotlightMode AsPage::asGetSpotlightMode( void ) const
{
    return m_SpotlightMode;
}

void AsPage::asSetSpotlightMode( AsPage::AsSpotlightMode newMode)
{
    m_SpotlightMode = newMode;
}





quint32 AsPage::asGetNextAnnotationNumber() const
{
    return m_nNextAnnotationNumber;
}

void AsPage::asSetNextAnnotationNumber(quint32 nNextAnnotationNumber)
{
    m_nNextAnnotationNumber = nNextAnnotationNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextImageNumber() const
{
    return m_nNextImageNumber;
}

void AsPage::asSetNextImageNumber(quint32 nNextImageNumber)
{
    m_nNextImageNumber = nNextImageNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextActivityNumber() const
{
    return m_nNextActivityNumber;
}

void AsPage::asSetNextActivityNumber(quint32 nNextActivityNumber)
{
    m_nNextActivityNumber = nNextActivityNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextTextNumber() const
{
    return m_nNextTextNumber;
}

void AsPage::asSetNextTextNumber(quint32 nNextTextNumber)
{
    m_nNextTextNumber = nNextTextNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextConnectorNumber() const
{
    return m_nNextConnectorNumber;
}

void AsPage::asSetNextConnectorNumber(quint32 nNextConnectorNumber)
{
    m_nNextConnectorNumber = nNextConnectorNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextMediaContainerNumber() const
{
    return m_nNextMediaContainerNumber;
}

void AsPage::asSetNextMediaContainerNumber(quint32 nNextMediaContainerNumber)
{
    m_nNextMediaContainerNumber = nNextMediaContainerNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextShapeNumber() const
{
    return m_nNextShapeNumber;
}

void AsPage::asSetNextShapeNumber(quint32 nNextShapeNumber)
{
    m_nNextShapeNumber = nNextShapeNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextMathMLNumber() const
{
    return m_nextMathMLNumber;
}

void AsPage::asSetNextMathMLNumber(quint32 nNextMathMLNumber)
{
    m_nextMathMLNumber = nNextMathMLNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextVerTextNumber() const
{
    return m_nextVerTextNumber;
}

void AsPage::asSetNextVerTextNumber(quint32 nNextVerTextNumber)
{
    m_nextVerTextNumber = nNextVerTextNumber;
    asSetDirtyForWrite(true);
}

quint32 AsPage::asGetNextGroupNumber() const
{
    return m_nNextGroupNumber;
}

void AsPage::asSetNextGroupNumber(quint32 nNextGroupNumber)
{
    m_nNextGroupNumber = nNextGroupNumber;
    asSetDirtyForWrite(true);
}

const AsPage::AsRevealerMode& AsPage::asGetRevealerMode( void ) const
{
    return m_RevealerMode;
}

void AsPage::asSetRevealerMode( AsPage::AsRevealerMode newMode )
{
    m_RevealerMode = newMode;
}

double AsPage::asGetRevealedDistance( void ) const
{
    return m_nRevealedDistance;
}

void AsPage::asSetRevealedDistance( double newDist )
{
    m_nRevealedDistance = newDist;
}

AsPointer AsPage::asGetGridPointer( void )
{
    return m_pGrid;
}

void AsPage::asSetGridPointer( AsPointer grid )
{
    m_pGrid = grid;
}

QRectF AsPage::asGetRevealerRect() const
{
    QRectF rect;

    switch( this->m_RevealerMode )
    {
        case AsPage::AS_REVEALERMODE_BOTTOM:
            rect.setTop( 0 );
            rect.setLeft( 0 );
            rect.setWidth( m_PageSize.width() );
            if( m_nRevealedDistance < m_PageSize.height() )
                rect.setHeight( m_PageSize.height() - m_nRevealedDistance );
            else rect.setHeight( 0 );
            break;

        case AsPage::AS_REVEALERMODE_TOP:
            if( m_nRevealedDistance < m_PageSize.height() )
                rect.setHeight( m_PageSize.height() - m_nRevealedDistance );
            else rect.setHeight( 0 );
            rect.moveBottom( m_PageSize.height() );
            rect.setLeft( 0 );
            rect.setWidth( m_PageSize.width() );
            break;

        case AsPage::AS_REVEALERMODE_LEFT:
            rect.setTop( 0 );
            rect.setHeight( m_PageSize.height() );
            if( m_nRevealedDistance < m_PageSize.width() )
                rect.setWidth( m_PageSize.width() - m_nRevealedDistance );
            else rect.setWidth( 0 );
            rect.moveRight( m_PageSize.width() );
            break;

        case AsPage::AS_REVEALERMODE_RIGHT:
            rect.setTop( 0 );
            rect.setHeight( m_PageSize.height() );
            rect.setLeft( 0 );
            if( m_nRevealedDistance < m_PageSize.width() )
                rect.setWidth( m_PageSize.width() - m_nRevealedDistance );
            else rect.setWidth( 0 );
            break;

        case AsPage::AS_REVEALERMODE_FULL:
            rect.setTop( 0 );
            rect.setLeft( 0 );
            rect.setWidth( m_PageSize.width() );
            rect.setHeight( m_PageSize.height() );
            break;

        default:
            return QRectF();
    }

    return rect;
}

quint32 AsPage::asGetQuestionID( void ) const
{
    return this->m_nQuestionID;
}

void AsPage::asSetQuestionID( quint32 id )
{
    this->m_nQuestionID = id;
}

bool AsPage::asGetGridVisible()
{
    return m_bGridVisible;
}

void AsPage::asSetGridVisible(bool bGridVisible)
{
    m_bGridVisible = bGridVisible;

    // GJO. Temp. Logic below belongs in another place.
    // Putting it here affects the streaming.

    /*
    AsApp * pApplication = AsApp::asInstance();

    if (pApplication != 0)
    {
        QList<AsNode *> listNodeGrids = pApplication->asGetGrids();

        int nGrids = listNodeGrids.size();

        for (int i=0; i<nGrids; ++i)
        {
            AsNode * pNode = listNodeGrids.at(i);

            if (pNode != 0)
            {
                int nStyles = pNode->asGetChildCount();

                for (int j=0; j<nStyles; ++j)
                {
                    AsNode * pGSNode = pNode->asGetChildAt(j);

                    AsGridStyle * pGS = (AsGridStyle *)pGSNode->asGetAsObjectReference();

                    pGS->asSetVisible(m_bGridVisible);
                }
            }
        }
    }
    */
}

bool AsPage::asGetOverlayBackground()
{
    return m_bOverlayBackground;
}

void AsPage::asSetOverlayBackground(bool bOverlayBackground)
{
    m_bOverlayBackground = bOverlayBackground;
}

AsPage::AsPageToolMode AsPage::asGetPageToolMode() const
{
    return m_pageToolMode;
}

void AsPage::asSetPageToolMode(const AsPage::AsPageToolMode& mode)
{
    m_pageToolMode = mode;
}












bool AsPage::asIsThumbnailDirty( void ) const
{
    return m_bThumbnailDirty;
}

void AsPage::asSetThumbnailDirty( bool setting )
{
    m_bThumbnailDirty = setting;
}





QPointF AsPage::asGetPasteOffset( const QString& id )
{
    return m_pasteOffsets.value( id, QPointF() );
}

void AsPage::asSetPasteOffset( const QString& id, const QPointF& offset )
{
    m_pasteOffsets.insert( id, offset );
}

bool AsPage::asHasPasteOffset( const QString& offset )
{
    if ( m_pasteOffsets.contains( offset ))
        return true;

    return false;
}

bool AsPage::asGetPageResetDataDirty( void ) const
{
    return m_bPageResetDataDirty;
}

void AsPage::asSetPageResetDataDirty( bool b )
{
    m_bPageResetDataDirty = b;
}



quint32 AsPage::asGetAsyncTestID() const
{
    return this->m_nAsyncTestID;
}

void AsPage::asSetAsyncTestID(quint32 asyncTestID)
{
    this->m_nAsyncTestID = asyncTestID;
}












/**
  Adds each drawing response to the current slide in a grid layout

  @param images - list of images to be added

  */










bool AsPage::asGetPageIsDirtyForNavigate() const
{
    return m_bPageIsDirtyForNavigate;
}

void AsPage::asSetPageIsDirtyForNavigate(bool bPageIsDirtyForNavigate)
{
    m_bPageIsDirtyForNavigate = bPageIsDirtyForNavigate;
}

bool AsPage::asHasV2PageNavigationLinks() const
{
    if (m_v2PageNavigationLinks.size() > 0)
    {
        return true;
    }

    return false;
}

void AsPage::asSetPageNavigationLink(int nKey, int nData)
{
    m_v2PageNavigationLinks[nKey] = nData;
}

QHash<int, int> AsPage::asGetV2PageNavigationLinks() const
{
    return m_v2PageNavigationLinks;
}

void AsPage::asSetV2PageNavigationLinks(QHash<int, int>& v2PageNavigationLinks)
{
    m_v2PageNavigationLinks = v2PageNavigationLinks;
}

void AsPage::asFixPageNavigationLinks(int nOriginalPageId, int nNewPageId)
{
    for (QHash<int, int>::iterator i = m_v2PageNavigationLinks.begin(); i != m_v2PageNavigationLinks.end(); ++i)
    {
        int nValue = i.value();

        if (nValue == nOriginalPageId)
        {
            i.value() = nNewPageId;
        }
    }
}

void AsPage::asSetPageIsExtended( bool bIsExtended )
{
    m_bPageIsExtended = bIsExtended;
}

bool AsPage::asGetPageIsExtended() const
{
    return m_bPageIsExtended;
}

QString AsPage::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsPage::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsPage::typeName()
{
    return "page";
}


