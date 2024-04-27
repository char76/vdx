/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: View.C,v $
 *  $Date: 1999/08/27 15:30:25 $
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
 * $Log: View.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:25  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.4  1998/03/30 19:09:42  lazy
 * *** empty log message ***
 *
 * Revision 1.3  1997/07/25 19:49:59  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1995/09/28  15:14:27  lazy
 * SensitiveContainer kann jetzt ueber die Resource
 * *Box.labelFontList: font
 * gesteuert werden.
 *
 * Revision 1.1  1995/09/27  21:14:17  lazy
 * Initial revision
 *
 */

// ------------------------------------
// Classes: View
//
//          RecView
//          WinView
//
// (C) Dirk Laessig
// ------------------------------------


#include <lac/View.h>
#include <lac/Model.h>
#include <lac/ConModel.h>

#include <stdio.h>
#include <math.h>
#include <X11/Intrinsic.h>
#include <Xm/BulletinB.h>
#include <Xm/MessageB.h>
#include <Xm/DialogS.h>
#include <Xm/FileSB.h>
#include <Xm/DragIcon.h>

#include "loaderror.xpm"

/* #######################################################
                         View
   ####################################################### */

Boolean View::waitForUpdate = FALSE;    // we are in a transaction
RefArray<View> View::pendingUpdateViews;  // collection of all views getting
RefArray<View> View::refreshViews;

// -----------------------
//       View()
// -----------------------
View::View( Model *m )
{
  pendingUpdateFlags = 0;
  model = m;
  if( model )
    model->view_opened( this );
}

// -----------------------
//       changeModel()
// -----------------------
void View::changeModel( Model *m )
{
  if( model )
    model->view_closed( this );
  model = m;
  if( model )
    model->view_opened( this );
}

// -----------------------
//       ~View()
// -----------------------
View::~View()
{
//  model->view_closed( *this );
}

// -----------------------
//     updateFromModel()
// -----------------------
void View::updateFromModel(unsigned long flags)
{
  if(waitForUpdate) {
    pendingUpdateFlags |= flags;
    for(unsigned int i=0; i<pendingUpdateViews.getSize(); i++) {
      if(pendingUpdateViews[i] == this)
	return;
    }
    pendingUpdateViews.add(this);
  } else {
    update(flags);
    for(unsigned int i=0; i<refreshViews.getSize(); i++)
      refreshViews[i]->refresh();
    refreshViews.empty();
  }
}

// -----------------------
//   needRefresh()
// -----------------------
void View::needRefresh()
{
  for(unsigned int i=0; i<refreshViews.getSize(); i++)
    if(refreshViews[i] == this)
      return;
  refreshViews.add(this);
}

// -----------------------
//   transactionBegin()
// -----------------------
void View::transactionBegin()
{
  waitForUpdate = TRUE;
}

// -----------------------
//   transactionEnd()
// -----------------------
void View::transactionEnd()
{
  waitForUpdate = FALSE;
  for(unsigned int i=0; i<pendingUpdateViews.getSize(); i++) {
    pendingUpdateViews[i]->update(pendingUpdateViews[i]->pendingUpdateFlags);
    pendingUpdateViews[i]->pendingUpdateFlags = 0;
  }
  pendingUpdateViews.empty();
  for(unsigned int i=0; i<refreshViews.getSize(); i++)
    refreshViews[i]->refresh();
  refreshViews.empty();
}

/* #######################################################
                        WinView
   ####################################################### */

WinView::PixmapEntry *WinView::first = NULL;
TArray<WinView::IconData> WinView::buildInIcons;

// --------------------------
//        WinView()
// --------------------------

WinView::WinView(Model *m)
: View(m)
{
}

// --------------------------
//        ~WinView()
// --------------------------

WinView::~WinView()
{
  while( allActions.getSize() )
    allActions[0].Delete();
}

// -------------------------------------
//    command - Callback for all button 
// -------------------------------------
void WinView::command( Widget , XtPointer client, XtPointer)
{
  ((CBInfo*)client)->instance->act(((CBInfo*)client)->actionName);
}


