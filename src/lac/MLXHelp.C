/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MLXHelp.C,v $
 *  $Date: 1999/08/27 15:29:48 $
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
 * $Log: MLXHelp.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:48  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:32:26  lazy
 * Initial revision
 *
 * Revision 1.1  1995/09/27  21:04:24  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// MLXHelp.C                      
// ------------------------------

#include "MLXHelp.h"
#include "HelpTreeNodeView.h"
#include <Xm/Text.h>
#include <Xm/TextP.h>
#include <Xm/PushB.h>
#include <X11/cursorfont.h>
#include <Xm/ToggleB.h>
#include <Xm/SelectioB.h>
#include <Xm/FileSB.h>
#include <ctype.h>
#include <unistd.h>

#define REF_TOK "Link"

static char *fbRes =
#include "MLXHelp_res.h"
;

XtResource MLXHelp::mlxHelpResources [] = {
  {
    "hypertextColor", "hypertextColor", XmRPixel, sizeof(Pixel),
    XtOffsetOf(::MLXHelp, htPixel), XtRString, (XtPointer)"steelblue4"
  },
  {
    "charHighlightColor", "charHighlightColor", XmRPixel, sizeof(Pixel),
    XtOffsetOf(::MLXHelp, highlightPixel), XtRString, (XtPointer)"red"
  }
};

// ------------------------------ 
// MLXHelp()                      
// ------------------------------

MLXHelp::MLXHelp(char *filename, Widget wg, HelpNode *hn)
:MLXHelp_base(wg, NULL, 0, fbRes) 
{
  this->filename[0] = 0;
  quickHelpLabel = quickHelp;

  normGC = invGC = htGC = invHtGC = 0;

  XtVaSetValues(text, XmNuserData, this, NULL);
  oldDrawProc = ((XmTextWidget)text)->text.output->Draw;
  ((XmTextWidget)text)->text.output->Draw = newDrawProc;

  XtAddEventHandler(text, ButtonPressMask,  False, buttonPressEvent, this );
  XtAddEventHandler(text, PointerMotionMask,  False, mouseMotionEvent, this );

  XtGetSubresources(this->getTop(), this, NULL, NULL, 
		    mlxHelpResources, XtNumber(mlxHelpResources),
		    NULL, 0);

  XtUnmanageChild(XmSelectionBoxGetChild(identDialog, XmDIALOG_HELP_BUTTON));
  XtUnmanageChild(XmSelectionBoxGetChild(titleDialog, XmDIALOG_HELP_BUTTON));
  XtUnmanageChild(XmSelectionBoxGetChild(findDialog, XmDIALOG_HELP_BUTTON));
  XtUnmanageChild(XmFileSelectionBoxGetChild(exportDialog, XmDIALOG_HELP_BUTTON));

  if(filename) {
    setFilename(filename);

    editable = TRUE;
    XtManageChild(Save);
    XtManageChild(exportLatex);
    XtManageChild(Edit);
    
    XtVaSetValues(text,
		  XmNeditable, true,
		  XmNcursorPositionVisible, true,
		  NULL);
  } else {
    editable = FALSE;
    XtVaSetValues(text,
		  XmNeditable, false,
		  XmNcursorPositionVisible, false,
		  NULL);
  }

  if( hn == NULL )
    helpNode = new HelpNode(MLXHelp_base::MLXHelp);
  else
    helpNode = hn;

  htnv = new HelpTreeNodeView(this);
  treeView = new HelpTreeView(helpNode, frame, this, htnv);

  treeView->setDragOperations( XmDROP_COPY|XmDROP_MOVE|XmDROP_LINK );
  XtManageChild(treeView->getTop());
  XmToggleButtonSetState(contentsButton, TRUE, FALSE);

  historyPage = 0;
  setSelectedHelpNode(helpNode);
}


// ------------------------------ 
// ~MLXHelp()
// ------------------------------

MLXHelp::~MLXHelp()
{
  delete treeView;
}

// ------------------------------ 
// exitMLXHelp()
// ------------------------------

void MLXHelp::exitMLXHelp(Widget, XtPointer)
{
  close();
}


