/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lproject.h,v $
 *  $Date: 1999/08/27 15:31:19 $
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
 * $Log: Lproject.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:19  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:28  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:27:16  lazy
 * Initial revision
 *
 */

/* --------------------------------------------------------------------
   (C) Dirk Laessig 1994

   Lproject - Ein Projekt im LIC

   Linterface - Ein Interfaces eines Projektes

   --------------------------------------------------------------------*/
#ifndef _LPROJECT_H_
#define _LPROJECT_H_

#include <limits.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <lac/Model.h>
#include <lac/IconView.h>
#include <parse.h>
#include <lac/LicView.h>
#include <lac/MLXHelp.h>
#include <lac/HelpNode.h>

class Lwidget;
class Lcreator;
class Linterface;
class InterfaceView;
class WidgetView;

#include "LApp.h"
#include "Lwidget.h"
#include "Ltmpl.h"

enum FileClass {              // needed to classify generated files
  FILE_CLASS_IMAKEFILE,
  FILE_CLASS_MAIN_PROGRAM,
  FILE_CLASS_GLOBAL_RESOURCES,
  FILE_CLASS_INTERFACE_SOURCE
};

//  ------------ Lproject -----------

class Lproject : public Model {
private:
  Container<Linterface> interfaces;
  Ref<Linterface> startupInterface;
  char *resources;                        // default resources
  char *programName;

  char file[PATH_MAX];
  char sourcePath[PATH_MAX];
  Ref<LangInfo> lang;                     // the generation language
  char helpfile[PATH_MAX];

  char applClass[PATH_MAX];
  char execFile[PATH_MAX];
  char *moreSource;
  char *extraCCOptions;
  char *extraLDOptions;
  char *extraLibraries;
  char *description;
  char *globalResources;

  static Lproject *currentProject;            // only one project exist

  Widget topLevel;                            // top of wysiwyg-Views
  Ref<MLXHelp> mlxHelp;                       // help instance
  Ref<HelpNode> helpNode;

  Boolean unspecFilename;

public:
  Lproject(char *filename = NULL, YResult *parsed=NULL);
  ~Lproject();

  Lwidget *find( Window id );               // for drag and drop
  Boolean save(char *filename=NULL);                      // save whole project

  Linterface *addInterface(YInterface *parseResult); // loaded from file
  Linterface *addInterface(Lcreator *shellClass = NULL);
                                                     // other as default shell
  Linterface *addInterface(Linterface *interface);  

  Boolean existNamedInterface( char *name );
  Linterface *getInterface( Lwidget *shell );
  Linterface *getInterface( char *name );

  char *getFilename() { return file; }
  void setFilename(char *newFilename = NULL);
  Boolean isUnspecFilename() { return unspecFilename; }

  LangInfo *getLang() { return lang; }          // the generation languages
  void setLang(LangInfo *l) { lang = l; }
 
  Linterface *getStartupInterface();
  void setStartupInterface(Linterface *linterface);

  char *getSourcePath() { return sourcePath; }
  void setSourcePath(char *sp) { strcpy(sourcePath, sp); }

  char *getApplClass() { return applClass; }
  void setApplClass(char *s) { 
    strcpy(applClass, s); 
    updateTopLevel();
  }

  char *getExecFile() { return execFile; }
  void setExecFile(char *s) { strcpy(execFile, s); }

  char *getMoreSource() { return moreSource; }
  void setMoreSource(char *s) { 
    delete moreSource; 
    moreSource = new char[strlen(s)+1];
    strcpy(moreSource, s);
  }

  char *getExtraCCOptions() { return extraCCOptions; }
  void setExtraCCOptions(char *s) { 
    delete extraCCOptions; 
    extraCCOptions = new char[strlen(s)+1];
    strcpy(extraCCOptions, s);
  }

  char *getExtraLDOptions() { return extraLDOptions; }
  void setExtraLDOptions(char *s) { 
    delete extraLDOptions; 
    extraLDOptions = new char[strlen(s)+1];
    strcpy(extraLDOptions, s);
  }

  char *getExtraLibraries() { return extraLibraries; }
  void setExtraLibraries(char *s) { 
    delete extraLibraries; 
    extraLibraries = new char[strlen(s)+1];
    strcpy(extraLibraries, s);
  }

