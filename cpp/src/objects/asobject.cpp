#include "asobject.h"
//#include "asproperty.h"
#include "../io/asnode.h"
#include "../global/global.h"
#include <QTextStream>

//#include "../convert.h"
#include "../util/commonlog.h"
#include "../asfactory.h"
#include "../resources/asresourcemanager.h"
#include "../resources/asresource.h"

AsObject::AsObject() : m_pAsFactory(nullptr),
                       m_pResource(nullptr)
{
}

AsObject::AsObject(AsFactory *pAsFactory) : m_pAsFactory(pAsFactory),
                                            m_pResource(nullptr),
                                            m_tType(AsObject::AS_OBJECT_NULL),
                                            m_nID(0),
                                            m_pProperties(0)
{
    //  mpropertyList=QHash<int,QVariant>();
}

QHash<QString, AsObject::AsEnumObjectType>& AsObject::m_lTypes( void )
{
    // Here we create a new static hash table only on the first call to
    // this static method.
    static QHash<QString, AsObject::AsEnumObjectType> *hashTypes = new QHash<QString, AsObject::AsEnumObjectType>();

    // We only want to load the table once.
    if ( hashTypes->isEmpty() )
    {
        // Objects...
        hashTypes->insert( "AsAnnotation", AsObject::AS_OBJECT_ANNOTATION );
        hashTypes->insert( "AsAnnotationRes", AsObject::AS_OBJECT_ANNOTATIONRES );
        hashTypes->insert( "AsLine", AsObject::AS_OBJECT_LINE );
        hashTypes->insert( "AsLineRes", AsObject::AS_OBJECT_LINERES );
        hashTypes->insert( "AsShape", AsObject::AS_OBJECT_SHAPE );
        hashTypes->insert( "AsShapeRes", AsObject::AS_OBJECT_SHAPERES );
        hashTypes->insert( "AsImage", AsObject::AS_OBJECT_IMAGE );
        hashTypes->insert( "AsImageRes", AsObject::AS_OBJECT_IMAGERES );
        hashTypes->insert( "AsText", AsObject::AS_OBJECT_TEXT );
        hashTypes->insert( "AsTextRes", AsObject::AS_OBJECT_TEXTRES );
        hashTypes->insert( "AsGrid", AsObject::AS_OBJECT_GRID );
        hashTypes->insert( "AsGridStyle", AsObject::AS_OBJECT_GRIDSTYLE );
        hashTypes->insert( "AsAppAction", AsObject::AS_OBJECT_APPACTION );
        hashTypes->insert( "AsMoveAction", AsObject::AS_OBJECT_MOVEACTION );
        hashTypes->insert( "AsMotion", AsObject::AS_OBJECT_MOTIONRES );
        hashTypes->insert( "AsNavAction", AsObject::AS_OBJECT_NAVIGATEACTION );
        hashTypes->insert( "AsObjAction", AsObject::AS_OBJECT_ACTIONONOBJECT );
        hashTypes->insert( "AsOpenExtAction", AsObject::AS_OBJECT_ACTIONOPENEXTERNAL );
        hashTypes->insert( "AsMediaFileRes", AsObject::AS_OBJECT_MEDIAFILERES );
        hashTypes->insert( "AsSelectToolAction", AsObject::AS_OBJECT_SELECTTOOLACTION );
        hashTypes->insert( "AsConnector", AsObject::AS_OBJECT_CONNECTOR );
        hashTypes->insert( "AsLabel", AsObject::AS_OBJECT_LABEL );
        hashTypes->insert( "AsQuestion", AsObject::AS_OBJECT_QUESTION );
        hashTypes->insert( "AsTest", AsObject::AS_OBJECT_TEST );
        hashTypes->insert( "AsAsyncTest", AsObject::AS_OBJECT_ASYNCTEST );
        hashTypes->insert( "AsMediaContainer", AsObject::AS_OBJECT_MEDIACONTAINER );
        hashTypes->insert( "AsMathML", AsObject::AS_OBJECT_MATHML );
        hashTypes->insert( "AsVerText", AsObject::AS_OBJECT_VERTEXT );

        // Groups...
        hashTypes->insert( "AsFlipchart", AsObject::AS_OBJECT_FLIPCHART );
        hashTypes->insert( "AsPage", AsObject::AS_OBJECT_PAGE );
        hashTypes->insert( "AsRenderableGroup", AsObject::AS_OBJECT_ASRENDERABLEGROUP );
        hashTypes->insert( "AsAS4", AsObject::AS_OBJECT_AS4 );

        // Modifiers...
        hashTypes->insert( "AsTransform", AsObject::AS_OBJECT_TRANSFORM );

        // Utilities...
        hashTypes->insert( "AsResourceRegister", AsObject::AS_OBJECT_RESOURCEREGISTER );
        hashTypes->insert( "AsApp", AsObject::AS_OBJECT_ASAPP );
        hashTypes->insert( "AsCamera", AsObject::AS_OBJECT_CAMERA );
        hashTypes->insert( "AsInk", AsObject::AS_OBJECT_INK );
        hashTypes->insert( "AsOrigin", AsObject::AS_OBJECT_ORIGIN );
        hashTypes->insert( "AsBackground", AsObject::AS_OBJECT_BACKGROUND );
        hashTypes->insert( "AsTextRun", AsObject::AS_OBJECT_TEXTRUN );
        hashTypes->insert( "AsTempResIndex", AsObject::AS_OBJECT_TEMPRESINDEX );
        hashTypes->insert( "AsVirtualFolderIndex", AsObject::AS_OBJECT_VIRTUAL_FOLDER_INDEX );

        // Undo Commamds...
        hashTypes->insert( "AsUndoStep", AsObject::AS_OBJECT_UNDO_STEP );
        hashTypes->insert( "AsUndoNewPage", AsObject::AS_OBJECT_UNDO_NEWPAGE );
        hashTypes->insert( "AsUndoReorderPages", AsObject::AS_OBJECT_UNDO_REORDERPAGES );
        hashTypes->insert( "AsUndoDeletePage", AsObject::AS_OBJECT_UNDO_DELETEPAGE );
        hashTypes->insert( "AsUndoResetPage", AsObject::AS_OBJECT_UNDO_RESETPAGE );
        hashTypes->insert( "AsUndoClearPage", AsObject::AS_OBJECT_UNDO_CLEARPAGE );
        hashTypes->insert( "AsUndoGroupObjects", AsObject::AS_OBJECT_UNDO_GROUPOBJECTS );
        hashTypes->insert( "AsUndoUngroupObjects", AsObject::AS_OBJECT_UNDO_UNGROUPOBJECTS );
        hashTypes->insert( "AsUndoNewObject", AsObject::AS_OBJECT_UNDO_NEWOBJECT );
        hashTypes->insert( "AsUndoEditObject", AsObject::AS_OBJECT_UNDO_EDITOBJECT );
        hashTypes->insert( "AsUndoDeleteObject", AsObject::AS_OBJECT_UNDO_DELETEOBJECT );
        hashTypes->insert( "AsUndoNewAction", AsObject::AS_OBJECT_UNDO_NEWACTION );
        hashTypes->insert( "AsUndoEditAction", AsObject::AS_OBJECT_UNDO_EDITACTION );
        hashTypes->insert( "AsUndoDeleteAction", AsObject::AS_OBJECT_UNDO_DELETEACTION );
        hashTypes->insert( "AsUndoReplaceAnnotations", AsObject::AS_OBJECT_UNDO_REPLACEANNOTATIONS );
        hashTypes->insert( "AsUndoSimpleEdit", AsObject::AS_OBJECT_UNDO_SIMPLEEDIT );
        hashTypes->insert( "AsUndoDeleteResource", AsObject::AS_OBJECT_UNDO_DELETERESOURCE );

        // Meta objects...
        hashTypes->insert( "AsCategory", AsObject::AS_OBJECT_CATEGORY );
        hashTypes->insert( "AsMetaProperty", AsObject::AS_OBJECT_METAPROPERTY );
        hashTypes->insert( "AsMetaResourceFolder", AsObject::AS_OBJECT_METARESOURCEFOLDER );

        hashTypes->insert( "AsMetaGui", AsObject::AS_OBJECT_METAGUI );
        hashTypes->insert( "AsGuiToolStore", AsObject::AS_OBJECT_GUITOOLSTORE );
        hashTypes->insert( "AsUserGui", AsObject::AS_OBJECT_USERGUI );
        hashTypes->insert( "AsContainerToolStore", AsObject::AS_OBJECT_CONTAINERTOOLSTORE );
        hashTypes->insert( "AsContainerToolSet", AsObject::AS_OBJECT_CONTAINERTOOLSET );

        // Inspire Tools.
        hashTypes->insert( "AsToolSelector", AsObject::AS_OBJECT_TOOL_SELECT );
        hashTypes->insert( "AsToolPen", AsObject::AS_OBJECT_TOOL_PEN );
        hashTypes->insert( "AsToolHighlighter", AsObject::AS_OBJECT_TOOL_HIGHLIGHTER );
        hashTypes->insert( "AsToolEraser", AsObject::AS_OBJECT_TOOL_ERASER );
        hashTypes->insert( "AsToolText", AsObject::AS_OBJECT_TOOL_TEXT );
        hashTypes->insert( "AsToolHandwriting", AsObject::AS_OBJECT_TOOL_HANDWRITING );
        hashTypes->insert( "AsToolShapeRecognition", AsObject::AS_OBJECT_TOOL_SHAPERECOGNITION );
        hashTypes->insert( "AsToolConnector", AsObject::AS_OBJECT_TOOL_CONNECTOR );
        hashTypes->insert( "AsToolFloodFill", AsObject::AS_OBJECT_TOOL_FLOODFILL );
        hashTypes->insert( "AsToolShape", AsObject::AS_OBJECT_TOOL_SHAPE );
        hashTypes->insert( "AsToolMagicInk", AsObject::AS_OBJECT_TOOL_MAGICINK );
        hashTypes->insert( "AsToolPageZoom", AsObject::AS_OBJECT_TOOL_PAGEZOOM );
        hashTypes->insert( "AsToolRubberStamp", AsObject::AS_OBJECT_TOOL_RUBBER_STAMP );
        hashTypes->insert( "AsToolPenModifier", AsObject::AS_OBJECT_TOOL_PENMODIFIER );
        hashTypes->insert( "AsToolEquation", AsObject::AS_OBJECT_TOOL_EQUATION );
        hashTypes->insert( "AsToolVerText", AsObject::AS_OBJECT_TOOL_VERTEXT );

        // Inspire Commands.
        hashTypes->insert( "AsCmdAbout", AsObject::AS_OBJECT_COMMAND_ABOUT );
        hashTypes->insert( "AsCmdPublishDetails", AsObject::AS_OBJECT_COMMAND_PUBLISH_DETAILS );
        hashTypes->insert( "AsCmdFlipchartSummary", AsObject::AS_OBJECT_COMMAND_FLIPCHART_SUMMARY );
        hashTypes->insert( "AsCmdClearAnnotations", AsObject::AS_OBJECT_COMMAND_CLEAR_ANNOTATIONS );
        hashTypes->insert( "AsCmdClearObjects", AsObject::AS_OBJECT_COMMAND_CLEAR_OBJECTS );
        hashTypes->insert( "AsCmdClearGrid", AsObject::AS_OBJECT_COMMAND_CLEAR_GRID );
        hashTypes->insert( "AsCmdClearBackground", AsObject::AS_OBJECT_COMMAND_CLEAR_BACKGROUND );
        hashTypes->insert( "AsCmdClearPage", AsObject::AS_OBJECT_COMMAND_CLEAR_PAGE );
        hashTypes->insert( "AsCmdCloseFlipchart", AsObject::AS_OBJECT_COMMAND_CLOSEFLIPCHART );
        //hashTypes->insert( "AsCmdCurrentFlipcharts", AsObject::AS_OBJECT_COMMAND_CURRENTFLIPCHARTS );
        hashTypes->insert( "AsCmdDelete", AsObject::AS_OBJECT_COMMAND_DELETE );
        hashTypes->insert( "AsCmdExit", AsObject::AS_OBJECT_COMMAND_EXIT );
        hashTypes->insert( "AsCmdExpressPoll", AsObject::AS_OBJECT_COMMAND_EXPRESSPOLL );
        hashTypes->insert( "AsCmdStartStopVote", AsObject::AS_OBJECT_COMMAND_STARTSTOPVOTE );
        hashTypes->insert( "AsCmdPauseVote", AsObject::AS_OBJECT_COMMAND_PAUSEVOTE );
        hashTypes->insert( "AsCmdExportTestToExcel", AsObject::AS_OBJECT_COMMAND_EXPORTTESTTOEXCEL );
        hashTypes->insert( "AsCmdHelp", AsObject::AS_OBJECT_COMMAND_HELP );
        hashTypes->insert( "AsCmdPenOptions", AsObject::AS_OBJECT_COMMAND_PENOPTIONS );
        hashTypes->insert( "AsCmdLink", AsObject::AS_OBJECT_COMMAND_LINK );
        hashTypes->insert( "AsCmdMostRecentlyUsed", AsObject::AS_OBJECT_COMMAND_MOSTRECENTLYUSED );
        hashTypes->insert( "AsCmdNewFlipchart", AsObject::AS_OBJECT_COMMAND_NEWFLIPCHART );
        hashTypes->insert( "AsCmdNextPage", AsObject::AS_OBJECT_COMMAND_NEXTPAGE );
        hashTypes->insert( "AsCmdOpenFromMyFlipcharts", AsObject::AS_OBJECT_COMMAND_OPENFROMMYFLIPCHARTS );
        hashTypes->insert( "AsCmdOpenFromSharedFlipcharts", AsObject::AS_OBJECT_COMMAND_OPENFROMSHAREDFLIPCHARTS );
        hashTypes->insert( "AsCmdOpenFromOtherLocation", AsObject::AS_OBJECT_COMMAND_OPENFROMOTHERLOCATION );
        hashTypes->insert( "AsCmdPreviousPage", AsObject::AS_OBJECT_COMMAND_PREVIOUSPAGE );
        hashTypes->insert( "AsCmdRedo", AsObject::AS_OBJECT_COMMAND_REDO );
        hashTypes->insert( "AsCmdResetPage", AsObject::AS_OBJECT_COMMAND_RESETPAGE );
        hashTypes->insert( "AsCmdRevealer", AsObject::AS_OBJECT_COMMAND_REVEALER );
        hashTypes->insert( "AsCmdSaveToMyFlipcharts", AsObject::AS_OBJECT_COMMAND_SAVETOMYFLIPCHARTS );
        hashTypes->insert( "AsCmdSaveToSharedFlipcharts", AsObject::AS_OBJECT_COMMAND_SAVETOSHAREDFLIPCHARTS );
        hashTypes->insert( "AsCmdSaveToOtherLocation", AsObject::AS_OBJECT_COMMAND_SAVETOOTHERLOCATION );
        hashTypes->insert( "AsCmdSaveFlipchart", AsObject::AS_OBJECT_COMMAND_SAVEFLIPCHART );
        hashTypes->insert( "AsCmdSendViaEmail", AsObject::AS_OBJECT_COMMAND_SEND_VIA_EMAIL );
        hashTypes->insert( "AsCmdStopAllSounds", AsObject::AS_OBJECT_COMMAND_STOPALLSOUNDS );
        hashTypes->insert( "AsCmdToggleDualMode", AsObject::AS_OBJECT_COMMAND_TOGGLEDUALMODE );
        //hashTypes->insert( "AsCmdToggleDualUser", AsObject::AS_OBJECT_COMMAND_TOGGLEDUALUSER );
        hashTypes->insert( "AsCmdUndo", AsObject::AS_OBJECT_COMMAND_UNDO );
        //hashTypes->insert( "AsCmdQuestionBuilder", AsObject::AS_OBJECT_COMMAND_QUESTIONBUILDER );
        hashTypes->insert( "AsCmdPrint", AsObject::AS_OBJECT_COMMAND_PRINTFLIPCHART );
        hashTypes->insert( "AsCmdLaunchClock", AsObject::AS_OBJECT_COMMAND_LAUNCHCLOCK );
        hashTypes->insert( "AsCmdCameraArea", AsObject::AS_OBJECT_COMMAND_CAMERA_AREA );
        hashTypes->insert( "AsCmdCameraFullscreenCurrentPage", AsObject::AS_OBJECT_COMMAND_CAMERA_FULLSCREEN_CURRENTPAGE );
        hashTypes->insert( "AsCmdCameraFullscreenNewPage", AsObject::AS_OBJECT_COMMAND_CAMERA_FULLSCREEN_NEWPAGE );
        hashTypes->insert( "AsCmdCameraFullscreen", AsObject::AS_OBJECT_COMMAND_CAMERA_FULLSCREEN);
        hashTypes->insert( "AsCmdCameraActiView", AsObject::AS_OBJECT_COMMAND_CAMERA_ACTIVIEW);
        hashTypes->insert( "AsCmdCut", AsObject::AS_OBJECT_COMMAND_CUT );
        hashTypes->insert( "AsCmdCopy", AsObject::AS_OBJECT_COMMAND_COPY );
        hashTypes->insert( "AsCmdPaste", AsObject::AS_OBJECT_COMMAND_PASTE );
        hashTypes->insert( "AsCmdDuplicate", AsObject::AS_OBJECT_COMMAND_DUPLICATE );
        hashTypes->insert( "AsCmdRuler", AsObject::AS_OBJECT_COMMAND_DEFAULT_RULER );
        hashTypes->insert( "AsCmdSetSquare", AsObject::AS_OBJECT_COMMAND_SET_SQUARE );
        hashTypes->insert( "AsCmdProtractor", AsObject::AS_OBJECT_COMMAND_DEFAULT_PROTRACTOR );
        hashTypes->insert( "AsCmdMilitaryProtractor", AsObject::AS_OBJECT_COMMAND_MILITARY_PROTRACTOR );
        hashTypes->insert( "AsCmdWeaponDangerArea", AsObject::AS_OBJECT_COMMAND_WEAPON_DANGER_AREA );
        hashTypes->insert( "AsCmdCompass", AsObject::AS_OBJECT_COMMAND_COMPASS );
        hashTypes->insert( "AsCmdShowExpressPollFlipchart", AsObject::AS_OBJECT_COMMAND_SHOWEXPRESSPOLLFLIPCHART );
        hashTypes->insert( "AsCmdResultsBrowser", AsObject::AS_OBJECT_COMMAND_RESULTSBROWSER );
        hashTypes->insert( "AsCmdSpotlight", AsObject::AS_OBJECT_COMMAND_SPOTLIGHT );
        hashTypes->insert( "AsCmdSpotlightReversed", AsObject::AS_OBJECT_COMMAND_SPOTLIGHT_REVERSED );
        hashTypes->insert( "AsCmdSpotlightSquare", AsObject::AS_OBJECT_COMMAND_SPOTLIGHT_SQUARE );
        hashTypes->insert( "AsCmdSpotlightSquareReversed", AsObject::AS_OBJECT_COMMAND_SPOTLIGHT_SQUAREREVERSED );
        hashTypes->insert( "AsCmdTickertape", AsObject::AS_OBJECT_COMMAND_TICKERTAPE );
        hashTypes->insert( "AsCmdDice", AsObject::AS_OBJECT_COMMAND_DICE );
        hashTypes->insert( "AsCmdXYOriginTool", AsObject::AS_OBJECT_COMMAND_XYORIGIN );
        hashTypes->insert( "AsCmdLaunchDevReg", AsObject::AS_OBJECT_COMMAND_LAUNCHDEVREG );
        hashTypes->insert( "AsCmdFollowOnQuestion", AsObject::AS_OBJECT_COMMAND_FOLLOWONQUESTION );
        //hashTypes->insert( "AsCmdPresent", AsObject::AS_OBJECT_COMMAND_PRESENT );
        hashTypes->insert( "AsCmdLaunchSettings", AsObject::AS_OBJECT_COMMAND_LAUNCH_SETTINGS );
        hashTypes->insert( "AsCmdDesktopAnnotate", AsObject::AS_OBJECT_COMMAND_DESKTOPANNOTATE );
        hashTypes->insert( "AsCmdDesktopTools", AsObject::AS_OBJECT_COMMAND_DESKTOPTOOLS );
        hashTypes->insert( "AsCmdInsertFromFile", AsObject::AS_OBJECT_COMMAND_INSERTFROMFILE );
        //hashTypes->insert( "AsCmdFlipchartBuilder", AsObject::AS_OBJECT_COMMAND_FLIPCHARTBUILDER );
        hashTypes->insert( "AsCmdSoundRecorder", AsObject::AS_OBJECT_COMMAND_SOUNDRECORDER );
        hashTypes->insert( "AsCmdSoundController", AsObject::AS_OBJECT_COMMAND_SOUNDCONTROLLER );
        //hashTypes->insert( "AsCmdFlipchartRecorder", AsObject::AS_OBJECT_COMMAND_FLIPCHARTRECORDER );
        hashTypes->insert( "AsCmdOnscreenKeyboard", AsObject::AS_OBJECT_COMMAND_ONSCREENKEYBOARD );
        hashTypes->insert( "AsCmdUserDefinedButton", AsObject::AS_OBJECT_COMMAND_USERDEFINEDBUTTON );
        hashTypes->insert( "AsCmdEditProfile", AsObject::AS_OBJECT_COMMAND_EDITPROFILE );
        hashTypes->insert( "AsCmdSwitchProfile", AsObject::AS_OBJECT_COMMAND_SWITCHPROFILE );
        hashTypes->insert( "AsCmdPageBrowser", AsObject::AS_OBJECT_COMMAND_PAGEBROWSER );
        hashTypes->insert( "AsCmdResourceBrowser", AsObject::AS_OBJECT_COMMAND_RESOURCEBROWSER );
        hashTypes->insert( "AsCmdObjectBrowser", AsObject::AS_OBJECT_COMMAND_OBJECTBROWSER );
        hashTypes->insert( "AsCmdNoteBrowser", AsObject::AS_OBJECT_COMMAND_NOTEBROWSER );
        hashTypes->insert( "AsCmdPropertyBrowser", AsObject::AS_OBJECT_COMMAND_PROPERTYBROWSER );
        hashTypes->insert( "AsCmdActionBrowser", AsObject::AS_OBJECT_COMMAND_ACTIONBROWSER );
        hashTypes->insert( "AsCmdVotingBrowser", AsObject::AS_OBJECT_COMMAND_VOTINGBROWSER );
        hashTypes->insert( "AsCmdConvertAnnotationToText", AsObject::AS_OBJECT_COMMAND_CONVERTANNOTATIONTOTEXT );
        hashTypes->insert( "AsCmdConvertAnnotationToShape", AsObject::AS_OBJECT_COMMAND_CONVERTANNOTATIONTOSHAPE );
        hashTypes->insert( "AsCmdEditText", AsObject::AS_OBJECT_COMMAND_EDITTEXT );
        hashTypes->insert( "AsCmdEditShape", AsObject::AS_OBJECT_COMMAND_EDITSHAPE );
        hashTypes->insert( "AsCmdToggleLocked", AsObject::AS_OBJECT_COMMAND_TOGGLELOCKED );
        hashTypes->insert( "AsCmdToggleGrouped", AsObject::AS_OBJECT_COMMAND_TOGGLEGROUPED );
        hashTypes->insert( "AsCmdToggleHidden", AsObject::AS_OBJECT_COMMAND_TOGGLEHIDDEN );
        hashTypes->insert( "AsCmdToggleDragCopy", AsObject::AS_OBJECT_COMMAND_TOGGLEDRAGCOPY );
        hashTypes->insert( "AsCmdMirrorX", AsObject::AS_OBJECT_COMMAND_MIRRORX );
        hashTypes->insert( "AsCmdMirrorY", AsObject::AS_OBJECT_COMMAND_MIRRORY );
        hashTypes->insert( "AsCmdFlipX", AsObject::AS_OBJECT_COMMAND_FLIPX );
        hashTypes->insert( "AsCmdFlipY", AsObject::AS_OBJECT_COMMAND_FLIPY );
        hashTypes->insert( "AsCmdAlignLeft", AsObject::AS_OBJECT_COMMAND_ALIGNLEFT );
        hashTypes->insert( "AsCmdAlignCentreX", AsObject::AS_OBJECT_COMMAND_ALIGNCENTREX );
        hashTypes->insert( "AsCmdAlignRight", AsObject::AS_OBJECT_COMMAND_ALIGNRIGHT );
        hashTypes->insert( "AsCmdAlignTop", AsObject::AS_OBJECT_COMMAND_ALIGNTOP );
        hashTypes->insert( "AsCmdAlignCentreY", AsObject::AS_OBJECT_COMMAND_ALIGNCENTREY );
        hashTypes->insert( "AsCmdAlignBottom", AsObject::AS_OBJECT_COMMAND_ALIGNBOTTOM );
        hashTypes->insert( "AsCmdAlignWidth", AsObject::AS_OBJECT_COMMAND_ALIGNWIDTH );
        hashTypes->insert( "AsCmdAlignHeight", AsObject::AS_OBJECT_COMMAND_ALIGNHEIGHT );
        hashTypes->insert( "AsCmdAlignAngle", AsObject::AS_OBJECT_COMMAND_ALIGNANGLE );
        hashTypes->insert( "AsCmdAlignComplete", AsObject::AS_OBJECT_COMMAND_ALIGNCOMPLETE );
        hashTypes->insert( "AsCmdBringToFront", AsObject::AS_OBJECT_COMMAND_BRINGTOFRONT );
        hashTypes->insert( "AsCmdBringForwards", AsObject::AS_OBJECT_COMMAND_BRINGFORWARDS );
        hashTypes->insert( "AsCmdSendToBack", AsObject::AS_OBJECT_COMMAND_SENDTOBACK );
        hashTypes->insert( "AsCmdSendBackwards", AsObject::AS_OBJECT_COMMAND_SENDBACKWARDS );
        hashTypes->insert( "AsCmdInsertFileLink", AsObject::AS_OBJECT_COMMAND_INSERTFILELINK );
        hashTypes->insert( "AsCmdInsertWebsiteLink", AsObject::AS_OBJECT_COMMAND_INSERTWEBSITELINK );
        hashTypes->insert( "AsCmdInsertEmbeddedHtmlFragment", AsObject::AS_OBJECT_COMMAND_INSERT_EMBEDDED_HTML_FRAGMENT );
        hashTypes->insert( "AsCmdInsertLinkOnCurrentSelection", AsObject::AS_OBJECT_COMMAND_INSERTLINK_CURRENTSELECTION );
        //hashTypes->insert( "AsCmdTileFlipcharts", AsObject::AS_OBJECT_COMMAND_TILEFLIPCHARTS );
        hashTypes->insert( "AsCmdSpellChecker", AsObject::AS_OBJECT_COMMAND_SPELLCHECKER );
        hashTypes->insert( "AsCmdCustomise", AsObject::AS_OBJECT_COMMAND_CUSTOMISE );
        hashTypes->insert( "AsCmdInsertPage", AsObject::AS_OBJECT_COMMAND_INSERTPAGE );
        hashTypes->insert( "AsCmdInsertPageBlank", AsObject::AS_OBJECT_COMMAND_INSERTPAGE_BLANK );
        hashTypes->insert( "AsCmdInsertPageDesktopSnapshot", AsObject::AS_OBJECT_COMMAND_INSERTPAGE_DESKTOPSNAPSHOT );
        hashTypes->insert( "AsCmdSetPageBackground", AsObject::AS_OBJECT_COMMAND_SETPAGEBACKGROUND );
        hashTypes->insert( "AsCmdSavePageToResources", AsObject::AS_OBJECT_COMMAND_SAVEPAGETORESOURCES );
        hashTypes->insert( "AsCmdSaveBackgroundToResources", AsObject::AS_OBJECT_COMMAND_SAVEBACKGROUNDTORESOURCES );
        hashTypes->insert( "AsCmdSaveGridToResources", AsObject::AS_OBJECT_COMMAND_SAVEGRIDTORESOURCES );
        hashTypes->insert( "AsCmdGridDesigner", AsObject::AS_OBJECT_COMMAND_GRIDDESIGNER );
        hashTypes->insert( "AsCmdHideGrid", AsObject::AS_OBJECT_COMMAND_HIDEGRID );
        hashTypes->insert( "AsCmdClearFlipchartsMRUList", AsObject::AS_OBJECT_COMMAND_CLEARFLIPCHARTSMRULIST );
        //hashTypes->insert( "AsCmdSelectMarqueeMode", AsObject::AS_OBJECT_COMMAND_SELECTMARQUEEMODE );
        //hashTypes->insert( "AsCmdSelectCollectMode", AsObject::AS_OBJECT_COMMAND_SELECTCOLLECTMODE );
        //hashTypes->insert( "AsCmdSelectCrossingMode", AsObject::AS_OBJECT_COMMAND_SELECTCROSSINGMODE );
        hashTypes->insert( "AsCmdViewFullscreen", AsObject::AS_OBJECT_COMMAND_VIEWFULLSCREEN );
#ifndef Q_OS_MAC
        hashTypes->insert( "AsCmdShowMenuBar", AsObject::AS_OBJECT_COMMAND_SHOWMENUBAR );
#endif
        hashTypes->insert( "AsCmdShowTrashCan", AsObject::AS_OBJECT_COMMAND_SHOWTRASHCAN );
        hashTypes->insert( "AsCmdShowPageExtender", AsObject::AS_OBJECT_COMMAND_SHOWPAGEEXTENDER );
        //hashTypes->insert( "AsCmdZoomToFitSelection", AsObject::AS_OBJECT_COMMAND_ZOOMTOFITSELECTION );
        hashTypes->insert( "AsCmdTimestamp", AsObject::AS_OBJECT_COMMAND_TIMESTAMP );
        hashTypes->insert( "AsCmdObjectIncreaseSize", AsObject::AS_OBJECT_COMMAND_OBJECTINCREASESIZE );
        hashTypes->insert( "AsCmdObjectDecreaseSize", AsObject::AS_OBJECT_COMMAND_OBJECTDECREASESIZE );
        hashTypes->insert( "AsCmdObjectOriginalSize", AsObject::AS_OBJECT_COMMAND_OBJECTORIGINALSIZE );
        hashTypes->insert( "AsCmdObjectBestFitWidth", AsObject::AS_OBJECT_COMMAND_OBJECTBESTFITWIDTH );
        hashTypes->insert( "AsCmdObjectBestFitHeight", AsObject::AS_OBJECT_COMMAND_OBJECTBESTFITHEIGHT );
        hashTypes->insert( "AsCmdObjectBestFitPage", AsObject::AS_OBJECT_COMMAND_OBJECTBESTFITPAGE );
        //hashTypes->insert( "AsCmdShowMainToolBar", AsObject::AS_OBJECT_COMMAND_SHOWMAINTOOLBAR );
        //hashTypes->insert( "AsCmdShowMainToolBox", AsObject::AS_OBJECT_COMMAND_SHOWMAINTOOLBOX );
        hashTypes->insert( "AsCmdShowBrowsers", AsObject::AS_OBJECT_COMMAND_SHOWBROWSERS );
        hashTypes->insert( "AsCmdShowDocumentTabs", AsObject::AS_OBJECT_COMMAND_SHOWDOCUMENTTABS );
        hashTypes->insert( "AsCmdCalculator", AsObject::AS_OBJECT_COMMAND_CALCULATOR );
        hashTypes->insert( "AsCmdFullScreenRecorder", AsObject::AS_OBJECT_COMMAND_FULLSCREENRECORDER );
        hashTypes->insert( "AsCmdAreaScreenRecorder", AsObject::AS_OBJECT_COMMAND_AREASCREENRECORDER );
        hashTypes->insert( "AsCmdEditUserDefinedButtons", AsObject::AS_OBJECT_COMMAND_EDITUSERDEFINEDBUTTONS );
        hashTypes->insert( "AsCmdCameraPointToPoint", AsObject::AS_OBJECT_COMMAND_CAMERA_POINTTOPOINT );
        hashTypes->insert( "AsCmdCameraFreehand", AsObject::AS_OBJECT_COMMAND_CAMERA_FREEHAND );
        hashTypes->insert( "AsCmdCameraWindow", AsObject::AS_OBJECT_COMMAND_CAMERA_WINDOW );
        hashTypes->insert( "AsCmdSpellcheckFlipchart", AsObject::AS_OBJECT_COMMAND_SPELLCHECK_FLIPCHART );
        hashTypes->insert( "AsCmdExtractText", AsObject::AS_OBJECT_COMMAND_EXTRACT_TEXT );
        //hashTypes->insert( "AsCmdCopyFormat", AsObject::AS_OBJECT_COMMAND_COPY_FORMAT );
        //hashTypes->insert( "AsCmdPasteFormatSelected", AsObject::AS_OBJECT_COMMAND_PASTE_FORMAT_SELECTED );
        //hashTypes->insert( "AsCmdPasteFormatPageObjects", AsObject::AS_OBJECT_COMMAND_PASTE_FORMAT_PAGEOBJECTS );
        //hashTypes->insert( "AsCmdPasteFormatAll", AsObject::AS_OBJECT_COMMAND_PASTE_FORMAT_ALL );
        hashTypes->insert( "AsCmdSnapToGrid", AsObject::AS_OBJECT_COMMAND_SNAPTOGRID );
        //hashTypes->insert( "AsCmdEditLabel", AsObject::AS_OBJECT_COMMAND_EDITLABEL );
        hashTypes->insert( "AsCmdTeacherLock", AsObject::AS_OBJECT_COMMAND_TEACHERLOCK );
        hashTypes->insert( "AsCmdNewBrowserWindow", AsObject::AS_OBJECT_COMMAND_NEWBROWSERWINDOW );
        hashTypes->insert( "AsCmdFirstPage", AsObject::AS_OBJECT_COMMAND_FIRSTPAGE );
        hashTypes->insert( "AsCmdLastPage", AsObject::AS_OBJECT_COMMAND_LASTPAGE );
        hashTypes->insert( "AsCmdAnotherPage", AsObject::AS_OBJECT_COMMAND_ANOTHERPAGE );
        hashTypes->insert( "AsCmdDuplicatePageAfterCurrent", AsObject::AS_OBJECT_COMMAND_DUPLICATE_PAGEAFTERCURRENT );
        hashTypes->insert( "AsCmdDuplicatePageBeforeCurrent", AsObject::AS_OBJECT_COMMAND_DUPLICATE_PAGEBEFORECURRENT );
        hashTypes->insert( "AsCmdDuplicatePageAtEndOfFlipchart", AsObject::AS_OBJECT_COMMAND_DUPLICATE_PAGEATEND );
        hashTypes->insert( "AsCmdInsertPageBlankBeforeCurrent", AsObject::AS_OBJECT_COMMAND_INSERTPAGE_BLANKBEFORECURRENT);
        hashTypes->insert( "AsCmdPageHistoryBack", AsObject::AS_OBJECT_COMMAND_PAGEHISTORYBACK );
        hashTypes->insert( "AsCmdPageHistoryForward", AsObject::AS_OBJECT_COMMAND_PAGEHISTORYFORWARD );
        hashTypes->insert( "AsCmdAngle", AsObject::AS_OBJECT_COMMAND_ANGLE );
        hashTypes->insert( "AsCmdAngleIncrementally", AsObject::AS_OBJECT_COMMAND_ANGLEINCREMENTALLY );
        hashTypes->insert( "AsCmdReflect", AsObject::AS_OBJECT_COMMAND_REFLECT );
        hashTypes->insert( "AsCmdInvert", AsObject::AS_OBJECT_COMMAND_INVERT );
        hashTypes->insert( "AsCmdTranslucency", AsObject::AS_OBJECT_COMMAND_TRANSLUCENCY );
        hashTypes->insert( "AsCmdMoreTranslucent", AsObject::AS_OBJECT_COMMAND_MORETRANSLUCENT );
        hashTypes->insert( "AsCmdLessTranslucent", AsObject::AS_OBJECT_COMMAND_LESSTRANSLUCENT );
        hashTypes->insert( "AsCmdToTopLayer", AsObject::AS_OBJECT_COMMAND_TOTOPLAYER );
        hashTypes->insert( "AsCmdToMiddleLayer", AsObject::AS_OBJECT_COMMAND_TOMIDDLELAYER );
        hashTypes->insert( "AsCmdToBottomLayer", AsObject::AS_OBJECT_COMMAND_TOBOTTOMLAYER );
        hashTypes->insert( "AsCmdSelectAll", AsObject::AS_OBJECT_COMMAND_SELECTALL );
        hashTypes->insert( "AsCmdToolboxRollup", AsObject::AS_OBJECT_COMMAND_TOOLBOXROLLUP );
        hashTypes->insert( "AsCmdToolboxRollIn", AsObject::AS_OBJECT_COMMAND_TOOLBOXROLLIN );
        hashTypes->insert( "AsCmdDisableRightClick", AsObject::AS_OBJECT_COMMAND_DISABLERIGHTCLICK );
        hashTypes->insert( "AsCmdObjectsToFront", AsObject::AS_OBJECT_COMMAND_OBJECTSTOFRONT );
        hashTypes->insert( "AsCmdCameraFullscreenMyResLibrary", AsObject::AS_OBJECT_COMMAND_CAMERA_FULLSCREEN_MYRESLIB );
        hashTypes->insert( "AsCmdCameraFullscreenSharedResLibrary", AsObject::AS_OBJECT_COMMAND_CAMERA_FULLSCREEN_SHAREDRESLIB );
        hashTypes->insert( "AsCmdCameraFullscreenClipboard", AsObject::AS_OBJECT_COMMAND_CAMERA_FULLSCREEN_CLIPBOARD );
        hashTypes->insert( "AsCmdClockSettings", AsObject::AS_OBJECT_COMMAND_CLOCKSETTINGS );
        hashTypes->insert( "AsCmdSizeObjectTopLeft", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_TOPLEFT );
        hashTypes->insert( "AsCmdSizeObjectTop", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_TOP );
        hashTypes->insert( "AsCmdSizeObjectTopRight", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_TOPRIGHT );
        hashTypes->insert( "AsCmdSizeObjectLeft", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_LEFT );
        hashTypes->insert( "AsCmdSizeObjectCentral", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_CENTRAL );
        hashTypes->insert( "AsCmdSizeObjectRight", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_RIGHT );
        hashTypes->insert( "AsCmdSizeObjectBottomLeft", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_BOTTOMLEFT );
        hashTypes->insert( "AsCmdSizeObjectBottom", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_BOTTOM );
        hashTypes->insert( "AsCmdSizeObjectBottomRight", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_BOTTOMRIGHT );
        hashTypes->insert( "AsCmdSizeObjectTopLeftIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_TOPLEFT_INCR );
        hashTypes->insert( "AsCmdSizeObjectTopIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_TOP_INCR );
        hashTypes->insert( "AsCmdSizeObjectTopRightIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_TOPRIGHT_INCR );
        hashTypes->insert( "AsCmdSizeObjectLeftIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_LEFT_INCR );
        hashTypes->insert( "AsCmdSizeObjectCentralIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_CENTRAL_INCR );
        hashTypes->insert( "AsCmdSizeObjectRightIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_RIGHT_INCR );
        hashTypes->insert( "AsCmdSizeObjectBottomLeftIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_BOTTOMLEFT_INCR );
        hashTypes->insert( "AsCmdSizeObjectBottomIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_BOTTOM_INCR );
        hashTypes->insert( "AsCmdSizeObjectBottomRightIncr", AsObject::AS_OBJECT_COMMAND_SIZEOBJECT_BOTTOMRIGHT_INCR );
        hashTypes->insert( "AsCmdStretchObjectTopLeft", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_TOPLEFT );
        hashTypes->insert( "AsCmdStretchObjectTop", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_TOP );
        hashTypes->insert( "AsCmdStretchObjectTopRight", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_TOPRIGHT );
        hashTypes->insert( "AsCmdStretchObjectLeft", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_LEFT );
        hashTypes->insert( "AsCmdStretchObjectCentral", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_CENTRAL );
        hashTypes->insert( "AsCmdStretchObjectRight", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_RIGHT );
        hashTypes->insert( "AsCmdStretchObjectBottomLeft", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_BOTTOMLEFT );
        hashTypes->insert( "AsCmdStretchObjectBottom", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_BOTTOM );
        hashTypes->insert( "AsCmdStretchObjectBottomRight", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_BOTTOMRIGHT );
        hashTypes->insert( "AsCmdStretchObjectTopLeftIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_TOPLEFT_INCR );
        hashTypes->insert( "AsCmdStretchObjectTopIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_TOP_INCR );
        hashTypes->insert( "AsCmdStretchObjectTopRightIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_TOPRIGHT_INCR );
        hashTypes->insert( "AsCmdStretchObjectLeftIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_LEFT_INCR );
        hashTypes->insert( "AsCmdStretchObjectCentralIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_CENTRAL_INCR );
        hashTypes->insert( "AsCmdStretchObjectRightIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_RIGHT_INCR );
        hashTypes->insert( "AsCmdStretchObjectBottomLeftIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_BOTTOMLEFT_INCR );
        hashTypes->insert( "AsCmdStretchObjectBottomIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_BOTTOM_INCR );
        hashTypes->insert( "AsCmdStretchObjectBottomRightIncr", AsObject::AS_OBJECT_COMMAND_STRETCHOBJECT_BOTTOMRIGHT_INCR );
        hashTypes->insert( "AsCmdPositionObjectTopLeft", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_TOPLEFT );
        hashTypes->insert( "AsCmdPositionObjectTop", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_TOP );
        hashTypes->insert( "AsCmdPositionObjectTopRight", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_TOPRIGHT );
        hashTypes->insert( "AsCmdPositionObjectLeft", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_LEFT );
        hashTypes->insert( "AsCmdPositionObjectCentral", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_CENTRAL );
        hashTypes->insert( "AsCmdPositionObjectRight", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_RIGHT );
        hashTypes->insert( "AsCmdPositionObjectBottomLeft", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_BOTTOMLEFT );
        hashTypes->insert( "AsCmdPositionObjectBottom", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_BOTTOM );
        hashTypes->insert( "AsCmdPositionObjectBottomRight", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_BOTTOMRIGHT );
        hashTypes->insert( "AsCmdPositionObjectIncrementally", AsObject::AS_OBJECT_COMMAND_POSITIONOBJECT_INCREMENTALLY );
        hashTypes->insert( "AsCmdImportResourcePackToMyResLib", AsObject::AS_OBJECT_COMMAND_IMPORTRESOURCEPACKTOMYRESLIB );
        hashTypes->insert( "AsCmdImportResourcePackToSharedResLib", AsObject::AS_OBJECT_COMMAND_IMPORTRESOURCEPACKTOSHAREDRESLIB );
        hashTypes->insert( "AsCmdWebUpdate", AsObject::AS_OBJECT_COMMAND_WEBUPDATE );
        hashTypes->insert( "AsCmdEditStudentDatabase", AsObject::AS_OBJECT_COMMAND_EDITSTUDENTDATABASE );
        hashTypes->insert( "AsCmdEditLRSGroups", AsObject::AS_OBJECT_COMMAND_EDITLRSGROUPS );
        hashTypes->insert( "AsCmdSaveToPlanet", AsObject::AS_OBJECT_COMMAND_SAVETOPLANET );
        hashTypes->insert( "AsCmdSearchPlanet", AsObject::AS_OBJECT_COMMAND_SEARCHPLANET );
        hashTypes->insert( "AsCmdColourPicker", AsObject::AS_OBJECT_COMMAND_COLOURPICKER );
        hashTypes->insert( "AsCmdShowDashboard", AsObject::AS_OBJECT_COMMAND_SHOWDASHBOARD );
        hashTypes->insert( "AsCmdRevealerRevealNorth", AsObject::AS_OBJECT_COMMAND_REVEALER_REVEAL_NORTH );
        hashTypes->insert( "AsCmdRevealerRevealEast", AsObject::AS_OBJECT_COMMAND_REVEALER_REVEAL_EAST );
        hashTypes->insert( "AsCmdRevealerRevealSouth", AsObject::AS_OBJECT_COMMAND_REVEALER_REVEAL_SOUTH );
        hashTypes->insert( "AsCmdRevealerRevealWest", AsObject::AS_OBJECT_COMMAND_REVEALER_REVEAL_WEST );
        hashTypes->insert( "AsCmdRevealerHide", AsObject::AS_OBJECT_COMMAND_REVEALER_HIDE );
        hashTypes->insert( "AsCmdToggleDesignMode", AsObject::AS_OBJECT_COMMAND_TOGGLEDESIGNMODE );
        hashTypes->insert( "AsCmdDesignModeSettings", AsObject::AS_OBJECT_COMMAND_DESIGNMODESETTINGS );
        hashTypes->insert( "AsCmdCutPage", AsObject::AS_OBJECT_COMMAND_CUT_PAGE );
        hashTypes->insert( "AsCmdCopyPage", AsObject::AS_OBJECT_COMMAND_COPY_PAGE );
        hashTypes->insert( "AsCmdDeletePage", AsObject::AS_OBJECT_COMMAND_DELETE_PAGE );
        hashTypes->insert( "AsCmdExportPageToImage", AsObject::AS_OBJECT_COMMAND_EXPORTPAGETOIMAGE );
        hashTypes->insert( "AsCmdAssignStudentsToDevices", AsObject::AS_OBJECT_COMMAND_ASSIGNSTUDENTSTODEVICES );
        hashTypes->insert( "AsCmdShowPageTransitions", AsObject::AS_OBJECT_COMMAND_SHOWPAGETRANSITIONS );
        hashTypes->insert( "AsCmdShowPenModifier", AsObject::AS_OBJECT_COMMAND_SHOWPENMODIFIER );
        hashTypes->insert( "AsCmdWhatsNew", AsObject::AS_OBJECT_COMMAND_WHATSNEW );
        hashTypes->insert( "AsCmdActiView", AsObject::AS_OBJECT_COMMAND_ACTIVIEW );

        // Commands to support boards with physical buttons.
        hashTypes->insert( "AsCmdBrdNewFile", AsObject::AS_OBJECT_COMMAND_BRD_NEW_FILE );
        hashTypes->insert( "AsCmdBrdSaveFile", AsObject::AS_OBJECT_COMMAND_BRD_SAVE_FILE );
        hashTypes->insert( "AsCmdBrdPrevPage", AsObject::AS_OBJECT_COMMAND_BRD_PREV_PAGE );
        hashTypes->insert( "AsCmdBrdNextPage", AsObject::AS_OBJECT_COMMAND_BRD_NEXT_PAGE );
        hashTypes->insert( "AsCmdBrdToolSelect", AsObject::AS_OBJECT_COMMAND_BRD_TOOL_SELECT );
        hashTypes->insert( "AsCmdBrdRightMouseClick", AsObject::AS_OBJECT_COMMAND_BRD_RIGHT_MOUSE_CLICK );
        hashTypes->insert( "AsCmdBrdPenBlack", AsObject::AS_OBJECT_COMMAND_BRD_PEN_BLACK );
        hashTypes->insert( "AsCmdBrdPenRed", AsObject::AS_OBJECT_COMMAND_BRD_PEN_RED );
        hashTypes->insert( "AsCmdBrdPenBlue", AsObject::AS_OBJECT_COMMAND_BRD_PEN_BLUE );
        hashTypes->insert( "AsCmdBrdPenGreen", AsObject::AS_OBJECT_COMMAND_BRD_PEN_GREEN );
        hashTypes->insert( "AsCmdBrdToolErase", AsObject::AS_OBJECT_COMMAND_BRD_TOOL_ERASE );
        hashTypes->insert( "AsCmdBrdToolBoxMenu", AsObject::AS_OBJECT_COMMAND_BRD_TOOLBOX_MENU );
        hashTypes->insert( "AsCmdBrdToolBoxSettings", AsObject::AS_OBJECT_COMMAND_BRD_TOOLBOXSETTINGS );
        hashTypes->insert( "AsCmdBrdQuestion", AsObject::AS_OBJECT_COMMAND_BRD_QUESTION );
        hashTypes->insert( "AsCmdBrdFullScreen", AsObject::AS_OBJECT_COMMAND_BRD_FULL_SCREEN );
        hashTypes->insert( "AsCmdBrdShutDown", AsObject::AS_OBJECT_COMMAND_BRD_SHUTDOWN );
        hashTypes->insert( "AsCmdBrdToolHighlight", AsObject::AS_OBJECT_COMMAND_BRD_TOOL_HIGHLIGHT );
        hashTypes->insert( "AsCmdBrdUndo", AsObject::AS_OBJECT_COMMAND_BRD_UNDO );
        hashTypes->insert( "AsCmdBrdPageReset", AsObject::AS_OBJECT_COMMAND_BRD_PAGE_RESET );
        hashTypes->insert( "AsCmdBrdDesktopAnnotate", AsObject::AS_OBJECT_COMMAND_BRD_DESKTOP_ANNOTATE );

        //action commands
        hashTypes->insert( "AsCmdLaunchMiniApp", AsObject::AS_OBJECT_COMMAND_LAUNCH_MINIAPP );
        hashTypes->insert( "AsCmdActivProgress", AsObject::AS_OBJECT_COMMAND_ACTIVPROGRESS );
        hashTypes->insert( "AsCmdPlaySound", AsObject::AS_OBJECT_COMMAND_PLAYSOUND );
        hashTypes->insert( "AsCmdOpenFile", AsObject::AS_OBJECT_COMMAND_OPENFILE );
        hashTypes->insert( "AsCmdOpenWebsite", AsObject::AS_OBJECT_COMMAND_OPENWEBSITE );
        hashTypes->insert( "AsCmdOpenEmbeddedFile", AsObject::AS_OBJECT_COMMAND_OPENEMBEDDEDFILE );
        hashTypes->insert( "AsCmdNewTextObject", AsObject::AS_OBJECT_COMMAND_NEWTEXTOBJECT );
        hashTypes->insert( "AsCmdAppendText", AsObject::AS_OBJECT_COMMAND_APPENDTEXT );
        hashTypes->insert( "AsCmdChangeText", AsObject::AS_OBJECT_COMMAND_CHANGETEXT );
        hashTypes->insert( "AsCmdDeconstructText", AsObject::AS_OBJECT_COMMAND_DECONSTRUCTTEXT );
        hashTypes->insert( "AsCmdAntares", AsObject::AS_OBJECT_COMMAND_ANTARES );
        hashTypes->insert( "AsCmdPrometheanWebsite", AsObject::AS_OBJECT_COMMAND_PROMETHEANWEBSITE );
        hashTypes->insert( "AsCmdPrometheanPlanet", AsObject::AS_OBJECT_COMMAND_PROMETHEANPLANET );
        hashTypes->insert( "AsCmdPublisherWebsite", AsObject::AS_OBJECT_COMMAND_PUBLISHER_WEBSITE );
        hashTypes->insert( "AsCmdTrainingAndSupportWebsite", AsObject::AS_OBJECT_COMMAND_TRAINING_AND_SUPPORT_WEBSITE );
        hashTypes->insert( "AsCmdBrowserShrinkThumbs", AsObject::AS_OBJECT_COMMAND_BROWSER_SHRINKTHUMBS );
        hashTypes->insert( "AsCmdBrowserGrowThumbs", AsObject::AS_OBJECT_COMMAND_BROWSER_GROWTHUMBS );
        hashTypes->insert( "AsCmdConvertPPTAsImages", AsObject::AS_OBJECT_COMMAND_CONVERTPPT_ASIMAGES );
        hashTypes->insert( "AsCmdConvertPPTAsObjects", AsObject::AS_OBJECT_COMMAND_CONVERTPPT_ASOBJECTS );
        hashTypes->insert( "AsCmdScreenSizeFlipchart", AsObject::AS_OBJECT_COMMAND_SCREENSIZE_FLIPCHART);
        hashTypes->insert( "AsCmd1280X1024Flipchart", AsObject::AS_OBJECT_COMMAND_1280X1024_FLIPCHART );
        hashTypes->insert( "AsCmd1152X864Flipchart", AsObject::AS_OBJECT_COMMAND_1152X864_FLIPCHART );
        hashTypes->insert( "AsCmd1024X768Flipchart", AsObject::AS_OBJECT_COMMAND_1024X768_FLIPCHART );
        hashTypes->insert( "AsCmdCustomSizeFlipchart", AsObject::AS_OBJECT_COMMAND_CUSTOMSIZE_FLIPCHART );
        hashTypes->insert( "AsCmdImportSmartFile", AsObject::AS_OBJECT_COMMAND_SMART_IMPORT );
        hashTypes->insert( "AsCmdImportSmartGallery", AsObject::AS_OBJECT_COMMAND_SMART_GALLERY_IMPORT );
        hashTypes->insert( "AsCmdPDFImport", AsObject::AS_OBJECT_COMMAND_PDF_IMPORT );
        hashTypes->insert( "AsCmdExtendPage", AsObject::AS_OBJECT_COMMAND_EXTEND_PAGE );

        hashTypes->insert( "AsCmdPenModifierLine", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_LINE );
        hashTypes->insert( "AsCmdPenModifierHorizontalLine", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_HORIZONTAL_LINE );
        hashTypes->insert( "AsCmdPenModifierVerticalLine", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_VERTICAL_LINE );
        hashTypes->insert( "AsCmdPenModifierSquare", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_SQUARE );
        hashTypes->insert( "AsCmdPenModifierRectangle", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_RECTANGLE );
        hashTypes->insert( "AsCmdPenModifierCircle", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_CIRCLE );
        hashTypes->insert( "AsCmdPenModifierEllipse", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_ELLIPSE );
        hashTypes->insert( "AsCmdPenModifierCurve", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_CURVE );
        hashTypes->insert( "AsCmdPenModifierSemiCircle", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_SEMICIRCLE );
        hashTypes->insert( "AsCmdPenModifierCallout1", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_CALLOUT1 );
        hashTypes->insert( "AsCmdPenModifierCallout2", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_CALLOUT2 );
        hashTypes->insert( "AsCmdPenModifierLine", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_LINE );
        hashTypes->insert( "AsCmdPenModifierSquare", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_SQUARE );
        hashTypes->insert( "AsCmdPenModifierLineChainShape", AsObject::AS_OBJECT_COMMAND_PENMODIFIER_LINE_CHAIN );

        // marquee handles
        hashTypes->insert( "AsCmdMarqueeSizeTopLeft", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZETOPLEFT );
        hashTypes->insert( "AsCmdMarqueeSizeTopCentre", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZETOPCENTRE );
        hashTypes->insert( "AsCmdMarqueeSizeTopRight", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZETOPRIGHT );
        hashTypes->insert( "AsCmdMarqueeSizeLeftCentre", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZELEFTCENTRE );
        hashTypes->insert( "AsCmdMarqueeSizeRightCentre", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZERIGHTCENTRE );
        hashTypes->insert( "AsCmdMarqueeSizeBottomLeft", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZEBOTTOMLEFT );
        hashTypes->insert( "AsCmdMarqueeSizeBottomCentre", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZEBOTTOMCENTRE );
        hashTypes->insert( "AsCmdMarqueeSizeBottomRight", AsObject::AS_OBJECT_COMMAND_MARQUEE_SIZEBOTTOMRIGHT );
        hashTypes->insert( "AsCmdMarqueeFreeMove", AsObject::AS_OBJECT_COMMAND_MARQUEE_FREEMOVE );
        hashTypes->insert( "AsCmdMarqueeRotate", AsObject::AS_OBJECT_COMMAND_MARQUEE_ROTATE );
        hashTypes->insert( "AsCmdMarqueeContextMenu", AsObject::AS_OBJECT_COMMAND_MARQUEE_CONTEXTMENU );
        hashTypes->insert( "AsCmdMarqueeTransparencySlider", AsObject::AS_OBJECT_COMMAND_MARQUEE_TRANSPARENCYSLIDER );

        // Studio Settings...
        hashTypes->insert( "AsSetting", AsObject::AS_OBJECT_SETTING );
        hashTypes->insert( "AsUserDefinedButton", AsObject::AS_OBJECT_USERDEFINEDBUTTON );
        hashTypes->insert( "AsCmdOSWebBrowser", AsObject::AS_OBJECT_COMMAND_OSWEBBROWSER );
        hashTypes->insert( "AsCmdPageTemplates", AsObject::AS_OBJECT_COMMAND_PAGETEMPLATES );
        hashTypes->insert( "AsCmdMorePageTemplates", AsObject::AS_OBJECT_COMMAND_MOREPAGETEMPLATES );

        //gradebook types
        hashTypes->insert( "AsStudent", AsObject::AS_OBJECT_GRADEBOOK_STUDENT );
        hashTypes->insert( "AsClass", AsObject::AS_OBJECT_GRADEBOOK_CLASS );
        hashTypes->insert( "AsDatabase", AsObject::AS_OBJECT_GRADEBOOK_DATABASE );
        hashTypes->insert( "AsStudents", AsObject::AS_OBJECT_GRADEBOOK_STUDENTS );
        hashTypes->insert( "AsClasses", AsObject::AS_OBJECT_GRADEBOOK_CLASSES );

        // Assessment Objects..
        hashTypes->insert( "AsResponses", AsObject::AS_OBJECT_RESPONSES);
        hashTypes->insert( "AsResponse", AsObject::AS_OBJECT_RESPONSE );

        // Question master
        hashTypes->insert( "AsCmdQuestionMaster", AsObject::AS_OBJECT_COMMAND_QUESTION_MASTER );
        hashTypes->insert( "AsCmdQuestionEditor", AsObject::AS_OBJECT_COMMAND_QUESTION_EDITOR );
        hashTypes->insert( "AsCmdRemoveQuestion", AsObject::AS_OBJECT_COMMAND_REMOVE_QUESTION );

        // Twain commands to insert image from Scanner / Camera
        hashTypes->insert( "AsCmdInsertTwain", AsObject::AS_OBJECT_COMMAND_INSERT_TWAIN );

        // Start image acquisition from document camera
        hashTypes->insert( "AsCmdDocumentCamera", AsObject::AS_OBJECT_COMMAND_DOCUMENT_CAMERA );

        // Becta
        hashTypes->insert( "AsCmdBectaImport", AsObject::AS_OBJECT_COMMAND_BECTA_IMPORT );
        hashTypes->insert( "AsCmdBectaExport", AsObject::AS_OBJECT_COMMAND_BECTA_EXPORT );

        // Export all pages
        hashTypes->insert( "AsCmdExportAllPagesToJPEG", AsObject::AS_OBJECT_COMMAND_ALL_PAGES_EXPORT_TO_JPEG );
        hashTypes->insert( "AsCmdExportAllPagesToBMP", AsObject::AS_OBJECT_COMMAND_ALL_PAGES_EXPORT_TO_BMP );
        hashTypes->insert( "AsCmdExportAllPagesToPDF", AsObject::AS_OBJECT_COMMAND_ALL_PAGES_EXPORT_TO_PDF );

        // Change look and feel
        hashTypes->insert( "AsCmdLookAndFeelStudio", AsObject::AS_OBJECT_COMMAND_LOOK_AND_FEEL_STUDIO );
        hashTypes->insert( "AsCmdLookAndFeelPrimary", AsObject::AS_OBJECT_COMMAND_LOOK_AND_FEEL_PRIMARY );
    }

    return *hashTypes;
}

void AsObject::asSetUserProperty(const QString &sName, const Variant &value)
{
    //    AsProperty *pProperty;
    //
    //    // First check whether we have this property, if so then set it, if not then add it.
    //    if ( m_PropertyBag.contains( sName ) )
    //    {
    //        pProperty = m_PropertyBag.value( sName );
    //        pProperty->asSetValue( value );
    //    }
    //    else
    //    {
    //        pProperty = new AsProperty( sName, value );
    //        m_PropertyBag.insert( sName, pProperty );
    //    }
}

quint32 AsObject::asGetID() const
{
    return m_nID;
}

void AsObject::asSetID(quint32 id)
{
    m_nID = id;
}

void AsObject::asSetType(AsObject::AsEnumObjectType tType)
{
    m_tType = tType;
}

AsObject::AsEnumObjectType AsObject::asGetType() const
{
    return m_tType;
}

const char *AsObject::asGetTypeChar()
{
    const char *str = nullptr;
    switch (m_tType)
    {
        case AsObject::AS_OBJECT_BACKGROUND:
            str = "background";
            break;
        case AsObject::AS_OBJECT_GRID:
            str = "grid";
            break;
        case AsObject::AS_OBJECT_IMAGE:
            str = "image";
            break;
        case AsObject::AS_OBJECT_IMAGERES:
            str = "image_res";
            break;
        case AsObject::AS_OBJECT_ANNOTATION:
            str = "annotation";
            break;
        case AsObject::AS_OBJECT_ANNOTATIONRES:
            str = "annotation_res";
            break;
        case AsObject::AS_OBJECT_SHAPE:
            str = "shape";
            break;
        case AsObject::AS_OBJECT_SHAPERES:
            str = "shape_res";
            break;
        case AsObject::AS_OBJECT_TEXT:
            str = "text";
            break;
        case AsObject::AS_OBJECT_TEXTRES:
            str = "text_res";
            break;
        case AsObject::AS_OBJECT_INK:
            str = "ink";
            break;
        case AsObject::AS_OBJECT_PAGE:
            str = "page";
            break;
        case AsObject::AS_OBJECT_TRANSFORM:
            str = "transform";
            break;
        case AsObject::AS_OBJECT_ORIGIN:
            str = "origin";
            break;
        case AsObject::AS_OBJECT_ASRENDERABLEGROUP:
            str = "renderableGroup";
            break;
        case AsObject::AS_OBJECT_MEDIACONTAINER:
            str = "mediaContainer";
            break;
        case AsObject::AS_OBJECT_MEDIAFILERES:
            str = "media_res";
            break;
        default:
            str = "unparsed_type";
            LOGDEBUG("unknow type:%d", m_tType);
            break;
    }
    return str;
}

const QString AsObject::asGetTypeName( ) const
{
    QString sTypeName = m_lTypes().key( m_tType );
    return sTypeName;
}

bool AsObject::asGetNextProperty(quint16 &nID, Variant &vValue)
{
    QString sName;
    if (!this->asGetNextProperty(nID, sName, vValue))
    {
        return false;
    }
    return true;
}

void AsObject::asAddReference(AsNode *pNode)
{
    if (!m_References.contains(pNode))
    {
        m_References.append(pNode);
    }
}

AsNode *AsObject::asGetIndexNode() const
{
    if (m_References.isEmpty())
        return NULL;
    return m_References.first();
}

bool AsObject::asGetNextProperty(quint16 &nID, QString &sName, Variant &vValue)
{
    // This method steps through the property table in the 'static
    // property table method' in the derived class.  Each call will
    // return true with the next property value.  Once the end of the
    // table is reached this method will return false to indicate that
    // there are no more properties.
    // First we need to check that we have not come to the end
    // of the property list.
    //    if ( m_itProperties == ( *m_pProperties )().constEnd() )
    ////    {
    ////        m_itProperties = ( *m_pProperties )().constBegin();
    ////        return false;
    ////    }
    ////
    ////    // The ID we return is the ID of the property from the hash table.
    ////    nID = m_itProperties.value();
    ////
    ////    // The value we return is the value of the propery which has the
    ////    // same name as the key for this entry in the hash table.
    ////    sName = m_itProperties.key();
    ////   // vValue = property( sName.toUtf8().data() );
    ////
    ////    // On the next call we will return the next property.
    ////    ++m_itProperties;
    vValue = property(nID);
    return true;
}

bool AsObject::asSetProperty(quint16 &nID, Variant vValue)
{
    // First, we need to check if we have a pointer to the 'static
    // property table method' in the derived class.  If not then we
    // will call asResetPropertyIndex() in the dervied class to set
    // this pointer.
    //    if ( m_pProperties == 0 )
    //    {
    ////        this->asResetPropertyIndex();
    //    }
    //
    //    // Now, the derived class may not have properties, in which case the
    //    // derived class will not overload asResetPropertyIndex() and the
    //    // base version of asResetPropertyIndex() will be called.  Therefore,
    //    // pointer will still be null.
    //    if ( m_pProperties == 0 )
    //    {
    //        return false;
    //    }
    //    mpropertyList.insert(nID,vValue);
    // Then we check whether this ID in the property hash table.  If not then
    // we don't recognise this property for this class.
    ////    QString sPropName = ( *m_pProperties )().key( nID );
    ////    if ( sPropName.isNull() )
    ////    {
    ////        return false;
    ////    }

    //    // OK, so we have a property with this ID, now we simply call
    //    // the meta property object to set the property value.
    //    if ( !setProperty( sPropName.toUtf8().data(), vValue ) )
    //    {
    //        return false;
    //    }
    setProperty(nID, vValue);
    return true;
}

void AsObject::asSetDirtyForWrite(bool stat)
{
}



Json::Value &AsObject::serialized()
{
    Json::Value obj;
    if (!isSupportSerializer()) {
        return jsonObj;
    }
            foreach (int propertyId, m_properties.keys()) {
            Variant var = m_properties.value(propertyId);
            if (!var.value) {
                continue;
            }
            if ( !isPropertyNeededSerialized(propertyId) ){
                continue;
            }
            if (asGetPropertyNameById(propertyId) == "transform") {
                Json::Value transform;
                transform << m_properties.value(propertyId);
                jsonObj["transform"] = transform;
                continue;
            }
            if (asGetPropertyNameById(propertyId) == "ink"){
                Json::Value ink;
                ink << m_properties.value(propertyId);
                jsonObj["ink"] = ink;
                continue;
            }
            if (var.isSimpleType()) {
                QString propertyName = asGetPropertyNameById(propertyId);
                if (propertyName != "")
                    var.simpleSerializer(obj, asGetPropertyNameById(propertyId));

            } else {
                Json::Value content;
                content << m_properties.value(propertyId);
                QString propertyName = asGetPropertyNameById(propertyId);
                if (propertyName != "")
                    obj[asGetPropertyNameById(propertyId).toStdString()] = content;
            }


        }
    if (this->asGetResourcePointer()) {
        jsonObj["resource"] = this->asResourceSerialized();
    }
    jsonObj["id"] = static_cast<int>(m_nID);
    jsonObj["type"] = typeName().toStdString();
    jsonObj["property"] = obj;
    if(m_lActionId.size()>0){
        jsonObj["actionId"]=m_lActionId.first();
    }
    return jsonObj;
}

void AsObject::asSetPropertyIterator(QHash<QString, quint16> &(*pProperties)())
{
    if (pProperties != 0)
    {
        m_pProperties = pProperties;
        m_itProperties = (*m_pProperties)().constBegin();
    }
}

bool AsObject::operator==(const AsObject &O)
{
    if ((this->m_tType != O.asGetType()) ||
        (this->m_nID != O.asGetID()))
    //( this->m_DateTimeCreated != O.asGetDataTimeCreated ))
    {
        return false;
    }
    return true;
}

AsObject::AsObject(const AsObject &O)
{
    asCopy(O);
}

void AsObject::operator=(const AsObject &O)
{
    asCopy(O);
}

void AsObject::asCopy(const AsObject &O)
{
    m_tType = O.asGetType();
    m_nID = O.asGetID();
    m_properties = O.m_properties;

}

void AsObject::setProperty(int id, Variant property)
{
    // LOGDEBUG("Object Type:%d,setProperty:%d,valueType:%d",m_tType,id,property.type);
    m_properties[id] = property;
}

Variant AsObject::property(int id)
{
    if (m_properties.contains(id))
    {
        return m_properties[id];
    }
    return Variant();
}

AsFactory *AsObject::asGetFactoryPointer(void) const
{
    return m_pAsFactory;
}

// AsObjects that have AsResources should re-implement this method.
AsResource * AsObject::asGetResourcePointer( void )
{
    return Q_NULLPTR;
}

// AsObjects that have AsResources should re-implement this method.
bool AsObject::asIsResourcePointerValid( void )
{
    return true;
}

void AsObject::asSetResource( AsResource * )
{

}

unsigned int AsObject::asGetResource( void ) const
{
    int resId =getPropertyIdByName("resource");
    void *value = m_properties.value(resId).value;
    if( !value ){
        return 0;
    }
    return *(unsigned int*)value;
}

bool AsObject::asLoadResourceDataFile( const QString&, const QString& )
{
    return false;
}

QString AsObject::asGetPropertyNameById(int nID)
{
    return getPropertyNameById(nID);
}

QString AsObject::getPropertyNameById(int nID)
{
    return m_lTypes().key((AsEnumObjectType)nID);
}

bool AsObject::isSupportSerializer()
{
    bool support = false;
    switch (m_tType)
    {
        case AsObject::AS_OBJECT_BACKGROUND:
        case AsObject::AS_OBJECT_GRID:
        case AsObject::AS_OBJECT_IMAGE:
        case AsObject::AS_OBJECT_IMAGERES:
        case AsObject::AS_OBJECT_ANNOTATION:
        case AsObject::AS_OBJECT_ANNOTATIONRES:
        case AsObject::AS_OBJECT_SHAPE:
        case AsObject::AS_OBJECT_SHAPERES:
        case AsObject::AS_OBJECT_TEXT:
        case AsObject::AS_OBJECT_TEXTRES:
        case AsObject::AS_OBJECT_ORIGIN:
        case AsObject::AS_OBJECT_TRANSFORM:
        case AsObject::AS_OBJECT_INK:
        case AsObject::AS_OBJECT_PAGE:
        case AsObject::AS_OBJECT_ASRENDERABLEGROUP:
        case AsObject::AS_OBJECT_MEDIACONTAINER:
        case AsObject::AS_OBJECT_MEDIAFILERES:
        case AsObject::AS_OBJECT_ACTIONOPENEXTERNAL:
        case AsObject::AS_OBJECT_ACTIONONOBJECT:
        case AsObject::AS_OBJECT_ACTIONONTEXT:
        case AsObject::AS_OBJECT_LAUNCH_MINIAPP_ACTION:
        case AsObject::AS_OBJECT_MOTIONRES:
        case AsObject::AS_OBJECT_MOVEACTION:
        case AsObject::AS_OBJECT_NAVIGATEACTION:
        case AsObject::AS_OBJECT_LINE:
        case AsObject::AS_OBJECT_LINERES:
            support = true;
            break;
        default:
            break;
    }
    return support;
}

int AsObject::getPropertyIdByName(QString name) const
{
    return m_lTypes().value(name);
}

const Json::Value &AsObject::asResourceSerialized()
{
    return m_resourceJsonObject;
}

bool AsObject::isPropertyNeededSerialized(int nID)
{
    return true;
}

QString AsObject::typeName()
{
    return "UnParsedType";
}

void AsObject::addAction(int nId)
{
    m_lActionId.append(nId);
}

bool AsObject::isAction()
{
    return false;
}




