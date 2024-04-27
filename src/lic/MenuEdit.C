/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MenuEdit.C,v $
 *  $Date: 1999/08/27 15:31:44 $
 *  $Revision: 1.1.1.1.2.2 $
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
 * $Log: MenuEdit.C,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:31:44  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:45  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:29:33  lazy
 * Initial revision
 *
 */

#include "lic.h"
#include "MenuEdit.h"
#include "Lcreator.h"
#include "Lwhere.h"
#include <Xm/Xm.h>
#include <Xm/ToggleB.h>

#define PUSH_BUTTON_NAME    "XmPushButton"
#define TOGGLE_BUTTON_NAME  "XmToggleButton"
#define LABEL_NAME          "XmLabel"
#define SEPARATOR_NAME      "XmSeparator"
#define CASCADE_NAME        "XmCascadeButton"
#define ROW_COLUMN_NAME     "XmRowColumn"
#define POPUP_NAME          "XmCreatePopupMenu"
#define PULLDOWN_NAME       "XmCreatePulldownMenu"
#define RADIOBOX_NAME       "XmCreateRadioBox"
#define MENUBAR_NAME        "XmCreateMenuBar"

#define CASCADE_RESOURCE_NAME "subMenuId"


RefArray<MenuEdit> MenuEdit::allViews;
Ref<MenuEdit> MenuEdit::automaticLoadView;


// --------------------------------------------
//                 MenuEdit()
// --------------------------------------------

MenuEdit::MenuEdit(Lwidget *lw) 
: selectionCallback(this), model(lw)
{
  quickHelpLabel = quickHelp;

  Selectable::selectionCallbacks.add(&selectionCallback);

  allViews.add(this);

  iconView = new WidgetIconView(model, iconViewFrame);
  iconView->setOneRow(TRUE);
  XtManageChild(iconView->getTop());

  setWidget(model);
  setGeometryModel(app);

  controllerImpl.add(editButton, LWIDGET_EDIT);
  controllerImpl.add(browseButton, LWIDGET_BROWSE);
  controllerImpl.add(menuEditButton, LWIDGET_MENUEDIT);
  controllerImpl.add(cutButton, LWIDGET_CUT);
  controllerImpl.add(copyButton, LWIDGET_COPY);
  controllerImpl.add(pasteButton, LWIDGET_PASTE);
  controllerImpl.add(deleteButton, LWIDGET_DELETE);

  XmToggleButtonSetState(automaticLoadButton, 
			 app->getMenuEditAutomaticLoad(), TRUE);
  XmToggleButtonSetState(withClassNameButton, TRUE, FALSE);
  XmToggleButtonSetState(withClassNameButton, 
			 app->getMenuEditWithClassName(), TRUE);
  XmToggleButtonSetState(smallIconButton, 
			 app->getMenuEditSmallIcons(), TRUE);
  XmToggleButtonSetState(withIconButton, TRUE, FALSE);
  XmToggleButtonSetState(withIconButton, 
			 app->getMenuEditWithIcons(), TRUE);

}


// ------------------------------
// setWidget()
// ------------------------------

void MenuEdit::setWidget(Lwidget *m)
{
  this->model = m;
  setModel(m);
  iconView->setModel(m);

  XtSetSensitive(addPushButtonLazy, 
		 model->getClass()->
		 asChildOk(Lcreator::getClass(PUSH_BUTTON_NAME)));

  XtSetSensitive(addToggleButtonButton, 
		 model->getClass()->
		 asChildOk(Lcreator::getClass(TOGGLE_BUTTON_NAME)));

  XtSetSensitive(addLabelButton, 
		 model->getClass()->
		 asChildOk(Lcreator::getClass(LABEL_NAME)));

  XtSetSensitive(addSeparatorButton, 
		 model->getClass()->
		 asChildOk(Lcreator::getClass(SEPARATOR_NAME)));

  XtSetSensitive(addSubMenuButton, 
		 model->getClass()->
		 asChildOk(Lcreator::getClass(CASCADE_NAME)));

  selectionCallback.call();
  if(model->getParent() && isOfValidClass(model->getParent()))
    XtSetSensitive(loadParentButton, TRUE);
  else
    XtSetSensitive(loadParentButton, FALSE);

  update(NAME_CHANGED);
}

