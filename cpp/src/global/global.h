//
// Created by alex on 2019/8/23.
//

#ifndef FLIPCHARTQUICK_GLOBAL_H
#define FLIPCHARTQUICK_GLOBAL_H



#include <math.h>
#include <QtGlobal>

//struct Variant;

namespace Json{
   class Value;
}
enum class VariableType{
     BOOL=0,
     INT=10,
     UINT=11,
     DOUBLE=12,
     Q_POINT_F=13,
     Q_SIZE=14,
     Q_SIZE_F=15,
     Q_RECT=16,
     Q_RECT_F=17,
     Q_STRING=18,
     Q_STRING_LIST=19,
     Q_TIME=20,
     Q_DATE_TIME=21,
     Q_LIST=22,
     Q_BYTE_ARRAY=23,
     Q_COLOR=24,
     Q_IMAGE=25,
     ASPOINTFARRAY=26,
     ASRECTF=27,
     ASPOINTFAARAYARRAY=28,
     ASINSTRUCTLISTLIST=29,
     ASMOULIST=30,
     ASRESOUCREINDEX=31,
     ASTEXTRUNARRAY=32,
     ASPOINTER=33,
     ASUNDORESOURCEINDEX=34,
     ASOPTIONLIST=35,
     ASSTRINGPAIRLIST=36,
     ASFOLDERINDEX=37,
     ASRESOURCEREGISTER=38,
     ASINK=39,
     ASTRANSFORM=40,
     ASORIGIN=41,
     ASLABEL=42,
     ASTEXATCHARFORMAT=43,
     ASVIRTUALFOLDERINDEX=44,
     ASASYNCTESTLEVELLIST=45,


     };
struct Variant{
public:
    Variant(){
        value=Q_NULLPTR;
        type=VariableType::INT;
    }
    Variant(const Variant& rh){
       value = rh.value;
       type = rh.type;
    }
    bool isSimpleType();
    Json::Value&  operator <<(Json::Value& object)const;
    friend  Json::Value& operator <<(Json::Value& object,const Variant& val){
        val << object;
        return object;
    }
    void simpleSerializer(Json::Value& object,const QString& key);
    VariableType type;
    void* value;
};

class Math{
public:
    static double FormatSignificantDigits(const double& val,int32_t numsSignificantDigits = 3){
        double format = static_cast<int64_t >(val*pow(10,numsSignificantDigits))/pow(10,numsSignificantDigits);
        return format;
    }
};
#endif //FLIPCHARTQUICK_GLOBAL_H
