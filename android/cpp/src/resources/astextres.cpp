/****************************************************************************
 ** Copyright 2006 Promethean Technologies Group Limited
 ****************************************************************************/
// Implements the AsTextRes class.


#include <QTextCodec>
#include <QFile>
#include <QtDebug>



#include "astextres.h"






QString AsTextRes::m_HighlightStartTag = "<span style=\" color:#ff0001;\">";
QString AsTextRes::m_HighlightEndTag = "</span>";    

namespace
{
    const QList< QChar > nonLeftSideJoiningArabicCharacters = QList< QChar >() << QChar( 0x0621 ) << QChar( 0x0622 ) << QChar( 0x0623 ) << QChar( 0x0624 ) << QChar( 0x0625 ) << QChar( 0x0627 ) << QChar( 0x0629 ) << QChar( 0x062F )
                                                                               << QChar( 0x0630 ) << QChar( 0x0631 ) << QChar( 0x0632 ) << QChar( 0x0648 ) << QChar( 0x0649 ) << QChar( 0x0672 ) << QChar( 0x0673 ) << QChar( 0x0675 )
                                                                               << QChar( 0x0676 ) << QChar( 0x0677 ) << QChar( 0x0688 ) << QChar( 0x0689 ) << QChar( 0x0690 ) << QChar( 0x0691 ) << QChar( 0x0692 ) << QChar( 0x0693 )
                                                                               << QChar( 0x0694 ) << QChar( 0x0695 ) << QChar( 0x0696 ) << QChar( 0x0697 ) << QChar( 0x0698 ) << QChar( 0x0699 ) << QChar( 0x06C0 ) << QChar( 0x06C2 )
                                                                               << QChar( 0x06C3 ) << QChar( 0x06C4 ) << QChar( 0x06C5 ) << QChar( 0x06C6 ) << QChar( 0x06C7 ) << QChar( 0x06C8 ) << QChar( 0x06C9 ) << QChar( 0x06CA )
                                                                               << QChar( 0x06CB ) << QChar( 0x06CD ) << QChar( 0x06D2 ) << QChar( 0x06D3 );

    QHash< QChar, QChar > startArabicCharacters;
    QHash< QChar, QChar > midArabicCharacters;
    QHash< QChar, QChar > endArabicCharacters;

    const int ARABIC_TEXT_CLEARANCE_FRONT = 1;
    const int ARABIC_TEXT_CLEARANCE_BACK = 1;
    const int ARABIC_TEXT_CLEARANCE = ARABIC_TEXT_CLEARANCE_FRONT + ARABIC_TEXT_CLEARANCE_BACK;
};

AsTextRes::AsTextRes( AsFactory *pAsFactory ) 
  : AsResource( pAsFactory ),
    m_sText(""),
    m_nDPIX(0),
    m_nDPIY(0),
    m_bounds( QSize(0, 0) ),
    m_topOffset(0),
    m_nFrameWidth(0),
    m_nFrameHeight(0)
{
    asSetType( AsObject::AS_OBJECT_TEXTRES );

    // set up font defaults
  //  m_sDefaultFontFamily = AsApp::asInstance()->asGetUserSetting("DefaultFont", "Arial").toString();
  //  m_nDefaultFontSize = AsApp::asInstance()->asGetUserSetting("DefaultFontSize", 20).toInt();
  //  m_DefaultTextColor = QColor( AsApp::asInstance()->asGetUserSetting("DefaultTextColor", QVariant(QColor(Qt::black))).toString() );

    if( m_sDefaultFontFamily.isEmpty() )
    m_sDefaultFontFamily = "Arial";
    
    if( m_nDefaultFontSize == 0 )
    m_nDefaultFontSize = 20;

//    if( QApplication::isRightToLeft() )
//    {
//        asInitArabicCharacters();
//    }
}

AsTextRes::AsTextRes( const AsTextRes& res ) : AsResource( res )
{
    this->asCopy( res );
}

void AsTextRes::operator= ( const AsTextRes& res )
{
    AsResource::operator = ( res );
    this->asCopy( res );
}

