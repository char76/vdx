/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LApp.C,v $
 *  $Date: 1999/08/27 15:31:10 $
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
 * $Log: LApp.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:10  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:20  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:26:39  lazy
 * Initial revision
 *
 */

/* ---------------------------------------------------------
   LApp.C
   Implementation of classes: LApp

   (C) Dirk Laessig 1994
   --------------------------------------------------------- */

#include "lic.h"

#include "LApp.h"
#include "Lproject.h"
#include "Lwidget.h"
#include "Lwhere.h"
#include "Lpalette.h"
#include "VersionControl.h"

#include "MainWindow.h"
#include "TextEdit.h"
#include "misc.h"

#include <lwid/Bubble.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

//#include "license.h"

#define HOME_VAR          "VDX_HOME"
#define DEFAULT_HOME_DIR  "."
#define HOME              "HOME"
#define OPTIONS_FILE      ".vdxrc"
#define LANG_CONFIG      "lang.cf"
#define TMP_VAR          "TMPDIR"
#define BIN_DIR           "/bin"
#define CONFIG_DIR        "/lib/X11/vdx"
#define PIXMAP_DIR        "/lib/X11/pixmaps"
#define MAIN_TEMPLATE_NAME "template.pal"

#define COPY_STRING(s)\
  if(s) {\
    char *ptr;\
    ptr = new char[strlen(s)+1];\
    strcpy(ptr, s);\
    s = ptr;\
  }

XtResource LApp::applResources[] = {
  { "gridOn", "GridOn", XtRBoolean, sizeof(Boolean),
  XtOffset(LApp*,gridOn), XtRString, (void*)"TRUE"},

  { "gridValue", "GridValue", XtRDimension, sizeof(Dimension),
  XtOffset(LApp*,gridValue), XtRString, (void*)"10"},

  { "updatePolicy", "UpdatePolicy", XtRBoolean, sizeof(Boolean),
  XtOffset(LApp*,updatePolicy), XtRString, (void*)"TRUE"},

  { "lwhereFont", "LwhereFont", XtRString, sizeof(String),
  XtOffset(LApp*,lwhereFont), XtRString, (void*)"fixed"},

  { "currentProject", "CurrentProject", XtRString, sizeof(String),
    XtOffset(LApp*,currentProject), XtRString, (void*)""},

  { "normalQuit", "NormalQuit", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,normalQuit), XtRString, (void*)"TRUE"},

  { "viewData", "ViewData", XtRString, sizeof(String),
    XtOffset(LApp*,viewData), XtRString, (void*)""},

  // widget resource editor defaults

  { "defaultPublic", "DefaultPublic", XtRString, sizeof(String),
    XtOffset(LApp*,defaultPublic), XtRString, (void*)""},

  { "editorAutomaticLoad", "EditorAutomaticLoad", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,editorAutomaticLoad), XtRString, (void*)"FALSE"},

  { "editorWithSource", "EditorWithSource", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,editorWithSource), XtRString, (void*)"TRUE"},

  { "editorDefaultView", "EditorDefaultView", XtRInt, sizeof(int),
    XtOffset(LApp*,editorDefaultView), XtRString, (void*)"0"},

  // browser defaults

  { "browserAutomaticLoad", "BrowserAutomaticLoad", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,browserAutomaticLoad), XtRString, (void*)"FALSE"},

  { "browserSmallIcons", "BrowserSmallIcons", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,browserSmallIcons), XtRString, (void*)"FALSE"},

  { "browserWithIcons", "BrowserWithIcons", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,browserWithIcons), XtRString, (void*)"TRUE"},

  { "browserWithClassName", "BrowserWithClassName", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,browserWithClassName), XtRString, (void*)"TRUE"},

  // Menu Editor defaults

  { "menuEditAutomaticLoad", "MenuEditAutomaticLoad", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,menuEditAutomaticLoad), XtRString, (void*)"FALSE"},

  { "menuEditSmallIcons", "MenuEditSmallIcons", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,menuEditSmallIcons), XtRString, (void*)"FALSE"},

  { "menuEditWithIcons", "MenuEditWithIcons", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,menuEditWithIcons), XtRString, (void*)"TRUE"},

  { "menuEditWithClassName", "MenuEditWithClassName", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,menuEditWithClassName), XtRString, (void*)"TRUE"},

  // Attachment Editor defaults

  { "attachmentEditorAutomaticLoad", "AttachmentEditorAutomaticLoad", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,attachmentEditorAutomaticLoad), XtRString, (void*)"FALSE"},

  { "attachmentEditorSmallIcons", "AttachmentEditorSmallIcons", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,attachmentEditorSmallIcons), XtRString, (void*)"FALSE"},

  { "attachmentEditorWithIcons", "AttachmentEditorWithIcons", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,attachmentEditorWithIcons), XtRString, (void*)"TRUE"},

  { "attachmentEditorWithClassName", "AttachmentEditorWithClassName", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,attachmentEditorWithClassName), XtRString, (void*)"TRUE"},

  // generic options

  { "quickHelp", "QuickHelp", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,quickHelp), XtRString, (void*)"TRUE"},
  
  { "autoSavingOn", "AutoSavingOn", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,autoSavingOn), XtRString, (void*)"TRUE"},
  
  { "autoSaveSeconds", "AutoSaveSeconds", XtRInt, sizeof(int),
    XtOffset(LApp*,autoSaveSeconds), XtRString, (void*)"600"},
  
  { "autoSavePath", "AutoSavePath", XtRString, sizeof(String),
    XtOffset(LApp*,autoSavePath), XtRString, NULL},
  
  { "quickStartWindow", "QuickStartWindow", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,quickStartWindow), XtRString, (void*)"TRUE"},

  { "mainTemplatePath", "MainTemplatePath", XtRString, sizeof(String),
    XtOffset(LApp*,mainTemplatePath), XtRString, NULL},
  
  { "showInterfaceAfterLoad", "ShowInterfaceAfterLoad", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,showInterfaceAfterLoad), XtRString, (void*)"TRUE"},

  { "implicitInterfaceCreate", "ImplicitInterfaceCreate", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,implicitInterfaceCreate), XtRString, (void*)"TRUE"},

  { "toolTipsEnabled", "toolTipsEnabled", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,toolTipsEnabled), XtRString, (void*)"TRUE"},

  { "versionControl", "VersionControl", XtRBoolean, sizeof(Boolean),
    XtOffset(LApp*,versionControl), XtRString, (void*)"FALSE"}

};

