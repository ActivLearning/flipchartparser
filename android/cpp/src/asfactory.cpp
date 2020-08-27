#include "asfactory.h"

#include "io/asnode.h"
#include "objects/asvirtualfolder.h"
#include "objects/asflipchart.h"
#include "objects/asink.h"
#include "objects/asorigin.h"
#include "objects/astransform.h"
#include "objects/astext.h"
#include "objects/astextrun.h"
#include "objects/asimage.h"
#include "objects/asannotation.h"
#include "objects/asbackground.h"
#include "objects/asgrid.h"
#include "objects/aspage.h"
#include "objects/asrenderablegroup.h"
#include "objects/asshape.h"
#include "objects/asmediacontainer.h"
#include "resources/asresource.h"
#include "resources/asresourceregister.h"
#include "resources/asresourcemanager.h"
#include "resources/asannotationres.h"
#include "resources/asimageres.h"
#include "resources/astextres.h"
#include "resources/asshaperes.h"
#include "resources/asmediafileres.h"
#include "util/commonlog.h"
#include "resources/asmotion.h"
#include "objects/asactionmove.h"
#include "objects/asactionontext.h"
#include "objects/asactiononobject.h"
#include "objects/asactionapp.h"
#include "objects/asactionnavigate.h"
#include "objects/asactionopenexternal.h"
#include "objects/asactionlaunchminiapp.h"
#include "objects/asline.h"

AsFactory::AsFactory()
 : m_pFlipchart(nullptr),
   m_pResourceRegister(nullptr),
   m_pResourceManager(nullptr)
{
}

AsFactory::~AsFactory()
{
    QList<AsVirtualFolder *> folders = m_VirtualFolders.values();
    foreach (AsVirtualFolder *pFolder, folders)
    {
        delete pFolder;
    }
    foreach(AsNode *node ,m_Nodes){
        delete  node;
    }
    foreach(AsObject *object ,m_Objects){
        delete  object;
    }
//    if(m_pResourceManager){
//        delete m_pResourceManager;
//    }
}

AsResourceManager *AsFactory::getResourceManager()
{
    return m_pResourceManager;
}

void AsFactory::setResourceManager(AsResourceManager *pAsResourceManager)
{
    m_pResourceManager = pAsResourceManager;
    m_pResourceManager->asConfigure(m_pFlipchart);
}

AsObject *AsFactory::asCreateObject(AsObject::AsEnumObjectType tType, quint32 nID)
{
    AsObject *pAsObject = nullptr;

    if (m_Objects.contains(nID))
    {
        pAsObject = m_Objects.value(nID);
    }
    else
    {
        switch (tType)
        {
        case AsObject::AS_OBJECT_BACKGROUND:
             pAsObject = new AsBackground(this);
             break;
        case AsObject::AS_OBJECT_FLIPCHART:
            m_pFlipchart = new AsFlipchart(this);
            pAsObject = m_pFlipchart;
            break;
        case AsObject::AS_OBJECT_RESOURCEREGISTER:

           // m_pFlipchart. ->asSetResourceRegister( *pReg );

            pAsObject = new AsResourceRegister();
            m_pFlipchart->asSetResourceRegister(static_cast<AsResourceRegister*>(pAsObject));
            break;
        case AsObject::AS_OBJECT_INK:
            pAsObject = new AsInk();
            break;
        case AsObject::AS_OBJECT_TRANSFORM:
            pAsObject = new AsTransform(this);
            break;
        case AsObject::AS_OBJECT_ORIGIN:
            pAsObject = new AsOrigin(this);
            break;
        case AsObject::AS_OBJECT_TEXTRUN:
            pAsObject = new AsTextRun(this);
            break;
        case AsObject::AS_OBJECT_TEXT:
            pAsObject = new AsText(this);
            break;
        case AsObject::AS_OBJECT_IMAGE:
            pAsObject = new AsImage(this);
            break;
        case AsObject::AS_OBJECT_ANNOTATION:
            pAsObject = new AsAnnotation(this);
            break;
        case AsObject::AS_OBJECT_GRID:
            pAsObject = new AsGrid( this );
            break;
        case AsObject::AS_OBJECT_PAGE:
            pAsObject = new AsPage( this );
            break;
        case AsObject::AS_OBJECT_ANNOTATIONRES:
            pAsObject = new AsAnnotationRes( this );
            break;
        case AsObject::AS_OBJECT_IMAGERES:
            pAsObject = new AsImageRes( this );
            break;
        case AsObject::AS_OBJECT_TEXTRES:
            pAsObject = new AsTextRes( this );
            break;
        case AsObject::AS_OBJECT_SHAPERES:
            pAsObject = new AsShapeRes( this );
            break;
        case AsObject::AS_OBJECT_ASRENDERABLEGROUP:
            pAsObject = new AsRenderableGroup(this);
            break;
        case AsObject::AS_OBJECT_SHAPE:
            pAsObject = new AsShape(this);
            break;
        case AsObject::AS_OBJECT_MEDIAFILERES:
            pAsObject = new AsMediaFileRes(this);
            break;
        case AsObject::AS_OBJECT_MEDIACONTAINER:
            pAsObject = new AsMediaContainer(this);
            break;
        case AsObject::AS_OBJECT_MOTIONRES:
            pAsObject = new AsMotion(this);
            break;
        case AsObject::AS_OBJECT_LINE:
            pAsObject = new AsLine(this);
            break;
        case AsObject::AS_OBJECT_LINERES:
            pAsObject = new AsLineRes(this);
            break;
        case AsObject::AS_OBJECT_MOVEACTION:
            pAsObject = new AsActionMove(this);
            break;
        case AsObject::AS_OBJECT_ACTIONONTEXT:
            pAsObject = new AsActionOnText(this);
            break;
        case AsObject::AS_OBJECT_ACTIONONOBJECT:
            pAsObject = new AsActionOnObject(this);
            break;
        case AsObject::AS_OBJECT_APPACTION:
            pAsObject = new AsActionApp(this);
            break;
        case AsObject::AS_OBJECT_NAVIGATEACTION:
            pAsObject = new AsActionNavigate(this);
            break;
        case AsObject::AS_OBJECT_ACTIONOPENEXTERNAL:
            pAsObject = new AsActionOpenExternal(this);
            break;
        case AsObject::AS_OBJECT_LAUNCH_MINIAPP_ACTION:
            pAsObject = new AsActionLaunchMiniApp(this);
            break;
        default:
            pAsObject = new AsObject();
            break;
        }

        // Keep a record of the object on the correct list.
        if (nID >= AsFactory::AS_ID_BASE)
        {
            // Real flipchart objects (renderables and actions etc.).
            m_Objects.insert(nID, pAsObject);
        }
        else if (nID == AsFactory::AS_ID_PROPERTY)
        {
            // AsObjects that are properties of other AsObjects (exist only while streaming in!).
            m_Properties.append(pAsObject);
        }
        pAsObject->asSetType(tType);
        pAsObject->asSetID(nID);
    }

    return pAsObject;
}

