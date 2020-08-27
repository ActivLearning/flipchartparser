/****************************************************************************
** Copyright 2006 Promethean Technologies Group Limited
****************************************************************************/
// Defines the AstextRes class.

#ifndef ASTEXTRES_H
#define ASTEXTRES_H

#include <QObject>
#include <QString>

#include <QHash>

#include "asresource.h"
#include "../objects/qcolor.h"
#include <QSizeF>
//#include "astextrun.h"
//#include "astextrunarray.h"
//#include "asrtftohtml.h"

#define DEFAULT_DPI_X 96
#define DEFAULT_DPI_Y 96

class AsFactory;

/**
 * Represents a TextRes resource object in a flipchart
 *
 * \see AsText
 */
class AsTextRes : public AsResource
{
Q_PROPERTY( AsTextRunArray asTextRuns READ asGetTextRunList WRITE asSetTextRunList )       
Q_PROPERTY( QString asText READ asGetText WRITE asSetText )
Q_PROPERTY( AsEnumTextType asTextType READ asGetTextType WRITE asSetTextType )
Q_PROPERTY( QString asOriginalText READ asGetOriginalText WRITE asSetOriginalText )
Q_PROPERTY( AsEnumTextType asOriginalTextType READ asGetOriginalTextType WRITE asSetOriginalTextType )
Q_PROPERTY( int asDPIX READ asGetDPIX WRITE asSetDPIX )
Q_PROPERTY( int asDPIY READ asGetDPIY WRITE asSetDPIY )
//Q_PROPERTY( QString asFontFamily READ asGetDefaultFontFamily WRITE asSetDefaultFontFamily )
//Q_PROPERTY( int asDefaultPointSize READ asGetDefaultFontSize WRITE asSetDefaultFontSize )
//Q_PROPERTY( qreal asLineWrapWidth READ asGetLineWrapWidth WRITE asSetLineWrapWidth )
Q_PROPERTY( qreal asConversionOffset READ asGetConversionOffset WRITE asSetConversionOffset )
Q_ENUMS(AsEnumTextType)

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        // From AsTextRes...
        AS_PROPERTY_TEXTRUNS,
        AS_PROPERTY_TEXT,
        AS_PROPERTY_TEXT_TYPE,
        AS_PROPERTY_ORIGINAL_TEXT,
        AS_PROPERTY_ORIGINAL_TEXT_TYPE,
        AS_PROPERTY_DPIX,
        AS_PROPERTY_DPIY,
		AS_PROPERTY_CONV_OFFSET
    };

    enum AsEnumTextType
    {
        AS_V2_ALLTEXT_RTF,
        AS_V2_Q3_HTML,
        AS_INSPIRE_QT4_HTML,
        AS_INSPIRE_PLAIN
    };


    AsTextRes( AsFactory * );
    virtual ~AsTextRes();

    AsTextRes( const AsTextRes& );
    void operator= ( const AsTextRes& );

    // Interface..
    const QByteArray& asGetHashData( void ) ;
    bool asIsHashDataDirty( void );
    void asComputeHashData( void );

    // Properties.
    void asResetPropertyIndex( void );

    const QString& asGetText( void ) const;
    void asSetText( const QString&, bool bSizeTopFit = false );

    const AsEnumTextType & asGetTextType( void ) const;
    void asSetTextType( AsEnumTextType );

    const QString& asGetOriginalText( void ) const;
    void asSetOriginalText( const QString& );

    const AsEnumTextType & asGetOriginalTextType( void ) const;
    void asSetOriginalTextType( AsEnumTextType );

    const qreal & asGetConversionOffset( void ) const;
    void asSetConversionOffset( qreal );
        qreal asGetAndResetConversionOffset( void );

//    // TextRuns
//    void asBuildAddTextRun(const QPointF & TextPos,
//                            const QString & Text ,
//                            const QString & FontFamily ,
//                            const qreal & FontSize ,
//                            const int & FontWeight ,
//                            const bool & Italic,
//                            const bool & UnderLine,
//                            const bool & Strikeout ,
//                            const QColor & TextColor,
//							AsTextRun::AsEnumTextListFormat bulletStyle,
//							QRectF bulletPosition );
 //   const AsTextRunArray & asGetTextRunList ( void ) const;
//	void asSetTextRunList( AsTextRunArray& );
    void asImportText( const QString &, AsEnumTextType );
    void asSetDPIX(const int &);
    void asSetDPIY(const int &);
    const int & asGetDPIX( void ) const;
    const int & asGetDPIY( void ) const;
    const QString & asGetDefaultFontFamily() const;
    void asSetDefaultFontFamily(const QString &);
    const int & asGetDefaultFontSize() const;
    void asSetDefaultFontSize(const int &);
    void asCreateTextRuns( bool bAdjustHeightToFit = true, bool     bForceWidth = false );

    void asSetDefaultTextColor( const QColor& );
    const QColor& asGetDefaultTextColor( void ) const;

    QString asGetWordAtPosition(const QPointF &);

    void asSetBounds( const QSizeF& );
    const QSizeF& asGetBounds() const;

//    AsRectF asCalculateBoundingRect();

    void asCopy( const AsTextRes& );
    
    void asCreateBoundingRects();

	static QString asModifyFSInRtf( QString &, qreal scale );
	static QString asModifyFSInHTML( QString &, qreal scale );

	void asSetFrameWidth(int);
	void asSetFrameHeight(int);

	void asSetMisspelltWordOriginalColorList(const QHash<QString, QColor>& misspelltWords);
	const QHash<QString, QColor>& asGetMisspelltWordOriginalColorList();

	bool asIsTextRightToLeft();

private:
    void asInitArabicCharacters();
    bool asIsArabicChar( QChar character );

    static QHash<QString, quint16>& m_lProperties( void );

	//bool asIsThereRightToLeftTextInTextRunArray( AsTextRunArray & asTextRunArray );
	//void asShuffleTextRunsToLeftWRTZeroXPos( AsTextRunArray & asTextRunArray );

  //  void asSwapBrackets( QList<AsTextRun*>* pTextRuns );

 //   AsTextRunArray m_CachedTextRuns;

    QString m_sText;
    AsEnumTextType m_TextType;

    QString m_sOriginalText;
    AsEnumTextType m_OriginalTextType;
    
    int m_nDPIX;
    int m_nDPIY;

  //  AsRTFtoHTML m_RTFtoHTMLConverter;

    QString m_sDefaultFontFamily;
    int m_nDefaultFontSize;
    QColor m_DefaultTextColor;

    QSizeF m_bounds;
	qreal m_topOffset;
	int m_nFrameWidth;
	int m_nFrameHeight;

	static QString m_HighlightStartTag;
	static QString m_HighlightEndTag;	

	QHash<QString, QColor> m_MisspelltWords;	
};

#endif // ASTEXTRES_H
