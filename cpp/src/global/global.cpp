//
// Created by alex on 2019/9/11.
//

#include "global.h"
#include "../io/QJsonConvert.h"
#include <QDateTime>
#include "../serialization/json/json.h"
#include "../util/commonlog.h"

bool Variant::isSimpleType()
{

    switch (type){
       case VariableType::BOOL:
       case VariableType::INT:
       case VariableType::UINT:
       case VariableType::DOUBLE:
       case VariableType::Q_STRING:
       case VariableType::Q_DATE_TIME:
           return true;

    }
    return false;
}

Json::Value&  Variant::operator <<(Json::Value& object)const {

    if(!value){
        return object;
    }
    switch (type){
        case VariableType ::BOOL:
            object["bool"]= *static_cast<bool *>(value);
            break;
        case VariableType ::INT:
            object["int"] = *static_cast<int *>(value);
            break;
        case VariableType ::UINT:
            object["uint"] = (int)*static_cast<uint32_t *>(value);
            break;
        case VariableType ::DOUBLE:
            object["double"] = *static_cast<double *>(value);
            break;
        case VariableType ::Q_POINT_F:
            object << *static_cast<QPointF *>(value);
            break;
        case VariableType ::Q_SIZE:
            object << *static_cast<QSize *>(value);
            break;
        case VariableType ::Q_SIZE_F:
            object << *static_cast<QSizeF *>(value);
            break;
        case VariableType ::Q_RECT:
            object << *static_cast<QRect *>(value);
            break;
        case VariableType ::Q_RECT_F:
            object << *static_cast<QRectF *>(value);
            break;
        case VariableType ::Q_STRING:
            object << *static_cast<QString *>(value);
            break;
        case VariableType ::Q_STRING_LIST:
            object << *static_cast<QStringList *>(value);
            break;
        case VariableType ::Q_TIME:
            object << *static_cast<QTime *>(value);
            break;
        case VariableType ::Q_DATE_TIME:
            object << *static_cast<QDateTime *>(value);
            break;
        case VariableType ::Q_LIST:
            object << *static_cast<QList<Variant> *>(value);
            break ;
        case VariableType ::Q_BYTE_ARRAY:
            object << *static_cast<QByteArray *>(value);
            break;
        case VariableType ::Q_COLOR:
            object << *static_cast<QColor *>(value);
            break;
        case VariableType ::Q_IMAGE:
            break;
        case VariableType ::ASPOINTFARRAY:
            object << *static_cast<AsPointFArray *>(value);
            break;
        case VariableType ::ASRECTF:
            object << *static_cast<AsRectF *>(value);
            break;
        case VariableType ::ASPOINTFAARAYARRAY:
            object << *static_cast<AsPointFArrayArray *>(value);
            break;
        case VariableType ::ASINSTRUCTLISTLIST:
            object << *static_cast<AsInstructListList *>(value);
            break;
        case VariableType ::ASMOULIST:
            break;
        case VariableType ::ASRESOUCREINDEX:
            break;
        case VariableType ::ASTEXTRUNARRAY:
            object << *static_cast<AsTextRunArray *>(value);
            break;
        case VariableType ::ASPOINTER:
            object << *static_cast<AsPointer *>(value);
            break;
        case VariableType ::ASUNDORESOURCEINDEX:
            break;
        case VariableType ::ASOPTIONLIST:
            break;
        case VariableType ::ASSTRINGPAIRLIST:
            break;
        case VariableType ::ASFOLDERINDEX:
            break;
        case VariableType ::ASRESOURCEREGISTER:
            break;
        case VariableType ::ASINK:
            object << *static_cast<AsInk *>(value);
            break;
        case VariableType ::ASTRANSFORM:
            object << *static_cast<AsTransform *>(value);
            break;
        case VariableType ::ASORIGIN:
            object << *static_cast<AsOrigin *>(value);
            break;
        case VariableType ::ASLABEL:
            break;
        case VariableType ::ASTEXATCHARFORMAT:
            break;
        case VariableType ::ASVIRTUALFOLDERINDEX:
            break;
        case VariableType ::ASASYNCTESTLEVELLIST:
            break;
        default:

            break;
    }
    return object;
}

void Variant::simpleSerializer(Json::Value &object, const QString &key)
{
    std::string keyStd = key.toStdString();
    switch (type) {
        case VariableType::BOOL:
            object[keyStd] = *static_cast<bool *>(value);
            break;
        case VariableType::INT:
            object[keyStd] = *static_cast<int *>(value);
            break;
        case VariableType::UINT:
            object[keyStd] = (int) *static_cast<uint32_t *>(value);
            break;
        case VariableType::DOUBLE:
            if( key == "zOrder" )
            {
                object[keyStd] = (int)(*static_cast<double *>(value));
            }else{
                object[keyStd] = Math::FormatSignificantDigits(*static_cast<double *>(value));
            }
            break;
//        case VariableType::Q_POINT_F:
//            object << *static_cast<QPointF *>(value);
//            break;
//        case VariableType::Q_SIZE:
//            object << *static_cast<QSize *>(value);
//            break;
//        case VariableType::Q_SIZE_F:
//            object << *static_cast<QSizeF *>(value);
//            break;
//        case VariableType::Q_RECT:
//            object << *static_cast<QRect *>(value);
//            break;
//        case VariableType::Q_RECT_F:
//            object << *static_cast<QRectF *>(value);
//            break;
        case VariableType::Q_STRING:
            object[keyStd] =  static_cast<QString *>(value)->toStdString();
            break;
//        case VariableType::Q_STRING_LIST:
//            object << *static_cast<QStringList *>(value);
//            break;
//        case VariableType::Q_TIME:
//            object << *static_cast<QTime *>(value);
//            break;
        case VariableType::Q_DATE_TIME:
            object[keyStd] =  static_cast<QDateTime *>(value)->toString().toStdString();
            break;
//        case VariableType::Q_LIST:
//            object << *static_cast<QList<Variant> *>(value);
//            break;
//        case VariableType::Q_BYTE_ARRAY:
//            object << *static_cast<QByteArray *>(value);
//            break;
//        case VariableType::Q_COLOR:
//            object << *static_cast<QColor *>(value);
//            break;
//        case VariableType::Q_IMAGE:
//            break;
    }

}

