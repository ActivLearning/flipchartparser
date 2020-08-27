/** @file asresourceregister.cpp
 * Categorised lists of resources used in a flipchart
 * Copyright (C) 2006-2010 Promethean Limited. All Rights Reserved.
 */

//#include <QDebug>
//#include <AsCommon>
#include "asresourceregister.h"
#include "../util/commonlog.h"



// Uncomment line below for event debug output
//#define AS_USE_DEBUG
//#ifdef AS_USE_DEBUG
//static int debugCounter = 0;
//#define AS_DEBUG(x) qDebug() << "[RR]" << "[" << debugCounter++ << "]" << "(" << __FUNCTION__ << ")" << x;
//#else
//#define AS_DEBUG(x)
//#endif


AsResourceRegister::AsResourceRegister()
{
//    AS_DEBUG("Constructor" << this)
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_RESOURCEREGISTER );
}

AsResourceRegister::AsResourceRegister( const AsResourceRegister& reg ) : AsObject( reg )
{
//    AS_DEBUG("Copy Constructor" << this)
    m_AnnotationResources = reg.asGetAnnotationResources();
    m_ImageResources = reg.asGetImageResources();
    m_LineResources = reg.asGetLineResources();
    m_ShapeResources = reg.asGetShapeResources();
    m_TextResources = reg.asGetTextResources();
    m_MotionResources = reg.asGetMotionResources();
    m_MediaFileResources = reg.asGetMediaFileResources();
}

AsResourceRegister::~AsResourceRegister()
{
    LOGDEBUG("free resourcereg","");
//    AS_DEBUG("Destructor" << this)
}

void AsResourceRegister::operator= ( const AsResourceRegister& reg )
{
//    AS_DEBUG("operator=" << this)
    AsObject::operator =( reg );

    m_AnnotationResources = reg.asGetAnnotationResources();
    m_ImageResources = reg.asGetImageResources();
    m_LineResources = reg.asGetLineResources();
    m_ShapeResources = reg.asGetShapeResources();
    m_TextResources = reg.asGetTextResources();
    m_MotionResources = reg.asGetMotionResources();
    m_MediaFileResources = reg.asGetMediaFileResources();
}

// Static
QHash<QString, quint16>& AsResourceRegister::m_lProperties( void )
{

    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsResourceRegister::AS_PROPERTY_DATETIMECREATED );

        // From AsFlipchart
        HashProperties.insert( "annotationResources", ( quint16 )AsResourceRegister::AS_PROPERTY_ANNOTATIONRESOURCES );
        HashProperties.insert( "imageResources", ( quint16 )AsResourceRegister::AS_PROPERTY_IMAGERESOURCES );
        HashProperties.insert( "lineResources", ( quint16 )AsResourceRegister::AS_PROPERTY_LINERESOURCES );
        HashProperties.insert( "shapeResources", ( quint16 )AsResourceRegister::AS_PROPERTY_SHAPERESOURCES );
        HashProperties.insert( "textResources", ( quint16 )AsResourceRegister::AS_PROPERTY_TEXTRESOURCES );
        HashProperties.insert( "motionResources", ( quint16 )AsResourceRegister::AS_PROPERTY_MOTIONRESOURCES );
        HashProperties.insert( "mediaFileResources", ( quint16 )AsResourceRegister::AS_PROPERTY_MEDIAFILERESOURCES );
    }

    return HashProperties;
}

void AsResourceRegister::asRemoveAllNullResourceItems( void )
{
//    AS_DEBUG( this )
    m_AnnotationResources.asRemoveNullResourceItems();
    m_ImageResources.asRemoveNullResourceItems();
    m_LineResources.asRemoveNullResourceItems();
    m_ShapeResources.asRemoveNullResourceItems();
    m_TextResources.asRemoveNullResourceItems();
    m_MotionResources.asRemoveNullResourceItems();
    m_MediaFileResources.asRemoveNullResourceItems();
}

//void AsResourceRegister::asResetPropertyIndex( void )
//{
////    AS_DEBUG( this )
////    AsObject::asSetPropertyIterator( &m_lProperties );
//}

const AsResourceIndex& AsResourceRegister::asGetAnnotationResources( void ) const
{
//    AS_DEBUG( this )
   Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_ANNOTATIONRESOURCES);
   if(var.type == VariableType::ASRESOUCREINDEX && var.value){
       return *static_cast<AsResourceIndex*>(var.value);
   }
   return m_AnnotationResources;
}

AsResourceIndex* AsResourceRegister::asGetAnnotationResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_ANNOTATIONRESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_AnnotationResources;
}

