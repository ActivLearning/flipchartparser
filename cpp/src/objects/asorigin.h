// Defines the AsOrigin class.
// $Author: Paul Wareing.

#ifndef ASORIGIN_H
#define ASORIGIN_H

#include <QMetaType>
#include <QPointF>

#include "asobject.h"

class AsFactory;

/**
 * Represents an Origin property in a flipchart
 */
class AsOrigin : public AsObject
{


    Q_PROPERTY( QPointF asOrigin READ asGetOrigin WRITE asSetOrigin EDITABLE true )

public:
    enum AsEnumProperty
    {
        // From AsObject...
                AS_PROPERTY_DATETIMECREATED = 1,

        // From AsOrigin...
                AS_PROPERTY_ORIGIN
    };

    // Construction and destruction.
    AsOrigin( AsFactory * );
    AsOrigin();
    AsOrigin( const AsOrigin& );

    virtual ~AsOrigin();

    void operator= ( const AsOrigin& );

    bool operator== ( const AsOrigin& );

    void asCopy( const AsOrigin& );

    // Properties.
    void asResetPropertyIndex( void );

    const QPointF& asGetOrigin( void ) const;
    void asSetOrigin( QPointF& );

    void asSetXY(qreal x , qreal y );
    qreal asGetX( void ) const;
    qreal asGetY( void ) const;

    QString typeName() override;

    Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:
    // Property hash table.
    static QHash<QString, quint16>& m_lProperties( void );

    // Properties.
    QPointF m_Origin;
};

Q_DECLARE_METATYPE( AsOrigin )

#endif // ASORIGIN_H
