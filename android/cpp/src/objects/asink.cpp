// Implements the AsInk class.
// (c)2006 Promethean Technologies Group Ltd.

#include "asink.h"
//#include "asbrushdesc.h"

int AsInk::m_v3_HighLightAlpha = 128;

AsInk::AsInk()
{
    // Set our type.
    this->asSetType( AsObject::AS_OBJECT_INK );

    // Initialise.
    m_InkType = AsInk::AS_INKTYPE_NORMAL;
    m_nPenWidth = 0;
    m_PenStyle = AsInk::AS_PENSTYLE_NONE;
    m_PenCapStyle = AsInk::AS_PENCAPSTYLE_ROUND;
    m_PenJoinStyle = AsInk::AS_PENJOINSTYLE_ROUND;
    m_BrushStyle = AsInk::AS_BRUSHSTYLE_NONE;
    m_BackgroundMode = AsInk::AS_BACKGROUNDMODE_TRANSPARENT;
    m_BrushGradientType = AsInk::AS_BRUSHGRADIENT_NONE;

    m_bPenDirty = true;
    m_bBrushDirty = true;
}

AsInk::~AsInk()
{

}

//AsInk::AsInk( const AsInk& ink ) : AsObject( ink )
//{
////    asCopy( ink );
//}
//
//void AsInk::operator= ( const AsInk& ink )
//{
//    AsObject::operator =( ink );
////    asCopy( ink );
//}

//void AsInk::asCopy( const AsInk& ink )
//{
//    m_InkType = ink.asGetInkType();
//    m_nPenWidth = ink.asGetPenWidth();
//    m_PenStyle = ink.asGetPenStyle();
//    m_PenCapStyle = ink.asGetPenCapStyle();
//    m_PenJoinStyle = ink.asGetPenJoinStyle();
//    m_PenColor = ink.asGetPenColor();
//    m_BrushStyle = ink.asGetBrushStyle();
//    m_BrushColor = ink.asGetBrushColor();
//    m_BrushColor2 = ink.asGetBrushColor2();
//    m_BrushGradientType = ink.asGetBrushGradientType();
//    m_BackgroundMode = ink.asGetBackgroundMode();
//    m_BackgroundColor = ink.asGetBackgroundColor();
//    m_BrushImage = ink.asGetBrushImage();
//
//    m_bPenDirty = true;
//    m_bBrushDirty = true;
//}

//bool AsInk::operator== ( const AsInk& ink )
//{
//    if (( m_InkType != ink.asGetInkType() ) ||
//        ( m_nPenWidth != ink.asGetPenWidth() ) ||
//        ( m_PenStyle != ink.asGetPenStyle() ) ||
//        ( m_PenCapStyle != ink.asGetPenCapStyle() ) ||
//        ( m_PenJoinStyle != ink.asGetPenJoinStyle() ) ||
//        ( m_PenColor != ink.asGetPenColor() ) ||
//        ( m_BrushStyle != ink.asGetBrushStyle() ) ||
//        ( m_BrushColor != ink.asGetBrushColor() ) ||
//        ( m_BrushColor2 != ink.asGetBrushColor2() ) ||
//        ( m_BrushGradientType != ink.asGetBrushGradientType() ) ||
//        ( m_BackgroundMode != ink.asGetBackgroundMode() ) ||
//        ( m_BackgroundColor != ink.asGetBackgroundColor() ))
//    {
//        return false;
//    }
//    return true;
//}

QHash<QString, quint16>& AsInk::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
      //  HashProperties.insert( "asDateTimeCreated", ( quint16 )AsInk::AS_PROPERTY_DATETIMECREATED );

        // From AsInk...
        HashProperties.insert( "inkType", ( quint16 )AsInk::AS_PROPERTY_INKTYPE );
        HashProperties.insert( "penWidth", ( quint16 )AsInk::AS_PROPERTY_PENWIDTH );
        HashProperties.insert( "penStyle", ( quint16 )AsInk::AS_PROPERTY_PENSTYLE );
        HashProperties.insert( "penCapStyle", ( quint16 )AsInk::AS_PROPERTY_PENCAPSTYLE );
        HashProperties.insert( "penJoinStyle", ( quint16 )AsInk::AS_PROPERTY_PENJOINSTYLE );
        HashProperties.insert( "penColor", ( quint16 )AsInk::AS_PROPERTY_PENCOLOR );
        HashProperties.insert( "brushStyle", ( quint16 )AsInk::AS_PROPERTY_BRUSHSTYLE );
        HashProperties.insert( "brushColor", ( quint16 )AsInk::AS_PROPERTY_BRUSHCOLOR );
        HashProperties.insert( "brushColor2", ( quint16 )AsInk::AS_PROPERTY_BRUSHCOLOR2 );
        HashProperties.insert( "brushGradientType", ( quint16 )AsInk::AS_PROPERTY_BRUSHGRADIENTTYPE );
        HashProperties.insert( "backgroundMode", ( quint16 )AsInk::AS_PROPERTY_BACKGROUNDMODE );
        HashProperties.insert( "backgroundColor", ( quint16 )AsInk::AS_PROPERTY_BACKGROUNDCOLOR );
    }

    return HashProperties;
}

