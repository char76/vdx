/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: SensitiveView.h,v $
 *  $Date: 1999/08/27 15:30:13 $
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
 * $Log: SensitiveView.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:13  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.4  1998/03/30 19:09:39  lazy
 * *** empty log message ***
 *
 * Revision 1.3  1997/09/11  14:57:19  lazy
 * Keyboard traversal inserted.
 *
 * Revision 1.2  1997/09/08  17:07:15  lazy
 * Move visible to RecView
 *
 * Revision 1.1  1997/07/25  19:33:34  lazy
 * Initial revision
 *
 */

#ifndef _SensitiveRec_H_
#define _SensitiveRec_H_

#include <lac/View.h>
#include <lac/RefArray.h>
#include <lac/Controller.h>

#include <Xm/AtomMgr.h>
#include <Xm/DragDrop.h>
#include <Xm/Screen.h>

#ifdef MAX
#undef MAX
#endif
#define MAX(x,y) ((x)>(y) ? (x) : (y))

class Iconable;
class SensitiveContainer;
class ContainerBase;


// -------------------  RecView  ---------------------

class RecView : public View {
protected:
  Position x, y;
  Boolean isVisible;

public:
  RecView(Model *m);      
  virtual ~RecView();

  virtual void setPosition( Position x, Position y ) 
    { 
      this->x = x;
      this->y = y; 
    }

  // virtual methods

  // query the size of this object
  virtual Dimension getWidth() = 0;
  virtual Dimension getHeight() = 0;

  // query the position
  Position getX() { return x; }
  Position getY() { return y; }

  // is point in object's area
  virtual Boolean isIn(Position x, Position y);

  // is full object in area
  virtual Boolean isInRec(Rec &rec);        

  // is object partialy in area
  virtual Boolean isInRecPart(Rec &rec);        

  // draw me
  virtual void draw(Boolean asSelected = FALSE) = 0;
  
  // Visibility
  void setVisible( Boolean vs )      { isVisible = vs; }
  Boolean getVisible()               { return isVisible; }

  // simple query method
  Position getRightBorder()   { return x + getWidth(); }
  Position getBottomBorder()  { return y + getHeight(); }

  void getMiddle(Position &x, Position &y);
};


// --------------------- SensitiveRec -----------------------

class SensitiveRec : public RecView {
private:
  Iconable *m;
  SensitiveContainer *sensitiveContainer;     // parent container

  Widget dragContext;                         // drag and drop
  static SensitiveRec *draggedObject;
  static Boolean convertProc(Widget w, Atom *selection, 
			     Atom *target, Atom *type,
			     XtPointer *value, unsigned long *length, 
			     int *format, unsigned long *max_length,
			     XtPointer clientData, XtRequestId *requId);
protected: 
  GC fgGC;
  GC bgGC;

  Widget parent;
  Boolean pressed;
  Atom exports[2];       
  Boolean highlightState;
  Boolean tmpSelect;

public:
  SensitiveRec(Iconable *am, SensitiveContainer *c);
  ~SensitiveRec();

  virtual void highlight(Boolean state);
  virtual void expose();
  void update( unsigned long flags );

  // mouse clicks
  virtual void select( Boolean multi, Position x, Position y );    // Btn1
  virtual void move(Widget wg,
		    XEvent *event,
		    Position x,Position y, 
		    unsigned char dragO);  // Btn2

  void setTmpSelect(Boolean t) { tmpSelect = t; }
  Boolean getTmpSelect() { return tmpSelect; }

  void setPressed( Boolean state );
  Boolean getPressed()               { return pressed; }
  virtual void edit(Position x, Position y, Boolean mode) {}

  SensitiveContainer *getContainer() { return sensitiveContainer; }
  Iconable *getModel()               { return m; }

  virtual void configure() = 0;

  // drag and drop
  virtual void dragQueryExports(Atom *&exportTargets, 
				Cardinal &numExportTargets,
				Widget &icon);
  virtual Boolean convert(Widget w, Atom *selection, 
			  Atom *target,Atom *type,
			  XtPointer *value, unsigned long *length,
			  int *format);

  virtual Boolean isBefore(Position x, Position y) = 0;
  virtual void highlightBefore(Boolean state) = 0;

  virtual void traverseUp();
  virtual void traverseDown();
  virtual void traverseLeft();
  virtual void traverseRight();
};

// --------------------- SensitivContainer -------------------

class SensitiveContainer : public WinView {
private:
  ContainerBase *m;
  unsigned char dragOperations;
  RefArray<SensitiveRec> pressed;
  WidgetRef quickHelpLabel;
  Ref<SensitiveRec> currentQuickHelpObject;
  
  Boolean highlightParent;
  Boolean rubberBandMode;
  Rec rubberBand;
  Position beginX, beginY;     // starting point of rubber band mode
  RefArray<SensitiveRec> inRubberBand;
  Boolean timerOn;
  XtIntervalId timerId;

  Widget bubble;

  static void expose(Widget wg, XtPointer this_class, 
		     XEvent *event, Boolean *b );
  static void button_press(Widget wg, XtPointer this_class,
			   XEvent *event, Boolean *b );
  static void button_motion(Widget wg, XtPointer this_class,
			    XEvent *event, Boolean *b );
  static void button_release(Widget, XtPointer this_class,
			     XEvent *event, Boolean *b );
  static void mouse_move(Widget, XtPointer, XEvent *, Boolean *);
  static void key_pressed(Widget, XtPointer, XEvent *, Boolean *);

