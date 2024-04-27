/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: SensitiveView.C,v $
 *  $Date: 1999/08/27 15:30:11 $
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
 * $Log: SensitiveView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:11  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.5  1998/03/30 19:09:37  lazy
 * *** empty log message ***
 *
 * Revision 1.4  1997/09/11  14:56:25  lazy
 * Keyboard traversal inserted and
 * scrollToMakeVisible() improved.
 *
 * Revision 1.3  1997/09/08  17:08:04  lazy
 * Move visible to test mode and changed
 * isIn*() methods of RecView()
 *
 * Revision 1.2  1997/09/06  14:06:57  lazy
 * fontList subresource added.
 *
 * Revision 1.1  1997/07/25  19:33:30  lazy
 * Initial revision
 *
 */

#include <string.h>

#include <Xm/BulletinB.h>
#include <Xm/DrawingA.h>
#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>
#include <lwid/Bubble.h>
#include <Xm/XmP.h>

#include <lac/SensitiveView.h>
#include <lac/Model.h>
#include <lac/ConModel.h>
#include <lac/LicView.h>
#include <Xm/VirtKeys.h>

#include <math.h>

#define RB_SCROLL_VALUE  5

/* ##########################################################
                        RecView
   ########################################################## */

// ----------------------
//     RecView()
// ----------------------
RecView::RecView( Model *m)
:View(m) 
{
  x = y = 0;
  isVisible = TRUE;
}      


// ----------------------
//     ~RecView()
// ----------------------
RecView::~RecView()
{}


// ----------------------
//      isIn()
// ----------------------
Boolean RecView::isIn( Position px, Position py )
{
  if(isVisible &&
     px >= x && px <= x+getWidth() && py >= y && py <= y+getHeight())
    return TRUE;
  return FALSE;
}



// ----------------------
//      isInRec()
// ----------------------
Boolean RecView::isInRec(Rec &rec)
{
  Position px, py;
  Dimension pw, ph;

  if(isVisible) {
    rec.getPosition(px, py);
    rec.getDimension(pw, ph);

    if(px <= x && px+pw >= x+getWidth() && py <= y && py+ph >= y+getHeight()) {
      return TRUE;
    }
  }
  return FALSE;
}


// ----------------------
//      isInRecPart()
// ----------------------
Boolean RecView::isInRecPart(Rec &rec)
{
  Position px, py;
  Dimension pw, ph, w, h;

  if(isVisible) {
    w = getWidth();
    h = getHeight();
    rec.getPosition(px, py);
    rec.getDimension(pw, ph);
    
    if((x+w>=px && x<=px+pw) && (y+h>=py && y<=py+ph))
      return TRUE;
  }
  return FALSE;
}


// ----------------------------
//  getMiddle()
// ----------------------------

void 
RecView::getMiddle(Position &mx, Position &my)
{
  mx = x + getWidth()/2;
  my = y + getHeight()/2;
}


/* ######################################################
                        SensitiveRec
   ###################################################### */

SensitiveRec *SensitiveRec::draggedObject;

// ------------------------------------
//         Konstruktor
// ------------------------------------
SensitiveRec::SensitiveRec(Iconable *am, SensitiveContainer *c)
: RecView(am) 
{
  m = am;
  sensitiveContainer = c;
  if( sensitiveContainer ) {
    parent = sensitiveContainer->getWidget();
    fgGC = sensitiveContainer->getForegroundGC();
    bgGC = sensitiveContainer->getBackgroundGC();
  }
  pressed = FALSE;
  exports[0] = 0;
  highlightState = FALSE;
  tmpSelect = FALSE;
}

// ------------------------------------
//         ~SensitiveRec()
// ------------------------------------
SensitiveRec::~SensitiveRec()
{
}


// ------------------------------------
//         expose()
// ------------------------------------

void SensitiveRec::expose()
{
  if(isVisible && XtWindow(sensitiveContainer->getWidget()) &&
     isInRecPart(sensitiveContainer->getViewport())) {

    draw(tmpSelect);
    
  }
}


// ------------------------------------
//         hightlight()
// ------------------------------------
void SensitiveRec::highlight(Boolean state)
{
  if(highlightState == state)     // nothing changed
    return;
  highlightState = state;
  expose();
}

// ------------------------------------
//         update()
// ------------------------------------

void SensitiveRec::update( unsigned long flags )
{
  if( flags & SELECTION_CHANGED ) {
    expose();
  }
}

// ------------------------------------
//         select()
// ------------------------------------

void SensitiveRec::select( Boolean multi, Position, Position )
{
  m->select( multi );
}

// ------------------------------------
//         move()   
// ------------------------------------

void SensitiveRec::move(Widget wg,XEvent *event, Position, Position, unsigned char dragOperations)
{
  Atom *exportTargets = NULL;
  Cardinal numExportTargets = 0;
  Arg args[16];
  int n = 0;
  Widget sourceIcon;

  draggedObject = this;
  dragQueryExports(exportTargets,numExportTargets,sourceIcon);

  XtSetArg(args[n], XmNexportTargets, exportTargets); n++;
  XtSetArg(args[n], XmNnumExportTargets, numExportTargets); n++;
  XtSetArg(args[n], XmNconvertProc, convertProc); n++;
  XtSetArg(args[n], XmNdragOperations, dragOperations); n++;
  XtSetArg(args[n], XmNsourceCursorIcon, sourceIcon); n++;
  dragContext = XmDragStart(wg, event, args, n);
}

// ------------------------------------
//         convertProc()
// ------------------------------------

Boolean SensitiveRec::convertProc(Widget w, Atom *selection, 
				  Atom *target, Atom *type,
				  XtPointer *value, unsigned long *length, 
				  int *format, unsigned long *,
				  XtPointer, XtRequestId *)
{
  return draggedObject->convert(w, selection, target, type,
				value, length, format );
}

// ------------------------------------
//         setPressed()
// ------------------------------------

void SensitiveRec::setPressed( Boolean state )
{
  pressed = state;
  expose();
}

// -----------------------------
// dragQueryExports()
// -----------------------------

void SensitiveRec::dragQueryExports(Atom *&exportTargets, 
				    Cardinal &numExportTargets,
				    Widget &sourceIcon)
{
  if(exports[0] == 0) {
    exports[0] = XmInternAtom(XtDisplay(parent),"COMPOUND_TEXT",False);
    exports[1] = XmInternAtom(XtDisplay(parent),m->getClassName(),False);
  }
  exportTargets = exports;
  numExportTargets = 2;
  sourceIcon = NULL;
  sourceIcon = WinView::getIconFromPixmapName(parent, m->getPixmapFile());
}

// -----------------------------
// convert()
// -----------------------------

Boolean SensitiveRec::convert(Widget w, Atom *, 
			      Atom *target,Atom *type,
			      XtPointer *value, unsigned long *length,
			      int *format)
{
  XmString xmstr;
  char *ctext;
  char *passtext;

  if(*target == XmInternAtom(XtDisplay(parent),"DELETE",False)) {
    *value = NULL;
    *type = XmInternAtom(XtDisplay(w), "NULL", False);
    *length = 0;
    *format = 8;
    return True;
  }

  if(*target == exports[0]) {
    xmstr = XmStringCreateLocalized(m->getName());
    ctext = XmCvtXmStringToCT(xmstr);
    passtext = XtMalloc(strlen(ctext)+1);
    memcpy(passtext, ctext, strlen(ctext)+1);
    *value = (XtPointer) passtext;
    *length = strlen(passtext);
    *type = exports[0];
    *format = 8;
  } else {
    if(*target == exports[1]) {
      Iconable **ptr;
      *length = 1;
      *format = sizeof(Iconable*)*8;
      ptr = (Iconable**)XtMalloc(sizeof(Iconable*)*(*length));
      *ptr = m;
      *value = (XtPointer)ptr;
      *type = exports[1];
    } else
      return False;
  }

  return TRUE;
}

