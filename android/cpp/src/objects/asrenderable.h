// Defines the AsRenderable class.
// $Author: Paul Wareing.

#ifndef ASRENDERABLE_H
#define ASRENDERABLE_H

#include <QObject>
//#include <QColor>
#include <QSizeF>
//#include <QPainter>
#include <QPointF>

#include "asobject.h"
#include "astransform.h"
#include "asink.h"
#include "asorigin.h"
#include "../dataStruct/asrectf.h"
#include "../objects/aspointer.h"
//#include "asmath.h"
//#include "aslabel.h"
//#include <common/asinputmethod.h>

class AsFactory;
class AsNode;
class AsUser;


/**
 * An abstract base class for stuff we want to draw (images, lines, text etc.)
 */
class AsRenderable : public AsObject
{
Q_PROPERTY( AsTransform asTransform READ asGetTransform WRITE asSetTransform EDITABLE true)
Q_PROPERTY( QPointF asTwips READ asGetTwips WRITE asSetTwips )
Q_PROPERTY( QString asName READ asGetName WRITE asSetName EDITABLE true)
Q_PROPERTY( QStringList asKeywords READ asGetKeywords WRITE asSetKeywords EDITABLE true )
Q_PROPERTY( bool asVisible READ asIsVisible WRITE asSetVisible EDITABLE true )
Q_PROPERTY( AsRectF asBoundingRect READ asGetBoundingRect WRITE asSetBoundingRect EDITABLE true )
Q_PROPERTY( int asLayer READ asGetLayer WRITE asSetLayer EDITABLE true )
Q_PROPERTY( double asZ READ asGetZ WRITE asSetZ EDITABLE true )
Q_PROPERTY( AsInk asInk READ asGetInk WRITE asSetInk EDITABLE true )
Q_PROPERTY( AsOrigin asScaleOrigin READ asGetScaleOrigin WRITE asSetScaleOrigin EDITABLE true )
Q_PROPERTY( AsOrigin asRotateOrigin READ asGetRotateOrigin WRITE asSetRotateOrigin EDITABLE true )
Q_PROPERTY( AsEnumCanMove asCanMove READ asGetCanMove WRITE asSetCanMove EDITABLE true )
Q_PROPERTY( AsEnumCanSize asCanSize READ asGetCanSize WRITE asSetCanSize EDITABLE true )
Q_PROPERTY( AsEnumCanRotate asCanRotate READ asGetCanRotate WRITE asSetCanRotate EDITABLE true )
Q_PROPERTY( bool asCanBlock READ asGetCanBlock WRITE asSetCanBlock EDITABLE true )
Q_PROPERTY( bool asCanSnap READ asGetCanSnap WRITE asSetCanSnap EDITABLE true )
Q_PROPERTY( bool asLocked READ asGetLocked WRITE asSetLocked EDITABLE true )
Q_PROPERTY( bool asSnapback READ asGetSnapback WRITE asSetSnapback EDITABLE true )
Q_PROPERTY( AsPointer asPathPointer READ asGetPathPointer WRITE asSetPathPointer EDITABLE true )
Q_PROPERTY( AsPointer asRotateAboutPointer READ asGetRotateAboutPointer WRITE asSetRotateAboutPointer EDITABLE true )
Q_PROPERTY( QPointF asRotatePoint READ asGetRotatePoint WRITE asSetRotatePoint EDITABLE true )
Q_PROPERTY( AsEnumPoint asRotateAbout READ asGetRotateAbout WRITE asSetRotateAbout EDITABLE true )
Q_PROPERTY( int asRotateStep READ asGetRotateStep WRITE asSetRotateStep EDITABLE true )
Q_PROPERTY( AsPointer asSnapToPointer READ asGetSnapToPointer WRITE asSetSnapToPointer EDITABLE true )
Q_PROPERTY( QPointF asSnapPoint READ asGetSnapPoint WRITE asSetSnapPoint EDITABLE true )
Q_PROPERTY( AsEnumPoint asSnapTo READ asGetSnapTo WRITE asSetSnapTo EDITABLE true )
Q_PROPERTY( AsEnumCanContain asCanContain READ asGetCanContain WRITE asSetCanContain EDITABLE true )
Q_PROPERTY( AsPointer asContainPointer READ asGetContainPointer WRITE asSetContainPointer EDITABLE true )
Q_PROPERTY( QStringList asContainWords READ asGetContainWords WRITE asSetContainWords EDITABLE true )
Q_PROPERTY( AsEnumContainRule asContainRule READ asGetContainRule WRITE asSetContainRule EDITABLE true )
Q_PROPERTY( AsEnumV2Type asV2Type READ asGetV2Type WRITE asSetV2Type EDITABLE true )
Q_PROPERTY( QVariantList asConnectorList READ asGetConnectorList WRITE asSetConnectorList EDITABLE false )
Q_PROPERTY( AsLabel asLabel READ asGetLabel WRITE asSetLabel EDITABLE true )
Q_PROPERTY( bool asAllowSnapback READ asGetAllowSnapback WRITE asSetAllowSnapback EDITABLE false )
Q_PROPERTY( int asTranslucency READ asGetTranslucency WRITE asSetTranslucency )
Q_PROPERTY( QPointF asTopLeft READ asGetTopLeft WRITE asSetTopLeft EDITABLE true)
Q_PROPERTY( double asWidth READ asGetWidth WRITE asSetWidth EDITABLE true)
Q_PROPERTY( double asHeight READ asGetHeight WRITE asSetHeight EDITABLE true)
Q_PROPERTY( bool asDragACopy READ asGetDragACopy WRITE asSetDragACopy EDITABLE true)
Q_PROPERTY( AsEnumQuestionItem asQuestionItem READ asGetQuestionItem WRITE asSetQuestionItem EDITABLE false )
Q_PROPERTY( int asQuestionItemID READ asGetQuestionItemID WRITE asSetQuestionItemID EDITABLE false )
Q_PROPERTY( AsEnumQuestionTag asQuestionTag READ asGetQuestionTag WRITE asSetQuestionTag EDITABLE true )
Q_PROPERTY( bool asRewardSound READ asGetRewardSound WRITE asSetRewardSound EDITABLE true)
Q_PROPERTY( QString asRewardSoundLocation READ asGetRewardSoundLocation WRITE asSetRewardSoundLocation EDITABLE true)
Q_PROPERTY( AsEnumAsyncTestTag asAsyncTestTag READ asGetAsyncTestTag WRITE asSetAsyncTestTag EDITABLE true )
Q_PROPERTY( AsEnumInteractMode asInteractMode READ asGetInteractMode WRITE asSetInteractMode EDITABLE true )

Q_ENUMS( AsEnumInteractMode )
Q_ENUMS( AsEnumCanMove )
Q_ENUMS( AsEnumCanSize )
Q_ENUMS( AsEnumCanRotate )
Q_ENUMS( AsEnumCanContain )
Q_ENUMS( AsEnumContainRule )
Q_ENUMS( AsEnumPoint )
Q_ENUMS( AsEnumV2Type )
Q_ENUMS( AsEnumQuestionItem )
Q_ENUMS( AsEnumQuestionTag )
Q_ENUMS( AsEnumAsyncTestTag )

public:

