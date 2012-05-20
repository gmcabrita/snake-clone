/* wxTiny.cpp
   Artur Miguel Dias, 2012
   Dept. de Informatica, FCT, Universidade Nova de Lisboa.

   wxTiny is a small framework that supports simple 2D arcade games.
   It has been created for pedagogical purposes.

   wxTiny works on Windows, Linux and MacOS X and is compatible with C and C++.
   wxTiny runs on top of the (wonderful) wxWidgets library.
*/

#include <wx/wx.h>
#include <math.h>
#include "wxTiny.h"

#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif

using namespace std;

// ----------------------------------------------------------------------------
// Strings
// ----------------------------------------------------------------------------

static wxMBConv *conv;

static void SetupCharCoversion() {
    if( strlen("á") > 1 )
        conv = &wxConvUTF8;
    else
        conv = &wxConvISO8859_1;
}

#define wxStr(s)    wxString(s, *conv)

static char *cStr(wxString s) {
    static char c[1024];
#if _WIN32
    strcpy(c, s.c_str());
#else
    strcpy(c, s.char_str(*conv));
#endif
    return c;
}


// ----------------------------------------------------------------------------
// Console
// ----------------------------------------------------------------------------

#if _WIN32
#define _WIN32_WINNT 0x0500
#include <windows.h>

static HWND console = 0;

