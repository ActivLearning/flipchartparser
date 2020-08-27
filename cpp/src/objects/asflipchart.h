#ifndef ASFLIPCHART_H
#define ASFLIPCHART_H

#include <QString>


#include "asobject.h"

class  AsResourceRegister;

class AsFlipchart : public AsObject
{
public:
    AsFlipchart( AsFactory * );
    virtual ~AsFlipchart();

    AsNode *asLoadPageObjects( int nPageNumber );

    void asSetResourceRegister(AsResourceRegister* asResourceRegister);
    AsResourceRegister* asGetResourceRegister();
    const QString& asGetFlipchartWorkingPath( void ) const;
    void asSetFlipchartWorkingPath( QString& );

private:
    QString m_sWorkingPath;
    AsResourceRegister* m_pResRegister;
};


#endif //ASFLIPCHART_H