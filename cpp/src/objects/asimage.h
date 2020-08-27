// Defines the AsImage class.
// $Author: Paul Wareing.

#ifndef ASIMAGE_H
#define ASIMAGE_H

#include <QMetaType>
#include <QObject>
#include "qcolor.h"
#include <QSizeF>

#include "asrenderable.h"


class AsFactory;
class AsImageRes;
/**
 * Represents an Image object in a flipchart
 */
class AsImage : public AsRenderable
{
Q_PROPERTY( unsigned int asResource READ asGetResource WRITE asSetResource )
Q_PROPERTY( bool asTransparent READ asGetTransparent WRITE asSetTransparent EDITABLE true )
Q_PROPERTY( QColor asTransparentColor READ asGetTransparentColor WRITE asSetTransparentColor EDITABLE true )
Q_PROPERTY( bool asTiled READ asGetTiled WRITE asSetTiled EDITABLE true )
Q_PROPERTY( AsEnumTileFit asTileFit READ asGetTileFit WRITE asSetTileFit EDITABLE true )
Q_PROPERTY( QSizeF asTileArea READ asGetTileArea WRITE asSetTileArea EDITABLE true )
Q_PROPERTY( bool asPickThrough READ asGetPickThrough WRITE asSetPickThrough EDITABLE true )
Q_PROPERTY( QByteArray asAlternativePalette READ asGetAltPalette WRITE asSetAltPalette )
Q_PROPERTY( bool asRewardSound READ asGetRewardSound WRITE asSetRewardSound EDITABLE true)
Q_PROPERTY( QString asRewardSoundLocation READ asGetRewardSoundLocation WRITE asSetRewardSoundLocation EDITABLE true)
Q_ENUMS( AsEnumTileFit )

public:

    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsRenderable...
        AS_PROPERTY_TRANSFORM = 2,
        AS_PROPERTY_TWIPS = 3,
        AS_PROPERTY_NAME = 4,
        AS_PROPERTY_KEYWORDS = 5,
        AS_PROPERTY_VISIBLE = 6,
        AS_PROPERTY_BOUNDINGRECT = 7,
        AS_PROPERTY_LAYER = 8,
        AS_PROPERTY_Z = 9,
        AS_PROPERTY_INK = 10,
        AS_PROPERTY_SCALEORIGIN = 11,
        AS_PROPERTY_ROTATEORIGIN = 12,
        AS_PROPERTY_CANMOVE = 13,
        AS_PROPERTY_CANSIZE = 14,
        AS_PROPERTY_CANROTATE = 15,
        AS_PROPERTY_CANBLOCK = 16,
        AS_PROPERTY_CANSNAP = 17,
        AS_PROPERTY_LOCKED = 18,
        AS_PROPERTY_SNAPBACK = 19,
        AS_PROPERTY_PATHPOINTER = 20,
        AS_PROPERTY_ROTATEABOUTPOINTER = 21,
        AS_PROPERTY_ROTATEPOINT = 22,
        AS_PROPERTY_ROTATEABOUT = 23,
        AS_PROPERTY_ROTATESTEP = 24,
        AS_PROPERTY_SNAPTOPOINTER = 25,
        AS_PROPERTY_SNAPPOINT = 26,
        AS_PROPERTY_SNAPTO = 27,
        AS_PROPERTY_CANCONTAIN = 28,
        AS_PROPERTY_CONTAINPOINTER = 29,
        AS_PROPERTY_CONTAINWORDS = 30,
        AS_PROPERTY_CONTAINRULE = 31,
        AS_PROPERTY_V2TYPE = 32,
        AS_PROPERTY_CONNECTORLIST = 33,
        AS_PROPERTY_LABEL = 34,
        AS_PROPERTY_QUESTIONITEM = 35,
        AS_PROPERTY_QUESTIONITEMID = 36,
		AS_PROPERTY_ALLOWSNAPBACK = 37,
        AS_PROPERTY_DRAGACOPY = 46,
        AS_PROPERTY_QUESTIONTAG = 47,
        AS_PROPERTY_REWARD_SOUND = 48,
        AS_PROPERTY_REWARD_SOUND_LOCATION = 49,
		AS_PROPERTY_ASYNCTESTTAG = 50,
        AS_PROPERTY_INTERACTMODE = 51,


