// Defines the AsPointFArray class.
// $Author: Paul Wareing

#ifndef ASPOINTFARRAY_H
#define ASPOINTFARRAY_H

#include <QMetaType>
#include "../objects/qpolygonf.h"
#include <QByteArray>

class AsPointFArray : public QPolygonF
{ 
public:
    AsPointFArray();
    // ATE added 20/10/2005
    //AsPointFArray( int size );
   // AsPointFArray( const AsPointFArray &pnt );

    virtual ~AsPointFArray();

    const QByteArray& asToByteArray( void );
    bool asFromByteArray( QByteArray *array, int numPoints );

    //AsPointFArray& AsGetPointFArray( void );
    //const AsPointFArray& AsGetPointFArrayConst() const;

    int asGetNextIndex( int index );
    int asGetPreviousIndex( int index );

    void asAppend( qreal x, qreal y );

private:
    void asAppendDoubleToByteArray( QByteArray&, double );
    double asGetDoubleFromByteArray( const double * );

    bool m_bNoSwap;

    QByteArray m_Array;
};

Q_DECLARE_METATYPE( AsPointFArray )

#endif // ASPOINTFARRAY_H