  char *getDescription() { return description; }
  void setDescription(char *s) { 
    delete description; 
    description = new char[strlen(s)+1];
    strcpy(description, s);
  }

  char *getGlobalResources() { return globalResources; }
  void setGlobalResources(char *s) { 
    delete globalResources; 
    globalResources = new char[strlen(s)+1];
    strcpy(globalResources, s);
    updateTopLevel();
  }

  static Lproject& current() 
    { return *currentProject; }
  Widget getTopLevel() { return topLevel; }
  void updateTopLevel();
  
  char *getClassName() { return "Lproject"; }
  Container<Linterface> &getInterfaces() { return interfaces; }

  // code generation
  Boolean generate(Boolean generateInterfaces,
		   Boolean overwriteStubs, 
		   Boolean imakefile,
		   Boolean mainprogramm,
		   RefArray<Lfile> &overwriteFiles, //return the files to overwrite
		   char *path = NULL);

  // show the help instance
  void getHelp(int id);
  HelpNode *findHelpNode(int id) { return helpNode->find(id); }


  // changes
  Boolean getChangedFlag();
  void resetChangedFlag();
};


// ----------------- Linterface -----------------

class Linterface : public Iconable {
private:
  Boolean isDeleted;
  char *name;
  static Cardinal count;


  Ref<Lwidget> shell;           // The Popupshell
  Ref<InterfaceView> wysiwyg;   // Its View !!!!!!!!!!

  Position x, y;                // not persistent
  Dimension width, height;      // not persistent
  Boolean correctionInit;         
  Boolean trick;
  Position correctX, correctY;

  Boolean isSaved;

public:
  Linterface( Lcreator *shellClass = NULL );
  Linterface( YWidget *parsingResult );
  ~Linterface();
  
  // informations
  Lproject *getProject();
  Lwidget *getShell() { return shell; }
  Boolean existNamedWidget( char *aName );

  // actions
  void show();   // Manage the shell
  void hide();   // Unmanage the shell, and destroy
  void destroyView();  // Destroy the shell
  Boolean isShown() { return !wysiwyg.isNil(); }

  void moveTo( Position x, Position y, Boolean fromConfigure=FALSE );  
                                                    // move the view
  void setSize( Dimension width, Dimension height );

  Boolean save( char *filename = NULL );

  // overloaded
  char *getClassName() { return "Linterface"; }
  char *getPixmapFile();
  void delNotify( BaseRef *toDel );
  char *getName();
  Boolean nameChangeable() { return TRUE; }
  Boolean setName(char *n);

  // code generation
  Boolean generate(char *lang, Boolean overwriteStubs, 
		   RefArray<Lfile> &overwriteFiles, char *path=NULL);   
                   // return false, if language not exist

  // changes
  Boolean getChangedFlag();
  void resetChangedFlag();
};

// ------------------- InterfaceView -------------------

class InterfaceView : public LicView {
private:
  Linterface   *interface;
  Ref<WidgetView> widgetView;
  Boolean inDelete;
public:
  InterfaceView( Widget top, Linterface *model );
  ~InterfaceView();
  void delNotify( BaseRef *toDel );
  void act( char * ){}
  void moveTo( Position x, Position y );
  void setSize( Dimension width, Dimension height );

  WidgetView *getShell();
  void newPopupShell( Widget );

  void update( unsigned long flags );
  
  void wmDelete();
};


// ------------------ InterfaceController --------------------

class InterfaceController : public Controller {
private:
  Linterface *interface;
  void createMenuEntries();
public:
  InterfaceController(Linterface *am, View *icon);
  void act(MenuEntry *me);
  void actOnce(MenuEntry *me);
  void defaultAction();
};

// ------------------- InterfaceIconView ---------------------

class InterfaceIconView : public IconView {
public:
  InterfaceIconView(ContainerBase *cm, Widget p, Icon *icon=NULL )
    :IconView(cm,p,icon){}

  Controller *getController(SensitiveRec *v) {
    return new InterfaceController((Linterface*)v->getModel(),v);
  }
};

#endif /* DON'T ... */



