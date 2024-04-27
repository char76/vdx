/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LApp.h,v $
 *  $Date: 1999/08/27 15:31:11 $
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
 * $Log: LApp.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:11  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:21  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:26:41  lazy
 * Initial revision
 *
 */

#ifndef _LAPP_H_
#define _LAPP_H_

/* ---------------------------------------------------------
   (C) Dirk Laessig 1994
   --------------------------------------------------------- */


#include <lac/Model.h>
#include <lac/IconView.h>
#include <limits.h>
#include <X11/Intrinsic.h>
#include <parse.h>
#include <lac/ConModel.h>
#include <string.h>

class Lproject;
class WidClasses;
class Lpalette;

#define APPL_CLASS "Vdx"

enum Button1Mode { WV_RESIZE, WV_EDIT, WV_SELECT };  // obsolete


//
// VDX provides generation of different Language
// LangInfo is a describtion of such generation model
//

class LangInfo : public Lobject {
private:
  char langName[LIC_LANG_MAX];
  char implementationSuffix[32];
  Boolean withLibLac;
  
public:
  LangInfo(FILE *fp); 
  char *getName() { return langName; }
  char *getSuffix() { return implementationSuffix; }
  Boolean getWithLibLac() { return withLibLac; }
};

//
// LApp - The application object of this application
//

class LApp : public Model {
private:

  Boolean gridOn;		// Is grid enabled within WYSIWYG
  Dimension gridValue;		// Value of this grid
  Boolean updatePolicy;		// refresh strategy of WYSIWYG
  Boolean quickHelp;		// show quick help lines in each window
  char *lwhereFont;		// font name during drag and resize
  char *mainTemplatePath;	// file name of main template folder
  char *currentProject;		// last saved project
  Boolean normalQuit;		// last running normaly ended (recover or not)
  Boolean quickStartWindow;	// show the quick start dialog at startup
  char *viewData;		// geometry information of several windows

  /* Widget Resource Editor */
  Boolean editorAutomaticLoad;	// automatic load on in WidResEditor
  Boolean editorWithSource;       /* unused */
  char *defaultPublic;		/* All resources, that have to put in resource
				   file by default */
  int editorDefaultView;	/* resource category first displayed 
				   (Core, Extra, ...) */

  /* Widget Tree Browser */
  Boolean browserAutomaticLoad; // automatic load in WidBrowseView
  Boolean browserSmallIcons;	// show small icons in tree view
  Boolean browserWithIcons;	// show icons or not
  Boolean browserWithClassName;	// show class names in tree view

  /* Menu Editor */
  Boolean menuEditAutomaticLoad;// same as above
  Boolean menuEditSmallIcons;
  Boolean menuEditWithIcons;
  Boolean menuEditWithClassName;

  /* Attachment Editor */
  Boolean attachmentEditorAutomaticLoad; // same
  Boolean attachmentEditorSmallIcons;
  Boolean attachmentEditorWithIcons;
  Boolean attachmentEditorWithClassName;

  /* Other Settings */
  Boolean versionControl;		// execute scripts during file ops
  Boolean showInterfaceAfterLoad;	// display WYSIWYG when loaded
  Boolean implicitInterfaceCreate;	// allow interface creation on root ??
  Boolean toolTipsEnabled;		// display XlBubble widgets

  Boolean autoSavingOn;		// auto saving enabled
  unsigned int autoSaveSeconds;	// timeout for autosaving
  char *autoSavePath;		// where the auto saved project is

  Boolean demoMode;		// Demo mode is enabled :-)
  Boolean first;		// first execution (need to display agreement

  static XtResource applResources[];	// resource list to configure options

  char configPath[PATH_MAX];	
  char homePath[PATH_MAX];
  char binPath[PATH_MAX];
  char pixmapPath[PATH_MAX];
  char startupDir[PATH_MAX];

  char licensee[1024];

  Lproject *project;                // currentProject in lic
  Ref<Lpalette> mainTemplate;           // main template
  Container<Lpalette> templates;     // all templates 

  Boolean testMode;                 // is LIC in test mode
  Button1Mode button1Mode;

  RefArray<LangInfo> languages;

  XtIntervalId  autoSaveTimer;      // auto save timer
  Boolean inAutoSave;

  // Lcreator Objects - Initialized during creation
  WidClasses *widClasses;

public:
  LApp( int argc, char **argv );

  char *getConfigPath() { return configPath; }
  char *getHomePath() { return homePath; }
  char *getBinPath() { return binPath; }
  char *getPixmapPath() { return pixmapPath; }
  char *getStartupDir() { return startupDir; }

  void setProject(Lproject *p) { project = p; }
  Lproject *getProject() { return project; }

  Container<Lpalette> &getTemplates() { return templates; }

  WidClasses &getWidClasses() { return *widClasses; }

  Boolean getTestMode() { return testMode; }
  void setTestMode( Boolean t = TRUE );

  char *getLwhereFont() { return lwhereFont; }
  
  void setButton1Mode( Button1Mode bm) { button1Mode = bm; }
  Button1Mode getButton1Mode() { return button1Mode; }

  void setOptimalRefresh(Boolean v) { updatePolicy=v; }
  Boolean getOptimalRefresh() { return updatePolicy; }
  void loadFile( char *filename );

  void addLang( LangInfo * );
  LangInfo *getLang( char *name );
  RefArray<LangInfo> getLanguages() { return languages; }

