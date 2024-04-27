/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ProjectSettings.C,v $
 *  $Date: 1999/08/27 15:31:49 $
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
 * $Log: ProjectSettings.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:49  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:17  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:30:10  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// ProjectSettings.C                      
// ------------------------------

#include "ProjectSettings.h"
#include "Lproject.h"
#include "lic.h"
#include "misc.h"
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <Xm/PushB.h>
#include <Xm/List.h>

RefArray<ProjectSettings> ProjectSettings::allViews;

// ------------------------------
// ProjectSettings()
// ------------------------------

ProjectSettings::ProjectSettings(Lproject *lp)
:ProjectSettings_base(NULL, NULL, 0), startupInterfaceView(startupOptionMenu)
{
  model = lp;
  quickHelpLabel = quickHelp;

  startupInterfaceView.setContainer(&(lp->getInterfaces()));

  RefArray<LangInfo> langs(app->getLanguages());
  for(unsigned int i=0; i<langs.getSize(); i++) {
    if(langs[i]->getName()) {
      XtVaCreateManagedWidget(langs[i]->getName(),xmPushButtonWidgetClass,
			      PSLangMenu, NULL);
    } 
  }
  XtVaSetValues(PSLangOptionMenu, XmNsubMenuId, PSLangMenu, NULL);

  XmTextSetString(PSNameText, model->getFilename());       
  XmTextSetString(PSSourceDirText, model->getSourcePath());
  if(model->getStartupInterface()) {
    startupInterfaceView.setSelected(model->getStartupInterface());   
  }

  Widget wg = XtNameToWidget(PSLangMenu, model->getLang()->getName());
  if(wg) {
    XtVaSetValues(PSLangOptionMenu, XmNmenuHistory, wg, NULL);
  }
  
  XmTextSetString(applClassText, model->getApplClass());
  XmTextSetString(execFileText, model->getExecFile());
  XmTextSetString(moreSourceText, model->getMoreSource());
  XmTextSetString(extraCompilerOptionText, model->getExtraCCOptions());
  XmTextSetString(extraLinkerOptionText, model->getExtraLDOptions());
  XmTextSetString(extraLibrariesText, model->getExtraLibraries());
  XmTextSetString(descriptionText, model->getDescription());

}

// ------------------------------
// ~ProjectSettings()
// ------------------------------
ProjectSettings::~ProjectSettings()
{
  for(unsigned int i=0; i<files.getSize(); i++) {
    delete files[i];
  }
  files.empty();
}

// ------------------------------
// wmDelete()
// ------------------------------
void ProjectSettings::wmDelete()
{
  delete this;
}

// ------------------------------
// showView()
// ------------------------------
void ProjectSettings::showView(Lproject *lp)
{
  ::ProjectSettings *view = NULL;

  for(unsigned int i=0; i<allViews.getSize(); i++) {
    if(allViews[i]->model == lp) {
      view = allViews[i];
      break;
    }
  }
  if(view == NULL)
    view = new ::ProjectSettings(lp);
  view->open();
}

// ------------------------------
// do_loseFocus()
// ------------------------------
void ProjectSettings::do_loseFocus(Widget, XtPointer)
{
  char prjName[PATH_MAX];
  char *name = XmTextGetString(PSNameText);
  
  withoutSuffix(name);
  strcpy(prjName, name);
  strcat(prjName, ".prj");
  XmTextSetString(PSNameText, prjName);

  getBasename(name);

  name[0] = toupper(name[0]);
  XmTextSetString(applClassText, name);

  name[0] = tolower(name[0]);
  XmTextSetString(execFileText, name);

  XtFree(name);
}


// ------------------------------
// PSSourceDirChanged()
// ------------------------------
void ProjectSettings::PSSourceDirChanged(Widget, XtPointer)
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


// ------------------------------
// do_setStartupInterface()
// ------------------------------
void ProjectSettings::do_setStartupInterface(Widget wg, XtPointer)
{
  printf("Callback ProjectSettings::do_setStartupInterface called by widget '%s'.\n",
         XtName(wg));
}


