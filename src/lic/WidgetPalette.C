/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidgetPalette.C,v $
 *  $Date: 1999/08/27 15:32:25 $
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
 * $Log: WidgetPalette.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:25  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:51  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:37:14  lazy
 * Initial revision
 *
 */

#include "WidgetPalette.h"
#include "Lcreator.h"
#include <Xm/ToggleB.h>
#include "lic_hlp.h"
#include "LApp.h"

#define PALETTE_SPACING  4
#define PALETTE_SHADOW   4

#define VD_SHOW_SHELLS "ShowShells"
#define VD_SHOW_MANAGERS "ShowManagers"
#define VD_SHOW_PRIMITIVES "ShowPrimitives"
#define VD_SHOW_DIALOGS "ShowDialogs"
#define VD_SHELLS_HEIGHT "ShellsHeight"
#define VD_MANAGERS_HEIGHT "ManagersHeight"
#define VD_PRIMITIVES_HEIGHT "PrimitivesHeight"
#define VD_DIALOGS_HEIGHT "DialogsHeight"
#define VD_WITH_NAMES "WithNames"
#define VD_WITH_ICONS "WithIcons"
#define VD_CREATE_ON_CLICK "CreateOnClick"
#define VD_AS_CHILD "AsChild"

// -----------------------------
//        WidgetPalette()
// -----------------------------

