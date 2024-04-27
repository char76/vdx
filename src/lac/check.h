/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: check.h,v $
 *  $Date: 1999/08/27 15:30:32 $
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
 * $Log: check.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:32  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/30 19:09:43  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/07/25  19:50:02  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:15:19  lazy
 * Initial revision
 *
 */

#include <stdio.h>
#include <lac/View.h>
#include <lac/Model.h>
#include <lac/IconView.h>
#include <lac/LicView.h>
#include <lac/TreeNode.h>
#include <lac/TreeView.h>

#include <X11/Shell.h>
#include <X11/xpm.h>
#include <Xm/BulletinB.h>
#include <Xm/ScrolledW.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>

#include <lac/ConModel.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/timeb.h>

Widget applShell;

#define ICO "/home/lazy/prj/lic/lib/X11/pixmaps/MenuBar.xpm"

class LTree : public TreeNode<LTree> {
private:
  char *name;
  char *filename;
  char *pixmap;

  Boolean directory;

  char *getNameFromPath(char *path) {
    for( int i = strlen(path)-1; i>0; i--)
      if(path[i]=='/') {
	return &path[i+1];
      }
    return path;
  }

  LTree(char *filename, Boolean dir = TRUE) {
    this->directory = dir;
    char *name = getNameFromPath(filename);
    this->name = new char[strlen(name)+1]; 
    strcpy(this->name, name);
    this->filename = new char[strlen(filename)+1];
    strcpy(this->filename, filename);
    this->pixmap = ICO; 
  }
public:
  static LTree* createLTree(char *filename) {
    DIR * d = opendir(filename);
    if( d ) {
      closedir(d);
      return new LTree(filename);
    }
    return NULL;
  }

  Boolean nameChangeable() { return TRUE; }

  char *getClassName() { return "LModel";}
  
  char *getName() { return name; }
  Boolean setName(char *n) { 
    delete name;
    name = new char[strlen(n)+1]; 
    strcpy(name, n);
    return TRUE; 
  }
  char *getPixmapFile() { return pixmap; }

  LTree *copy() {
    return new LTree(filename);
  }

  Boolean hasChildren() { return directory; }
  Boolean populate() {
    if( directory && getSize() == 0 ) {
      DIR *d = opendir(filename);

      struct stat buf;
      struct dirent *de;
      char fName[256];
      Boolean isDir;

      if(d) {
	while( (de = readdir(d)) ) {
	  if( strcmp(de->d_name,".") && strcmp(de->d_name,"..") ) {
	    strcpy(fName, filename);
	    strcat(fName, "/");
	    strcat(fName, de->d_name);
	    if( stat(fName, &buf) == 0 ) {
	      isDir = (buf.st_mode & S_IFDIR) == S_IFDIR;
	      children.add( new LTree(fName, isDir) );
	    } 
	  }
	}
	closedir(d);
	return TRUE;
      }
    }
    return FALSE;
  }
};

#define L_INS "li"
#define L_ADD "la"
#define L_DEL "ld"
#define L_BRW "lb"

#if(0)
class LazyMenu : public Menu {
public:
  LazyMenu( Iconable *am = NULL, Widget parent = NULL )
    :Menu(am,NULL)
      {
	Widget button;
	
	if( parent ) {
	  popupMenu = XmCreatePopupMenu( parent, "Popupmenu", (Arg*)NULL, 0 );
	  label = XtCreateManagedWidget("Label", xmLabelWidgetClass, 
					popupMenu, (Arg*)NULL, 0 );
	  button = XtCreateManagedWidget("Browse",xmPushButtonWidgetClass,
					 popupMenu, (Arg*)NULL, 0 );
	  addAction( button, L_BRW );
	  button = XtCreateManagedWidget("Add Child",xmPushButtonWidgetClass,
					 popupMenu, (Arg*)NULL, 0 );
	  addAction( button, L_ADD );
	  button = XtCreateManagedWidget("Insert Before",xmPushButtonWidgetClass,
					 popupMenu, (Arg*)NULL, 0 );
	  addAction( button, L_INS );
	  button = XtCreateManagedWidget("Delete",xmPushButtonWidgetClass,
					 popupMenu, (Arg*)NULL, 0 );
	  addAction( button, L_DEL );
	} else {
	  popupMenu = NULL;
	  button = NULL;
	}
	update(0);
      }

  virtual Menu *copy( Iconable *iconable, Widget parent )
    {
      return new LazyMenu(iconable,parent);
    }
  void act( char *action );
};

#endif

class MyModel : public Iconable {
  char *name;
  char *file;
public:
  MyModel( char *name, char *file ): Iconable() 
    {
      this->name = name;
      this->file = file;
    }
  char *getClassName() { return "MyModel";}
  char *getName() { return name; }
  char *getPixmapFile() { return file; }
  
private:
  static void printName( Widget, XtPointer clientData, XtPointer )
    {
      MyModel *self = (MyModel*)clientData;
      if(self->isSelected()) {
	RefArray<Selectable> s = self->getSelection();
	for( unsigned int i=0; i<s.getSize(); i++ ) 
	  printf("NAME:%s\n",((MyModel*)(Selectable*)s[i])->getName());
      } else {
	printf("NAME:%s\n",self->getName());
      }
      printf("MsgResult:%d\n", 
	     LicView::MsgBox("Eine Frage","Moechtest Du das\noder nich."));
    }
};



class Lazy : public LicView {
  IconView *sc;
  LTree *ltree;
public:
  Lazy( LTree *am ): LicView(am){
    ltree = am;
    popupShell = XtVaCreatePopupShell ("Shell", 
				  topLevelShellWidgetClass,
				  topLevel,
				  NULL );

    sc = new IconView(am, popupShell);
    //    sc->setNames(TRUE);
    //    sc->setOneRow(TRUE);

    XtManageChild(sc->getTop());
  }
  ~Lazy() { 
    XtDestroyWidget(popupShell); 
    delete sc; 
  }
  void update( unsigned long ){}
  void act(char*){}
  void wmDelete() {printf("Hallo Lazy\n");LicView::wmDelete();}
};

class Lazy1 : public LicView {
  TreeView *sc;

public:
  Lazy1( LTree *am ): LicView(am){
    popupShell = XtVaCreatePopupShell ("Shell", 
				  topLevelShellWidgetClass,
				  topLevel,
				  NULL );

    sc = new TreeView(am, popupShell);
    XtManageChild(sc->getTop());
  }
  ~Lazy1() { delete sc; XtDestroyWidget(popupShell); }
  void update( unsigned long ){}
  void act(char*){}
  void wmDelete() {
    static Cardinal id = 0;
    getHelp(id);
  }

  Boolean saveSize() {return TRUE;}
};




