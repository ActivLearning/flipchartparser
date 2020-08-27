// Defines the AsPathInstruct Class
// $Author: Mark Roberts

#ifndef ASPATHINSTRUCTS_H
#define ASPATHINSTRUCTS_H

#include <QRectF>
#include <QString>
#include <QStringList>




struct AsArcInfo
{
    QRectF bounds;
    double startAngle;
    double numDegrees;
};



class AsPathInstruct
{
public:
    enum AsEnumInstructType
    {
        AS_INSTRUCT_TYPE_NONE,
        AS_INSTRUCT_TYPE_MOVE,
        AS_INSTRUCT_TYPE_LINE,
        AS_INSTRUCT_TYPE_ARC,
        AS_INSTRUCT_TYPE_CUBIC,
        AS_INSTRUCT_TYPE_QUAD,
        AS_INSTRUCT_TYPE_CLOSE_PATH
    };

    enum AsEnumMutatorType
    {
        AS_MUTATOR_TYPE_NONE,
        AS_MUTATOR_TYPE_LEFT,
        AS_MUTATOR_TYPE_RIGHT,
        AS_MUTATOR_TYPE_TOP,
        AS_MUTATOR_TYPE_BOTTOM,
        AS_MUTATOR_TYPE_CENTER,
        AS_MUTATOR_TYPE_RADIUS
    };
public:


    AsPathInstruct(const QPointF &point , AsEnumInstructType type);
    AsPathInstruct();
    AsPathInstruct(const QString &instructStr, AsEnumInstructType type);

    ~AsPathInstruct(){};

    bool operator==(const AsPathInstruct& other);

    AsPathInstruct::AsEnumInstructType asGetType()const;;


    void asModifyMutators(const QSizeF& size,const QList<AsPathInstruct>& instructs);

    void asSetControlVar(double val, int index)
    {
        if(index == m_xControlVarIndex)
            m_xControlVar = val;

        if(index == m_yControlVarIndex)
            m_yControlVar = val;
    };

    void asSetXControlVarIndex(int index);
   
    void asSetYControlVarIndex(int index);
   
    void asSetXMutator( const float multiplier,const AsEnumMutatorType type, int affectorIndex )
    {
        m_xAffectorIndex = affectorIndex;
        m_xMutatorMult = multiplier;
        m_xMutatorType = type;
    };

    void asSetXRadiusMutator( const float multiplier,const AsEnumMutatorType type)
    {
        m_xRadiusMult = multiplier;
        m_xRadiusMutatorType = type;
    };

    void asSetYRadiusMutator( const float multiplier,const AsEnumMutatorType type )
    {
        m_yRadiusMult = multiplier;
        m_yRadiusMutatorType = type;
    };

    void asSetYMutator( const float multiplier, const AsEnumMutatorType type, int affectorIndex  )
    {
        m_yAffectorIndex = affectorIndex;
        m_yMutatorMult = multiplier;
        m_yMutatorType = type;
    };

    const QPointF asGetEndPoint()const {return m_endPoint;};
    void asSetEndPoint(const QPointF endPoint) {m_endPoint = endPoint;};


    AsArcInfo asGetArcParams(double xMult,double yMult,const  QPointF& pos);

    AsEnumInstructType m_type;

    double m_xRadius;
    double m_yRadius;

    bool   m_bClockwise;
    bool   m_bLargeArc;

    double m_xControlVar;
    double m_yControlVar;

    double m_xMutatorMult;
    double m_yMutatorMult;

    double m_xRadiusMult;
    double m_yRadiusMult;

    int m_xAffectorIndex;
    int m_yAffectorIndex;

    int m_xControlVarIndex;
    int m_yControlVarIndex;

    AsEnumMutatorType m_xMutatorType;
    AsEnumMutatorType m_yMutatorType;

    AsEnumMutatorType m_xRadiusMutatorType;
    AsEnumMutatorType m_yRadiusMutatorType;

    QPointF m_endPoint;
};







#endif


