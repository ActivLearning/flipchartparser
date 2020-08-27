// Implements the AsPathInstruct Class
// $Author: Mark Roberts


#include "aspathinstructs.h"

AsPathInstruct::AsPathInstruct(const QPointF &point , AsEnumInstructType type)
{
    m_xRadius = 0;
    m_yRadius = 0;

    m_bClockwise = false;
    m_bLargeArc = false;

    m_type = type;
    m_endPoint = point;

    m_xControlVar = 1;
    m_yControlVar = 1 ;

    m_xMutatorMult = 1;
    m_yMutatorMult = 1;

    m_xRadiusMult = 1;
    m_yRadiusMult =1 ;

    m_xAffectorIndex = -1;
    m_yAffectorIndex = -1;

    m_xControlVarIndex = -1;
    m_yControlVarIndex = -1;

    m_xRadiusMutatorType = AS_MUTATOR_TYPE_NONE;
    m_yRadiusMutatorType = AS_MUTATOR_TYPE_NONE;

    m_xMutatorType = AS_MUTATOR_TYPE_NONE;
    m_yMutatorType = AS_MUTATOR_TYPE_NONE;
}

AsPathInstruct::AsPathInstruct()
{
    m_xRadius = 0;
    m_yRadius = 0;

    m_bClockwise = false;
    m_bLargeArc = false;

    m_xControlVar = 1;
    m_yControlVar = 1 ;

    m_xMutatorMult = 1;
    m_yMutatorMult = 1;

    m_xRadiusMult = 1;
    m_yRadiusMult =1 ;

    m_xAffectorIndex = -1;
    m_yAffectorIndex = -1;

    m_xControlVarIndex = -1;
    m_yControlVarIndex = -1;

    m_xRadiusMutatorType = AS_MUTATOR_TYPE_NONE;
    m_yRadiusMutatorType = AS_MUTATOR_TYPE_NONE;

    m_xMutatorType = AS_MUTATOR_TYPE_NONE;
    m_yMutatorType = AS_MUTATOR_TYPE_NONE;
}



AsPathInstruct::AsPathInstruct(const QString &instructStr, AsEnumInstructType type)
{
    m_xRadius = 0;
    m_yRadius = 0;
    m_bClockwise = false;
    m_bLargeArc = false;
    m_type = type;

    m_xControlVar = 1;
    m_yControlVar = 1 ;

    m_xMutatorMult = 1;
    m_yMutatorMult = 1;

    m_xRadiusMult = 1;
    m_yRadiusMult =1 ;

    m_xAffectorIndex = -1;
    m_yAffectorIndex = -1;

    m_xControlVarIndex = -1;
    m_yControlVarIndex = -1;

    m_xRadiusMutatorType = AS_MUTATOR_TYPE_NONE;
    m_yRadiusMutatorType = AS_MUTATOR_TYPE_NONE;

    m_xMutatorType = AS_MUTATOR_TYPE_NONE;
    m_yMutatorType = AS_MUTATOR_TYPE_NONE;

    QStringList params = instructStr.split(" ",QString::SkipEmptyParts);


    switch(type)
    {
    case AS_INSTRUCT_TYPE_MOVE:
        {
            Q_ASSERT(params.count() == 2);
            m_endPoint = QPointF(params.at(0).toDouble(), params.at(1).toDouble());
        }
        break;

    case AS_INSTRUCT_TYPE_LINE:
        {
            Q_ASSERT(params.count() == 2);
            m_endPoint = QPointF(params.at(0).toDouble(), params.at(1).toDouble());
        }
        break;

    case AS_INSTRUCT_TYPE_ARC:
        {
            Q_ASSERT(params.count() == 7);

            m_xRadius = params.at(0).toDouble();
            m_yRadius = params.at(1).toDouble();
            m_bLargeArc = params.at(3).toInt();
            m_bClockwise = params.at(4).toInt();
            m_endPoint = QPointF( params.at(5).toDouble(), params.at(6).toDouble());
        }
        break;

    case AS_INSTRUCT_TYPE_CUBIC:
        {
        }
        break;

    case AS_INSTRUCT_TYPE_QUAD:
        {
        }
        break;

    case AS_INSTRUCT_TYPE_CLOSE_PATH:
        {
        }
        break;

    default:
        break;
    }
}