    enum AsEnumInteractMode
    {
        ASINTERACTMODE_NONE = 0,
        ASINTERACTMODE_ANY = 1,
        ASINTERACTMODE_ACTIVPEN = 2,
        ASINTERACTMODE_TOUCH = 3,
    };

    enum AsEnumCanMove
    {
        ASCANMOVE_NONE = 0,
        ASCANMOVE_FREELY,
        ASCANMOVE_VERTICALLY,
        ASCANMOVE_HORIZONTALLY,
        ASCANMOVE_ALONGPATH
    };

    enum AsEnumCanSize
    {
        ASCANSIZE_NONE = 0,
        ASCANSIZE_FREELY
    };

    enum AsEnumCanRotate
    {
        ASCANROTATE_NONE = 0,
        ASCANROTATE_FREELY,
        ASCANROTATE_CLOCKWISE,
        ASCANROTATE_ANTICLOCKWISE
    };

    enum AsEnumCanContain
    {
        ASCANCONTAIN_NONE = 0,
        ASCANCONTAIN_ANYTHING,
        ASCANCONTAIN_SPECIFICOBJECT,
        ASCANCONTAIN_KEYWORDS
    };

    enum AsEnumContainRule
    {
        ASCONTAINRULE_MATCHCENTRES = 0,
        ASCONTAINRULE_MATCHCOMPLETE
    };

