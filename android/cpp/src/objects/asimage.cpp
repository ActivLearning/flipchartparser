// Implements the AsImage class.
// (c) Promethean Technology Group

#include "asimage.h"
#include "../resources/asresourcemanager.h"
#include "../resources/asimageres.h"
#include "../asfactory.h"
//#include "asfileutils.h"
//#include "asmath.h"
//#include "aslocale.h"
//#include "asapp.h"

AsImage::AsImage() : AsRenderable( 0 )
{
    this->asConstruct();
}

AsImage::AsImage( AsFactory *pAsFactory ) : AsRenderable( pAsFactory )
{
    this->asConstruct();
}

void AsImage::asConstruct( void )
{
    // Set the type property.
    asSetType( AsObject::AS_OBJECT_IMAGE );

    // Initialise the properties with primitive types.
    m_nResource = 0;
    m_pAsImageRes = 0;
    m_bTransparent = false;
    m_bTiled = false;
    m_nTileFit = AsImage::AS_TILEFIT_BESTFIT;
    m_bPickThrough = false;
    m_alternativePalette.resize( 0 );
}

AsImage::AsImage( const AsImage& image ) : AsRenderable( image )
{
    this->asCopy( image );
}

void AsImage::operator= ( const AsImage& image )
{
    AsRenderable::operator = ( image );
    this->asCopy( image );
}

bool AsImage::operator== ( const AsImage& image )
{
    if ( !AsRenderable::operator ==( image ) )
    {
        return false;
    }

//    if (( m_nResource != image.asGetResource() ) ||
//        ( m_bTransparent != image.asGetTransparent() ) ||
//        ( m_TransparentColor != image.asGetTransparentColor() ) ||
//        ( m_bTiled != image.asGetTiled() ) ||
//        ( m_nTileFit != image.asGetTileFit() ) ||
//        ( m_TileArea != image.asGetTileArea() ) ||
//        ( m_bPickThrough != image.asGetPickThrough() ) ||
//    ( m_alternativePalette != image.asGetAltPalette() ))
//    {
//        return false;
//    }
    return true;
}

void AsImage::asCopy( const AsImage& image )
{
    this->m_nResource = image.asGetResource();
    this->m_bTransparent = image.asGetTransparent();
    this->m_TransparentColor = image.asGetTransparentColor();
    this->m_bTiled = image.asGetTiled();
    this->m_nTileFit = image.asGetTileFit();
    this->m_TileArea = image.asGetTileArea();
    this->m_bPickThrough = image.asGetPickThrough();
    this->m_alternativePalette = image.asGetAltPalette();
    this->m_pAsImageRes = 0;
}

AsImage::~AsImage()
{
//    if ( m_pAsImageRes != 0 )
//    {
//        this->m_pAsFactory->asGetResourceManager()->asUnloadResource( m_pAsImageRes );
//    }
}

