// Implements the AsAnnotation class.
// $Author: Paul Wareing.

#include "asannotation.h"
#include "../resources/asresourcemanager.h"
#include "../resources/asannotationres.h"
//#include "asstudio.h"
#include "../asfactory.h"
#include "../dataStruct/aspointfarray.h"
#include <QVector>
//#include "asannotationres.h"
//#include "aslocale.h"

namespace
{
    const qreal MIN_ANNOTATION_TOUCH_TOLERENCE = 15.0;
};

AsAnnotation::AsAnnotation( AsFactory *pAsFactory ) : AsRenderable( pAsFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_ANNOTATION );

    // Initialise the properties with primitive types.
    m_nResource = 0;
    m_pAsAnnotationRes = 0;
    m_nEndCapA = AsAnnotation::AS_ENDCAP_NONE;
    m_nEndCapB = AsAnnotation::AS_ENDCAP_NONE;
    m_forHandwriting = false;
    m_bNewlyCreated = false;
    m_bAnnotating = false;
    m_bEndCapPainterPathDirty = true;
}

AsAnnotation::AsAnnotation( const AsAnnotation& annotation ) : AsRenderable( annotation )
{
    this->asCopy( annotation );
}

AsAnnotation::~AsAnnotation()
{
    if ( m_pAsAnnotationRes != 0 )
    {
     //   this->m_pAsFactory->asGetResourceManager()->asUnloadResource( m_pAsAnnotationRes );
    }
}

void AsAnnotation::operator= ( const AsAnnotation& annotation )
{
    AsRenderable::operator = ( annotation );
    this->asCopy( annotation );
}

bool AsAnnotation::operator== ( const AsAnnotation& annotation )
{
    if ( !AsRenderable::operator ==( annotation ) )
    {
        return false;
    }

    if (( m_nResource != annotation.asGetResource() ) ||
        ( m_nEndCapA != annotation.asGetEndCapA() ) ||
        ( m_nEndCapB != annotation.asGetEndCapB() ))
    {
        return false;
    }
    return true;
}

void AsAnnotation::asCopy( const AsAnnotation& annotation )
{
    this->m_nResource = annotation.asGetResource();
    this->m_nEndCapA = annotation.asGetEndCapA();
    this->m_nEndCapB = annotation.asGetEndCapB();
    this->m_pAsAnnotationRes = 0;
    m_forHandwriting = false;
    m_bNewlyCreated = annotation.m_bNewlyCreated;
    m_bAnnotating = annotation.m_bAnnotating;
    m_bEndCapPainterPathDirty = true;
    m_bTransformedRectDirty = true;
}



void AsAnnotation::asPrepareBoundingRect()
{
//    if(m_bTransformedRectDirty)
//    {
//        AsAnnotationRes * pAnnoRes = qobject_cast<AsAnnotationRes *>(this->asGetResourcePointer());
//        if( pAnnoRes != 0 )
//        {
//	        const AsPointFArray &pntArray = pAnnoRes->asGetPoints();
//	        AsInk *pInk = asGetInkPointer();
//	        const QPen& pen = pInk->asGetPen();
//	        QRectF newBound;
//
//	        if(pntArray.count() == 1)
//	        {
//	            float adjust = pen.width()/2.0;
//	            QPointF srcPoint = pntArray.at(0);
//	            QPointF topLeft(srcPoint.x()-adjust,srcPoint.y()-adjust);
//	            QPointF bottomRight(srcPoint.x()+adjust,srcPoint.y()+adjust);
//
//	            newBound.setTopLeft(topLeft);
//	            newBound.setBottomRight(bottomRight);
//	        }
//	        else
//	        {
//	            QPainterPath localPath;
//	            localPath.addPolygon(pntArray);
//
//	            if( pInk->asGetPenStyle() == AsInk::AS_PENSTYLE_NONE )
//			        newBound = localPath.boundingRect();
//		        else
//		        {
//	                // ensure end cap paths are built:
//	                asBuildEndCapPainterPaths();
//			        QPainterPathStroker stroker;
//			        stroker.setWidth(pen.width());
//			        stroker.setCapStyle(pen.capStyle());
//			        stroker.setJoinStyle(pen.joinStyle());
//			        QPainterPath stroked = stroker.createStroke(localPath);
//
//	                // add the stroked end caps
//	                if( !m_endCapPainterPaths.empty() )
//	                {
//	                    QListIterator<QPainterPath*> it( m_endCapPainterPaths );
//			            while ( it.hasNext() )
//	                        stroked = stroked.united( *(it.next()) );
//	                }
//
//			        newBound = stroked.boundingRect();
//		        }
//	        }
//	        AsRectF newAsBound( newBound.topLeft(), newBound.bottomRight() );
//		    this->asSetBoundingRect( newAsBound );
//        }
//    }
}



