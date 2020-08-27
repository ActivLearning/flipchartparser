/** @file astextrun.h
 * Responsible for maintaining text items.
 * Copyright (C) 2006-2010 Promethean Limited. All Rights Reserved.
 */

#ifndef ASTEXTRUN_H
#define ASTEXTRUN_H


#include "asobject.h"
#include "../dataStruct/aspointfarrayarray.h"
#include "../dataStruct/asrectf.h"

/**
 * Represents a TextRun property in a flipchart
 */
class AsTextRun : public AsObject
{
//Q_OBJECT
//Q_PROPERTY( AsRectF asBoundingRect READ asGetBoundingRect WRITE asSetBoundingRect )
//Q_PROPERTY( QPointF asTextPos READ asGetTextPos WRITE asSetTextPos )
//Q_PROPERTY( QColor asTextColor READ asGetTextColor WRITE asSetTextColor )
//Q_PROPERTY( QString asText READ asGetText WRITE asSetText )
//Q_PROPERTY( QString asFontFamily READ asGetFontFamily WRITE asSetFontFamily )
//Q_PROPERTY( double asFontSize READ asGetFontSize WRITE asSetFontSize )
//Q_PROPERTY( int asFontWeight READ asGetFontWeight WRITE asSetFontWeight )
//Q_PROPERTY( bool asFontItalic READ asIsItalic WRITE asSetItalic )
//Q_PROPERTY( bool asFontUnderline READ asIsUnderline WRITE asSetUnderline )
//Q_PROPERTY( bool asFontStrikeout READ asIsStrikeout WRITE asSetStrikeout )
//Q_PROPERTY( AsPointFArrayArray asPolygonList READ asGetPolygonList WRITE asSetPolygonList )
//Q_PROPERTY( AsEnumTextListFormat asBulletType READ asGetBulletType WRITE asSetBulletType )
//Q_PROPERTY( QRectF asBulletPosition READ asGetBulletPosition WRITE asSetBulletPosition )
//Q_PROPERTY( QString asBulletText READ asGetBulletText WRITE asSetBulletText )
//Q_PROPERTY( bool asMisspelltWord READ asIsMisspelltWord WRITE asSetMisspelltWord )
//Q_ENUMS( AsEnumTextListFormat )

public:
    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsTextRun...
        AS_PROPERTY_BOUNDING_RECT,
        AS_PROPERTY_TEXTPOS,
        AS_PROPERTY_TEXTFONT,
        AS_PROPERTY_TEXTCOLOR,
        AS_PROPERTY_TEXT,
        AS_PROPERTY_FONTFAMILY,
        AS_PROPERTY_FONTSIZE,
        AS_PROPERTY_FONTWEIGHT,
        AS_PROPERTY_FONTITALIC,
        AS_PROPERTY_FONTUNDERLINE,
        AS_PROPERTY_FONTSTRIKEOUT,
        AS_PROPERTY_POLYGONLIST,
        AS_PROPERTY_BULLETTYPE,
        AS_PROPERTY_BULLETPOSITION,
        AS_PROPERTY_BULLETTEXT,
        AS_PROPERTY_MISSPELLTWORD
    };

    enum AsEnumTextListFormat
    {
        AS_TEXT_LISTUNKNOWN = 0,
        AS_TEXT_LISTDISC = -1,
        AS_TEXT_LISTCIRCLE = -2,
        AS_TEXT_LISTSQUARE = -3,
        AS_TEXT_LISTDECIMAL = -4,
        AS_TEXT_LISTLOWERALPHA = -5,
        AS_TEXT_LISTUPPERALPHA = -6
    };

    AsTextRun( AsFactory * );
    AsTextRun();
    virtual ~AsTextRun();
    AsTextRun( const AsTextRun& );
    void operator= ( const AsTextRun& );
    bool operator== ( const AsTextRun& );


    void asSetTextRun( const QPointF & TextPos,
                        const QString & Text ,
                        const QString & FontFamily ,
                        const qreal & FontSize ,
                        const int & FontWeight ,
                        const bool & Italic,
                        const bool & UnderLine,
                        const bool & Strikeout ,
                        const QColor & TextColor,
                        AsTextRun::AsEnumTextListFormat bulletStyle,
                        QRectF bulletPosition);

    const QFont & asGetCachedFont ( void ) const;
    void asSetCachedFont( const QFont & );

    //generate a painter path from the text
    void asBuildPathFromPolygons();
    bool asBuildPainterPath() const;
  //  const QPainterPath & asGetPainterPath() const ;

    // Properties.
    void asResetPropertyIndex( void );

    const QColor & asGetTextColor( void ) const;
    const QPointF & asGetTextPos( void ) const;
    const QString & asGetText( void ) const;
    const QString & asGetFontFamily( void ) const;
        double asGetFontSize( void ) const;
        int asGetFontWeight( void ) const;
        bool asIsItalic( void ) const;
        bool asIsUnderline( void ) const;
        bool asIsStrikeout( void ) const;

    void asSetTextColor( QColor &colour );
    void asSetTextPos( const QPointF &pos );
    void asSetText( QString &text );
    void asSetFontFamily( QString &fontFamily );
    void asSetFontSize( double fontSize );
    void asSetFontWeight( int fontWeight );
    void asSetItalic( bool italic );
    void asSetUnderline( bool underline );
    void asSetStrikeout( bool strikeout );

        bool asIsMisspelltWord(void)const ;
    void asSetMisspelltWord(bool misspellt);

    int asGetLineNumber();
    void asSetLineNumber( int );

    const AsPointFArrayArray & asGetPolygonList() const;
    void asSetPolygonList( AsPointFArrayArray & );

    const AsRectF & asGetBoundingRect() const;
    void asSetBoundingRect( AsRectF &);

    void asCalculateBoundingRect(const QSizeF& bounds = QSizeF());

    QByteArray asToByteArray() const;

        AsEnumTextListFormat asGetBulletType()const;
    void asSetBulletType(AsEnumTextListFormat type);

    void asSetBulletText(const QString& bulletText);
    const QString& asGetBulletText()const;

    const QRectF & asGetBulletPosition() const;
    void asSetBulletPosition( QRectF & rect);
//    void asCalculateBulletPosition(const QSizeF& bounds = QSizeF(), const QFont& font = QFont(), bool rightToLeft = false );

    qreal asGetSnapOffset();

    QString typeName() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

private:

    static QHash<QString, quint16>& m_lProperties( void );
    void asCopy( const AsTextRun& );

    QString m_sText;
    QString m_sFontFamily;
    int m_nLineNumber;
    Qt::AlignmentFlag m_eAlignment;
    QPointF m_textPos;

    qreal m_nFontSize;
    int  m_nFontWeight;
    bool m_bFontItalic;
    bool m_bFontUnderline;
    bool m_bFontStrikeOut;
    bool m_bMisspelltWord;
   // QTextCharFormat::VerticalAlignment m_eValign; // subscript/super/normal
  //  QColor m_cTextColor;
 //   mutable QFont m_fCachedFont;
    mutable bool m_bTextRunDirty;
   // mutable QPainterPath m_painterPath;
    mutable AsPointFArrayArray m_polygonList;

    AsEnumTextListFormat m_bulletStyle;
    QRectF m_bulletPosition;
    QString m_bulletText;

    AsRectF m_boundingRect;

};

#endif
