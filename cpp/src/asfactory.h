#ifndef ASFACTORY_H
#define ASFACTORY_H

#include <QHash>
#include <QList>

#include "objects/asobject.h"
class AsNode;
class AsVirtualFolder;
class AsFlipchart;
class AsResourceRegister;
class AsResourceManager;

class AsFactory
{
public:
    enum AsEnumObjectID
    {
        AS_ID_NULL = 0,
        AS_ID_NEW,
        AS_ID_PROPERTY,
        AS_ID_APP,
        AS_ID_UNDO,
        AS_ID_COPY,
        AS_ID_ALLCATEGORY,
        AS_ID_METARESOURCEFOLDER,
        AS_ID_TEMPRESINDEX,
        AS_ID_FEATURE,
        AS_ID_RESPONSES,
        AS_ID_PAGEOBJECTCOLLECTION,
        AS_ID_VIRTUALRESOURCEFOLDER,
        AS_ID_VIRTUALAS4FOLDER,
        AS_ID_VIRTUALFOLDERINDEX,
        AS_ID_BASE = 100
    };


    AsFactory();
    ~AsFactory();
    AsResourceManager *getResourceManager();
    void setResourceManager(AsResourceManager *pAsResourceManager);
    AsObject * asCreateObject( AsObject::AsEnumObjectType, quint32 nID = AS_ID_NEW );
    bool asDeleteObject(AsObject *pAsObject);
    bool asChangeObjectID( quint32 oldID, quint32 newID );
    AsNode * asCreateNode( quint32 nID = AS_ID_NEW );

    AsVirtualFolder * asGetVirtualFolder( int id, const QString& path = QString() );
    void asRemoveVirtualFolder( AsVirtualFolder * );
    void asRemoveVirtualFolder( int id );
    bool asHasVirtualFolder( int id );
    AsFlipchart * asGetFlipchart( void );
    AsResourceRegister *asGetResourceRegister();
private:

    QHash<quint32, AsObject *> m_Objects;

    // The definitive list of nodes created by this factory...
    QHash<quint32, AsNode *> m_Nodes;

    // We also need a separate list for those AsObjects that are properties of other objects.
    // Temporay version of these AsObjects are created by this factory when they are being streamed in.
    QList< AsObject * > m_Properties;

    AsFlipchart *m_pFlipchart;

    AsResourceRegister *m_pResourceRegister;
    AsResourceManager *m_pResourceManager;


    QHash< quint32, AsVirtualFolder * > m_VirtualFolders;
};

#endif // ASFACTORY_H