void AsTextRes::asCopy( const AsTextRes& res )
{
 //   this->m_CachedTextRuns = res.asGetTextRunList();
    this->m_sText = res.asGetText();
    this->m_TextType = res.asGetTextType();
    this->m_sOriginalText = res.asGetOriginalText();
    this->m_OriginalTextType = res.asGetOriginalTextType();
    this->m_nDPIX = res.asGetDPIX();
    this->m_nDPIY = res.asGetDPIY();
    this->m_sDefaultFontFamily = res.asGetDefaultFontFamily();
    this->m_nDefaultFontSize = res.asGetDefaultFontSize();
    this->m_bounds = res.asGetBounds();
    this->m_topOffset = res.m_topOffset;
    this->m_nFrameWidth = res.m_nFrameWidth;
    this->m_nFrameHeight = res.m_nFrameHeight;
}

AsTextRes::~AsTextRes()
{
}

void AsTextRes::asInitArabicCharacters()
{
    endArabicCharacters.insert( QChar( 0x0623 ), QChar( 0xFE84 ) );
    endArabicCharacters.insert( QChar( 0x0627 ), QChar( 0xFE8E ) );
    endArabicCharacters.insert( QChar( 0x0628 ), QChar( 0xFE90 ) );
    endArabicCharacters.insert( QChar( 0x062A ), QChar( 0xFE96 ) );
    endArabicCharacters.insert( QChar( 0x062B ), QChar( 0xFE9A ) );
    endArabicCharacters.insert( QChar( 0x062C ), QChar( 0xFE9E ) );
    endArabicCharacters.insert( QChar( 0x062D ), QChar( 0xFEA2 ) );
    endArabicCharacters.insert( QChar( 0x062E ), QChar( 0xFEA6 ) );
    endArabicCharacters.insert( QChar( 0x062F ), QChar( 0xFEAA ) );
    endArabicCharacters.insert( QChar( 0x0630 ), QChar( 0xFEAC ) );
    endArabicCharacters.insert( QChar( 0x0631 ), QChar( 0xFEAE ) );
    endArabicCharacters.insert( QChar( 0x0632 ), QChar( 0xFEB0 ) );
    endArabicCharacters.insert( QChar( 0x0633 ), QChar( 0xFEB2 ) );
    endArabicCharacters.insert( QChar( 0x0634 ), QChar( 0xFEB6 ) );
    endArabicCharacters.insert( QChar( 0x0635 ), QChar( 0xFEBA ) );
    endArabicCharacters.insert( QChar( 0x0636 ), QChar( 0xFEBE ) );
    endArabicCharacters.insert( QChar( 0x0637 ), QChar( 0xFEC2 ) );
    endArabicCharacters.insert( QChar( 0x0638 ), QChar( 0xFEC6 ) );
    endArabicCharacters.insert( QChar( 0x0639 ), QChar( 0xFECA ) );
    endArabicCharacters.insert( QChar( 0x063A ), QChar( 0xFECE ) );
    endArabicCharacters.insert( QChar( 0x0641 ), QChar( 0xFED2 ) );
    endArabicCharacters.insert( QChar( 0x0642 ), QChar( 0xFED6 ) );
    endArabicCharacters.insert( QChar( 0x0643 ), QChar( 0xFEDA ) );
    endArabicCharacters.insert( QChar( 0x0644 ), QChar( 0xFEDE ) );
    endArabicCharacters.insert( QChar( 0x0645 ), QChar( 0xFEE2 ) );
    endArabicCharacters.insert( QChar( 0x0646 ), QChar( 0xFEE6 ) );
    endArabicCharacters.insert( QChar( 0x0647 ), QChar( 0xFEEA ) );
    endArabicCharacters.insert( QChar( 0x0648 ), QChar( 0xFEEE ) );
    endArabicCharacters.insert( QChar( 0x0649 ), QChar( 0xFEF0 ) );
    endArabicCharacters.insert( QChar( 0x064A ), QChar( 0xFEF2 ) );
    endArabicCharacters.insert( QChar( 0x0622 ), QChar( 0xFE82 ) );
    endArabicCharacters.insert( QChar( 0x0629 ), QChar( 0xFE94 ) );


    midArabicCharacters.insert( QChar( 0x0623 ), QChar( 0xFE84 ) ); //end character
    midArabicCharacters.insert( QChar( 0x0627 ), QChar( 0xFE8E ) ); //end character
    midArabicCharacters.insert( QChar( 0x0628 ), QChar( 0xFE92 ) );
    midArabicCharacters.insert( QChar( 0x062A ), QChar( 0xFE98 ) );
    midArabicCharacters.insert( QChar( 0x062B ), QChar( 0xFE9C ) );
    midArabicCharacters.insert( QChar( 0x062C ), QChar( 0xFEA0 ) );
    midArabicCharacters.insert( QChar( 0x062D ), QChar( 0xFEA4 ) );
    midArabicCharacters.insert( QChar( 0x062E ), QChar( 0xFEA8 ) );
    midArabicCharacters.insert( QChar( 0x062F ), QChar( 0xFEAA ) ); //end character
    midArabicCharacters.insert( QChar( 0x0630 ), QChar( 0xFEAC ) ); //end character
    midArabicCharacters.insert( QChar( 0x0631 ), QChar( 0xFEAE ) ); //end character
    midArabicCharacters.insert( QChar( 0x0632 ), QChar( 0xFEB0 ) ); //end character
    midArabicCharacters.insert( QChar( 0x0633 ), QChar( 0xFEB4 ) );
    midArabicCharacters.insert( QChar( 0x0634 ), QChar( 0xFEB8 ) );
    midArabicCharacters.insert( QChar( 0x0635 ), QChar( 0xFEBC ) );
    midArabicCharacters.insert( QChar( 0x0636 ), QChar( 0xFEC0 ) );
    midArabicCharacters.insert( QChar( 0x0637 ), QChar( 0xFEC4 ) );
    midArabicCharacters.insert( QChar( 0x0638 ), QChar( 0xFEC8 ) );
    midArabicCharacters.insert( QChar( 0x0639 ), QChar( 0xFECC ) );
    midArabicCharacters.insert( QChar( 0x063A ), QChar( 0xFED0 ) );
    midArabicCharacters.insert( QChar( 0x0641 ), QChar( 0xFED4 ) );
    midArabicCharacters.insert( QChar( 0x0642 ), QChar( 0xFED8 ) );
    midArabicCharacters.insert( QChar( 0x0643 ), QChar( 0xFEDC ) );
    midArabicCharacters.insert( QChar( 0x0644 ), QChar( 0xFEE0 ) );
    midArabicCharacters.insert( QChar( 0x0645 ), QChar( 0xFEE4 ) );
    midArabicCharacters.insert( QChar( 0x0646 ), QChar( 0xFEE8 ) );
    midArabicCharacters.insert( QChar( 0x0647 ), QChar( 0xFEEC ) );
    midArabicCharacters.insert( QChar( 0x0648 ), QChar( 0xFEEE ) ); //end character
    midArabicCharacters.insert( QChar( 0x064A ), QChar( 0xFEF4 ) );
    midArabicCharacters.insert( QChar( 0x0622 ), QChar( 0xFE82 ) ); //end character
    midArabicCharacters.insert( QChar( 0x0629 ), QChar( 0xFE94 ) ); //end character


    startArabicCharacters.insert( QChar( 0x0628 ), QChar( 0xFE91 ) );
    startArabicCharacters.insert( QChar( 0x062A ), QChar( 0xFE97 ) );
    startArabicCharacters.insert( QChar( 0x062B ), QChar( 0xFE9B ) );
    startArabicCharacters.insert( QChar( 0x062C ), QChar( 0xFE9F ) );
    startArabicCharacters.insert( QChar( 0x062D ), QChar( 0xFEA3 ) );
    startArabicCharacters.insert( QChar( 0x062E ), QChar( 0xFEA7 ) );
    startArabicCharacters.insert( QChar( 0x0633 ), QChar( 0xFEB3 ) );
    startArabicCharacters.insert( QChar( 0x0634 ), QChar( 0xFEB7 ) );
    startArabicCharacters.insert( QChar( 0x0635 ), QChar( 0xFEBB ) );
    startArabicCharacters.insert( QChar( 0x0636 ), QChar( 0xFEBF ) );
    startArabicCharacters.insert( QChar( 0x0637 ), QChar( 0xFEC3 ) );
    startArabicCharacters.insert( QChar( 0x0638 ), QChar( 0xFEC7 ) );
    startArabicCharacters.insert( QChar( 0x0639 ), QChar( 0xFECB ) );
    startArabicCharacters.insert( QChar( 0x063A ), QChar( 0xFECF ) );
    startArabicCharacters.insert( QChar( 0x0641 ), QChar( 0xFED3 ) );
    startArabicCharacters.insert( QChar( 0x0642 ), QChar( 0xFED7 ) );
    startArabicCharacters.insert( QChar( 0x0643 ), QChar( 0xFEDB ) );
    startArabicCharacters.insert( QChar( 0x0644 ), QChar( 0xFEDF ) );
    startArabicCharacters.insert( QChar( 0x0645 ), QChar( 0xFEE3 ) );
    startArabicCharacters.insert( QChar( 0x0646 ), QChar( 0xFEE7 ) );
    startArabicCharacters.insert( QChar( 0x0647 ), QChar( 0xFEEB ) );
    startArabicCharacters.insert( QChar( 0x064A ), QChar( 0xFEF3 ) );
}

