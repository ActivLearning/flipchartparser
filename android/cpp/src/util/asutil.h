/****************************************************************************
** Copyright 2006 Promethean Technologies Group Limited
****************************************************************************/

#ifndef ASUTIL_H
#define ASUTIL_H

#include <Qt>
#include <QObject>


class QObject;
class QSize;
class QString;

#define AsSafeDelete(x)		if (x!=NULL) { delete x; x=NULL; }


//! Collects some public static utility functions into a single scope
struct AsUtil
{
    //! Wraps QObject::connect to detect failed connections (DEBUG builds only)
    static bool asConnect( const QObject *sender, const char *signal, const QObject *receiver, const char *slot, Qt::ConnectionType type = Qt::AutoConnection );

	//! Wraps QObject::disconnect to detect failed connections (DEBUG builds only)
    static bool asDisconnect( const QObject *sender, const char *signal, const QObject *receiver, const char *slot);

    static QString asGetSystemTempPath();

    static QString asGetRootTempPath();

    static bool asGetPathCase( QString& );

    // Returns true if the string is a url.  This could return a false pos if the protocal is missing but it's the best we can do.
    // If the return is true and needToAppendHTTP == true the protocal is missing so the caller must prepend the string. 
    static bool asIsWebExternalLink( const QString & toTest, bool & needToAppendHTTP );



    static bool asSufficientMemoryToLoadAndSaveVideo( quint64 fileSize );
};

namespace AsUtils
{

    
    /**
     * Utility functor that can be passed as a type parameter to a template method.
     * Useful for organising connections into separate methods, and re-using that 
     * method for disconnecting
     */
    class AsConnect
    {
    public:
        bool operator()(
            const QObject *sender, 
            const char *signal, 
            const QObject *receiver, 
            const char *slot);
    };
    
    /**
     * Utility functor that can be passed as a type parameter to a template method.
     * Intended to complement AsConnect
     */
    class AsDisconnect
    {
    public:
        bool operator()(
            const QObject *sender, 
            const char *signal, 
            const QObject *receiver, 
            const char *slot);
    };
}
#endif      // #ifndef ASUTIL_H
