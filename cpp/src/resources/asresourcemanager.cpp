/** @file asresourcemanager.cpp
 * Handles sharing of resources in a flipchart
 * Copyright (C) 2006-2010 Promethean Limited. All Rights Reserved.
 */

#include "asresourcemanager.h"

#include <QFile>

#include "../util/asutil.h"
#include "../objects/asflipchart.h"
//#include "asapp.h"
#include "asresourceindex.h"
#include "asresourceitem.h"
#include "asresource.h"
//#include "asimageres.h"
//#include "asannotationres.h"
//#include "aspointfarray.h"
//#include "ashashmd5.h"
#include "../asfactory.h"
#include "../io/asfileio.h"
#include "../util/asfileutils.h"
#include "../objects/asvirtualfolder.h"
#include "../util/ashashmd5.h"

//#define USE_ASDEBUGOUTPUT
#ifdef USE_ASDEBUGOUTPUT
static int debugCounter = 0 ;
    #define ASDEBUGOUTPUT(x) (qDebug() << "[" << debugCounter++ << "]" << "[" << __FUNCTION__ << "] - " << x)
#else
#define ASDEBUGOUTPUT(x)
#endif

//#define USE_ASDUMPRESOURCESINFOTOOUTPUT
#ifdef USE_ASDUMPRESOURCESINFOTOOUTPUT
#define ASDUMPRESOURCESINFOTOOUTPUT() asDumpResourcesInfoToOutput()
#else
#define ASDUMPRESOURCESINFOTOOUTPUT()
#endif


AsResourceManager::AsResourceManager() : m_pFlipchart( 0 ),
                                         m_pFactory( 0 )
{
    ASDEBUGOUTPUT("");
}

AsResourceManager::~AsResourceManager()
{
    ASDEBUGOUTPUT("");
}

void AsResourceManager::asConfigure( AsFlipchart *pFlipchart )
{
    ASDEBUGOUTPUT("");
    m_pFlipchart = pFlipchart;
    m_pFactory = m_pFlipchart->asGetFactoryPointer();
    m_ResourceRegister = *m_pFlipchart->asGetResourceRegister();
}

//void AsResourceManager::asConfigure( AsApp *pApp )
//{
//    ASDEBUGOUTPUT("");
//    m_pApp = pApp;
//    m_pFactory = m_pApp->asGetFactoryPointer();
//}

// Interface...
const AsResourceRegister& AsResourceManager::asGetResourceRegister( void ) const
{
    ASDEBUGOUTPUT("");
    return m_ResourceRegister;
}

void AsResourceManager::asSetResourceRegister( AsResourceRegister& reg )
{
    ASDEBUGOUTPUT("");
//    As::writeErrorLog( "AsResourceManager", "asSetResourceRegister", "", As::LOGLEVEL_TRACING );
    m_ResourceRegister = reg;
}

/** Creates a AsResourceItem from pResourse and adds it to the correct AsResourceIndex for its type
 *
 */

