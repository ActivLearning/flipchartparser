//
// Created by alex on 2019/9/9.
//

#ifndef FLIPCHARTQUICK_QJSONCOVERT_H
#define FLIPCHARTQUICK_QJSONCOVERT_H

#include "../global/global.h"

class AsInk;
class AsInstructListList;
class AsOrigin;
class AsPointer;
class AsPointFArray;
class AsPointFArrayArray;
class AsRectF;
class AsTextRunArray;
class AsTransform;




class QByteArray;
class QColor;
class QDateTime;
class QPointF;
class QRect;
class QRectF;
class QSize;
class QSizeF;
class QString;
class QStringList;
class QTime;



Json::Value& operator <<(Json::Value& object, QPointF& pt);
Json::Value& operator <<(Json::Value& object,  QSize& size);
Json::Value& operator <<(Json::Value& object,  QSizeF& size);
Json::Value& operator <<(Json::Value& object,  QRect& rect);
Json::Value& operator <<(Json::Value& object,  QRectF& rect);
Json::Value& operator <<(Json::Value& object,  QString& str);
Json::Value& operator <<(Json::Value& object,  QStringList& strList);
Json::Value& operator <<(Json::Value& object,  QTime& time);
Json::Value& operator <<(Json::Value& object,  QDateTime& dateTime);
Json::Value& operator <<(Json::Value& object,  QByteArray& byteArray);
Json::Value& operator <<(Json::Value& object,  QColor& color);
Json::Value& operator <<(Json::Value& object,  AsPointFArray& asPointFArray);
Json::Value& operator <<(Json::Value& object,  AsRectF& asRectF);
Json::Value& operator <<(Json::Value& object,  AsPointFArrayArray& asRectF);
Json::Value& operator <<(Json::Value& object,  AsOrigin& asOrigin);
Json::Value& operator <<(Json::Value& object,  AsInk& asInk);
Json::Value& operator <<(Json::Value& object,  AsTransform& asTransform);
Json::Value& operator <<(Json::Value& object,  QList<Variant>& listVariant);
Json::Value& operator <<(Json::Value& object,  AsPointer& asPointer);
Json::Value& operator <<(Json::Value& object,  AsTextRunArray& asTextRunArray);
Json::Value& operator <<(Json::Value& object,  AsInstructListList& asInstructListList);
#endif //FLIPCHARTQUICK_QJSONCOVERT_H