// ----------------------------
//  traversUp()
// ----------------------------

void 
SensitiveRec::traverseUp()
{
  Position mx, my;
  SensitiveRec *found;

  getMiddle(mx, my);
  found = sensitiveContainer->queryNextContent(mx, my, 0, -1);
  if(found) {
    found->getModel()->select();
    sensitiveContainer->scrollToMakeVisible(found->getModel());
  }
}

// ----------------------------
//  traversDown()
// ----------------------------

void 
SensitiveRec::traverseDown()
{
  Position mx, my;
  SensitiveRec *found;

  getMiddle(mx, my);
  found = sensitiveContainer->queryNextContent(mx, my, 0, 1);
  if(found) {
    found->getModel()->select();
    sensitiveContainer->scrollToMakeVisible(found->getModel());
  }
}

// ----------------------------
//  traversLeft()
// ----------------------------

void 
SensitiveRec::traverseLeft()
{
  Position mx, my;
  SensitiveRec *found;

  getMiddle(mx, my);
  found = sensitiveContainer->queryNextContent(mx, my, -1, 0);
  if(found) {
    found->getModel()->select();
    sensitiveContainer->scrollToMakeVisible(found->getModel());
  }
}

// ----------------------------
//  traversRight()
// ----------------------------

void 
SensitiveRec::traverseRight()
{
  Position mx, my;
  SensitiveRec *found;

  getMiddle(mx, my);
  found = sensitiveContainer->queryNextContent(mx, my, 1, 0);
  if(found) {
    found->getModel()->select();
    sensitiveContainer->scrollToMakeVisible(found->getModel());
  }
}

/* ###########################################################
                         SensitiveContainer
   ########################################################### */

// --------------------------------------
//           Konstruktor
// --------------------------------------
SensitiveContainer::SensitiveContainer( ContainerBase *m, Widget p )
: WinView(m)
{
  fgGC = 0;
  bgGC = 0;

  rubberBandMode = FALSE;
  highlightParent = FALSE;
  timerOn = FALSE;
  timerId = 0;
  bubble = NULL;

  this->m = m;
  dragOperations = XmDROP_COPY | XmDROP_MOVE;

  scrolledWindow = XtVaCreateWidget("SensitiveViewScrolledWindow",
				    xmScrolledWindowWidgetClass, p,
				    XmNscrollingPolicy, XmAUTOMATIC,
				    XmNscrolledWindowMarginHeight, 2,
				    XmNscrolledWindowMarginWidth, 2,
				    NULL);
  Widget hs, vs;
  XtVaGetValues(scrolledWindow, 
		XmNhorizontalScrollBar, &hs,
		XmNverticalScrollBar, &vs,
		NULL);
  XtAddCallback(vs, XmNdecrementCallback, scrollCB, this);
  XtAddCallback(vs, XmNincrementCallback, scrollCB, this);
  XtAddCallback(vs, XmNdragCallback, scrollCB, this);
  XtAddCallback(vs, XmNpageDecrementCallback, scrollCB, this);
  XtAddCallback(vs, XmNpageIncrementCallback, scrollCB, this);
  XtAddCallback(vs, XmNtoBottomCallback, scrollCB, this);
  XtAddCallback(vs, XmNtoTopCallback, scrollCB, this);
  XtAddCallback(vs, XmNvalueChangedCallback, scrollCB, this);

  XtAddCallback(hs, XmNdecrementCallback, scrollCB, this);
  XtAddCallback(hs, XmNincrementCallback, scrollCB, this);
  XtAddCallback(hs, XmNdragCallback, scrollCB, this);
  XtAddCallback(hs, XmNpageDecrementCallback, scrollCB, this);
  XtAddCallback(hs, XmNpageIncrementCallback, scrollCB, this);
  XtAddCallback(hs, XmNtoBottomCallback, scrollCB, this);
  XtAddCallback(hs, XmNtoTopCallback, scrollCB, this);
  XtAddCallback(hs, XmNvalueChangedCallback, scrollCB, this);

  box = XtVaCreateManagedWidget("SensitiveContainer",
				xmDrawingAreaWidgetClass, scrolledWindow,
				XmNresizePolicy, XmRESIZE_GROW,
				XmNmarginHeight, 0,
				XmNmarginWidth, 0,
				NULL);
    
  XtInsertEventHandler(scrolledWindow, StructureNotifyMask, 
		       False, configureEvent, this, XtListHead);
  XtAddEventHandler(box, ExposureMask,  False, expose, this );
  XtAddEventHandler(box, Button1MotionMask,  False, button_motion, this );
  XtAddEventHandler(box, ButtonPressMask,  False, button_press, this );
  XtAddEventHandler(box, KeyPressMask,  False, key_pressed, this );
  XtAddEventHandler(box, ButtonReleaseMask,  False, button_release, this );
  XtAddEventHandler(box, PointerMotionMask,  False, mouse_move, this );

  XtAddEventHandler(XtParent(box), Button1MotionMask,  
		    False, button_motion, this );
  XtAddEventHandler(XtParent(box), ButtonPressMask,  
		    False, button_press, this );
  XtAddEventHandler(XtParent(box), ButtonReleaseMask,  
		    False, button_release, this );

  XtAddEventHandler(box, FocusChangeMask,  False, focus_in, this );
  XtAddEventHandler(box, FocusChangeMask,  False, focus_out, this );
  XtAddEventHandler(scrolledWindow, ExposureMask,  False, 
		    expose_clip_window, this );
  createGCs();
  display = XtDisplay(box);
}

// ----------------------------------------
//       setModel()
// ----------------------------------------

void SensitiveContainer::setModel(ContainerBase *m)
{
  this->m = m;
  View::changeModel(m);
}

// ----------------------------------------
//       ~SensitiveContainer()
// ----------------------------------------

SensitiveContainer::~SensitiveContainer()
{
  XtRemoveEventHandler(scrolledWindow, StructureNotifyMask, 
		       False, configureEvent, this);
  XtRemoveEventHandler(box, ExposureMask,  False, expose, this );
  XtRemoveEventHandler(box, Button1MotionMask,  False, button_motion, this );
  XtRemoveEventHandler(box, ButtonPressMask,  False, button_press, this );
  XtRemoveEventHandler(box, KeyPressMask,  False, key_pressed, this );
  XtRemoveEventHandler(box, ButtonReleaseMask,  False, button_release, this );
  XtRemoveEventHandler(box, PointerMotionMask,  False, mouse_move, this );
  
  XtRemoveEventHandler(XtParent(box), Button1MotionMask,  
		       False, button_motion, this );
  XtRemoveEventHandler(XtParent(box), ButtonPressMask,  
		       False, button_press, this );
  XtRemoveEventHandler(XtParent(box), ButtonReleaseMask,  
		       False, button_release, this );
  
  XtRemoveEventHandler(box, FocusChangeMask,  False, focus_in, this );
  XtRemoveEventHandler(box, FocusChangeMask,  False, focus_out, this );
  XtRemoveEventHandler(scrolledWindow, ExposureMask,  False, 
		       expose_clip_window, this );
  
  while( contents.getSize() ) {
    contents[0].Delete();
  }
  XtDestroyWidget(scrolledWindow);
  XFreeGC(display,fgGC);
  XFreeGC(display,bgGC);
  if(fontList)
    XmFontListFree(fontList);
}


