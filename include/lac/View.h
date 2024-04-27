/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: View.h,v $
 *  $Date: 1999/08/27 15:30:26 $
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
 * $Log: View.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:26  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:14:50  lazy
 * Initial revision
 *
 */

// -----------------------------
//         View
//         
//         WinView
//         
//         RecView
//
// (C) Dirk Laessig
// -----------------------------

#ifndef _VIEW_H_
#define _VIEW_H_


#include <X11/Intrinsic.h>
#include <lac/Lobject.h>
#include <lac/RefArray.h>
#include <lac/Rec.h>
#include <lac/WidgetRef.h>
#include <lac/TArray.h>

#include <limits.h>
#include <X11/xpm.h>


// -------------------    View    --------------------
class Model;

class View : public Lobject {
private:
  Ref<Model> model;
protected:
  Ref<View> parentView;            // the view in which this view is a part
  static Boolean waitForUpdate;    // we are in a transaction
  static RefArray<View> pendingUpdateViews;  // collection of all views getting
                                             // an update in a transaction
  unsigned long pendingUpdateFlags;  

  static RefArray<View> refreshViews;    // all views that need a refresh
  
public:
  View( Model *m=NULL );
  ~View();

  virtual void updateFromModel(unsigned long flags);
  virtual void update( unsigned long flags ) = 0;
  virtual void refresh() {}
  void needRefresh();                    // mark this view for refresh

  virtual const char *getName() { return "unnamed"; }
  virtual Boolean destroyFromModel() { return True; }

  void changeModel( Model *m );

  static void transactionBegin();
  static void transactionEnd();
};


// -------------------  WinView  ---------------------

class WinView : public View {
private:

  // callback for all actions in the menu, or buttons in views
  // XtPointer contains a pointer of struct CBInfo
  static void command( Widget, XtPointer, XtPointer );

  struct IconData {
    const char *name;
    char **data;
  };

  static TArray<IconData> buildInIcons;
  static char **findIcon(const char *name);

  struct PixmapEntry {            
    XpmAttributes attributes;
    Pixmap loaded;
    Pixmap bitmap;         // converted to black and white (depth 1);
    Pixmap mask;
    char name[PATH_MAX];
    Dimension iconHeight;  // requested height
    PixmapEntry *next;
  };

  static PixmapEntry *first;
  static PixmapEntry *findEntry(char *name, Dimension iconHeight = 0);
  static PixmapEntry *loadEntry(Widget wg, const char *name);
  static PixmapEntry *createScaledEntry(Widget wg, char *name, 
					Dimension iconHeight);
  static Pixmap scalePixmap(Widget wg, 
			    Pixmap pixmap, 
			    Dimension height,
			    Dimension width,
			    Dimension depth,
			    float scaleFactor);

  static void createBitmap(Widget wg, PixmapEntry *entry);

protected:
  class CBInfo : public Lobject {
  public:
    WinView *instance;
    char *actionName;
  };
  RefArray<CBInfo> allActions;

  virtual void act( char *actionName ) = 0;    // called from command
  void addAction( Widget, char *actionName );  // only for Buttons

public:
  WinView( Model *m);      
  virtual ~WinView();

  // get an icon: look into the cache, look in buildInIcons and at last
  // search in the filesystem
  static Boolean getNamedPixmap(Widget wg, 
				char *filename, 
				XpmAttributes &attr,
				Pixmap &pixmap,
				Pixmap &mask,
				Dimension iconHeight = 0);

  static Boolean getNamedBitmap(Widget wg,
				char *filename, 
				XpmAttributes &attr,
				Pixmap &pixmap,
				Pixmap &mask);
				
  // add icons in the program code
  static void addIcon(const char *name, char **data);

  static Widget getIconFromBits(Widget wg, 
				char *bits, Dimension w, Dimension h,
				char *mask, Dimension mw, Dimension mh,
				Position offsetX, Position offsetY);
  static Widget getIconFromPixmapName(Widget wg, char *name);

  static XtArgVal cvtResourceFromString(Widget wg, char *type, char *value);
};



#endif /* DON'T ADD ... */
