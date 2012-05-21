/*  Snake.cpp
    Goncalo Cabrita,    34422
    Filipe Fernandes,   34525

    LAP - Project 3
*/

#include "wxTiny.h"
#include <string>
#include <sstream>
#include <iostream> // TODO: tirar
#include <vector>

using namespace std;

/* BitMaps in XPM format -- http://en.wikipedia.org/wiki/X_PixMap */

XpmImage empty_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Black",
"  c White",
/* pixels */
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                "};

XpmImage shrub_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Black",
"  c White",
/* pixels */
"                ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
" XXXXXXXXXXXXXX ",
"                "};

XpmImage berryBlue_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Blue",
"  c White",
"                ",
"                ",
"     XXXXX      ",
"   XXXXXXXXX    ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
" XXXXXXXXXXXXX  ",
" XXXXXXXXXXXXX  ",
" XXXXXXXXXXXXX  ",
" XXXXXXXXXXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

// XpmImage snakeHead_xpm = {
// /* columns rows colors chars-per-pixel */
// "16 16 21 1",
// "   c White",
// ".  c #000000",
// "+  c #DBB600",
// "@  c #DB9200",
// "#  c #DB9249",
// "$  c #DBDB49",
// "%  c #FFFF00",
// "&  c #DBB649",
// "*  c #DBDB92",
// "=  c #6D6D49",
// "-  c #B6B6B6",
// ";  c #FFFFFF",
// ">  c #6D4949",
// ",  c #494949",
// "'  c #DBDB00",
// ")  c #920000",
// "!  c #DB4900",
// "~  c #DB2400",
// "{  c #DB92B6",
// "]  c #DBB692",
// "^  c #922400",
// /* pixels */
// "                ",
// "     .....      ",
// "   ..+@#+@..    ",
// "  .@#@$%$@&@.   ",
// " .@&*******+#.  ",
// " .@*=.-;>.-*+.  ",
// ".+**.%;;.%;**@. ",
// ".**%-.,;-.,%**. ",
// ".*%$;;;;;;;$'*. ",
// ".*''';;;;;''$*. ",
// ".**)))))))))**. ",
// " .*)!~!~!~!)*.  ",
// " .+#)!{{]!)@+.  ",
// "  .@@)^)))@&.   ",
// "   ..@@#+#..    ",
// "     .....      "};

XpmImage snakeHead_xpm = {
"16 16 31 1",
"   c None",
".  c #FFFFFF",
"+  c #3CB878",
"@  c #8BCFAC",
"#  c #A6D7BE",
"$  c #63C492",
"%  c #44BA7D",
"&  c #EAEBEB",
"*  c #111111",
"=  c #B0DAC4",
"-  c #6AC596",
";  c #82CDA6",
">  c #51BE86",
",  c #3DB074",
"'  c #3EA16E",
")  c #3DB175",
"!  c #408E66",
"~  c #445D50",
"{  c #49584C",
"]  c #73332E",
"^  c #62423B",
"/  c #3F9468",
"(  c #FDFDFD",
"_  c #6B6545",
":  c #9E0B0F",
"<  c #9D0D10",
"[  c #42AE72",
"}  c #5A8358",
"|  c #90231E",
"1  c #3DB677",
"2  c #46A66D",
"................",
"..++++++++++++..",
".++++++++++++++.",
".++++++++++++++.",
".+++@#$++@#$+++.",
".++%&*=+%&*=+++.",
".+++-;>++-;>+++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++,'''''''')++.",
".++!~~{]^~~~/++.",
"(+++++_:<[+++++.",
"..++++}:|1+++++.",
"...++++21+++++..",
"................"
};

