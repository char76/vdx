/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -----------------------------------------------------
// MainWindow_base.h
// 
// This file was automaticly generated by
// View Designer/X  v1.2
//
// User: lazy@apfel
// Date: Tue Jun  2 17:02:45 1998
//
// Don't edit this file, please !
// -----------------------------------------------------

#ifndef _MainWindow_base_H_
#define _MainWindow_base_H_

#include <X11/Intrinsic.h>
#include <lac/LicView.h>



// -----------------------------------------------------
// Class definition 
// class MainWindow_base is a derived class of LicView
// -----------------------------------------------------

class MainWindow_base : public LicView {
private:
  void createWidgets();
  void addRelations();
  void addCallbacks();

protected:
  Widget MainWindow;
  Widget XmForm_1;       /* XmForm */
  Widget MenuBar;       /* XmCreateMenuBar */
  Widget File;       /* XmCascadeButton */
  Widget FileMenu;       /* XmCreatePulldownMenu */
  Widget ProjectNew;       /* XmPushButton */
  Widget FileOpen;       /* XmPushButton */
  Widget FileSave;       /* XmPushButton */
  Widget FileSaveAs;       /* XmPushButton */
  Widget separator;       /* XmSeparator */
  Widget newTemplates;       /* XmPushButton */
  Widget openTemplates;       /* XmPushButton */
  Widget separator_2;       /* XmSeparator */
  Widget FileExit;       /* XmPushButton */
  Widget Project;       /* XmCascadeButton */
  Widget ProjectMenu;       /* XmCreatePulldownMenu */
  Widget ProjectSettings;       /* XmPushButton */
  Widget ProjectLoadInterface;       /* XmPushButton */
  Widget ProjectShowHelp;       /* XmPushButton */
  Widget ProjectResources;       /* XmPushButton */
  Widget ProjectGenerate;       /* XmPushButton */
  Widget ProjectExecute;       /* XmPushButton */
  Widget Widgets;       /* XmCascadeButton */
  Widget WidgetsMenu;       /* XmCreatePulldownMenu */
  Widget WidgetsPalette;       /* XmPushButton */
  Widget XmSeparator;       /* XmSeparator */
  Widget ShellMenuButton;       /* XmCascadeButton */
  Widget ShellMenu;       /* XmCreatePulldownMenu */
  Widget ManagerMenuButton;       /* XmCascadeButton */
  Widget ManagerMenu;       /* XmCreatePulldownMenu */
  Widget PrimitivesMenuButton;       /* XmCascadeButton */
  Widget PrimitivesMenu;       /* XmCreatePulldownMenu */
  Widget DialogsMenuButton;       /* XmCascadeButton */
  Widget DialogsMenu;       /* XmCreatePulldownMenu */
  Widget Options;       /* XmCascadeButton */
  Widget OptionsMenu;       /* XmCreatePulldownMenu */
  Widget genericOptionButton;       /* XmPushButton */
  Widget OptionsGrid;       /* XmPushButton */
  Widget UpdatePolicy;       /* XmCascadeButton */
  Widget UpdatePolicyMenu;       /* XmCreatePulldownMenu */
  Widget minimalRefreshButton;       /* XmToggleButton */
  Widget optimalRefreshButton;       /* XmToggleButton */
  Widget defaultShellButton;       /* XmCascadeButton */
  Widget defaultShellMenu;       /* XmCreatePulldownMenu */
  Widget applicationShellButton;       /* XmToggleButton */
  Widget toplevelShellButton;       /* XmToggleButton */
  Widget transientShellButton;       /* XmToggleButton */
  Widget dialogShellButton;       /* XmToggleButton */
  Widget viewDefaultsButton;       /* XmPushButton */
  Widget defaultPublicButton;       /* XmPushButton */
  Widget helpButton;       /* XmCascadeButton */
  Widget HelpMenu;       /* XmCreatePulldownMenu */
  Widget HelpForHelp;       /* XmPushButton */
  Widget HelpOnContext;       /* XmPushButton */
  Widget HelpTutorial;       /* XmPushButton */
  Widget XmSeparator_1;       /* XmSeparator */
  Widget HelpProduct;       /* XmPushButton */
  Widget OpenIcon;       /* XmDrawnButton */
  Widget SaveIcon;       /* XmDrawnButton */
  Widget PaletteIcon;       /* XmDrawnButton */
  Widget ProductIcon;       /* XmDrawnButton */
  Widget seperateBelowToolBar;       /* XmSeparator */
  Widget WidgetPaletteIcon;       /* XmDrawnButton */
  Widget XmPanedWindow_1;       /* XmPanedWindow */
  Widget ViewForm;       /* XmForm */
  Widget ViewLabel;       /* XmLabel */
  Widget MessageForm;       /* XmForm */
  Widget MessageLabel;       /* XmLabel */
  Widget XmScrolledWindow_1;       /* XmScrolledWindow */
  Widget XmText_1;       /* XmText */
  Widget MessageClearButton;       /* XmPushButton */
  Widget quickHelp;       /* XmLabel */
  Widget TestModeToggle;       /* XmToggleButton */
  Widget ProductInfoDialog;       /* XmCreateFormDialog */
  Widget PIClose;       /* XmPushButton */
  Widget ProductInfoLabel;       /* XmLabel */
  Widget label_2;       /* XmLabel */
  Widget ProjectNewDialog;       /* XmCreateFormDialog */
  Widget ProjectNewLabel;       /* XmLabel */
  Widget ProjectNewText;       /* XmText */
  Widget ProjectNewOk;       /* XmPushButton */
  Widget ProjectNewCancel;       /* XmPushButton */
  Widget ProjectNewHelp;       /* XmPushButton */
  Widget ProjectNewSeparator;       /* XmSeparator */
  Widget ProjectSettingsDialog;       /* XmCreateFormDialog */
  Widget PSNameLabel;       /* XmLabel */
  Widget PSNameText;       /* XmText */
  Widget PSPaletteLabel;       /* XmLabel */
  Widget PSPaletteText;       /* XmText */
  Widget PSLangMenu;       /* XmCreatePulldownMenu */
  Widget PSLangOptionMenu;       /* XmCreateOptionMenu */
  Widget XmSeparator_4;       /* XmSeparator */
  Widget PSStartLabel;       /* XmLabel */
  Widget PCStartText;       /* XmText */
  Widget PSOk;       /* XmPushButton */
  Widget PSCancel;       /* XmPushButton */
  Widget PSHelp;       /* XmPushButton */
  Widget PSSourceDirLabel;       /* XmLabel */
  Widget PSSourceDirText;       /* XmText */
  Widget PSPaletteFiles;       /* XmDrawnButton */
  Widget PSSourceDirFiles;       /* XmDrawnButton */
  Widget PSPaletteFileSB;       /* XmCreateFileSelectionDialog */
  Widget PSSourceDirFileSB;       /* XmCreateFileSelectionDialog */
  Widget GridDialog;       /* XmCreateFormDialog */
  Widget GridOk;       /* XmPushButton */
  Widget GridCancel;       /* XmPushButton */
  Widget GridHelp;       /* XmPushButton */
  Widget GridSeparator;       /* XmSeparator */
  Widget GridRadioBox;       /* XmCreateRadioBox */
  Widget GridModeOn;       /* XmToggleButton */
  Widget GridModeOff;       /* XmToggleButton */
  Widget GridValueLabel;       /* XmLabel */
  Widget GridValue;       /* XmScale */
  Widget saveProjectDialog;       /* XmCreateFileSelectionDialog */
  Widget loadProjectDialog;       /* XmCreateFileSelectionDialog */
  Widget loadInterfaceDialog;       /* XmCreateFileSelectionDialog */
  Widget overwriteDialog;       /* XmCreateFormDialog */
  Widget owOk;       /* XmPushButton */
  Widget owCancel;       /* XmPushButton */
  Widget owHelp;       /* XmPushButton */
  Widget scrolledWindow_1;       /* XmScrolledWindow */
  Widget overwriteFilesList;       /* XmList */
  Widget ExecIcon;       /* XmDrawnButton */
  Widget openTemplatesDialog;       /* XmCreateFileSelectionDialog */
  Widget quickStartDialog;       /* XmCreateQuestionDialog */
  Widget xlCellTable_1;       /* XlCellTable */
  Widget qsOpenButton;       /* XmToggleButton */
  Widget qsNewButton;       /* XmToggleButton */
  Widget qsRecoverButton;       /* XmToggleButton */
  Widget qsOpenText;       /* XmText */
  Widget qsNewText;       /* XmText */
  Widget qsRecoverText;       /* XmText */
  Widget generateIcon;       /* XmDrawnButton */
  Widget viewDefaultsDialog;       /* XmCreateMessageDialog */
  Widget rowColumn_2;       /* XmRowColumn */
  Widget widBrowseViewFrame;       /* XmFrame */
  Widget label_3;       /* XmLabel */
  Widget rowColumn_3;       /* XmRowColumn */
  Widget browserSmallIconToggle;       /* XmToggleButton */
  Widget browserWithIconToggle;       /* XmToggleButton */
  Widget browserWithClassNameToggle;       /* XmToggleButton */
  Widget browserAutomaticLoadToggle;       /* XmToggleButton */
  Widget menuEditFrame;       /* XmFrame */
  Widget label_3_1;       /* XmLabel */
  Widget rowColumn_3_1;       /* XmRowColumn */
  Widget menuEditSmallIconToggle;       /* XmToggleButton */
  Widget menuEditWithIconToggle;       /* XmToggleButton */
  Widget menuEditWithClassNameToggle;       /* XmToggleButton */
  Widget menuEditAutomaticLoadToggle;       /* XmToggleButton */
  Widget attachmentEditorFrame;       /* XmFrame */
  Widget label_3_1_1;       /* XmLabel */
  Widget rowColumn_3_1_1;       /* XmRowColumn */
  Widget aeSmallIconToggle;       /* XmToggleButton */
  Widget aeWithIconToggle;       /* XmToggleButton */
  Widget aeWithClassNameToggle;       /* XmToggleButton */
  Widget aeAutomaticLoadToggle;       /* XmToggleButton */
  Widget resourceEditorFrame;       /* XmFrame */
  Widget label_3_2;       /* XmLabel */
  Widget rowColumn_3_2;       /* XmRowColumn */
  Widget editorAutomaticLoadToggle;       /* XmToggleButton */
  Widget defaultViewOptionMenu;       /* XmCreateOptionMenu */
  Widget defaultViewMenu;       /* XmCreatePulldownMenu */
  Widget coreView;       /* XmPushButton */
  Widget specificView;       /* XmPushButton */
  Widget constraintView;       /* XmPushButton */
  Widget callbackView;       /* XmPushButton */
  Widget extraView;       /* XmPushButton */
  Widget defaultPublicDialog;       /* XmCreateMessageDialog */
  Widget rowColumn_4;       /* XmRowColumn */
  Widget scrolledWindow_2;       /* XmScrolledWindow */
  Widget defaultPublicList;       /* XmList */
  Widget defaultPublicText;       /* XmText */
  Widget defaultPublicAdd;       /* XmPushButton */
  Widget defaultPublicDelete;       /* XmPushButton */
  Widget genericOptionsDialog;       /* XmCreateMessageDialog */
  Widget xlCellTable_2;       /* XlCellTable */
  Widget label_4;       /* XmLabel */
  Widget label_4_1;       /* XmLabel */
  Widget label_4_2;       /* XmLabel */
  Widget label_4_3;       /* XmLabel */
  Widget label_4_4;       /* XmLabel */
  Widget genericQuickStartToggle;       /* XmToggleButton */
  Widget genericAutoSaveToggle;       /* XmToggleButton */
  Widget genericAutoSaveScale;       /* XmScale */
  Widget genericAutoSaveText;       /* XmText */
  Widget genericMainTemplateText;       /* XmText */
  Widget label_4_4_1;       /* XmLabel */
  Widget quickHelpToggle;       /* XmToggleButton */
  Widget label_4_4_1_1;       /* XmLabel */
  Widget genericAfterLoadToggle;       /* XmToggleButton */
  Widget toolTipLabel;       /* XmLabel */
  Widget versionControlLabel;       /* XmLabel */
  Widget toolTipToggle;       /* XmToggleButton */
  Widget versionControlToggle;       /* XmToggleButton */
  Widget executeDialog;       /* XmCreateFormDialog */
  Widget executeCellTable;       /* XmForm */
  Widget executeRowColumn;       /* XmRowColumn */
  Widget xmkmfToggleButton;       /* XmToggleButton */
  Widget makeDependToggleButton;       /* XmToggleButton */
  Widget makeToggleButton;       /* XmToggleButton */
  Widget execToggleButton;       /* XmToggleButton */
  Widget StopIcon;       /* XmDrawnButton */
  Widget ProjectGenerateDialog;       /* XmCreateFormDialog */
  Widget rowColumn_1;       /* XmRowColumn */
  Widget ImakefileGenerateToggle;       /* XmToggleButton */
  Widget MainGenerateToggle;       /* XmToggleButton */
  Widget StubsGenerateToggle;       /* XmToggleButton */


