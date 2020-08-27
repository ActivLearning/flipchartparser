// Defines the AsImageRes class.
// $Author: Paul Wareing.

#ifndef ASIMAGERES_H
#define ASIMAGERES_H

#include <QObject>
#include <QByteArray>
#include <QSizeF>

#include "../objects/qcolor.h"

#include <QHash>
#include <QVector>
#include <QBuffer>

#include "asresource.h"

class AsFactory;

/**
 * Represents an ImageRes resource object in a flipchart
 *
 * \see AsImage
 */
class AsImageRes : public AsResource
{
Q_PROPERTY( unsigned int asBitDepth READ asGetBitDepth WRITE asSetBitDepth )
Q_PROPERTY( QSize asImageSize READ asGetImageSize WRITE asSetImageSize )
Q_PROPERTY( unsigned int asFrameCount READ asGetFrameCount WRITE asSetFrameCount )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        // From AsImageRes...
        
        AS_PROPERTY_BITDEPTH,
        AS_PROPERTY_IMAGESIZE,
        AS_PROPERTY_FRAMECOUNT
    };

    AsImageRes( AsFactory * );
    virtual ~AsImageRes();

    AsImageRes( const AsImageRes& );
    void operator= ( const AsImageRes& );

    bool asUsesDataFile( void )override ;

    // Interface.
    const QPixmap * asConstructImage();
    const QPixmap * asConstructImage(QByteArray& instancePal, bool transparent, const QColor& transparentColor = QColor(),
        QColor * pNewTransparentColor = 0, bool * pbImageIsNotTransparent = 0);
    const QPixmap * asConstructImage(QByteArray&, QByteArray&, bool transparent, const QColor& transparentColor = QColor(),
        QColor * pNewTransparentColor = 0, bool * pbImageIsNotTransparent = 0);
    const QPixmap & asGetImage( QByteArray& instancePal, bool transparent, const QColor& transparentColor = QColor() );

    // Interface..
    const QByteArray& asGetHashData( void ) override ;
    bool asIsHashDataDirty( void )override ;
    void asComputeHashData( void )override ;
    bool asIsImageDataValid();

    // Properties.
    void asResetPropertyIndex( void );

    unsigned int asGetBitDepth( void ) const;
    void asSetBitDepth( unsigned int );

    const QSize& asGetImageSize( void ) const;
    void asSetImageSize( QSize& );

    unsigned int asGetFrameCount( void ) const;
    void asSetFrameCount( unsigned int );

	QColor asGetComputedTransparentColor( void ) const;

    bool asSaveImage( const QString & fileName );
    bool asLoadImage( const QString & fileName, bool bMakeTransparent = false, bool bFromRes = false, const QColor& transparentColor = QColor() );
    bool asLoadScaledImage( const QString & fileName, const QSize& size  );

    // Replaces current image, if any, with a new one.
    bool asReplaceImage( const QString & newImageFilename, bool setFilename = false );
    bool asReplaceImage( const QImage & newImage );

    /* Dont think we are using this anywhere. Need to discuss */

    //bool asLoadImage( const QByteArray& );

    bool asLoadImage( QImage&, QColor& transparentColor, bool bMakeTransparent = false );

    bool asIsPixelTransparent( const QPoint & pos, bool transparent, const QColor& transparentColor );

    bool asRedirectTransparentColor( const QColor& );
    bool asSetTransparentColor( const QColor&, QByteArray& instancePal );

    // swaps a color in the color table. Only works with palletized (ie. 8 bit) images, others will return false.
    bool asSwap8BitColorTableEntry( QByteArray* pal, const QColor& oldcolor, const QColor& newcolor );
    
    // swaps the color at the clicked position. For 8-bit images the color table is changed directly, 
    // for others all pixels are changed which have a similar color within a tolerance.
    bool asSwapColorAtPosition( QByteArray* pal, const QPoint& position, const QColor& color );
    bool asSwapColorAtPosition( const QPoint& position, const QColor& color, const int tolerance = 95 );

    void asCopyImageDataCache( const AsImageRes& oldImage );
    const QByteArray& asGetImageDataCache() const;

    QByteArray asGetPalette( void );

    void asValidTransparencyData(const QByteArray& alternativePalette, QColor& colourLastPixel);

protected:
    const Json::Value &asResourceSerialized() override;
private:
    void asCopy( const AsImageRes& );

    static QHash<QString, quint16>& m_lProperties( void );

    QByteArray m_ImageData;
    bool m_bLoaded;
    unsigned int m_nBitDepth;
    QSize m_ImageSize;
    unsigned int m_nFrameCount;
    
    /// Helper function to stop any memory leaks while inserting into the one of the image hashes.
    void asInsertPixmapIntoHash( QHash< QByteArray, QPixmap *> & theHash, const QByteArray & instancePal, QPixmap *pPixmap );
    
    /// Never directly add to these hash's always go through asInsertPixmapIntoHash()
    QHash< QByteArray, QPixmap *> m_Images;
	QHash< QByteArray, QPixmap *> m_transparentImages;   

	QColor m_TransparentColor;
};

#endif // ASIMAGERES_H
