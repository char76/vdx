/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: OptionMenuView.C,v $
 *  $Date: 1999/08/27 15:30:00 $
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
 * $Log: OptionMenuView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:00  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:09:34  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  19:33:22  lazy
 * Initial revision
 *
 */

#include "OptionMenuView.h"
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>

// ########################################################################

// ---------------------------------------
//     LabelView()
// ---------------------------------------

LabelView::LabelView(Widget labelWidget)
:WinView(NULL), model(NULL,this)
{
  label = labelWidget;
  if(labelWidget) {
    XtVaSetValues(label, XmNuserData, NULL, NULL);
    XtUnmanageChild(labelWidget);
  }
}

// ---------------------------------------
//     update()
// ---------------------------------------

void LabelView::update(unsigned long flags)
{
  if((flags & NAME_CHANGED) && !model.isNil() && ((Widget)label != NULL)) {
    XmString xms = XmStringCreateLtoR(model->getName(), 
				      XmSTRING_DEFAULT_CHARSET);
    XtVaSetValues(label, XmNlabelString, xms, NULL);
    XmStringFree(xms);
  }
}

// ---------------------------------------
//     setIconable()
// ---------------------------------------

void LabelView::setIconable(Iconable *m)
{
  model = m;
  changeModel(m);
  if(m) {
    XtManageChild(label);
  } else {
    XtUnmanageChild(label);
  }
  XtVaSetValues(label, XmNuserData, m, NULL);
  update(NAME_CHANGED);
}

// ---------------------------------------
//     delNotify()
// ---------------------------------------

void LabelView::delNotify(BaseRef *ref)
{
  if((ref == &model) && (Widget)label) {
    XtVaSetValues(label, XmNuserData, NULL, NULL);
    XtUnmanageChild(label);
  }
}


// ########################################################################

// ---------------------------------------
//     OptionMenuView()
// ---------------------------------------

OptionMenuView::OptionMenuView(Widget om)
:WinView(NULL), model(NULL,this)
{
  optionMenu = om;
  if(om) {
    XtSetSensitive(om, FALSE);
  }
}

// ---------------------------------------
//     ~OptionMenuView()
// ---------------------------------------

OptionMenuView::~OptionMenuView()
{
  while(partViews.getSize())
    partViews[0].Delete();
}

// ---------------------------------------
//     update()
// ---------------------------------------

void OptionMenuView::update(unsigned long flags)
{
  if((flags & CONTAINER_CHANGED) 
     && !model.isNil() && (Widget)optionMenu != NULL) {

    Widget pulldownMenu = NULL;
    Widget selected = NULL;
    unsigned int index;
    Boolean trust;

    trust = selectedIndex(index);        // save selected value

    while(partViews.getSize())
      partViews[0].Delete();

    XtVaGetValues(optionMenu, XmNsubMenuId, &pulldownMenu, NULL);
    if(pulldownMenu) {
      XtDestroyWidget(pulldownMenu);
    }
    pulldownMenu = XmCreatePulldownMenu(optionMenu, "Pulldown", NULL, 0);
    
    for(unsigned int i=0; i<model->getSize(); i++) {
      Widget wg;
      LabelView *labelView;
      XmString name;

      name = XmStringCreateLtoR(model->at(i)->getName(), 
				XmSTRING_DEFAULT_CHARSET);
      wg = XtVaCreateManagedWidget(model->at(i)->getName(),
				   xmPushButtonWidgetClass, pulldownMenu,
				   XmNuserData, NULL,
				   XmNlabelString, name,
				   NULL);
      XmStringFree(name);
      labelView = new LabelView(wg);
      labelView->setIconable(model->at(i));
      partViews.add(labelView);

      if(i == index)
	selected = wg;
    }
    if(model->getSize() == 0) {
      Widget wg;
      wg = XtVaCreateManagedWidget("empty",
				   xmPushButtonWidgetClass, pulldownMenu,
				   XmNuserData, NULL,
				   NULL);
      XtSetSensitive(optionMenu, FALSE);
    } else {
      XtSetSensitive(optionMenu, TRUE);
    }
    XtVaSetValues(optionMenu,
		  XmNmenuHistory, selected,
		  XmNsubMenuId, pulldownMenu,
		  NULL);
  }
}
  
// ---------------------------------------
//     setContainer()
// ---------------------------------------

void OptionMenuView::setContainer(ContainerBase *m)
{
  model = m;
  update(CONTAINER_CHANGED);
  changeModel(m);
  XtSetSensitive(optionMenu, (m != NULL) && (m->getSize() > 0));
}

// ---------------------------------------
//     selectedIndex()
// ---------------------------------------

Boolean OptionMenuView::selectedIndex(unsigned int &ret)
{
  if((Widget)optionMenu != NULL) {
    Widget wg = NULL;
    
    XtVaGetValues(optionMenu, XmNmenuHistory, &wg, NULL);
    if(wg) {
      Iconable *m;
      XtVaGetValues(wg, XmNuserData, &m, NULL);
      for(unsigned int i=0; i<model->getSize(); i++) {
	if(model->at(i) == m) {
	  ret = i;
	  return TRUE;
	}
      }
    }
  }
  return FALSE;
}


// ---------------------------------------
//     delNotify()
// ---------------------------------------

void OptionMenuView::delNotify(BaseRef *ref)
{
  if((ref == &model) && (Widget)optionMenu) {
    XtSetSensitive(optionMenu, FALSE);
  }
}



// ---------------------------------------
//     setSelected()
// ---------------------------------------

void OptionMenuView::setSelected(Iconable *s)
{
  if((Widget)optionMenu != NULL) {
    Widget wg = NULL;
    Iconable *m;

    for(unsigned int i=0; i<partViews.getSize(); i++) {
      wg = partViews[i]->getWidget();
      if(wg) {
	XtVaGetValues(wg, XmNuserData, &m, NULL);
	if(m == s) {
	  XtVaSetValues(optionMenu, XmNmenuHistory, wg, NULL);
	  return;
	}
      }
    }
  }
}

