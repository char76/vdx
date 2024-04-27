/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MLXHelp.h,v $
 *  $Date: 1999/08/27 15:29:49 $
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
 * $Log: MLXHelp.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:49  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:32:29  lazy
 * Initial revision
 *
 * Revision 1.1  1995/09/27  21:04:41  lazy
 * Initial revision
 *
 */

// ----------------------------
// MLXHelp.h
// ----------------------------

#ifndef _MLXHelp_H_
#define _MLXHelp_H_

#include <lac/HelpNode.h>
#include <lac/MLXHelp_base.h>
#include <lac/TreeView.h>
#include <Xm/TextOutP.h>

class HelpTreeNodeView;
//class HelpNodeMenu;

// A pair of text positions, which are the beginning and the end of
// a highlighted.
struct HighlightPosition {
  XmTextPosition begin;
  XmTextPosition end;
};

class MLXHelp : public MLXHelp_base {
protected:

  // ---- for finding and highlighting functionality -----

  // Search for a string toFind in source and returns the pointer
  // to this substring. If caseSens is TRUE the search is done with
  // case sensitive comparation
  char *findStrings(char *source, char *toFind, Boolean caseSens);

  // An a array of all highlighted text positions.
  TArray<HighlightPosition> currentHighlightPositions;

  // add a text string to currentHighlightPositions
  void addHighlightPosition(char *source, char *first, char *toFind);

  // make the currentHighlightPositions empty
  void emptyHighlightPositions();

  // The highlight color. adjustable with resource charHighlightColor.
  Pixel highlightPixel;

  
  // ---- Drawing of Hypertext and Highlight string ----

  // In this variable we're saving the old drawing procedure of the
  // text widget.
  DrawProc oldDrawProc;

  // This is the new drawing procedure
  static void newDrawProc(XmTextWidget, LineNum, XmTextPosition,
			  XmTextPosition,	XmHighlightMode);
  
  // Mouse move event to trace the pointer position and change
  // the pointer, if it is over a hypertext link.
  static void mouseMotionEvent(Widget, XtPointer client, 
			       XEvent *event, Boolean *);
  
  // If the user press the left mouse butten over a hypertext link,
  // the is a little bit to do.
  static void buttonPressEvent(Widget, XtPointer client, 
			       XEvent *event, Boolean *);

  // This funktion draws the strings depending on the hypertext links
  // highlight characters.
  void drawHTLinks(XmTextPosition begin, XmTextPosition end, 
		   XmHighlightMode hlmode);

  // To adjust the color of hypertext links und highlight chars, we
  // need a XtResourceList.
  static XtResource mlxHelpResources[];

  // hypertextColor
  Pixel htPixel;

  // need a graphic contexts to draw the different text.
  GC normGC, invGC;
  GC htGC, invHtGC;
  GC hlGC, invHlGC;
  Dimension lineHeight, lineBase;

  // If this is TRUE, the function textValueChanged() does not call the
  // link update function.
  Boolean dontCallLinkUpdate;

  // root HelpNode - the top help node of the whole document.
  HelpNode *helpNode;

  // The History of help sections.
  RefArray<HelpNode> history;
  // the current visitited history page.
  unsigned historyPage;        

  // The help node which is selected and visible in the text widget.
  Ref<HelpNode> selectedHelpNode;            

  // The help node, which is edited by the title dialog
  Ref<HelpNode> titleHelpNode;

  // The help node, which is edited by the ident dialog
  Ref<HelpNode> identHelpNode;

  // Contents tree view
  TreeView *treeView;                    

  // prototype for the contents tree view
  HelpTreeNodeView *htnv;                

  // The filenames of the help file (*.hlp) the header file (*.h) and
  // the export file.
  char filename[PATH_MAX];
  char headerFilename[PATH_MAX];
  char latexName[PATH_MAX];

  // if editable is TRUE, the edit menu is visible and the text widget
  // is used to edit the section text. The context menus in the contents
  // tree view have more items (e.g. for link creation).
  Boolean editable;

  // the callbacks
  virtual void exitMLXHelp(Widget,XtPointer);
  virtual void saveFile(Widget,XtPointer);
  virtual void titleDialogMap(Widget,XtPointer);
  virtual void titleChanged(Widget,XtPointer);
  virtual void saveText(Widget,XtPointer);
  virtual void do_forward(Widget,XtPointer);
  virtual void do_backward(Widget,XtPointer);
  virtual void identDialogMap(Widget,XtPointer);
  virtual void identChanged(Widget,XtPointer);
  virtual void do_exportLatex(Widget,XtPointer);
  virtual void contentsButtonChanged(Widget,XtPointer);
  virtual void textValueChanged(Widget,XtPointer);
  virtual void cancelFindDialog(Widget,XtPointer);
  virtual void mapFindDialog(Widget,XtPointer);
  virtual void okFindDialog(Widget,XtPointer);
  virtual void do_lastSection(Widget,XtPointer);
  virtual void do_nextSection(Widget,XtPointer);
  virtual void mapExportDialog(Widget,XtPointer);
  virtual void exportTypeChanged(Widget,XtPointer);
  virtual void do_export(Widget,XtPointer);

  // Don't destroy this help instance, if the users closes the window
  // by window manager.
  void wmDelete() { LicView::close(); }

public:  
  // yes, the constructor
  MLXHelp(char *filename = NULL, Widget parent = NULL, HelpNode *hn = NULL);
  ~MLXHelp();

  // Sets the selected help node, which will be visible in this
  // help instance.
  void setSelectedHelpNode(HelpNode *shn, 
			   char *toHighlight = NULL, Boolean caseSens = FALSE);

  // Shows the titleDialog.
  void editTitle(HelpNode *);
  // Shows the identDialog.
  void editIdent(HelpNode *);

  // Insert a link in the selected help node, depending on the selected string.
  void insertLink(HelpNode *);

  // some query methods
  Boolean isEditable() { return editable; }
  char *getFilename() { return filename; }
  HelpNode *getHelpNode() { return helpNode; }

  // sets the filename of the help file.
  void setFilename(char *fName);

  // displays a help node with id
  void find(Cardinal id);
};


#endif /* Don't add stuff after this #endif */


