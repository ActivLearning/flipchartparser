// Implements the AsRenderable class.
// $Author: Paul Wareing.

#include <QtDebug>

#include "asrenderable.h"
//#include "asrenderablegroup.h"
#include "../io/asnode.h"
//#include "asapp.h"
#include "asflipchart.h"
//#include "asflipchartmanager.h"
#include "../asfactory.h"
#include "../dataStruct/aspointfarray.h"
#include "qpolygonf.h"

namespace {
    const qreal MIN_TEXT_TOUCH_TOLERENCE = 30;
};

const int AsRenderable::n_kMin_Layer = -1;
const int AsRenderable::n_kMax_Layer = 2;
AsRenderable::AsEnumInteractMode AsRenderable::m_defaultInteractMode = AsRenderable::ASINTERACTMODE_ANY;

AsRenderable::AsRenderable(AsFactory *pAsFactory) : AsObject(pAsFactory) {
    m_bVisible = true;
    m_sName = "";
    m_nLayer = 1;
    m_nZ = -1;
    m_CanMove = AsRenderable::ASCANMOVE_FREELY;
    m_CanSize = AsRenderable::ASCANSIZE_FREELY;
    m_CanRotate = AsRenderable::ASCANROTATE_FREELY;
    m_nRotateStep = 0;
    m_bCanBlock = false;
    m_bCanSnap = true;
    m_bLocked = false;
    m_bSnapback = false;
    m_CanContain = AsRenderable::ASCANCONTAIN_NONE;
    m_ContainRule = AsRenderable::ASCONTAINRULE_MATCHCOMPLETE;
    m_RotateAbout = AsRenderable::ASPOINT_CENTRE;
    m_SnapTo = AsRenderable::ASPOINT_BOTTOMLEFT;
    m_V2Type = AsRenderable::ASV2TYPE_NONE;

    m_bTransformedRectDirty = true;
    m_bTransformedPolyDirty = true;
    m_bAllowSnapback = true;
    m_bPlayedRewardSound = false;
    m_assocCount = 0;

    this->m_QuestionItem = AsRenderable::ASQUESTIONITEM_NONE;
    this->m_nQuestionItemID = 0;
    this->m_QuestionTag = AsRenderable::ASQUESTIONTAG_NONE;

    m_AsyncTestTag = AsRenderable::ASASYNCTESTTAG_NONE;

    m_nTranslucency = 0;

    m_bDragACopy = false;
    m_bRewardSound = false;
    m_bIsTargettedForConn = false;

    m_rotateStepPortion = 0.0;
    m_interactMode = m_defaultInteractMode;
}

AsRenderable::AsRenderable(const AsRenderable &renderable) : AsObject(renderable) {
    this->asCopy(renderable);
    m_assocCount = 0;
}

void AsRenderable::operator=(const AsRenderable &renderable) {
    AsObject::operator=(renderable);
    this->asCopy(renderable);
}

void AsRenderable::asCopy(const AsRenderable &r) {
    m_Transform = r.asGetTransform();
    m_Twips = r.asGetTwips();
    m_sName = r.asGetName();
    m_Keywords = r.asGetKeywords();
    m_bVisible = r.asIsVisible();
    m_BoundingRect = r.asGetBoundingRect();
    m_nLayer = r.asGetLayer();
    m_nZ = r.asGetZ();
    m_Ink = r.asGetInk();
    m_ScaleOrigin = r.asGetScaleOrigin();
    m_RotateOrigin = r.asGetRotateOrigin();
    m_CanMove = r.asGetCanMove();
    m_CanSize = r.asGetCanSize();
    m_CanRotate = r.asGetCanRotate();
    m_bCanBlock = r.asGetCanBlock();
    m_bCanSnap = r.asGetCanSnap();
    m_bLocked = r.asGetLocked();
    m_bSnapback = r.asGetSnapback();
    m_PathPointer = r.asGetPathPointer();
    m_RotateAboutPointer = r.asGetRotateAboutPointer();
    m_RotatePoint = r.asGetRotatePoint();
    m_RotateAbout = r.asGetRotateAbout();
    m_nRotateStep = r.asGetRotateStep();
    m_SnapToPointer = r.asGetSnapToPointer();
    m_SnapPoint = r.asGetSnapPoint();
    m_SnapTo = r.asGetSnapTo();
    m_CanContain = r.asGetCanContain();
    m_ContainPointer = r.asGetContainPointer();
    m_ContainWords = r.asGetContainWords();
    m_ContainRule = r.asGetContainRule();
    m_V2Type = r.asGetV2Type();
    m_ConnectorList = r.asGetConnectorList();
    // m_Label = r.asGetLabel();
    m_QuestionItem = r.asGetQuestionItem();
    m_nQuestionItemID = r.asGetQuestionItemID();
    m_QuestionTag = r.asGetQuestionTag();
    m_bAllowSnapback = r.asGetAllowSnapback();
    m_nTranslucency = r.asGetTranslucency();
    m_bDragACopy = r.asGetDragACopy();
    m_bRewardSound = r.asGetRewardSound();
    m_bRewardSoundLocation = r.asGetRewardSoundLocation();
    m_bIsTargettedForConn = r.asIsTargettedForConnector();
    m_AsyncTestTag = r.asGetAsyncTestTag();
    m_interactMode = r.asGetInteractMode();;
}

AsRenderable::~AsRenderable() {
    // If you hit this assert you are deleting a renderable which the camera still
    // has a pointer to - without the assert it will crash later during paint.
    Q_ASSERT(m_assocCount == 0);
}

