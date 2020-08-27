// Implements the AsActionApp class.
// $Author: Paul Ellis.

#include "asactionapp.h"


#include "../io/asnode.h"

#include "../asfactory.h"

#include "asflipchart.h"



AsActionApp::AsActionApp(AsFactory * pAsFactory) : AsAction(pAsFactory), m_nClockCount(0)
{
    asSetType(AsObject::AS_OBJECT_APPACTION);

} 

AsActionApp::AsActionApp(const AsActionApp& actionApp) : AsAction(actionApp)
{
    asCopy(actionApp);
}

AsActionApp::~AsActionApp()
{

}

void AsActionApp::operator= ( const AsActionApp& actionApp )
{
    AsAction::operator =( actionApp );
    this->asCopy( actionApp );
}

void AsActionApp::asCopy( const AsActionApp& actionApp )
{
    m_actionType = actionApp.asGetActionType();
    m_nClockCount = actionApp.asGetClockCount();
}

QHash<QString, quint16>& AsActionApp::m_lProperties( void )
{
    static QHash<QString, quint16> HashProperties;

    if ( HashProperties.isEmpty() )
    {
        // From AsObject...
        HashProperties.insert( "asDateTimeCreated", ( quint16 )AsActionApp::AS_PROPERTY_DATETIMECREATED );

        // From AsAction...
	HashProperties.insert( "asActionFeatureType", ( quint16 )AsActionApp::AS_PROPERTY_ACTIONFEATURETYPE );
        
	// From AsActionApp...
        HashProperties.insert( "asActionAppType", ( quint16 )AsActionApp::AS_PROPERTY_ACTIONAPPTYPE );
        HashProperties.insert( "asClockCount", ( quint16 )AsActionApp::AS_PROPERTY_CLOCKCOUNT );
    }

    return HashProperties;
}

void AsActionApp::asRun( AsUser* pUser, QPointF unUsed )
{

}