QHash<QString, quint16>& AsAnnotation::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsAnnotation::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsAnnotation::AS_PROPERTY_TRANSFORM );
   //     HashProperties.insert( "asTwips", ( quint16 )AsAnnotation::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsAnnotation::AS_PROPERTY_NAME );
    //    HashProperties.insert( "asKeywords", ( quint16 )AsAnnotation::AS_PROPERTY_KEYWORDS );
    //    HashProperties.insert( "asVisible", ( quint16 )AsAnnotation::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsAnnotation::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsAnnotation::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsAnnotation::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsAnnotation::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsAnnotation::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsAnnotation::AS_PROPERTY_ROTATEORIGIN );
        HashProperties.insert( "moveType", ( quint16 )AsAnnotation::AS_PROPERTY_CANMOVE );
   //     HashProperties.insert( "asCanSize", ( quint16 )AsAnnotation::AS_PROPERTY_CANSIZE );
   //     HashProperties.insert( "asCanRotate", ( quint16 )AsAnnotation::AS_PROPERTY_CANROTATE );
  //      HashProperties.insert( "asCanBlock", ( quint16 )AsAnnotation::AS_PROPERTY_CANBLOCK );
  //      HashProperties.insert( "asCanSnap", ( quint16 )AsAnnotation::AS_PROPERTY_CANSNAP );
        HashProperties.insert( "locked", ( quint16 )AsAnnotation::AS_PROPERTY_LOCKED );
  //      HashProperties.insert( "asSnapback", ( quint16 )AsAnnotation::AS_PROPERTY_SNAPBACK );
  //      HashProperties.insert( "asPathPointer", ( quint16 )AsAnnotation::AS_PROPERTY_PATHPOINTER );
   //     HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsAnnotation::AS_PROPERTY_ROTATEABOUTPOINTER );
  //      HashProperties.insert( "asRotatePoint", ( quint16 )AsAnnotation::AS_PROPERTY_ROTATEPOINT );
  //      HashProperties.insert( "asRotateAbout", ( quint16 )AsAnnotation::AS_PROPERTY_ROTATEABOUT );
  //      HashProperties.insert( "asRotateStep", ( quint16 )AsAnnotation::AS_PROPERTY_ROTATESTEP );
   //     HashProperties.insert( "asSnapToPointer", ( quint16 )AsAnnotation::AS_PROPERTY_SNAPTOPOINTER );
  //      HashProperties.insert( "asSnapPoint", ( quint16 )AsAnnotation::AS_PROPERTY_SNAPPOINT );
  //      HashProperties.insert( "asSnapTo", ( quint16 )AsAnnotation::AS_PROPERTY_SNAPTO );
  //      HashProperties.insert( "asCanContain", ( quint16 )AsAnnotation::AS_PROPERTY_CANCONTAIN );
  //      HashProperties.insert( "asContainPointer", ( quint16 )AsAnnotation::AS_PROPERTY_CONTAINPOINTER );
  //      HashProperties.insert( "asContainWords", ( quint16 )AsAnnotation::AS_PROPERTY_CONTAINWORDS );
  //      HashProperties.insert( "asContainRule", ( quint16 )AsAnnotation::AS_PROPERTY_CONTAINRULE );
  //      HashProperties.insert( "asV2Type", ( quint16 )AsAnnotation::AS_PROPERTY_V2TYPE );
  //      HashProperties.insert( "asConnectorList", ( quint16 )AsAnnotation::AS_PROPERTY_CONNECTORLIST );
  //      HashProperties.insert( "asLabel", ( quint16 )AsAnnotation::AS_PROPERTY_LABEL );
  //      HashProperties.insert( "asQuestionItem", ( quint16 )AsAnnotation::AS_PROPERTY_QUESTIONITEM );
  //      HashProperties.insert( "asQuestionItemID", ( quint16 )AsAnnotation::AS_PROPERTY_QUESTIONITEMID );
   //     HashProperties.insert( "asQuestionTag", ( quint16 )AsAnnotation::AS_PROPERTY_QUESTIONTAG );
   //     HashProperties.insert( "asAllowSnapback", ( quint16 )AsAnnotation::AS_PROPERTY_ALLOWSNAPBACK );
        HashProperties.insert( "translucency", ( quint16 )AsAnnotation::AS_PROPERTY_TRANSLUCENCY );
 //       HashProperties.insert( "asDragACopy", ( quint16 )AsAnnotation::AS_PROPERTY_DRAGACOPY );
 //       HashProperties.insert( "asRewardSound", ( quint16 )AsAnnotation::AS_PROPERTY_REWARD_SOUND );
  //      HashProperties.insert( "asRewardSoundLocation", ( quint16 )AsAnnotation::AS_PROPERTY_REWARD_SOUND_LOCATION );
