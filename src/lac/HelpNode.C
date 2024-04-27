/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: HelpNode.C,v $
 *  $Date: 1999/08/27 15:29:25 $
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
 * $Log: HelpNode.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:25  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:28  lazy
 * Initial revision
 *
 * Revision 1.9  1995/09/27  21:00:01  lazy
 * Nach einigen 'rumtesten, habe ich
 * den Header fertig.
 *
 */

#include "HelpNode.h"
#include "View.h"
#include "helpnode.xpm"
#include <ctype.h>

#define SUBPART "help"
#define DEFAULT_TITLE "SUBSECTION"

RefArray<Selectable> HelpNode::selection;

// -----------------------------------------------------------
//              SubResourcesLists
// -----------------------------------------------------------

static XtResource helpResources [] = {
  {
    "title", "Title", XmRString, sizeof(String),
    XtOffsetOf(HelpResource, title), XtRImmediate, (XtPointer)NULL
  },
  {
    "ident", "Ident", XmRString, sizeof(String),
    XtOffsetOf(HelpResource, ident), XtRImmediate, (XtPointer)NULL
  },
  {
    "sections", "Sections", XmRString, sizeof(String),
    XtOffsetOf(HelpResource, sections), XtRImmediate, (XtPointer)NULL
  },
  {
    "hypertextLinks", "HyperTextLinks", XmRString, sizeof(String),
    XtOffsetOf(HelpResource, links), XtRImmediate, (XtPointer)NULL
  },
  {
    "text", "Text", XmRString, sizeof(String),
    XtOffsetOf(HelpResource, text), XtRImmediate, (XtPointer)NULL
  }
};


// ------------------------------
// HelpNodeLink()
// ------------------------------
HelpNodeLink::HelpNodeLink(char *string)
  :refers(NULL, this)
{
  if(!string)
    return;
  sscanf(string, "%d %ld %ld", &tmpId, &begin, &end);
}

// ------------------------------
// HelpNodeLink()
// ------------------------------
HelpNodeLink::HelpNodeLink(HelpNode *hn, XmTextPosition b, XmTextPosition e)
  :refers(hn,this), begin(b), end(e)
{
  
}

// ------------------------------
// resolveRefers()
// ------------------------------
void 
HelpNodeLink::resolveRefers(HelpNode *root)
{
  refers = root->find(tmpId);
  if(refers.isNil()) {
    fprintf(stderr, 
	    "Fatal Error: can't resolve hypertext link to %d\n", tmpId);
  }
}

// ------------------------------
// delNotify()
// ------------------------------
void 
HelpNodeLink::delNotify(BaseRef *ref)
{
  if(ref == &refers)
    delete this;
}

// ------------------------------
// getString()
// ------------------------------
void 
HelpNodeLink::getString(char *str, unsigned int &len)
{
  char buf[256];
  unsigned int i;

  sprintf(buf, "%d %ld %ld ", refers->getId(), begin, end);
  i = strlen(buf)+1;
  if(str && len >= i)
    strcpy(str, buf);
  len = i;
}

// ------------------------------
// getHelpNode()
// ------------------------------
HelpNode *
HelpNodeLink::getHelpNode()
{
  return refers;
}

// ------------------------------
// isIn()
// ------------------------------
Boolean 
HelpNodeLink::isIn(XmTextPosition klickPoint)
{
  return ((klickPoint >= begin) && (klickPoint < end));
}


// -------------------------------
// HelpNodeLinks: update()
// -------------------------------

Boolean 
HelpNodeLink::update(XmTextPosition b, XmTextPosition e, int length)
{
  
  if(b >= end)
    return FALSE;

  if(begin >= b && end <= e)
    return TRUE;

  if(e < begin) {
    begin += b - e + length;
    end   += b - e + length;
  } else if(b <= begin && e < end) {
    begin = e + length;
    end   += b - e + length;
  } else if(b > begin && e < end) {
    end   += b - e + length;
  } else if(b > begin && e >= end) {
    end = b;
  }
  
  return FALSE;
}

