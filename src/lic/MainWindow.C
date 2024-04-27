/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MainWindow.C,v $
 *  $Date: 1999/08/27 15:31:35 $
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
 * $Log: MainWindow.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:35  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.4  1998/03/30 19:08:34  lazy
 * *** empty log message ***
 *
 * Revision 1.3  1997/09/06  13:40:31  lazy
 * New global settings.
 *
 * Revision 1.2  1997/09/02  22:25:15  lazy
 * Global resources and openFileHook()
 *
 * Revision 1.1  1997/07/25  20:29:08  lazy
 * Initial revision
 *
 */


#include "MainWindow.h"

#include "lic.h"

#include <lac/Model.h>
#include <lac/View.h>
#include <lac/IconView.h>
#include <lac/TArray.h>

#include "Lproject.h"
#include "Lcreator.h"
#include "Lwidget.h"
#include "LApp.h"
#include "Lpalette.h"
#include "misc.h"
#include "TextEdit.h"
#include "LresEditor.h"
#include "TemplateView.h"
#include "ProjectSettings.h"
#include "GlobalResEditor.h"
#include "VersionControl.h"
#include "WidResEditor.h"

#include <Xm/Text.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/Scale.h>
#include <Xm/ToggleB.h>
#include <Xm/List.h>
#include <Xm/MessageB.h>

#include <lwid/Bubble.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>

#define READ_BUFFER_SIZE 256

#define MW_FILEOPEN "fileopen"
#define MW_FILESAVE "filesave"
#define MW_FILESAVEAS "filesaveas"
#define MW_FILEEXIT "fileexit"
#define MW_PROJECTNEW "projectnew"
#define MW_PROJECTSETTINGS "projectsettings"
#define MW_PROJECTPALETTE "projectpalette"
#define MW_PROJECTLOADINTERFACE "projectloadinterface"
#define MW_PROJECTGENERATE "projectgenerate"
#define MW_MESSAGECLEAR "messageclear"
#define MW_PRODUCTINFO "productInfo"
#define MW_SETDEFAULTSHELL "defaultShell"
#define MW_CREATEWIDGET "createWidget"
#define MW_TUTORIAL "tutorial"


#define VD_ICONBOX_HEIGHT "IconBoxHeight"
#define VD_PALETTE_OPEN "PaletteOpen"


RefArray<MainWindow> MainWindow::allViews;
pid_t MainWindow::current_pid = 0;
extern int rd_fd;

MainWindow::MainWindow(LApp *model)
{
  lApp = model;
  setModel(model);

  allViews.add(this);
  quickHelpLabel = quickHelp;

#ifndef WITHOUT_LAC
  XtManageChild(ProjectShowHelp);
#endif

  long boxHeight;
  if(lApp->getVDLong(this, VD_ICONBOX_HEIGHT, boxHeight)) {
    XtVaSetValues(ViewForm, XmNheight, boxHeight, NULL);
  }
  Boolean palOpen;
  if(lApp->getVDBoolean(this, VD_PALETTE_OPEN, palOpen)) {
    if(palOpen)
      showWidgetPalette(NULL, NULL);
  }
  
  XtVaCreateWidget("openBubble", xlBubbleWidgetClass, OpenIcon, NULL);
  XtVaCreateWidget("saveBubble", xlBubbleWidgetClass, SaveIcon, NULL);
  XtVaCreateWidget("templateBubble", xlBubbleWidgetClass, PaletteIcon, NULL);
  XtVaCreateWidget("productBubble", xlBubbleWidgetClass, ProductIcon, NULL);
  XtVaCreateWidget("paletteBubble", xlBubbleWidgetClass, WidgetPaletteIcon, NULL);
  XtVaCreateWidget("testModeBubble", xlBubbleWidgetClass, TestModeToggle, NULL);
  XtVaCreateWidget("execBubble", xlBubbleWidgetClass, ExecIcon, NULL);
  XtVaCreateWidget("generateBubble", xlBubbleWidgetClass, generateIcon, NULL);

  Lstring defShell = Lcreator::getDefaultShell()->getName();
  if(defShell == "ApplicationShell")
    XmToggleButtonSetState(applicationShellButton, TRUE, FALSE);
  else   if(defShell == "TopLevelShell")
    XmToggleButtonSetState(toplevelShellButton, TRUE, FALSE);
  else   if(defShell == "TransientShell")
    XmToggleButtonSetState(transientShellButton, TRUE, FALSE);
  else   if(defShell == "XmDialogShell")
    XmToggleButtonSetState(dialogShellButton, TRUE, FALSE);


  // Activate-Callbacks setzen
  // Die Methode MainWindow::act() wird von diesem
  // Callback aufgerufen, Parameter ist dabei der zweite
  // Parameter von addAction()

  addAction(FileSave, MW_FILESAVE);
  addAction(SaveIcon, MW_FILESAVE);
  addAction(FileExit, MW_FILEEXIT);
  addAction(ProjectNew, MW_PROJECTNEW);
  addAction(ProjectSettings, MW_PROJECTSETTINGS);
  //  addAction(ProjectPalette, MW_PROJECTPALETTE);
  addAction(PaletteIcon, MW_PROJECTPALETTE);
  addAction(ProjectLoadInterface, MW_PROJECTLOADINTERFACE);
  addAction(ProjectGenerate, MW_PROJECTGENERATE);
  addAction(MessageClearButton, MW_MESSAGECLEAR);
  addAction(HelpProduct, MW_PRODUCTINFO);
  addAction(ProductIcon, MW_PRODUCTINFO);
  addAction(HelpTutorial, MW_TUTORIAL);

  // Umleiten von Standard-Ausgabe und Standard-Error in
  // ein Textwidget
#if(0)
  int fdout[2], fderr[2];
  if(pipe(fdout) == -1 || pipe(fderr) == -1) {
    perror("pipe");
  } else {
    dup2(fdout[1], fileno(stdout));
    dup2(fderr[1], fileno(stderr));
    ::close(fdout[1]);
    ::close(fderr[1]);
    outId = XtAppAddInput(context,fdout[0],(void*)XtInputReadMask,
			  inputCallback,this);
    errId = XtAppAddInput(context,fderr[0],(void*)XtInputReadMask,
			  inputCallback,this);
    fflush(stdout);
    setbuf(stdout, NULL);
    fflush(stderr);
    setbuf(stderr, NULL);
  }
#endif
  
  XtAppContext context = XtWidgetToApplicationContext(popupShell);
  inputId = XtAppAddInput(context,rd_fd,(void*)XtInputReadMask,
			  inputCallback, this);

  // add a signal handler
  struct sigaction saction;

  saction.sa_handler = (void (*)(int))sigchild_handler;
  saction.sa_flags = 0;
  sigemptyset(&saction.sa_mask);
  sigaction(SIGCHLD, &saction, NULL);

  done = NOTHING;
  updateExecuteDialog(0);

  // WidgetCreatorDialog aufbereiten

  unsigned int i;
  Widget button;

  // Shell-Klassen

  for(i=0; i<Lcreator::getShells().getSize(); i++) {
    char *name = Lcreator::getShells()[i]->getShortName();
    button = XtVaCreateManagedWidget(name,xmPushButtonWidgetClass,
				     ShellMenu, NULL);
    XtAddCallback(button, XmNactivateCallback,
		  createWidgetCB, Lcreator::getShells()[i]);
  }
  XtVaSetValues(ShellMenu, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);

  // Manager-Klassen

  for(i=0; i<Lcreator::getManager().getSize(); i++) {
    char *name = Lcreator::getManager()[i]->getShortName();
    button = XtVaCreateManagedWidget(name,xmPushButtonWidgetClass,
				     ManagerMenu, NULL);
    XtAddCallback(button, XmNactivateCallback,
		  createWidgetCB, Lcreator::getManager()[i]);
  }
  XtVaSetValues(ManagerMenu, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);

  for(i=0; i<Lcreator::getPrimitives().getSize(); i++) {
    char *name = Lcreator::getPrimitives()[i]->getShortName();
    button = XtVaCreateManagedWidget(name,xmPushButtonWidgetClass,
				     PrimitivesMenu, NULL);
    XtAddCallback(button, XmNactivateCallback,
		  createWidgetCB, Lcreator::getPrimitives()[i]);
  }
  XtVaSetValues(PrimitivesMenu, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);

  // Dialogs

  for(i=0; i<Lcreator::getDialogs().getSize(); i++) {
    char *name = Lcreator::getDialogs()[i]->getShortName();
    button = XtVaCreateManagedWidget(name,xmPushButtonWidgetClass,
				     DialogsMenu, NULL);
    XtAddCallback(button, XmNactivateCallback,
		  createWidgetCB, Lcreator::getDialogs()[i]);
  }
  XtVaSetValues(DialogsMenu, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);

  RefArray<LangInfo> langs(lApp->getLanguages());
  for(i=0; i<langs.getSize(); i++) {
    if(langs[i]->getName()) {
      XtVaCreateManagedWidget(langs[i]->getName(),xmPushButtonWidgetClass,
			      PSLangMenu, NULL);
    } 
  }
  XtVaSetValues(PSLangOptionMenu, XmNsubMenuId, PSLangMenu, NULL);
  
  withLibLac(lApp->getProject()->getLang()->getWithLibLac());
  
  if(lApp->isDemo()) {
    char msg[1024];
    msgCat->getMsg(msg, DEMO_MESSAGE, DEMO_MAX_WIDGETS);
    printf("%s\n", msg);
  } else {
    XmString xms1, xms2, xms;
    xms1 = XmStringCreate("License: ", XmSTRING_DEFAULT_CHARSET);
    xms2 = XmStringCreate(app->getLicensee(), "bold");
    xms = XmStringConcat(xms1, xms2);
    XtVaSetValues(label_2, 
		  XmNlabelString, xms, 
		  NULL);
    XmStringFree(xms1);
    XmStringFree(xms2);
    XmStringFree(xms);
  }
  update( OPTIONS_CHANGED | PROJECT_CHANGED | WIDGETCLASSES_CHANGED );

}