// ------------------------------ 
// setFilename()
// ------------------------------

void MLXHelp::setFilename(char *fName)
{
  strcpy(filename, fName);
  strcpy(headerFilename, filename);
  strcpy(latexName, filename);

  unsigned int beginName = 0;
  for(unsigned int i=0; i<strlen(headerFilename); i++) {
    if(headerFilename[i] == '/') {
      beginName = i+1;
    }
  }
  for(unsigned int i=beginName; i<strlen(headerFilename); i++) {
    if(headerFilename[i] == '.') {
      headerFilename[i] = '_';
    }
  }
  strcat(headerFilename, ".h");

  for(unsigned int i=beginName; i<strlen(latexName); i++) {
    if(latexName[i] == '.') {
      latexName[i] = '_';
    }
  }
  strcat(latexName, ".tex");
}

// ------------------------------ 
// saveFile()
// ------------------------------

void MLXHelp::saveFile(Widget, XtPointer)
{
  FILE *fp;
  
  if(editable) {
    saveText(NULL,NULL);
    if( (fp = fopen(filename,"w")) ) {
      helpNode->writeTo(fp);
      fclose(fp);
    }
    if( (fp = fopen(headerFilename,"w")) ) {
      helpNode->writeHeader(fp);
      fclose(fp);
    }
  }
}


// ------------------------------ 
// setSelectedHelpNode()
//
// Zeigt im Textfenster den Text
// des HelpNodes an                      
// ------------------------------

void MLXHelp::setSelectedHelpNode(HelpNode *shn,
				  char *toHighlight, 
				  Boolean caseSens)
{
  saveText(NULL,NULL);

  if(shn == selectedHelpNode)
    return;

  if(!selectedHelpNode.isNil()) {             // If we have a current node
#if(0)
    for(unsigned int i=0; i<history.getSize(); i++) {
      if(selectedHelpNode == history[i]) {
	currentIndex = i+1;                   // item behind the current node
	break;
      }
    }
#endif

    for(unsigned int i = history.getSize()-1; i > historyPage; i-- )
      history.remove(history[historyPage+1]);
  }

  selectedHelpNode = shn;
  selectedHelpNode->select();

  treeView->scrollToMakeVisible(shn);

  if(history.getSize() == 0 || 
     history[history.getSize()-1] != selectedHelpNode) {
    if(history.getSize() != 0) // first call
      historyPage++;
    history.add(selectedHelpNode);             // now we are the last item
  }

  XtSetSensitive(forwardButton, FALSE);
  XtSetSensitive(historyForward, FALSE);
  if(history.getSize() > 1) {
    XtSetSensitive(backButton, TRUE);
    XtSetSensitive(historyBack, TRUE);
  } else {
    XtSetSensitive(backButton, FALSE);
    XtSetSensitive(historyBack, FALSE);
  }
  XtSetSensitive(nextSection, shn->getNext() != NULL);
  XtSetSensitive(lastSection, shn->getLast() != NULL);

  emptyHighlightPositions();
  if(toHighlight) {
    char *ptr = shn->getText();
    while((ptr = findStrings(ptr, toHighlight, caseSens)) != NULL) {
      addHighlightPosition(shn->getText(), ptr, toHighlight);
      ptr++;
    }
  }

  dontCallLinkUpdate = TRUE;
  XmTextSetString(text,shn->getText());
  dontCallLinkUpdate = FALSE;
  XmTextSetString(titleText, shn->getName());
}

// ------------------------------ 
// do_forward()
// ------------------------------