void AsActionApp::asDoRun( AsUser* pUser, QPointF )
{
//    qDebug( "[ AsActionApp ] - asRun, m_actionType is %d.", m_actionType );
//    As::writeErrorLog( "AsActionApp", "asDoRun", qPrintable( QString::number( m_actionType ) ), As::LOGLEVEL_CRASHSUPPORT );
//
//    AsStudio *pStudio = AsStudio::asInstance();
//    AsGuiController *pGuiController = pStudio->asGetGuiControllerPointer();
//    AsApp *pApp = AsApp::asInstance();
//    AsFlipchart * pFlipchart = pApp->asGetFlipchartManager().asGetCurrentFlipchart();
//
//    this->asDoConnections();
//    switch( (AsActionApp::AsEnumAppActionType) m_actionType )
//    {
//	case AsActionApp::AS_APPACTION_ABOUT_DLG:
//	    AsStudio::asInstance()->asShowAboutBox();
//	    break;
//
//	case AsActionApp::AS_APPACTION_OPEN_MY_FLIP_DLG:
//	    AsStudio::asInstance()->asOpenMyFlipcharts();
//	    break;
//
//	case AsActionApp::AS_APPACTION_OPEN_SHARED_FLIP_DLG:
//	    AsStudio::asInstance()->asOpenSharedFlipcharts();
//	    break;
//
//	case AsActionApp::AS_APPACTION_OPEN_OTHER_FLIP_DLG:
//	    AsStudio::asInstance()->asOpenOtherFlipcharts();
//	    break;
//
//	case AsActionApp::AS_APPACTION_SAVE_MY_FLIP_DLG:
//	    pFlipchart->asSaveToMyFlipcharts();
//	    break;
//
//	case AsActionApp::AS_APPACTION_SAVE_SHARED_FLIP_DLG:
//	    pFlipchart->asSaveToSharedFlipcharts();
//	    break;
//
//	case AsActionApp::AS_APPACTION_SAVE_OTHER_FLIP_DLG:
//	    pFlipchart->asSaveToOtherFlipcharts();
//	    break;
//
//	case AsActionApp::AS_APPACTION_SEND_VIA_EMAIL:
//	    AsStudio::asInstance()->asSendViaEmail();
//	    break;
//
//        case AsActionApp::AS_APPACTION_EDITLRSGROUPS:
//            AsStudio::asInstance()->asEditLRSGroups();
//            break;
//
//	case AsActionApp::AS_APPACTION_QUIT:
//	    AsUtil::asConnect( this, SIGNAL( asLaunchQuit() ), pApp, SLOT( asQuit() ), Qt::QueuedConnection );
//	    emit asLaunchQuit();
//	    break;
//
//	    //case AsActionApp::AS_APPACTION_SHOWPAGENOTES:
//	    //    {
//	    //        AsNode *pThis = asGetIndexNode();
//	    //        AsNode *pFlipchartNode = AsNode::asGetAscendant( pThis, AsObject::AS_OBJECT_FLIPCHART );
//	    //        AsStudio::asInstance()->asShowPageNotes( pFlipchartNode );
//	    //    }
//	    //    break;
//
//        case AsActionApp::AS_APPACTION_RESETPAGE:
//	{
//	    AsStudio::asInstance()->asResetPage();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_UNDO:
//	{
//	    //pUser->asClearSelection();
//	    AsStudio::asInstance()->asFireForceRelease();
//	    this->m_pAsFactory->asGetUndoController()->asUndo();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_REDO:
//	{
//	    this->m_pAsFactory->asGetUndoController()->asRedo();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_SHOWREVEALER:
//	{
//	    AsGuiEvent guiEvent( pUser );
//	    AsStudio::asInstance()->asToggleRevealer( &guiEvent );
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CLEARANNOTATIONS:
//	{
//	    AsStudio::asInstance()->asClearAnnotations();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CLEARBACKGROUND:
//	{
//	    AsStudio::asInstance()->asClearBackground();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CLEARGRID:
//	{
//	    AsStudio::asInstance()->asClearGrid();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CLEAROBJECTS:
//	{
//	    AsStudio::asInstance()->asClearObjects();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CLEARPAGE:
//	{
//	    AsStudio::asInstance()->asClearPage();
//	}
//	break;
//
//		case AsActionApp::AS_APPACTION_GROUP:
//			{
//                AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//                if (pSelectTool)
//                {
//				    pSelectTool->asGroupUsingOldSelection( pUser );
//                }
//			}
//			break;
//
//		case AsActionApp::AS_APPACTION_UNGROUP:
//			{
//                AsToolSelect* pSelectTool = (AsToolSelect*)pUser->asGetFeature( AsObject::AS_OBJECT_TOOL_SELECT );
//                if (pSelectTool)
//                {
//				    pSelectTool->asUngroupUsingOldSelection( pUser );
//                }
//			}
//			break;
//
//        case AsActionApp::AS_APPACTION_PASTE:
//	{
//	    AsStudio::asInstance()->asPasteObjectsFromClipboard();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_RECTCAMERA:
//	{
//	    AsStudio::asInstance()->asCameraArea();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_ANALOGCLOCK:
//	{
//	    AsStudio::asInstance()->asShowClock(AsClock::AS_CLOCK_ANALOG);
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_DIGITALCLOCK:
//	{
//	    AsStudio::asInstance()->asShowClock(AsClock::AS_CLOCK_DIGITAL);
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_ANADIGICLOCK:
//	{
//	    AsStudio::asInstance()->asShowClock(AsClock::AS_CLOCK_BOTH);
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_COUNTDOWNCLOCK:
//	{
//	    AsStudio::asInstance()->asShowClock(AsClock::AS_CLOCK_COUNTDOWN, m_nClockCount);
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_COUNTUPCLOCK:
//	{
//	    AsStudio::asInstance()->asShowClock(AsClock::AS_CLOCK_COUNTUP, m_nClockCount);
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_SHOWHELP:
//	{
//	    AsStudio::asInstance()->asShowHelp();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_PRINTDLG:
//	{
//	    pFlipchart->asPrintPages();
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_QUESTIONEDITOR:
//	{
//	    AsStudio::asInstance()->asEditQuestionOrAsyncTest();
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_QUESTIONMASTER:
//	{
//	    AsStudio::asInstance()->asInsertQuestion();
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_TOGGLERULER_DEFAULT:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateRuler();
//	    }
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_TOGGLERULER_MM:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateRuler(AsRuler::AS_UNITS_MM,
//                                AsRuler::AS_UNITS_NONE);
//	    }
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_TOGGLERULER_CM:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateRuler(AsRuler::AS_UNITS_CM,
//                                AsRuler::AS_UNITS_NONE);
//	    }
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_TOGGLERULER_INCH:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateRuler(AsRuler::AS_UNITS_INCH,
//                                AsRuler::AS_UNITS_NONE);
//	    }
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_TOGGLEPROTRACTOR_DEFAULT:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateProtractor(AsProtractor::AS_PROTRACTOR_TYPE_DEFAULT);
//	    }
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TOGGLEPROTRACTOR_HALF:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateProtractor(AsProtractor::AS_PROTRACTOR_TYPE_HALF);
//	    }
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_TOGGLEPROTRACTOR_FULL:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateProtractor(AsProtractor::AS_PROTRACTOR_TYPE_FULL);
//	    }
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_TOGGLECOMPASS:
//	{
//	    AsGuiController *pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if( pGui != NULL )
//	    {
//            pGui->asCreateCompass();
//	    }
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_1024X768FLIPCHART:
//	{
//	    AsStudio::asInstance()->asNew1024X768Flipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_1152X864FLIPCHART:
//	{
//	    AsStudio::asInstance()->asNew1152X864Flipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_1280X1024FLIPCHART:
//	{
//	    AsStudio::asInstance()->asNew1280X1024Flipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CUSTOMSIZEFLIPCHART:
//	{
//	    AsStudio::asInstance()->asNewCustomSizeFlipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SCREENSIZEFLIPCHART:
//	{
//	    AsStudio::asInstance()->asNewScreenSizeFlipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CALCULATOR:
//	{
//	    AsStudio::asInstance()->asToggleCalc();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_KEYBOARD:
//	{
//	    AsStudio::asInstance()->asOnScreenKeyboard();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SPOTLIGHT_CIRCULAR:
//	{
//	    AsStudio::asInstance()->asFireForceRelease();
//	    AsStudio::asInstance()->asToggleSpotlight(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SPOTLIGHT_INVERSECIRCULAR:
//	{
//	    AsStudio::asInstance()->asFireForceRelease();
//	    AsStudio::asInstance()->asToggleSpotlightReversed(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SPOTLIGHT_RECTANGULAR:
//	{
//	    AsStudio::asInstance()->asFireForceRelease();
//	    AsStudio::asInstance()->asToggleSpotlightSquare(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SPOTLIGHT_INVERSERECTANGULAR:
//	{
//	    AsStudio::asInstance()->asFireForceRelease();
//	    AsStudio::asInstance()->asToggleSpotlightSquareReversed(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DEVICEREGISTRATION:
//	{
//	    AsStudio::asInstance()->asLaunchDevReg();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DICEROLLER:
//	{
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asDiceRoller();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_EDITPROFILE:
//	{
//	    AsObject::AsEnumObjectType type = asGetFeatureType();
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asShowProfileWidget(type);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FLIPCHARTSPELLCHECKER:
//	{
//	    AsStudio::asInstance()->asSpellcheckFlipchart(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FRACTIONCREATOR:
//	{
//	    //AsStudio::asInstance()->asFractions(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CAMERA_POINT2POINT:
//	{
//	    AsStudio::asInstance()->asCameraPointToPoint(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CAMERA_FREEHAND:
//	{
//	    AsStudio::asInstance()->asCameraFreehand(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CAMERA_WINDOW:
//	{
//	    AsStudio::asInstance()->asCameraWindow(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FULLSCREENPHOTO_TOCURRENTPAGE:
//	{
//	    AsStudio::asInstance()->asCameraFullscreenCurrentPage();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FULLSCREENPHOTO_TONEWPAGE:
//	{
//	    AsStudio::asInstance()->asCameraFullscreenNewPage();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FULLSCREENPHOTO_TOCLIPBOARD:
//	{
//	    AsStudio::asInstance()->asCameraFullscreenClipboard();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FULLSCREENPHOTO_TOMYRESOURCELIBRARY:
//	{
//	    AsStudio::asInstance()->asCameraFullscreenMyResourceLibrary();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FULLSCREENPHOTO_TOSHAREDRESOURCELIBRARY:
//	{
//	    AsStudio::asInstance()->asCameraFullscreenSharedResourceLibrary();
//	}
//	break;
//	case AsActionApp::AS_APPACTION_FULLSCREENPHOTO:
//	{
//	    AsStudio::asInstance()->asCameraFullscreen();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_GRIDDESIGNER:
//	{
//	    AsStudio::asInstance()->asGridDesigner(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_NEWFLIPCHART:
//	{
//	    AsStudio::asInstance()->asNewFlipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CLOSEFLIPCHART:
//	{
//	    AsUtil::asConnect( this, SIGNAL( asLaunchCloseFlipchart() ), pGuiController, SLOT( asCloseActiveCanvas() ), Qt::QueuedConnection );
//	    emit asLaunchCloseFlipchart();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_IMPORTPPT_ASIMAGES:
//	{
//	    AsStudio::asInstance()->asImportPptToFlipChartAsImages();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_IMPORTPPT_ASOBJECTS:
//	{
//	    AsStudio::asInstance()->asImportPptToFlipChartAsObjects();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_FULLSCREENRECORDER:
//	{
//	    AsStudio::asInstance()->asScreenRecorder(0);
//	}
//	break;
//	case AsActionApp::AS_APPACTION_AREASCREENRECORDER:
//	{
//	    AsStudio::asInstance()->asAreaScreenRecorder(0);
//	}
//	break;
//	case AsActionApp::AS_APPACTION_SOUNDRECORDER:
//	{
//	    AsStudio::asInstance()->asSoundRecorder(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TEACHERLOCK:
//	{
//	    AsStudio::asInstance()->asTeacherLock();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TICKERTAPE:
//	{
//	    AsStudio::asInstance()->asShowTickerTape(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TIMESTAMP:
//	{
//	    AsStudio::asInstance()->asTimestamp(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_NEWPAGE_AFTERCURRENT:
//	{
//	    AsStudio::asInstance()->asInsertPageBlank(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SETPAGEBACKGROUND:
//	{
//	    AsStudio::asInstance()->asSetPageBackground(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_EXTRACTTEXT:
//	{
//	    AsStudio::asInstance()->asExtractText(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_INSERTLINKTOFILE:
//	{
//	    AsStudio::asInstance()->asInsertFileLink(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_INSERTLINKTOWEBSITE:
//	{
//	    AsStudio::asInstance()->asInsertWebsiteLink(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_INSERTMEDIAFROMFILE:
//	{
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asInsertFromFile(0);
//	}
//	break;
//
//    case AsActionApp::AS_APPACTION_ACTIVIEW:
//	{
//#ifndef Q_OS_LINUX
//            AsStudio::asInstance()->asLaunchActiView();
//#endif
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_ACTIONSBROWSER:
//	{
//	    if (AsStudio::asInstance()->asGetDefaults()->asGetDerivativeName() != ASDERIVATIVE_PERSONAL)
//	    {
//		quint8 browserID = 0;
//		AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser(browserID, AsObject::AS_OBJECT_COMMAND_ACTIONBROWSER);
//	    }
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_OBJECTBROWSER:
//	{
//	    quint8 browserID = 0;
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser(browserID, AsObject::AS_OBJECT_COMMAND_OBJECTBROWSER);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_PAGEBROWSER:
//	{
//	    quint8 browserID = 0;
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser( browserID, AsObject::AS_OBJECT_COMMAND_PAGEBROWSER );
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_PROPERTIESBROWSER:
//	{
//	    quint8 browserID = 0;
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser(browserID, AsObject::AS_OBJECT_COMMAND_PROPERTYBROWSER);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_RESOURCEBROWSER:
//	{
//	    quint8 browserID = 0;
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser(browserID, AsObject::AS_OBJECT_COMMAND_RESOURCEBROWSER);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_VOTINGBROWSER:
//	{
//	    quint8 browserID = 0;
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser(browserID, AsObject::AS_OBJECT_COMMAND_VOTINGBROWSER);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SHOWPAGENOTES:
//	{
//	    quint8 browserID = 0;
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleBrowser(browserID, AsObject::AS_OBJECT_COMMAND_NOTEBROWSER);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SETROTATIONCENTER:
//	{
//	    AsStudio::asInstance()->asToggleXYOrigin(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_EXPRESSPOLL:
//	{
//	    AsStudio::asInstance()->asToggleExpressVoteWidget();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_STARTSTOPVOTE:
//	{
//	    AsStudio::asInstance()->asStartStopVote();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_HIDEGRID:
//	{
//	    AsStudio::asInstance()->asHideGrid();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SNAPTOGRID:
//	{
//	    AsStudio::asInstance()->asSnapToGrid();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TOOLBOXROLLUP:
//	{
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleToolBarRollUp();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TOOLBOXROLLIN:
//	{
//	    AsStudio::asInstance()->asGetGuiControllerPointer()->asToggleToolBarRollIn();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_NEWPAGE_BEFORECURRENT:
//	{
//	    AsStudio::asInstance()->asInsertPageBlankBeforeCurrent();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SELECTALL:
//	{
//	    AsStudio::asInstance()->asSelectAll();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DUPLICATEPAGEBEFORE:
//	{
//	    int pos = AsApp::asInstance()->asGetCurrentPage()->asGetMyChildPosition();
//	    pos--;
//	    AsStudio::asInstance()->asDuplicateCurrentPage(pos);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DUPLICATEPAGEAFTER:
//	{
//	    int pos = AsApp::asInstance()->asGetCurrentPage()->asGetMyChildPosition();
//	    AsStudio::asInstance()->asDuplicateCurrentPage(pos);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DUPLICATEPAGEATEND:
//	{
//	    int pos = pApp->asGetFlipchartManager().asGetCurrentFlipchartNode()->asGetChildCount();
//	    AsStudio::asInstance()->asDuplicateCurrentPage(pos);
//	}
//	break;
//
//	case AsActionApp::AS_APPLICATION_OSWEBBROWSER:
//	{
//	    AsStudio::asInstance()->asOpenOSWebBrowser();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_COLOURPICKER:
//	{
//	    AsGuiController* pGuiController = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if ( pGuiController )
//		pGuiController->asLaunchColourPicker();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SEARCHPLANET:
//	{
//	    AsStudio::asInstance()->asSearchPlanet();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_PAUSEVOTE:
//	{
//	    AsStudio::asInstance()->asSetPauseVote(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DUALMODE:
//	{
//	    if (AsStudio::asInstance()->asGetDefaults()->asGetDerivativeName() != ASDERIVATIVE_PERSONAL)
//	    {
//		AsStudio::asInstance()->asToggleDualMode();
//	    }
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_EXPORTTESTTOEXCEL:
//	{
//	    AsStudio::asInstance()->asExportTestToExcel();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SHOWDASHBOARD:
//	{
//	    AsGuiController* pGuiController = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    pGuiController->asShowDashboard();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_EDITSTUDENTDATABASE:
//	{
//	    AsStudio::asInstance()->asEditStudentDatabase();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_NEWBROWSERWINDOW:
//	{
//	    AsGuiController* pGuiController = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    pGuiController->asNewBrowserWindow();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_SOUNDCONTROLLER:
//	{
//	    AsStudio::asInstance()->asSoundController(0);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_TOGGLEDESIGNMODE:
//	{
//	    if (AsStudio::asInstance()->asGetDefaults()->asGetDerivativeName() != ASDERIVATIVE_PERSONAL)
//	    {
//		AsStudio::asInstance()->asToggleDesignMode();
//	    }
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_ASSIGNSTUDENTSTODEVICES:
//	{
//	    AsStudio::asInstance()->asAssignStudentsToDevices();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_INSERTASYNCTEST:
//	{
//	    AsStudio::asInstance()->asInsertAsyncTest();
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_CUTPAGE:
//	{
//	    AsNode *pPageNode = AsApp::asInstance()->asGetCurrentPage();
//	    QList<AsNode *> nodes;
//	    nodes.append(pPageNode);
//	    AsStudio::asInstance()->asCutObjectsToClipboard(nodes, pUser);
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_COPYPAGE:
//	{
//	    AsNode *pPageNode = AsApp::asInstance()->asGetCurrentPage();
//	    QList<AsNode *> nodes;
//	    nodes.append(pPageNode);
//	    AsStudio::asInstance()->asCopyObjectsToClipboard( nodes );
//	}
//	break;
//
//	case AsActionApp::AS_APPACTION_DELETEPAGE:
//	{
//	    AsNode *pPageNode = AsApp::asInstance()->asGetCurrentPage();
//	    QList<AsNode *> nodes;
//	    nodes.append(pPageNode);
//	    pUser->asContextDelete( nodes );
//	}
//	break;
//
//        case AsActionApp::AS_APPACTION_SHOWPENMODIFIER:
//	{
//
//	    // Select pen tool, then show pen mod toolbar.
//	    AsGuiEvent guiEvent( pUser );
//	    guiEvent.asSetFeature( AsObject::AS_OBJECT_TOOL_PEN );
//	    guiEvent.asSetPenWidth(-1);
//	    AsStudio::asInstance()->asSelectTool( &guiEvent );
//	    AsStudio::asInstance()->asShowPenModifier();
//	}
//	break;
//
//
//        // Pen mod actions. Note, 0 is freeform, and is not used.
//        case AsActionApp::AS_APPACTION_PENMODIFIER_LINE:
//	{
//	    asSelectPenModifierAction( pUser, 1 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_HORIZONTAL_LINE:
//	{
//	    asSelectPenModifierAction( pUser, 2 );
//	}
//        break;
//
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_VERTICAL_LINE:
//	{
//	    asSelectPenModifierAction( pUser, 3 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_SQUARE:
//	{
//	    asSelectPenModifierAction( pUser, 4 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_RECTANGLE:
//	{
//	    asSelectPenModifierAction( pUser, 5 );
//	}
//        break;
//
//	case AsActionApp::AS_APPACTION_PENMODIFIER_CIRCLE:
//	{
//	    asSelectPenModifierAction( pUser, 6 );
//	}
//        break;
//
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_ELLIPSE:
//	{
//	    asSelectPenModifierAction( pUser, 7 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_CURVE:
//	{
//	    asSelectPenModifierAction( pUser, 8 );
//	}
//        break;
//
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_SEMICIRCLE:
//	{
//	    asSelectPenModifierAction( pUser, 9 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_CALLOUT1:
//	{
//	    asSelectPenModifierAction( pUser, 10 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_CALLOUT2:
//	{
//	    asSelectPenModifierAction( pUser, 11 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_ARROWLINE:
//	{
//	    asSelectPenModifierAction( pUser, 12 );
//	}
//        break;
//
//        case AsActionApp::AS_APPACTION_PENMODIFIER_LINE_CHAIN:
//	{
//	    asSelectPenModifierAction( pUser, 13 );
//	}
//        break;
//
//	case AsActionApp::AS_APPACTION_TOGGLE_SET_SQUARE:
//	{
//	    AsGuiController* pGui = AsStudio::asInstance()->asGetGuiControllerPointer();
//	    if (pGui)
//	    {
//            pGui->asCreateSetSquare();
//	    }
//	}
//	break;
//
//	default:
//	    //Do Nothing
//	    break;
//    }
}

void AsActionApp::asResetPropertyIndex( void )
{
    AsObject::asSetPropertyIterator( &m_lProperties );
}

void AsActionApp::asSetActionType( AsActionApp::AsEnumAppActionType actionType )
{
    m_actionType = actionType;
}

AsActionApp::AsEnumAppActionType AsActionApp::asGetActionType( void ) const
{
    return m_actionType;
}

void AsActionApp::asSetClockCount(int nClockCount)
{
    m_nClockCount = nClockCount;
}

int AsActionApp::asGetClockCount() const
{
    return m_nClockCount;
}

void AsActionApp::asSelectPenModifierAction( AsUser* pUser, int index )
{
    // [BRS] Todo - to be the same as v3 we must not force select the pen tool - we
    // must keep the current tool if it is Pen, highlighter or magic ink.

    // Select pen tool, show pen mod toolbar, then select the pen mod.
//    AsGuiEvent guiEvent( pUser );
//    guiEvent.asSetFeature( AsObject::AS_OBJECT_TOOL_PEN ); // [BRS] fix this - dont select if already have suitable tool.
//    guiEvent.asSetPenWidth(-1);
//    AsStudio::asInstance()->asSelectTool( &guiEvent );
//    // Force select the required pen mod shape.
//    AsStudio::asInstance()->asInitialisePenModifierToolBar();
//    AsStudio::asInstance()->asStudioForceSelectPenModifier( index );
}

QString AsActionApp::typeName()
{
    return "actionApp";
}