//	    HashProperties.insert( "asAsyncTestTag", ( quint16 )AsAnnotation::AS_PROPERTY_ASYNCTESTTAG );
   //     HashProperties.insert( "asInteractMode", ( quint16 )AsAnnotation::AS_PROPERTY_INTERACTMODE );

        // From AsAnnotation...
        HashProperties.insert( "resource", ( quint16 )AsAnnotation::AS_PROPERTY_RESOURCE );

        HashProperties.insert( "endCapA", ( quint16 )AsAnnotation::AS_PROPERTY_ENDCAPA );
        HashProperties.insert( "endCapB", ( quint16 )AsAnnotation::AS_PROPERTY_ENDCAPB );
    }

    return HashProperties;
}

void AsAnnotation::asResetPropertyIndex( void )
{
   // AsObject::asSetPropertyIterator( &m_lProperties );
}

bool AsAnnotation::asCheckHit(  const QPointF & worldPos )
{
    bool ret = false;
	
//    AsRectF tbRect = this->asGetTransformedBoundingRect( true );
//    if( tbRect.contains( worldPos ) )
//    {
//        QPointF checkPos = worldPos;
//        asUnTransformPoint(checkPos);
//
//        AsAnnotationRes * pAnnoRes = qobject_cast<AsAnnotationRes *>(asGetResourcePointer());
//        Q_ASSERT_X( pAnnoRes != 0, "AsAnnotation", "asCheckHit pAnnoRes is NULL");
//        if( pAnnoRes != 0 )
//        {
//	        const AsPointFArray &pntArray = pAnnoRes->asGetPoints();
//
//            AsInk *pInk = this->asGetInkPointer();
//            if( pInk != 0 )
//            {
//                unsigned int penWidth = pInk->asGetPenWidth();
//
//	            qreal tol = ( qreal )penWidth/2.0;
//                qreal minTol = 1.0;
//                if( AsConcurrencyFilter::asGetInputMethod() == ASINPUTMETHOD_TOUCH )
//                {
//                    minTol = MIN_ANNOTATION_TOUCH_TOLERENCE;
//                }
//                tol = qMax(tol, minTol);
//
//	            if( As2DGeom::asPntOnLines( checkPos , pntArray , tol ) )
//	            {
//	                ret = true;
//	            }
//            }
//        }
//    }
    return ret;
}


