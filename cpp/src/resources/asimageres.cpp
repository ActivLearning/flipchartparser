// Implements the AsImageRes class.
// $Author: Paul Wareing.

#include <QFile>
#include <QDataStream>
#include "../objects/qcolor.h"

#include "asimageres.h"
#include <QPoint>

#define     BYTES_PER_COLOR         3
#define     PALETTE_COLORS          256
#define     PALETTE_SIZE            PALETTE_COLORS * BYTES_PER_COLOR

#define     OPAQUE                  255
#define     TRANSPARENT             0

AsImageRes::AsImageRes( AsFactory *pAsFactory ) : AsResource( pAsFactory ),
                                                  m_bLoaded( false )
{
   // asSetType( AsObject::AS_OBJECT_IMAGERES );

    // Initialise the members with primitive types.
    m_nBitDepth = 0;
    m_nFrameCount = 1;
    m_TransparentColor = QColor();
}

AsImageRes::AsImageRes( const AsImageRes& imageres ) : AsResource( imageres ),
                                                       m_bLoaded( false )
{
    this->asCopy( imageres );
}

void AsImageRes::operator= ( const AsImageRes& imageres )
{
    AsResource::operator = ( imageres );
    this->asCopy( imageres );
}

void AsImageRes::asCopy( const AsImageRes& imageres )
{
    this->m_nBitDepth = imageres.asGetBitDepth();
    this->m_ImageSize = imageres.asGetImageSize();
    this->m_nFrameCount = imageres.asGetFrameCount();
}

void AsImageRes::asCopyImageDataCache( const AsImageRes& oldImage )
{
    m_ImageData = oldImage.asGetImageDataCache();
}

const QByteArray& AsImageRes::asGetImageDataCache() const
{
    return m_ImageData;
}

AsImageRes::~AsImageRes()
{

}

QHash<QString, quint16>& AsImageRes::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsImageRes::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
        HashProperties.insert( "asOriginalType", AsImageRes::AS_PROPERTY_ORIGINALTYPE );
        HashProperties.insert( "asOriginalFilename", AsImageRes::AS_PROPERTY_ORIGINALFILENAME );
        
        // From AsImageRes
        HashProperties.insert( "asBitDepth", AsImageRes::AS_PROPERTY_BITDEPTH );
        HashProperties.insert( "asImageSize", AsImageRes::AS_PROPERTY_IMAGESIZE );
        HashProperties.insert( "asFrameCount", AsImageRes::AS_PROPERTY_FRAMECOUNT );
    }

    return HashProperties;
}

void AsImageRes::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

bool AsImageRes::asUsesDataFile( void )
{
    // Images always use a separate data file for their data.
    return true;
}


const QByteArray& AsImageRes::asGetHashData( void )
{
    return m_HashData;
}

bool AsImageRes::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsImageRes::asComputeHashData( void )
{
    m_HashData = m_ImageData;
    m_bHashDataDirty = false;
}

bool AsImageRes::asIsImageDataValid()
{
    int reqSize = 0;
    if( m_nBitDepth == 8 )
    {
        reqSize = ( m_ImageSize.width() * m_ImageSize.height() ) + PALETTE_SIZE;
    }
    else
    {
        //32 bit image
        reqSize = m_ImageSize.width() * m_ImageSize.height() * 4;
    }
    if( m_ImageData.size() < reqSize )
    {
        return false;
    }
    return true;
}

unsigned int AsImageRes::asGetBitDepth( void ) const
{
    return m_nBitDepth;
}

void AsImageRes::asSetBitDepth( unsigned int nBitDepth )
{
    m_nBitDepth = nBitDepth;
    m_bHashDataDirty = true;
}

const QSize& AsImageRes::asGetImageSize( void ) const
{
    return m_ImageSize;
}

void AsImageRes::asSetImageSize( QSize& imageSize )
{
    m_ImageSize = imageSize;
    m_bHashDataDirty = true;
}

unsigned int AsImageRes::asGetFrameCount( void ) const
{
    return m_nFrameCount;
}

void AsImageRes::asSetFrameCount( unsigned int nFrameCount )
{
    m_nFrameCount = nFrameCount;
    m_bHashDataDirty = true;
}

