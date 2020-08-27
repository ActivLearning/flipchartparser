/** @file asactionlaunchminiapp.cpp
 * Implements the AsActionLaunchMiniApp class.
 * Copyright (C) 2006-2011 Promethean Limited. All Rights Reserved.
 */

#include "asactionlaunchminiapp.h"



#include "asflipchart.h"

#include "../asfactory.h"


#include "asflipchart.h"





AsActionLaunchMiniApp::AsActionLaunchMiniApp(AsFactory * pAsFactory) : AsAction(pAsFactory)
{
    asSetType(AsObject::AS_OBJECT_LAUNCH_MINIAPP_ACTION);
}


AsActionLaunchMiniApp::AsActionLaunchMiniApp(const AsActionLaunchMiniApp& actionApp) : AsAction(actionApp)
{
    asCopy(actionApp);
}


AsActionLaunchMiniApp& AsActionLaunchMiniApp::operator= ( const AsActionLaunchMiniApp& actionApp )
{
    if( &actionApp != this )
    {
        AsAction::operator =( actionApp );
        asCopy( actionApp );
    }
    return *this;
}


void AsActionLaunchMiniApp::asCopy( const AsActionLaunchMiniApp& actionApp )
{
    m_appUUID = actionApp.m_appUUID;
    m_lastKnownAppName = actionApp.m_lastKnownAppName;
}


QHash<QString, quint16>& AsActionLaunchMiniApp::m_lProperties()
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        enum AsEnumProperty
        {
            // From AsObject...
            AS_PROPERTY_DATETIMECREATED = 1,

            // From AsActionLaunchMiniApp...
            AS_PROPERTY_APPUUID,
            AS_PROPERY_LASTKNOWNAPPNAME,

            // From AsAction...
            AS_PROPERTY_ACTIONFEATURETYPE
        };

        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
	    HashProperties.insert( "asActionFeatureType", AS_PROPERTY_ACTIONFEATURETYPE );

	    // From AsActionLaunchMiniApp...
        HashProperties.insert( "asAppUUID", AS_PROPERTY_APPUUID);
        HashProperties.insert( "asLastKnownAppName", AS_PROPERY_LASTKNOWNAPPNAME);
    }

    return HashProperties;
}


void AsActionLaunchMiniApp::asRun( AsUser* /*pUser*/, QPointF )
{
    qDebug( "[ AsActionLaunchMiniApp ] - asRun ");

//    AsApp *pApp = AsApp::asInstance();
//    AsFlipchart * pFlipchart = pApp->asGetFlipchartManager().asGetCurrentFlipchart();
//
//    if (!pFlipchart)
//        return;
//
//    asDoConnections();
//
//    //run the mini app
//    AppFramework::AppController& appController = AppFramework::AppController::instance();
//
//    AppFramework::AppInfoList appList = appController.installedAppInfoList();
//    bool appFound = false;
//
//    for (int i=0; i < appList.count(); i++)
//    {
//        const AppFramework::AppInfo& appInfo = appList.at(i);
//        if (appInfo.id() == m_appUUID)
//        {
//            int runError = appController.loadApplication(appInfo);
//
//            appFound = true;
//
//            if (runError < 0)
//            {
//                //<TODO> should we display atlas errors as per enum AppFramework::AppController::Error?
//
//                QString sMsg(AsLocale::asGetString( AsLocale::AS_STRING_APPLICATION_CANNOT_BE_STARTED )
//							.arg(appInfo.name("")));
//                AsStudio::asInstance()->asGetGuiControllerPointer()->asStandardMessageBox(QMessageBox::Critical,
//                                                                                  AsLocale::asGetString( AsLocale::AS_STRING_OPEN_MINIAPP ),
//								                                                  sMsg, QMessageBox::Ok);
//            }
//        break;
//        }
//    }
//
//    if (!appFound)
//    {
//        //Contruct an error message based on the last known application name.
//        QString sMsg(AsLocale::asGetString( AsLocale::AS_STRING_A_PROBLEM_HAS_OCCURED_WHILE_OPENING_THIS_APPLICATION_THE_APPLICATION_CANNOT_BE_FOUND )
//						.arg(m_lastKnownAppName));
//        AsStudio::asInstance()->asGetGuiControllerPointer()->asStandardMessageBox(QMessageBox::Critical,
//                                                                                  AsLocale::asGetString( AsLocale::AS_STRING_OPEN_MINIAPP ),
//                                                                                  sMsg, QMessageBox::Ok);
//    }
}


void AsActionLaunchMiniApp::asResetPropertyIndex()
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}


const QString& AsActionLaunchMiniApp::asGetAppUUID() const
{
    return m_appUUID;
}


void AsActionLaunchMiniApp::asSetAppUUID(const QString& aAppUUID)
{
    m_appUUID = aAppUUID;
}


const QString& AsActionLaunchMiniApp::asGetLastKnownAppName() const
{
    return m_lastKnownAppName;
}


void AsActionLaunchMiniApp::asSetLastKnownAppName(const QString& aAppName)
{
    m_lastKnownAppName = aAppName;
}

QString AsActionLaunchMiniApp::typeName()
{
    return "actionLaunchMiniApp";
}
