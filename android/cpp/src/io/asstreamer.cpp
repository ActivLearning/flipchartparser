// Implementation of the AsStreamer class.
// $Author: Paul Wareing

#include "asstreamer.h"

AsStreamer::AsStreamer()
{
    m_AsTypes.insert( "AsPointFArray", AsStreamer::AS_REGISTEREDTYPE_ASPOINTFARRAYT );
    m_AsTypes.insert( "AsPointFArrayArray", AsStreamer::AS_REGISTEREDTYPE_ASPOINTFARRAYARRAYT );
    m_AsTypes.insert( "AsResourceIndex", AsStreamer::AS_REGISTEREDTYPE_ASRESOURCEINDEXT );
    m_AsTypes.insert( "AsResourceRegister", AsStreamer::AS_REGISTEREDTYPE_ASRESOURCEREGISTERT );
    m_AsTypes.insert( "AsRectF", AsStreamer::AS_REGISTEREDTYPE_ASRECTF );
    m_AsTypes.insert( "AsInk", AsStreamer::AS_REGISTEREDTYPE_ASINKT );
    m_AsTypes.insert( "AsTransform", AsStreamer::AS_REGISTEREDTYPE_ASTRANSFORMT );
    m_AsTypes.insert( "AsOrigin", AsStreamer::AS_REGISTEREDTYPE_ASORIGINT );
    m_AsTypes.insert( "AsPointer", AsStreamer::AS_REGISTEREDTYPE_ASPOINTERT );
    m_AsTypes.insert( "AsTextRunArray", AsStreamer::AS_REGISTEREDTYPE_ASTEXTRUNARRAYT );
    m_AsTypes.insert( "AsUndoResourceIndex", AsStreamer::AS_REGISTEREDTYPE_ASUNDORESOURCEINDEX );
    m_AsTypes.insert( "AsLabel", AsStreamer::AS_REGISTEREDTYPE_ASLABEL );
    m_AsTypes.insert( "AsOptionList", AsStreamer::AS_REGISTEREDTYPE_ASOPTIONLIST );
    m_AsTypes.insert( "AsTextCharFormat", AsStreamer::AS_REGISTEREDTYPE_ASTEXTCHARFORMAT );
    m_AsTypes.insert( "AsStringPairList", AsStreamer::AS_REGISTEREDTYPE_ASSTRINGPAIRLIST );
    m_AsTypes.insert( "AsInstructListList", AsStreamer::AS_REGISTEREDTYPE_ASINSTRUCTLISTLIST );
    m_AsTypes.insert( "AsMOUList", AsStreamer::AS_REGISTEREDTYPE_ASMOULIST );
    m_AsTypes.insert( "AsVirtualFolderIndex", AsStreamer::AS_REGISTEREDTYPE_ASVIRTUALFOLDERINDEX );
    m_AsTypes.insert( "AsFolderIndex", AsStreamer::AS_REGISTEREDTYPE_ASFOLDERINDEX );
    m_AsTypes.insert( "AsAsyncTestLevelList", AsStreamer::AS_REGISTEREDTYPE_ASASYNCTESTLEVELLIST );
}

AsStreamer::~AsStreamer()
{

}