// -------------------------------
// LinkArray: getClickedHelpNode()
// -------------------------------

LinkArray::~LinkArray()
{
  while(getSize()) {
    (*this)[0].Delete();
  }
}

// -------------------------------
// LinkArray: getClickedHelpNode()
// -------------------------------

HelpNode *
LinkArray::getClickedHelpNode(XmTextPosition pos)
{
  for(unsigned int i=0; i<getSize(); i++) {
    if((*this)[i]->isIn(pos)) {
      return (*this)[i]->getHelpNode();
    }
  }
  return NULL;
}

// -----------------------------
// LinkArray: getString()
// -----------------------------

void 
LinkArray::getString(char *str, unsigned int &len)
{
  unsigned int l;
  unsigned int tmp, left;
  char *ptr;

  l = 0;
  for(unsigned int i=0; i<getSize(); i++) {
    (*this)[i]->getString(NULL, tmp);
    l += tmp;
  }
  l++;        // zero terminated

  if(str && len >= l) {
    left = len;
    ptr = str;
    for(unsigned int i=0; i<getSize(); i++) {
      tmp = left;
      (*this)[i]->getString(ptr, tmp);
      ptr += tmp-1;   // plus len minus terminating zero byte
    }
    *ptr = 0;
  }
  len = l;
}

// ------------------------------
// LinkArray: restoreFromString()
// ------------------------------

void 
LinkArray::restoreFromString(char *str)
{
  char *ptr;
  long dummy2, dummy3;
  Cardinal dummy1;
  int ret;

  ptr = str;
  ret = sscanf(ptr, "%d %ld %ld", &dummy1, &dummy2, &dummy3);
  while(ret == 3) {
    add(new HelpNodeLink(ptr));
    while(*ptr && isspace(*ptr)) ptr++;  // leading space
    while(*ptr && !isspace(*ptr)) ptr++; // first number
    while(*ptr && isspace(*ptr)) ptr++;  // space
    while(*ptr && !isspace(*ptr)) ptr++; // second
    while(*ptr && isspace(*ptr)) ptr++;  // space
    while(*ptr && !isspace(*ptr)) ptr++;
    while(*ptr && isspace(*ptr)) ptr++;
    ret = sscanf(ptr, "%d %ld %ld", &dummy1, &dummy2, &dummy3);
  }
}


// -----------------------------
// update()
// -----------------------------

void 
LinkArray::update(XmTextPosition begin, XmTextPosition end, int length)
{
  RefArray<HelpNodeLink> needDestroy;

  for(unsigned int i=0; i<getSize(); i++) {
    if((*this)[i]->update(begin, end, length))
      needDestroy.add((*this)[i]);
  }
  while(needDestroy.getSize())
    needDestroy[0].Delete();
}

// -----------------------------
// HelpNode()  Root constructor
// -----------------------------

HelpNode::HelpNode(Widget aW)
{

  associatedWidget = aW;
  id = 0;

  buildPath();
  getResources();
  if(hRes.sections)
    createSections();
  resolveLinks(this);
}


// ---------------------------------
// HelpNode()  Sections constructor
// ---------------------------------

HelpNode::HelpNode(HelpNode *p, Cardinal id)
{
  this->id = id;
  associatedWidget = p->associatedWidget;
  if(id>0) {
    buildPath();
    getResources();
    if(hRes.sections)
      createSections();
    if(children.getSize() > 0) {
    }
  } else {
    HelpNode *pa = p;
    Cardinal myID = id;
    while( pa->parent ) pa = pa->parent;
    pa->newID(myID);
    this->id = myID;

    buildPath();
    title = new char[strlen(DEFAULT_TITLE)+1];
    strcpy(title, DEFAULT_TITLE);
    text = new char[1];
    text[0] = 0;
    ident = new char[1];
    ident[0] = 0;
  }
}


// ---------------------------------
// resolveLinks()
// ---------------------------------