// XpmImage snakeTail_xpm = {
// /* columns rows colors chars-per-pixel */
// "16 16 3 1",
// /* colors */
// "   c White",
// "X  c Yellow",
// ".  c Black",
// /* pixels */
// "                ",
// "     .....      ",
// "   ..XXXXX..    ",
// "  .XXXXXXXXX.   ",
// " .XXXXXXXXXXX.  ",
// " .XXXXXXXXXXXX. ",
// ".XXXXXXXXXXXXX. ",
// ".XXXXXXXXXXXXX. ",
// ".XXXXXXXXXXXXX. ",
// ".XXXXXXXXXXXXX. ",
// ".XXXXXXXXXXXXX. ",
// " .XXXXXXXXXXX.  ",
// " .XXXXXXXXXXX.  ",
// "  .XXXXXXXXX.   ",
// "   ..XXXXX..    ",
// "     .....      "};

XpmImage snakeTail_xpm = {
"16 16 4 1",
"   c None",
".  c #FFFFFF",
"+  c #3CB878",
"@  c #FDFDFD",
"................",
"..++++++++++++..",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
".++++++++++++++.",
"@++++++++++++++.",
"..+++++++++++++.",
"...+++++++++++..",
"................"
};

int empty_img, shrub_img, berryBlue_img, snakeHead_img, snakeTail_img;

void CreateImg()
{
    empty_img = tyCreateImage(empty_xpm);
    shrub_img = tyCreateImage(shrub_xpm);
    berryBlue_img = tyCreateImage(berryBlue_xpm);
    snakeHead_img = tyCreateImage(snakeHead_xpm);
    snakeTail_img = tyCreateImage(snakeTail_xpm);
// TODO: More images...
}


/* Declaration of all the classes */

class Edible { // "Interface"
};

class Actor { // "Interface"
  public:
    virtual ~Actor();
    virtual void Hide() const =0;
    virtual void Show() const =0;
    virtual void Animation() =0;
    virtual void KeyHandler(int dx, int xy) =0;
// TODO: If necessary, more methods
};

class ActorClass: public Actor {
  public:
    ActorClass(int x, int y, int img);
    virtual ~ActorClass();
    static const int ACTOR_SIZE = 16;
    void Hide() const;
    void Show() const;
    void Animation();
    void KeyHandler(int dx, int xy);
  protected:
    int x, y;
    int img;
// TODO: If necessary, more methods
};

class ShrubClass: public ActorClass {
  public:
    ShrubClass(int x, int y);
    virtual ~ShrubClass();
    void Animation();
// TODO: If necessary, more methods
  private:
    vector<ActorClass *> rest ;
};

class BerryClass: public ActorClass, public Edible {
  public:
    BerryClass(int x, int y, int img);
    virtual ~BerryClass();
    void Animation();
// TODO: If necessary, more methods
};

class SnakeClass: public ActorClass {
  public:
    SnakeClass(int x, int y, int img);
    virtual ~SnakeClass();
    void KeyHandler(int dx, int xy);
    void Animation();

// TODO: If necessary, more methods
protected:
    int dx;
    int dy;
    vector<ActorClass *> rest ;
};

class SnakeTailClass: public SnakeClass {
  public:
    SnakeTailClass(int x, int y, int dx, int dy);
    virtual ~SnakeTailClass();
    void Animation();
};

class GameControl { // "Interface"
  public:
    virtual Actor *Get(int x, int y) const =0;
    virtual void Set(int x, int y, Actor *a) =0;

    virtual void KeyHandler(int dx, int xy) =0; // Player pressed a game key
    virtual void MenuHandler(CStr command) =0; // Player selected a menu
    virtual void RedrawHandler() =0; // When the window needs redrawing
    virtual void TimerHandler() =0; // Every tenth of second
};

class GameControlClass: public GameControl {
  public:
    GameControlClass();
    ~GameControlClass();

    static const int SWAMP_WIDTH = 70;
    static const int SWAMP_HEIGHT = 40;
    static const int N_SHRUBS = 10;
    static const int MAX_BERRIES = 100;

    Actor *Get(int x, int y) const;
    void Set(int x, int y, Actor *a);

    void KeyHandler(int dx, int xy);
    void MenuHandler(CStr command);
    void RedrawHandler();
    void TimerHandler();

  private:
    static string appName, authors, version;

