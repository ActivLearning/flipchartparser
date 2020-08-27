// Defines the AsWidgetContainer class.
// (c) 2008 Promethean Technologies Group Ltd.
#ifndef ASWIDGETCONTAINER_H
#define ASWIDGETCONTAINER_H




#include "asrenderable.h"

class AsImageRes;
class AsUser;
class AsCamera;
class AsMarqueeSelect;



/**
 * A base class for containers in a flipchart
 */
class AsWidgetContainer : public AsRenderable
{

	/// The image res for the container, this should always be there as a fallback.
	Q_PROPERTY( unsigned int asPlaceHolderResource READ asGetResource WRITE asSetResource )
	Q_PROPERTY( bool asForceOverLay READ asGetForceOverlay WRITE asSetForceOverlay EDITABLE true )

public:
    // How the painter should handle this object.
    enum AsPainterRenderMode 
    {   
        /// We dont want the item to painted at all.
        AS_PAINTER_RENDER_DONT,
        /// We are just painting the place holder image.
        AS_PAINTER_RENDER_IMAGE,  
        /// We are painting to a widget which is over the canvas.
        AS_PAINTER_RENDER_WIDGET_SURFACE,
        /// We are painting into the canvas as part of the normal AsPainter.
        AS_PAINTER_RENDER_CANVAS_SURFACE,
    };

    /// The painter need to know what to paint if in canvas paint mode.
    /// This is due to the workers might present as pixmap or bitmap.
    enum AsPainterCanvasPaintBufferType 
    {   
        /// Used to tell the painter there is no image type to handle.
        AS_PAINTER_CANVAS_BUFFER_NULL,
        /// Used to tell the painter to paint using QPixmap.
        AS_PAINTER_CANVAS_BUFFER_QPIXMAP,
        /// Used to tell the painter to paint using a QImage.
        AS_PAINTER_CANVAS_BUFFER_QIMAGE
    };

	/* This enum list needs to be in any derived classes.
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
        AS_PROPERTY_DEPRECATED_2 = 35,
        AS_PROPERTY_DEPRECATED_1 = 36,
		AS_PROPERTY_ALLOWSNAPBACK = 37,
        AS_PROPERTY_TRANSLUCENCY = 38,
        AS_PROPERTY_DRAGACOPY = 42,
        AS_PROPERTY_QUESTIONTAG = 43,

        // From AsAnnotation...
        AS_PROPERTY_RESOURCE = 39,
        AS_PROPERTY_FORCEOVERLAY = 40,

        // Next Prop ID = 44
    };
	*/

	AsWidgetContainer( AsFactory *pFactory );
	AsWidgetContainer( const AsWidgetContainer & );

	~AsWidgetContainer();

	void operator = ( const AsWidgetContainer & );

	bool operator == ( const AsWidgetContainer & );

    /// Called when the item become the that active.
    virtual void asOnActiveItem() = 0;

    /// Called when deactive widget container.
    virtual void asOnDeactiveItem() = 0;

    /// Used to see if the object is not just in place holder mode.
    virtual bool asIsActive() const; 

    /// Used to tell if we are in hit test.
    bool asCheckHit(  const QPointF & worldPos );




    //@}

	void asSetResource( const unsigned int & );
	void asSetResource( AsResource *pRes );
    bool asLoadResourceDataFile( const QString& filename, const QString& path );

	bool asGetForceOverlay() const;
	void asSetForceOverlay( const bool & );
	//@}

	/// Runtime propertys
	//{@
	// Used this to set the rotation state.  The idea is that a derived class can turn on and off rotation at run time.
	void asSetRotationLockState( bool unlockState );
	bool asGetRotationLockState() const;
	
	AsResource* asGetResourcePointer();

    

    //@}

    // Overrides to AsRenderable
    AsRenderable::AsEnumCanRotate asGetCanRotate( void ) const;
    void asSetCanRotate( AsRenderable::AsEnumCanRotate );

    /// Helper function to get the current Camera.
    AsCamera* asGetCamera();
    
    /// Used to return the current state of the surface, this might not be a clean image as it might come from a screen capture.

    virtual void asCapturePlaceHolderImage();    
    
    // Used in the painter to see if there is a differance in device space rects.
    bool asIsCachedDeviceSpaceDifferance( const QRect & deviceSpaceRect );

	bool asIsResourcePointerValid( void );
    
    /// Used to see if the item is selected or not.
    bool asGetSelected() const;
    
    /// Used to set the item as selected. When the select changes the virtual methods asOnSelected or asOnDeselected will be called.
    /// \arg isSelected true or false
    void asSetSelected( bool isSelected );
    
public slots:
    void asSetPlaceHolderImage( const QPixmap & newPlaceHolderImage, bool doPageUpdate = true );
    
    void asOnNodeAddedToMarqueeSelectionList( AsNode *pNode );
    
    void asOnNodeRemovedFromMarqueeSelectionList( AsNode *pNode );
    
    /// signal used to tell that a marquee selection list is being cleared.
    void asOnMarqueeSelectionClearing( AsMarqueeSelect *pClearing );
    
    
protected:   
    /// Caches.
    //@{
    QRectF m_cacheWorldSpaceRect;
    QRect m_cacheDeviceSpaceRect;
    //@}
    QString m_sTumbFilePath;
	/// Called when the object is selected.
	virtual void asOnSelected();
	
	/// Called when the object is deselected.
	virtual void asOnDeselected();

    AsImageRes *m_pImageRes;
private:
    /// The device space rect of the widget container.
    QRect m_cacheTheDeviceSpaceRect;

	/// Properties that are streamed out.
	//@{
	// id of the image resource used as the place holder image
	unsigned int m_resourceId;

	// Force an overlay or not.
	bool m_forceOverlay;
	//@}

	/// Runtime properties.
	//@{
	// The image res object when loaded.

	// Stop the item from being rotated.
	bool m_lockRotationState;
	/// Used to see if the item is selected or not.
	bool m_isSelected;
	
	//@}

    /// Clear the object to default states.
    void asClear();

    /// Used to copy one widget container to another.
	void asCopy( const AsWidgetContainer & );
};



#endif // ASWIDGETCONTAINER_H

