/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lproject.C,v $
 *  $Date: 1999/08/27 15:31:18 $
 *  $Revision: 1.2.2.2 $
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
 * $Log: Lproject.C,v $
 * Revision 1.2.2.2  1999/08/27 15:31:18  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.2.2.1  1998/07/01 18:31:43  lazy
 * Patches gcc 2.8
 *
 * Revision 1.2  1998/05/13 15:57:11  lazy
 * Xfe Integration complete
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:27  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:27:13  lazy
 * Initial revision
 *
 */

/* --------------------------------------------------------------------
   (C) Dirk Laessig 1994

   Lproject - Ein Projekt im LIC

   Linterface - Ein Interfaces eines Projektes

   --------------------------------------------------------------------*/

#include "Lproject.h"
#include "Lwidget.h"
#include "Lcreator.h"
#include "Lwhere.h"
#include "LresEditor.h"
#include "lic.h"
#include "Lpalette.h"
#include "Ltmpl.h"
#include "InterfaceInfo.h"
#include "misc.h"
#include "WidBrowseView.h"
#include "VersionControl.h"

#include <lac/IconView.h>
#include <lac/Model.h>
#include <lac/View.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Shell.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>

// #######################################################
//
// Class Lproject
//
// #######################################################

#define UNTITLED          "Untitled.prj"
#define DEFAULT_LANG      "c"
#define IMAKEFILE_TMPL    "Imakefile.tmpl"
#define MAINPROGRAMM_TMPL "main.tmpl"
#define GROBAL_RES_TMPL   "global_res.tmpl"
#define DEFAULT_INTERFACE_NAME "View"
#define DEFAULT_HELPFILE  "lic.hlp"

#define DEFAULT_RESOURCES \
"*dragReceiverProtocolStyle: DRAG_PREFER_DYNAMIC\n"\
"*dragInitiatorProtocolStyle: DRAG_PREFER_DYNAMIC\n"\
"*MLXHelp*Box.labelFontList: -adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1\n"\
"*MLXHelp*titleLabel.labelString:	Title:\n"\
"*MLXHelp*contentsDialog.dialogTitle:	Contents\n"\
"*MLXHelp.title: 			Help System\n"\
"*MLXHelp*Exit.labelString: 		Close\n"\
"*Popupmenu.MenuEdit.labelString:	Menu Editor\n"



Lproject *Lproject::currentProject;

// ---------------------------
//   Konstruktor
// ---------------------------

Lproject::Lproject(char *filename, YResult *parsed)
{
  currentProject = this;
  
  applClass[0] = 0;
  execFile[0] = 0;

  moreSource = new char[1];
  moreSource[0] = 0;
  extraCCOptions = new char[1];
  extraCCOptions[0] = 0;
  extraLDOptions = new char[1];
  extraLDOptions[0] = 0;
  extraLibraries = new char[1];
  extraLibraries[0] = 0;
  description = new char[1];
  description[0] = 0;
  globalResources = new char[1];
  globalResources[0] = 0;

  lang = app->getLang(DEFAULT_LANG);
  strcpy(helpfile, DEFAULT_HELPFILE);
  strcpy(sourcePath, app->getStartupDir());

  startupInterface = NULL;
  resources = new char[4096];
  // We need resources for popup menus in WYSIWYG views
  msgCat->getMsg(resources, DEFAULT_WYSIWYG_RESOURCES);

  programName = "test";
  topLevel = (Widget)NULL;
  unspecFilename = TRUE;

  if( !filename ) {
    setFilename(UNTITLED);
  } else {
    char sd[PATH_MAX];
    setFilename(filename);
    getPath(filename, sd, sizeof(sd));
    if(sd[0]) {     // full qualified file name
      strcpy(sourcePath, sd);
      if(sourcePath[strlen(sourcePath)-1] == '/')  // throw the slash away
	sourcePath[strlen(sourcePath)-1] = 0;
    }
  }

  // Setup default values

  strcpy(applClass, file);           
  getBasename(applClass);
  withoutSuffix(applClass);
  applClass[0] = toupper(applClass[0]);

  strcpy(execFile, file);
  getBasename(execFile);
  withoutSuffix(execFile);
  execFile[0] = tolower(execFile[0]);

  if(parsed) {

    // get information for project file
    if( parsed->helpfile[0] ) {
      char fName[PATH_MAX];
      getPath(file, fName, PATH_MAX);
      strcat(fName,parsed->helpfile);
      strcpy(helpfile, fName);
    } 
    if( parsed->global_resources ) {
      setGlobalResources(parsed->global_resources);
    }

    if( parsed->sourcedir[0] ) {
      strcpy(sourcePath, parsed->sourcedir);
    }
    if(parsed->exec_file[0])
      setExecFile(parsed->exec_file);
    if(parsed->more_source)
      setMoreSource(parsed->more_source);
    if(parsed->extra_cc_options)
      setExtraCCOptions(parsed->extra_cc_options);
    if(parsed->extra_ld_options)
      setExtraLDOptions(parsed->extra_ld_options);
    if(parsed->extra_libraries)
      setExtraLibraries(parsed->extra_libraries);
    if(parsed->description)
      setDescription(parsed->description);

  }

  // We have enough information to create the new display for
  // WYSIWYG view

  if(parsed && parsed->appl_class[0]) {
    setApplClass(parsed->appl_class);      // Calls updateToplevel()
  } else {
    setApplClass(applClass);               // Calls updateToplevel()
  }

  if( parsed ) {
    YInterface *inter;
    Linterface *linter;

    // For all interfaces belonging to this project
    for( inter=parsed->first_interface; inter; inter = inter->next ) {
      linter = addInterface(inter);

      // Display the interface if necessary
      if(linter && app->getShowInterfaceAfterLoad()) {
       	linter->show();
      }
    }

    if( parsed->startup[0] ) {
      linter = getInterface(parsed->startup);
      if(linter)
	startupInterface = linter;
    }
    if( parsed->palette[0] ) {
      char fName[PATH_MAX];
      getPath(file, fName, PATH_MAX);
      strcat(fName,parsed->palette);
      //lpalette = new Lpalette(fName);
    } //else
    //lpalette = new Lpalette();

    if( parsed->lang[0] ) {
      LangInfo *l = app->getLang(parsed->lang);
      if(l) {
	lang = l;
      }	else {
	fprintf(stderr,"Fatal error: Undefined programming language '%s'\nin project file.\n", parsed->lang);
      }
    }
  }
}

