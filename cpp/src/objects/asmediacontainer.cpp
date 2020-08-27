
#include <QMutexLocker>
#include <QObject>
#include <QObjectList>


#include "asmediacontainer.h"

#include "../resources/asimageres.h"
#include "../resources/asmediafileres.h"
#include "../asfactory.h"
#include "../resources/asresourcemanager.h"



#include "../util/asutil.h"
#include "asflipchart.h"
#include "../util/commonlog.h"


#ifdef Q_OS_WIN32
#include "asaxwidget.h"
#endif












AsMediaContainer::AsMediaContainer( AsFactory *pFactory )
    : AsWidgetContainer( pFactory ), m_creationMutex( QMutex::Recursive ),
    m_bSelected(false),
    m_autoTakePlaceHolderImage( false )
{
    this->asClear();
}


AsMediaContainer::AsMediaContainer( const AsMediaContainer & container )
    : AsWidgetContainer( container ), m_creationMutex( QMutex::Recursive )
{
    this->asClear();
    this->asCopy( container );
}


AsMediaContainer::~AsMediaContainer()
{
    this->asDestroyMediaObjectAndSurface();

}


void AsMediaContainer::asDestroyMediaObjectAndSurface()
{

}


void AsMediaContainer::asSetVisible( bool bVisible )
{
	if( asIsVisible() == bVisible )
	{
		// do nothing.
		return;
	}

	AsRenderable::asSetVisible( bVisible );
	// restart the media, well start 
	this->asRestartMediaObject();
}


void AsMediaContainer::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}


void AsMediaContainer::asClear()
{
    this->asSetType( AsObject::AS_OBJECT_MEDIACONTAINER );
	
    this->m_isContextCreated = false;

    this->m_pTheSurfaceWidget = NULL;


    this->m_pMediaFileRes = NULL;
    this->m_pMultiMediaObject = NULL;
    this->m_autoPlay = false;
    this->m_loop = false;
    this->m_hideControls = false;
    this->m_forceAspect = false;
    this->m_mediaFileResource = 0;
    this->m_transparentBackground = false;
    this->m_unableToCreateMultiMediaObject = false;
    this->m_unableToCreateController = false;
    this->m_unableToCreateSurfaceWidget = false;
    this->m_unableToCreateSurface = false;
    this->m_creationState = AsMediaContainer::NotCreated;
    this->m_giveFocusOnCreate = false;
    this->m_firstRenderDone = false;
    this->m_currentRenderMode = AsWidgetContainer::AS_PAINTER_RENDER_IMAGE;
    this->m_knownDeviceSpaceRectChange = false;
    
    this->m_cachedForceOverlay = true;
    this->m_cachedAutoPlay = false;
    this->m_cachedLoop = false;
    this->m_cachedHideControls = true;
    this->m_cachedForceAspect = true;
    this->m_cachedTransparentBackground = false;  
    
    this->m_cahcedRestartWasPlaying = false;  
    
    this->m_needToDoMainSignalsAndSlotsConnection = true;
}


void AsMediaContainer::asCopy( const AsMediaContainer & container )
{
    AsWidgetContainer::operator = ( container );

    this->m_autoPlay = container.m_autoPlay;
    this->m_loop = container.m_loop;
    this->m_hideControls = container.m_hideControls;
    this->m_forceAspect = container.m_forceAspect;
    this->m_transparentBackground = container.m_transparentBackground;
}


void AsMediaContainer::operator = ( const AsMediaContainer & container )
{
    this->asCopy( container );
}


bool AsMediaContainer::operator == ( const AsMediaContainer & )
{
    return false;
}

void AsMediaContainer::asOnObjectEditing( AsNode *, AsNode *pObjectNode )
{

}


void AsMediaContainer::asOnObjectEdited( AsNode *, AsNode *pObjectNode )
{

}


bool AsMediaContainer::asGetAutoPlay() const
{
    return this->m_autoPlay;
}


bool AsMediaContainer::asGetLoop() const
{
    return this->m_loop;
}


bool AsMediaContainer::asGetHideControls() const
{
    return this->m_hideControls;
}


bool AsMediaContainer::asGetForceAspect() const
{
    return this->m_forceAspect;
}


