// Defines the AsMotion class.
// (c) 2006 Promethean Technologies Group Ltd

#ifndef ASMOTION_H
#define ASMOTION_H

#include <QPointF>
#include "../io/asnode.h"
#include "../resources/asresource.h"
#include "../objects/aspointer.h"


class AsRenderable;

/**
 * Represents a Motion resource object in a flipchart
 */
class AsMotion : public AsResource
{

Q_PROPERTY( AsPointer aspMovingObjectNode READ asGetObjectToMoveNode WRITE asSetObjectToMoveNode )
Q_PROPERTY( QPointF asTranslate READ asGetTranslate WRITE asSetTranslate )
Q_PROPERTY( double asAngle READ asGetRotation WRITE asSetRotation )
Q_PROPERTY( bool asincremental READ asIsIncremental WRITE asSetIncremental )
Q_PROPERTY( bool asDoAngle READ asIsDoAngle WRITE asSetDoAngle )
Q_PROPERTY( AsEnumPosition asPosition READ asGetPosition WRITE asSetPosition )
Q_PROPERTY( AsEnumSize asSize READ asGetSize WRITE asSetSize )
Q_PROPERTY( AsEnumStretch asStretch READ asGetStretch WRITE asSetStretch )
Q_ENUMS( AsEnumPosition )
Q_ENUMS( AsEnumSize )
Q_ENUMS( AsEnumStretch )

public:
    enum AsEnumProperty
    {
        //! From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        //! From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        //! From AsMotion...
	    AS_PROPERTY_MOVINGOBJECT,
	    AS_PROPERTY_TRANS,
	    AS_PROPERTY_ANGLE,
	    AS_PROPERTY_INC_ANGLE,
        AS_PROPERTY_POSITION,
        AS_PROPERTY_SIZE,
        AS_PROPERTY_STRETCH,
	    AS_PROPERTY_DOANGLE
    };

    enum AsEnumPosition
    {
        AS_POSITION_NONE = 0,
        AS_POSITION_TOPLEFT,
        AS_POSITION_TOP,
        AS_POSITION_TOPRIGHT,
        AS_POSITION_LEFT,
        AS_POSITION_CENTRAL,
        AS_POSITION_RIGHT,
        AS_POSITION_BOTTOMLEFT,
        AS_POSITION_BOTTOM,
        AS_POSITION_BOTTOMRIGHT
    };

    enum AsEnumSize
    {
        AS_SIZE_NONE = 0,
        AS_SIZE_TOPLEFT,
        AS_SIZE_TOP,
        AS_SIZE_TOPRIGHT,
        AS_SIZE_LEFT,
        AS_SIZE_CENTRAL,
        AS_SIZE_RIGHT,
        AS_SIZE_BOTTOMLEFT,
        AS_SIZE_BOTTOM,
        AS_SIZE_BOTTOMRIGHT
    };

    enum AsEnumStretch
    {
        AS_STRETCH_NONE = 0,
        AS_STRETCH_TOPLEFT,
        AS_STRETCH_TOP,
        AS_STRETCH_TOPRIGHT,
        AS_STRETCH_LEFT,
        AS_STRETCH_CENTRAL,
        AS_STRETCH_RIGHT,
        AS_STRETCH_BOTTOMLEFT,
        AS_STRETCH_BOTTOM,
        AS_STRETCH_BOTTOMRIGHT
    };

    enum AsEnumReason
    {
        AS_REASON_UNKNOWN = 0,
        AS_REASON_ACTION,
        AS_REASON_DRAG,
        AS_REASON_FREEMOVE
    };

	AsMotion( AsFactory * );
	AsMotion( const AsMotion& );
    ~AsMotion();

    //! Interface..
    const QByteArray& asGetHashData( void ) override ;
    bool asIsHashDataDirty( void ) override ;
    void asComputeHashData( void )override ;

	//! all parameters
    void asCreateMotion( const AsPointer& pObject2MoveNode, 
			 const QPointF& translate, 
			 qreal angle = 0,
			 bool incremental = false,
                         AsEnumPosition pos = AsMotion::AS_POSITION_NONE,
                         AsEnumSize size = AsMotion::AS_SIZE_NONE,
                         AsEnumStretch stretch = AsMotion::AS_STRETCH_NONE,
			 bool doAngle = false,
			 const bool maintainAspect = false);

    void asResetMotion( void );

    //! Properties.
    void asResetPropertyIndex( void );

    //! Motion vector, in world co-ords.
    const QPointF& asGetTranslate( void ) const;
	void asSetTranslate( const QPointF& );

    //! Pointer to the object being moved
    const AsPointer& asGetObjectToMoveNode( void ) const;
	void asSetObjectToMoveNode( const AsPointer& pObject2MoveNode );

    //! Angle to rotate to, or to increment by.
    qreal asGetRotation( void ) const;
    void asSetRotation( qreal angle );

    bool asGetOverrideOrigin( void ) const;
    void asSetOverrideOrigin( bool );

    const QPointF& asGetOrigin( void ) const;
    void asSetOrigin( const QPointF& );

    //! How to modify the angle.
    bool asIsIncremental( void ) const;			            
    void asSetIncremental( bool incremental ); 

	bool asIsDoAngle( void ) const;
	void asSetDoAngle( bool doAngle );

    //! Position...
    AsEnumPosition asGetPosition( void ) const;
    void asSetPosition( const AsEnumPosition );

    //! Size...
    AsEnumSize asGetSize( void ) const;
    void asSetSize( const AsEnumSize );

    //! Stretch...
    AsEnumStretch asGetStretch( void ) const;
    void asSetStretch( const AsEnumStretch );

    bool asIsMaintainAspect() const;
    void asSetMaintainAspect(const bool maintainAspect);

    //! What caused this motion.
    AsEnumReason asGetReason( void ) const;
    void asSetReason( const AsEnumReason );

    bool asGetUseTarget( void ) const;
    void asSetUseTarget( bool );

    const QPointF& asGetPenPosition( void ) const;
    void asSetPenPosition( const QPointF& );

    const QPointF& asGetPenFromPosition() const;
    void asSetPenFromPosition( const QPointF& );



	//! to get and set the Object in motion renderable
	void asSetMovingObjRenderable(AsRenderable *);
	AsRenderable* asGetMovingObjRenderable(void) const;

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:
    static QHash<QString, quint16>& m_lProperties( void );

	//! Object in motion node and renderable
	AsPointer m_pMovingObjectNode;
	AsRenderable *m_pMovingObjectRend;

    QPointF m_Translate;

    QPointF m_PenPosition;
    QPointF m_PenFromPosition;

    //! Rotation
    qreal m_Angle;
    bool m_incremental;
    bool m_doAngle;
    bool m_bOverrideOrigin;
    QPointF m_Origin;

	//! poisition details
    AsEnumPosition m_Position;
	//! size details
    AsEnumSize m_Size;
	//! stretch details
    AsEnumStretch m_Stretch;
    /// Whether stretching should be applied equally in x and y directions.
    bool m_maintainAspect;
    AsEnumReason m_Reason;

    //! For moving objects to an absolute position.
    QPointF m_Target;
    bool m_UseTarget;


};

#endif // ASMOTION_H