bool AsFactory::asDeleteObject( AsObject *pAsObject )
{
    LOGDEBUG("###Delete Object:%d,%d",pAsObject->asGetType(),pAsObject->asGetID());
    return  true;
}

bool AsFactory::asChangeObjectID( quint32 oldID, quint32 newID )
{
    // First, check we have an object with this ID.
    AsObject *pObject = m_Objects.value( oldID );
    if ( pObject == 0 )
    {
        return false;
    }

    // Next, check there are no other objects or nodes with the new ID.
    if (( m_Objects.contains( newID )) ||
        ( m_Nodes.contains( newID )))
    {
        return false;
    }

    // Ok, we can update the objects ID.
    pObject->asSetID( newID );
    m_Objects.remove( oldID );
    m_Objects.insert( newID, pObject );
    return true;
}

AsNode *AsFactory::asCreateNode(quint32 nID)
{
    AsNode *pAsNode = nullptr;
    if (m_Nodes.contains(nID))
    {
        pAsNode = m_Nodes.value(nID);
    }
    else
    {
        pAsNode = new AsNode(this);
        pAsNode->asSetID(nID);
        m_Nodes.insert(nID, pAsNode);
    }

    LOGDEBUG("CreateNode:%d", nID);

    return pAsNode;
}

AsVirtualFolder *AsFactory::asGetVirtualFolder(int id, const QString &path)
{
    if (m_VirtualFolders.contains(id))
    {
        return m_VirtualFolders.value(id);
    }

    QString thePath = path;
    if (path.isEmpty())
    {
        thePath = this->m_pFlipchart->asGetFlipchartWorkingPath();
    }

    AsVirtualFolder *pFolder = new AsVirtualFolder(this);
    pFolder->asInitialise(thePath, id);

    m_VirtualFolders.insert(id, pFolder);
    return pFolder;
}

void AsFactory::asRemoveVirtualFolder(AsVirtualFolder *pFolder)
{
    int id = pFolder->asGetFolderId();
    m_VirtualFolders.remove(id);
    delete pFolder;
}

bool AsFactory::asHasVirtualFolder(int id)
{
    return m_VirtualFolders.contains(id);
}

void AsFactory::asRemoveVirtualFolder(int id)
{
    AsVirtualFolder *pFolder = m_VirtualFolders.value(id);
    if (pFolder != NULL)
    {
        m_VirtualFolders.remove(id);
        delete pFolder;
    }
}

AsFlipchart *AsFactory::asGetFlipchart(void)
{
    return m_pFlipchart;
}

AsResourceRegister *AsFactory::asGetResourceRegister()
{
    return m_pResourceRegister;
}
