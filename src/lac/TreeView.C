/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TreeView.C,v $
 *  $Date: 1999/08/27 15:30:22 $
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
 * $Log: TreeView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:22  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.3  1997/09/11  14:54:13  lazy
 * Keyboard traversal and + and - sign inserted
 *
 * Revision 1.2  1997/07/25  19:49:56  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:13:28  lazy
 * Initial revision
 *
 */

// --------------------------------
// TreeView.C
// (C) Dirk Laessig
// --------------------------------

#include <Xm/Xm.h>
#include <lac/TreeView.h>
#include <lac/ConModel.h>
#include <Xm/DragCP.h>

#include "forbidden.xbm"
#include "forbiddenMask.xbm"
#include "insertBefore.xbm"
#include "insertBeforeMask.xbm"
#include "asChild.xbm"
#include "asChildMask.xbm"

#include "expand.xpm"
#include "collapse.xpm"

#define STATE_ICON_OFFSET_X -20
#define STATE_ICON_OFFSET_Y -8

#define TNV_SPACE 5

// ####################################################
//   TreeNodeView
// ####################################################

#define VD_WITH_CHILDREN "WithChildren"

// ----------------------------
//  ExpandPixmap()
// ----------------------------
TreeNodeView::ExpandIcon::ExpandIcon(TreeNodeBase *m, TreeNodeView *tnv)
:StatePixmapRecView(m,tnv)
{
  static Boolean init = TRUE;
  if(init) {
    init = FALSE;
    WinView::addIcon("@Collapse", collapse_xpm);
    WinView::addIcon("@Expand", expand_xpm);
  }
  addState(COLLAPSE, "@Collapse");
  addState(EXPAND, "@Expand");

  parentObject = tnv;
  this->m = m;
  update(VD_WITH_CHILDREN_CHANGED);
}

void TreeNodeView::ExpandIcon::update(unsigned long flags)
{
  Boolean withChildren = FALSE;
  if( flags & VD_WITH_CHILDREN_CHANGED ) {
    if(!m->getVDBoolean(parentObject, VD_WITH_CHILDREN, withChildren )) {
      if(m->getSize() == 0)
	setState(COLLAPSE);
      else
	setState(EXPAND);
    } else {
      if(withChildren)
	setState(EXPAND);
      else
	setState(COLLAPSE);
    }
  }
}

// ----------------------------
//  TreeNodeView()
// ----------------------------

TreeNodeView::TreeNodeView( TreeView *tv, TreeNodeView *p, TreeNodeBase *m )
:SensitiveRec(m,tv)
{
  unsigned int i;
  
  treeView = tv;
  this->m = m;
  treeNodeViewParent = p;

  if(!m->getVDBoolean( this, VD_WITH_CHILDREN, withChildren ))
    withChildren = TRUE;
  if(m->hasChildren() && m->getSize() == 0) {
    withChildren = FALSE;
  }

  if(m->hasChildren())
    expandIcon = new ExpandIcon(m, this);
  if(treeView->getWithIcons())
    pixmap = new PixmapRecView(m, this, 
			       treeView->getWithSmallIcons() ? 16 : 0);
  text = new TextRecView(m, this);

  intentY = 10;
  intentX = 30;

  for( i=0; i<m->getSize(); i++ ) {
    this->children.add(treeView->getPrototype()->copy(treeView, this,
						      this->m->child(i))); 
    if( !withChildren || !getVisible())    // Do not show children, if
                                           // I'm not visible or if I
                                           // don't want it.
      this->children[i]->visibilityChanged(FALSE);
  }
}

// ------------------------------
//      edit()
// ------------------------------

void TreeNodeView::edit(Position, Position, Boolean state)
{
  if(!text.isNil())
    text->setEditable(state);
}

// ----------------------
//      isInRecPart()
// ----------------------
Boolean TreeNodeView::isInRecPart(Rec &rec)
{
  Position px, py, x, y;
  Dimension pw, ph, w, h;

  fullRec.getPosition(x,y);
  fullRec.getDimension(w,h);
  rec.getPosition(px, py);
  rec.getDimension(pw, ph);

  if((x+w>=px && x<=px+pw) && (y+h>=py && y<=py+ph))
    return TRUE;
  return FALSE;
}

// ----------------------------
//  copy()
// ----------------------------

TreeNodeView *TreeNodeView::copy(TreeView *treeView, TreeNodeView *p, TreeNodeBase *m )
{
  return new TreeNodeView(treeView,p,m);
}

