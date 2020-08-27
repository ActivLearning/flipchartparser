// Implementation of the AsObjectStreamer class.
// $Author: Paul Wareing
#include <QDateTime>
#include <iostream>
#include "asobjectstreamer.h"

#include "../asfactory.h"

#include "../util/asutil.h"

#include "../dataStruct/aspointfarray.h"
#include "../objects/aspointer.h"
#include "../objects/astransform.h"
#include "../objects/asorigin.h"
#include "../objects/asink.h"
#include "../resources/asresourceregister.h"
#include "../resources/asresourceindex.h"
#include "../dataStruct/asinstructlistlist.h"
#include "../dataStruct/astextrunarray.h"
#include "../objects/asundoresourceindex.h"
#include "../dataStruct/asoptionlist.h"
#include "../dataStruct/asstringpairlist.h"
#include "../dataStruct/asmoulist.h"
#include "../objects/asvirtualfolderindex.h"
#include "asasynctestlevellist.h"




// Uncomment line below for event debug output
//#define AS_USE_DEBUG
#ifdef AS_USE_DEBUG
#include <QDebug>
    static int debugCounter = 0;
    #define AS_DEBUG(x) qDebug() << "[OS]:" << "[" << debugCounter++ << "]" << "(" << __FUNCTION__ << ")" << x;
#else
    #define AS_DEBUG(x)
#endif

AsObjectStreamer::AsObjectStreamer( QIODevice *pDevice )
    :m_nStreamVerionUpQt4(false)
{
    AS_DEBUG("Constructor" << this)
    // Configure the file we will write to.
    m_FileStream.setByteOrder( QDataStream::LittleEndian );
    m_FileStream.setDevice( pDevice );
}

AsObjectStreamer::~AsObjectStreamer()
{
    AS_DEBUG("Destructor:" << this)
}

bool AsObjectStreamer::asWriteHeader()
{
    AS_DEBUG("")
    // First, we write the file type magic number.
    m_FileStream << ( quint64 ) FILEHEADER_OBJECT;
    if( m_FileStream.status() != QDataStream::Ok )
    {
        return false;
    }

    // Next, we write the file type version number.
    m_FileStream << ( quint16 ) FILEVERSION_OBJECT_V1;
    if( m_FileStream.status() != QDataStream::Ok )
    {
        return false;
    }

    // We also write out the version of the streamer we are using.
    m_FileStream << ( qint16 ) QDataStream::Qt_DefaultCompiledVersion;
    if( m_FileStream.status() != QDataStream::Ok )
    {
        return false;
    }

    return true;
}

bool AsObjectStreamer::asWriteObject( AsObject *pObject )
{
//	AS_DEBUG("")
//    return( asWriteAsObject( m_FileStream, pObject ) );
    return true;
}






// Returns true is OK else false








AsObject * AsObjectStreamer::asReadObjects( AsFactory * asFactory )
{
    AS_DEBUG("")
    // read file into buffer
    QIODevice * pDevice = m_FileStream.device();
    if( pDevice == 0 )
    {
        return NULL;
    }
    QByteArray aFile;
    aFile = pDevice->readAll();
    QBuffer bFile( &aFile );
    bFile.open( QIODevice::ReadOnly );
    QDataStream stream( &bFile );
    stream.setByteOrder( QDataStream::LittleEndian );
    stream.device()->reset();

    // We must first check that the file we are attempting to read is
    // a flipchart object file.
    quint64 nFirst8Bytes;
    stream >> ( quint64& ) nFirst8Bytes;
    if ( nFirst8Bytes != FILEHEADER_OBJECT )
    {
        return 0;
    }

    // Next, we must check that we can handle this version of the flipchart object file.
    quint16 nVersion;
    stream >> ( quint16& ) nVersion;
    if ( nVersion != FILEVERSION_OBJECT_V1 )
    {
        return 0;
    }

    // Ok, we have a flipchart object file.  What version of the streamer was
    // it streamed with??  If it is Qt_4_0 or earlier then we will
    // set our version to it.  If it is later then we cannot handle
    // it??
    qint16 nStreamVersion;
    stream >>( qint16& ) nStreamVersion;
    if ( nStreamVersion > QDataStream::Qt_4_0 )
    {
        m_nStreamVerionUpQt4=true;
    }
    stream.setVersion( nStreamVersion );

    AsObject *pReturn = NULL;

    // The object file may contain many objects.  Here we read them all and return a pointer to the first.
    bool finished = false;
    while ( !finished )
    {
        if ( stream.atEnd() )
        {
            finished = true;
        }
        else
        {
            // The first data byte must be an 'open object' tag.
            quint8 nTag;
            stream >> ( quint8& ) nTag;
            if ( nTag != OPEN_OBJECT )
            {
                finished = true;
            }
            else
            {
                // Now we can read the object data...
                AsObject * pObject = asReadAsObject( stream, asFactory );
                if ( pReturn == NULL )
                    pReturn = pObject;
            }
        }
    }

    return pReturn;
}

