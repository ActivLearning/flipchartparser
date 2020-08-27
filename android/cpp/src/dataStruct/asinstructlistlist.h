// Defines the AsInstructList Class
// $Author: Mark Roberts

#ifndef ASINSTRUCTLISTLIST_H
#define ASINSTRUCTLISTLIST_H

//#include <QRectF>
//#include <QString>
//#include <QStringList>
//#include <QPainterPath>
#include <QMetaType>
#include "asinstructlist.h"


class AsInstructListList : public QList<AsInstructList>
{
public: 
    AsInstructListList(){};
    ~AsInstructListList(){};

    void asUpdateControlVars(const QSizeF& size);

};

Q_DECLARE_METATYPE( AsInstructListList );


#endif