// -------------------------
//    Destructor
// ------------------------
Lproject::~Lproject() 
{
  Display *display;

  if(!isUnspecFilename()) {
    closeFileHook(getFilename());
  }

  while( interfaces.getSize() )
    delete interfaces[0];

  display = XtDisplay(topLevel);
  // XtDestroyWidget(topLevel);
  //  XtCloseDisplay(display);

  topLevel = NULL;
  currentProject = NULL;

  delete resources;
  delete description;
  delete moreSource;
  delete extraCCOptions;
  delete extraLDOptions;
}

// -------------------------
//    updateTopLevel()
// ------------------------

void Lproject::updateTopLevel()
{
  RefArray<Linterface> shownViews;

  if(!mlxHelp.isNil())
    mlxHelp.Delete();
  
  if(topLevel) {
    for( unsigned int i=0; i<interfaces.getSize(); i++) {
      if(interfaces[i]->isShown())
	shownViews.add(interfaces[i]);
      interfaces[i]->destroyView();
    }
    // XtDestroyWidget(topLevel);     DANGER !
    // XtCloseDisplay(XtDisplay(topLevel));
  }
  
  int argc = 1;
  char **argv = new char*[1];
  argv[0] = new char[strlen(execFile)+1];
  strcpy(argv[0], execFile);

  char *applClass = new char[strlen(this->applClass)+1];
  strcpy(applClass, this->applClass);

  char *default_resources 
    = new char[strlen(resources)+1+strlen(globalResources)+1];
  strcpy(default_resources, resources);
  strcat(default_resources, "\n");
  strcat(default_resources, globalResources);

  topLevel = LicView::init(applClass, argc, argv, default_resources);


  if(helpNode.isNil()) {
    XrmDatabase data, file;
    file = XrmGetFileDatabase(helpfile);
    data = XrmGetDatabase(XtDisplay(topLevel));
    
    XrmCombineDatabase(file, &data, TRUE);
    Widget dummy = XtVaCreateWidget("MLXHelp", 
				    xmPushButtonWidgetClass, topLevel, NULL);
    helpNode = new HelpNode(dummy);
  }

  for( unsigned int i=0; i<shownViews.getSize(); i++) {
    shownViews[i]->show();
  }
}
  
// ------------------------
//     find()
// ------------------------
 
Lwidget *Lproject::find( Window id )
{
  Lwidget *ret;

  for(unsigned int i=0; i<interfaces.getSize(); i++) {
    if( (ret = (interfaces[i]->getShell()->find( id ))) != NULL )
      return ret;
  }
  return NULL;
}

// ------------------------
//     setFilename()
// ------------------------
 
void Lproject::setFilename(char *newFilename)
{
  unsigned int len;
  Boolean withSlash = FALSE;

  if(newFilename)
    strcpy(file, newFilename);
  else
    strcpy(file, UNTITLED);

  // test file name

  len = strlen(file);

  for(unsigned int i=0; i<len; i++) {
    if(file[i] == ' ' || file[i] == '$' || 
       file[i] == '(' || file[i] == ')' ||
       file[i] == ':') {
      
      file[i] = '_';
    } else if (file [i] == '/') {
      withSlash = TRUE;
    }
  }
  if(withSlash) {
    unspecFilename = FALSE;
  } else {
    unspecFilename = TRUE;
  }
}

// ------------------------
//     save()
// ------------------------
 
