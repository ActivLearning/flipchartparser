//
// Created by Goblin on 2019-09-05.
//

#ifndef FLIPCHARTQUICK_QCOLOR_H
#define FLIPCHARTQUICK_QCOLOR_H

#include <QtGlobal>
class QColor {
public:
    QColor(Qt::GlobalColor color){

    }
    QColor(){

    }
    int a;
    int r;
    int g;
    int b;


    inline void setAlpha(int alpha)
    {
        a = alpha;
    }
};

#endif //FLIPCHARTQUICK_QCOLOR_H
