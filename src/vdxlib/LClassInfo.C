/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LClassInfo.C,v $
 *  $Date: 1999/08/27 15:33:20 $
 *  $Revision: 1.3.2.1 $
 *
 *  Copyright 1997 1998, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Muehlenpfordtstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: LClassInfo.C,v $
 * Revision 1.3.2.1  1999/08/27 15:33:20  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.3  1998/06/06 18:33:38  lazy
 * Drawer finished, fixing bugs in Imakefile
 *
 * Revision 1.2  1998/05/13 15:57:15  lazy
 * Xfe Integration complete
 *
 * Revision 1.1.1.1  1998/04/24 23:45:53  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:10:18  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1998/01/17  18:54:38  lazy
 * Initial revision
 *
 */

#include "LClassInfo.h"

#include <Xm/DialogS.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/BulletinB.h>
#include <Xm/ScrolledW.h>
#include <Xm/Text.h>
#include <Xm/ToggleB.h>
#include <Xm/DrawnB.h>
#include <Xm/List.h>
#include <Xm/FileSB.h>
#include <Xm/PanedW.h>
#include <Xm/ArrowB.h>
#include <Xm/CascadeB.h>
#include <Xm/Command.h>
#include <Xm/DrawingA.h>
#include <Xm/Frame.h>
#include <Xm/MainW.h>
#include <Xm/MessageB.h>
#include <Xm/Scale.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/SelectioB.h>
#include <Xm/Separator.h>
#include <Xm/TextF.h>

#ifdef USE_LWID
#include <lwid/ButtonBox.h>
#include <lwid/CellTable.h>
#include <lwid/Bubble.h>
#include <lwid/Drawer.h>
#endif

#if XmVERSION >= 2
#include <Xm/ComboBox.h>
#include <Xm/Notebook.h>
#include <Xm/Container.h>
#include <Xm/SpinB.h>
#if XmREVISION < 1
#include <Xm/CSText.h>
#else
#include <Xm/Print.h>
#endif
#endif



#ifdef CDE_WIDGETS
#ifndef USE_CDE
#define USE_CDE
#endif
#endif

#ifdef USE_CDE
#include <Dt/Dt.h>
#include <Dt/SpinBox.h>
#include <Dt/ComboBox.h>
#include <Dt/Editor.h>
#include <Dt/HelpDialog.h>
#include <Dt/HelpQuickD.h>
#include <Dt/MenuButton.h>
#include <Dt/Term.h>
#endif

#ifdef USE_XRT
#include <Xm/Xrt3d.h>
#include <Xm/XrtGraph.h>
#include <Xm/XrtTable.h>
#include <Xm/XrtField.h>
#include <Xm/XrtGearCombo.h>
#include <Xm/XrtComboBox.h>
#include <Xm/XrtAligner.h>
#include <Xm/XrtTabB.h>
#include <Xm/XrtTabM.h>
#include <Xm/XrtOutliner.h>
#include <Xm/XrtProgress.h>
#include <Xm/XrtPushB.h>
#include <Xm/XrtToggleB.h>
#include <Xm/XrtToolbar.h>
#endif

#ifdef USE_INT
#include <Xint/Axis.h>
#include <Xint/Box.h>
#include <Xint/ChartW.h>
#include <Xint/CompBase.h>
#include <Xint/EditObject.h>
#include <Xint/EditTable.h>
#include <Xint/Glue.h>
#include <Xint/ObjectEditor.h>
#include <Xint/Scroll.h>
#include <Xint/Surf3D.h>
#endif

#ifdef USE_BX
#include <BXm/TextTable.h>
#include <BXm/Regex.h>
#include <BXm/Center.h>
#include <BXm/TableMan.h>
#include <BXm/ScrollMan.h>
#endif

#ifdef USE_XFE
#include <Xfe/XfeAll.h>
#include <Xfe/Chrome.h>
#include <Xfe/FontChooser.h>
#endif

