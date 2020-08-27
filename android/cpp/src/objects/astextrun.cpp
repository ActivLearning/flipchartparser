/** @file astextrun.cpp
 * Responsible for maintaining text items.
 * Copyright (C) 2006-2010 Promethean Limited. All Rights Reserved.
 */

#include "astextrun.h"
#include <QByteArray>


AsTextRun::AsTextRun( AsFactory *pAsFactory )
: AsObject( pAsFactory ),
  m_bMisspelltWord(false),
  m_bTextRunDirty(false),
  m_bulletStyle(AsTextRun::AS_TEXT_LISTUNKNOWN)
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_TEXTRUN );
    m_polygonList.clear();
}

AsTextRun::AsTextRun()
: AsObject( NULL ),
  m_bMisspelltWord(false),
  m_bTextRunDirty(false),
  m_bulletStyle(AsTextRun::AS_TEXT_LISTUNKNOWN)
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_TEXTRUN );
    m_polygonList.clear();
}

AsTextRun::~AsTextRun()
{
}

QHash<QString, quint16>& AsTextRun::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
      //  HashProperties.insert( "asDateTimeCreated", ( quint16 )AsTextRun::AS_PROPERTY_DATETIMECREATED );

        // From AsTextRun...
        HashProperties.insert( "asBoundingRect", ( quint16 )AsTextRun::AS_PROPERTY_BOUNDING_RECT );
        HashProperties.insert( "asTextPos", ( quint16 )AsTextRun::AS_PROPERTY_TEXTPOS );
        HashProperties.insert( "asTextColor", ( quint16 )AsTextRun::AS_PROPERTY_TEXTCOLOR );
        HashProperties.insert( "asText", ( quint16 )AsTextRun::AS_PROPERTY_TEXT );
        HashProperties.insert( "asFontFamily", ( quint16 )AsTextRun::AS_PROPERTY_FONTFAMILY );
        HashProperties.insert( "asFontSize", ( quint16 )AsTextRun::AS_PROPERTY_FONTSIZE );
        HashProperties.insert( "asFontWeight", ( quint16 )AsTextRun::AS_PROPERTY_FONTWEIGHT );
        HashProperties.insert( "asFontItalic", ( quint16 )AsTextRun::AS_PROPERTY_FONTITALIC );
        HashProperties.insert( "asFontUnderline", ( quint16 )AsTextRun::AS_PROPERTY_FONTUNDERLINE );
        HashProperties.insert( "asFontStrikeout", ( quint16 )AsTextRun::AS_PROPERTY_FONTSTRIKEOUT );
        HashProperties.insert( "asPolygonList", ( quint16 )AsTextRun::AS_PROPERTY_POLYGONLIST );

        HashProperties.insert( "asBulletType", ( quint16 )AsTextRun::AS_PROPERTY_BULLETTYPE );
        HashProperties.insert( "asBulletPosition", ( quint16 )AsTextRun::AS_PROPERTY_BULLETPOSITION );
        HashProperties.insert( "asBulletText", ( quint16 )AsTextRun::AS_PROPERTY_BULLETTEXT );

        HashProperties.insert( "asMisspelltWord", ( quint16 )AsTextRun::AS_PROPERTY_MISSPELLTWORD );
    }

    return HashProperties;
}

void AsTextRun::asSetTextRun(  const QPointF & TextPos,
                               const QString & Text ,
                               const QString & FontFamily ,
                               const qreal & FontSize ,
                               const int & FontWeight ,
                               const bool & Italic,
                               const bool & UnderLine,
                               const bool & Strikeout ,
                               const QColor & TextColor,
                               AsTextRun::AsEnumTextListFormat bulletStyle,
                               QRectF bulletPosition)
{
    this->m_textPos = TextPos;
    this->m_sText = Text;
    this->m_sFontFamily = FontFamily;
    this->m_nFontSize = FontSize;
    this->m_nFontWeight = FontWeight;
    this->m_bFontItalic = Italic;
    this->m_bFontUnderline = UnderLine;
    this->m_bFontStrikeOut = Strikeout;
//    this->m_cTextColor = TextColor;

    this->m_bulletStyle = bulletStyle;
    this->m_bulletPosition = bulletPosition;

    m_bTextRunDirty = true;
}

AsTextRun::AsTextRun( const AsTextRun& textrun ) : AsObject( textrun )
{
    this->asCopy( textrun );
}