void AsResourceRegister::asSetAnnotationResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_AnnotationResources = a;
}

const AsResourceIndex& AsResourceRegister::asGetImageResources( void ) const
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_IMAGERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return *static_cast<AsResourceIndex*>(var.value);
    }
    return m_ImageResources;
}

AsResourceIndex* AsResourceRegister::asGetImageResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_IMAGERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_ImageResources;
}

void AsResourceRegister::asSetImageResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_ImageResources = a;
}

const AsResourceIndex& AsResourceRegister::asGetLineResources( void ) const
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_LINERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return *static_cast<AsResourceIndex*>(var.value);
    }
    return m_LineResources;
}

AsResourceIndex* AsResourceRegister::asGetLineResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_LINERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_LineResources;
}

void AsResourceRegister::asSetLineResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_LineResources = a;
}

const AsResourceIndex& AsResourceRegister::asGetShapeResources( void ) const
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_SHAPERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return *static_cast<AsResourceIndex*>(var.value);
    }
    return m_ShapeResources;
}

AsResourceIndex* AsResourceRegister::asGetShapeResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_SHAPERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_ShapeResources;
}

void AsResourceRegister::asSetShapeResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_ShapeResources = a;
}

const AsResourceIndex& AsResourceRegister::asGetTextResources( void ) const
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_TEXTRESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return *static_cast<AsResourceIndex*>(var.value);
    }
    return m_TextResources;
}

AsResourceIndex* AsResourceRegister::asGetTextResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_TEXTRESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_TextResources;
}

void AsResourceRegister::asSetTextResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_TextResources = a;
}

const AsResourceIndex& AsResourceRegister::asGetMotionResources( void ) const
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_MOTIONRESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return *static_cast<AsResourceIndex*>(var.value);
    }
    return m_MotionResources;
}

AsResourceIndex* AsResourceRegister::asGetMotionResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_MOTIONRESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_MotionResources;
}

void AsResourceRegister::asSetMotionResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_MotionResources = a;
}

const AsResourceIndex& AsResourceRegister::asGetMediaFileResources( void ) const
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_MEDIAFILERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return *static_cast<AsResourceIndex*>(var.value);
    }
    return m_MediaFileResources;
}

AsResourceIndex* AsResourceRegister::asGetMediaFileResourcesPointer( void )
{
//    AS_DEBUG( this )
    Variant var = m_properties.value(AsResourceRegister::AS_PROPERTY_MEDIAFILERESOURCES);
    if(var.type == VariableType::ASRESOUCREINDEX && var.value){
        return static_cast<AsResourceIndex*>(var.value);
    }
    return &m_MediaFileResources;
}

void AsResourceRegister::asSetMediaFileResources( AsResourceIndex& a )
{
//    AS_DEBUG( this )
    m_MediaFileResources = a;
}

AsResourceIndex * AsResourceRegister::asGetResourceIndex( AsObject::AsEnumObjectType type )
{
//    AS_DEBUG("type:" << type)
    AsResourceIndex *pIndex = 0;
    switch ( type )
    {
        case AsObject::AS_OBJECT_ANNOTATIONRES:
            pIndex = this->asGetAnnotationResourcesPointer();
            break;

        case AsObject::AS_OBJECT_MATHML:
        case AsObject::AS_OBJECT_VERTEXT:
        case AsObject::AS_OBJECT_IMAGERES:
            pIndex = this->asGetImageResourcesPointer();
            break;

        case AsObject::AS_OBJECT_LINERES:
            pIndex = this->asGetLineResourcesPointer();
            break;

        case AsObject::AS_OBJECT_MOTIONRES:
            pIndex = this->asGetMotionResourcesPointer();
            break;

        case AsObject::AS_OBJECT_SHAPERES:
            pIndex = this->asGetShapeResourcesPointer();
            break;

        case AsObject::AS_OBJECT_TEXTRES:
            pIndex = this->asGetTextResourcesPointer();
            break;

        case AsObject::AS_OBJECT_MEDIAFILERES:
            pIndex = this->asGetMediaFileResourcesPointer();
            break;

        default:
            QString msg = QString("Resource index pointer requested for invalid type").arg(type);
//            As::logAndAssert( false, "AsResourceRegister", "asGetResourceIndex", qPrintable(msg) );
            break;
    }

    if( pIndex == NULL )
    {
        QString msg = QString( "Index pointer is NULL for type: %1" ).arg(type);
//        As::logAndAssert( false, "AsResourceRegister", "asGetResourceIndex", qPrintable(msg) );
    }
    return pIndex;
}

QString AsResourceRegister::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