void HelpNode::resolveLinks(HelpNode *root)
{
  for(unsigned int i=0; i<links.getSize(); i++) {    // do my links
    links[i]->resolveRefers(root);
  }
  for(unsigned int i=0; i<children.getSize(); i++) { // say children
    children[i]->resolveLinks(root);
  }
}

// ---------------------------------
// getResources()
// ---------------------------------

void HelpNode::getResources()
{
  XtGetSubresources(associatedWidget, &hRes, path, path,
		    helpResources, XtNumber(helpResources),
		    NULL, 0);
  if(!hRes.title) 
    hRes.title = "Warning: Inconsistent Help resources.";
  if(!hRes.text) 
    hRes.text = "Warning: Inconsistent Help resources.\nCheck the resources file entries.";
  if(!hRes.ident) 
    hRes.ident = "";

  title = new char[strlen(hRes.title)+1];
  strcpy(title, hRes.title);
  ident = new char[strlen(hRes.ident)+1];
  strcpy(ident, hRes.ident);
  text = new char[strlen(hRes.text)+1];
  strcpy(text, hRes.text);

  if(hRes.links)
    links.restoreFromString(hRes.links);
}


// ---------------------------------
// createSections()
// ---------------------------------

void HelpNode::createSections()
{
  char *item;
  char ptr[strlen(hRes.sections)+1];
  char *items[strlen(hRes.sections)+1];   // heuristic
  int i;

  strcpy(ptr, hRes.sections);
  memset(items, 0, (strlen(hRes.sections)+1)*sizeof(char*));

  i = 0;
  item = strtok(ptr," ");
  if(item) {
    items[i] = item;
    i++;

    while((item = strtok(NULL, " ")))
      items[i++] = item;
    
    for(i=0; items[i]; i++)
      add(new HelpNode(this, atoi(items[i])));
  } else {
    if(ptr[0]) {
      add(new HelpNode(this, atoi(ptr)));
    }
  }
}

// ---------------------------------
// buildPath()
// ---------------------------------

void HelpNode::buildPath()
{
  path = new char[strlen(SUBPART)+10];     // muss reichen
  sprintf(path, "%s_%d", SUBPART, id);
}


// ---------------------------------
// newID()
// ---------------------------------

void HelpNode::newID(Cardinal &id)
{
  if(this->id >= id) 
    id = this->id+1;
  for(unsigned int i=0; i<children.getSize(); i++)
    children[i]->newID(id);
}

// ---------------------------------
// ~HelpNode()
// ---------------------------------

HelpNode::~HelpNode()
{
  delete path;
  delete title;
  delete text;
  delete ident;
}


// ---------------------------------
// writeTo()
// ---------------------------------

void HelpNode::writeTo(FILE *fp)
{
  unsigned int i;
  unsigned long len;

  getResourceText(getTitle(), NULL, len);
  char t1[len];
  getResourceText(getTitle(), t1, len);
  fprintf(fp, "*MLXHelp.%s.title: %s\n", path, t1);

  getResourceText(getIdent(), NULL, len);
  char ident[len];
  getResourceText(getIdent(), ident, len);
  fprintf(fp, "*MLXHelp.%s.ident: %s\n", path, ident);

  unsigned int aLen;
  links.getString(NULL, aLen);
  char linksString[aLen];
  links.getString(linksString, aLen);
  
  getResourceText(linksString, NULL, len);
  char htlinks[len];
  getResourceText(linksString, htlinks, len);
  fprintf(fp, "*MLXHelp.%s.hypertextLinks: %s\n", path, htlinks);

  if(children.getSize() > 0) {
    fprintf(fp, "*MLXHelp.%s.sections: ", path);
    for(i=0; i<children.getSize(); i++) {
      fprintf(fp, " %d", children[i]->id);
    }
    fprintf(fp, "\n");
  }
  getResourceText(getText(), NULL, len);
  char t2[len];
  getResourceText(getText(), t2, len);
  if(t2) {
    fprintf(fp, "*MLXHelp.%s.text: %s\n", path, t2);
  }
  fprintf(fp, "\n");
  for(i=0; i<children.getSize(); i++) {
    children[i]->writeTo(fp);
  }
}

