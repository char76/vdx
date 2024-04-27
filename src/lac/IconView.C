/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: IconView.C,v $
 *  $Date: 1999/08/27 15:29:33 $
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
 * $Log: IconView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:33  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:59  lazy
 * Initial revision
 *
 */

#include <lac/IconView.h>

#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>

/* #############################################################
                           Icon
   ############################################################# */


// -------------------------------
//   Icon()  - Konstuktor
// -------------------------------

Icon::Icon( Iconable *am, IconView *iv)
: SensitiveRec(am,iv), m(am)
{ 
  iconView = iv;
  offset = 2;

  if(iv->getWithNames() || !iv->getWithIcons())
    text = new TextRecView(am, this);
  if(iv->getWithIcons())
    pixmap = new PixmapRecView(am, this, iv->getWithSmallIcons() ? 16 : 0);
};

// -------------------------------
//   Icon()  - Konstuktor
// -------------------------------

Icon::Icon()
: SensitiveRec(NULL,NULL), m(NULL)
{
}

Icon::~Icon() 
{
  if(!text.isNil())
    text.Delete();
  if(!pixmap.isNil())
    pixmap.Delete();
}

// -------------------------------
//    copy()
// -------------------------------
Icon* Icon::copy( Iconable *am, IconView *iv )
{
  return new Icon(am,iv);
}

// --------------------------------
//        draw()
// --------------------------------

void Icon::draw(Boolean asSelected) 
{
  if(!pixmap.isNil())
    pixmap->draw(asSelected);
  if(!text.isNil())
    text->draw(asSelected);
}

// --------------------------------------
//             update()
// --------------------------------------

void Icon::update( unsigned long ) 
{
}

// ---------------------------------------
//            setPosition()
// ---------------------------------------
    
void Icon::setPosition( Position x, Position y ) {
  this->x = x;
  this->y = y;
  
  if(!pixmap.isNil()) {
    if(iconView->getOneRow()) {
      if(text.isNil()) {
	width = pixmap->getWidth();
	height = pixmap->getHeight();
      } else {
	width = pixmap->getWidth() + offset + text->getWidth();
	height = MAX(pixmap->getHeight(),text->getHeight());
      }
      pixmap->setPosition(x,y);
      if(!text.isNil())
	text->setPosition(x + pixmap->getWidth() + offset, 
			  y + pixmap->getHeight()/2 - text->getHeight()/2);
    } else {

      if(text.isNil()) {
	width = pixmap->getWidth();
	height = pixmap->getHeight();
      } else {
	width = MAX(pixmap->getWidth(),text->getWidth());
	height = pixmap->getHeight() + offset + text->getHeight();
      }
      pixmap->setPosition(x + width/2 - pixmap->getWidth()/2, y);
      if(!text.isNil())
	text->setPosition(x + width/2 - text->getWidth()/2, 
			  y + pixmap->getHeight() + offset);
    }
  } else {
    if(iconView->getOneRow()) {
      if(text.isNil()) {
	fprintf(stderr, "text is nil and pixmap is nil\n");
      } else {
	width = text->getWidth();
	height = text->getHeight();
	text->setPosition(x, y);
      }
    } else {
      if(text.isNil()) {
	fprintf(stderr, "text is nil and pixmap is nil\n");
      } else {
	width = text->getWidth();
	height = text->getHeight();
	text->setPosition(x, y);
      }
    }
  }
}

// ---------------------------
//        getWidth()
// ---------------------------

Dimension Icon::getWidth()
{
  return width;
}

// ---------------------------
//        getHeight()
// ---------------------------

Dimension Icon::getHeight()
{
  return height;
}

// ---------------------------
//        isIn()
// ---------------------------

Boolean Icon::isIn( Position x, Position y )
{
  if(!text.isNil() && text->isIn(x,y))
    return TRUE;
  if(!pixmap.isNil() && pixmap->isIn(x,y))
    return TRUE;
  return FALSE;
}


// ---------------------------
//        configure()
// ---------------------------

void Icon::configure()
{
  setPosition(x,y);
  iconView->configure();
}


			
// ------------------------------
//      isBefore()
// ------------------------------
Boolean Icon::isBefore(Position x, Position y)
{
  if(this->x < x)
    return False;
  if(this->y > y)
    return False;
  return True;
}

// ------------------------------
//      highlightBefore()
// ------------------------------
void Icon::highlightBefore(Boolean state)
{
  GC gc;
  if(state)
    gc = fgGC;
  else
    gc = bgGC;
  XDrawLine(XtDisplay(parent), XtWindow(parent), gc, 
	    x-5, y, x-5, y+getHeight());
}

// ------------------------------
//      edit()
// ------------------------------

