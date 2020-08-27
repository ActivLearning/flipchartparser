// Implements the AsActionOpenExternal class.
// $Author: Paul Ellis.

#include "asactionopenexternal.h"
#include "../asfactory.h"
#include "../resources/asresourcemanager.h"


#include "../resources/asmediafileres.h"



QHash<QString, QString> AsActionOpenExternal::m_mimeTypes;

AsActionOpenExternal::AsActionOpenExternal( AsFactory *pAsFactory ) : AsAction( pAsFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_ACTIONOPENEXTERNAL );
    m_pAsMediaFileRes = NULL;
    m_nResource = 0;
    m_bDisplayInPlace = false;

    m_loop = false;
    m_keepAspect = true;
    m_showController = true;
}

AsActionOpenExternal::AsActionOpenExternal( const AsActionOpenExternal& actionOpenEx ) : AsAction( actionOpenEx )
{
    this->asCopy( actionOpenEx );
}

AsActionOpenExternal::~AsActionOpenExternal()
{
//    if ( m_pAsMediaFileRes != 0 )
//    {
//        this->m_pAsFactory->asGetResourceManager()->asUnloadResource( m_pAsMediaFileRes );
//    }
}

void AsActionOpenExternal::operator= ( const AsActionOpenExternal& actionOpenEx )
{
    AsAction::operator = ( actionOpenEx );
    this->asCopy( actionOpenEx );
}

void AsActionOpenExternal::asCopy( const AsActionOpenExternal& actionOpenEx )
{
    this->m_nResource = actionOpenEx.asGetResource();
    this->m_pAsMediaFileRes = 0;
    this->m_bAutoStart = actionOpenEx.m_bAutoStart;
    this->m_bDisplayInPlace = actionOpenEx.m_bDisplayInPlace;
    this->m_pInPlaceNode = actionOpenEx.m_pInPlaceNode;
    this->m_loop = actionOpenEx.m_loop;
    this->m_keepAspect = actionOpenEx.m_keepAspect;
    this->m_showController = actionOpenEx.m_showController;
}


QHash<QString, quint16>& AsActionOpenExternal::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsActionOpenExternal::AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
        HashProperties.insert( "asActionFeatureType", ( quint16 )AsActionOpenExternal::AS_PROPERTY_ACTIONFEATURETYPE );

        // From AsActionOpenExternal...
        HashProperties.insert( "asResource", ( quint16 )AsActionOpenExternal::AS_PROPERTY_RESOURCE );
        HashProperties.insert( "asInPlace", ( quint16 )AsActionOpenExternal::AS_PROPERTY_ISINPLACE );
        HashProperties.insert( "asInPlaceNode", ( quint16 )AsActionOpenExternal::AS_PROPERTY_INPLACENODE );
        HashProperties.insert( "asAutoStart", ( quint16 )AsActionOpenExternal::AS_PROPERTY_HASAUTOSTART );
        HashProperties.insert( "asCommandLineParameters", ( quint16 )AsActionOpenExternal::AS_PROPERTY_COMMANDLINEPARAMETERS );
        HashProperties.insert( "asLoop", ( quint16 )AsActionOpenExternal::AS_PROPERTY_LOOP );
        HashProperties.insert( "asKeepAspect", ( quint16 )AsActionOpenExternal::AS_PROPERTY_KEEPASPECT );
        HashProperties.insert( "asShowController", ( quint16 )AsActionOpenExternal::AS_PROPERTY_SHOWCONTROLLER );
    }

    return HashProperties;
}

