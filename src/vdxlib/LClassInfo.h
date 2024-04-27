/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LClassInfo.h,v $
 *  $Date: 1999/08/27 15:33:21 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997 1998, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Muehlenpfordtstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: LClassInfo.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:21  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:53  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:10:20  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1998/01/17 18:55:07  lazy
 * Initial revision
 *
 */

#include <X11/IntrinsicP.h>

enum ManagePolicy {
  NEVER_MANAGE,                // e.g. Popup menus
  DIALOG_MANAGE,               // e.g. XmFormDialog
  NORMAL_MANAGE                // the other widgets
};

enum UpdatePolicy {
  // Update when a child needs an update. e.g. RowColumn because the
  // childs order is important, so all children must be recreated.
  ON_CHILD_UPDATE,             
  // When a child needs an update, the parent do not need it.
  NO_ON_CHILD_UPDATE     
};
  

struct LClassInfo {

  // A String describing the category e.g. Xrt. This will help to find the
  // widget class in menus. (The category is currently use be the browsers
  // Create menu)
  String category;              

  // The pointer to widget class record, e.g. xmPushButtonWidgetClass. 
  // If you add an coventient widget class and set the create_func 
  // this must be NULL.
  WidgetClass widget_class;     

  // The same but as a string. Needed by code generation.
  String widget_class_str;      

  // If the widget class is a convenient widget class, the create function
  // must be specified, e.g. XmCreatePopupMenu. Otherwise NULL
  Widget (*create_func)(Widget,char*,ArgList,Cardinal);

  // The same as above but a string. Needed by code generation
  String create_func_str;
  
  // The header file that declares the widget class,
  // e.g. "<Xm/PushB.h>" Needed by code generation
  String header_file;

  // Filename of the pixmap. XFILESEARCHPATH is used to find it.
  String pixmap;

  // Specify how the widget is managed.
  // - NEVER_MANAGE, never manage the widget in WYSIWYG view.
  // - DIALOG_MANAGER, widget is unmanaged in WYSIWYG view, but
  //   its visibility can be changed by the context menu.
  // - NORMAL_MANAGE, widget is managed.
  ManagePolicy managePolicy;

  // Specifiy how the WYSIWYG view is updated. If the layout of the children
  // depends on the order of creation, set this to ON_CHILD_UPDATE, otherwise
  // NO_ON_CHILD_UPDATE.
  UpdatePolicy updatePolicy;
  
  // If the widget is created without specifing the width and height,
  // the widget determines its size, e.g. a Label widget has always its
  // min size to display the labelString. A Frame widget will have zero width
  // and height, so it will be unvisible in the WYSIWYG view. Specify TRUE
  // for these widget classes. They will get a width and height of 100.
  Boolean defaultSize;
};

// -----------------------------------------
// getVdxClassInfo() - Return the Array
//
// This function is used by VDX to determine
// the ClassInfo array.
// -----------------------------------------


LClassInfo *getVdxClassInfo();









