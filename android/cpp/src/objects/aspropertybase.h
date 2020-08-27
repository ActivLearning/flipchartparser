//
// Created by alex on 2019/8/23.
//

#ifndef FLIPCHARTQUICK_ASPROPERTYBASE_H
#define FLIPCHARTQUICK_ASPROPERTYBASE_H

#include <QMap>
#include "../global/global.h"

class AsPropertyBase{
public:
    AsPropertyBase(){};

    virtual ~AsPropertyBase();
public:
    virtual void setProperty(int id,Variant property)=0;
    virtual Variant property(int id)=0;
    QMap<int,Variant> m_properties;
};
#endif //FLIPCHARTQUICK_ASPROPERTYBASE_H