void AsActionOpenExternal::asRun( AsUser*, QPointF )
{
    qDebug( "[ AsActionOpenExternal ] - asRun." );

//    this->asDoConnections();
//    this->asGetResourcePointer();
//
//    if ( m_pAsMediaFileRes != 0 )
//    {
//        const QString & filename = this->m_pAsMediaFileRes->asGetSourceLocation();
//        const QString & mimeType = m_pAsMediaFileRes->asGetMimeType();
//        const QString & displayName = this->m_pAsMediaFileRes->asGetDisplayName();
//        AsNode *pTargetNode = m_pInPlaceNode.asGetNode();
//
//        AsTelemetryController* pTelemetryController = AsTelemetryController::instance();
//        pTelemetryController->asSendTelemetryEvent( mimeType == "application/vnd.promethean.w3c" ? AsTelemetryController::PROMETHEAN_WIDGET_OPENED_EVENT : mimeType == "text/html" ? AsTelemetryController::LINKED_WEBSITE_OPENED_EVENT : AsTelemetryController::LINKED_FILE_OPENED_EVENT );
//
//        if( mimeType == "application/vnd.promethean.w3c" )
//        {
//            AsActivityLauncher* pActivityLauncher = AsActivityLauncher::instance();
//            pActivityLauncher->asLaunchActivityIfPossible( pTargetNode, filename );
//            return;
//        }
//
//        AsStudio* pStudio = AsStudio::asInstance();
//        pStudio->asGetMultiMediaManager()->asSetLaunchHTMLInExtBrowserHint(true);   //Just make sure we launch the external browser rather than the viewing the web page in the embedded multimedia plugin.
//
//        // removed the use of the autostart as people want things to auto start when they click on the action.
//        pStudio->asOpenExtFile( pTargetNode, mimeType, filename, /*this->m_bAutoStart*/ true, this->m_loop, !this->m_showController, this->m_keepAspect, this->m_strCommandLineParameters, displayName );
//
//        pStudio->asGetMultiMediaManager()->asSetLaunchHTMLInExtBrowserHint(false);  //Unset flag and assumes asOpenExtFile() doesn't throw!
//    }
}

void AsActionOpenExternal::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

bool AsActionOpenExternal::asIsResourcePointerValid( void )
{
    return asGetResourcePointer() == NULL ? false : true;
}

unsigned int AsActionOpenExternal::asGetResource( void ) const
{
    return m_nResource;
}

void AsActionOpenExternal::asSetResource( unsigned int nResource )
{
    m_nResource = nResource;
}

AsResource * AsActionOpenExternal::asGetResourcePointer( void )
{
    if ( m_pAsMediaFileRes == 0 )
    {
//        // Load the resource.
//        As::logAndAssert(m_nResource != 0,
//                         "AsActionOpenExternal", "asGetResourcePointer",
//                         "Attempting to load resource when the resource ID has not been set");
//
//        if (m_nResource != 0)
//        {
//            m_pAsMediaFileRes = qobject_cast<AsMediaFileRes *>(m_pAsFactory->asGetResourceManager()->asLoadResource( AsObject::AS_OBJECT_MEDIAFILERES, m_nResource ));
//        }
    }

    return m_pAsMediaFileRes;
}

void AsActionOpenExternal::asSetResource( AsResource *pResource )
{
//    m_pAsMediaFileRes = qobject_cast< AsMediaFileRes * >( pResource );
//    if ( m_pAsMediaFileRes != NULL )
//    {
//        m_nResource = m_pAsMediaFileRes->asGetID();
//    }
//    else
//    {
//        m_nResource = 0;
//    }
//    this->asSetDirtyForWrite( true );
}

void AsActionOpenExternal::asSetInPlace( bool inPlace )
{
    m_bDisplayInPlace = inPlace;
}

bool AsActionOpenExternal::asIsInPlace( void ) const
{
    return m_bDisplayInPlace;
}

void AsActionOpenExternal::asSetInPlaceNode( AsPointer pTargetNode )
{
    m_pInPlaceNode = pTargetNode;
}

const AsPointer AsActionOpenExternal::asGetInPlaceNode( void ) const
{
    return m_pInPlaceNode;
}

void AsActionOpenExternal::asSetAutoStart( bool autoStart )
{
    m_bAutoStart = autoStart;
}

bool AsActionOpenExternal::asHasAutoStart( void ) const
{
    return m_bAutoStart;
}

void AsActionOpenExternal::asSetCommandLineParameters(QString strCommandLineParameters)
{
    m_strCommandLineParameters = strCommandLineParameters;
}

QString AsActionOpenExternal::asGetCommandLineParameters() const
{
    return m_strCommandLineParameters;
}


bool AsActionOpenExternal::asGetLoop() const
{
    return m_loop;
}

bool AsActionOpenExternal::asGetKeepAspect() const
{
    return m_keepAspect;
}

bool AsActionOpenExternal::asGetShowController() const
{
    return m_showController;
}


void AsActionOpenExternal::asSetLoop( bool loop )
{
    m_loop = loop;
}

void AsActionOpenExternal::asSetKeepAspect( bool keepAspect )
{
    m_keepAspect = keepAspect;
}

void AsActionOpenExternal::asSetShowController( bool showController )
{
    m_showController = showController;
}

QString AsActionOpenExternal::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsActionOpenExternal::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsActionOpenExternal::typeName()
{
    return "actionOpenExternal";
}