// -------------------------
//   opened()
// -------------------------

void 
MainWindow::opened()
{
  if(!lApp->getNormalQuit() || lApp->getQuickStartWindow()) {
    char path[PATH_MAX];
    char recoverPath[PATH_MAX];

    XtVaSetValues(XtParent(quickStartDialog), XmNallowShellResize, TRUE, NULL);
    
    strcpy(path, lApp->getCurrentProject());
    getBasename(path);

    strcpy(recoverPath, lApp->getAutoSavePath());
    if(recoverPath[strlen(recoverPath)-1] != '/')
      strcat(recoverPath, "/");
    strcat(recoverPath, path);

    XmTextSetString(qsOpenText, lApp->getCurrentProject());
    XmTextSetString(qsNewText, "Untitled.prj");
    XmTextSetString(qsRecoverText, recoverPath);

    if(lApp->getCurrentProject()[0]) { // there was a project
      if(lApp->getNormalQuit()) {
	XmToggleButtonSetState(qsOpenButton, TRUE, TRUE);
      } else {
	XmToggleButtonSetState(qsRecoverButton, TRUE, TRUE);
      }
    } else {
      XtSetSensitive(qsOpenText, FALSE);
      XtSetSensitive(qsRecoverText, FALSE);
      XtSetSensitive(qsOpenButton, FALSE);
      XtSetSensitive(qsRecoverButton, FALSE);
      XmToggleButtonSetState(qsNewButton, TRUE, TRUE);
      XtSetSensitive(qsNewButton, FALSE);
    }

    XtManageChild(quickStartDialog);
  }
}

// -------------------------
//   beforeClose()
// -------------------------

void 
MainWindow::beforeClose()
{
  long height = 0;
  Boolean b = FALSE;

  XtVaGetValues(ViewForm, XmNheight, &height, NULL);
  lApp->setVDLong(this, VD_ICONBOX_HEIGHT, height);

  lApp->setVDBoolean(this, VD_PALETTE_OPEN, b);
}

// -------------------------
//   ~MainWindow()
// -------------------------

MainWindow::~MainWindow()
{
  if( !interfaceIconView.isNil() )
    interfaceIconView.Delete();
}


// -------------------------
//   update()
// -------------------------

void MainWindow::update( unsigned long flags )
{
  char title[1024];

  if( flags & PROJECT_CHANGED ) {
    if( !interfaceIconView.isNil() )
      interfaceIconView.Delete();
    interfaceIconView = 
      new InterfaceIconView(&lApp->getProject()->getInterfaces(), 
			    ViewForm);
    XtManageChild(interfaceIconView->getTop());
    XtVaSetValues(interfaceIconView->getTop(),
		  XmNtopAttachment,	XmATTACH_WIDGET,
		  XmNtopOffset,		2,
		  XmNtopWidget,		ViewLabel,
		  XmNleftAttachment,	XmATTACH_FORM,
		  XmNleftOffset,	2,
		  XmNrightAttachment,	XmATTACH_FORM,
		  XmNrightOffset,	2,
		  XmNbottomAttachment,  XmATTACH_FORM,
		  XmNbottomOffset,      2,
		  NULL);


    msgCat->getMsg(title, MAINWINDOW_TITLE, lApp->getProject()->getFilename());
    XtVaSetValues(popupShell, 
		  XmNtitle, title,
		  XmNiconName, title,
		  NULL);
  }
  if( flags & OPTIONS_CHANGED ) {
    XtVaSetValues(optimalRefreshButton,
		  XmNset, lApp->getOptimalRefresh(),
		  NULL);
  }
}

// -------------------------
//   act()
// -------------------------