// --------------------------------------
//           processKey()
// --------------------------------------
void SensitiveContainer::processKey(XKeyEvent *event)
{
  KeySym sym;
  Modifiers ret_mod;

  XmTranslateKey(event->display, event->keycode, event->state,
		 &ret_mod, &sym);

  RefArray<Controller> controllers;
  RefArray<SensitiveRec> selection;

  for(unsigned int i=0; i<contents.getSize(); i++) {
    if(contents[i]->getModel()->isSelected()) {
      selection.add(contents[i]);
    }
  }

  for(unsigned int i=0; i<selection.getSize(); i++) {
    controllers.add(getController(selection[i]));
  } 
  
  if(controllers.getSize()) {
    if( !controllers[0]->processKey(event->state, 
				    XKeysymToString(sym), controllers) ) {
      if(sym == osfXK_Menu) {
	controllers[0]->popupMenu(box, 0, 0, controllers);
	return;
      } else if(sym == osfXK_Right) {
	for(unsigned int i=0; i<contents.getSize(); i++) {
	  if(contents[i]->getModel()->isSelected()) {
	    contents[i]->traverseRight();
	    break;
	  }
	}
      } else if(sym == osfXK_Left) {
	for(unsigned int i=0; i<contents.getSize(); i++) {
	  if(contents[i]->getModel()->isSelected()) {
	    contents[i]->traverseLeft();
	    break;
	  }
	}
      } else if(sym == osfXK_Up) {
	for(unsigned int i=0; i<contents.getSize(); i++) {
	  if(contents[i]->getModel()->isSelected()) {
	    contents[i]->traverseUp();
	    break;
	  }
	}
      } else if(sym == osfXK_Down) {
	for(unsigned int i=0; i<contents.getSize(); i++) {
	  if(contents[i]->getModel()->isSelected()) {
	    contents[i]->traverseDown();
	    break;
	  }
	}
      } 
    }
  }
  while(controllers.getSize())
    controllers[0].Delete();
}

// --------------------------------------
//           key_pressed()
// --------------------------------------

void SensitiveContainer::key_pressed(Widget, XtPointer client, 
				     XEvent *event, Boolean *)
{
  if(event->type == KeyPress) {
    XKeyEvent *keyEvent = (XKeyEvent*)event;
    SensitiveContainer *self = (SensitiveContainer*)client;
    self->processKey(keyEvent);
  }
}


// --------------------------------------
//          focus_in()
// --------------------------------------

void SensitiveContainer::focus_in(Widget, XtPointer client, 
				  XEvent *e, Boolean *)
{
  SensitiveContainer *self = (SensitiveContainer*)client;

  if(e->type == FocusIn) {
    self->highlightParent = TRUE;
    self->drawHighlightParent();
#if(0)
    if(self->highlighted.isNil()) {
      if(self->contents.getSize()) {
	Iconable *ic = self->contents[0]->getModel();
	self->setHighlighted(ic);
      }
    } else {
      self->highlighted->highlight(TRUE);
      self->highlighted->expose();
    }
#endif
    XmProcessTraversal(self->box, XmTRAVERSE_CURRENT);
  }
}

// --------------------------------------
//           focus_out()
// --------------------------------------

void SensitiveContainer::focus_out(Widget, XtPointer client, 
				   XEvent *e, Boolean *)
{
  SensitiveContainer *self = (SensitiveContainer*)client;

  if(e->type == FocusOut) {
    self->highlightParent = FALSE;
    self->drawHighlightParent();
#if(0)
    if(!self->highlighted.isNil()) {
      self->highlighted->highlight(FALSE);
      self->highlighted->expose();
    }
#endif
  }
}

// --------------------------------------
//       expose_clip_window()
// --------------------------------------

void SensitiveContainer::expose_clip_window(Widget, XtPointer client, 
					    XEvent *, Boolean *)
{
  SensitiveContainer *self = (SensitiveContainer*)client;
  self->drawHighlightParent();
}

// --------------------------------------
//      drawHighlightParent()
// --------------------------------------

void SensitiveContainer::drawHighlightParent()
{
  GC gc;
  Widget wg;
  Dimension width, height;
  Dimension shadowThickness;
  Position x, y;
  XGCValues gcValues;
  Pixel parentBG, highlightColor;

  wg = XtParent(box);
  if(highlightParent) {
    gc = fgGC;
  } else {
    gc = bgGC;
  }

  XtVaGetValues(wg, 
		XmNx, &x, XmNy, &y,
		XmNwidth, &width, XmNheight, &height, 
		NULL);
  XtVaGetValues(scrolledWindow,
		XmNshadowThickness, &shadowThickness,
		XmNbackground, &parentBG,
		XmNhighlightColor, &highlightColor,
		NULL);

  XGetGCValues(XtDisplay(wg), gc, 
	       GCLineWidth | GCLineStyle | GCCapStyle | GCJoinStyle |
	       GCForeground,
	       &gcValues);
  if(!highlightParent) {
    XSetForeground(XtDisplay(wg), gc, parentBG);
  } else {
    XSetForeground(XtDisplay(wg), gc, highlightColor);
  }
  XSetLineAttributes(XtDisplay(wg), gc, 2, LineSolid, CapRound, JoinMiter);
  XDrawRectangle(XtDisplay(scrolledWindow), 
		 XtWindow(scrolledWindow), gc,
		 x - 1 - shadowThickness, 
		 y - 1 - shadowThickness, 
		 width + 2*(shadowThickness+1), 
		 height + 2*(shadowThickness+1));
  XChangeGC(XtDisplay(wg), gc, 
	    GCLineWidth | GCLineStyle | GCCapStyle | GCJoinStyle |
	    GCForeground,
	    &gcValues);
		 
}

// --------------------------------------
//           mouse_move()
// --------------------------------------

void SensitiveContainer::mouse_move(Widget, XtPointer client, XEvent *event, Boolean *)
{
  SensitiveContainer *self = (SensitiveContainer*)client;
  XMotionEvent *mEvent = (XMotionEvent*)event;
  self->doQuickHelp(mEvent->x,mEvent->y);
}

// --------------------------------------
//            setBubbleHelp()
// --------------------------------------

void 
SensitiveContainer::setBubbleHelp(Boolean b)
{
  if(b && bubble == NULL) {
#ifndef CDE_WIDGETS    
    // When using CDE bubble crashes
    bubble = XtVaCreateWidget("bubble", xlBubbleWidgetClass, box,
			      XmNuseEvents, FALSE,
			      NULL);
#endif
  } else if(!b && bubble != NULL) {
    XtDestroyWidget(bubble);
  }
}

// --------------------------------------
//            doQuickHelp()
// --------------------------------------

void SensitiveContainer::doQuickHelp(Position x, Position y)
{
  SensitiveRec *found = NULL;

  if(quickHelpLabel || bubble) {
    for(unsigned int i=0; i<contents.getSize(); i++)
      if(contents[i]->isIn(x,y)) {
	found = contents[i];
	break;
      }
    if(found) {
      if(found != currentQuickHelpObject) {
	XmString xmString = 
	  XmStringCreateLtoR(found->getModel()->getDescription(),
			     XmSTRING_DEFAULT_CHARSET);

	if(quickHelpLabel)
	  XtVaSetValues(quickHelpLabel, XmNlabelString, xmString, NULL);
	if(bubble) {
	  XlBubbleSimLeave(bubble);
	  XlBubbleSimEnter(bubble, found->getX(), found->getY(),
			   found->getWidth(), found->getHeight(),
			   xmString);
	}
	XmStringFree(xmString);
	currentQuickHelpObject = found;
      }
    } else {
      static XmString emptyString = NULL;
      if(emptyString == NULL)
	emptyString = XmStringCreateLtoR(" ", XmSTRING_DEFAULT_CHARSET);

      if(quickHelpLabel)
	XtVaSetValues(quickHelpLabel, XmNlabelString, emptyString, NULL);
      if(bubble)
	XlBubbleSimLeave(bubble);

      currentQuickHelpObject = NULL;
    }
  }
}


// --------------------------------------
//           configureEvent() 
// --------------------------------------

void SensitiveContainer::configureEvent(Widget,XtPointer self,XEvent* event,Boolean*)
{
  if( event->type==ConfigureNotify || event->type==MapNotify ) {
    ((SensitiveContainer*)self)->queryViewport();
    ((SensitiveContainer*)self)->configure();
  }
}