  static void do_newTemplates_CB(Widget,XtPointer,XtPointer);
  static void do_projectSettings_CB(Widget,XtPointer,XtPointer);
  static void showHelp_CB(Widget,XtPointer,XtPointer);
  static void do_openGlobalResources_CB(Widget,XtPointer,XtPointer);
  static void showWidgetPalette_CB(Widget,XtPointer,XtPointer);
  static void quickHelpMenuMap_CB(Widget,XtPointer,XtPointer);
  static void updatePolicyChanged_CB(Widget,XtPointer,XtPointer);
  static void defaultShellChanged_CB(Widget,XtPointer,XtPointer);
  static void DoHelpForHelp_CB(Widget,XtPointer,XtPointer);
  static void DoContextHelp_CB(Widget,XtPointer,XtPointer);
  static void testModeChanged_CB(Widget,XtPointer,XtPointer);
  static void projectNewMapped_CB(Widget,XtPointer,XtPointer);
  static void newProject_CB(Widget,XtPointer,XtPointer);
  static void newProjectCancel_CB(Widget,XtPointer,XtPointer);
  static void newProjectHelp_CB(Widget,XtPointer,XtPointer);
  static void projectSettingsMap_CB(Widget,XtPointer,XtPointer);
  static void projectSettingsOk_CB(Widget,XtPointer,XtPointer);
  static void projectSettingsCancel_CB(Widget,XtPointer,XtPointer);
  static void projectSettingsHelp_CB(Widget,XtPointer,XtPointer);
  static void PSPaletteFileChanged_CB(Widget,XtPointer,XtPointer);
  static void PSSourceDirChanged_CB(Widget,XtPointer,XtPointer);
  static void gridMap_CB(Widget,XtPointer,XtPointer);
  static void gridOkCB_CB(Widget,XtPointer,XtPointer);
  static void gridCancelCB_CB(Widget,XtPointer,XtPointer);
  static void gridHelpCB_CB(Widget,XtPointer,XtPointer);
  static void saveProjectOk_CB(Widget,XtPointer,XtPointer);
  static void loadProjectOk_CB(Widget,XtPointer,XtPointer);
  static void loadInterfaceOk_CB(Widget,XtPointer,XtPointer);
  static void do_overwrite_CB(Widget,XtPointer,XtPointer);
  static void overwriteCancel_CB(Widget,XtPointer,XtPointer);
  static void overwriteHelp_CB(Widget,XtPointer,XtPointer);
  static void do_openTemplates_CB(Widget,XtPointer,XtPointer);
  static void do_qsDo_CB(Widget,XtPointer,XtPointer);
  static void do_qsChanged_CB(Widget,XtPointer,XtPointer);
  static void do_viewDefaultsMap_CB(Widget,XtPointer,XtPointer);
  static void do_viewDefaultsOk_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicCancel_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicMap_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicChanged_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicSelect_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicFocus_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicAdd_CB(Widget,XtPointer,XtPointer);
  static void do_defaultPublicDelete_CB(Widget,XtPointer,XtPointer);
  static void do_genericOptionsMap_CB(Widget,XtPointer,XtPointer);
  static void do_genericOptionsOk_CB(Widget,XtPointer,XtPointer);
  static void executeCancel_CB(Widget,XtPointer,XtPointer);
  static void executeHelp_CB(Widget,XtPointer,XtPointer);
  static void executeOk_CB(Widget,XtPointer,XtPointer);
  static void do_stop_CB(Widget,XtPointer,XtPointer);
  static void generateCancel_CB(Widget,XtPointer,XtPointer);
  static void generateHelp_CB(Widget,XtPointer,XtPointer);
  static void generateOk_CB(Widget,XtPointer,XtPointer);