void AsInk::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

// Properties.
AsInk::AsEnumInkType AsInk::asGetInkType( void ) const
{
    return m_InkType;
}

void AsInk::asSetInkType( AsInk::AsEnumInkType inkType )
{
    m_InkType = inkType;

    if( m_InkType == AsInk::AS_INKTYPE_HIGHLIGHT )
    {
        // hard code highlight type to be half transulcent
        // we have all but not sure about background yet. Revisit
        this->asSetAlpha(AsInk::AS_COLOR_PEN, m_v3_HighLightAlpha );
        this->asSetAlpha(AsInk::AS_COLOR_BRUSH, m_v3_HighLightAlpha );
    }
    else if (AsInk::AS_INKTYPE_NORMAL == m_InkType)
    {
        this->asSetAlpha(AsInk::AS_COLOR_PEN, 255);
        this->asSetAlpha(AsInk::AS_COLOR_BRUSH, 255);
    }
}

unsigned int AsInk::asGetPenWidth( void ) const
{
    return m_nPenWidth;
}

void AsInk::asSetPenWidth( unsigned int nWidth )
{
    m_nPenWidth = nWidth;
    m_bPenDirty = true;
}

AsInk::AsEnumPenStyle AsInk::asGetPenStyle( void ) const
{
    return m_PenStyle;
}

void AsInk::asSetPenStyle( AsInk::AsEnumPenStyle penStyle )
{
    m_PenStyle = penStyle;
    m_bPenDirty = true;
}

AsInk::AsEnumPenCapStyle AsInk::asGetPenCapStyle( void ) const
{
    return m_PenCapStyle;
}

void AsInk::asSetPenCapStyle( AsInk::AsEnumPenCapStyle capStyle )
{
    m_PenCapStyle = capStyle;
    m_bPenDirty = true;
}

AsInk::AsEnumPenJoinStyle AsInk::asGetPenJoinStyle( void ) const
{
    return m_PenJoinStyle;
}

void AsInk::asSetPenJoinStyle( AsInk::AsEnumPenJoinStyle joinStyle )
{
    m_PenJoinStyle = joinStyle;
    m_bPenDirty = true;
}

const QColor& AsInk::asGetPenColor( void ) const
{
    return m_PenColor;
}

void AsInk::asSetPenColor( const QColor& color )
{
    m_PenColor = color;
    m_bPenDirty = true;
}

AsInk::AsEnumBrushStyle AsInk::asGetBrushStyle( void ) const
{
    return m_BrushStyle;
}

void AsInk::asSetBrushStyle( AsInk::AsEnumBrushStyle brushStyle )
{
    m_BrushStyle = brushStyle;
    m_bBrushDirty = true;
}

const QColor& AsInk::asGetBrushColor( void ) const
{
    return m_BrushColor;
}

void AsInk::asSetBrushColor( const QColor& color )
{
    m_BrushColor = color;
    m_bBrushDirty = true;
}

const QColor& AsInk::asGetBrushColor2( void ) const
{
    return m_BrushColor2;
}

void AsInk::asSetBrushColor2( const QColor& color )
{
    m_BrushColor2 = color;
    m_bBrushDirty = true;
}

AsInk::AsEnumBrushGradientType AsInk::asGetBrushGradientType( void ) const
{
    return m_BrushGradientType;
}

void AsInk::asSetBrushGradientType( AsInk::AsEnumBrushGradientType gradient )
{
    m_BrushGradientType = gradient;
    m_bBrushDirty = true;
}

//WARNING - Brush image is not a streamable property.
//const QImage& AsInk::asGetBrushImage( void ) const
//{
//    return m_BrushImage;
//}
////WARNING - Brush image is not a streamable property.
//void AsInk::asSetBrushImage( const QImage& image )
//{
//    m_BrushImage = image;
//    m_bBrushDirty = true;
//}
//
//int AsInk::asGetBrushAlpha( void )
//{
//    return this->m_BrushColor.alpha();
//}