bool AsRenderable::operator==(const AsRenderable &r) {
    if (!AsObject::operator==(r)) {
        return false;
    }

    if ((!(m_Transform == r.asGetTransform())) ||
        (m_Twips != r.asGetTwips()) ||
        (m_sName != r.asGetName()) ||
        (m_Keywords != r.asGetKeywords()) ||
        (m_bVisible != r.asIsVisible()) ||
        (m_BoundingRect != r.asGetBoundingRect()) ||
        (m_nLayer != r.asGetLayer()) ||
        (m_nZ != r.asGetZ()) ||
        (!(m_Ink == r.asGetInk())) ||
        (!(m_ScaleOrigin == r.asGetScaleOrigin())) ||
        (!(m_RotateOrigin == r.asGetRotateOrigin())) ||
        (m_CanMove != r.asGetCanMove()) ||
        (m_CanSize != r.asGetCanSize()) ||
        (m_CanRotate != r.asGetCanRotate()) ||
        (m_bCanBlock != r.asGetCanBlock()) ||
        (m_bCanSnap != r.asGetCanSnap()) ||
        (m_bLocked != r.asGetLocked()) ||
        (m_bSnapback != r.asGetSnapback()) ||
        (!(m_PathPointer == r.asGetPathPointer())) ||
        (!(m_RotateAboutPointer == r.asGetRotateAboutPointer())) ||
        (m_RotatePoint != r.asGetRotatePoint()) ||
        (m_RotateAbout != r.asGetRotateAbout()) ||
        (m_nRotateStep != r.asGetRotateStep()) ||
        (!(m_SnapToPointer == r.asGetSnapToPointer())) ||
        (m_SnapPoint != r.asGetSnapPoint()) ||
        (m_SnapTo != r.asGetSnapTo()) ||
        (m_CanContain != r.asGetCanContain()) ||
        (!(m_ContainPointer == r.asGetContainPointer())) ||
        (m_ContainWords != r.asGetContainWords()) ||
        (m_ContainRule != r.asGetContainRule()) ||
        (m_V2Type != r.asGetV2Type()) ||
        (m_ConnectorList != r.asGetConnectorList()) ||
        //        ( !( m_Label == r.asGetLabel() ) ) ||
        (m_QuestionItem != r.asGetQuestionItem()) ||
        (m_nQuestionItemID != r.asGetQuestionItemID()) ||
        (m_QuestionTag != r.asGetQuestionTag()) ||
        (m_bAllowSnapback != r.asGetAllowSnapback()) ||
        (m_bDragACopy != r.asGetDragACopy()) ||
        (m_bRewardSound != r.asGetRewardSound()) ||
        (m_AsyncTestTag != r.asGetAsyncTestTag()) ||
        (m_bRewardSoundLocation != r.asGetRewardSoundLocation()) ||
        (m_interactMode != r.asGetInteractMode())) {
        return false;
    }
    return true;
}


bool AsRenderable::asIsTargettedForConnector() const {
    return m_bIsTargettedForConn;
}

void AsRenderable::asSetTargettedForConnector(bool targetted) {
    m_bIsTargettedForConn = targetted;
}


const QList<QPointF> AsRenderable::asGetAnchorPoints() {
    QList<QPointF> anchorPoints;
    return anchorPoints;
}


void AsRenderable::asClicked(AsUser *pUser, QPointF pos) {
    // this->asDoConnections();
    // emit asRun_Clicked( pUser, pos );
}


void AsRenderable::asPlayRewardSound(void) {
    // this->asDoConnections();
    //  emit this->asRewardSound( NULL, QPointF() );
}

// Properties...
const AsTransform &AsRenderable::asGetTransform(void) const {
    return m_Transform;
}

void AsRenderable::asSetTransform(const AsTransform &transform) {
    m_Transform = transform;
    m_bTransformedPolyDirty = true;
    m_bTransformedRectDirty = true;
}

AsTransform *AsRenderable::asGetTransformPointer(void) {
    return &m_Transform;
}

const QPointF &AsRenderable::asGetTwips(void) const {
    return m_Twips;
}

void AsRenderable::asSetTwips(const QPointF &twips) {
    m_Twips = twips;
}

const QString &AsRenderable::asGetName(void) const {
    return m_sName;
}

void AsRenderable::asSetName(const QString &sName) {
    m_sName = sName;
}

const QStringList &AsRenderable::asGetKeywords(void) const {
    return m_Keywords;
}

void AsRenderable::asSetKeywords(const QStringList &keywords) {
    QStringList oldKeywords;
    QStringList tempKeywords;

            foreach(QString keyword, keywords) {
            keyword = keyword.remove(',');
            tempKeywords.append(keyword);
        }

    if (m_Keywords != tempKeywords) {
        oldKeywords = m_Keywords;
        m_Keywords = tempKeywords;
    }

    QStringListIterator i(oldKeywords);
    while (i.hasNext()) {
        if (!m_Keywords.contains(i.next())) {
            //keyword has been removed/edited
            qDebug() << "[ AsRenderable ] - asSetKeywords: keyword removed:";// << i;
//            AsFlipchart *pFlip = AsApp::asInstance()->asGetFlipchartManager().asGetCurrentFlipchart();
//            if( pFlip != NULL )
//            {
//                pFlip->asSetKeywordDataDirty( true );
//            }
        }
    }
    QStringListIterator j(m_Keywords);
    while (j.hasNext()) {
        QString keyword = j.next();
        if (!oldKeywords.contains(keyword)) {
            //keyword has been added/edited
            qDebug() << "[ AsRenderable ] - asSetKeywords: keyword added:" << keyword;
            // AsFlipchart* pFlip = AsApp::asInstance()->asGetFlipchartManager().asGetCurrentFlipchart();
//            if( pFlip != NULL )
//            {
//                pFlip->asAddKeywordToAddOnSave( keyword );
//            }
        }
    }

}

void AsRenderable::asAppendKeywords(const QString &sKeyword) {
    m_Keywords.append(sKeyword);
}

void AsRenderable::asClearKeywords(void) {
    m_Keywords.clear();
}

bool AsRenderable::asIsVisible(void) const {
    return m_bVisible;
}

void AsRenderable::asSetVisible(bool bVisible) {
    m_bVisible = bVisible;
}

const AsRectF &AsRenderable::asGetBoundingRect(void) const {
    return m_BoundingRect;
}

void AsRenderable::asSetBoundingRect(const AsRectF &boundingRect) {
    m_BoundingRect = boundingRect;
    m_bTransformedPolyDirty = true;
    m_bTransformedRectDirty = true;
}

int AsRenderable::asGetLayer(void) const {
    return m_nLayer;
}

void AsRenderable::asSetLayer(int nLayer) {
    if (nLayer > n_kMax_Layer) {
        nLayer = n_kMax_Layer;
    }
    m_nLayer = nLayer;
}

double AsRenderable::asGetZ(void) const {
    return m_nZ;
}

void AsRenderable::asSetZ(double nZ) {
    m_nZ = nZ;
}

const AsInk &AsRenderable::asGetInk(void) const {
    return m_Ink;
}

void AsRenderable::asSetInk(const AsInk &ink) {
    m_bTransformedRectDirty = true;
    m_Ink = ink;
}

AsInk *AsRenderable::asGetInkPointer(void) {
    return &m_Ink;
}

const AsOrigin &AsRenderable::asGetScaleOrigin(void) const {
    return m_ScaleOrigin;
}

void AsRenderable::asSetScaleOrigin(const AsOrigin &origin) {
    m_ScaleOrigin = origin;
}