AsResource * AsResourceManager::asCommitResource( AsResource *pResource, bool bForce )
{
//    QString msg = QString("Res Type: %1 id: %2 Force: %3").arg(pResource->asGetTypeName()).arg(pResource->asGetID()).arg(bForce);
//    ASDEBUGOUTPUT( "ENTRY " << msg );
//    ASDUMPRESOURCESINFOTOOUTPUT();
//    ASDEBUGOUTPUT( "pResource: OriginalFilename =" << pResource->asGetOriginalFilename() << ", OriginalFilePath =" << pResource->asGetOriginalFilePath() );
//    As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable(msg), As::LOGLEVEL_TRACING );
    // We only compute the hash key if we are not being forced to add a new resource item.
    QString sHash = "unknown";
    if ( !bForce )
    {
        if ( pResource->asIsHashDataDirty() )
        {
            pResource->asComputeHashData();
        }
        const QByteArray& ba = pResource->asGetHashData();
        if ( ba.isEmpty() )
        {
            // If we get a null byte array then we treat this resource as a forced resource.
            bForce = true;
        }
        else
        {
            sHash = AsHashMD5::hashData( ba );
            ASDEBUGOUTPUT( "Calculated hash: " << sHash );
        }
    }

    // This pointer will be set when we are dealing with resources that use data files, i.e. images and
    // we have found an existing resource with the same data.
    AsResourceItem *pItemWithSameDataFile = NULL;
    AsResource* pOldResource = pResource;

    // First, check if a resource with this key is already loaded.
    // If there is an entry in the 'loaded' table we know it must also be in the resource register.
    AsResourceItem *pItem = this->asGetResourceItem( sHash, pResource->asGetType() );
    if ( !bForce )
    {
        if ( pItem != NULL )
        {
            if ( pItem->asIsLoaded() )
            {
                ASDEBUGOUTPUT( "Item already loaded.  pItem: " << pItem );
                // Ok, we already have this resource loaded.
                if ( !pResource->asUsesDataFile() )
                {
                    // Instead, we will use the loaded resource.
                    pResource = ( AsResource * )pItem->asGetResourcePointer();
                    if( pResource != 0 )
                    {
                        // If the loaded resource has its data in the AsResource file then we use that resource and
                        // delete the resource passed in, as it has become redundant.
                        m_pFactory->asDeleteObject( pOldResource );
                        pItem->asIncrementRefCount();
                        qint32 nCount = pItem->asIncrementLoadedCount();
                        QString msg = QString("Resource (%1) already loaded, count is (%2).").arg( pItem->asGetID() ).arg(nCount);
//                        As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );
                        ASDEBUGOUTPUT( "EXIT " << msg );
                        return pResource;
                    }
                    else
                    {
                        pResource = pOldResource;
                    }
                }
                else
                {
                    // If the loaded resource keeps its data in a separate file, such as an image then we
                    // still create a new res, i.e. new resource meta data, but we share the data file.
                    QString msg = QString("Found loaded resource (%1) with same data file (%2).").arg(pItem->asGetID()).arg(pItem->asGetDataFilename());
//                    As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );
                    ASDEBUGOUTPUT( msg );
                    pItemWithSameDataFile = pItem;
                }
            }
            else
            {
                ASDEBUGOUTPUT( "Item not already loaded.  pItem: " << pItem );
            }
        }
    }

    // OK, not loaded, forced, or shared data.
    // If not forced and not shared data we must check whether this resource is already present in our resource register.
    if (( !bForce ) && ( pItemWithSameDataFile == NULL ) && ( pResource != 0 ) )
    {
        if ( pItem != NULL )
        {
            // First check that the ref count is not zero.
            // If it is zero then the flipchart may not have the resource data so we will force a new resource.
            if ( pItem->asGetRefCount() == 0 )
            {
                pItem = 0;
            }
            else
            {
                // We found an entry in the resource register.
                if ( !pResource->asUsesDataFile() )
                {
                    // We will use the resource passed in as the loaded resource.
                    m_pFactory->asChangeObjectID( pResource->asGetID(), pItem->asGetID() );
                    pItem->asSetResource( pResource );
                    qint32 nRef = pItem->asIncrementRefCount();
                    pItem->asIncrementLoadedCount();
                    QString msg = QString("Loaded resource (%1), ref count is (%2).").arg(pItem->asGetID()).arg(nRef);
//                    As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );
                    ASDEBUGOUTPUT( "EXIT " << msg );
                    return pResource;
                }
                else
                {
                    QString msg = QString("Found registered resource (%1) with same data file (%2).").arg(pItem->asGetID()).arg(pItem->asGetDataFilename());
//                    As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );
                    ASDEBUGOUTPUT( msg );
                    pItemWithSameDataFile = pItem;
                }
            }
        }
    }

    // OK, so either we are being forced to add the resource, it uses shared data, or we don't already have it.
    AsResourceIndex *pIndex = this->asGetResourceIndex( pResource->asGetType() );
    AsResourceItem item;
    item.asSetID( pResource->asGetID() );
    QString sFilename = AsFileUtils::asGetObjectFilename( pResource );
    item.asSetResourceFilename( sFilename );
    item.asSetHash( sHash );
    item.asSetResource( pResource );

    ASDEBUGOUTPUT( "Creating new item. Id: " << item.asGetID() << " Filename: " << sFilename << " Hash: " << sHash );

    // We add a new item to the register.
    item.asIncrementRefCount();

    // Add a new entry into the 'loaded' items table.
    item.asIncrementLoadedCount();

//    msg = QString("Added and loaded new resource (%1).").arg(pResource->asGetID());
//    As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );
    ASDEBUGOUTPUT( msg );

    // Write the resource.
    AsVirtualFolder *pFolder = this->m_pFactory->asGetVirtualFolder( AsFactory::AS_ID_VIRTUALRESOURCEFOLDER );
    AsFileIO io( m_pFlipchart );
    io.asSaveObject( pResource, pFolder );

    // If the resource uses an external file then we must copy it to our flipchart/app folder.
    if ( pResource->asUsesDataFile() )
    {
        QString sDataFilename;
        if ( pItemWithSameDataFile != 0 )
        {
            sDataFilename = pItemWithSameDataFile->asGetDataFilename();
//            msg = QString("Using existing resource data file (%1).").arg(sDataFilename);
//            As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );
            ASDEBUGOUTPUT( msg );
        }
        else
        {
            sDataFilename = AsFileUtils::asGetResourceDataFilename( pResource );

            QString sOriginalFilePath = pResource->asGetOriginalFilePath();
            QString sResPath;
            if ( m_pFlipchart != 0 )
            {
                sResPath = m_pFlipchart->asGetFlipchartWorkingPath();
            }
//            else
//            {
//                sResPath = m_pApp->asGetTempAppPath();
//            }
            QString sPathAndName = sResPath + sDataFilename;

            // Need to potentially overwrite the target external file (e.g. for bitmap image fill), so remove
            // the current one. (QFile::copy does not overwrite files that already exist). Require force=true for this.
            if ( bForce && sOriginalFilePath != sPathAndName )
            {
                QFile target( sPathAndName );
                if ( target.exists() )
                    target.remove( sPathAndName );
            }

//            msg = QString("Copying resource data file from (%1) to (%2).").arg(sOriginalFilePath).arg(sPathAndName);
            ASDEBUGOUTPUT( msg );
//            As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable( msg ), As::LOGLEVEL_TRACING );

            if ( !QFile::exists( sOriginalFilePath ) || !QFile::copy( sOriginalFilePath, sPathAndName ) )
            {
                ASDEBUGOUTPUT( "Failed to copy resource file - " << sOriginalFilePath );
                Q_ASSERT( false );
//                As::writeErrorLog( "AsResourceManager", "asCommitResource", qPrintable("Failed to copy resource file (" + sOriginalFilePath + ")"), As::LOGLEVEL_ERROR );
            }
        }

        item.asSetDataFilename( sDataFilename );
    }

    // Append the new resource item to the relevant index.
    pIndex->append( item );

    pFolder->asWriteIndex();
    asWriteWorkingResourceRegister();

    ASDEBUGOUTPUT( "EXIT item added to register: " << &item );
    ASDUMPRESOURCESINFOTOOUTPUT();

    return pResource;
}

