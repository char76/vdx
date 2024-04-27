/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: lic_gen.C,v $
 *  $Date: 1999/08/27 15:32:34 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: lic_gen.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:34  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:57  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25 22:56:12  lazy
 * Initial revision
 *
 */

#include "Lproject.h"
#include "Ltmpl.h"
#include <lac/RefArray.h>
#include <parse.h>
#include "misc.h"
#include "lic.h"
#include <lac/MsgCat.h>

#define VDX_GEN_NAME "vdxgen.bin"

extern char *fallback_resources;

// ---------------------------
// generate()
// ---------------------------
void
generate(char *gen_model, char *interface_file, char *dest_file)
{
  YResult *result;
  char *argv[1];
  int argc = 1;
  argv[0] = VDX_GEN_NAME;

  result = parse(interface_file);
  if(result && result->root_widget) {
    RefArray<Lfile> files;

    Widget topLevel;
    topLevel = LicView::init("Vdxgen", argc, argv, fallback_resources); 
    msgCat = new MsgCat(XtDisplay(LicView::getTopLevel()));
    app = new LApp(argc, argv);           

    Linterface *linterface = new Linterface(result->root_widget);
    linterface->generate(gen_model, False, files);
    for(unsigned int i=0; i<files.getSize(); i++) {
      char name[PATH_MAX];
      strcpy(name, files[i]->getFilename());
      getBasename(name);
      if(!strcmp(dest_file, name)) {
	files[i]->write();
	exit(0);
      }
    }
    fprintf(stderr, "File %s not generated\n", dest_file);
    exit(1);
  } else {
    fprintf(stderr, "Can't open %s\n", interface_file);
    exit(1);
  }
}


// ---------------------------
// checkForGenerateMode()
// ---------------------------

void
checkForGenerateMode(int argc, char **argv)
{
  char name[PATH_MAX];
  
  strcpy(name, argv[0]);
  getBasename(name);

  if(!strcmp(name, VDX_GEN_NAME)) {
    if(argc != 4) {
      printf("Usage: %s gen_model interface_file destination_file\n", 
	     VDX_GEN_NAME);
      exit(1);
    }
    generate(argv[1], argv[2], argv[3]);
  }
}