// ----------------------------
//  ~TreeNodeView()
// ----------------------------

TreeNodeView::~TreeNodeView()
{
  while(children.getSize()) {
    children[0].Delete();
  }
  if(!expandIcon.isNil())
    expandIcon.Delete();
  if(!pixmap.isNil())
    pixmap.Delete();
  if(!text.isNil())
    text.Delete();
}

// ----------------------------
//  draw()
// ----------------------------

void TreeNodeView::draw(Boolean asSelected)
{
  Position beginX, beginY, endX, endY, childX, childY;
  Dimension childWidth, childHeight;
  unsigned int i;

  if(XtWindow(parent) == None)
    return;
  
  if( m->hasChildren() ) {
    if( withChildren && children.getSize()) {
      beginX = x + intentX/2;
      if(!expandIcon.isNil())
	beginY = expandIcon->getY() + expandIcon->getHeight();
      else
	beginY = y + height;
      
      childX = children[children.getSize()-1]->x;
      childY = children[children.getSize()-1]->y;
      childWidth = children[children.getSize()-1]->width;
      childHeight = children[children.getSize()-1]->height;

      endX = beginX;
      endY = childY+childHeight/2;
      
      XDrawLine(XtDisplay(parent),XtWindow(parent),fgGC,
		beginX,beginY,endX,endY);
      
      for( i=0; i<children.getSize(); i++ ) {
//	children[i]->draw();

	childX = children[i]->x;
	childY = children[i]->y;
	childWidth = children[i]->width;
	childHeight = children[i]->height;
	
	beginY = childY+childHeight/2;
	endX = childX-1;
	endY = beginY;
	XDrawLine(XtDisplay(parent),XtWindow(parent),fgGC,
		  beginX,beginY,endX,endY);
      }
    }
  }
  if(!expandIcon.isNil())
    expandIcon->draw(asSelected);
  if(!pixmap.isNil())
    pixmap->draw(asSelected);
  if(!text.isNil())
    text->draw(asSelected);
}

// --------------------------
//  visiblityChanged()
// --------------------------

void TreeNodeView::visibilityChanged(Boolean vis)
{
  setVisible( vis );
  if( withChildren )
    for( unsigned int i=0; i<children.getSize(); i++ ) 
      children[i]->visibilityChanged( vis );
}


// ----------------------------
//  select()
// ----------------------------

void TreeNodeView::select( Boolean s, Position x, Position y )
{
  if(!expandIcon.isNil()) {
    if(expandIcon->isIn(x,y)) {
      if( withChildren )
	hideChildren();
      else {
	showChildren();
      }
      return;
    } 
  } 
  SensitiveRec::select(s,x,y);
}

// ----------------------------
//  calculate()
// ----------------------------

void TreeNodeView::calculate()
{
  Dimension childHeight, childWidth, maxWidth;
  Position childX, childY;

  if(!expandIcon.isNil()) {
    intentX = expandIcon->getWidth();
  }
  childHeight = childWidth = 0;
  childX = x+intentX;
  childY = y+height+intentY;
  maxWidth = width;

  if( withChildren ) {
    for( unsigned i=0; i<children.getSize(); i++ ) {
      children[i]->setPosition(childX, childY);
      children[i]->calculate();                   // Groesse berechnen
      children[i]->fullRec.getDimension(childWidth, childHeight);
      childY += childHeight+intentY;
      maxWidth = maxWidth > childWidth+intentX ? maxWidth : childWidth+intentX;
    }
  }
  fullRec.setPosition(x,y);
  fullRec.setDimension(maxWidth,childY-y-intentY);
}


// ----------------------------
//  update()
// ----------------------------

void TreeNodeView::update( unsigned long flags )
{
  unsigned int i;

  if( flags & CONTAINER_CHANGED ) {
    while( children.getSize() )
      children[0].Delete();
    for( i=0; i<m->getSize(); i++ ) {
      children.add(treeView->getPrototype()->copy(treeView, this, m->child(i)));
      treeView->addTreeNodeView( children[i] );
      if( !withChildren || !getVisible())    // Do not show children, if
	// I'm not visible or if I
	// don't want it.
	this->children[i]->visibilityChanged(FALSE);
    }
    if(m->hasChildren()) {
      if(expandIcon.isNil())
	expandIcon = new ExpandIcon(m, this);
    } else {
      if(!expandIcon.isNil())
	expandIcon.Delete();
    }
    treeView->needRefresh();
  }
  
  if( flags & VD_WITH_CHILDREN_CHANGED ) {
    m->getVDBoolean( this, VD_WITH_CHILDREN, withChildren );
    for( i=0; i<children.getSize(); i++ )
      children[i]->visibilityChanged(withChildren);
    treeView->needRefresh();
  }
}

