// Defines the AsShape class.
// $Author: Paul Wareing.

#ifndef ASSHAPE_H
#define ASSHAPE_H

#include "asrenderable.h"
#include "../resources/asshaperes.h"
#include "../dataStruct/asinstructlistlist.h"


class AsFactory;

/**
 * Represents a Shape object in a flipchart
 */
class AsShape : public AsRenderable
{
Q_PROPERTY( unsigned int asResource READ asGetResource WRITE asSetResource )
Q_PROPERTY( AsEnumFillMode asFillMode READ asGetFillMode WRITE asSetFillMode EDITABLE true )
Q_PROPERTY( bool asIntelligent READ asIsIntelligent WRITE asSetIsIntelligent )
Q_PROPERTY( bool asIsOpen READ asIsOpen WRITE asSetIsOpen )
Q_PROPERTY( bool asIsConnector READ asIsConnector WRITE asSetIsConnector )

Q_PROPERTY( int asNumShapePoints  READ asGetNumPoints WRITE asSetNumPoints )

Q_PROPERTY( double asInnerDiam READ asGetInnerDiam WRITE asSetInnerDiam )
Q_PROPERTY( AsInstructListList asShapeInstructs READ asGetInstructs WRITE asSetInstructs )

Q_PROPERTY( bool asIsStar READ asGetIsStar WRITE asSetIsStar )
Q_PROPERTY( AsEnumShapeType asShapetype READ asGetShapeType WRITE asSetShapeType )
Q_PROPERTY( AsPointFArray asLocalPoints READ asGetLocalPoints WRITE asSetLocalPoints )

Q_PROPERTY( AsPointer asEndA READ asGetEndA WRITE asSetEndA)
Q_PROPERTY( AsPointer asEndB READ asGetEndB WRITE asSetEndB)

Q_PROPERTY( QPointF asEndAPos READ asGetEndAPos WRITE asSetEndAPos )
Q_PROPERTY( QPointF asEndBPos READ asGetEndBPos WRITE asSetEndBPos )

Q_PROPERTY( int asEndAIndex READ asGetEndAIndex WRITE asSetEndAIndex )
Q_PROPERTY( int asEndBIndex READ asGetEndBIndex WRITE asSetEndBIndex )

Q_PROPERTY( QPointF asEndAShapeCenterDiff READ asGetEndAShapeCenterDiff WRITE asSetEndAShapeCenterDiff )
Q_PROPERTY( QPointF asEndBShapeCenterDiff READ asGetEndBShapeCenterDiff WRITE asSetEndBShapeCenterDiff )

Q_PROPERTY( AsEnumEndCap asEndCapA READ asGetEndCapA WRITE asSetEndCapA EDITABLE true )
Q_PROPERTY( AsEnumEndCap asEndCapB READ asGetEndCapB WRITE asSetEndCapB EDITABLE true )

Q_ENUMS( AsEnumEndCap )
Q_ENUMS( AsEnumShapeType )
Q_ENUMS( AsEnumFillMode )

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
        AS_PROPERTY_DRAGACOPY = 40,
        AS_PROPERTY_QUESTIONTAG = 55,
        AS_PROPERTY_REWARD_SOUND = 59,
        AS_PROPERTY_REWARD_SOUND_LOCATION = 60,
        AS_PROPERTY_ASYNCTESTTAG = 63,
        AS_PROPERTY_INTERACTMODE = 64,