QHash<QString, quint16>& AsTextRes::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsTextRes::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
        HashProperties.insert( "asOriginalType", AsTextRes::AS_PROPERTY_ORIGINALTYPE );
        HashProperties.insert( "asOriginalFilename", AsTextRes::AS_PROPERTY_ORIGINALFILENAME );

        // From AsTextRes...
        HashProperties.insert( "asTextRuns", ( quint16 )AsTextRes::AS_PROPERTY_TEXTRUNS );

        HashProperties.insert( "asText", AsTextRes::AS_PROPERTY_TEXT );
        HashProperties.insert( "asTextType", ( quint16 )AsTextRes::AS_PROPERTY_TEXT_TYPE );

        HashProperties.insert( "asOriginalText", AsTextRes::AS_PROPERTY_ORIGINAL_TEXT );
        HashProperties.insert( "asOriginalTextType", ( quint16 )AsTextRes::AS_PROPERTY_ORIGINAL_TEXT_TYPE );

        HashProperties.insert("asDPIX", ( quint16 )AsTextRes::AS_PROPERTY_DPIX );
        HashProperties.insert("asDPIY", ( quint16 )AsTextRes::AS_PROPERTY_DPIY );

    HashProperties.insert("asConversionOffset", AsTextRes::AS_PROPERTY_CONV_OFFSET );
    }

    return HashProperties;
}