bool AsAnnotation::asCheckHitByCircle(  const QPointF & worldPos, int width )
{
    bool ret = false;

//    if( width <= 0 )
//    {
//        width = 1;
//    }
//
//    qreal halfWid = (qreal)width / 2.0;
//    AsRectF tbRect = this->asGetTransformedBoundingRect( true );
//    tbRect.adjust( -halfWid, -halfWid, halfWid, halfWid );
//    if( tbRect.contains( worldPos ) )
//    {
//	QPointF checkPos = worldPos;
//        asUnTransformPoint(checkPos);
//
//        AsAnnotationRes * pAnnoRes = ( AsAnnotationRes * )this->asGetResourcePointer();
//	const AsPointFArray &pntArray = pAnnoRes->asGetPoints();
//
//        AsInk *pInk = this->asGetInkPointer();
//        qreal tol = pInk->asGetPenWidth();
//        tol/=2;
//        tol = qMax(tol, 1.0);
//
//	if( As2DGeom::asPntOnLines( checkPos , pntArray , halfWid + tol ) )
//	{
//	    ret = true;
//	}
//    }
    return ret;
}



const QList<QPointF>  AsAnnotation::asGetAnchorPoints() 
{
    QList<QPointF> anchorPoints;

//    AsTransform* pTransform = asGetTransformPointer();
//    double angle = pTransform->asGetAngle();
//    QMatrix matRot;
//    matRot.rotate( angle );
//
//    AsPointFArray points = asGetPoints();
//
//    int count = points.count();
//    int divisor =  5;
//
//    if(count < divisor)
//    {
//        divisor = count;
//    }
//
//    divisor = qMax(divisor, 1);
//
//    for (int i=0; i< count ;i+= divisor)
//    {
//        QPointF scaledPoint = points.at(i);
//        scaledPoint.setX(scaledPoint.x() * asGetTransformPointer()->asGetScaleFactor().x());
//        scaledPoint.setY(scaledPoint.y() * asGetTransformPointer()->asGetScaleFactor().y());
//
//        QPointF transformed = matRot.map(scaledPoint);
//        transformed = transformed + pTransform->asGetTranslate();
//        anchorPoints.append(transformed);
//    }
    return anchorPoints;
}

AsPointFArray AsAnnotation::asGetPoints( void )
{
//    AsAnnotationRes *pRes = qobject_cast<AsAnnotationRes *>(this->asGetResourcePointer());
//    if( pRes == 0 )
//    {
//        return AsPointFArray();
//    }
//    return  pRes->asGetPoints();
    return AsPointFArray();
}

QVector<int>& AsAnnotation::asGetTimePoints( void )
{
   // AsAnnotationRes *pRes = qobject_cast<AsAnnotationRes *>(this->asGetResourcePointer());
    static  QVector<int> vector;
    return  vector;
}

bool AsAnnotation::asIsResourcePointerValid( void )
{
    return asGetResourcePointer() == 0 ? false : true;
}

//unsigned int AsAnnotation::asGetResource( void ) const
//{
//    return m_nResource;
//}

void AsAnnotation::asSetResource( unsigned int nResource )
{
    m_nResource = nResource;
}

AsResource * AsAnnotation::asGetResourcePointer( void )
{
    if ( m_pAsAnnotationRes == 0 )
    {
        m_pAsAnnotationRes = dynamic_cast<AsAnnotationRes*>(m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_ANNOTATIONRES, asGetResource() ));
    }

    return m_pAsAnnotationRes;

}

void AsAnnotation::asSetResource( AsResource *pResource )
{
//    m_pAsAnnotationRes = qobject_cast< AsAnnotationRes * >( pResource );
//    if ( m_pAsAnnotationRes != 0 )
//    {
//        m_nResource = m_pAsAnnotationRes->asGetID();
//    }
//    else
//    {
//        m_nResource = 0;
//    }
//    this->asSetDirtyForWrite( true );
}

