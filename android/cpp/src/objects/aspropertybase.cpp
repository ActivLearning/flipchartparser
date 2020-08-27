//
// Created by alex on 2019/10/28.
//

#include "aspropertybase.h"
#include "../dataStruct/aspointfarray.h"
#include "../dataStruct/asrectf.h"
#include "asundoresourceindex.h"
#include "../dataStruct/asoptionlist.h"
#include "../dataStruct/asstringpairlist.h"
#include "../io/asasynctestlevellist.h"
#include "../resources/asresourceregister.h"
#include "asvirtualfolderindex.h"

AsPropertyBase::~AsPropertyBase(){
    auto iterator = m_properties.begin();
    while(iterator!=m_properties.end()) {
        void *value = iterator.value().value;
        VariableType type =iterator.value().type;
        switch (type) {
        case VariableType::BOOL:
            delete static_cast<bool *>(value);
            break;
        case VariableType::INT:
            delete static_cast<int *>(value);
            break;
        case VariableType::UINT:
            delete static_cast<uint32_t *>(value);
            break;
        case VariableType::DOUBLE:
            delete static_cast<double *>(value);
            break;
        case VariableType::Q_POINT_F:
            delete static_cast<QPointF *>(value);
            break;
        case VariableType::Q_SIZE:
            delete static_cast<QSize *>(value);
            break;
        case VariableType::Q_SIZE_F:
            delete static_cast<QSizeF *>(value);
            break;
        case VariableType::Q_RECT:
            delete static_cast<QRect *>(value);
            break;
        case VariableType::Q_RECT_F:
            delete static_cast<QRectF *>(value);
            break;
        case VariableType::Q_STRING:
            delete static_cast<QString *>(value);
            break;
        case VariableType::Q_STRING_LIST:
            delete static_cast<QStringList *>(value);
            break;
        case VariableType::Q_TIME:
            delete static_cast<QTime *>(value);
            break;
        case VariableType::Q_DATE_TIME:
            delete static_cast<QDateTime *>(value);
            break;
        case VariableType::Q_LIST:
            delete static_cast<QList<Variant> *>(value);
            break;
        case VariableType::Q_BYTE_ARRAY:
            delete static_cast<QByteArray *>(value);
            break;
        case VariableType::Q_COLOR:
            delete static_cast<QColor *>(value);
            break;
        case VariableType::Q_IMAGE:
            break;
        case VariableType::ASPOINTFARRAY:
            delete static_cast<AsPointFArray *>(value);
            break;
        case VariableType::ASRECTF:
            delete static_cast<AsRectF *>(value);
            break;
        case VariableType::ASPOINTFAARAYARRAY:
            delete static_cast<AsPointFArrayArray *>(value);
            break;
        case VariableType::ASINSTRUCTLISTLIST:
            delete static_cast<AsInstructListList *>(value);
            break;
        case VariableType::ASMOULIST:
            //  delete static_cast<AsMOUList*>(value);
            break;
        case VariableType::ASRESOUCREINDEX:
             delete static_cast<AsResourceIndex*>(value);
            break;
        case VariableType::ASTEXTRUNARRAY:
            delete static_cast<AsTextRunArray *>(value);
            break;
        case VariableType::ASPOINTER:
            delete static_cast<AsPointer *>(value);
            break;
        case VariableType::ASUNDORESOURCEINDEX:
            delete static_cast<AsUndoResourceIndex*>(value);
            break;
        case VariableType::ASOPTIONLIST:
            delete static_cast<AsOptionList*>(value);
            break;
        case VariableType::ASSTRINGPAIRLIST:
            delete static_cast<AsStringPairList*>(value);
            break;
        case VariableType::ASFOLDERINDEX:
            delete static_cast<AsFolderIndex*>(value);
            break;
        case VariableType::ASRESOURCEREGISTER:
            delete static_cast<AsResourceRegister*>(value);
            break;
        case VariableType::ASINK:
            delete static_cast<AsInk *>(value);
            break;
        case VariableType::ASTRANSFORM:
            delete static_cast<AsTransform *>(value);
            break;
        case VariableType::ASORIGIN:
            delete static_cast<AsOrigin *>(value);
            break;
        case VariableType::ASLABEL:
            //  delete static_cast<AsLabel*>(value);
            break;
        case VariableType::ASTEXATCHARFORMAT:
            //   delete static_cast<AsTextCharFormat*>(value);
            break;
        case VariableType::ASVIRTUALFOLDERINDEX:
          //   delete static_cast<AsVirtualFolderIndex*>(value);
            break;
        case VariableType::ASASYNCTESTLEVELLIST:
            delete static_cast<AsAsyncTestLevelList*>(value);
            break;
        default:

            break;
        }
        iterator++;
    }
};