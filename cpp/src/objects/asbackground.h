// Defines the AsBackground class
// $Author: Andy Edwardson

#ifndef ASBACKGROUND_H
#define ASBACKGROUND_H

#include <QHash>
#include "asobject.h"
#include "qcolor.h"
#include "../objects/aspointer.h"
#include "asink.h"

class AsImage;

/**
 * Represents a Background object in a flipchart
 */
class AsBackground : public AsObject
{
public:
    
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        AS_PROPERTY_BACKGROUNDTYPE,
        AS_PROPERTY_BACKGROUNDINK,
        AS_PROPERTY_BACKGROUNDIMAGE
    };

    enum AsEnumBackgroundType
    {
        AS_BACKGROUNDTYPE_INK = 0,
        AS_BACKGROUNDTYPE_IMAGE
    };

    // Construction and destruction.
    AsBackground();
    AsBackground( AsFactory *pFactory );
    virtual ~AsBackground();
    AsBackground( const AsBackground& );
    void operator= ( const AsBackground& );
    
    // properties
    void asResetPropertyIndex( void );

    AsEnumBackgroundType asGetBackgroundType( void ) const;
    void asSetBackgroundType( AsEnumBackgroundType );

    const AsInk & asGetBackgroundInk( void ) const;
    void asSetBackgroundInk( AsInk &  );
    AsInk * asGetBackgroundInkPointer( void );

    // convenience functions
    void asSetBackgroundColor( QColor & );
    const QColor & asGetBackgroundColor( void );

    AsPointer asGetBackgroundImagePointer( void );
    void asSetBackgroundImagePointer( AsPointer  );

    bool asDrawImageBackInk( void );

    Json::Value &serialized() override;

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:
    // Construction and copying.
    void asCopy( const AsBackground& );
    void asSetDefaults( void );

    // Properties.
    static QHash<QString, quint16>& m_lProperties( void );
    AsInk m_BackgroundInk;
    AsEnumBackgroundType m_nBackgroundType;
	AsPointer m_pImg;
};

#endif // AS_BACKGROUND_H
