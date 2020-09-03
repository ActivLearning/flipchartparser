// Implements the AsTransform class.
// (c)2006 Promethean Technologies Group Ltd.

#include "astransform.h"
#include "asorigin.h"
#include "../dataStruct/asrectf.h"


const double AsTransform::s_kMaxAngle = 360.0;
const double AsTransform::s_kMinAngle = 0.0;


AsTransform::AsTransform(AsFactory *pAsFactory) : AsObject(pAsFactory) {
    // Set the type property.
    asSetType(AsObject::AS_OBJECT_TRANSFORM);

    // set defaults - identity matrix compatible
    this->asResetTransformProps();
}

AsTransform::AsTransform() : AsObject(0) {
    // Set the type property.
    asSetType(AsObject::AS_OBJECT_TRANSFORM);

    // set defaults - identity matrix compatible
    this->asResetTransformProps();
}

AsTransform::AsTransform(const AsTransform &transform) : AsObject(transform) {
    asCopy(transform);
}

void AsTransform::operator=(const AsTransform &transform) {
    AsObject::operator=(transform);
    asCopy(transform);
}

void AsTransform::asCopy(const AsTransform &transform) {
    m_Translate = transform.asGetTranslate();
    m_dAngle = transform.asGetAngle();
    m_ScaleFactor = transform.asGetScaleFactor();
    m_bReflected = transform.asGetReflected();
    m_bInverted = transform.asGetInverted();
}

bool AsTransform::operator==(const AsTransform &transform) {
    if ((m_Translate != transform.asGetTranslate()) ||
        (m_dAngle != transform.asGetAngle()) ||
        (m_ScaleFactor != transform.asGetScaleFactor()) ||
        (m_bReflected != transform.asGetReflected()) ||
        (m_bInverted != transform.asGetInverted())) {
        return false;
    }
    return true;
}

AsTransform::~AsTransform() {

}

QHash<QString, quint16> &AsTransform::m_lProperties(void) {
    static QHash<QString, quint16> HashProperties;

    if (HashProperties.isEmpty()) {
        // From AsObject...
        //  HashProperties.insert( "asDateTimeCreated", ( quint16 )AsTransform::AS_PROPERTY_DATETIMECREATED );

        // From AsTransform...
        HashProperties.insert("translate", (quint16) AsTransform::AS_PROPERTY_TRANSLATE);
        HashProperties.insert("angle", (quint16) AsTransform::AS_PROPERTY_ANGLE);
        HashProperties.insert("scaleFactor", (quint16) AsTransform::AS_PROPERTY_SCALEFACTOR);
        HashProperties.insert("reflected", (quint16) AsTransform::AS_PROPERTY_REFLECTED);
        HashProperties.insert("inverted", (quint16) AsTransform::AS_PROPERTY_INVERTED);
    }

    return HashProperties;
}

void AsTransform::asResetPropertyIndex(void) {
    AsObject::asSetPropertyIterator(&m_lProperties);
}

const QPointF &AsTransform::asGetTranslate(void) const {
    return m_Translate;
}

void AsTransform::asSetTranslate(const QPointF &translate) {
    // Assert on NaN
    Q_ASSERT(translate.x() == translate.x());
    Q_ASSERT(translate.y() == translate.y());

    m_Translate = translate;
}

double AsTransform::asGetAngle() const {
    return m_dAngle;
}

void AsTransform::asSetAngle(double dAngle) {
    dAngle = asNormaliseAngle(dAngle);

    m_dAngle = dAngle;
}

const QPointF &AsTransform::asGetScaleFactor(void) const {
    return m_ScaleFactor;
}

void AsTransform::asSetScaleFactor(const QPointF &scaleFactor) {
    m_ScaleFactor = scaleFactor;
}

bool AsTransform::asGetReflected(void) const {
    return this->m_bReflected;
}

void AsTransform::asSetReflected(bool reflect) {
    this->m_bReflected = reflect;
}