    enum AsEnumPoint
    {
        ASPOINT_CENTRE = 0,
        ASPOINT_OTHERPLACE,
        ASPOINT_OTHEROBJECT,
        ASPOINT_FIRSTTEXTLINE,
        ASPOINT_SPECIFICPOINT,
        ASPOINT_TOPLEFT,
        ASPOINT_TOP,
        ASPOINT_TOPRIGHT,
        ASPOINT_LEFT,
        ASPOINT_RIGHT,
        ASPOINT_BOTTOMLEFT,
        ASPOINT_BOTTOM,
        ASPOINT_BOTTOMRIGHT
    };

    enum AsEnumV2Type
    {
        ASV2TYPE_NONE = 0,
        ASV2TYPE_ANNOTATION,
        ASV2TYPE_IMAGE,
        ASV2TYPE_ACTION,
        ASV2TYPE_LINE,
        ASV2TYPE_SHAPE,
        ASV2TYPE_TEXT,
        ASV2TYPE_PLACEHOLDER
    };

    enum AsEnumQuestionItem
    {
        ASQUESTIONITEM_NONE = 0,
        ASQUESTIONITEM_QUESTION,
        ASQUESTIONITEM_LABEL,
        ASQUESTIONITEM_OPTION,
    };

    enum AsEnumQuestionTag
    {
        ASQUESTIONTAG_NONE = 0,
        ASQUESTIONTAG_QUESTION,
        ASQUESTIONTAG_OPTION_1,
        ASQUESTIONTAG_OPTION_2,
        ASQUESTIONTAG_OPTION_3,
        ASQUESTIONTAG_OPTION_4,
        ASQUESTIONTAG_OPTION_5,
        ASQUESTIONTAG_OPTION_6,
        ASQUESTIONTAG_OPTION_7,
        ASQUESTIONTAG_LABEL_1,
        ASQUESTIONTAG_LABEL_2,
        ASQUESTIONTAG_LABEL_3,
        ASQUESTIONTAG_LABEL_4,
        ASQUESTIONTAG_LABEL_5,
        ASQUESTIONTAG_LABEL_6,
        ASQUESTIONTAG_LABEL_7,
        ASQUESTIONTAG_OPTION_8,
        ASQUESTIONTAG_OPTION_9,
        ASQUESTIONTAG_LABEL_8,
        ASQUESTIONTAG_LABEL_9,
        ASQUESTIONTAG_IMAGE,
        ASQUESTIONTAG_OPTION_IMAGE_1,
        ASQUESTIONTAG_OPTION_IMAGE_2,
        ASQUESTIONTAG_OPTION_IMAGE_3,
        ASQUESTIONTAG_OPTION_IMAGE_4,
        ASQUESTIONTAG_OPTION_IMAGE_5,
        ASQUESTIONTAG_OPTION_IMAGE_6,
        ASQUESTIONTAG_OPTION_IMAGE_7,
        ASQUESTIONTAG_OPTION_IMAGE_8,
        ASQUESTIONTAG_OPTION_IMAGE_9,
        ASQUESTIONTAG_DRAWING_BACKGROUND_IMAGE
    };