void MainWindow::act(char *action)
{
  char title[1024];
  char msg[1024];
  char file[PATH_MAX];
    
  if( !strcmp( action, MW_TUTORIAL ) ) {
    getHelp(0);
    return;
  }
  if( !strcmp( action, MW_FILEOPEN ) ) {
    msgCat->getMsg( title, FILE_OPEN_TITLE );
    if( MSGBOX_OK == FileBox( title, file ) ) {
      setWaitCursor(TRUE);
      lApp->loadFile(file);
      setWaitCursor(FALSE);
    }
    return;
  }
  if( !strcmp( action, MW_FILESAVE ) ) {
    if(lApp->getProject()->isUnspecFilename()) {
      XmString xmstr;
      char filename[PATH_MAX];

      getcwd(filename, PATH_MAX);
      if(filename[strlen(filename)-1] != '/') {
	strcat(filename, "/");
      }
      strcat(filename, lApp->getProject()->getFilename());
      xmstr = XmStringCreateLtoR(filename, XmSTRING_DEFAULT_CHARSET);
      XtVaSetValues(saveProjectDialog, 
		    XmNtextString, xmstr,
		    NULL );
      XmStringFree(xmstr);
      XtManageChild(saveProjectDialog);

      return;
    }
    setWaitCursor(TRUE);
    if(lApp->getProject()->save()) {
      msgCat->getMsg(msg, PROJECT_SAVE_SUCCESS);
      puts(msg);
    }
    setWaitCursor(FALSE);
    return;
  }
  if( !strcmp( action, MW_FILESAVEAS ) ) {
    msgCat->getMsg( title, PROJECT_SAVE_TITLE );
    if( MSGBOX_OK == FileBox( title, file ) ) {
      setWaitCursor(TRUE);
      if(lApp->getProject()->save(file)) {
	msgCat->getMsg(msg, PROJECT_SAVE_SUCCESS);
	puts(msg);
      }
      setWaitCursor(FALSE);
    }
    return;
  }
  if( !strcmp( action, MW_PROJECTGENERATE ) ) {
    return;
  }
  if( !strcmp( action, MW_FILEEXIT ) ) {
    msgCat->getMsg( title, QUERY_QUIT_TITLE );
    msgCat->getMsg( msg, QUERY_QUIT_MSG );
    if( !lApp->getProject()->getChangedFlag() ||
	MSGBOX_OK == MsgBox(title, msg, MSGBOX_STYLE_YESNO) ) {
      lApp->exit();
    }
    return;
  }
  if( !strcmp( action, MW_PROJECTPALETTE ) ) {
    setWaitCursor(TRUE);
    TemplateView::showView(lApp->getMainTemplate());
    setWaitCursor(FALSE);
    return;
  }
  if( !strcmp( action, MW_MESSAGECLEAR ) ) {
    XmTextSetString(XmText_1, "");
    return;
  }
}

// ------------------------------------
// wmDelete()
// ------------------------------------

void MainWindow::wmDelete()
{
  act(MW_FILEEXIT);
}


// ------------------------------------
// inputCallback
// ------------------------------------

void
MainWindow::inputCallback(XtPointer clientData, int *, XtInputId *)
{
  ::MainWindow *self = (::MainWindow*)clientData;
  char buf[BUFSIZ+1];
  int len;
  Lstring output;

  while((len = read(rd_fd, buf, BUFSIZ)) > 0) {
    buf[len] = 0;
    output += buf;
  }

  XmTextInsert(self->XmText_1,
	       XmTextGetLastPosition(self->XmText_1), output);
  
}


// ------------------------------------
// testModeChanged()
// ------------------------------------

void MainWindow::testModeChanged(Widget, XtPointer )
{
  Boolean set;

  XtVaGetValues( TestModeToggle, XmNset, &set, NULL );
  lApp->setTestMode(set);
}

// ------------------------------------
// newProject()
// ------------------------------------

void MainWindow::newProject(Widget ,XtPointer)
{
  char title[1024];
  char msg[1024];

  char *str=XmTextGetString(ProjectNewText);

  if(str) {
    // new project
    msgCat->getMsg(title, QUERY_NEW_PROJECT_TITLE);
    msgCat->getMsg(msg, QUERY_NEW_PROJECT);
    if( !lApp->getProject()->getChangedFlag() ||
       MSGBOX_OK == LicView::MsgBox( title, msg )) {
      char buf[PATH_MAX];
      if(strlen(str) > 0) {
	strcpy(buf, str);
	withSuffix(buf, sizeof(buf), "prj");
	delete lApp->getProject();
	lApp->setProject(new Lproject(buf));
      } else {
	delete lApp->getProject();
	lApp->setProject(new Lproject());
      }
      lApp->changed( PROJECT_CHANGED );
    }
    XtFree(str);
  }
  XtUnmanageChild(ProjectNewDialog);
}

// ------------------------------------
// newProjectCancel()
// ------------------------------------

void MainWindow::newProjectCancel(Widget ,XtPointer)
{
  XtUnmanageChild(ProjectNewDialog);
}

// ------------------------------------
// newProjectHelp()
// ------------------------------------

void MainWindow::newProjectHelp(Widget ,XtPointer )
{
  getHelp(HID_NEW_PROJECT);
}


// ------------------------------------
// projectSettingsMap()
// ------------------------------------

void MainWindow::projectSettingsMap(Widget,XtPointer)
{
  ProjectSettings::showView(lApp->getProject());

  XmTextSetString(PSNameText, lApp->getProject()->getFilename());       
  XmTextSetString(PSSourceDirText, 
		  lApp->getProject()->getSourcePath());
  if(lApp->getProject()->getStartupInterface()) {
    XtSetSensitive(PCStartText, TRUE);
    XmTextSetString(PCStartText, 
		    lApp->getProject()->getStartupInterface()->getName());   
  } else {
    XmTextSetString(PCStartText, "");
    if(lApp->getProject()->getInterfaces().getSize()) 
      XtSetSensitive(PCStartText, TRUE);
    else
      XtSetSensitive(PCStartText, FALSE);
  }

  Widget wg = XtNameToWidget(PSLangMenu, 
			     lApp->getProject()->getLang()->getName());
  if(wg) {
    XtVaSetValues(PSLangOptionMenu, XmNmenuHistory, wg, NULL);
  }
}

// ------------------------------------
// projectSettingsOk()
// ------------------------------------

void MainWindow::projectSettingsOk(Widget ,XtPointer )
{
  char *name = XmTextGetString(PSNameText);        // allocation
  char *startup = XmTextGetString(PCStartText);   
  char *sourcedir = XmTextGetString(PSSourceDirText);

  Widget langWg;
  XtVaGetValues(PSLangOptionMenu,
		XmNmenuHistory, &langWg,
		NULL);
  char *langName = XtName(langWg);                // no allocation

  if(startup) {
    if(lApp->getProject()->getInterfaces().getSize() ) {
      Linterface *linterface = lApp->getProject()->getInterface(startup);
      if(linterface) {
	lApp->getProject()->setStartupInterface(linterface);
      } else {
	char title[256];
	char msg[1024];
	msgCat->getMsg(title, ERROR_TITLE);
	msgCat->getMsg(msg, INTERFACE_NOT_EXIST, startup );
	LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
	XtFree(startup);
	return;
      }
    }
    XtFree(startup);
  }

  if(name) {
    char buf[PATH_MAX];
    if(strlen(name) > 0) {
      strcpy(buf, name);
      withSuffix(buf, sizeof(buf), "prj");
      lApp->getProject()->setFilename(buf);
    } else {
      lApp->getProject()->setFilename();
    }
    XtFree(name);
  }

  if(sourcedir) {
    char buf[PATH_MAX];
    if(strlen(sourcedir) > 0) {
      strcpy(buf, sourcedir);
      lApp->getProject()->setSourcePath(buf);
    }
    XtFree(sourcedir);
  }

  if(langName) {
    LangInfo *lang = lApp->getLang(langName);
    if(lang) {
      lApp->getProject()->setLang(lang);
    }
  }
  
  lApp->changed( PROJECT_CHANGED );
  lApp->getProject()->changed(0);         // dummy to set the changed flag
  XtUnmanageChild(ProjectSettingsDialog);
}