WidgetPalette::WidgetPalette(LApp *m)
:WidgetPalette_base(NULL, NULL, 0) 
{
  Boolean b;
  long l;

  quickHelpLabel = quickHelp;

  model = m;

  setModel(model);
  
  b = TRUE;
  if(model->getVDBoolean(this, VD_SHOW_SHELLS, b)) {
    if(b)
      XtManageChild(ShellForm);
    else
      XtUnmanageChild(ShellForm);
  }
  XmToggleButtonSetState(shellsButton, b, FALSE);

  b = TRUE;
  if(model->getVDBoolean(this, VD_SHOW_MANAGERS, b)) {
    if(b)
      XtManageChild(ManagerForm);
    else
      XtUnmanageChild(ManagerForm);
  }
  XmToggleButtonSetState(managersButton, b, FALSE);

  b = TRUE;
  if(model->getVDBoolean(this, VD_SHOW_PRIMITIVES, b)) {
    if(b)
      XtManageChild(PrimitiveForm);
    else
      XtUnmanageChild(PrimitiveForm);
  }
  XmToggleButtonSetState(primitivesButton, b, FALSE);

  b = TRUE;
  if(model->getVDBoolean(this, VD_SHOW_DIALOGS, b)) {
    if(b)
      XtManageChild(DialogForm);
    else
      XtUnmanageChild(DialogForm);
  }
  XmToggleButtonSetState(dialogsButton, b, FALSE);
  
  if(model->getVDLong(this, VD_SHELLS_HEIGHT, l))
    XtVaSetValues(ShellForm, XmNheight, l, NULL);

  if(model->getVDLong(this, VD_MANAGERS_HEIGHT, l))
    XtVaSetValues(ManagerForm, XmNheight, l, NULL);

  if(model->getVDLong(this, VD_PRIMITIVES_HEIGHT, l))
    XtVaSetValues(PrimitiveForm, XmNheight, l, NULL);

  if(model->getVDLong(this, VD_DIALOGS_HEIGHT, l))
    XtVaSetValues(DialogForm, XmNheight, l, NULL);

  // IconView fuer Shell-Klassen

  shellIconView = new LcreatorIconView(&Lcreator::getShells(),
				       ShellForm, 
				       new LcreatorIcon());
  shellIconView->setWithNames(FALSE);
  shellIconView->setSpacing(PALETTE_SPACING);
  shellIconView->setShadow(PALETTE_SHADOW);
  shellIconView->setQuickHelpLabel(quickHelp);
  shellIconView->setBubbleHelp(TRUE);
  XtManageChild(shellIconView->getTop());

  XtVaSetValues( shellIconView->getTop(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 5,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopOffset, 5,
		XmNtopWidget, ShellLabel,
		XmNrightAttachment, XmATTACH_FORM,
		XmNrightOffset, 5,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNbottomOffset, 5,
		NULL );

  // Manager-Klassen

  managerIconView = new LcreatorIconView(&Lcreator::getManager(),
					 ManagerForm, 
					 new LcreatorIcon());
  managerIconView->setWithNames(FALSE);
  managerIconView->setSpacing(PALETTE_SPACING);
  managerIconView->setShadow(PALETTE_SHADOW);
  managerIconView->setQuickHelpLabel(quickHelp);
  managerIconView->setBubbleHelp(TRUE);
  XtManageChild(managerIconView->getTop());

  XtVaSetValues( managerIconView->getTop(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 5,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopOffset, 5,
		XmNtopWidget, ManagerLabel,
		XmNrightAttachment, XmATTACH_FORM,
		XmNrightOffset, 5,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNbottomOffset, 5,
		NULL );

  primitiveIconView = new LcreatorIconView(&Lcreator::getPrimitives(),
					   PrimitiveForm, 
					   new LcreatorIcon());
  primitiveIconView->setWithNames(FALSE);
  primitiveIconView->setSpacing(PALETTE_SPACING);
  primitiveIconView->setShadow(PALETTE_SHADOW);
  primitiveIconView->setQuickHelpLabel(quickHelp);
  primitiveIconView->setBubbleHelp(TRUE);
  XtManageChild(primitiveIconView->getTop());

  XtVaSetValues( primitiveIconView->getTop(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 5,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopOffset, 5,
		XmNtopWidget, PrimitiveLabel,
		XmNrightAttachment, XmATTACH_FORM,
		XmNrightOffset, 5,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNbottomOffset, 5,
		NULL );

  // Dialogs

  dialogIconView = new LcreatorIconView(&Lcreator::getDialogs(),
					DialogForm, 
					new LcreatorIcon());
  dialogIconView->setWithNames(FALSE);
  dialogIconView->setSpacing(PALETTE_SPACING);
  dialogIconView->setShadow(PALETTE_SHADOW);
  dialogIconView->setQuickHelpLabel(quickHelp);
  dialogIconView->setBubbleHelp(TRUE);
  XtManageChild(dialogIconView->getTop());

  XtVaSetValues( dialogIconView->getTop(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 5,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopOffset, 5,
		XmNtopWidget, DialogLabel,
		XmNrightAttachment, XmATTACH_FORM,
		XmNrightOffset, 5,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNbottomOffset, 5,
		NULL );

  b = FALSE;
  model->getVDBoolean(this, VD_WITH_NAMES, b);
  XmToggleButtonSetState(withNamesButton, b, TRUE);

  b = TRUE;
  model->getVDBoolean(this, VD_WITH_ICONS, b);
  XmToggleButtonSetState(withIconsButton, b, TRUE);

  b = TRUE;
  model->getVDBoolean(this, VD_CREATE_ON_CLICK, b);
  XmToggleButtonSetState(createOnClickButton, b, TRUE);

  b = FALSE;
  model->getVDBoolean(this, VD_AS_CHILD, b);
  XmToggleButtonSetState(asChildOfSelectedButton, b, TRUE);
  
}

// ------------------------
//     ~WidgetPalette()
// ------------------------

WidgetPalette::~WidgetPalette() 
{

  if( !shellIconView.isNil() )
    shellIconView.Delete();
  if( !managerIconView.isNil() )
    managerIconView.Delete();
  if( !primitiveIconView.isNil() )
    primitiveIconView.Delete();
  if( !dialogIconView.isNil() )
    dialogIconView.Delete();


}

// ------------------------
//     act()
// ------------------------

void WidgetPalette::act(char *)
{
}

// ------------------------
//     do_close()
// ------------------------

void WidgetPalette::do_close(Widget, XtPointer)
{
  close();
}

// ------------------------
//     beforeClose()
// ------------------------

void 
WidgetPalette::beforeClose()
{
  long height;

  model->setVDBoolean(this, VD_SHOW_SHELLS, XtIsManaged(ShellForm));
  model->setVDBoolean(this, VD_SHOW_MANAGERS, XtIsManaged(ManagerForm));
  model->setVDBoolean(this, VD_SHOW_PRIMITIVES, XtIsManaged(PrimitiveForm));
  model->setVDBoolean(this, VD_SHOW_DIALOGS, XtIsManaged(DialogForm));
  
  XtVaGetValues(ShellForm, XmNheight, &height, NULL);
  model->setVDLong(this, VD_SHELLS_HEIGHT, height);
  XtVaGetValues(ManagerForm, XmNheight, &height, NULL);
  model->setVDLong(this, VD_MANAGERS_HEIGHT, height);
  XtVaGetValues(PrimitiveForm, XmNheight, &height, NULL);
  model->setVDLong(this, VD_PRIMITIVES_HEIGHT, height);
  XtVaGetValues(DialogForm, XmNheight, &height, NULL);
  model->setVDLong(this, VD_DIALOGS_HEIGHT, height);

  model->setVDBoolean(this, VD_WITH_NAMES, 
		      XmToggleButtonGetState(withNamesButton));
  model->setVDBoolean(this, VD_WITH_ICONS, 
		      XmToggleButtonGetState(withIconsButton));
  model->setVDBoolean(this, VD_CREATE_ON_CLICK, 
		      XmToggleButtonGetState(createOnClickButton));
  model->setVDBoolean(this, VD_AS_CHILD, 
		      XmToggleButtonGetState(asChildOfSelectedButton));
}

// ------------------------
//     do_help()
// ------------------------

void WidgetPalette::do_help(Widget, XtPointer)
{
  getHelp(HID_WIDGET_PALETTE);
}


// ------------------------
//     do_viewEntry()
// ------------------------

void 
WidgetPalette::do_viewEntry(Widget,XtPointer callData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callData;
  
  if(cbs->widget == withNamesButton) {
    if(XmToggleButtonGetState(cbs->widget)) {
      shellIconView->setWithNames(TRUE);
      managerIconView->setWithNames(TRUE);
      primitiveIconView->setWithNames(TRUE);
      dialogIconView->setWithNames(TRUE);
    } else {
      shellIconView->setWithNames(FALSE);
      managerIconView->setWithNames(FALSE);
      primitiveIconView->setWithNames(FALSE);
      dialogIconView->setWithNames(FALSE);
      XmToggleButtonSetState(withIconsButton, TRUE, TRUE);
    }
  } else if(cbs->widget == withIconsButton) {
    if(XmToggleButtonGetState(cbs->widget)) {
      shellIconView->setWithIcons(TRUE);
      managerIconView->setWithIcons(TRUE);
      primitiveIconView->setWithIcons(TRUE);
      dialogIconView->setWithIcons(TRUE);
    } else {
      shellIconView->setWithIcons(FALSE);
      managerIconView->setWithIcons(FALSE);
      primitiveIconView->setWithIcons(FALSE);
      dialogIconView->setWithIcons(FALSE);
      XmToggleButtonSetState(withNamesButton, TRUE, TRUE);
    }
  } else if(cbs->widget == shellsButton) {
    if(XmToggleButtonGetState(cbs->widget)) {
      XtManageChild(ShellForm);
    } else {
      XtUnmanageChild(ShellForm);
    }
  } else if(cbs->widget == managersButton) {
    if(XmToggleButtonGetState(cbs->widget)) {
      XtManageChild(ManagerForm);
    } else {
      XtUnmanageChild(ManagerForm);
    }
  } else if(cbs->widget == primitivesButton) {
    if(XmToggleButtonGetState(cbs->widget)) {
      XtManageChild(PrimitiveForm);
    } else {
      XtUnmanageChild(PrimitiveForm);
    }
  } else if(cbs->widget == dialogsButton) {
    if(XmToggleButtonGetState(cbs->widget)) {
      XtManageChild(DialogForm);
    } else {
      XtUnmanageChild(DialogForm);
    }
  }

}

// ------------------------
//     do_optionsEntry()
// ------------------------

void 
WidgetPalette::do_optionsEntry(Widget,XtPointer callData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callData;
  Boolean b;

  if(cbs->widget == createOnClickButton) {
    b = XmToggleButtonGetState(cbs->widget);
    shellIconView->setCreateOnClick(b);
    managerIconView->setCreateOnClick(b);
    primitiveIconView->setCreateOnClick(b);
    dialogIconView->setCreateOnClick(b);
  } else if(cbs->widget == asChildOfSelectedButton) {
    b = XmToggleButtonGetState(cbs->widget);
    shellIconView->setAsChildOfSelected(b);
    managerIconView->setAsChildOfSelected(b);
    primitiveIconView->setAsChildOfSelected(b);
    dialogIconView->setAsChildOfSelected(b);
  }
}

// ------------------------
//     do_onHelp()
// ------------------------

void 
WidgetPalette::do_onHelp(Widget,XtPointer)
{
  getHelp(HID_USING_HELP);
}

// ------------------------
//     do_onContext()
// ------------------------

void 
WidgetPalette::do_onContext(Widget,XtPointer)
{
  contextHelp();
}