AsAnnotation::AsEnumEndCap AsAnnotation::asGetEndCapA( void ) const
{
    return m_nEndCapA;
}

void AsAnnotation::asSetEndCapA( AsAnnotation::AsEnumEndCap cap )
{
    m_nEndCapA = cap;
    m_bEndCapPainterPathDirty = true;
}

AsAnnotation::AsEnumEndCap AsAnnotation::asGetEndCapB( void ) const
{
    return m_nEndCapB;
}

void AsAnnotation::asSetEndCapB( AsAnnotation::AsEnumEndCap cap )
{
    m_nEndCapB = cap;
    m_bEndCapPainterPathDirty = true;
}

void AsAnnotation::asAddLocalPoint( QPointF & pnt )
{
    if( m_pAsAnnotationRes != 0 )
    {
     //   m_pAsAnnotationRes->asAddPoint( pnt );
    }
    
    // revisit bounding calc
}

void AsAnnotation::asSetInk( const AsInk& ink )
{
    m_bEndCapPainterPathDirty = true;
    AsRenderable::asSetInk( ink );
}

void AsAnnotation::asSetForHandwriting( bool forHWR )
{
    m_forHandwriting = forHWR;
}

bool AsAnnotation::asIsForHandwriting( void ) const
{
    return m_forHandwriting;
}

void AsAnnotation::asSetNewlyCreated(bool bNewlyCreated)
{
    m_bNewlyCreated = bNewlyCreated;
}

bool AsAnnotation::asGetNewlyCreated() const
{
    return m_bNewlyCreated;
}

bool AsAnnotation::asIsSelectable( void )
{
    if( m_forHandwriting || m_bAnnotating )
	return false;

    return true;
}

int AsAnnotation::asGetTranslucency()
{
//    AsInk * pInk = this->asGetInkPointer();
//    if( pInk != 0 )
//    {
//        QColor penColour = pInk->asGetPenColor();
//        return penColour.alpha();
//    }
//    else
    {
        return 0;
    }
}

void AsAnnotation::asSetTranslucency(int translucency)
{
//    AsInk * pInk = this->asGetInkPointer();
//    if( pInk != 0 )
//    {
//        pInk->asSetAlpha(AsInk::AS_COLOR_PEN, translucency);
//    }
}

QString AsAnnotation::asGetNewObjectName(quint32 nIndex)
{
    QString strNextName;
//    strNextName = AsLocale::asGetString(AsLocale::AS_STRING_PEN) + AsLocale::asInstance()->asGetLocale().toString(nIndex);
    return strNextName;
}

bool AsAnnotation::asGetAnnotating( void ) const
{
    return m_bAnnotating;
}

void AsAnnotation::asSetAnnotating( bool b )
{
    m_bAnnotating = b;
}