//AsResource * AsResourceManager::asDetachResource( AsResource *pResource )
//{
//    ASDEBUGOUTPUT( "ENTRY" );
//    // Assume caller can have the same res in memory for now, until we know that it is shared in memory.
//    AsResource *pDetachedRes = pResource;
//    if ( pResource == NULL )
//    {
////        As::logAndAssert( false, "AsResourceManager", "asDetachResource", "Trying to detach NULL resource" );
//        ASDEBUGOUTPUT( "EXIT WITH ERROR - Trying to detach NULL resource" );
//        return NULL;
//    }
////    QString msg = QString("Res Type: %1 id: %2").arg(pResource->asGetTypeName()).arg(pResource->asGetID());
//    ASDEBUGOUTPUT( msg );
////    As::writeErrorLog( "AsResourceManager", "asDetachResource", qPrintable(msg), As::LOGLEVEL_TRACING );
//
//    // Test if the resource is managed.
//    AsResourceItem *pItem = this->asGetResourceItem( pResource );
//    if ( pItem == NULL )
//    {
//        // Resource not managed.
////        As::writeErrorLog( "AsResourceManager", "asDetachResource", "Detaching a resource that isn't managed", As::LOGLEVEL_WARNING );
//        ASDEBUGOUTPUT( "EXIT WITH ERROR - Detaching a resource that isn't managed" );
//        return pDetachedRes;
//    }
//
//    // If the resource is shared in memory then we need to create a new in memory version and re-assign the given pointer.
//    // Otherwise, we can remove the entry from the loaded resource table.
//    if ( pItem->asDecrementLoadedCount() > 0 )
//    {
//        // Where a resource uses a data file then it always has its own res object.
//        pDetachedRes = ( AsResource * )this->m_pFactory->asCopyObject( pResource );
//        QString msg = QString("Loaded count still > 0, Copied Resource Object to id: %1").arg(pDetachedRes->asGetID());
//        ASDEBUGOUTPUT( msg );
////        As::writeErrorLog( "AsResourceManager", "asDetachResource", qPrintable(msg), As::LOGLEVEL_TRACING );
//    }
//    else
//    {
////        As::writeErrorLog( "AsResourceManager", "asDetachResource", "Decremented loaded count now 0", As::LOGLEVEL_TRACING );
//        ASDEBUGOUTPUT( "Decremented loaded count now 0" );
//        pItem->asSetResource( NULL );
//    }
//
//    this->asRemoveResourceItem( pResource->asGetID(), pResource->asGetType() );
//    this->m_pFactory->asAssignNextId( pDetachedRes );
//
//    QString msg2 = QString("Assigned next id to detached res id: %1").arg(pDetachedRes->asGetID());
//    ASDEBUGOUTPUT( "EXIT " << msg2 );
////    As::writeErrorLog( "AsResourceManager", "asDetachResource", qPrintable(msg2), As::LOGLEVEL_TRACING );
//    ASDUMPRESOURCESINFOTOOUTPUT();
//    return pDetachedRes;
//}

