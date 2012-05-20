#ifndef _wxTiny_
#define _wxTiny_

/* wxTiny.h
   Artur Miguel Dias, 2012
   Dept. de Informatica, FCT, Universidade Nova de Lisboa.

   wxTiny is a small framework that supports simple 2D arcade games.
   It has been created for pedagogical purposes.

   wxTiny works on Windows, Linux and MacOS X and is compatible with C and C++.
   wxTiny runs on top of the (wonderful) wxWidgets library.
*/

typedef const char *const CStr;
typedef const char *XpmImage[];

typedef void (*Fun)();
typedef void (*FunD)(int dx, int dy);
typedef void (*MenuFun)(CStr command);

#ifdef __cplusplus
extern "C" {
#endif

/* How does the wxTiny framework work?
    
    The wxTiny framework owns the function 'main'. Therefore, it is wxTiny
    that is in charge of the execution of the program.
    
    wxTiny keeps running an event loop that waits for events (user-generated
    events and timer events) and dispatches them to the application
    side via four event handlers.
    
    The wxTiny framework exports several functions but requires that
    the client application defines the function 'tyMain'
*/
    
  
      
// Your application must define the function 'tyMain', a function that is
// automatically called by wxTiny to give you the opportunity to initialize
// your data structures and to supply wxTiny with essential information.
int tyMain(void);  // Application defined

    
// Call this to pass important information to the wxTiny library:
//    - the title of the game window;
//    - the width and height of the game window in pixels;
//    - a string describing the menus of the application;
//    - four event handlers that wxTiny will call automatically when appropriate.
void tySetup(CStr title,
            int panelWidth, int panelHeight, CStr menus, 
            FunD keyHandler, MenuFun menuHandler,
            Fun redrawHandler, Fun timerHandler);

// Creates an image from a description in XPM format. Returns an
// integer handle that can be used later in the DrawImage function.
int tyCreateImage(XpmImage xpm);

// Draws an image at coordinates (x, y).
void tyDrawImage(int image, int x, int y);

// Displays a message in a dialog.
void tyAlertDialog(CStr title, CStr message);

// Asks a question to the user through a dialog.
CStr tyQueryDialog(CStr title, CStr question);

// Asks the user to select an existing file.
// The dialog window supports navigating the filesystem.
CStr tyOpenDialog(void);

// Asks the user to select an existing file or create a new file.
// The dialog window supports navigating the filesystem.
CStr tySaveDialog(void);

// Displays an error message in a dialog and then quits the application.
void tyFatalError(CStr s);

// If 'paused' is true, wxTiny suspends emitting events and the game pauses.
void tyPaused(bool paused);

// Specifies the text that should appear in the status bar at the bottom of the
// window. The status bar has three parts, referenced by position: 0, 1, or 2.
void tySetStatusText(int pos, CStr txt);

// Exits the application
void tyQuit(void);

// Cartesian distance between two points, rounded up to an integer.
int tyDistance(int x1, int y1, int x2, int y2);

// Generates random ​​integer between 0 and n-1 inclusive.
int tyRand(int n);

#ifdef __cplusplus
}
#endif
     
#endif