// ------------------------------------
// projectSettingsCancel()
// ------------------------------------

void MainWindow::projectSettingsCancel(Widget ,XtPointer )
{
  XtUnmanageChild(ProjectSettingsDialog);
}

// ------------------------------------
// projectSettingsHelp()
// ------------------------------------

void MainWindow::projectSettingsHelp(Widget ,XtPointer )
{
  getHelp(HID_PROJECT_SETTINGS);
}

// -----------------------------------
//       generateOk()
// -----------------------------------

void MainWindow::generateOk(Widget,XtPointer)
{
  Boolean overwrite = XmToggleButtonGetState(StubsGenerateToggle);
  Boolean mainprogram = XmToggleButtonGetState(MainGenerateToggle);
  Boolean imakefile = XmToggleButtonGetState(ImakefileGenerateToggle);
  Boolean interfaces = TRUE;

  XtUnmanageChild(ProjectGenerateDialog);

  while(toOverwrite.getSize())
    toOverwrite[0].Delete();
  
  setWaitCursor(TRUE);
  lApp->getProject()->generate(interfaces, TRUE, TRUE, TRUE, toOverwrite);
  setWaitCursor(FALSE);

  XmListDeleteAllItems(overwriteFilesList);
  
  // if we don't want to overwrite the stubs, we have to delete them

  RefArray<Lfile> toDelete;
  for(unsigned int i=0; i<toOverwrite.getSize(); i++) {
    if(toOverwrite[i]->getCareOverwrite() && toOverwrite[i]->fileExist()) {
      if((!overwrite && 
	  toOverwrite[i]->getFileClass() == FILE_CLASS_INTERFACE_SOURCE) ||
	 (!imakefile && 
	  toOverwrite[i]->getFileClass() == FILE_CLASS_IMAKEFILE) ||
	 (!mainprogram && 
	  toOverwrite[i]->getFileClass() == FILE_CLASS_MAIN_PROGRAM)) 
	toDelete.add(toOverwrite[i]);
    }
  }
  while(toDelete.getSize())
    toDelete[0].Delete();
  
  // file in the list widget
  
  unsigned int maxNameLen = 0;
  for(unsigned int i=0; i<toOverwrite.getSize(); i++) 
    maxNameLen = maxNameLen < strlen(toOverwrite[i]->getFilename()) ?
      strlen(toOverwrite[i]->getFilename()) : maxNameLen;
  maxNameLen++;
  for(unsigned int i=0; i<toOverwrite.getSize(); i++) {
    char buf[PATH_MAX];
    char spaces[PATH_MAX];
    char *message;
    if(toOverwrite[i]->getCareOverwrite() && toOverwrite[i]->fileExist()) {
      message = CARE_OVERWRITE;
    } else {
      message = SHOULD_BE_WRITTEN;
    }
    memset(spaces, ' ', sizeof(spaces));
    spaces[maxNameLen - strlen(toOverwrite[i]->getFilename()) + 1] = 0;
    msgCat->getMsg(buf, message, toOverwrite[i]->getFilename(), spaces);
    XmString xms = XmStringCreateLtoR(buf, XmSTRING_DEFAULT_CHARSET);
    XmListAddItem(overwriteFilesList, xms, 0);
    XmListSelectItem(overwriteFilesList, xms, FALSE);
    XmStringFree(xms);
  }
  XtManageChild(overwriteDialog);
}

// -----------------------------------
//       generateCancel()
// -----------------------------------

void MainWindow::generateCancel(Widget,XtPointer)
{
  XtUnmanageChild(ProjectGenerateDialog);
}

// -----------------------------------
//       generateHelp()
// -----------------------------------

void MainWindow::generateHelp(Widget,XtPointer)
{
  getHelp(HID_GENERATE_DIALOG);
}


// -----------------------------------
//       gridMap()
// -----------------------------------

void MainWindow::gridMap(Widget,XtPointer)
{
  XmScaleSetValue(GridValue, lApp->getGridValue());
  XmToggleButtonSetState(GridModeOn, lApp->getGrid(), TRUE);
}

// -----------------------------------
//       gridOkCB()
// -----------------------------------

void MainWindow::gridOkCB(Widget,XtPointer)
{
  int v;

  XmScaleGetValue(GridValue,&v);
  lApp->setGrid(XmToggleButtonGetState(GridModeOn));
  lApp->setGridValue(v);
  lApp->changed(OPTIONS_CHANGED);

  XtUnmanageChild(GridDialog);
}

// -----------------------------------
//       gridCancelCB()
// -----------------------------------

void MainWindow::gridCancelCB(Widget,XtPointer)
{
  XtUnmanageChild(GridDialog);
}

// -----------------------------------
//       gridHelpCB()
// -----------------------------------

void MainWindow::gridHelpCB(Widget,XtPointer)
{
  getHelp(HID_GRID_DIALOG);
}


// -----------------------------------
//       loadInterfaceOk()
// -----------------------------------

void MainWindow::loadInterfaceOk(Widget,XtPointer)
{
  XmString xmstr;
  char *filename;
  char title[256], msg[1024];
  YResult *result;

  XtVaGetValues(loadInterfaceDialog, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );

  setWaitCursor(TRUE);
  openFileHook(filename);
  result = parse( filename );
  setWaitCursor(FALSE);
  if( result == NULL ) {
    msgCat->getMsg( title, ERROR_TITLE );
    msgCat->getMsg( msg, ERROR_FILE_NOT_FOUND, filename );
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    return;
  }
  if(result->error) {
    app->showSystemError(filename, result->error);
  }

  if( result->parseError[0] ) {
    // Error occured
    msgCat->getMsg( title, ERROR_TITLE );
    LicView::MsgBox(title, result->parseError, MSGBOX_STYLE_OK);
  } else {
    if( result->root_widget && result->root_widget->widget_class[0] ) {
      Linterface *li;
      li = new Linterface( result->root_widget );
      li = lApp->getProject()->addInterface( li );
      if(li && lApp->getShowInterfaceAfterLoad())
	li->show();
      setWaitCursor(FALSE);
    } else {   
      msgCat->getMsg( title, ERROR_TITLE );
      msgCat->getMsg( msg, INVALID_FILE_FORMAT, filename );
      LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    }
  }
  XtFree(filename);
}

// ------------------------------------
// loadProjectOk()
// ------------------------------------