void AsResourceManager::asAddResourceItem( quint32 id, AsObject::AsEnumObjectType type, QString& sHash, QString& sResourceFile, QString& sDataFile )
{
    QString msg = QString( "id: %1, type %2, res file: %3, data file: %4" ).arg(id).arg(type).arg(sResourceFile).arg(sDataFile);
    ASDEBUGOUTPUT( "ENTRY - " << msg );
//    As::writeErrorLog( "AsResourceManager", "asAddResourceItem", qPrintable(msg), As::LOGLEVEL_TRACING );
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    AsResourceItem *pItem = this->asGetRegisteredResourceItem( pIndex, id );
    if ( pItem != NULL )
    {
//        As::writeErrorLog( "AsResourceManager", "asAddResourceItem", "Item exists already", As::LOGLEVEL_TRACING );
        pItem->asIncrementRefCount();
        ASDEBUGOUTPUT( "EXIT - Already exists, asIncrementRefCount(), Ref Count now " << pItem->asGetRefCount() );
    }
    else
    {
        AsResourceItem item;
        item.asSetID( id );
        item.asSetResourceFilename( sResourceFile );
        item.asSetDataFilename( sDataFile );
        item.asSetHash( sHash );
        item.asSetResource( NULL );
        item.asIncrementRefCount();
        pIndex->append( item );
//        As::writeErrorLog( "AsResourceManager", "asAddResourceItem", "New item created", As::LOGLEVEL_TRACING );
        ASDEBUGOUTPUT( "EXIT - New item created, Id: " << id << " Hash: " << sHash );
    }
    ASDUMPRESOURCESINFOTOOUTPUT();
}

bool AsResourceManager::asRemoveResourceItem( quint32 id, AsObject::AsEnumObjectType type )
{
    QString msg = QString( "id: %1, type %2" ).arg(id).arg(type);
    ASDEBUGOUTPUT( "ENTRY - " << msg );
//    As::writeErrorLog( "AsResourceManager", "asRemoveResourceItem", qPrintable(msg), As::LOGLEVEL_TRACING );
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    AsResourceItem *pItem = this->asGetRegisteredResourceItem( pIndex, id );
    if ( pItem != NULL )
    {
        qint32 nRefs = pItem->asDecrementRefCount();
        if ( nRefs == 0 )
        {
            this->asRemoveResourceFiles( pIndex, pItem );
            this->asRemoveRegisteredItem( pIndex, id );
//            As::writeErrorLog( "AsResourceManager", "asRemoveResourceItem", "Resource Removed", As::LOGLEVEL_TRACING );
            ASDEBUGOUTPUT( "EXIT - Removed Id: " << id );
            return true;
        }
        ASDEBUGOUTPUT( "Resource ref > 0" );
//        As::writeErrorLog( "AsResourceManager", "asRemoveResourceItem", "Resource ref > 0", As::LOGLEVEL_TRACING );
    }
    ASDUMPRESOURCESINFOTOOUTPUT();
    ASDEBUGOUTPUT( "EXIT" );
    return false;
}

void AsResourceManager::asRemoveResourceFiles( AsResourceIndex *pIndex, AsResourceItem *pItem )
{
    ASDEBUGOUTPUT( "ENTRY" );

    // Delete the resource file.
    QString sResPath;
    if ( m_pFlipchart != 0 )
    {
//        As::writeErrorLog( "AsResourceManager", "asRemoveResourceFiles", "Using flipchart path", As::LOGLEVEL_TRACING );
        sResPath = m_pFlipchart->asGetFlipchartWorkingPath();
    }
    else
    {
//        As::writeErrorLog( "AsResourceManager", "asRemoveResourceFiles", "Using temp app path", As::LOGLEVEL_TRACING );
//        sResPath = m_pApp->asGetTempAppPath();
    }
    QString sResourceFile = pItem->asGetResourceFilename();
    AsVirtualFolder *pFolder = m_pFactory->asGetVirtualFolder( AsFactory::AS_ID_VIRTUALRESOURCEFOLDER );
    pFolder->asRemoveFile( sResourceFile );

    ASDEBUGOUTPUT( "Deleted: " << sResourceFile );

    // Read the data file name for this resource.
    QString sDataFile = pItem->asGetDataFilename();

    // If the data file name is not empty then we look through the register for any other resources
    // using the same data file.  If there are none then we can delete the data file itself.
    if ( !sDataFile.isEmpty() )
    {
        qint32 nDataFileShared = 0;

        QLinkedList< AsResourceItem >::const_iterator it = pIndex->constBegin();
        while ( it != pIndex->constEnd() )
        {
            AsResourceItem *pOtherItem = ( AsResourceItem * ) &*it;
            if ( pOtherItem->asGetDataFilename() == sDataFile )
            {
                ++nDataFileShared;
            }
            ++it;
        }

        // If there are no other resources using this data file then we mark it as deleted.
        if ( nDataFileShared <= 1 )
        {
            QString sDataFilePath = sResPath + sDataFile;
            QString sDelFilePath = sResPath + "d" + sDataFile;
            QFile file( sDataFilePath );
            file.rename( sDelFilePath );
            QString msg = QString("Data file %1 marked deleted").arg(sDataFilePath);
//            As::writeErrorLog( "AsResourceManager", "asRemoveResourceFiles", qPrintable(msg), As::LOGLEVEL_TRACING );
            //QFile::remove( sDataFilePath );
        }
    }
    ASDUMPRESOURCESINFOTOOUTPUT();
    ASDEBUGOUTPUT( "EXIT" );
}


static const QString emptyString;