QHash<QString, quint16>& AsImage::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
     //   HashProperties.insert( "asDateTimeCreated", ( quint16 )AsImage::AS_PROPERTY_DATETIMECREATED );

        // From AsRenderable...
        HashProperties.insert( "transform", ( quint16 )AsImage::AS_PROPERTY_TRANSFORM );
     //   HashProperties.insert( "asTwips", ( quint16 )AsImage::AS_PROPERTY_TWIPS );
        HashProperties.insert( "name", ( quint16 )AsImage::AS_PROPERTY_NAME );
     //   HashProperties.insert( "asKeywords", ( quint16 )AsImage::AS_PROPERTY_KEYWORDS );
    //    HashProperties.insert( "asVisible", ( quint16 )AsImage::AS_PROPERTY_VISIBLE );
        HashProperties.insert( "boundingRect", ( quint16 )AsImage::AS_PROPERTY_BOUNDINGRECT );
        HashProperties.insert( "layer", ( quint16 )AsImage::AS_PROPERTY_LAYER );
        HashProperties.insert( "zOrder", ( quint16 )AsImage::AS_PROPERTY_Z );
        HashProperties.insert( "ink", ( quint16 )AsImage::AS_PROPERTY_INK );
        HashProperties.insert( "scaleOrigin", ( quint16 )AsImage::AS_PROPERTY_SCALEORIGIN );
        HashProperties.insert( "rotateOrigin", ( quint16 )AsImage::AS_PROPERTY_ROTATEORIGIN );
        HashProperties.insert( "moveType", ( quint16 )AsImage::AS_PROPERTY_CANMOVE );
       // HashProperties.insert( "asCanSize", ( quint16 )AsImage::AS_PROPERTY_CANSIZE );
      //  HashProperties.insert( "asCanRotate", ( quint16 )AsImage::AS_PROPERTY_CANROTATE );
      //  HashProperties.insert( "asCanBlock", ( quint16 )AsImage::AS_PROPERTY_CANBLOCK );
      //  HashProperties.insert( "asCanSnap", ( quint16 )AsImage::AS_PROPERTY_CANSNAP );
        HashProperties.insert( "locked", ( quint16 )AsImage::AS_PROPERTY_LOCKED );
     //   HashProperties.insert( "asSnapback", ( quint16 )AsImage::AS_PROPERTY_SNAPBACK );
     //   HashProperties.insert( "asPathPointer", ( quint16 )AsImage::AS_PROPERTY_PATHPOINTER );
     //   HashProperties.insert( "asRotateAboutPointer", ( quint16 )AsImage::AS_PROPERTY_ROTATEABOUTPOINTER );
     //   HashProperties.insert( "asRotatePoint", ( quint16 )AsImage::AS_PROPERTY_ROTATEPOINT );
     //   HashProperties.insert( "asRotateAbout", ( quint16 )AsImage::AS_PROPERTY_ROTATEABOUT );
     //   HashProperties.insert( "asRotateStep", ( quint16 )AsImage::AS_PROPERTY_ROTATESTEP );
     //   HashProperties.insert( "asSnapToPointer", ( quint16 )AsImage::AS_PROPERTY_SNAPTOPOINTER );
     //   HashProperties.insert( "asSnapPoint", ( quint16 )AsImage::AS_PROPERTY_SNAPPOINT );
     //   HashProperties.insert( "asSnapTo", ( quint16 )AsImage::AS_PROPERTY_SNAPTO );
     //   HashProperties.insert( "asCanContain", ( quint16 )AsImage::AS_PROPERTY_CANCONTAIN );
     //   HashProperties.insert( "asContainPointer", ( quint16 )AsImage::AS_PROPERTY_CONTAINPOINTER );
    //    HashProperties.insert( "asContainWords", ( quint16 )AsImage::AS_PROPERTY_CONTAINWORDS );
     //   HashProperties.insert( "asContainRule", ( quint16 )AsImage::AS_PROPERTY_CONTAINRULE );
     //   HashProperties.insert( "asV2Type", ( quint16 )AsImage::AS_PROPERTY_V2TYPE );
    //    HashProperties.insert( "asConnectorList", ( quint16 )AsImage::AS_PROPERTY_CONNECTORLIST );
     //   HashProperties.insert( "asLabel", ( quint16 )AsImage::AS_PROPERTY_LABEL );
    //    HashProperties.insert( "asQuestionItem", ( quint16 )AsImage::AS_PROPERTY_QUESTIONITEM );
     //   HashProperties.insert( "asQuestionItemID", ( quint16 )AsImage::AS_PROPERTY_QUESTIONITEMID );
     //   HashProperties.insert( "asQuestionTag", ( quint16 )AsImage::AS_PROPERTY_QUESTIONTAG );
    //    HashProperties.insert( "asAllowSnapback", ( quint16 )AsImage::AS_PROPERTY_ALLOWSNAPBACK );
    //    HashProperties.insert( "asDragACopy", ( quint16 )AsImage::AS_PROPERTY_DRAGACOPY );
    //    HashProperties.insert( "asRewardSound", ( quint16 )AsImage::AS_PROPERTY_REWARD_SOUND );
    //    HashProperties.insert( "asRewardSoundLocation", ( quint16 )AsImage::AS_PROPERTY_REWARD_SOUND_LOCATION );
    //    HashProperties.insert( "asAsyncTestTag", ( quint16 )AsImage::AS_PROPERTY_ASYNCTESTTAG );
    //    HashProperties.insert( "asInteractMode", ( quint16 )AsImage::AS_PROPERTY_INTERACTMODE );

        // From AsImage...
        HashProperties.insert( "resource", ( quint16 )AsImage::AS_PROPERTY_RESOURCE );
        HashProperties.insert( "transparent", ( quint16 )AsImage::AS_PROPERTY_TRANSPARENT );
        HashProperties.insert( "transparentColor", ( quint16 )AsImage::AS_PROPERTY_TRANSPARENTCOLOR );
        HashProperties.insert( "tiled", ( quint16 )AsImage::AS_PROPERTY_TILED );
        HashProperties.insert( "tileFit", ( quint16 )AsImage::AS_PROPERTY_TILEFIT );
        HashProperties.insert( "tileArea", ( quint16 )AsImage::AS_PROPERTY_TILEAREA );
    //    HashProperties.insert( "asPickThrough", ( quint16 )AsImage::AS_PROPERTY_PICKTHROUGH );
    //    HashProperties.insert( "asAlternativePalette", ( quint16 )AsImage::AS_PROPERTY_ALTERNATIVEPALETTE );
    }

    return HashProperties;
}