// ------------------------------------
//    LApp()     - Kontruktor
// ------------------------------------
LApp::LApp(int argc, char ** argv)
{
  char *env;
  XrmDatabase database, options;
  char fName[PATH_MAX];

  demoMode = FALSE;
  first = TRUE;
  inAutoSave = FALSE;

  // only one instance can be create
  app = this;

  // because XtResourceList will be compiled
  XtResource saveList[XtNumber(applResources)];   

  for(unsigned int i=0; i<XtNumber(applResources); i++)
    saveList[i] = applResources[i];
  
  if(getcwd(startupDir, sizeof(startupDir)) == NULL) 
    perror("getcwd");

  strcpy(fName, getenv(HOME));
  strcat(fName, "/");
  strcat(fName, OPTIONS_FILE);


  options = XrmGetFileDatabase(fName);
  if(options) {
    database = XrmGetDatabase(XtDisplay(LicView::getTopLevel()));
  
    XrmCombineDatabase(options, &database, TRUE);
    
    first = FALSE;
  } 
  XtGetApplicationResources(LicView::getTopLevel(), this, 
			    saveList, XtNumber(applResources),
			    NULL, 0);

  testMode = FALSE;
  button1Mode = WV_SELECT;
  LicView::enableQuickHelp(quickHelp);

  WidgetView::SetTestMode(testMode);
  Lwhere::setGrid(gridValue);
  if(!gridOn) 
    Lwhere::setGrid(1);
  WidgetView::setButton1Mode(button1Mode);
  WidgetView::setOptimalRefresh(updatePolicy);
  XlBubbleSetEnabled(toolTipsEnabled);

  env = getenv( HOME_VAR );
  if( !env ) {
    fprintf(stderr, "Error: %s not set.\n", HOME_VAR);
    ::exit(1);
  }
  strcpy(homePath, env );
  strcpy(configPath, env );
  strcat(configPath, CONFIG_DIR );
  strcpy(pixmapPath, env );
  strcat(pixmapPath, PIXMAP_DIR );
  strcpy(binPath, env );
  strcat(binPath, BIN_DIR );

  // init autosave
  autoSaveTimer = 0;
  setAutoSaveSeconds(autoSaveSeconds);


  FILE *fp;                            // Welche Programmiersprachen sind
                                       // definiert
  char lang_cf[PATH_MAX];
  LangInfo *lang = NULL;
  strcpy(lang_cf, getConfigPath());
  strcat(lang_cf, "/");
  strcat(lang_cf, LANG_CONFIG);
  fp = fopen(lang_cf, "r");
  if(fp) {
    while(!feof(fp)) {
      lang = new LangInfo(fp);
      if(lang->getName() && lang->getName()[0]
#ifdef WITHOUT_LAC
	 && !lang->getWithLibLac()
#endif
	 ) {
	addLang(lang);
      } else {
	delete lang;
      }
    }
    fclose(fp);
  } else {
    fprintf(stderr,"Fatal error, can't open file '%s'\n",lang_cf);
  }

#if(0)
  unsigned int size;
  Lcreator::InitClasses(NULL,&size);
  char *names[size];
  Lcreator::InitClasses(names,&size);
#endif
  widClasses = new WidClasses();      // Configure the widget classes

  //demoMode = !testLicenseFile(getConfigPath(), licensee, sizeof(licensee));

  project = new Lproject("Untitled.prj");
  if( argc > 1 )
    loadFile(argv[1]);

  parseViewData(viewData);

  if(mainTemplatePath == NULL) {
    mainTemplatePath = new char[PATH_MAX];
    strcpy(mainTemplatePath, configPath);
    if(configPath[strlen(configPath)-1] != '/') {
      strcat(mainTemplatePath, "/");
    }
    strcat(mainTemplatePath, MAIN_TEMPLATE_NAME);
  } else {
    COPY_STRING(mainTemplatePath);
  }

  if(autoSavePath == NULL) {
    char user[256];
    size_t len;

    autoSavePath = new char[PATH_MAX];

    len = sizeof(user);
    getUserName(user, len);

    sprintf(autoSavePath, "/tmp/vdx-%s", user);
  } else {
    COPY_STRING(autoSavePath);
  }

  COPY_STRING(defaultPublic);
  COPY_STRING(currentProject);
}