const QString& AsResourceManager::asGetHash( quint32 id, AsObject::AsEnumObjectType type )
{
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    AsResourceItem *pItem = this->asGetRegisteredResourceItem( pIndex, id );

//    As::logAndAssert( pItem != NULL, "AsResourceManager", "asGetHash", "Item not found in resource register" );
    if( pItem != NULL )
    {
        ASDEBUGOUTPUT( "Id: " << id << ", Type: " << type << " Hash: " << pItem->asGetHash() );
        return pItem->asGetHash();
    }
    ASDEBUGOUTPUT( "Id: " << id << ", Type: " << type << " Hash: emptyString (pItm was NULL)" );
    return emptyString;
}

qint32 AsResourceManager::asAddInstanceRef( AsObject::AsEnumObjectType type, quint32 nId )
{
    ASDEBUGOUTPUT("");
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    if ( pIndex == 0 )
    {
        ASDEBUGOUTPUT( "Index not found" );
        return -1;
    }

    AsResourceItem *pItem = this->asGetRegisteredResourceItem( pIndex, nId );
    if ( pItem == 0 )
    {
        ASDEBUGOUTPUT( "Item not found" );
        return -1;
    }

    qint32 refCount = pItem->asIncrementRefCount();
//    QString msg = QString("Added ref count (%1) to resource (%2).").arg(refCount).arg(nId);
    ASDEBUGOUTPUT( msg );
//    As::writeErrorLog( "AsResourceManager", "asAddInstanceRef", qPrintable(msg), As::LOGLEVEL_TRACING );
    return refCount;
}

qint32 AsResourceManager::asReleaseInstanceRef( AsObject::AsEnumObjectType type, quint32 nId )
{
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    if ( pIndex == 0 )
    {
//        QString msg = QString("Res id: %1, Type: %2, index not found").arg( nId ).arg( type );
        ASDEBUGOUTPUT( msg );
//        As::writeErrorLog( "AsResourceManager", "asReleaseInstanceRef", qPrintable(msg), As::LOGLEVEL_ERROR );
        return -1;
    }

    AsResourceItem *pItem = this->asGetRegisteredResourceItem( pIndex, nId );
    if ( pItem == 0 )
    {
//        QString msg = QString("Res id: %1, Type: %2, item not found").arg( nId ).arg( type );
        ASDEBUGOUTPUT( msg );
//        As::writeErrorLog( "AsResourceManager", "asReleaseInstanceRef", qPrintable(msg), As::LOGLEVEL_ERROR );
        return -1;
    }

    qint32 refCount = pItem->asDecrementRefCount();
//    QString msg = QString("Released ref count (%1) on resource (%2).").arg(refCount).arg(nId);
    ASDEBUGOUTPUT( msg );
//    As::writeErrorLog( "AsResourceManager", "asAddInstanceRef", qPrintable(msg), As::LOGLEVEL_TRACING );
    ASDEBUGOUTPUT( msg );
    return refCount;
}