const QByteArray& AsTextRes::asGetHashData( void )
{
    return m_HashData;
}

bool AsTextRes::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsTextRes::asComputeHashData( void )
{
    QString strBoundsText = "(" + QString::number(m_bounds.width()) + "," + QString::number(m_bounds.height()) + ")";
    QString strDefaultFontSize = QString::number(m_nDefaultFontSize);
   // QString strDefaultTextColor = m_DefaultTextColor.name();

    QString strHash;

    strHash += m_sText;
    strHash += strBoundsText;
    strHash += m_sOriginalText;
    strHash += m_sDefaultFontFamily;
    strHash += strDefaultFontSize;
  //  strHash += strDefaultTextColor;

    m_HashData = strHash.toUtf8();

    m_bHashDataDirty = false;
}

void AsTextRes::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

const QString& AsTextRes::asGetText( void ) const
{
    return m_sText;
}

void AsTextRes::asSetText( const QString& sText, bool bSizeToFit )
{
    m_sText = sText;
    m_bHashDataDirty = true;

    if ( bSizeToFit )
    m_bounds.setWidth( 0 );
}

//void AsTextRes::asBuildAddTextRun(const QPointF & TextPos,
//                  const QString & Text ,
//                  const QString & FontFamily ,
//                  const qreal & FontSize ,
//                  const int & FontWeight ,
//                  const bool & Italic,
//                  const bool & UnderLine,
//                  const bool & Strikeout ,
//                  const QColor & TextColor,
//                  AsTextRun::AsEnumTextListFormat bulletStyle,
//                  QRectF bulletPosition )
//{
//    AsTextRun TextRun;
//    TextRun.asSetTextRun( TextPos , Text , FontFamily , FontSize , FontWeight ,
//                          Italic , UnderLine , Strikeout , TextColor, bulletStyle, bulletPosition);
//    this->m_CachedTextRuns.append( TextRun );
//
//}