void AsImage::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}


bool AsImage::asCheckHit(  const QPointF & worldPos )
{
    /* if we hit the transformed image and it is transparent and finally
       the user wants to ignore transparent regions then do the more expensive test */
    bool hit = false;


//    if( As2DGeom::asPntInPolygon( poly, worldPos ) )
//    {
//        hit = true;
//        if( asGetPickThrough() )
//        {
//            AsTransform *ppTran = asGetTransformPointer();
//            AsOrigin porigin = asGetScaleOrigin();
//            const AsRectF &bRect = asGetBoundingRect();
//            const QMatrix &combMatRef = ppTran->asDoTransform( porigin, bRect);
//
//            AsImageRes * pImageRes = ( AsImageRes * )asGetResourcePointer();
//            if( pImageRes != 0 )
//            {
//                QPointF iWorldPos = combMatRef.inverted().map( worldPos );
//                QPoint iPos( ( int )iWorldPos.x(), ( int )iWorldPos.y() );
//                if( pImageRes->asIsPixelTransparent( iPos, m_bTransparent, m_TransparentColor ) )
//                {
//                    hit = false;
//                }
//            }
//        }
//    }
    return hit;

}

bool AsImage::asIsResourcePointerValid( void )
{
    return asGetResourcePointer() == NULL ? false : true;
}

//unsigned int AsImage::asGetResource( void ) const
//{
//    return m_nResource;
//}

void AsImage::asSetResource( unsigned int nResource )
{
    m_nResource = nResource;
}

AsResource * AsImage::asGetResourcePointer( void )
{
    if ( m_pAsImageRes == 0 && asGetResource() > 0)
    {
        // Load the resource.
        m_pAsImageRes = dynamic_cast<AsImageRes*>(m_pAsFactory->getResourceManager()->asLoadResource( AsObject::AS_OBJECT_IMAGERES, asGetResource() ));

        if (m_pAsImageRes != 0)
        {
            // load..
            QString sDataFilename = this->m_pAsFactory->getResourceManager()->asGetResourceDataFilename( m_pAsImageRes );
            QString sWorkingPath = this->m_pAsFactory->getResourceManager()->asGetWorkingPath();
            m_sResFilePath = sWorkingPath + "/" + sDataFilename;
            asLoadResourceDataFile( sDataFilename, sWorkingPath );
        }
    }

    return m_pAsImageRes;

}

