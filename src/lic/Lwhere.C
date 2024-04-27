/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lwhere.C,v $
 *  $Date: 1999/08/27 15:31:30 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1995, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: Lwhere.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:30  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:28:55  lazy
 * Initial revision
 *
 */

/* -------------------------------------------------------------
   (C) Dirk Laessig
   ------------------------------------------------------------- */

#include "Lwhere.h"
#include "Lwidget.h"
#include "Lproject.h"
#include "Lpalette.h"

#include <X11/cursorfont.h>
#include <unistd.h>
#include <lac/View.h>

Cursor Lwhere::tl;
Cursor Lwhere::bl;
Cursor Lwhere::br;
Cursor Lwhere::tr;
Cursor Lwhere::mv;
Cursor Lwhere::t;
Cursor Lwhere::r;
Cursor Lwhere::l;
Cursor Lwhere::b;
Cursor Lwhere::cross;

GC Lwhere::gc;
Cardinal Lwhere::grid = 10;


// -------------------------------------------------------
//    Konstruktor zum erzeugen eines neuen Widgets
// -------------------------------------------------------

Lwhere::Lwhere( Lproject &, Boolean withSize )
{
  initClass();

  cancel = FALSE;

  Window root = XRootWindowOfScreen( XtScreen(Lproject::current().getTopLevel()));
  Display *display = XtDisplay(Lproject::current().getTopLevel());

  Window window = root, retRoot, retChild;
  int pressX, pressY, retRootX, retRootY, retX, retY, 
      endX, endY, storeX, storeY;
  unsigned int retKey;
  Boolean toDo, pressed, firstFlag = TRUE;
  int dummy;
  unsigned int udummy;
  Cursor currentCursor;
  
  while(  XQueryPointer( display, root,            // wait til left mb is up
			&retRoot, &retChild,
			&retRootX, &retRootY,
			&retX, &retY,
			&retKey ) && (retKey & Button1Mask) == Button1Mask );

  toDo = TRUE;
  pressed = False;
  
  if( withSize )
    currentCursor = tl;
  else
    currentCursor = cross;

  XGrabPointer( display, root, True, 0, GrabModeAsync, GrabModeAsync,
	       root, currentCursor, CurrentTime );
  while( XQueryPointer(display, root, &retRoot, &retChild,
		       &retRootX, &retRootY, &retX, &retY, &retKey) && toDo) {

    if( !pressed && ( (retKey & Button1Mask) == Button1Mask ) ) {
      pressed = True;        // Das erste mal wird der Button gedrueckt
      pressX = storeX = retX;
      pressY = storeY = retY;
      while( retChild ) {
	window = retChild;
	XQueryPointer( display, window,       // Window in dem sich der 
		      &retRoot, &retChild,    // Cursor befindet ermitteln
		      &dummy, &dummy,
		      &dummy, &dummy,
		      &udummy );
      }
      XFlush( display );
      if( !withSize )       // es reicht
	toDo = FALSE;
    }
    if( pressed && !( (retKey & Button1Mask) == Button1Mask ) ) {
      toDo = False;                           // end of action
      endX = retX;
      endY = retY;
    }
    if( pressed && ( (retKey & Button1Mask) == Button1Mask ) ) {
      // Anpassung ans Grid                   // dragging
      retX = retX-((retX-pressX)%grid);       
      retY = retY-((retY-pressY)%grid);

      if(storeX!=retX || storeY!=retY) {
	if( pressX < retX && pressY < retY )
	  currentCursor = br;
	if( pressX > retX && pressY < retY )
	  currentCursor = bl;
	if( pressX > retX && pressY > retY )
	  currentCursor = tl;
	if( pressX < retX && pressY > retY )
	  currentCursor = tr;
	XGrabPointer( display, root, True, 0, GrabModeAsync, GrabModeAsync,
		     root, currentCursor, CurrentTime );

	if(firstFlag) {
	  firstFlag = FALSE;
	} else {
	  XDrawLine(display,root,gc,pressX,pressY,storeX,pressY);
	  XDrawLine(display,root,gc,storeX,pressY,storeX,storeY);
	  XDrawLine(display,root,gc,storeX,storeY,pressX,storeY);
	  XDrawLine(display,root,gc,pressX,storeY,pressX,pressY);
	  XDrawLine(display,root,gc,pressX,pressY,storeX,storeY);
	  XDrawLine(display,root,gc,pressX,storeY,storeX,pressY);
	  
	  drawSize(root, pressX, pressY, storeX-pressX, storeY-pressY);
	}

	XDrawLine(display,root,gc,pressX,pressY,  retX,pressY);
	XDrawLine(display,root,gc,  retX,pressY,  retX,  retY);
	XDrawLine(display,root,gc,  retX,  retY,pressX,  retY);
	XDrawLine(display,root,gc,pressX,  retY,pressX,pressY);
	XDrawLine(display,root,gc,pressX,pressY,  retX,  retY);
	XDrawLine(display,root,gc,pressX,  retY,  retX,pressY);

	storeX = retX;
	storeY = retY;

	drawSize(root, pressX, pressY, storeX-pressX, storeY-pressY);
      }
    }
    if( (retKey & Button3Mask) == Button3Mask ) {
      // cancel this action
      cancel = TRUE;
      toDo = FALSE;
    }
    XFlush( display );
  } 
  if(!(!pressed && cancel)) {
    if(withSize) {
      XDrawLine(display,root,gc,pressX,pressY,storeX,pressY);
      XDrawLine(display,root,gc,storeX,pressY,storeX,storeY);
      XDrawLine(display,root,gc,storeX,storeY,pressX,storeY);
      XDrawLine(display,root,gc,pressX,storeY,pressX,pressY);
      XDrawLine(display,root,gc,pressX,pressY,storeX,storeY);
      XDrawLine(display,root,gc,pressX,storeY,storeX,pressY);
    }
    drawSize(root, pressX, pressY, storeX-pressX, storeY-pressY);
  }

  // ungrab the pointer
  XUngrabPointer( display, CurrentTime);
  XFlush(display);

  if( cancel )
    return;

  // Mal gucken wo er dat ding fallen laesst
  Widget widget;
  WidgetView *widgetView;

  widget = XtWindowToWidget( display, window );         
  if( widget ) {
    widgetView = WidgetView::findWidget( widget );
    while( widgetView && !XtIsComposite(widgetView->getWidget()))
      widgetView = widgetView->getParent();
    if( widgetView ) {
      window = XtWindow( widgetView->getWidget() );
      parent = widgetView->getLwidget();
    } else {
      parent = NULL;
    }
  } else 
    parent = NULL;
  if( !parent )
    window = root;

  // X und Y ausrechnen
  if( withSize ) {
    endX = endX-((endX-pressX)%grid);
    endY = endY-((endY-pressY)%grid);
    retX = pressX > endX ? endX : pressX;
    retY = pressY > endY ? endY : pressY;
  } else {
    retX = pressX;
    retY = pressY;
    endX = endY = 0;
  }

  unsigned long dummyLong;
  int ix, iy;
  XTranslateCoordinates(display, root, window, 
			retX, retY, &ix, &iy, &dummyLong );
  x = ix-(ix%grid);
  y = iy-(iy%grid);

  if( withSize ) {
    retX = pressX-endX;
    retY = pressY-endY;
    width = retX < 0 ? -retX : retX;
    height = retY < 0 ? -retY : retY;
  } else {
    width = height = 0;
  }
}



