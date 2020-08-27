// Defines the AsMediaContainer class.
// (c) 2008 Promethean Technologies Group Ltd.#ifndef ASMEDIACONTAINER_H
#ifndef ASMEDIACONTAINER_H
#define ASMEDIACONTAINER_H

#include <QPointer>
#include <QMutex>

#include "aswidgetcontainer.h"


// Forward decs.
class AsMultiMediaObject;
class AsMediaFileRes;
class AsCamera;
class AsMediaContainer;






/** This class is used to represent an "in-canvas" media objects such as movies.
* This class forms part of the internal object types for flipcharts and is based on AsRenderable so it can be handled by the painter.
* 
*/
class AsMediaContainer : public AsWidgetContainer
{
	/// The media container surface class whats to be a friend.
    friend class AsMediaContainerSurface;



    Q_PROPERTY( bool asAutoPlay READ asGetAutoPlay WRITE asSetAutoPlay EDITABLE true )
    Q_PROPERTY( bool asLoop READ asGetLoop WRITE asSetLoop EDITABLE true )
    Q_PROPERTY( bool asHideControls READ asGetHideControls WRITE asSetHideControls EDITABLE true )
    Q_PROPERTY( bool asForceAspect READ asGetForceAspect WRITE asSetForceAspect EDITABLE true )
    Q_PROPERTY( bool asTransparentBackground READ asGetTransparentBackground WRITE asSetTransparentBackground EDITABLE true )
    Q_PROPERTY( unsigned int asMediaFileResource READ asGetMediaFileResource WRITE asSetMediaFileResource )



public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsRenderable...
        AS_PROPERTY_TRANSFORM = 2,
        AS_PROPERTY_TWIPS = 3,
        AS_PROPERTY_NAME = 4,
        AS_PROPERTY_KEYWORDS = 5,
        AS_PROPERTY_VISIBLE = 6,
        AS_PROPERTY_BOUNDINGRECT = 7,
        AS_PROPERTY_LAYER = 8,
        AS_PROPERTY_Z = 9,
        AS_PROPERTY_INK = 10,
        AS_PROPERTY_SCALEORIGIN = 11,
        AS_PROPERTY_ROTATEORIGIN = 12,
        AS_PROPERTY_CANMOVE = 13,
        AS_PROPERTY_CANSIZE = 14,
        AS_PROPERTY_CANROTATE = 15,
        AS_PROPERTY_CANBLOCK = 16,
        AS_PROPERTY_CANSNAP = 17,
        AS_PROPERTY_LOCKED = 18,
        AS_PROPERTY_SNAPBACK = 19,
        AS_PROPERTY_PATHPOINTER = 20,
        AS_PROPERTY_ROTATEABOUTPOINTER = 21,
        AS_PROPERTY_ROTATEPOINT = 22,
        AS_PROPERTY_ROTATEABOUT = 23,
        AS_PROPERTY_ROTATESTEP = 24,
        AS_PROPERTY_SNAPTOPOINTER = 25,
        AS_PROPERTY_SNAPPOINT = 26,
        AS_PROPERTY_SNAPTO = 27,
        AS_PROPERTY_CANCONTAIN = 28,
        AS_PROPERTY_CONTAINPOINTER = 29,
        AS_PROPERTY_CONTAINWORDS = 30,
        AS_PROPERTY_CONTAINRULE = 31,
        AS_PROPERTY_V2TYPE = 32,
        AS_PROPERTY_CONNECTORLIST = 33,
        AS_PROPERTY_LABEL = 34,
        AS_PROPERTY_QUESTIONITEM = 35,
        AS_PROPERTY_QUESTIONITEMID = 36,
		AS_PROPERTY_ALLOWSNAPBACK = 37,
        AS_PROPERTY_DRAGACOPY = 40,
        AS_PROPERTY_QUESTIONTAG = 46,
		AS_PROPERTY_ASYNCTESTTAG = 48,
        AS_PROPERTY_INTERACTMODE = 49,


