// Defines the AsResourceRegister class.
// $Author: Paul Wareing.

#ifndef ASRESOURCEREGISTER_H
#define ASRESOURCEREGISTER_H

#include <QMetaType>
#include <QHash>
#include <QPointF>

#include "asresourceindex.h"
#include "../objects/asobject.h"

/**
 * Represents a ResourceRegister property in a flipchart
 */
class AsResourceRegister : public AsObject
{

    Q_PROPERTY( AsResourceIndex asAnnotationResources READ asGetAnnotationResources WRITE asSetAnnotationResources )
    Q_PROPERTY( AsResourceIndex asImageResources READ asGetImageResources WRITE asSetImageResources )
    Q_PROPERTY( AsResourceIndex asLineResources READ asGetLineResources WRITE asSetLineResources )
    Q_PROPERTY( AsResourceIndex asShapeResources READ asGetShapeResources WRITE asSetShapeResources )
    Q_PROPERTY( AsResourceIndex asTextResources READ asGetTextResources WRITE asSetTextResources )
    Q_PROPERTY( AsResourceIndex asMotionResources READ asGetMotionResources WRITE asSetMotionResources )
    Q_PROPERTY( AsResourceIndex asMediaFileResources READ asGetMediaFileResources WRITE asSetMediaFileResources )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResourceRegister...
        AS_PROPERTY_NAME,
        AS_PROPERTY_VERSION,
        AS_PROPERTY_CURRENTPAGEID,
        AS_PROPERTY_ANNOTATIONRESOURCES,
        AS_PROPERTY_IMAGERESOURCES,
        AS_PROPERTY_LINERESOURCES,
        AS_PROPERTY_SHAPERESOURCES,
        AS_PROPERTY_TEXTRESOURCES,
        AS_PROPERTY_MOTIONRESOURCES,
        AS_PROPERTY_MEDIAFILERESOURCES
    };

    // Construction and destruction.
    AsResourceRegister();
    AsResourceRegister( const AsResourceRegister& );
    virtual ~AsResourceRegister();

    void operator= ( const AsResourceRegister& );

    // Interface.
//    void asResetPropertyIndex( void );

    void asRemoveAllNullResourceItems( void );

    const AsResourceIndex& asGetAnnotationResources( void ) const;
    AsResourceIndex* asGetAnnotationResourcesPointer( void );
    void asSetAnnotationResources( AsResourceIndex& );

    const AsResourceIndex& asGetImageResources( void ) const;
    AsResourceIndex* asGetImageResourcesPointer( void );
    void asSetImageResources( AsResourceIndex& );

    const AsResourceIndex& asGetLineResources( void ) const;
    AsResourceIndex* asGetLineResourcesPointer( void );
    void asSetLineResources( AsResourceIndex& );

    const AsResourceIndex& asGetShapeResources( void ) const;
    AsResourceIndex* asGetShapeResourcesPointer( void );
    void asSetShapeResources( AsResourceIndex& );

    const AsResourceIndex& asGetTextResources( void ) const;
    AsResourceIndex* asGetTextResourcesPointer( void );
    void asSetTextResources( AsResourceIndex& );

    const AsResourceIndex& asGetMotionResources( void ) const;
    AsResourceIndex* asGetMotionResourcesPointer( void );
    void asSetMotionResources( AsResourceIndex& );

    const AsResourceIndex& asGetMediaFileResources( void ) const;
    AsResourceIndex* asGetMediaFileResourcesPointer( void );
    void asSetMediaFileResources( AsResourceIndex& );
    AsResourceIndex * asGetResourceIndex( AsObject::AsEnumObjectType type );

protected:
    QString getPropertyNameById(int nID) override;

private:
    // Property hash table.
    static QHash<QString, quint16>& m_lProperties( void );

    // Properties.
    AsResourceIndex m_AnnotationResources;
    AsResourceIndex m_ImageResources;
    AsResourceIndex m_LineResources;
    AsResourceIndex m_ShapeResources;
    AsResourceIndex m_TextResources;
    AsResourceIndex m_MotionResources;
    AsResourceIndex m_MediaFileResources;
};

//Q_DECLARE_METATYPE( AsResourceRegister )

#endif // ASRESOURCEREGISTER_H
