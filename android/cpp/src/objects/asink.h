// Defines the AsInk class.
// (c)2006 Promethean Technologies Group Ltd.

#ifndef ASINK_H
#define ASINK_H

#include <QMetaType>
#include "qcolor.h"
#include "asobject.h"
//#include <QPen>
//#include <QBrush>



class AsFactory;
class AsBrushDesc;

/**
 * Represents an Ink property in a flipchart
 */
class AsInk : public AsObject
{


private:

    Q_PROPERTY( AsEnumInkType asInkType READ asGetInkType WRITE asSetInkType EDITABLE true )
    Q_PROPERTY( unsigned int asPenWidth READ asGetPenWidth WRITE asSetPenWidth EDITABLE true )
    Q_PROPERTY( AsEnumPenStyle asPenStyle READ asGetPenStyle WRITE asSetPenStyle EDITABLE true )
    Q_PROPERTY( AsEnumPenCapStyle asPenCapStyle READ asGetPenCapStyle WRITE asSetPenCapStyle EDITABLE true )
    Q_PROPERTY( AsEnumPenJoinStyle asPenJoinStyle READ asGetPenJoinStyle WRITE asSetPenJoinStyle EDITABLE true )
    Q_PROPERTY( QColor asPenColor READ asGetPenColor WRITE asSetPenColor EDITABLE true )
    Q_PROPERTY( AsEnumBrushStyle asBrushStyle READ asGetBrushStyle WRITE asSetBrushStyle EDITABLE true )
    Q_PROPERTY( QColor asBrushColor READ asGetBrushColor WRITE asSetBrushColor EDITABLE true )
    Q_PROPERTY( AsEnumBackgroundMode asBackgroundMode READ asGetBackgroundMode WRITE asSetBackgroundMode EDITABLE true )
    Q_PROPERTY( QColor asBackgroundColor READ asGetBackgroundColor WRITE asSetBackgroundColor EDITABLE true )
    Q_PROPERTY( QColor asBrushColor2 READ asGetBrushColor2 WRITE asSetBrushColor2 EDITABLE true )
    Q_PROPERTY( AsEnumBrushGradientType asBrushGradientType READ asGetBrushGradientType WRITE asSetBrushGradientType EDITABLE true )

    Q_ENUMS( AsEnumInkType )
    Q_ENUMS( AsEnumPenStyle )
    Q_ENUMS( AsEnumPenCapStyle )
    Q_ENUMS( AsEnumPenJoinStyle )
    Q_ENUMS( AsEnumBrushStyle )
    Q_ENUMS( AsEnumBackgroundMode )
    Q_ENUMS( AsEnumColors )
    Q_ENUMS( AsEnumBrushGradientType )

public:

    enum AsEnumProperty
    {
        // From AsObject...
                AS_PROPERTY_DATETIMECREATED = 1,

        // From AsInk...
                AS_PROPERTY_INKTYPE = 2,
        AS_PROPERTY_PENWIDTH = 3,
        AS_PROPERTY_PENSTYLE = 4,
        AS_PROPERTY_PENCAPSTYLE = 5,
        AS_PROPERTY_PENJOINSTYLE = 6,
        AS_PROPERTY_PENCOLOR = 7,
        AS_PROPERTY_BRUSHSTYLE = 8,
        AS_PROPERTY_BRUSHCOLOR = 9,
        AS_PROPERTY_BACKGROUNDMODE = 10,
        AS_PROPERTY_BACKGROUNDCOLOR = 11,
        UNUSED_AS_PROPERTY_BRUSHIMAGE_UNUSED = 12,
        AS_PROPERTY_BRUSHCOLOR2 = 13,
        AS_PROPERTY_BRUSHGRADIENTTYPE = 14,
        // Next Proprerty ID = 15.
    };

    enum AsEnumInkType
    {
        AS_INKTYPE_NORMAL = 0,
        AS_INKTYPE_HIGHLIGHT,
        AS_INKTYPE_MASK
    };

    enum AsEnumColors
    {
        AS_COLOR_ALL = 0,
        AS_COLOR_PEN,
        AS_COLOR_BRUSH,
        AS_COLOR_BACKGROUND
    };


    // The following enum values must align with the equivalent Qt namespace
    // enums.  This is so we can return a reference to the brush and to the pen
    // by just copying these values directly into the QPen and QBrush properties.
    // We cannot have the Qt namespace enums as our property types because they
    // don't stream even when declared with Q_ENUM( ... ).
    enum AsEnumPenStyle
    {
        AS_PENSTYLE_NONE = 0,
        AS_PENSTYLE_SOLIDLINE,
        AS_PENSTYLE_DASHEDLINE,
        AS_PENSTYLE_DOTLINE,
        AS_PENSTYLE_DASHDOTLINE,
        AS_PENSTYLE_DASHDOTDOTLINE
    };

    enum AsEnumPenCapStyle
    {
        AS_PENCAPSTYLE_FLAT = 0x0,
        AS_PENCAPSTYLE_SQUARE = 0x10,
        AS_PENCAPSTYLE_ROUND = 0x20
    };

    enum AsEnumPenJoinStyle
    {
        AS_PENJOINSTYLE_MITER = 0,
        AS_PENJOINSTYLE_BEVEL = 0x40,
        AS_PENJOINSTYLE_ROUND = 0x80
    };