AsObject * AsObjectStreamer::asReadAsObject( QDataStream& stream, AsFactory * pAsFactory )
{
    AS_DEBUG("")
    // Now we read in the object type.
    quint16 nType = AsObject::AS_OBJECT_NULL;
    stream >> ( quint16& ) nType;
    if ( nType == AsObject::AS_OBJECT_NULL )
    {
        return 0;
    }

    // Read in the unique ID.
    quint32 nID = 0;
    stream >> ( quint32& ) nID;
    if ( nID == 0 )
    {
        return 0;
    }

    // Next, call the factory to create the object.
    AsObject * pAsObject = pAsFactory->asCreateObject( ( AsObject::AsEnumObjectType )nType, nID );
    if ( pAsObject == 0 )
    {
        return 0;
    }

    // Mark dirty for future writes...
    pAsObject->asSetDirtyForWrite( true );

    // Every object has its own property map.
    QList< quint32 > m_PropertyMap;
    int propertyIndex = 0;
    qint32 propertyBytes;

    bool bFinishedObject = false;
    while ( !bFinishedObject )
    {
        // What we do next depends on the next tag.
        // If the next tag is a 'P' then we read in the property.
        // If the next tag is an 'O', then we read in the child object refs of this object.
        // If the next tag is an 'o', or anything else, we're finished with this object.
        quint8 nTag;
        stream >> ( quint8& ) nTag;

        switch ( nTag )
        {
            case OPEN_PROPERTY:
                if ( propertyIndex < m_PropertyMap.count() )
                {
                    propertyBytes = m_PropertyMap.at( propertyIndex );
                }
                else
                {
                    propertyBytes = -1;
                }
                asReadProperty( stream, propertyBytes, pAsFactory, pAsObject );
                propertyIndex++;
                break;

            case OPEN_USER_PROPERTY:
                if ( propertyIndex < m_PropertyMap.count() )
                {
                    propertyBytes = m_PropertyMap.at( propertyIndex );
                }
                else
                {
                    propertyBytes = -1;
                }
                this->asReadUserProperty( stream, propertyBytes, pAsFactory, pAsObject );
                propertyIndex++;
                break;

            case OPEN_CONNECTION:
                this->asReadConnection( stream, pAsFactory, pAsObject );
                break;

            case OPEN_REFERENCE:
                asReadReference( stream, pAsFactory, pAsObject );
                break;

            case OPEN_OBJECT_MAP:
                asReadObjectMap( stream, m_PropertyMap );
                break;


            default:
//                LOGDEBUG("##############Read Error:未正常退出################","");
                bFinishedObject = true;
                // We're just going to return from building this object.
                break;
        }
    }
    return pAsObject;
}

void AsObjectStreamer::asReadObjectMap( QDataStream& stream, QList< quint32 >& map )
{
    AS_DEBUG("")
    quint32 count;
    stream >> ( quint32& ) count;

    quint32 propSize;
    for ( quint32 i = 0 ; i < count ; i ++ )
    {
        stream >> ( quint32& ) propSize;
        map.append( propSize );
    }

    quint8 nTag;
    stream >> ( quint8& ) nTag;
}

void AsObjectStreamer::asReadReference( QDataStream& stream, AsFactory *pAsFactory, AsObject *pAsObject )
{
    AS_DEBUG("")
    // First read the ID of the reference.
    quint32 nID;
    stream >> ( quint32& ) nID;

    // Now get the factory to create, or retrieve the node with this ID.
    AsNode *pAsNode = pAsFactory->asCreateNode( nID );

    // Add the reference to our object.
    pAsObject->asAddReference( pAsNode );

    // Stream in the CLOSE_REFERENCE tag.
    quint8 nTag;
    stream >> ( quint8& ) nTag;
}

void AsObjectStreamer::asReadConnection( QDataStream& stream, AsFactory *pFactory, AsObject *pObject )
{
    AS_DEBUG("")
    // First, read the source type.
    quint16 nSourceType;
    stream >> ( quint16& ) nSourceType;
    AsMetaConnection::AsEnumConnectionSource sourceType = ( AsMetaConnection::AsEnumConnectionSource ) nSourceType;

    // Read the sink type.
    quint16 nSinkType;
    stream >> ( quint16& ) nSinkType;
    AsMetaConnection::AsEnumConnectionSink sinkType = ( AsMetaConnection::AsEnumConnectionSink ) nSinkType;

    // Next, the connection type.
    quint16 nConnectionType;
    stream >> ( quint16& ) nConnectionType;
    AsMetaConnection::AsEnumConnectionType connectionType = ( AsMetaConnection::AsEnumConnectionType ) nConnectionType;

    // Read the partner type...
    quint16 nPartnerType;
    stream >> ( quint16& ) nPartnerType;
    AsMetaConnection::AsEnumPartnerType partner = ( AsMetaConnection::AsEnumPartnerType ) nPartnerType;

    // If the connection type is an AsObject then get the ID, type and create the target.
    QObject *pPartner = 0;
    switch ( partner )
    {
    case AsMetaConnection::ASPARTNER_ASOBJECT:
        {
            // Read the target object ID.
            quint32 objectID;
            stream >> ( quint32& ) objectID;

            // Read the target object type.
            quint16 objectType;
            stream >> ( quint16& ) objectType;

            // Next, we create/get the target object from the factory.
            pPartner = ( QObject * )pFactory->asCreateObject( ( AsObject::AsEnumObjectType ) objectType, objectID );
            pObject->addAction(objectID);
        }
        break;

    case AsMetaConnection::ASPARTNER_STUDIO:
        {
//            pPartner = ( QObject * ) AsStudio::asInstance();
        }
        break;

    case AsMetaConnection::ASPARTNER_APP:
        {
//            pPartner = ( QObject * ) AsApp::asInstance();
        }
        break;

    case AsMetaConnection::ASPARTNER_GUICONTROLLER:
        {
//            pPartner = ( QObject * ) AsStudio::asInstance()->asGetGuiControllerPointer();
        }
        break;

    default:
        //Do Nothing
        break;
    }

    // Read the close tag.
    quint8 nTag;
    stream >> ( quint8& ) nTag;

    if ( pPartner != 0 )
    {
//        AsMetaConnection::asSetupConnection( pObject, sourceType, pPartner, sinkType, connectionType );
    }
    else
    {
        qDebug( "[ AsObjectStreamer ] - Attempted to stream in a connection with a NULL partner pointer!" );
    }
}

void AsObjectStreamer::asReadProperty( QDataStream& stream, qint32 propBytes, AsFactory *pAsFactory, AsObject *pAsObject )
{
    AS_DEBUG("")
    // First get the property ID.
    quint16 nID;
    stream >> ( quint16& ) nID;

    propBytes -= 4; // 'P' + 'p' + id ( 2 )
    // Read the variant value.
    Variant vValue;
    if ( this->asReadVariant( stream, propBytes, pAsFactory, vValue ) )
    {
        // Now we set this property.
        pAsObject->asSetProperty( nID, vValue );
    }

    // Lastly, read the closing 'p' tag.
    quint8 nTag;
    stream >> ( quint8& ) nTag;
}