const AsOrigin &AsRenderable::asGetRotateOrigin(void) const {
    return m_RotateOrigin;
}

void AsRenderable::asSetRotateOrigin(const AsOrigin &origin) {
    m_RotateOrigin = origin;
}

AsRenderable::AsEnumCanMove AsRenderable::asGetCanMove(void) const {
    return m_CanMove;
}

void AsRenderable::asSetCanMove(AsRenderable::AsEnumCanMove move) {
    m_CanMove = move;
}

AsRenderable::AsEnumCanSize AsRenderable::asGetCanSize(void) const {
    return m_CanSize;
}

void AsRenderable::asSetCanSize(AsRenderable::AsEnumCanSize size) {
    m_CanSize = size;
}

AsRenderable::AsEnumCanRotate AsRenderable::asGetCanRotate(void) const {
    return m_CanRotate;
}

void AsRenderable::asSetCanRotate(AsRenderable::AsEnumCanRotate rotate) {
    m_CanRotate = rotate;
}

bool AsRenderable::asGetCanBlock(void) const {
    return m_bCanBlock;
}

void AsRenderable::asSetCanBlock(bool block) {
    m_bCanBlock = block;
}

bool AsRenderable::asGetCanSnap(void) const {
    return m_bCanSnap;
}

void AsRenderable::asSetCanSnap(bool snap) {
    m_bCanSnap = snap;
}

bool AsRenderable::asGetLocked(void) const {
    return m_bLocked;
}

void AsRenderable::asSetLocked(bool bLocked) {
    m_bLocked = bLocked;
}

bool AsRenderable::asGetSnapback(void) const {
    return m_bSnapback;
}

void AsRenderable::asSetSnapback(bool snapback) {
    m_bSnapback = snapback;
}

const AsPointer AsRenderable::asGetPathPointer(void) const {
    return m_PathPointer;
}

void AsRenderable::asSetPathPointer(AsPointer pathPointer) {
    m_PathPointer = pathPointer;
}

const AsPointer AsRenderable::asGetRotateAboutPointer(void) const {
    return m_RotateAboutPointer;
}

void AsRenderable::asSetRotateAboutPointer(AsPointer rotateAboutPointer) {
    m_RotateAboutPointer = rotateAboutPointer;
}

const QPointF &AsRenderable::asGetRotatePoint(void) const {
    return m_RotatePoint;
}

void AsRenderable::asSetRotatePoint(const QPointF &rotatePoint) {
    m_RotatePoint = rotatePoint;
}

AsRenderable::AsEnumPoint AsRenderable::asGetRotateAbout(void) const {
    return m_RotateAbout;
}

void AsRenderable::asSetRotateAbout(AsRenderable::AsEnumPoint pt) {
    m_RotateAbout = pt;
}

int AsRenderable::asGetRotateStep(void) const {
    return m_nRotateStep;
}

void AsRenderable::asSetRotateStep(int angle) {
    m_nRotateStep = angle;
}

const AsPointer AsRenderable::asGetSnapToPointer(void) const {
    return m_SnapToPointer;
}

void AsRenderable::asSetSnapToPointer(AsPointer snapToPointer) {
    m_SnapToPointer = snapToPointer;
}

const QPointF &AsRenderable::asGetSnapPoint(void) const {
    return m_SnapPoint;
}

void AsRenderable::asSetSnapPoint(const QPointF &snapPoint) {
    m_SnapPoint = snapPoint;
}

AsRenderable::AsEnumPoint AsRenderable::asGetSnapTo(void) const {
    return m_SnapTo;
}

void AsRenderable::asSetSnapTo(AsRenderable::AsEnumPoint pt) {
    m_SnapTo = pt;
}

AsRenderable::AsEnumCanContain AsRenderable::asGetCanContain(void) const {
    return m_CanContain;
}

void AsRenderable::asSetCanContain(AsRenderable::AsEnumCanContain contain) {
    m_CanContain = contain;
}

const AsPointer AsRenderable::asGetContainPointer(void) const {
    return m_ContainPointer;
}

void AsRenderable::asSetContainPointer(AsPointer containPointer) {
    m_ContainPointer = containPointer;
}

const QStringList &AsRenderable::asGetContainWords(void) const {
    return m_ContainWords;
}

void AsRenderable::asSetContainWords(const QStringList &words) {
    m_ContainWords = words;
}

AsRenderable::AsEnumContainRule AsRenderable::asGetContainRule(void) const {
    return m_ContainRule;
}

void AsRenderable::asSetContainRule(AsRenderable::AsEnumContainRule rule) {
    m_ContainRule = rule;
}

AsRenderable::AsEnumV2Type AsRenderable::asGetV2Type(void) const {
    return m_V2Type;
}

void AsRenderable::asSetV2Type(AsRenderable::AsEnumV2Type type) {
    m_V2Type = type;
}


QPointF AsRenderable::asGetRotationPoint(AsRenderable::AsEnumPoint point) {
    switch (point) {
        case AsRenderable::ASPOINT_TOPLEFT:
            return this->m_BoundingRect.asTopLeft();
            break;

        case AsRenderable::ASPOINT_TOP:
            return this->m_BoundingRect.asTopCentre();
            break;

        case AsRenderable::ASPOINT_TOPRIGHT:
            return this->m_BoundingRect.asTopRight();
            break;

        case AsRenderable::ASPOINT_LEFT:
            return this->m_BoundingRect.asLeftCentre();
            break;

        case AsRenderable::ASPOINT_CENTRE:
            return this->m_BoundingRect.center();
            break;

        case AsRenderable::ASPOINT_RIGHT:
            return this->m_BoundingRect.asRightCentre();
            break;

        case AsRenderable::ASPOINT_BOTTOMLEFT:
            return this->m_BoundingRect.asBottomLeft();
            break;

        case AsRenderable::ASPOINT_BOTTOM:
            return this->m_BoundingRect.asBottomCentre();
            break;

        case AsRenderable::ASPOINT_BOTTOMRIGHT:
            return this->m_BoundingRect.asBottomRight();
            break;

            // RHC I've had to add this as higher level code is domanding it.
        case AsRenderable::ASPOINT_SPECIFICPOINT: {
            return this->m_RotatePoint;
        }
            break;

        case AsRenderable::ASPOINT_OTHERPLACE: {
            return this->m_RotatePoint;
        }
            break;


        case AsRenderable::ASPOINT_OTHEROBJECT: {
            AsNode *pNode = m_RotateAboutPointer.asGetNode();
            if (pNode != NULL) {
                AsObject *pOtherObj = pNode->asGetAsObjectReference();
//                AsRenderable *pOtherRend = qobject_cast< AsRenderable * >( pOtherObj );
//                if ( pOtherRend != NULL )
//                {
//                    QPointF origin = pOtherRend->asGetTransformedBoundingRect().center();
//                    this->asUnTransformPoint( origin );
//                    return origin;
//                }
            }
        }
            break;

        default:
            //Do Nothing
            break;
    }

    // For all other AsEnumPoint cases this method can't help because it would depend on which AsEnumPoint,
    // i.e. snap point or rotate point.
    return QPointF();
}