// ------------------------------
// do_mapMoreSourceFiles()
// ------------------------------
void ProjectSettings::do_mapMoreSourceFiles(Widget, XtPointer)
{
  char dir[PATH_MAX];
  char test[PATH_MAX];
  char suffix[PATH_MAX];
  DIR *d;
  struct dirent *dent;
  struct stat s;
  unsigned long len = sizeof(suffix);
  XmString xms, name, desc;
  char *entry, *sourceDir;

  entry = XmTextGetString(moreSourceText);
  sourceDir = XmTextGetString(PSSourceDirText);

  XmListDeleteAllItems(sourceFilesList);
  for(unsigned int i=0; i<files.getSize(); i++) {
    delete files[i];
  }
  files.empty();

  strcpy(dir, sourceDir);
  d = opendir(dir);
  if(d) {
    dent = readdir(d);
    while(dent) {
      strcpy(test, dir);
      if(strlen(test) > 0 && test[strlen(test)-1] != '/')
	strcat(test, "/");
      strcat(test, dent->d_name);
      if(stat(test, &s) > -1 && S_ISREG(s.st_mode)) {
	getSuffix(test, suffix, len);
	if(!strcmp(suffix, "c") || !strcmp(suffix, "C") || 
	   !strcmp(suffix, "cc") || !strcmp(suffix, "cpp") || 
	   !strcmp(suffix, "cxx") || !strcmp(suffix, "c++")) {
	  files.add(new Lstring(dent->d_name));
	}
      }
      dent = readdir(d);
    }
    closedir(d);
  } else {
    app->showSystemError(dir, errno);
    return;
  }

  files.sort();

  for(unsigned int i=0; i<files.getSize(); i++) {
    name = XmStringCreate(*(files[i]), "bold");
    getSuffix(*(files[i]), suffix, len);
    if(!strcmp(suffix, "c")) {
      desc = XmStringCreate(" (C)", "italic");
    } else {
      desc = XmStringCreate(" (C++)", "italic");
    }
    xms = XmStringConcat(name, desc);
    XmListAddItem(sourceFilesList, xms, 0);
    XmStringFree(xms);
    XmStringFree(name);
    XmStringFree(desc);
    
    if(strstr(entry, *(files[i]))) {
      XmListSelectPos(sourceFilesList, 0, TRUE);
    }
  }

  XtFree(entry);
}


// ------------------------------
// do_moreSourceFiles()
// ------------------------------
void ProjectSettings::do_moreSourceFiles(Widget, XtPointer)
{
  int *list;
  int n;
  unsigned long len = 0;
  char *str;

  if(XmListGetSelectedPos(sourceFilesList, &list, &n)) {
    for(int i=0; i<n; i++) {
      len += strlen(*(files[list[i]-1])) + 1;
    }
    str = new char[len];
    str[0] = 0;
    for(int i=0; i<n; i++) {
      strcat(str, *(files[list[i]-1]));
      if(i+1<n)
	strcat(str, " ");
    }
    XmTextSetString(moreSourceText, str);
    delete str;
    XtFree((char*)list);
  } else 
    XmTextSetString(moreSourceText, "");
}


// ------------------------------
// do_ok()
// ------------------------------
void ProjectSettings::do_ok(Widget, XtPointer)
{
  char *name = XmTextGetString(PSNameText);        // allocation
  char *sourcedir = XmTextGetString(PSSourceDirText);
  char *applClass = XmTextGetString(applClassText);
  char *execFile = XmTextGetString(execFileText);
  char *description = XmTextGetString(descriptionText);
  char *extraCCOptions = XmTextGetString(extraCompilerOptionText);
  char *extraLDOptions = XmTextGetString(extraLinkerOptionText);
  char *extraLibraries = XmTextGetString(extraLibrariesText);
  char *moreSource = XmTextGetString(moreSourceText);
  unsigned int i;
  Widget langWg;

  XtVaGetValues(PSLangOptionMenu,
		XmNmenuHistory, &langWg,
		NULL);
  char *langName = XtName(langWg);                // no allocation
  
  if(description) {
    model->setDescription(description);
    XtFree(description);
  }
  if(extraCCOptions) {
    model->setExtraCCOptions(extraCCOptions);
    XtFree(extraCCOptions);
  }
  if(extraLDOptions) {
    model->setExtraLDOptions(extraLDOptions);
    XtFree(extraLDOptions);
  }
  if(extraLibraries) {
    model->setExtraLibraries(extraLibraries);
    XtFree(extraLibraries);
  }
  if(moreSource) {
    model->setMoreSource(moreSource);
    XtFree(moreSource);
  }
  if(applClass) {
    model->setApplClass(applClass);
    XtFree(applClass);
  }
  if(execFile) {
    model->setExecFile(execFile);
    XtFree(execFile);
  }

  if(model->getInterfaces().getSize() && 
     startupInterfaceView.selectedIndex(i)) {
    Linterface *linterface = model->getInterfaces()[i];
    if(linterface) {
      model->setStartupInterface(linterface);
    } 
  }
  if(name) {
    char buf[PATH_MAX];
    if(strlen(name) > 0) {
      strcpy(buf, name);
      withSuffix(buf, sizeof(buf), "prj");
      model->setFilename(buf);
    } else {
      model->setFilename();
    }
    XtFree(name);
  }

  if(sourcedir) {
    char buf[PATH_MAX];
    if(strlen(sourcedir) > 0) {
      strcpy(buf, sourcedir);
      model->setSourcePath(buf);
    }
    XtFree(sourcedir);
  }

  if(langName) {
    LangInfo *lang = app->getLang(langName);
    if(lang) {
      model->setLang(lang);
    }
  }
  
  app->changed( PROJECT_CHANGED );
  model->changed(0);         // dummy to set the changed flag
  
  close();
  delete this;
}


// ------------------------------
// do_cancel()
// ------------------------------
void ProjectSettings::do_cancel(Widget, XtPointer)
{
  close();
  delete this;
}


// ------------------------------
// do_help()
// ------------------------------
void ProjectSettings::do_help(Widget, XtPointer)
{
  getHelp(HID_PROJECT_SETTINGS);
}