        // From AsShape...
        AS_PROPERTY_RESOURCE = 38,
        AS_PROPERTY_FILLMODE = 39,
        AS_PROPERTY_INTELLIGENT = 41,
        AS_PROPERTY_OPEN = 42,
        AS_PROPERTY_NUM_POINTS = 43,
        AS_PROPERTY_INNER_DIAM = 44,
        AS_PROPERTY_IS_STAR = 45,
        AS_PROPERTY_FILE_AND_PATH = 46,
        AS_PROPERTY_SHAPE_TYPE = 47,
        AS_PROPERTY_SHAPE_INSTRUCTS = 48,
        AS_PROPERTY_LOCAL_POINTS = 49,
        AS_PROPERTY_ENDA = 50,
        AS_PROPERTY_ENDB = 51,
        AS_PROPERTY_ENDA_INDEX = 52,
        AS_PROPERTY_ENDB_INDEX = 53,
        AS_PROPERTY_IS_CONNECTOR = 54,
        AS_PROPERTY_ENDA_POS = 57,
        AS_PROPERTY_ENDB_POS = 58,
        AS_PROPERTY_IS_ENDCAPA	= 61,
        AS_PROPERTY_IS_ENDCAPB = 62,
        AS_PROPERTY_ENDA_SHAPE_CENTER_DIFF = 65,
        AS_PROPERTY_ENDB_SHAPE_CENTER_DIFF = 66
        // Next Property ID = 67
    };

    enum AsEnumFillMode
    {
        AS_FILLMODE_NONE = 0,
        AS_FILLMODE_ALTERNATE,
        AS_FILLMODE_WINDING
    };

    enum AsEnumShapeType
    {
        AS_SHAPE_TYPE_DUMB,
        AS_SHAPE_TYPE_FREEFORM,
        AS_SHAPE_TYPE_LINE_CHAIN,
        AS_SHAPE_TYPE_CURVE_CHAIN,
        AS_SHAPE_TYPE_COMPUTED,
        AS_SHAPE_TYPE_SCRIPTED
    };

    enum AsEnumShapeCreationMethod
    {
        AS_SHAPE_CREATION_NONE,
        AS_SHAPE_CREATION_NORMAL,
        AS_SHAPE_CREATION_HORIZONTAL_ONLY,
        AS_SHAPE_CREATION_VERTICAL_ONLY,
        AS_SHAPE_CREATION_UNIFORM
    };

    enum AsEnumEndCap
    {
        AS_ENDCAP_NONE = 0,
        AS_ENDCAP_RADIUS,
        AS_ENDCAP_ARROW
    };


    struct AsIntelligentShapeParms
    {
        AsShape::AsEnumShapeType type;
        AsShape::AsEnumShapeCreationMethod shapeCreationMethod;
        int   numPoints;
        float innerDiam;
        bool  isStar;
        QString sFileAndPath;
        bool  isConnector;
        int   displayPriority;
        AsShape::AsEnumEndCap endACap;
        AsShape::AsEnumEndCap endBCap;
        AsInk::AsEnumPenStyle m_penStyle;

        bool operator==(AsIntelligentShapeParms other)
        {
            if(other.type != type ||
               other.numPoints != numPoints ||
               other.innerDiam != innerDiam ||
               other.isStar != isStar ||
               other.sFileAndPath != sFileAndPath ||
               other.shapeCreationMethod != shapeCreationMethod ||
               other.isConnector != isConnector  ||
               other.displayPriority != displayPriority ||
               other.endACap != endACap ||
               other.endBCap != endBCap ||
               other.m_penStyle )
            {
                return false;
            }
            return true;
        }
    };

    // Construction and destruction
    AsShape( AsFactory * );
    virtual ~AsShape();

    AsShape( const AsShape& );
    void operator= ( const AsShape& );

    bool operator== ( const AsShape& );

    // Operations
    bool asCheckHit(  const QPointF & worldPos )override ;


    //! Returns the shapes points as separate arrays (note, asGetPoints() concatonates into a single array).
    const AsPointFArrayArray& asGetShapePoints( void );

    // Properties
    void asResetPropertyIndex( void );


    void asSetResource( unsigned int );

    bool asHasResourcePointer() const;
    AsResource * asGetResourcePointer( void )override ;
    void asSetResource( AsResource * )override ;

    AsEnumFillMode asGetFillMode( void ) const;
    void asSetFillMode( AsEnumFillMode );



    // AsRenderable override to ensure bounding rect is calculated before AsCamera dirty rect queries
    void asPrepareBoundingRect() override ;

    bool asCachedGetLastHitWasOnEdge() const;


    /////////////////////////////////////////////
    //Intelligence Streaming..........
    bool asIsIntelligent() const;
    void asSetIsIntelligent( bool intelligent );

    bool asIsOpen() const;
    void asSetIsOpen(bool bOpen);

    const AsInstructListList& asGetInstructs()const;
    void asSetInstructs(const AsInstructListList& instructs);



    AsEnumShapeType asGetShapeType() const;
    void asSetShapeType(const AsEnumShapeType type);

    int asGetNumPoints() const;
    void asSetNumPoints(const int numPoints);

    double asGetInnerDiam() const;
    void asSetInnerDiam(const double diam);

    bool asGetIsStar() const;
    void asSetIsStar(const bool star);

    bool asIsConnector() const;
    void asSetIsConnector(const bool isConn);

    bool asIsLine() const;
    bool asIsVerticalLine() const;
    bool asIsHorizontalLine() const;

    const AsPointer& asGetEndA( void ) const;
    void asSetEndA( AsPointer& );

    const AsPointer& asGetEndB( void ) const;
    void asSetEndB( AsPointer& );

    const QPointF &asGetEndAPos( void ) const;
    void asSetEndAPos( const QPointF& );

    const QPointF &asGetEndBPos( void ) const;
    void asSetEndBPos( const QPointF& );

    void asSetEndAIndex( int index );
    int asGetEndAIndex( void ) const;

    void asSetEndBIndex( int index );
    int asGetEndBIndex( void ) const;

    void asSetEndAShapeCenterDiff( QPointF diff );
    const QPointF& asGetEndAShapeCenterDiff( void ) const;

    void asSetEndBShapeCenterDiff( QPointF diff );
    const QPointF& asGetEndBShapeCenterDiff( void ) const;

    AsEnumEndCap asGetEndCapA( void ) const;
    void asSetEndCapA( AsEnumEndCap );

    AsEnumEndCap asGetEndCapB( void ) const;
    void asSetEndCapB( AsEnumEndCap );

    //Intelligence interface functions.......
    void asBuildIntelligentShape( const AsShape::AsIntelligentShapeParms& parms);

    void asSetCurrentPointerPos(QPointF t, bool noSnap = false);

    bool asClickAt(QPointF t);

    void asCreationComplete(QPointF t);


    void asAddChainPoint(QPointF thePoint);



    //shape editing.....

    void asShapeEditComplete();





    bool asHaveControls()const;




    AsEnumShapeCreationMethod asGetCreationMethod()const;



    void asSetDrawing( bool bDrawing);


    QString typeName() override;

