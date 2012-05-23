/*  Snake.cpp
    Goncalo Cabrita,    34422
    Filipe Fernandes,   34525

    LAP - Project 3
*/

#include "wxTiny.h"
#include <string>
#include <sstream>
#include <iostream> // delete
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

int sinkToNormal(int img)
{
    if (img == berryBlueSink_img) return berryBlue_img;
    else if (img == berryRedSink_img) return berryRed_img;
    else if (img == berryPinkSink_img) return berryPink_img;
    else if (img == berryGreenSink_img) return berryGreen_img;
    else if (img == berryPurpleSink_img) return berryPurple_img;
    else if (img == berryYellowSink_img) return berryYellow_img;

    return img;
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
    virtual void KeyHandler(int dx, int dy) =0;
    virtual int getX() const =0;
    virtual int getY() const =0;
    virtual int getImg() const =0;
    virtual void setImg(int img) =0;
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
    void KeyHandler(int dx, int dy);
    int getX() const;
    int getY() const;
    int getImg() const;
    void setImg(int img);

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
    int time;
};

class BerryClass: public ActorClass, public Edible {
  public:
    BerryClass(int x, int y, int img);
    virtual ~BerryClass();
    void Animation();
// TODO: If necessary, more methods
  private:
    int time;
};

class SnakeTailClass: public ActorClass {
  public:
    SnakeTailClass(int x, int y, int dx, int dy, int img);
    virtual ~SnakeTailClass();
    void Animation();
    virtual void Animation(list<SnakeTailClass*>::iterator i,
                                            list<SnakeTailClass*>::iterator j);
    virtual void KeyHandler(int dx, int dy);
    virtual int getDx() const;
    virtual int getDy() const;
    virtual int getX() const;
    virtual int getY() const;

  private:
    int dx;
    int dy;
};

class SnakeClass: public ActorClass {
  public:
    SnakeClass(int x, int y);
    virtual ~SnakeClass();
    void KeyHandler(int dx, int dy);
    void Animation();

// TODO: If necessary, more methods
  private:
    int dx;
    int dy;
    list<SnakeTailClass *> rest ;
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

int ActorClass::getX() const
{
    return this->x;
}

int ActorClass::getY() const
{
    return this->y;
}

int ActorClass::getImg() const
{
    return this->img;
}

void ActorClass::setImg(int img)
{
    this->img = img;
}

/* Concrete classes implementation */

ShrubClass::ShrubClass(int x, int y): ActorClass(x, y, shrub_img)
{
    this->time = tyRand(81) + 20;
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
            ActorClass *s = new ShrubClass(dx, dy);
            control->Set(dx, dy, s);
            this->rest.push_back(s);
            s->Show();
        }
    }

    for (vector<ActorClass *>::iterator i = rest.begin();
            i != rest.end(); ++i)
    {
        (*i)->Animation();
    }
}

BerryClass::BerryClass(int x, int y, int img): ActorClass(x, y, img) {
    Show();
    this->time = tyRand(81) + 20;
}
BerryClass::~BerryClass() {}

