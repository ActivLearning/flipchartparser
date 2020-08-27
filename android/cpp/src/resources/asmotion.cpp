// Implements the AsMotion class.
// (c) 2006 Promethean Technologies Group Ltd

#include "asmotion.h"


AsMotion::AsMotion( AsFactory *pAsFactory ) : AsResource( pAsFactory ),
                                              m_pMovingObjectNode( NULL ),
                                              m_pMovingObjectRend(NULL),
                                              m_Translate( QPointF(0 ,0) ),
                                              m_Angle( 0 ),
                                              m_incremental( true ),
					      m_doAngle( false ),
                                              m_bOverrideOrigin( false ),
                                              m_Position( AsMotion::AS_POSITION_NONE ),
                                              m_Size( AsMotion::AS_SIZE_NONE ),
                                              m_Stretch( AsMotion::AS_STRETCH_NONE ),
					      m_maintainAspect(false),
                                              m_Reason( AsMotion::AS_REASON_UNKNOWN ),
                                              m_UseTarget( false )


                    
{
    asSetType( AsObject::AS_OBJECT_MOTIONRES );
}

AsMotion::~AsMotion()
{

}

AsMotion::AsMotion( const AsMotion& motion ) : AsResource( motion )
{
    // Beware - motion params only, no resource params copied!
    this->m_pMovingObjectNode = motion.asGetObjectToMoveNode();
    this->m_pMovingObjectRend = motion.asGetMovingObjRenderable();
    this->m_Translate = motion.asGetTranslate();
    this->m_Angle = motion.asGetRotation();
    this->m_incremental = motion.asIsIncremental();
    this->m_doAngle = motion.asIsDoAngle();
    this->m_bOverrideOrigin = motion.asGetOverrideOrigin();
    this->m_Position = motion.asGetPosition();
    this->m_Size = motion.asGetSize();
    this->m_Stretch = motion.asGetStretch();
    this->m_Reason = motion.asGetReason();
    this->m_UseTarget = motion.asGetUseTarget();
    this->m_maintainAspect = motion.asIsMaintainAspect();


}

void AsMotion::asCreateMotion(const AsPointer& pObject2Move, 
			      const QPointF& translate, 
			      qreal angle,
			      bool incremental,
			      AsMotion::AsEnumPosition pos,
			      AsMotion::AsEnumSize size,
			      AsMotion::AsEnumStretch stretch,
			      bool doAngle,
			      const bool maintainAspect/*=false*/)
{
    m_pMovingObjectNode = pObject2Move;
    m_Translate = translate;
    m_Angle = angle;
    m_incremental = incremental;
    m_doAngle = doAngle;
    m_Position = pos;
    m_Size = size;
    m_Stretch = stretch;
    m_bOverrideOrigin = false;
    m_UseTarget = false;
    m_maintainAspect = maintainAspect;

    m_bHashDataDirty = true;
}

void AsMotion::asResetMotion( void )
{
    m_pMovingObjectNode = NULL;
    m_pMovingObjectRend = NULL;
    m_Translate = QPointF(0 ,0);
    m_Angle = 0;
    m_incremental = true;
    m_doAngle = false;
    m_bOverrideOrigin = false;
    m_Position = AsMotion::AS_POSITION_NONE;
    m_Size = AsMotion::AS_SIZE_NONE;
    m_Stretch = AsMotion::AS_STRETCH_NONE;
    m_Reason = AsMotion::AS_REASON_UNKNOWN;
    m_UseTarget = false;
    m_maintainAspect = false;


}

void AsMotion::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

QHash<QString, quint16>& AsMotion::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
       // HashProperties.insert( "asDateTimeCreated", ( quint16 )AsMotion::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
      //  HashProperties.insert( "asOriginalType", AsMotion::AS_PROPERTY_ORIGINALTYPE );
      //  HashProperties.insert( "asOriginalFilename", AsMotion::AS_PROPERTY_ORIGINALFILENAME );

        // From AsMotion...
       // HashProperties.insert( "movingObjectNode", AsMotion::AS_PROPERTY_MOVINGOBJECT );
        HashProperties.insert( "translate", AsMotion::AS_PROPERTY_TRANS );
        HashProperties.insert( "angle", AsMotion::AS_PROPERTY_ANGLE );
        HashProperties.insert( "incremental", AsMotion::AS_PROPERTY_INC_ANGLE );
	    HashProperties.insert( "doAngle", AsMotion::AS_PROPERTY_DOANGLE );
        HashProperties.insert( "position", AsMotion::AS_PROPERTY_POSITION );
        HashProperties.insert( "size", AsMotion::AS_PROPERTY_SIZE );
        HashProperties.insert( "stretch", AsMotion::AS_PROPERTY_STRETCH );
    }

    return HashProperties;
}