        // From AsWidgetContainer
        AS_PROPERTY_RESOURCE = 38,
        AS_PROPERTY_FORCEOVERLAY = 39,

        // From AsMediaContainer
        AS_PROPERTY_AUTOPLAY = 41,
        AS_PROPERTY_LOOP = 42,
        AS_PORPERTY_HIDECONTROLS = 43,
        AS_PROPERTY_FORCEASPECT = 44,

        AS_PROPERTY_MEDIAFILERESOURCE = 45,
        AS_PROPERTY_TRANSPARENTBACKGROUND = 47,

        // Next id = 50

    };

    QRect asGetSurfaceRect();

    AsMediaContainer( AsFactory * );
    AsMediaContainer( const AsMediaContainer & );
    ~AsMediaContainer();

    void operator = ( const AsMediaContainer & );
    bool operator == ( const AsMediaContainer & );

    bool event( QEvent *pEvent );


    /// Qt Streamable propertys interfaces
    //@{
    bool asGetAutoPlay() const;
    bool asGetLoop() const;
    bool asGetHideControls() const;
    bool asGetForceAspect() const;
    const QString & asGetMimeType() const;
    const QString & asGetSourceUrl() const;
    unsigned int asGetMediaFileResource() const;
    bool asGetTransparentBackground() const;

    void asSetAutoPlay( bool & );
    void asSetLoop( bool & );
    void asSetHideControls( bool & );
    void asSetForceAspect( bool & );
    void asSetMediaFileResource( unsigned int & id );
    void asSetTransparentBackground( bool & );
    //@}
    
    /// Called by the render to tell how to paint the object.
    enum AsWidgetContainer::AsPainterRenderMode asPainterToRender();

    /// Call this to init the media object. The creation will be done async so not to mess with Qt and its backing store.
    bool asInitMultiMedia();

    /// Used this to (re-)set the media file resource object.
    void asSetMediaFileResource( AsMediaFileRes *pMediaFileResource );

    AsMediaFileRes* asGetMediaFileResourcePointer();

    enum AsPainterCanvasPaintBufferType asCanvasPaintSourceType();



    // True if the object is to display it's controller.
    bool asIsControllerVisable();

    ///
    QMutex* asGetCanvasModeBufferProtection();

    /// Returns the current Pixmap.
    QPixmap *asCanvasModeGetQPixmap();



    void asResetPropertyIndex();

    // dep.
    bool asIsActive() const override ;



    /// Used when an widget container gains or loses the keyboard focus.
    //@{
    void asOnLoseKeyboardFocus();
    void asOnGainKeyboardFocus();
    //@}
    
    /// Used when the widget container gains or loses the hover focus.
    //@{
    void asOnLoseHoverFocus();
    void asOnGainHoverFocus();
    //@}

    /// Called when the item become the that active or deactive widget container.
    //@{
    void asOnActiveItem()override ;
    void asOnDeactiveItem()override ;
    //@}

    virtual QString asGetNewObjectName(quint32 nIndex)override ;

    /// Call this to update the painter.
    void asDoForceUpdate();
    
    // Do the draw of the plugin now!
    void asDoPosForceDraw();
    
	QPoint asGetOrigin();

    QPixmap* asCaptureCurrentSurface();
    
    void asDoSurfaceDeviceSpaceRectChange( const QRect & newDeviceSpaceRect );

    void asSetPlaceHolderOnFirstPaint( bool doIt = true );
    

    /// Use this to clear the media object and clean up any surfaces.
    void asDestroyMediaObjectAndSurface();

    // Used to determine whether z-ordering commands are applicable to this multimedia object i.e. Bring Forwards/Send to Back etc
    bool asDoesSupportZReOrderingCommands() const;
    
    /*! Called when the container is hidden to shown.  This overrides what is @AsRenderable but we do call the base method as well. */ 
	void asSetVisible( bool bVisible )override ;

    void asUpdateSurfacePosition();

    bool asGetPlaceholderRequired();