unsigned int AsMediaContainer::asGetMediaFileResource() const
{
    return this->m_mediaFileResource;
}


bool AsMediaContainer::asGetTransparentBackground() const 
{
    return this->m_transparentBackground;
}


void AsMediaContainer::asSetAutoPlay( bool & v )
{
    this->m_autoPlay = v;
}


void AsMediaContainer::asSetLoop( bool & v )
{
    this->m_loop = v;
}


void AsMediaContainer::asSetHideControls( bool & v )
{
    this->m_hideControls = v;
}


void AsMediaContainer::asSetForceAspect( bool & v )
{
    this->m_forceAspect = v;
}


void AsMediaContainer::asSetMediaFileResource( unsigned int & id )
{
    this->m_pMediaFileRes = NULL;
    this->m_mediaFileResource = id;
}


void AsMediaContainer::asSetTransparentBackground( bool & value )
{
    this->m_transparentBackground = value;
}


QHash<QString, quint16> & AsMediaContainer::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsMediaContainer::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsMediaContainer::AS_PROPERTY_TRANSFORM );
      //  HashProperties.insert( "asTwips", ( quint16 )AsMediaContainer::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsMediaContainer::AS_PROPERTY_NAME );
     //   HashProperties.insert( "asKeywords", ( quint16 )AsMediaContainer::AS_PROPERTY_KEYWORDS );
     //  HashProperties.insert( "asVisible", ( quint16 )AsMediaContainer::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsMediaContainer::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsMediaContainer::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsMediaContainer::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsMediaContainer::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsMediaContainer::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsMediaContainer::AS_PROPERTY_ROTATEORIGIN );
        HashProperties.insert( "moveType", ( quint16 )AsMediaContainer::AS_PROPERTY_CANMOVE );
//        HashProperties.insert( "asCanSize", ( quint16 )AsMediaContainer::AS_PROPERTY_CANSIZE );
//        HashProperties.insert( "asCanRotate", ( quint16 )AsMediaContainer::AS_PROPERTY_CANROTATE );
//        HashProperties.insert( "asCanBlock", ( quint16 )AsMediaContainer::AS_PROPERTY_CANBLOCK );
//        HashProperties.insert( "asCanSnap", ( quint16 )AsMediaContainer::AS_PROPERTY_CANSNAP );
        HashProperties.insert( "locked", ( quint16 )AsMediaContainer::AS_PROPERTY_LOCKED );