QPointF AsRenderable::asGetRotationCentre(void) {
    QPointF anchor = this->asGetRotationPoint(this->asGetRotateAbout());
    this->asTransformPoint(anchor);
    return anchor;
}

QPointF AsRenderable::asGetSnapPoint(AsRenderable::AsEnumPoint point) {
    switch (point) {
        case AsRenderable::ASPOINT_TOPLEFT:
            return this->m_BoundingRect.asTopLeft();
            break;

        case AsRenderable::ASPOINT_TOP:
            return this->m_BoundingRect.asTopCentre();
            break;

        case AsRenderable::ASPOINT_TOPRIGHT:
            return this->m_BoundingRect.asTopRight();
            break;

        case AsRenderable::ASPOINT_LEFT:
            return this->m_BoundingRect.asLeftCentre();
            break;

        case AsRenderable::ASPOINT_CENTRE:
            return this->m_BoundingRect.center();
            break;

        case AsRenderable::ASPOINT_RIGHT:
            return this->m_BoundingRect.asRightCentre();
            break;

        case AsRenderable::ASPOINT_BOTTOMLEFT:
            return this->m_BoundingRect.asBottomLeft();
            break;

        case AsRenderable::ASPOINT_BOTTOM:
            return this->m_BoundingRect.asBottomCentre();
            break;

        case AsRenderable::ASPOINT_BOTTOMRIGHT:
            return this->m_BoundingRect.asBottomRight();
            break;

            // RHC I've had to add this as higher level code is domanding it.
        case AsRenderable::ASPOINT_SPECIFICPOINT: {
            return this->m_SnapPoint;
        }
            break;


        default:
            //Do Nothing
            break;
    }

    // For all other AsEnumPoint cases this method can't help because it would depend on which AsEnumPoint,
    // i.e. snap point or rotate point.
    return QPointF();
}


AsPointFArray AsRenderable::asGetPoints(void) {
    AsPointFArray points;
//    QRectF rect = this->m_BoundingRect;
//    points.append( rect.topLeft() );
//    points.append( rect.bottomLeft() );
//    points.append( rect.bottomRight() );
//    points.append( rect.topRight() );
//    points.append( rect.topLeft() );
    return points;
}

AsRectF AsRenderable::asGetTransformedBoundingRect(bool bLabel) {
//    AsRenderableGroup * pRenderableGroup = qobject_cast<AsRenderableGroup *>(this);
//
//    if (pRenderableGroup != 0)
//    {
//        m_TransformedBoundingRect = (AsRectF&) pRenderableGroup->asCompileGroupData();
//    }
//
//    if (( m_TransformedBoundingRect.isNull() ) ||
//        ( m_bTransformedRectDirty ))
//    {
//        this->asComputeTransformedBoundingRect();
//    }

    AsRectF rect = this->m_TransformedBoundingRect;

//    if ( bLabel )
//    {
//        QRectF labelRect = this->m_Label.asGetBoundingRect();
//        if ( labelRect.isValid() )
//        {
//            QPointF center = this->m_TransformedBoundingRect.center();
//            labelRect.translate( center.x(), center.y() );
//            QRectF united = this->m_TransformedBoundingRect.united( labelRect );
//            rect = AsRectF( united.left(), united.top(), united.width(), united.height() );
//        }
//    }

    return rect;
}


const AsRectF AsRenderable::asGetRectWithTouchTolerence(const AsRectF &rect) {
    qreal left = rect.left();
    qreal top = rect.top();
    qreal width = rect.width();
    qreal height = rect.height();
    if (width < MIN_TEXT_TOUCH_TOLERENCE) {
        left -= (MIN_TEXT_TOUCH_TOLERENCE - width) / 2;
    }
    if (height < MIN_TEXT_TOUCH_TOLERENCE) {
        top -= (MIN_TEXT_TOUCH_TOLERENCE - height) / 2;
    }
    const AsRectF touchRect(left, top, qMax(width, MIN_TEXT_TOUCH_TOLERENCE),
                            qMax(height, MIN_TEXT_TOUCH_TOLERENCE));
    return touchRect;
}

const QPolygonF AsRenderable::asGetTransformedBoundingPoly(const AsRectF &rect) {
//    const QMatrix combMatRef = m_Transform.asDoTransform( asGetScaleOrigin(), rect );
//    return combMatRef.map( QPolygonF( rect ) );
    return QPolygonF();
}

void AsRenderable::asComputeTransformedBoundingRect(void) {
//    const AsRectF& rect = asGetBoundingRect();
//    const QMatrix &combMatRef = m_Transform.asDoTransform( asGetScaleOrigin(), rect );
//    const QPolygonF& poly = combMatRef.map( QPolygonF(rect) );
//    m_TransformedBoundingRect = poly.boundingRect();
//    m_bTransformedRectDirty = false;
//    qDebug( "[ AsRenderable ] - Transformed bounding rect is (%f,%f %f x %f).", m_TransformedBoundingRect.left(), m_TransformedBoundingRect.top(), m_TransformedBoundingRect.width(), m_TransformedBoundingRect.height() );
}

void AsRenderable::asTransformPoint(QPointF &p) {
    AsRectF rect = this->asGetBoundingRect();
    AsOrigin orig = this->asGetScaleOrigin();

//    const QMatrix &combMatRef = this->m_Transform.asDoTransform( orig, rect );

    // transform
//    qreal m11 = combMatRef.m11();
//    qreal m12 = combMatRef.m12();
//    qreal m21 = combMatRef.m21();
//    qreal m22 = combMatRef.m22();
//
//    qreal dx = combMatRef.dx();
//    qreal dy = combMatRef.dy();
//
//    qreal px = p.x();
//    qreal py = p.y();
//
//    qreal tx = m11 * px + m21 * py + dx;
//    qreal ty = m22 * py + m12 * px + dy;
//
//    p.setX( tx );
//    p.setY( ty );
}

void AsRenderable::asUnTransformPoint(QPointF &p) {
    AsRectF rect = this->asGetBoundingRect();
    AsOrigin orig = this->asGetScaleOrigin();

    // const QMatrix &combMatRef = this->m_Transform.asDoTransform( orig, rect );

    // p = combMatRef.inverted().map( p );
}