AsResource * AsResourceManager::asLoadResource( AsObject::AsEnumObjectType type, quint32 nID )
{
    AsResource *pResource = NULL;

    QString msg = QString( "Type: %1, id: %2" ).arg( type ).arg( nID );
    ASDEBUGOUTPUT( msg );
//    As::writeErrorLog( "AsResourceManager", "asLoadResource", qPrintable(msg), As::LOGLEVEL_TRACING );
    // First check if this resource is already loaded.
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    AsResourceItem *pItem = this->asGetRegisteredResourceItem( pIndex, nID );
    if ( pItem != NULL )
    {
        if ( pItem->asGetRefCount() == 0 )
        {
//            qDebug( "[ AsResourceManager ] - Registered item has 0 ref count!" );
//            As::logAndAssert( false, "AsResourceManager", "asLoadResource", "Registered item has 0 ref count" );
            return 0;
        }

        pResource = pItem->asGetResourcePointer();
        if ( pItem->asIsLoaded() && pResource != 0 )
        {
            qint32 nCount = pItem->asIncrementLoadedCount();
//            msg = QString( "Resource (%1) already loaded, load count is now (%2)." ).arg(nID).arg(nCount);
//            As::writeErrorLog( "AsResourceManager", "asLoadResource", qPrintable(msg), As::LOGLEVEL_TRACING );
            ASDEBUGOUTPUT( msg );
            ASDUMPRESOURCESINFOTOOUTPUT();
            return pResource;
        }

        // Ok we will load it.
        AsVirtualFolder *pFolder = m_pFactory->asGetVirtualFolder( AsFactory::AS_ID_VIRTUALRESOURCEFOLDER );
        QByteArray file;

        const QString resourceFileName = pItem->asGetResourceFilename();
        if( pFolder->asReadFile( resourceFileName, file ) == false )
        {
            QString er;
            er = "Resource (" + QString::number( pItem->asGetID() ) + ":" + resourceFileName + ") Failed to load from AsVirtualFolder (" + QString::number( pFolder->asGetFolderId() ) + ":" + pFolder->asGetFilePath() + ")";
//            qDebug( "[ AsResourceManager ] - Resource (Id:%d File:%s) Failed to load from AsVirtualFolder (%s)", pItem->asGetID(), resourceFileName.toUtf8().data(), pFolder->asGetFilePath().toUtf8().data() );
//            As::logAndAssert( false, "AsResourceManager", "asLoadResource", qPrintable(er));
            return NULL;
        }

        AsFileIO io( m_pFlipchart );

        pResource = (AsResource *)(io.asLoadObject( file ));
        if( !pResource )
        {
//            As::logAndAssert( false, "AsResourceManager", "asLoadResource", "pResource is NULL" );
            return NULL;
        }

        pItem->asSetResource( pResource );
        pItem->asIncrementLoadedCount();

        if( pResource != NULL )
        {
            // Check that the data file exists, or unmark as deleted (after flip recovery).
            if ( pResource->asUsesDataFile() )
            {
                QString sResPath;
                if ( m_pFlipchart != 0 )
                {
                    sResPath = m_pFlipchart->asGetFlipchartWorkingPath();
                }
//                else
//                {
//                    sResPath = m_pApp->asGetTempAppPath();
//                }

                QString sDataFile = pItem->asGetDataFilename();
                QString sDataFilePath = sResPath + sDataFile;
                QFile dataFile( sDataFilePath );

                QString sDelDataFilePath = sResPath + "d" + sDataFile;
                QFile delFile( sDelDataFilePath );

                if ( !dataFile.exists() )
                {
                    if( delFile.exists() )
                    {
                        bool res = delFile.rename( sDataFilePath );
                        if( !res )
                        {
//                            QString msg = "Failed to rename file: " + sDataFile;
//                            As::logAndAssert( false, "AsResourceManager", "asLoadResource", qPrintable(sDataFile));
                        }
                    }
                }
                else
                {
                    if ( delFile.exists() )
                    {
                        bool res = delFile.remove();
                        if( !res )
                        {
//                            QString msg = "Failed to remove file: " + sDataFile;
//                            As::logAndAssert( false, "AsResourceManager", "asLoadResource", qPrintable(sDataFile));
                        }
                    }
                }
            }
            msg = QString( "Loaded resource (%1)." ).arg(nID);
            ASDEBUGOUTPUT( msg );
//            As::writeErrorLog( "AsResourceManager", "asLoadResource", qPrintable(msg), As::LOGLEVEL_TRACING );
        }
        else
        {
            ASDEBUGOUTPUT("Resource not loaded. asLoadObject NULL!" );
//            As::logAndAssert( false, "AsResourceManager", "asLoadResource", "Resource not loaded, asLoadObject returned NULL" );
        }
    }
    else
    {
        ASDEBUGOUTPUT("Resource not loaded. Returning NULL pointer!" );
//        As::writeErrorLog( "AsResourceManager", "asLoadResource", "Resource not loaded, item pointer NULL", As::LOGLEVEL_TRACING );
    }
    ASDUMPRESOURCESINFOTOOUTPUT();
    return pResource;
}

void AsResourceManager::asUnloadResource( AsResource *pResource )
{
    ASDEBUGOUTPUT("ENTRY");
    // First check if this resource is loaded.
    // If it is then decrement the ref.
    // If the ref is 0 then we can unload the resource.
//    As::logAndAssert( pResource != NULL, "AsResourceManager", "asUnloadResource", "pResource is NULL" );
//    QString msg = QString( "Type: %1, id: %2" ).arg( pResource->asGetTypeName() ).arg( pResource->asGetID() );
//    As::writeErrorLog( "AsResourceManager", "asUnloadResource", qPrintable(msg), As::LOGLEVEL_TRACING );
    AsResourceItem *pItem = this->asGetResourceItem( pResource );
    if ( pItem != NULL )
    {
        if ( pItem->asIsLoaded() )
        {
            qint32 nCount = pItem->asDecrementLoadedCount();
            if ( nCount == 0 )
            {
                m_pFactory->asDeleteObject( pResource );
                pItem->asSetResource( 0 );
//                msg = QString( "Unloaded resource id: %1" ).arg( pItem->asGetID() );
            }
            else
            {
//                msg = QString("Resource (%1), decremented load count is (%2).").arg(pItem->asGetID()).arg(nCount);
            }
//            As::writeErrorLog( "AsResourceManager", "asUnloadResource", qPrintable(msg), As::LOGLEVEL_TRACING );
            ASDEBUGOUTPUT( "EXIT - " << msg );
            return;
        }
    }

    // So the resource is not in our resource table, but we will still call our factory to delete it.
    quint32 nID = pResource->asGetID();
    ASDEBUGOUTPUT( "Id: " << nID << " resource is not in  resource table, call our factory to delete it" );
    if ( m_pFactory->asDeleteObject( pResource ) )
    {
//        msg = QString("Deleted unmanaged resource (%1).").arg(nID);
        ASDEBUGOUTPUT( msg );
//        As::writeErrorLog( "AsResourceManager", "asUnloadResource", qPrintable(msg), As::LOGLEVEL_TRACING );
    }
    ASDUMPRESOURCESINFOTOOUTPUT();
    ASDEBUGOUTPUT( "EXIT" );
}