    enum AsEnumBrushStyle
    {
        AS_BRUSHSTYLE_NONE = 0,
        AS_BRUSHSTYLE_SOLID,
        AS_BRUSHSTYLE_DENSE1,
        AS_BRUSHSTYLE_DENSE2,
        AS_BRUSHSTYLE_DENSE3,
        AS_BRUSHSTYLE_DENSE4,
        AS_BRUSHSTYLE_DENSE5,
        AS_BRUSHSTYLE_DENSE6,
        AS_BRUSHSTYLE_DENSE7,
        AS_BRUSHSTYLE_HORIZONTAL,
        AS_BRUSHSTYLE_VERTICAL,
        AS_BRUSHSTYLE_CROSS,
        AS_BRUSHSTYLE_BACKWARDDIAGONAL,
        AS_BRUSHSTYLE_FOWARDDIAGONAL,
        AS_BRUSHSTYLE_CROSSDIAGONAL,
        AS_BRUSHSTYLE_TEXTURE = 24,
        AS_BRUSHSTYLE_GRADIENT = 25
    };

    enum AsEnumBackgroundMode
    {
        AS_BACKGROUNDMODE_TRANSPARENT = 0,
        AS_BACKGROUNDMODE_OPAQUE
    };

    enum AsEnumBrushGradientType
    {
        AS_BRUSHGRADIENT_NONE		= 0,
        AS_BRUSHGRADIENT_VERTICAL	= 1,
        AS_BRUSHGRADIENT_HORIZONTAL = 2,
        AS_BRUSHGRADIENT_DIAGONAL1	= 3,
        AS_BRUSHGRADIENT_DIAGONAL2	= 4,
        AS_BRUSHGRADIENT_RADIAL		= 5
    };

    // Construction and destruction.
    AsInk();
//    AsInk( const AsInk& );
    virtual ~AsInk();

//    void operator= ( const AsInk& );

//    bool operator== ( const AsInk& );
//
//    void asCopy( const AsInk& );

    // Interface.
//    const QPen& asGetPen( void );
//    const QBrush& asGetBrush( void );

    void asSetTranslucency(int nAlpha);

    // Properties.
    void asResetPropertyIndex( void );

    AsEnumInkType asGetInkType( void ) const;
    void asSetInkType( AsEnumInkType );

    unsigned int asGetPenWidth( void ) const;
    void asSetPenWidth( unsigned int );

    AsEnumPenStyle asGetPenStyle( void ) const;
    void asSetPenStyle( AsEnumPenStyle );

    AsEnumPenCapStyle asGetPenCapStyle( void ) const;
    void asSetPenCapStyle( AsEnumPenCapStyle );

    AsEnumPenJoinStyle asGetPenJoinStyle( void ) const;
    void asSetPenJoinStyle( AsEnumPenJoinStyle );

    const QColor& asGetPenColor( void ) const;
    void asSetPenColor( const QColor& );

    void asSetAlpha( AsEnumColors, int );

    AsEnumBrushStyle asGetBrushStyle( void ) const;
    void asSetBrushStyle( AsEnumBrushStyle );

    const QColor& asGetBrushColor( void ) const;
    void asSetBrushColor( const QColor& );

    const QColor& asGetBrushColor2( void ) const;
    void asSetBrushColor2( const QColor& );

    AsEnumBrushGradientType asGetBrushGradientType( void ) const;
    void asSetBrushGradientType( AsEnumBrushGradientType );

    AsEnumBackgroundMode asGetBackgroundMode( void ) const;
    void asSetBackgroundMode( AsEnumBackgroundMode );

    const QColor& asGetBackgroundColor( void ) const;
    void asSetBackgroundColor( const QColor& );

//    AsBrushDesc asGetBrushDesc() const;
//    void asSetBrushDesc( const AsBrushDesc& );
//
//    //WARNING - Brush image is not a streamable property.
//    const QImage& asGetBrushImage( void ) const;
//    void asSetBrushImage( const QImage& image );

    // alpha for brush. use this if you want to retrieve pixmaps alpha

    //int AsInk::asGetBrushAlpha( void );
    //int asGetBrushAlpha( void );

    static void asSetHighlighterAlpha( int alpha );

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override ;

    int getPropertyIdByName(QString name) const override;

private:
    // Property hash table.
    static QHash<QString, quint16>& m_lProperties( void );

    // Properties.
    AsEnumInkType m_InkType;
    unsigned int m_nPenWidth;
    AsEnumPenStyle m_PenStyle;
    AsEnumPenCapStyle m_PenCapStyle;
    AsEnumPenJoinStyle m_PenJoinStyle;
    QColor m_PenColor;
    AsEnumBrushStyle m_BrushStyle;
    QColor m_BrushColor;
    QColor m_BrushColor2;
    AsEnumBrushGradientType m_BrushGradientType;
    AsEnumBackgroundMode m_BackgroundMode;
    QColor m_BackgroundColor;

//    QImage m_BrushImage;

    // Computed...
//    QPen m_Pen;
    bool m_bPenDirty;
//    QBrush m_Brush;
    bool m_bBrushDirty;

    // highlight alpha value. Just a guess
    static int m_v3_HighLightAlpha;
};



#endif // ASINK_H