const QPixmap * AsImageRes::asConstructImage()
{
    QByteArray dummyPal;
    return asConstructImage(dummyPal, false);
}

const QPixmap * AsImageRes::asConstructImage(QByteArray& instancePal, bool bTransparent, const QColor& transparentColor,
    QColor * pNewTransparentColor, bool * pbImageIsNotTransparent)
{
    bool bFoundTransparency = false;

    // First, lets check if we have already created this image.
    // int nImageIndex = this->asIndex( bTransparent, nAlpha );
	QPixmap *pPixmap = NULL;
	if( !bTransparent )
	{
        QHash< QByteArray, QPixmap *>::iterator have = m_Images.find( instancePal );
        if( have != m_Images.end() )
        {
		    pPixmap = have.value();
	    }
	}
	else
	{
        QHash< QByteArray, QPixmap *>::iterator have = m_transparentImages.find( instancePal );
        if( have != m_transparentImages.end() )
        {
		    pPixmap = have.value();
        }
	}
    if ( pPixmap != NULL )
    {   //qDebug() << " AsImageRes::asConstructImage found previous pixmap in QHash, returning it";
        return pPixmap;
    }

    /* Currently does not handle 32 bit transparent
       basically the whole thing needs to be refactored
       there is too much data being copied over and 
       a redesign needs to be done. */

    // For now we only handle 8 bit and 32 bit
    if ( m_nBitDepth != 8  && m_nBitDepth != 32 )
    {
        return NULL;
    }

    // OK, so we need to create this version of the image.
//	QImage image( this->m_ImageSize, QImage::Format_ARGB32 );
//
//	if( image.isNull() )
//	{
//		return NULL;
//	}

    QColor transColor = transparentColor;

    if( m_nBitDepth == 8 )
    {
     
        // First we set a pointer to the start of the raw data.
        /* Ate - need to get the pointer back using constdata
        otherwise we get a detach and because we are not writing
        to the original data we will end up with a potentially
        large copy occuring in the detach. Use constdata call
        seems this compiler is not picking the right signature
        even if we assign the correct type on the lvalue. */

		const unsigned char * pPalette = 0;
		const unsigned char * pRawData = 0;

        int imageDataRequired = ( m_ImageSize.width() * m_ImageSize.height()) + PALETTE_SIZE;
        if( imageDataRequired <= m_ImageData.size() )
        {
		    if( instancePal.size() != PALETTE_SIZE )
		    {
			    pPalette =  (const unsigned char *) m_ImageData.constData();
			    pRawData =  pPalette + PALETTE_SIZE;
		    }
		    else
		    {
			    pPalette =  (const unsigned char *) instancePal.constData();
			    pRawData =  (const unsigned char *) m_ImageData.constData() + PALETTE_SIZE;
		    }
            
            // Now we loop through the raw data.  For each row we set a pointer to the 
            // start of the scanline in the target QImage.
            
            int nImageHeight = m_ImageSize.height();
            int nImageWidth = m_ImageSize.width();

            if (pNewTransparentColor != 0)
            {
                // Record  last pixel colour.
                
                const unsigned char * pLastPixel = pRawData + ((nImageHeight * nImageWidth) - 1);

                int index = *pLastPixel;

                const unsigned char * pColor =  pPalette + (index * BYTES_PER_COLOR);

                int red = (int) *pColor++;
                int green = (int) *pColor++;
                int blue = (int) *pColor;

             //   pNewTransparentColor->setRed(red);
              //  pNewTransparentColor->setGreen(green);
             //   pNewTransparentColor->setBlue(blue);
            }

            for (int row=0 ; row<nImageHeight ; ++row)
            {
				//quint32 *pTarget = reinterpret_cast< quint32 * >( image.scanLine( row ) );

                for (int column=0 ; column<nImageWidth; ++column)
                {
                    int index = *pRawData;
                    const unsigned char *pColor =  pPalette + ( index * BYTES_PER_COLOR );
                    int red = ( int )*pColor++;
                    int green = ( int )*pColor++;
                    int blue = ( int )*pColor;

                    ++pRawData;

                    // Here, we can write the alpha channel even if the image is an RGB type
                    // rather than an ARGB type since an RGB type still has an alpha channel
                    // and is just 0xffRRGGBB.  The renderer will use the format flag and
                    // will ignore the alpha channel.
                    if ( index == 0 && bTransparent )
                    {
                       // *pTarget++ = qRgba( red, green, blue, TRANSPARENT );

                        bFoundTransparency = true;
                    }
                    else
                    {
                       // *pTarget++ = qRgba( red, green, blue, OPAQUE );
                    }
                }
            }
        }
        else
        {
            QFile file(":\redx.tif");
            file.open(QIODevice::ReadOnly);
            QByteArray arr = file.readAll();
//            QImage tempImg;
//            tempImg.loadFromData( arr );
//            file.close();
//			image = QImage( tempImg.scaled( m_ImageSize ) );
            m_nBitDepth = 32;
        }

    } // 8 bit
    else 
    { // 32 bit
        // nasty. Totally needs relooking at!!!
	//	memcpy( image.scanLine(0) , m_ImageData.constData() , m_ImageData.size());

        // Transparency...

        
    } // 32 bit

    // Now we convert the QImage to a QPixmap, keep the QPixmap and 
    // delete the QImage.

    return pPixmap;
}


