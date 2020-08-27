// Implements the AsVirtualFolderIndex class.
// $Author: Paul Wareing.

#include "asvirtualfolderindex.h"

AsVirtualFolderIndex::AsVirtualFolderIndex()
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_VIRTUAL_FOLDER_INDEX );
}

AsVirtualFolderIndex::AsVirtualFolderIndex( AsFactory *pFactory) : AsObject( pFactory )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_VIRTUAL_FOLDER_INDEX );
}

AsVirtualFolderIndex::AsVirtualFolderIndex( const AsVirtualFolderIndex& idx ) : AsObject( idx )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_VIRTUAL_FOLDER_INDEX );

    m_Index = idx.asGetFolderIndex();
}

AsVirtualFolderIndex::~AsVirtualFolderIndex()
{

}

void AsVirtualFolderIndex::operator= ( const AsVirtualFolderIndex& idx )
{
    AsObject::operator =( idx );

    m_Index = idx.asGetFolderIndex();
}

QHash<QString, quint16>& AsVirtualFolderIndex::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsVirtualFolderIndex::AS_PROPERTY_DATETIMECREATED );

        // From AsFlipchart
        HashProperties.insert( "asFolderIndex", ( quint16 )AsVirtualFolderIndex::AS_PROPERTY_FOLDERINDEX );
    }

    return HashProperties;
}

void AsVirtualFolderIndex::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

void AsVirtualFolderIndex::asSetFolderIndex( const AsFolderIndex& idx )
{
    m_Index = idx;
}

const AsFolderIndex& AsVirtualFolderIndex::asGetFolderIndex( void ) const
{
    return m_Index;
}

AsFolderIndex * AsVirtualFolderIndex::asGetFolderIndexPointer( void )
{
    return &m_Index;
}