// --------------------------------------
//           scrollCB()
// --------------------------------------
void SensitiveContainer::scrollCB(Widget, XtPointer client, XtPointer)
{
  SensitiveContainer *self = (SensitiveContainer*)client;
  self->queryViewport();
}

// --------------------------------------
//           queryViewport() 
// --------------------------------------
void SensitiveContainer::queryViewport()
{
  Dimension viewportH, viewportW;
  Position viewportX, viewportY;

  Widget w;

  XtVaGetValues(scrolledWindow,XmNclipWindow,&w,NULL);
  if(w == NULL)
    w = scrolledWindow;

  XtVaGetValues(w, 
		XmNwidth, &viewportW,
		XmNheight, &viewportH,
		NULL);
  viewportRec.setDimension(viewportW, viewportH);

  XtVaGetValues(box, XmNx, &viewportX, XmNy, &viewportY, NULL);
  viewportRec.setPosition(-viewportX, -viewportY);
}

// --------------------------------------
//           expose()   
// --------------------------------------
void SensitiveContainer::expose(Widget, XtPointer this_class,
				XEvent *event, Boolean * )
{
  SensitiveContainer *self = (SensitiveContainer*)this_class;
  XExposeEvent *exevent = (XExposeEvent*)event;
  
//  Rec exposed(exevent->x, exevent->y, exevent->width, exevent->height);

  if(exevent->count == 0)
    for(unsigned int i=0; i<self->contents.getSize(); i++)
//      if(self->contents[i]->isInRecPart(exposed))
	self->contents[i]->expose();
}

// --------------------------------------
//           button_press
// --------------------------------------
void SensitiveContainer::button_press(Widget, XtPointer this_class,
			   XEvent *event, Boolean * )
{
  SensitiveContainer *self = (SensitiveContainer*)this_class;
  Window retRoot, retChild;
  int retRootX, retRootY, retX, retY;
  unsigned int retKey;

  XmProcessTraversal(self->box, XmTRAVERSE_CURRENT);

  XQueryPointer( XtDisplay(self->box), XtWindow(self->box), 
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&retX, &retY,
		&retKey );
  self->button( event, retX, retY, retKey );

}
  
// ------------------------------------
//         makePopup()
// ------------------------------------

void SensitiveContainer::makePopup(SensitiveRec *found, Position x,Position y)
{
  static RefArray<Controller> all;
  while(all.getSize())
    all[0].Delete();
  if(found->getModel()->isSelected()) {
    for(unsigned int i=0; i<contents.getSize(); i++)
      if(contents[i]->getModel()->isSelected()) {
	all.add(getController(contents[i]));
      }
  } else
    all.add(getController(found));
  all[0]->popupMenu(box, x, y, all);
}


// ------------------------------------
//         getController()
// ------------------------------------

Controller *SensitiveContainer::getController(SensitiveRec *v)
{
  return new Controller(v->getModel(),v);
}

// --------------------------------------
//           rubberDraw()
// --------------------------------------

void SensitiveContainer::rubberDraw(Position x, Position y, Boolean newValues)
{
  XGCValues gcValues;
  RefArray<SensitiveRec> oldSelection;
  Widget clipWindow;
  int transX, transY;
  Dimension width, height;
  Window dummy;

  clipWindow = XtParent(box);
  XtVaGetValues(clipWindow, XmNwidth, &width, XmNheight, &height, NULL);

  // if newValues is false, we make rectangle visible
  // else we, hide the rectangle
  // rectangle is drawn on clip window

  XGetGCValues(XtDisplay(box), fgGC, 
	       GCFunction | GCForeground | GCSubwindowMode, &gcValues );
  XSetFunction(XtDisplay(box), fgGC, GXxor);
  XSetForeground(XtDisplay(box), fgGC, 1);
  XSetSubwindowMode(XtDisplay(box), fgGC, IncludeInferiors);
  XTranslateCoordinates(XtDisplay(box), 
			XtWindow(box), XtWindow(clipWindow),
			rubberBand.getX(), rubberBand.getY(),
			&transX, &transY, &dummy);
  XDrawRectangle(XtDisplay(box), XtWindow(clipWindow), fgGC, 
		 transX, transY,
		 rubberBand.getWidth(), rubberBand.getHeight());
  XChangeGC(XtDisplay(box), fgGC, 
	    GCFunction | GCForeground | GCSubwindowMode, &gcValues );

  // now we determine whether to scroll or not
  // but only if new values
  
  if(newValues) {
    int scrollHor = 0, scrollVer = 0;
    Position curX, curY;
    Dimension boxWidth, boxHeight;
    Widget hs, vs;

    XtVaGetValues(box, 
		  XmNx, &curX, XmNy, &curY, 
		  XmNwidth, &boxWidth, XmNheight, &boxHeight,
		  NULL);

    XTranslateCoordinates(XtDisplay(box), 
			  XtWindow(box), XtWindow(clipWindow),
			  x, y, &transX, &transY, &dummy);
    if(transX < 0)
      scrollHor = RB_SCROLL_VALUE;
    else if(transX > width && width < boxWidth)
      scrollHor = -RB_SCROLL_VALUE;
    if(transY < 0)
      scrollVer = RB_SCROLL_VALUE;
    else if(transY > height && height < boxHeight)
      scrollVer = -RB_SCROLL_VALUE;
    
    XtVaGetValues(scrolledWindow, 
		  XmNhorizontalScrollBar, &hs,
		  XmNverticalScrollBar, &vs,
		  NULL);

    if(curX+scrollHor > 0 && scrollHor != 0)
      scrollHor = -curX;
    if(curY+scrollVer > 0 && scrollVer != 0)
      scrollVer = -curY;
    if(boxWidth-width+curX+scrollHor < 0 && scrollHor != 0)
      scrollHor = -(boxWidth-width+curX);
    if(boxHeight-height+curY+scrollVer < 0 && scrollVer != 0)
      scrollVer = -(boxHeight-height+curY);

    if(scrollHor != 0)
      XmScrollBarSetValues(hs, -(curX+scrollHor), 0, 0, 0, TRUE);
    if(scrollVer != 0)
      XmScrollBarSetValues(vs, -(curY+scrollVer), 0, 0, 0, TRUE);
    
    if((scrollHor != 0 || scrollVer != 0) && !timerOn) {
      timerId = XtAppAddTimeOut(XtWidgetToApplicationContext(box),
				100, timerCallback, this);
      timerOn = TRUE;
    }
  }

  if(newValues) {
    if(beginX > x && beginY > y) {
      rubberBand.setPosition(x,y);
      rubberBand.setDimension(beginX-x, beginY-y);
    } else if(beginX > x && beginY < y) {
      rubberBand.setPosition(x, beginY);
      rubberBand.setDimension(beginX-x, y-beginY);
    } else if(beginX < x && beginY < y) {
      rubberBand.setPosition(beginX, beginY);
      rubberBand.setDimension(x-beginX, y-beginY);
    } else if(beginX < x && beginY > y) {
      rubberBand.setPosition(beginX, y);
      rubberBand.setDimension(x-beginX, beginY-y);
    }
    oldSelection = inRubberBand;
    inRubberBand.empty();
    for(unsigned int i=0; i<contents.getSize(); i++) {
      if(contents[i]->isInRec(rubberBand) && contents[i]->getVisible()) {
	inRubberBand.add(contents[i]);
	oldSelection.remove(contents[i]);    // successful or not
      }
    }
    for(unsigned int i=0; i<oldSelection.getSize(); i++)
      oldSelection[i]->setTmpSelect(FALSE);
    for(unsigned int i=0; i<inRubberBand.getSize(); i++)
      inRubberBand[i]->setTmpSelect(TRUE);
    for(unsigned int i=0; i<contents.getSize(); i++)
      contents[i]->expose();

    XGetGCValues(XtDisplay(box), fgGC, 
		 GCFunction | GCForeground | GCSubwindowMode, &gcValues );
    XSetFunction(XtDisplay(box), fgGC, GXxor);
    XSetForeground(XtDisplay(box), fgGC, 1);
    XSetSubwindowMode(XtDisplay(box), fgGC, IncludeInferiors);
    XTranslateCoordinates(XtDisplay(box), XtWindow(box), XtWindow(clipWindow),
			  rubberBand.getX(), rubberBand.getY(),
			  &transX, &transY, &dummy);
    XDrawRectangle(XtDisplay(box), XtWindow(clipWindow), fgGC, 
		   transX, transY,
		   rubberBand.getWidth(), rubberBand.getHeight());
    XChangeGC(XtDisplay(box), fgGC, 
	      GCFunction | GCForeground | GCSubwindowMode, &gcValues );
  }
}