qint32 AsResourceManager::asAddLoadedRef( AsResource *pResource )
{
    ASDEBUGOUTPUT("");
    AsResourceItem *pItem = this->asGetResourceItem( pResource );
    if ( pItem == 0 )
    {
//        QString msg = QString("Res id: %1, Type: %2, item not found").arg( pResource->asGetID() ).arg( pResource->asGetTypeName() );
        ASDEBUGOUTPUT( msg );
//        As::writeErrorLog( "AsResourceManager", "asReleaseInstanceRef", qPrintable(msg), As::LOGLEVEL_ERROR );
        return -1;
    }

    qint32 count = pItem->asIncrementLoadedCount();
    ASDEBUGOUTPUT( "Count: " << count );
    return count;
}

qint32 AsResourceManager::asReleaseLoadedRef( AsResource *pResource )
{
    ASDEBUGOUTPUT("");
    AsResourceItem *pItem = this->asGetResourceItem( pResource );
    if ( pItem == 0 )
    {
//        QString msg = QString("Res id: %1, Type: %2, item not found").arg( pResource->asGetID() ).arg( pResource->asGetTypeName() );
        ASDEBUGOUTPUT( msg );
//        As::writeErrorLog( "AsResourceManager", "asReleaseInstanceRef", qPrintable(msg), As::LOGLEVEL_ERROR );
        return -1;
    }

    qint32 count = pItem->asDecrementLoadedCount();
    ASDEBUGOUTPUT( "Count: " << count );
    return count;
}

//AsResource * AsResourceManager::asReuseResource( AsResource *pResource )
//{
//    ASDEBUGOUTPUT("ENTRY");
//    ASDUMPRESOURCESINFOTOOUTPUT();
////    As::writeErrorLog( "AsResourceManager", "asReuseResource", "", As::LOGLEVEL_TRACING );
//    AsResource *pCopyRes;
//
//    if ( pResource->asUsesDataFile() )
//    {
//        // Where a resource uses a data file then it always has its own res object.
//        pCopyRes = ( AsResource * )this->m_pFactory->asCopyObject( pResource );
//
//        // Create an index item, and set its data.
//        AsResourceItem item;
//        item.asSetID( pCopyRes->asGetID() );
//        ASDEBUGOUTPUT("Id: " <<  pCopyRes->asGetID() );
//        QString sFilename = AsFileUtils::asGetObjectFilename( pCopyRes );
//        item.asSetResourceFilename( sFilename );
//        item.asSetResource( pCopyRes );
//
//        AsResourceItem *pCopiedItem = this->asGetResourceItem( pResource );
//        QString sHash = pCopiedItem->asGetHash();
//        item.asSetHash( sHash );
//
//        QString sDataFilename = pCopiedItem->asGetDataFilename();
//        item.asSetDataFilename( sDataFilename );
//
//        // The copied resource is loaded.
//        item.asIncrementRefCount();
//
//        // The copied resource has a new reference.
//        item.asIncrementLoadedCount();
//
//        // Save the resource file.
//        AsFileIO fileIO( m_pFlipchart );
//        fileIO.asSaveObject( pCopyRes );
//
//        // Add the new item to the register.
//        AsResourceIndex *pIndex = this->asGetResourceIndex( pCopyRes->asGetType() );
//        pIndex->append( item );
//    }
//    else
//    {
//        this->asAddInstanceRef( pResource->asGetType(), pResource->asGetID() );
//        this->asAddLoadedRef( pResource );
//        pCopyRes = pResource;
//    }
//    ASDUMPRESOURCESINFOTOOUTPUT();
//    ASDEBUGOUTPUT("EXIT");
//    return pCopyRes;
//}

AsResourceIndex * AsResourceManager::asGetResourceIndex( AsObject::AsEnumObjectType type )
{
    ASDEBUGOUTPUT( "Type: " << type );
//    As::writeErrorLog( "AsResourceManager", "asGetResourceIndex", "", As::LOGLEVEL_TRACING );
    AsResourceIndex *pIndex = m_ResourceRegister.asGetResourceIndex( type );

    return pIndex;
}

AsResourceItem * AsResourceManager::asGetResourceItem( QString& sHash, AsObject::AsEnumObjectType type )
{
    ASDEBUGOUTPUT( "Type: " << type << "  Hash: " << sHash );
//    As::writeErrorLog( "AsResourceManager", "asGetResourceItem", "", As::LOGLEVEL_TRACING );
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    QLinkedList< AsResourceItem >::const_iterator it = pIndex->constBegin();
    while ( it != pIndex->constEnd() )
    {
        AsResourceItem *pItem = ( AsResourceItem * ) &*it;
        if ( pItem->asGetHash() == sHash )
        {
            return pItem;
        }
        ++it;
    }
    ASDEBUGOUTPUT( "Not found" );
    return NULL;
}

