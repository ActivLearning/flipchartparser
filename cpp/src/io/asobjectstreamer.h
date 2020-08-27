// Defintion of the AsObjectStreamer class.
// $Author: Paul Wareing

#ifndef ASOBJECTSTREAMER_H
#define ASOBJECTSTREAMER_H

// Chunk file delimeters...
#define OPEN_OBJECT             'O'
#define CLOSE_OBJECT            'o'
#define OPEN_PROPERTY           'P'
#define CLOSE_PROPERTY          'p'
#define OPEN_REFERENCE          'R'
#define CLOSE_REFERENCE         'r'
#define OPEN_NODE               'N'
#define CLOSE_NODE              'n'
#define OPEN_SOFT_CHILD         'S'
#define CLOSE_SOFT_CHILD        's'
#define OPEN_CONNECTION         'C'
#define CLOSE_CONNECTION        'c'
#define OPEN_USER_PROPERTY      'U'
#define CLOSE_USER_PROPERTY     'u'
#define OPEN_OBJECT_MAP         'M'
#define CLOSE_OBJECT_MAP        'm'

#include <QVariant>
#include <QDataStream>
#include <QRectF>

#include "asstreamer.h"
#include "../dataStruct/aspointfarray.h"
#include "../objects/asobject.h"
#include "../global/asdefines.h"
#include "asnode.h"
#include "../asfactory.h"
#include <QBuffer>

#include "../util/asutil.h"

#include "../dataStruct/aspointfarrayarray.h"
#include "../objects/aspointer.h"
#include "../resources/asresourceindex.h"
#include "../dataStruct/astextrunarray.h"
#include "../objects/asundoresourceindex.h"
#include "../dataStruct/asoptionlist.h"
#include "../dataStruct/asstringpairlist.h"

#include "../dataStruct/asmoulist.h"
#include "../objects/asvirtualfolderindex.h"
#include "asasynctestlevellist.h"

