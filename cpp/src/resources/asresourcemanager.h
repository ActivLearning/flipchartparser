// Defines the AsResourceManager class.
// $Author: Paul Wareing.

#ifndef ASRESOURCEMANAGER_H
#define ASRESOURCEMANAGER_H

#include <QList>

#include "../objects/asobject.h"
#include "asresourceregister.h"

class AsResource;
class AsResourceItem;
class AsResourceIndex;
class AsFactory;
class AsFlipchart;
//class AsApp;

class AsResourceManager
{
public:
    // Construction and destruction...
    AsResourceManager();
    virtual ~AsResourceManager();

    void asConfigure( AsFlipchart * );
//    void asConfigure( AsApp * );

    // Interface...
    const AsResourceRegister& asGetResourceRegister( void ) const;
    void asSetResourceRegister( AsResourceRegister& );

    AsResource * asCommitResource( AsResource *, bool forceNew = false );
//    AsResource * asDetachResource( AsResource * );
    qint32 asAddInstanceRef( AsObject::AsEnumObjectType type, quint32 id );
    qint32 asReleaseInstanceRef( AsObject::AsEnumObjectType type, quint32 id );

    AsResource * asLoadResource( AsObject::AsEnumObjectType, quint32 id );
    void asUnloadResource( AsResource * );
    qint32 asAddLoadedRef( AsResource * );
    qint32 asReleaseLoadedRef( AsResource * );

    void asAddResourceItem( quint32 id, AsObject::AsEnumObjectType type, QString& hash, QString& sResourceFile, QString& sDataFile );
    bool asRemoveResourceItem( quint32 id, AsObject::AsEnumObjectType type );

//    AsResource * asReuseResource( AsResource * );

    const QString& asGetHash( quint32 id, AsObject::AsEnumObjectType type );

    const QString& asGetResourceDataFilename( AsResource * );
    QString asGetWorkingPath( void );

    // To get a pointer to the specific resource item for a resource.
    AsResourceItem * asGetResourceItem( AsResource * );

    // The working copy of the resource register must also be written out whenever it is modified to
    // enable crash recovery
    void asWriteWorkingResourceRegister( void );

private:
    // Personality.
//    AsApp *m_pApp;
    AsFlipchart *m_pFlipchart;

    AsFactory *m_pFactory;

    // To get a pointer to a resource item for a resource with the same data (hash).
    AsResourceItem * asGetResourceItem( QString& hash, AsObject::AsEnumObjectType );


    // Is the resource registered...
    AsResourceItem * asGetRegisteredResourceItem( AsResourceIndex *, quint32 id );

    // To remove resoure items from the lists.
    bool asRemoveRegisteredItem( AsResourceIndex *, quint32 );

    // Which index...
    AsResourceIndex * asGetResourceIndex( AsObject::AsEnumObjectType );

    // We keep the active register here.  Otherwise we cant delete the resources correctly when the
    // flipchart is closed.  !!The flipchart tree is deleted top down!!
    // We operate on this copy of the resource register.
    // This resource register must be set/copied to the flipcharts/apps on streaming!!
    AsResourceRegister m_ResourceRegister;

    // To remove the resource and data files.
    void asRemoveResourceFiles( AsResourceIndex *, AsResourceItem * );

    // Debugging aid, dumps all current resources to output.  NB only image resources as its currently coded.
    void asDumpResourcesInfoToOutput();
};

#endif // ASRESOURCEMANAGER_H