void AsImageRes::asInsertPixmapIntoHash( QHash< QByteArray, QPixmap *> & theHash, const QByteArray & instancePal, QPixmap *pPixmap )
{
    QHash< QByteArray, QPixmap *>::iterator have = theHash.find( instancePal );
    if( have != theHash.end() )
    {

    }

    theHash.insert( instancePal, pPixmap );
}


const QPixmap * AsImageRes::asConstructImage( QByteArray& instancePal, QByteArray& rawImage, bool bTransparent,
    const QColor& transparentColor, QColor * pNewTransparentColor, bool * pbImageIsNotTransparent)
{
    m_ImageData = rawImage;
    return asConstructImage( instancePal, bTransparent, transparentColor, pNewTransparentColor, pbImageIsNotTransparent);
}

const QPixmap & AsImageRes::asGetImage( QByteArray& instancePal, bool bTransparent, const QColor& transparentColor )
{
    const QPixmap *pPixmap = asConstructImage( instancePal, bTransparent, transparentColor );
    return *pPixmap;
}

bool AsImageRes::asIsPixelTransparent( const QPoint & pos, bool transparent, const QColor& transparentColor )
{
    int x = pos.x();
    int y = pos.y();

    if( x < 0 ) x = 0;
    if( x > this->m_ImageSize.width() - 1 )  x = this->m_ImageSize.width() - 1;

    if( y < 0 ) y = 0;
    if( y > this->m_ImageSize.height() - 1 ) y = this->m_ImageSize.height() - 1;

    if( this->m_nBitDepth == 8 )
    {
        if ( !transparent )
            return false;

        const unsigned char *pPalette =  (const unsigned char *) m_ImageData.constData();
        const unsigned char *pRawData =   pPalette + PALETTE_SIZE;
        pRawData += (( m_ImageSize.width() * y) + x );
        int index = *pRawData;
        if( index == 0 )
            return true; 
        else 
            return false;
    }
    else
    {
        int pos = (( m_ImageSize.width() * y ) + x ) * 4;
        if( m_ImageData.size() > pos )
        {
            const unsigned char *pRawData =  (const unsigned char *) m_ImageData.constData();
            pRawData += pos;
            int blue = ( int )*pRawData++;
            int green = ( int )*pRawData++;
            int red = ( int )*pRawData++;
            int alpha = ( int ) *pRawData;

          //  QColor theColor( red, green, blue );

           // if( ( theColor == transparentColor && transparent ) || alpha == 0 )
                return true; 
           // else
              //  return false;
        }
        else
        {
            return false;
        }

    }

    return false;

}

