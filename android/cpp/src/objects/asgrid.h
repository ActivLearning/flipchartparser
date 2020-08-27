// Defines the AsGrid class.
// $Author: Paul Wareing.

#ifndef ASGRID_H
#define ASGRID_H

#include "asrenderable.h"

class AsFactory;

/**
 * Represents a Grid object in a flipchart
 */
class AsGrid : public AsRenderable
{
Q_PROPERTY( double asThumbNailScale READ asGetThumbNailScale WRITE asSetThumbNailScale EDITABLE true )
Q_PROPERTY( double asDefaultScale READ asGetDefaultScale WRITE asSetDefaultScale EDITABLE true )
Q_PROPERTY( double asScaleStep READ asGetScaleStep WRITE asSetScaleStep EDITABLE true )
Q_PROPERTY( bool asAllowSnap READ asGetAllowSnap WRITE asSetAllowSnap EDITABLE true )
Q_PROPERTY( bool asOnTop READ asGetOnTop WRITE asSetOnTop EDITABLE true )
Q_PROPERTY( bool asLevelEditor READ asGetLevelEditor WRITE asSetLevelEditor EDITABLE true )

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

        // From AsGrid...
        AS_PROPERTY_THUMBNAILSCALE,
        AS_PROPERTY_DEFAULTSCALE,
        AS_PROPERTY_SCALESTEP,
        AS_PROPERTY_ALLOWSNAP,
        AS_PROPERTY_ONTOP,
        AS_PROPERTY_LEVELEDITOR
    };

    // Construction and destruction
    AsGrid( AsFactory * );
    virtual ~AsGrid();

    AsGrid( const AsGrid& );
    void operator= ( const AsGrid& );

    bool asCheckHit(  const QPointF & worldPos )override ;

    // Properties
    void asResetPropertyIndex( void );

    double asGetThumbNailScale( void ) const;
    void asSetThumbNailScale( double );

    double asGetDefaultScale( void ) const;
    void asSetDefaultScale( double );

    double asGetScaleStep( void ) const;
    void asSetScaleStep( double );

    bool asGetAllowSnap( void ) const;
    void asSetAllowSnap( bool );

    bool asGetOnTop() const;
    void asSetOnTop(bool);

    bool asGetLevelEditor() const;
    void asSetLevelEditor(bool bLevelEditor);

    QPointF asGetNearestPoint( AsNode *, const QPointF& );

    bool asIsSelectable( void )override ;

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;



private:
    void asCopy( const AsGrid& );

    static QHash<QString, quint16>& m_lProperties( void );

    double m_dThumbNailScale;
    double m_dDefaultScale;
    double m_dScaleStep;
    bool m_bAllowSnap;
    bool m_bOnTop;
    bool m_bLevelEditor;
};

#endif // ASGRID_H