// -------------------------------------------------------
//    Konstruktor fuer resize und move
// -------------------------------------------------------

Lwhere::Lwhere( Lproject &, Widget wg )
{
  cancel = FALSE;
  selected = FALSE;

  initClass();

  Window root = XRootWindowOfScreen( XtScreen(Lproject::current().getTopLevel()));
  Display *display = XtDisplay(Lproject::current().getTopLevel());
  Window window = XtWindow(wg);
  Window dropWindow, dummyw;
  unsigned int iw, ih, bwidth, depth;
  int ix, iy;
  Pixel bg;

  XtVaGetValues(wg, XmNbackground, &bg, NULL);
  if(bg != BlackPixelOfScreen(XtScreen(wg))) {
    XSetForeground(display, gc, BlackPixelOfScreen(XtScreen(wg)) ^ bg);
  } else {
    XSetForeground(display, gc, WhitePixelOfScreen(XtScreen(wg)) ^ bg);
  }

  XGetGeometry(XtDisplay(wg), XtWindow(wg), &dummyw, 
	       &ix, &iy, &iw, &ih,
	       &bwidth, &depth);
  x = ix;
  y = iy;
  width = iw;
  height = ih;

  Window retRoot, retChild;
  int dx, dy, retRootX, retRootY, retX, retY, storeX, storeY, wd, hd;
  unsigned int retKey;
  unsigned long dummyLong;
  Boolean toDo, first;
  Cursor currentCursor;
  
  hd = height/3;
  wd = width/3;

  XQueryPointer(display,window,&retRoot,&retChild,&retRootX, &retRootY,
		&storeX, &storeY,        // Koordinaten im Widget
		&retKey );

  currentCursor = setMode(storeX,storeY,wd,hd);
  if(mode == LWHERE_MOVE || (retKey & Button1Mask)!=Button1Mask ) {    
                                   // in die Mitte gedrueckt oder losgelassen
    selected = TRUE;
    return;
  }
  int oldX = storeX, oldY = storeY;

#ifdef linux
  usleep(200000);     // 200 ms warten
#endif
  XFlush(display);

  XQueryPointer(display,window,&retRoot,&retChild,&retRootX, &retRootY,
		&storeX, &storeY,        // Koordinaten im Widget
		&retKey );

  if((retKey & Button1Mask)!=Button1Mask ) {    
                            // nicht mehr geclicked
    selected = TRUE;
    return;
  }

  dx = 0; 
  dy = 0;
  Rec rec(dx,dy,width,height);

  toDo = TRUE;
  first = TRUE;
  while( XQueryPointer( display, window, &retRoot, &retChild,
			&retRootX, &retRootY, &retX, &retY, &retKey) && toDo){
    if( (retKey & Button1Mask) != Button1Mask ) {
      toDo = False;      // no Button1 -> end
      if(retX==storeX && retY==storeY)
	selected = TRUE;       // keine Aenderung, muss wohl select sein
    }
    if( retX != oldX || retY != oldY ) {
      if(first) {
	XGrabPointer(display, root, True, 0, GrabModeAsync, GrabModeAsync,
		     root, currentCursor, CurrentTime );
	first = FALSE;
      } else {
	drawConfigure(window,rec.getX(),rec.getY(),
		      rec.getWidth(),rec.getHeight(), FALSE);
      }
      calculate(retX-oldX,retY-oldY,dx,dy,width,height);
      oldX = retX;
      oldY = retY;

      rec.setPosition(dx,dy);
      rec.setDimension(width,height);
      doGrid(rec);

      drawConfigure(window,rec.getX(),rec.getY(),
		    rec.getWidth(),rec.getHeight(), FALSE);
    }
    if( (retKey & Button3Mask) == Button3Mask ) {
      toDo = FALSE;               // cancel this action
      cancel = TRUE;
    }
  }

  // overwrite the rectangle
  if(!first)
    drawConfigure(window,rec.getX(),rec.getY(),rec.getWidth(),rec.getHeight(), 
		  FALSE);
  dx = rec.getX(); dy = rec.getY();
  width = rec.getWidth(); height = rec.getHeight();

  XUngrabPointer( display, CurrentTime );
  XFlush(display);

  if( cancel || selected ) 
    return;

  dropWindow = XtWindow(XtParent(wg));

  XTranslateCoordinates(display, window, dropWindow, 
			dx, dy, &ix, &iy, &dummyLong );
  
  x = ix;  // Die neuen Koordinaten
  y = iy;
}



