// Defines the AsAction class.
// $Author: Paul Ellis.

#ifndef ASACTION_H
#define ASACTION_H

#include <QPoint>
#include "asobject.h"

class AsFactory;
class AsNode;
class AsUser;

/**
 * An abstract base class for flipchart actions
 */
class AsAction : public AsObject
{



public:
	// Construction and destruction
    AsAction( AsFactory * );
    virtual ~AsAction();

    AsAction( const AsAction& );
    void operator= ( const AsAction& );

	void asSetFeatureType(AsObject::AsEnumObjectType featureType);
    AsObject::AsEnumObjectType asGetFeatureType() const;

    // Interface.


    // Properties.
private:
    void asCopy( const AsAction& );
	AsObject::AsEnumObjectType m_featureType;
};

#endif // ASACTION_H