Boolean Lproject::save( char *fname )
{
  char filename[PATH_MAX];
  char path[PATH_MAX];
  Boolean ret = TRUE;

  if( fname == NULL || fname[0]==0 )
    strcpy(filename, file);
  else {
    if( fname[strlen(fname)-1]=='/' ) {
      strcpy(filename,fname);
      strcat(filename,file);
    } else
      strcpy(filename, fname);
    withSuffix(filename, sizeof(filename), "prj");
    setFilename(filename);
  }
  getPath(filename, path, PATH_MAX);

  YInterface *lastInterface = NULL;

  YResult *toWrite = (YResult*)malloc(sizeof(YResult));
  memset( toWrite, 0, sizeof(YResult));

  for( unsigned int i=0; i<interfaces.getSize(); i++) {

    YInterface *yInterface = (YInterface*)malloc(sizeof(YInterface));
    memset( yInterface, 0, sizeof(YInterface) );
    strcpy( yInterface->filename, interfaces[i]->getName());
    withSuffix( yInterface->filename, sizeof(yInterface->filename), "i");

    if( !lastInterface ) {
      toWrite->first_interface = yInterface;
    } else {
      lastInterface->next = yInterface;
    }
    lastInterface = yInterface;
    
    if(!interfaces[i]->save(path))  // save interface in separate file
      ret = FALSE; 
  }
  strcpy( toWrite->lang, lang->getName() );
  if(!startupInterface.isNil())
    strcpy( toWrite->startup, startupInterface->getName() );

  strcpy(toWrite->sourcedir, sourcePath);
  strcpy(toWrite->appl_class, applClass);
  strcpy(toWrite->exec_file, execFile);
  m_strcpy(&toWrite->more_source, moreSource);
  m_strcpy(&toWrite->extra_cc_options, extraCCOptions);
  m_strcpy(&toWrite->extra_ld_options, extraLDOptions);
  m_strcpy(&toWrite->extra_libraries, extraLibraries);
  m_strcpy(&toWrite->description, description);
  m_strcpy(&toWrite->global_resources, globalResources);


  int error;

  error = createPath(filename);
  if(error) {
    app->showSystemError(filename, error);
    ret = FALSE;
  } else {
    if( (error = writeFile( filename, toWrite ))) {
      app->showSystemError(filename, error);
      ret = FALSE;
    } else {
      saveFileHook(filename);
    }
  }
  free_YResult( toWrite );

  if(ret)
    resetChangedFlag();
  return ret;
}

// --------------------------------
//       addInterface()
// --------------------------------

Linterface *Lproject::addInterface(YInterface *yInterface)
{
  Linterface *ret = NULL;
  char filename[PATH_MAX];
  char basename[PATH_MAX];
  YResult *result;

  if( yInterface ) {
    getPath(file, filename, PATH_MAX);
    strcpy(basename,yInterface->filename);
    getBasename(basename);
    strcat(filename, basename);
    openFileHook(filename);
    result = parse(filename);
    if( result ) {
      if(result->error) {
	app->showSystemError(filename, result->error);
      }
      if( result->root_widget ) {
	ret = new Linterface( result->root_widget );
      }
      free_YResult( result );
    }
  } 
  if( ret ) {
    interfaces.add(ret);
    if(interfaces.getSize() == 1) {
      startupInterface = ret;
    }
//    interfaces.changed(CONTAINER_CHANGED);
  }
  return ret;
}

// --------------------------------
//       addInterface()
// --------------------------------

Linterface *Lproject::addInterface(Lcreator *shellClass)
{
  Linterface *ret;

  ret = new Linterface( shellClass );
  
  if( ret ) {
    interfaces.add(ret);
    if(interfaces.getSize() == 1) {
      startupInterface = ret;
    }
    interfaces.changed(CONTAINER_CHANGED);
  }
  return ret;
}

// --------------------------------
//       addInterface()
// --------------------------------

Linterface *Lproject::addInterface(Linterface *interface)
{
  Linterface *ret;

  ret = interface;
  
  if( ret ) {
    interfaces.add(ret);
    if(interfaces.getSize() == 1) {
      startupInterface = ret;
    }
    interfaces.changed(CONTAINER_CHANGED);
  }
  return ret;
}

// --------------------------------
//       existNamedInterface()
// --------------------------------

Boolean Lproject::existNamedInterface( char *name )
{
  for( unsigned int i=0; i<interfaces.getSize(); i++)
    if( !strcmp( interfaces[i]->getName(),name) )
      return TRUE;
  return FALSE;
}


// --------------------------------
//       getInterface(Lwidget*)
// --------------------------------

Linterface *Lproject::getInterface( Lwidget *shell )
{
  for( unsigned int i=0; i<interfaces.getSize(); i++ )
    if( interfaces[i]->getShell() == shell ) 
      return interfaces[i];
  return NULL;
}

// --------------------------------
//       getInterface(char*)
// --------------------------------

Linterface *Lproject::getInterface( char *name )
{
  for( unsigned int i=0; i<interfaces.getSize(); i++ )
    if( !strcmp(interfaces[i]->getName(),name) ) 
      return interfaces[i];
  return NULL;
}


// --------------------------------
//       getChangedFlag()
// --------------------------------
Boolean Lproject::getChangedFlag()
{
  if(Model::getChangedFlag())
    return TRUE;
  if(interfaces.getChangedFlag())
    return TRUE;
  return FALSE;
}


// --------------------------------
//       resetChangedFlag()
// --------------------------------
void Lproject::resetChangedFlag()
{
  Model::resetChangedFlag();
  interfaces.resetChangedFlag();
}


// --------------------------------
//       getStartupInterface()
// --------------------------------

Linterface *Lproject::getStartupInterface()
{
  if(startupInterface.isNil())
    return NULL;
  return startupInterface;
}

// --------------------------------
//       setStartupInterface()
// --------------------------------

void Lproject::setStartupInterface(Linterface *linterface)
{
  startupInterface = linterface;
}

// --------------------------------
//       generate()
// --------------------------------

