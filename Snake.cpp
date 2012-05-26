/*  Snake.cpp
    Goncalo Cabrita,    34422
    Filipe Fernandes,   34525

    LAP - Project 3

    Everything has been implemented as requested and is fully working.
*/

#include "wxTiny.h"
#include <string>
#include <sstream>
#include <vector>
#include <list>

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

XpmImage berryBlueSink_xpm = {
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
" XXXXX   XXXXX  ",
" XXXX     XXXX  ",
" XXXXX   XXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

XpmImage berryRed_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Red",
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

XpmImage berryRedSink_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Red",
"  c White",
"                ",
"                ",
"     XXXXX      ",
"   XXXXXXXXX    ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
" XXXXXXXXXXXXX  ",
" XXXXX   XXXXX  ",
" XXXX     XXXX  ",
" XXXXX   XXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

XpmImage berryGreen_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Green",
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

XpmImage berryGreenSink_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Green",
"  c White",
"                ",
"                ",
"     XXXXX      ",
"   XXXXXXXXX    ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
" XXXXXXXXXXXXX  ",
" XXXXX   XXXXX  ",
" XXXX     XXXX  ",
" XXXXX   XXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

XpmImage berryPink_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Pink",
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

XpmImage berryPinkSink_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Pink",
"  c White",
"                ",
"                ",
"     XXXXX      ",
"   XXXXXXXXX    ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
" XXXXXXXXXXXXX  ",
" XXXXX   XXXXX  ",
" XXXX     XXXX  ",
" XXXXX   XXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

XpmImage berryPurple_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Purple",
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

XpmImage berryPurpleSink_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Purple",
"  c White",
"                ",
"                ",
"     XXXXX      ",
"   XXXXXXXXX    ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
" XXXXXXXXXXXXX  ",
" XXXXX   XXXXX  ",
" XXXX     XXXX  ",
" XXXXX   XXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

XpmImage berryYellow_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Yellow",
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

XpmImage berryYellowSink_xpm = {
/* columns rows colors chars-per-pixel */
"16 16 2 1",
/* colors */
"X c Yellow",
"  c White",
"                ",
"                ",
"     XXXXX      ",
"   XXXXXXXXX    ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
" XXXXXXXXXXXXX  ",
" XXXXX   XXXXX  ",
" XXXX     XXXX  ",
" XXXXX   XXXXX  ",
" XXXXXXXXXXXXX  ",
"  XXXXXXXXXXX   ",
"  XXXXXXXXXXX   ",
"   XXXXXXXXX    ",
"     XXXXX      ",
"                "};

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

int empty_img, shrub_img, berryBlue_img, berryBlueSink_img,
    berryRed_img, berryRedSink_img, berryPink_img, berryPinkSink_img,
    berryGreen_img, berryGreenSink_img, berryPurple_img, berryPurpleSink_img,
    berryYellow_img, berryYellowSink_img, snakeHead_img, snakeTail_img;

void CreateImg()
{
    empty_img = tyCreateImage(empty_xpm);
    shrub_img = tyCreateImage(shrub_xpm);
    berryBlue_img = tyCreateImage(berryBlue_xpm);
    berryBlueSink_img = tyCreateImage(berryBlueSink_xpm);
    berryRed_img = tyCreateImage(berryRed_xpm);
    berryRedSink_img = tyCreateImage(berryRedSink_xpm);
    berryPink_img = tyCreateImage(berryPink_xpm);
    berryPinkSink_img = tyCreateImage(berryPinkSink_xpm);
    berryGreen_img = tyCreateImage(berryGreen_xpm);
    berryGreenSink_img = tyCreateImage(berryGreenSink_xpm);
    berryPurple_img = tyCreateImage(berryPurple_xpm);
    berryPurpleSink_img = tyCreateImage(berryPurpleSink_xpm);
    berryYellow_img = tyCreateImage(berryYellow_xpm);
    berryYellowSink_img = tyCreateImage(berryYellowSink_xpm);
    snakeHead_img = tyCreateImage(snakeHead_xpm);
    snakeTail_img = tyCreateImage(snakeTail_xpm);
}

/* Exception declarations */

class SnakeWinsException {};
class SnakeLosesException {};

/* Declaration of all the classes */

class Actor { // "Interface"
  public:
    virtual ~Actor();
    virtual void Hide() const =0;
    virtual void Show() const =0;
    virtual void Animation() =0;
    virtual void KeyHandler(int dx, int dy) =0;
    virtual int calories() const =0;
    virtual int getX() const =0;
    virtual int getY() const =0;
    virtual int getDx() const =0;
    virtual int getDy() const =0;
    virtual int getImg() const =0;
    virtual void setImg(int img) =0;
    virtual int sinkToNormal(int img) const =0;
    virtual void kill() =0;
};

class ActorClass: public Actor {
  public:
    ActorClass(int x, int y, int img, int dx, int dy);
    virtual ~ActorClass();
    static const int ACTOR_SIZE = 16;

    void Hide() const;
    void Show() const;
    void Animation();
    void KeyHandler(int dx, int dy);
    int calories() const;
    int getX() const;
    int getY() const;
    int getDx() const;
    int getDy() const;
    int getImg() const;
    void setImg(int img);
    int sinkToNormal(int img) const;
    void kill();

  protected:
    int x, y, dx, dy;
    int num_calories;
    int img;
};

class ShrubClass: public ActorClass {
  public:
    ShrubClass(int x, int y);
    virtual ~ShrubClass();
    void Animation();

  private:
    vector<Actor *> rest ;
    int time;
};

class BerryClass: public ActorClass {
  public:
    BerryClass(int x, int y, int img);
    virtual ~BerryClass();
    void Animation();

  private:
    int time;
};

class SnakeTailClass: public ActorClass {
  public:
    SnakeTailClass(int x, int y, int dx, int dy, int img);
    virtual ~SnakeTailClass();
    void Animation();
    virtual void KeyHandler(int dx, int dy);
};

class SnakeClass: public ActorClass {
  public:
    SnakeClass(int x, int y);

    virtual ~SnakeClass();

    void KeyHandler(int dx, int dy);
    void Animation();

  private:
    list<Actor *> rest ;
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
    vector<Actor *> shrubs;
    list<Actor *> berries;
    Actor *swamp[SWAMP_WIDTH][SWAMP_HEIGHT];
    int time, berries_period;

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

ActorClass::ActorClass(int x, int y, int img, int dx=0, int dy=0):
    x(x), y(y), dx(dx), dy(dy), img(img) {}
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

// Returns the number of calories an actor has.
// = 0 is non-Edible
// > 0 is Edible
int ActorClass::calories() const
{
    return num_calories;
}

// Returns the position x of the actor.
int ActorClass::getX() const
{
    return this->x;
}

// Returns the position y of the actor.
int ActorClass::getY() const
{
    return this->y;
}

// Returns the direction of the actor in the x axis.
int ActorClass::getDx() const
{
    return dx;
}

// Returns the direction of the actor in the y axis.
int ActorClass::getDy() const
{
    return dy;
}

// Returns the image of the actor.
int ActorClass::getImg() const
{
    return this->img;
}

// Sets the image of the actor.
void ActorClass::setImg(int img)
{
    this->img = img;
}

// Returns the non-sink image of a berry.
// If the given image is not a berry return the same image.
int ActorClass::sinkToNormal(int img) const
{
    if (img == berryBlueSink_img) return berryBlue_img;
    else if (img == berryRedSink_img) return berryRed_img;
    else if (img == berryPinkSink_img) return berryPink_img;
    else if (img == berryGreenSink_img) return berryGreen_img;
    else if (img == berryPurpleSink_img) return berryPurple_img;
    else if (img == berryYellowSink_img) return berryYellow_img;

    return img;
}

// Kill the actor.
void ActorClass::kill()
{
    delete this;
}

/* Concrete classes implementation */

ShrubClass::ShrubClass(int x, int y): ActorClass(x, y, shrub_img)
{
    this->time = tyRand(81) + 20;
    this->num_calories = 0;
}

ShrubClass::~ShrubClass() {}
    
void ShrubClass::Animation()
{
    time--;

    if (time <= 0)
    {
        int w = GameControlClass::SWAMP_WIDTH;
        int h = GameControlClass::SWAMP_HEIGHT;
        int tx = tyRand(2+1) - 1;
        int ty = tyRand(2+1) - 1;
        int dx = (x + w + tx) % w;
        int dy = (y + h + ty) % h;

        if (control->Get(dx, dy) == 0)
        {
            time = tyRand(81) + 20;
            Actor *s = new ShrubClass(dx, dy);
            control->Set(dx, dy, s);
            this->rest.push_back(s);
            s->Show();
        }
    }

    // animate the rest of the shrubs in the 'family'
    for (vector<Actor *>::iterator i = rest.begin();
            i != rest.end(); ++i)
    {
        (*i)->Animation();
    }
}

BerryClass::BerryClass(int x, int y, int img): ActorClass(x, y, img) {
    Show();
    this->time = tyRand(81) + 20;
    this->num_calories = 1;
}
BerryClass::~BerryClass() {}

void BerryClass::Animation()
{
    time--;

    if (time == 10)
    {
        // swap berry image to sink version
        Hide();
        if (img == berryBlue_img) img = berryBlueSink_img;
        else if (img == berryRed_img) img = berryRedSink_img;
        else if (img == berryPink_img) img = berryPinkSink_img;
        else if (img == berryGreen_img) img = berryGreenSink_img;
        else if (img == berryPurple_img) img = berryPurpleSink_img;
        else if (img == berryYellow_img) img = berryYellowSink_img;
        num_calories++; // sinking berry is worth 2 calories
        Show();
    }
    else if (time == 0)
    {
        Hide();
        control->Set(x, y, 0);
        throw this;
    }
}

SnakeTailClass::SnakeTailClass(int x, int y, int dx = 0,
                                        int dy = -1, int img = snakeTail_img):
        ActorClass(x, y, img, dx, dy) {
    this->num_calories = 0;
}

SnakeTailClass::~SnakeTailClass() {}

void SnakeTailClass::Animation()
{
    int w = GameControlClass::SWAMP_WIDTH;
    int h = GameControlClass::SWAMP_HEIGHT;
    int nx = (x + w + dx) % w;
    int ny = (y + h + dy) % h;

    Hide();
    control->Set(x, y, 0);
    x = nx;
    y = ny;
    Show();
    control->Set(x, y, this);
}

void SnakeTailClass::KeyHandler(int dx, int dy)
{
    this->dx = dx;
    this->dy = dy;
}

SnakeClass::SnakeClass(int x, int y):
    ActorClass(x, y, snakeHead_img, 0, -1) {
    this->num_calories = 0;
    int h = GameControlClass::SWAMP_HEIGHT;

    // add snake tail(initially only 1 node)
    Actor *tail = new SnakeTailClass(x, (y + h - dy) % h);
    this->rest.push_front(tail);
}
SnakeClass::~SnakeClass() {}
    
void SnakeClass::Animation()
{
    int w = GameControlClass::SWAMP_WIDTH;
    int h = GameControlClass::SWAMP_HEIGHT;
    int nx = (x + w + dx) % w;
    int ny = (y + h + dy) % h;

    Actor *neighbor = control->Get(nx, ny);

    // neighbor exists and is edible
    if (neighbor != 0 && neighbor->calories() != 0) {
        int img = neighbor->getImg();
        int img2 = sinkToNormal(img);
        bool repeat = false;
        Actor *t = new SnakeTailClass(x, y, 0, 0, img2);
        rest.push_front(t);
        list<Actor*>::iterator j = rest.begin();
        ++j; // ignore the one we just added

        for (int i = 1; i < 5 && j != rest.end(); i++, ++j)
        {
            // check if the berry we just ate has been eaten in the last 3 bites
            if ((*j)->getImg() == img2)
            {
                repeat = true;
            }

            // swap last colored berry in stomach to a snaketail image
            if (i == 3)
            {
                (*j)->setImg(snakeTail_img);
            }
        }

        // check if berry we ate was sinking
        if (neighbor->calories() > 1)
        {
            // add another tail cell in the back
            Actor *tmp = rest.back();
            rest.push_back(new SnakeTailClass(
                                (tmp->getX() + w - tmp->getDx()) % w,
                                (tmp->getY() + h - tmp->getDy()) % h,
                                tmp->getDx(), tmp->getDy()));

        }

        int tx, ty;
        tx = x;
        ty = y;
        Hide();
        x = nx;
        y = ny;
        Show();
        control->Set(x, y, this);

        // setup the new berry cell in the tail
        control->Set(tx, ty, t);
        t->Show();
        t->KeyHandler(dx, dy);

        // berry we just ate was repeated
        if (repeat)
        {
            // iterate everything in reverse
            // remove half the tail
            list<Actor*>::reverse_iterator x = rest.rbegin();
            int size = rest.size();
            int i;
            Actor *t;
            for (i = size; i > 0 && i > (size/2) &&
                x != rest.rend(); --i, ++x)
            {
                t = (*x);
                t->Hide();
                control->Set(t->getX(), t->getY(), 0);
            }

            for (; i < size; i++)
            {
                // need to pop the elements from the container
                rest.pop_back();
            }
        }

        // total of >=300 cells so the game ends in a win
        if (rest.size() >= 299) {
            throw SnakeWinsException();
        }
        else
        {
            throw neighbor;
        }

    }
    // neighbor exists and is not edible, game ends in a loss
    else if (neighbor != 0 && neighbor->calories() == 0) {
        throw SnakeLosesException();
    }
    // neighbor does not exist
    else if( neighbor == 0 )
    {
        Hide();
        control->Set(x, y, 0);
        x = nx;
        y = ny;
        Show();
        control->Set(x, y, this);

        Actor *current;
        Actor *previous = this;
        // animate the tail of the snake
        for (list<Actor*>::iterator i = rest.begin();
            i != rest.end(); ++i)
        {
            current = (*i);
            current->Animation();
            previous = (*i);

        }

        list<Actor*>::reverse_iterator i = rest.rbegin();

        current = (*i);
        i++;
        // update the tail directions
        // every node gets the previous node's direction values
        for (;i != rest.rend(); ++i)
        {
            previous = (*i);
            current->KeyHandler(previous->getDx(), previous->getDy());
            current = (*i);

        }
        current->KeyHandler(this->getDx(), this->getDy());
    }
}

void SnakeClass::KeyHandler(int dx, int dy)
{
    this->dx = dx;
    this->dy = dy;
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
    // generate next berry spawn time
    berries_period = tyRand(11) + 1;
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
    if( time % 10 == 0 ) { // counting seconds
        berries_period--;

        // time to spawn some berries
        if (berries_period == 0 && berries.size() < MAX_BERRIES)
        {
            // generate the number of berries we're spawning
            int n_berries = tyRand(5) + 1;
            int x, y;

            // spawn the actual berries
            for (;n_berries > 0; n_berries--)
            {
                do
                {
                    // get (x,y) for the berry
                    x = tyRand(SWAMP_WIDTH);
                    y = tyRand(SWAMP_HEIGHT);
                } while (this->Get(x, y) != 0);

                // randomize its color
                int img;
                switch(tyRand(6)) {
                case 0: img = berryBlue_img;
                    break;
                case 1: img = berryRed_img;
                    break;
                case 2: img = berryPink_img;
                    break;
                case 3: img = berryGreen_img;
                    break;
                case 4: img = berryPurple_img;
                    break;
                case 5: img = berryYellow_img;
                    break;
                }

                // berry is spawned and added to the berry container
                Actor *b = new BerryClass(x, y, img);
                this->berries.push_back(b);
                swamp[x][y] = b;
            }

            // generate the next berry spawn time
            berries_period = tyRand(11) + 1;
        }

        // animate ALL the shrubs
        for (vector<Actor*>::iterator i = this->shrubs.begin();
                i != this->shrubs.end(); ++i)
        {
            (*i)->Animation();
        }

        // animate ALL the berries
        for (list<Actor*>::iterator i = berries.begin();
                i != berries.end(); ++i)
        {
            try
            {
                (*i)->Animation();
            }
            catch (Actor *b)
            {
                // berry has sunk, kill it
                berries.remove(b);
                b->kill();
                break;
            }
        }

        stringstream ss;
        ss << "TIME = " << time/10;
        tySetStatusText(2, ss.str().c_str());
    }

    if( time % 1 == 0) {
        try
        {
            snake->Animation();
        }
        catch (Actor *s)
        {
            // berry was devoured, kill it
            berries.remove(s);
            s->kill();
        }
        catch (SnakeWinsException e)
        {
            // snake has won!
            stringstream ss;
            ss << "You win!"<< endl << "Score: " << time/10;
            tyAlertDialog("Win", ss.str().c_str());
            tyQuit();
        }
        catch (SnakeLosesException e)
        {
            // snake has lost!
            tyAlertDialog("Lose", "You lose!");
            tyQuit();
        }
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
    shrubs.clear();
    berries.clear();
}

void GameControlClass::BuildBoard()
{
    FreeBoard();
    int snakeX, snakeY, shrubX, shrubY;
    bool found;
    snakeX = tyRand(SWAMP_WIDTH);
    snakeY = tyRand(SWAMP_HEIGHT);

    // spawn the snake
    swamp[snakeX][snakeY] = snake = new SnakeClass(snakeX, snakeY);

    // generate and spawn the 10 shrubs while making sure they are at least 10
    // cells away from each other
    for (int i = 0; i < 10; i++)
    {

        do
        {
            found = false;
            shrubX = tyRand(SWAMP_WIDTH);
            shrubY = tyRand(SWAMP_HEIGHT);
            for(vector<Actor *>::iterator i = shrubs.begin();
                    i != shrubs.end(); ++i)
            {
                if (tyDistance((*i)->getX(), (*i)->getY(), shrubX, shrubY) < 10)
                {
                    found = true;
                    break;
                }
            }
        } while (this->Get(shrubX, shrubY) != 0 || found);

        // finally spawn the shrub and add it to the container
        Actor *s = new ShrubClass(shrubX, shrubY);
        this->shrubs.push_back(s);
        swamp[shrubX][shrubY] = s;
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