// --------------------------------------
//           timerCallback
// --------------------------------------
void SensitiveContainer::timerCallback(XtPointer this_class, XtIntervalId *)
{
  SensitiveContainer *self = (SensitiveContainer*)this_class;
  
  Window retRoot, retChild;
  int retRootX, retRootY, x, y;
  unsigned int key;
  XQueryPointer( XtDisplay(self->box), XtWindow(self->box), 
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&x, &y,
		&key );

  self->timerOn = FALSE;
  if(self->rubberBandMode && key & Button1Mask) {
    self->rubberDraw(x,y,TRUE);
  } 
}

// --------------------------------------
//           button_motion
// --------------------------------------
void SensitiveContainer::button_motion(Widget , XtPointer this_class,
				       XEvent *, Boolean * )
{
  SensitiveContainer *self = (SensitiveContainer*)this_class;

  SensitiveRec *found=NULL;
  Window retRoot, retChild;
  int retRootX, retRootY, x, y;
  unsigned int key;
  XQueryPointer( XtDisplay(self->box), XtWindow(self->box), 
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&x, &y,
		&key );

  if(self->rubberBandMode && key & Button1Mask) {
    self->rubberDraw(x,y,TRUE);
  } else {
    for(unsigned int i=0; i<self->contents.getSize(); i++)
      if(self->contents[i]->isIn(x,y) && self->contents[i]->getVisible()) {
	found = self->contents[i];;
	break;
      }
    if(found ) {
      if( key & Button1Mask ) {  // Select
	if(found->getPressed() == FALSE) {
	  Boolean f = FALSE;
	  for(unsigned int i=0; i<self->pressed.getSize(); i++) {
	    if(self->pressed[i] != found)
	      self->pressed[i]->setPressed(FALSE);
	    else
	      f = TRUE;
	  }
	  self->pressed.empty();
	  self->pressed.add(found);
	  if(!f)
	    found->setPressed(TRUE);
	  if( !found->getModel()->isSelected() )
	    found->select(TRUE, x, y);    

	  XFlush(XtDisplay(self->box));
	}
      }
    } else {
      for(unsigned int i=0; i<self->pressed.getSize(); i++) {
	self->pressed[i]->setPressed(FALSE);
      }
      self->pressed.empty();
    }
  }
}
// --------------------------------------
//           button_release
// --------------------------------------
void SensitiveContainer::button_release(Widget , XtPointer this_class,
					XEvent *, Boolean * )
{
  SensitiveContainer *self = (SensitiveContainer*)this_class;

  Window retRoot, retChild;
  int retRootX, retRootY, x, y;
  unsigned int key;
  XQueryPointer( XtDisplay(self->box), XtWindow(self->box), 
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&x, &y,
		&key );

  if(self->timerOn) {
    XtRemoveTimeOut(self->timerId);
    self->timerOn = FALSE;
  }

  while(self->pressed.getSize() > 0) {
    self->pressed[0]->setPressed(FALSE);
    self->pressed.remove(self->pressed[0]);
  }
  self->pressed.empty();

  if(self->rubberBandMode) {
    Boolean extendSelection, first;

    self->rubberDraw(0,0,FALSE);

    extendSelection = (key & ControlMask);
    first = TRUE;
    for(unsigned int i=0; i<self->inRubberBand.getSize(); i++) {
      Boolean multi = (extendSelection && first) || !first;
      self->inRubberBand[i]->setTmpSelect(FALSE);
      if(first) {
	first = FALSE;
	if(self->inRubberBand[i]->getModel()->isSelected()) {
	  self->inRubberBand[i]->getModel()->select(TRUE);
	}
      }
      if( !self->inRubberBand[i]->getModel()->isSelected() ) {
	self->inRubberBand[i]->getModel()->select(multi);
      }
    }
    self->inRubberBand.empty();
  }
  self->rubberBandMode = FALSE;
}
  
// --------------------------------------
//           button()   
// --------------------------------------
void SensitiveContainer::button( XEvent *event, Position x, Position y, unsigned int key )
{
  static Time lastTime = 0;
  Boolean doubleClick = FALSE;
  Time thisTime = ((XButtonEvent*)event)->time;
  if(thisTime - lastTime < 300)
    doubleClick = TRUE;
  
  if(bubble) {                   // hide the bubble when button is pressed
    XlBubbleSimLeave(bubble);
  }

  SensitiveRec *found=NULL;
  for(unsigned int i=0; i<contents.getSize(); i++)
    if(contents[i]->isIn(x,y) && contents[i]->getVisible()) {
      found = contents[i];;
      break;
    }
  if(found ) {
    if( key & Button1Mask ) {  // Select
#if(0)
      setHighlighted(found->getModel());
#endif
      lastTime = thisTime;                    // double click == default action
      if(doubleClick) {

	RefArray<Controller> controllers;     // query all controllers

	if(found->getModel()->isSelected()) {   // for all selected objects in
	                                        // this container
	  for(unsigned int i=0; i<contents.getSize(); i++) {
	    if(contents[i]->getModel()->isSelected())
	      controllers.add(getController(contents[i]));
	  }
	} else {
	  controllers.add(getController(found));
	}
	LicView::setWaitCursor(TRUE);
	for(unsigned int i=0; i<controllers.getSize(); i++) 
	  controllers[i]->defaultAction();    // call default action
	LicView::setWaitCursor(FALSE);

	while(controllers.getSize() != 0)
	  controllers[0].Delete();
	return;
      }

      if((key & Mod1Mask)) {
	edit(found, x, y, TRUE);
	return;
      } else {
	if(!inEditMode.isNil())
	  edit(inEditMode, x, y, FALSE);
      }
      rubberBandMode = FALSE;
      if(found->getPressed() == FALSE) {
	pressed.add(found);
	found->setPressed(TRUE);
	XFlush(XtDisplay(box));
	if( key & ControlMask )
	  found->select(True, x, y);       // Multiselect
	else
	  found->select(False, x, y);      // Singleselect
      }
    } else {
      if( key & Button2Mask ) // Move
	found->move( box, event, x, y, dragOperations );
      else
	if( key & Button3Mask )  // Popupmenu
	  makePopup(found, x, y);
    }
  } else {
    if( key & Button1Mask ) {  // Select
      rubberBandMode = TRUE;
      beginX = x;
      beginY = y;
      rubberBand.setPosition(x,y);
      rubberBand.setDimension(0,0);
      inRubberBand.empty();
      rubberDraw(x,y,FALSE);
    }
  }
}


// --------------------------------------
//           edit()   
// --------------------------------------
void SensitiveContainer::edit(SensitiveRec *toEdit, 
			      Position x, Position y, Boolean b)
{
  if(!inEditMode.isNil() && b)
    inEditMode->edit(x, y, !b);     // disable edit
  toEdit->edit(x, y, b);
  if(b)
    inEditMode = toEdit;
  else
    inEditMode = NULL;
}