// ------------------------------
//      showChildren()
// ------------------------------
void TreeNodeView::showChildren()
{
  unsigned int i;

  withChildren = TRUE;

  if(m->populate()) {
    while( children.getSize() )
      children[0].Delete();
    for( i=0; i<m->getSize(); i++ ) {
      children.add(treeView->getPrototype()->copy(treeView, this, m->child(i)));
      treeView->addTreeNodeView( children[i] );
      if( !withChildren )
	children[i]->visibilityChanged(FALSE);
    }
  }

  m->setVDBoolean(this, VD_WITH_CHILDREN, withChildren );
  m->changed( VD_WITH_CHILDREN_CHANGED );
}

// ------------------------------
//      hideChildren()
// ------------------------------
void TreeNodeView::hideChildren()
{
  withChildren = FALSE;
  m->setVDBoolean(this, VD_WITH_CHILDREN, withChildren );
  m->changed( VD_WITH_CHILDREN_CHANGED );
}

// ------------------------------
//      isBefore()
// ------------------------------
Boolean TreeNodeView::isBefore(Position x, Position y)
{
  if(this->x > x)
    return False;
  if(this->y < y)
    return False;
  if(this->y-intentY > y)
    return False;
  if(this->x+width < x)
    return False;
  return True;
}

// ------------------------------
//      highlightBefore()
// ------------------------------
void TreeNodeView::highlightBefore(Boolean state)
{
  GC gc;
  if(state)
    gc = fgGC;
  else
    gc = bgGC;
  XDrawLine(XtDisplay(parent), XtWindow(parent), gc, 
	    x, y-intentY/2, x + getWidth(), y-intentY/2);
}

// ------------------------------
//      setPosition()
// ------------------------------
void TreeNodeView::setPosition(Position x, Position y)
{
  this->x = x;
  this->y = y;

  height = 0;
  if(!expandIcon.isNil())
    height = MAX(height, expandIcon->getHeight());
  if(!pixmap.isNil())
    height = MAX(height, pixmap->getHeight());
  if(!text.isNil())
    height = MAX(height, text->getHeight());
  
  width = 0;
  if(!expandIcon.isNil()) {
    width += expandIcon->getWidth();
    width += TNV_SPACE;
  }
  if(!pixmap.isNil()) {
    width += pixmap->getWidth();
    width += TNV_SPACE;
  }
  if(!text.isNil())
    width += text->getWidth();
  
  Dimension offset = 0;
  if(!expandIcon.isNil()) {
    expandIcon->setPosition(x, y + height/2 - expandIcon->getHeight()/2);
    offset += expandIcon->getWidth() + TNV_SPACE;
  }
  if(!pixmap.isNil()) {
    pixmap->setPosition(x + offset, y + height/2 - pixmap->getHeight()/2);
    offset += pixmap->getWidth() + TNV_SPACE;
  }
  if(!text.isNil()) {
    text->setPosition(x + offset, y + height/2 - text->getHeight()/2);
  }
}

// ----------------------------
//  configure()
// ----------------------------

void TreeNodeView::configure()
{
  treeView->refreshTree();
}

// ----------------------------
//  traversUp()
// ----------------------------

void 
TreeNodeView::traverseUp()
{
  SensitiveRec::traverseUp();
}

// ----------------------------
//  traversDown()
// ----------------------------

void 
TreeNodeView::traverseDown()
{
  SensitiveRec::traverseDown();
}

// ----------------------------
//  traversLeft()
// ----------------------------

void 
TreeNodeView::traverseLeft()
{
  SensitiveRec::traverseUp();
}

// ----------------------------
//  traversRight()
// ----------------------------

void 
TreeNodeView::traverseRight()
{
  SensitiveRec::traverseDown();
}

// ##########################################
//       TreeView()  
// ##########################################

// ----------------------------
//  TreeView()
// ----------------------------

