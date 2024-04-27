/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TreeView.h,v $
 *  $Date: 1999/08/27 15:30:24 $
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
 * $Log: TreeView.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:24  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.3  1997/09/11  14:57:02  lazy
 * processKey() and traverse*() inserted.
 *
 * Revision 1.2  1997/07/25  19:49:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:13:51  lazy
 * Initial revision
 *
 */

// --------------------------------
// TreeView.h
//
// (C) Dirk Laessig
// -------------------------------

#ifndef _TREEVIEW_H_
#define _TREEVIEW_H_

#include <lac/TreeNode.h>
#include <lac/View.h>
#include <lac/SensitiveView.h>

// --------------------------------
// TreeNodeView
// --------------------------------
class TreeView;

class TreeNodeView : public SensitiveRec  {
private:
  class ExpandIcon : public StatePixmapRecView {
  private:
    TreeNodeBase *m;
    TreeNodeView *parentObject;
    enum { COLLAPSE, EXPAND };
  public:
    ExpandIcon(TreeNodeBase *m, TreeNodeView *tnv);
    void update(unsigned long flags);
  };

private:
  TreeNodeBase *m;
  Dimension width, height;

  RefArray<TreeNodeView> children;
  Rec fullRec;                      // groesse mit Kindern

  Ref<ExpandIcon>    expandIcon;
  Ref<PixmapRecView> pixmap;
  Ref<TextRecView>   text;
  
  TreeView *treeView;
  TreeNodeView *treeNodeViewParent;

  Boolean withChildren;
  
protected:
  Dimension intentX, intentY;       // kann durch ableiten veraendert werden

  virtual void traverseUp();
  virtual void traverseDown();
  virtual void traverseLeft();
  virtual void traverseRight();

public:
  TreeNodeView(TreeView *treeView, TreeNodeView *p, TreeNodeBase *m);

  // tut nichts, nur fuer Prototypen
  TreeNodeView(): SensitiveRec(NULL,NULL){parent=NULL;} 
  virtual TreeNodeView *copy(TreeView *treeView, TreeNodeView *p,
			     TreeNodeBase *m);

  ~TreeNodeView();

  void draw(Boolean asSelected = FALSE);
  
  void configure(); 
  void calculate();

  TreeNodeView *getTNVParent() { return treeNodeViewParent; }
  Dimension getWidth() { return width; }
  Dimension getHeight() { return height; }
  void setPosition(Position x, Position y);
  void edit(Position x, Position y, Boolean state);
  Boolean isInRecPart(Rec &rec);        

  void update( unsigned long flags );

  RefArray<TreeNodeView> &getChildren() { return children; }
  Rec getFullRec() { return fullRec; }

  void select( Boolean s, Position x, Position y );
  void visibilityChanged(Boolean vis);
  void showChildren();
  void hideChildren();

  char *getName() { return "TreeNodeView"; }
  TreeNodeBase *getTreeNodeBase() { return m; }

  Boolean isBefore(Position x, Position y);
  void highlightBefore(Boolean state);
};


// --------------------------------
// TreeView
// --------------------------------
//


class TreeView : public SensitiveContainer {
private:
  struct DropInfo {
    TreeView *self;
    TreeNodeBase *droppedOn;
    Boolean insertBefore;
    unsigned char operation;
  };

  TreeNodeBase *m;
  Position spacing;
  Boolean withIcons;              // show icons
  Boolean withSmallIcons;         // show small icons

  Ref<TreeNodeView> treeNodeViewProto;
  Ref<TreeNodeView> treeNodeView;
  Widget oldStateIcon;
  Widget insertBeforeIcon;
  Widget asChildIcon;
  Widget forbiddenIcon;

  Atom imports[1];              // drop imports

  static void dropProc(Widget wg, XtPointer clientData, XtPointer callData );
  static void dragProc(Widget wg, XtPointer clientData, XtPointer callData );
  static void transferProc(Widget w, XtPointer closure, 
			   Atom *seltype, Atom *type,
			   XtPointer value, unsigned long *length, 
			   int *format);

  static void structureEvent(Widget,XtPointer self,XEvent* event,Boolean*) {
    if( event->type==MapNotify )
      ((TreeView*)self)->refreshTree();
  }

  void processKey(XKeyEvent *event);   // overload to a + and - binding
  
public:
  TreeView( TreeNodeBase *cm, Widget p, TreeNodeView *tnv = NULL);
  ~TreeView();
  void update( unsigned long flags );
  void act( char *){}
  void setModel(TreeNodeBase *m);

  void scrollToMakeVisible(Iconable *model);

  void configure() { refreshTree(); }          
  void refresh() { refreshTree(); }      // override
  void refreshTree();
  void addTreeNodeView( TreeNodeView *parent );   
  TreeNodeView *getPrototype() { return treeNodeViewProto; }

  Boolean getWithIcons() { return withIcons; }
  void setWithIcons(Boolean b) 
  { withIcons = b; update(CONTAINER_CHANGED); refresh(); }

  Boolean getWithSmallIcons() { return withSmallIcons; }
  void setWithSmallIcons(Boolean b) 
  { withSmallIcons = b; update(CONTAINER_CHANGED); refresh(); }

};

#endif /* Don't add stuff after this #endif */

