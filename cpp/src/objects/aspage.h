/** @file aspage.h
 * Represents a page on the flipchart
 * Copyright (C) 2006-2009 Promethean Limited. All Rights Reserved.
 */

#ifndef ASPAGE_H
#define ASPAGE_H

#include <QString>
#include <QStringList>
#include <QSizeF>
#include "../objects/qcolor.h"

#include "asobject.h"
#include "asbackground.h"

class AsFactory;
class AsResourceManager;
class AsFileIO;
class AsUndoResourceIndex;
class AsVirtualFolder;
class AsRenderable;
class AsResponse;
class AsLabel;

class AsPage : public AsObject
{
Q_PROPERTY( QString asName READ asGetName WRITE asSetName  EDITABLE true )
Q_PROPERTY( QString asDescription READ asGetDescription WRITE asSetDescription EDITABLE true )
Q_PROPERTY( QStringList asKeywords READ asGetKeywords WRITE asSetKeywords EDITABLE true )
Q_PROPERTY( QString asTeacherNotes READ asGetTeacherNotes WRITE asSetTeacherNotes EDITABLE true )
Q_PROPERTY( QSizeF asPageSize READ asGetPageSize WRITE asSetPageSize EDITABLE true )
Q_PROPERTY( QSizeF asPageFrameSize READ asGetPageFrameSize WRITE asSetPageFrameSize EDITABLE true )
Q_PROPERTY( AsPointer asBackground READ asGetBackgroundPointer WRITE asSetBackgroundPointer EDITABLE true )
Q_PROPERTY( AsRevealerMode asRevealerMode READ asGetRevealerMode WRITE asSetRevealerMode EDITABLE true )
Q_PROPERTY( double asRevealedDistance READ asGetRevealedDistance WRITE asSetRevealedDistance EDITABLE true )
Q_PROPERTY( AsPointer asGridPointer READ asGetGridPointer WRITE asSetGridPointer )
Q_PROPERTY( quint32 asQuestionID READ asGetQuestionID WRITE asSetQuestionID )
Q_PROPERTY( AsSpotlightMode asSpotlightMode READ asGetSpotlightMode WRITE asSetSpotlightMode EDITABLE true )
Q_PROPERTY( bool asGridVisible READ asGetGridVisible WRITE asSetGridVisible EDITABLE true )
Q_PROPERTY( QRectF asSpotlightBounds READ asGetSpotlightBounds WRITE asSetSpotlightBounds EDITABLE true )
Q_PROPERTY( quint32 asNextAnnotationNumber READ asGetNextAnnotationNumber WRITE asSetNextAnnotationNumber )
Q_PROPERTY( quint32 asNextImageNumber READ asGetNextImageNumber WRITE asSetNextImageNumber )
Q_PROPERTY( quint32 asNextTextNumber READ asGetNextTextNumber WRITE asSetNextTextNumber )
Q_PROPERTY( quint32 asNextConnectorNumber READ asGetNextConnectorNumber WRITE asSetNextConnectorNumber )
Q_PROPERTY( quint32 asNextMediaContainerNumber READ asGetNextMediaContainerNumber WRITE asSetNextMediaContainerNumber )
Q_PROPERTY( quint32 asNextShapeNumber READ asGetNextShapeNumber WRITE asSetNextShapeNumber )
Q_PROPERTY( quint32 asNextGroupNumber READ asGetNextGroupNumber WRITE asSetNextGroupNumber )
Q_PROPERTY( bool asOverlayBackground READ asGetOverlayBackground WRITE asSetOverlayBackground EDITABLE true )
Q_PROPERTY( AsPageToolMode asPageToolMode READ asGetPageToolMode WRITE asSetPageToolMode EDITABLE true )
Q_PROPERTY( quint32 asAsyncTestID READ asGetAsyncTestID WRITE asSetAsyncTestID )
Q_PROPERTY( QPointF asXYOrigin READ asGetXYOrigin WRITE asSetXYOrigin EDITABLE true )
Q_PROPERTY( AsPerPageTransition asPerPageTransition READ asGetPerPageTransition WRITE asSetPerPageTransition EDITABLE true )
Q_PROPERTY( quint32 asNextMathMLNumber READ asGetNextMathMLNumber WRITE asSetNextMathMLNumber )
Q_ENUMS( AsScaleMode AsRevealerMode AsSpotlightMode AsPageToolMode AsPerPageTransition )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsPage...
        AS_PROPERTY_NAME,
        AS_PROPERTY_DESCRIPTION,
        AS_PROPERTY_KEYWORDS,
        AS_PROPERTY_TEACHERNOTES,
        AS_PROPERTY_PAGESIZE,
        AS_PROPERTY_PAGEFRAMESIZE,
        AS_PROPERTY_BACKCOLOR,
        AS_PROPERTY_SCALEMODE,
        AS_PROPERTY_USERSCALE,
        AS_PROPERTY_BACKGROUND,
        AS_PROPERTY_REVEALERMODE,
        AS_PROPERTY_REVEALEDDISTANCE,
        AS_PROPERTY_GRIDPOINTER,
        AS_PROPERTY_QUESTIONID,
        AS_PROPERTY_SPOTLIGHTMODE,
        AS_PROPERTY_GRIDVISIBLE,
        AS_PROPERTY_SPOTLIGHTBOUNDS,
        AS_PROPERTY_NEXTANNOTATIONNUMBER,
        AS_PROPERTY_NEXTIMAGENUMBER,
        AS_PROPERTY_NEXTTEXTNUMBER,
        AS_PROPERTY_NEXTCONNECTORNUMBER,
        AS_PROPERTY_NEXTMEDIACONTAINERNUMBER,
        AS_PROPERTY_NEXTSHAPENUMBER,
        AS_PROPERTY_NEXTGROUPNUMBER,
        AS_PROPERTY_OVERLAYBACKGROUND,
        AS_PROPERTY_PAGE_TOOL_MODE,
        AS_PROPERTY_ASYNCTESTID,
        AS_PROPERTY_XYORIGIN,
        AS_PROPERTY_TRANSITION
    };

    enum AsRevealerMode
    {
        AS_REVEALERMODE_TOP = 0,    //The top (north) is exposed
        AS_REVEALERMODE_BOTTOM,     //The bottom (south) of the screen is exposed
        AS_REVEALERMODE_LEFT,       //The left (west) of the screen is exposed
        AS_REVEALERMODE_RIGHT,      //The right (east) of the screen is exposed
        AS_REVEALERMODE_FULL        //The entire screen (world) is filled, the dotted cross is on and dragging tests position to set direction mode
    };

    enum AsSpotlightMode
    {
        AS_SPOTLIGHTMODE_CIRCLE = 0,        //The spotlight will be circular or eliptical.
        AS_SPOTLIGHTMODE_SQUARE,            //The spotlight will be rectangular.
        AS_SPOTLIGHTMODE_CIRCLE_REVERSED,   //Eliptical solid spotlight(obscurer).
        AS_SPOTLIGHTMODE_SQUARE_REVERSED    //Rectangular solid spotlight(obscurer).
    };

    enum AsPageToolMode
    {
        AS_PAGE_TOOL_MODE_AS_BEFORE = 0,
        AS_PAGE_TOOL_MODE_REVEALER,
        AS_PAGE_TOOL_MODE_SPOTLIGHT,
        AS_PAGE_TOOL_MODE_OFF
    };

    enum AsPerPageTransition
    {
        AS_PER_PAGE_TRANSITION_NONE = 0,
        AS_PER_PAGE_TRANSITION_RANDOM,
        AS_PER_PAGE_TRANSITION_PAGE_CURL,
        AS_PER_PAGE_TRANSITION_CROSS_FADE,
        AS_PER_PAGE_TRANSITION_CUBE_ROTATE

    };

    AsPage( AsFactory * );
    virtual ~AsPage();

    AsPage( const AsPage& );
    void operator= ( const AsPage& );

    // Interface.
    void asResetPropertyIndex( void );

    const QString& asGetName( void ) const;
    void asSetName( const QString& );

    const QString& asGetDescription( void ) const;
    void asSetDescription( QString& );

    const QStringList& asGetKeywords( void ) const;
    void asSetKeywords( QStringList& );
    void asAppendKeyword( QString& );
    void asClearKeywords( void );

    const QString& asGetTeacherNotes( void ) const;
    void asSetTeacherNotes( QString& sTeacherNotes );
    void asResetTeacherNotes();

    const QSizeF& asGetPageSize( void ) const;
    void asSetPageSize( const QSizeF & pageSize, AsNode * pPageNode = NULL );

    const QSizeF& asGetPageFrameSize( void ) const;
    void asSetPageFrameSize( QSizeF& );

    AsPointer asGetBackgroundPointer( void );
    void asSetBackgroundPointer( AsPointer );

    AsPage::AsPerPageTransition asGetPerPageTransition( void ) const;
    void asSetPerPageTransition(AsPage::AsPerPageTransition effect );

    AsPage::AsSpotlightMode asGetSpotlightMode(void) const;
    void    asSetSpotlightMode( AsPage::AsSpotlightMode );

    const   QRectF& asGetSpotlightBounds( void ) const;
    void    asSetSpotlightBounds( QRectF& );

    quint32 asGetNextAnnotationNumber() const;
    void asSetNextAnnotationNumber(quint32 nNextAnnotationNumber);

    quint32 asGetNextImageNumber() const;
    void asSetNextImageNumber(quint32 nNextImageNumber);

    quint32 asGetNextActivityNumber() const;
    void asSetNextActivityNumber(quint32 nNextImageNumber);

    quint32 asGetNextTextNumber() const;
    void asSetNextTextNumber(quint32 nNextTextNumber);

    quint32 asGetNextConnectorNumber() const;
    void asSetNextConnectorNumber(quint32 nNextConnectorNumber);

    quint32 asGetNextMediaContainerNumber() const;
    void asSetNextMediaContainerNumber(quint32 nNextMediaContainerNumber);

    quint32 asGetNextShapeNumber() const;
    void asSetNextShapeNumber(quint32 nNextShapeNumber);

    quint32 asGetNextGroupNumber() const;
    void asSetNextGroupNumber(quint32 nNextGroupNumber);

    quint32 asGetNextMathMLNumber() const;
    void asSetNextMathMLNumber(quint32 nNextMathMLNumber);

    quint32 asGetNextVerTextNumber() const;
    void asSetNextVerTextNumber(quint32 nNextVerTextNumber);

    const   AsPage::AsRevealerMode& asGetRevealerMode( void ) const;
    void    asSetRevealerMode( AsPage::AsRevealerMode );

    double asGetRevealedDistance( void ) const;
    void asSetRevealedDistance( double );

    AsPointer asGetGridPointer( void );
    void asSetGridPointer( AsPointer );

    QRectF asGetRevealerRect() const;

    quint32 asGetQuestionID( void ) const;
    void asSetQuestionID( quint32 );

    quint32 asGetAsyncTestID() const;
    void asSetAsyncTestID( quint32 asyncTestID );

    bool asGetGridVisible();
    void asSetGridVisible(bool bGridVisible);

    bool asGetOverlayBackground();
    void asSetOverlayBackground(bool);

    AsPageToolMode asGetPageToolMode() const;
    void asSetPageToolMode(const AsPageToolMode&);

    //Create thumbnail from page objects
    QPixmap asCreateThumbnail( const QSize& size, bool useDefaultScaleForGrids = false );
    const QImage asCreateThumbnailImage( const QSize& size, QRect& actualSize );
    void asSaveThumbnail( QPixmap& thumbnail );
    //Get thumbnail from file unless dirty
   // QPixmap asGetThumbnail( const QSize& size = QSize( DEFAULT_THUMBNAIL_WIDTH, DEFAULT_THUMBNAIL_HEIGHT ) );
    //Get a thumbnail and return false if it didn't work;
    bool asGetThumbnail( QPixmap& thumbnail );

    bool asIsThumbnailDirty( void ) const;
    void asSetThumbnailDirty( bool setting );

    bool asHasQuestionText() const;

    QString asSetPageName();

    QPointF asGetPasteOffset( const QString& );
    void asSetPasteOffset( const QString&, const QPointF& );
    bool asHasPasteOffset( const QString& );

    bool asGetPageResetDataDirty( void ) const;
    void asSetPageResetDataDirty( bool );

    QPointF asGetXYOrigin() const;
    void asSetXYOrigin(const QPointF& ptXYOrigin);

    bool asIsValid();

