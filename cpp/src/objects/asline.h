// Defines the AsLine class.
// $Author: Paul Wareing.

#ifndef ASLINE_H
#define ASLINE_H

#include "asrenderable.h"
#include "../resources/aslineres.h"


class AsFactory;

/**
 * Represents a Line object in a flipchart
 */
class AsLine : public AsRenderable
{

Q_PROPERTY( unsigned int asResource READ asGetResource WRITE asSetResource )
Q_PROPERTY( AsEnumEndCap asEndCapA READ asGetEndCapA WRITE asSetEndCapA EDITABLE true )
Q_PROPERTY( AsEnumEndCap asEndCapB READ asGetEndCapB WRITE asSetEndCapB EDITABLE true )
Q_ENUMS( AsEnumEndCap )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsRenderable...
        AS_PROPERTY_TRANSFORM = 2,
        AS_PROPERTY_TWIPS = 3,
        AS_PROPERTY_NAME = 4,
        AS_PROPERTY_KEYWORDS = 5,
        AS_PROPERTY_VISIBLE = 6,
        AS_PROPERTY_BOUNDINGRECT = 7,
        AS_PROPERTY_LAYER = 8,
        AS_PROPERTY_Z = 9,
        AS_PROPERTY_INK = 10,
        AS_PROPERTY_SCALEORIGIN = 11,
        AS_PROPERTY_ROTATEORIGIN = 12,
        AS_PROPERTY_CANMOVE = 13,
        AS_PROPERTY_CANSIZE = 14,
        AS_PROPERTY_CANROTATE = 15,
        AS_PROPERTY_CANBLOCK = 16,
        AS_PROPERTY_CANSNAP = 17,
        AS_PROPERTY_LOCKED = 18,
        AS_PROPERTY_SNAPBACK = 19,
        AS_PROPERTY_PATHPOINTER = 20,
        AS_PROPERTY_ROTATEABOUTPOINTER = 21,
        AS_PROPERTY_ROTATEPOINT = 22,
        AS_PROPERTY_ROTATEABOUT = 23,
        AS_PROPERTY_ROTATESTEP = 24,
        AS_PROPERTY_SNAPTOPOINTER = 25,
        AS_PROPERTY_SNAPPOINT = 26,
        AS_PROPERTY_SNAPTO = 27,
        AS_PROPERTY_CANCONTAIN = 28,
        AS_PROPERTY_CONTAINPOINTER = 29,
        AS_PROPERTY_CONTAINWORDS = 30,
        AS_PROPERTY_CONTAINRULE = 31,
        AS_PROPERTY_V2TYPE = 32,
        AS_PROPERTY_CONNECTORLIST = 33,
        AS_PROPERTY_LABEL = 34,
        AS_PROPERTY_QUESTIONITEM = 35,
        AS_PROPERTY_QUESTIONITEMID = 36,
		AS_PROPERTY_ALLOWSNAPBACK = 37,
        AS_PROPERTY_DRAGACOPY = 41,
        AS_PROPERTY_QUESTIONTAG = 42,
        AS_PROPERTY_REWARD_SOUND = 43,
        AS_PROPERTY_REWARD_SOUND_LOCATION = 44,
		AS_PROPERTY_ASYNCTESTTAG = 45,
        AS_PROPERTY_INTERACTMODE = 46,

        // From AsLine...
        AS_PROPERTY_RESOURCE = 38,
        AS_PROPERTY_ENDCAPA = 39,
        AS_PROPERTY_ENDCAPB = 40

        // Next Property ID = 47
    };

    enum AsEnumEndCap
    {
        AS_ENDCAP_NONE = 0,
        AS_ENDCAP_RADIUS,
        AS_ENDCAP_BLOB,
        AS_ENDCAP_SQUARE,
        AS_ENDCAP_ARROW,
        AS_ENDCAP_SOLIDARROW
    };

	enum AsEnumLineEnd
	{
		AS_END_NONE = 0,
		AS_END_A,
		AS_END_B 
	};

    // Construction and destruction
    AsLine( AsFactory * );
    virtual ~AsLine();

    AsLine( const AsLine& );
    void operator= ( const AsLine& );

    bool operator== ( const AsLine& );

    // Operations.
    bool asCheckHit(  const QPointF & worldPos )override ;
	AsEnumLineEnd asCheckHitEnd( const QPointF & worldPos );
    AsPointFArray asGetPoints( void )override ;

    // Properties
    void asResetPropertyIndex( void );


    void asSetResource( unsigned int );

    AsResource * asGetResourcePointer( void )override ;
    void asSetResource( AsResource * )override ;

    AsEnumEndCap asGetEndCapA( void ) const;
    void asSetEndCapA( AsEnumEndCap );

    AsEnumEndCap asGetEndCapB( void ) const;
    void asSetEndCapB( AsEnumEndCap );



	bool asIsResourcePointerValid( void )override ;

    Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

    const Json::Value &asResourceSerialized() override;

public:
    QString typeName() override;

public slots:
    void asLineResChanged( AsLineRes * );

private:
    void asCopy( const AsLine& );

    static QHash<QString, quint16>& m_lProperties( void );

    AsEnumEndCap m_nEndCapA;
    AsEnumEndCap m_nEndCapB;
    unsigned int m_nResource;
    AsLineRes *m_pAsLineRes;



    void asBuildPainterPath( void );
    bool m_bPainterPathDirty;
};

#endif // ASLINE_H