AsInk::AsEnumBackgroundMode AsInk::asGetBackgroundMode( void ) const
{
    return m_BackgroundMode;
}

void AsInk::asSetBackgroundMode( AsInk::AsEnumBackgroundMode background )
{
    m_BackgroundMode = background;
}

const QColor& AsInk::asGetBackgroundColor( void ) const
{
    return m_BackgroundColor;
}

void AsInk::asSetBackgroundColor( const QColor& color )
{
    m_BackgroundColor = color;
}

void AsInk::asSetAlpha( AsEnumColors color, int alpha )
{
    // The owness is on the caller to set the ink type to highlighter first!
    if( this->m_InkType == AsInk::AS_INKTYPE_HIGHLIGHT )
    {
        if(alpha != 255 && alpha != 0 )
        {
            qreal pcent = (qreal) alpha / 255.0;
            qreal newAlpha = (qreal) m_v3_HighLightAlpha * pcent;
            alpha = ( int ) newAlpha;
            if( alpha < 0)
            {
                alpha = 0;
            }
            else if ( alpha > 255)
            {
                alpha = 255;
            }
        }
        else
        {
            if( alpha != 0 ) alpha = m_v3_HighLightAlpha;
        }
    }

    switch ( color )
    {
        case AsInk::AS_COLOR_ALL:

            this->m_BackgroundColor.setAlpha( alpha );
            this->m_PenColor.setAlpha( alpha );
            this->m_BrushColor.setAlpha( alpha );
            this->m_BrushColor2.setAlpha( alpha );
            m_bPenDirty = true;
            m_bBrushDirty = true;
            break;

        case AsInk::AS_COLOR_BACKGROUND:
            this->m_BackgroundColor.setAlpha( alpha );
            break;

        case AsInk::AS_COLOR_BRUSH:
            this->m_BrushColor.setAlpha( alpha );
            this->m_BrushColor2.setAlpha( alpha );
            m_bBrushDirty = true;
            break;

        case AsInk::AS_COLOR_PEN:
            this->m_PenColor.setAlpha( alpha );
            m_bPenDirty = true;
            break;
    }
}

// Interface...
//const QPen& AsInk::asGetPen( void )
//{
//    if ( m_bPenDirty )
//    {
//        m_Pen.setWidth( m_nPenWidth );
//        m_Pen.setStyle( ( Qt::PenStyle ) m_PenStyle );
//        m_Pen.setCapStyle( ( Qt::PenCapStyle ) m_PenCapStyle );
//        m_Pen.setJoinStyle( ( Qt::PenJoinStyle ) m_PenJoinStyle );
//        m_Pen.setColor( m_PenColor );
//        m_bPenDirty = false;
//    }
//    return m_Pen;
//}
//
//const QBrush& AsInk::asGetBrush( void )
//{
//    if ( m_bBrushDirty )
//    {
//        m_bBrushDirty = false;
//
//        if ( this->m_BrushStyle == AsInk::AS_BRUSHSTYLE_GRADIENT )
//        {
//            AsBrushDesc brushDesc( m_BrushGradientType, m_BrushColor, m_BrushColor2 );
//            m_Brush = brushDesc.asCreateBrush();
//        }
//        else
//        {
//            m_Brush.setStyle( ( Qt::BrushStyle ) m_BrushStyle );
//            m_Brush.setColor( m_BrushColor );
//
//            if( this->m_BrushStyle == AsInk::AS_BRUSHSTYLE_TEXTURE )
//                m_Brush.setTextureImage( m_BrushImage );
//        }
//    }
//    return m_Brush;
//}

void AsInk::asSetTranslucency(int nAlpha)
{
    m_PenColor.setAlpha(nAlpha);

    m_bPenDirty = true;

    m_BrushColor.setAlpha(nAlpha);
    m_BrushColor2.setAlpha(nAlpha);

    m_bBrushDirty = true;
}

//AsBrushDesc AsInk::asGetBrushDesc() const
//{
//    return AsBrushDesc( m_BrushStyle, m_BrushGradientType, m_BrushColor, m_BrushColor2 );
//}

//void AsInk::asSetBrushDesc( const AsBrushDesc& brushDesc )
//{
//    asSetBrushStyle( brushDesc.Style );
//    asSetBrushGradientType( brushDesc.GradientType );
//    asSetBrushColor( brushDesc.Colour1 );
//    asSetBrushColor2( brushDesc.Colour2 );
//}

void AsInk::asSetHighlighterAlpha( int alpha )
{
    m_v3_HighLightAlpha = alpha;
}

QString AsInk::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsInk::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsInk::typeName()
{
    return "ink";
}
