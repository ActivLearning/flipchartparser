// Defines the AsActionOnObject class.
// (c) 2006 Promethean Technologies Group Ltd

#ifndef ASACTIONONOBJECT_H
#define ASACTIONONOBJECT_H

#include "asaction.h"
#include "aspointer.h"

class AsFactory;
class AsUser;
class AsNode;

/**
 * Represents an OnObject action object in a flipchart
 */
class AsActionOnObject : public AsAction
{



public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsActionOnObject...
		AS_PROPERTY_ACTIONONOBJ_TARGET,
        AS_PROPERTY_ACTIONONOBJ_ACTION,
        AS_PROPERTY_ACTIONONOBJ_TRANSLUCENCY,

		// From AsAction...
		AS_PROPERTY_ACTIONFEATURETYPE,
    };

    enum AsEnumAction
    {
        AS_ACTION_NONE = 0,
        AS_ACTION_SHOW,
        AS_ACTION_HIDE,
        AS_ACTION_TRANSLUCENCY,
        AS_ACTION_MORETRANSLUCENCY,
        AS_ACTION_LESSTRANSLUCENCY,
        AS_ACTION_TOFRONT,
        AS_ACTION_TOBACK,
        AS_ACTION_TOFRONTLAYER,
        AS_ACTION_TOMIDDLELAYER,
        AS_ACTION_TOBACKLAYER,
        AS_ACTION_LOCK,
        AS_ACTION_UNLOCK,
        AS_ACTION_REFLECT,
        AS_ACTION_INVERT,
        AS_ACTION_FLIPINX,
        AS_ACTION_FLIPINY,
        AS_ACTION_MIRRORINX,
        AS_ACTION_MIRRORINY,
		AS_ACTION_DUPLICATE,
		AS_ACTION_IMAGEFITTOWIDTH,
		AS_ACTION_IMAGEFITTOHEIGHT,
		AS_ACTION_IMAGEFITTOPAGE,
		AS_ACTION_RESETSIZE,
		AS_ACTION_RESETCOLOURS,
        AS_ACTION_COPYOBJECT,
        AS_ACTION_CUTOBJECT,
		AS_ACTION_BRINGFORWARDS,
		AS_ACTION_SENDBACKWARDS,
		AS_ACTION_ALIGN,
		AS_ACTION_ALIGNLEFT,
		AS_ACTION_ALIGNCENTREX,
		AS_ACTION_ALIGNRIGHT,
		AS_ACTION_ALIGNTOP,
		AS_ACTION_ALIGNCENTREY,
		AS_ACTION_ALIGNBOTTOM,
		AS_ACTION_ALIGNWIDTH,
		AS_ACTION_ALIGNHEIGHT,
		AS_ACTION_ALIGNCOMPLETE,
		AS_ACTION_ALIGNANGLE,
		AS_ACTION_DELETE,
		AS_ACTION_TOGGLELOCKED,
		AS_ACTION_TOGGLEHIDDEN,
		AS_ACTION_TOGGLEGROUPED,
		AS_ACTION_EDITTEXT,
    };

    // Construction and destruction
    AsActionOnObject( AsFactory * );
    virtual ~AsActionOnObject();

    AsActionOnObject( const AsActionOnObject& );
    void operator= ( const AsActionOnObject& );

    // Properties
    void asResetPropertyIndex( void );

	void asSetTargetNode( AsPointer pTargetNode );
	const AsPointer asGetTargetNode( void ) const;

    void asSetAction( AsEnumAction action );
    AsEnumAction asGetAction( void ) const;

    void asSetTranslucency( int translucency );
    int asGetTranslucency( void ) const;

    QString typeName() override;

    bool isAction() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;


	void asRun( AsUser*, QPointF );

private:
    void asCopy( const AsActionOnObject& );

	void asVerifyTargets(QList<AsNode *> &targetNodes);
	bool asCheckClearSelection(QList<AsNode *> targetNodes, QList<AsNode *> nodesAtCursor);

    static QHash<QString, quint16>& m_lProperties( void );

	AsPointer m_pTargetNode;
    AsEnumAction m_Action;
    unsigned int m_nTranslucency;
};

#endif // ASACTIONONOBJECT_H
