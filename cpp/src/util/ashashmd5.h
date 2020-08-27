#ifndef _ASHASHMD5_H
#define _ASHASHMD5_H

#include <QString>

class AsHashMD5
{
public:
    static QString hashData( const QByteArray& buffer );

private:
    struct md5Context
    {
        unsigned int buffer[4];
        unsigned int bits[2];
        unsigned char in[64];
    };

    static void updateHash(md5Context* context, const char* data, long int length);
    static void md5Transform(unsigned int buf[4], quint32 const in[16], bool bLastCall = false);
};

#endif
