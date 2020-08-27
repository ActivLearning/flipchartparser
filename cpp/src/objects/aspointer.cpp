// Implements the AsPointer class.
// $Author: Paul Wareing.

#include "aspointer.h"
#include "../io/asnode.h"
#include "asobject.h"


AsPointer::AsPointer() : m_pNode( NULL ),
                         m_pObject( NULL )
{

}

AsPointer::~AsPointer()
{

}

AsPointer::AsPointer( const AsPointer& obj )
{
    this->asCopy( obj );
}

AsPointer::AsPointer( AsNode *pNode )
{
	this->asSetNode( pNode );
}

void AsPointer::operator= ( const AsPointer& obj )
{
    this->asCopy( obj );
}

bool AsPointer::operator==( const AsPointer& p )
{
    if ( m_pNode != p.asGetNode() )
    {
        return false;
    }
    return true;
}

void AsPointer::asCopy( const AsPointer& obj )
{
    this->m_pNode = obj.asGetNode();
    if ( m_pNode != NULL )
    {
        m_pObject = m_pNode->asGetAsObjectReference();
    }
    else
    {
        m_pObject = NULL;
    }
}

void AsPointer::asSetNode( AsNode *pNode )
{
    m_pNode = pNode;
    if ( m_pNode != NULL )
    {
        m_pObject = pNode->asGetAsObjectReference();
    }
    else
    {
        m_pObject = NULL;
    }
}

AsNode * AsPointer::asGetNode( void ) const
{
    if ( m_pObject == NULL )
    {
        return NULL;
    }
    return m_pNode;
}
