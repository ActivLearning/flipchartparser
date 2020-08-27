// Defines the AsShapeRes class.
// $Author: Paul Wareing.

#ifndef ASSHAPERES_H
#define ASSHAPERES_H

#include <QObject>


#include "asresource.h"
#include "../dataStruct/aspointfarrayarray.h"

class AsFactory;

/**
 * Represents a ShapeRes resource object in a flipchart
 *
 * \see AsShape
 */
class AsShapeRes : public AsResource
{
Q_PROPERTY( AsPointFArrayArray asShapes READ asGetShapes WRITE asSetShapes )
public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        // From AsAnnotationRes...
        AS_PROPERTY_SHAPES
    };

    AsShapeRes( AsFactory * );
    virtual ~AsShapeRes();

    AsShapeRes( const AsShapeRes& );
    void operator= ( const AsShapeRes& );

    // Interface..
    const QByteArray& asGetHashData( void ) ;
    bool asIsHashDataDirty( void );
    void asComputeHashData( void );

    // Properties.
    void asResetPropertyIndex( void );

    const AsPointFArrayArray& asGetShapes( void ) const;
    void asSetShapes( AsPointFArrayArray& );
    void asAddShape( AsPointFArray& );
    void asClearShapes( void );

    const AsPointFArray& asGetShape( int idx );

signals:
    void asShapeResChanged( AsShapeRes * );

private:
    void asCopy( const AsShapeRes& );

    static QHash<QString, quint16>& m_lProperties( void );

    AsPointFArrayArray m_Shapes;
};

#endif // ASSHAPERES_H