void AsTextRun::operator= ( const AsTextRun& textrun )
{
    AsObject::operator = ( textrun );
    this->asCopy( textrun );
}

bool AsTextRun::operator== ( const AsTextRun& txtRun )
{
        bool bRetVal = true;

        if(  this->asGetTextPos().x() != txtRun.asGetTextPos().x() )
            bRetVal = false;
        else if( this->m_sText != txtRun.m_sText )
            bRetVal = false;
//        else if( this->m_fCachedFont != txtRun.m_fCachedFont )
//            bRetVal = false;

        return bRetVal;
}


void AsTextRun::asCopy( const AsTextRun& textrun )
{
    m_sText = textrun.m_sText;
    m_sFontFamily = textrun.m_sFontFamily;
    m_nLineNumber = textrun.m_nLineNumber;
    m_eAlignment = textrun.m_eAlignment;
    m_textPos = textrun.m_textPos;
    m_nFontSize = textrun.m_nFontSize;
    m_nFontWeight = textrun.m_nFontWeight;
    m_bFontItalic = textrun.m_bFontItalic;
    m_bFontUnderline = textrun.m_bFontUnderline;
    m_bFontStrikeOut = textrun.m_bFontStrikeOut;
  //  m_eValign = textrun.m_eValign;
  //  m_cTextColor = textrun.m_cTextColor;
    m_boundingRect = textrun.m_boundingRect;
    m_bulletStyle = textrun.m_bulletStyle;
    m_bulletText = textrun.m_bulletText;
    m_bulletPosition = textrun.m_bulletPosition;
    m_bMisspelltWord = textrun.m_bMisspelltWord;

//    this->m_fCachedFont.setFamily( this->m_sFontFamily );
//    this->m_fCachedFont.setPointSizeF( this->m_nFontSize );
//    this->m_fCachedFont.setWeight( this->m_nFontWeight );
//    this->m_fCachedFont.setItalic( this->m_bFontItalic );
//    this->m_fCachedFont.setUnderline( this->m_bFontUnderline );
//    this->m_fCachedFont.setStrikeOut( this->m_bFontStrikeOut );
//    this->m_painterPath = textrun.m_painterPath;
}


//const QFont & AsTextRun::asGetCachedFont ( void ) const
//{
//    if( m_bTextRunDirty )
//    {
////        m_fCachedFont.setFamily( m_sFontFamily );
////        m_fCachedFont.setPointSizeF( m_nFontSize );
////        m_fCachedFont.setWeight( m_nFontWeight );
////        m_fCachedFont.setItalic( m_bFontItalic );
////        m_fCachedFont.setUnderline( m_bFontUnderline );
////        m_fCachedFont.setStrikeOut( m_bFontStrikeOut );
//        m_bTextRunDirty = false;
//    }
//   // return m_fCachedFont;
//}

void AsTextRun::asSetCachedFont( const QFont &font )
{
//    m_sFontFamily = font.family();
//    m_nFontSize = font.pointSizeF();
//    m_nFontWeight = font.weight();
//    m_bFontItalic = font.italic();
//    m_bFontUnderline = font.underline();
//    m_bFontStrikeOut = font.strikeOut();
//    m_fCachedFont = font;
//
//    m_bTextRunDirty = true;
}



//const QColor & AsTextRun::asGetTextColor( void ) const
//{
//   // return this->m_cTextColor;
//}

const QPointF & AsTextRun::asGetTextPos( void ) const
{
    return this->m_textPos;
}

const QString & AsTextRun::asGetText( void ) const
{
    return this->m_sText;
}

const QString& AsTextRun::asGetFontFamily( void ) const
{
    return m_sFontFamily;
}

double AsTextRun::asGetFontSize( void ) const
{
    return (double)m_nFontSize;
}

int AsTextRun::asGetFontWeight( void ) const
{
    return m_nFontWeight;
}

bool AsTextRun::asIsItalic( void ) const
{
    return m_bFontItalic;
}

bool AsTextRun::asIsUnderline( void ) const
{
    return m_bFontUnderline;
}

bool AsTextRun::asIsStrikeout( void ) const
{
    return m_bFontStrikeOut;
}

void AsTextRun::asSetTextColor( QColor &colour )
{
  //  m_cTextColor = colour;
}

