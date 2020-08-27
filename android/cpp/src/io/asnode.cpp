#include "asnode.h"
#include "../asfactory.h"


AsNode::AsNode():
        m_pParentNode(nullptr),
        m_pAsObjectRef(nullptr),
        m_pFactory(nullptr)
{

}

AsNode::AsNode(AsFactory *factory):
m_pParentNode(nullptr),
m_pAsObjectRef(nullptr),
m_pFactory(factory)
{

}

AsNode::AsNode(const AsNode &)
{

}

AsNode &AsNode::operator=(const AsNode &)
{
    return *(new AsNode);
}

bool AsNode::compare(const AsNode *left, const AsNode *right)
{
    return false;
}

AsObject *AsNode::asGetAsObjectReference() const
{
    return m_pAsObjectRef;
}

void AsNode::asSetAsObjectReference(AsObject *pObject)
{
    m_pAsObjectRef=pObject;
}

void AsNode::asSetParent(AsNode *pNode, int index )
{
    if ( m_pParentNode != pNode )
    {
        if ( m_pParentNode != 0 )
        {
            m_pParentNode->asRemoveChild( this );
        }

        m_pParentNode = pNode;

        if ( pNode != 0 )
        {
            pNode->asAddChild( this, index );
        }
    }
}

AsNode *AsNode::asGetParent() const
{
    return new AsNode;
}

void AsNode::asAddSoftChild( AsNode *pNode )
{
    if ( this == pNode )
        return;

    if ( m_SoftParents.contains( pNode ))
        return;

    if ( !m_SoftChildren.contains( pNode ) )
    {
        m_SoftChildren.append( pNode );
        pNode->asAddSoftParent( this );
    }
}

void AsNode::asRemoveSoftChild( AsNode *pNode )
{
    if ( m_SoftChildren.contains( pNode ) )
    {
        m_SoftChildren.removeAll( pNode );
        pNode->asRemoveSoftParent( this );
    }
}

bool AsNode::asHasSoftChildren( void ) const
{
    if ( m_SoftChildren.count() == 0 )
    {
        return false;
    }
    return true;
}

void AsNode::asAddSoftParent( AsNode *pNode )
{
    if ( this == pNode )
        return;

    if ( m_SoftChildren.contains( pNode ))
        return;

    if ( !m_SoftParents.contains( pNode ) )
    {
        m_SoftParents.append( pNode );
        pNode->asAddSoftChild( this );
    }
}

void AsNode::asRemoveSoftParent( AsNode *pNode )
{
    if ( m_SoftParents.contains( pNode ) )
    {
        m_SoftParents.removeAll( pNode );
        pNode->asRemoveSoftChild( this );
    }
}

bool AsNode::asHasSoftParents( void ) const
{
    if ( m_SoftParents.count() == 0 )
    {
        return false;
    }
    return true;
}

const QList<AsNode *> AsNode::asGetSoftParents( void ) const
{
    return m_SoftParents;
}


const QList<AsNode *> AsNode::asGetSoftChildren( void ) const
{
    return m_SoftChildren;
}

void AsNode::asAddChild( AsNode *pNode, int index )
{
    if ( !m_Children.contains( pNode ) )
    {
        if (( index < 0 ) || ( index >= m_Children.count()))
            m_Children.append( pNode );
        else
            m_Children.insert( index, pNode );

        pNode->asSetParent( this );
    }
}

void AsNode::asRemoveChild( AsNode *pNode )
{
    if ( m_Children.contains( pNode ) )
    {
        m_Children.removeAll( pNode );
        pNode->asSetParent( 0 );
    }

    // If we have a quick look up entry to this node in the key table
    // then we must also remove this entry.
//    unsigned int nKey = m_NodeKeys.key( pNode );
//    if ( nKey != 0 )
//    {
//        m_NodeKeys.remove( nKey );
//    }
}

int AsNode::asGetChildCount( void ) const
{
    return m_Children.count();
}

AsNode * AsNode::asGetChildAt(int nPageNumber) const
{
    if (nPageNumber < 0) return (AsNode *) 0;

    return m_Children.at(nPageNumber);
}

// To get a pointer to the factory that created this object...
AsFactory * AsNode::asGetFactoryPointer( void ) const
{
    return m_pFactory;
}

quint32 AsNode::asGetID( void ) const
{
    return m_nID;
}

void AsNode::asSetID( quint32 nID )
{
    m_nID = nID;
}
