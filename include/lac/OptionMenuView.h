/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: OptionMenuView.h,v $
 *  $Date: 1999/08/27 15:30:01 $
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
 * $Log: OptionMenuView.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:01  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:09:36  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  19:33:27  lazy
 * Initial revision
 *
 */

#ifndef _OPTIONMENUVIEW_H_
#define _OPTIONMENUVIEW_H_

#include <lac/View.h>
#include <lac/WidgetRef.h>
#include <lac/ConModel.h>


class LabelView : public WinView {
protected:
  WidgetRef label;
  Ref<Iconable> model;
  
  void update(unsigned long flags);
  Boolean destroyFromModel() { return False; }
  void delNotify(BaseRef *ref);
  void act(char *){}

public:
  LabelView(Widget labelWidget);

  void setIconable(Iconable *m);
  Widget getWidget() { return label; }
};


class OptionMenuView : public WinView {
protected:
  WidgetRef optionMenu;
  Ref<ContainerBase> model;
  RefArray<LabelView> partViews;

  void update(unsigned long flags);
  Boolean destroyFromModel() { return False; }
  void delNotify(BaseRef *ref);
  void act(char *){}

public:
  OptionMenuView(Widget om);
  ~OptionMenuView();

  void setContainer(ContainerBase *m);
  Boolean selectedIndex(unsigned int &ret);
  void setSelected(Iconable *s);
};


#endif