Boolean Lproject::generate(Boolean generateInterfaces,
			   Boolean overwriteStubs, 
			   Boolean imakefile,
			   Boolean mainprogramm,
			   RefArray<Lfile> &overwriteFiles,
			   char *path)
{
  Boolean ret = TRUE;
  char msg[1024];
  char tmplPath[PATH_MAX];
  char fileName[PATH_MAX];
  LangInfo *li = lang;

  char objects[256*interfaces.getSize()+strlen(moreSource)+1];
  char sources[256*interfaces.getSize()+strlen(moreSource)+1];
  char resourceFiles[256*interfaces.getSize()];
  char projectName[PATH_MAX];

  strcpy(projectName, execFile);
  getBasename(projectName);
  changeSuffix(projectName, sizeof(projectName), "o");
  strcpy(objects, projectName);
  changeSuffix(projectName, sizeof(projectName), li->getSuffix());
  strcpy(sources, projectName);
  withoutSuffix(projectName);

  resourceFiles[0]=0;

  if(generateInterfaces) {
    for( unsigned i=0; i<interfaces.getSize(); i++ ) {
      ret = ret && interfaces[i]->generate(lang->getName(), overwriteStubs, overwriteFiles, path);
    }
  }    
  for( unsigned i=0; i<interfaces.getSize(); i++ ) {
    char interfaceName[256];
    strcpy(interfaceName, interfaces[i]->getName());
    
    changeSuffix(interfaceName, sizeof(interfaceName), "o");
    strcat(objects, " ");
    strcat(objects, interfaceName);
    changeSuffix(interfaceName, sizeof(interfaceName), "rf");
    strcat(resourceFiles, " ");
    strcat(resourceFiles, interfaceName);
    changeSuffix(interfaceName, sizeof(interfaceName), li->getSuffix());
    strcat(sources, " ");      
    strcat(sources, interfaceName);

    withoutSuffix(interfaceName);
    strcat(interfaceName, "_base");

    changeSuffix(interfaceName, sizeof(interfaceName), "o");
    strcat(objects, " ");
    strcat(objects, interfaceName);
    changeSuffix(interfaceName, sizeof(interfaceName), li->getSuffix());
    strcat(sources, " ");      
    strcat(sources, interfaceName);
  }

  strcat(sources, " ");                      // add to sources
  strcat(sources, moreSource);

  char msTmp[strlen(moreSource)+1];         // add to objects
  strcpy(msTmp, moreSource);
  char *tok = strtok(msTmp, " ");
  while(tok) {
    char obj[PATH_MAX];
    strcpy(obj, tok);
    changeSuffix(obj, sizeof(obj), "o");
    strcat(objects, " ");
    strcat(objects, obj);
    tok = strtok(NULL, " ");
  }

  if( imakefile ) {
    strcpy(tmplPath, app->getConfigPath() );   
    strcat(tmplPath, "/" );
    strcat(tmplPath, lang->getName() );
    strcat(tmplPath, "." );
    strcat(tmplPath, IMAKEFILE_TMPL ); 

    Ltmpl tmpl(tmplPath);
    if( !tmpl.getText() ) {
      msgCat->getMsg(msg, CANT_OPEN_FILE, tmplPath);
      fprintf(stderr,"%s\n",msg);
      ret = FALSE;
    } else {

      tmpl.insertVariable("HOME", app->getHomePath());
      tmpl.insertVariable("RESOURCEFILES", resourceFiles);
      tmpl.insertVariable("OBJECTS", objects);
      tmpl.insertVariable("SOURCES", sources);
      tmpl.insertVariable("PROGRAM", execFile);
      tmpl.insertVariable("APPL_CLASS", applClass);
      tmpl.insertVariable("DESCRIPTION", description);
      tmpl.insertVariable("EXTRA_CC_OPTIONS", extraCCOptions);
      tmpl.insertVariable("EXTRA_LD_OPTIONS", extraLDOptions);
      tmpl.insertVariable("EXTRA_LIBRARIES", extraLibraries);
      
      strcpy(fileName, getSourcePath());
      if(fileName[strlen(fileName)-1] != '/')
	strcat(fileName, "/");
      strcat(fileName, "Imakefile");
      overwriteFiles.add( new Lfile(tmpl, fileName, 
				    TRUE, FILE_CLASS_IMAKEFILE));
    }
  }

  if( mainprogramm ) {
    strcpy(tmplPath, app->getConfigPath() );   
    strcat(tmplPath, "/" );
    strcat(tmplPath, lang->getName() );
    strcat(tmplPath, "." );
    strcat(tmplPath, MAINPROGRAMM_TMPL ); 

    Ltmpl tmpl(tmplPath);

    if( !tmpl.getText() ) {
      msgCat->getMsg(msg, CANT_OPEN_FILE, tmplPath);
      fprintf(stderr,"%s\n",msg);
      ret = FALSE;
    } else {

      tmpl.insertVariable("HOME", app->getHomePath());
      tmpl.insertVariable("OBJECTS", objects);
      tmpl.insertVariable("SOURCES", sources);
      tmpl.insertVariable("RESOURCEFILES", resourceFiles);
      if(!startupInterface.isNil())
	tmpl.insertVariable("STARTUP", startupInterface->getName());
      tmpl.insertVariable("APPL_CLASS", applClass);
      tmpl.insertVariable("PROGRAM", execFile);
      tmpl.insertVariable("DESCRIPTION", description);
      tmpl.insertVariable("EXTRA_CC_OPTIONS", extraCCOptions);
      tmpl.insertVariable("EXTRA_LD_OPTIONS", extraLDOptions);
      tmpl.insertVariable("EXTRA_LIBRARIES", extraLibraries);
      
      char buf[strlen(file)+1];
      strcpy(buf, execFile);
      getBasename(buf);
      changeSuffix(buf, strlen(file)+1, li->getSuffix());

      strcpy(fileName, getSourcePath());
      if(fileName[strlen(fileName)-1] != '/')
	strcat(fileName, "/");
      strcat(fileName, buf);
      overwriteFiles.add( new Lfile(tmpl, fileName, TRUE, 
				    FILE_CLASS_MAIN_PROGRAM));
    }
  }

  strcpy(tmplPath, app->getConfigPath() );   
  strcat(tmplPath, "/" );
  strcat(tmplPath, lang->getName() );
  strcat(tmplPath, "." );
  strcat(tmplPath, GROBAL_RES_TMPL ); 

  Ltmpl tmpl(tmplPath);

  if( !tmpl.getText() ) {
    msgCat->getMsg(msg, CANT_OPEN_FILE, tmplPath);
    fprintf(stderr,"%s\n",msg);
    ret = FALSE;
  } else {
    tmpl.insertVariable("HOME", app->getHomePath());
    tmpl.insertVariable("OBJECTS", objects);
    tmpl.insertVariable("SOURCES", sources);
    tmpl.insertVariable("RESOURCEFILES", resourceFiles);
    tmpl.insertVariable("GLOBAL_RESOURCES", globalResources);
    if(!startupInterface.isNil())
      tmpl.insertVariable("STARTUP", startupInterface->getName());
    tmpl.insertVariable("APPL_CLASS", applClass);
    tmpl.insertVariable("PROGRAM", execFile);
    tmpl.insertVariable("DESCRIPTION", description);
    tmpl.insertVariable("EXTRA_CC_OPTIONS", extraCCOptions);
    tmpl.insertVariable("EXTRA_LD_OPTIONS", extraLDOptions);
    tmpl.insertVariable("EXTRA_LIBRARIES", extraLibraries);
      
    char buf[PATH_MAX];
    strcpy(buf, applClass);
    getBasename(buf);
    changeSuffix(buf, PATH_MAX, "rf");

    strcpy(fileName, getSourcePath());
    if(fileName[strlen(fileName)-1] != '/')
      strcat(fileName, "/");
    strcat(fileName, buf);
    overwriteFiles.add( new Lfile(tmpl, fileName, TRUE, 
				  FILE_CLASS_GLOBAL_RESOURCES));
  }

  return ret;
}


