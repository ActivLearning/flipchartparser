// Defines the AsInstructList Class
// $Author: Mark Roberts

#ifndef ASINSTRUCTLIST_H
#define ASINSTRUCTLIST_H

//#include <QRectF>
//#include <QString>
//#include <QStringList>


#include "aspathinstructs.h"




class AsInstructList : public QList<AsPathInstruct>
{
public:
    AsInstructList()
    {
    };

    ~AsInstructList(){};

    void asUpdateControlVar(const QSizeF& size);



    void asModifyControlDivisor(QPointF delta, QSizeF size, int controlIndex);

private:

    
};




#endif


