// Implemented the AsRectF class.
// $Author: Andrew Edwardson

#include "asrectf.h"



AsRectF::AsRectF()
{
}

AsRectF::~AsRectF()
{
}

AsRectF::AsRectF( const QPointF& pt1, const QPointF& pt2 )
{
    QPointF topLeft;
    QPointF bottomRight;

    if ( pt1.x() < pt2.x() )
    {
        topLeft.setX( pt1.x() );
        bottomRight.setX( pt2.x() );
    }
    else
    {
        topLeft.setX( pt2.x() );
        bottomRight.setX( pt1.x() );
    }

    if ( pt1.y() < pt2.y() )
    {
        topLeft.setY( pt1.y() );
        bottomRight.setY( pt2.y() );
    }
    else
    {
        topLeft.setY( pt2.y() );
        bottomRight.setY( pt1.y() );
    }

    QSizeF size = QSizeF( bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y() );
    this->setTopLeft( topLeft );
    this->setSize( size );
}

AsRectF::AsRectF( const QRectF& rect )
{
	setTopLeft( rect.topLeft() );
	setSize( rect.size() );
}

QPointF AsRectF::asTopLeft( void ) const
{
    return this->topLeft();
}

QPointF AsRectF::asTopRight( void ) const
{
    return QPointF( this->topRight().x() - 1, this->topRight().y() );
}

QPointF AsRectF::asBottomLeft( void ) const
{
    return QPointF( this->bottomLeft().x(), this->bottomLeft().y() - 1 );
}

QPointF AsRectF::asBottomRight( void ) const
{
    return QPointF( this->bottomRight().x() - 1, this->bottomRight().y() - 1 );
}

QPointF AsRectF::asTopCentre( void ) const
{
    QPointF p = this->topLeft();
    p.setX( p.x() + ( ( this->width() - 1 ) / 2 ) );
    return p;
}

QPointF AsRectF::asBottomCentre( void ) const
{
    QPointF p = this->bottomLeft();
    p.setY( p.y() - 1 );
    p.setX( p.x() + ( ( this->width() -1 ) / 2 ) );
    return p;
}

QPointF AsRectF::asLeftCentre( void ) const
{
    QPointF p = this->topLeft();
    p.setY( p.y() + ( ( this->height() - 1 ) / 2 ) );
    return p;
}

QPointF AsRectF::asRightCentre( void ) const
{
    QPointF p = this->topRight();
    p.setX( p.x() - 1 );
    p.setY( p.y() + ( ( this->height() - 1 ) / 2 ) );
    return p;
}

void AsRectF::asUnite( const QRectF& rect )
{
    qreal left = this->left();
    qreal top = this->top();
    qreal right = this->right();
    qreal bottom = this->bottom();

    if ( rect.left() < left )
        left = rect.left();

    if ( rect.top() < top )
        top = rect.top();

    if ( rect.bottom() > bottom )
        bottom = rect.bottom();

    if ( rect.right() > right )
        right = rect.right();

    this->setRect( left, top, right - left, bottom - top );
}
