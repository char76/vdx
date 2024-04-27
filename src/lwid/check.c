/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
#include <Xm/Xm.h>
#include "ButtonBox.h"
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/BulletinB.h>
#include <Xm/Text.h>
#include <Xm/Form.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <X11/CompositeP.h>
#include <sys/timeb.h>
#include "CellTable.h"
#include "Bubble.h"
#include "Drawer.h"

Widget appShell, rc, box, b, t, bubbleParent;


void main(Cardinal argc, char **argv)
{
  XtAppContext context;
  struct timeb begin, end;

  appShell = XtAppInitialize(&context, "Check", NULL, 0, &argc, argv,
			     NULL, NULL, 0);
  XtVaSetValues(appShell, XmNallowShellResize, TRUE, NULL);

  rc = XtCreateWidget("test", xmFormWidgetClass, 
			      appShell, NULL, 0);
  time(&begin);
  t = XtVaCreateManagedWidget("Table", xlCellTableWidgetClass, rc, 
			      XmNleftAttachment, XmATTACH_FORM,
			      XmNrightAttachment, XmATTACH_FORM,
			      XmNtopAttachment, XmATTACH_FORM,
			      XmNbottomAttachment, XmATTACH_WIDGET,
			      XmNresizeRow, 1,
			      XmNresizeColumn, 1,
			      XmNwidth, 400,
			      XmNheight, 500,
			      NULL);
  XtVaCreateManagedWidget("Button", xmPushButtonWidgetClass, t,
			XmNcellRow, 2,
			XmNcellColumn, 2,
			NULL);
  XtVaCreateManagedWidget("Button2", xmPushButtonWidgetClass, t,
			XmNcellRow, 1,
			XmNcellColumn, 2,
			NULL);
  bubbleParent = XtVaCreateManagedWidget("BubbleParent", 
					 xmPushButtonWidgetClass, t,
					 XmNcellRow, 2,
					 XmNcellColumn, 1,
					 XmNhorizontalAlignment, 
					 XmCELL_ALIGNMENT_CENTER,
					 NULL);
  XtVaCreateWidget("bubble", xlBubbleWidgetClass, bubbleParent, 
		   NULL);

  box = XtVaCreateManagedWidget("Drawer", xlDrawerWidgetClass, t,
				XmNcellRow, 1,
				XmNcellColumn, 0,
				NULL);
  XtVaCreateManagedWidget("Text", xmTextWidgetClass, box,
			  NULL);

  XtVaCreateManagedWidget("Text", xmTextWidgetClass, t,
			  XmNcellRow, 1,
			  XmNcellColumn, 1,
			  NULL);
  XtVaCreateManagedWidget("Text", xmTextWidgetClass, t,
			  XmNcellRow, 0,
			  XmNcellColumn, 0,
			  XmNresizeHeight, TRUE,
			  XmNresizeWidth, TRUE,
			  XmNeditMode, XmMULTI_LINE_EDIT,
			  NULL);
  XtVaCreateManagedWidget("Button2", xmPushButtonWidgetClass, t,
			  XmNcellRow, 0,
			  XmNcellColumn, 1,
			  XmNhorizontalAlignment, XmCELL_ALIGNMENT_BEGINNING,
			  NULL);
  XtVaCreateManagedWidget("Text", xmTextWidgetClass, t,
			  XmNcellRow, 3,
			  XmNcellColumn, 0,
			  NULL);
  XtVaCreateManagedWidget("Button2", xmPushButtonWidgetClass, t,
			  XmNcellRow, 3,
			  XmNcellColumn, 1,
			  XmNhorizontalAlignment, XmCELL_ALIGNMENT_BEGINNING,
			  NULL);
  XtVaCreateManagedWidget("Text", xmTextWidgetClass, t,
			  XmNcellRow, 4,
			  XmNcellColumn, 0,
			  NULL);
  XtVaCreateManagedWidget("Button2", xmPushButtonWidgetClass, t,
			  XmNcellRow, 4,
			  XmNcellColumn, 0,
			  XmNhorizontalAlignment, XmCELL_ALIGNMENT_BEGINNING,
			  NULL);

  box = XtVaCreateWidget("box", xlButtonBoxWidgetClass, rc, 
			 XmNleftAttachment, XmATTACH_FORM,
			 XmNrightAttachment, XmATTACH_FORM,
			 XmNbottomAttachment, XmATTACH_FORM,
			 NULL);
  XtCreateManagedWidget("Ok", xmPushButtonWidgetClass, box, NULL, 0);
  XtCreateManagedWidget("Apply", xmPushButtonWidgetClass, box, NULL, 0);
  XtCreateManagedWidget("Cancel", xmPushButtonWidgetClass, box, NULL, 0);
  XtCreateManagedWidget("Help", xmPushButtonWidgetClass, box, NULL, 0);

  XtManageChild(box);

  XtVaSetValues(t,
		XmNbottomWidget, box,
		NULL);

  XtManageChild(rc);

  XtRealizeWidget(appShell);

  ftime(&end);
  printf("time difference: %hu\n", (((end.time-begin.time)*1000)+end.millitm)-begin.millitm);

  printf("enabled: %d\n", XlBubbleIsEnabled());
  XlBubbleSetEnabled(FALSE);
  printf("enabled: %d\n", XlBubbleIsEnabled());
  XlBubbleSetEnabled(TRUE);
  printf("enabled: %d\n", XlBubbleIsEnabled());

  XtAppMainLoop(context);
}