void Icon::edit(Position, Position, Boolean state)
{
  if(!text.isNil())
    text->setEditable(state);
}

/* ###################################################
                  IconView
   ################################################### */

IconView::IconView( ContainerBase *cm, Widget p, Icon *picon )
: SensitiveContainer(cm,p),m(cm) 
{ 
  spacing = 10; 
  names = TRUE;
  shadow = 2;
  oneRow = FALSE;
  withIcons = TRUE;
  withSmallIcons = FALSE;

  if(picon) {           
    icon = picon;         // user want its own icon class 
  } else {
    icon = new Icon();    // use icon base class
  }

  update(CONTAINER_CHANGED);         
}


// --------------------------------
//      setModel()
// --------------------------------
void IconView::setModel(ContainerBase *m)
{
  this->m = m;

  SensitiveContainer::setModel(m);
  update(CONTAINER_CHANGED);
}

// --------------------------------
//      ~IconView()
// --------------------------------
IconView::~IconView()
{
  if( !icon.isNil() )
    icon.Delete();
}

// ----------------------------------
//       update()
// ----------------------------------

void IconView::update( unsigned long flags ) {
  unsigned int i;

  if( flags & SELECTION_CHANGED ) {
    // Do nothing
  } 
  if( flags & CONTAINER_CHANGED ) {
    while( contents.getSize() )
      contents[0].Delete();
    contents.empty();
    for( i=0 ; i< m->getSize(); i++ ) {
      contents.add( icon->copy(m->at(i), this) );
    }
    if(XtWindow(box)) {
      for( i=0 ; i<contents.getSize(); i++ )       // create pixmaps -> w&h
	contents[i]->expose();
      XClearWindow(display ,XtWindow(box));  // Draw Icons
    }

    configure();                  // arange icons
    
  }
}


Dimension IconView::getParentWidth()
{
  Widget w;
  Dimension width;

  XtVaGetValues(scrolledWindow,XmNclipWindow,&w,NULL);
  if(w == NULL)
    w = scrolledWindow;

  XtVaGetValues(w,XmNwidth,&width,NULL);
  
  return width;
}


void IconView::calculate()
{
  Dimension width, minWidth;

  width = getParentWidth();
  minWidth = getMinWidth();
  if( width < minWidth )
    width = minWidth;

  Dimension rowHeight;
  Position x,y;

  x = y = spacing;
  if( contents.getSize() > 0 ) {

    if(oneRow)
      contents[0]->setPosition(x, y);
    else
      contents[0]->setPosition(x + minWidth/2 - contents[0]->getWidth()/2,y);
    rowHeight = contents[0]->getBottomBorder();
    x = x+minWidth+spacing;

    for( unsigned int i=1 ; i<contents.getSize(); i++ ) {

      contents[i]->setPosition(x + minWidth/2 - contents[i]->getWidth()/2, y);

      // passt dat Ding nich mehr rein, oder wollen wir nur eine Spalte

      if((contents[i]->getRightBorder()+spacing > width) || oneRow ) {
	x = spacing;
	y = rowHeight+spacing;
	if(oneRow)
	  contents[i]->setPosition(x, y);
	else
	  contents[i]->setPosition(x + minWidth/2 - contents[i]->getWidth()/2, y);
      }

      x = x+minWidth+spacing;     
      rowHeight = contents[i]->getBottomBorder()>rowHeight ?
	contents[i]->getBottomBorder() : rowHeight;
    }
  }
}


Dimension IconView::getMinWidth() 
{
  int ret = 0;

  for( unsigned int i=0; i<contents.getSize(); i++ ) {
    contents[i]->setPosition(spacing,spacing);
    ret = contents[i]->getRightBorder()>ret ? 
      contents[i]->getRightBorder() : ret;
  }
  ret += spacing;
  return ret;
}


void IconView::configure()
{
  calculate();   // calculate icon positions
  
  Position maxX = 0, maxY = 0;
  unsigned int i;

  for( i=0 ; i<contents.getSize(); i++ ) {
    maxX = maxX > contents[i]->getRightBorder() ? 
      maxX : contents[i]->getRightBorder();
    maxY = maxY > contents[i]->getBottomBorder() ? 
      maxY : contents[i]->getBottomBorder();
  }
  XtVaSetValues( box,
		XmNheight, maxY == 0 ? 1: maxY+spacing,
		XmNwidth, maxX == 0 ? 1: maxX+spacing,
		NULL );
    
  if(XtWindow(box)) {
    XClearWindow(display,XtWindow(box));  // Draw Icons
    for( i=0 ; i<contents.getSize(); i++ ) {
//      Icon *icon = (Icon*)((SensitiveRec*)contents[i]);
//      icon->textVisible(names);
      contents[i]->expose();
    }
  }
}