void AsAnnotation::asBuildEndCapPainterPaths( void )
{
    // See AsShape::asSetPainterPathEndCap, we build the same end caps here (code duplication?).

    if ( !m_bEndCapPainterPathDirty )
        return;

    m_bEndCapPainterPathDirty = false;
    asDeleteEndCapPainterPaths();

//    AsInk *pInk = asGetInkPointer();
//    if( pInk != 0 )
//    {
//        const QPen& pen = pInk->asGetPen();
//
//        if( m_pAsAnnotationRes == 0 )
//        {
//            return;
//        }
//
//        // we dont convert endcaps to magic ink, so we dont build any
//        if ( pInk->asGetInkType() == AsInk::AS_INKTYPE_MASK )
//        {
//            return;
//        }
//
//        // need 2 points draw any end cap
//        if( this->asGetPoints().count() <= 1 )
//        {
//            return;
//        }
//
//        //qDebug() << "endcaps " << this->asGetEndCapA() << " " << this->asGetEndCapB();
//
//        // build painterpaths if we have endcaps.
//        if ( m_nEndCapA == AsAnnotation::AS_ENDCAP_ARROW )
//        {
//            QPointF pos1 = m_pAsAnnotationRes->asGetPoints().at(0);
//            QPointF pos2 = m_pAsAnnotationRes->asGetPoints().at(1);
//
//            QLineF line( pos2, pos1 );
//
//            unsigned int headwidth = pInk->asGetPenWidth();
//            QLineF unitv = line.unitVector();
//            unitv.translate( -pos2 );
//            double extent = double(headwidth)/line.length();
//
//            QPointF overHead( pos1 - unitv.p2()*extent );
//            QLineF localizer( overHead, line.p2() );
//            QLineF join = localizer.normalVector();
//            join.setLength( headwidth ) ;
//            QLineF downWind = join.normalVector();
//            QLineF base = downWind.normalVector();
//            QLineF finals = base.normalVector();
//
//            QPainterPath track;
//            track.moveTo( join.p2() );
//            track.lineTo( base.p2() );
//            track.lineTo( finals.p2() );
//            track.lineTo( join.p2() );
//
//            QPainterPathStroker stroker;
//
//            stroker.setJoinStyle( pen.joinStyle() );
//            stroker.setCapStyle( pen.capStyle() );
//            stroker.setWidth( pInk->asGetPenWidth() );
//
//            track = stroker.createStroke( track );
//
//            QPainterPath *ppath = new QPainterPath( track );
//            m_endCapPainterPaths.push_back( ppath );
//        }
//        else if ( m_nEndCapA == AsAnnotation::AS_ENDCAP_RADIUS )
//        {
//            QPointF start = m_pAsAnnotationRes->asGetPoints().at(0);
//
//            unsigned int penwidth = pInk->asGetPenWidth();
//            QPainterPath blob;
//            blob.addEllipse( -(qreal)penwidth / 2.0, -(qreal)penwidth / 2.0, (qreal)penwidth, (qreal)penwidth );
//            blob.moveTo( start );
//
//            QPainterPathStroker stroker;
//
//            stroker.setJoinStyle( pen.joinStyle() );
//            stroker.setCapStyle( pen.capStyle() );
//            stroker.setWidth( pInk->asGetPenWidth() );
//
//            blob = stroker.createStroke( blob );
//
//            QPainterPath *ppath = new QPainterPath( blob );
//            m_endCapPainterPaths.push_back( ppath );
//        }
//    }
}

void AsAnnotation::asDeleteEndCapPainterPaths( void )
{
//    if( !m_endCapPainterPaths.empty() )
//    {
//        QListIterator<QPainterPath*> it( m_endCapPainterPaths );
//	while ( it.hasNext() )
//            delete it.next();
//        m_endCapPainterPaths.clear();
//    }
}

//const QList< QPainterPath *>& AsAnnotation::asGetEndCapPainterPathsConstRef( void )
//{
//    asBuildEndCapPainterPaths();
//
//    return m_endCapPainterPaths;
//}

void AsAnnotation::asScaleBy(const QPointF& scaleFactor, 
			     const bool maintainAspect/*=false*/)
{
    m_bEndCapPainterPathDirty = true;
    //AsRenderable::asScaleBy(scaleFactor, maintainAspect);
}

void AsAnnotation::asScaleTo( const QPointF& scale )
{
    m_bEndCapPainterPathDirty = true;
   // AsRenderable::asScaleTo( scale );
}

QString AsAnnotation::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsAnnotation::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

const Json::Value &AsAnnotation::asResourceSerialized()
{
        asGetResourcePointer();
        if(m_pAsAnnotationRes){
            m_resourceJsonObject <<   m_pAsAnnotationRes->property(AsAnnotationRes::AS_PROPERTY_POINTS);
        }
        return m_resourceJsonObject;
}

Json::Value &AsAnnotation::serialized()
{
    Json::Value &jsonObject = AsRenderable::serialized();
    return  jsonObject;

}

QString AsAnnotation::typeName()
{
    return "annotation";
}