void AsImage::asUnloadResource( void )
{
//    if ( m_pAsImageRes != NULL )
//    {
//        this->m_pAsFactory->asGetResourceManager()->asUnloadResource( m_pAsImageRes );
//        m_pAsImageRes = NULL;
//    }
}

bool AsImage::asLoadResourceDataFile( const QString& filename, const QString& path )
{
    // Load the image data and construct the image.
//    QString filePath = path + QDir::separator() + filename;
//    filePath = AsFileUtils::asCleanPath( filePath );
//    bool res = m_pAsImageRes->asLoadImage( filePath, this->asGetTransparent(), true, this->asGetTransparentColor() );
//    if( res )
//    {
//        m_pAsImageRes->asConstructImage( m_alternativePalette, this->asGetTransparent(), this->asGetTransparentColor() );
//    }
//    else
//    {
//        res = m_pAsImageRes->asLoadScaledImage( ":/redx.tif", m_pAsImageRes->asGetImageSize() );
//    }

    return false;
}

void AsImage::asSetResource( AsResource *pResource )
{
//    m_pAsImageRes = qobject_cast< AsImageRes * >( pResource );
//    if( m_pAsImageRes != NULL )
//    {
//    m_nResource = m_pAsImageRes->asGetID();
//    }
//    else
//    {
//    m_nResource = 0;
//    }
//    this->asSetDirtyForWrite( true );
}

bool AsImage::asGetTransparent( void ) const
{
    return m_bTransparent;
}

void AsImage::asSetTransparent( bool bTransparent )
{
    m_bTransparent = bTransparent;
}

const QColor& AsImage::asGetTransparentColor( void ) const
{
    return m_TransparentColor;
}

void AsImage::asSetTransparentColor( QColor& color )
{
    m_TransparentColor = color;
}

bool AsImage::asProcessTransparentColor( const QColor& color )
{
//    AsImageRes * pImageRes = ( AsImageRes * )this->asGetResourcePointer();
//    if ( pImageRes == NULL )
//        return false;
//
//    if ( pImageRes->asGetBitDepth() == 8 )
//    {
//        AsResourceManager *pManager = this->asGetFactoryPointer()->asGetResourceManager();
//        pImageRes = ( AsImageRes * )pManager->asDetachResource( pImageRes );
//        this->asSetResource( pImageRes );
//        pImageRes->asRedirectTransparentColor( this->m_TransparentColor );
//        pImageRes->asSetTransparentColor( color, m_alternativePalette );
//
//        QString path = AsApp::asInstance()->asGetTempAppPath();
//        QString sFileName = QString( "temp.bmp" );
//        QString temp = path + QDir::separator() + sFileName;
//        pImageRes->asSaveImage( temp );
//
//        pImageRes->asSetOriginalFilename( sFileName );
//        pImageRes->asSetOriginalFilePath( temp );
//
//        pImageRes = ( AsImageRes * )pManager->asCommitResource( pImageRes );
//        this->asSetResource( pImageRes );
//    }
//
//    m_TransparentColor = color;

    return true;
}

bool AsImage::asGetTiled( void ) const
{
    return m_bTiled;
}

void AsImage::asSetTiled( bool bTiled )
{
    m_bTiled = bTiled;
}

AsImage::AsEnumTileFit AsImage::asGetTileFit( void ) const
{
    return m_nTileFit;
}

void AsImage::asSetTileFit( AsImage::AsEnumTileFit nTileFit )
{
    m_nTileFit = nTileFit;
}

const QSizeF& AsImage::asGetTileArea( void ) const
{
    return m_TileArea;
}

void AsImage::asSetTileArea( QSizeF& sizef )
{
    m_TileArea = sizef;
}

bool AsImage::asGetPickThrough( void ) const
{
    return m_bPickThrough;
}

void AsImage::asSetPickThrough( bool pickThrough )
{
    m_bPickThrough = pickThrough;
}

int AsImage::asGetTranslucency( void )
{
    // we map to the brush alpha for pixmaps
    AsInk *pInk = this->asGetInkPointer();
    return 0;
   // return( pInk->asGetBrushAlpha() );
}

