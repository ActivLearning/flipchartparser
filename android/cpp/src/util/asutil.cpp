/****************************************************************************
** Copyright 2006 Promethean Technologies Group Limited
****************************************************************************/

#include "asutil.h"

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QRegExp>
#include <QRect>


#if defined(Q_OS_LINUX) && defined(UBUNTU1404)
    #include <unistd.h>
#endif

#ifdef Q_OS_WIN
// Need this as pulling information about the user is best through the win32 API and not enviroment
#include <windows.h>
#endif

/**
 * Connects a Qt signal to a slot.
 *
 * Differs from the normal Qt function by causing an assert if the connection is unsuccessful.
 * For more information on signals and slots see the Qt manual.
 *
 * Note that an assert will not be thrown for a unique connection. This is because a return
 * of false is valid behaviour for that connection type.
 *
 * @param[in] sender    The object sending the signal.
 * @param[in] signal    The signal.
 * @param[in] receiver  The object receiving the signal.
 * @param[in] slot      The slot.
 * @param[in] type      The type of connection.
 * @return True if the connection succeeds, false otherwise.
 */
bool AsUtil::asConnect( const QObject *sender, const char *signal, const QObject *receiver, const char *slot, Qt::ConnectionType type )
{
    Q_ASSERT_X( sender, __FUNCTION__, "Trying to connect to NULL sender.");
    Q_ASSERT_X( receiver, __FUNCTION__, "Trying to connect to NULL receiver.");

	bool bConnected = QObject::connect( sender, signal, receiver, slot, type );

    if( type != Qt::UniqueConnection )
    {
        Q_ASSERT_X( bConnected == true, "AsUtil::asConnect", "Failed to connect" );
    }
    return bConnected;
}

bool AsUtil::asDisconnect( const QObject *sender, const char *signal, const QObject *receiver, const char *slot)
{
    Q_ASSERT_X( sender, __FUNCTION__, "Trying to disconnect to NULL sender.");
    Q_ASSERT_X( receiver, __FUNCTION__, "Trying to disconnect to NULL receiver.");

	bool bDisconnected = QObject::disconnect(sender,signal,receiver, slot );
    Q_ASSERT_X( bDisconnected == true, "AsUtil::asDisconnect", "Failed to disconnect" );
    return bDisconnected;
}

QString AsUtil::asGetSystemTempPath()
{
#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    QFileInfo tempPathInfo("/var/tmp");

    if (tempPathInfo.exists() && tempPathInfo.isWritable())
    {
    return tempPathInfo.absoluteFilePath();
    }
    else
    {
    return QDir::tempPath();
    }
#else
    return QDir::tempPath();
#endif
}

QString AsUtil::asGetRootTempPath()
{
    // Get the system temporary path.
    QString tempPath = AsUtil::asGetSystemTempPath();

    if ( !tempPath.endsWith( "/" ) )
    {
        tempPath.append( "/" );
    }

    // Get the Inspire temporary sub path.
    tempPath.append( "com.nd.flipchartparser/" );

    return tempPath;
}

bool AsUtil::asGetPathCase( QString& path )
{
    QDir dir( path );
    if ( !dir.exists() )
	{
        qDebug( "[ AsUtil ] - Path doesnt exist (%s).", path.toLatin1().data() );
        return false;
	}

    if ( !dir.isAbsolute() )
	{
        qDebug( "[ AsUtil ] - Path is not absolute (%s).", path.toLatin1().data() );
        return true;
	}

    QString cleanPath = QDir::cleanPath( path );
    QString normalized = QDir::fromNativeSeparators( cleanPath );

    QStringList parts = normalized.split( "/" );

    path.clear();
    path += parts.takeFirst();
	while( path.isEmpty() )
	{
		if ( parts.isEmpty() )
			return false;

		path += "/" + parts.takeFirst();
	}

    while( !parts.isEmpty() )
    {
        QString part = parts.takeFirst();

        QDir dir( path );
        QFileInfoList list = dir.entryInfoList( QDir::AllDirs );
        foreach( QFileInfo info, list )
        {
            QString entry = info.baseName();
            if ( entry.compare( part, Qt::CaseInsensitive ) == 0 )
            {
                path += "/" + entry;
                break;
            }
        }
    }
    return true;
}


bool AsUtil::asIsWebExternalLink( const QString & toTest, bool & needToAppendHTTP )
{
    needToAppendHTTP = false;
    
    if( toTest.contains( "http://" ) )
    {
        return true;
    }
    
    if( toTest.contains( "https://" ) )
    {
        return true;
    }
    
    if( toTest.contains( "ftp://" ) )
    {
        return true;
    }
    
    if( toTest.contains( "https://" ) )
    {
        return true;
    }
    
    if( toTest.contains( "file://" ) )
    {
        // we have a url but it's local.
        return false;
    }
    
    // we are missing a protocal so if we return true the caller will have to modifie.
    needToAppendHTTP = true;
    
    if( toTest.contains( "wwww." ) )
    {
        return true;
    } 
    if( toTest.contains( ".com" ) )
    {
        return true;
    }
    if( toTest.contains( ".org" ) )
    {
        return true;
    }
    if( toTest.contains( ".gov" ) )
    {
        return true;
    }
    if( toTest.contains( ".mil" ) )
    {
        return true;
    }
    if( toTest.contains( ".co." ) )
    {
        return true;
    }

    // test for ip address.
    QRegExp ipTest( "\\b\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\b" );
    
    if( ipTest.indexIn( toTest ) != -1 )
    {
        return true;
    }
    
    // I don't know what more tests I can do at this point.  
    // I would like to call a DNS server but thats not an options realy.
    return false;
}
// AsUtils

bool AsUtils::AsConnect::operator()(
    const QObject *sender, 
    const char *signal, 
    const QObject *receiver, 
    const char *slot)
{
    return AsUtil::asConnect(sender,signal,receiver,slot);
}

bool AsUtils::AsDisconnect::operator()(
    const QObject *sender, 
    const char *signal, 
    const QObject *receiver, 
    const char *slot)
{
    return AsUtil::asDisconnect(sender,signal,receiver,slot);
}





bool AsUtil::asSufficientMemoryToLoadAndSaveVideo( quint64 fileSize )
{
    enum
    {
        extraMemoryRequired = 60000000
    };

    //need memory of more than twice the file size so the flipchart can be saved
    //try a dummy alloc to see if we should allow the load
    //split this across 2 QByteArrays to allow for limit in size of an int
    try
    {
        //need memory of more than twice the file size so the flipchart can be saved
        //try a dummy alloc to see if we should allow the load
        qint64 size = fileSize + extraMemoryRequired;
        QByteArray byteArray( size, ' ' );
        QByteArray byteArray2( size, ' ' );
    }
    catch( ... )
    {
        return false;
    }
    return true;
}

// END OF FILE
