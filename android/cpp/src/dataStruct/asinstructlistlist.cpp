// Implements the AsInstructList Class
// $Author: Mark Roberts



#include "asinstructlistlist.h"


void AsInstructListList::asUpdateControlVars(const QSizeF& size)
{
     for(int i=0;i<count();i++)
     {
         operator[](i).asUpdateControlVar(size);
     }
}