class AsResourceIndex;
class AsPointer;
class AsTextRunArray;
class AsUndoResourceIndex;
class AsPointFArrayArray;
class AsInstructListList;
class AsInstructList;
class AsPathInstruct;
class AsAsyncTestLevelList;
class AsResourceRegister;
class AsInk;
class AsTransform;
class AsOrigin;
class AsLabel{};
class AsTextCharFormat{};
struct Variant;
class AsMetaConnection
{
public:
    // note: new entries must be added to the bottom of enums
    // you must not insert into or delete from these enums
    enum AsEnumConnectionSource
    {
        ASSOURCE_NONE									= 0,
        ASSOURCE_UNUSED_1                 				= 1,
        ASSOURCE_ACTION_RUNMODE_CLICKED					= 2,
        ASSOURCE_UNUSED_2             			        = 3,
        ASSOURCE_ACTION_RUNMODE_MOUSEOVER				= 4,
        ASSOURCE_UNUSED_3                       		= 5,
        ASSOURCE_ACTION_RUNMODE_MOUSEDOWN				= 6,
        ASSOURCE_UNUSED_4               				= 7,
        ASSOURCE_ACTION_RUNMODE_MOUSEUP					= 8,
        ASSOURCE_ACTION_REWARDSOUND						= 9,
        ASSOURCE_FEATURE_GUI_GUIEVENT					= 10,
        ASSOURCE_FEATURE_CORE_GUIEVENT					= 11,
        ASSOURCE_FEATURE_SHOWHIDECANVASSES				= 12,
        //ASSOURCE_FEATURE_PENCOLOR						= 13,
        //ASSOURCE_FEATURE_PENWIDTH						= 14,
        //ASSOURCE_FEATURE_RESOURCELIBRARY				= 15,
        ASSOURCE_FEATURE_DUALUSER						= 16,
        ASSOURCE_FEATURE_REVEALER						= 17,
        ASSOURCE_FEATURE_TOOLSELECTED					= 18,
        ASSOURCE_FEATURE_LAUNCHCLOCK					= 19,
        //ASSOURCE_FEATURE_SPOTLIGHTSELECTED			= 22,
        ASSOURCE_FEATURE_XYORIGIN                       = 24,
        ASSOURCE_FEATURE_EXPRESSPOLL                    = 25,
        ASSOURCE_FEATURE_STARTSTOPVOTE                  = 26,
        ASSOURCE_FEATURE_DUALMODETOGGLED				= 27,
        ASSOURCE_FEATURE_PROPERTIES						= 28,
        ASSOURCE_FEATURE_LAUNCHDEVREG					= 29,
        ASSOURCE_FEATURE_FOLLOWONQUESTION               = 30,
        ASSOURCE_FEATURE_LAUNCHDICE						= 31,
        //ASSOURCE_FEATURE_FLIPCHARTSTILED				= 33,
        ASSOURCE_FEATURE_FULLSCREEN						= 34,
        ASSOURCE_FEATURE_GROUPEDTOGGLED					= 35,
        ASSOURCE_FEATURE_PAUSEVOTE  					= 36,
        ASSOURCE_FEATURE_SHOWBROWSERS					= 37,
        ASSOURCE_FEATURE_SHOWDOCUMENTTABS				= 38,
        ASSOURCE_FEATURE_SHOWMENUBAR					= 39,
        ASSOURCE_FEATURE_SHOWTRASHCAN					= 40,
        ASSOURCE_FEATURE_TOGGLEDESIGNMODE				= 41,
        ASSOURCE_FEATURE_TEACHERLOCK					= 42,
        ASSOURCE_FEATURE_SPOTLIGHTCIRCLE				= 43,
        ASSOURCE_FEATURE_SPOTLIGHTCIRCLEREVERSED    	= 44,
        ASSOURCE_FEATURE_SPOTLIGHTSQUARE				= 45,
        ASSOURCE_FEATURE_SPOTLIGHTSQUAREREVERSED    	= 46,
        ASSOURCE_FEATURE_LAUNCHCALC                     = 47,
        ASSOURCE_FEATURE_HIDEGRID                       = 48,
        ASSOURCE_FEATURE_SNAPTOGRID                     = 49,
        ASSOURCE_FEATURE_SHOWPAGEEXTENDER				= 50,
        ASSOURCE_FEATURE_ACTIVIEW                       = 51,
        // note: new entries must be added to the bottom of this list
        // you must not insert into or delete from this list
        // current next entry available = 52: PLEASE KEEP UPTO DATE
    };