void AsImage::asSetTranslucency( int translucency )
{
    // map to brush
    AsInk *pInk = this->asGetInkPointer();
    pInk->asSetAlpha( AsInk::AS_COLOR_BRUSH , translucency );
}

const QByteArray& AsImage::asGetAltPalette( void ) const
{
    return m_alternativePalette;
}

void AsImage::asSetAltPalette( QByteArray& altPalette )
{
    m_alternativePalette = altPalette;
}


QString AsImage::asGetNewObjectName(quint32 nIndex)
{
    QString strNextName;
   // strNextName = AsLocale::asGetString(AsLocale::AS_STRING_IMAGE) + AsLocale::asInstance()->asGetLocale().toString(nIndex);
    return strNextName;
}

bool AsImage::asSwapColorAtPosition( const QPoint& position, const QColor& color, const int tolerance )
{
   // qDebug() << "[ AsImage ] - asSwapColorAtPosition posn " << position.x() << position.y() << " color " << color.red() << color.green() << color.blue() << color.alpha();

    bool ok = false;

////    AsImageRes * pImageRes = ( AsImageRes * )this->asGetResourcePointer();
////    if ( pImageRes == NULL )
////        return ok;
////
////    qDebug() << " [ AsImage ] - asSwapColorAtPosition bit depth is " << pImageRes->asGetBitDepth();
////
////    if ( pImageRes->asGetBitDepth() == 8 )
////    {
////        // What if there is no alt palette - does this still work? (create the alt palette as copy of normal palette?)
////        QByteArray pPalette = asGetAltPalette();
////        qDebug() << " [ AsImage ] - asSwapColorAtPosition asGetAltPalette  size is " << pPalette.size();
////        if ( pPalette.size() == 0 )
////        {
////            qDebug() << " [ AsImage ] - asSwapColorAtPosition Warning! alt palette size is zero!";
////
////            // Construct the alternatte palette from the Imageres palette...
////            pPalette = pImageRes->asGetPalette();
////        }
////
////        qDebug() << " about to call pImageRes->asSwapColorAtPosition ";
////        ok = pImageRes->asSwapColorAtPosition( &pPalette, position, color );
////
////        asSetAltPalette( pPalette );
////
////        //pImageRes->asConstructImage( pPalette, true ); // not needed?
////    }
////    else if ( pImageRes->asGetBitDepth() > 8 ) // (non-palletised)
////    {
////        ok = pImageRes->asSwapColorAtPosition( position, color, tolerance );
////    }
////    else
////    {
////        // (do nothing for now)
////    }
    
    return ok;
}

/**
 * Returns a pointer to a pixmap version of the image suitable for rendering. Can be null if there is no image data constructed.
 *
 */
const QPixmap* AsImage::asGetPixmap()
{
//    AsImageRes* pImageRes = qobject_cast<AsImageRes*>(asGetResourcePointer());
//
//    if (pImageRes)
//    {
//        return pImageRes->asConstructImage( m_alternativePalette, m_bTransparent, m_TransparentColor );
//    }
//    else
//    {
//        return 0;
//    }
    return Q_NULLPTR;
}

QString AsImage::getPropertyNameById(int nID)
{
    return m_lProperties().key(AsEnumProperty(nID));
}

int AsImage::getPropertyIdByName(QString name) const
{
    return m_lProperties().value(name);
}

const Json::Value &AsImage::asResourceSerialized()
{
    asGetResourcePointer();
    if(m_pAsImageRes){
        m_resourceJsonObject["imageUrl"] = m_sResFilePath.toStdString();
    }
    return m_resourceJsonObject;
}

QString AsImage::getImagePath()
{
    asGetResourcePointer();
    return m_sResFilePath;
}

Json::Value &AsImage::serialized()
{
    Json::Value &jsonObject=AsRenderable::serialized();
    jsonObject.removeMember("ink");
    return jsonObject;
}

QString AsImage::typeName()
{
    return "image";
}