// ---------------------------------
//   isPublicResource()
// ---------------------------------

Boolean 
LApp::isPublicResource(char *res_name)
{
  char *ptr = NULL;
  unsigned int len;

  if(defaultPublic == NULL)
    return FALSE;

  len = strlen(res_name);

  ptr = defaultPublic;
  while((ptr = strstr(ptr, res_name)) != NULL) {
    if(ptr == defaultPublic || *(ptr-1) == ' ')
      if(ptr[len] == 0 || ptr[len] == ' ')
	return TRUE;
    if(*ptr)
      ptr++;
  }
  return FALSE;
}


// ---------------------------------
//   setDefaultPublic()
// ---------------------------------

void 
LApp::setDefaultPublic(char *s)
{
  if(defaultPublic)
    delete defaultPublic;
  defaultPublic = new char[strlen(s)+1];
  strcpy(defaultPublic, s);
}

// ---------------------------------
//   getMainTemplate()
// ---------------------------------

Lpalette *LApp::getMainTemplate() 
{ 
  if(!mainTemplate.isNil())
    return mainTemplate; 
  mainTemplate = new Lpalette(mainTemplatePath);
  templates.add(mainTemplate);
  return mainTemplate; 
}


// ---------------------------------
//   setMainTemplatePath()
// ---------------------------------

void LApp::setMainTemplatePath(char *name)
{
  delete mainTemplatePath;
  mainTemplatePath = new char[PATH_MAX];
  strcpy(mainTemplatePath, name);
}


// ---------------------------------
//   loadFile() 
// ---------------------------------