    enum AsEnumConnectionSink
    {
        ASSINK_NONE										= 0,
        ASSINK_ACTION_ASRUN								= 1,				//asRun from AsAction
        ASSINK_FEATURE_GUI_GUIEVENT						= 2,
        ASSINK_FEATURE_CORE_GUIEVENT					= 3,
        ASSINK_FEATURE_ABOUT							= 4,
        ASSINK_FEATURE_NEWFLIPCHART						= 5,
        //ASSINK_FEATURE_SHOWHIDECANVASSES				= 6,
        ASSINK_FEATURE_CLEARANNOTATIONS					= 7,
        ASSINK_FEATURE_CLEAROBJECTS						= 8,
        ASSINK_FEATURE_CLEARGRID						= 9,
        ASSINK_FEATURE_CLEARBACKGROUND					= 10,
        ASSINK_FEATURE_CLEARPAGE						= 11,
        ASSINK_FEATURE_CLOSEFLIPCHART					= 12,
        ASSINK_FEATURE_EXIT								= 13,
        ASSINK_FEATURE_EXPRESSPOLL						= 14,
        ASSINK_FEATURE_STARTSTOPVOTE    				= 15,
        ASSINK_FEATURE_HELP								= 16,
        ASSINK_FEATURE_PREVIOUSPAGE						= 17,
        ASSINK_FEATURE_NEXTPAGE							= 18,
        ASSINK_FEATURE_UNDO								= 19,
        ASSINK_FEATURE_REDO								= 20,
        ASSINK_FEATURE_RESETPAGE						= 21,
        ASSINK_FEATURE_RESOURCELIBRARY					= 22,
        ASSINK_FEATURE_REVEALER							= 23,
        ASSINK_FEATURE_OPENFROMMYFLIPCHARTS				= 24,
        ASSINK_FEATURE_OPENFROMSHAREDFLIPCHARTS			= 25,
        ASSINK_FEATURE_OPENFROMOTHERLOCATION			= 26,
        ASSINK_FEATURE_DELETE							= 27,
        ASSINK_FEATURE_LABEL							= 28,
        //ASSINK_FEATURE_PENCOLOR						= 29,
        //ASSINK_FEATURE_PENWIDTH						= 30,
        ASSINK_FEATURE_CURRENTFLIPCHART					= 31,
        ASSINK_FEATURE_MRULIST							= 32,
        ASSINK_FEATURE_TOGGLEDUALMODE					= 33,
        //ASSINK_FEATURE_DUALUSER						= 34,
        //ASSINK_FEATURE_PANDA							= 35,
        ASSINK_FEATURE_LINK								= 36,
        ASSINK_FEATURE_SELECTTOOL						= 37,
        ASSINK_FEATURE_SAVE								= 38,
        ASSINK_FEATURE_SAVETOMYFLIPCHARTS				= 39,
        ASSINK_FEATURE_SAVETOSHAREDFLIPCHARTS			= 40,
        ASSINK_FEATURE_SAVETOOTHERLOCATION				= 41,
        ASSINK_FEATURE_PRINTFLIPCHART					= 42,
        ASSINK_FEATURE_EXPORTTESTTOEXCEL				= 44,
        ASSINK_FEATURE_LAUNCHCLOCK						= 45,
        ASSINK_FEATURE_CAMERA_AREA						= 46,
        ASSINK_FEATURE_CAMERA_FULLSCREEN_CURRENTPAGE	= 47,
        ASSINK_FEATURE_CAMERA_FULLSCREEN_NEWPAGE		= 48,
        ASSINK_FEATURE_CUT								= 49,
        ASSINK_FEATURE_COPY								= 50,
        ASSINK_FEATURE_PASTE							= 51,
        ASSINK_FEATURE_DUPLICATE						= 52,
        ASSINK_FEATURE_RULER							= 53,
        ASSINK_FEATURE_PROTRACTOR						= 54,
        ASSINK_FEATURE_COMPASS							= 55,
        ASSINK_FEATURE_SHOWEXPRESSPOLLFLIPCHART			= 56,
        ASSINK_FEATURE_RESULTSBROWSER					= 57,
        ASSINK_FEATURE_SPOTLIGHT						= 73,
        ASSINK_FEATURE_SPOTLIGHT_REVERSED				= 74,
        ASSINK_FEATURE_SPOTLIGHT_SQUARE					= 75,
        ASSINK_FEATURE_SPOTLIGHT_SQUAREREVERSED			= 76,
        ASSINK_FEATURE_TICKERTAPE						= 77,
        ASSINK_FEATURE_DICE								= 78,
        //ASSINK_FEATURE_DISABLEACTIONS					= 79,
        //ASSINK_FEATURE_DISABLELOCK					= 80,
        ASSINK_FEATURE_XYORIGIN                         = 82,
        //ASSINK_FEATURE_TEMPLATE_TITLEPAGE             = 83,
        //ASSINK_FEATURE_TEMPLATE_CONTENTPAGE           = 84,
        //ASSINK_FEATURE_TEMPLATE_QUESTIONPAGE          = 85,
        ASSINK_FEATURE_LAUNCHDEVREG			            = 86,
        ASSINK_FEATURE_FOLLOWONQUESTION					= 87,
        //ASSINK_FEATURE_PRESENT              			= 88,
        ASSINK_FEATURE_LAUNCH_SETTINGS					= 89,
        ASSINK_FEATURE_DESKTOPANNOTATE					= 90,
        ASSINK_FEATURE_INSERTFROMFILE					= 91,
        //ASSINK_FEATURE_FLIPCHARTBUILDER				= 92,
        ASSINK_FEATURE_ONSCREENKEYBOARD					= 93,
        ASSINK_FEATURE_USERDEFINEDBUTTON				= 95,
        ASSINK_FEATURE_EDITPROFILE						= 96,
        ASSINK_FEATURE_PAGEBROWSER						= 97,
        ASSINK_FEATURE_RESOURCEBROWSER					= 98,
        ASSINK_FEATURE_OBJECTBROWSER					= 99,
        //ASSINK_FEATURE_WEBBROWSER						= 100,
        ASSINK_FEATURE_PROPERTYBROWSER					= 101,
        ASSINK_FEATURE_ACTIONBROWSER					= 102,
        ASSINK_FEATURE_NOTEBROWSER						= 103,
        ASSINK_FEATURE_VOTINGBROWSER					= 104,
        ASSINK_FEATURE_CONVERTANNOTATIONTOTEXT			= 105,
        ASSINK_FEATURE_CONVERTANNOTATIONTOSHAPE			= 106,
        ASSINK_FEATURE_EDITTEXT							= 107,
        ASSINK_FEATURE_EDITSHAPE						= 108,
        ASSINK_FEATURE_TOGGLELOCKED						= 109,
        ASSINK_FEATURE_TOGGLEGROUPED					= 110,
        ASSINK_FEATURE_TOGGLEHIDDEN						= 111,
        ASSINK_FEATURE_TOGGLEDRAGCOPY					= 112,
        ASSINK_FEATURE_MIRRORHORIZ						= 113,
        ASSINK_FEATURE_MIRRORVERT						= 114,
        ASSINK_FEATURE_FLIPHORIZ						= 115,
        ASSINK_FEATURE_FLIPVERT							= 116,
        ASSINK_FEATURE_ALIGNLEFT						= 117,
        ASSINK_FEATURE_ALIGNCENTREHORIZ					= 118,
        ASSINK_FEATURE_ALIGNRIGHT						= 119,
        ASSINK_FEATURE_ALIGNTOP							= 120,
        ASSINK_FEATURE_ALIGNCENTREVERT					= 121,
        ASSINK_FEATURE_ALIGNBOTTOM						= 122,
        ASSINK_FEATURE_MATCHWIDTHS						= 123,
        ASSINK_FEATURE_MATCHHEIGHTS						= 124,
        ASSINK_FEATURE_MATCHANGLES						= 125,
        ASSINK_FEATURE_MATCHALL							= 126,
        ASSINK_FEATURE_BRINGTOFRONT						= 127,
        ASSINK_FEATURE_BRINGFORWARDS					= 128,
        ASSINK_FEATURE_SENDTOBACK						= 129,
        ASSINK_FEATURE_SENDBACKWARDS					= 130,
        ASSINK_FEATURE_INSERTFILELINK					= 131,
        //ASSINK_FEATURE_TILEFLIPCHARTS				    = 132,
        ASSINK_FEATURE_SPELLCHECKER					    = 133,
        ASSINK_FEATURE_CUSTOMISE					    = 134,
        ASSINK_FEATURE_INSERTPAGE					    = 135,
        //ASSINK_FEATURE_MOREQUESTIONPAGETEMPLATES	    = 136,
        ASSINK_FEATURE_SETPAGEBACKGROUND			    = 137,
        ASSINK_FEATURE_GRIDDESIGNER					    = 138,
        ASSINK_FEATURE_HIDEGRID							= 139,
        ASSINK_FEATURE_CLEARFLIPCHARTSMRULIST			= 140,
        //ASSINK_FEATURE_SELECTMARQUEEMODE				= 141,
        //ASSINK_FEATURE_SELECTCOLLECTMODE				= 142,
        //ASSINK_FEATURE_SELECTCROSSINGMODE				= 143,
        ASSINK_FEATURE_VIEWFULLSCREEN					= 144,
        ASSINK_FEATURE_SHOWMENUBAR						= 145,
        ASSINK_FEATURE_SHOWTRASHCAN						= 146,
        //ASSINK_FEATURE_ZOOMTOFITSELECTION				= 149,
        ASSINK_FEATURE_TIMESTAMP						= 150,
        ASSINK_FEATURE_OBJECTINCREASESIZE				= 151,
        ASSINK_FEATURE_OBJECTDECREASESIZE				= 152,
        ASSINK_FEATURE_OBJECTORIGINALSIZE				= 153,
        ASSINK_FEATURE_OBJECTBESTFITWIDTH				= 154,
        ASSINK_FEATURE_OBJECTBESTFITHEIGHT				= 155,
        ASSINK_FEATURE_OBJECTBESTFITPAGE				= 156,
        ASSINK_FEATURE_CALCULATOR						= 159,
        ASSINK_FEATURE_FULLSCREENRECORDER				= 160,
        ASSINK_FEATURE_SHOWBROWSERS						= 161,
        ASSINK_FEATURE_EDITUSERDEFINEDBUTTONS			= 162,
        ASSINK_FEATURE_CAMERA_POINTTOPOINT				= 163,
        ASSINK_FEATURE_CAMERA_FREEHAND					= 164,
        ASSINK_FEATURE_CAMERA_WINDOW					= 165,
        ASSINK_FEATURE_SPELLCHECK_FLIPCHART				= 166,
        ASSINK_FEATURE_EXTRACT_TEXT						= 167,
        //ASSINK_FEATURE_COPY_FORMAT					= 171,
        //ASSINK_FEATURE_PASTE_FORMAT_SELECTED			= 172,
        //ASSINK_FEATURE_PASTE_FORMAT_PAGEOBJECTS		= 173,
        //ASSINK_FEATURE_PASTE_FORMAT_ALL				= 174,
        ASSINK_FEATURE_INSERTWEBSITELINK				= 175,
        ASSINK_FEATURE_SOUNDRECORDER					= 176,
        ASSINK_FEATURE_SNAPTOGRID						= 177,
        //ASSINK_FEATURE_EDITLABEL						= 178,
        ASSINK_FEATURE_TEACHERLOCK						= 179,
        ASSINK_FEATURE_INSERTPAGE_BLANK                 = 180,
        ASSINK_FEATURE_INSERTPAGE_DESKTOPSNAPSHOT       = 181,
        //ASSINK_FEATURE_INSERTPAGE_DESKTOPOVERLAY      = 182,
        ASSINK_FEATURE_NEWBROWSERWINDOW                 = 183,
        ASSINK_FEATURE_CONVERTPPT_ASIMAGES				= 184,
        ASSINK_FEATURE_CONVERTPPT_ASOBJECTS				= 185,
        ASSINK_FEATURE_SCREENSIZE_FLIPCHART				= 186,
        ASSINK_FEATURE_800X600_FLIPCHART				= 187,
        ASSINK_FEATURE_1024X768_FLIPCHART				= 188,
        ASSINK_FEATURE_CUSTOMSIZE_FLIPCHART				= 189,
        ASSINK_FEATURE_SMART_IMPORT                     = 190,
        //ASSINK_FEATURE_IMPORTEXAMVIEW                 = 191,
        //ASSINK_FEATURE_IMPORTIMSQTI                   = 192,
        ASSINK_FEATURE_PUBLISH_DETAILS                  = 193,
        ASSINK_FEATURE_FLIPCHART_SUMMARY				= 194,
        ASSINK_FEATURE_SMART_GALLERY_IMPORT             = 195,
        ASSINK_FEATURE_TOTOPLAYER			            = 196,
        ASSINK_FEATURE_TOBOTTOMLAYER					= 197,
        ASSINK_FEATURE_TOMIDDLELAYER					= 198,
        ASSINK_FEATURE_OSWEBBROWSER						= 199,
        ASSINK_FEATURE_CAMERA_FULLSCREEN_CLIPBOARD  	= 200,
        ASSINK_FEATURE_CAMERA_FULLSCREEN_MYRESLIB		= 201,
        ASSINK_FEATURE_CAMERA_FULLSCREEN_SHAREDRESLIB	= 202,
        ASSINK_FEATURE_MOREPAGETEMPLATES				= 203,
        ASSINK_FEATURE_SELECTALL                        = 204,
        ASSINK_FEATURE_SWITCHPROFILE					= 205,
        //ASSINK_FEATURE_MOREACTIVITYTEMPLATES			= 206,
        ASSINK_FEATURE_IMPORTRESOURCEPACKTOMYRESLIB		= 207,
        ASSINK_FEATURE_IMPORTRESOURCEPACKTOSHAREDRESLIB	= 208,
        ASSINK_FEATURE_WEBUPDATE                        = 209,
        ASSINK_FEATURE_EDITSTUDENTDATABASE              = 210,
        ASSINK_FEATURE_SEARCHPLANET                     = 211,
        ASSINK_FEATURE_SAVETOPLANET                     = 212,
        ASSINK_FEATURE_COLOURPICKER						= 213,
        ASSINK_FEATURE_PAUSEVOTE						= 214,
        ASSINK_FEATURE_QUESTIONMASTER					= 215,
        ASSINK_FEATURE_QUESTIONEDITOR					= 216,
        ASSINK_FEATURE_SHOWDASHBOARD					= 217,
        ASSINK_FEATURE_CAMERA_FULLSCREEN				= 218,
        ASSINK_FEATURE_SHOWDOCUMENTTABS					= 219,
        ASSINK_FEATURE_REVEALER_REVEAL_NORTH  			= 220,
        ASSINK_FEATURE_REVEALER_REVEAL_EAST       		= 221,
        ASSINK_FEATURE_REVEALER_REVEAL_SOUTH   	    	= 222,
        ASSINK_FEATURE_REVEALER_REVEAL_WEST    			= 223,
        ASSINK_FEATURE_REVEALER_HIDE         			= 224,
        ASSINK_FEATURE_SAVEPAGETORESOURCES              = 225,
        ASSINK_FEATURE_TOGGLEDESIGNMODE					= 226,
        ASSINK_FEATURE_DESIGNMODESETTINGS				= 227,
        ASSINK_FEATURE_SAVEBACKGROUNDTORESOURCES        = 228,
        ASSINK_FEATURE_SAVEGRIDTORESOURCES              = 229,
        ASSINK_FEATURE_INSERTLINK_CURRENTSELECTION		= 230,
        ASSINK_FEATURE_1152X864_FLIPCHART				= 231,
        ASSINK_FEATURE_1280X1024_FLIPCHART				= 232,
        ASSINK_FEATURE_INSERTPAGE_BLANKBEFORECURRENT	= 233,
        ASSINK_FEATURE_SOUNDCONTROLLER                  = 234,
        ASSINT_FEATURE_STOPALLSOUNDS                    = 235,
        ASSINK_FEATURE_PROMETHEANWEBSITE				= 236,
        ASSINK_FEATURE_PROMETHEANPLANET					= 237,
        ASSINK_FEATURE_EXPORTPAGETOIMAGE                = 238,
        ASSINK_FEATURE_ASSIGNSTUDENTSTODEVICES			= 239,
        ASSINK_FEATURE_DESKTOPTOOLS						= 240,
        //ASSINK_FEATURE_INSERT_ASYNCTEST				= 241,
        //ASSINK_FEATURE_EDIT_ASYNCTEST					= 242,
        ASSINK_FEATURE_AREASCREENRECORDER				= 243,
        ASSINK_FEATURE_INSERT_TWAIN						= 244,
        ASSINK_FEATURE_PDF_IMPORT                        = 245,
        ASSINK_FEATURE_REMOVE_QUESTION                   = 246,
        ASSINK_FEATURE_SHOWPAGETRANSITIONS              = 247,
        ASSINK_FEATURE_DOCUMENT_CAMERA					 = 248,
        ASSINK_FEATURE_SHOWPENMODIFIER                  = 249,
        ASSINK_FEATURE_EDITLRSGROUPS                    = 250,
        ASSINK_FEATURE_WHATSNEW                         = 251,
        ASSINK_FEATURE_SET_SQUARE                       = 252,
        ASSINK_FEATURE_BECTA_IMPORT                     = 253,
        ASSINK_FEATURE_BECTA_EXPORT                     = 254,
        ASSINK_FEATURE_LAUNCH_MINI_APP                  = 255,
        ASSINK_FEATURE_ACTIVPROGRESS                    = 256,
        ASSINK_FEATURE_EMBED_HTML_FRAGMENT              = 257,
        ASSINK_FEATURE_SHOWPAGEEXTENDER					= 258,
        ASSINK_FEATURE_ACTIVIEW                         = 259,
        ASSINK_FEATURE_CAMERA_ACTIVIEW                  = 260,
        ASSINK_FEATURE_ANTARES                          = 261,
        ASSINK_FEATURE_SEND_VIA_EMAIL                   = 262,
        ASSINK_FEATURE_MILITARY_PROTRACTOR              = 263,
        ASSINK_FEATURE_ALL_PAGES_EXPORT_TO_JPEG          = 264,
        ASSINK_FEATURE_ALL_PAGES_EXPORT_TO_BMP          = 265,
        ASSINK_FEATURE_ALL_PAGES_EXPORT_TO_PDF          = 266,
        ASSINK_FEATURE_WEAPON_DANGER_AREA               = 267,