void AsRenderable::asTranslateTo(const QPointF &pos, bool forceDirty) {
    QPointF oldPos = m_Transform.asGetTranslate();
    this->m_Transform.asSetTranslate((QPointF &) pos);

    if (forceDirty) {
        this->m_bTransformedPolyDirty = true;
        this->m_bTransformedRectDirty = true;
    } else if (!m_TransformedBoundingRect.isNull()) {
        qreal offsetX = pos.x() - oldPos.x();
        qreal offsetY = pos.y() - oldPos.y();

//    m_TransformedBoundingPoly.translate( offsetX, offsetY );
        m_TransformedBoundingRect.translate(offsetX, offsetY);
    }
    asUpdateAssociatedConnectors();
}

void AsRenderable::asTranslateBy(const QPointF &diff, bool forceDirty) {
    QPointF oldPos = m_Transform.asGetTranslate();
    QPointF pos = QPointF(oldPos.x() + diff.x(), oldPos.y() + diff.y());
    this->m_Transform.asSetTranslate((QPointF &) pos);

    if (forceDirty) {
        this->m_bTransformedPolyDirty = true;
        this->m_bTransformedRectDirty = true;
    } else if (!m_TransformedBoundingRect.isNull()) {
        qreal offsetX = pos.x() - oldPos.x();
        qreal offsetY = pos.y() - oldPos.y();

//        m_TransformedBoundingPoly.translate( offsetX, offsetY );
        m_TransformedBoundingRect.translate(offsetX, offsetY);
    }
    asUpdateAssociatedConnectors();
}

void AsRenderable::asRotateTo(const qreal angle) {
    this->m_Transform.asSetAngle(angle);
    this->m_bTransformedPolyDirty = true;
    this->m_bTransformedRectDirty = true;
}

void AsRenderable::asRotateBy(const qreal incAngle) {
    qreal angle = m_Transform.asGetAngle() + incAngle;
    this->asRotateTo(angle);
}

void AsRenderable::asScaleTo(const QPointF &scale) {
    // clamp the scale to avoid negative/zero scaling
    m_Transform.asSetScaleFactor(scale);
    this->m_bTransformedPolyDirty = true;
    this->m_bTransformedRectDirty = true;
    asUpdateAssociatedConnectors();
}

/**
 * Applies the passed scaling to the renderable.
 *
 * The scaling is composed with any existing scaling on the renderable.
 * The scaling is applied to m_Transform.
 *
 * @param factor The x and y scale factors to be applied.
 * @param maintainAspect Whether an equal scaling is desired in both directions.
 * If true, the x component of @c factor is used.  It defaults to @c false.
 *
 */
void AsRenderable::asScaleBy(const QPointF &factor, bool maintainAspect/*=false*/) {
    const QPointF oldScale = m_Transform.asGetScaleFactor();
    const QPointF scale(oldScale.x() * factor.x(),
                        (maintainAspect)
                        ? oldScale.y() * factor.x()
                        : oldScale.y() * factor.y());

    m_Transform.asSetScaleFactor(scale);
    m_bTransformedPolyDirty = true;
    m_bTransformedRectDirty = true;
    asUpdateAssociatedConnectors();
}

bool AsRenderable::asOverlaps(const QRectF &b) {
    //    If top1 + ht1 < top2 Or top1 > top2 + ht2 Or left1 + wid1 < left2 Or left1 > left2 + wid2 Then Exit Function

    QRectF a = this->asGetTransformedBoundingRect();
/*  Defect: AIns2991 Sliding puzzle resource is not working correctly, blocker bug?
    This issue seems to be caused by a rounding error causing the logic below to sometimes
    add an object to the 'already overlapping' list in the motion controller.
    Ref: bool AsMotionController::asAddStaticObject( AsNode *pNode )

    An attempt to correct the rounding error by adding 1 to one side of each condition below fixes the 'blocker not working' 
    problem but causes an object following a path to get stuck if it hits a blocker.

    // Please leave debug in (but commented) for time being  ADS 09/12/2011
    qDebug() << "";
    qDebug() << "Rect of rend " << a;
    qDebug() << "Rect to compare " << b;

    qDebug() << "a.top() + a.height() [" << (a.top() + a.height()) << "] < b.top() [" << b.top() << "]  == " << ((a.top() + a.height() < b.top()) ? "True" : "False") << " Diff = " << ((a.top() + a.height()) - b.top()) ;
    qDebug() << "a.top() [" << a.top() << "] > b.top() + b.height() [" << (b.top() + b.height()) << "] == " << ((a.top() > b.top() + b.height()) ? "True" : "False") << " Diff = " << ((b.top() + b.height()) - a.top());
    qDebug() << "a.left() + a.width() [" << (a.left() + a.width()) << "]  < b.left() [" << b.left() << "] == " << ((a.left() + a.width() < b.left()) ? "True" : "False") << " Diff = " << ((a.left() + a.width()) - b.left()) ;
    qDebug() << "a.left() [" << a.left() << "]  > b.left() + b.width() [" << (b.left() + b.width()) << "] == " << ((a.left() > b.left() + b.width()) ? "True" : "False")  << " Diff = " << ((b.left() + b.width()) - a.left());
*/

    if ((a.top() + a.height() < b.top()) ||
        (a.top() > b.top() + b.height()) ||
        (a.left() + a.width() < b.left()) ||
        (a.left() > b.left() + b.width())) {
        return false;
    }
    return true;
}

void AsRenderable::asSetDragStartPos(const QPointF &pos) {
    this->m_DragStartPos = pos;
}

QPointF &AsRenderable::asGetDragStartPos(void) {
    return this->m_DragStartPos;
}

