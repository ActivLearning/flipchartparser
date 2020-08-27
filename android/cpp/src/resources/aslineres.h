// Defines the AsLineRes class.
// $Author: Paul Wareing.

#ifndef ASLINERES_H
#define ASLINERES_H

#include <QObject>
#include <QLineF>

#include "../dataStruct/aspointfarray.h"
#include "asresource.h"

class AsFactory;

/**
 * Represents a LineRes resource object in a flipchart
 *
 * \see AsLine
 */
class AsLineRes : public AsResource
{

Q_PROPERTY( AsPointFArray asLine READ asGetLine WRITE asSetLine )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        // From AsLineRes...
        AS_PROPERTY_LINE
    };

    AsLineRes( AsFactory * );
    virtual ~AsLineRes();

    AsLineRes( const AsLineRes& );
    void operator= ( const AsLineRes& );

    // Interface..
    const QByteArray& asGetHashData( void ) override ;
    bool asIsHashDataDirty( void )override ;
    void asComputeHashData( void )override ;

    // Properties.
    void asResetPropertyIndex( void );

    const AsPointFArray asGetLine( void ) const;
    void asSetLine( AsPointFArray& );

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;



private:
    void asCopy( const AsLineRes& );

    static QHash<QString, quint16>& m_lProperties( void );

    AsPointFArray m_Line;
};

#endif // ASLINERES_H
