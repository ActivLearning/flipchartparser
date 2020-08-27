/** @file asresourceitem.cpp
 * Handles resource index entry data
 * Copyright (C) 2006-2010 Promethean Limited. All Rights Reserved.
 */

#include "asresourceitem.h"
#include "asresource.h"

//#define USE_ASDEBUGOUTPUT
#ifdef USE_ASDEBUGOUTPUT
#include <QDebug>
static int debugCounter = 0 ;
#define ASDEBUGOUTPUT(x) qDebug() << "[" << debugCounter++ << "]" << "[" << __FUNCTION__ << "] - " << x
#else
#define ASDEBUGOUTPUT(x)
#endif


AsResourceItem::AsResourceItem()
{
    // Persisted...
    m_nID = 0;
    m_nRefCount = 0;

    // Note persisted...
    m_pResource = nullptr;
    m_nLoadedCount = 0;
}

AsResourceItem::~AsResourceItem()
{

}

quint32 AsResourceItem::asGetID( void ) const
{
    return m_nID;
}

void AsResourceItem::asSetID( quint32 nID )
{
    m_nID = nID;
    ASDEBUGOUTPUT( "Item Id:" << m_nID );
}

const QString& AsResourceItem::asGetResourceFilename( void ) const
{
    return m_sResourceFilename;
}

void AsResourceItem::asSetResourceFilename( QString& sFilename )
{
    m_sResourceFilename = sFilename;
}

const QString& AsResourceItem::asGetDataFilename( void ) const
{
    return m_sDataFilename;
}

void AsResourceItem::asSetDataFilename( QString& sFilename )
{
    m_sDataFilename = sFilename;
}

const QString& AsResourceItem::asGetHash( void ) const
{
    return m_sHash;
}

void AsResourceItem::asSetHash( QString& sHash )
{
    m_sHash = sHash;
}

AsResource * AsResourceItem::asGetResourcePointer( void ) const
{
    return m_pResource;
}

void AsResourceItem::asSetResource( AsResource *pResource )
{
    m_pResource = pResource;
}

qint32 AsResourceItem::asGetRefCount( void ) const
{
    return m_nRefCount;
}

void AsResourceItem::asSetRefCount( qint32 nRefCount )
{
    m_nRefCount = nRefCount;
    ASDEBUGOUTPUT( "Item Id:" << m_nID << "Ref Count:" << m_nRefCount );
}

qint32 AsResourceItem::asIncrementRefCount( void )
{
    ++m_nRefCount;
    ASDEBUGOUTPUT( "Item Id:" << m_nID << "Ref Count:" << m_nRefCount );
    return m_nRefCount;
}

qint32 AsResourceItem::asDecrementRefCount( void )
{
    if ( m_nRefCount > 0 )
    {
        --m_nRefCount;
    }
    ASDEBUGOUTPUT( "Item Id:" << m_nID << "Ref Count:" << m_nRefCount );
    return m_nRefCount;
}

qint32 AsResourceItem::asIncrementLoadedCount( void )
{
    ++m_nLoadedCount;
    ASDEBUGOUTPUT( "Item Id:" << m_nID << "Loaded Count:" << m_nLoadedCount );
    return m_nLoadedCount;
}

qint32 AsResourceItem::asDecrementLoadedCount( void )
{
    if ( m_nLoadedCount > 0 )
    {
        --m_nLoadedCount;
    }
    ASDEBUGOUTPUT( "Item Id:" << m_nID << "Loaded Count:" << m_nLoadedCount );
    return m_nLoadedCount;
}

bool AsResourceItem::asIsLoaded( void )
{
    return ( m_nLoadedCount > 0 );
}