bool AsTransform::asGetInverted(void) const {
    return this->m_bInverted;
}

void AsTransform::asSetInverted(bool inverted) {
    this->m_bInverted = inverted;
}

void AsTransform::asResetTransformProps(void) {
    // The default values must result in an identity matrix...
    // Therefore, no translation...
    m_Translate = QPointF(0, 0);
    // No rotation...
    m_dAngle = 0;
    // Scale factor = 1...
    m_ScaleFactor = QPointF(1, 1);
    // ATE - Added 13/10/2005 Inverted and reflected set to false
    this->m_bReflected = this->m_bInverted = false;
}

//const QMatrix& AsTransform::asDoTransform( const AsOrigin & ScaleOrigin , const AsRectF & obRect )
//{
//    this->m_Matrix.reset();
//    this->m_Matrix.translate( this->m_Translate.x() + ScaleOrigin.asGetX(),
//                              this->m_Translate.y() + ScaleOrigin.asGetY());
//    this->m_Matrix.rotate( this->m_dAngle );
//    this->m_Matrix.scale( this->m_ScaleFactor.x(), this->m_ScaleFactor.y());
//
//    this->m_Matrix.translate( -ScaleOrigin.asGetX(), - ScaleOrigin.asGetY() );
//
//    /* check for reflected and inverted . need to do some manipulation
//    that's why I need the original bounding rect to adjust */
//    if( this->m_bReflected || this->m_bInverted )
//    {
//        qreal tx,ty,sfx,sfy;
//        // reflecting causes mirroring we want to adjust back not to let this happen
//        if( this->m_bReflected )
//        {
//            tx = obRect.width();
//            // flip x scale
//            sfx = -1.0;
//        }
//        else
//        {
//            // as normal
//            tx = 0.0;
//            sfx = 1.0;
//        }
//
//        // same again for inverted
//        if( this->m_bInverted )
//        {
//            ty = obRect.height();
//            sfy = -1.0;
//        }
//        else
//        {
//            ty = 0.0;
//            sfy = 1.0;
//        }
//
//        this->m_Matrix.translate( tx , ty );
//        this->m_Matrix.scale( sfx , sfy );
//
//    }  // reflected / inverted ?
//
//    return this->m_Matrix;
//}
//
//
//const QMatrix& AsTransform::asDoTransform( const AsOrigin & ScaleOrigin, const AsRectF & obRect, const QMatrix & WorldMat  )
//{
//    this->asDoTransform( ScaleOrigin , obRect );
//    m_Matrix *= WorldMat;
//    return m_Matrix;
//}

double AsTransform::asNormaliseAngle(double dAngle) {
    while (dAngle > s_kMaxAngle) dAngle -= s_kMaxAngle;

    while (dAngle < s_kMinAngle) dAngle += s_kMaxAngle;

    return dAngle;
}

QString AsTransform::getPropertyNameById(int nID) {
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsTransform::getPropertyIdByName(QString name) const {
    return m_lProperties().value(name);
}

QString AsTransform::typeName() {
    return "transform";
}

Json::Value &AsTransform::serialized() {
    Json::Value &serializedString = AsObject::serialized();
    serializedString.removeMember("property");
    for (int propertyId: m_properties.keys()) {
        Variant var = m_properties.value(propertyId);
        if (!var.value) {
            continue;
        }
        if (!isPropertyNeededSerialized(propertyId)) {
            continue;
        }
        if (var.isSimpleType()) {
            QString propertyName = asGetPropertyNameById(propertyId);
            if (propertyName != "")
                var.simpleSerializer(serializedString, asGetPropertyNameById(propertyId));

        } else {
            Json::Value content;
            content << m_properties.value(propertyId);
            QString propertyName = asGetPropertyNameById(propertyId);
            if (propertyName != "")
                serializedString[asGetPropertyNameById(propertyId).toStdString()] = content;
        }
    }
    return serializedString;
}