const QByteArray& AsMotion::asGetHashData( void )
{
    return m_HashData;
}

bool AsMotion::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsMotion::asComputeHashData( void )
{
    // TODO - Compute hash data.
    m_bHashDataDirty = false;
}

const AsPointer& AsMotion::asGetObjectToMoveNode( void ) const
{
    return m_pMovingObjectNode;
}

void AsMotion::asSetObjectToMoveNode( const AsPointer& pObject2Move )
{
    m_pMovingObjectNode = pObject2Move;
    m_bHashDataDirty = true;
}

const QPointF& AsMotion::asGetTranslate( void ) const
{
    return m_Translate;
}

void AsMotion::asSetTranslate( const QPointF& translate )
{
    m_Translate = translate;
    m_bHashDataDirty = true;
}

bool AsMotion::asGetUseTarget( void ) const
{
    return this->m_UseTarget;
}

void AsMotion::asSetUseTarget( bool b )
{
    this->m_UseTarget = b;
    m_bHashDataDirty = true;
}

const QPointF& AsMotion::asGetPenPosition( void ) const
{
    return m_PenPosition;
}

void AsMotion::asSetPenPosition( const QPointF& pos )
{
    m_PenPosition = pos;
}

const QPointF& AsMotion::asGetPenFromPosition() const
{
    return m_PenFromPosition;
}

void AsMotion::asSetPenFromPosition( const QPointF& pos )
{
    m_PenFromPosition = pos;
}

qreal AsMotion::asGetRotation( void ) const
{
    return m_Angle;
}

void AsMotion::asSetRotation( qreal angle )
{
    m_Angle = angle;
    m_bHashDataDirty = true;
}

bool AsMotion::asGetOverrideOrigin( void ) const
{
    return m_bOverrideOrigin;
}

void AsMotion::asSetOverrideOrigin( bool b )
{
    m_bOverrideOrigin = b;
}

const QPointF& AsMotion::asGetOrigin( void ) const
{
    return m_Origin;
}

void AsMotion::asSetOrigin( const QPointF& pt )
{
    m_Origin = pt;
}

bool AsMotion::asIsIncremental( void ) const
{
    return m_incremental;
}

void AsMotion::asSetIncremental( bool incremental )
{
    m_incremental = incremental;
    m_bHashDataDirty = true;
}

bool AsMotion::asIsDoAngle( void ) const
{
    return m_doAngle;
}

void AsMotion::asSetDoAngle( bool doAngle )
{
    m_doAngle = doAngle;
    m_bHashDataDirty = true;
}

AsMotion::AsEnumPosition AsMotion::asGetPosition( void ) const
{
    return m_Position;
}

void AsMotion::asSetPosition( const AsMotion::AsEnumPosition pos )
{
    m_Position = pos;
    m_bHashDataDirty = true;
}

// Size...
AsMotion::AsEnumSize AsMotion::asGetSize( void ) const
{
    return m_Size;
}

void AsMotion::asSetSize( const AsMotion::AsEnumSize size )
{
    m_Size = size;
    m_bHashDataDirty = true;
}

// Stretch...
AsMotion::AsEnumStretch AsMotion::asGetStretch( void ) const
{
    return m_Stretch;
}

void AsMotion::asSetStretch( const AsMotion::AsEnumStretch stretch )
{
    m_Stretch = stretch;
    m_bHashDataDirty = true;
}

/**
 * Accessor for the @c m_maintainAspect member variable.
 */
bool AsMotion::asIsMaintainAspect() const
{
    return m_maintainAspect;
}

/**
 * Mutator for the @c m_maintainAspect member variable.
 */
void AsMotion::asSetMaintainAspect(const bool maintainAspect)
{
    m_maintainAspect = maintainAspect;
}

AsMotion::AsEnumReason AsMotion::asGetReason( void ) const
{
    return m_Reason;
}

void AsMotion::asSetReason( const AsMotion::AsEnumReason r )
{
    m_Reason = r;
}



void AsMotion::asSetMovingObjRenderable(AsRenderable *pObj2MoveRend)
{
    m_pMovingObjectRend = pObj2MoveRend;
}

AsRenderable* AsMotion::asGetMovingObjRenderable(void) const
{
    return m_pMovingObjectRend;
}

QString AsMotion::getPropertyNameById(int nID)
{
    return m_lProperties().key(nID);
}

int AsMotion::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

QString AsMotion::typeName()
{
    return "motionRes";
}