    enum AsEnumAsyncTestTag
    {
        ASASYNCTESTTAG_NONE = 0,
        ASASYNCTESTTAG_TITLE,
        ASASYNCTESTTAG_DESCRIPTION,
    };

    static const int n_kMin_Layer;
    static const int n_kMax_Layer;

    // Construction and destruction
    AsRenderable( AsFactory * );
    virtual ~AsRenderable();
    AsRenderable( const AsRenderable& );
    void operator= ( const AsRenderable& );

    bool operator== ( const AsRenderable& );

    // Interface.
    virtual bool asCheckHit(  const QPointF & worldPos ) = 0;
    virtual bool asCheckBoundingBoxHit(  const QPointF & worldPos );
    bool asCheckHitLabel( const QPointF& worldPos );
    bool asEnter( void );
    bool asLeave( void );

    // Action triggers
    virtual void asClicked( AsUser*, QPointF  );
    void asPlayRewardSound( void );

    // Properties.
    const AsTransform& asGetTransform( void ) const;
    void asSetTransform( const AsTransform& );
    AsTransform * asGetTransformPointer( void );

    const QPointF& asGetTwips( void ) const;
    void asSetTwips( const QPointF& );

    const QString& asGetName( void ) const;
    void asSetName( const QString& );

    const QStringList& asGetKeywords( void ) const;
    void asSetKeywords( const QStringList& );
    void asAppendKeywords( const QString& );
    void asClearKeywords( void );

    bool asIsVisible( void ) const;
    virtual void asSetVisible( bool );

    const AsRectF& asGetBoundingRect( void ) const;
    void asSetBoundingRect( const AsRectF& );

    int asGetLayer( void ) const;
    void asSetLayer( int );

    double asGetZ( void ) const;
    void asSetZ( double );

    const AsInk& asGetInk ( void ) const;
    virtual void asSetInk( const AsInk& );
    AsInk *asGetInkPointer( void );

    const AsOrigin& asGetScaleOrigin( void ) const;
    void asSetScaleOrigin( const AsOrigin& );

    const AsOrigin& asGetRotateOrigin( void ) const;
    void asSetRotateOrigin( const AsOrigin& );

    virtual AsEnumCanMove asGetCanMove( void ) const;
    virtual void asSetCanMove( AsRenderable::AsEnumCanMove );

    virtual AsEnumCanSize asGetCanSize( void ) const;
    virtual void asSetCanSize( AsRenderable::AsEnumCanSize );

    virtual AsEnumCanRotate asGetCanRotate( void ) const;
    virtual void asSetCanRotate( AsRenderable::AsEnumCanRotate );

//    bool asAllowsInteraction(AsInputMethod method) const;
    virtual AsEnumInteractMode asGetInteractMode( void ) const;
    virtual void asSetInteractMode( AsRenderable::AsEnumInteractMode );
    static void asSetDefaultInteractMode( AsRenderable::AsEnumInteractMode );

    bool asGetCanBlock( void ) const;
    void asSetCanBlock( bool );

    bool asGetCanSnap( void ) const;
    void asSetCanSnap( bool );

    bool asGetLocked( void ) const;
    void asSetLocked( bool );

    bool asGetSnapback( void ) const;
    void asSetSnapback( bool );

    const AsPointer asGetPathPointer( void ) const;
    void asSetPathPointer( AsPointer );

    const AsPointer asGetRotateAboutPointer( void ) const;
    void asSetRotateAboutPointer( AsPointer );

    const QPointF& asGetRotatePoint( void ) const;
    void asSetRotatePoint( const QPointF& );

    AsEnumPoint asGetRotateAbout( void ) const;
    void asSetRotateAbout( AsEnumPoint );

    int asGetRotateStep( void ) const;
    void asSetRotateStep( int );

    const AsPointer asGetSnapToPointer( void ) const;
    void asSetSnapToPointer( AsPointer );