void AsPathInstruct::asSetXControlVarIndex(int index)
{
    Q_ASSERT(index >= 0);
    m_xControlVarIndex = index;
}


void AsPathInstruct::asSetYControlVarIndex(int index)
{
    Q_ASSERT(index >= 0);
    m_yControlVarIndex = index;
}


bool AsPathInstruct::operator==(const AsPathInstruct& other)
{
    if(other.m_type != m_type ||
        other.m_xRadius != m_xRadius ||
        other.m_yRadius != m_yRadius ||
        other.m_bClockwise != m_bClockwise ||
        other.m_bLargeArc != m_bLargeArc ||
        other.m_endPoint != m_endPoint ||
        other.m_xControlVar != m_xControlVar ||
        other.m_yControlVar != m_yControlVar ||
        other.m_xMutatorMult != m_xMutatorMult ||
        other.m_yMutatorMult != m_yMutatorMult ||
        other.m_xRadiusMult != m_xRadiusMult ||
        other.m_yRadiusMult != m_yRadiusMult ||
        other.m_xAffectorIndex != m_xAffectorIndex ||
        other.m_yAffectorIndex != m_yAffectorIndex ||
        other.m_xControlVarIndex != m_xControlVarIndex ||
        other.m_yControlVarIndex != m_yControlVarIndex ||
        other.m_xRadiusMutatorType != m_xRadiusMutatorType ||
        other.m_yRadiusMutatorType != m_yRadiusMutatorType ||
        other.m_xMutatorType != m_xMutatorType ||
        other.m_yMutatorType != m_yMutatorType)
    {
        return false;
    }
    return true;
}





AsArcInfo AsPathInstruct::asGetArcParams(double xMult,double yMult,const  QPointF& pos)
{
    QPointF startPoint = pos;

    QPointF endPoint(m_endPoint.x() * xMult, m_endPoint.y() * yMult);
    QPointF diff = endPoint-startPoint;

    double startAngle, numDegrees,top,left;

    if(diff.x() < 0 && diff.y() <0)
    {
        if(m_bLargeArc)
        {
            if(m_bClockwise)
            {
                startAngle = 0;
                numDegrees = -270;
                left = endPoint.x() + diff.x();
                top =  endPoint.y();
            }
            else
            {
                startAngle = -90;
                numDegrees = 270;
                left = endPoint.x();
                top =  endPoint.y()+diff.y();
                
            }
        }
        else
        {
            if(m_bClockwise)
            {
                startAngle = -90;
                numDegrees = -90;
                left = endPoint.x();
                top =  endPoint.y()+diff.y();
            }
            else
            {
                startAngle = 0;
                numDegrees = 90;
                left = endPoint.x() + diff.x();
                top =  endPoint.y();
            }
        }
    }
    else if(diff.x() < 0 && diff.y() > 0)
    {
        if(m_bLargeArc)
        {
            if(m_bClockwise)
            {
                startAngle = 90;
                numDegrees = -270;
                left = endPoint.x();
                top =  startPoint.y();
            }
            else
            {
                startAngle = 0;
                numDegrees = 270;
                left = endPoint.x() + diff.x();
                top =  startPoint.y() - diff.y();                           
            }
        }
        else
        {
            if(m_bClockwise)
            {
                startAngle = 0;
                numDegrees = -90;
                left = endPoint.x() + diff.x();
                top =  startPoint.y() - diff.y();  
            }
            else
            {
                startAngle = 90;
                numDegrees = 90;
                left = endPoint.x();
                top =  startPoint.y();
            }
        }
    }
    else if(diff.x() > 0 && diff.y() <0)
    {
        if(m_bLargeArc)
        {
            if(m_bClockwise)
            {
                startAngle = -90;
                numDegrees = -270;
                left = startPoint.x() - diff.x();
                top =  endPoint.y() + diff.y();        
            }
            else
            {
                startAngle = 180;
                numDegrees = 270;
                left = startPoint.x();
                top =  endPoint.y();                         
            }
        }
        else
        {
            if(m_bClockwise)
            {
                startAngle = 180;
                numDegrees = -90;
                left = startPoint.x();
                top =  endPoint.y();        
            }
            else
            {
                startAngle = -90;
                numDegrees = 90;
                left = startPoint.x() - diff.x();
                top =  endPoint.y() + diff.y();        
            }
        }
    }
    else  //both positive
    {
        if(m_bLargeArc)
        {
            if(m_bClockwise)
            {
                startAngle = 180;
                numDegrees = -270;
                left = startPoint.x();
                top =  startPoint.y() - diff.y();
            }
            else
            {
                startAngle = -90;
                numDegrees = -270;
                left = startPoint.x() - diff.x();
                top =  startPoint.y();                           
            }
        }  
        else
        {
            if(m_bClockwise)
            {
                startAngle = 90;
                numDegrees = -90;
                left = startPoint.x() - diff.x();
                top =  startPoint.y();         
            }
            else
            {
                startAngle = 180;
                numDegrees = 90;
                left = startPoint.x();
                top =  startPoint.y() - diff.y();
            }
        }
    }

    AsArcInfo info;
    info.bounds = QRectF(left, top, m_xRadius * xMult * 2.0, m_yRadius * yMult * 2.0);
    info.startAngle = startAngle;
    info.numDegrees = numDegrees;
    return info;
}




