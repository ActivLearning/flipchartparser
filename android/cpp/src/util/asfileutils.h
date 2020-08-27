#ifndef ASFILEUTILS_H
#define ASFILEUTILS_H


#include <QString>

class AsObject;
class AsResource;
class AsNode;

class AsFileUtils
{
public:
    AsFileUtils();
    ~AsFileUtils();


public:

    //! Returns the file name (including extension) for the passed object
    static QString asGetObjectFilename( AsObject * );

    //! Returns the file name (including extension) for the passed resource
    static QString asGetResourceDataFilename( AsResource * );

    //! Returns the file name (including extension) for the passed node tree
    static QString asGetNodeTreeFilename( AsNode * );
        //! Cleans up the formatting of a path (directory separators, etc.)
    static QString asCleanPath( const QString& path );
};

#endif //ASFILEUTILS_H