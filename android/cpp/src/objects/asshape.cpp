// Implements the AsShape class.
// $Author: Paul Wareing.

#include "asshape.h"

#include "../util/asutil.h"
#include "../resources/asresourcemanager.h"
#include "../asfactory.h"
#include "asflipchart.h"


namespace {
    const qreal MIN_ANNOTATION_TOUCH_TOLERENCE = 15.0;
};

AsShape::AsShape(AsFactory *pAsFactory) :
        AsRenderable(pAsFactory),
        m_nResource(0),
        m_pAsShapeRes(0),
        m_nFillMode(AsShape::AS_FILLMODE_NONE),
        m_bPainterPathDirty(true),
        m_cachedLastHitWasOnEdge(false),
        m_bIntelligent(false),
        m_bIsOpen(false),
        m_endAIndex(-1),
        m_endBIndex(-1),
        m_shapeType(AS_SHAPE_TYPE_DUMB),
        m_numPoints(0),
        m_innerDiam(0),
        m_bIsStar(0),
        m_shapeUniformity(AS_SHAPE_CREATION_NONE),
        m_bIsConnector(false),
        m_bIsTargettedForConn(false),
        m_nEndCapA(AS_ENDCAP_NONE),
        m_nEndCapB(AS_ENDCAP_NONE),
        m_bDrawing(false),
        m_bCheckInitialPosIsAnchorPoint(true) {
    // Set the type property.
    asSetType(AsObject::AS_OBJECT_SHAPE);
}

AsShape::AsShape(const AsShape &shape) : AsRenderable(shape) {
    m_bIntelligent = false;
    m_bIsOpen = false;
    m_bIsConnector = false;
    m_bIsTargettedForConn = false;
    this->asCopy(shape);
}

void AsShape::asBuildIntelligentShape(const AsShape::AsIntelligentShapeParms &parms) {

}

/**
 * Applies the passed scaling to the shape.
 *
 * The scaling is composed with any existing scaling on the shape. The shape
 * resource is rebuilt with the new dimensions.
 *
 * @param factor The x and y scale factors to be applied. The x scaling factor
 * is ignored for horizontal lines, and the y scaling factor is ignored for
 * vertical lines.
 * @param maintainAspect Whether an equal scaling is desired in both directions.
 * If true, the x component of @c factor is used.  It defaults to @c false and
 * is ignored in the cases of horizontal and vertical lines.
 *
 */






AsShape::~AsShape() {

}

void AsShape::operator=(const AsShape &shape) {
    AsRenderable::operator=(shape);
    this->asCopy(shape);
}

bool AsShape::operator==(const AsShape &shape) {
    if (!AsRenderable::operator==(shape)) {
        return false;
    }

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CHECK THIS LAST!!!!
    if (!(m_endA == shape.asGetEndA()) ||
        !(m_endB == shape.asGetEndB()) ||
        m_endAPos != shape.asGetEndAPos() ||
        m_endBPos != shape.asGetEndBPos() ||
        m_endAIndex != shape.asGetEndAIndex() ||
        m_endBIndex != shape.asGetEndBIndex() ||
        m_endAShapeCenterDiff != shape.asGetEndAShapeCenterDiff() ||
        m_endBShapeCenterDiff != shape.asGetEndBShapeCenterDiff() ||
        m_nResource != shape.asGetResource() ||
        m_nFillMode != shape.asGetFillMode() ||
        m_bIsOpen != shape.asIsOpen() ||
        m_bIntelligent != shape.asIsIntelligent() ||
        m_shapeType != shape.asGetShapeType() ||
        m_numPoints != shape.asGetNumPoints() ||
        m_innerDiam != shape.asGetInnerDiam() ||
        m_bIsStar != shape.asGetIsStar() ||
        m_bIsConnector != shape.asIsConnector() ||
        m_nEndCapA != shape.asGetEndCapA() ||
        m_nEndCapB != shape.asGetEndCapB()) {
        return false;
    }
    return true;
}