AsResourceItem * AsResourceManager::asGetResourceItem( AsResource *pResource )
{
//    As::writeErrorLog( "AsResourceManager", "asGetResourceItem", "", As::LOGLEVEL_TRACING );
    AsObject::AsEnumObjectType type = pResource->asGetType();
    AsResourceIndex *pIndex = this->asGetResourceIndex( type );
    ASDEBUGOUTPUT( "Type: " << type << " Index: " << pIndex );

    if( pIndex != 0 )
    {
        quint32 id = pResource->asGetID();
        ASDEBUGOUTPUT( "Id: " << id );
        QLinkedList< AsResourceItem >::const_iterator it = pIndex->constBegin();
        while ( it != pIndex->constEnd() )
        {
            AsResourceItem *pItem = ( AsResourceItem * ) &*it;
            if ( pItem->asGetID() == id )
            {
                ASDEBUGOUTPUT( "Found Id: " << id );
                return pItem;
            }

            ++it;
        }
    }
    ASDEBUGOUTPUT( "Not found" );
    return NULL;
}

AsResourceItem * AsResourceManager::asGetRegisteredResourceItem( AsResourceIndex *pIndex, quint32 nId )
{
    ASDEBUGOUTPUT( "Id: " << nId );
//    As::writeErrorLog( "AsResourceManager", "asGetRegisteredResourceItem", "", As::LOGLEVEL_TRACING );
    QLinkedList< AsResourceItem >::const_iterator it = pIndex->constBegin();
    while ( it != pIndex->constEnd() )
    {
        AsResourceItem *pItem = ( AsResourceItem * ) &*it;
        if ( pItem->asGetID() == nId )
        {
            return pItem;
        }

        ++it;
    }
    ASDEBUGOUTPUT( "Not found" );
    return 0;
}

bool AsResourceManager::asRemoveRegisteredItem( AsResourceIndex *pIndex, quint32 nId )
{
    ASDEBUGOUTPUT( "Id: " << nId );
//    As::writeErrorLog( "AsResourceManager", "asRemoveRegisteredItem", "", As::LOGLEVEL_TRACING );
    QLinkedList< AsResourceItem >::iterator it = pIndex->begin();
    while ( it != pIndex->end() )
    {
        AsResourceItem *pItem = ( AsResourceItem * ) &*it;
        if ( pItem->asGetID() == nId )
        {
            pIndex->erase( it );
            return true;
        }

        ++it;
    }
    ASDEBUGOUTPUT( "Not found" );
    return false;
}

void AsResourceManager::asWriteWorkingResourceRegister( void )
{
    ASDEBUGOUTPUT("");
//    As::writeErrorLog( "AsResourceManager", "asWriteWorkingResourceRegister", "", As::LOGLEVEL_TRACING );
    if ( m_pFlipchart != NULL )
    {
//
    }

    QString sWorkingPath = this->asGetWorkingPath();
    AsFileIO fileIO( m_pFlipchart );
    fileIO.asSaveObject( &( this->m_ResourceRegister ), sWorkingPath, QString( "register" ) );
}

const QString& AsResourceManager::asGetResourceDataFilename( AsResource *pResource )
{
//    As::writeErrorLog( "AsResourceManager", "asGetResourceDataFilename", "", As::LOGLEVEL_TRACING );
    // We can assume that this resource is loaded, and therefore there is an entry in the loaded table.
    AsResourceItem *pItem = this->asGetResourceItem( pResource );
//    As::logAndAssert( pItem != 0, "AsResourceManager", "asGetResourceDataFilename", "pItem is NULL" );
    ASDEBUGOUTPUT( pItem->asGetDataFilename() );
    return pItem->asGetDataFilename();
}

QString AsResourceManager::asGetWorkingPath( void )
{
    QString sWorkingPath = "";
    if ( m_pFlipchart != 0 )
    {
        sWorkingPath = m_pFlipchart->asGetFlipchartWorkingPath();
    }
    else
    {
//        sWorkingPath = m_pApp->asGetTempAppPath();
    }
//    As::writeErrorLog( "AsResourceManager", "asGetWorkingPath", qPrintable(sWorkingPath), As::LOGLEVEL_TRACING );
    ASDEBUGOUTPUT( sWorkingPath );
    return sWorkingPath;
}

void AsResourceManager::asDumpResourcesInfoToOutput()
{
    AsResourceIndex *pIndex = asGetResourceIndex( AsObject::AS_OBJECT_IMAGERES );
    QLinkedList< AsResourceItem >::const_iterator it = pIndex->constBegin();
//    qDebug();
//    qDebug("** Start resource dump **");
    while ( it != pIndex->constEnd() )
    {
        AsResourceItem *pItem = ( AsResourceItem * ) &*it;
        pItem = pItem; // Suppress 'pItem not used' warning when USE_ASDEBUGOUTPUT is not defined.

//        qDebug() << "Id:" << pItem->asGetID()
//                 << ", ResourceFilename:" << pItem->asGetResourceFilename()
//                 << ", DataFilename:" << pItem->asGetDataFilename()
//                 << ", RefCount:" << pItem->asGetRefCount()
//                 << ", Hash:" << pItem->asGetHash();

        ++it;
    }
//    qDebug("** End resource dump **");
//    qDebug();
}
