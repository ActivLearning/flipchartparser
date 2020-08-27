// Implements the AsText class.
// $Author: Paul Wareing.

#include "astext.h"
#include <QString>
#include "../asfactory.h"
#include "../resources/astextres.h"
#include "../resources/asresourcemanager.h"

AsText::AsText( AsFactory *pAsFactory ) : AsRenderable( pAsFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_TEXT );

    // Initialise the properties with primitive types.
    m_nResource = 0;
    m_pAsTextRes = Q_NULLPTR;
    m_nQA = 0;
    
    asSetSnapTo(AsRenderable::ASPOINT_FIRSTTEXTLINE);
}

AsText::AsText( const AsText& text ) : AsRenderable( text )
{
    this->asCopy( text );
}

AsText::~AsText()
{
//    emit asTextObjectDeleted(this);
//    if ( m_pAsTextRes != 0 )
//    {
//        this->m_pAsFactory->asGetResourceManager()->asUnloadResource( m_pAsTextRes );
//    }
}

void AsText::operator= ( const AsText& text )
{
    AsRenderable::operator =( text );
    this->asCopy( text );
}

bool AsText::operator==( const AsText& text )
{
    if ( !AsRenderable::operator ==( text ) )
    {
        return false;
    }

    if (( m_nResource != text.asGetResource() ) ||
        ( m_nQA != text.asGetQA() ))
    {
        return false;
    }
    return true;
}

void AsText::asCopy( const AsText& text )
{
    this->m_nResource = text.asGetResource();
    this->m_nQA = text.asGetQA();
    this->m_pAsTextRes = Q_NULLPTR;
    this->m_LastInvertedHitPos = QPointF();
}

QHash<QString, quint16>& AsText::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsText::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsText::AS_PROPERTY_TRANSFORM );
      //  HashProperties.insert( "asTwips", ( quint16 )AsText::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsText::AS_PROPERTY_NAME );
      //  HashProperties.insert( "asKeywords", ( quint16 )AsText::AS_PROPERTY_KEYWORDS );
     //   HashProperties.insert( "asVisible", ( quint16 )AsText::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsText::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsText::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsText::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsText::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsText::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsText::AS_PROPERTY_ROTATEORIGIN );
        HashProperties.insert( "moveType", ( quint16 )AsText::AS_PROPERTY_CANMOVE );
      //  HashProperties.insert( "asCanSize", ( quint16 )AsText::AS_PROPERTY_CANSIZE );
      //  HashProperties.insert( "asCanRotate", ( quint16 )AsText::AS_PROPERTY_CANROTATE );
     //   HashProperties.insert( "asCanBlock", ( quint16 )AsText::AS_PROPERTY_CANBLOCK );
     //   HashProperties.insert( "asCanSnap", ( quint16 )AsText::AS_PROPERTY_CANSNAP );
        HashProperties.insert( "locked", ( quint16 )AsText::AS_PROPERTY_LOCKED );
      //  HashProperties.insert( "asSnapback", ( quint16 )AsText::AS_PROPERTY_SNAPBACK );
     //   HashProperties.insert( "asPathPointer", ( quint16 )AsText::AS_PROPERTY_PATHPOINTER );
    //    HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsText::AS_PROPERTY_ROTATEABOUTPOINTER );
    //    HashProperties.insert( "asRotatePoint", ( quint16 )AsText::AS_PROPERTY_ROTATEPOINT );
    //    HashProperties.insert( "asRotateAbout", ( quint16 )AsText::AS_PROPERTY_ROTATEABOUT );
    //    HashProperties.insert( "asRotateStep", ( quint16 )AsText::AS_PROPERTY_ROTATESTEP );
    //    HashProperties.insert( "asSnapToPointer", ( quint16 )AsText::AS_PROPERTY_SNAPTOPOINTER );
   //     HashProperties.insert( "asSnapPoint", ( quint16 )AsText::AS_PROPERTY_SNAPPOINT );
   //     HashProperties.insert( "asSnapTo", ( quint16 )AsText::AS_PROPERTY_SNAPTO );
   //     HashProperties.insert( "asCanContain", ( quint16 )AsText::AS_PROPERTY_CANCONTAIN );
   //     HashProperties.insert( "asContainPointer", ( quint16 )AsText::AS_PROPERTY_CONTAINPOINTER );
   //     HashProperties.insert( "asContainWords", ( quint16 )AsText::AS_PROPERTY_CONTAINWORDS );
   //     HashProperties.insert( "asContainRule", ( quint16 )AsText::AS_PROPERTY_CONTAINRULE );
   //     HashProperties.insert( "asV2Type", ( quint16 )AsText::AS_PROPERTY_V2TYPE );
   //     HashProperties.insert( "asConnectorList", ( quint16 )AsText::AS_PROPERTY_CONNECTORLIST );
    //    HashProperties.insert( "asLabel", ( quint16 )AsText::AS_PROPERTY_LABEL );
    //    HashProperties.insert( "asQuestionItem", ( quint16 )AsText::AS_PROPERTY_QUESTIONITEM );
    //    HashProperties.insert( "asQuestionItemID", ( quint16 )AsText::AS_PROPERTY_QUESTIONITEMID );
   //     HashProperties.insert( "asQuestionTag", ( quint16 )AsText::AS_PROPERTY_QUESTIONTAG );
    //    HashProperties.insert( "asAllowSnapback", ( quint16 )AsText::AS_PROPERTY_ALLOWSNAPBACK );
   //     HashProperties.insert( "asDragACopy", ( quint16 )AsText::AS_PROPERTY_DRAGACOPY );
   //     HashProperties.insert( "asAsyncTestTag", ( quint16 )AsText::AS_PROPERTY_ASYNCTESTTAG );
   //     HashProperties.insert( "asInteractMode", ( quint16 )AsText::AS_PROPERTY_INTERACTMODE );

        // From AsText...
        HashProperties.insert( "resource", ( quint16 )AsText::AS_PROPERTY_RESOURCE );
     //   HashProperties.insert( "asQA", ( quint16 )AsText::AS_PROPERTY_QA );

    }

    return HashProperties;
}