void AsShape::asCopy(const AsShape &shape) {
    this->m_nResource = shape.asGetResource();
    this->m_nFillMode = shape.asGetFillMode();

    m_bIsOpen = shape.asIsOpen();
    m_bIntelligent = shape.asIsIntelligent();
    m_shapeType = shape.asGetShapeType();
    m_numPoints = shape.asGetNumPoints();
    m_innerDiam = shape.asGetInnerDiam();
    m_bIsStar = shape.asGetIsStar();

    m_endA = shape.asGetEndA();
    m_endB = shape.asGetEndB();
    m_endAPos = shape.asGetEndAPos();
    m_endBPos = shape.asGetEndBPos();
    m_endAIndex = shape.asGetEndAIndex();
    m_endBIndex = shape.asGetEndBIndex();
    m_endAShapeCenterDiff = shape.asGetEndAShapeCenterDiff();
    m_endBShapeCenterDiff = shape.asGetEndBShapeCenterDiff();
    m_bIsConnector = shape.asIsConnector();

    m_nEndCapA = shape.asGetEndCapA();
    m_nEndCapB = shape.asGetEndCapB();


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CHECK FULLNES!!!!!

    this->m_pAsShapeRes = 0;
    this->m_bPainterPathDirty = true;
}


const AsPointer &AsShape::asGetEndA(void) const {
    return m_endA;
}

void AsShape::asSetEndA(AsPointer &endA) {
    m_endA = endA;
}


const AsPointer &AsShape::asGetEndB(void) const {
    return m_endB;
}

void AsShape::asSetEndB(AsPointer &endB) {
    m_endB = endB;
}

const QPointF &AsShape::asGetEndAPos(void) const {
    return m_endAPos;
}

void AsShape::asSetEndAPos(const QPointF &pos) {
    m_endAPos = pos;
}

const QPointF &AsShape::asGetEndBPos(void) const {
    return m_endBPos;
}

void AsShape::asSetEndBPos(const QPointF &pos) {
    m_endBPos = pos;
}

void AsShape::asSetEndAIndex(int index) {
    m_endAIndex = index;
}

int AsShape::asGetEndAIndex(void) const {
    return m_endAIndex;
}

void AsShape::asSetEndBIndex(int index) {
    m_endBIndex = index;
}

int AsShape::asGetEndBIndex(void) const {
    return m_endBIndex;
}

void AsShape::asSetEndAShapeCenterDiff(QPointF diff) {
    m_endAShapeCenterDiff = diff;
}

const QPointF &AsShape::asGetEndAShapeCenterDiff(void) const {
    return m_endAShapeCenterDiff;
}

void AsShape::asSetEndBShapeCenterDiff(QPointF diff) {
    m_endBShapeCenterDiff = diff;
}

const QPointF &AsShape::asGetEndBShapeCenterDiff(void) const {
    return m_endBShapeCenterDiff;
}

bool AsShape::asIsIntelligent() const {
    return m_bIntelligent;
}

void AsShape::asSetIsIntelligent(bool intelligent) {
    m_bIntelligent = intelligent;
}

bool AsShape::asIsOpen() const {
    return m_bIsOpen;
}

void AsShape::asSetIsOpen(bool bOpen) {
    m_bIsOpen = bOpen;
}

const AsInstructListList &AsShape::asGetInstructs() const {
    return m_instructLists;
}

void AsShape::asSetInstructs(const AsInstructListList &instructs) {
    m_instructLists = instructs;
}


AsShape::AsEnumShapeType AsShape::asGetShapeType() const {
    return m_shapeType;
}

void AsShape::asSetShapeType(const AsEnumShapeType type) {
    m_shapeType = type;
}

int AsShape::asGetNumPoints() const {
    return m_numPoints;
}

void AsShape::asSetNumPoints(const int numPoints) {
    m_numPoints = numPoints;
}

double AsShape::asGetInnerDiam() const {
    return m_innerDiam;
}

void AsShape::asSetInnerDiam(const double diam) {
    m_innerDiam = diam;
}

bool AsShape::asGetIsStar() const {
    return m_bIsStar;
}

void AsShape::asSetIsStar(const bool star) {
    m_bIsStar = star;
}

bool AsShape::asIsConnector() const {
    return m_bIsConnector;
}

void AsShape::asSetIsConnector(const bool isConn) {
    m_bIsConnector = isConn;
}