// ----------------------------
//   getHelp()
// ----------------------------
void Lproject::getHelp(int id)
{
  if(mlxHelp.isNil()) {
    mlxHelp = new MLXHelp(helpfile, topLevel, helpNode);
  }
  mlxHelp->open();
  mlxHelp->find(id);
}

// #######################################################
//
// Class Linterface
//
// #######################################################


// static member
Cardinal Linterface::count;

// ----------------------------
//   Konstuktor
// ----------------------------

Linterface::Linterface(Lcreator *shellClass )
:Iconable(), shell(NULL,this)
{
  char new_name[256];
  isDeleted = FALSE;
  x = -1;
  y = -1;
  width = height = 0;
  trick = correctionInit = FALSE;
  correctX = correctY = 0;
  isSaved = FALSE;

  sprintf(new_name,"Interface_%d",++count);
  while(getProject()->existNamedInterface( new_name ) )
    sprintf(new_name,"Interface_%d",++count);
    
  if( shellClass )
    shell = new Lwidget(shellClass,
			new_name, Lwhere() );
  else
    shell = new Lwidget(Lcreator::getDefaultShell(),
			new_name, Lwhere() );
  
  name = new char[strlen( new_name )+1];
  strcpy( name, new_name );
}
  
// -------------------------------------------------
//     Load Interface from a separate file
// -------------------------------------------------

Linterface::Linterface( YWidget *yWidget )
: Iconable(), shell(NULL,this)
{
  isDeleted = FALSE;
  x = -1;
  y = -1;
  width = height = 0;
  trick = correctionInit = FALSE;
  correctX = correctY = 0;
  isSaved = TRUE;

  if(yWidget) {
    shell = new Lwidget( yWidget );
  } else {
    fprintf(stderr, "Fatal error: yWidget is zero\n");
  }
  
  if( shell.isNil() ) {
    name = new char[strlen(DEFAULT_INTERFACE_NAME)+1];
    strcpy(name, DEFAULT_INTERFACE_NAME);
  } else {
    name = new char[strlen(shell->getName())+1];
    strcpy(name, shell->getName());
  }
}


// -------------------------------------------------
//     Destruktor
// -------------------------------------------------

Linterface::~Linterface()
{
  if(isSaved && !shell.isNil()) {
    char filename[PATH_MAX];
    
    getPath(getProject()->getFilename(), filename, sizeof(filename));
    strcat(filename, getName());
    withSuffix(filename, sizeof(filename), "i" );
    
    closeFileHook(filename);
  }

  isDeleted = TRUE;
  if(!shell.isNil())
    shell.Delete();
  delete name;
}

// --------------------------------
//       getChangedFlag()
// --------------------------------
Boolean Linterface::getChangedFlag()
{
  if(Model::getChangedFlag())
    return TRUE;
  if(shell->getChangedFlag())
    return TRUE;
  return FALSE;
}