        // From AsImage...
        AS_PROPERTY_RESOURCE = 38,
        AS_PROPERTY_TRANSPARENT = 39,
        AS_PROPERTY_TRANSPARENTCOLOR = 40,
        AS_PROPERTY_TILED = 41,
        AS_PROPERTY_TILEFIT = 42,
        AS_PROPERTY_TILEAREA = 43,
        AS_PROPERTY_PICKTHROUGH = 44,
		AS_PROPERTY_ALTERNATIVEPALETTE = 45

        // Next Property ID = 52
    };

    enum AsEnumTileFit
    {
        AS_TILEFIT_NONE = 0,
        AS_TILEFIT_BESTFIT,
        AS_TILEFIT_STRETCHFIT,
        AS_TILEFIT_CENTRE,
        AS_TILEFIT_TOPLEFT,
        AS_TILEFIT_TOPCENTRE,
        AS_TILEFIT_TOPRIGHT,
        AS_TILEFIT_LEFTCENTRE,
        AS_TILEFIT_RIGHTCENTRE,
        AS_TILEFIT_BOTTOMLEFT,
        AS_TILEFIT_BOTTOMCENTRE,
        AS_TILEFIT_BOTTOMRIGHT
    };

    // Construction and destruction
    AsImage();
    AsImage( AsFactory * );
    virtual ~AsImage();

    AsImage( const AsImage& );
    void operator= ( const AsImage& );

    bool operator== ( const AsImage& );

    bool asCheckHit(  const QPointF & worldPos )override ;
    
    // Properties
    void asResetPropertyIndex( void );

 //   unsigned int asGetResource( void ) const;
    void asSetResource( unsigned int );

    AsResource * asGetResourcePointer( void )override ;
    void asSetResource( AsResource * )override ;
    void asUnloadResource( void );

    bool asLoadResourceDataFile( const QString& filename, const QString& path )override ;

    bool asGetTransparent( void ) const;
    void asSetTransparent( bool );

    const QColor& asGetTransparentColor( void ) const;
    void asSetTransparentColor( QColor& );

    bool asGetTiled( void ) const;
    void asSetTiled( bool );

    AsEnumTileFit asGetTileFit( void ) const;
    void asSetTileFit( AsEnumTileFit );

    const QSizeF& asGetTileArea( void ) const;
    void asSetTileArea( QSizeF& );

    bool asGetPickThrough( void ) const;
    void asSetPickThrough( bool );

	const QByteArray& asGetAltPalette( void ) const;
	void asSetAltPalette( QByteArray& altPalette );

    // convenience functions for getting/setting global translucency values for pixmaps
    // we use an inker but more inutitive to go to the image and do it

    void asSetTranslucency( int translucency )override ;
    int asGetTranslucency( void )override ;

    virtual QString asGetNewObjectName(quint32 nIndex)override ;
    
    // swaps the color at the specified position. For 8-bit images the alt color palette is changed, 
    // for others all pixels are changed which have a similar color within a tolerance. 
    // (tolerance argument ignored for palettised images).
    bool asSwapColorAtPosition( const QPoint& position, const QColor& color, const int tolerance = 95 );

    bool asProcessTransparentColor( const QColor& color );

	bool asIsResourcePointerValid( void )override ;
    const QPixmap* asGetPixmap();
    QString getImagePath();

public:
    Json::Value &serialized() override;

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

    const Json::Value &asResourceSerialized() override;

private:
    void asConstruct( void );
    void asCopy( const AsImage& );

    static QHash<QString, quint16>& m_lProperties( void );

    unsigned int m_nResource;
    AsImageRes *m_pAsImageRes;

    bool m_bTransparent;
    QColor m_TransparentColor;
    bool m_bTiled;
    AsEnumTileFit m_nTileFit;
    QSizeF m_TileArea;
	QByteArray m_alternativePalette;
    bool m_bPickThrough;

    QString m_sResFilePath;
};

#endif // ASIMAGE_H