void MainWindow::loadProjectOk(Widget,XtPointer)
{
  XmString xmstr;
  char *filename;
  char title[256], msg[1024];
  YResult *result;

  XtVaGetValues(loadProjectDialog, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );

  setWaitCursor(TRUE);
  openFileHook(filename);
  result = parse(filename);
  setWaitCursor(FALSE);
  if( result == NULL ) {
    msgCat->getMsg( title, ERROR_TITLE );
    msgCat->getMsg( msg, ERROR_FILE_NOT_FOUND, filename );
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    XtFree(filename);
    return;
  }
  if(result->error) {
    app->showSystemError(filename, result->error);
  } else if( result->parseError[0] ) {
    // Error occured
    msgCat->getMsg( title, ERROR_TITLE );
    LicView::MsgBox(title, result->parseError, MSGBOX_STYLE_OK);
  } else {
    if( result->first_interface ) {
      
      // new project
      msgCat->getMsg( title, QUERY_NEW_PROJECT_TITLE );
      msgCat->getMsg( msg, QUERY_NEW_PROJECT );
      
      if( !lApp->getProject()->getChangedFlag() || 
	 MSGBOX_OK == LicView::MsgBox(title, msg)) {
	setWaitCursor(TRUE);
	delete lApp->getProject();
	lApp->setProject( new Lproject( filename, result ));
	lApp->changed( PROJECT_CHANGED );
	setWaitCursor(FALSE);
      }
    } else {   
      msgCat->getMsg( title, ERROR_TITLE );
      msgCat->getMsg( msg, INVALID_FILE_FORMAT, filename );
      LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    }
  }
  free_YResult(result);
  XtFree(filename);
}

// ------------------------------------
// saveProjectOk()
// ------------------------------------

void MainWindow::saveProjectOk(Widget,XtPointer)
{
  XmString xmstr;
  char *filename;

  XtVaGetValues(saveProjectDialog, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );
  
  if(filename) {
    setWaitCursor(TRUE);
    if(lApp->getProject()->isUnspecFilename()) {
      lApp->getProject()->setFilename(filename);
      lApp->changed(PROJECT_CHANGED);
    }
    if(lApp->getProject()->save(filename)) {
      char msg[1024];
      msgCat->getMsg(msg, PROJECT_SAVE_SUCCESS);
      puts(msg);
    }
    setWaitCursor(FALSE);
  }
}

// ------------------------------------
// updatePolicyChanged()
// ------------------------------------

void MainWindow::updatePolicyChanged(Widget ,XtPointer callData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callData;
  
  if( cbs->widget == optimalRefreshButton ) {
    Boolean s;
    s = XmToggleButtonGetState(optimalRefreshButton);
    lApp->setOptimalRefresh(s);
    lApp->changed(OPTIONS_CHANGED);
  }
}

// ------------------------------------
// createWidgetCB()
// ------------------------------------

void MainWindow::createWidgetCB(Widget , XtPointer client, XtPointer )
{
  Lcreator *lcreator = (Lcreator*)client;
  
  lcreator->createLwidget(NULL);
}


// ------------------------------------
// quickHelpMenuMap()
// ------------------------------------

void MainWindow::quickHelpMenuMap(Widget,XtPointer)
{
  XmToggleButtonSetState(quickHelpToggle, quickHelpEnabled, FALSE);
}

// ------------------------------------
// autoSaveEntry()
// ------------------------------------

void MainWindow::autoSaveEntry(Widget,XtPointer)
{
}

// ------------------------------------
// autoSaveMap()
// ------------------------------------

void MainWindow::autoSaveMap(Widget,XtPointer)
{
#if(0)
  unsigned int time = app->getAutoSaverSeconds();
  if(time == 0)
    XmToggleButtonSetState(autoSaveOff, TRUE, FALSE);
  else if(time <= 1*60)
    XmToggleButtonSetState(autoSave1, TRUE, FALSE);
  else if(time <= 3*60)
    XmToggleButtonSetState(autoSave3, TRUE, FALSE);
  else
    XmToggleButtonSetState(autoSave10, TRUE, FALSE);
#endif
}

// ------------------------------------
// quickHelpChanged()
// ------------------------------------

void MainWindow::quickHelpChanged(Widget,XtPointer callData)
{
  XmToggleButtonCallbackStruct *cbs = (XmToggleButtonCallbackStruct*)callData;
  
  enableQuickHelp(cbs->set);
}

// ------------------------------------
// saveOptions()
// ------------------------------------

void MainWindow::saveOptions(Widget,XtPointer)
{
  lApp->saveOptions();
}



void MainWindow::showHelp(Widget, XtPointer) 
{
  lApp->getProject()->getHelp(0);
}



void MainWindow::do_overwrite(Widget,XtPointer)
{
  int *items;
  int count;
  Boolean errorSeen = FALSE;
  XtUnmanageChild(overwriteDialog);
  Boolean imakefile = FALSE;

  XmListGetSelectedPos(overwriteFilesList, &items, &count);
  for(int i=0; i<count; i++) {
    int ret;
    ret = toOverwrite[items[i]-1]->write();
    if( ret != 0) {
      char buf[PATH_MAX];
      msgCat->getMsg(buf, WRITE_FILE_ERROR, 
		  toOverwrite[items[i]-1]->getFilename(), strerror(ret));
      puts(buf);
      errorSeen = TRUE;
    } else {
      char buf[PATH_MAX];
      msgCat->getMsg(buf, FILE_WRITTEN, 
		     toOverwrite[items[i]-1]->getFilename());
      puts(buf);

      // if we have generated an Imakefile, we should set the 
      // xmkmf-Toggle in the Execute-Dialog

      char *fn = toOverwrite[items[i]-1]->getFilename();   
      char *imf = "Imakefile";
      if(strlen(fn) >= strlen(imf)) {
	if(!strcmp(fn + strlen(fn)-strlen(imf), imf)) {
	  imakefile = TRUE;
	}
      }
    }
  }
  if(errorSeen) {
    char title[256];
    char msg[1024];
    msgCat->getMsg(title, ERROR_TITLE);
    msgCat->getMsg(msg, ERROR_SEEN);
    MsgBox( title, msg, MSGBOX_STYLE_OK);
  }

  if(imakefile)
    XmToggleButtonSetState(xmkmfToggleButton, TRUE, TRUE);
  else
    XmToggleButtonSetState(makeToggleButton, TRUE, TRUE);
}

void MainWindow::overwriteCancel(Widget,XtPointer)
{
  XtUnmanageChild(overwriteDialog);
}

void MainWindow::overwriteHelp(Widget,XtPointer)
{
  getHelp(HID_OVERWRITE_DIALOG);
}