// --------------------------------------
//           update()   
// --------------------------------------
void SensitiveContainer::update( unsigned long  )
{
}

// --------------------------------------
//           createGCs()
// --------------------------------------

void SensitiveContainer::createGCs()
{
  Pixel fg, bg;
  XGCValues gcValues;
  XmFontContext context;
  XmFontList fl;
  XFontStruct *font;
  Font fid;
  XmStringCharSet charset;

  fl = NULL;
  font = NULL;
  XtVaGetValues(box, 
		XmNbackground, &bg, 
		XmNforeground, &fg, 
		NULL);

  {
    XtResource resources[] = {
      { "fontList", "FontList", XmRFontList, sizeof(XmFontList),
	0, XtRImmediate, NULL }
    };

    XtGetSubresources(box, &fl, NULL, NULL, resources, XtNumber(resources),
		      NULL, 0);
  }

  if(fl == NULL) {
    // its an ugly thing, but we call a private Xm function (XmP.h)

#if XmVERSION < 2
    fl = _XmGetDefaultFontList(box, XmLABEL_FONTLIST);
#else
    fl = XmeGetDefaultRenderTable(box, XmLABEL_FONTLIST);
#endif
  }

  if(fl)
    fontList = XmFontListCopy(fl);
  else
    fontList = NULL;

  if(fl) {
    XmFontListInitFontContext(&context, fl);
    while(XmFontListGetNextFont(context, &charset, &font)) {
      if(!strcmp(charset,XmSFONTLIST_DEFAULT_TAG_STRING)) {
	XtFree(charset);
	break;
      }
      XtFree(charset);
      font = NULL;
    }
    XmFontListFreeFontContext(context);
  }

  if(font) {
    fid = font->fid;
  } else {
    fid = XLoadFont( XtDisplay(box), "fixed" );
  }
  if(!fontList)
    fontList = XmFontListCreate(XQueryFont(XtDisplay(box), fid), 
				XmSTRING_DEFAULT_CHARSET);

  gcValues.foreground = fg;
  gcValues.background = bg;
  gcValues.font = fid;
  fgGC = XCreateGC(XtDisplay(box), 
		   XRootWindowOfScreen(XtScreen(box)),
		   GCBackground | GCForeground | GCFont,
		   &gcValues );
  XFlushGC(XtDisplay(box), fgGC );

  gcValues.foreground = bg;
  gcValues.background = bg;
  gcValues.font = fid;
  bgGC = XCreateGC(XtDisplay(box), 
		   XRootWindowOfScreen(XtScreen(box)),
		   GCBackground | GCForeground | GCFont,
		   &gcValues );
  XFlushGC(XtDisplay(box), bgGC );
}


// -----------------------------
// getSelectedObjects()
// -----------------------------

void SensitiveContainer::getSelectedObjects(RefArray<Iconable> &selection)
{
  for(unsigned int i=0; i<contents.getSize(); i++)
    if(contents[i]->getModel()->isSelected())
      selection.add(contents[i]->getModel());
}

// -----------------------------
// getSelectedControllers()
// -----------------------------

void SensitiveContainer::getSelectedControllers(RefArray<Controller> 
						&controllers)
{
  for(unsigned int i=0; i<contents.getSize(); i++) {
    if(contents[i]->getModel()->isSelected() && contents[i]->getVisible())
      controllers.add(getController(contents[i]));
  }  
}

// -----------------------------
// setHighlighted()
// -----------------------------

void SensitiveContainer::setHighlighted(Iconable *m)
{
  SensitiveRec *toHighlight = NULL;
  if(m == NULL) {
    if(!highlighted.isNil())
      highlighted->highlight(FALSE);
    highlighted = NULL;
  }
  for(unsigned int i=0; i<contents.getSize(); i++) {
    if(contents[i]->getModel() == m) {
      toHighlight = contents[i];
      break;
    }
  }
  if(toHighlight) {
    if(!highlighted.isNil())
      highlighted->highlight(FALSE);
    highlighted = toHighlight;
    highlighted->highlight(TRUE);
    scrollToMakeVisible(highlighted->getModel());
  }
}

// ----------------------------
//  queryInsertBefore()
// ----------------------------

SensitiveRec *SensitiveContainer::queryInsertBefore(Position x, Position y)
{
  SensitiveRec *v;
  
  for(unsigned int i=0; i<contents.getSize(); i++) {
    v = contents[i];
    if(v->isBefore(x,y)) {
      return v;
    }
  }
  return NULL;
}


// ----------------------------
//  queryAsChild()
// ----------------------------

SensitiveRec *SensitiveContainer::queryAsChild(Position x, Position y)
{
  SensitiveRec *v;
  
  for(unsigned int i=0; i<contents.getSize(); i++) {
    v = contents[i];
    if(v->isIn(x,y)) {
      return v;
    }
  }
  return NULL;
}

// --------------------------------
// scrollToMakeVisible()
// --------------------------------

void SensitiveContainer::scrollToMakeVisible(Iconable *model)
{
  SensitiveRec *found = NULL;
  Rec testRec = viewportRec;
  Widget hs, vs;

  for(unsigned int i=0; i<contents.getSize(); i++) {
    if(contents[i]->getModel() == model) {
      found = contents[i];
      break;
    }
  }
  if(found && found->getVisible()) {
    Position dx, dy, x, y;
    Dimension width, height;

    testRec.setDimension(testRec.getWidth()-found->getWidth(),
			 testRec.getHeight()-found->getHeight());
    if(testRec.isIn(found->getX(), found->getY()))    // dont have to scroll
      return;
    dx = dy = 0;
    if(found->getX() < viewportRec.getX())
      dx = viewportRec.getX() - found->getX();

    if(found->getY() < viewportRec.getY())
      dy = viewportRec.getY() - found->getY();

    if(found->getX()+found->getWidth() > 
       viewportRec.getX()+viewportRec.getWidth())
      dx = viewportRec.getX()+viewportRec.getWidth() -
	found->getX() - found->getWidth();

    if(found->getY()+found->getHeight() > 
       viewportRec.getY()+viewportRec.getHeight())
      dy = viewportRec.getY()+viewportRec.getHeight() -
	found->getY() - found->getHeight();

#if(0)
    if(found->getX() > viewportRec.getX() + viewportRec.getWidth()) {
      dx += viewportRec.getWidth() - found->getWidth();
    }
    if(found->getY() > viewportRec.getY() + viewportRec.getHeight()) {
      dy += viewportRec.getHeight() - found->getHeight();
    }
#endif
    XtVaGetValues(box, 
		  XmNx, &x,
		  XmNy, &y,
		  XmNwidth, &width,
		  XmNheight, &height,
		  NULL);
    XtVaGetValues(scrolledWindow, 
		  XmNhorizontalScrollBar, &hs,
		  XmNverticalScrollBar, &vs,
		  NULL);
    if( (width-viewportRec.getWidth() > -(x+dx)) && (0 <= -(x+dx)) )
      XmScrollBarSetValues(hs, -(x+dx), 0, 0, 0, TRUE);
    if( (height-viewportRec.getHeight() > -(y+dy)) && (0 <= -(y+dy)) )
      XmScrollBarSetValues(vs, -(y+dy), 0, 0, 0, TRUE);
  }
}

// ------------------------------
// createXmString()
// ------------------------------

XmString SensitiveContainer::createXmString(Iconable *m)
{
  XmString xms;
  xms = XmStringCreate(m->getName(), XmFONTLIST_DEFAULT_TAG);
  return xms;
}

// ------------------------------
// queryNextContent()
// ------------------------------

