// Implements the AsBackground class
// $Author: Andrew Edwardson

#include "asbackground.h"
#include "../io/asnode.h"
#include "asimage.h"


AsBackground::AsBackground(AsFactory *pFactory) : AsObject(pFactory),
                                                  m_pImg(NULL) {
    this->asSetDefaults();
}

AsBackground::AsBackground() : AsObject(0),
                               m_pImg(NULL) {
    this->asSetDefaults();
}

AsBackground::AsBackground(const AsBackground &background) : AsObject(background) {
    this->asCopy(background);
}

AsBackground::~AsBackground() {

}

void AsBackground::operator=(const AsBackground &background) {
    AsObject::operator=(background);
    this->asCopy(background);
}

void AsBackground::asCopy(const AsBackground &background) {
    this->m_BackgroundInk = background.asGetBackgroundInk();
    this->m_nBackgroundType = background.asGetBackgroundType();
    this->m_pImg = background.m_pImg;
}

void AsBackground::asSetDefaults(void) {
    // Set our type.
    this->asSetType(AsObject::AS_OBJECT_BACKGROUND);

    // Initialise the properties with primitive values
    this->m_nBackgroundType = AsBackground::AS_BACKGROUNDTYPE_INK;
    QColor black = QColor(Qt::black);
    this->m_BackgroundInk.asSetBrushColor(black);
    this->m_BackgroundInk.asSetBrushStyle(AsInk::AS_BRUSHSTYLE_SOLID);
}

// Properties.
QHash<QString, quint16> &AsBackground::m_lProperties(void) {
    static QHash<QString, quint16> HashProperties;

    if (HashProperties.isEmpty()) {
        // From AsObject...
        //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsBackground::AS_PROPERTY_DATETIMECREATED );

        // From AsBackground
        HashProperties.insert("backgroundType", (quint16) AsBackground::AS_PROPERTY_BACKGROUNDTYPE);
        HashProperties.insert("backgroundInk", (quint16) AsBackground::AS_PROPERTY_BACKGROUNDINK);
        HashProperties.insert("backgroundImage",
                              (quint16) AsBackground::AS_PROPERTY_BACKGROUNDIMAGE);
    }

    return HashProperties;
}

// only relevant for background type image
bool AsBackground::asDrawImageBackInk(void) {
    if (this->m_nBackgroundType == AsBackground::AS_BACKGROUNDTYPE_IMAGE) {
        /*  conditional
            if tiled image is transparent or (tilefit != full and tilefit != stretch) then
            we need to paint background color as tile does not cover entire page
        */

        AsNode *pImageNode = m_pImg.asGetNode();

        if (0 == pImageNode) return false;

        AsImage *pImg = (AsImage *) pImageNode->asGetAsObjectReference();

        if (pImg->asGetTiled()) {
            AsImage::AsEnumTileFit TileFitEnum = pImg->asGetTileFit();

            if (pImg->asGetTransparent() || (TileFitEnum != AsImage::AS_TILEFIT_NONE &&
                                             TileFitEnum != AsImage::AS_TILEFIT_STRETCHFIT)) {
                return true;
            } else {
                return false;
            } // met conditions ?
        } else {
            return false;
        }  // tiled ?
    } else {
        // ideally should assert as we are a ink background. be friendly for now
        return false;
    } // is type image ?
}

AsBackground::AsEnumBackgroundType AsBackground::asGetBackgroundType(void) const {
    return this->m_nBackgroundType;
}

void AsBackground::asSetBackgroundType(AsBackground::AsEnumBackgroundType btype) {
    this->m_nBackgroundType = btype;
}

const AsInk &AsBackground::asGetBackgroundInk(void) const {
    return this->m_BackgroundInk;
}

void AsBackground::asSetBackgroundInk(AsInk &clr) {
    this->m_BackgroundInk = clr;
}

void AsBackground::asSetBackgroundColor(QColor &bcolor) {
    this->m_BackgroundInk.asSetBrushStyle(AsInk::AS_BRUSHSTYLE_SOLID);
    this->m_BackgroundInk.asSetBrushColor(bcolor);
}

const QColor &AsBackground::asGetBackgroundColor(void) {
    return this->m_BackgroundInk.asGetBrushColor();
}

void AsBackground::asResetPropertyIndex(void) {
    AsObject::asSetPropertyIterator(&m_lProperties);
}

void AsBackground::asSetBackgroundImagePointer(AsPointer img) {
    m_pImg = img;
}

AsInk *AsBackground::asGetBackgroundInkPointer(void) {
    return &this->m_BackgroundInk;
}

AsPointer AsBackground::asGetBackgroundImagePointer(void) {
    return m_pImg;
}

QString AsBackground::getPropertyNameById(int nID) {
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsBackground::getPropertyIdByName(QString name) const {
    return m_lProperties().value(name);
}

Json::Value &AsBackground::serialized() {
    Json::Value obj;
    if (!isSupportSerializer()) {
        return jsonObj;
    }
            foreach (int propertyId, m_properties.keys()) {
            Variant var = m_properties.value(propertyId);
            if (!var.value) {
                continue;
            }
            if (asGetPropertyNameById(propertyId) == "backgroundImage") {

                AsPointer *pointer = static_cast<AsPointer *>(var.value);
                AsImage *image = static_cast<AsImage *>(pointer->asGetNode()->asGetAsObjectReference());
                jsonObj["backgroundImage"] = image->serialized();
                continue;
            }
            if (asGetPropertyNameById(propertyId) == "backgroundInk") {
                AsInk *asInk = static_cast<AsInk *>(var.value);
                Json::Value ink;
                if (asInk) {
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
                    jsonObj["ink"] = ink;
                }
                continue;
            }
            if (var.isSimpleType()) {
                QString propertyName = asGetPropertyNameById(propertyId);
                if (propertyName != "")
                    var.simpleSerializer(jsonObj, asGetPropertyNameById(propertyId));

            } else {
                Json::Value content;
                content << m_properties.value(propertyId);
                QString propertyName = asGetPropertyNameById(propertyId);
                if (propertyName != "")
                    obj[asGetPropertyNameById(propertyId).toStdString()] = content;
            }


        }

    jsonObj["id"] = static_cast<int>(asGetID());
    jsonObj["type"] = asGetTypeChar();

    return jsonObj;
}

QString AsBackground::typeName() {
    return "background";
}
