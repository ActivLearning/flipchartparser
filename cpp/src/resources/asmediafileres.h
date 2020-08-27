// Defines the AsMediaFileRes class.
// $Author: Paul Ellis.

#ifndef ASMEDIAFILERES_H
#define ASMEDIAFILERES_H

#include <QObject>

#include "asresource.h"

#define MAX_HASH_FILE_READ 10000

class AsFactory;
class AsFlipchart;

/**
 * Represents a MediaFileRes resource object in a flipchart
 *
 * \see AsMediaContainer
 */
class AsMediaFileRes : public AsResource
{
Q_PROPERTY( QString asMimeType READ asGetMimeType WRITE asSetMimeType )
Q_PROPERTY( bool asInternal READ asIsInternal WRITE asSetInternal )

public:
    static const QString AsInternalLinkedURI;
    static const QString AsInternalLinedFolder;

    enum AsEnumProperty
    {
        // From AsObject...
        AS_PROPERTY_DATETIMECREATED = 1,

        // From AsResource...
        AS_PROPERTY_ORIGINALTYPE,
        AS_PROPERTY_ORIGINALFILENAME,

        // From AsMediaFileRes...
        AS_PROPERTY_MIMETYPE,
		AS_PROPERTY_INTERNAL
    };

    AsMediaFileRes( AsFactory * );
    virtual ~AsMediaFileRes();

    // Interface..
    const QByteArray& asGetHashData( void ) ;
    bool asIsHashDataDirty( void );
    void asComputeHashData( void );
	bool asUsesDataFile( void );

    // Properties.
    void asResetPropertyIndex( void );

    const QString asGetMimeType( void ) const;
    void asSetMimeType( QString );

    bool asIsInternal( void ) const;
    void asSetInternal( bool );

    // Helper, Used this to get the location of the resource, it will test if internal or external.
    QString asGetSourceLocation( AsFlipchart *pFlipchart = NULL ) const;

    // True if the source internaly linked.
    bool asIsInternalyLinked() const;

    QString asGetDisplayName() const;


private:
    static QHash<QString, quint16>& m_lProperties( void );

    QString m_MimeType;
    bool m_bInternal;
};

#endif // ASMEDIAFILERES_H