//const AsTextRunArray & AsTextRes::asGetTextRunList ( void ) const
//{
//    return this->m_CachedTextRuns;
//}
//
//void AsTextRes::asSetTextRunList( AsTextRunArray &textRuns )
//{
//    m_CachedTextRuns = textRuns;
//}

void AsTextRes::asImportText( const QString & sText, AsEnumTextType type )
{
    m_sOriginalText = sText;
    m_OriginalTextType = type;
    m_topOffset = 0;
    qreal topOffset;

    if( m_OriginalTextType == AS_V2_ALLTEXT_RTF )
    {
        // convert text from rtf to html
        //m_sText = m_RTFtoHTMLConverter.asConvert(sText, &topOffset);
		m_topOffset = topOffset;
    }
    else
    {
        // may need a converter for QT3 html to QT4 html here
        m_sText = sText;
    }

    m_TextType = AS_INSPIRE_QT4_HTML;

    // invalidate text run list
   // m_CachedTextRuns.clear();
}

void AsTextRes::asCreateTextRuns( bool bAdjustHeightToFit, bool bForceWidth )
{
    // don't attempt to create text runs for an empty string.
    if( m_sText.isEmpty() )
        return;

    m_bHashDataDirty = true;

    // clear previous text runs

}

//void AsTextRes::asSwapBrackets(QList<AsTextRun*>* pTextRuns )
//{
//    for( int i=0 ; i < pTextRuns->count() ; i++ )
//    {
//        QString bracketTest = pTextRuns->at(i)->asGetText();
//
//        qDebug() << "bracketTest is : " << bracketTest;
//        QRegExp bracketsOrSpecials("[(){}[\\]!\"�$%\\^&*_\\-\\+=;:'@#~|\\\\,<>./? ]");
//
//        if(bracketTest.contains(bracketsOrSpecials))
//        {
//            //if only brackets reorder the characters
//            QRegExp notBracketsOrSpecials("[^(){}[\\]!\"�$%\\^&*_\\-\\+=;:'@#~|\\\\,<>./? ]");
//
//            int length = bracketTest.length();
//            if( length > 1 )
//            {
//                if(bracketTest.contains(notBracketsOrSpecials))
//                {
//                    //mixture of brackets and characters, leave alone
//                    continue;
//                }
//                else
//                {
//                    qDebug() << "all brackets, reordering";
//                    QString reordered;
//                    for(int k=length-1; k>=0; k--)
//                    {
//                        reordered.append(bracketTest[k]);
//                    }
//                    bracketTest = reordered;
//                    qDebug() << "bracketTest reordered is : " << bracketTest;
//                }
//            }
//
//            for(int j=0; j < bracketTest.length(); j++)
//            {
//                QChar oneChar = bracketTest[j];
//                if(oneChar == '(')
//                {
//                    qDebug() << "found (, bracketTest before : " << bracketTest;
//                    bracketTest[j] = ')';
//                    qDebug() << ", bracketTest after : " << bracketTest;
//                }
//                else if(oneChar == ')')
//                {
//                    qDebug() << "found ), bracketTest before : " << bracketTest;
//                    bracketTest[j] = '(';
//                    qDebug() << ", bracketTest after : " << bracketTest;
//                }
//                else if(oneChar == '[')
//                {
//                    qDebug() << "found [, bracketTest before : " << bracketTest;
//                    bracketTest[j] = ']';
//                    qDebug() << ", bracketTest after : " << bracketTest;
//                }
//                else if(oneChar == ']')
//                {
//                    qDebug() << "found ], bracketTest before : " << bracketTest;
//                    bracketTest[j] = '[';
//                    qDebug() << ", bracketTest after : " << bracketTest;
//                }
//                else if(oneChar == '{')
//                {
//                    qDebug() << "found {, bracketTest before : " << bracketTest;
//                    bracketTest[j] = '}';
//                    qDebug() << ", bracketTest after : " << bracketTest;
//                }
//                else if(oneChar == '}')
//                {
//                    qDebug() << "found }, bracketTest before : " << bracketTest;
//                    bracketTest[j] = '{';
//                    qDebug() << ", bracketTest after : " << bracketTest;
//                }
//            }
//
//            pTextRuns->at(i)->asSetText(bracketTest);
//        }
//    }
//}