// ------------------------------------------
//   addAction - add a callback to a button 
// ------------------------------------------
void WinView::addAction( Widget button, char *actionName )
{
  CBInfo *cb = new CBInfo;
  allActions.add( cb );

  cb->instance = this;
  cb->actionName = actionName;
  
  XtAddCallback(button, XmNactivateCallback, command, (XtPointer)cb );
}

// --------------------------------
//     addIcon()  
// --------------------------------

void WinView::addIcon(const char *name, char **data)
{
  IconData *iconData = new IconData;
  iconData->name = name;
  iconData->data = data;
  buildInIcons.add(iconData);
}

// --------------------------------
//     findIcon()
// --------------------------------

char **WinView::findIcon(const char *name)
{
  unsigned int i;
  for(i=0; i<buildInIcons.getSize(); i++)
    if(!strcmp(name, buildInIcons[i]->name))
      return buildInIcons[i]->data;
  return (char**)NULL;
}

// --------------------------------
//     findEntry()
// --------------------------------

WinView::PixmapEntry *WinView::findEntry(char *name, Dimension iconHeight)
{
  PixmapEntry *ptr;

  for( ptr = first; ptr; ptr = ptr->next ) 
    if( !strcmp( ptr->name, name ) && ptr->iconHeight == iconHeight) {
      return ptr;
    }
  return NULL;
}


// --------------------------------
//     loadEntry()
// --------------------------------

WinView::PixmapEntry *WinView::loadEntry(Widget wg, const char *name)
{
  PixmapEntry *ptr;
  int ErrorStatus;
  static int init=1;

  if(init) {
    init = 0;
    addIcon("@loaderror", loaderror_xpm);
    loadEntry(wg, "@loaderror");
  }

  ptr = new PixmapEntry;
  ptr->attributes.valuemask = XpmReturnPixels;
  ptr->iconHeight = 0;

  char **data = findIcon(name);
  if(data) {
    ErrorStatus = XpmCreatePixmapFromData(XtDisplay(wg), 
					  XRootWindowOfScreen(XtScreen(wg)),
					  data, &ptr->loaded,
					  &ptr->mask, &ptr->attributes);
    if( ErrorStatus != 0 ) {
      fprintf(stderr,"Error:%d while pixmap loading\n",ErrorStatus);
      delete ptr;
      return findEntry("@loaderror");
    }

  } else {
    // not found => load it
    ErrorStatus = XpmReadFileToPixmap(XtDisplay(wg), 
				      XRootWindowOfScreen(XtScreen(wg)),
				      (char *)name, &ptr->loaded,
				      &ptr->mask, &ptr->attributes);
    
    if(ErrorStatus != XpmSuccess) {    // Ok try XtResolvePathname()
      char *path;
      path = XtResolvePathname(XtDisplay(wg), "pixmaps", name, "", NULL,
			       NULL, 0, NULL);
      if(path) {
	ErrorStatus = XpmReadFileToPixmap(XtDisplay(wg), 
					  XRootWindowOfScreen(XtScreen(wg)),
					  path, &ptr->loaded,
					  &ptr->mask, &ptr->attributes);
	XtFree(path);
      }
    }
    if( ErrorStatus != XpmSuccess ) {
      fprintf(stderr,"Error:%d while pixmap loading\n",ErrorStatus);
      delete ptr;
      return findEntry("@loaderror");
    }
  }

  strcpy( ptr->name, name );
  ptr->next = first;
  first = ptr;
  ptr->bitmap = 0;

  return ptr;
}