// --------------------------------
//       resetChangedFlag()
// --------------------------------
void Linterface::resetChangedFlag()
{
  Model::resetChangedFlag();
  shell->resetChangedFlag();
}


// ----------------------------------------
//           getName()
// ----------------------------------------

char *Linterface::getName()
{ 
  if(shell.isNil()) {
    return NULL;
  }
  return shell->getName(); 
}


// ----------------------------------------
//           setName()
// ----------------------------------------

Boolean Linterface::setName(char *n)
{ 
  if(shell.isNil())
    return False;
  return shell->setName(n); 
}

// ----------------------------------------
//           show()
// ----------------------------------------

void Linterface::show()
{
  if( wysiwyg.isNil() ) {
    wysiwyg = new InterfaceView( getProject()->getTopLevel(), this );
    if( wysiwyg->getShell() ) {
      wysiwyg->getShell()->setRelation();
      wysiwyg->getShell()->manageDialogs();
    }
  }
  wysiwyg->newPopupShell(wysiwyg->getShell()->getWidget());

  if(x>=0 && y>=0)
    wysiwyg->moveTo(x, y);

  if( shell->getChildren().getSize()==0 )
    if(width>0 && height>0)
      wysiwyg->setSize(width,height);

  wysiwyg->open();
}
  
// ----------------------------------------
//           hide()
// ----------------------------------------

void Linterface::hide()
{
  if( !wysiwyg.isNil() ) {
    if(wysiwyg->getShell()->getWidget()) {
      XtVaGetValues(wysiwyg->getShell()->getWidget(),
		    XmNx, &x,
		    XmNy, &y,
		    NULL);
    }
    wysiwyg->close();
    wysiwyg.Delete();
  }
}


// ----------------------------------------
//           destroyView()
// ----------------------------------------

void Linterface::destroyView()
{
  wysiwyg.Delete();
}

// ----------------------------------------
//       moveTo()
// ----------------------------------------

void Linterface::moveTo( Position x, Position y, Boolean fromConfigure )
{
  if(fromConfigure && !correctionInit) {     // das erste ConfigureNotify
    correctionInit = TRUE;
//    correctX = this->x - x;
//    correctY = this->y - y;
//    printf("correct(%d,%d)\n", correctX, correctY);
  }
  if( (this->x < 0 && this->y < 0) || fromConfigure ) {
    this->x = x;
    this->y = y;
  }
  x = this->x + correctX;
  y = this->y + correctY;
  if( !wysiwyg.isNil() && !fromConfigure ) {
    printf("move(%d,%d)\n", x, y);
    wysiwyg->moveTo(x,y);
  }
}

// ----------------------------------------
//     setSize()
// ----------------------------------------

void Linterface::setSize(Dimension w, Dimension h )
{
  width = w;
  height = h;
}

// ----------------------------------------
//           getProject()
// ----------------------------------------

Lproject *Linterface::getProject()
{
  return &Lproject::current();
}

// ----------------------------------------
//           save()
// ----------------------------------------

Boolean Linterface::save( char *f )
{
  char filename[PATH_MAX];

  if(f==NULL) {
    getPath(getProject()->getFilename(), filename, sizeof(filename));
    strcat(filename, getName());
  } else {
    if( f[0]==0 ) {
      strcpy( filename, getName() );
    } else {
      if( f[strlen(f)-1] == '/') {
	strcpy( filename, f );
	strcat( filename, getName() );
      } else 
	strcpy( filename, f );
    }
  }
  withSuffix(filename, sizeof(filename), "i" );

  YWidget *yWidget = shell->createYWidget();
  YResult *toWrite = (YResult*)malloc(sizeof(YResult));
  memset( toWrite, 0, sizeof(YResult));
  toWrite->root_widget = yWidget;

  if(app->isDemo() && shell->countSubTree() > DEMO_MAX_WIDGETS) {
    char msg[1024];

    msgCat->getMsg(msg, DEMO_ERROR, filename);
    fprintf(stderr,"%s\n",msg);

    free_YResult( toWrite );
    return FALSE;
  } else {
    int error;

    error = createPath(filename);
    if(error) {
      app->showSystemError(filename, error);
      free_YResult( toWrite );
      return FALSE;
    }
    if( (error = writeFile( filename, toWrite ))) {
      app->showSystemError(filename, error);
      free_YResult( toWrite );
      return FALSE;
    }
    saveFileHook(filename);
  }
  free_YResult( toWrite );
  resetChangedFlag();
  isSaved = TRUE;
  return TRUE;
}


// ----------------------------------------
//      existNamedWidget()
// ----------------------------------------

Boolean Linterface::existNamedWidget( char *aName )
{
  return shell->existNamedWidget( aName );
}


// -------------------------------
//        getPixmapFile()
// -------------------------------

char *Linterface::getPixmapFile()
{
  if( !shell.isNil() ) {
    return shell->getClass()->getPixmapFile();
  }
  return Iconable::getPixmapFile();
}

// ------------------------------
//      delNotify()
// ------------------------------
void Linterface::delNotify( BaseRef *toDel )
{
  if( (&shell == toDel) && !isDeleted )
    delete this;
}

// ------------------------------
//   generate()
// ------------------------------