const AsTextRes::AsEnumTextType & AsTextRes::asGetTextType( void ) const
{
    return m_TextType;
}

void AsTextRes::asSetTextType( AsEnumTextType type)
{
    m_TextType = type;
}


const QString& AsTextRes::asGetOriginalText( void ) const
{
    return m_sOriginalText;
}
        
void AsTextRes::asSetOriginalText( const QString& text)
{
    m_sOriginalText = text;
}

        
const AsTextRes::AsEnumTextType & AsTextRes::asGetOriginalTextType( void ) const
{
    return m_OriginalTextType;
}
        
void AsTextRes::asSetOriginalTextType( AsEnumTextType type)
{
    m_OriginalTextType = type;
}


void AsTextRes::asSetDPIX(const int & nDPIX )
{
    m_nDPIX = nDPIX;
}

const int & AsTextRes::asGetDPIX( void ) const
{
    return m_nDPIX;
}

void AsTextRes::asSetDPIY(const int & nDPIY )
{
    m_nDPIY = nDPIY;
}

const int & AsTextRes::asGetDPIY( void ) const
{
    return m_nDPIY;
}

QString AsTextRes::asGetWordAtPosition(const QPointF &pos)
{
//    QTextEdit textEdit;
//    textEdit.setHtml(m_sText);
//
//    // get root frame for document and remove padding
//    QTextFrame * rootFrame = textEdit.document()->rootFrame();
//    QTextFrameFormat format;
//    format.setMargin( 0 );
//    format.setPadding( 0 );
//    format.setBorder( 0 );
//
//    rootFrame->setFrameFormat( format );
//
//    if( m_bounds.width() > 0 )
//    {
//        textEdit.setLineWrapMode(QTextEdit::FixedPixelWidth);
//    textEdit.setLineWrapColumnOrWidth( m_bounds.width() );
//    }
//
//    //// dummy call to force a re-layout of the document
//    //int width = textEdit.lineWrapColumnOrWidth();
//    //textEdit.setLineWrapColumnOrWidth(width);
//
//    QTextDocument *doc = textEdit.document();
//    AsGraphicsTextItem::asUpdateIndentWidth( *doc );
//
//    QAbstractTextDocumentLayout * pLayout = doc->documentLayout();
//
//    int cursorPos = pLayout->hitTest(pos,Qt::FuzzyHit);
//
//    if (cursorPos == -1)
//        return QString("");
//
//    QTextCursor c(doc);
//    c.setPosition(cursorPos);
//
//    c.select(QTextCursor::WordUnderCursor);
//
//    QTextCharFormat tcf = c.charFormat();
//    QTextDocumentFragment frag = c.selection();
//
//    QTextEdit tempTextEdit;
//    tempTextEdit.setHtml(frag.toHtml());
//    tempTextEdit.selectAll();
//    tempTextEdit.setCurrentCharFormat(tcf);

    QString sHtml ; // combined text in Html
   
    return sHtml;
}


        
const QString & AsTextRes::asGetDefaultFontFamily() const
{
    return m_sDefaultFontFamily;
}
        
void AsTextRes::asSetDefaultFontFamily(const QString & sFontFamily)
{
    m_sDefaultFontFamily = sFontFamily;
  //  AsApp::asInstance()->asSetUserSetting("DefaultFont", sFontFamily );
}
        
const int & AsTextRes::asGetDefaultFontSize() const
{
    return m_nDefaultFontSize;
}
        
void AsTextRes::asSetDefaultFontSize(const int & nFontSize)
{
    m_nDefaultFontSize = nFontSize;
  //  AsApp::asInstance()->asSetUserSetting("DefaultFontSize", nFontSize );
}

void AsTextRes::asSetDefaultTextColor( const QColor& color )
{
    this->m_DefaultTextColor = color;
  //  AsApp::asInstance()->asSetUserSetting("DefaultTextColor", color.name() );
}