QHash<QString, quint16> &AsShape::m_lProperties(void) {
    static QHash<QString, quint16> HashProperties;

    if (HashProperties.isEmpty()) {
        // From AsObject...
        // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsShape::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert("transform", (quint16) AsShape::AS_PROPERTY_TRANSFORM);
        //  HashProperties.insert( "asTwips", ( quint16 )AsShape::AS_PROPERTY_TWIPS );
        HashProperties.insert("name", (quint16) AsShape::AS_PROPERTY_NAME);
        //  HashProperties.insert( "asKeywords", ( quint16 )AsShape::AS_PROPERTY_KEYWORDS );
        //  HashProperties.insert( "asVisible", ( quint16 )AsShape::AS_PROPERTY_VISIBLE );
        HashProperties.insert("boundingRect", (quint16) AsShape::AS_PROPERTY_BOUNDINGRECT);
        HashProperties.insert("layer", (quint16) AsShape::AS_PROPERTY_LAYER);
        HashProperties.insert("zOrder", (quint16) AsShape::AS_PROPERTY_Z);
        HashProperties.insert("ink", (quint16) AsShape::AS_PROPERTY_INK);
        HashProperties.insert("scaleOrigin", (quint16) AsShape::AS_PROPERTY_SCALEORIGIN);
        HashProperties.insert("rotateOrigin", (quint16) AsShape::AS_PROPERTY_ROTATEORIGIN);
        HashProperties.insert("moveType", (quint16) AsShape::AS_PROPERTY_CANMOVE);
//        HashProperties.insert( "asCanSize", ( quint16 )AsShape::AS_PROPERTY_CANSIZE );
//        HashProperties.insert( "asCanRotate", ( quint16 )AsShape::AS_PROPERTY_CANROTATE );
//        HashProperties.insert( "asCanBlock", ( quint16 )AsShape::AS_PROPERTY_CANBLOCK );
//        HashProperties.insert( "asCanSnap", ( quint16 )AsShape::AS_PROPERTY_CANSNAP );
        HashProperties.insert("locked", (quint16) AsShape::AS_PROPERTY_LOCKED);
//        HashProperties.insert( "asSnapback", ( quint16 )AsShape::AS_PROPERTY_SNAPBACK );
//        HashProperties.insert( "asPathPointer", ( quint16 )AsShape::AS_PROPERTY_PATHPOINTER );
//        HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsShape::AS_PROPERTY_ROTATEABOUTPOINTER );
//        HashProperties.insert( "asRotatePoint", ( quint16 )AsShape::AS_PROPERTY_ROTATEPOINT );
//        HashProperties.insert( "asRotateAbout", ( quint16 )AsShape::AS_PROPERTY_ROTATEABOUT );
//        HashProperties.insert( "asRotateStep", ( quint16 )AsShape::AS_PROPERTY_ROTATESTEP );
//        HashProperties.insert( "asSnapToPointer", ( quint16 )AsShape::AS_PROPERTY_SNAPTOPOINTER );
//        HashProperties.insert( "asSnapPoint", ( quint16 )AsShape::AS_PROPERTY_SNAPPOINT );
//        HashProperties.insert( "asSnapTo", ( quint16 )AsShape::AS_PROPERTY_SNAPTO );
//        HashProperties.insert( "asCanContain", ( quint16 )AsShape::AS_PROPERTY_CANCONTAIN );
//        HashProperties.insert( "asContainPointer", ( quint16 )AsShape::AS_PROPERTY_CONTAINPOINTER );
//        HashProperties.insert( "asContainWords", ( quint16 )AsShape::AS_PROPERTY_CONTAINWORDS );
//        HashProperties.insert( "asContainRule", ( quint16 )AsShape::AS_PROPERTY_CONTAINRULE );
        HashProperties.insert("v2Type", (quint16) AsShape::AS_PROPERTY_V2TYPE);
//       HashProperties.insert( "connectorList", ( quint16 )AsShape::AS_PROPERTY_CONNECTORLIST );
//        HashProperties.insert( "asLabel", ( quint16 )AsShape::AS_PROPERTY_LABEL );
//        HashProperties.insert( "asQuestionItem", ( quint16 )AsShape::AS_PROPERTY_QUESTIONITEM );
//        HashProperties.insert( "asQuestionItemID", ( quint16 )AsShape::AS_PROPERTY_QUESTIONITEMID );
//        HashProperties.insert( "asQuestionTag", ( quint16 )AsShape::AS_PROPERTY_QUESTIONTAG );
//        HashProperties.insert( "asAllowSnapback", ( quint16 )AsShape::AS_PROPERTY_ALLOWSNAPBACK );
//        HashProperties.insert( "asDragACopy", ( quint16 )AsShape::AS_PROPERTY_DRAGACOPY );
//        HashProperties.insert( "asRewardSound", ( quint16 )AsShape::AS_PROPERTY_REWARD_SOUND );
//        HashProperties.insert( "asRewardSoundLocation", ( quint16 )AsShape::AS_PROPERTY_REWARD_SOUND_LOCATION );
//        HashProperties.insert( "asAsyncTestTag", ( quint16 )AsShape::AS_PROPERTY_ASYNCTESTTAG );

        // From AsShape...
        HashProperties.insert("resource", (quint16) AsShape::AS_PROPERTY_RESOURCE);
        HashProperties.insert("fillMode", (quint16) AsShape::AS_PROPERTY_FILLMODE);

        //Added for intelligent shape functionality....
        HashProperties.insert("intelligent", (quint16) AsShape::AS_PROPERTY_INTELLIGENT);
        HashProperties.insert("isOpen", (quint16) AsShape::AS_PROPERTY_OPEN);
        HashProperties.insert("numShapePoints", (quint16) AsShape::AS_PROPERTY_NUM_POINTS);
        HashProperties.insert("isStar", (quint16) AsShape::AS_PROPERTY_IS_STAR);
        HashProperties.insert("shapeType", (quint16) AsShape::AS_PROPERTY_SHAPE_TYPE);
        HashProperties.insert("localPoints", (quint16) AsShape::AS_PROPERTY_LOCAL_POINTS);

        HashProperties.insert("innerDiam", (quint16) AsShape::AS_PROPERTY_INNER_DIAM);
        // HashProperties.insert( "shapeInstructs", ( quint16 )AsShape::AS_PROPERTY_SHAPE_INSTRUCTS);

        HashProperties.insert("endA", (quint16) AsShape::AS_PROPERTY_ENDA);
        HashProperties.insert("endB", (quint16) AsShape::AS_PROPERTY_ENDB);

        HashProperties.insert("endCapA", (quint16) AsShape::AS_PROPERTY_IS_ENDCAPA);
        HashProperties.insert("endCapB", (quint16) AsShape::AS_PROPERTY_IS_ENDCAPB);

        HashProperties.insert("endAPos", (quint16) AsShape::AS_PROPERTY_ENDA_POS);
        HashProperties.insert("endBPos", (quint16) AsShape::AS_PROPERTY_ENDB_POS);

        HashProperties.insert("endAIndex", (quint16) AsShape::AS_PROPERTY_ENDA_INDEX);
        HashProperties.insert("endBIndex", (quint16) AsShape::AS_PROPERTY_ENDB_INDEX);

        HashProperties.insert("endAShapeCenterDiff",
                              (quint16) AsShape::AS_PROPERTY_ENDA_SHAPE_CENTER_DIFF);
        HashProperties.insert("endBShapeCenterDiff",
                              (quint16) AsShape::AS_PROPERTY_ENDB_SHAPE_CENTER_DIFF);

        HashProperties.insert("isConnector", (quint16) AsShape::AS_PROPERTY_IS_CONNECTOR);
        // HashProperties.insert( "asInteractMode", ( quint16 )AsShape::AS_PROPERTY_INTERACTMODE );
    }
    return HashProperties;
}