// --------------------------------------------
//                 showEditor()
// --------------------------------------------

MenuEdit *MenuEdit::showEditor(Lwidget *lw) 
{
  ::MenuEdit *ret = NULL;

  if(!automaticLoadView.isNil()) {
    ret = automaticLoadView;
    ret->setWidget(lw);
  } else {
    for(unsigned int i=0; i<allViews.getSize(); i++) {
      if(allViews[i]->model == lw) {
	ret = allViews[i];
	break;
      }
    }
  }

  if(ret == NULL) 
    ret = new ::MenuEdit(lw);

  ret ->open();

  return ret;
}

// --------------------------------------------
//                 ~MenuEdit()
// --------------------------------------------

MenuEdit::~MenuEdit()
{
  if(!iconView.isNil())
    iconView.Delete();
}

// --------------------------------------------
//                 isOfValidClass()
// --------------------------------------------

Boolean MenuEdit::isOfValidClass(Lwidget* lw)
{
  Lcreator *lclass;
  lclass = lw->getClass();
  if(lclass) {
    if(!strcmp(lclass->getName(),ROW_COLUMN_NAME)) 
      return TRUE;
    if(!strcmp(lclass->getName(),PULLDOWN_NAME)) 
      return TRUE;
    if(!strcmp(lclass->getName(),POPUP_NAME)) 
      return TRUE;
    if(!strcmp(lclass->getName(),RADIOBOX_NAME)) 
      return TRUE;
    if(!strcmp(lclass->getName(),MENUBAR_NAME)) 
      return TRUE;
  }
  return FALSE;
}


// --------------------------------------------
//                 update()
// --------------------------------------------

void MenuEdit::update( unsigned long flags ) 
{
  if( flags & NAME_CHANGED ) {
    if( Widget(popupShell) ) {
      char title[256];
      msgCat->getMsg(title, MENU_EDIT_TITLE, 
		     model->getName(), 
		     model->getClass()->getName() );
      XtVaSetValues(popupShell, 
		    XmNtitle, title,
		    XmNiconName, title,
		    NULL );
    }
  }
}

// --------------------------------------------
//                 moveUp()
// --------------------------------------------

void MenuEdit::moveUp(Widget, XtPointer)
{
  char msgTitle[256];
  char msgText[1024];
  
  msgCat->getMsg( msgTitle, ERROR_MENUEDIT_TITLE );
  msgCat->getMsg( msgText, ERROR_MENUEDIT_MSG );

  if( strcmp(Selectable::getCurrentClass(), model->getClassName()) ) {
    LicView::MsgBox(msgTitle, msgText, MSGBOX_STYLE_OK);
    return;
  }

  RefArray<Selectable> selection( Selectable::getSelection() );

  if( selection.getSize() != 1 ) {
    LicView::MsgBox(msgTitle, msgText, MSGBOX_STYLE_OK);
    return;
  }
  
  for( unsigned int i=0 ; i<model->getChildren().getSize(); i++ ) {
    if(model->getChildren()[i]==(Lwidget*)(Selectable*)selection[0]) {
      if(i>0) {
	Lwidget *before = model->getChildren()[i-1];
	Lwidget *toInsert = model->getChildren()[i];
	model->getChildren().remove(toInsert);
	model->getChildren().insert(toInsert,before);
	model->changed(CONTAINER_CHANGED);
      }
      return;
    }
  }
  LicView::MsgBox(msgTitle, msgText, MSGBOX_STYLE_OK);
}


// --------------------------------------------
//                 moveDown()
// --------------------------------------------

