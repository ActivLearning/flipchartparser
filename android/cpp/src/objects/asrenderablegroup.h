// Defines the AsRenderableGroup class.
// $Author: Paul Wareing.

#ifndef ASRENDERABLEGROUP_H
#define ASRENDERABLEGROUP_H

#include "asrenderable.h"
#include "astransform.h"

class AsFactory;

/**
 * Represents a RenderableGroup object in a flipchart
 */
class AsRenderableGroup : public AsRenderable
{
Q_PROPERTY( AsPointer asNode READ asGetNode WRITE asSetNode )
Q_PROPERTY( bool asV2Group READ asGetV2Group WRITE asSetV2Group )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsRenderable...
        AS_PROPERTY_TRANSFORM,
        AS_PROPERTY_TWIPS,
        AS_PROPERTY_NAME,
        AS_PROPERTY_KEYWORDS,
        AS_PROPERTY_VISIBLE,
        AS_PROPERTY_BOUNDINGRECT,
        AS_PROPERTY_LAYER,
        AS_PROPERTY_Z,
        AS_PROPERTY_INK,
        AS_PROPERTY_SCALEORIGIN,
        AS_PROPERTY_ROTATEORIGIN,
        AS_PROPERTY_CANMOVE,
        AS_PROPERTY_CANSIZE,
        AS_PROPERTY_CANROTATE,
        AS_PROPERTY_CANBLOCK,
        AS_PROPERTY_CANSNAP,
        AS_PROPERTY_LOCKED,
        AS_PROPERTY_SNAPBACK,
        AS_PROPERTY_PATHPOINTER,
        AS_PROPERTY_ROTATEABOUTPOINTER,
        AS_PROPERTY_ROTATEPOINT,
        AS_PROPERTY_ROTATEABOUT,
        AS_PROPERTY_ROTATESTEP,
        AS_PROPERTY_SNAPTOPOINTER,
        AS_PROPERTY_SNAPPOINT,
        AS_PROPERTY_SNAPTO,
        AS_PROPERTY_CANCONTAIN,
        AS_PROPERTY_CONTAINPOINTER,
        AS_PROPERTY_CONTAINWORDS,
        AS_PROPERTY_CONTAINRULE,
        AS_PROPERTY_V2TYPE,
        AS_PROPERTY_CONNECTORLIST,
        AS_PROPERTY_LABEL,
        AS_PROPERTY_QUESTIONITEM,
        AS_PROPERTY_QUESTIONITEMID,
		AS_PROPERTY_ALLOWSNAPBACK,

        // AsRenderableGroup...
        AS_PROPERTY_NODE,
        AS_PROPERTY_V2GROUP,

        AS_PROPERTY_QUESTIONTAG,
		AS_PROPERTY_ASYNCTESTTAG,

        // From AsRenderable again...
        AS_PROPERTY_INTERACTMODE,

    };

    // Construction and destruction
    AsRenderableGroup( AsFactory * );
    virtual ~AsRenderableGroup();

    AsRenderableGroup( const AsRenderableGroup& );
    void operator= ( const AsRenderableGroup& );

    bool operator== ( const AsRenderableGroup& );

    // Properties
    void asResetPropertyIndex( void );

    const AsPointer& asGetNode( void ) const;
    void asSetNode( const AsPointer& );

    bool asGetV2Group( void ) const;
    void asSetV2Group( bool );

    // Group rect data is compiled from the items in the group...
    const AsRectF& asCompileGroupData( void );

    bool asCheckHit(  const QPointF & worldPos )override ;

    QPointF asGetRotateCentre( void );

    virtual QString asGetNewObjectName(quint32 nIndex)override ;

    virtual void asTranslateTo(const QPointF&, bool forceDirty = false)override ;
    virtual void asTranslateBy(const QPointF&, bool forceDirty = false)override ;

    void asSetDragStartPosition(const QPointF& point);
    void asReturnToDragStart( bool forceDirty = false );

    QString typeName() override;

public:
    Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:
    void asCopy( const AsRenderableGroup& );

    void asComputeTransform( void );

    static QHash<QString, quint16>& m_lProperties( void );

    AsPointer m_Node;
    bool m_bV2Group;
};

#endif // ASRENDERABLEGROUP_H