void AsShape::asResetPropertyIndex(void) {
    AsObject::asSetPropertyIterator(&m_lProperties);
}


bool AsShape::asCheckHit(const QPointF &worldPos) {

    return false;
}


const AsPointFArrayArray &AsShape::asGetShapePoints(void) {
    AsShapeRes *pShapeRes = (AsShapeRes *) this->asGetResourcePointer();
    return pShapeRes->asGetShapes();
}


void AsShape::asSetResource(unsigned int nResource) {
    m_nResource = nResource;
}

AsResource *AsShape::asGetResourcePointer(void) {
    if (m_pAsShapeRes == Q_NULLPTR) {
        m_pAsShapeRes = dynamic_cast<AsShapeRes *>(m_pAsFactory->getResourceManager()->asLoadResource(
                AsObject::AS_OBJECT_SHAPERES, asGetResource()));
        if (m_pAsShapeRes != Q_NULLPTR) {

        }
    }
    return m_pAsShapeRes;
}

bool AsShape::asHasResourcePointer() const {
    if (m_pAsShapeRes) {
        return true;
    }

    return false;
}

void AsShape::asSetResource(AsResource *pResource) {

}

AsShape::AsEnumFillMode AsShape::asGetFillMode(void) const {
    return m_nFillMode;
}

