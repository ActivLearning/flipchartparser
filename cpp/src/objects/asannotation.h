 // Defines the AsAnnotation class.
// $Author: Paul Wareing.

#ifndef ASANNOTATION_H
#define ASANNOTATION_H

#include <QPointF>
#include "asrenderable.h"

class AsFactory;
class AsAnnotationRes;

/**
 * Represents an Annotation object in a flipchart
 */
class AsAnnotation : public AsRenderable
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
        AS_PROPERTY_TRANSLUCENCY = 38,
        AS_PROPERTY_DRAGACOPY = 42,
        AS_PROPERTY_QUESTIONTAG = 43,
        AS_PROPERTY_REWARD_SOUND = 44,
        AS_PROPERTY_REWARD_SOUND_LOCATION = 45,
		AS_PROPERTY_ASYNCTESTTAG = 46,
        AS_PROPERTY_INTERACTMODE = 49,

        // From AsAnnotation...
        AS_PROPERTY_RESOURCE = 39,      
        AS_PROPERTY_ENDCAPA = 47,
        AS_PROPERTY_ENDCAPB = 48

        // Next Prop ID = 50
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

    // Construction and destruction
    AsAnnotation( AsFactory * );
    virtual ~AsAnnotation();

    AsAnnotation( const AsAnnotation& );
    void operator= ( const AsAnnotation& );

    bool operator== ( const AsAnnotation& );

    // Operations...
    bool asCheckHit(  const QPointF & worldPos );
    bool asCheckHitByCircle(  const QPointF & worldPos, int width );
    AsPointFArray asGetPoints( void );
    QVector<int>& asGetTimePoints(void);

    // Properties...
    void asResetPropertyIndex( void );

 //   unsigned int asGetResource( void ) const;
    void asSetResource( unsigned int );

    AsResource * asGetResourcePointer( void );
    void asSetResource( AsResource * );

    AsEnumEndCap asGetEndCapA( void ) const;
    void asSetEndCapA( AsEnumEndCap );

    AsEnumEndCap asGetEndCapB( void ) const;
    void asSetEndCapB( AsEnumEndCap );

    void asSetInk( const AsInk& );

    void asAddLocalPoint( QPointF & pnt );

	void asSetForHandwriting( bool forHWR );
        bool asIsForHandwriting( void ) const;

    void asSetNewlyCreated(bool bNewlyCreated);
    bool asGetNewlyCreated() const;

	bool asIsSelectable( void );

    void asSetTranslucency( int translucency );
    int asGetTranslucency( void );

    virtual void asScaleBy(const QPointF& scaleFactor, 
			   const bool maintainAspect = false);
    virtual void asScaleTo( const QPointF& );

    virtual QString asGetNewObjectName(quint32 nIndex);
    const QList<QPointF>  asGetAnchorPoints();

    bool asGetAnnotating( void ) const;
    void asSetAnnotating( bool );

    void asPrepareBoundingRect();

	bool asIsResourcePointerValid( void )override ;

    QString typeName() override;

public:
    Json::Value &serialized() override;
    // const QList<QPainterPath*> & asGetEndCapPainterPathsConstRef( void );
protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

    const Json::Value &asResourceSerialized() override;

private:
    void asCopy( const AsAnnotation& );

    void asBuildEndCapPainterPaths( void );
    void asDeleteEndCapPainterPaths( void );

    static QHash<QString, quint16>& m_lProperties( void );

    unsigned int m_nResource;
    AsAnnotationRes *m_pAsAnnotationRes;
    AsEnumEndCap m_nEndCapA;
    AsEnumEndCap m_nEndCapB;
	bool m_forHandwriting;
    bool m_bNewlyCreated;	
    bool m_bAnnotating;

//    QList<QPainterPath *> m_endCapPainterPaths;
    bool m_bEndCapPainterPathDirty;
};

#endif // ASANNOTATION_H