void AsTextRun::asSetTextPos( const QPointF &pos )
{
    m_textPos = pos;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetText( QString &text )
{
    m_sText = text;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetFontFamily( QString &fontFamily )
{
    m_sFontFamily = fontFamily;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetFontSize( double fontSize )
{
    m_nFontSize = (qreal)fontSize;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetFontWeight( int fontWeight )
{
    m_nFontWeight = fontWeight;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetItalic( bool italic )
{
    m_bFontItalic = italic;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetUnderline( bool underline )
{
    m_bFontUnderline = underline;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetStrikeout( bool strikeout )
{
    m_bFontStrikeOut = strikeout;
    m_bTextRunDirty = true;
}

void AsTextRun::asResetPropertyIndex( void )
{
   // AsObject::asSetPropertyIterator( &m_lProperties );
}


int AsTextRun::asGetLineNumber()
{
    return m_nLineNumber;
}

void AsTextRun::asSetLineNumber( int nLineNumber )
{
    m_nLineNumber = nLineNumber;
}

bool AsTextRun::asBuildPainterPath() const
{
    bool bRetVal = true;

//    //if( m_bTextRunDirty ) // (BRS removed this check - else painterpath never generated. Then, text fill breaks)
//    {
//        // rebuild font first
//        m_fCachedFont.setFamily( m_sFontFamily );
//        m_fCachedFont.setPointSizeF( m_nFontSize );
//        m_fCachedFont.setWeight( m_nFontWeight );
//        m_fCachedFont.setItalic( m_bFontItalic );
//        m_fCachedFont.setUnderline( m_bFontUnderline );
//        m_fCachedFont.setStrikeOut( m_bFontStrikeOut );
//
//        // check for empty string or if text is not glyphable i.e a bitmap font.
//        if( (m_sText.isEmpty()) || (m_fCachedFont.styleStrategy() == QFont::PreferBitmap))
//            bRetVal = false;
//        else
//        {
//            m_painterPath.addText(m_textPos, m_fCachedFont, m_sText);
//
//            QVector<QPolygonF> polygons = m_painterPath.toSubpathPolygons().toVector();
//
//            // FIXME : have to do an element by element copy because there is currently not way
//            // to downcast from QPolygonF to an AsPointFArray
//            int nSize = polygons.size();
//
//            for( int i = 0; i < nSize; i++ )
//            {
//                QVector<QPointF> polygon = polygons[i];
//                AsPointFArray arr;
//                for( int j = 0; j < polygon.size(); j++ )
//                {
//                    arr.append(polygon[j]);
//                }
//
//                m_polygonList.append(arr);
//            }
//        }
//
//        m_bTextRunDirty = false;
//    }

    return bRetVal;
}

//const QPainterPath & AsTextRun::asGetPainterPath() const
//{
//    // if( m_bTextRunDirty ) // (BRS removed this check - else painterpath never generated. Then, text fill breaks)
//    {
//        asBuildPainterPath();
//        m_bTextRunDirty = false;
//    }
//
//    return m_painterPath;
//}

const AsPointFArrayArray & AsTextRun::asGetPolygonList() const
{
    // ensure we don't attempt to build the initial painter path here
    // as we are not guaranteed to have all the required properties set at this point of the
    // serialissation process
//    if( m_bTextRunDirty && !m_painterPath.isEmpty())
//    {
//        asBuildPainterPath();
//    }

    return m_polygonList;
}

void AsTextRun::asSetPolygonList(AsPointFArrayArray & polygons)
{
    m_polygonList = polygons;

    // build painter path from polygon list
    asBuildPathFromPolygons();
}

void AsTextRun::asBuildPathFromPolygons()
{
    for( int i = 0; i < m_polygonList.size(); i++ )
    {
       // m_painterPath.addPolygon(m_polygonList[i]);
    }
}



AsTextRun::AsEnumTextListFormat AsTextRun::asGetBulletType()const
{
    return m_bulletStyle;
}

void AsTextRun::asSetBulletType(AsTextRun::AsEnumTextListFormat type)
{
    m_bulletStyle = type;
    m_bTextRunDirty = true;
}

void AsTextRun::asSetBulletText(const QString& bulletText)
{
    m_bulletText = bulletText;
}

const QString& AsTextRun::asGetBulletText()const
{
    return m_bulletText;
}

const QRectF & AsTextRun::asGetBulletPosition() const
{
    return m_bulletPosition;
}

void AsTextRun::asSetBulletPosition( QRectF & rect)
{
    m_bulletPosition = rect;
}

//void AsTextRun::asCalculateBulletPosition(const QSizeF&, const QFont& bulletFont, bool rightToLeft)
//{
//    // calculate the bounding rect
//   // QFontMetricsF metrics( m_fCachedFont );
//    qreal xPos = 0.0;
//    if( rightToLeft )
//    {
//        asCalculateBoundingRect();
//        // The magic number in the following line should be replaced with the right end offset when the right to left text edit lays out
//        // indents properly, check AsPaintEngineCaptureText::drawTextItem if you change this value
//        xPos = m_boundingRect.right() + 80;
//    }
//    else
//    {
//        xPos = m_textPos.x();
//    }
//    qreal yPos = m_textPos.y();
//  //  qreal yadjust = metrics.ascent();
//
//    QSizeF size;
//    if( m_bulletStyle == AsTextRun::AS_TEXT_LISTDECIMAL  ||
//        m_bulletStyle == AsTextRun::AS_TEXT_LISTLOWERALPHA ||
//        m_bulletStyle == AsTextRun::AS_TEXT_LISTUPPERALPHA)
//    {
////        QFontMetricsF bulletFontMetrics( bulletFont );
////        size.setWidth(bulletFontMetrics.width(m_bulletText));
////        size.setHeight(bulletFontMetrics.height());
////
////        xPos = xPos - (1.3 * size.width());
////
////        yPos = (yPos - yadjust);
//    }
//    else
//    {
//        // NN:remove this once we receive fix from Qt for averageCharWidth
////#ifdef Q_OS_WIN
////        size.setWidth(metrics.averageCharWidth() * 0.9);
////#else
////        size.setWidth(metrics.lineSpacing() / 3);
////#endif
//
////        size.setHeight(size.width());
////
////        xPos = xPos - (1.67 * size.width());
////
////        yPos = (yPos - yadjust + (metrics.height()-size.height())/2 );
//    }
//
//    QRectF rect(QPointF(xPos,yPos), size);
//
//    asSetBulletPosition(rect);
//}

qreal AsTextRun::asGetSnapOffset()
{
  //  QFontMetricsF metrics(m_fCachedFont);
    qreal dAscent=0.0f;
    return dAscent;
}

const AsRectF & AsTextRun::asGetBoundingRect() const
{
    return m_boundingRect;
}

void AsTextRun::asSetBoundingRect( AsRectF & rect)
{
    m_boundingRect = rect;
}

void AsTextRun::asCalculateBoundingRect(const QSizeF& bounds)
{
    Q_UNUSED(bounds);

    // calculate the bounding rect
   // QFontMetricsF metrics( m_fCachedFont );
    qreal nWidth = 0.0f;
    qreal nHeight = 0.0f;

    // need to align to top
    qreal yadjust = 0.0f;
    qreal xPos = m_textPos.x();

    //if(bounds.height() > 0 && !m_nLineNumber)
    //    nHeight = bounds.height();

    AsRectF rect( xPos, m_textPos.y() - yadjust, nWidth, nHeight );

    this->asSetBoundingRect(rect);
}


// A simple function.
static int __toInt__( bool v )
{
    if( v ){ return 1; }
    return 0;
}


// Gets the byte array for this text run.
QByteArray AsTextRun::asToByteArray() const
{
    QByteArray ret;

    ret.append( this->m_sText.toUtf8() );
    ret.append( this->m_sFontFamily.toUtf8() );
    ret.append( QByteArray::number( this->m_nLineNumber ) );
    ret.append( QByteArray::number( this->m_nFontWeight ) );
    ret.append( QByteArray::number( this->m_nFontSize ) );
    ret.append( QByteArray::number( this->m_textPos.x() ) );
    ret.append( QByteArray::number( this->m_textPos.y() ) );
  //  ret.append( QByteArray::number( this->m_cTextColor.value() ) );

    ret.append( QByteArray::number( __toInt__( this->m_bFontItalic ) ) );
    ret.append( QByteArray::number( __toInt__( this->m_bFontUnderline ) ) );
    ret.append( QByteArray::number( __toInt__( this->m_bFontStrikeOut ) ) );
  //  ret.append( QByteArray::number( ( int )this->m_eValign ) );
    ret.append( QByteArray::number( ( int )this->m_eAlignment ) );

    return ret;
}


bool AsTextRun::asIsMisspelltWord(void) const
{
    return m_bMisspelltWord;
}

void AsTextRun::asSetMisspelltWord(bool misspellt)
{
    m_bMisspelltWord = misspellt;
}

QString AsTextRun::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsTextRun::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsTextRun::typeName()
{
    return "textRun";
}