//        HashProperties.insert( "asSnapback", ( quint16 )AsMediaContainer::AS_PROPERTY_SNAPBACK );
//        HashProperties.insert( "asPathPointer", ( quint16 )AsMediaContainer::AS_PROPERTY_PATHPOINTER );
//        HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsMediaContainer::AS_PROPERTY_ROTATEABOUTPOINTER );
//        HashProperties.insert( "asRotatePoint", ( quint16 )AsMediaContainer::AS_PROPERTY_ROTATEPOINT );
//        HashProperties.insert( "asRotateAbout", ( quint16 )AsMediaContainer::AS_PROPERTY_ROTATEABOUT );
//        HashProperties.insert( "asRotateStep", ( quint16 )AsMediaContainer::AS_PROPERTY_ROTATESTEP );
//        HashProperties.insert( "asSnapToPointer", ( quint16 )AsMediaContainer::AS_PROPERTY_SNAPTOPOINTER );
//        HashProperties.insert( "asSnapPoint", ( quint16 )AsMediaContainer::AS_PROPERTY_SNAPPOINT );
//        HashProperties.insert( "asSnapTo", ( quint16 )AsMediaContainer::AS_PROPERTY_SNAPTO );
//        HashProperties.insert( "asCanContain", ( quint16 )AsMediaContainer::AS_PROPERTY_CANCONTAIN );
//        HashProperties.insert( "asContainPointer", ( quint16 )AsMediaContainer::AS_PROPERTY_CONTAINPOINTER );
//        HashProperties.insert( "asContainWords", ( quint16 )AsMediaContainer::AS_PROPERTY_CONTAINWORDS );
//        HashProperties.insert( "asContainRule", ( quint16 )AsMediaContainer::AS_PROPERTY_CONTAINRULE );
//        HashProperties.insert( "asV2Type", ( quint16 )AsMediaContainer::AS_PROPERTY_V2TYPE );
//        HashProperties.insert( "asConnectorList", ( quint16 )AsMediaContainer::AS_PROPERTY_CONNECTORLIST );
//        HashProperties.insert( "asLabel", ( quint16 )AsMediaContainer::AS_PROPERTY_LABEL );
//        HashProperties.insert( "asQuestionItem", ( quint16 )AsMediaContainer::AS_PROPERTY_QUESTIONITEM );
//        HashProperties.insert( "asQuestionItemID", ( quint16 )AsMediaContainer::AS_PROPERTY_QUESTIONITEMID );
//        HashProperties.insert( "asQuestionTag", ( quint16 )AsMediaContainer::AS_PROPERTY_QUESTIONTAG );
//        HashProperties.insert( "asAllowSnapback", ( quint16 )AsMediaContainer::AS_PROPERTY_ALLOWSNAPBACK );
//        HashProperties.insert( "asDragACopy", ( quint16 )AsMediaContainer::AS_PROPERTY_DRAGACOPY );
//		HashProperties.insert( "asAsyncTestTag", ( quint16 )AsMediaContainer::AS_PROPERTY_ASYNCTESTTAG );
//        HashProperties.insert( "asInteractMode", ( quint16 )AsMediaContainer::AS_PROPERTY_INTERACTMODE );

        // From AsWidgetContainer
        HashProperties.insert( "placeHolderResource", ( quint16 )AsMediaContainer::AS_PROPERTY_RESOURCE );
    //    HashProperties.insert( "asForceOverLay", ( quint16 )AsMediaContainer::AS_PROPERTY_FORCEOVERLAY );

        // From AsMediaContainer
        HashProperties.insert( "autoPlay", ( quint16 )AsMediaContainer::AS_PROPERTY_AUTOPLAY );
        HashProperties.insert( "loop", ( quint16 )AsMediaContainer::AS_PROPERTY_LOOP );
       // HashProperties.insert( "asHideControls", ( quint16 )AsMediaContainer::AS_PORPERTY_HIDECONTROLS );
       // HashProperties.insert( "asForceAspect", ( quint16 )AsMediaContainer::AS_PROPERTY_FORCEASPECT );
        HashProperties.insert( "resource", ( quint16 )AsMediaContainer::AS_PROPERTY_MEDIAFILERESOURCE );
        HashProperties.insert( "transparentBackground", ( quint16 )AsMediaContainer::AS_PROPERTY_TRANSPARENTBACKGROUND );
    }
    return HashProperties;
}


void AsMediaContainer::asSetMediaFileResource( AsMediaFileRes *pMediaFileResource )
{

}


AsMediaFileRes* AsMediaContainer::asGetMediaFileResourcePointer()
{
    if( this->m_pMediaFileRes == NULL )
    {
        if( m_mediaFileResource != 0 )
        {
            this->m_pMediaFileRes = ( AsMediaFileRes* )this->m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_MEDIAFILERES, asGetResource() );
            if( m_pMediaFileRes && m_mediaFileResource != m_pMediaFileRes->asGetID() )
            {
                QString sDataFilename = this->m_pAsFactory->getResourceManager()->asGetResourceDataFilename( m_pMediaFileRes );
                QString sWorkingPath = this->m_pAsFactory->getResourceManager()->asGetWorkingPath();
                m_sResFilePath = sWorkingPath + "/" + sDataFilename;

                //this can happen when duplicating multiple pages where a page which is not the current page ( so its resources are not loaded ) has content that has a storage of 
                //AsInternalPathLink. AsInternalPathLink storage does not use a data file so the duplicated page uses the same resource as the existing page. The resource has a 
                //reference in the resource manager with the id as per the existing page. The resource created above has a new id due to the duplication being classed as import in the
                //factory. The resource id needs to match the reference id so the resource is not unloaded when it should not be and can be found in the resource manager when needed.
                m_pMediaFileRes->asSetID( m_mediaFileResource );
            }
        }
    }
    return this->m_pMediaFileRes;
}


bool AsMediaContainer::asCreateWidgetSurface()
{

    return true;
}

bool AsMediaContainer::asCreateSurface()
{

    return true;
}


bool AsMediaContainer::asCreateController()
{

    return true;
}