void AsText::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}


const QPointF& AsText::asLastInvertedHitPos( void ) const
{
    return this->m_LastInvertedHitPos;
}



bool AsText::asCheckHitFine( const QPointF & worldPos, int & whichTextRun )
{
    bool hit = false;
//    whichTextRun = -1;
//
//    const QPolygonF& poly = this->asGetTransformedBoundingPoly();
//    if( As2DGeom::asPntInPolygon( poly, worldPos ) )
//    {
//	//Text runs don't have a pre-transformed bounding rect, so must transform each one.
//	AsTransform *ppTran = this->asGetTransformPointer();
//	AsOrigin porigin = this->asGetScaleOrigin();
//	const AsRectF & bRect = this->asGetBoundingRect();
//	const QMatrix &combMatRef = ppTran->asDoTransform( porigin, bRect);
//	QPointF iWorldPos = combMatRef.inverted().map( worldPos );
//
//	AsTextRes *pTextRes = ( AsTextRes * )this->asGetResourcePointer();
//        const QList< AsTextRun > & TListRef = pTextRes->asGetTextRunList();
//
//        for( int tidx = 0; tidx < TListRef.size(); ++tidx )
//        {
//            const AsTextRun & TRef = TListRef.at( tidx );
//            const QRectF & bRect = TRef.asGetBoundingRect();
//
//	    if( bRect.contains( iWorldPos ))
//	    {
//		whichTextRun = tidx;
//                m_LastInvertedHitPos = iWorldPos;
//		hit = true;
//                break;
//            }
//        }	// text run
//
//		// if the background is opaque then this is a hit!
//	if ( hit == false && asGetInk().asGetBackgroundMode() == AsInk::AS_BACKGROUNDMODE_OPAQUE )
//	{
//	    hit = true;
//        }
//    } // hit text bounding rect

    return hit ;
}



bool AsText::asCheckHit(  const QPointF & worldPos )
{
    bool hit = false;
	    
//    QPolygonF poly;
//    if( AsConcurrencyFilter::asGetInputMethod() == ASINPUTMETHOD_TOUCH )
//    {
//        //ensure a minimum size for the touch hit area for the text's bounding area
//		poly = asGetTransformedBoundingPoly( asGetRectWithTouchTolerence( asGetBoundingRect() ) );
//    }
//    else
//    {
//        poly = this->asGetTransformedBoundingPoly();
//    }
//
//    if( As2DGeom::asPntInPolygon( poly, worldPos ) )
//    {
//	    //Text runs don't have a pre-transformed bounding rect, so must transform each one.
//	    AsTransform *ppTran = this->asGetTransformPointer();
//	    AsOrigin porigin = this->asGetScaleOrigin();
//	    const AsRectF & bRect = this->asGetBoundingRect();
//	    const QMatrix &combMatRef = ppTran->asDoTransform( porigin, bRect);
//	    QPointF iWorldPos = combMatRef.inverted().map( worldPos );
//
//	    AsTextRes *pTextRes = qobject_cast<AsTextRes*>(asGetResourcePointer());
//        if( pTextRes != 0 )
//        {
//            const QList< AsTextRun > & TListRef = pTextRes->asGetTextRunList();
//
//            for( int tidx = 0; tidx < TListRef.size(); ++tidx )
//            {
//                const AsTextRun & TRef = TListRef.at( tidx );
//                QColor bgColor = asGetInkPointer()->asGetBackgroundColor();
//                AsInk::AsEnumBackgroundMode backgroundMode = asGetInkPointer()->asGetBackgroundMode();
//                const AsRectF & textBoundingRect = TRef.asGetBoundingRect();
//
//                QRectF bRect;
//                if( AsConcurrencyFilter::asGetInputMethod() == ASINPUTMETHOD_TOUCH )
//                {
//                    //ensure a minimum size for the touch hit area for the text
//                    bRect = asGetRectWithTouchTolerence( textBoundingRect );
//                }
//                else
//                {
//                    bRect = textBoundingRect;
//                }
//
//	            if( bRect.contains( iWorldPos ))
//	            {
//                    m_LastInvertedHitPos = iWorldPos;
//                    hit = true;
//                }
//
//	            // if background color is present then select the text
//	            if( bgColor.isValid() && bgColor != Qt::transparent && backgroundMode == AsInk::AS_BACKGROUNDMODE_OPAQUE )
//	            {
//		            if(asGetTransformedBoundingRect().contains(worldPos))
//		            {
//		                m_LastInvertedHitPos = iWorldPos;
//		                hit = true;
//		            }
//	            }
//            }	// text run
//        }
//    } // hit text bounding rect
    return hit ;
}