void MainWindow::executeOk(Widget,XtPointer)
{
  char *prg;
  char *args[10];
  char execFile[PATH_MAX];
  char buf[PATH_MAX];
  char cmdLine[PATH_MAX];

  //XtUnmanageChild(executeDialog);

  if(current_pid != 0) {
    printf("Fatal error: current_pid != 0\n");
  }

  if(XmToggleButtonGetState(xmkmfToggleButton)) {
    prg = "xmkmf";
    args[0] = "xmkmf";
    args[1] = NULL;
    done = IMAKEFILE;
  } else if(XmToggleButtonGetState(makeDependToggleButton)) {
    prg = "make";
    args[0] = "make";
    args[1] = "depend";
    args[2] = NULL;
    done = MAKE_DEPEND;
  } else if(XmToggleButtonGetState(makeToggleButton)) {
    prg = "make";
    args[0] = "make";
    args[1] = NULL;
    done = MAKE;
  } else if(XmToggleButtonGetState(execToggleButton)) {
    sprintf(execFile, "./%s", lApp->getProject()->getExecFile());
    prg = execFile;
    args[0] = execFile;
    args[1] = NULL;
    done = PROGRAM;
  } else
    return;
  
  current_pid = fork();
  switch(current_pid) {
  case 0:
    ::close(0);    // stdin closed
    ::open("/dev/null", O_RDONLY);   // new stdin
    cmdLine[0] = 0;
    for(unsigned int i=0; args[i]; i++) {
      strcat(cmdLine, args[i]);
      strcat(cmdLine, " ");
    }
    msgCat->getMsg(buf, STARTING_PROGRAM, cmdLine);
    puts(buf);
    chdir(app->getProject()->getSourcePath());
    if(execvp(prg,args) < 0)
      perror("execvp");
    exit(0);
    break;
  case -1:
    perror("fork");
    current_pid = 0;
    break;
  default:
    FOREACH(i,allViews) {
      allViews[i]->updateExecuteDialog(0);
    }
    break;
  }
}

void MainWindow::sigchild_handler(int)
{
  int status;
  pid_t pid;

  pid = wait(&status);
  if(pid < 0)
    perror("wait");
  if(pid == current_pid) {
    char buf[1024];
    current_pid = 0;
    if(WIFSIGNALED(status)) {
      msgCat->getMsg(buf, CHILD_GET_SIGNAL, WTERMSIG(status));
    } else if(WIFSTOPPED(status)) {
      msgCat->getMsg(buf, CHILD_STOPPED, WSTOPSIG(status));
    } else {
      msgCat->getMsg(buf, CHILD_RETURNED, WEXITSTATUS(status));
    }
    puts(buf);
    FOREACH(i,allViews) {
      allViews[i]->updateExecuteDialog(status);
    }
  }
}

void MainWindow::executeCancel(Widget,XtPointer)
{
  XtUnmanageChild(executeDialog);
}

void MainWindow::executeHelp(Widget,XtPointer)
{
  getHelp(HID_EXECUTE_DIALOG);
}

void MainWindow::do_stop(Widget,XtPointer)
{
  kill(current_pid, SIGKILL);
}

void MainWindow::updateExecuteDialog(int status)
{
  if(current_pid) {    // program is running
    XtSetSensitive(executeRowColumn, FALSE);
    XtSetSensitive(XmMessageBoxGetChild(executeDialog, XmDIALOG_OK_BUTTON), 
		   FALSE);
    XtSetSensitive(StopIcon, TRUE);
    if(XtWindow(StopIcon)) 
      XtMapWidget(StopIcon);
    else
      XtSetMappedWhenManaged(StopIcon, TRUE);
  } else {             // no program, exited
    XtSetSensitive(executeRowColumn, TRUE);
    XtSetSensitive(XmMessageBoxGetChild(executeDialog, XmDIALOG_OK_BUTTON), 
		   TRUE);
    XtSetSensitive(StopIcon, FALSE);
    if(XtWindow(StopIcon)) 
      XtUnmapWidget(StopIcon);
    else
      XtSetMappedWhenManaged(StopIcon, FALSE);

    if(status == 0) {
      switch(done) {
      case IMAKEFILE:
	done = MAKE_DEPEND;
	XmToggleButtonSetState(makeDependToggleButton, TRUE, TRUE);
	break;
      case MAKE_DEPEND:
	done = MAKE;
	XmToggleButtonSetState(makeToggleButton, TRUE, TRUE);
	break;
      case MAKE:
	done = PROGRAM;
	XmToggleButtonSetState(execToggleButton, TRUE, TRUE);
	break;
      default:
	done = IMAKEFILE;
	XmToggleButtonSetState(xmkmfToggleButton, TRUE, TRUE);
	break;
      }
    }
  }
}


// -------------------------------
//    withLibLac()
// -------------------------------

void MainWindow::withLibLac(Boolean w)
{
  for(unsigned int i=0; i<allViews.getSize(); i++) {
    XtSetSensitive(allViews[i]->ProjectShowHelp, w);
  }
}


// ---------------------------
//   showWidgetPalette()
// --------------------------
void MainWindow::showWidgetPalette(Widget,XtPointer)
{
  LicView::setWaitCursor(TRUE);
  if(widgetPalette.isNil())
    widgetPalette = new WidgetPalette(lApp);
  widgetPalette->open();
  LicView::setWaitCursor(FALSE);
}