void MLXHelp::do_forward(Widget, XtPointer)
{

  saveText(NULL,NULL);

  if(historyPage < history.getSize()-1)
    historyPage++;
  
  if(history.getSize() > 0) {
    selectedHelpNode = history[historyPage];
    selectedHelpNode->select();
  
    treeView->scrollToMakeVisible(selectedHelpNode);

    if(history.getSize() > historyPage+1) {
      XtSetSensitive(forwardButton, TRUE);
      XtSetSensitive(historyForward, TRUE);
    } else {
      XtSetSensitive(forwardButton, FALSE);
      XtSetSensitive(historyForward, FALSE);
    }
    if(historyPage > 0) {
      XtSetSensitive(backButton, TRUE);
      XtSetSensitive(historyBack, TRUE);
    } else {
      XtSetSensitive(backButton, FALSE);
      XtSetSensitive(historyBack, FALSE);
    }
    XtSetSensitive(nextSection, selectedHelpNode->getNext() != NULL);
    XtSetSensitive(lastSection, selectedHelpNode->getLast() != NULL);

    emptyHighlightPositions();
    dontCallLinkUpdate = TRUE;
    XmTextSetString(text,selectedHelpNode->getText());
    dontCallLinkUpdate = FALSE;
    XmTextSetString(titleText, selectedHelpNode->getName());
  }
}


// ------------------------------ 
// do_backward()
// ------------------------------

void MLXHelp::do_backward(Widget, XtPointer)
{
  saveText(NULL,NULL);
  
  if(historyPage > 0)
    historyPage--;
  
  if(history.getSize() > 0) {
    selectedHelpNode = history[historyPage];
    selectedHelpNode->select();
  
    treeView->scrollToMakeVisible(selectedHelpNode);

    if(history.getSize() > historyPage+1) {
      XtSetSensitive(forwardButton, TRUE);
      XtSetSensitive(historyForward, TRUE);
    } else {
      XtSetSensitive(forwardButton, FALSE);
      XtSetSensitive(historyForward, FALSE);
    }
    if(historyPage > 0) {
      XtSetSensitive(backButton, TRUE);
      XtSetSensitive(historyBack, TRUE);
    } else {
      XtSetSensitive(backButton, FALSE);
      XtSetSensitive(historyBack, FALSE);
    }
    XtSetSensitive(nextSection, selectedHelpNode->getNext() != NULL);
    XtSetSensitive(lastSection, selectedHelpNode->getLast() != NULL);

    emptyHighlightPositions();
    dontCallLinkUpdate = TRUE;
    XmTextSetString(text,selectedHelpNode->getText());
    dontCallLinkUpdate = FALSE;
    XmTextSetString(titleText, selectedHelpNode->getName());
  }
}


// ---------------------------------
// titleDialogMap()
//
// Fuellt das Eingabefeld mit dem
// Titel den selektierten HelpNodes
// ---------------------------------

void MLXHelp::titleDialogMap(Widget,XtPointer)
{
  XmString xms;
  xms = XmStringCreateLtoR(titleHelpNode->getTitle(), 
			   XmSTRING_DEFAULT_CHARSET);
  XtVaSetValues(titleDialog,
		XmNtextString, xms,
		NULL);
}


// ---------------------------------
// titleChanged()
//
// OK im titleDialog ->
// aendert den Titel und sendet
// ein NAME_CHANGED an den HelpNode
// ---------------------------------

void MLXHelp::titleChanged(Widget,XtPointer)
{
  XmString xms;
  char *str;

  XtVaGetValues(titleDialog,
		XmNtextString, &xms,
		NULL);
  XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &str);
  titleHelpNode->setTitle(str);
  titleHelpNode->changed(NAME_CHANGED);
}


// ---------------------------------
// identDialogMap()
// ---------------------------------

void MLXHelp::identDialogMap(Widget,XtPointer)
{
  XmString xms;
  xms = XmStringCreateLtoR(identHelpNode->getIdent(), 
			   XmSTRING_DEFAULT_CHARSET);
  XtVaSetValues(identDialog,
		XmNtextString, xms,
		NULL);
}


// ---------------------------------
// identChanged()
// ---------------------------------

void MLXHelp::identChanged(Widget,XtPointer)
{
  XmString xms;
  char *str;

  XtVaGetValues(identDialog,
		XmNtextString, &xms,
		NULL);
  XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &str);
  identHelpNode->setIdent(str);
}


// ---------------------------------
// saveText()
//
// Aendert den Text des HelpNodes
// ---------------------------------

void MLXHelp::saveText(Widget,XtPointer)
{
  char *t;
  
  if(!selectedHelpNode.isNil() && editable) {
    t = XmTextGetString(text);
    selectedHelpNode->setText(t);
    XtFree(t);
  }
}


