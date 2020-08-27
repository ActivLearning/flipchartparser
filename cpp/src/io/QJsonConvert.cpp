//
// Created by alex on 2019/9/9.
//

#include "QJsonConvert.h"
#include "../dataStruct/aspointfarray.h"
#include "../dataStruct/aspointfarrayarray.h"
#include "../dataStruct/asrectf.h"
#include "../objects/asink.h"
#include "../io/asnode.h"
#include "../objects/asorigin.h"
#include "../objects/aspointer.h"
#include "../objects/astransform.h"
#include "../objects/qcolor.h"
#include "../dataStruct/astextrunarray.h"

#include "../dataStruct/asinstructlistlist.h"
#include "../serialization/json/json.h"
#include <QRect>
#include <QRectF>
#include <QPointF>
#include <QSize>
#include <QSizeF>
#include <QStringList>
#include <QTime>



Json::Value & operator <<(Json::Value& object, QPointF& pt){
   // Json::Value tmp;
    object["x"]=Math::FormatSignificantDigits(pt.x()) ;
    object["y"]=Math::FormatSignificantDigits(pt.y()) ;
  //  object["qpointf"]=tmp;
    return object;
}

Json::Value& operator <<(Json::Value& object,  QSize& size){
 //   Json::Value tmp;
    object["width"]=Math::FormatSignificantDigits(size.width()) ;
    object["height"]=Math::FormatSignificantDigits(size.height()) ;
  //  object["qsize"]=tmp;
    return object;
}

Json::Value& operator <<(Json::Value& object, QSizeF& size){
  //  Json::Value tmp;
    object["width"]=Math::FormatSignificantDigits(size.width()) ;
    object["height"]=Math::FormatSignificantDigits(size.height()) ;
   // object["qsizef"]=tmp;
    return object;
}

Json::Value& operator <<(Json::Value& object,  QRect& rect){
  //  Json::Value tmp;
    object["x"]=Math::FormatSignificantDigits(rect.x()) ;
    object["y"]=Math::FormatSignificantDigits(rect.y()) ;
    object["width"]=Math::FormatSignificantDigits(rect.width()) ;
    object["height"]=Math::FormatSignificantDigits(rect.height()) ;
   // object["qrect"]=tmp;
    return object;
}

Json::Value &operator<<(Json::Value &object,  QRectF &rect)
{
   // Json::Value tmp;
    object["x"]=Math::FormatSignificantDigits(rect.x()) ;
    object["y"]=Math::FormatSignificantDigits(rect.y()) ;
    object["width"]=Math::FormatSignificantDigits(rect.width()) ;
    object["height"]=Math::FormatSignificantDigits(rect.height()) ;
   // object["qrectf"]=tmp;
    return object;
}

Json::Value &operator<<(Json::Value &object,  QString &str)
{
   // Json::Value tmp;
    object["text"]=str.toStdString();
   // object["qstring"]=tmp;
    return object;
}

Json::Value &operator<<(Json::Value &object, QStringList &strList)
{
   // Json::Value tmp;
    for (int i = 0; i < strList.length(); ++i) {
        object["text"+QString::number(i).toStdString()]=strList.at(i).toStdString();
    }
   // object["qstringlist"]=tmp;
    return object;
}

Json::Value &operator<<(Json::Value &object, QTime &time)
{
  //  Json::Value tmp;
    object["hour"]=time.hour();
    object["minute"]=time.minute();
    object["second"]=time.second();
    object["msecond"]=time.msec();
   // object["qtime"]=tmp;
    return object;
}

Json::Value &operator<<(Json::Value &object, QDateTime &dateTime)
{

    object["dateTime"]=dateTime.toString().toStdString();
    return  object;
}

Json::Value &operator<<(Json::Value &object, QByteArray &byteArray)
{
    object["byteArray"]=QString(byteArray).toStdString();
    return  object;

}

Json::Value &operator<<(Json::Value &object, QColor &color)
{
   // Json::Value tmp;
    object["a"]=color.a;
    object["r"]=color.r;
    object["g"]=color.g;
    object["b"]=color.b;
   // object["qcolor"]=tmp;
    return object;
}

Json::Value &operator<<(Json::Value &object, AsPointFArray &asPointFArray)
{
    Json::Value tmp;
    Json::Value array;
    for (int i = 0; i < asPointFArray.length(); ++i) {
        tmp["x"]=Math::FormatSignificantDigits(asPointFArray.at(i).x());
        tmp["y"]=Math::FormatSignificantDigits(asPointFArray.at(i).y());
        array.append(tmp);
    }

    object["pointArray"]=array;
    return object;

}

Json::Value &operator<<(Json::Value &object, AsRectF &asRectF)
{
    Json::Value tmp;
    tmp["left"]=Math::FormatSignificantDigits(asRectF.left());
    tmp["top"]=Math::FormatSignificantDigits(asRectF.top());
    tmp["width"]=Math::FormatSignificantDigits(asRectF.width());
    tmp["height"]=Math::FormatSignificantDigits(asRectF.height());
    object=tmp;
    return object;
//    return <#initializer#>;
}


