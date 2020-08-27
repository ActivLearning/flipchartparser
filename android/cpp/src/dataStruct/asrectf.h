// Defines the AsRectF class.
// $Author: Andrew Edwardson

#ifndef ASRECTF_H
#define ASRECTF_H

#include <QMetaType>
#include <QRectF>
#include "../io/QJsonConvert.h"


class AsRectF : public QRectF
{ 
public:
    AsRectF();
    AsRectF( qreal left, qreal top , qreal width , qreal height) : QRectF( left , top , width , height ) {}
    AsRectF( const QPointF&, const QPointF& );
    AsRectF( const QRectF& );
    virtual ~AsRectF();

    QPointF asTopLeft( void ) const;
    QPointF asTopRight( void ) const;
    QPointF asBottomLeft( void ) const;
    QPointF asBottomRight( void ) const;

    QPointF asTopCentre( void ) const;
    QPointF asBottomCentre( void ) const;
    QPointF asLeftCentre( void ) const;
    QPointF asRightCentre( void ) const;

    void asUnite( const QRectF& );
};




#endif // ASRECTF_H