        // Commands to support boards with physical buttons.
        ASSINK_FEATURE_BRD_NEW_FILE						= 268,
        ASSINK_FEATURE_BRD_SAVE_FILE					= 269,
        ASSINK_FEATURE_BRD_PREV_PAGE					= 270,
        ASSINK_FEATURE_BRD_NEXT_PAGE					= 271,
        ASSINK_FEATURE_BRD_TOOL_SELECT					= 272,
        ASSINK_FEATURE_BRD_RIGHT_MOUSE_CLICK			= 273,
        ASSINK_FEATURE_BRD_PEN_BLACK					= 274,
        ASSINK_FEATURE_BRD_PEN_RED						= 275,
        ASSINK_FEATURE_BRD_PEN_BLUE						= 276,
        ASSINK_FEATURE_BRD_PEN_GREEN					= 277,
        ASSINK_FEATURE_BRD_TOOL_ERASE					= 278,
        ASSINK_FEATURE_BRD_TOOLBOX_MENU					= 279,
        ASSINK_FEATURE_BRD_TOOLBOXSETTINGS				= 280,
        ASSINK_FEATURE_BRD_QUESTION						= 281,
        ASSINK_FEATURE_BRD_FULL_SCREEN					= 282,
        ASSINK_FEATURE_BRD_SHUTDOWN						= 283,
        ASSINK_FEATURE_BRD_TOOL_HIGHLIGHT				= 284,
        ASSINK_FEATURE_BRD_UNDO							= 285,
        ASSINK_FEATURE_BRD_PAGE_RESET					= 286,
        ASSINK_FEATURE_BRD_DESKTOP_ANNOTATE				= 287,
        ASSINK_FEATURE_LOOK_AND_FEEL_PRIMARY            = 288,
        ASSINK_FEATURE_LOOK_AND_FEEL_STUDIO             = 289,
        // note: new entries must be added to the bottom of this list
        // you must not insert into or delete from this list
        // current next entry available = 290: PLEASE KEEP UPTO DATE

    };

