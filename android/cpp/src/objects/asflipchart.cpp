#include "asflipchart.h"
#include "../io/asfileio.h"
#include "../io/asnode.h"

#include "../asfactory.h"
#include "../util/commonlog.h"

AsFlipchart::AsFlipchart( AsFactory *pAsFactory ):AsObject(pAsFactory)
{

}


AsFlipchart::~AsFlipchart()
{

}


AsNode * AsFlipchart::asLoadPageObjects( int nPageNumber )
{

//    QString msg = QString("Page number: %1").arg( nPageNumber );
//    As::writeErrorLog( "AsFlipchart", "asLoadPageObjects", qPrintable( msg ), As::LOGLEVEL_TRACING );

    AsNode* pFlipchartNode = this->asGetIndexNode();

    AsNode *pPageNode = pFlipchartNode->asGetChildAt(nPageNumber);
//    AsNode *pCurrentNode = m_pCurrentPageNode;
//
//    // Only load if the requested page is not the current page.  Don't re-load!
//    if ( pCurrentNode == pPageNode )
//    {
//        qDebug( "[ AsApp ] - Warning - re-loading current page!" );
//    }

    AsFileIO fileIO( pFlipchartNode );
    pPageNode = fileIO.asLoadPage( pPageNode );
    if( pPageNode == NULL )
    {
        QString er;

        er = "Failed to load page " + QString::number( nPageNumber ) + " from flipchart ";


        er += asGetFlipchartWorkingPath();

        qWarning( "%s", er.toUtf8().data() );
//        As::writeErrorLog( "AsApp", "asLoadPageObjects", qPrintable(er), As::LOGLEVEL_ERROR );
    }

    //qDebug() << "[ AsApp ] - Loading page" << nPageNumber << "for flipchart at address:" << m_pCurrentFlipchartNode;

    return pPageNode;
}

const QString& AsFlipchart::asGetFlipchartWorkingPath( void ) const
{
    return m_sWorkingPath;
}


void AsFlipchart::asSetFlipchartWorkingPath( QString& sPath )
{
    m_sWorkingPath = sPath;
    LOGDEBUG("Flipchart WorkPath %s", sPath.toUtf8().data());
}

void AsFlipchart::asSetResourceRegister(AsResourceRegister *asResourceRegister)
{
    m_pResRegister = asResourceRegister;
}

AsResourceRegister *AsFlipchart::asGetResourceRegister()
{
    return m_pResRegister;
}
