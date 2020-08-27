// Implements the AsPointFArrayArray class.
// $Author: Paul Wareing.

#include "aspointfarrayarray.h"
#include <QRectF>


AsPointFArrayArray::AsPointFArrayArray()
{

}

const QByteArray& AsPointFArrayArray::asToByteArray( void )
{
    m_Array.clear();
    foreach( AsPointFArray shape, *this )
    {
        QByteArray baShape;
        baShape = shape.asToByteArray();
        m_Array.append( baShape );
    }
    return m_Array;
}

QRectF AsPointFArrayArray::asBoundingRect()
{
    QRectF brect;
    foreach(const AsPointFArray &shape, *this )
    {
        //brect = brect.united(shape.boundingRect());
    }
    return brect;
}


void AsPointFArrayArray::asTranslate(const QPointF& trans)
{
    for(int i=0;i<count();++i )
    {
      //  operator[](i).translate(trans);
    }
}