Boolean Linterface::generate(char *lang, Boolean overwriteStubs, 
			     RefArray<Lfile> &overwriteFiles, char *)
{
  FILE *langFp;
  char msg[1024];
  char tmplPath[PATH_MAX];
  char fileName[PATH_MAX];
  char langFile[PATH_MAX];
  char firstTmpl[PATH_MAX], base[PATH_MAX], ext[PATH_MAX];
  char query[10];

  if(app->isDemo() && shell->countSubTree() > DEMO_MAX_WIDGETS) {
    char msg[1024];

    msgCat->getMsg(msg, DEMO_GEN_ERROR, getName());
    fprintf(stderr,"%s\n",msg);
    return FALSE;
  }

  InterfaceInfo interfaceInfo( this );

  strcpy(langFile, app->getConfigPath());   // definition tmpl name
  strcat(langFile, "/");
  strcat(langFile, lang);
  strcat(langFile, ".tmpl");

  langFp = fopen(langFile, "r");
  if(!langFp) {
    msgCat->getMsg(msg, CANT_OPEN_FILE, langFile);
    fprintf(stderr,"%s\n",msg);
    return FALSE;
  }
  while( !feof(langFp) ) {
    fscanf(langFp, "%s", firstTmpl);
    if( feof(langFp) )
      break;

    fscanf(langFp, "%s%s%s", base, ext, query );
    
    strcpy(tmplPath, app->getConfigPath() );   // definition tmpl name
    strcat(tmplPath, "/" );
    strcat(tmplPath, firstTmpl );
    
    Ltmpl tmpl(tmplPath);                       // definition template
    if( !tmpl.getText() ) {
      msgCat->getMsg(msg, CANT_OPEN_FILE, tmplPath);
      fprintf(stderr,"%s\n",msg);
      fclose( langFp );
      return FALSE;
    }

    if( base[0] != '>' ) {
      interfaceInfo.fillout(&tmpl); 
      strcpy(fileName, app->getProject()->getSourcePath());
      if(fileName[strlen(fileName)-1] != '/')
	strcat(fileName, "/");
      strcat( fileName, getName() );             // write the file
      if( base[0] != '*' )
	strcat( fileName, base );
      strcat( fileName, "." );
      strcat( fileName, ext );
    } else {                                     // direkte Kopie
      strcpy(fileName, app->getProject()->getSourcePath());
      if(fileName[strlen(fileName)-1] != '/')
	strcat(fileName, "/");
      strcat( fileName, ext );                   // Name steht in ext
    }
    if((overwriteStubs && query[0] == 'y') ||
       (query[0] != 'y')) {                 // only if we want staps
      Boolean exists = FALSE;
      for(unsigned int i=0; i < overwriteFiles.getSize(); i++) {
	if(!strcmp(overwriteFiles[i]->getFilename(), fileName)) {
	  exists = TRUE;
	  break;
	}
      }
      if(!exists)
	overwriteFiles.add( new Lfile(tmpl, fileName, query[0] == 'y',
				      FILE_CLASS_INTERFACE_SOURCE));
    }
  }
  
  fclose(langFp);
  return TRUE;
}



/* ###################################################
             InterfaceView
   ################################################### */

InterfaceView::InterfaceView( Widget top, Linterface *model )
:LicView(top, model), widgetView(NULL,this)
{
  inDelete = FALSE;
  interface = model;
  widgetView = new WidgetView( interface->getShell() );
  popupShell =  widgetView->getWidget();
}

// ------------------------------
//     ~InterfaceView()
// ------------------------------

InterfaceView::~InterfaceView()
{
  inDelete = TRUE;
  if(!widgetView.isNil())
    widgetView.Delete();
}

// ------------------------------
//     delNotify()
// ------------------------------

void InterfaceView::delNotify( BaseRef *toDel )
{
  if(inDelete)
    return;
  if( toDel == &widgetView ) {
    delete this;
  }
}

// ------------------------------
//     moveTo()
// ------------------------------

void InterfaceView::moveTo( Position x, Position y )
{
  if(widgetView->getWidget()) {
    XtVaSetValues(widgetView->getWidget(), 
		  XmNx, x,
		  XmNy, y,
		  XmNwinGravity, CenterGravity,
		  NULL);
  }
}

// ------------------------------
//     setSize
// ------------------------------

void InterfaceView::setSize(Dimension w, Dimension h )
{
  if(widgetView->getWidget())
    XtVaSetValues(widgetView->getWidget(),
		  XmNwidth, w,
		  XmNheight, h,
		  NULL);
}


// ------------------------------
//     getShell()
// ------------------------------

WidgetView *InterfaceView::getShell() 
{ 
  return widgetView; 
}

// ------------------------------
//     update()
// ------------------------------

void InterfaceView::update( unsigned long )
{

}


// ------------------------------
//     newPopupShell()
// ------------------------------

void InterfaceView::newPopupShell( Widget wg )
{
  popupShell = wg;
}


// ------------------------------
//   wmDelete()
// ------------------------------

void InterfaceView::wmDelete()
{
  interface->hide();
}


/* ###################################################
             InterfaceController
   ################################################### */

#define INTERFACE_SHOW   "Show"
#define INTERFACE_HIDE   "Hide"
#define INTERFACE_DELETE "Delete"
#define INTERFACE_SAVE   "Save"
#define INTERFACE_SAVEAS "SaveAs"
#define INTERFACE_CREATELINK "CreateLink"
#define INTERFACE_BROWSE  "InterfaceBrowse"
#define INTERFACE_GENERATE  "CodeGenerate"

