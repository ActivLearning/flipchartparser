


#include <QTemporaryFile>




#include "../util/asutil.h"
#include "aswidgetcontainer.h"

#include "../asfactory.h"
#include "../resources/asresourcemanager.h"
#include "../resources/asimageres.h"


#include "aspage.h"



AsWidgetContainer::AsWidgetContainer( AsFactory *pFactory )
	: AsRenderable( pFactory )
{
    this->asClear();
}



AsWidgetContainer::AsWidgetContainer( const AsWidgetContainer & other )
	: AsRenderable( other )
{
    this->asClear();
	this->asCopy( other );
}


AsWidgetContainer::~AsWidgetContainer()
{

}


void AsWidgetContainer::operator = ( const AsWidgetContainer & other )
{
	AsRenderable::operator = ( other );
	this->asCopy( other );
}


bool AsWidgetContainer::operator == ( const AsWidgetContainer & other )
{
	bool ret = false;
	if( AsRenderable::operator == ( other ) )
	{
		if( this->m_resourceId == other.m_resourceId &&
			this->m_forceOverlay == other.m_forceOverlay )
		{
			ret = true;
		}
	}
	return ret;
}


bool AsWidgetContainer::asIsActive() const
{ 
    return false;
} 


bool AsWidgetContainer::asCheckHit( const QPointF & worldPos )
{
    bool ret = false;

    AsRectF theRect = this->asGetTransformedBoundingRect();
    
    if( theRect.contains( worldPos ) )
    {
        ret = true;
    }
    return ret;
}


void AsWidgetContainer::asClear()
{
    /// stream
    this->m_resourceId = 0;
    
    /// Dont by default for overlay.
    this->m_forceOverlay = false;

    // default to locking rotation.
    this->m_lockRotationState = true;
    
	this->m_isSelected = false;    
    
    /// Runtime.
    this->m_pImageRes = NULL;
    

}
    

void AsWidgetContainer::asCopy( const AsWidgetContainer & other )
{
	this->m_resourceId = other.m_resourceId;
	this->m_forceOverlay = other.m_forceOverlay;
	this->m_lockRotationState = other.m_lockRotationState;
}




bool AsWidgetContainer::asGetForceOverlay() const
{
    return this->m_forceOverlay;
}


void AsWidgetContainer::asSetResource( AsResource *pRes )
{

}


void AsWidgetContainer::asSetResource( const unsigned int & res )
{
    this->m_resourceId = res;
}   


void AsWidgetContainer::asSetForceOverlay( const bool & v )
{
    this->m_forceOverlay = v;
}


/// Runtime propertes.
void AsWidgetContainer::asSetRotationLockState( bool lockState )
{
	this->m_lockRotationState = lockState;
}


bool AsWidgetContainer::asGetRotationLockState() const
{
	return this->m_lockRotationState;
}


bool AsWidgetContainer::asIsResourcePointerValid( void )
{
	return asGetResourcePointer() == NULL ? false : true;
}


AsResource* AsWidgetContainer::asGetResourcePointer()
{
    // do on demand loading of the resource.
    if( this->m_pImageRes == NULL )
    {
        Variant var = property(38);
        this->m_pImageRes = dynamic_cast<AsImageRes*>(m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_IMAGERES, *static_cast<int*>(var.value)));

        if (m_pImageRes != 0)
        {
            // Load the image data and construct the image.
            QString sDataFilename = this->m_pAsFactory->getResourceManager()->asGetResourceDataFilename( ( AsResource* )this->m_pImageRes );
            QString sWorkingPath = this->m_pAsFactory->getResourceManager()->asGetWorkingPath();
            m_sTumbFilePath = sWorkingPath+"/"+sDataFilename;
//            asLoadResourceDataFile( sDataFilename, sWorkingPath );
        }
    }
    return this->m_pImageRes;
}


bool AsWidgetContainer::asLoadResourceDataFile( const QString& filename, const QString& path )
{
    // Load the image data and construct the image.
    return false;
}


AsRenderable::AsEnumCanRotate AsWidgetContainer::asGetCanRotate( void ) const
{
    if( !this->m_lockRotationState )
    {
        return AsRenderable::asGetCanRotate();
    }
    return AsRenderable::ASCANROTATE_NONE;
}


void AsWidgetContainer::asSetCanRotate( AsRenderable::AsEnumCanRotate rotationState )
{
    if( !this->m_lockRotationState )
    {
        AsRenderable::asSetCanRotate( rotationState ); 
    }
}


AsCamera* AsWidgetContainer::asGetCamera()
{
    AsCamera *pRet = NULL; 

    return pRet;
}


void AsWidgetContainer::asSetPlaceHolderImage( const QPixmap & newPlaceHolderImage, bool doPageUpdate )
{

}


void AsWidgetContainer::asCapturePlaceHolderImage()
{


}


void AsWidgetContainer::asOnSelected()
{
}


void AsWidgetContainer::asOnDeselected()
{
}


bool AsWidgetContainer::asGetSelected() const
{
	return this->m_isSelected;
}


void AsWidgetContainer::asSetSelected( bool isSelected )
{
	if( this->m_isSelected == isSelected )
	{
		return;
	}

	// update the runtime setting and inform the object of the selection change.
	this->m_isSelected = isSelected;
	if( isSelected )
	{
		this->asOnSelected();
	}
	else
	{
		this->asOnDeselected();
	}
}



void AsWidgetContainer::asOnNodeAddedToMarqueeSelectionList( AsNode *pNode )
{
    AsNode *pThisNode = this->asGetIndexNode();
    if( pThisNode == pNode )
    {
        this->asSetSelected( true );
    }
}

void AsWidgetContainer::asOnNodeRemovedFromMarqueeSelectionList( AsNode *pNode )
{
    AsNode *pThisNode = this->asGetIndexNode();
    if( pThisNode == pNode )
    {
        this->asSetSelected( false );
    }
}

void AsWidgetContainer::asOnMarqueeSelectionClearing( AsMarqueeSelect *pClearing )
{

}

