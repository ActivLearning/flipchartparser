// Defines the AsNode class.
// $Author: Paul Wareing.

#ifndef ASNODE_H
#define ASNODE_H

#include <QMetaType>
#include <QList>
#include <QHash>
#include <QVector>
#include "../util/commonlog.h"


class AsFactory;
class AsObject;
class AsNode
{
public:
    // Construction and destruction.
    AsNode();
    AsNode( AsFactory * );
    virtual ~AsNode(){
        LOGDEBUG("node is delete","");
    }
    AsNode( const AsNode& );
    AsNode& operator= ( const AsNode& );
    static bool compare(const AsNode *left, const AsNode *right);
   AsObject * asGetAsObjectReference( void ) const;
   void asSetAsObjectReference(AsObject *pObject);
   // The Parent...
   void asSetParent( AsNode *, int index = -1 );
   AsNode * asGetParent( void ) const;
   quint32 asGetID( void ) const;
   void asSetID( quint32 );
    void asAddSoftChild( AsNode * );
    void asAddChild( AsNode *pNode, int index );
    void asRemoveChild( AsNode * );
    int asGetChildCount( void ) const;
    AsNode *asGetChildAt( int ) const;
    // To get a pointer to the factory that created this object...
    AsFactory * asGetFactoryPointer( void ) const;
    bool asHasSoftChildren() const;
    void asRemoveSoftChild(AsNode *pNode);
    const QList<AsNode *> asGetSoftChildren() const;
    void asAddSoftParent(AsNode *pNode);
    void asRemoveSoftParent(AsNode *pNode);
    bool asHasSoftParents() const;
    const QList<AsNode *> asGetSoftParents() const;
private:

    // We have a pointer to our single parent.
    AsNode * m_pParentNode;
   // We have a reference to a single AsObject.
   AsObject *m_pAsObjectRef;
   AsFactory * m_pFactory;
   quint32 m_nID;

   QList<AsNode *> m_Children;
   QList<AsNode *> m_SoftChildren;
   QList<AsNode *> m_SoftParents;
};

// These objects are used to walk a tree of AsNodes.
class AsNodeGraphWalker
{
public:
    // To construct a tree walker the caller must specify a root
    // node and whether soft children should also be walked.
    explicit AsNodeGraphWalker( AsNode *, bool bIncludeSoftChildren = false );

    // This is the tree walk method. It will perform a depth first
    // walk of children ( and soft children if specified ).
    AsNode * asGetNextNode( void );

    // This method searches a tree for a node with a specific ID, and
    // returns a pointer to it if found, else returns 0.
    AsNode * asGetNode( quint32& nID );

    // Method to add a blocking node to this particular walk.
    void asAddBlockedNode( AsNode * );



private:
    // Every walker gets a unique ID.
    // It uses this ID to 'stamp' the nodes to determine whether they have been blocked or explored already.
    quint32 m_nWalkerID;

    // This is the recursive method used to walk the tree of nodes
    // by asGetNextNode.
    AsNode * asExploreChildren( AsNode * );

    // The caller can decide whether to walk hard children only,
    // or hard and soft children.
    bool m_bIncludeSoftChildren;

    // The root node is the node from which we walk, through children
    // and soft children if specified.
    AsNode * m_pRootNode;

    // This is a store of the last node we walked, and where we will
    // continue walking from.
    AsNode * m_pLastNode;


};

class AsNodeWalker
{
public:
    friend class AsNode;
public:

    explicit AsNodeWalker( AsNode * );
    AsNode * asGetNextNode();
    AsNode * asGetNode( quint32& nID );
    void asAddBlockedNode( AsNode * );


private:
    struct frame
    {
        frame() { };
        frame(AsNode * node, int index) : node(node), index(index) { }
        frame(const frame & other) : node(other.node), index(other.index) { }
        AsNode * node;
        int index;
    };
private:
    bool m_root;
    QVector<frame> m_stack;
    QVector<AsNode *> m_blocked;

};

#endif // ASNODE_H