SensitiveRec *
SensitiveContainer::queryNextContent(Position x, Position y, 
				     Position dx, Position dy)
{
  Position mx, my;
  Position ax, ay, currentAX, currentAY;
  double diff, currentDiff;
  SensitiveRec *current = NULL;

  for(unsigned int i=0; i<contents.getSize(); i++) {
    if(!contents[i]->getVisible())
      continue;
    contents[i]->getMiddle(mx, my);
    if(mx == x && my == y)
      continue;
    diff = sqrt((mx - x) * (mx - x) + (my - y) * (my - y));
    ax = (mx - x) * dx;
    ay = (my - y) * dy;
    if(ax < 0 || ay < 0 || (ax == 0 && ay == 0))
      continue;
    if(current) {
      if(currentAX >= ax || currentAY >= ay) {
	if(currentDiff > diff) {
	  current = contents[i];
	  currentDiff = diff;
	  currentAX = ax;
	  currentAY = ay;
	}
      }
    } else {
      current = contents[i];
      currentDiff = diff;
      currentAX = ax;
      currentAY = ay;
    }
  }
  return current;
}

// #################################################################
//
//                          TextRecView
//
// #################################################################
TextRecView::TextRecView( Iconable *am, SensitiveRec *p )
: RecView(am), m(am) 
{ 
  parentObject = p;
  container = parentObject->getContainer();
  parent = container->getWidget();
  fgGC = container->getForegroundGC();
  bgGC = container->getBackgroundGC();
  fontList = container->getFontList();

  nameChanged = TRUE;
  margin=3; 
  textWidget = NULL;
  editable = FALSE;
  xmString = NULL;
}

TextRecView::~TextRecView()
{
  if(xmString)
    XmStringFree(xmString);
  if(textWidget)
    XtDestroyWidget(textWidget);
}

// ---------------------------------
//        getWidth()
// ---------------------------------
Dimension TextRecView::getWidth()
{
  if(nameChanged) {
    if(xmString)
      XmStringFree(xmString);
    xmString = container->createXmString(m);
    queryTextExtend();
    nameChanged = FALSE;
  }
  if(editable && textWidget) {
    Dimension w;
    XtVaGetValues(textWidget, XmNwidth, &w, NULL);
    return w;
  } else
    return width;
}

// ---------------------------------
//        getHeight()
// ---------------------------------
Dimension TextRecView::getHeight()
{
  if(nameChanged) {
    if(xmString)
      XmStringFree(xmString);
    xmString = container->createXmString(m);
    queryTextExtend();
    nameChanged = FALSE;
  }
  if(editable && textWidget) {
    Dimension h;
    XtVaGetValues(textWidget, XmNheight, &h, NULL);
    return h;
  } else
    return height;
}


// ---------------------------------
//        setPosition()
// ---------------------------------
void TextRecView::setPosition(Position x, Position y)
{
  if(editable && textWidget)
    XtVaSetValues(textWidget, XmNx, x, XmNy, y, NULL);
  RecView::setPosition(x,y);
}

// ---------------------------------
//        draw()
// ---------------------------------

void TextRecView::draw(Boolean asSelected) {

  if(!m->getName())               // no name -> nothing to do
    return;

  if(nameChanged) {               // if name changed -> query new size
    if(xmString)
      XmStringFree(xmString);
    xmString = container->createXmString(m);
    queryTextExtend();
    nameChanged = FALSE;
  }

  if(XtWindow(parent) == None)   // no window -> nothing to do
    return;

  if(editable)
    return;

  if( m->isSelected() || asSelected ) {
    XFillRectangle(XtDisplay(parent),XtWindow(parent), fgGC,
		   x, y, width, height);
    XmStringDraw(XtDisplay(parent), XtWindow(parent), fontList,
		 xmString, bgGC, x, y+margin,
		 width, XmALIGNMENT_CENTER, XmSTRING_DIRECTION_DEFAULT, NULL);

  } else {
    XFillRectangle(XtDisplay(parent),XtWindow(parent), bgGC,
		   x, y, width, height);
    XmStringDraw(XtDisplay(parent), XtWindow(parent), fontList,
		 xmString, fgGC, x, y+margin,
		 width, XmALIGNMENT_CENTER, XmSTRING_DIRECTION_DEFAULT, NULL);
  }
}


// -------------------------------------
//        update()
// ------------------------------------- 

void TextRecView::update( unsigned long flags ) {
  if( flags & NAME_CHANGED ) {
    XmStringFree(xmString);
    xmString = container->createXmString(m);
    queryTextExtend();
    parentObject->configure();
  }
  if( flags & SELECTION_CHANGED ) {
    parentObject->expose();
  }
}


// -------------------------------------
//        createTextWidget()
// ------------------------------------- 

Widget TextRecView::createTextWidget()
{
  Widget wg;

  wg = XtVaCreateManagedWidget("TextEdit", xmTextWidgetClass, parent, 
			       XmNx, x,
			       XmNy, y,
	//			XmNeditMode, XmMULTI_LINE_EDIT,
			       XmNmappedWhenManaged, FALSE,
			       NULL);
  XtAddCallback(wg, XmNactivateCallback, textActivateCallback, this);
  XtAddEventHandler(wg, KeyPressMask,  False, textKeyPressed, this);

  return wg;
}


// -------------------------------------
//        textActivateCallback()
// ------------------------------------- 

void TextRecView::textActivateCallback(Widget, XtPointer client, XtPointer)
{
  TextRecView *self = (TextRecView*)client;
  self->container->edit(self->parentObject, 0, 0, FALSE);
}


// -------------------------------------
//        textKeyPressed()
// ------------------------------------- 

void TextRecView::textKeyPressed(Widget, XtPointer client, 
				 XEvent *event, Boolean *)
{
  KeySym sym;
  Modifiers ret_mod;
  XKeyEvent *kEvent = (XKeyEvent*)event;

  XmTranslateKey(kEvent->display, kEvent->keycode, kEvent->state,
		 &ret_mod, &sym);
  if(sym == osfXK_Cancel) {
    TextRecView *self = (TextRecView*)client;
    XmTextSetString(self->textWidget, self->m->getName());   // put it back
    self->container->edit(self->parentObject, 0, 0, FALSE);
  }
}


// -------------------------------------
//        setEditable()
// ------------------------------------- 

void TextRecView::setEditable(Boolean mode)
{
  if(mode != editable && m->nameChangeable()) {
    editable = mode;
    if(editable) {
      Cardinal cols, rows;

      if(textWidget == 0) {
	textWidget = createTextWidget();
      }
      if(m->getName()) {
	cols = strlen(m->getName());
	if(cols == 0)
	  cols = 10;
	rows = 1;
	for(char *ptr = m->getName(); ptr; rows++)
	  ptr = strchr(ptr, '\n');

	XtVaSetValues(textWidget,
		      XmNcolumns, cols,
		      XmNrows, rows,
		      XmNx, x,
		      XmNy, y,
		      NULL);
	XmTextSetString(textWidget, m->getName());
      }
      XtMapWidget(textWidget);
      parentObject->configure();
      XmProcessTraversal(textWidget, XmTRAVERSE_CURRENT);
      XmTextSetSelection(textWidget, 0, strlen(m->getName()), CurrentTime);
    } else {
      if(textWidget != NULL) {
	char *str = XmTextGetString(textWidget);
	if(m->setName(str))
	  m->changed(NAME_CHANGED);
	else {
	  XBell(XtDisplay(textWidget), 100);
	  parentObject->configure();
	}
	XtFree(str);
	XtDestroyWidget(textWidget);
	textWidget = 0;
	XmProcessTraversal(parent, XmTRAVERSE_CURRENT);
      }
    }
  }
}

// -------------------------------------
//        queryTextExtend()
// ------------------------------------- 