    const QPointF& asGetSnapPoint( void ) const;
    void asSetSnapPoint( const QPointF& );

    AsEnumPoint asGetSnapTo( void ) const;
    void asSetSnapTo( AsEnumPoint );

    AsRenderable::AsEnumCanContain asGetCanContain( void ) const;
    void asSetCanContain( AsRenderable::AsEnumCanContain );

    const AsPointer asGetContainPointer( void ) const;
    void asSetContainPointer( AsPointer );

    const QStringList& asGetContainWords( void ) const;
    void asSetContainWords( const QStringList& );

    AsEnumContainRule asGetContainRule( void ) const;
    void asSetContainRule( AsEnumContainRule );

    AsEnumV2Type asGetV2Type( void ) const;
    void asSetV2Type( AsEnumV2Type );

    virtual AsRectF asGetTransformedBoundingRect( bool uniteLabel = false );
    void asComputeTransformedBoundingRect( void );

    const QPolygonF& asGetTransformedBoundingPoly( void );
    const QPolygonF asGetTransformedBoundingPoly( const AsRectF& rect );
    const AsRectF asGetRectWithTouchTolerence( const AsRectF& rect );
    void asComputeTransformedBoundingPoly( void );

    const QVariantList& asGetConnectorList( void ) const;
    void asSetConnectorList( const QVariantList& );

    void asAddConnectorRef( quint32 );
    void asRemoveConnectorRef( quint32 );

//    const AsLabel& asGetLabel( void ) const;
  //  void asSetLabel( const AsLabel& );
   // AsLabel * asGetLabelPointer( void );

    AsEnumQuestionItem asGetQuestionItem( void ) const;
    void asSetQuestionItem( AsEnumQuestionItem );

    int asGetQuestionItemID( void ) const;
    void asSetQuestionItemID( int );

    AsEnumQuestionTag asGetQuestionTag( void ) const;
    void asSetQuestionTag( AsEnumQuestionTag );

    //!returns the value of the tag in the enum based on the label or option number
    AsEnumQuestionTag asGetQuestionTagEnumValueFromIndex(int index, AsEnumQuestionItem tagType);

    //!returns the index of a label or option based on the question tag enum
    int asGetIndexFromQuestionTagEnum(AsEnumQuestionTag tag);

    AsEnumAsyncTestTag asGetAsyncTestTag() const;
    void asSetAsyncTestTag( AsEnumAsyncTestTag );

    // Motion Interface
    void asTransformPoint( QPointF& );
    void asUnTransformPoint( QPointF& );

    virtual void asTranslateTo(const QPointF&, bool forceDirty = false);
    virtual void asTranslateBy(const QPointF&, bool forceDirty = false);

    virtual void asRotateTo( const qreal );
    virtual void asRotateBy( const qreal );

    virtual void asScaleTo( const QPointF& );
    virtual void asScaleBy(const QPointF& scale,
               const bool maintainAspect = false);

    // Helper.
    QPointF asGetRotationPoint( AsEnumPoint );
    QPointF asGetSnapPoint( AsEnumPoint );
    virtual AsPointFArray asGetPoints( void );

    bool asOverlaps( const QRectF& );

    // Containers.
    bool asContains( AsRenderable *, int tolerance );
    void asSetDragStartPos( const QPointF& );
    QPointF& asGetDragStartPos( void );

    bool asGetAllowSnapback( void ) const;
    void asSetAllowSnapback( bool );

    virtual void asSetTranslucency(int translucency);
    virtual int asGetTranslucency() const;
    virtual int asGetTranslucency();
    void asSetTopLeft(QPointF pointTopLeft);
    const QPointF asGetTopLeft() const;

    void asSetWidth(double dWidth);
    double asGetWidth();

    void asSetHeight(double dHeight);
    double asGetHeight();

    bool asGetPlayedRewardSound( void );
    void asSetPlayedRewardSound( bool );