bool AsRenderable::asContains(AsRenderable *pRend, int tolerance) {
    // Quick check to see if the transformed bounding rects overlap..
    if (!this->asOverlaps(pRend->asGetTransformedBoundingRect())) {
        return false;
    }

    // Now, can we contain the target object by the 'CanContain' param.
    if (this->m_CanContain == AsRenderable::ASCANCONTAIN_NONE) {
        return false;
    } else if (this->m_CanContain == AsRenderable::ASCANCONTAIN_SPECIFICOBJECT) {
        AsNode *pNode = this->asGetContainPointer().asGetNode();
        if (pNode == NULL) {
            return false;
        }
        AsObject *pObject = pNode->asGetAsObjectReference();
        if (pObject == NULL) {
            return false;
        }
        if (pObject->asGetID() != pRend->asGetID()) {
            return false;
        }
    } else if (this->m_CanContain == AsRenderable::ASCANCONTAIN_KEYWORDS) {
        bool bFound = false;
                foreach(QString sKeyword, this->m_ContainWords) {
                if (pRend->asGetKeywords().contains(sKeyword, Qt::CaseInsensitive)) {
                    bFound = true;
                    break;
                }
            }
        if (!bFound) {
            return false;
        }
    }

    // OK, do we contain the object in the way that the 'Contain Rule' specifies.
    if (this->m_ContainRule == AsRenderable::ASCONTAINRULE_MATCHCENTRES) {
        QPointF myCentre = this->asGetTransformedBoundingRect().center();
        QPointF theirCentre = pRend->asGetTransformedBoundingRect().center();
        //qreal dist = As2DGeom::asGetLength( myCentre, theirCentre );
//        if ( dist > tolerance )
//        {
//            return false;
//        }
    } else if (this->m_ContainRule == AsRenderable::ASCONTAINRULE_MATCHCOMPLETE) {
//        AsPointFArray points = pRend->asGetPoints();
//        foreach( QPointF point, points )
//        {
//            pRend->asTransformPoint( point );
//            const QPolygonF& poly = this->asGetTransformedBoundingPoly();
////            if( !As2DGeom::asPntInPolygon( poly, point ) )
////            {
////                return false;
////            }
//        }
    }

    return true;
}

void AsRenderable::asPrepareBoundingRect() {
}

bool AsRenderable::asGetAllowSnapback(void) const {
    return this->m_bAllowSnapback;
}

void AsRenderable::asSetAllowSnapback(bool allow) {
    this->m_bAllowSnapback = allow;
}

bool AsRenderable::asGetPlayedRewardSound(void) {
    return this->m_bPlayedRewardSound;
}

void AsRenderable::asSetPlayedRewardSound(bool b) {
    this->m_bPlayedRewardSound = b;
}

const QVariantList &AsRenderable::asGetConnectorList(void) const {
    return this->m_ConnectorList;
}

void AsRenderable::asSetConnectorList(const QVariantList &list) {
    this->m_ConnectorList = list;
}

void AsRenderable::asAddConnectorRef(quint32 id) {
    if (!this->m_ConnectorList.contains(id)) {
        this->m_ConnectorList.append(id);
    }
}

void AsRenderable::asRemoveConnectorRef(quint32 id) {
    this->m_ConnectorList.removeAll(id);
}

bool AsRenderable::asIsSelectable(void) {
    return true;
}

//const AsLabel& AsRenderable::asGetLabel( void ) const
//{
//    return this->m_Label;
//}

//void AsRenderable::asSetLabel( const AsLabel& lbl )
//{
//    this->m_Label = lbl;
//}

//AsLabel * AsRenderable::asGetLabelPointer( void )
//{
//    return &this->m_Label;
//}

bool AsRenderable::asCheckHitLabel(const QPointF &worldPos) {
    //don't return a hit if the label is empty or not currently visible
//    if ( m_Label.asGetCaption().isEmpty() || m_Label.asGetBehaviour() == AsLabel::AS_BEHAVIOUR_ROLLOVER )
//    {
//        return false;
//    }
//
//    QRectF labelRect = m_Label.asGetBoundingRect();
//    QPointF centre = this->asGetTransformedBoundingRect().center();
//    labelRect.translate( centre );
//    if ( labelRect.contains( worldPos ) )
//    {
//        return true;
//    }

    return false;
}

bool AsRenderable::asCheckBoundingBoxHit(const QPointF &worldPos) {
    return asGetTransformedBoundingRect().contains(worldPos);
}

AsRenderable::AsEnumQuestionItem AsRenderable::asGetQuestionItem(void) const {
    return this->m_QuestionItem;
}

void AsRenderable::asSetQuestionItem(AsRenderable::AsEnumQuestionItem item) {
    this->m_QuestionItem = item;
}

int AsRenderable::asGetQuestionItemID(void) const {
    return this->m_nQuestionItemID;
}

void AsRenderable::asSetQuestionItemID(int id) {
    this->m_nQuestionItemID = id;
}