void LApp::loadFile( char *filename )
{
  char title[256], msg[256];
  YResult *result;

  // Loading a file with yacc-lex parsing
  //   -> new Project
  // | -> new Interface
  // | -> new Palette

  openFileHook(filename);
  result = parse(filename);
  if( result == NULL ) {
    msgCat->getMsg( title, ERROR_TITLE );
    msgCat->getMsg( msg, ERROR_FILE_NOT_FOUND, filename );
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    return;
  }
  if( result->parseError[0] ) {
    // Error occured
    msgCat->getMsg( title, ERROR_TITLE );
    LicView::MsgBox(title, result->parseError, MSGBOX_STYLE_OK);
  } else if (result->error) {
    showSystemError(filename, result->error);
  } else {

    // Parsed without any error

    if( result->first_interface ) {

      // new project
      msgCat->getMsg( title, QUERY_NEW_PROJECT_TITLE );
      msgCat->getMsg( msg, QUERY_NEW_PROJECT );

      if( !project->getChangedFlag() ||
	 (MSGBOX_OK == LicView::MsgBox(title, msg))) {
	delete project;
	project = new Lproject( filename, result );
	changed( PROJECT_CHANGED );
      }
    } else 
      if( result->root_widget ) {
	YInterface dummy;
	Linterface *li;
	dummy.next = NULL;
	strcpy( dummy.filename, filename );
	li = project->addInterface( &dummy );
	li->show();
      } else {   
	// no valid data
	msgCat->getMsg( title, ERROR_TITLE );
	msgCat->getMsg( msg, ERROR_NO_VALID_FORMAT, filename );
	LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
	
      }
  }
  free_YResult( result );
}



// --------------------------
//    setTestMode()
// --------------------------

void LApp::setTestMode( Boolean t ) { 
  testMode = t; 
  WidgetView::SetTestMode(t);
}



// --------------------------
//    changed()
// --------------------------
void LApp::changed( unsigned long flags )
{
  if( flags & OPTIONS_CHANGED ) {
    WidgetView::SetTestMode(testMode);
    Lwhere::setGrid(gridValue);
    if(!gridOn) 
      Lwhere::setGrid(1);
    WidgetView::setButton1Mode(button1Mode);
    WidgetView::setOptimalRefresh(updatePolicy);
    XlBubbleSetEnabled(toolTipsEnabled);
  }
  if( flags & PROJECT_CHANGED ) {
    if(project) {
      if(project->getLang()->getWithLibLac()) {
	MainWindow::withLibLac(TRUE);
      } else {
	MainWindow::withLibLac(FALSE);
      }
    }
    Boolean f = getChangedFlag();
    Model::changed(flags);
    if(!f)
      resetChangedFlag();
    return;
  }
  Model::changed(flags);
}

// --------------------------
//    addLang()
// --------------------------
void LApp::addLang( LangInfo *li )
{
  languages.add(li);
}

// --------------------------
//    getLang()
// --------------------------
LangInfo *LApp::getLang( char *name )
{
  for( unsigned int i=0; i<languages.getSize(); i++ )
    if(!strcmp(name,languages[i]->getName()))
      return languages[i];
  return NULL;
}


// --------------------------
//    saveOptions()
// --------------------------
void LApp::saveOptions()
{
  char fName[PATH_MAX];
  char *ptr;
  char buf[1024];
  static XrmDatabase database = NULL;

  if(project && !project->isUnspecFilename()) {

    normalQuit = !project->getChangedFlag();

    if(currentProject)
      delete currentProject;

    currentProject = new char[strlen(project->getFilename())+1];
    strcpy(currentProject, project->getFilename());

  } else {
    normalQuit = TRUE;
  }

  // reset the changed flag
  resetChangedFlag();

  // Read the values from other classes :-(
  quickHelp = LicView::getEnableQuickHelp();

  // get view data from model
  viewData = Model::getViewData();

  // For all option resources 

  for(unsigned int i=0; i<XtNumber(applResources); i++) {

    XPointer from = (((XPointer)this)+applResources[i].resource_offset);
    
    if(!strcmp(applResources[i].resource_type, XtRString)) {
      ptr = *(String*)from;
    } else if(!strcmp(applResources[i].resource_type, XtRBoolean)) {
      ptr = (*(Boolean*)from) ? (char*)"True" : (char*)"False";
    } else if(!strcmp(applResources[i].resource_type, XtRDimension)) {
      ptr = buf;
      sprintf(ptr, "%d", *(Dimension*)from);
    } else if(!strcmp(applResources[i].resource_type, XtRInt)) {
      ptr = buf;
      sprintf(ptr, "%d", *(int*)from);
    } else {
      fprintf(stderr, "Fatal error: Can't convert %s to string\n",
	      applResources[i].resource_type);
      continue;
    }

    // Save the value into the resource database

    char spec[256];
    XrmValue to;
    strcpy(spec, APPL_CLASS);
    strcat(spec, ".");
    strcat(spec, applResources[i].resource_name);
    to.addr =  (XPointer)ptr;
    to.size = strlen(ptr)+1;
    XrmPutResource(&database, spec, XtRString, &to);
  }
  if(database) {
    strcpy(fName, getenv(HOME));
    strcat(fName, "/");
    strcat(fName, OPTIONS_FILE);
    XrmPutFileDatabase(database, fName);
    //    XrmDestroyDatabase(database);
  }
  
}


