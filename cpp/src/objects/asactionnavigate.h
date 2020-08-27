// Defines the AsActionNavigate class.
// $Author: Paul Ellis.

#ifndef ASACTIONNAVIGATE_H
#define ASACTIONNAVIGATE_H

#include "asaction.h"

class AsFactory;
class AsUser;
class AsNode;

/**
 * Represents a Navigate action object in a flipchart
 */
class AsActionNavigate : public AsAction
{



public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsActionNavigate...
		AS_PROPERTY_NAVIGATETYPE,
		AS_PROPERTY_GOTOPAGENUMBER,

		// From AsAction...
		AS_PROPERTY_ACTIONFEATURETYPE,
    };

	enum AsEnumNavigate
	{
		ASNAVIGATE_NEXTPAGE = 0,
		ASNAVIGATE_PREVIOUSPAGE,
		ASNAVIGATE_FIRSTPAGE,
		ASNAVIGATE_LASTPAGE,
		ASNAVIGATE_ANOTHERPAGE,
		ASNAVIGATE_NEXTPAGEINHISTORY,
		ASNAVIGATE_PREVIOUSPAGEINHISTORY,
	};

    // Construction and destruction
    AsActionNavigate( AsFactory * );
    virtual ~AsActionNavigate();

    AsActionNavigate( const AsActionNavigate& );
    void operator= ( const AsActionNavigate& );

    void asRun( AsUser*, QPointF );

	void asSetUserPointer( AsUser* pUser );
	AsUser * asGetUserPointer( void );

    // Properties
    void asResetPropertyIndex( void );

	void asSetNavigateType( AsEnumNavigate );
    AsEnumNavigate asGetNavigateType( void ) const;
    
	int asGetDestinationPageNumber() const;
    void asSetDestinationPageNumber( int pageNumber );

    int asGetDestinationPageId() const;
    void asSetDestinationPageId( int pageId );

    void asSetDestinationPageVar(int dest);
	int asGetDestinationPageVar() const;

    static const int FLP_FIRST_PASS_PAGE_NUMBER_MODIFIER;

    QString typeName() override;

    bool isAction() override;

	Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:

    void asCopy( const AsActionNavigate& );
    quint32 asGetPageId(int nPageNumber) const;
    int asGetPageNumber(quint32 nPageId) const;

private:

    static QHash<QString, quint16>& m_lProperties( void );
	AsEnumNavigate m_NavigateType;

    // Only used for asActionAnotherPage
    mutable int m_nDestinationPageId;
    mutable int m_nDestinationPageNumber;
    mutable int m_nDestinationPageVar;
};

#endif // ASACTIONNAVIGATE_H
