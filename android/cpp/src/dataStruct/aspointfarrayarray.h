#ifndef ASPOINTFARRAYARRAY_H
#define ASPOINTFARRAYARRAY_H


#include <QVector>

#include "aspointfarray.h"

class AsPointFArrayArray : public QVector<AsPointFArray>
{ 
public:
    AsPointFArrayArray();

    const QByteArray& asToByteArray( void );

    QRectF asBoundingRect();
    void asTranslate(const QPointF& trans);


private:
    QByteArray m_Array;
};



#endif // ASPOINTFARRAYARRAY_H