TreeView::TreeView( TreeNodeBase *cm, Widget p, TreeNodeView *proto)
: SensitiveContainer(cm,p),m(cm) 
{
//  nodeMenu = pmenu;
  withIcons = TRUE;
  withSmallIcons = FALSE;

  if(proto)
    treeNodeViewProto = proto;
  else 
    treeNodeViewProto = new TreeNodeView();

  imports[0] = XmInternAtom(XtDisplay(p), cm->getClassName(), False);

  XtVaSetValues( box, XmNuserData, (XtPointer)this, NULL );  // fuer dropProc
  Arg args[10];
  Cardinal n = 0;
  XtSetArg(args[n], XmNimportTargets, imports); n++;
  XtSetArg(args[n], XmNnumImportTargets, 1); n++;
  XtSetArg(args[n], XmNdropSiteOperations, XmDROP_COPY|XmDROP_MOVE); n++;
  XtSetArg(args[n], XmNdropSiteType, XmDROP_SITE_COMPOSITE); n++;
  XtSetArg(args[n], XmNdropProc, dropProc); n++;
  XtSetArg(args[n], XmNdragProc, dragProc); n++;
  XtSetArg(args[n], XmNanimationStyle, XmDRAG_UNDER_NONE); n++;
  XmDropSiteRegister(box,args,n);

  XtInsertEventHandler(box,StructureNotifyMask, 
		       False,structureEvent,this,XtListTail);

  oldStateIcon = NULL;

  forbiddenIcon = getIconFromBits(box, forbidden_bits, forbidden_width,
				  forbidden_height, forbiddenMask_bits,
				  forbiddenMask_width, forbiddenMask_height,
				  STATE_ICON_OFFSET_X, STATE_ICON_OFFSET_Y);
  insertBeforeIcon = getIconFromBits(box, insertBefore_bits,insertBefore_width,
				     insertBefore_height,insertBeforeMask_bits,
				     insertBeforeMask_width,
				     insertBeforeMask_height,
				     STATE_ICON_OFFSET_X, STATE_ICON_OFFSET_Y);
  asChildIcon = getIconFromBits(box, asChild_bits, asChild_width,
				asChild_height, asChildMask_bits,
				asChildMask_width,asChildMask_height,
				STATE_ICON_OFFSET_X,STATE_ICON_OFFSET_Y);
  
  update(CONTAINER_CHANGED);
}


// ----------------------------
//  setModel()
// ----------------------------

void TreeView::setModel(TreeNodeBase *m)
{
  this->m = m;

  SensitiveContainer::setModel(m);
  update(CONTAINER_CHANGED);
  refresh();
}

// ----------------------------
//  ~TreeView()
// ----------------------------

TreeView::~TreeView()
{
  if(!treeNodeView.isNil())
    treeNodeView.Delete();

  if( !treeNodeViewProto.isNil() )
    treeNodeViewProto.Delete();
}


// ----------------------------
//  update()
// ----------------------------

void TreeView::update( unsigned long flags )
{
  if( flags & SELECTION_CHANGED ) {
  } 
  if( flags & (CONTAINER_CHANGED) ) {
    while( contents.getSize() )
      contents[0].Delete();
    treeNodeView = treeNodeViewProto->copy(this,NULL,m);
    addTreeNodeView( treeNodeView );

    needRefresh();
  }
}

// ---------------------------
//     refreshTree()
// ---------------------------

void TreeView::refreshTree()
{
  Dimension height, width;

  if(XtWindow((Widget)box) && 
     !treeNodeView.isNil()) {     // Optimierung noetig
//    treeNodeView->calculate();
//    treeNodeView->draw();
    
    treeNodeView->setPosition(TNV_SPACE, TNV_SPACE);
    treeNodeView->calculate();
    treeNodeView->getFullRec().getDimension(width,height);
    width += 1 + 2*TNV_SPACE;
    height += 1 + 2*TNV_SPACE;
    XtVaSetValues((Widget)box,
		  XmNunitType, XmPIXELS,
		  XmNwidth, width,
		  XmNheight, height,
		  NULL);
    XFlush(XtDisplay((Widget)box));
    queryViewport();
    XClearArea(XtDisplay((Widget)box),XtWindow((Widget)box),0,0,
	       width, height, TRUE);  // Draw Icons
    
  }
}

// ----------------------------
//  addTreeNodeView()
// ----------------------------

void TreeView::addTreeNodeView( TreeNodeView *parent )
{
  contents.add(parent);
  for( unsigned int i=0; i<parent->getChildren().getSize(); i++ )
    addTreeNodeView( parent->getChildren()[i] );
}


// ----------------------------
//    scrollToMakeVisible()
// ----------------------------