    // default implementation does nothing: override to ensure that bounding rect will be up-to-date
    // for calls to asGetBoundingRect() in the camera (important for calculating dirty rectangles)
    virtual void asPrepareBoundingRect();

    virtual bool asIsSelectable( void );

    // returns a list of AsRenderables, listing renderable group members but not the groups themselves
    static void asListGroupMembers( QList<AsRenderable*>&, AsNode* );

    bool asGetDragACopy( void ) const;
    void asSetDragACopy( bool );

    bool asGetRewardSound() const;
    void asSetRewardSound(bool bRewardSound);

    QString asGetRewardSoundLocation() const;
    void asSetRewardSoundLocation(const QString& bRewardSoundLocation);

    virtual QString asGetNewObjectName(quint32 nIndex);

    bool asIsTargettedForConnector() const;
    void asSetTargettedForConnector(bool targetted);

    virtual const QList<QPointF>  asGetAnchorPoints();

    qreal asGetRotateStepPortion( void ) const;
    void asSetRotateStepPortion( qreal );

    virtual QPointF asGetRotationCentre( void );

    virtual void asUpdateConnectorParams(AsNode*, AsUser* ) {};
public:
    Json::Value &serialized() override;

signals:
    void asRun_Clicked( AsUser*, QPointF pos );
    void asRewardSound( AsUser*, QPointF );

protected:
    static void asBuildGroupMembersList( QList<AsRenderable*>&, AsNode* );
    void asUpdateAssociatedConnectors();



    AsRectF m_TransformedBoundingRect;
//    QPolygonF m_TransformedBoundingPoly;
    bool m_bTransformedRectDirty;
    bool m_bTransformedPolyDirty;
  //  AsLabel m_Label;
    QList<AsRenderable*> m_expandedGroupsList;

private:
    void asCopy( const AsRenderable& );

    AsRectF m_BoundingRect;
    AsTransform m_Transform;

    QPointF m_Twips;
    QString m_sName;
    QStringList m_Keywords;
    bool m_bVisible;
    int m_nLayer;
    double m_nZ;
    AsInk m_Ink;
    AsOrigin m_ScaleOrigin;
    AsOrigin m_RotateOrigin;
    AsEnumCanMove m_CanMove;
    AsEnumCanSize m_CanSize;
    AsEnumCanRotate m_CanRotate;
    bool m_bCanBlock;
    bool m_bCanSnap;
    bool m_bLocked;
    bool m_bSnapback;
    AsPointer m_PathPointer;
    AsPointer m_RotateAboutPointer;
    QPointF m_RotatePoint;
    AsEnumPoint m_RotateAbout;
    int m_nRotateStep;
    AsPointer m_SnapToPointer;
    QPointF m_SnapPoint;
    AsEnumPoint m_SnapTo;
    AsEnumCanContain m_CanContain;
    AsPointer m_ContainPointer;
    QStringList m_ContainWords;
    AsEnumContainRule m_ContainRule;
    AsEnumV2Type m_V2Type;
    AsEnumQuestionItem m_QuestionItem;
    int m_nQuestionItemID;
    mutable AsEnumQuestionTag m_QuestionTag;
    mutable AsEnumAsyncTestTag m_AsyncTestTag;
    bool m_bDragACopy;
    bool m_bRewardSound;
    QString m_bRewardSoundLocation;

    unsigned int m_nTranslucency;

    // For the container parameter for 'return if not contained'.
    QPointF m_DragStartPos;
    bool m_bAllowSnapback;

    // For rewardsound.
    bool m_bPlayedRewardSound;

    bool m_bIsTargettedForConn;

    QVariantList m_ConnectorList;

    qreal m_rotateStepPortion;

    static AsEnumInteractMode m_defaultInteractMode;
    AsEnumInteractMode m_interactMode;

public:
    int m_assocCount; // debug for AsVisualObjNodeAssoc
};

#endif // ASRENDERABLE_H