static void CreateConsole()
{
    if( AllocConsole() ) {
        console = GetConsoleWindow();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

static void Interpreter()
{
    ::SetForegroundWindow(console);
    int x;
    do {
        fflush(stdin);
        printf("> ");
        scanf("%d", &x);
        printf("< %d\n", x);    
    } while( x != 0 );
}

static void DeleteConsole()
{
    FreeConsole();
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);    
}

#else
void CreateConsole()
{
    // Nada
}
#endif


// ----------------------------------------------------------------------------
// tySetup
// ----------------------------------------------------------------------------

static wxString G_title;
static int G_panelWidth;
static int G_panelHeight;
static wxString G_menus;
static FunD G_keyHandler;
static MenuFun G_menuHandler;
static Fun G_redrawHandler;
static Fun G_timerHandler;

void tySetup(CStr title,
            int panelWidth, int panelHeight, CStr menus,
            FunD keyHandler, MenuFun menuHandler,
            Fun redrawHandler, Fun timerHandler) {
    G_title = wxStr(title);
    G_panelWidth = panelWidth;
    G_panelHeight = panelHeight;
    G_menus = wxStr(menus);
    G_keyHandler = keyHandler;    
    G_menuHandler = menuHandler;
    G_redrawHandler = redrawHandler;
    G_timerHandler = timerHandler;
}


// ----------------------------------------------------------------------------
// Images
// ----------------------------------------------------------------------------

static wxClientDC *curr_dc = 0;

static const int MAX_BITMAPS = 100;

static wxBitmap *bitMaps[MAX_BITMAPS];
static int n_bitMaps = 0;

int tyCreateImage(XpmImage xpm) {
    if( n_bitMaps < MAX_BITMAPS ) {
        bitMaps[n_bitMaps] = new wxBitmap(xpm);
        return n_bitMaps++;
    }
    else {
        tyFatalError("Too many images created.\nBye bye!");
        return 0;
    }
}

void tyDrawImage(int image, int x, int y) {
    if( curr_dc == 0 )
        tyFatalError("DrawImage called in an invalid context.\nBye bye!");
    curr_dc->DrawBitmap(*bitMaps[image], x, y, false);
}

#if !_WIN32
/* XPM */
static XpmImage mondrian_xpm = {
/* columns rows colors chars-per-pixel */
"32 32 6 1",
"  c Black",
". c Blue",
"X c #00bf00",
"o c Red",
"O c Yellow",
"+ c Gray100",
/* pixels */
"                                ",
" oooooo +++++++++++++++++++++++ ",
" oooooo +++++++++++++++++++++++ ",
" oooooo +++++++++++++++++++++++ ",
" oooooo +++++++++++++++++++++++ ",
" oooooo +++++++++++++++++++++++ ",
" oooooo +++++++++++++++++++++++ ",
" oooooo +++++++++++++++++++++++ ",
"                                ",
" ++++++ ++++++++++++++++++ .... ",
" ++++++ ++++++++++++++++++ .... ",
" ++++++ ++++++++++++++++++ .... ",
" ++++++ ++++++++++++++++++ .... ",
" ++++++ ++++++++++++++++++ .... ",
" ++++++ ++++++++++++++++++      ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++ ++++++++++++++++++ ++++ ",
" ++++++                    ++++ ",
" ++++++ OOOOOOOOOOOO XXXXX ++++ ",
" ++++++ OOOOOOOOOOOO XXXXX ++++ ",
" ++++++ OOOOOOOOOOOO XXXXX ++++ ",
" ++++++ OOOOOOOOOOOO XXXXX ++++ ",
" ++++++ OOOOOOOOOOOO XXXXX ++++ ",
" ++++++ OOOOOOOOOOOO XXXXX ++++ ",
"                                "
};
#endif


// ----------------------------------------------------------------------------
// Classes GameApp, GameFrame & GamePanel
// ----------------------------------------------------------------------------

class GameApp;
class GameFrame;
class GamePanel;

static GameFrame *gameFrame = 0;

class GameApp : public wxApp {
public:
    virtual bool OnInit();
    virtual int OnExit();
};

class GameFrame : public wxFrame {
  public:
    GameFrame();
    void Start();
    void Paused(bool paused);
  protected:
  // event handlers (these functions should _not_ be virtual)
    void OnMenu(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
  private:
    GamePanel *board;
    DECLARE_EVENT_TABLE()
};

class GamePanel: public wxPanel {
  public:
    GamePanel(GameFrame *parent);
    void Paused(bool paused);
  protected:
  // event handlers (these functions should _not_ be virtual)
    void OnPaint(wxPaintEvent& event);
  //void OnMouseMove(wxMouseEvent& event);
    void OnKeyDown(wxKeyEvent& event);
  //void OnKeyUp(wxKeyEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnSetFocus(wxFocusEvent& event);
    void OnKillFocus(wxFocusEvent& event);
  private:
    GameFrame *owner;
    bool hasFocus;
    wxTimer timer;
    int dx, dy;
    bool paused;
    DECLARE_EVENT_TABLE()
};


// ----------------------------------------------------------------------------
// Class GameApp implementation
// ----------------------------------------------------------------------------

IMPLEMENT_APP(GameApp)

bool GameApp::OnInit()
{
    SetupCharCoversion();
    CreateConsole();
    gameFrame = new GameFrame();
    if( tyMain() != 0 )
        return false;
    gameFrame->Start();
    SetTopWindow(gameFrame);
    return true;
}

int GameApp::OnExit() {
    return wxApp::OnExit();
}


// ----------------------------------------------------------------------------
// Class GameFrame implementation
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(GameFrame, wxFrame)
    EVT_MENU( 1, GameFrame::OnMenu)
    EVT_MENU( 2, GameFrame::OnMenu)
    EVT_MENU( 3, GameFrame::OnMenu)
    EVT_MENU( 4, GameFrame::OnMenu)
    EVT_MENU( 5, GameFrame::OnMenu)
    EVT_MENU( 6, GameFrame::OnMenu)
    EVT_MENU( 7, GameFrame::OnMenu)
    EVT_MENU( 8, GameFrame::OnMenu)
    EVT_MENU( 9, GameFrame::OnMenu)
    EVT_MENU(10, GameFrame::OnMenu)
    EVT_CLOSE(GameFrame::OnClose)
END_EVENT_TABLE()

GameFrame::GameFrame()
        : wxFrame(0, wxID_ANY, wxT(""),
                    wxPoint(50, 50), wxDefaultSize,
                    wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
#ifdef __WXMAC__
    ProcessSerialNumber PSN;
    GetCurrentProcess(&PSN);
    TransformProcessType(&PSN,kProcessTransformToForegroundApplication);
#endif
    
    SetIcon(wxICON(mondrian));
    CreateStatusBar(3, 0);
    
    board = new GamePanel(this);
    board->SetBackgroundColour(*wxWHITE);
    board->SetFocus();
}

void GameFrame::Start()
{
    // create the menu bar
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *menu = 0;
    wxString menuName;
    int id = 1;
    char *s = strtok(cStr(G_menus), ":");
    do {
        switch( s[0] ) {
            case '+':
                if( menu != 0 )
                    menuBar->Append(menu, menuName);
                menu = new wxMenu; 
                menuName = wxStr(s+1); 
                break;                
            case '-':
                menu->AppendSeparator();
                break; 
            default:
                menu->Append(id++, wxStr(s));
                break;
        }
    }
    while( (s = strtok(0, ":")) != 0 );
    if( menu != 0 )
        menuBar->Append(menu, menuName);
    SetMenuBar(menuBar);
    
    SetTitle(G_title);

    /* must be last */
    SetClientSize(G_panelWidth, G_panelHeight);
    Show(true);
}

void GameFrame::Paused(bool paused)
{
    board->Paused(paused);
}

void GameFrame::OnMenu(wxCommandEvent& event)
{
    unsigned int i;
    wxString s = GetMenuBar()->GetLabel(event.GetId());
    wxString n = wxT("");
    for( i = 0 ; i < s.size() && s[i] != '\t' ; i++ )
        if( s[i] != '_' && s[i] != '&' )
            n += s[i];
    G_menuHandler(cStr(n));
    board->Refresh();
}

void GameFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
    G_menuHandler("Quit");
}

void tyPaused(bool paused)
{
     if( gameFrame != 0 )
        gameFrame->Paused(paused);
}

void tySetStatusText(int pos, CStr txt)
{
    if( 0 <= pos && pos <= 2 && gameFrame != 0 )
        gameFrame->SetStatusText(wxStr(txt), pos);
}

void tyQuit()
{
    if( gameFrame != 0 )
        gameFrame->Destroy();
    else
        exit(0);
}


// ----------------------------------------------------------------------------
// GamePanel
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(GamePanel, wxPanel)
    EVT_PAINT(GamePanel::OnPaint)
  //EVT_MOTION(GamePanel::OnMouseMove)
    EVT_KEY_DOWN(GamePanel::OnKeyDown)
  //EVT_KEY_UP(GamePanel::OnKeyUp)
    EVT_TIMER(wxID_ANY, GamePanel::OnTimer)
    EVT_SET_FOCUS(GamePanel::OnSetFocus)
    EVT_KILL_FOCUS(GamePanel::OnKillFocus)
END_EVENT_TABLE()

GamePanel::GamePanel(GameFrame *parent):
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE),
    timer(this)
{
    owner = parent;
    hasFocus = false;
    timer.Start(100);
    dx = dy = 0;
    paused = false;
}