void MenuEdit::moveDown(Widget, XtPointer)
{
  char msgTitle[256];
  char msgText[1024];
  
  msgCat->getMsg( msgTitle, ERROR_MENUEDIT_TITLE );
  msgCat->getMsg( msgText, ERROR_MENUEDIT_MSG );

  if( strcmp(Selectable::getCurrentClass(), model->getClassName()) ) {
    LicView::MsgBox(msgTitle, msgText, MSGBOX_STYLE_OK);
    return;
  }

  RefArray<Selectable> selection( Selectable::getSelection() );

  if( selection.getSize() != 1 ) {
    LicView::MsgBox(msgTitle, msgText, MSGBOX_STYLE_OK);
    return;
  }
  
  for( unsigned int i=0 ; i<model->getChildren().getSize(); i++ ) {
    if(model->getChildren()[i]==(Lwidget*)(Selectable*)selection[0]) {
      if(i < model->getChildren().getSize()-1) {
	Lwidget *before = (i != model->getChildren().getSize()-2) ?
	  (Lwidget*)model->getChildren()[i+2] : (Lwidget*)NULL ; 
	Lwidget *toInsert = model->getChildren()[i];
	model->getChildren().remove(toInsert);
	model->getChildren().insert(toInsert,before);
	model->changed(CONTAINER_CHANGED);
      }
      return;
    }
  }
  LicView::MsgBox(msgTitle, msgText, MSGBOX_STYLE_OK);
}


// --------------------------------------------
//                 addLabel()
// --------------------------------------------

void MenuEdit::addLabel(Widget, XtPointer)
{
  Lcreator *lclass;

  lclass = Lcreator::getClass(LABEL_NAME);
  if( lclass ) {
    Lwhere where;
    where.setparent(model);
    new Lwidget( lclass, "label", where );
    model->changed(CONTAINER_CHANGED);
  }
}


// --------------------------------------------
//                 addPushButton()
// --------------------------------------------

void MenuEdit::addPushbutton(Widget, XtPointer)
{
  Lcreator *lclass;

  lclass = Lcreator::getClass(PUSH_BUTTON_NAME);
  if( lclass ) {
    Lwhere where;
    where.setparent(model);
    new Lwidget( lclass, "pushButton", where );
    model->changed(CONTAINER_CHANGED);
  }
}


// --------------------------------------------
//                 addSeparator()
// --------------------------------------------

void MenuEdit::addSeparator(Widget, XtPointer)
{
  Lcreator *lclass;

  lclass = Lcreator::getClass(SEPARATOR_NAME);
  if( lclass ) {
    Lwhere where;
    where.setparent(model);
    new Lwidget( lclass, "separator", where );
    model->changed(CONTAINER_CHANGED);
  }
}


// --------------------------------------------
//                 addToggleButton()
// --------------------------------------------

void MenuEdit::addToggleButton(Widget, XtPointer)
{
  Lcreator *lclass;

  lclass = Lcreator::getClass(TOGGLE_BUTTON_NAME);
  if( lclass ) {
    Lwhere where;
    where.setparent(model);
    new Lwidget( lclass, "toggleButton", where );
    model->changed(CONTAINER_CHANGED);
  }
}


// --------------------------------------------
//                 addSubMenu()
// --------------------------------------------

void MenuEdit::addSubMenu(Widget, XtPointer)
{
  Lwidget *cascade, *pulldown;
  Lcreator *cascadeClass, *pulldownClass;

  cascadeClass = Lcreator::getClass(CASCADE_NAME);
  pulldownClass = Lcreator::getClass(PULLDOWN_NAME);
  if( cascadeClass && pulldownClass ) {
    Lwhere where;
    where.setparent(model);
    cascade = new Lwidget(cascadeClass,"cascadeButton",where);
    pulldown = new Lwidget(pulldownClass, "pulldownMenu",where);
    cascade->getProperties()->setResource(CASCADE_RESOURCE_NAME,
					  pulldown->getName());
    model->changed(CONTAINER_CHANGED);
  }
}




// ----------------------------
// do_load()
// ----------------------------
void MenuEdit::do_load(Widget,XtPointer)
{
  RefArray<Selectable> selection(Selectable::getSelection());
  
  if(!strcmp(Selectable::getCurrentClass(), "Linterface")
     && selection.getSize() > 0) {
    Linterface *linterface = (Linterface*)(Selectable*)selection[0];
    if(isOfValidClass(linterface->getShell()))
      setWidget(linterface->getShell());
  } else if(!strcmp(Selectable::getCurrentClass(), "Lwidget")
	    && selection.getSize() > 0) {
    Lwidget *lwidget = (Lwidget*)(Selectable*)selection[0];
    if(isOfValidClass(lwidget))
      setWidget(lwidget);
  }
}


