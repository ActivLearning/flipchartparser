// Defines the AsPointer class.
// $Author: Paul Wareing.

#ifndef ASPOINTER_H
#define ASPOINTER_H



class AsNode;
class AsObject;
class AsPointer
{
public:

    // Construction and destruction.
    AsPointer();
    ~AsPointer();
    AsPointer( const AsPointer& );
    AsPointer( AsNode * );
    void operator= ( const AsPointer& );
    void asCopy( const AsPointer& );

    bool operator==( const AsPointer& );

    // Interface
    void asSetNode( AsNode * );
    AsNode * asGetNode( void ) const;

private:
    AsNode *m_pNode;
    AsObject* m_pObject;
};


#endif // ASPOINTER_H