void TreeView::scrollToMakeVisible(Iconable *model)
{
  TreeNodeView *found = NULL;
  for(unsigned int i=0; i<contents.getSize(); i++) {
    if(contents[i]->getModel() == model) {
      found = (TreeNodeView*)(SensitiveRec*)contents[i];
      break;
    }
  }
  if(found) {
    View::transactionBegin();
    while(!found->getVisible() && found->getTNVParent()) {
      found = found->getTNVParent();
      found->showChildren();
    }
    View::transactionEnd();
  }
  SensitiveContainer::scrollToMakeVisible(model);
}

// -------------------------------
// processKey()
// -------------------------------
void TreeView::processKey(XKeyEvent *event)
{
  KeySym sym;
  Modifiers ret_mod;
  
  XmTranslateKey(event->display, event->keycode, event->state,
		 &ret_mod, &sym);
  if(sym == (KeySym)'+') {
    for(unsigned int i=0; i<contents.getSize(); i++) {
      if(contents[i]->getModel()->isSelected() && contents[i]->getVisible()) {
	TreeNodeView *tnv = (TreeNodeView*)(SensitiveRec*)contents[i];
	tnv->showChildren();
	break;
      }
    }
  } else if(sym == (KeySym)'-') {
    for(unsigned int i=0; i<contents.getSize(); i++) {
      if(contents[i]->getModel()->isSelected() && contents[i]->getVisible()) {
	TreeNodeView *tnv = (TreeNodeView*)(SensitiveRec*)contents[i];
	tnv->hideChildren();
	break;
      }
    }
  } else {
    SensitiveContainer::processKey(event);
  }
}

// ----------------------------
//  dragProc()
// ----------------------------

void TreeView::dragProc( Widget wg, XtPointer, XtPointer callData )
{
  TreeView *tv;
  TreeNodeBase *tnb = NULL;
  Boolean insertBefore = FALSE;
  XmDragProcCallback dd = (XmDragProcCallback)callData;

  static TreeNodeBase *oldTnb = NULL;
  static Boolean oldInsertBefore;
  SensitiveRec *sr;
  Widget tmp;

  
  if(((XmDragContextRec*)dd->dragContext)->drag.sourceIsExternal)
    return;

  XtVaGetValues(wg, XmNuserData, &tv, NULL);
  switch( dd->reason ) {
  case XmCR_DROP_SITE_ENTER_MESSAGE:
    XtVaGetValues(dd->dragContext,                // altes Icon speichern
		  XmNstateCursorIcon, &tmp,
		  NULL);
    tv->oldStateIcon = tmp;
    break;
  case XmCR_DROP_SITE_MOTION_MESSAGE:
    sr = tv->queryAsChild(dd->x, dd->y);
    tnb = sr ? (TreeNodeBase*)sr->getModel() : (TreeNodeBase*)NULL;
                                            // soll es ein Kind werden
    if( !tnb ) {
      sr = tv->queryInsertBefore(dd->x, dd->y);
      tnb = sr ? (TreeNodeBase*)sr->getModel() : (TreeNodeBase*)NULL;
                                            // oder ein Bruder
      insertBefore = TRUE;
    } else {
      insertBefore = FALSE;
    }
    if( tnb ) {
      if( insertBefore ) {
	if( !oldInsertBefore || !oldTnb ) {
//	  tv->setHighlighted(NULL);
	  XtVaSetValues(dd->dragContext, 
			XmNstateCursorIcon, tv->insertBeforeIcon,
			NULL);
	}
      } else {
	if( oldInsertBefore || !oldTnb ) {
//	  tv->setHighlighted(tnb);
	  XtVaSetValues(dd->dragContext, 
			XmNstateCursorIcon, tv->asChildIcon,
			NULL);
	}
      }
    } else {
//      tv->setHighlighted(NULL);
      if( oldTnb )
	XtVaSetValues(dd->dragContext, 
		      XmNstateCursorIcon, tv->forbiddenIcon,
		      NULL);
    }
    oldTnb = tnb;
    oldInsertBefore = insertBefore;
    break;
  case XmCR_DROP_SITE_LEAVE_MESSAGE:
    XtVaSetValues(dd->dragContext, 
		  XmNstateCursorIcon, tv->oldStateIcon,
		  NULL);
    tv->oldStateIcon = NULL;
    oldTnb = NULL;
    break;
  }
}

// ----------------------------
//  dropProc()
// ----------------------------

