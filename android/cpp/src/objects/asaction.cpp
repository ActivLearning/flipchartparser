// Implements the AsAction class.
// $Author: Paul Ellis.

#include "asaction.h"

AsAction::AsAction( AsFactory *pAsFactory ) : AsObject( pAsFactory )
{

}

AsAction::AsAction( const AsAction& action ) : AsObject( action )
{
    this->asCopy( action );
}

AsAction::~AsAction()
{

}

void AsAction::operator= ( const AsAction& action )
{
    AsObject::operator =( action );
    this->asCopy( action );
}

void AsAction::asCopy( const AsAction& action )
{
	m_featureType = action.asGetFeatureType();
}

// Properties...
void AsAction::asSetFeatureType(AsObject::AsEnumObjectType featureType)
{
	m_featureType = featureType;
}

AsObject::AsEnumObjectType AsAction::asGetFeatureType() const
{
	return m_featureType;
}