// --------------------------------
//    Klassenkonstruktor
// --------------------------------
void Lwhere::initClass()
{
  Screen *screen = XtScreen(Lproject::current().getTopLevel());
  Window root = XRootWindowOfScreen(XtScreen(Lproject::current().getTopLevel()));
  Display *display = XtDisplay(Lproject::current().getTopLevel());

  if( !tl ) 
    tl = XCreateFontCursor( display, XC_top_left_corner );
  if( !bl ) 
    bl = XCreateFontCursor( display, XC_bottom_left_corner );
  if( !br ) 
    br = XCreateFontCursor( display, XC_bottom_right_corner );
  if( !tr ) 
    tr = XCreateFontCursor( display, XC_top_right_corner );
  if( !mv ) 
    mv = XCreateFontCursor( display, XC_fleur );
  if( !t ) 
    t = XCreateFontCursor( display, XC_top_side );
  if( !l ) 
    l = XCreateFontCursor( display, XC_left_side );
  if( !b ) 
    b = XCreateFontCursor( display, XC_bottom_side );
  if( !r ) 
    r = XCreateFontCursor( display, XC_right_side );
  if( !cross ) 
    cross = XCreateFontCursor( display, XC_cross );

  if( !gc ) {
    XGCValues gcValues;
    Font fid;
    XWindowAttributes attributes;

    XGetWindowAttributes(display, root, &attributes);

    fid = XLoadFont(display, app->getLwhereFont());
    if(!fid) {
      fid = XLoadFont(display, "fixed");
    }
  
    gcValues.function = GXxor;
    gcValues.subwindow_mode = IncludeInferiors;

    if(attributes.backing_pixel != BlackPixelOfScreen(screen)) {
      gcValues.foreground=attributes.backing_pixel^BlackPixelOfScreen(screen);
    } else {
      gcValues.foreground=attributes.backing_pixel^WhitePixelOfScreen(screen);
    }

    gcValues.background = 0;
    gcValues.line_width = 1;
    gcValues.font = fid;
    gc = XCreateGC( display, root, 
		   GCFunction | GCForeground | GCFont |
		   GCBackground | GCLineWidth | GCSubwindowMode,
		   &gcValues );
    XFlushGC( display, gc );
  }
}