Json::Value& operator <<(Json::Value& object,  AsPointFArrayArray& asRectF)
{
    Json::Value tmp;
    Json::Value array;
    for (int i = 0; i < asRectF.length(); ++i) {
        QString indexStr = QString::number(i);
        AsPointFArray asPointFArray = asRectF.at(i);
        Json::Value tmp1;
        Json::Value array1;
        for (int j = 0; j < asPointFArray.length(); ++j) {
            tmp1["x"]=Math::FormatSignificantDigits(asPointFArray.at(j).x());
            tmp1["y"]=Math::FormatSignificantDigits(asPointFArray.at(j).y());
            array1.append(tmp1);
        }
        array.append(array1);
    }
    object["pointArrayArray"]=array;
    return  object;
}

Json::Value &operator<<(Json::Value &object, AsOrigin &asOrigin)
{

     object=asOrigin.serialized();
     return  object;
}

Json::Value& operator <<(Json::Value& object,  AsInk& asInk)
{
    object=asInk.serialized();
    return  object;
}


Json::Value& operator <<(Json::Value& object,  AsTransform& asTransform)
{
    object=asTransform.serialized();
    return  object;
}



Json::Value& operator <<(Json::Value& object,  QList<Variant>& listVariant)
{

    Json::Value array;
    for (int i = 0; i < listVariant.length(); ++i) {
        QString index = QString::number(i);
        Json::Value tmp;
        tmp << listVariant.at(i);
        array.append(tmp);
    }
    object["listVariant"] = array;
    return  object;
}


Json::Value& operator <<(Json::Value& object,  AsPointer& asPointer)
{
    object["pointer"] = (int)asPointer.asGetNode()->asGetID();
    return  object;
}

Json::Value& operator <<(Json::Value& object,  AsTextRun& asTextRun)
{
    Variant var;
    var = asTextRun.property(AsTextRun::AS_PROPERTY_TEXT);
    if(var.type == VariableType::Q_STRING && var.value){
        object["text"] = static_cast<QString*>(var.value)->toStdString();
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_FONTSIZE);
    if(var.type == VariableType::DOUBLE && var.value){
        object["fontSize"] = *static_cast<double *>(var.value);
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_FONTFAMILY);
    if(var.type == VariableType::Q_STRING && var.value){
        object["fontFamily"] = static_cast<QString*>(var.value)->toStdString();
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_TEXTCOLOR);
    if(var.type == VariableType::Q_COLOR && var.value){
        Json::Value tmp;
        tmp << var;
        object["textColor"] = tmp;
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_TEXTPOS);
    if(var.type == VariableType::Q_POINT_F && var.value){
        Json::Value tmp;
        tmp << var;
        object["position"] = tmp;
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_BOUNDING_RECT);
    if(var.type == VariableType::ASRECTF && var.value){
        Json::Value tmp;
        tmp << var;
        object["boundingRect"] = tmp;
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_BULLETTEXT);
    if(var.type == VariableType::Q_STRING && var.value){
        Json::Value tmp;
        tmp << var;
        object["bulletText"] = tmp;
    }
    var = asTextRun.property(AsTextRun::AS_PROPERTY_BULLETPOSITION);
    if(var.type == VariableType::Q_POINT_F && var.value){
        Json::Value tmp;
        tmp << var;
        object["bulletPosition"] = tmp;
    }
    return object;
}

Json::Value& operator <<(Json::Value& object,  AsTextRunArray& asTextRunArray)
{
    Json::Value array;
    for (int i = 0; i < asTextRunArray.length(); ++i) {
        Json::Value tmp;
        tmp << const_cast<AsTextRun&>(asTextRunArray.at(i));
        array.append(tmp);
    }
    object["textRunArray"] = array;
    return  object;
}

Json::Value& operator <<(Json::Value& object,  AsInstructListList& asInstructListList)
{
    Json::Value array;
    for (int i = 0; i < asInstructListList.length(); ++i) {
        Json::Value object1;
        Json::Value array1;
        AsInstructList asInstructList = asInstructListList[i];
        for (int j = 0; j < asInstructList.length(); ++j) {
            AsPathInstruct asPathInstruct = asInstructList[j];
            if( asPathInstruct.asGetType() == AsPathInstruct::AS_INSTRUCT_TYPE_ARC ){
                object1["majorAxisRadius"]=asPathInstruct.m_xRadius;
                object1["minorAxisRadius"]=asPathInstruct.m_yRadius;
                object1["clockWise"]=asPathInstruct.m_bClockwise;
                object1["largeArc"]=asPathInstruct.m_bLargeArc;
                Json::Value jsonObject;
                jsonObject << asPathInstruct.m_endPoint;
                object1["endPoint"]=jsonObject;
                object1["type"]="ellispe";
                array1.append(object1);
            }else {
                Json::Value jsonObject;
                jsonObject << asPathInstruct.m_endPoint;
                object1["endPoint"]=jsonObject;
                if(asPathInstruct.asGetType() == AsPathInstruct::AS_INSTRUCT_TYPE_MOVE ) {
                    object1["type"] = "movement";
                }
                else{
                    object1["type"] = "line";
                }
                array1.append(object1);
            }
        }
        array.append(array1);
    }
    object["shapeElements"]=array;
    return  object;
}