bool AsText::asIsResourcePointerValid( void )
{
    return asGetResourcePointer() == NULL ? false : true;
}



void AsText::asSetResource( unsigned int nResource )
{
    m_nResource = nResource;
}

AsResource * AsText::asGetResourcePointer( void )
{
    if ( m_pAsTextRes == 0 )
    {
        m_pAsTextRes = dynamic_cast<AsTextRes*>(m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_TEXTRES, asGetResource() ));
    }

    return m_pAsTextRes;
}

void AsText::asSetResource( AsResource *pResource )
{
//    m_pAsTextRes = qobject_cast< AsTextRes * >( pResource );
//    if ( m_pAsTextRes != NULL )
//    {
//        m_nResource = m_pAsTextRes->asGetID();
//    }
//    else
//    {
//        m_nResource = 0;
//    }
//    this->asSetDirtyForWrite( true );
}

unsigned int AsText::asGetQA( void ) const
{
    return m_nQA;
}

void AsText::asSetQA( unsigned int nQA )
{
    m_nQA = nQA;
}

void AsText::asEdit()
{
//    m_pAsTextRes = ( AsTextRes * )this->asGetResourcePointer();
//    m_pAsTextRes = ( AsTextRes * )this->m_pAsFactory->asGetResourceManager()->asDetachResource( m_pAsTextRes );
//    this->asSetResource( m_pAsTextRes );
//    m_pAsTextRes->asCreateTextRuns();
}

//void AsText::asCommit( const QString & sText, const QSizeF& size, int nDPIX, int nDPIY )
//{
////    m_pAsTextRes->asSetDPIX(nDPIX);
////    m_pAsTextRes->asSetDPIY(nDPIY);
////    m_pAsTextRes->asSetText(sText);
////    m_pAsTextRes->asSetTextType(AsTextRes::AS_INSPIRE_QT4_HTML);
////
////    m_pAsTextRes->asSetBounds( size );
////    this->asCommit();
//}

void AsText::asCommit( void )
{
//    m_pAsTextRes->asCreateTextRuns( true, QApplication::isRightToLeft() );
//    asReCalculateBoundingRect();
//
//    m_pAsTextRes = (AsTextRes *)this->m_pAsFactory->asGetResourceManager()->asCommitResource(m_pAsTextRes );
//    this->asSetResource(m_pAsTextRes);
}

void AsText::asReCalculateBoundingRect()
{
//    const QSizeF& bounds = m_pAsTextRes->asGetBounds();
//    AsRectF rect = AsRectF( 0, 0, bounds.width(), bounds.height() ); //m_pAsTextRes->asCalculateBoundingRect();
//    const AsInk& ink = asGetInk();
//    if (ink.asGetPenStyle() != AsInk::AS_PENSTYLE_NONE )
//    {
//	qreal halfw = (qreal)ink.asGetPenWidth()/2;
//	rect.adjust(-halfw, -halfw, halfw, halfw);
//    }
//    asSetBoundingRect( rect );
}