// ---------------------------------
// setText()
// ---------------------------------

void HelpNode::setText(char *t)
{
  delete text;
  text = new char[strlen(t)+1];
  strcpy(text, t);
}


// ---------------------------------
// setTitle()
// ---------------------------------

void HelpNode::setTitle(char *t)
{
  delete title;
  title = new char[strlen(t)+1];
  strcpy(title, t);
  if(ident[0] == 0) {
    delete ident;
    ident = new char[strlen(t)+4+1];
    strcpy(ident, "HID_");
    strcat(ident, t);
    for(unsigned int i=0; ident[i]; i++) {
      ident[i] = toupper(ident[i]);
      if((ident[i] < 'A' || ident[i] > 'Z') && 
	 (ident[i] < '0' || ident[i] > '9'))
	ident[i] = '_';
    }
  }
}


// ---------------------------------
// setIdent()
// ---------------------------------

void HelpNode::setIdent(char *t)
{
  delete ident;
  ident = new char[strlen(t)+1];
  strcpy(ident, t);
}


// ---------------------------------
// getResourceText()
// ---------------------------------

void HelpNode::getResourceText(char *str, char *buffer, unsigned long &len)
{
  unsigned long l, i;

  if(buffer == NULL) {
    for(l = i = 0; str[i]; i++, l++) {
      switch(str[i]) {
      case '\n':
	l++; l++; l++;    // \n -> "\n\"\n
	break;
      default:
	break;
      }
    }
    l++;       // mit null
    
    len = l;
    return;
  }
  
  for(l = i = 0; str[i]; i++, l++) {
    switch(str[i]) {
    case '\n':
      buffer[l++] = '\\';
      buffer[l++] = 'n';
      if(str[i+1] != 0)             // if this is the last character, we don't
	buffer[l++] = '\\';         // need a backslash
      buffer[l] = '\n';
      break;
    default:
      buffer[l] = str[i];
      break;
    }
  }
  buffer[l] = 0;
}


// ---------------------------------
// find()
// ---------------------------------

HelpNode *HelpNode::find(Cardinal id)
{
  if(this->id == id) 
    return this;
  for(unsigned int i=0; i<children.getSize(); i++) {
    HelpNode *ret = children[i]->find(id);
    if(ret) 
      return ret;
  }
  return NULL;
}


// ---------------------------------
// getPrivateSelection()
// ---------------------------------

RefArray<Selectable> &HelpNode::getPrivateSelection(Boolean &pri)
{
  pri = TRUE;
  return HelpNode::selection;
}


// ---------------------------------
// getPixmapFile()
// ---------------------------------

char *HelpNode::getPixmapFile()
{ 
  static Boolean init = TRUE;
  if(init) {
    init = FALSE;
    WinView::addIcon(HELPNODE_PIXMAP, helpnode_xpm);
  }
  return HELPNODE_PIXMAP; 
}


// ---------------------------------
// writeHeader()
// ---------------------------------

void HelpNode::writeHeader(FILE *fp)
{
  fprintf(fp, "#ifndef %s\n", ident);
  fprintf(fp, "#define %s %d\n", ident, id);
  fprintf(fp, "#endif\n\n");
  for(unsigned int i=0; i<children.getSize(); i++) {
    children[i]->writeHeader(fp);
  }
}


// ---------------------------------
// exportLatex()
// ---------------------------------
void myReplace(char *tmp, char *rep, char *newStr) 
{
  char res[strlen(tmp)*2];
  char *ptr = tmp;
  char *ptr2 = res;
  *ptr2 = 0;
  while(*ptr) {
    if(!strncmp(ptr, rep, strlen(rep))) {
      strcat(ptr2, newStr);
      ptr2 += strlen(newStr);
      ptr += strlen(rep);
    } else {
      *ptr2 = *ptr;
      ptr2++; ptr++;
      *ptr2 = 0;
    }
  }
  strcpy(tmp, res);
}

