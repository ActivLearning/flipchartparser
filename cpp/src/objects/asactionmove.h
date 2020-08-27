// Defines the AsActionMove class.
// $Author: Paul Ellis.

#ifndef ASACTIONMOVE_H
#define ASACTIONMOVE_H

#include "asaction.h"

class AsFactory;
class AsUser;
class AsMotion;

/**
 * Represents a Move action object in a flipchart
 */
class AsActionMove : public AsAction
{



public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsActionMove..
        AS_PROPERTY_RESOURCE,

		        // From AsAction...
		AS_PROPERTY_ACTIONFEATURETYPE,

    };

    // Construction and destruction
    AsActionMove( AsFactory * );
    virtual ~AsActionMove();

    AsActionMove( const AsActionMove& );
    void operator= ( const AsActionMove& );

    void asRun( AsUser*, QPointF );

    // Properties
    void asResetPropertyIndex( void );


    void asSetResource( unsigned int );

    AsResource * asGetResourcePointer( void ) override ;
    void asSetResource( AsResource * ) override ;

	bool asIsResourcePointerValid( void )override ;

    QString typeName() override;

    bool isAction() override;

    Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;


private:
    void asCopy( const AsActionMove& );

	void asVerifyTargets(QList<AsNode *> &targetNodes);

    static QHash<QString, quint16>& m_lProperties( void );

	unsigned int m_nResource;
	AsMotion *m_pMotion;
};

#endif // ASACTIONMOVE_H
