/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
#ifndef _LWHERE_H_
#define _LWHERE_H_

#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <lac/Rec.h>

class Lwidget;
class Lproject;
class Lpalette;

class Lwhere {
  typedef enum { 
    LWHERE_MOVE,
    LWHERE_TOP,
    LWHERE_TOP_LEFT,
    LWHERE_LEFT,
    LWHERE_BOTTOM_LEFT,
    LWHERE_BOTTOM,
    LWHERE_BOTTOM_RIGHT,
    LWHERE_RIGHT,
    LWHERE_TOP_RIGHT } Mode;

private:
  static Cursor tl, bl, br, tr, mv, t, l, r, b, cross;
  static GC gc;
  static Cardinal grid;

  Position  x, y;
  Dimension width, height;
  Lwidget   *parent;
  Boolean   cancel;
  Boolean   selected;

  Mode mode;

  // draw rectangles on root window
  void drawConfigure(Window window, int x, int y, int width, int height, 
		     Boolean move);
  void drawSize(Window window, int x, int y, int width, int height);

  Cursor setMode(int x, int y, int wd, int hd);
  void calculate(int dx,int dy,int &x,int &y,Dimension &width,Dimension &height);
  void doGrid(Rec &rec);

public:
  Lwhere(Lproject& project, Boolean withSize=TRUE);
  Lwhere(Lproject& project, Widget toDrag);
  Lwhere(): x(0), y(0), width(0), height(0), parent(NULL), cancel(FALSE) {}

  Position getx() const { return x; }
  Position gety() const { return y; }
  Dimension getwidth() const { return width; }
  Dimension getheight() const { return height; }

  void setx(Position xx) { x = xx; }
  void sety(Position xx) { y = xx; }
  void setwidth(Dimension xx) { width = xx; }
  void setheight(Dimension xx) { height = xx; }

  Lwidget *getparent() const { return parent; }
  Boolean isCanceled() const { return cancel; }
  Boolean isSelected() const { return selected; }
  void setparent( Lwidget *aParent ) { parent = aParent; }

  static void setGrid( Cardinal );
  static void getGrid( void );
  static void initClass();
};

#endif














