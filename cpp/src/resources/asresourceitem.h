/** @file asresourceitem.h
 * Handles resource index entry data
 * Copyright (C) 2006-2010 Promethean Limited. All Rights Reserved.
 */

#ifndef ASRESOURCEITEM_H
#define ASRESOURCEITEM_H

#include <QString>
#include <QPointer>

class AsResource;
class AsFactory;

class AsResourceItem
{
public:
    // Construction and destruction.
    AsResourceItem();
    virtual ~AsResourceItem();

    // Interface.
    quint32 asGetID( void ) const;
    void asSetID( quint32 );

    const QString& asGetResourceFilename( void ) const;
    void asSetResourceFilename( QString& );

    const QString& asGetDataFilename( void ) const;
    void asSetDataFilename( QString& );

    const QString& asGetHash( void ) const;
    void asSetHash( QString& );

    AsResource * asGetResourcePointer( void ) const;
    void asSetResource( AsResource * );

    qint32 asGetRefCount( void ) const;
    void asSetRefCount( qint32 );
    qint32 asIncrementRefCount( void );
    qint32 asDecrementRefCount( void );

    qint32 asIncrementLoadedCount( void );
    qint32 asDecrementLoadedCount( void );
    bool asIsLoaded( void );

private:
    // Persisted Properties.
    quint32 m_nID;
    QString m_sResourceFilename;
    QString m_sDataFilename;
    QString m_sHash;
    qint32 m_nRefCount;

    // Non-persisted properties.
    AsResource *m_pResource;
    qint32 m_nLoadedCount;
};

#endif // ASRESOURCEITEM_H