public slots:
    /// hooked to the media object and captures the pre start signal and will create the video widget.
    void asMediaObjectStarted();

	/// Called by the media object when it has finished.
	/// \arg pMediaObject The media object finishing.
	void asMediaObjectFinished( QObject *pMediaObject );

    // Called if the media object is released outside of the media container.  This is possable.
    void asMediaObjectReleased();






	/// Called when a GUI plugins is unloaded. This is protection if the canvas is still active but the current GUI plugin
	/// is unloaded. Basic support for runtime switching of the GUIs.
    void asGuiPluginUnloaded();

	/// Called when a GUI plugin is loaded. Basic support for runtime switching of GUIs.
    void asGuiPluginLoaded();
    
	/// Use to insert the current video frame into the current flipchart as an AsImage. 
    void asVideoCaptureInsertIntoFlipchart();
	
	/// Set the current video frame as the place holder image.
    void asVideoCapturePlaceHolderImage();
    
	/// Used to show the controller, if the controller is enabled.
    void asControllerShow();
	
	/// Used to hide the controller.
    void asControllerHide();    
    	
	/// Used to watch when an object is being edited.
	/// \arg pPageNode The page node of the node that is being edited.
    /// \arg pObjectNode The node being edited.
	void asOnObjectEditing( AsNode *pPageNode, AsNode *pObjectNode );
	
	/// Used to watch when an object has been edited.
	/// \arg pPageNode The page node of the node that is being edited.
	/// \arg pObjectNode The node that has been edited.
    void asOnObjectEdited( AsNode *pPageNode, AsNode *pObjectNode );

	/// Called by the media object has rendered its first frame.  This allows the first frame to be captured and set as the placeholder.
    void asOnFirstFrame();
    
    void asOnDragAndDropFinished();
   
	/// Added to support media containers that don't populate mouse events up so the existing code does not work.
	/// \arg button Which button is down. 0 = none 1=left
	/// \arg x The x offset in the local coordinates of the container, these will need to be translated.
	/// \arg y The y offset in the local coordinates of the container. 
	void asMediaContainerProxyForMouseEvents( int button, int x, int y );

    AsResource *  asGetMediaResourcePointer();

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

    const Json::Value &asResourceSerialized() override;

    bool isPropertyNeededSerialized(int nID) override;

