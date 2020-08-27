// Defines the AsResourceIndex class.
// $Author: Paul Wareing

#ifndef ASRESOURCEINDEX_H
#define ASRESOURCEINDEX_H

#include <QMetaType>
#include <QLinkedList>
#include <QFile>

#include "asresourceitem.h"

class AsFactory;

class AsResourceIndex : public QLinkedList<AsResourceItem>
{
public:

    // Clears the index of all items with 0 ref count.
    void asRemoveNullResourceItems( void );

private:

};

Q_DECLARE_METATYPE( AsResourceIndex )

#endif // ASRESOURCEINDEX_H