// ------------------------------
// editTitle()
// ------------------------------

void MLXHelp::editTitle(HelpNode *hn)
{
  titleHelpNode = hn;
  XtManageChild(titleDialog);
}


// ------------------------------
// editIdent()
// ------------------------------

void MLXHelp::editIdent(HelpNode *hn)
{
  identHelpNode = hn;
  XtManageChild(identDialog);
}


// ------------------------------
// find()
// ------------------------------

void MLXHelp::find(Cardinal id)
{
  HelpNode *found = helpNode->find(id);
  if(found) {
    setSelectedHelpNode(found);
  } else {
    char buf[256];
    sprintf(buf, "Fatal error: Help for ID %d not found\n", id);
    XmTextSetString(text,buf);
  }
}


// ------------------------------
// do_exportLatex()
// ------------------------------

void MLXHelp::do_exportLatex(Widget,XtPointer)
{
}

// -----------------------------
//   newDrawProc()
// -----------------------------

void MLXHelp::newDrawProc(XmTextWidget textWidget, LineNum line, 
		       XmTextPosition start, XmTextPosition end,
		       XmHighlightMode hlmode)
{
  ::MLXHelp *self = NULL;
  Widget wg = (Widget)textWidget;

  XtVaGetValues(wg,
		XmNuserData, &self,
		NULL);

  if(self) {

    //    self->oldDrawProc(textWidget, line, start, end, hlmode);

    if(start == end)   // seems to draw nothing, but we have to draw the line
      textWidget->text.output->MeasureLine(textWidget, 
					   line, start, &end, NULL);
    if(end == PASTENDPOS)
      end = start;
    self->drawHTLinks(start, end, hlmode);
  }
  
}


class MyItem {
public:
  XmTextPosition begin;
  XmTextPosition end;
  Boolean isHypertext;
  Boolean isHighlight;

  MyItem(XmTextPosition b, XmTextPosition e, Boolean ht, Boolean hl)
  { begin = b; end = e; isHypertext = ht; isHighlight = hl; }
};
  
class HelpfullClass : public TArray<MyItem> {
public:
  HelpfullClass(HelpNode *hn, XmTextPosition begin, XmTextPosition end, 
		TArray<HighlightPosition> *hp) 
  {

    LinkArray *la = hn->getLinks();

    XmTextPosition curBegin = begin;

    while(curBegin < end) {
      XmTextPosition nextPosition = end;
      Boolean wasLink = FALSE;
      Boolean wasHL = FALSE;

      for(unsigned int i=0; i<la->getSize(); i++) {
	XmTextPosition lBegin = (*la)[i]->getBegin();
	XmTextPosition lEnd = (*la)[i]->getEnd();
	XmTextPosition nBegin, nEnd;

	if(lBegin <= curBegin && lEnd > curBegin) {
	  nBegin = curBegin;
	  if(lEnd >= end) 
	    nEnd = end;
	  else
	    nEnd = lEnd;
	  add( new MyItem(nBegin, nEnd, TRUE, FALSE));
	  nextPosition = nEnd;
	  wasLink = TRUE;
	  break;
	} else if(lBegin < end && lBegin > curBegin) {
	  if(nextPosition > lBegin)
	    nextPosition = lBegin;
	}
      }
      if(!wasLink) {
	for(unsigned int i=0; i<hp->getSize(); i++) {
	  XmTextPosition lBegin = (*hp)[i]->begin;
	  XmTextPosition lEnd = (*hp)[i]->end;
	  XmTextPosition nBegin, nEnd;
	  
	  if(lBegin <= curBegin && lEnd > curBegin) {
	    nBegin = curBegin;
	    if(lEnd >= end) 
	      nEnd = end;
	    else
	      nEnd = lEnd;
	    add( new MyItem(nBegin, nEnd, FALSE, TRUE));
	    nextPosition = nEnd;
	    wasHL = TRUE;
	    break;
	  } else if(lBegin < end && lBegin > curBegin) {
	    if(nextPosition > lBegin)
	      nextPosition = lBegin;
	  }
	}
	if(!wasHL)
	  add( new MyItem(curBegin, nextPosition, FALSE, FALSE));
      }
      curBegin = nextPosition;
    }
  }
  