void AsObjectStreamer::asReadUserProperty( QDataStream& stream, qint32 propBytes, AsFactory *pFactory, AsObject *pObject )
{
    AS_DEBUG("")
    // First read the property name.
    QString sName;
    this->streamIn( stream, sName );

    propBytes -= 2;  // 'P' + 'p'
    propBytes -= sName.length();  // sName

    // Next, read the variant value.
    Variant vValue;
    if ( this->asReadVariant( stream, propBytes, pFactory, vValue ) )
    {
        // Now, set the property on the object.
        pObject->asSetUserProperty( sName, vValue );
    }

    // Last, read the close tag.
    quint8 nTag;
    stream >> ( quint8& ) nTag;
}

bool AsObjectStreamer::asReadVariant( QDataStream& stream, qint32 propBytes, AsFactory *pAsFactory, Variant &var )
{
    AS_DEBUG("")
    // Now read the data type.
    quint16 nType;
    stream >> ( quint16& ) nType;
    if ( propBytes > 2 )
    {
        propBytes -= 2;
    }
    else
    {
        propBytes = -1;
    }
    //if load filpchart which created by qt4
    if( !m_nStreamVerionUpQt4 && nType==127 ){
        nType=QVariant::UserType;
    }
    // Now read in the data.
    switch ( nType )
    {
    case QVariant::Image:
        {
//            Variant var;
//            var.type=VariableType::Q_IMAGE;
//            QImage image;
//            streamIn( stream, image );
//            var = image;
        }
        break;

    case QVariant::Bool:
        {
            bool b;
            Variant mvar;
            streamIn( stream, b );
            mvar.type = VariableType ::BOOL;
            mvar.value = new bool(b);
            var=mvar;
          //  var = ( bool ) b;
        }
        break;

    case QVariant::UInt:
        {
            quint32 n;
            Variant mvar;
            mvar.type = VariableType ::UINT;
            stream >> ( quint32& ) n;
            mvar.value = new quint32(n);
            var = mvar;
          //  var = ( unsigned int )n;
        }
        break;

    case QVariant::Int:
        {
            qint32 n;
            Variant mvar;
            mvar.type = VariableType ::INT;
            stream >> ( qint32& ) n;
            mvar.value = new qint32(n);
            var = mvar;
          //  var = ( int ) n;
        }
        break;

    case QVariant::Double:
        {
            double d;
            Variant mvar;
            mvar.type = VariableType ::DOUBLE;
            stream >> ( double& ) d;
            mvar.value = new double(d);
            var = mvar;
           // var = ( double ) d;
        }
        break;

    case QVariant::PointF:
        {
            QPointF point;
            Variant mvar;
            mvar.type = VariableType ::Q_POINT_F;
            streamIn( stream, point );
            mvar.value = new QPointF(point);
            var = mvar;
           // var = point;
        }
        break;

    case QVariant::SizeF:
        {
            QSizeF size;
            Variant mvar;
            mvar.type = VariableType ::Q_SIZE_F;
            streamIn( stream, size );
            mvar.value = new QSizeF(size);
            var = mvar;
          //  var = size;
        }
        break;

    case QVariant::Size:
        {
            QSize size;
            Variant mvar;
            mvar.type = VariableType ::Q_SIZE;
            streamIn( stream, size );
            mvar.value = new QSize(size);
            var = mvar;
          //  var = size;
        }
        break;

    case QVariant::RectF:
        {
            QRectF rect;
            Variant mvar;
            mvar.type = VariableType ::Q_RECT_F;
            streamIn( stream, rect );
            mvar.value = new QRectF(rect);
            var = mvar;
          //  var = rect;
        }
        break;

    case QVariant::Rect:
        {
            QRect rect;
            Variant mvar;
            mvar.type = VariableType ::Q_RECT;
            streamIn( stream, rect );
            mvar.value = new QRect(rect);
            var = mvar;
         //   var = rect;
        }
        break;

    case QVariant::Color:
        {
            QColor color;

            Variant mvar;
            mvar.type = VariableType ::Q_COLOR;
            streamIn( stream, color );
            mvar.value = new QColor(color);
            var = mvar;
        }
        break;

    case QVariant::String:
        {
            QString str;
            Variant mvar;
            mvar.type = VariableType ::Q_STRING;
            streamIn( stream, str );
            mvar.value = new QString(str);
            var = mvar;
          //  var = str;
        }
        break;

    case QVariant::StringList:
        {
            QStringList stringList;
            Variant mvar;
            mvar.type = VariableType ::Q_STRING_LIST;
            streamIn( stream, stringList );
            mvar.value = new QStringList(stringList);
            var = mvar;
           // var = stringList;
        }
        break;

    case QVariant::DateTime:
        {
            QDateTime dateTime;
            Variant mvar;
            mvar.type = VariableType ::Q_DATE_TIME;
            streamIn( stream, dateTime );
            mvar.value = new QDateTime(dateTime);
            var = mvar;
           // var = dateTime;
        }
        break;

    case QVariant::Time:
        {
            QTime time;
            Variant mvar;
            mvar.type = VariableType ::Q_TIME;
            streamIn( stream, time );
            mvar.value = new QTime(time);
            var = mvar;

          //  var = time;
        }
        break;

    case QVariant::ByteArray:
        {
            QByteArray ba;
            stream >> ( QByteArray& ) ba;
            Variant mvar;
            mvar.type = VariableType ::Q_BYTE_ARRAY;
            mvar.value = new QByteArray(ba);
            var = mvar;
          //  var = ( QByteArray ) ba;
        }
        break;

    case QVariant::List:    // QList<QVariant>, a.k.a. QVariantList
        {
            QList<Variant> varList;
            this->streamIn( stream, varList, pAsFactory );
            Variant mvar;
            mvar.type = VariableType ::Q_LIST;
            mvar.value = new QList<Variant>(varList);
            var = mvar;
           // var = varList;
        }
        break;

    case QVariant::UserType:
        {
            // For a user type, the first item streamed was the type name.
            quint16 nType;
            stream >> ( quint16& ) nType;

            // Next we read the data, according to the type.
            switch ( nType )
            {
            case AsStreamer::AS_REGISTEREDTYPE_ASPOINTFARRAYT:
                {
                    AsPointFArray points;
                    streamIn( stream, points );
                    Variant mvar;
                    mvar.type = VariableType ::ASPOINTFARRAY;
                    mvar.value = new AsPointFArray(points);
                    var = mvar;

                 //   var.setValue( points );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASRECTF:
                {
                    AsRectF rect;
                    streamIn( stream, rect );
                    Variant mvar;
                    mvar.type = VariableType ::ASRECTF;
                    mvar.value = new AsRectF(rect);
                    var = mvar;
                   // var.setValue( rect );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASPOINTFARRAYARRAYT:
                {
                    AsPointFArrayArray shapes;
                    streamIn( stream, shapes );
                    Variant mvar;
                    mvar.type = VariableType ::ASPOINTFAARAYARRAY;
                    mvar.value = new AsPointFArrayArray(shapes);
                    var = mvar;
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASINSTRUCTLISTLIST:
                {
                    AsInstructListList instructs;
                    streamIn( stream, instructs );
                    Variant mvar;
                    mvar.type = VariableType ::ASINSTRUCTLISTLIST;
                    mvar.value = new AsInstructListList(instructs);
                    var = mvar;
                  //  var.setValue( instructs );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASMOULIST:
                {
                    AsMOUList list;
                    streamIn( stream, list );
                    Variant mvar;
                    mvar.type = VariableType ::ASMOULIST;
                    mvar.value = new AsMOUList(list);
                    var = mvar;
                   // var.setValue( list );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASRESOURCEINDEXT:
                {
                    AsResourceIndex resources;
                    streamIn( stream, resources );
                    Variant mvar;
                    mvar.type = VariableType ::ASRESOUCREINDEX;
                    mvar.value = new AsResourceIndex(resources);
                    var = mvar;
                 //   var.setValue( resources );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASTEXTRUNARRAYT:
                {
                    AsTextRunArray *textruns =new AsTextRunArray;
                    streamIn( stream, *textruns, pAsFactory );
                    Variant mvar;
                    mvar.type = VariableType ::ASTEXTRUNARRAY;
                    mvar.value = textruns;
                    var = mvar;
                   // var.setValue( textruns );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASPOINTERT:
                {
                    AsPointer asPointer;
                    Variant mvar;
                    if(streamIn( stream, asPointer, pAsFactory )){
                        mvar.type = VariableType ::ASPOINTER;
                        mvar.value = new AsPointer(asPointer);
                    }
                    var = mvar;


                 //   var.setValue( asPointer );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASUNDORESOURCEINDEX:
                {
                    AsUndoResourceIndex index;
                    streamIn( stream, index );
                    Variant mvar;
                    mvar.type = VariableType ::ASUNDORESOURCEINDEX;
                    mvar.value = new AsUndoResourceIndex(index);
                    var = mvar;
                  //  var.setValue( index );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASOPTIONLIST:
                {
                    AsOptionList list;
                    streamIn( stream, list );
                    Variant mvar;
                    mvar.type = VariableType ::ASOPTIONLIST;
                    mvar.value = new AsOptionList(list);
                    var = mvar;
                 //   var.setValue( list );
                }
                break;


            case AsStreamer::AS_REGISTEREDTYPE_ASSTRINGPAIRLIST:
                {
                    AsStringPairList list;
                    streamIn( stream, list );
                    Variant mvar;
                    mvar.type = VariableType ::ASSTRINGPAIRLIST;
                    mvar.value = new AsStringPairList(list);
                    var = mvar;
                   // var.setValue( list );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASFOLDERINDEX:
                {
                    AsFolderIndex idx;
                    streamIn( stream, idx );
                    Variant mvar;
                    mvar.type = VariableType ::ASFOLDERINDEX;
                    mvar.value = new AsFolderIndex(idx);
                    var = mvar;
                  //  var.setValue( idx );
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASRESOURCEREGISTERT:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsResourceRegister *pResourceRegister = ( AsResourceRegister* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pResourceRegister != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASRESOURCEREGISTER;
                        mvar.value = pResourceRegister;
                        var = mvar;
                       // var.setValue( *pResourceRegister );
                        //pAsFactory->asDeleteObject( pResourceRegister );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASINKT:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsInk *pInk = ( AsInk* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pInk != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASINK;
                        mvar.value = pInk;
                        var = mvar;
                      //  var.setValue( *pInk );
                       // pAsFactory->asDeleteObject( pInk );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASTRANSFORMT:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsTransform *pTransform = ( AsTransform* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pTransform != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASTRANSFORM;
                        mvar.value = pTransform;
                        var = mvar;
                      //  var.setValue( *pTransform );
                       // pAsFactory->asDeleteObject( pTransform );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASORIGINT:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsOrigin *pOrigin = ( AsOrigin* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pOrigin != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASORIGIN;
                        mvar.value = pOrigin;
                        var = mvar;
                      //  var.setValue( *pOrigin );
                       // pAsFactory->asDeleteObject( pOrigin );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASLABEL:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsLabel *pLabel = ( AsLabel* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pLabel != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASLABEL;
                        mvar.value = pLabel;
                        var = mvar;
                      //  var.setValue( *pLabel );
                      //  pAsFactory->asDeleteObject( pLabel );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASTEXTCHARFORMAT:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsTextCharFormat *pFormat = ( AsTextCharFormat* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pFormat != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASTEXATCHARFORMAT;
                        mvar.value = pFormat;
                        var = mvar;
                      //  var.setValue( *pFormat );
                      //  pAsFactory->asDeleteObject( pFormat );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASVIRTUALFOLDERINDEX:
                {
                    quint8 nTag;
                    stream >> ( quint8& ) nTag;

                    AsVirtualFolderIndex *pIdx = ( AsVirtualFolderIndex* ) this->asReadAsObject( stream, pAsFactory );
                    if ( pIdx != NULL )
                    {
                        Variant mvar;
                        mvar.type = VariableType ::ASVIRTUALFOLDERINDEX;
                        mvar.value = pIdx;
                        var = mvar;
                       // var.setValue( *pIdx );
                       // pAsFactory->asDeleteObject( pIdx );
                    }
                    else
                    {
                        return false;
                    }
                }
                break;

            case AsStreamer::AS_REGISTEREDTYPE_ASASYNCTESTLEVELLIST:
                {
                    AsAsyncTestLevelList list;
                    streamIn( stream, list );
                    Variant mvar;
                    mvar.type = VariableType ::ASASYNCTESTLEVELLIST;
                    mvar.value = new AsAsyncTestLevelList(list);
                    var = mvar;
                  //  var.setValue( list );
                }
                break;

            default:
                {
                    // Here we need to skip past an unknown type...
                    // propBytes has been decremented as bytes have been read so now we have to skip past the
                    // number of bytes in propBytes, thus ignoring this unknown property type.
                    if ( propBytes > 0 )
                    {
                        stream.skipRawData( propBytes );
                    }
                    QString sError = QString( "Skipped property with unknown usertype(%1)!" ).arg( nType );

                    return false;
                }
            }
        }
        break;

    default:
        {
            // Here we need to skip past an unknown type...
            // propBytes has been decremented as bytes have been read so now we have to skip past the
            // number of bytes in propBytes, thus ignoring this unknown property type.
            QString sError = QString( "Skipped property with unknown type(%1), skipping %2 bytes!" ).arg( nType ).arg( propBytes );
            if ( propBytes > 0 )
            {
                stream.skipRawData( propBytes );

            }
            sError = "[ AsObjectStreamer ] - asReadVariant: " + sError;

            qDebug( "%s", qPrintable( sError ) );

            return false;
        }
    }

    // If we get here then we successfully read the property.
    return true;
}



void AsObjectStreamer::streamIn( QDataStream& stream, bool& b )
{
    AS_DEBUG("")
    b = false;
    quint8 n;
    stream >> ( quint8& ) n;
    if ( n==0xFF )
    {
        b = true;
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, QPointF& point )
{
    AS_DEBUG("")
    double d;
    stream >> ( double& ) d;
    point.setX( d );
    stream >> ( double& ) d;
    point.setY( d );
}



void AsObjectStreamer::streamIn( QDataStream& stream, QSizeF& size )
{
    AS_DEBUG("")
    double d;
    stream >> ( double& ) d;
    size.setWidth( d );
    stream >> ( double& ) d;
    size.setHeight( d );
}



void AsObjectStreamer::streamIn( QDataStream& stream, QSize& size )
{
    AS_DEBUG("")
    quint32 n;
    stream >> ( quint32& ) n;
    size.setWidth( n );
    stream >> ( quint32& ) n;
    size.setHeight( n );
}





void AsObjectStreamer::streamIn( QDataStream& stream, QRectF& rect )
{
    AS_DEBUG("")
    double d;
    stream >> ( double& ) d;
    rect.setX( d );
    stream >> ( double& ) d;
    rect.setY( d );
    stream >> ( double& ) d;
    rect.setWidth( d );
    stream >> ( double& ) d;
    rect.setHeight( d );
}

void AsObjectStreamer::streamIn( QDataStream& stream, QRect& rect )
{
    AS_DEBUG("")
    qint32 d;
    stream >> ( qint32& ) d;
    rect.setX( d );
    stream >> ( qint32& ) d;
    rect.setY( d );
    stream >> ( qint32& ) d;
    rect.setWidth( d );
    stream >> ( qint32& ) d;
    rect.setHeight( d );
}



void AsObjectStreamer::streamIn( QDataStream& stream, QColor& color )
{
    AS_DEBUG("")
    quint8 b;

    stream >> ( quint8& ) b;
    color.r = b;
    stream >> ( quint8& ) b;
    color.g = b;
    stream >> ( quint8& ) b;
    color.b = b;
    stream >> ( quint8& ) b;
    color.a = b;
}



void AsObjectStreamer::streamIn( QDataStream& stream, QString& str )
{
    AS_DEBUG("")
    quint16 nEncoding;
    stream >> ( quint16& ) nEncoding;
    stream >> ( QString& ) str;
}



void AsObjectStreamer::streamIn( QDataStream& stream, QStringList& stringList )
{
    AS_DEBUG("")
    quint16 nEncoding;
    stream >> ( quint16& ) nEncoding;

    quint32 nNumStrings;
    stream >> ( quint32& ) nNumStrings;

    QString str;
    for( int i = 0 ; i < ( int ) nNumStrings ; ++i )
    {
        stream >> ( QString& ) str;
        stringList.append( str );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, QDateTime& dateTime )
{
    AS_DEBUG("")
    QDate date;
    quint16 nYear;
    stream >> ( quint16& ) nYear;

    quint8 nMonth;
    stream >> ( quint8& ) nMonth;

    quint8 nDay;
    stream >> ( quint8& ) nDay;

    date.setDate( ( int ) nYear, ( int ) nMonth, ( int ) nDay );

    QTime time;
    quint8 nHour;
    stream >> ( quint8& ) nHour;

    quint8 nMinute;
    stream >> ( quint8& ) nMinute;

    quint8 nSecond;
    stream >> ( quint8& ) nSecond;

    time.setHMS( ( int ) nHour, ( int ) nMinute, ( int ) nSecond );

    dateTime.setDate( date );
    dateTime.setTime( time );
}



void AsObjectStreamer::streamIn( QDataStream& stream, QTime& time )
{
    AS_DEBUG("")
    quint8 nHour;
    stream >> ( quint8& ) nHour;

    quint8 nMinute;
    stream >> ( quint8& ) nMinute;

    quint8 nSecond;
    stream >> ( quint8& ) nSecond;

    time.setHMS( ( int ) nHour, ( int ) nMinute, ( int ) nSecond );
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsPointFArray& points )
{
    AS_DEBUG("")
    // For an AsPolygonF, the first data written was the number of
    // points.
    quint32 numPoints;
    stream >> ( quint32& ) numPoints;

    // Then, the data was written as a bytearray for speed.  So we need to
    // read back the byte array and parse the points.
    QByteArray ba;
    stream >> ba;

    points.asFromByteArray( &ba, ( int ) numPoints );
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsPointFArrayArray& shapes )
{
    AS_DEBUG("")
    // For an arrays of AsPointFArrays, the first data streamed
    // out was the number of arrays (shapes).
    quint32 numShapes;
    stream >> ( quint32& ) numShapes;

    for ( quint32 i = 0 ; i < numShapes ; ++i )
    {
        AsPointFArray shape;
        streamIn( stream, shape );
        shapes.append( shape );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsResourceIndex& resourceIndex )
{
    AS_DEBUG("")
    // The first data streamed was the number of indexes in the array.
    quint32 numIndexes;
    stream >> ( quint32& ) numIndexes;

    AsResourceItem resourceItem;
    for ( quint32 i = 0 ; i < numIndexes ; ++i )
    {
        quint32 nID;
        stream >> ( quint32& ) nID;
        resourceItem.asSetID( nID );

        QString sResourceFilename;
        streamIn( stream, sResourceFilename );
        resourceItem.asSetResourceFilename( sResourceFilename );

        QString sDataFilename;
        streamIn( stream, sDataFilename );
        resourceItem.asSetDataFilename( sDataFilename );

        QString sHash;
        streamIn( stream, sHash );
        resourceItem.asSetHash( sHash );

        qint32 nRefCount;
        stream >> ( qint32& ) nRefCount;
        resourceItem.asSetRefCount( nRefCount );

        resourceIndex.append( resourceItem );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsInstructListList& instructLists )
{
    AS_DEBUG("")
    quint32 numLists;
    stream >> numLists;

    for(quint32 i =0; i< numLists; i++)
    {
        //for each instruct list.....
        AsInstructList instructs;

        quint32 numControls;
        stream >> (quint32&)numControls;

        for(quint32 j=0;j<numControls;j++)
        {
            double divisor;
            stream >> divisor;

            double maxDivisor;
            stream >> maxDivisor;

            double minDivisor;
            stream >> minDivisor;

            int editIndex;
            stream >> editIndex;

            int controlLimitIndex;
            stream >> controlLimitIndex;

            quint32 intControlType = 0;
            stream >> intControlType;

            quint32 intControlMovementType = 0;
            stream >> intControlMovementType;

//            instructs.asAddControl(AsShapePathControl::AsEnumControlType(intControlType),
//                                     AsShapePathControl::AsEnumControlMovementType(intControlMovementType),
//                                     maxDivisor,
//                                     minDivisor,
//                                     divisor,
//                                     editIndex,
//                                     controlLimitIndex);
        }

        quint32 numInstructs;
        stream >> numInstructs;

        for(quint32 j=0; j< numInstructs ; j++)
        {
            AsPathInstruct asPathInstruct;
            streamIn(stream, asPathInstruct);
            instructs.append(asPathInstruct);
        }
        instructLists.append(instructs);
    }
}




void AsObjectStreamer::streamIn( QDataStream& stream, AsMOUList& list )
{
    AS_DEBUG("")
    quint32 listSize;
    stream >> (quint32&)listSize;

    for(quint32 i =0; i< listSize; i++)
    {
        QPair<AsObject::AsEnumObjectType,  int> curPair;

        stream>>(quint32&)(curPair.first)>>(quint32&)(curPair.second);
     //   list.append(curPair);
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsPathInstruct& instruct )
{
    AS_DEBUG("")
    quint32 type = 0;
    stream >> type;
    instruct.m_type =  AsPathInstruct::AsEnumInstructType(type);

    stream >> instruct.m_xRadius;
    stream >> instruct.m_yRadius;

    stream >> instruct.m_xControlVar;
    stream >> instruct.m_yControlVar;

    stream >> instruct.m_xControlVarIndex;
    stream >> instruct.m_yControlVarIndex;

    stream >> instruct.m_xAffectorIndex;
    stream >> instruct.m_yAffectorIndex;

    stream >> instruct.m_xMutatorMult;
    stream >> instruct.m_yMutatorMult;

    quint32 xType, yType;
    stream >> xType;
    stream >> yType;

    instruct.m_xMutatorType = AsPathInstruct::AsEnumMutatorType(xType);
    instruct.m_yMutatorType = AsPathInstruct::AsEnumMutatorType(yType);

    stream >> xType;
    stream >> yType;

    instruct.m_xRadiusMutatorType = AsPathInstruct::AsEnumMutatorType(xType);
    instruct.m_yRadiusMutatorType = AsPathInstruct::AsEnumMutatorType(yType);

    streamIn(stream, instruct.m_bClockwise);
    streamIn(stream, instruct.m_bLargeArc);
    streamIn(stream, instruct.m_endPoint);
}




bool AsObjectStreamer::streamIn( QDataStream& stream, AsPointer& asPointer, AsFactory *pFactory )
{
    AS_DEBUG("")
    quint32 nodeID;
    quint32 objectID;
    quint16 objectType;
    stream >> ( quint32& ) nodeID;
    stream >> ( quint32& ) objectID;
    stream >> ( quint16& ) objectType;

    if (( nodeID != 0 ) &&
        ( objectID != 0 ) &&
        ( objectType != 0 ))
    {
        AsNode *pNode = pFactory->asCreateNode( nodeID );
        AsObject *pObject = pFactory->asCreateObject( ( AsObject::AsEnumObjectType )objectType, objectID );
        if (( pNode != 0 ) &&
            ( pObject != 0 ))
        {
            pNode->asSetAsObjectReference( pObject );
            asPointer.asSetNode( pNode );
        }
        else
        {
            qDebug( "[ AsObjectStreamer ] - Error streaming in AsPointer!" );
        }
        return true;
    }else{
        return false;
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsTextRunArray& textruns, AsFactory *pFactory )
{
    AS_DEBUG("")
    quint32 numRuns;
    stream >> ( quint32& ) numRuns;

    for ( quint32 i = 0 ; i < numRuns ; ++i )
    {
        quint8 nTag;
        stream >> ( quint8& ) nTag;

        AsTextRun *pTextRun = ( AsTextRun* ) this->asReadAsObject( stream, pFactory );
        if ( pTextRun != NULL )
        {
            textruns.append( *pTextRun );
           // pFactory->asDeleteObject( pTextRun );
        }
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsUndoResourceIndex& index )
{
    AS_DEBUG("")
    // The first data streamed was the number of indexes in the array.
    quint32 numIndexes;
    stream >> ( quint32& ) numIndexes;

//    AsUndoResourceRecord record;
    for ( quint32 i = 0 ; i < numIndexes ; ++i )
    {
        quint32 nID;
        stream >> ( quint32& ) nID;
//        record.asSetResourceID( nID );

        unsigned int type;
        stream >> ( unsigned int& ) type;
//        record.asSetResourceType( ( AsResource::AsEnumObjectType )type );

        QString sResourceFile;
        stream >> ( QString& ) sResourceFile;
//        record.asSetResourceFile( sResourceFile );

        QString sDataFile;
        stream >> ( QString& ) sDataFile;
//        record.asSetDataFile( sDataFile );

        QString sHash;
        stream >> ( QString& ) sHash;
//        record.asSetHash( sHash );

        quint32 objectID;
        stream >> ( quint32& ) objectID;
//        record.asSetObjectID( objectID );

        unsigned int objectType;
        stream >> ( unsigned int& ) objectType;
//        record.asSetObjectType( ( AsObject::AsEnumObjectType )objectType );

//        index.append( record );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, QList<Variant>& list, AsFactory *pFactory )
{
    AS_DEBUG("")
    // The first data streamed was the number of indexes in the array.
    int listCount;
    stream >> ( int& ) listCount;

    for ( int i = 0 ; i < listCount ; i++ )
    {
        Variant var;
        if ( this->asReadVariant( stream, 0, pFactory, var ) )
        {
            list.append( var );
        }
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsOptionList& list )
{
    AS_DEBUG("")
    // The first data streamed was the number of indexes in the array.
    quint32 numOptions;
    stream >> ( quint32& ) numOptions;

   // AsOption option;
    for ( uint i = 0 ; i < numOptions ; ++i )
    {
        QString sOption;
        this->streamIn( stream, sOption );
       // option.asSetOptionString( sOption );

        QStringList alternatives;
        this->streamIn( stream, alternatives );
      //  option.asSetAlternatives( alternatives );

        int points;
        stream >> ( int& ) points;
       // option.asSetPoints( points );

        bool bCorrect;
        this->streamIn( stream, bCorrect );
      //  option.asSetCorrect( bCorrect );

        bool bRemoveOnSimplify;
        this->streamIn( stream, bRemoveOnSimplify );
      //  option.asSetRemoveOnSimplify( bRemoveOnSimplify );

        int nSortPos;
        stream >> ( int& ) nSortPos;
      //  option.asSetSortPosition( nSortPos );

        int weight;
        stream >> ( int& ) weight;
       // option.asSetWeight( weight );

        // Placeholder for deprecated property...
        quint32 nLabelObjectID;
        stream >> ( quint32& ) nLabelObjectID;
        //option.asSetLabelObjectID( nLabelObjectID );

        // Placeholder for deprecated property...
        quint32 nOptionObjectID;
        stream >> ( quint32& ) nOptionObjectID;
        //option.asSetOptionObjectID( nOptionObjectID );

       // list.append( option );
    }
}


void AsObjectStreamer::streamIn( QDataStream& stream, AsStringPairList& list )
{
    AS_DEBUG("")
    quint32 numPairs;
    stream >> ( quint32& ) numPairs;

    for( int i = 0 ; i < ( int ) numPairs ; ++i )
    {
        QString key;
        this->streamIn( stream, key );

        QString value;
        this->streamIn( stream, value );

     //   list.insert( key, value );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsFolderIndex& index )
{
    AS_DEBUG("")
    quint32 num;
    stream >> ( quint32& ) num;

    for( int i = 0 ; i < ( int ) num ; ++i )
    {
        QString key;
        this->streamIn( stream, key );

        QString filename;
        this->streamIn( stream, filename );

        quint64 pos;
        stream >> ( qint64& ) pos;

        quint64 size;
        stream >> ( qint64& ) size;

//        AsFileInfo info;
//        info.m_sFilename = filename;
//        info.m_pos = pos;
//        info.m_size = size;

//        index.insert( key, info );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, AsAsyncTestLevelList& list )
{
    AS_DEBUG("")
    // The first data streamed was the number of indexes in the array.
    quint32 numOptions;
    stream >> ( quint32& ) numOptions;

   // AsLevel level;
    for ( uint i = 0 ; i < numOptions ; ++i )
    {
        int nCorrect;
        stream >> ( int& ) nCorrect;
      //  level.asSetCorrectAnswersRequiredToProgress(nCorrect);

        int nLevel;
        stream >> ( int& ) nLevel;
      //  level.asSetLevelNumber(nLevel);

        bool bRandom;
        this->streamIn( stream, bRandom );
       // level.asSetRandomize( bRandom );

       // list.append( level );
    }
}



void AsObjectStreamer::streamIn( QDataStream& stream, QImage& image)
{
    AS_DEBUG("")
  //  stream >> image;
}

bool AsObjectStreamer::asWriteAsNodes( AsNode *pAsNode, int nMaxGenerations )
{
//    AS_DEBUG("pAsNode->asGetID()" << pAsNode->asGetID())
//    QByteArray aFile;
//    QBuffer bFile( &aFile );
//    if( !bFile.open( QIODevice::ReadWrite ) )
//    {
//        return false;
//    }
//
//    QDataStream sFile( &bFile );
//    sFile.setByteOrder( QDataStream::LittleEndian );
//
//    // First, we write the file type magic number.
//    sFile << ( quint64 ) FILEHEADER_NODES;
//    if( sFile.status() != QDataStream::Ok )
//    {
//        return false;
//    }
//
//    // Next, we write the file type version number.
//    sFile << ( quint16 ) FILEVERSION_NODES_V1;
//    if( sFile.status() != QDataStream::Ok )
//    {
//        return false;
//    }
//
//    // We also write out the version of the streamer we are using.
//    sFile << ( qint16 ) QDataStream::Qt_DefaultCompiledVersion;
//    if( sFile.status() != QDataStream::Ok )
//    {
//        return false;
//    }
//
//    m_nMaxGenerations = nMaxGenerations;
//    m_nCurrentGeneration = 0;
//
//    // Now write the top object.
//    if( !asWriteAsNode( sFile, pAsNode ) )
//    {
//        return false;
//    }
//
//    sFile.device()->reset();
//    if( !m_FileStream.writeRawData( aFile.data(), aFile.size() ) )
//    {
//        return false;
//    }

    return true;
}


AsNode * AsObjectStreamer::asReadAsNodes( AsFactory *pAsFactory )
{
    AS_DEBUG("")
    // read file into a buffer.
    QIODevice * pDevice = m_FileStream.device();
    if( pDevice == 0 )
    {
        return NULL;
    }
    QByteArray aFile;
    aFile = pDevice->readAll();
    QBuffer bFile( &aFile );
    bFile.open( QIODevice::ReadOnly );
    QDataStream stream( &bFile );
    stream.setByteOrder( QDataStream::LittleEndian );
    stream.device()->reset();

    // We must first check that the file we are attempting to read is
    // a flipchart node file.
    quint64 nFirst8Bytes;
    stream >> ( quint64& ) nFirst8Bytes;
    if ( nFirst8Bytes != FILEHEADER_NODES )
    {
        return 0;
    }

    // Next, we must check that we can handle this version of the flipchart node file.
    quint16 nVersion;
    stream >> ( quint16& ) nVersion;
    if ( nVersion != FILEVERSION_NODES_V1 )
    {
        return 0;
    }

    // Ok, we have a flipchart node file.  What version of the streamer was
    // it streamed with??  If it is Qt_4_0 or earlier then we will
    // set our version to it.  If it is later then we cannot handle
    // it??
    qint16 nStreamVersion;
    stream >>( qint16& ) nStreamVersion;
    if ( nStreamVersion > QDataStream::Qt_4_0 )
    {
         m_nStreamVerionUpQt4=true;
    }
    stream.setVersion( nStreamVersion );

    // The first data byte must be an 'open node' tag.
    quint8 nTag;
    stream >> ( quint8& ) nTag;
    if ( nTag != OPEN_NODE )
    {
        return 0;
    }

    // Now we can read the node tree...
    AsNode *pAsNode = asReadAsNode( stream, pAsFactory );

    return pAsNode;
}

AsNode * AsObjectStreamer::asReadAsNode ( QDataStream& stream, AsFactory *pAsFactory, AsNode *pParentNode, int pos )
{
    AS_DEBUG("")
    // One thing that is happening in this function is:
    //   when we don't recognise an object, we ignore it and all it's children

    static int nCurrentDepth= 1; // Start at level 1, first open node read else where
    static int nErrorDepth  = 0;

    AsNode* pAsNode= NULL;


    // Read in the unique ID.
    quint32 nID = 0;
    stream >> ( quint32& ) nID;
    if ( nID == 0 )
    {
        return 0;
    }

    //Read in the AsObject ref ID.
    quint16 nAsObjectRefType = AsObject::AS_OBJECT_NULL;
    stream >> ( quint16& ) nAsObjectRefType;
    quint32 nAsObjectRefID = AsFactory::AS_ID_NULL;
    stream >> ( quint32& ) nAsObjectRefID;
    if ( nAsObjectRefID != AsFactory::AS_ID_NULL )
    {
        if( !nErrorDepth )
        {
            AsObject *pAsObjectRef = pAsFactory->asCreateObject( ( AsObject::AsEnumObjectType )nAsObjectRefType, nAsObjectRefID );

            if ( pAsObjectRef )
            {
                // Call the factory to create the node.
                pAsNode= pAsFactory->asCreateNode( nID );

                if ( pAsNode == 0 )
                {
                    return 0;
                }

                // If this node has a parent then set it.
                if ( pParentNode != 0 )
                {
                    pAsNode->asSetParent( pParentNode, pos );
                }

                pAsNode->asSetAsObjectReference( pAsObjectRef );
            }
            else
            {
                // Couldn't create object
                nErrorDepth= nCurrentDepth;
            }
        }
    }

    int index = 0;
    bool bFinishedNode = false;
    while ( !bFinishedNode )
    {
        // What we do next depends on the next tag.
        // If the next tag is a 'N' then we read in a child node, recursively.
        // If the next tag is a 'C' then we read in a soft child reference.
        quint8 nTag;
        stream >> ( quint8& ) nTag;

        switch ( nTag )
        {
            case OPEN_NODE:
                nCurrentDepth++;
                asReadAsNode( stream, pAsFactory, pAsNode, index );
                index++;
                break;

            case OPEN_SOFT_CHILD:
                asReadSoftChild( stream, pAsFactory, pAsNode );
                break;

            default:
                bFinishedNode = true;
                if( nErrorDepth == nCurrentDepth )
                {
                    nErrorDepth= 0;
                }
                // Don't decrement on last end node tag (we can't increment on first)
                // remember this class stays alive over many node file reads, inc. canopy
                if( nCurrentDepth != 1 )
                {
                    nCurrentDepth--;
                }
                // We're just going to return from building this node.
                break;
        }
    }
    return pAsNode;
}



void AsObjectStreamer::asReadSoftChild( QDataStream& stream, AsFactory *pAsFactory, AsNode *pAsNode )
{
    AS_DEBUG("")
    quint32 nSoftChildID;
    stream >> ( quint32& ) nSoftChildID;

    if( pAsNode )
    {
        AsNode *pSoftChildNode = pAsFactory->asCreateNode( nSoftChildID );
        if ( pSoftChildNode != 0 )
        {
            pAsNode->asAddSoftChild( pSoftChildNode );
        }
    }

    quint8 nTag;
    stream >> ( quint8& ) nTag;
}