    Actor *snake;
    Actor *shrubs[N_SHRUBS];
    Actor *berries[MAX_BERRIES];
    Actor *swamp[SWAMP_WIDTH][SWAMP_HEIGHT];
    int time;

    virtual void StartNewGame();

    virtual void InitBoard();
    virtual void FreeBoard();
    virtual void BuildBoard();

    virtual void ComandAbout();
    virtual void ComandNewGame();
    virtual void ComandQuit();
};

GameControl *control;


/* Abstract ActorClass implementation */

Actor::~Actor() {}

ActorClass::ActorClass(int x, int y, int img): x(x), y(y), img(img) {}
ActorClass::~ActorClass() {}
void ActorClass::Animation() {} // Default: do nothing
void ActorClass::KeyHandler(int dx, int xy) {} // Default: do nothing
    
void ActorClass::Show() const
{
    tyDrawImage(img, x * ACTOR_SIZE, y * ACTOR_SIZE);
}

void ActorClass::Hide() const
{
    tyDrawImage(empty_img, x * ACTOR_SIZE, y * ACTOR_SIZE);
}


/* Concrete classes implementation */

ShrubClass::ShrubClass(int x, int y): ActorClass(x, y, shrub_img) {}
ShrubClass::~ShrubClass() {}
    
void ShrubClass::Animation()
{
    // TODO: Implement the Shrub behavior
}

BerryClass::BerryClass(int x, int y, int img): ActorClass(x, y, img) {}
BerryClass::~BerryClass() {}
    
void BerryClass::Animation()
{
    // TODO: Implement the Berry behavior
}

SnakeClass::SnakeClass(int x, int y, int img):
    ActorClass(x, y, img) {
    dx = 0;
    dy = -1;
}
SnakeClass::~SnakeClass() {}
    
void SnakeClass::Animation()
{
    int w = GameControlClass::SWAMP_WIDTH;
    int h = GameControlClass::SWAMP_HEIGHT;
    int nx = (x + w + dx) % w;
    int ny = (y + h + dy) % h;

    Actor *neighbor = control->Get(nx, ny);
    if (dynamic_cast<Edible *>(neighbor) != 0) {
        delete neighbor;
        control->Set(nx, ny, 0);

    }
    else if (neighbor != 0 && dynamic_cast<Edible *>(neighbor) == 0) {
        tyAlertDialog("Loss", "You fail!");
        tyQuit();
    }

    if( control->Get(nx, ny) == 0 ) {
        Hide();
        control->Set(x, y, 0);
        x = nx;
        y = ny;
        Show();
        control->Set(x, y, this);
    }
}

void SnakeClass::KeyHandler(int dx, int dy)
{
    if (this->dx + dx != 0 && this->dy + dy != 0) {
        this->dx = dx;
        this->dy = dy;
    }
}

SnakeTailClass::SnakeTailClass(int x, int y, int dx, int dy):
        SnakeClass(x, y, snakeTail_img) {
    this->dx = dx;
    this->dy = dy;
}

SnakeTailClass::~SnakeTailClass() {}

void SnakeTailClass::Animation() {
    // TODO
}

/* GameControlClass implementation */

void KeyHandlerFun(int dx, int dy) { control->KeyHandler(dx, dy); }
void MenuHandlerFun(CStr command) { control->MenuHandler(command); }
void RedrawHandlerFun() { control->RedrawHandler(); }
void TimerHandlerFun() { control->TimerHandler(); }

string GameControlClass::appName = "Snake!";
string GameControlClass::authors =
                "Gonçalo Cabrita 34422, Filipe Fernandes 34525";
string GameControlClass::version = "FCT/UNL, 2012";

GameControlClass::GameControlClass()
{
    CreateImg();
    tySetup(
        appName.c_str(),
        SWAMP_WIDTH * ActorClass::ACTOR_SIZE,
        SWAMP_HEIGHT * ActorClass::ACTOR_SIZE,
        ":+Game"
            ":&About\tCtrl-A"
            ":-"
            ":&New Game\tCtrl-N"
            ":-"
            ":&Quit\tCtrl-Q",
        KeyHandlerFun,
        MenuHandlerFun,
        RedrawHandlerFun,
        TimerHandlerFun);
    InitBoard();
    StartNewGame();
}