void AsShape::asSetFillMode(AsShape::AsEnumFillMode fillMode) {
    m_nFillMode = fillMode;
}

void AsShape::asShapeResChanged(AsShapeRes *pShapeRes) {
    if (m_pAsShapeRes == pShapeRes) {
        m_bPainterPathDirty = true;
    }
}

AsInk::AsEnumPenJoinStyle AsShape::asGetEndCapJoinStyle() {
    if (this->asGetInk().asGetPenCapStyle() == AsInk::AS_PENCAPSTYLE_SQUARE)
        return (AsInk::AS_PENJOINSTYLE_BEVEL);
    else if (this->asGetInk().asGetPenCapStyle() == AsInk::AS_PENCAPSTYLE_FLAT)
        return (AsInk::AS_PENJOINSTYLE_MITER);

    // default join style will be round
    return (AsInk::AS_PENJOINSTYLE_ROUND);
}


void AsShape::asDeletePainterPaths() {

}

void AsShape::asBuildPainterPaths(void) {

}


void AsShape::asPrepareBoundingRect() {
    // call asGet...PainterPathConstRef() to ensure that the bounding rect is calculated if necessary

}

bool AsShape::asCachedGetLastHitWasOnEdge() const {
    return this->m_cachedLastHitWasOnEdge;
}


void AsShape::asShapePointEditMove(QPointF delta, int index, bool bRedraw) {

}

void AsShape::asShapePointEditMove(QPointF delta, int index) {
    asShapePointEditMove(delta, index, true);
}


void AsShape::asConvertToDumbShape() {


}


void AsShape::asShapeEditComplete() {
    m_bPainterPathDirty = true;
    asPrepareBoundingRect();
}


bool AsShape::asHaveControls() const {

    return false;
}


void AsShape::asStartChainShape() {

}


AsShape::AsEnumShapeCreationMethod AsShape::asGetCreationMethod() const {
    return m_shapeUniformity;
}


void AsShape::asSetCurrentPointerPos(QPointF t, bool noSnap) {


}

bool
AsShape::asHasMovementDirectionChanged(QPointF curPoint, QPointF prevPoint, QPointF controlPoint,
                                       int tolerance) {
    QPointF controlVec = prevPoint - controlPoint;
    double maxDist = qMax(qAbs(controlVec.x()), qAbs(controlVec.y()));
    controlVec.setX(controlVec.x() / maxDist);
    controlVec.setY(controlVec.y() / maxDist);

    double xLength = qAbs(curPoint.x() - prevPoint.x());
    double yLength = qAbs(curPoint.y() - prevPoint.y());

    double mult = qMax(xLength, yLength);

    QPointF vecTarget((controlVec * mult) + prevPoint);

    QPoint diff = (curPoint - vecTarget).toPoint();
    return (qAbs(diff.x()) > tolerance || qAbs(diff.y()) > tolerance);
}


bool AsShape::asClickAt(QPointF t) {

    return true;
}

void AsShape::asAddChainPoint(QPointF thePoint) {

}

void AsShape::asCreationComplete(QPointF t) {

}


QChar AsShape::asGetNextInstruct(QString &str) {
    while (str.length()) {
        if (!str.at(0).isLetter()) {
            str.remove(0, 1);
        } else {
            QChar instruct = str.at(0);
            str.remove(0, 1);
            return instruct;
        }
    };
    return QChar();
}

QString AsShape::asGetInstructStr(QString &str) {
    QString numStr;

    while (str.length()) {
        if (!str.at(0).isLetter()) {
            QChar instruct = str.at(0);
            numStr += QString(instruct);
            str.remove(0, 1);
        } else
            break;
    };
    return numStr;
}

void AsShape::asCreatePathElems(int numPoints, double innerDiam, bool isStar) {

}