void makeItNice(char *ptr, int maxColumns)
{
  int currentColumn;
  char *lastSpace;

  currentColumn = 0;
  lastSpace = NULL;

  while(*ptr) {
    if(currentColumn >= maxColumns) {
      if(lastSpace) {
	*lastSpace = '\n';
	currentColumn = ptr - lastSpace - 1;
      } else {
	*(ptr - 1) = 'n';
	currentColumn = 0;
      }
    } else {
      if(*ptr == '\n') {
	lastSpace = NULL;
	currentColumn = 0;
      } else {
	if(isspace(*ptr)) 
	  lastSpace = ptr;
	currentColumn++;
      }
    }
    ptr++;
  }
}

void HelpNode::exportLatex(FILE *fp, int depth)
{
  char *section = "section";

  if(depth == 1)
    section = "section";
  else if(depth == 2)
    section = "subsection";
  else if(depth == 3)
    section = "subsubsection";
  else if(depth > 3)
    section = "minisection";

  if(depth == 0) {
    char tmp[strlen(getName())*2];
    strcpy(tmp,getName());
    myReplace(tmp, "&", "\\&");
    myReplace(tmp, "_", "\\_");
    myReplace(tmp, "$", "\\$");
    myReplace(tmp, "<", "$<$");
    myReplace(tmp, ">", "$>$");
    myReplace(tmp, "#", "\\#");
    myReplace(tmp, "\n\n", "\\par\\medskip ");
    myReplace(tmp, "\n", "\\par ");
    fprintf(fp,"\\documentstyle{article}\n\n");
    fprintf(fp,"\\title{%s}\n", tmp);
    fprintf(fp,"\\author{%s}\n", "Latex Export");
    fprintf(fp,"\\parindent0cm\n");
    fprintf(fp,"\\begin{document}\n\n");
    fprintf(fp,"\\maketitle\n\n");
    fprintf(fp,"\\tableofcontents\n\\bigskip\n\n");
  } else {
    char tmp[strlen(getName())*2];
    strcpy(tmp,getName());
    myReplace(tmp, "&", "\\&");
    myReplace(tmp, "_", "\\_");
    myReplace(tmp, "$", "\\$");
    myReplace(tmp, "<", "$<$");
    myReplace(tmp, ">", "$>$");
    myReplace(tmp, "#", "\\#");
    myReplace(tmp, "\n\n", "\\par\\medskip ");
    myReplace(tmp, "\n", "\\par ");
    fprintf(fp,"\\%s{%s}\n\n", section, tmp);
  }

  char tmp[strlen(getText())*3];
  strcpy(tmp,getText());
  myReplace(tmp, "&", "\\&");
  myReplace(tmp, "_", "\\_");
  myReplace(tmp, "$", "\\$");
  myReplace(tmp, "<", "$<$");
  myReplace(tmp, ">", "$>$");
  myReplace(tmp, "#", "\\#");
  myReplace(tmp, "\n\n", "\\medskip\n ");
  myReplace(tmp, "\n", "\\par\n");

  makeItNice(tmp, 75);

  fprintf(fp,"%s\n\n", tmp);

  for(unsigned int i=0; i<children.getSize(); i++) {
    children[i]->exportLatex(fp, depth+1);
  }
  
  if(depth == 0) {
    fprintf(fp,"\\end{document}\n");
  }
}

// ----------------------------
// exportPlainText()
// ----------------------------

