// Implements the AsMediaFileRes class.
// $Author: Paul Ellis.

#include "asmediafileres.h"
#include "../asfactory.h"
#include "asresourcemanager.h"
#include "../io/asnode.h"
#include <QVariant>
#include <QDir>



const QString AsMediaFileRes::AsInternalLinkedURI = "INTERNALY_LINKED://";
const QString AsMediaFileRes::AsInternalLinedFolder = "InternallyLinked";


AsMediaFileRes::AsMediaFileRes( AsFactory *pAsFactory ) : AsResource( pAsFactory )
{
    asSetType( AsObject::AS_OBJECT_MEDIAFILERES );
}

AsMediaFileRes::~AsMediaFileRes()
{
}

QHash<QString, quint16>& AsMediaFileRes::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsMediaFileRes::AS_PROPERTY_DATETIMECREATED );

        // From AsResource...
        HashProperties.insert( "asOriginalType", AsMediaFileRes::AS_PROPERTY_ORIGINALTYPE );
        HashProperties.insert( "asOriginalFilename", AsMediaFileRes::AS_PROPERTY_ORIGINALFILENAME );
        
        // From AsMediaFileRes
        HashProperties.insert( "asMimeType", AsMediaFileRes::AS_PROPERTY_MIMETYPE );
        HashProperties.insert( "asInternal", AsMediaFileRes::AS_PROPERTY_INTERNAL );
}

    return HashProperties;
}

void AsMediaFileRes::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

bool AsMediaFileRes::asUsesDataFile( void )
{
    if( m_bInternal )
	{
		return true;
	}
	else
	{
		return false;
	}
}

const QByteArray& AsMediaFileRes::asGetHashData( void )
{
    return m_HashData;
}

bool AsMediaFileRes::asIsHashDataDirty( void )
{
    return m_bHashDataDirty;
}

void AsMediaFileRes::asComputeHashData( void )
{
	if( m_bInternal )
	{
		//We have the file so calculate a hash based on its binary data
		//This is called before the file is imported so needs to use the original path
		QString filename = this->asGetOriginalFilePath();
		QFile inFile( filename );
		if ( inFile.open( QIODevice::ReadOnly ) )
		{
			//Media may be very large, read only the first portion of large files
			//prepend the length of the original file
			qint64 fileSize = inFile.size();
			m_HashData.setNum( fileSize );
			m_HashData.append ( inFile.read( MAX_HASH_FILE_READ ));
			inFile.close();
		}
		else
		{
			//error
			m_HashData = QByteArray();
		}
	}
	else
	{
		//We don't have the file, use the filename (which for external files should include the path)
		m_HashData = this->asGetOriginalFilename().toLatin1();
	}
    m_bHashDataDirty = false;
}

const QString AsMediaFileRes::asGetMimeType( void ) const
{
    return m_MimeType;
}

void AsMediaFileRes::asSetMimeType( QString mimeType )
{
    m_MimeType = mimeType;
    m_bHashDataDirty = true;
}

bool AsMediaFileRes::asIsInternal( void ) const
{
    return m_bInternal;
}

void AsMediaFileRes::asSetInternal( bool internal )
{
    m_bInternal = internal;
    m_bHashDataDirty = true;
}


bool AsMediaFileRes::asIsInternalyLinked() const
{
    bool ret = false;
    if( this->asGetOriginalFilename().startsWith( AsMediaFileRes::AsInternalLinkedURI ) )
    {
        ret = true;
    }
    return ret;
}

QString AsMediaFileRes::asGetDisplayName() const
{
    QString ret = this->asGetOriginalFilename();
    if( ret.startsWith( AsMediaFileRes::AsInternalLinkedURI ) )
    {
        QFileInfo f( ret );
        ret = f.fileName();
    }
    return ret;
}



QString AsMediaFileRes::asGetSourceLocation( AsFlipchart *pFlipchart ) const
{
    return  QString();
}