  static void focus_in(Widget, XtPointer, XEvent *, Boolean *);
  static void focus_out(Widget, XtPointer, XEvent *, Boolean *);
  static void expose_clip_window(Widget, XtPointer, XEvent *, Boolean *);
  static void timerCallback(XtPointer client_data, XtIntervalId *id);

  void createGCs();
  void rubberDraw(Position x, Position y, Boolean newValues);
  virtual void makePopup(SensitiveRec *found, Position x,Position y);  // Btn3
  void doQuickHelp(Position x, Position y);
  void drawHighlightParent();

protected:
  RefArray<SensitiveRec> contents;
  Ref<SensitiveRec> highlighted;
  Ref<SensitiveRec> inEditMode;
  Widget scrolledWindow;
  Widget box;
  Display *display;
  GC fgGC;
  GC bgGC;
  XmFontList fontList;

  Rec viewportRec;

  static void configureEvent(Widget,XtPointer self,XEvent* event,Boolean*);
  static void scrollCB(Widget, XtPointer, XtPointer);
  void queryViewport();
  virtual void processKey(XKeyEvent *event);

public:  
  SensitiveContainer( ContainerBase *m, Widget p );
  virtual ~SensitiveContainer();
  void setModel(ContainerBase *m);

  virtual void button( XEvent *event,Position x,Position y,unsigned int key );
  void update( unsigned long flags );

  unsigned char queryDragOperations() {return dragOperations;}
  void setDragOperations(unsigned char dragO) { dragOperations = dragO; }

  GC getForegroundGC() { return fgGC; }
  GC getBackgroundGC() { return bgGC; }
  XmFontList getFontList() { return fontList; }

  virtual XmString createXmString(Iconable *m);

  Widget getWidget() { return box; }
  Widget getTop() { return scrolledWindow; }

  // Help functionality
  void setQuickHelpLabel(Widget label) { quickHelpLabel = label; }
  void setBubbleHelp(Boolean b);
  Boolean getBubbleHelp() { return bubble != 0; }

  void edit(SensitiveRec *toEdit, Position x, Position y, Boolean b);

  void getSelectedObjects(RefArray<Iconable> &seletion);
  void getSelectedControllers(RefArray<Controller> &seletion);
  virtual Controller *getController(SensitiveRec *v);
  Rec &getViewport() { return viewportRec; }
  
  void setHighlighted(Iconable *);
  virtual void configure() = 0;          

  SensitiveRec *queryInsertBefore(Position x, Position y);
  SensitiveRec *queryAsChild(Position x, Position y);
  SensitiveRec *queryNextContent(Position x, Position y, 
				 Position dx, Position dy);
  virtual void scrollToMakeVisible(Iconable *model);
};


// -------------------------------------------------
//             TextRecView
// This class define a text, which is visible in
// a SensitiveContainer
// -------------------------------------------------

class TextRecView : public RecView {
private: 
  Iconable *m;
  SensitiveRec *parentObject;

  SensitiveContainer *container; // query in constructor
  Widget parent;                 // parent widget
  Widget textWidget;             // for edit mode
  Boolean editable;              // if true -> text widget
  GC fgGC;
  GC bgGC;
  XmFontList fontList;

  XmString xmString;

  Dimension margin;
  Dimension width, height;

  Boolean nameChanged;
  void queryTextExtend();
  Widget createTextWidget();

  static void textActivateCallback(Widget, XtPointer, XtPointer);
  static void textKeyPressed(Widget, XtPointer, XEvent *, Boolean *);

public:
  TextRecView( Iconable *am, SensitiveRec *p );
  ~TextRecView();

  void draw(Boolean asSelected = FALSE);
  void update( unsigned long flags );
  void setEditable(Boolean mode);

  // overloaded
  Dimension getWidth(); 
  Dimension getHeight();
  void setPosition(Position x, Position y);

};

// ---------------------------
// PixmapRecView
// ---------------------------

class PixmapRecView : public RecView {
private:
  Iconable *m;                   // the model
  SensitiveRec *parentObject;

  SensitiveContainer *container; // query in constructor
  Widget parent;                 // parent widget
  GC fgGC;
  GC bgGC;

  Pixmap normalPixmap;
  Pixmap pressedPixmap;

  Dimension width, height;
  Dimension iconHeight;

  void readPixmap();
  
public:
  PixmapRecView(Iconable *am, SensitiveRec *p, Dimension iconHeight = 0);
  ~PixmapRecView();

  void draw(Boolean asSelected = FALSE);
  void update( unsigned long flags );

  // overloaded
  Dimension getWidth() { return width; }
  Dimension getHeight() { return height; }
};


// --------------------------------
// StatePixmapRecView
// --------------------------------

class StatePixmapRecView : public RecView {
private:
  class StatePixmap : public Lobject {
  public:
    Position x, y;
    Dimension width, height;
    Pixmap pixmap;
    Pixmap mask;

    unsigned char id;
  };

  RefArray<StatePixmap> states;

  Dimension width, height;
  GC fgGC;
  GC bgGC;
  Widget parent;

  Ref<StatePixmap> currentState;

  void configure();

public:
  StatePixmapRecView(Iconable *m, SensitiveRec *p);
  ~StatePixmapRecView();
  Dimension getWidth() { return width; }
  Dimension getHeight() { return height; }

  void addState(unsigned char id, char *iconName);
  void removeState(unsigned char id);
  void setState(unsigned char id);

  void draw(Boolean asSelected = FALSE);
};



#endif
