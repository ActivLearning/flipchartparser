#ifndef ASTEXTRUNARRAY_H
#define ASTEXTRUNARRAY_H

#include <QMetaType>
#include <QList>
#include "../objects/astextrun.h"

class AsTextRunArray : public QList<AsTextRun>
{
public:
    AsTextRunArray();

//        const QByteArray& asToByteArray( void );

private:
//       QByteArray m_Array;
};

Q_DECLARE_METATYPE( AsTextRunArray )

#endif // ASTEXTRUNARRAY_H