  ~HelpfullClass() 
  {
    for(unsigned int i=0; i<getSize(); i++)
      delete (*this)[i];
  }

};


// -----------------------------
//   drawHTLinks()
// -----------------------------

void MLXHelp::drawHTLinks(XmTextPosition begin, 
			  XmTextPosition end,
			  XmHighlightMode hlmode)
{
  Position beginX, beginY, endX, endY, lastX, lastY;
  Dimension width, height, marginHeight, marginWidth;
  Dimension shadowThickness, highlightThickness;
  GC gc;

  if(normGC == 0) {          		// prepare the GC's
    Pixel fg, bg;
    XGCValues gcValues;
    XmFontContext context;
    XmFontList fl;
    XFontStruct *font;
    Font fid;
    XmStringCharSet charset;
    int direction, ascent, descent;
    XCharStruct charStruct;

    fl = NULL;
    font = NULL;

    XtVaGetValues(text,          // get text widget resource for draw sim
		  XmNbackground, &bg, 
		  XmNforeground, &fg, 
		  XmNfontList, &fl,
		  NULL);

    if(fl) {                     // get the font from the font list
      XmFontListInitFontContext(&context, fl);
      while(XmFontListGetNextFont(context, &charset, &font)) {
	if(!strcmp(charset,XmSFONTLIST_DEFAULT_TAG_STRING)) {
	  XtFree(charset);
	  break;
	}
	XtFree(charset);
	font = NULL;
      }
      XmFontListFreeFontContext(context);
    }
    
    if(font) {                   // get the font id, need it in gcValues
      fid = font->fid;
    } else {
      fid = XLoadFont( XtDisplay(text), "fixed" );
    }
    
    XQueryTextExtents(XtDisplay(text), fid,    // query line height
		      "WyYg", 4,
		      &direction, &ascent, &descent, &charStruct );
    lineHeight = ascent;
    lineBase = descent;

    gcValues.font = fid;              // create normal gc
    gcValues.foreground = fg;
    gcValues.background = bg;
    normGC = XCreateGC(XtDisplay(text), 
		       XtWindow(text),
		       GCBackground | GCForeground | GCFont,
		       &gcValues );
    XFlushGC(XtDisplay(text), normGC );

    gcValues.foreground = bg;		// create inverting gc
    gcValues.background = fg;
    invGC = XCreateGC(XtDisplay(text), 
		      XtWindow(text),
		      GCBackground | GCForeground | GCFont,
		      &gcValues );
    XFlushGC(XtDisplay(text), invGC );

    gcValues.foreground = htPixel;		// create hypertext link gc
    gcValues.background = bg;
    htGC = XCreateGC(XtDisplay(text), 
		     XtWindow(text),
		     GCBackground | GCForeground | GCFont,
		     &gcValues );
    XFlushGC(XtDisplay(text), htGC );

    gcValues.foreground = bg;			// create hypertext link gc
    gcValues.background = htPixel;
    invHtGC = XCreateGC(XtDisplay(text), 
		     XtWindow(text),
		     GCBackground | GCForeground | GCFont,
		     &gcValues );
    XFlushGC(XtDisplay(text), htGC );

    gcValues.foreground = highlightPixel;	// create highlight gc
    gcValues.background = bg;
    hlGC = XCreateGC(XtDisplay(text), 
		     XtWindow(text),
		     GCBackground | GCForeground | GCFont,
		     &gcValues );
    XFlushGC(XtDisplay(text), hlGC );

    gcValues.foreground = bg;			// create invers highlight gc
    gcValues.background = highlightPixel;
    invHlGC = XCreateGC(XtDisplay(text), 
		     XtWindow(text),
		     GCBackground | GCForeground | GCFont,
		     &gcValues );
    XFlushGC(XtDisplay(text), hlGC );
  }

  XmTextPosToXY(text, begin, &beginX, &beginY);
  XmTextPosToXY(text, end, &endX, &endY);

  XtVaGetValues(text, 
		XmNwidth, &width, 
		XmNheight, &height,
		XmNmarginHeight, &marginHeight,
		XmNmarginWidth, &marginWidth,
		XmNshadowThickness, &shadowThickness,
		XmNhighlightThickness, &highlightThickness,
		NULL);

  if(XmTextPosToXY(text, XmTextGetLastPosition(text), &lastX, &lastY)) {
    XClearArea(XtDisplay(text), XtWindow(text), 
	       marginWidth+shadowThickness+highlightThickness, lastY+lineBase,
	       width-(marginWidth+shadowThickness+highlightThickness) * 2, 
	       height-lastY-marginHeight-shadowThickness-highlightThickness, 
	       FALSE);
  }


  if(!hlmode)
    XClearArea(XtDisplay(text), XtWindow(text), 
	       beginX, beginY-lineHeight-1,
	       width-beginX-marginWidth-shadowThickness-highlightThickness, 
	       lineHeight+lineBase+2, FALSE);

  char *str = XmTextGetString(text);

  HelpfullClass bitsToDraw(selectedHelpNode, begin, end, 
			   &currentHighlightPositions);

  for(unsigned int i=0; i<bitsToDraw.getSize(); i++) {

    XmTextPosToXY(text, bitsToDraw[i]->begin, &beginX, &beginY);
    XmTextPosToXY(text, bitsToDraw[i]->end, &endX, &endY);

    if(endY != beginY) {
      endY = beginY;
      endX = width - (marginWidth+shadowThickness+highlightThickness);
    }

    if(!hlmode && !bitsToDraw[i]->isHypertext && !bitsToDraw[i]->isHighlight) {
      gc = normGC;
    } else if(hlmode && !bitsToDraw[i]->isHypertext 
	      && !bitsToDraw[i]->isHighlight) {
      gc = invGC;
      XFillRectangle(XtDisplay(text),XtWindow(text), 
		     normGC, beginX, beginY-lineHeight-1, 
		     endX-beginX, lineHeight+lineBase+2);
    } else if(!hlmode && bitsToDraw[i]->isHypertext) {
      gc = htGC;
    } else if(hlmode && bitsToDraw[i]->isHypertext) {
      gc = invHtGC;
      XFillRectangle(XtDisplay(text),XtWindow(text), 
		     htGC, beginX, beginY-lineHeight-1, 
		     endX-beginX, lineHeight+lineBase+2);
    } else if(!hlmode && bitsToDraw[i]->isHighlight) {
      gc = hlGC;
    } else if(hlmode && bitsToDraw[i]->isHighlight) {
      gc = invHlGC;
      XFillRectangle(XtDisplay(text),XtWindow(text), 
		     hlGC, beginX, beginY-lineHeight-1, 
		     endX-beginX, lineHeight+lineBase+2);
    } else
      gc = normGC;
    
    int len = bitsToDraw[i]->end - bitsToDraw[i]->begin;
    if(str[bitsToDraw[i]->end-1] == '\n')
      len--;
    XDrawString(XtDisplay(text),XtWindow(text), gc,
		beginX, beginY, 
		&(str)[bitsToDraw[i]->begin], len);

  }
  XtFree(str);
}