InterfaceController::InterfaceController( Linterface *am, View *icon )
:Controller(am,icon)
{
  interface = am;
}

// ------------------------------
//       defaultAction()
// ------------------------------

void InterfaceController::defaultAction()
{
  interface->show();
}

// ------------------------------
//       act()
// ------------------------------

void InterfaceController::act(MenuEntry *me)
{
  char title[1024];
  char msg[1024];

  if(me->match(INTERFACE_SHOW)) {
    interface->show();
  }

  if(me->match(INTERFACE_HIDE)) {
    interface->hide();
  }

  if(me->match(INTERFACE_DELETE)) {
    msgCat->getMsg( title, QUERY_INTERFACE_DELETE_TITLE );
    msgCat->getMsg( msg, QUERY_INTERFACE_DELETE_MSG, interface->getName());
    if( MSGBOX_OK == LicView::MsgBox( title, msg, MSGBOX_STYLE_YESNO) )
      delete interface;
  }


  Boolean doSaveAs = FALSE;
  if(me->match(INTERFACE_SAVE)) {
    if(app->getProject()->isUnspecFilename()) {
      doSaveAs = TRUE;
    } else {
      if(interface->save()) {
	msgCat->getMsg(msg, INTERFACE_SAVE_SUCCESS);
	puts(msg);
      }
    }
  }

  if(me->match(INTERFACE_SAVEAS) || doSaveAs) {
    char f[PATH_MAX];
    msgCat->getMsg( title, INTERFACE_SAVE_TITLE );
    getcwd(f, PATH_MAX);
    if(f[strlen(f)-1] != '/') {
      strcat(f,"/");
    }
    strcat(f,interface->getName());
    strcat(f,".i");
    if( MSGBOX_OK == LicView::FileBox(title, f)) {
      if(interface->save(f)) {
	msgCat->getMsg(msg, INTERFACE_SAVE_SUCCESS);
	puts(msg);
      }
    }
  }

  if(me->match(INTERFACE_CREATELINK)) {
    Lwhere where(*interface->getProject(), (Boolean)FALSE);
    if(where.isCanceled())
      return;
    if( where.getparent() ) {                 // parent found
      Boolean notTheSame =                    // not in the same interface
	strcmp(where.getparent()->getInterface()->getName(),
	       interface->getName());
      if( notTheSame ) {                      // create it
	Lwidget *lw = new Lwidget(where.getparent(),
				  interface->getName(),"Link");
	lw->getProperties()->setResource( "x", where.getx() );
	lw->getProperties()->setResource( "y", where.gety() );
	where.getparent()->changed(CONTAINER_CHANGED);
      }
    }
  }

  if(me->match(INTERFACE_BROWSE)) {
    LicView::setWaitCursor(TRUE);
    WidBrowseView::showView(interface->getShell());
    LicView::setWaitCursor(FALSE);
  }

  if(me->match(INTERFACE_GENERATE)) {
    RefArray<Lfile> toWrite;      
    Boolean errorSeen = FALSE;
    
    LicView::setWaitCursor(TRUE);
    interface->generate(interface->getProject()->getLang()->getName(), 
			TRUE, toWrite);
    LicView::setWaitCursor(FALSE);

    // delete the generated files if exit

    RefArray<Lfile> toDelete;
    for(unsigned int i=0; i<toWrite.getSize(); i++) {
      if(toWrite[i]->getCareOverwrite() && toWrite[i]->fileExist()) {
	toDelete.add(toWrite[i]);
      }
    }
    while(toDelete.getSize())
      toDelete[0].Delete();

    // write the generated files

    for(unsigned int i=0; i<toWrite.getSize(); i++) {
      int ret;
      ret = toWrite[i]->write();
      if( ret != 0) {
	char buf[PATH_MAX];
	msgCat->getMsg(buf, WRITE_FILE_ERROR, toWrite[i]->getFilename(), 
		       strerror(ret));
	puts(buf);
	errorSeen = TRUE;
      } else {
	char buf[PATH_MAX];
	msgCat->getMsg(buf, FILE_WRITTEN, toWrite[i]->getFilename());
	puts(buf);
      }
    }
    if(errorSeen) {
      char title[256];
      char msg[1024];
      msgCat->getMsg(title, ERROR_TITLE);
      msgCat->getMsg(msg, ERROR_SEEN);
      LicView::MsgBox( title, msg, MSGBOX_STYLE_OK);
    }
  }
}


void InterfaceController::actOnce(MenuEntry *)
{

}

void InterfaceController::createMenuEntries()
{
  MenuEntry *me;

  me = new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_BROWSE, FALSE);
  me->setKeyBinding(0, "b");
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_SAVE, FALSE);
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_SAVEAS, FALSE);
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_CREATELINK,FALSE);
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_GENERATE, FALSE);
  entries.add(me);

  me =  new MenuEntry(this, ME_SEPARATOR, "Sep", FALSE);
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_SHOW, FALSE);
  me->setKeyBinding(0, "s");
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_HIDE, FALSE);
  me->setKeyBinding(0, "h");
  entries.add(me);

  me =  new MenuEntry(this, ME_SEPARATOR, "Sep", FALSE);
  entries.add(me);

  me =  new MenuEntry(this, ME_PUSHBUTTON, INTERFACE_DELETE, FALSE);
  me->setKeyBinding(0, "osfDelete");
  entries.add(me);
}