const QColor& AsTextRes::asGetDefaultTextColor( void ) const
{
    return this->m_DefaultTextColor;
}  
        
void AsTextRes::asSetBounds( const QSizeF& bounds )
{
    m_bounds = bounds;
            
/*    if ( bounds.width()<=0 )
    {
    AsRectF combinedRect = m_CachedTextRuns.at(0).asGetBoundingRect();

    int count = m_CachedTextRuns.size();
    for( int i=1; i < count; i++ )
    {
    AsTextRun &tRun = m_CachedTextRuns[i];
    combinedRect.asUnite( tRun.asGetBoundingRect() );
    }
    m_bounds = combinedRect.size().toSize();
    }*/
}

const QSizeF& AsTextRes::asGetBounds() const
{
    return m_bounds;
}

void AsTextRes::asCreateBoundingRects()
{
//    for( int i = 0; i < m_CachedTextRuns.size(); i++ )
//    {
//        m_CachedTextRuns[i].asCalculateBoundingRect();
//    }
}

QString AsTextRes::asModifyFSInRtf( QString &sInput, qreal scale )
{
    QString sConvertedRtf;

    // font size compressed by a factor of 0.78 on the Mac. Need to pre-process the RTF in order to convert the font size back to the original value
    // by re-applying the scaling factor of 1.33 to the font. ie. /fs36 becomes /fs48

    QString sOrigRtf = sInput;

    int nPos = 0;
    int nPrevPos = 0;

    while( nPos != -1 )
    {
        //nPos = sOrigRtf.indexOf(QString("\\fs"),nPos);
        QRegExp rx("\\\\fs\\d+");
        nPos = sOrigRtf.indexOf(rx,nPos);

        if( nPos != -1 )
        {
            sConvertedRtf += sOrigRtf.mid(nPrevPos,(nPos - nPrevPos)); 

            QRegExp rx2("[ |\\\\]");
            int nPos2 = sOrigRtf.indexOf(rx2,nPos+1);

            int len = nPos2 - nPos;
        QString sFontSize = sOrigRtf.mid(nPos, len);
    
            QStringList sFontVal = sFontSize.split(QString("\\fs"));
            
            if( sFontVal.size() > 0 ) 
            {
                int nFontVal = sFontVal[1].toInt();

        nFontVal = qRound((qreal)nFontVal * scale );

                sFontVal.clear();

                QString sNewFontVal("\\fs");
                QString sNum = QString::number(nFontVal);
        sNewFontVal += sNum;
                sConvertedRtf += sNewFontVal;

        nPrevPos = nPos = nPos2;
            }
            else
        break;
        }            
    }

    // copy across rest of the string
    int len = sOrigRtf.length() - nPrevPos;
    sConvertedRtf += sOrigRtf.mid(nPrevPos, len);

    return sConvertedRtf;
}

QString AsTextRes::asModifyFSInHTML( QString &sInput, qreal scale )
{
    QString sConvertedHTML;

    int nPos = 0;
    int nPrevPos = 0;
    QString searchText = "font-size:";
    int searchTextLen = searchText.size();

//    //qDebug() << "[ AsTextRes ] - asModifyFSInHTML sInput =" << sInput;

    while( nPos != -1 )
    {
    nPos = sInput.indexOf(searchText, nPos, Qt::CaseInsensitive );

    int ltPos = sInput.lastIndexOf( "<", nPos );
    int gtPos = sInput.lastIndexOf( ">", nPos );

    if ( (gtPos > ltPos) && (nPos != -1) )
    {
        //Outside an HTML tag
        nPos++;
        continue;
    }

        if( nPos != -1 )
        {
            sConvertedHTML += sInput.mid( nPrevPos, nPos - nPrevPos ); 
//            //qDebug() << "[ AsTextRes ] - asModifyFSInHTML sConvertedHTML =" << sConvertedHTML;

            int nPos2 = sInput.indexOf("pt", nPos + 1);
            int len = nPos2 - ( nPos + searchTextLen );

        QString sFontSize = sInput.mid(nPos + searchTextLen, len);
            
            if( sFontSize.size() > 0 ) 
            {
                int nFontVal = sFontSize.toInt();
        nFontVal = qRound((qreal)nFontVal * scale );
                QString sNum = QString::number(nFontVal);
                sConvertedHTML += ( searchText + sNum );
        nPrevPos = nPos = nPos2;
            }
            else
        {
        break;
        }
        }            
    }

    // copy across rest of the string
    int len = sInput.length() - nPrevPos;
    sConvertedHTML += sInput.mid(nPrevPos, len);
//    //qDebug() << "[ AsTextRes ] - asModifyFSInHTML sConvertedHTML =" << sConvertedHTML;

    return sConvertedHTML;
}