// --------------------------------
//     createScaledEntry()
// --------------------------------
WinView::PixmapEntry *
WinView::createScaledEntry(Widget wg, char *name, 
			   Dimension iconHeight)
{
  PixmapEntry *pe = NULL, *ptr = NULL;

  pe = findEntry(name);      // try to find default height entry
  if(pe == NULL)
    pe = loadEntry(wg, name);
  if(pe && iconHeight !=0) {
    Dimension height, width;
    float scale;

    scale = float(iconHeight)/float(pe->attributes.height);
    height = iconHeight;
    width =  Dimension(scale * pe->attributes.width);
    ptr = new PixmapEntry;
    ptr->iconHeight = iconHeight;
    ptr->attributes = pe->attributes;
    ptr->attributes.height = height;
    ptr->attributes.width = width;
    ptr->bitmap = 0;
    strcpy( ptr->name, name );
    ptr->next = first;
    first = ptr;

    ptr->loaded = scalePixmap(wg, pe->loaded, 
			      pe->attributes.width, pe->attributes.height,
			      DefaultDepthOfScreen(XtScreen(wg)), scale);
    if(pe->mask)
      ptr->mask = scalePixmap(wg, pe->mask, 
			      pe->attributes.width, pe->attributes.height,
			      1, scale);
    else
      ptr->mask = 0;
  } else {
    ptr = pe;
  }
  return ptr;
}

// --------------------------------
//     scalePixmap()
// --------------------------------
Pixmap WinView::scalePixmap(Widget wg, 
			  Pixmap pixmap, 
			  Dimension height,
			  Dimension width,
			  Dimension depth,
			  float scaleFactor)
{
  Pixmap 		ret;
  XImage 		*image, *destImage;
  unsigned long 	plane_mask;
  Dimension 		newWidth, newHeight;
  GC			gc = 0;

  newWidth = Dimension(width*scaleFactor);
  newHeight = Dimension(height*scaleFactor);

  ret = XCreatePixmap(XtDisplay(wg), 
		      XRootWindowOfScreen(XtScreen(wg)),
		      newWidth, newHeight,
		      depth);

  plane_mask = (1 << depth) - 1;

  image = XGetImage(XtDisplay(wg), pixmap, 0, 0, width, height,
		    plane_mask, XYPixmap);
  destImage = XGetImage(XtDisplay(wg), ret, 0, 0, 
			newWidth, newHeight, plane_mask, XYPixmap);

  if(image == NULL) {
    fprintf(stderr, "Fatal error: can't get image\n");
    return ret;
  }
  if(destImage == NULL) {
    fprintf(stderr, "Fatal error: can't get destination image\n");
    return ret;
  }

  for(unsigned int x=0; x < newWidth; x++) {
    for(unsigned int y=0; y < newHeight; y++) {
      Pixel pix;
      pix = XGetPixel(image, int(x/scaleFactor), int(y/scaleFactor));
      XPutPixel(destImage, x, y, pix);
    }
  }

  XGCValues gcValues;
  gcValues.plane_mask = plane_mask;
  gc = XCreateGC(XtDisplay(wg), ret, GCPlaneMask, &gcValues);

  XPutImage(XtDisplay(wg), ret, gc, destImage, 0, 0, 0, 0, 
	    newWidth, newHeight);

  XDestroyImage(image);
  XDestroyImage(destImage);
  XFreeGC(XtDisplay(wg), gc);

  return ret;
}

// --------------------------------
//     getNamedPixmap()
// --------------------------------
Boolean WinView::getNamedPixmap(Widget wg, char *name, 
				XpmAttributes &attr, 
				Pixmap &pixmap,
				Pixmap &mask,
				Dimension iconHeight)
{
  PixmapEntry *ptr;
  
  ptr = findEntry(name, iconHeight);
  if( ptr ) {
    attr = ptr->attributes;
    mask = ptr->mask;
    pixmap = ptr->loaded;
    return TRUE;
  }
  if(iconHeight == 0) {
    ptr = loadEntry(wg, name);
  } else {
    ptr = createScaledEntry(wg, name, iconHeight);
  }
  if( ptr ) {
    attr = ptr->attributes;
    mask = ptr->mask;
    pixmap = ptr->loaded;
    return TRUE;
  }
  return FALSE;
}