void TreeView::dropProc( Widget wg, XtPointer, XtPointer callData )
{
  TreeView *tv;
  TreeNodeBase *tnb = NULL;
  SensitiveRec *sr;

  static XmDropTransferEntryRec transList[1];
  static DropInfo dropInfo;

  Arg args[10];
  Cardinal n=0;
  XmDropProcCallback dd = (XmDropProcCallback)callData;

  XtVaGetValues(wg, XmNuserData, &tv, NULL);
  sr = tv->queryAsChild(dd->x, dd->y);
  tnb = sr ? (TreeNodeBase*)sr->getModel() : (TreeNodeBase*)NULL; 
                                // soll es ein Kind werden
  if( !tnb ) {
    sr = tv->queryInsertBefore(dd->x, dd->y);
    tnb = sr ? (TreeNodeBase*)sr->getModel() : (TreeNodeBase*)NULL;
                                // oder ein Bruder
    dropInfo.insertBefore = TRUE;
  } else {
    dropInfo.insertBefore = FALSE;
  }
  if( tnb ) {
    dropInfo.self = tv;
    dropInfo.droppedOn = tnb;
    dropInfo.operation = dd->operation;
    transList[0].target = tv->imports[0];
    transList[0].client_data = (XtPointer)&dropInfo;
    XtSetArg(args[n], XmNdropTransfers, transList); n++;
    XtSetArg(args[n], XmNnumDropTransfers, 1); n++;
    XtSetArg(args[n], XmNtransferProc, transferProc); n++;
  } else {
    XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE); n++;
  }
  XmDropTransferStart(dd->dragContext,args,n);
}

// ----------------------------
//  transferProc()
// ----------------------------

void TreeView::transferProc(Widget w, XtPointer closure, 
			    Atom *, Atom *,
			    XtPointer value, unsigned long *, 
			    int *)
{
  if(!value) {
    XtVaSetValues(w, 
		  XmNtransferStatus, XmTRANSFER_FAILURE,
		  NULL);
    return;
  }

  DropInfo *dropInfo = (DropInfo*)closure;
  TreeNodeBase *tnb = dropInfo->droppedOn;
  TreeNodeBase **ptr = (TreeNodeBase**)value;
  TreeNodeBase *toMove = *ptr;
  TreeNodeBase *parent, *newParent, *copied = NULL;

  if( dropInfo->insertBefore ) {
    parent = tnb->tnb_getParent();
    if( !tnb || !parent ) {
      XtVaSetValues(w, 
		    XmNtransferStatus, XmTRANSFER_FAILURE,
		    NULL);
      return;
    }
  } else 
    parent = tnb;
  
  // der Baum darf nicht abgesaegt werden

  if( dropInfo->operation == XmDROP_MOVE ) {
    for( ; parent; parent = parent->tnb_getParent()) {
      if(parent==toMove) {
	XtVaSetValues(w, 
		      XmNtransferStatus, XmTRANSFER_FAILURE,
		      NULL);
	return;
      }
    }
  }

  // nicht auf sich selbst verschieben

  if(toMove == tnb && dropInfo->operation == XmDROP_MOVE) {
    XtVaSetValues(w, 
		  XmNtransferStatus, XmTRANSFER_FAILURE,
		  NULL);
    return;
  }

  // neuen Pappi bestimmen

  newParent = tnb;
  if( dropInfo->insertBefore ) 
    newParent = tnb->tnb_getParent();

  // wenn Pappi das Kind nicht akzeptiert, dann ...

  if( !newParent->tnb_asChildOk(toMove) ) {
    XtVaSetValues(w, 
		  XmNtransferStatus, XmTRANSFER_FAILURE,
		  NULL);
    return;
  }

  // Wenn dies ein Move ist, dann Objekt beim Parent herausnehmen

  if(dropInfo->operation == XmDROP_MOVE) {
    parent = toMove->tnb_getParent();
    if(parent) {
      parent->tnb_remove(toMove);
    }
  }

  // Wenn dies ein Copy ist, dann kopieren: toMove ist Prototype

  if( dropInfo->operation == XmDROP_COPY ) {
    copied = toMove->tnb_copy();
    if( !copied ) {
      XtVaSetValues(w, 
		    XmNtransferStatus, XmTRANSFER_FAILURE,
		    NULL);
      return;
    }
    toMove = copied;
  }

  // Beim neuen Parent einfuegen

  if( dropInfo->insertBefore ) {
    newParent->tnb_insert(toMove,tnb);
    newParent->changed(CONTAINER_CHANGED);
  } else {
    newParent->tnb_add(toMove);
    newParent->changed(CONTAINER_CHANGED);
  }
  if(parent && parent != newParent && dropInfo->operation == XmDROP_MOVE)
    parent->changed(CONTAINER_CHANGED);
}
			   