void Lwhere::setGrid( Cardinal g ) { grid = g; }
void Lwhere::getGrid( void ) {}

// -------------------------------
// draw configure reactangles
// -------------------------------

void Lwhere::drawConfigure(Window window,int dx,int dy,int width,int height,Boolean moveOnly)
{
  Window root;
  Display *display;
  int wd, hd;
  int x, y;
  unsigned long dummyLong;

  root = XRootWindowOfScreen(XtScreen(Lproject::current().getTopLevel()));
  display = XtDisplay(Lproject::current().getTopLevel());

  XTranslateCoordinates(display, window, root, 
			dx, dy, &x, &y, &dummyLong );

  wd = width/3;
  hd = height/3;

  XDrawRectangle(display,root,gc, x, y, width, height );

  if( !moveOnly ) {
    XDrawLine(display,root,gc, x+wd, y+1, x+wd, y+height-1 );
    XDrawLine(display,root,gc, x+(wd<<1), y+1, x+(wd<<1), y+height-1 );

    XDrawLine(display,root,gc, x+1, y+hd, x+width-1, y+hd );
    XDrawLine(display,root,gc, x+1, y+(hd<<1), x+width-1, y+(hd<<1) );
    drawSize(root, x, y, width, height);
  }
}


// ----------------------
// drawSize()
// ----------------------

void Lwhere::drawSize(Window window, int x, int y, int width, int height)
{
  char buf[64];
  int direction, ascent, descent;
  XCharStruct charStruct;
  XGCValues gcValues;
  Dimension tWidth, tHeight;
  Display *display = XtDisplay(Lproject::current().getTopLevel());
  
  sprintf(buf,"%dx%d", width, height);
  
  XGetGCValues(display, gc, GCFont, &gcValues );
  XQueryTextExtents(display, gcValues.font, 
		    buf, strlen(buf),
		    &direction, &ascent, &descent, &charStruct );
  tWidth = charStruct.lbearing+charStruct.rbearing;
  tHeight = charStruct.ascent+charStruct.descent;
  
  XDrawString(display, window, gc, 
	      x + width/2 - tWidth/2, 
	      y + height/2 + tHeight/2, 
	      buf, strlen(buf));
}

// ----------------------
// setMode()
// ----------------------

