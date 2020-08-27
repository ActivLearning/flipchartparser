// Implements the AsResourceIndex class.
// $Author: Paul Wareing.

#include "asresourceindex.h"




void AsResourceIndex::asRemoveNullResourceItems( void )
{
    QLinkedList< AsResourceItem >::iterator it = this->begin();
    while ( it != this->end() )
    {
        AsResourceItem *pItem = ( AsResourceItem * ) &*it;
        if ( pItem->asGetRefCount() == 0 )
        {
            // The erase may cause a re-allocation, so we will start from the beginning again.
            this->erase( it );
            it = this->begin();
        }
        else
        {
            ++it;
        }
    }
}