void AsPathInstruct::asModifyMutators(const QSizeF& size, const QList<AsPathInstruct>& instructs)
{
    double normalizer;
    double width = qAbs(size.width());
    double height = qAbs(size.height());
    
    //smaller than this may lead to rounding issues....
    if(width>1 && height>1 )    
    {
        normalizer = m_xControlVar/width;

        switch (m_xMutatorType)
        {
        case AS_MUTATOR_TYPE_LEFT:
            
            if(m_xAffectorIndex != -1)
            {
                m_endPoint.setX(normalizer * m_xMutatorMult + instructs[m_xAffectorIndex].asGetEndPoint().x() ); 
            }
            else
            {
                m_endPoint.setX(normalizer * m_xMutatorMult);
            }
            break;

        case AS_MUTATOR_TYPE_RIGHT:
            if(m_xAffectorIndex != -1)
            {
                m_endPoint.setX(instructs[m_xAffectorIndex].asGetEndPoint().x() - (normalizer * m_xMutatorMult));
            }
            else
            {
                m_endPoint.setX(1 - (normalizer * m_xMutatorMult));
            }
            break;

        case AS_MUTATOR_TYPE_CENTER:
            m_endPoint.setX(0.5 - (normalizer * m_xMutatorMult));
            break;
           
        default:
            break;
        }

        normalizer = m_yControlVar/height;

        switch (m_yMutatorType)
        {
        case AS_MUTATOR_TYPE_TOP:
            
            if(m_yAffectorIndex != -1)
            {
                m_endPoint.setY(normalizer * m_yMutatorMult + instructs[m_yAffectorIndex].asGetEndPoint().y() ); 
            }
            else
            {
                m_endPoint.setY(normalizer * m_yMutatorMult);
            }
            
            break;

        case AS_MUTATOR_TYPE_BOTTOM:
            if(m_yAffectorIndex != -1)
            {
                m_endPoint.setY(instructs[m_yAffectorIndex].asGetEndPoint().y()  - (normalizer * m_yMutatorMult));
            }
            else
            {
                m_endPoint.setY(1 - (normalizer * m_yMutatorMult));
            }
            
            break;

        case AS_MUTATOR_TYPE_CENTER:
            m_endPoint.setY(0.5 - (normalizer * m_yMutatorMult));
            break;

        default:
            break;
        }

        
        if(m_xRadiusMutatorType == AS_MUTATOR_TYPE_RADIUS)
        {
            normalizer = m_xControlVar/width;
            m_xRadius  = normalizer * m_xRadiusMult;
        }

        if(m_yRadiusMutatorType == AS_MUTATOR_TYPE_RADIUS)
        {
            normalizer = m_yControlVar/height;
            m_yRadius  = normalizer * m_yRadiusMult;
        }
    }
}

AsPathInstruct::AsEnumInstructType AsPathInstruct::asGetType() const
{
    return m_type;
}
