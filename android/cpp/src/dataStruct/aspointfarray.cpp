// Implements the AsPointFArray class.
// $Author: Paul Wareing.

#include "aspointfarray.h"



AsPointFArray::AsPointFArray()
{
    // We will always return the byte array in little endian.  Therefore,
    // if the system is a little endian system we don't have to 
    // swap the doubles in the QPointFs.  If the system is a big endian
    // then we have to reverse the doubles.
    m_bNoSwap = QSysInfo::ByteOrder == QSysInfo::LittleEndian;
}

/*
AsPointFArray::AsPointFArray( int size ) : QVector<QPointF>( size )
{
    m_bNoSwap = QSysInfo::ByteOrder == QSysInfo::LittleEndian;
}
*/
/*
AsPointFArray::AsPointFArray( const AsPointFArray &pnt ) : QVector<QPointF>( pnt )
{
   m_bNoSwap = QSysInfo::ByteOrder == QSysInfo::LittleEndian;
}
*/
AsPointFArray::~AsPointFArray()
{

}

const QByteArray& AsPointFArray::asToByteArray( void )
{
    m_Array.clear();
    foreach( QPointF point, *this )
    {
        asAppendDoubleToByteArray( m_Array, point.x() );
        asAppendDoubleToByteArray( m_Array, point.y() );
    }
    return m_Array;
}

bool AsPointFArray::asFromByteArray( QByteArray *ba, int numPoints )
{
    // TODO... If the byte array does not have the correct number of bytes 
    // then return false.

    double * pDouble = ( double * ) ba->data();

    for ( int i = 0 ; i < numPoints ; ++i )
    {
        QPointF point;
        point.setX( asGetDoubleFromByteArray( pDouble++ ) );
        point.setY( asGetDoubleFromByteArray( pDouble++ ) );

        this->append( point );
    };

    return true;
}

void AsPointFArray::asAppendDoubleToByteArray( QByteArray& ba, double d )
{
    char * pByte;
    if ( m_bNoSwap )
    {
        pByte = ( char* ) &d;
        for ( int i = 0 ; i<8 ; ++i )
        {
            ba.append( *pByte++ );
        }
    }
    else
    {
        pByte = ( char* ) &d + 7;
        for ( int i = 0 ; i<8 ; ++i )
        {
            ba.append( *pByte-- );
        }
    }
}

double AsPointFArray::asGetDoubleFromByteArray( const double * pDouble )
{
    double d;
    if ( m_bNoSwap )
    {
        d = *pDouble;
    }
    else
    {
        char dInverted[ 8 ];
        char* pByte = ( char* ) pDouble;
        for ( int i = 0 ; i < 8 ; ++i )
        {
            dInverted[ i ] = *( pByte + 7 - i );
        }
        d = *( double* ) dInverted;
    }
    return d;
}

/*
AsPointFArray & AsPointFArray::AsGetPointFArray( void )
{
    return *this;
}

const AsPointFArray &AsPointFArray::AsGetPointFArrayConst() const
{
  return *this;
}
*/

int AsPointFArray::asGetNextIndex( int index )
{
    index++;
    if ( index == this->count() )
    {
        index = 0;
    }
    return index;
}

int AsPointFArray::asGetPreviousIndex( int index )
{
    index--;
    if ( index < 0 )
    {
        index = this->count() - 1;
    }
    return index;
}


void AsPointFArray::asAppend( qreal x, qreal y )
{
    QPointF q( x, y );
    this->append( q );
}