qreal AsTextRes::asGetAndResetConversionOffset( void )
{
    qreal retVal = m_topOffset;
    m_topOffset = 0;
    return retVal;
}

const qreal & AsTextRes::asGetConversionOffset( void ) const
{
    return m_topOffset;
}

void AsTextRes::asSetConversionOffset( qreal topOff )
{
    m_topOffset = topOff;
}

void AsTextRes::asSetFrameWidth(int nWidth)
{
    m_nFrameWidth = nWidth;
}

void AsTextRes::asSetFrameHeight(int nHeight)
{
    m_nFrameHeight = nHeight;
}


void AsTextRes::asSetMisspelltWordOriginalColorList(const QHash<QString, QColor>& misspelltWords)
{
    m_MisspelltWords = misspelltWords;    
}

const QHash<QString, QColor>& AsTextRes::asGetMisspelltWordOriginalColorList(void)
{
//    for( int i = 0; i < m_CachedTextRuns.size(); i++ )
//    {
//        if(m_CachedTextRuns[i].asIsMisspelltWord())
//    {
//        m_MisspelltWords.insert(m_CachedTextRuns[i].asGetText(),m_CachedTextRuns[i].asGetTextColor());
//    }
//    }

    return m_MisspelltWords;    
}

bool AsTextRes::asIsArabicChar( QChar character )
{
    if( ( character >= QChar( 0x0600 ) && character <= QChar( 0x06FF ) ) ||
        ( character >= QChar( 0x0750 ) && character <= QChar( 0x077F ) ) ||
        ( character >= QChar( 0x08A0 ) && character <= QChar( 0x08FF ) ) ||
        ( character >= QChar( 0xFB50 ) && character <= QChar( 0xFDFF ) ) || 
        ( character >= QChar( 0xFE70 ) && character <= QChar( 0xFEFF ) ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Public method
bool AsTextRes::asIsTextRightToLeft()
{
    return  false;
	//return asIsThereRightToLeftTextInTextRunArray( m_CachedTextRuns );
}

//bool AsTextRes::asIsThereRightToLeftTextInTextRunArray( AsTextRunArray & asTextRunArray )
//{
//	bool retVal = false ;
//
//	int asTextRunArrayCount = asTextRunArray.size();
//	for( int i = 0; i < asTextRunArrayCount; i++ )
//	{
//		if( asTextRunArray[i].asGetText().isRightToLeft() )
//		{
//			retVal = true;
//			break;
//		}
//	}
//
//	return retVal;
//}
//
//void AsTextRes::asShuffleTextRunsToLeftWRTZeroXPos( AsTextRunArray & asTextRunArray )
//{
//	int asTextRunArrayCount = asTextRunArray.size();
//
//	if( asTextRunArrayCount > 0 )
//	{
//        qreal offset = asTextRunArray[0].asGetTextPos().x() - ARABIC_TEXT_CLEARANCE_FRONT;
//
//		for( int j = 1; j < asTextRunArrayCount; j++ )
//		{
//			offset = qMin(offset, asTextRunArray[j].asGetTextPos().x() - ARABIC_TEXT_CLEARANCE_FRONT ) ;
//		}
//
//		for( int i = 0; i < asTextRunArrayCount; i++ )
//		{
//			QPointF newPos = asTextRunArray[i].asGetTextPos();
//			qreal newX = newPos.x() - offset;
//			newPos.setX( newX );
//			asTextRunArray[i].asSetTextPos( newPos );
//
//			AsRectF newRect = asTextRunArray[i].asGetBoundingRect();
//			newRect.setX( newX );
//			asTextRunArray[i].asSetBoundingRect( newRect );
//		}
//	}
//}