AsRenderable::AsEnumQuestionTag AsRenderable::asGetQuestionTag(void) const {
    // Expression v1.0 & v1.1 question objects will have specific names for question items.
    if ((m_QuestionTag == AsRenderable::ASQUESTIONTAG_NONE) &&
        (!m_sName.isEmpty())) {
        if (m_sName == "question_text") {
            m_QuestionTag = AsRenderable::ASQUESTIONTAG_QUESTION;
        } else if (m_sName.startsWith("option_")) {
            if (m_sName.endsWith("_text")) {
                if (m_sName.contains("1"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_1;
                else if (m_sName.contains("2"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_2;
                else if (m_sName.contains("3"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_3;
                else if (m_sName.contains("4"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_4;
                else if (m_sName.contains("5"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_5;
                else if (m_sName.contains("6"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_6;
                else if (m_sName.contains("7"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_7;
                else if (m_sName.contains("8"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_8;
                else if (m_sName.contains("9"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_OPTION_9;


            } else {
                if (m_sName.contains("1"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_1;
                else if (m_sName.contains("2"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_2;
                else if (m_sName.contains("3"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_3;
                else if (m_sName.contains("4"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_4;
                else if (m_sName.contains("5"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_5;
                else if (m_sName.contains("6"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_6;
                else if (m_sName.contains("7"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_7;
                else if (m_sName.contains("8"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_8;
                else if (m_sName.contains("9"))
                    m_QuestionTag = AsRenderable::ASQUESTIONTAG_LABEL_9;
            }
        }
    }

    return this->m_QuestionTag;
}

void AsRenderable::asSetQuestionTag(AsRenderable::AsEnumQuestionTag item) {
    this->m_QuestionTag = item;
}

AsRenderable::AsEnumQuestionTag
AsRenderable::asGetQuestionTagEnumValueFromIndex(int index, AsEnumQuestionItem tagType) {
    //this nasty little function exists because we perform arithmetic on the AsEnumQuestionTag values
    //we need to add values to the enum for 9-scale likerts, but we can't add them in the logical place
    //because the enum is streamed to disk.

    AsEnumQuestionTag nValue = ASQUESTIONTAG_NONE;

    if (tagType == ASQUESTIONITEM_OPTION) {
        if (index == 1) {
            nValue = ASQUESTIONTAG_OPTION_1;
        } else if (index == 2) {
            nValue = ASQUESTIONTAG_OPTION_2;
        } else if (index == 3) {
            nValue = ASQUESTIONTAG_OPTION_3;
        } else if (index == 4) {
            nValue = ASQUESTIONTAG_OPTION_4;
        } else if (index == 5) {
            nValue = ASQUESTIONTAG_OPTION_5;
        } else if (index == 6) {
            nValue = ASQUESTIONTAG_OPTION_6;
        } else if (index == 7) {
            nValue = ASQUESTIONTAG_OPTION_7;
        } else if (index == 8) {
            nValue = ASQUESTIONTAG_OPTION_8;
        } else if (index == 9) {
            nValue = ASQUESTIONTAG_OPTION_9;
        }
    } else if (tagType == ASQUESTIONITEM_LABEL) {
        if (index == 1) {
            nValue = ASQUESTIONTAG_LABEL_1;
        } else if (index == 2) {
            nValue = ASQUESTIONTAG_LABEL_2;
        } else if (index == 3) {
            nValue = ASQUESTIONTAG_LABEL_3;
        } else if (index == 4) {
            nValue = ASQUESTIONTAG_LABEL_4;
        } else if (index == 5) {
            nValue = ASQUESTIONTAG_LABEL_5;
        } else if (index == 6) {
            nValue = ASQUESTIONTAG_LABEL_6;
        } else if (index == 7) {
            nValue = ASQUESTIONTAG_LABEL_7;
        } else if (index == 8) {
            nValue = ASQUESTIONTAG_LABEL_8;
        } else if (index == 9) {
            nValue = ASQUESTIONTAG_LABEL_9;
        }
    } else if (tagType == ASQUESTIONITEM_QUESTION) {
        nValue = ASQUESTIONTAG_QUESTION;
    }

    return nValue;
}

int AsRenderable::asGetIndexFromQuestionTagEnum(AsEnumQuestionTag tag) {
    //this nasty little function exists because we perform arithmetic on the AsEnumQuestionTag values
    //we need to add values to the enum for 9-scale likerts, but we can't add them in the logical place
    //because the enum is streamed to disk.

    int nIndex = -1;

    if (tag == ASQUESTIONTAG_OPTION_1) {
        nIndex = 1;
    } else if (tag == ASQUESTIONTAG_OPTION_2) {
        nIndex = 2;
    } else if (tag == ASQUESTIONTAG_OPTION_3) {
        nIndex = 3;
    } else if (tag == ASQUESTIONTAG_OPTION_4) {
        nIndex = 4;
    } else if (tag == ASQUESTIONTAG_OPTION_5) {
        nIndex = 5;
    } else if (tag == ASQUESTIONTAG_OPTION_6) {
        nIndex = 6;
    } else if (tag == ASQUESTIONTAG_OPTION_7) {
        nIndex = 7;
    } else if (tag == ASQUESTIONTAG_OPTION_8) {
        nIndex = 8;
    } else if (tag == ASQUESTIONTAG_OPTION_9) {
        nIndex = 9;
    } else if (tag == ASQUESTIONTAG_LABEL_1) {
        nIndex = 1;
    } else if (tag == ASQUESTIONTAG_LABEL_2) {
        nIndex = 2;
    } else if (tag == ASQUESTIONTAG_LABEL_3) {
        nIndex = 3;
    } else if (tag == ASQUESTIONTAG_LABEL_4) {
        nIndex = 4;
    } else if (tag == ASQUESTIONTAG_LABEL_5) {
        nIndex = 5;
    } else if (tag == ASQUESTIONTAG_LABEL_6) {
        nIndex = 6;
    } else if (tag == ASQUESTIONTAG_LABEL_7) {
        nIndex = 7;
    } else if (tag == ASQUESTIONTAG_LABEL_8) {
        nIndex = 8;
    } else if (tag == ASQUESTIONTAG_LABEL_9) {
        nIndex = 9;
    } else if (tag == ASQUESTIONTAG_QUESTION) {
        nIndex = 1;
    }

    return nIndex;
}

AsRenderable::AsEnumAsyncTestTag AsRenderable::asGetAsyncTestTag(void) const {
    if ((m_AsyncTestTag == AsRenderable::ASASYNCTESTTAG_NONE) && (!m_sName.isEmpty())) {
        if (m_sName == "asynctest_title") {
            m_AsyncTestTag = AsRenderable::ASASYNCTESTTAG_TITLE;
        } else if (m_sName == "asynctest_description") {
            m_AsyncTestTag = AsRenderable::ASASYNCTESTTAG_DESCRIPTION;
        }
    }

    return this->m_AsyncTestTag;
}

void AsRenderable::asSetAsyncTestTag(AsRenderable::AsEnumAsyncTestTag item) {
    this->m_AsyncTestTag = item;
}

void AsRenderable::asListGroupMembers(QList<AsRenderable *> &list, AsNode *pNode) {
    asBuildGroupMembersList(list, pNode);
}

void AsRenderable::asBuildGroupMembersList(QList<AsRenderable *> &list, AsNode *pNode) {
//    AsRenderable* pRenderable = qobject_cast<AsRenderable*>( pNode->asGetAsObjectReference() );
//    if ( pRenderable )
//    {
//        if ( pRenderable->asGetType() == AsObject::AS_OBJECT_ASRENDERABLEGROUP )
//        {
////            const QList< AsNode* > softKids = pNode->asGetSoftChildren();
////            int sz = softKids.size();
////            for( int i=0; i<sz; ++i )
////            {
////                AsNode *pK = softKids[ i ];
////                if( pK != NULL )
////                {
////                    asBuildGroupMembersList( list, pK );
////                }
////            }
//        }
//        else
//        {
//             list.append( pRenderable );
//        }
//    }
}

void AsRenderable::asSetTranslucency(int translucency) {
    m_nTranslucency = translucency;
}

int AsRenderable::asGetTranslucency() const {
    return m_nTranslucency;
}

int AsRenderable::asGetTranslucency() {
    return m_nTranslucency;
}

void AsRenderable::asSetTopLeft(QPointF pointTopLeft) {
    QPointF pointTopLeftOld(m_TransformedBoundingRect.left(), m_TransformedBoundingRect.top());

    double dX = pointTopLeft.rx() - pointTopLeftOld.rx();
    double dY = pointTopLeft.ry() - pointTopLeftOld.ry();

    QPointF pointTranslate = m_Transform.asGetTranslate();

    double dNewX = pointTranslate.rx() + dX;
    double dNewY = pointTranslate.ry() + dY;

    pointTranslate.setX(dNewX);
    pointTranslate.setY(dNewY);

    asTranslateTo(pointTranslate);
}

const QPointF AsRenderable::asGetTopLeft() const {
    QPointF pointTopLeft(m_TransformedBoundingRect.left(), m_TransformedBoundingRect.top());

    return pointTopLeft;
}

void AsRenderable::asSetWidth(double dWidth) {
    if (dWidth == 0.0f) {
        return;
    }

    double dOldWidth = m_TransformedBoundingRect.width();
    if (dOldWidth == 0.0f) {
        return;
    }

    double dScaleFactorX = dWidth / dOldWidth;

    QPointF pointScale(dScaleFactorX, 1.0);
    asScaleBy(pointScale);
}

double AsRenderable::asGetWidth() {
    return m_TransformedBoundingRect.width();
}

void AsRenderable::asSetHeight(double dHeight) {
    if (dHeight == 0.0f) {
        return;
    }

    double dOldHeight = m_TransformedBoundingRect.height();
    if (dOldHeight == 0.0f) {
        return;
    }

    double dScaleFactorY = dHeight / dOldHeight;

    QPointF pointScale(1.0, dScaleFactorY);
    asScaleBy(pointScale);
}

double AsRenderable::asGetHeight() {
    return m_TransformedBoundingRect.height();
}

bool AsRenderable::asGetDragACopy(void) const {
    return m_bDragACopy;
}

void AsRenderable::asSetDragACopy(bool b) {
    m_bDragACopy = b;
}

bool AsRenderable::asGetRewardSound() const {
    return m_bRewardSound;
}

void AsRenderable::asSetRewardSound(bool bRewardSound) {
    m_bRewardSound = bRewardSound;
}

QString AsRenderable::asGetRewardSoundLocation() const {
    return m_bRewardSoundLocation;
}

void AsRenderable::asSetRewardSoundLocation(const QString &bRewardSoundLocation) {
    m_bRewardSoundLocation = bRewardSoundLocation;
}

QString AsRenderable::asGetNewObjectName(quint32) {
    QString strEmpty;

    return strEmpty;
}

bool AsRenderable::asEnter(void) {
    return false;
    //  return m_Label.asTooltip( true );
}

bool AsRenderable::asLeave(void) {
    return false;
}

qreal AsRenderable::asGetRotateStepPortion(void) const {
    return m_rotateStepPortion;
}

void AsRenderable::asSetRotateStepPortion(qreal angle) {
    m_rotateStepPortion = angle;
}

//bool AsRenderable::asAllowsInteraction(AsInputMethod method) const
//{
////    if (method == ASINPUTMETHOD_POINTER)
////    {
////        return m_interactMode == ASINTERACTMODE_ANY || m_interactMode == ASINTERACTMODE_ACTIVPEN;
////    }
////    else if (method == ASINPUTMETHOD_TOUCH)
////    {
////        return m_interactMode == ASINTERACTMODE_ANY || m_interactMode == ASINTERACTMODE_TOUCH;
////    }
////    else
////    {
////        return m_interactMode == ASINTERACTMODE_ANY;
////    }
//}

AsRenderable::AsEnumInteractMode AsRenderable::asGetInteractMode(void) const {
    return m_interactMode;
}

void AsRenderable::asSetInteractMode(AsRenderable::AsEnumInteractMode mode) {
    m_interactMode = mode;
}

void AsRenderable::asSetDefaultInteractMode(AsRenderable::AsEnumInteractMode mode) {
    m_defaultInteractMode = mode;
}

void AsRenderable::asUpdateAssociatedConnectors() {
    QVariantList connectors = asGetConnectorList();
    if (connectors.count() != 0) {
                foreach(const QVariant &conVar, connectors) {
                quint32 id = conVar.toUInt();
            }
    }
}

Json::Value &AsRenderable::serialized() {
    Json::Value &jsonObject = AsObject::serialized();
    Json::Value softParentArry(Json::arrayValue);
    Json::Value ink;
    AsNode *node = asGetIndexNode();
    if (node) {
        for (AsNode *parent:node->asGetSoftParents()) {
            AsObject *object = parent->asGetAsObjectReference();
            softParentArry.append((int) object->asGetID());
        }

    }
    jsonObject["softParentIds"] = softParentArry;
    //Ink Serialization
    Variant varInk = property(getPropertyIdByName("ink"));
    if (varInk.value && varInk.type == VariableType::ASINK) {
        AsInk *asInk = static_cast<AsInk *>(varInk.value);
        Variant var;
        //Stroke
        var = asInk->property(AsInk::AS_PROPERTY_PENCAPSTYLE);
        if (var.type == VariableType::INT && var.value) {
            ink["strokePenCapStyle"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_PENJOINSTYLE);
        if (var.type == VariableType::INT && var.value) {
            ink["strokeJoinStyle"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_PENWIDTH);
        if (var.type == VariableType::UINT && var.value) {
            ink["strokePenWidth"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_PENSTYLE);
        if (var.type == VariableType::INT && var.value) {
            ink["strokeStyle"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_PENCOLOR);
        if (var.type == VariableType::Q_COLOR && var.value) {
            Json::Value color;
            color << var;
            ink["strokePenColor"] = color;
        }
        //Fill
        var = asInk->property(AsInk::AS_PROPERTY_BACKGROUNDMODE);
        if (var.type == VariableType::INT && var.value) {
            ink["backgroundMode"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_BACKGROUNDCOLOR);
        if (var.type == VariableType::Q_COLOR && var.value) {
            Json::Value color;
            color << var;
            ink["backgroundColor"] = color;
        }
        var = asInk->property(AsInk::AS_PROPERTY_BRUSHCOLOR);
        if (var.type == VariableType::Q_COLOR && var.value) {
            Json::Value color;
            color << var;
            ink["brushColor"] = color;
        }
        var = asInk->property(AsInk::AS_PROPERTY_BRUSHCOLOR2);
        if (var.type == VariableType::Q_COLOR && var.value) {
            Json::Value color;
            color << var;
            ink["brushColor2"] = color;
        }
        var = asInk->property(AsInk::AS_PROPERTY_BRUSHGRADIENTTYPE);
        if (var.type == VariableType::INT && var.value) {
            ink["brushGradientType"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_BRUSHSTYLE);
        if (var.type == VariableType::INT && var.value) {
            ink["brushStyle"] = *static_cast<int *>(var.value);
        }
        var = asInk->property(AsInk::AS_PROPERTY_INKTYPE);
        if (var.type == VariableType::INT && var.value) {
            ink["inkType"] = *static_cast<int *>(var.value);
        }
        jsonObject["ink"] = ink;
    }
    return jsonObject;
}