AsShape::AsEnumEndCap AsShape::asGetEndCapA(void) const {
    return m_nEndCapA;
}

void AsShape::asSetEndCapA(AsShape::AsEnumEndCap nEndCap) {
    // check for end caps only if it is a line
    if (asIsOpen() && m_nEndCapA != nEndCap) {
        m_nEndCapA = nEndCap;
        m_bPainterPathDirty = true;
    }
}

AsShape::AsEnumEndCap AsShape::asGetEndCapB(void) const {
    return m_nEndCapB;
}

void AsShape::asSetEndCapB(AsShape::AsEnumEndCap nEndCap) {
    // check for end caps only if it is a line
    if (asIsOpen() && m_nEndCapB != nEndCap) {
        m_nEndCapB = nEndCap;
        m_bPainterPathDirty = true;
    }
}

void AsShape::asSetDrawing(bool bDrawing) {
    m_bDrawing = bDrawing;
}


/**
 * Determines whether the shape is a line or not.
 */
bool AsShape::asIsLine() const {
    return false;
}

/**
 * Determines whether the shape is a vertical line or not.
 */
bool AsShape::asIsVerticalLine() const {
    return false;
}

/**
 * Determines whether the shape is a horizontal line or not.
 */
bool AsShape::asIsHorizontalLine() const {
    return false;
}

bool AsShape::asSetInitialIndexOrDiff(QPointF &pos, AsRenderable *pRenderable, bool bEndA) {
    bool b_MatchFound = false;

    return b_MatchFound;
}


void AsShape::asConvertCenterFractionToDiff(QPointF &diff, AsRenderable *pRenderable) {

}

QString AsShape::getPropertyNameById(int nID) {
    return m_lProperties().key(nID);
}

int AsShape::getPropertyIdByName(QString name) const {
    return m_lProperties().value(name);
}

const Json::Value &AsShape::asResourceSerialized() {
    asGetResourcePointer();
    Variant variant = property(AsShape::AS_PROPERTY_SHAPE_TYPE);
    if (variant.type == VariableType::INT && variant.value) {
        int shapeType = *static_cast<int *>(variant.value);
        if (true) {
            if (m_pAsShapeRes) {
                m_resourceJsonObject << m_pAsShapeRes->property(AsShapeRes::AS_PROPERTY_SHAPES);
            }
//       }else if(shapeType >=4 && shapeType <=5 || shapeType==0){
//            variant = property(AsShape::AS_PROPERTY_SHAPE_INSTRUCTS);
//            if( variant.type == VariableType::ASINSTRUCTLISTLIST && variant.value){
//                m_resourceJsonObject << variant;
//            }
        }
    }

    return m_resourceJsonObject;
}

Json::Value &AsShape::serialized() {
    Json::Value &jsonObject = AsRenderable::serialized();
    Variant variant = property(AsShape::AS_PROPERTY_IS_CONNECTOR);
    bool isConnector = variant.value ? *static_cast<bool *>( variant.value ) : false;
    if (isConnector) {
        jsonObject["type"] = "connector";
    }
    return jsonObject;
}

QString &AsShape::inkPropertyName(AsInk::AsEnumProperty asEnumProperty) {
    static QString propertyName;
    if (asEnumProperty == AsInk::AS_PROPERTY_PENCAPSTYLE) {
        propertyName = !m_bIsConnector ? "boarderPenCapStyle" : "connectorPenCapStyle";
    } else if (asEnumProperty == AsInk::AS_PROPERTY_PENCOLOR) {
        propertyName = !m_bIsConnector ? "boarderPenColor" : "connectorPenColor";
    } else if (asEnumProperty == AsInk::AS_PROPERTY_PENSTYLE) {
        propertyName = !m_bIsConnector ? "boarderStyle" : "connectorStyle";
    } else if (asEnumProperty == AsInk::AS_PROPERTY_PENWIDTH) {
        propertyName = !m_bIsConnector ? "boarderPenWidth" : "connectorPenWidth";
    } else if (asEnumProperty == AsInk::AS_PROPERTY_PENJOINSTYLE) {
        propertyName = !m_bIsConnector ? "boarderJoinStyle" : "connectorJoinStyle";
    }
    return propertyName;
}

QString AsShape::typeName() {
    return "shape";
}