void GamePanel::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    wxPaintDC dc(this);
    PrepareDC(dc);
    dc.SetPen(*wxWHITE_PEN);
    dc.Clear();
    wxClientDC *save_dc = curr_dc;
    curr_dc = &dc;
    G_redrawHandler();
    curr_dc = save_dc;
}

/*
void GamePanel::OnMouseMove(wxMouseEvent &event)
{
    wxClientDC dc(this);
    PrepareDC(dc);
    dc.SetPen(*wxWHITE_PEN);
    wxPoint pos = event.GetPosition();
    long x = dc.DeviceToLogicalX( pos.x );
    long y = dc.DeviceToLogicalY( pos.y );
    wxString str;
    str.Printf( wxT("x=%d, y=%d"), (int)x, (int)y );
    owner->SetStatusText(str, 0);
}
*/

void GamePanel::OnKeyDown(wxKeyEvent& event)
{
    switch ( event.GetKeyCode() )
    {
        case WXK_LEFT:  case 'O': case 'J': dx = -1; dy =  0; break;
        case WXK_UP:    case 'Q': case 'I': dx =  0; dy = -1; break;
        case WXK_RIGHT: case 'P': case 'L': dx =  1; dy =  0; break;
        case WXK_DOWN:  case 'A': case 'K': dx =  0; dy =  1; break;
        default:                             dx =  0; dy =  0; break;
    }
    event.Skip();
}

// void GamePanel::OnKeyUp(wxKeyEvent& event){}

void GamePanel::OnTimer(wxTimerEvent& WXUNUSED(event))
{
    if( hasFocus && !paused ) {
        wxClientDC dc(this);
        PrepareDC(dc);
        dc.SetPen(*wxWHITE_PEN);
        curr_dc = &dc;
        if( dx != dy ) {
            G_keyHandler(dx, dy);
            dx = dy = 0;
        }
        G_timerHandler();
        curr_dc = 0;
   }
}

void GamePanel::Paused(bool paused)
{
    this->paused = paused;
}

void GamePanel::OnSetFocus(wxFocusEvent& WXUNUSED(event))
{
    hasFocus = true;
}

void GamePanel::OnKillFocus(wxFocusEvent& WXUNUSED(event))
{
    hasFocus = false;
}


// ----------------------------------------------------------------------------
// DIALOGS
// ----------------------------------------------------------------------------

void tyAlertDialog(CStr title, CStr message) {
    wxMessageDialog *d =
        new wxMessageDialog(0, wxStr(message),
                            wxStr(title), wxOK | wxICON_INFORMATION);
    d->ShowModal();
    d->Destroy();
    gameFrame->Refresh();
}

CStr tyQueryDialog(CStr title, CStr question) {
    wxTextEntryDialog *d =
        new wxTextEntryDialog(
                0, wxStr(question),
                wxStr(title), wxT(""),
                wxOK | wxCENTRE);
    return d->ShowModal() == wxID_OK ? cStr(d->GetValue()) : 0;
}

CStr tyOpenDialog()
{
    wxFileDialog *d = new wxFileDialog(
            gameFrame, wxT("Open File"), wxT(""), wxT(""),
            wxT("Text files (*.txt)|*.txt"),
#if wxMINOR_VERSION > 8
            wxFD_OPEN
#else
            wxOPEN
#endif
    );
    return d->ShowModal() == wxID_OK ? cStr(d->GetPath()) : 0;
}

CStr tySaveDialog()
{
    wxFileDialog *d = new wxFileDialog(
            gameFrame, wxT("Save File As"), wxT(""), wxT(""),
            wxT("Text files (*.txt)|*.txt"),
#if wxMINOR_VERSION > 8
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT
#else
            wxSAVE | wxOVERWRITE_PROMPT
#endif
    );
    return d->ShowModal() == wxID_OK ? cStr(d->GetPath()) : 0;
}

void tyFatalError(CStr s)
{
    tyAlertDialog("Fatal Error", s);
    tyQuit();
}


// ----------------------------------------------------------------------------
// Numeric functions
// ----------------------------------------------------------------------------

int tyDistance(int x1, int y1, int x2, int y2)
{
    return (int)ceil(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

int tyRand(int n)
{
    static bool initialized = false;
    if( !initialized ) {
        srand(time(0));
        initialized = true;
    }
    return rand() % n;
}
