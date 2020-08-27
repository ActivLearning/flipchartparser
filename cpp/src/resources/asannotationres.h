// Defines the AsAnnotationRes class.
// $Author: Paul Wareing.

#ifndef ASANNOTATIONRES_H
#define ASANNOTATIONRES_H

#include <QObject>
#include <QTime>
#include "../dataStruct/aspointfarray.h"


#include "asresource.h"

class AsFactory;

/**
 * Represents an AnnotationRes resource object in a flipchart
 *
 * \see AsAnnotation
 */
class AsAnnotationRes : public AsResource
{
Q_PROPERTY( AsPointFArray asPoints READ asGetPoints WRITE asSetPoints )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        // From AsAnnotationRes...
        AS_PROPERTY_POINTS
    };

    AsAnnotationRes( AsFactory * );
    virtual ~AsAnnotationRes();

    AsAnnotationRes( const AsAnnotationRes& );
    void operator= ( const AsAnnotationRes& );

    // Interface..
    const QByteArray& asGetHashData( void );
    bool asIsHashDataDirty( void );
    void asComputeHashData( void );

    // Properties.
    void asResetPropertyIndex( void );

    const AsPointFArray& asGetPoints( void ) const;
    QVector<int>& asGetTimePoints( void );
    void asSetPoints( AsPointFArray& );
    void asAddPoint( QPointF& );
    void asClearPoints( void );

private:
    void asCopy( const AsAnnotationRes& );

    static QHash<QString, quint16>& m_lProperties( void );

    AsPointFArray m_Points;
    QVector<int> m_TimePoints;
    QTime m_time;

};

#endif // ASANNOTATIONRES_H
