#include "asfileutils.h"

#include <QDir>

#include "../objects/asobject.h"
#include "../io/asnode.h"
#include "../resources/asresource.h"

AsFileUtils::AsFileUtils()
{

}

AsFileUtils::~AsFileUtils()
{

}

QString AsFileUtils::asGetObjectFilename( AsObject *pObject )
{
    QString sSuffix = ".io";
    AsObject::AsEnumObjectType type = pObject->asGetType();
    switch ( type )
    {
        case AsObject::AS_OBJECT_ANNOTATIONRES:
        case AsObject::AS_OBJECT_IMAGERES:
        case AsObject::AS_OBJECT_LINERES:
        case AsObject::AS_OBJECT_MOTIONRES:
        case AsObject::AS_OBJECT_SHAPERES:
        case AsObject::AS_OBJECT_TEXTRES:
        case AsObject::AS_OBJECT_MEDIAFILERES:
        {
            sSuffix = ".ir";
        }
            break;

        default:
            //Do Nothing
            break;
    }
    return QString::number( pObject->asGetID() ) + sSuffix;
}

QString AsFileUtils::asGetResourceDataFilename( AsResource *pResource )
{
    QString sSuffix = "ird";
    QString sOrig = pResource->asGetOriginalFilename();
    if ( !sOrig.isEmpty() )
    {
        QFileInfo orig( sOrig );
        if ( !orig.suffix().isEmpty() )
        {
            sSuffix = orig.suffix();
        }
    }
    return QString::number( pResource->asGetID() ) + "." + sSuffix;
}

QString AsFileUtils::asGetNodeTreeFilename( AsNode *pNode )
{
    return QString::number( pNode->asGetID() ) + ".in";
}

QString AsFileUtils::asCleanPath( const QString& path )
{
    QString clean = QDir::cleanPath( path );
    /** NN: this is to make sure that any paths stored in the '\' windows format are modified to the standard
       '/' unix format */
    clean.replace('\\', '/');
    clean = QDir::toNativeSeparators( clean );
    return clean;
}