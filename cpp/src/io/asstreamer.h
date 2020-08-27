// Defintion of the AsStreamer class.
// $Author: Paul Wareing

#ifndef ASSTREAMER_H
#define ASSTREAMER_H

#include <QHash>
#include <QObject>

/**
 * Base class for streamers
 */
class AsStreamer
{
public:
    AsStreamer();
    virtual ~AsStreamer();

protected:
    //! Enumeration for each non-Qt type that we might want to stream
    enum AsEnumRegisteredType
    {
        //! AsPointFArray
        AS_REGISTEREDTYPE_ASPOINTFARRAYT = 1,
        //! AsPointFArrayArray
        AS_REGISTEREDTYPE_ASPOINTFARRAYARRAYT,
        //! AsResourceIndex
        AS_REGISTEREDTYPE_ASRESOURCEINDEXT,
        //! AsResourceRegister
        AS_REGISTEREDTYPE_ASRESOURCEREGISTERT,
        //! AsRectF
        AS_REGISTEREDTYPE_ASRECTF,
        //! AsInk
        AS_REGISTEREDTYPE_ASINKT,
        //! AsTransform
        AS_REGISTEREDTYPE_ASTRANSFORMT,
        //! AsOrigin
        AS_REGISTEREDTYPE_ASORIGINT,
        //! AsPointer
        AS_REGISTEREDTYPE_ASPOINTERT,
        //! AsTextRunArray
        AS_REGISTEREDTYPE_ASTEXTRUNARRAYT,
        //! AsUndoResourceIndex
        AS_REGISTEREDTYPE_ASUNDORESOURCEINDEX,
        //! AsLabel
        AS_REGISTEREDTYPE_ASLABEL,
        //! AsOptionList
        AS_REGISTEREDTYPE_ASOPTIONLIST,
        //! AsTextCharFormat
        AS_REGISTEREDTYPE_ASTEXTCHARFORMAT,
        //! AsStringPairList
        AS_REGISTEREDTYPE_ASSTRINGPAIRLIST,
        //! AsInstructListList
        AS_REGISTEREDTYPE_ASINSTRUCTLISTLIST,
        //! AsMOUList
        AS_REGISTEREDTYPE_ASMOULIST,
        //! AsVirtualFolderIndex
        AS_REGISTEREDTYPE_ASVIRTUALFOLDERINDEX,
        //! AsFolderIndex
        AS_REGISTEREDTYPE_ASFOLDERINDEX,
        //! AsAsyncTestLevelList
        AS_REGISTEREDTYPE_ASASYNCTESTLEVELLIST,
    };

    //! Use this to look up the AsEnumRegisteredType for a type name
    QHash<QString, int> m_AsTypes;
};

#endif // ASSTREAMER_H