    enum AsEnumConnectionType
    {
        ASTYPE_SENDER				= 0,
        ASTYPE_RECEIVER				= 1,
    };

    enum AsEnumPartnerType
    {
        ASPARTNER_ASOBJECT			= 0,
        ASPARTNER_APP				= 1,
        ASPARTNER_STUDIO			= 2,
        ASPARTNER_GUICONTROLLER		= 3,
    };
};

/**
 * Streams AsObjects to and from a QIODevice using a binary format
 */
class AsObjectStreamer : public AsStreamer
{
public:
    AsObjectStreamer( QIODevice * );
    virtual ~AsObjectStreamer();

    bool asWriteHeader();
    bool asWriteObject( AsObject *pObject );

    AsObject * asReadObjects( AsFactory * );

    bool asWriteAsNodes( AsNode *, int maxGenerations = 0 );
    AsNode * asReadAsNodes( AsFactory * );

    bool asWriteObjectProperty( AsObject *, quint16, QVariant );

private:
    QDataStream m_FileStream;


    AsObject * asReadAsObject( QDataStream&, AsFactory * );


    void asReadProperty( QDataStream&, qint32 bytes, AsFactory *, AsObject * );


    void asReadReference( QDataStream&, AsFactory *, AsObject * );


    void asReadConnection( QDataStream&, AsFactory *, AsObject * );