// ---------------------------
//   PSPaletteFileChanged()
// --------------------------
void MainWindow::PSPaletteFileChanged(Widget,XtPointer)
{
  XmString xmstr;
  char *str;

  XtVaGetValues(PSPaletteFileSB, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR(xmstr, XmSTRING_DEFAULT_CHARSET, &str);
  XmTextSetString(PSPaletteText, str);
  XtFree(str);
}


// ---------------------------
//   PSSourceDirChanged()
// --------------------------
void MainWindow::PSSourceDirChanged(Widget,XtPointer)
{
  XmString xmstr;
  char *str;

  XtVaGetValues(PSSourceDirFileSB, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &str );
  XmTextSetString(PSSourceDirText, str);
  XtFree(str);
}


// ---------------------------
//   DoContextHelp()
// --------------------------
void MainWindow::DoContextHelp(Widget,XtPointer)
{
  contextHelp();
}


// ---------------------------
//   DoHelpForHelp()
// --------------------------
void MainWindow::DoHelpForHelp(Widget,XtPointer)
{
  getHelp(HID_USING_HELP);
}


// ---------------------------
//   projectNewMapped()
// --------------------------

void MainWindow::projectNewMapped(Widget,XtPointer)
{
  XmTextSetString(ProjectNewText,"Untitled.prj");
}


// ---------------------------
//   do_newTemplates()
// --------------------------

void MainWindow::do_newTemplates(Widget,XtPointer)
{
  Lpalette *t;

  t = new Lpalette();
  lApp->getTemplates().add(t);
  TemplateView::showView(t);
}


// ---------------------------
//   do_openTemplates()
// --------------------------

void MainWindow::do_openTemplates(Widget,XtPointer)
{
  XmString xmstr;
  char *filename;
  Lpalette *t;

  XtVaGetValues(openTemplatesDialog, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );

  setWaitCursor(TRUE);

  t = new Lpalette(filename);
  lApp->getTemplates().add(t);
  TemplateView::showView(t);

  setWaitCursor(FALSE);

  XtFree(filename);
}


// ---------------------------
//   do_qsDo()
// --------------------------

void 
MainWindow::do_qsDo(Widget,XtPointer)
{
  char *str = NULL;
  if(XmToggleButtonGetState(qsOpenButton)) {
    str = XmTextGetString(qsOpenText);
    setWaitCursor(TRUE);
    lApp->loadFile(str);
    setWaitCursor(FALSE);
  } else if(XmToggleButtonGetState(qsNewButton)) {
    str = XmTextGetString(qsNewText);

    char buf[PATH_MAX];
    if(strlen(str) > 0) {
      strcpy(buf, str);
      withSuffix(buf, sizeof(buf), "prj");
    } else {
      strcpy(buf, "Untitled.prj");
    }
    
    delete lApp->getProject();
    lApp->setProject(new Lproject(buf));
    lApp->changed( PROJECT_CHANGED );

  } else if(XmToggleButtonGetState(qsRecoverButton)) {
    str = XmTextGetString(qsRecoverText);

    setWaitCursor(TRUE);
    lApp->loadFile(str);
    setWaitCursor(FALSE);

    lApp->getProject()->setFilename(lApp->getCurrentProject());
    lApp->changed( PROJECT_CHANGED );
  } 
  if(str)
    XtFree(str);
}

// ---------------------------
//   do_qsChanged()
// --------------------------

void 
MainWindow::do_qsChanged(Widget wg,XtPointer)
{
  if(!XmToggleButtonGetState(wg)) {
    XmToggleButtonSetState(wg, TRUE, FALSE);
  } else {
    if(wg != qsRecoverButton)
       XmToggleButtonSetState(qsRecoverButton, FALSE, FALSE);
    if(wg != qsOpenButton)
       XmToggleButtonSetState(qsOpenButton, FALSE, FALSE);
    if(wg != qsNewButton)
       XmToggleButtonSetState(qsNewButton, FALSE, FALSE);
  }
}


// ---------------------------
//   do_projectSettings()
// --------------------------

void 
MainWindow::do_projectSettings(Widget,XtPointer)
{
  ProjectSettings::showView(lApp->getProject());
}

// ------------------------------------
// do_defaultShellChanged()
// ------------------------------------
void 
MainWindow::defaultShellChanged(Widget, XtPointer callData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callData;
  char *defShell = NULL;

  if(XmToggleButtonGetState(cbs->widget)) {

    if(cbs->widget == applicationShellButton) 
      defShell = "ApplicationShell";
    else if(cbs->widget == toplevelShellButton) 
      defShell = "TopLevelShell";
    else if(cbs->widget == transientShellButton) 
      defShell = "TransientShell";
    else if(cbs->widget == dialogShellButton) 
      defShell = "XmDialogShell";

    if(defShell)
      Lcreator::setDefaultShell(Lcreator::getClass(defShell));
  }
}

// ------------------------------------
// do_defaultPublicMap()
// ------------------------------------
void 
MainWindow::do_defaultPublicMap(Widget, XtPointer)
{
  unsigned int len;

  len = strlen(lApp->getDefaultPublic());
  char buf[len+1];
  strcpy(buf, lApp->getDefaultPublic());

  TSortArray<Lstring> items;
  char *ptr;

  ptr = strtok(buf, " ");
  while(ptr) {
    items.add( new Lstring(ptr) );
    ptr = strtok(NULL, " ");
  }
  items.sort();

  XmListDeleteAllItems(defaultPublicList);
  for(unsigned int i=0; i<items.getSize(); i++) {
    XmString xms;
    xms = XmStringCreate(*items[i], "bold");
    XmListAddItem(defaultPublicList, xms, 0);
    XmStringFree(xms);
    delete items[i];
  }

  XtSetSensitive(defaultPublicDelete, FALSE);
}

// ------------------------------------
// do_defaultPublicCancel()
// ------------------------------------
void 
MainWindow::do_defaultPublicCancel(Widget,XtPointer)
{
  XtUnmanageChild(defaultPublicDialog);
}

// ------------------------------------
// do_defaultPublicSelect()
// ------------------------------------
void 
MainWindow::do_defaultPublicSelect(Widget,XtPointer)
{
  int *sel, num;

  if(XmListGetSelectedPos(defaultPublicList, &sel, &num)) {
    XtSetSensitive(defaultPublicDelete, TRUE);
    XtFree((char*)sel);
  } else {
    XtSetSensitive(defaultPublicDelete, FALSE);
  }
}

// ------------------------------------
// do_defaultPublicFocus()
// ------------------------------------
void 
MainWindow::do_defaultPublicFocus(Widget,XtPointer)
{
  XtVaSetValues(defaultPublicDialog, 
		XmNdefaultButton, defaultPublicAdd,
		NULL);
}

// ------------------------------------
// do_defaultPublicAdd()
// ------------------------------------
void 
MainWindow::do_defaultPublicAdd(Widget, XtPointer)
{
  char *str, *ptr, *begin;
  XmString xms;

  str = XmTextGetString(defaultPublicText);
  ptr = str;
  while(*ptr && isspace(*ptr)) ptr++;
  begin = ptr;
  while(*ptr && !isspace(*ptr)) ptr++;
  *ptr = 0;

  xms = XmStringCreate(begin, "bold");
  XmListAddItem(defaultPublicList, xms, 0);
  XmStringFree(xms);

  XtFree(str);
}

// ------------------------------------
// do_defaultPublicDelete()
// ------------------------------------
void 
MainWindow::do_defaultPublicDelete(Widget, XtPointer)
{
  int *pos, num;

  if(XmListGetSelectedPos(defaultPublicList, &pos, &num)) {
    for(int i=num-1; i>=0; i--)
      XmListDeletePos(defaultPublicList, pos[i]);
    XtFree((char*)pos);
  }
}

// ------------------------------------
// do_defaultPublicChanged()
// ------------------------------------
void 
MainWindow::do_defaultPublicChanged(Widget, XtPointer)
{
  XmString *items;
  Cardinal num;
  char *str;
  Lstring s;

  XtVaGetValues(defaultPublicList, 
		XmNitems, &items,
		XmNitemCount, &num,
		NULL);

  for(unsigned int i=0; i<num; i++) {
    if(XmStringGetLtoR(items[i], "bold", &str)) {
      s += str;
      if(i < num-1)
	s += " ";
      XtFree(str);
    }
  }

  lApp->setDefaultPublic(s);

  XtUnmanageChild(defaultPublicDialog);
}

// ------------------------------------
// do_genericOptionsMap()
// ------------------------------------
void 
MainWindow::do_genericOptionsMap(Widget, XtPointer)
{
  XmToggleButtonSetState(genericQuickStartToggle, 
			 lApp->getQuickStartWindow(), FALSE);
  XmToggleButtonSetState(genericAutoSaveToggle, 
			 lApp->getAutoSavingOn(), FALSE);
  
  XmScaleSetValue(genericAutoSaveScale, lApp->getAutoSaveSeconds()/6);

  XmTextSetString(genericAutoSaveText, lApp->getAutoSavePath());
  XmTextSetString(genericMainTemplateText, lApp->getMainTemplatePath());

  XmToggleButtonSetState(quickHelpToggle, quickHelpEnabled, FALSE);
  XmToggleButtonSetState(genericAfterLoadToggle, 
			 lApp->getShowInterfaceAfterLoad(), FALSE);

  XmToggleButtonSetState(toolTipToggle, lApp->getToolTipsEnabled(), FALSE);
  XmToggleButtonSetState(versionControlToggle, 
			 lApp->getVersionControl(), FALSE);
}

// ------------------------------------
// do_genericOptionsOk()
// ------------------------------------
void 
MainWindow::do_genericOptionsOk(Widget, XtPointer)
{
  int v;
  char *str;
  
  lApp->setQuickStartWindow(XmToggleButtonGetState(genericQuickStartToggle));
  lApp->setAutoSavingOn(XmToggleButtonGetState(genericAutoSaveToggle));

  XmScaleGetValue(genericAutoSaveScale, &v);
  lApp->setAutoSaveSeconds(v*6);

  str = XmTextGetString(genericAutoSaveText);
  lApp->setAutoSavePath(str);
  XtFree(str);

  str = XmTextGetString(genericMainTemplateText);
  lApp->setMainTemplatePath(str);
  XtFree(str);

  enableQuickHelp(XmToggleButtonGetState(quickHelpToggle));
  lApp->setShowInterfaceAfterLoad(XmToggleButtonGetState(genericAfterLoadToggle));

  lApp->setToolTipsEnabled(XmToggleButtonGetState(toolTipToggle));
  lApp->setVersionControl(XmToggleButtonGetState(versionControlToggle));
  lApp->changed(OPTIONS_CHANGED);
}

// ------------------------------------
// do_viewDefaultsMap()
// ------------------------------------
void 
MainWindow::do_viewDefaultsMap(Widget, XtPointer)
{
  XmToggleButtonSetState(browserSmallIconToggle,
			 lApp->getBrowserSmallIcons(), FALSE);
  XmToggleButtonSetState(browserWithIconToggle,
			 lApp->getBrowserWithIcons(), FALSE);
  XmToggleButtonSetState(browserWithClassNameToggle,
			 lApp->getBrowserWithClassName(), FALSE);
  XmToggleButtonSetState(browserAutomaticLoadToggle,
			 lApp->getBrowserAutomaticLoad(), FALSE);

  XmToggleButtonSetState(menuEditSmallIconToggle,
			 lApp->getMenuEditSmallIcons(), FALSE);
  XmToggleButtonSetState(menuEditWithIconToggle,
			 lApp->getMenuEditWithIcons(), FALSE);
  XmToggleButtonSetState(menuEditWithClassNameToggle,
			 lApp->getMenuEditWithClassName(), FALSE);
  XmToggleButtonSetState(menuEditAutomaticLoadToggle,
			 lApp->getMenuEditAutomaticLoad(), FALSE);

  XmToggleButtonSetState(aeSmallIconToggle,
			 lApp->getAttachmentEditorSmallIcons(), FALSE);
  XmToggleButtonSetState(aeWithIconToggle,
			 lApp->getAttachmentEditorWithIcons(), FALSE);
  XmToggleButtonSetState(aeWithClassNameToggle,
			 lApp->getAttachmentEditorWithClassName(), FALSE);
  XmToggleButtonSetState(aeAutomaticLoadToggle,
			 lApp->getAttachmentEditorAutomaticLoad(), FALSE);

  XmToggleButtonSetState(editorAutomaticLoadToggle,
			 lApp->getEditorAutomaticLoad(), FALSE);

  XtVaSetValues(coreView, XmNuserData, PW_CORE, NULL);
  XtVaSetValues(specificView, XmNuserData, PW_SPECIFIC, NULL);
  XtVaSetValues(constraintView, XmNuserData, PW_CONSTRAINT, NULL);
  XtVaSetValues(callbackView, XmNuserData, PW_CALLBACKS, NULL);
  XtVaSetValues(extraView, XmNuserData, PW_EXTRA, NULL);
  
  switch(lApp->getEditorDefaultView()) {
  case PW_CORE:
    XtVaSetValues(defaultViewOptionMenu, XmNmenuHistory, coreView, NULL);
    break;
  case PW_SPECIFIC:
    XtVaSetValues(defaultViewOptionMenu, XmNmenuHistory, specificView, NULL);
    break;
  case PW_CONSTRAINT:
    XtVaSetValues(defaultViewOptionMenu, XmNmenuHistory, constraintView, NULL);
    break;
  case PW_CALLBACKS:
    XtVaSetValues(defaultViewOptionMenu, XmNmenuHistory, callbackView, NULL);
    break;
  case PW_EXTRA:
    XtVaSetValues(defaultViewOptionMenu, XmNmenuHistory, extraView, NULL);
    break;
  }

}

// ------------------------------------
// do_viewDefaultsOk()
// ------------------------------------
void 
MainWindow::do_viewDefaultsOk(Widget, XtPointer)
{
  Boolean b;
  Widget wg;
  int i;

  b = XmToggleButtonGetState(browserSmallIconToggle);
  lApp->setBrowserSmallIcons(b);
  b = XmToggleButtonGetState(browserWithIconToggle);
  lApp->setBrowserWithIcons(b);
  b = XmToggleButtonGetState(browserWithClassNameToggle);
  lApp->setBrowserWithClassName(b);
  b = XmToggleButtonGetState(browserAutomaticLoadToggle);
  lApp->setBrowserAutomaticLoad(b);

  b = XmToggleButtonGetState(menuEditSmallIconToggle);
  lApp->setMenuEditSmallIcons(b);
  b = XmToggleButtonGetState(menuEditWithIconToggle);
  lApp->setMenuEditWithIcons(b);
  b = XmToggleButtonGetState(menuEditWithClassNameToggle);
  lApp->setMenuEditWithClassName(b);
  b = XmToggleButtonGetState(menuEditAutomaticLoadToggle);
  lApp->setMenuEditAutomaticLoad(b);

  b = XmToggleButtonGetState(aeSmallIconToggle);
  lApp->setAttachmentEditorSmallIcons(b);
  b = XmToggleButtonGetState(aeWithIconToggle);
  lApp->setAttachmentEditorWithIcons(b);
  b = XmToggleButtonGetState(aeWithClassNameToggle);
  lApp->setAttachmentEditorWithClassName(b);
  b = XmToggleButtonGetState(aeAutomaticLoadToggle);
  lApp->setAttachmentEditorAutomaticLoad(b);

  b = XmToggleButtonGetState(editorAutomaticLoadToggle);
  lApp->setEditorAutomaticLoad(b);

  XtVaGetValues(defaultViewOptionMenu, XmNmenuHistory, &wg, NULL);
  XtVaGetValues(wg, XmNuserData, &i, NULL);
  lApp->setEditorDefaultView(i);
}


// ------------------------------------
// do_openGlobalResources()
// ------------------------------------
void 
MainWindow::do_openGlobalResources(Widget,XtPointer)
{
  GlobalResEditor::showView(lApp->getProject());
}