void AsText::asScaleTextBy(const QPointF& factor, 
			   const bool maintainAspect/*=false*/)
{
//    AsRectF rect = asGetBoundingRect();
//    qreal w = rect.width() * factor.x();
//    qreal h = rect.height() * (maintainAspect ? factor.x() : factor.y());
//    rect.setSize( QSizeF( w, h ) );
//
//    // Detach the resource from the shared resource mechanism.
//    AsResourceManager *pResMan = m_pAsFactory->asGetResourceManager();
//
//    AsTextRes* pTextRes = ( AsTextRes * )pResMan->asDetachResource( asGetResourcePointer() );
//    asSetResource( pTextRes );
//
//    pTextRes->asSetBounds( rect.size() );
//
//    bool bAdjustHeightToFit = !qFuzzyCompare( factor.x(), 1 );
//    pTextRes->asCreateTextRuns( bAdjustHeightToFit );
//
//    // Place the resource back into the shared res mechanism.
//    pTextRes = ( AsTextRes * )pResMan->asCommitResource( pTextRes );
//    asSetResource( pTextRes );
//
//    asReCalculateBoundingRect();
}

void AsText::asReLayoutText()
{
//    // Detach the resource from the shared resource mechanism.
//    AsResourceManager *pResMan = m_pAsFactory->asGetResourceManager();
//
//    AsTextRes* pTextRes = ( AsTextRes * )pResMan->asDetachResource( asGetResourcePointer() );
//    asSetResource( pTextRes );
//
//    AsRectF rect = asGetBoundingRect();
//    pTextRes->asSetBounds( rect.size() );
//
//    pTextRes->asCreateTextRuns( true, QApplication::isRightToLeft() );
//
//    // Place the resource back into the shared res mechanism.
//    pTextRes = ( AsTextRes * )pResMan->asCommitResource( pTextRes );
//    asSetResource( pTextRes );
//
//    asReCalculateBoundingRect();
}

void AsText::asReplaceText( const QString& text, bool bKeepBounds )
{
//    if (!asIsPlainTextEqual(text))
//    {
//        asEdit();
//
//        AsTextRes *pTextRes = ( AsTextRes* )asGetResourcePointer();
//        const QString& originalText = pTextRes->asGetText();
//
//        QTextDocument doc;
//        doc.setHtml( originalText );
//
//        QTextCursor cursor( &doc );
//        QTextCharFormat cf = cursor.charFormat();
//        QTextBlockFormat bf = cursor.blockFormat();
//
//        doc.setPlainText( text );
//        cursor.select( QTextCursor::Document );
//        cursor.setCharFormat( cf );
//        cursor.setBlockFormat( bf );
//
//        QSizeF size(0, 0);
//        if ( bKeepBounds )
//            size = asGetBoundingRect().size();
//        asCommit( doc.toHtml(), size );
//    }
}

QString AsText::asGetNewObjectName(quint32 nIndex)
{
    QString strNextName;
    
   // strNextName = AsLocale::asGetString(AsLocale::AS_STRING_TEXT) + AsLocale::asInstance()->asGetLocale().toString(nIndex);
    return strNextName;
}

/**
 * Extracts plain text from the text stored in the resource (which may have HTML or RTF
 * tags in it) and compares it for equality with a supplied plain text string.
 *
 * @param otherPlainText The plain text to compare ours to.
 */
bool AsText::asIsPlainTextEqual(const QString& otherPlainText)
{
    return false;
//    AsTextRes* pTextRes = qobject_cast<AsTextRes*>(asGetResourcePointer());
//    bool isEqual = false;
//
//    if (!pTextRes)
//    {
//        isEqual = otherPlainText.isEmpty();
//    }
//    else
//    {
//        const AsTextRes::AsEnumTextType textType = pTextRes->asGetTextType();
//
//        if (textType == AsTextRes::AS_INSPIRE_PLAIN)
//        {
//            isEqual = (pTextRes->asGetText() == otherPlainText);
//        }
//        else
//        {
//            QString htmlText;
//
//            if (textType == AsTextRes::AS_V2_ALLTEXT_RTF)
//            {
//                AsRTFtoHTML rtfConverter;
//                htmlText = rtfConverter.asConvert(pTextRes->asGetText());
//            }
//            else
//            {
//                htmlText = pTextRes->asGetText();
//            }
//
//            QTextDocument doc;
//            doc.setHtml(htmlText);
//
//            isEqual = (doc.toPlainText() == otherPlainText);
//        }
//
//    }
//
//    return isEqual;
}

QString AsText::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsText::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

const Json::Value &AsText::asResourceSerialized()
{
    asGetResourcePointer();
    if(m_pAsTextRes){
        Variant var = m_pAsTextRes->property(AsTextRes::AS_PROPERTY_TEXTRUNS);
        m_resourceJsonObject << var;
    }
    return m_resourceJsonObject;
}

Json::Value &AsText::serialized()
{
    Json::Value &jsonObject = AsRenderable::serialized();
    return  jsonObject;

}

QString AsText::typeName()
{
    return "text";
}