  // override the following methods in class MainWindow

  virtual void do_newTemplates(Widget,XtPointer) = 0;
  virtual void do_projectSettings(Widget,XtPointer) = 0;
  virtual void showHelp(Widget,XtPointer) = 0;
  virtual void do_openGlobalResources(Widget,XtPointer) = 0;
  virtual void showWidgetPalette(Widget,XtPointer) = 0;
  virtual void quickHelpMenuMap(Widget,XtPointer) = 0;
  virtual void updatePolicyChanged(Widget,XtPointer) = 0;
  virtual void defaultShellChanged(Widget,XtPointer) = 0;
  virtual void DoHelpForHelp(Widget,XtPointer) = 0;
  virtual void DoContextHelp(Widget,XtPointer) = 0;
  virtual void testModeChanged(Widget,XtPointer) = 0;
  virtual void projectNewMapped(Widget,XtPointer) = 0;
  virtual void newProject(Widget,XtPointer) = 0;
  virtual void newProjectCancel(Widget,XtPointer) = 0;
  virtual void newProjectHelp(Widget,XtPointer) = 0;
  virtual void projectSettingsMap(Widget,XtPointer) = 0;
  virtual void projectSettingsOk(Widget,XtPointer) = 0;
  virtual void projectSettingsCancel(Widget,XtPointer) = 0;
  virtual void projectSettingsHelp(Widget,XtPointer) = 0;
  virtual void PSPaletteFileChanged(Widget,XtPointer) = 0;
  virtual void PSSourceDirChanged(Widget,XtPointer) = 0;
  virtual void gridMap(Widget,XtPointer) = 0;
  virtual void gridOkCB(Widget,XtPointer) = 0;
  virtual void gridCancelCB(Widget,XtPointer) = 0;
  virtual void gridHelpCB(Widget,XtPointer) = 0;
  virtual void saveProjectOk(Widget,XtPointer) = 0;
  virtual void loadProjectOk(Widget,XtPointer) = 0;
  virtual void loadInterfaceOk(Widget,XtPointer) = 0;
  virtual void do_overwrite(Widget,XtPointer) = 0;
  virtual void overwriteCancel(Widget,XtPointer) = 0;
  virtual void overwriteHelp(Widget,XtPointer) = 0;
  virtual void do_openTemplates(Widget,XtPointer) = 0;
  virtual void do_qsDo(Widget,XtPointer) = 0;
  virtual void do_qsChanged(Widget,XtPointer) = 0;
  virtual void do_viewDefaultsMap(Widget,XtPointer) = 0;
  virtual void do_viewDefaultsOk(Widget,XtPointer) = 0;
  virtual void do_defaultPublicCancel(Widget,XtPointer) = 0;
  virtual void do_defaultPublicMap(Widget,XtPointer) = 0;
  virtual void do_defaultPublicChanged(Widget,XtPointer) = 0;
  virtual void do_defaultPublicSelect(Widget,XtPointer) = 0;
  virtual void do_defaultPublicFocus(Widget,XtPointer) = 0;
  virtual void do_defaultPublicAdd(Widget,XtPointer) = 0;
  virtual void do_defaultPublicDelete(Widget,XtPointer) = 0;
  virtual void do_genericOptionsMap(Widget,XtPointer) = 0;
  virtual void do_genericOptionsOk(Widget,XtPointer) = 0;
  virtual void executeCancel(Widget,XtPointer) = 0;
  virtual void executeHelp(Widget,XtPointer) = 0;
  virtual void executeOk(Widget,XtPointer) = 0;
  virtual void do_stop(Widget,XtPointer) = 0;
  virtual void generateCancel(Widget,XtPointer) = 0;
  virtual void generateHelp(Widget,XtPointer) = 0;
  virtual void generateOk(Widget,XtPointer) = 0;


public:
  MainWindow_base(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0, char
*fbRes = NULL);

  Widget getTop() { return MainWindow; }
  Pixmap createPixmapFromData(char **data);
  Pixmap createPixmapFromFile(char *filename);
  static void manageWidget(Widget wg, XtPointer c, XtPointer call);
};

#endif /* Don't add stuff after this #endif */