//From AsApp
    // Objects.
    void asClearAnnotations( void );
    void asClearBackground( int undoId = -1 );
    void asClearGrid(int undoId = -1, bool bUpdatePage = true);
    QList<AsNode *> asGetGrids();
    void asClearObjects( void );
    void asClearPage( int undoId = -1 );
    void asClearObjectConnectors( AsNode *, int undoId = -1 );
    AsNode * asNewConnector( AsNode *from, AsNode *to, AsInk *ink = NULL );
    AsNode * asNewConnector( AsNode *from, QPointF& fromPoint, AsNode *, QPointF& toPoint, AsInk *ink = NULL );
    void asWordSeed( const QMultiMap<QString,AsResponse*>& responseMap );
    void asImageSeed( const QList< QImage > );
    
    bool asDeleteObject( AsNode *pObjectNode, int undoId );
    bool asDeleteObjects( AsNode *objectNode, int undoId = -1, bool checkOnlyMe = true );

    double asGetMaxZOrderForLayer(int nLayer);
    double asGetMinZOrderForLayer(int nLayer);
    AsRenderable * asGetNextRenderable(AsRenderable * pRenderable, AsNode ** ppNextNode);

    bool asWrite( bool bAllObjects = false );

    // Resource Reset folders.
    void asBuildPageResetFolder( const QString& sResPath = QString(), bool includeSoftChildren = false );
    bool asSetupBackgroundCache();

    bool asGetPageIsDirtyForNavigate() const;
    void asSetPageIsDirtyForNavigate(bool bPageIsDirtyForNavigate);

    bool asHasV2PageNavigationLinks() const;
    void asSetPageNavigationLink(int nKey, int nData);
    QHash<int, int> asGetV2PageNavigationLinks() const;
    void asSetV2PageNavigationLinks(QHash<int, int>& v2PageNavigationLinks);
    void asFixPageNavigationLinks(int nOriginalPageId, int nNewPageId);

    void asSetPageIsExtended( bool bIsExtended );
    bool asGetPageIsExtended() const;

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;