bool AsMediaContainer::asDoDelayedInitMultiMedia()
{

	
    return true;
}


QRect AsMediaContainer::asGetSurfaceRect()
{

    return QRect();
}








void AsMediaContainer::asOnLoseKeyboardFocus()
{
}


void AsMediaContainer::asOnGainKeyboardFocus()
{
}


void AsMediaContainer::asOnLoseHoverFocus()
{

}


void AsMediaContainer::asOnGainHoverFocus()
{

}


void AsMediaContainer::asOnActiveItem()
{
}


void AsMediaContainer::asOnDeactiveItem()
{
}



QPoint AsMediaContainer::asGetOrigin()
{
   return QPoint();
}


void AsMediaContainer::asMediaObjectStarted()
{
}


void AsMediaContainer::asMediaObjectFinished( QObject* )
{
}


QString AsMediaContainer::asGetNewObjectName(quint32 nIndex)
{
    QString strNextName;

    return strNextName;
}


enum AsWidgetContainer::AsPainterCanvasPaintBufferType AsMediaContainer::asCanvasPaintSourceType()
{
    enum AsWidgetContainer::AsPainterCanvasPaintBufferType ret = AsWidgetContainer::AS_PAINTER_CANVAS_BUFFER_NULL;


    return ret;
}


QMutex* AsMediaContainer::asGetCanvasModeBufferProtection()
{

    return NULL;
}


QPixmap *AsMediaContainer::asCanvasModeGetQPixmap()
{
    QPixmap *pPixmap = NULL;


    return pPixmap;
}




void AsMediaContainer::asDoForceUpdate()
{

}

enum AsWidgetContainer::AsPainterRenderMode AsMediaContainer::asPainterToRender()
{

    return this->m_currentRenderMode;
}


void AsMediaContainer::asUpdateSurfacePosition()
{


}


void AsMediaContainer::asDoPosForceDraw()
{

}





void AsMediaContainer::asUpdateControllerPosition( const QRect & devicePositionOfSurface )
{

}


void AsMediaContainer::asGuiPluginUnloaded()
{
    // we are just about to lose the GUI so destroy all media.
    this->asDestroyMediaObjectAndSurface();
}


void AsMediaContainer::asGuiPluginLoaded()
{
}
 

#include <QDebug>
   
QPixmap* AsMediaContainer::asCaptureCurrentSurface()
{


	QPixmap *pRet = NULL;


	return pRet;
}


void AsMediaContainer::asVideoCaptureInsertIntoFlipchart()
{

}


void AsMediaContainer::asVideoCapturePlaceHolderImage()
{
    this->asCapturePlaceHolderImage();
}

    



bool AsMediaContainer::asIsControllerVisable()
{

    return false;
}


void AsMediaContainer::asControllerShow()
{
    // we don't show the controller if we have nothing active.

}


void AsMediaContainer::asControllerHide()
{

}


void AsMediaContainer::asDoSurfaceDeviceSpaceRectChange( const QRect & newDeviceSpaceRect )
{

}


bool AsMediaContainer::event( QEvent *pEvent )
{

    return false;
}

bool AsMediaContainer::asInitMultiMedia()
{

    return true;
}





void AsMediaContainer::asSetPlaceHolderOnFirstPaint( bool doIt )
{
    qDebug() << "AsMediaContainer::asSetPlaceHolderOnFirstPaint : " << this << ", doit : " << doIt;

    this->m_autoTakePlaceHolderImage = doIt;
    this->m_autoTakePlaceHolderFrameNumber = 1;
    this->m_surfacePaintCount = 0;
}


void AsMediaContainer::asOnFirstFrame()
{

}


void AsMediaContainer::asOnDragAndDropFinished()
{

    this->m_firstRenderDone = true;
}


void AsMediaContainer::asMediaObjectReleased()
{
    if( this->m_pMultiMediaObject != NULL )
    {
        this->m_firstRenderDone = false;
        this->m_currentRenderMode = AsWidgetContainer::AS_PAINTER_RENDER_IMAGE;
        this->m_pMultiMediaObject = NULL;
        this->asDestroyMediaObjectAndSurface();
    }
}


bool AsMediaContainer::asIsActive() const
{

    return false;
}


void AsMediaContainer::asOnSelected()
{
    if( AsWidgetContainer::asIsActive() == false )
    {

	}
}


