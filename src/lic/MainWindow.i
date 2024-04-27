WIDGET {
  NAME "MainWindow"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 315 LONG LicView height 570 BOOLEAN TreeNodeView WithChildren TRUE "
  DESCRIPTION "TopLevelShell"
  iconPixmap "Logo.xpm" load
  WIDGET {
    NAME "XmForm_1"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "1"
    VIEWDATA "LONG LicView width 456 LONG LicView height 688 BOOLEAN TreeNodeView WithChildren TRUE "
    DESCRIPTION "XmForm"
    height "450" private
    width "500" private
    x "0" private
    y "0" private
    WIDGET {
      NAME "MenuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE LONG LicView width 329 LONG LicView height 485 "
      DESCRIPTION "XmCreateMenuBar"
      height "34" private
      width "498" private
      x "1" private
      y "1" private
      menuHelpWidget "helpButton" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      topAttachment "XmATTACH_FORM" private
      topOffset "1" private
      WIDGET {
        NAME "File"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "File" public
        mnemonic "F" public
        subMenuId "FileMenu" private
      }
      WIDGET {
        NAME "FileMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "ProjectNew"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Create new project."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "New ..." public
          mnemonic "N" public
          activateCallback "ProjectNewDialog" manage
        }
        WIDGET {
          NAME "FileOpen"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Load project from file."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>o" public
          acceleratorText "^O" public
          labelString "Open ..." public
          mnemonic "O" public
          activateCallback "loadProjectDialog" manage
        }
        WIDGET {
          NAME "FileSave"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Save current project."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>s" public
          acceleratorText "^S" public
          labelString "Save" public
          mnemonic "S" public
        }
        WIDGET {
          NAME "FileSaveAs"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Save current project to another location."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Save As ..." public
          mnemonic "A" public
          activateCallback "saveProjectDialog" manage
        }
        WIDGET {
          NAME "separator"
          CLASS "XmSeparator"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmSeparator"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "newTemplates"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Create new widget template folder."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "New Templates" public
          mnemonic "T" private
          activateCallback "do_newTemplates" method
        }
        WIDGET {
          NAME "openTemplates"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Read template folder from a file."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Open Templates ..." public
          mnemonic "p" public
          activateCallback "openTemplatesDialog" manage
        }
        WIDGET {
          NAME "separator_2"
          CLASS "XmSeparator"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmSeparator"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "FileExit"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Exit View Designer/X."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>x" public
          acceleratorText "^X" public
          labelString "Exit" public
          mnemonic "x" public
        }
      }
      WIDGET {
        NAME "Project"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Project" public
        mnemonic "P" public
        subMenuId "ProjectMenu" private
      }
      WIDGET {
        NAME "ProjectMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "ProjectSettings"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show project settings dialog."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Settings" public
          mnemonic "S" public
          activateCallback "do_projectSettings" method
        }
        WIDGET {
          NAME "ProjectLoadInterface"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Load an interface from file and add this to current project."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Import Interface ..." public
          mnemonic "I" public
          activateCallback "loadInterfaceDialog" manage
        }
        WIDGET {
          NAME "ProjectShowHelp"
          CLASS "XmPushButton"
          MANAGED "FALSE"
          QUICKHELP "Show help system for current project."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Show Help" public
          mnemonic "H" public
          activateCallback "showHelp" method
        }
        WIDGET {
          NAME "ProjectResources"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Open the global resource settings."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Global Resources" public
          mnemonic "R" public
          activateCallback "do_openGlobalResources" method
        }
        WIDGET {
          NAME "ProjectGenerate"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Generate project's source code."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>g" public
          acceleratorText "^G" public
          labelString "Generate ..." public
          mnemonic "G" public
          activateCallback "ProjectGenerateDialog" manage
        }
        WIDGET {
          NAME "ProjectExecute"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Execute xmkmf, make or application."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>e" public
          acceleratorText "^E" public
          labelString "Execute ..." public
          mnemonic "E" public
          activateCallback "executeDialog" manage
        }
      }
      WIDGET {
        NAME "Widgets"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Widgets" public
        mnemonic "W" public
        subMenuId "WidgetsMenu" private
      }
      WIDGET {
        NAME "WidgetsMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "WidgetsPalette"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show widget class palette."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Palette" public
          mnemonic "P" public
          activateCallback "showWidgetPalette" method
        }
        WIDGET {
          NAME "XmSeparator"
          CLASS "XmSeparator"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmSeparator"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "ShellMenuButton"
          CLASS "XmCascadeButton"
          MANAGED "TRUE"
          QUICKHELP "Create a shell widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Shell" public
          mnemonic "S" public
          subMenuId "ShellMenu" private
        }
        WIDGET {
          NAME "ShellMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          tearOffModel "XmTEAR_OFF_ENABLED" private
        }
        WIDGET {
          NAME "ManagerMenuButton"
          CLASS "XmCascadeButton"
          MANAGED "TRUE"
          QUICKHELP "Create a manager widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Manager" public
          mnemonic "M" private
          subMenuId "ManagerMenu" private
        }
        WIDGET {
          NAME "ManagerMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          tearOffModel "XmTEAR_OFF_ENABLED" private
        }
        WIDGET {
          NAME "PrimitivesMenuButton"
          CLASS "XmCascadeButton"
          MANAGED "TRUE"
          QUICKHELP "Create a primitive widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Primitive" public
          mnemonic "i" public
          subMenuId "PrimitivesMenu" private
        }
        WIDGET {
          NAME "PrimitivesMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          tearOffModel "XmTEAR_OFF_ENABLED" private
        }
        WIDGET {
          NAME "DialogsMenuButton"
          CLASS "XmCascadeButton"
          MANAGED "TRUE"
          QUICKHELP "Create a dialog widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Dialog" public
          mnemonic "D" public
          subMenuId "DialogsMenu" private
        }
        WIDGET {
          NAME "DialogsMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          tearOffModel "XmTEAR_OFF_ENABLED" private
        }
      }
      WIDGET {
        NAME "Options"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Options" public
        mnemonic "O" public
        subMenuId "OptionsMenu" private
      }
      WIDGET {
        NAME "OptionsMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE LONG LicView width 357 LONG LicView height 527 "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        mapCallback "quickHelpMenuMap" method
        WIDGET {
          NAME "genericOptionButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Change the behavior of Replace_Product."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Generic ..." public
          mnemonic "e" public
          activateCallback "genericOptionsDialog" manage
        }
        WIDGET {
          NAME "OptionsGrid"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show dialog to change wysiwyg view's grid value."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Grid ..." public
          mnemonic "G" public
          activateCallback "GridDialog" manage
        }
        WIDGET {
          NAME "UpdatePolicy"
          CLASS "XmCascadeButton"
          MANAGED "TRUE"
          QUICKHELP "Modify update behavior of wysiwyg view."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Update Policy" public
          mnemonic "U" public
          subMenuId "UpdatePolicyMenu" private
        }
        WIDGET {
          NAME "UpdatePolicyMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          radioBehavior "1" private
          entryCallback "updatePolicyChanged" method
          WIDGET {
            NAME "minimalRefreshButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP "Update current widget only."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "Minimum" public
            mnemonic "M" public
          }
          WIDGET {
            NAME "optimalRefreshButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP "Update wysiwig view with maximum effort."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "Optimum" public
            mnemonic "O" public
          }
        }
        WIDGET {
          NAME "defaultShellButton"
          CLASS "XmCascadeButton"
          MANAGED "TRUE"
          QUICKHELP "Change default shell."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Default Shell" public
          mnemonic "S" public
          subMenuId "defaultShellMenu" private
        }
        WIDGET {
          NAME "defaultShellMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          radioBehavior "1" private
          entryCallback "defaultShellChanged" method
          WIDGET {
            NAME "applicationShellButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "Application Shell" public
            mnemonic "A" public
          }
          WIDGET {
            NAME "toplevelShellButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "Toplevel Shell" public
            mnemonic "T" public
          }
          WIDGET {
            NAME "transientShellButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "Transient Shell" public
            mnemonic "r" public
          }
          WIDGET {
            NAME "dialogShellButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "Dialog Shell" public
            mnemonic "D" public
          }
        }
        WIDGET {
          NAME "viewDefaultsButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Change view defaults for Widget Resource, Menu Editor and Browser."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "View Defaults ..." public
          mnemonic "V" public
          activateCallback "viewDefaultsDialog" manage
        }
        WIDGET {
          NAME "defaultPublicButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Resources which should always be set in a resource file."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Default Public ..." public
          mnemonic "P" public
          activateCallback "defaultPublicDialog" manage
        }
      }
      WIDGET {
        NAME "helpButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Help" public
        mnemonic "H" public
        subMenuId "HelpMenu" private
      }
      WIDGET {
        NAME "HelpMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "HelpForHelp"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show's how to use the help system."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Help" public
          mnemonic "H" public
          activateCallback "DoHelpForHelp" method
        }
        WIDGET {
          NAME "HelpOnContext"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Get help for a clicked widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Context" public
          mnemonic "C" public
          activateCallback "DoContextHelp" method
        }
        WIDGET {
          NAME "HelpTutorial"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help for View Designer/X."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>F1" public
          acceleratorText "^F1" public
          labelString "Tutorial" public
          mnemonic "T" public
        }
        WIDGET {
          NAME "XmSeparator_1"
          CLASS "XmSeparator"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmSeparator"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "HelpProduct"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Who has developed this software?"
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "About" public
          mnemonic "A" public
          activateCallback "ProductInfoDialog" manage
        }
      }
    }
    WIDGET {
      NAME "OpenIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "Load a project file."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "5" private
      y "35" private
      labelPixmap "OpenProject.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
      activateCallback "loadProjectDialog" manage
    }
    WIDGET {
      NAME "SaveIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "Save current project."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "50" private
      y "35" private
      labelPixmap "SaveProject.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "2" private
      leftWidget "OpenIcon" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
    }
    WIDGET {
      NAME "PaletteIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "Show default template folder."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "95" private
      y "35" private
      labelPixmap "Templates.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "2" private
      leftWidget "SaveIcon" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
    }
    WIDGET {
      NAME "ProductIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "View Designer/X?"
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "405" private
      y "35" private
      labelPixmap "Logo_16.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
      activateCallback "ProductInfoDialog" manage
    }
    WIDGET {
      NAME "seperateBelowToolBar"
      CLASS "XmSeparator"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmSeparator"
      height "10" private
      width "490" private
      x "0" private
      y "80" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "1" private
      topWidget "ProductIcon" private
    }
    WIDGET {
      NAME "WidgetPaletteIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "Show widget class palette."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "140" private
      y "40" private
      labelPixmap "WidgetPalette.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "2" private
      leftWidget "PaletteIcon" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
      activateCallback "showWidgetPalette" method
    }
    WIDGET {
      NAME "XmPanedWindow_1"
      CLASS "XmPanedWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmPanedWindow"
      height "342" private
      width "490" private
      x "10" private
      y "90" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "3" private
      bottomWidget "quickHelp" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "1" private
      topWidget "seperateBelowToolBar" private
      WIDGET {
        NAME "ViewForm"
        CLASS "XmForm"
        MANAGED "TRUE"
        QUICKHELP "All user interfaces of the current project."
        HELPID "-1"
        VIEWDATA "LONG LicView height 300 LONG LicView width 200 LONG LicView height 300 LONG LicView width 200 BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmForm"
        height "130" private
        width "484" private
        x "30" private
        y "30" private
        paneMinimum "40" private
        WIDGET {
          NAME "ViewLabel"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "LONG LicView width 200 LONG LicView height 300 LONG LicView width 200 LONG LicView height 300 "
          DESCRIPTION "XmLabel"
          width "90" private
          x "40" private
          y "30" private
          alignment "XmALIGNMENT_BEGINNING" private
          labelString "Interfaces:" public
          leftAttachment "XmATTACH_FORM" private
          leftOffset "1" private
          topAttachment "XmATTACH_FORM" private
          topOffset "1" private
        }
      }
      WIDGET {
        NAME "MessageForm"
        CLASS "XmForm"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmForm"
        height "198" private
        width "484" private
        x "30" private
        y "30" private
        paneMinimum "80" private
        WIDGET {
          NAME "MessageLabel"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          width "90" private
          x "40" private
          y "30" private
          alignment "XmALIGNMENT_BEGINNING" private
          labelString "Output:" public
          bottomAttachment "XmATTACH_WIDGET" private
          bottomOffset "5" private
          bottomWidget "XmScrolledWindow_1" private
          leftAttachment "XmATTACH_FORM" private
          leftOffset "1" private
          topAttachment "XmATTACH_FORM" private
          topOffset "1" private
        }
        WIDGET {
          NAME "XmScrolledWindow_1"
          CLASS "XmScrolledWindow"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
          DESCRIPTION "XmScrolledWindow"
          height "172" private
          width "484" private
          x "0" private
          y "35" private
          bottomAttachment "XmATTACH_FORM" private
          leftAttachment "XmATTACH_FORM" private
          rightAttachment "XmATTACH_FORM" private
          topAttachment "XmATTACH_WIDGET" private
          topOffset "3" private
          topWidget "MessageClearButton" private
          WIDGET {
            NAME "XmText_1"
            CLASS "XmText"
            MANAGED "TRUE"
            QUICKHELP "The output of X-lib, X-Toolkit, Motif and View Designer/X."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmText"
            height "155" private
            width "467" private
            x "20" private
            y "10" private
            editMode "XmMULTI_LINE_EDIT" private
            editable "0" private
          }
        }
        WIDGET {
          NAME "MessageClearButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Clear output area."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "320" private
          y "10" private
          labelString "Clear" public
          rightAttachment "XmATTACH_FORM" private
          rightOffset "1" private
          topAttachment "XmATTACH_FORM" private
          topOffset "1" private
        }
      }
    }
    WIDGET {
      NAME "quickHelp"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP "This line show quick help while moving pointer."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmLabel"
      width "443" private
      x "0" private
      y "140" private
      alignment "XmALIGNMENT_BEGINNING" private
      labelString "This is the Quick Help Line." public
      marginHeight "0" private
      marginWidth "0" private
      recomputeSize "0" private
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "3" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
    }
    WIDGET {
      NAME "TestModeToggle"
      CLASS "XmToggleButton"
      MANAGED "TRUE"
      QUICKHELP "Switch wysiwyg view into test mode."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmToggleButton"
      height "41" private
      width "100" private
      x "290" private
      y "40" private
      indicatorSize "20" private
      labelString "Test Mode" public
      bottomAttachment "XmATTACH_WIDGET" private
      bottomWidget "seperateBelowToolBar" private
      rightAttachment "XmATTACH_WIDGET" private
      rightOffset "10" private
      rightWidget "ProductIcon" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
      valueChangedCallback "testModeChanged" method
    }
    WIDGET {
      NAME "ProductInfoDialog"
      CLASS "XmCreateFormDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFormDialog"
      height "170" private
      width "270" private
      x "0" private
      y "0" private
      cancelButton "PIClose" private
      dialogTitle "About Replace_Product" public
      noResize "1" private
      WIDGET {
        NAME "PIClose"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "90" private
        x "90" private
        y "160" private
        labelString "Close" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-45" private
        leftPosition "50" private
      }
      WIDGET {
        NAME "ProductInfoLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Replace_Product Release Replace_Revision
Copyright © 1996, 1997, 1998 Dirk Lässig.
All rights reserved." public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        leftWidget "" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_FORM" private
        topOffset "15" private
      }
      WIDGET {
        NAME "label_2"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "18" private
        width "250" private
        x "30" private
        y "108" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Demo Mode" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "20" private
        topWidget "ProductInfoLabel" private
      }
    }
    WIDGET {
      NAME "ProjectNewDialog"
      CLASS "XmCreateFormDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "2"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFormDialog"
      height "110" private
      width "340" private
      x "0" private
      y "0" private
      autoUnmanage "0" private
      cancelButton "ProjectNewCancel" private
      defaultButton "ProjectNewOk" private
      dialogTitle "New Project" public
      initialFocus "ProjectNewText" private
      noResize "1" private
      mapCallback "projectNewMapped" method
      WIDGET {
        NAME "ProjectNewLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        x "30" private
        y "20" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Project Name:" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        topAttachment "XmATTACH_FORM" private
        topOffset "10" private
      }
      WIDGET {
        NAME "ProjectNewText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        width "181" private
        x "160" private
        y "20" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "ProjectNewLabel" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_FORM" private
        topOffset "10" private
      }
      WIDGET {
        NAME "ProjectNewOk"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "30" private
        y "80" private
        labelString "Create" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-46" private
        leftPosition "20" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "ProjectNewSeparator" private
        activateCallback "newProject" method
      }
      WIDGET {
        NAME "ProjectNewCancel"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "125" private
        y "80" private
        labelString "Cancel" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-46" private
        leftPosition "50" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "ProjectNewSeparator" private
        activateCallback "newProjectCancel" method
      }
      WIDGET {
        NAME "ProjectNewHelp"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "210" private
        y "80" private
        labelString "Help" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-46" private
        leftPosition "80" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "ProjectNewSeparator" private
        activateCallback "newProjectHelp" method
      }
      WIDGET {
        NAME "ProjectNewSeparator"
        CLASS "XmSeparator"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmSeparator"
        height "10" private
        width "338" private
        x "0" private
        y "40" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "ProjectNewLabel" private
      }
    }
    WIDGET {
      NAME "ProjectSettingsDialog"
      CLASS "XmCreateFormDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "15"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE LONG LicView width 338 LONG LicView height 494 BOOLEAN TreeNodeView WithChildren FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFormDialog"
      height "270" private
      width "350" private
      x "0" private
      y "0" private
      autoUnmanage "0" private
      cancelButton "PSCancel" private
      defaultButton "PSOk" private
      initialFocus "PSNameText" private
      mapCallback "projectSettingsMap" method
      WIDGET {
        NAME "PSNameLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        width "110" private
        x "10" private
        y "10" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Project File:" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        topAttachment "XmATTACH_FORM" private
        topOffset "10" private
      }
      WIDGET {
        NAME "PSNameText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Name of project file."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        width "215" private
        x "90" private
        y "10" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "PSNameLabel" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_FORM" private
        topOffset "10" private
      }
      WIDGET {
        NAME "PSPaletteLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        width "110" private
        x "10" private
        y "50" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Application Class:" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSNameLabel" private
      }
      WIDGET {
        NAME "PSPaletteText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Name of template file."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        height "31" private
        width "215" private
        x "125" private
        y "50" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "PSPaletteLabel" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        rightWidget "PSPaletteFiles" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSNameLabel" private
      }
      WIDGET {
        NAME "PSLangMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "30" private
        y "10" private
      }
      WIDGET {
        NAME "PSLangOptionMenu"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP "Programming languages for code generation."
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateOptionMenu"
        x "10" private
        y "130" private
        labelString "Generation Model:" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        rightAttachment "XmATTACH_NONE" private
        rightOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSStartLabel" private
      }
      WIDGET {
        NAME "XmSeparator_4"
        CLASS "XmSeparator"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmSeparator"
        height "7" private
        width "348" private
        x "20" private
        y "150" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomOffset "5" private
        bottomWidget "PSCancel" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "PSLangOptionMenu" private
      }
      WIDGET {
        NAME "PSStartLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        width "110" private
        x "10" private
        y "130" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Startup Interface:" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSSourceDirLabel" private
      }
      WIDGET {
        NAME "PCStartText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "First interface after the programm startup."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        width "215" private
        x "110" private
        y "100" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "PSStartLabel" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSSourceDirLabel" private
      }
      WIDGET {
        NAME "PSOk"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "10" private
        y "160" private
        labelString "OK" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-48" private
        leftPosition "20" private
        activateCallback "projectSettingsOk" method
      }
      WIDGET {
        NAME "PSCancel"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "120" private
        y "160" private
        labelString "Cancel" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-48" private
        leftPosition "50" private
        activateCallback "projectSettingsCancel" method
      }
      WIDGET {
        NAME "PSHelp"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "90" private
        x "180" private
        y "160" private
        labelString "Help" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-48" private
        leftPosition "80" private
        activateCallback "projectSettingsHelp" method
      }
      WIDGET {
        NAME "PSSourceDirLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        width "110" private
        x "10" private
        y "90" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Source Path:" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSPaletteLabel" private
      }
      WIDGET {
        NAME "PSSourceDirText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Directory in which the source code is generated."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        height "31" private
        width "180" private
        x "125" private
        y "90" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "PSSourceDirLabel" private
        rightAttachment "XmATTACH_WIDGET" private
        rightOffset "5" private
        rightWidget "PSSourceDirFiles" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSPaletteLabel" private
      }
      WIDGET {
        NAME "PSPaletteFiles"
        CLASS "XmDrawnButton"
        MANAGED "FALSE"
        QUICKHELP "Open a file selection box."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmDrawnButton"
        height "30" private
        width "30" private
        x "310" private
        y "50" private
        labelString "..." public
        pushButtonEnabled "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSNameLabel" private
        activateCallback "PSPaletteFileSB" manage
      }
      WIDGET {
        NAME "PSSourceDirFiles"
        CLASS "XmDrawnButton"
        MANAGED "TRUE"
        QUICKHELP "Open a file selection box."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmDrawnButton"
        height "30" private
        width "30" private
        x "310" private
        y "90" private
        labelString "..." public
        pushButtonEnabled "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "PSPaletteLabel" private
        activateCallback "PSSourceDirFileSB" manage
      }
      WIDGET {
        NAME "PSPaletteFileSB"
        CLASS "XmCreateFileSelectionDialog"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
        DESCRIPTION "XmCreateFileSelectionDialog"
        x "210" private
        y "170" private
        autoUnmanage "1" private
        dialogTitle "Template file" public
        dirMask "*.pal" private
        okCallback "PSPaletteFileChanged" method
      }
      WIDGET {
        NAME "PSSourceDirFileSB"
        CLASS "XmCreateFileSelectionDialog"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
        DESCRIPTION "XmCreateFileSelectionDialog"
        x "250" private
        y "180" private
        autoUnmanage "1" private
        dialogTitle "Source directory" public
        fileTypeMask "XmFILE_DIRECTORY" private
        okCallback "PSSourceDirChanged" method
      }
    }
    WIDGET {
      NAME "GridDialog"
      CLASS "XmCreateFormDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "18"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE LONG LicView width 200 LONG LicView height 300 BOOLEAN TreeNodeView WithChildren FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFormDialog"
      height "200" private
      width "330" private
      x "170" private
      y "40" private
      autoUnmanage "0" private
      cancelButton "GridCancel" private
      defaultButton "GridOk" private
      dialogTitle "Wysiwyg View - Grid" public
      initialFocus "GridRadioBox" private
      noResize "1" private
      mapCallback "gridMap" method
      WIDGET {
        NAME "GridOk"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "20" private
        y "140" private
        labelString "OK" public
        activateCallback "gridOkCB" method
      }
      WIDGET {
        NAME "GridCancel"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "120" private
        y "140" private
        labelString "Cancel" public
        activateCallback "gridCancelCB" method
      }
      WIDGET {
        NAME "GridHelp"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "220" private
        y "140" private
        labelString "Help" public
        activateCallback "gridHelpCB" method
      }
      WIDGET {
        NAME "GridSeparator"
        CLASS "XmSeparator"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmSeparator"
        height "20" private
        width "320" private
        x "0" private
        y "110" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
      }
      WIDGET {
        NAME "GridRadioBox"
        CLASS "XmCreateRadioBox"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateRadioBox"
        borderWidth "1" private
        height "31" private
        x "20" private
        y "10" private
        orientation "XmHORIZONTAL" private
        packing "XmPACK_COLUMN" private
        WIDGET {
          NAME "GridModeOn"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Grid On" public
        }
        WIDGET {
          NAME "GridModeOff"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Grid Off" public
        }
      }
      WIDGET {
        NAME "GridValueLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        width "100" private
        x "20" private
        y "60" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Grid Value" public
      }
      WIDGET {
        NAME "GridValue"
        CLASS "XmScale"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmScale"
        height "40" private
        width "170" private
        x "130" private
        y "50" private
        maximum "50" private
        minimum "1" private
        orientation "XmHORIZONTAL" private
        processingDirection "XmMAX_ON_RIGHT" private
        showValue "XmNEAR_SLIDER" private
        value "10" private
      }
    }
    WIDGET {
      NAME "saveProjectDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "21"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFileSelectionDialog"
      x "170" private
      y "40" private
      autoUnmanage "1" private
      dialogTitle "Save as" public
      dirMask "*.prj" private
      okCallback "saveProjectOk" method
    }
    WIDGET {
      NAME "loadProjectDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "21"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFileSelectionDialog"
      x "170" private
      y "40" private
      autoUnmanage "1" private
      dialogTitle "Load project" public
      dirMask "*.prj" private
      okCallback "loadProjectOk" method
    }
    WIDGET {
      NAME "loadInterfaceDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "21"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFileSelectionDialog"
      x "170" private
      y "40" private
      autoUnmanage "1" private
      dialogTitle "Load interface" public
      dirMask "*.i" private
      okCallback "loadInterfaceOk" method
    }
    WIDGET {
      NAME "overwriteDialog"
      CLASS "XmCreateFormDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "19"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateFormDialog"
      height "300" private
      width "540" private
      x "0" private
      y "0" private
      autoUnmanage "0" private
      cancelButton "owCancel" private
      defaultButton "owOk" private
      dialogTitle "Write the following files?" public
      resizePolicy "XmRESIZE_GROW" private
      WIDGET {
        NAME "owOk"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Write selected files."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "32" private
        width "90" private
        x "10" private
        y "258" private
        labelString "Write" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        activateCallback "do_overwrite" method
      }
      WIDGET {
        NAME "owCancel"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Don't write anything."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "110" private
        y "250" private
        labelString "Do nothing" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        leftAttachment "XmATTACH_POSITION" private
        leftOffset "-45" private
        leftPosition "50" private
        activateCallback "overwriteCancel" method
      }
      WIDGET {
        NAME "owHelp"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Getting more help."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "210" private
        y "250" private
        labelString "Help" public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "10" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        activateCallback "overwriteHelp" method
      }
      WIDGET {
        NAME "scrolledWindow_1"
        CLASS "XmScrolledWindow"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmScrolledWindow"
        height "226" private
        width "520" private
        x "10" private
        y "70" private
        scrollBarDisplayPolicy "XmSTATIC" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomOffset "10" private
        bottomWidget "owOk" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "10" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "10" private
        topAttachment "XmATTACH_FORM" private
        topOffset "10" private
        WIDGET {
          NAME "overwriteFilesList"
          CLASS "XmList"
          MANAGED "TRUE"
          QUICKHELP "Selected files will be written."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmList"
          height "226" private
          width "520" private
          x "0" private
          y "0" private
          fontList "-adobe-courier-medium-r-normal--12-120-75-75-m-70-iso8859-1" public
          listSizePolicy "XmVARIABLE" private
          scrollBarDisplayPolicy "XmAS_NEEDED" private
          selectionPolicy "XmMULTIPLE_SELECT" private
        }
      }
    }
    WIDGET {
      NAME "ExecIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "Execute xmkmf, make or application."
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "140" private
      y "40" private
      labelPixmap "Execute.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "2" private
      leftWidget "generateIcon" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
      activateCallback "executeDialog" manage
    }
    WIDGET {
      NAME "openTemplatesDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "21"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFileSelectionDialog"
      x "200" private
      y "40" private
      autoUnmanage "1" private
      dialogTitle "Open Template File" private
      dirMask "*.pal" private
      okCallback "do_openTemplates" method
    }
    WIDGET {
      NAME "quickStartDialog"
      CLASS "XmCreateQuestionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "42"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateQuestionDialog"
      x "0" private
      y "0" private
      cancelLabelString "Close" public
      dialogTitle "Quick Start" public
      messageString "What do you want to do?" public
      okLabelString "Do" public
      okCallback "do_qsDo" method
      WIDGET {
        NAME "xlCellTable_1"
        CLASS "XlCellTable"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XlCellTable"
        x "100" private
        y "10" private
        WIDGET {
          NAME "qsOpenButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "10" private
          y "30" private
          alignment "XmALIGNMENT_BEGINNING" private
          indicatorType "XmONE_OF_MANY" private
          labelString "Open Project:" private
          cellColumn "0" private
          cellRow "0" private
          valueChangedCallback "do_qsChanged" method
        }
        WIDGET {
          NAME "qsNewButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "10" private
          y "40" private
          alignment "XmALIGNMENT_BEGINNING" private
          indicatorType "XmONE_OF_MANY" private
          labelString "New Project:" public
          cellColumn "0" private
          cellRow "1" private
          valueChangedCallback "do_qsChanged" method
        }
        WIDGET {
          NAME "qsRecoverButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "10" private
          y "40" private
          alignment "XmALIGNMENT_BEGINNING" private
          indicatorType "XmONE_OF_MANY" private
          labelString "Recover Project:" public
          cellColumn "0" private
          cellRow "2" private
          valueChangedCallback "do_qsChanged" method
        }
        WIDGET {
          NAME "qsOpenText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "80" private
          y "20" private
          resizeWidth "1" private
          cellColumn "1" private
          cellRow "0" private
        }
        WIDGET {
          NAME "qsNewText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "80" private
          y "20" private
          resizeWidth "1" private
          cellColumn "1" private
          cellRow "1" private
        }
        WIDGET {
          NAME "qsRecoverText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "80" private
          y "20" private
          resizeWidth "1" private
          cellColumn "1" private
          cellRow "2" private
        }
      }
    }
    WIDGET {
      NAME "generateIcon"
      CLASS "XmDrawnButton"
      MANAGED "TRUE"
      QUICKHELP "Generate Source Code"
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawnButton"
      height "40" private
      width "40" private
      x "220" private
      y "40" private
      labelPixmap "Generate.xpm" load
      labelType "XmPIXMAP" private
      pushButtonEnabled "1" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "2" private
      leftWidget "WidgetPaletteIcon" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "MenuBar" private
      activateCallback "ProjectGenerateDialog" manage
    }
    WIDGET {
      NAME "viewDefaultsDialog"
      CLASS "XmCreateMessageDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "39"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMessageDialog"
      dialogTitle "View Default Settings" public
      messageString "Define default settings of views." private
      mapCallback "do_viewDefaultsMap" method
      okCallback "do_viewDefaultsOk" method
      WIDGET {
        NAME "rowColumn_2"
        CLASS "XmRowColumn"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmRowColumn"
        height "100" private
        width "100" private
        x "20" private
        y "0" private
        numColumns "2" private
        packing "XmPACK_COLUMN" private
        WIDGET {
          NAME "widBrowseViewFrame"
          CLASS "XmFrame"
          MANAGED "TRUE"
          QUICKHELP "Widget Tree Browser defaults."
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XmFrame"
          WIDGET {
            NAME "label_3"
            CLASS "XmLabel"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmLabel"
            x "30" private
            y "0" private
            labelString "Widget Tree Browser" public
            childType "XmFRAME_TITLE_CHILD" private
          }
          WIDGET {
            NAME "rowColumn_3"
            CLASS "XmRowColumn"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
            DESCRIPTION "XmRowColumn"
            height "119" private
            width "166" private
            x "0" private
            y "0" private
            WIDGET {
              NAME "browserSmallIconToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Small Icons" public
            }
            WIDGET {
              NAME "browserWithIconToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "With Icons" public
            }
            WIDGET {
              NAME "browserWithClassNameToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "With Class Name" public
            }
            WIDGET {
              NAME "browserAutomaticLoadToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Automatic Load" public
            }
          }
        }
        WIDGET {
          NAME "menuEditFrame"
          CLASS "XmFrame"
          MANAGED "TRUE"
          QUICKHELP "Menu Editor defaults."
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XmFrame"
          WIDGET {
            NAME "label_3_1"
            CLASS "XmLabel"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmLabel"
            x "30" private
            y "0" private
            labelString "Menu Editor" public
            childType "XmFRAME_TITLE_CHILD" private
          }
          WIDGET {
            NAME "rowColumn_3_1"
            CLASS "XmRowColumn"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
            DESCRIPTION "XmRowColumn"
            height "119" private
            width "166" private
            x "0" private
            y "0" private
            WIDGET {
              NAME "menuEditSmallIconToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Small Icons" public
            }
            WIDGET {
              NAME "menuEditWithIconToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "With Icons" public
            }
            WIDGET {
              NAME "menuEditWithClassNameToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "With Class Name" public
            }
            WIDGET {
              NAME "menuEditAutomaticLoadToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Automatic Load" public
            }
          }
        }
        WIDGET {
          NAME "attachmentEditorFrame"
          CLASS "XmFrame"
          MANAGED "TRUE"
          QUICKHELP "Menu Editor defaults."
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XmFrame"
          WIDGET {
            NAME "label_3_1_1"
            CLASS "XmLabel"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmLabel"
            x "30" private
            y "0" private
            labelString "Attachment Editor" public
            childType "XmFRAME_TITLE_CHILD" private
          }
          WIDGET {
            NAME "rowColumn_3_1_1"
            CLASS "XmRowColumn"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
            DESCRIPTION "XmRowColumn"
            height "119" private
            width "180" private
            x "0" private
            y "0" private
            WIDGET {
              NAME "aeSmallIconToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Small Icons" public
            }
            WIDGET {
              NAME "aeWithIconToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "With Icons" public
            }
            WIDGET {
              NAME "aeWithClassNameToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "With Class Name" public
            }
            WIDGET {
              NAME "aeAutomaticLoadToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Automatic Load" public
            }
          }
        }
        WIDGET {
          NAME "resourceEditorFrame"
          CLASS "XmFrame"
          MANAGED "TRUE"
          QUICKHELP "Widget Resource Editor defauts."
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
          DESCRIPTION "XmFrame"
          WIDGET {
            NAME "label_3_2"
            CLASS "XmLabel"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmLabel"
            x "30" private
            y "0" private
            labelString "Widget Resource Editor" public
            childType "XmFRAME_TITLE_CHILD" private
          }
          WIDGET {
            NAME "rowColumn_3_2"
            CLASS "XmRowColumn"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XmRowColumn"
            height "119" private
            width "180" private
            x "0" private
            y "0" private
            WIDGET {
              NAME "editorAutomaticLoadToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "0" private
              y "0" private
              labelString "Automatic Load" public
            }
            WIDGET {
              NAME "defaultViewOptionMenu"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmCreateOptionMenu"
              x "30" private
              y "40" private
              labelString "Default View:" private
              subMenuId "defaultViewMenu" private
              WIDGET {
                NAME "defaultViewMenu"
                CLASS "XmCreatePulldownMenu"
                MANAGED "FALSE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmCreatePulldownMenu"
                x "60" private
                y "10" private
                WIDGET {
                  NAME "coreView"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP ""
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelString "Core" public
                }
                WIDGET {
                  NAME "specificView"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP ""
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelString "Specific" public
                }
                WIDGET {
                  NAME "constraintView"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP ""
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelString "Constraints" public
                }
                WIDGET {
                  NAME "callbackView"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP ""
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelString "Callbacks" public
                }
                WIDGET {
                  NAME "extraView"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP ""
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelString "Extra" private
                }
              }
            }
          }
        }
      }
    }
    WIDGET {
      NAME "defaultPublicDialog"
      CLASS "XmCreateMessageDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "40"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMessageDialog"
      x "0" private
      y "0" private
      autoUnmanage "0" private
      dialogTitle "Default Public Resources" public
      messageString "Resources which are always in resources files." public
      cancelCallback "do_defaultPublicCancel" method
      mapCallback "do_defaultPublicMap" method
      okCallback "do_defaultPublicChanged" method
      WIDGET {
        NAME "rowColumn_4"
        CLASS "XmRowColumn"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmRowColumn"
        height "185" private
        width "340" private
        x "0" private
        y "0" private
        WIDGET {
          NAME "scrolledWindow_2"
          CLASS "XmScrolledWindow"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmScrolledWindow"
          height "143" private
          width "334" private
          x "0" private
          y "0" private
          WIDGET {
            NAME "defaultPublicList"
            CLASS "XmList"
            MANAGED "TRUE"
            QUICKHELP "List of public resources."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmList"
            height "143" private
            width "334" private
            x "0" private
            y "0" private
            itemCount "3" private
            items "hallo, sss, ccc" private
            selectionPolicy "XmMULTIPLE_SELECT" private
            visibleItemCount "8" private
            multipleSelectionCallback "do_defaultPublicSelect" method
          }
        }
        WIDGET {
          NAME "defaultPublicText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP "Enter a resource name, like labelString."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "0" private
          y "0" private
          columns "25" private
          focusCallback "do_defaultPublicFocus" method
        }
      }
      WIDGET {
        NAME "defaultPublicAdd"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Add resource to the list."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelString "Add" public
        activateCallback "do_defaultPublicAdd" method
      }
      WIDGET {
        NAME "defaultPublicDelete"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Delete selected resource names. "
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelString "Delete" public
        activateCallback "do_defaultPublicDelete" method
      }
    }
    WIDGET {
      NAME "genericOptionsDialog"
      CLASS "XmCreateMessageDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "41"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMessageDialog"
      x "280" private
      y "50" private
      dialogTitle "Generic Options" public
      messageString "Customize Replace_Product's generic behavior." public
      mapCallback "do_genericOptionsMap" method
      okCallback "do_genericOptionsOk" method
      WIDGET {
        NAME "xlCellTable_2"
        CLASS "XlCellTable"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XlCellTable"
        x "50" private
        y "30" private
        WIDGET {
          NAME "label_4"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Quick Start Dialog:" public
          cellColumn "0" private
          cellRow "0" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "label_4_1"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Auto Saving:" public
          cellColumn "0" private
          cellRow "1" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "label_4_2"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Auto Save Time:" public
          cellColumn "0" private
          cellRow "2" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "label_4_3"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Auto Save Path:" public
          cellColumn "0" private
          cellRow "3" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "label_4_4"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Main Template Folder:" public
          cellColumn "0" private
          cellRow "4" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "genericQuickStartToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Shows a dialog at program startup."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "130" private
          y "10" private
          labelString "Show" public
          cellColumn "1" private
          cellRow "0" private
          horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
        }
        WIDGET {
          NAME "genericAutoSaveToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Enable automatic saving of projects."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "130" private
          y "10" private
          labelString "On" public
          cellColumn "1" private
          cellRow "1" private
          horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
        }
        WIDGET {
          NAME "genericAutoSaveScale"
          CLASS "XmScale"
          MANAGED "TRUE"
          QUICKHELP "Change the auto save time."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmScale"
          height "58" private
          width "138" private
          x "159" private
          y "67" private
          decimalPoints "1" private
          maximum "100" private
          minimum "1" private
          orientation "XmHORIZONTAL" private
          processingDirection "XmMAX_ON_RIGHT" private
          showValue "XmNEAR_SLIDER" private
          titleString "minutes" private
          cellColumn "1" private
          cellRow "2" private
        }
        WIDGET {
          NAME "genericAutoSaveText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP "Path where the auto saved project is placed."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "80" private
          y "130" private
          cellColumn "1" private
          cellRow "3" private
        }
        WIDGET {
          NAME "genericMainTemplateText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP "Template folder that is opened by template icon."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "80" private
          y "130" private
          cellColumn "1" private
          cellRow "4" private
        }
        WIDGET {
          NAME "label_4_4_1"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Quick Help:" public
          cellColumn "0" private
          cellRow "5" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "quickHelpToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Enable the Quick Help lines."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "130" private
          y "10" private
          labelString "Show Lines" public
          cellColumn "1" private
          cellRow "5" private
          horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
        }
        WIDGET {
          NAME "label_4_4_1_1"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "10" private
          y "0" private
          labelString "Wysiwyg after load:" public
          cellColumn "0" private
          cellRow "7" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
        }
        WIDGET {
          NAME "genericAfterLoadToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show wysiwyg view after an interface is read from a file."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "130" private
          y "10" private
          labelString "Show" public
          cellColumn "1" private
          cellRow "7" private
          horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
        }
        WIDGET {
          NAME "toolTipLabel"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "70" private
          y "230" private
          labelString "Tool Tips:" public
          cellColumn "0" private
          cellRow "6" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
          verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
        }
        WIDGET {
          NAME "versionControlLabel"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "90" private
          y "250" private
          labelString "Version Control:" public
          cellColumn "0" private
          cellRow "8" private
          horizontalAlignment "XmCELL_ALIGNMENT_END" private
          verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
        }
        WIDGET {
          NAME "toolTipToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show help on toolbar buttons."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "160" private
          y "250" private
          labelString "Show" private
          cellColumn "1" private
          cellRow "6" private
          horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
          verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
        }
        WIDGET {
          NAME "versionControlToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Execute scripts (vcopen, vcsave, vcclose)."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "210" private
          y "240" private
          labelString "Execute Scripts" public
          cellColumn "1" private
          cellRow "8" private
          horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
          verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
        }
      }
    }
    WIDGET {
      NAME "executeDialog"
      CLASS "XmCreateMessageDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "20"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateFormDialog"
      autoUnmanage "0" private
      cancelLabelString "Close" private
      dialogTitle "Execute Program" public
      messageString "Do you want to execute one program." private
      okLabelString "Apply" private
      resizePolicy "XmRESIZE_GROW" private
      cancelCallback "executeCancel" method
      helpCallback "executeHelp" method
      okCallback "executeOk" method
      WIDGET {
        NAME "executeCellTable"
        CLASS "XlCellTable"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmForm"
        resizeColumn "0" private
        resizeRow "0" private
        WIDGET {
          NAME "executeRowColumn"
          CLASS "XmRowColumn"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
          DESCRIPTION "XmRowColumn"
          height "119" private
          width "107" private
          x "5" private
          y "5" private
          radioBehavior "1" private
          cellColumn "0" private
          cellRow "0" private
          horizontalAlignment "XmCELL_ALIGNMENT_CENTER" private
          verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
          WIDGET {
            NAME "xmkmfToggleButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP "Execute xmkmf for makefile creation."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "xmkmf" public
          }
          WIDGET {
            NAME "makeDependToggleButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP "Execute 'make depend'."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "make depend" public
          }
          WIDGET {
            NAME "makeToggleButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP "Build your application using 'make'."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "make" public
          }
          WIDGET {
            NAME "execToggleButton"
            CLASS "XmToggleButton"
            MANAGED "TRUE"
            QUICKHELP "Run your application."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmToggleButton"
            x "0" private
            y "0" private
            labelString "program" public
          }
        }
        WIDGET {
          NAME "StopIcon"
          CLASS "XmDrawnButton"
          MANAGED "TRUE"
          QUICKHELP "Stop running program"
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmDrawnButton"
          height "60" private
          width "60" private
          labelPixmap "Stop.xpm" load
          labelType "XmPIXMAP" private
          pushButtonEnabled "1" private
          recomputeSize "0" private
          cellColumn "1" private
          cellRow "0" private
          horizontalAlignment "XmCELL_ALIGNMENT_CENTER" private
          verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
          activateCallback "do_stop" method
        }
      }
    }
    WIDGET {
      NAME "ProjectGenerateDialog"
      CLASS "XmCreateMessageDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "17"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE BOOLEAN WidgetView showDialog FALSE LONG LicView width 200 LONG LicView height 300 "
      DESCRIPTION "XmCreateFormDialog"
      autoUnmanage "0" private
      cancelButton "" private
      defaultButton "" private
      dialogTitle "Generate Source Code" public
      messageString "Overwrite the following files?" private
      cancelCallback "generateCancel" method
      helpCallback "generateHelp" method
      okCallback "generateOk" method
      WIDGET {
        NAME "rowColumn_1"
        CLASS "XmRowColumn"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmRowColumn"
        WIDGET {
          NAME "ImakefileGenerateToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Generate Imakefile for makefile creation."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "50" private
          y "20" private
          labelString "Imakefile" private
        }
        WIDGET {
          NAME "MainGenerateToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Generate main source file."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "10" private
          y "0" private
          labelString "Main Program" private
        }
        WIDGET {
          NAME "StubsGenerateToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Stubs you can edit."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "-10" private
          y "20" private
          labelString "Callback Stubs" private
        }
      }
    }
  }
}