// -------------------------------
// mouseMotionEvent()
// -------------------------------

void MLXHelp::mouseMotionEvent(Widget wg, XtPointer client, 
			       XEvent *event, Boolean *)
{
  static Cursor clickCursor = 0;
  ::MLXHelp *self = (::MLXHelp*)client;
  XMotionEvent *mEvent = (XMotionEvent*)event;
  XmTextPosition pos = XmTextXYToPos(wg, mEvent->x, mEvent->y);
  HelpNode *hn = self->selectedHelpNode->getLinks()->getClickedHelpNode(pos);

  if(clickCursor == 0)
    clickCursor = XCreateFontCursor(XtDisplay(wg), XC_hand2);

  if(hn) {
    XDefineCursor(XtDisplay(wg), XtWindow(wg), clickCursor);
  } else {
    XUndefineCursor(XtDisplay(wg), XtWindow(wg));
  }
}


// -------------------------------
// buttonPressEvent()
// -------------------------------

void MLXHelp::buttonPressEvent(Widget wg, XtPointer client, 
			       XEvent *, Boolean *)
{
  ::MLXHelp *self = (::MLXHelp*)client;
  Window retRoot, retChild;
  int retRootX, retRootY, retX, retY;
  unsigned int retKey;
  XQueryPointer( XtDisplay(wg), XtWindow(wg), 
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&retX, &retY,
		&retKey );

  if( retKey & Button1Mask ) {
    XmTextPosition pos = XmTextXYToPos(wg, retX, retY);
    HelpNode *hn = self->selectedHelpNode->getLinks()->getClickedHelpNode(pos);
    if(hn)
      self->setSelectedHelpNode(hn);
  }
}