// --------------------------------
//     getNamedBitmap()
// --------------------------------
Boolean WinView::getNamedBitmap(Widget wg, char *name, 
				XpmAttributes &attr, 
				Pixmap &bitmap,
				Pixmap &mask)
{
  PixmapEntry *ptr;
  
  ptr = findEntry(name);
  if( ptr ) {
    if(ptr->bitmap == 0)
      createBitmap(wg, ptr);

    attr = ptr->attributes;
    mask = ptr->mask;
    bitmap = ptr->bitmap;
    return TRUE;
  }
  ptr = loadEntry(wg, name);
  if( ptr ) {
    if(ptr->bitmap == 0)
      createBitmap(wg, ptr);
    
    attr = ptr->attributes;
    mask = ptr->mask;
    bitmap = ptr->bitmap;
    return TRUE;
  }
  return FALSE;
}


// ----------------------------
//  createBitmap()
// ----------------------------

void WinView::createBitmap(Widget wg, PixmapEntry *entry)
{
  Colormap 		cmap;
  XWindowAttributes 	winAttributes;
  Window 		window = XtWindow(wg);
  XImage 		*image, *destImage;
  unsigned long 	plane_mask;
  const unsigned int  	maxColors = 256;
  XColor 		colors[maxColors];
  unsigned int 		numColors;
  unsigned long		lumMax, lumMin, lumCut;
  static GC		gc = 0;
  unsigned int 		depth;

  struct { 
    unsigned long pixel;
    unsigned long lum;
    unsigned long blackOrWhite;
  } colorResult[maxColors];


  depth = DefaultDepthOfScreen(XtScreen(wg));
  plane_mask = (1 << depth) - 1;

  if(window == 0)
    window = XRootWindowOfScreen(XtScreen(wg));

  entry->bitmap = XCreatePixmap(XtDisplay(wg),
				XRootWindowOfScreen(XtScreen(wg)),
				entry->attributes.width,
				entry->attributes.height,
				1);                           // depth == 1
  if(entry->bitmap == 0) {
    fprintf(stderr, "Fatal error: can't create pixmap with depth = 1\n");
    return;
  }

  image = XGetImage(XtDisplay(wg), entry->loaded, 0, 0, 
		    entry->attributes.width, entry->attributes.height,
		    plane_mask, XYPixmap);
  destImage = XGetImage(XtDisplay(wg), entry->bitmap, 0, 0, 
			entry->attributes.width, entry->attributes.height,
			0x01, XYPixmap);
  if(image == NULL) {
    fprintf(stderr, "Fatal error: can't get image\n");
    return;
  }
  if(destImage == NULL) {
    fprintf(stderr, "Fatal error: can't get destination image\n");
    return;
  }


  XGetWindowAttributes(XtDisplay(wg), window, &winAttributes);
  cmap = winAttributes.colormap;
  if(cmap == None) {
    cmap = XDefaultColormapOfScreen(XtScreen(wg));
  }

  numColors = 0;
  for(unsigned int x = 0; x < entry->attributes.width; x++) {
    for(unsigned int y = 0; y < entry->attributes.height; y++) {

      Pixel pixel = XGetPixel(image, x, y);
      Boolean found = FALSE;

      for(unsigned int i=0; i<numColors; i++) {
	if(colors[i].pixel == pixel) {
	  found = TRUE;
	  break;
	}
      }
      
      if(!found && numColors < maxColors)
	colors[numColors++].pixel = pixel;
      
    }
  }

  XQueryColors(XtDisplay(wg), cmap, colors, numColors);
  
  for(unsigned int i=0; i<numColors; i++) {
    colors[i].red /= 256;
    colors[i].blue /= 256;
    colors[i].green /= 256;
    colorResult[i].pixel = colors[i].pixel;
    colorResult[i].lum = (unsigned long)
      sqrt (colors[i].red * colors[i].red + 
	    colors[i].green * colors[i].green + 
	    colors[i].blue * colors[i].blue);
    if(i == 0) {
      lumMax = lumMin = colorResult[i].lum;
    } else {
      lumMax = lumMax > colorResult[i].lum ? lumMax : colorResult[i].lum;
      lumMin = lumMin < colorResult[i].lum ? lumMin : colorResult[i].lum;
    }
  }
  lumCut = (lumMax - lumMin)/2 + lumMin;
  for(unsigned int i=0; i<numColors; i++) {
    colorResult[i].blackOrWhite = colorResult[i].lum > lumCut ? 0 : 1;
  }

  for(unsigned int x=0; x<entry->attributes.width; x++) {
    for(unsigned int y=0; y<entry->attributes.height; y++) {

      unsigned long pixel = XGetPixel(image, x, y);
      for(unsigned int i=0; i<numColors; i++) {
	if(pixel == colorResult[i].pixel) {
	  XPutPixel(destImage, x, y, colorResult[i].blackOrWhite);
	  break;
	}
      }
    }
  }

  if(gc == 0) {
    XGCValues gcValues;
    gcValues.plane_mask = 0x01;
    gc = XCreateGC(XtDisplay(wg), entry->bitmap, GCPlaneMask, &gcValues);
  }

  XPutImage(XtDisplay(wg), entry->bitmap, gc, destImage, 0, 0, 0, 0, 
	    entry->attributes.width, entry->attributes.height);
  XDestroyImage(image);
  XDestroyImage(destImage);
}