private:
    void asCopy( const AsPage& );
    QString asPrepareResponderInfo(QList<AsResponse*> responses);
    void asBuildPageResetFolderSaveResource( AsResourceManager *pResourceManager, AsFileIO *pIo, AsUndoResourceIndex *pResourceIndex, AsVirtualFolder *, AsResource *pResource, AsObject *pObject, const QString & sWorkingPath );

    void asSetUpWordSeedObjectLabel(QList<AsResponse*>& responses, AsLabel& label);

    // Property hash table.
    static QHash<QString, quint16>& m_lProperties( void );

    // Properties.
    QString m_sName;
    QString m_sDescription;
    QStringList m_Keywords;
    QString m_sTeacherNotes;
    QSizeF m_PageSize;
    QSizeF m_PageFrameSize;
    AsPage::AsPerPageTransition m_Transition;

    AsPage::AsRevealerMode m_RevealerMode;
    double m_nRevealedDistance;

    AsPage::AsSpotlightMode m_SpotlightMode;
   // QRectF m_SpotlightBounds;

    quint32 m_nNextAnnotationNumber;
    quint32 m_nNextImageNumber;
    quint32 m_nNextActivityNumber;
    quint32 m_nNextTextNumber;
    quint32 m_nNextConnectorNumber;
    quint32 m_nNextMediaContainerNumber;
    quint32 m_nNextShapeNumber;
    quint32 m_nNextGroupNumber;
    quint32 m_nextMathMLNumber;
    quint32 m_nextVerTextNumber;

    // RED FLAG Back pointer indicating if this page has a grid. TEMP!!!!
    AsPointer m_pGrid;
    AsPointer m_pBackground;

    quint32 m_nQuestionID;
    quint32 m_nAsyncTestID;

    bool m_bGridVisible;
    bool m_bOverlayBackground;

    AsPageToolMode m_pageToolMode;

    bool m_bThumbnailDirty;

    QHash< QString, QPointF > m_pasteOffsets;

    bool m_bPageResetDataDirty;

  //  QPointF m_ptXYOrigin;

    bool m_bPageIsDirtyForNavigate;

    // Associate target page ID (key) with original page index (data) for V2 pages only.

    QHash<int, int> m_v2PageNavigationLinks;

    bool     m_bPageIsExtended;
};


#endif // ASPAGE_H