// --------------------------------
// contentsButtonChanged()
// --------------------------------

void MLXHelp::contentsButtonChanged(Widget,XtPointer)
{
  if(XmToggleButtonGetState(contentsButton)) {
    XtManageChild(frame);
  } else {
    XtUnmanageChild(frame);
  }
}

// --------------------------------
// insertLink()
// --------------------------------

void MLXHelp::insertLink(HelpNode *hn)
{
  XmTextPosition begin, end;

  if( XmTextGetSelectionPosition(text, &begin, &end) ) {
    selectedHelpNode->getLinks()->add( new HelpNodeLink(hn, begin, end) );
  }
}


// --------------------------------
// textValueChanged()
// --------------------------------
void MLXHelp::textValueChanged(Widget,XtPointer call)
{
  XmTextVerifyCallbackStruct *cbs = (XmTextVerifyCallbackStruct *)call;

  if(!dontCallLinkUpdate) {
    selectedHelpNode->getLinks()->update(cbs->startPos, cbs->endPos,
					 cbs->text->length);
    emptyHighlightPositions();
  }
}

// --------------------------------
// cancelFindDialog()
// --------------------------------
void MLXHelp::cancelFindDialog(Widget,XtPointer)
{
  XtUnmanageChild(findDialog);
}

// --------------------------------
// okFindDialog()
// --------------------------------  
void MLXHelp::okFindDialog(Widget,XtPointer)
{
  XmString xms;
  char *str;
  Boolean found = FALSE;

  Boolean findBegin = XmToggleButtonGetState(findBeginToggle);
  Boolean caseSens = XmToggleButtonGetState(findCaseToggle);

  xms = NULL;
  XtVaGetValues(findDialog, XmNtextString, &xms, NULL);
  if(xms) {
    XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &str);
    if(str && *str) {
      HelpNode *toSearch;
      if(findBegin)
	toSearch = helpNode;
      else
	toSearch = selectedHelpNode->getNext();
      while(toSearch) {
	char *searchRes = findStrings(toSearch->getText(), str, caseSens);
	if(searchRes != NULL) {
	  XmToggleButtonSetState(findBeginToggle, FALSE, FALSE);
	  setSelectedHelpNode(toSearch, str, caseSens);
	  XmTextSetTopCharacter(text, searchRes - toSearch->getText());
	  found = TRUE;
	  break;
	}
	toSearch = toSearch->getNext();
      }
    }
    if(str)
      XtFree(str);
  }
  if(!found) {
    XBell(XtDisplay(text), 500);
    XmToggleButtonSetState(findBeginToggle, TRUE, FALSE);
  }
}

// --------------------------------
// mapFindDialog()
// --------------------------------
void MLXHelp::mapFindDialog(Widget,XtPointer)
{
  XmToggleButtonSetState(findBeginToggle, TRUE, FALSE);
}

// --------------------------------
// do_lastSection()
// --------------------------------
void MLXHelp::do_lastSection(Widget,XtPointer)
{
  HelpNode *hn = selectedHelpNode->getLast();
  if(hn)
    setSelectedHelpNode(hn);
}

// --------------------------------
// do_nextSection()
// --------------------------------
void MLXHelp::do_nextSection(Widget,XtPointer)
{
  HelpNode *hn = selectedHelpNode->getNext();
  if(hn)
    setSelectedHelpNode(hn);
}