// ----------------------------
//  getIconFromBits()
// ----------------------------

Widget WinView::getIconFromBits(Widget wg, 
				char *bits, Dimension w, Dimension h,
				char *mask, Dimension mw, Dimension mh,
				Position offsetX, Position offsetY)
{
  Pixmap icon, iconMask;
  Display *display = XtDisplay(wg);
  Arg args[10];
  Cardinal n=0;
  unsigned int maxCursorWidth, maxCursorHeight;

  XQueryBestCursor(display, 
		   RootWindowOfScreen(XtScreen(wg)), 64, 64, 
		   &maxCursorWidth, &maxCursorHeight);
  icon = XCreateBitmapFromData(display, DefaultRootWindow(display),
			       bits, w, h);
  iconMask = XCreateBitmapFromData(display, DefaultRootWindow(display),
				   mask, mw, mh);
  XtSetArg(args[n], XmNwidth, w > mw ? mw : w); n++;
  XtSetArg(args[n], XmNheight, h > mh ? mh : h); n++;
  XtSetArg(args[n], XmNpixmap, icon); n++;
  XtSetArg(args[n], XmNmask, iconMask); n++;
  XtSetArg(args[n], XmNmaxWidth, maxCursorWidth); n++;
  XtSetArg(args[n], XmNmaxHeight, maxCursorHeight); n++;
  XtSetArg(args[n], XmNoffsetX, offsetX ); n++;
  XtSetArg(args[n], XmNoffsetY, offsetY); n++;
  return XmCreateDragIcon(wg,"dragIcon",args,n);
}


Widget WinView::getIconFromPixmapName(Widget wg, char *name)
{
  Pixmap icon, iconMask;
  Arg args[10];
  Cardinal n=0;
  XpmAttributes attr;
 
  if(getNamedBitmap(wg, name, attr, icon, iconMask)) {
    XtSetArg(args[n], XmNwidth, attr.width); n++;
    XtSetArg(args[n], XmNheight, attr.height); n++;
    XtSetArg(args[n], XmNpixmap, icon); n++;
    if(iconMask) {
      XtSetArg(args[n], XmNmask, iconMask); n++;
    }
    XtSetArg(args[n], XmNdepth, 1); n++;
    return XmCreateDragIcon(wg,"dragIcon",args,n);
  }
  return NULL;
}

// -----------------------
// cvtResourceFromString()
// -----------------------

XtArgVal WinView::cvtResourceFromString(Widget wg, char *type, char *value)
{
  XtArgVal v;
  XrmValue from, to;

  from.addr = (XPointer)value;
  from.size = strlen(value)+1;
  to.addr = (XPointer)&v;
  to.size = sizeof(v);

  if( XtConvertAndStore(wg, XtRString, &from, type, &to) ) {
    return v;
  } 

  printf("Can't convert %s to %s.\n", value, type);
  return 0;
}