    AsNode * asReadAsNode ( QDataStream&, AsFactory *, AsNode *pParentNode = 0, int pos = -1 );


    void asReadSoftChild( QDataStream&, AsFactory *, AsNode * );


    void asReadUserProperty( QDataStream&, qint32 bytes, AsFactory *, AsObject * );


    bool asReadVariant( QDataStream&, qint32 bytes, AsFactory *, Variant& );

    void asReadObjectMap( QDataStream&, QList< quint32 >& );





    // Methods to stream in each object type.
    void streamIn( QDataStream&, bool& );
    void streamIn( QDataStream&, QPointF& );
    void streamIn( QDataStream&, QSizeF& );
    void streamIn( QDataStream&, QSize& );
    void streamIn( QDataStream&, QRectF& );
    void streamIn( QDataStream&, QRect& );
    void streamIn( QDataStream&, QColor& );
    void streamIn( QDataStream&, QString& );
    void streamIn( QDataStream&, QStringList& );
    void streamIn( QDataStream&, QDateTime& );
    void streamIn( QDataStream&, QTime& );
    void streamIn( QDataStream&, AsPointFArray& );
    void streamIn( QDataStream&, AsPointFArrayArray& );
    void streamIn( QDataStream&, AsResourceIndex& );
    bool streamIn( QDataStream&, AsPointer&, AsFactory * );
    void streamIn( QDataStream&, AsTextRunArray&, AsFactory * );
    void streamIn( QDataStream&, AsUndoResourceIndex& );
    void streamIn( QDataStream&, QList<Variant>&, AsFactory * );
    void streamIn( QDataStream&, AsOptionList& );
    void streamIn( QDataStream&, AsStringPairList& );
    void streamIn( QDataStream&, AsInstructListList& );
    void streamIn( QDataStream&, AsPathInstruct& );
    void streamIn( QDataStream&, AsMOUList& );
    void streamIn( QDataStream&, AsFolderIndex& );
    void streamIn( QDataStream&, AsAsyncTestLevelList& );
    void streamIn( QDataStream&, QImage& );

    // Members
    int m_nCurrentGeneration;
    int m_nMaxGenerations;
    bool m_nStreamVerionUpQt4;
};
//Q_DECLARE_METATYPE(AsVirtualFolderIndex)
//Q_DECLARE_METATYPE(AsTextCharFormat)
//Q_DECLARE_METATYPE(AsLabel)
//Q_DECLARE_METATYPE(AsOrigin)
//Q_DECLARE_METATYPE(AsTransform)
//Q_DECLARE_METATYPE(AsInk)
//Q_DECLARE_METATYPE(AsResourceRegister)
//Q_DECLARE_METATYPE(AsInstructListList)
//Q_DECLARE_METATYPE(AsMOUList)
//Q_DECLARE_METATYPE(AsUndoResourceIndex)
//Q_DECLARE_METATYPE(AsOptionList)
//Q_DECLARE_METATYPE(AsStringPairList)
//Q_DECLARE_METATYPE(AsAsyncTestLevelList)
#endif // ASOBJECTSTREAMER_H