void AsMediaContainer::asOnDeselected()
{
    if( AsWidgetContainer::asIsActive() == false )
    {

	}
}


void AsMediaContainer::asPushMediaSettingsToCache()
{
    this->m_cachedForceOverlay = this->asGetForceOverlay();
    this->m_cachedAutoPlay = this->m_autoPlay;
    this->m_cachedLoop = this->m_loop;
    this->m_cachedHideControls = this->m_hideControls;
    this->m_cachedForceAspect = this->m_forceAspect;
    this->m_cachedTransparentBackground = this->m_transparentBackground;
}


bool AsMediaContainer::asMediaSettingsDifferantThanCached()
{
    if( this->m_cachedForceOverlay != this->asGetForceOverlay() )
    {
        return true;
    }

    if(  this->m_cachedAutoPlay != this->m_autoPlay )
    {
        return true;
    }

    if( this->m_cachedLoop != this->m_loop )
    {
        return true;
    }
    
    if( this->m_cachedHideControls != this->m_hideControls )
    {
        return true;
    }

    if( this->m_cachedForceAspect != this->m_forceAspect )
    {
        return true;
    }

    if( this->m_cachedTransparentBackground != this->m_transparentBackground )
    {
        return true;
    }

    return false;
}


void AsMediaContainer::asRestartMediaObject()
{
    if( this->m_pMultiMediaObject != NULL )
    {
        // cache the current play/capture state so when we to the restart we know what to do.

        this->asDestroyMediaObjectAndSurface();
    }
    
    if( this->asIsVisible() )
    {
        this->asInitMultiMedia();
	}
}


bool AsMediaContainer::asDoesSupportZReOrderingCommands() const
{
    if (m_pMultiMediaObject)
    {

    }
    return true;
}   


void AsMediaContainer::asMediaContainerProxyForMouseEvents( int , int , int )
{
}

bool AsMediaContainer::asGetPlaceholderRequired()
{
    return m_autoTakePlaceHolderImage;
}

QString AsMediaContainer::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsMediaContainer::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

const Json::Value &AsMediaContainer::asResourceSerialized()
{
    asGetMediaResourcePointer();
    asGetResourcePointer();
    if(m_pMediaFileRes){
        m_resourceJsonObject["mediaUrl"] = m_sResFilePath.toStdString();
    }
    if(m_pImageRes){
        m_resourceJsonObject["tumbFileUrl"] = m_sTumbFilePath.toStdString();
    }
    return m_resourceJsonObject;
}

AsResource *AsMediaContainer::asGetMediaResourcePointer(void)
{
    if( this->m_pMediaFileRes == NULL )
    {

            Variant var = property(AsMediaContainer::AS_PROPERTY_MEDIAFILERESOURCE);
            this->m_pMediaFileRes = ( AsMediaFileRes* )this->m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_MEDIAFILERES,
                                                                                                                 *static_cast<int*>(var.value));
            if( m_pMediaFileRes && m_mediaFileResource != m_pMediaFileRes->asGetID() )
            {
                QString sDataFilename = this->m_pAsFactory->getResourceManager()->asGetResourceDataFilename( m_pMediaFileRes );
                QString sWorkingPath = this->m_pAsFactory->getResourceManager()->asGetWorkingPath();
                m_sResFilePath = sWorkingPath + "/" + sDataFilename;

                //this can happen when duplicating multiple pages where a page which is not the current page ( so its resources are not loaded ) has content that has a storage of
                //AsInternalPathLink. AsInternalPathLink storage does not use a data file so the duplicated page uses the same resource as the existing page. The resource has a
                //reference in the resource manager with the id as per the existing page. The resource created above has a new id due to the duplication being classed as import in the
                //factory. The resource id needs to match the reference id so the resource is not unloaded when it should not be and can be found in the resource manager when needed.
                m_pMediaFileRes->asSetID( m_mediaFileResource );
            }

    }
    return this->m_pMediaFileRes;
}

bool AsMediaContainer::isPropertyNeededSerialized(int nID)
{
    if(getPropertyNameById(nID) == "ink"){
        return  false;
    }
    return true;
}

QString AsMediaContainer::typeName()
{
    return "mediaContainer";
}