Cursor Lwhere::setMode(int x, int y, int wd, int hd)
{
  mode = LWHERE_MOVE;
  if( x<wd ) {
    if( y<hd )
      mode = LWHERE_TOP_LEFT;
    else
      if( y>(hd<<1) )
	mode = LWHERE_BOTTOM_LEFT;
      else
	mode = LWHERE_LEFT;
  } else 
    if( x>(wd<<1) ) {
      if( y<hd )
	mode = LWHERE_TOP_RIGHT;
      else
	if( y>(hd<<1) )
	  mode = LWHERE_BOTTOM_RIGHT;
	else
	  mode = LWHERE_RIGHT;
    } else
      if( y<hd )
	mode = LWHERE_TOP;
      else
	if( y>(hd<<1) )
	  mode = LWHERE_BOTTOM;
	else
	  mode = LWHERE_MOVE;

  switch(mode) {
  case LWHERE_MOVE:
    return mv;
    break;
  case LWHERE_TOP:
    return t;
    break;
  case LWHERE_TOP_LEFT:
    return tl;
    break;
  case LWHERE_LEFT:
    return l;
    break;
  case LWHERE_BOTTOM_LEFT:
    return bl;
    break;
  case LWHERE_BOTTOM:
    return b;
    break;
  case LWHERE_BOTTOM_RIGHT:
    return br;
    break;
  case LWHERE_RIGHT:
    return r;
    break;
  case LWHERE_TOP_RIGHT:
    return tr;
    break;
  }
  return mv;
}


// ------------------------------------
// calculate() - call while move/resize
// ------------------------------------

void Lwhere::calculate(int dx, int dy, int &x, int &y, Dimension &width, Dimension &height)
{

  switch(mode) {
  case LWHERE_MOVE:
    x += dx;
    y += dy;
    break;
  case LWHERE_TOP:
    dy = dy>height ? 0 : dy;
    y += dy;
    height -= dy;
    break;
  case LWHERE_TOP_LEFT:
    dx = dx>width ? 0 : dx;
    dy = dy>height ? 0 : dy;
    y += dy;
    height -= dy;
    x += dx;
    width -= dx;
    break;
  case LWHERE_LEFT:
    dx = dx>width ? 0 : dx;
    x += dx;
    width -= dx;
    break;
  case LWHERE_BOTTOM_LEFT:
    dx = dx>width ? 0 : dx;
    dy = -dy>height ? 0 : dy;
    x += dx;
    width -= dx;
    height += dy;
    break;
  case LWHERE_BOTTOM:
    dy = -dy>height ? 0 : dy;
    height += dy;
    break;
  case LWHERE_BOTTOM_RIGHT:
    dx = -dx>width ? 0 : dx;
    dy = -dy>height ? 0 : dy;
    height += dy;
    width += dx;
    break;
  case LWHERE_RIGHT:
    dx = -dx>width ? 0 : dx;
    width += dx;
    break;
  case LWHERE_TOP_RIGHT:
    dx = -dx>width ? 0 : dx;
    dy = dy>height ? 0 : dy;
    y += dy;
    height -= dy;
    width += dx;
    break;
  }
}

// --------------------------------------
//   doGrid()
// --------------------------------------
void Lwhere::doGrid( Rec &rec )
{
  Position x,y;
  Position nx,ny;
  Dimension w,h;

  rec.getPosition(x,y);
  rec.getDimension(w,h);

  switch( mode ) {
  case LWHERE_MOVE:
    rec.gridX(grid); rec.gridY(grid);
    break;
  case LWHERE_TOP:
    rec.gridY(grid); 
    rec.getPosition(nx, ny);
    rec.setDimension(w+(x-nx), h+(y-ny));
    break;
  case LWHERE_TOP_LEFT:
    rec.gridX(grid); rec.gridY(grid);
    rec.getPosition(nx, ny);
    rec.setDimension(w+(x-nx), h+(y-ny));
    break;
  case LWHERE_LEFT:
    rec.gridX(grid); 
    rec.getPosition(nx, ny);
    rec.setDimension(w+(x-nx), h+(y-ny));
    break;
  case LWHERE_BOTTOM_LEFT:
    rec.gridX(grid); rec.gridHeight(grid);
    rec.getPosition(nx, ny);
    rec.getDimension(w,h);
    rec.setDimension(w+(x-nx), h);
    break;
  case LWHERE_BOTTOM:
    rec.gridHeight(grid);
    break;
  case LWHERE_BOTTOM_RIGHT:
    rec.gridWidth(grid); rec.gridHeight(grid);
    break;
  case LWHERE_RIGHT:
    rec.gridWidth(grid);
    break;
  case LWHERE_TOP_RIGHT:
    rec.gridY(grid); rec.gridWidth(grid);
    rec.getPosition(nx, ny);
    rec.getDimension(w,h);
    rec.setDimension(w, h+(y-ny));
    break;
    
  }
}
