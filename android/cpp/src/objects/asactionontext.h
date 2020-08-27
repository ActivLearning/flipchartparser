#ifndef ASACTIONONTEXT_H
#define ASACTIONONTEXT_H

#include "asaction.h"
#include "aspointer.h"

class AsFactory;
class AsUser;


/**
 * Represents an OnText action object in a flipchart
 */
class AsActionOnText : public AsAction
{



public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsActionOnText...
        AS_PROPERTY_ACTIONONTEXT_SOURCE,
		AS_PROPERTY_ACTIONONTEXT_TARGET,
        AS_PROPERTY_ACTIONONTEXT_ACTION,
        AS_PROPERTY_ACTIONONTEXT_TEXT,

		// From AsAction...
		AS_PROPERTY_ACTIONFEATURETYPE,
    };

    enum AsEnumAction
    {
        AS_ACTION_NONE = 0,
        AS_ACTION_NEW_TEXT_OBJECT,
        AS_ACTION_APPEND_TEXT,
        AS_ACTION_CHANGE_TEXT_VALUE,
        AS_ACTION_DECONSTRUCT_TEXT
    };

    // Construction and destruction
    AsActionOnText( AsFactory * );
    virtual ~AsActionOnText();

    AsActionOnText( const AsActionOnText& );
    void operator= ( const AsActionOnText& );

    // Properties
    void asResetPropertyIndex( void );

	void asSetSourceNode( AsPointer pSourceNode );
	const AsPointer asGetSourceNode( void ) const;

	void asSetTargetNode( AsPointer pTargetNode );
	const AsPointer asGetTargetNode( void ) const;

    void asSetAction( AsEnumAction action );
    AsEnumAction asGetAction( void ) const;

    void asSetText( QString & );
    const QString & asGetText( void ) const;

    QString typeName() override;


	void asRun( AsUser*, QPointF );

private:
    void asCopy( const AsActionOnText& );

	bool asVerifyTarget(AsNode *pTargetNode);

    static QHash<QString, quint16>& m_lProperties( void );

    AsPointer m_pSourceNode;
	AsPointer m_pTargetNode;
    AsEnumAction m_Action;
    QString m_sText; // html format

};

#endif // ASACTIONONTEXT_H