LClassInfo vdxClassInfo[] = {

  // Mozilla's Widgets, NPL http://www.mozilla.org

#ifdef USE_XFE
  
    { "Xfe", 
      xfeChromeWidgetClass, "xfeChromeWidgetClass", NULL, NULL, 
      "Xfe/Chrome.h", "XfeChrome.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    { "Xfe", 
      xfeBmButtonWidgetClass, "xfeBmButtonWidgetClass", NULL, NULL, 
      "Xfe/BmButton.h", "XfeBmButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeButtonWidgetClass, "xfeButtonWidgetClass", NULL, NULL, 
      "Xfe/Button.h", "XfeButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeDashBoardWidgetClass, "xfeDashBoardWidgetClass", NULL, NULL, 
      "Xfe/DashBoard.h", "XfeDashBoard.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      TRUE },

    //    { "Xfe", 
    //      xfeComboBoxWidgetClass, "xfeComboBoxWidgetClass", NULL, NULL, 
    //  "Xfe/ComboBox.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    //  TRUE },

    { "Xfe", 
      xfeProgressBarWidgetClass, "xfeProgressBarWidgetClass", NULL, NULL, 
      "Xfe/ProgressBar.h", "XfeProgressBar.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfePaneWidgetClass, "xfePaneWidgetClass", NULL, NULL, 
      "Xfe/Pane.h", "XfePane.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeArrowWidgetClass, "xfeArrowWidgetClass", NULL, NULL, 
      "Xfe/Arrow.h", "XfeArrow.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeCascadeWidgetClass, "xfeCascadeWidgetClass", NULL, NULL, 
      "Xfe/Cascade.h", "XfeCascade.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeBmCascadeWidgetClass, "xfeBmCascadeWidgetClass", NULL, NULL, 
      "Xfe/BmCascade.h", "XfeBmCascade.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    //    { "Xfe", 
    //      xfeFancyBoxWidgetClass, "xfeFancyBoxWidgetClass", NULL, NULL, 
    //      "Xfe/FancyBox.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    //      TRUE },

    //{ "Xfe", 
    //  xfeFontChooserWidgetClass, "xfeFontChooserWidgetClass", NULL, NULL, 
    //  "Xfe/FontChooser.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    //  TRUE },

    { "Xfe", 
      xfeLabelWidgetClass, "xfeLabelWidgetClass", NULL, NULL, 
      "Xfe/Label.h", "XfeLabel.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeLogoWidgetClass, "xfeLogoWidgetClass", NULL, NULL, 
      "Xfe/Logo.h", "XfeLogo.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeTabWidgetClass, "xfeTabWidgetClass", NULL, NULL, 
      "Xfe/Tab.h", "XfeTab.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    { "Xfe", 
      xfeTaskBarWidgetClass, "xfeTaskBarWidgetClass", NULL, NULL, 
      "Xfe/TaskBar.h", "XfeTaskBar.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    { "Xfe", 
      xfeToolBarWidgetClass, "xfeToolBarWidgetClass", NULL, NULL, 
      "Xfe/ToolBar.h", "XfeToolBar.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    { "Xfe", 
      xfeToolBoxWidgetClass, "xfeToolBoxWidgetClass", NULL, NULL, 
      "Xfe/ToolBox.h", "XfeToolBox.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      TRUE },

    { "Xfe", 
      xfeToolItemWidgetClass, "xfeToolItemWidgetClass", NULL, NULL, 
      "Xfe/ToolItem.h", "XfeToolItem.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    //    { "Xfe", 
    //  xfeToolScrollWidgetClass, "xfeToolScrollWidgetClass", NULL, NULL, 
    //  "Xfe/ToolScroll.h", "XfeToolScroll.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    //  FALSE },

#endif

  // BXwidgets

#ifdef USE_BX

    { "BXwidgets", 
      bxmTextTableWidgetClass, "bxmTextTableWidgetClass", NULL, NULL, 
      "BXm/TextTable.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },
  
    { "BXwidgets", 
      bxmRegexWidgetClass, "bxmRegexWidgetClass", NULL, NULL, 
      "BXm/Regex.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "BXwidgets", 
      bxmCenterWidgetClass, "bxmCenterWidgetClass", NULL, NULL, 
      "BXm/Center.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },
  
    { "BXwidgets", 
      bxmTableManagerWidgetClass, "bxmTableManagerWidgetClass", NULL, NULL, 
      "BXm/TableMan.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },
  
    { "BXwidgets", 
      bxmScrollManagerWidgetClass, "bxmScrollManagerWidgetClass", NULL, NULL, 
      "BXm/ScrollMan.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

#endif

  // INT WIDGET CLASSES

#ifdef USE_INT

    { "INT", 
      xintAxisWidgetClass, "xintAxisWidgetClass", NULL, NULL, 
      "Xint/Axis.h", "IntAxis.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintChartWidgetClass, "xintChartWidgetClass", NULL, NULL, 
      "Xint/ChartW.h", "IntChart.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintCompBaseWidgetClass, "xintCompBaseWidgetClass", NULL, NULL, 
      "Xint/CompBase.h", "IntCompBase.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintEditObjectWidgetClass, "xintEditObjectWidgetClass", NULL, NULL, 
      "Xint/EditObject.h", "IntEditObject.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintEditTableWidgetClass, "xintEditTableWidgetClass", NULL, NULL, 
      "Xint/EditTable.h", "IntEditTable.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintGlueWidgetClass, "xintGlueWidgetClass", NULL, NULL, 
      "Xint/Glue.h", "IntGlue.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintObjectEditorWidgetClass, "xintObjectEditorWidgetClass", NULL, NULL, 
      "Xint/ObjectEditor.h", "IntObjectEditor.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },

    { "INT", 
      xintScrollWidgetClass, "xintScrollWidgetClass", NULL, NULL, 
      "Xint/Scroll.h", "IntScroll.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },
#if(0)
    { "INT", 
      xintSurf3DWidgetClass, "xintSurf3DWidgetClass", NULL, NULL, 
      "Xint/Surf3D.h", "IntSurf3D.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      TRUE },
#endif
#endif

  // XRT WIDGET CLASSES


#ifdef USE_XRT


  // Xrt Gear Classes

    { "Xrt Gear", 
      xmXrtAlignerWidgetClass, "xmXrtAlignerWidgetClass", NULL, NULL, 
      "Xm/XrtAligner.h", "XrtAligner.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      TRUE },

    // BUGGY
    //    { "Xrt Gear", 
    //      xmXrtGearComboWidgetClass, "xmXrtGearComboWidgetClass", NULL, NULL, 
    //      "Xm/XrtGearCombo.h", "XrtGearCombo.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    //      FALSE },

    { "Xrt Gear", 
      xmXrtTabButtonWidgetClass, "xmXrtTabButtonWidgetClass", NULL, NULL, 
      "Xm/XrtTabB.h", "XrtTabButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Gear", 
      xmXrtTabManagerWidgetClass, "xmXrtTabManagerWidgetClass", NULL, NULL, 
      "Xm/XrtTabM.h", "XrtTabManager.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Gear", 
      xmXrtOutlinerWidgetClass, "xmXrtOutlinerWidgetClass", NULL, NULL, 
      "Xm/XrtOutliner.h", "XrtOutliner.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Gear", 
      xmXrtProgressWidgetClass, "xmXrtProgressWidgetClass", NULL, NULL, 
      "Xm/XrtProgress.h", "XrtProgress.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Gear", 
      xmXrtPushButtonWidgetClass, "xmXrtPushButtonWidgetClass", NULL, NULL, 
      "Xm/XrtPushB.h", "XrtPushButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Gear", 
      xmXrtToggleButtonWidgetClass, "xmXrtToggleButtonWidgetClass", NULL, NULL, 
      "Xm/XrtToggleB.h", "XrtToggleButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Gear", 
      xmXrtToolbarWidgetClass, "xmXrtToolbarWidgetClass", NULL, NULL, 
      "Xm/XrtToolbar.h", "XrtToolbar.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    // Table Widget Class

    { "Xrt", 
      xtXrtTableWidgetClass, "xtXrtTableWidgetClass", NULL, NULL, 
      "Xm/XrtTable.h", "XrtTable.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
      FALSE },

    // Field Widget Class

    { "Xrt Field", 
      xmXrtSpinBoxWidgetClass, "xmXrtSpinBoxWidgetClass", NULL, NULL, 
      "Xm/XrtSpinBox.h", "XrtSpinBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

    { "Xrt Field", 
      xmXrtComboBoxWidgetClass, "xmXrtComboBoxWidgetClass", NULL, NULL, 
      "Xm/XrtComboBox.h", "XrtCombo.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
      FALSE },

   { "Xrt Field", 
     xmXrtFieldWidgetClass, "xmXrtFieldWidgetClass", NULL, NULL, 
     "Xm/XrtField.h", "XrtField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
     FALSE },

   { "Xrt Field", 
     xmXrtStringFieldWidgetClass, "xmXrtStringFieldWidgetClass", NULL, NULL, 
     "Xm/XrtField.h", "XrtStringField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
     FALSE },

   { "Xrt Field", 
     xmXrtDateFieldWidgetClass, "xmXrtDateFieldWidgetClass", NULL, NULL, 
     "Xm/XrtField.h", "XrtDateField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
     FALSE },

   { "Xrt Field", 
     xmXrtIntFieldWidgetClass, "xmXrtIntFieldWidgetClass", NULL, NULL, 
     "Xm/XrtField.h", "XrtIntField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
     FALSE },

   { "Xrt Field", 
     xmXrtFloatFieldWidgetClass, "xmXrtFloatFieldWidgetClass", NULL, NULL, 
     "Xm/XrtField.h", "XrtFloatField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
     FALSE },

   { "Xrt Field", 
     xmXrtCurrencyFieldWidgetClass, "xmXrtCurrencyFieldWidgetClass", NULL, NULL, 
     "Xm/XrtField.h", "XrtCurrencyField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
     FALSE },

  { "Xrt", 
    xtXrt3dWidgetClass, "xtXrt3dWidgetClass", NULL, NULL, 
    "Xm/Xrt3d.h", "Xrt3d.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xrt", 
    xtXrtGraphWidgetClass, "xtXrtGraphWidgetClass", NULL, NULL, 
    "Xm/XrtGraph.h", "XrtGraph.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },
#endif




    // MOTIF AND XT




  { "Shells", 
    applicationShellWidgetClass, "applicationShellWidgetClass", NULL, NULL, 
    "X11/Shell.h", "ApplicationShell.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Shells", 
    topLevelShellWidgetClass, "topLevelShellWidgetClass", NULL, NULL, 
    "X11/Shell.h", "TopLevelShell.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  //  { "Shells", 
  // overrideShellWidgetClass, "overrideShellWidgetClass", NULL, NULL, 
  //    "X11/Shell.h", "OverrideShell.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
  //    TRUE },

  { "Shells", 
    transientShellWidgetClass, "transientShellWidgetClass", NULL, NULL, 
    "X11/Shell.h", "TransientShell.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Shells", 
    xmDialogShellWidgetClass, "xmDialogShellWidgetClass", NULL, NULL, 
    "Xm/DialogS.h", "DialogShell.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm Container", 
    xmBulletinBoardWidgetClass, "xmBulletinBoardWidgetClass", NULL, NULL, 
    "Xm/BulletinB.h", "BulletinBoard.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmPushButtonWidgetClass, "xmPushButtonWidgetClass", NULL, NULL, 
    "Xm/PushB.h", "PushButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmLabelWidgetClass, "xmLabelWidgetClass", NULL, NULL, 
    "Xm/Label.h", "Label.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Container", 
    xmFormWidgetClass, "xmFormWidgetClass", NULL, NULL, 
    "Xm/Form.h", "Form.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Container", 
    xmRowColumnWidgetClass, "xmRowColumnWidgetClass", NULL, NULL, 
    "Xm/RowColumn.h", "RowColumn.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmToggleButtonWidgetClass, "xmToggleButtonWidgetClass", NULL, NULL, 
    "Xm/ToggleB.h", "ToggleButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmDrawnButtonWidgetClass, "xmDrawnButtonWidgetClass", NULL, NULL, 
    "Xm/DrawnB.h", "DrawnButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmFileSelectionBoxWidgetClass,"xmFileSelectionBoxWidgetClass", NULL, NULL, 
    "Xm/FileSB.h", "FileSelectionBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmListWidgetClass, "xmListWidgetClass", NULL, NULL, 
    "Xm/List.h", "List.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmTextWidgetClass, "xmTextWidgetClass", NULL, NULL, 
    "Xm/Text.h", "Text.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmArrowButtonWidgetClass, "xmArrowButtonWidgetClass", NULL, NULL, 
    "Xm/ArrowB.h", "ArrowButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmCascadeButtonWidgetClass, "xmCascadeButtonWidgetClass", NULL, NULL, 
    "Xm/CascadeB.h", "CascadeButton.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmCommandWidgetClass, "xmCommandWidgetClass", NULL, NULL, 
    "Xm/Command.h", "Command.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Container", 
    xmDrawingAreaWidgetClass, "xmDrawingAreaWidgetClass", NULL, NULL, 
    "Xm/DrawingA.h", "DrawingArea.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Container", 
    xmFrameWidgetClass, "xmFrameWidgetClass", NULL, NULL, 
    "Xm/Frame.h", "Frame.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Container", 
    xmMainWindowWidgetClass, "xmMainWindowWidgetClass", NULL, NULL, 
    "Xm/MainW.h", "MainWindow.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmMessageBoxWidgetClass, "xmMessageBoxWidgetClass", NULL, NULL, 
    "Xm/MessageB.h", "MessageBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Container", 
    xmPanedWindowWidgetClass, "xmPanedWindowWidgetClass", NULL, NULL, 
    "Xm/PanedW.h", "PanedWindow.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmScaleWidgetClass, "xmScaleWidgetClass", NULL, NULL, 
    "Xm/Scale.h", "Scale.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmScrollBarWidgetClass, "xmScrollBarWidgetClass", NULL, NULL, 
    "Xm/ScrollBar.h", "ScrollBar.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Container", 
    xmScrolledWindowWidgetClass, "xmScrolledWindowWidgetClass", NULL, NULL, 
    "Xm/ScrolledW.h", "ScrolledWindow.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmSelectionBoxWidgetClass, "xmSelectionBoxWidgetClass", NULL, NULL, 
    "Xm/SelectioB.h", "SelectionBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    xmSeparatorWidgetClass, "xmSeparatorWidgetClass", NULL, NULL, 
    "Xm/Separator.h", "Separator.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Display",
    xmTextFieldWidgetClass, "xmTextFieldWidgetClass", NULL, NULL, 
    "Xm/TextF.h", "TextField.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Menu",
    NULL, NULL, XmCreateOptionMenu, "XmCreateOptionMenu", 
    "Xm/RowColumn.h", "OptionMenu.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    FALSE },

  { "Xm Menu",
    NULL, NULL, XmCreateMenuBar, "XmCreateMenuBar", 
    "Xm/RowColumn.h", "MenuBar.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    FALSE },

  { "Xm Menu",
    NULL, NULL, XmCreatePulldownMenu, "XmCreatePulldownMenu", 
    "Xm/RowColumn.h", "PulldownMenu.xpm", NEVER_MANAGE, ON_CHILD_UPDATE,
    FALSE },

  { "Xm Menu",
    NULL, NULL, XmCreatePopupMenu, "XmCreatePopupMenu", 
    "Xm/RowColumn.h", "PopupMenu.xpm", NEVER_MANAGE, ON_CHILD_UPDATE,
    FALSE },

  { "Xm Container",
    NULL, NULL, XmCreateRadioBox, "XmCreateRadioBox", 
    "Xm/RowColumn.h", "RadioBox.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateFormDialog, "XmCreateFormDialog", 
    "Xm/Form.h", "FormDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateFileSelectionDialog, "XmCreateFileSelectionDialog", 
    "Xm/FileSB.h", "FileSelectionBoxDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    NULL, NULL, XmCreateScrolledText, "XmCreateScrolledText",
    "Xm/Text.h", "ScrolledText.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Display",
    NULL, NULL, XmCreateScrolledList, "XmCreateScrolledList",
    "Xm/List.h", "ScrolledList.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateBulletinBoardDialog, "XmCreateBulletinBoardDialog",
    "Xm/BulletinB.h", "BulletinBoardDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateCommandDialog, "XmCreateCommandDialog",
    "Xm/Command.h", "CommandDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateMessageDialog, "XmCreateMessageDialog",
    "Xm/MessageB.h", "MessageDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateErrorDialog, "XmCreateErrorDialog",
    "Xm/MessageB.h", "ErrorDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateInformationDialog, "XmCreateInformationDialog",
    "Xm/MessageB.h", "InformationDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateQuestionDialog, "XmCreateQuestionDialog",
    "Xm/MessageB.h", "QuestionDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateWarningDialog, "XmCreateWarningDialog",
    "Xm/MessageB.h", "WarningDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateWorkingDialog, "XmCreateWorkingDialog",
    "Xm/MessageB.h", "WorkingDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateTemplateDialog, "XmCreateTemplateDialog",
    "Xm/MessageB.h", "TemplateDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreateSelectionDialog, "XmCreateSelectionDialog",
    "Xm/SelectioB.h", "SelectionDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm Dialogs", 
    NULL, NULL, XmCreatePromptDialog, "XmCreatePromptDialog",
    "Xm/SelectioB.h", "PromptDialog.xpm", DIALOG_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },



    // MOTIF 2.x



#if XmVERSION >= 2
  { "Xm 2.x", xmComboBoxWidgetClass, "xmComboBoxWidgetClass", NULL, NULL,
    "Xm/ComboBox.h", "ComboBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm 2.x", xmSpinBoxWidgetClass, "xmSpinBoxWidgetClass", NULL, NULL,
    "Xm/SpinB.h", "SpinBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Xm 2.x", xmNotebookWidgetClass, "xmNotebookWidgetClass", NULL, NULL,
    "Xm/Notebook.h", "Notebook.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Xm 2.x", xmContainerWidgetClass, "xmContainerWidgetClass", NULL, NULL,
    "Xm/Container.h", "Container.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

#if XmREVISION < 1

  { "Xm 2.x", xmCSTextWidgetClass, "xmCSTextWidgetClass", NULL, NULL,
    "Xm/CSText.h", "CSText.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Xm 2.x", NULL, NULL, XmCreateScrolledCSText, "XmCreateScrolledCSText",
    "Xm/CSText.h", "ScrolledCSText.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },
#else

/*
    // Motif 2.1
  { "Xm 2.x", xmPrintShellWidgetClass, "xmPrintShellWidgetClass", NULL, NULL,
    "Xm/Print.h", "PrintShell.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },
*/
    

#endif

#endif




    // VDX WIDGET CLASSES



#ifdef USE_LWID
  { "Lwid", xlButtonBoxWidgetClass, "xlButtonBoxWidgetClass", NULL, NULL,
    "lwid/ButtonBox.h", "XlButtonBox.xpm", NORMAL_MANAGE, ON_CHILD_UPDATE,
    TRUE },

  { "Lwid", xlCellTableWidgetClass, "xlCellTableWidgetClass", NULL, NULL,
    "lwid/CellTable.h", "XlCellTable.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "Lwid", xlBubbleWidgetClass, "xlBubbleWidgetClass", NULL, NULL,
    "lwid/Bubble.h", "XlBubble.xpm", NEVER_MANAGE, NO_ON_CHILD_UPDATE,
    FALSE },

  { "Lwid", xlDrawerWidgetClass, "xlDrawerWidgetClass", NULL, NULL,
    "lwid/Drawer.h", "XlDrawer.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

#endif



    // CDE WIDGET CLASSES



#ifdef USE_CDE
  { "CDE", dtSpinBoxWidgetClass, "dtSpinBoxWidgetClass", NULL, NULL,
    "Dt/SpinBox.h", "SpinBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "CDE", dtComboBoxWidgetClass, "dtComboBoxWidgetClass", NULL, NULL,
    "Dt/ComboBox.h", "ComboBox.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "CDE", dtTermWidgetClass, "dtTermWidgetClass", NULL, NULL,
    "Dt/Term.h", "DtTerm.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "CDE", dtHelpDialogWidgetClass, "dtHelpDialogWidgetClass", NULL, NULL,
    "Dt/HelpDialog.h", "DtHelp.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  { "CDE", dtHelpQuickDialogWidgetClass, "dtHelpQuickDialogWidgetClass", NULL, NULL,
    "Dt/HelpQuickD.h", "DtHelp.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
    TRUE },

  // Buggy
  //  { "CDE", dtEditorWidgetClass, "dtEditorWidgetClass", NULL, NULL,
  //    "Dt/Editor.h", "Container.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
  //    TRUE },

  // Buggy
  //  { "CDE", dtMenuButtonWidgetClass, "dtMenuButtonWidgetClass", NULL, NULL,
  //    "Dt/MenuButton.h", "Container.xpm", NORMAL_MANAGE, NO_ON_CHILD_UPDATE,
  //    TRUE },

#endif

  { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NORMAL_MANAGE, ON_CHILD_UPDATE, TRUE }
};




LClassInfo *
getVdxClassInfo()
{
  return vdxClassInfo;
}