void TextRecView::queryTextExtend()
{
#if(0)
  XGCValues gcValues;
  int direction, ascent, descent;
  XCharStruct charStruct;

  if( m->getName() ) {
    XGetGCValues(XtDisplay(parent), fgGC, GCFont, &gcValues );
    XQueryTextExtents(XtDisplay(parent), gcValues.font, 
		      m->getName(), strlen(m->getName()),
		      &direction, &ascent, &descent, &charStruct );
    width = charStruct.lbearing+charStruct.rbearing+2*margin;
    XQueryTextExtents(XtDisplay(parent), gcValues.font, 
		      "W", 1,
		      &direction, &ascent, &descent, &charStruct );
    height = charStruct.ascent+charStruct.descent+2*margin;

  }
#endif
  if(xmString) {
    XmStringExtent(fontList, xmString, &width, &height);
    width += 2*margin;
    height += 2*margin;
  }
}


/* #############################################################
                      PixmapRecView
   ############################################################# */


// -------------------------------
//   PixmapRecView() - Konstuktor
// -------------------------------

PixmapRecView::PixmapRecView( Iconable *am, SensitiveRec *p, Dimension iconHeight)
: RecView(am), m(am)
{ 
  parentObject = p;
  container = parentObject->getContainer();
  parent = container->getWidget();
  fgGC = container->getForegroundGC();
  bgGC = container->getBackgroundGC();

  this->iconHeight = iconHeight;

  readPixmap();
}

// -------------------------------
//   ~PixmapRecView()
// -------------------------------

PixmapRecView::~PixmapRecView() {
  if(normalPixmap)
    XFreePixmap(XtDisplay(parent), normalPixmap);
  if(pressedPixmap)
    XFreePixmap(XtDisplay(parent), pressedPixmap);

}


// --------------------------------
//        readPixmap()
// --------------------------------
void PixmapRecView::readPixmap()
{
  XpmAttributes attributes;
  Pixmap pix, mask;
  Boolean loaded;

  loaded = WinView::getNamedPixmap(parent, 
				   m->getPixmapFile(),
				   attributes, 
				   pix, mask, iconHeight);

  if(loaded) {
    Dimension shadow;
    XGCValues gcValues;
    Pixel shadowColor = 1;

    XtVaGetValues(parent,
		  XmNbottomShadowColor, &shadowColor,
		  NULL);

    shadow = 2;
    width = attributes.width + shadow;
    height = attributes.height + shadow;

    normalPixmap = XCreatePixmap(XtDisplay(parent), 
				 XRootWindowOfScreen(XtScreen(parent)),
				 width, height, 
				 XDefaultDepthOfScreen(XtScreen(parent)));
    pressedPixmap = XCreatePixmap(XtDisplay(parent), 
				  XRootWindowOfScreen(XtScreen(parent)),
				  width, height,
				  XDefaultDepthOfScreen(XtScreen(parent)));

    XFillRectangle(XtDisplay(parent), normalPixmap, bgGC, 
		   0, 0, width, height);
    XFillRectangle(XtDisplay(parent), pressedPixmap, bgGC, 
		   0, 0, width, height);

    gcValues.clip_mask = None;
    XGetGCValues(XtDisplay(parent), fgGC, 
		 GCForeground | GCClipXOrigin | GCClipYOrigin,
		 &gcValues);

    XSetForeground(XtDisplay(parent), fgGC, shadowColor);
    if(mask != None) {
      XCopyPlane(XtDisplay(parent), mask, normalPixmap, fgGC, 0, 0,
		 attributes.width, attributes.height, 
		 shadow, shadow, 1);
    } else {
      XFillRectangle(XtDisplay(parent), normalPixmap, fgGC, 
		     shadow, shadow, attributes.width, attributes.height);
    }

    XSetClipMask(XtDisplay(parent), fgGC, mask);
    XCopyArea(XtDisplay(parent),pix, normalPixmap, fgGC, 0, 0,
	      attributes.width, attributes.height, 0, 0 );

    XSetClipOrigin(XtDisplay(parent), fgGC, shadow/2, shadow/2);
    XCopyArea(XtDisplay(parent),pix, pressedPixmap, fgGC, 0, 0,
	      attributes.width, attributes.height, shadow/2, shadow/2 );

    XChangeGC(XtDisplay(parent), fgGC, 
		 GCForeground | GCClipXOrigin | GCClipYOrigin | GCClipMask,
		 &gcValues);
  } else {
    fprintf(stderr, "NULL-Pixmap in contructor of PixmapRecView\n");
  }
}


// --------------------------------
//        draw()
// --------------------------------

void PixmapRecView::draw(Boolean) {
  if((m->isSelected() || parentObject->getPressed()) && pressedPixmap != 0) {
    XCopyArea(XtDisplay(parent),pressedPixmap, XtWindow(parent), fgGC, 
	      0, 0, width, height, x, y);
  } else {
    if(normalPixmap != 0)
      XCopyArea(XtDisplay(parent), normalPixmap, XtWindow(parent), fgGC, 
		0, 0, width, height, x, y);
  }
}

// --------------------------------------
//             update()
// --------------------------------------

void PixmapRecView::update( unsigned long flags ) {
  if( flags & NAME_CHANGED ) {
    XFreePixmap(XtDisplay(parent), normalPixmap);
    XFreePixmap(XtDisplay(parent), pressedPixmap);
    readPixmap();
    
    parentObject->configure();
  }
}


// ##############################################
//               StatePixmapRecView
// ##############################################

StatePixmapRecView::StatePixmapRecView(Iconable *m, SensitiveRec *p)
:RecView(m) 
{
  fgGC = p->getContainer()->getForegroundGC();
  bgGC = p->getContainer()->getBackgroundGC();
  parent = p->getContainer()->getWidget();
  width = height = 0;
}

StatePixmapRecView::~StatePixmapRecView()
{
  while(states.getSize())
    states[0].Delete();
}

// --------------------------------------
//            configure()
// --------------------------------------

void StatePixmapRecView::configure()
{
  width = 0;
  height = 0;

  for(unsigned int i=0; i<states.getSize(); i++) {
    width = MAX(width, states[i]->width);
    height = MAX(height, states[i]->height);
  }
  for(unsigned int i=0; i<states.getSize(); i++) {
    states[i]->x = width/2 - states[i]->width/2;
    states[i]->y = height/2 - states[i]->height/2;
  }
}

// --------------------------------------
//            addState()
// --------------------------------------

void StatePixmapRecView::addState(unsigned char id, char *iconName)
{
  XpmAttributes attr;
  Boolean loaded;

  StatePixmap *sp = new StatePixmap();

  loaded = WinView::getNamedPixmap(parent, 
				   iconName, 
				   attr, 
				   sp->pixmap, sp->mask);
  
  if(!loaded) {
    delete sp;
    return;
  }
  sp->id = id;
  sp->width = attr.width;
  sp->height = attr.height;
  states.add(sp);
  configure();
}


// --------------------------------------
//            removeState()
// --------------------------------------

void StatePixmapRecView::removeState(unsigned char id)
{
  for(unsigned int i=0; i<states.getSize(); i++) {
    if(states[i]->id == id) {
      states[i].Delete();
    }
  }
  configure();
}


// --------------------------------------
//            setState()
// --------------------------------------

void StatePixmapRecView::setState(unsigned char id)
{
  for(unsigned int i=0; i<states.getSize(); i++) {
    if(states[i]->id == id) {
      currentState = states[i];
      return;
    }
  }
}


// --------------------------------------
//            draw()
// --------------------------------------

void StatePixmapRecView::draw(Boolean)
{
  Display *display = XtDisplay(parent);
  Window window = XtWindow(parent);
  
  if(window == None || currentState.isNil())
    return;

  XSetClipMask(display, fgGC, currentState->mask);
  XSetClipOrigin(display, fgGC, x + currentState->x, y + currentState->y); 
  XCopyArea(display, currentState->pixmap, window, fgGC, 0, 0,
	    currentState->width, currentState->height, 
	    x + currentState->x, y + currentState->y); 
  XSetClipMask(display, fgGC, None);
  XSetClipOrigin(display, fgGC, 0, 0);
}

