// Defines the AsText class.
// $Author: Paul Wareing.

#ifndef ASTEXT_H
#define ASTEXT_H


#include <QString>
#include <QPointF>
#include <QList>
#include "asrenderable.h"
//#include "astextres.h"

class AsFactory;
class AsTextRes;
/**
 * Represents a Text object in a flipchart
 */
class AsText : public AsRenderable
{
Q_PROPERTY( unsigned int asResource READ asGetResource WRITE asSetResource )
Q_PROPERTY( unsigned int asQA READ asGetQA WRITE asSetQA )

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
        AS_PROPERTY_ASDRAGACOPY = 40,
        AS_PROPERTY_QUESTIONTAG = 41,
        AS_PROPERTY_DRAGACOPY = 42,
		AS_PROPERTY_ASYNCTESTTAG = 43,
        AS_PROPERTY_INTERACTMODE = 44,

        // From AsText...
        AS_PROPERTY_RESOURCE = 38,
        AS_PROPERTY_QA = 39

        // Next Property ID = 45
    };

    // Construction and destruction
    AsText( AsFactory * );
    virtual ~AsText();

    AsText( const AsText& );
    void operator= ( const AsText& );

    bool operator==( const AsText& );

    bool asCheckHit(  const QPointF & worldPos )override ;
    bool asCheckHitFine( const QPointF & worldPos, int & whichTextRun );
    // Properties
    void asResetPropertyIndex( void );

  //  unsigned int asGetResource( void ) const;
    void asSetResource( unsigned int );

    AsResource * asGetResourcePointer( void )override ;
    void asSetResource( AsResource * )override ;

    unsigned int asGetQA( void ) const;
    void asSetQA( unsigned int );

    void asEdit( void );
  //  void asCommit( const QString& , const QSizeF& size = QSizeF(0, 0), int = DEFAULT_DPI_X, int = DEFAULT_DPI_Y);
    void asCommit( void );

    void asReCalculateBoundingRect();
    void asScaleTextBy( const QPointF& factor,const bool maintainAspect = false );

	// replace text, keeping the format of the first text run
	void asReplaceText( const QString& text, bool bKeepBounds = true );

    // Last transform inverted hit pos.
    const QPointF& asLastInvertedHitPos( void ) const;

    virtual QString asGetNewObjectName(quint32 nIndex)override ;

	bool asIsResourcePointerValid( void )override ;

    void asReLayoutText();

    QString typeName() override;

signals:
	void asTextObjectDeleted(AsText *);

public:
    Json::Value &serialized() override;

protected:
    QString getPropertyNameById(int nID) override;

    int getPropertyIdByName(QString name) const override;

    const Json::Value &asResourceSerialized() override;

private:
    void asCopy( const AsText& );        

    static QHash<QString, quint16>& m_lProperties( void );

    bool asIsPlainTextEqual(const QString& otherPlainText);

    unsigned int m_nResource;
    AsTextRes *m_pAsTextRes;
    unsigned int m_nQA;
    
    // Cache of the last transform inverted hit pos.
    QPointF m_LastInvertedHitPos;
};

#endif // ASTEXT_H