// -------------------------------------------
//       showSystemError()
// -------------------------------------------

void LApp::showSystemError(char *filename, int err)
{
  char title[256], msg[1024];
  char *error = NULL;
  
  error = strerror(err);
  if(error == NULL)
    error = "strerror failed";
  msgCat->getMsg( title, ERROR_TITLE );
  msgCat->getMsg( msg, ERROR_SYSTEM, filename, error);
  if(inAutoSave)
    puts(msg);
  else
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
}

    
// -------------------------------------------
//       setAutoSaveSeconds()
// -------------------------------------------


void LApp::setAutoSaveSeconds(unsigned int s)
{
  autoSaveSeconds = s;
  XtAppContext context = XtWidgetToApplicationContext(LicView::getTopLevel());
  if(autoSaveTimer)
    XtRemoveTimeOut(autoSaveTimer);
  if(autoSaveSeconds && autoSavingOn)
    autoSaveTimer = XtAppAddTimeOut(context,  autoSaveSeconds * 1000,
				    autoSaveTimeout, this);
}


// -------------------------------------------
//       setAutoSavePath()
// -------------------------------------------

void 
LApp::setAutoSavePath(char *p)
{
  if(autoSavePath)
    delete autoSavePath;
  autoSavePath = new char[strlen(p)+1];
  strcpy(autoSavePath, p);
}

// -------------------------------------------
//       autoSaveTimeout()
// -------------------------------------------

void LApp::autoSaveTimeout(XtPointer client_data, XtIntervalId *)
{
  LApp *self = (LApp*)client_data;
  self->autoSaveTimer = 0;

  self->saveOptions();

  switch(fork()) {
  case 0:
    self->autoSave();
    _exit(0);
    break;
  case -1:
    perror("fork");
    break;
  default:
    self->setAutoSaveSeconds(self->autoSaveSeconds);
  }
}

// -------------------------------------------
//       autoSave()
// -------------------------------------------

void LApp::autoSave()
{
  char path[PATH_MAX];
  char mytime[64];
  char buf[256];
  time_t t;
  struct tm *tm;
  Boolean success;

  inAutoSave = TRUE;             // set the auto save flag

  strcpy(path, autoSavePath);

  char base[strlen(project->getFilename())+1];
  strcpy(base, project->getFilename());
  getBasename(base);
  strcat(path, "/");
  strcat(path, base);
  success = project->save(path);

  t = time(NULL);
  tm = localtime(&t);
  strftime(mytime, sizeof(mytime), "%H:%M:%S", tm);
  
  if(success) {
    msgCat->getMsg(buf, AUTOSAVING_DONE, path, mytime);
  } else {
    msgCat->getMsg(buf, AUTOSAVING_ERROR, path, mytime);
  }
  puts(buf);

  inAutoSave = FALSE;         // reset the auto save flag
}


// -------------------------------------------
//       exit()
// -------------------------------------------

void 
LApp::exit()
{
  LicView::closeAllOpenViews();
  saveOptions();
  if(!normalQuit)
    autoSave();
  delete project;
  ::exit(0);
}

// -------------------------------------------
//       getVersionControl()
// -------------------------------------------

Boolean 
LApp::getVersionControl()
{
  if(inAutoSave)
    return FALSE;
  return versionControl;
}

// -------------------------------------------
//       LangInfo()
// -------------------------------------------

LangInfo::LangInfo(FILE *fp)
{
  char w[32];
  int ret = fscanf(fp, "%s%s%s", langName, implementationSuffix, w);
  if(ret != 3) {
    langName[0] = 0;
  }
  if(!strcmp(w, "TRUE") || !strcmp(w, "True") || !strcmp(w, "true")) {
    withLibLac = TRUE;
  } else {
    withLibLac = FALSE;
  }
}
