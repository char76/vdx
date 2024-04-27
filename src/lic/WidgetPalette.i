WIDGET {
  NAME "WidgetPalette"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 377 LONG LicView height 603 "
  DESCRIPTION "TopLevelShell"
  iconPixmap "WidgetPalette.xpm" load
  title "Widget Class Palette" private
  WIDGET {
    NAME "WidgetCreateForm"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "14"
    VIEWDATA ""
    DESCRIPTION "XmForm"
    height "595" private
    width "349" private
    x "0" private
    y "-30" private
    defaultPosition "0" private
    WIDGET {
      NAME "quickHelp"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmLabel"
      x "-30" private
      y "100" private
      alignment "XmALIGNMENT_BEGINNING" private
      labelString "This is the Quick Help Line." public
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
    }
    WIDGET {
      NAME "menuBar_1"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMenuBar"
      height "35" private
      width "347" private
      x "10" private
      y "0" private
      menuHelpWidget "helpButton" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      topAttachment "XmATTACH_FORM" private
      topOffset "1" private
      WIDGET {
        NAME "fileButton"
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
        subMenuId "fileMenu" private
      }
      WIDGET {
        NAME "fileMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "fileClose"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Hide the widget class palette."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>c" public
          acceleratorText "^C" public
          labelString "Close" public
          mnemonic "C" public
          activateCallback "do_close" method
        }
      }
      WIDGET {
        NAME "viewButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "View" public
        mnemonic "V" public
        subMenuId "viewMenu" private
      }
      WIDGET {
        NAME "viewMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        entryCallback "do_viewEntry" method
        WIDGET {
          NAME "withNamesButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "With Names" public
          mnemonic "N" public
        }
        WIDGET {
          NAME "withIconsButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "With Icons" public
          mnemonic "I" public
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
          NAME "shellsButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Shells" public
          mnemonic "S" public
        }
        WIDGET {
          NAME "managersButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Managers" public
          mnemonic "M" public
        }
        WIDGET {
          NAME "primitivesButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Primitives" public
          mnemonic "P" public
        }
        WIDGET {
          NAME "dialogsButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Dialogs" public
          mnemonic "D" public
        }
      }
      WIDGET {
        NAME "optionsButton"
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
        subMenuId "optionsMenu" private
      }
      WIDGET {
        NAME "optionsMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        entryCallback "do_optionsEntry" method
        WIDGET {
          NAME "createOnClickButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "Create On Click" public
          mnemonic "C" public
        }
        WIDGET {
          NAME "asChildOfSelectedButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "As Child" public
          mnemonic "A" public
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
        mnemonic "H" private
        subMenuId "helpMenu" private
      }
      WIDGET {
        NAME "helpMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "onHelp"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Help" public
          mnemonic "H" public
          activateCallback "do_onHelp" method
        }
        WIDGET {
          NAME "onContext"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Context" public
          mnemonic "C" public
          activateCallback "do_onContext" method
        }
        WIDGET {
          NAME "helpHelp"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>F1" public
          acceleratorText "^F1" public
          labelString "On Window" public
          mnemonic "W" public
          activateCallback "do_help" method
        }
      }
    }
    WIDGET {
      NAME "scrollBar"
      CLASS "XmScrollBar"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmScrollBar"
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "0" private
      bottomWidget "quickHelp" private
      leftAttachment "XmATTACH_NONE" private
      resizable "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "3" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "3" private
      topWidget "menuBar_1" private
    }
    WIDGET {
      NAME "frame"
      CLASS "XmFrame"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmDrawingArea"
      shadowThickness "2" private
      shadowType "XmSHADOW_IN" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "0" private
      bottomWidget "quickHelp" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "3" private
      resizable "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "3" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "3" private
      topWidget "menuBar_1" private
      WIDGET {
        NAME "form"
        CLASS "XmForm"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmForm"
        x "0" private
        y "0" private
        WIDGET {
          NAME "WidgetPanedWindow"
          CLASS "XmPanedWindow"
          MANAGED "TRUE"
          QUICKHELP "Press left button on icons."
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
          DESCRIPTION "XmPanedWindow"
          marginHeight "0" private
          marginWidth "0" private
          spacing "2" private
          bottomAttachment "XmATTACH_FORM" private
          bottomOffset "0" private
          leftAttachment "XmATTACH_FORM" private
          leftOffset "0" private
          resizable "0" private
          rightAttachment "XmATTACH_FORM" private
          rightOffset "0" private
          topAttachment "XmATTACH_FORM" private
          topOffset "0" private
          WIDGET {
            NAME "ShellForm"
            CLASS "XmForm"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XmForm"
            height "96" private
            width "325" private
            x "0" private
            y "0" private
            paneMinimum "50" private
            WIDGET {
              NAME "ShellLabel"
              CLASS "XmLabel"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmLabel"
              x "10" private
              y "20" private
              alignment "XmALIGNMENT_BEGINNING" private
              labelString "Shells:" private
              bottomAttachment "XmATTACH_NONE" private
              leftAttachment "XmATTACH_FORM" private
              leftOffset "0" private
              resizable "1" private
              rightAttachment "XmATTACH_NONE" private
              topAttachment "XmATTACH_FORM" private
              topOffset "0" private
            }
          }
          WIDGET {
            NAME "ManagerForm"
            CLASS "XmForm"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XmForm"
            height "85" private
            width "325" private
            x "0" private
            y "102" private
            paneMinimum "50" private
            WIDGET {
              NAME "ManagerLabel"
              CLASS "XmLabel"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmLabel"
              x "10" private
              y "20" private
              alignment "XmALIGNMENT_BEGINNING" private
              labelString "Managers:" private
              bottomAttachment "XmATTACH_NONE" private
              leftAttachment "XmATTACH_FORM" private
              leftOffset "0" private
              resizable "1" private
              rightAttachment "XmATTACH_NONE" private
              topAttachment "XmATTACH_FORM" private
              topOffset "0" private
            }
          }
          WIDGET {
            NAME "PrimitiveForm"
            CLASS "XmForm"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XmForm"
            paneMinimum "50" private
            WIDGET {
              NAME "PrimitiveLabel"
              CLASS "XmLabel"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmLabel"
              x "10" private
              y "20" private
              alignment "XmALIGNMENT_BEGINNING" private
              labelString "Primitives:" private
              bottomAttachment "XmATTACH_NONE" private
              leftAttachment "XmATTACH_FORM" private
              leftOffset "0" private
              resizable "1" private
              rightAttachment "XmATTACH_NONE" private
              topAttachment "XmATTACH_FORM" private
              topOffset "0" private
            }
          }
          WIDGET {
            NAME "DialogForm"
            CLASS "XmForm"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XmForm"
            paneMinimum "50" private
            WIDGET {
              NAME "DialogLabel"
              CLASS "XmLabel"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmLabel"
              x "10" private
              y "20" private
              alignment "XmALIGNMENT_BEGINNING" private
              labelString "Dialogs:" private
              bottomAttachment "XmATTACH_NONE" private
              leftAttachment "XmATTACH_FORM" private
              leftOffset "0" private
              resizable "1" private
              rightAttachment "XmATTACH_NONE" private
              topAttachment "XmATTACH_FORM" private
              topOffset "0" private
            }
          }
        }
      }
    }
  }
}