void BerryClass::Animation()
{
    time--;

    if (time == 10)
    {
        Hide();
        if (img == berryBlue_img) img = berryBlueSink_img;
        else if (img == berryRed_img) img = berryRedSink_img;
        else if (img == berryPink_img) img = berryPinkSink_img;
        else if (img == berryGreen_img) img = berryGreenSink_img;
        else if (img == berryPurple_img) img = berryPurpleSink_img;
        else if (img == berryYellow_img) img = berryYellowSink_img;
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
        ActorClass(x, y, img) {
    this->dx = dx;
    this->dy = dy;
}

SnakeTailClass::~SnakeTailClass()
{
    Hide();
}

void SnakeTailClass::Animation()
{
//    int w = GameControlClass::SWAMP_WIDTH;
//    int h = GameControlClass::SWAMP_HEIGHT;
//    int nx = (x + w + dx) % w;
//    int ny = (y + h + dy) % h;
//
//    Hide();
//    control->Set(x, y, 0);
//    x = nx;
//    y = ny;
    Show();
//    control->Set(x, y, this);
}

void SnakeTailClass::Animation(list<SnakeTailClass*>::iterator i,
                                list<SnakeTailClass*>::iterator j) {
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

    // update next tail 'node'
    SnakeTailClass *s = *i;
    if (i != j)
    {
        s->Animation(++i, j);
        s->KeyHandler(this->dx, this->dy);
    }
}

void SnakeTailClass::KeyHandler(int dx, int dy)
{
    this->dx = dx;
    this->dy = dy;
}

int SnakeTailClass::getDx() const { return dx; }
int SnakeTailClass::getDy() const { return dy; }
int SnakeTailClass::getX() const { return x; }
int SnakeTailClass::getY() const { return y; }

SnakeClass::SnakeClass(int x, int y):
    ActorClass(x, y, snakeHead_img) {
    dx = 0;
    dy = -1;
    int h = GameControlClass::SWAMP_HEIGHT;

    // add snake tail(initially only 1 node)
    SnakeTailClass *tail = new SnakeTailClass(x, (y + h + 1) % h);
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
    if (dynamic_cast<Edible *>(neighbor) != 0) {
        int img = neighbor->getImg();
        int img2 = sinkToNormal(img);
        bool repeat = false;
        SnakeTailClass *t = new SnakeTailClass(x, y, 0, 0, img2);
        rest.push_front(t);
        list<SnakeTailClass*>::iterator j = rest.begin();
        ++j; // ignore the one we just added

        for (int i = 1; i < 5 && j != rest.end(); i++, ++j)
        {
            if ((*j)->getImg() == img2)
            {
                repeat = true;
            }

            if (i == 3)
            {
                (*j)->setImg(snakeTail_img);
            }
        }

        if (img == berryBlueSink_img || img == berryRedSink_img ||
                img == berryPinkSink_img || img == berryGreenSink_img
                || img == berryPurpleSink_img || img == berryYellowSink_img)
        {
            SnakeTailClass *tmp = rest.back();
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

        control->Set(tx, ty, t);
        t->Show();
        t->KeyHandler(dx, dy);

        // TODO: fix this shit
        if (repeat)
        {
            list<SnakeTailClass*>::reverse_iterator x = rest.rbegin();
            int size = rest.size();
            for (int i = size; i > size/2 &&
                x != rest.rend(); i--, --x)
            {
                SnakeTailClass *t = (*x);
                control->Set(t->getX(), t->getY(), 0);
                t->Hide();
                delete t;
            }

            for (int i = size; i > size/2; i--)
            {
                rest.pop_back();
            }
        }

        throw neighbor;

    }
    else if (neighbor != 0 && dynamic_cast<Edible *>(neighbor) == 0) {
        tyAlertDialog("Loss", "You fail!");
        tyQuit();
    }
    else if( neighbor == 0 )
    {
        Hide();
        control->Set(x, y, 0);
        x = nx;
        y = ny;
        Show();
        control->Set(x, y, this);

        list<SnakeTailClass*>::iterator i = rest.begin();

        SnakeTailClass *s = *i;
        s->Animation(++i, rest.end());
        s->KeyHandler(this->dx, this->dy);
    }
}

void SnakeClass::KeyHandler(int dx, int dy)
{
    if (this->dx + dx != 0 && this->dy + dy != 0) {
        this->dx = dx;
        this->dy = dy;
    }
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
        if (berries_period == 0 && berries.size() < MAX_BERRIES)
        {
            int n_berries = tyRand(5) + 1;
            int x, y;
            for (;n_berries > 0; n_berries--)
            {
                do
                {
                    x = tyRand(SWAMP_WIDTH);
                    y = tyRand(SWAMP_HEIGHT);
                } while (this->Get(x, y) != 0);

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
                Actor *b = new BerryClass(x, y, img);
                this->berries.push_back(b);
                swamp[x][y] = b;
            }
            berries_period = tyRand(11) + 1;
        }

        for (vector<Actor*>::iterator i = this->shrubs.begin();
                i != this->shrubs.end(); ++i)
        {
            (*i)->Animation();
        }
        for (list<Actor*>::iterator i = berries.begin();
                i != berries.end(); ++i)
        {
            try
            {
                (*i)->Animation();
            }
            catch (BerryClass *b)
            {
                berries.remove(b);
                delete b;
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
            berries.remove(s);
            delete s;
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

    swamp[snakeX][snakeY] = snake = new SnakeClass(snakeX, snakeY);

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
