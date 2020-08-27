// Defines the AsTransform class.
// (c)2006 Promethean Technologies Group Ltd.

#ifndef ASTRANSFORM_H
#define ASTRANSFORM_H

#include "asobject.h"
#include <QHash>
#include <QPointF>
//#include <QMatrix>

class AsFactory;
class AsOrigin;
class AsRectF;

/**
 * Represents a Transform property in a flipchart
 */
class AsTransform : public AsObject
{



public:
    enum AsEnumProperty
    {
        // From AsObject...
                AS_PROPERTY_DATETIMECREATED = 1,

        // From AsTransform...
                AS_PROPERTY_TRANSLATE,
        AS_PROPERTY_ANGLE,
        AS_PROPERTY_SCALEFACTOR,
        AS_PROPERTY_REFLECTED,
        AS_PROPERTY_INVERTED
    };

    // Construction and destruction.
    AsTransform( AsFactory * );
    AsTransform();
    AsTransform( const AsTransform& );

    virtual ~AsTransform();

    void operator= ( const AsTransform& );

    bool operator== ( const AsTransform& );

    void asCopy( const AsTransform& );

    // Properties.
    void asResetPropertyIndex( void );

    const QPointF& asGetTranslate( void ) const;
    void asSetTranslate( const QPointF& );

    double asGetAngle() const;
    void asSetAngle(double dAngle);

    const QPointF& asGetScaleFactor( void ) const;
    void asSetScaleFactor( const QPointF& );

    bool asGetReflected( void ) const;
    void asSetReflected( bool );

    bool asGetInverted( void ) const;
    void asSetInverted( bool );

    QString typeName() override;
    // affine transformations
//    const QMatrix& asDoTransform( const AsOrigin & ScaleOrigin , const AsRectF & obRect );
//    const QMatrix& asDoTransform( const AsOrigin & ScaleOrigin , const AsRectF & obRect , const QMatrix & WorldMatrix );
protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:
    // Property hash table.
    static QHash<QString, quint16>& m_lProperties( void );

    // Properties.
    QPointF m_Translate;
    double m_dAngle;
    QPointF m_ScaleFactor;
    bool m_bReflected;
    bool m_bInverted;

    // Computed.
//    QMatrix m_Matrix;

    void asResetTransformProps( void );

    double asNormaliseAngle(double dAngle);

    static const double s_kMaxAngle;
    static const double s_kMinAngle;
};



#endif // ASTRANSFORM_H