// --------------------------------
// mapExportDialog()
// --------------------------------
void MLXHelp::mapExportDialog(Widget,XtPointer)
{
  XmString xms;
  
  char filename[PATH_MAX];
  
  getcwd(filename, PATH_MAX);
  if(filename[strlen(filename)-1] != '/') {
    strcat(filename, "/");
  }
  strcat(filename, "documentation.txt");
  xms = XmStringCreateLtoR(filename, XmSTRING_DEFAULT_CHARSET);
  XtVaSetValues(exportDialog, 
		XmNtextString, xms,
		NULL );
  XmStringFree(xms);

  XtVaSetValues(exportType, XmNmenuHistory, plainText, NULL);
}

// --------------------------------
// exportTypeChanged()
// --------------------------------
void MLXHelp::exportTypeChanged(Widget, XtPointer callData)
{
  XmString xms = NULL;
  char *str = NULL;
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callData;
  
  XtVaGetValues(exportDialog, XmNtextString, &xms, NULL);
  if(xms) {
    XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &str);
    if(str) {
      char filename[PATH_MAX];
      strcpy(filename, str);
      for(int i=strlen(filename)-1; i>=0; i--) {        // find the dot
	if(filename[i] == '.') {
	  filename[i] = 0;
	  if(cbs->widget == plainText) 
	    strcat(filename, ".txt");
	  else if(cbs->widget == latexFormat)
	    strcat(filename, ".tex");
	  else if(cbs->widget == htmlText)
	    strcat(filename, ".html");
	  else
	    fprintf(stderr, "Fatal error: cbs->widget is invalid\n");

	  xms = XmStringCreateLtoR(filename, XmSTRING_DEFAULT_CHARSET);
	  XtVaSetValues(exportDialog, XmNtextString, xms, NULL);
	  XmStringFree(xms);
	  break;
	} else if(filename[i] == '/') {
	  break;
	}
      }
      XtFree(str);
    }
  }
}

// --------------------------------
// do_export()
// --------------------------------
void MLXHelp::do_export(Widget,XtPointer)
{
  Widget wg;
  char *str;
  XmString xms;
  FILE *fp;

  XtVaGetValues(exportDialog, XmNtextString, &xms, NULL);
  XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &str);
  if(str) {
    fp = fopen(str, "w");

    if(fp) {
      XtVaGetValues(exportType, XmNmenuHistory, &wg, NULL);
      if(wg == plainText) {
	helpNode->exportPlainText(fp, NULL);
      } else if(wg == latexFormat) {
	helpNode->exportLatex(fp, 0);
      } else {
	helpNode->exportHTML(fp, NULL);
      }
      fclose(fp);
    } else {
      perror("fopen");
      fprintf(stderr, "Fatal error: can't open file '%s'.\n", str);
    }
    XtFree(str);
  }
}


// --------------------------------
// findStrings()
// --------------------------------
char *MLXHelp::findStrings(char *source, char *toFind, Boolean caseSens)
{
  unsigned int len;
  char *ptr;

  len = strlen(toFind);
  ptr = source;

  while(*ptr) {
    unsigned int i;
    Boolean doNext;

    for(i=0, doNext = TRUE; i<len && ptr[i] && doNext; i++) {
      if(ptr[i] == toFind[i] || 
	 (!caseSens && tolower(ptr[i]) == tolower(toFind[i]))) 
	doNext = TRUE;
      else
	doNext = FALSE;
    }
    if(i == len && doNext)
      return ptr;
    ptr++;
  }
  return NULL;
}


// --------------------------------
// addHighlightPosition()
// --------------------------------
void MLXHelp::addHighlightPosition(char *source, char *first, char *toFind)
{
  HighlightPosition *hp = new HighlightPosition;
  hp->begin = first-source;
  hp->end = hp->begin + strlen(toFind);
  currentHighlightPositions.add(hp);
}


// --------------------------------
// emptyHighlightPositions()
// --------------------------------
void MLXHelp::emptyHighlightPositions()
{
  for(unsigned int i=0; i<currentHighlightPositions.getSize(); i++) {
    delete currentHighlightPositions[i];
  }
  currentHighlightPositions.empty();
}

