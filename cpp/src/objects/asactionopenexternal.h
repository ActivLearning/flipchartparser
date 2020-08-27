// Defines the AsActionOpenExternal class.
// $Author: Paul Ellis.

#ifndef ASACTIONOPENEXTERNAL_H
#define ASACTIONOPENEXTERNAL_H

#include "asaction.h"
#include "aspointer.h"

class AsFactory;
class AsUser;
class AsMediaFileRes;

/**
 * Represents an OpenExternal action object in a flipchart
 */
class AsActionOpenExternal : public AsAction
{



public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsActionOpenExternal...
		AS_PROPERTY_RESOURCE,
		AS_PROPERTY_ISINPLACE,
		AS_PROPERTY_INPLACENODE,
		AS_PROPERTY_HASAUTOSTART,
        AS_PROPERTY_COMMANDLINEPARAMETERS,
        AS_PROPERTY_LOOP,
        AS_PROPERTY_KEEPASPECT,
        AS_PROPERTY_SHOWCONTROLLER,

		// From AsAction...
		AS_PROPERTY_ACTIONFEATURETYPE,

    };

    // Construction and destruction
    AsActionOpenExternal( AsFactory * );
    virtual ~AsActionOpenExternal();

    AsActionOpenExternal( const AsActionOpenExternal& );
    void operator= ( const AsActionOpenExternal& );

    void asRun( AsUser* pUser = NULL, QPointF pos = QPointF() );

    // Properties
    void asResetPropertyIndex( void );

    unsigned int asGetResource( void ) const;
    void asSetResource( unsigned int );

    AsResource * asGetResourcePointer( void );
    void asSetResource( AsResource * );

	void asSetInPlace( bool inPlace );
        bool asIsInPlace( void ) const;
	void asSetInPlaceNode( AsPointer pTargetNode );
	const AsPointer asGetInPlaceNode( void ) const;

	void asSetAutoStart( bool autoStart );
        bool asHasAutoStart( void ) const;

    void asSetCommandLineParameters(QString strCommandLineParameters);
    QString asGetCommandLineParameters() const;

    bool asGetLoop() const;
    void asSetLoop( bool loop );
    
    bool asGetKeepAspect() const;
    void asSetKeepAspect( bool keepAspect );
    
    bool asGetShowController() const;
    void asSetShowController( bool showController );

	bool asIsResourcePointerValid( void );

    QString typeName() override;

protected:
    int getPropertyIdByName(QString name) const override;

    QString getPropertyNameById(int nID) override;

private:
    void asCopy( const AsActionOpenExternal& );

    static QHash<QString, quint16>& m_lProperties( void );

	static QHash<QString, QString> m_mimeTypes;

    unsigned int m_nResource;
	bool m_bDisplayInPlace;
	AsPointer m_pInPlaceNode;

	bool m_bAutoStart;

    QString m_strCommandLineParameters;

    bool m_loop;
    bool m_keepAspect;
    bool m_showController;

    AsMediaFileRes *m_pAsMediaFileRes;
};

#endif // ASACTIONOPENEXTERNAL_H
