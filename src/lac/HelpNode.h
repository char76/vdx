/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: HelpNode.h,v $
 *  $Date: 1999/08/27 15:29:26 $
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
 * $Log: HelpNode.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:26  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  19:48:58  lazy
 * Dont know.
 *
 * Revision 1.1  1995/09/29  17:46:38  lazy
 * Initial revision
 *
 * Revision 1.3  1995/09/27  21:01:33  lazy
 * Header fertig.
 *
 */

#ifndef _HELPNODE_H_
#define _HELPNODE_H_

#define HELPNODE_PIXMAP "@HelpNode"

#include <lac/TreeNode.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

struct HelpResource {      // filled in by XtGetSubResources
  char *title;
  char *sections;
  char *text;
  char *ident;
  char *links;               // hypetext links in string format
};

class HelpNode;

// a links item

class HelpNodeLink : public Lobject {
private:
  Ref<HelpNode> refers;
  XmTextPosition begin;
  XmTextPosition end;
  Cardinal tmpId;
  
  void delNotify(BaseRef *);
  
public:
  HelpNodeLink(char *string);      // restore a link
  HelpNodeLink(HelpNode *hn, XmTextPosition b, XmTextPosition e);
  
  void getString(char *str, unsigned int &len);  // for persistence
  HelpNode *getHelpNode();                       // query refers
  Boolean isIn(XmTextPosition klickPoint);       // is this the link ?
  void resolveRefers(HelpNode *root);
  
  XmTextPosition getBegin() { return begin; }
  XmTextPosition getEnd() { return end; }
  
  Boolean update(XmTextPosition b, XmTextPosition e, int length);
};

// the array of links

class LinkArray : public RefArray<HelpNodeLink> {   
public:
  ~LinkArray();
  HelpNode *getClickedHelpNode(XmTextPosition pos);
  void getString(char *str, unsigned int &len);
  void restoreFromString(char *str);
  void update(XmTextPosition begin, XmTextPosition end, int length);
};


// the HelpNode class


class HelpNode : public TreeNode<HelpNode> {
private:
  static RefArray<Selectable> selection;

  LinkArray links;

  Widget associatedWidget;
  char *path;
  Cardinal id;
  HelpResource hRes;
  char *title;
  char *text;
  char *ident;

  void getResources();
  void createSections();
  void buildPath();
  void resolveLinks(HelpNode *root);

  static void getResourceText(char *str, char *buffer, unsigned long &len);

  void newID(Cardinal &id);

  RefArray<Selectable> &getPrivateSelection(Boolean &pri);

public:
  HelpNode(HelpNode *p, Cardinal id);           // creates a sections
  HelpNode(Widget associatedWidget);        // creates the root of a three
  ~HelpNode();

  char *getPath() { return path; }
  char *getTitle() { return title; }
  char *getText() { return text; }
  char *getName() { return title; }
  char *getIdent() { return ident; }
  Cardinal getId() { return id; }
  LinkArray *getLinks() { return &links; }

  void setText(char*);
  void setTitle(char*);
  void setIdent(char *);

  Boolean setName(char *s) { setTitle(s); return TRUE; }
  Boolean nameChangeable() { return TRUE; }
  Boolean asChildOk(HelpNode *) { return TRUE; }

  HelpNode *getNext();
  HelpNode *getLast();

  HelpNode *find(Cardinal id);

  void writeTo(FILE *fp);
  void writeHeader(FILE *fp);
  void exportLatex(FILE *fp, int depth);
  void exportPlainText(FILE *fp, char *parentSection);
  void exportHTML(FILE *fp, char *parentSection);

  char *getClassName() { return "HelpNode"; }
  char *getPixmapFile();
};

#endif 