private:
    void asDeletePainterPaths();
    void asStartChainShape();

    void asCreatePathElems(int numPoints, double innerDiam,bool isStar);

    QChar asGetNextInstruct (QString& str);
    QString asGetInstructStr(QString& str);



    bool asHasMovementDirectionChanged(QPointF curPoint , QPointF prevPoint, QPointF controlPoint, int tolerance);

    void asShapePointEditMove( QPointF, int, bool bUpdate );

    void asCopy( const AsShape& );
    void asConvertToDumbShape();

    bool asSetInitialIndexOrDiff( QPointF&, AsRenderable*, bool );
    void asConvertCenterFractionToDiff( QPointF&, AsRenderable* );

public slots:
    void asShapeResChanged( AsShapeRes * );
    void asShapePointEditMove( QPointF, int );

public:
    Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

    const Json::Value &asResourceSerialized() override;

private:
    static QHash<QString, quint16>& m_lProperties( void );

    unsigned int m_nResource;
    AsShapeRes *m_pAsShapeRes;
    AsEnumFillMode m_nFillMode;


    void asBuildPainterPaths( void );
    bool m_bPainterPathDirty;

    // Used by asCheckHit to indecate that the last good hit was on the edge no inside the shape.
    bool m_cachedLastHitWasOnEdge;

//=======================================================
    bool m_bIntelligent;
    bool m_bIsOpen;

    AsPointer m_endA;
    AsPointer m_endB;

    int m_endAIndex;
    int m_endBIndex;

    QPointF m_endAShapeCenterDiff;
    QPointF m_endBShapeCenterDiff;

    QPointF m_endAPos;
    QPointF m_endBPos;

    AsEnumShapeType m_shapeType;

    int   m_numPoints;
    double m_innerDiam;
    bool  m_bIsStar;

    AsInstructListList m_instructLists;



    AsEnumShapeCreationMethod m_shapeUniformity;

    bool m_bIsConnector;
    bool m_bIsTargettedForConn;

    AsEnumEndCap m_nEndCapA;
    AsEnumEndCap m_nEndCapB;

    AsInk m_Ink;
    bool m_bDrawing;
    bool m_bCheckInitialPosIsAnchorPoint;


    AsInk::AsEnumPenJoinStyle asGetEndCapJoinStyle();
    QString& inkPropertyName(AsInk::AsEnumProperty asEnumProperty);
};




#endif // ASSHAPE_H