GameControlClass::~GameControlClass() {}

Actor *GameControlClass::Get(int x, int y) const
{
    return swamp[x][y];
}

void GameControlClass::Set(int x, int y, Actor *a)
{
    swamp[x][y] = a;
}

void GameControlClass::KeyHandler(int dx, int dy)
{
    snake->KeyHandler(dx, dy);
}

void GameControlClass::MenuHandler(CStr cmd)
{
    string c = cmd;
    if( c == "About" ) ComandAbout();
    else if( c == "New Game" ) ComandNewGame();
    else if( c == "Quit" ) ComandQuit();
    else tyFatalError(("Unknown menu command: '" + c + "'").c_str());
}

void GameControlClass::RedrawHandler()
{
    for( int y = 0 ; y < SWAMP_HEIGHT ; y++ )
        for( int x = 0 ; x < SWAMP_WIDTH ; x++ ) {
            Actor *a = swamp[x][y];
            if( a != 0 )
                a->Show();
        }
}

void GameControlClass::TimerHandler()
{
    // TODO: Send animation events to all the actors
    if( time % 10 == 0 ) { // counting seconds
        stringstream ss;
        ss << "TIME = " << time/10;
        tySetStatusText(2, ss.str().c_str());
    }

    if( time % 1 == 0) {
        snake->Animation();
    }
    time++;
}

void GameControlClass::StartNewGame()
{
    BuildBoard();
    tySetStatusText(0, appName.c_str());
    tySetStatusText(1, authors.c_str());
}

void GameControlClass::InitBoard()
{
    for( int x = 0 ; x < SWAMP_WIDTH ; x++ )
        for( int y = 0 ; y < SWAMP_HEIGHT ; y++ )
            swamp[x][y] = 0;
}

void GameControlClass::FreeBoard()
{
    for( int x = 0 ; x < SWAMP_WIDTH ; x++ )
        for( int y = 0 ; y < SWAMP_HEIGHT ; y++ )
            if( swamp[x][y] != 0 ) {
                delete swamp[x][y];
                swamp[x][y] = 0;
            }
}

void GameControlClass::BuildBoard()
{
    FreeBoard();
    int snakeX, snakeY, shrubX, shrubY, berryX, berryY;
    snakeX = tyRand(GameControlClass::SWAMP_WIDTH);
    snakeY = tyRand(GameControlClass::SWAMP_HEIGHT);

    snake = swamp[snakeX][snakeY] =
                                new SnakeClass(snakeX, snakeY, snakeHead_img);
    for (int i = 0; i < 10; i++)
    {
        do
        {
            berryX = tyRand(GameControlClass::SWAMP_WIDTH);
            berryY = tyRand(GameControlClass::SWAMP_HEIGHT);
        } while (this->Get(berryX, berryY) != 0);

        do
        {
            shrubX = tyRand(GameControlClass::SWAMP_WIDTH);
            shrubY = tyRand(GameControlClass::SWAMP_HEIGHT);
        } while (this->Get(shrubX, shrubY) != 0);

        swamp[berryX][berryY] = new BerryClass(berryX, berryY, berryBlue_img);
        swamp[shrubX][shrubY] = new ShrubClass(shrubX, shrubY);
    }
}

void GameControlClass::ComandAbout()
{
    stringstream ss;
    ss << appName << "\n\n" << authors  << "\n\n" << version;;
    tyAlertDialog("About", ss.str().c_str());
}

void GameControlClass::ComandNewGame()
{
    StartNewGame();
}

void GameControlClass::ComandQuit()
{
    tyAlertDialog("Quit", "Bye bye! Come back again!");
    tyQuit();
}


/* MAIN */

int tyMain()
{
    control = new GameControlClass();
    return 0;
}