void HelpNode::exportPlainText(FILE *fp, char *parentSection)
{
  char mySection[256];
  int childNum = 0;

  if(parent) {                           // query my child number
    for(unsigned int i=0; i<parent->children.getSize(); i++) {
      if(parent->children[i] == this) {
	childNum = i+1;
	break;
      }
    }
  }

  if(parentSection) {                    // I'm not the root node
    char toCat[8];
    strcpy(mySection, parentSection);    // build my section number
    if(*mySection) {
      sprintf(toCat, ".%d", childNum);
      strcat(mySection, toCat);
    } else {
      sprintf(toCat, "%d", childNum);
      strcat(mySection, toCat);
    }
    fprintf(fp, "%s %s\n", mySection, getTitle());
    for(unsigned int i=0; i<(strlen(mySection)+strlen(getTitle())+1); i++)
      fprintf(fp, "-");
  } else {                              // I'm the root node
    strcpy(mySection, "");
    fprintf(fp, "%s\n", getTitle());
    for(unsigned int i=0; i<strlen(getTitle()); i++)
      fprintf(fp, "-");
  }
  fprintf(fp,"\n\n");

  char buf[strlen(getText())+1];        // make a word wrap vvvvv

  strcpy(buf, getText());

  makeItNice(buf, 75);

  fprintf(fp, "%s\n", buf);       // end of word wrap, do the output
  if(buf[strlen(buf)-1] != '\n')
    fprintf(fp, "\n");
  
  for(unsigned int i=0; i<children.getSize(); i++) {  
    children[i]->exportPlainText(fp, mySection); // and now the subsections
  }
}

// ----------------------------
// exportHTML()
// ----------------------------

void HelpNode::exportHTML(FILE *fp, char *parentSection)
{
  char mySection[256];
  int childNum = 0;

  if(parent) {                           // query my child number
    for(unsigned int i=0; i<parent->children.getSize(); i++) {
      if(parent->children[i] == this) {
	childNum = i+1;
	break;
      }
    }
  }

  if(parentSection) {                    // I'm not the root node
    char toCat[8];
    strcpy(mySection, parentSection);    // build my section number
    if(*mySection) {
      sprintf(toCat, ".%d", childNum);
      strcat(mySection, toCat);
    } else {
      sprintf(toCat, "%d", childNum);
      strcat(mySection, toCat);
    }
    fprintf(fp, "<H2>%s %s</H2>\n", mySection, getTitle());
  } else {                              // I'm the root node
    strcpy(mySection, "");
    fprintf(fp, "<H1>%s</H1>\n", getTitle());
  }
  fprintf(fp,"\n\n");

  char buf[strlen(getText())*2];      

  strcpy(buf, getText());

  myReplace(buf, "<", "&#60;");
  myReplace(buf, ">", "&#62;");
  myReplace(buf, "\n", "<BR>\n");

  makeItNice(buf, 75);

  fprintf(fp, "%s\n", buf);       // end of word wrap, do the output
  if(buf[strlen(buf)-1] != '\n')
    fprintf(fp, "\n");
  
  for(unsigned int i=0; i<children.getSize(); i++) {  
    children[i]->exportHTML(fp, mySection); // and now the subsections
  }

}

// ----------------------------
// getNext()
// ----------------------------

HelpNode *HelpNode::getNext()
{
  HelpNode *hn;
  hn = this;

  if(hn->children.getSize())
    return hn->children[0];
  
  while(hn->parent) {
    for(unsigned int i=1; i<hn->parent->children.getSize(); i++) {
      if(hn->parent->children[i-1] == hn)
	return hn->parent->children[i];
    }
    hn = hn->parent;
  }
  return NULL;
}

// ----------------------------
// getLast()
// ----------------------------

HelpNode *HelpNode::getLast()
{
  HelpNode *hn;
  hn = this;

  if(hn->parent) {
    Boolean found = FALSE;
    for(unsigned int i=hn->parent->children.getSize()-2; (signed int)i>=0;i--)
      {
	if(hn->parent->children[i+1] == hn) {
	  hn =  hn->parent->children[i];
	  found = TRUE;
	  break;
	}
      }
    if(!found)                       // no prec -> parent
      return hn->parent;
    while(hn->children.getSize())    // if prec has children -> last child
      hn = hn->children[hn->children.getSize()-1];
    return hn;
  }
  return NULL;
}