  void saveOptions();               // Save global options

  Boolean isDemo() { return demoMode; }
  Boolean firstExecution() { return first; }
  char *getLicensee() { return licensee; }

  void changed( unsigned long flags );

  // error output
  void showSystemError(char *filename, int err);

  // auto saver
  static void autoSaveTimeout(XtPointer client_data, XtIntervalId *id);
  void autoSave();

  void setGrid( Boolean g ) { gridOn = g; }
  Boolean getGrid() { return gridOn; }
  void setGridValue( Cardinal gv ) { gridValue = gv; }
  Cardinal getGridValue() { return gridValue; }

  char *getCurrentProject() { return currentProject; }
  Boolean getNormalQuit() { return normalQuit; }

  Boolean getQuickStartWindow() { return quickStartWindow; }
  Boolean getShowInterfaceAfterLoad() { return showInterfaceAfterLoad; }
  Boolean getImplicitInterfaceCreate() { return implicitInterfaceCreate; }
  Boolean getAutoSavingOn() { return autoSavingOn; }
  unsigned int getAutoSaveSeconds() { return autoSaveSeconds; }
  char *getAutoSavePath() { return autoSavePath; }

  Boolean getEditorAutomaticLoad() { return editorAutomaticLoad; }
  Boolean getEditorWithSource() { return editorWithSource; }

  Boolean getBrowserAutomaticLoad() { return browserAutomaticLoad; }
  Boolean getBrowserSmallIcons() { return browserSmallIcons; }
  Boolean getBrowserWithIcons() { return browserWithIcons; }
  Boolean getBrowserWithClassName() { return browserWithClassName; }

  Boolean getMenuEditAutomaticLoad() { return menuEditAutomaticLoad; }
  Boolean getMenuEditSmallIcons() { return menuEditSmallIcons; }
  Boolean getMenuEditWithIcons() { return menuEditWithIcons; }
  Boolean getMenuEditWithClassName() { return menuEditWithClassName; }

  Boolean getAttachmentEditorAutomaticLoad() { return attachmentEditorAutomaticLoad; }
  Boolean getAttachmentEditorSmallIcons() { return attachmentEditorSmallIcons; }
  Boolean getAttachmentEditorWithIcons() { return attachmentEditorWithIcons; }
  Boolean getAttachmentEditorWithClassName() { return attachmentEditorWithClassName; }


  void setCurrentProject(char *s) { currentProject = s; }
  void setNormalQuit(Boolean b) { normalQuit = b; }

  void setQuickStartWindow(Boolean b) { quickStartWindow = b; }
  void setShowInterfaceAfterLoad(Boolean b) { showInterfaceAfterLoad = b; }
  void setImplicitInterfaceCreate(Boolean b) { implicitInterfaceCreate = b; }
  void setAutoSavingOn(Boolean b) { autoSavingOn = b; }
  void setAutoSaveSeconds(unsigned int s);
  void setAutoSavePath(char *s);

  void setEditorAutomaticLoad(Boolean b) { editorAutomaticLoad = b; }
  void setEditorWithSource(Boolean b) { editorWithSource = b; }

  void setBrowserAutomaticLoad(Boolean b) { browserAutomaticLoad = b; }
  void setBrowserSmallIcons(Boolean b) { browserSmallIcons = b; }
  void setBrowserWithIcons(Boolean b) { browserWithIcons = b; }
  void setBrowserWithClassName(Boolean b) { browserWithClassName = b; }

  void setMenuEditAutomaticLoad(Boolean b) { menuEditAutomaticLoad = b; }
  void setMenuEditSmallIcons(Boolean b) { menuEditSmallIcons = b; }
  void setMenuEditWithIcons(Boolean b) { menuEditWithIcons = b; }
  void setMenuEditWithClassName(Boolean b) { menuEditWithClassName = b; }

  void setAttachmentEditorAutomaticLoad(Boolean b) 
  { attachmentEditorAutomaticLoad = b; }
  void setAttachmentEditorSmallIcons(Boolean b) 
  { attachmentEditorSmallIcons = b; }
  void setAttachmentEditorWithIcons(Boolean b) 
  { attachmentEditorWithIcons = b; }
  void setAttachmentEditorWithClassName(Boolean b) 
  { attachmentEditorWithClassName = b; }

  void setDefaultPublic(char *s);
  char *getDefaultPublic() { return defaultPublic; }
  Boolean isPublicResource(char *res_name);

  void setEditorDefaultView(int i) { editorDefaultView = i; }
  int getEditorDefaultView() { return editorDefaultView; }

  void setToolTipsEnabled(Boolean b) { toolTipsEnabled = b; }
  Boolean getToolTipsEnabled() { return toolTipsEnabled; }

  void setMainTemplatePath(char *name);
  char *getMainTemplatePath() { return mainTemplatePath; }
  Lpalette *getMainTemplate();

  Boolean getVersionControl();
  void setVersionControl(Boolean b) { versionControl = b; }

  // exit the application()
  void exit();
};


// changed parameter, bit 3-0 is reserved by Model base class
#define OPTIONS_CHANGED         (USER_CHANGED<<1)
#define PROJECT_CHANGED         (USER_CHANGED<<2)
#define WIDGETCLASSES_CHANGED   (USER_CHANGED<<3)


extern LApp *app;



#endif /* DON'T ADD ... */