private:
	/// Protection.
    QMutex m_creationMutex;
    


    bool m_isPlayingBeforeHidding;

    /// Streamable propertys.
    //@{
	/// Used to see if the media object should start when the media object is first visable.
    bool m_autoPlay;
	/// Used to see if the media object should loop or not.
    bool m_loop;
	/// Used to see if the controls are to be displied or not.
    bool m_hideControls;
	/// Force aspect of the video surface, what ratio is up to the media object if supported.
    bool m_forceAspect;
	// Currently only for flash, if true then movie is set true then wmode = transparent.
    bool m_transparentBackground;   
    /// The media resource file id.
    unsigned int m_mediaFileResource;
    //@}

    /// Used to cache the state of the media settings for the media container when media object is created.
    //@{
    bool m_cachedForceOverlay;
    bool m_cachedAutoPlay;
    bool m_cachedLoop;
    bool m_cachedHideControls;
    bool m_cachedForceAspect;
    bool m_cachedTransparentBackground;
    /// Used to see if the item was playing.
    bool m_cahcedRestartWasPlaying;
    
    /// Used to push the current media settings to the cache so the cache can be used to see what has changed on an object edited call.
    void asPushMediaSettingsToCache();
    
    /// Used to see if the current settings have changed against those in the cache.
    bool asMediaSettingsDifferantThanCached();
    //@}


    /// Runtime propertys
    //@{
    // Use to stop multi creations of failing creates.
    bool m_unableToCreateMultiMediaObject;
    bool m_unableToCreateController;
    bool m_unableToCreateSurfaceWidget;
    bool m_unableToCreateSurface;

	/// Goes true when the first frame is done.
    bool m_firstRenderDone;
	
	/// Used to see if the media container should take "focus" on creation.
    bool m_giveFocusOnCreate;
    
	// If there is a delta of device space between paints it can be due to a number of things.
    // if this is true one of them was a editing/ed action, if so we should not send the update 
    // event from the painter
    bool m_knownDeviceSpaceRectChange;

    /// The Media File res pointer.
    AsMediaFileRes *m_pMediaFileRes;

    /// The MultiMedia Object.
    AsMultiMediaObject *m_pMultiMediaObject;

    /// The current Rendering model being used.
    enum AsWidgetContainer::AsPainterRenderMode m_currentRenderMode;

    /// The widget used to host the media object in overlay mode.
    QWidget *m_pTheSurfaceWidget;



	/// The current surface size.
    QSize m_theSurfaceSize;

	/// Flag used to tell the container to take a snapshot of a given frame and set that as the placeholder image.
    bool m_autoTakePlaceHolderImage;
	
	/// defines when the placeholder frame should be taken if m_autoTakePlaceHolderImage is set true.  This is used as we might not want the very first frame.
    quint32 m_autoTakePlaceHolderFrameNumber;
	
	/// Counter of the number of paints.
    quint32 m_surfacePaintCount;
    


	/// Used to see if the object is selected or not. This is used as some media types (flash) have differant behavord between selected and none-selected.
	bool m_bSelected;
	
	/// Used to indecate that we have wired up the main signals and slots to objects such as asStudio et al.
	bool m_needToDoMainSignalsAndSlotsConnection;
    //@}

	/// Part of the object properies system.
    static QHash<QString, quint16>& m_lProperties( void );

	/// Used to copy a media container.
    void asCopy( const AsMediaContainer & );

    /// Top level method that will create the surface or widget to display the visual content.
    bool m_isContextCreated;

	/// Used to clear/set default all the properties of this class.
    void asClear();

	/// Used to see if the file is a local file ( ie on the local file system ) or not.
	/// \arg filePath The path to test.
	/// \return true if the path is local.
    bool asIsLocalFile( const QString & filePath );

	/// The media creation state enums
    enum AsMediaCreationState 
	{ 
		/// Media object has not been creaded yet.
		NotCreated, 
		/// The creation of the media object is waiting to accure. ie it's pending (waiting for the creation event to be handled)
		WaitingForCreation, 
		/// The media object is created.
		Created
	};
	
	/// The current media creation state.
    enum AsMediaCreationState m_creationState;
        
	/// This does the creation of the multimedia object.
    bool asDoDelayedInitMultiMedia();

    void asCreateContext();

    /// Used to create the differant child objects.
    //@{
    bool asCreateController();
	
    // Used to update the current surface and controller using the current device position.
//    void asUpdateSurfacePosition();
    
	/// Used to update the postion of the controller, if it's selected.
	/// \arg devicePostionOfSurface The position of the controller in device space.
    void asUpdateControllerPosition( const QRect & devicePostionOfSurface );
    
	/// Used to create a widget surface/
	/// \return true if the surface widget was created.
    bool asCreateWidgetSurface();
	
	/// Used to create an in-canvas surface.
	/// \return true if the surface was created.
    bool asCreateSurface();
    //@}
    
	/// Called when the object is selected.
	void asOnSelected()override ;
	
	/// Called when the object is deselected.
	void asOnDeselected()override ;

    /// Used to restart the media object.  Handly when a setting changes.
    /// This will destroy the current running instance, if there is one and then start a new media object using the delayed start up call.
    void asRestartMediaObject();

    QString m_sResFilePath;
};


#endif // ASMEDIACONTAINER_H