// ----------------------------
// do_loadParent()
// ----------------------------
void MenuEdit::do_loadParent(Widget,XtPointer)
{
  Lwidget *lwidget;

  lwidget = model->getParent();
  if(lwidget && !strcmp(lwidget->getClassName(), "Lwidget") 
     && isOfValidClass(lwidget))
    setWidget(lwidget);
}


// ----------------------------
// do_close()
// ----------------------------
void MenuEdit::do_close(Widget,XtPointer)
{
  close();
  delete this;
}

// ----------------------------
// do_smallIcon()
// ----------------------------
void MenuEdit::do_smallIcon(Widget wg,XtPointer)
{
  iconView->setWithSmallIcons(XmToggleButtonGetState(wg));
}


// ----------------------------
// do_withIcon()
// ----------------------------
void MenuEdit::do_withIcon(Widget wg,XtPointer)
{
  iconView->setWithIcons(XmToggleButtonGetState(wg));
}

// ----------------------------
// do_withClassName()
// ----------------------------
void MenuEdit::do_withClassName(Widget,XtPointer)
{
  iconView->setWithClasses(XmToggleButtonGetState(withClassNameButton));
}

// ----------------------------
// do_widgetMenuMap()
// ----------------------------
void MenuEdit::do_widgetMenuMap(Widget,XtPointer)
{
  controllerImpl.process(iconView);
}

// ----------------------------
// do_onHelp()
// ----------------------------
void MenuEdit::do_onHelp(Widget,XtPointer)
{
  getHelp(HID_USING_HELP);
}

// ----------------------------
// do_onContext()
// ----------------------------
void MenuEdit::do_onContext(Widget,XtPointer)
{
  contextHelp();
}

// ----------------------------
// do_help()
// ----------------------------
void MenuEdit::do_help(Widget,XtPointer)
{
  getHelp(HID_MENU_EDITOR);
}

// ----------------------------
// do_automaticLoad()
// ----------------------------
void MenuEdit::do_automaticLoad(Widget,XtPointer)
{
  if(XmToggleButtonGetState(automaticLoadButton)) {
    if(!automaticLoadView.isNil())
      XmToggleButtonSetState(automaticLoadView->automaticLoadButton, FALSE,
			     TRUE);
    automaticLoadView = this;
  } else {
    automaticLoadView = NULL;
  }
}

// ----------------------------
// SelectionCallback::call
// ----------------------------
void
MenuEdit::SelectionCallback::call()
{
  RefArray<Selectable> selection(Selectable::getSelection());
  if(!strcmp(Selectable::getCurrentClass(), "Lwidget")
     && selection.getSize() == 1) {
    Lwidget *lwidget = (Lwidget*)(Selectable*)selection[0];
    if(MenuEdit::isOfValidClass(lwidget)) {
      XtSetSensitive(parent->loadButton, TRUE);
    } else {
      XtSetSensitive(parent->loadButton, FALSE);
    }
    if(parent->model->getSize() > 1) {
      if(lwidget->getParent() == parent->model) {
	if(lwidget == parent->model->getChildren()[0]) {
	  XtSetSensitive(parent->ArrowUp, FALSE);
	} else {
	  XtSetSensitive(parent->ArrowUp, TRUE);
	}
	if(lwidget == 
	   parent->model->getChildren()[parent->model->getSize()-1]) {
	  XtSetSensitive(parent->ArrowDown, FALSE);
	} else {
	  XtSetSensitive(parent->ArrowDown, TRUE);
	}
      } else {
	XtSetSensitive(parent->ArrowUp, FALSE);
	XtSetSensitive(parent->ArrowDown, FALSE);
      }
    }
  } else {
    XtSetSensitive(parent->loadButton, FALSE);
    XtSetSensitive(parent->ArrowUp, FALSE);
    XtSetSensitive(parent->ArrowDown, FALSE);
  }
}