bool AsImageRes::asSaveImage( const QString & fileName )
{
    return false;
    // For now we only handle 8 bit images.
//    if ( this->m_nBitDepth != 8 )
//    {
//        return false;
//    }
//
////   QImage *pImage = 0;
////   pImage = new QImage( this->m_ImageSize, QImage::Format_Indexed8 );
//
//   const unsigned char *pPalette =  (const unsigned char *) m_ImageData.constData();
//   const unsigned char *pRawData =  pPalette + PALETTE_SIZE;
//
//   pImage->setColorCount( 256 );
//
//   // set pallete
//   for( int p = 0 ; p < 256 ; ++ p )
//   {
//       int red =  ( int ) *pPalette++;
//       int green = (int ) *pPalette++;
//       int blue = ( int ) *pPalette++;
//       pImage->setColor( p , qRgb( red, green , blue ) );
//   }
//
//   // need images to be 32 bit aligned. but we can copy one row at a time using memcpy
//   // the extra bytes are just padding. Our qbytearray will not be aligned in the 8
//   // bit case
//   for ( int row = 0 ; row < m_ImageSize.height() ; ++row )
//   {
//        uchar *pTarget = pImage->scanLine(row );
//        memcpy( pTarget , pRawData , m_ImageSize.width() );
//        pRawData += m_ImageSize.width();
//   }
//
//   QByteArray ba;
//   QBuffer buffer(&ba);
//   buffer.open(QIODevice::ReadWrite);
//   pImage->save(&buffer, "BMP");
//
//   // single write of bitmap data to file.
//   QFile file(fileName);
//   file.open(QIODevice::WriteOnly);
//   QDataStream fileStream(&file);
//   int numBytes = fileStream.writeRawData(buffer.data(), buffer.size());
//
//   file.close();
//   buffer.close();
//
//   bool res = false;
//
//   if ( numBytes > 0 )
//     res = true;
//
//   delete pImage;
///*
//    QFile fOut( fileName + ".ba" );
//    fOut.open( QIODevice::WriteOnly );
//    QDataStream d( &fOut );
//    d << this->m_ImageSize;
//    d << this->m_nBitDepth;
//    d << this->m_nFrameCount;
//    d << this->m_ImageData;
//    fOut.close();
//*/
//   return res;
}

/*
bool AsImageRes::asLoadImage( const QByteArray& data )
{
    if ( m_bLoaded )
    {
        return true;
    }

    QImage image;
    if ( !image.loadFromData( data ) )
    {
        return false;
    }

    return this->asLoadImage( image );
}
*/

bool AsImageRes::asLoadScaledImage( const QString & fileName, const QSize& size  )
{
    if ( m_bLoaded )
    {
        return true;
    }
    
    // single read of bitmap data to file. 
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QByteArray arr = file.readAll();

    return true;
}

bool AsImageRes::asLoadImage( const QString & fileName, bool bMakeTransparent, bool /* bFromRes */, const QColor& transparentColor )
{
    if ( m_bLoaded )
    {
        return true;
    }

    
    // single read of bitmap data to file. 
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QByteArray arr = file.readAll();
 
   // QImage image;
//    if ( !image.loadFromData( arr ) )
//    {
//        return false;
//    }
//
//    file.close();
//
//    QColor transCol = transparentColor;
//
//    return this->asLoadImage( image, transCol, bMakeTransparent );
    return true;
}









QColor AsImageRes::asGetComputedTransparentColor( void ) const
{
	return m_TransparentColor;
}

const Json::Value &AsImageRes::asResourceSerialized()
{
    Variant var = m_properties.value(AsEnumProperty::AS_PROPERTY_ORIGINALFILENAME);
    if(var.type == VariableType ::Q_STRING&& var.value){
        m_resourceJsonObject["imageUrl"]=static_cast<QString*>(var.value)->toStdString();
    }
   return m_resourceJsonObject;
}

/**
 *  Replaces current image, if any, with the one passed in 'newImageFilename'.
 *  
 *  @return true if successful else false
 *  @param newImageFilename filename of new image with path
 *  @param setFilename if true sets the resource attributes filename and filepath to newImageFilename.
 *      defaults to false.
 */


/**
 *  Replaces current image, if any, with the one passed in 'newImage'.  
 *  
 *  @return true if successful else false
 *  @param newImage QImage containing new image
 */


// Transparency data is valid if colourLastPixel is set to a valid colour.


