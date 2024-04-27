WIDGET {
  NAME "MenuEdit"
  CLASS "TopLevelShell"
  MANAGED "FALSE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  iconPixmap "MenuEdit.xpm" load
  WIDGET {
    NAME "mainWindow"
    CLASS "XmMainWindow"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "12"
    VIEWDATA ""
    DESCRIPTION "XmMainWindow"
    WIDGET {
      NAME "form"
      CLASS "XmForm"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XmForm"
      height "360" private
      width "410" private
      x "0" private
      y "31" private
      WIDGET {
        NAME "Label1"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "110" private
        y "0" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Children" public
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "rowColumn_1" private
        topAttachment "XmATTACH_FORM" private
        topOffset "5" private
      }
      WIDGET {
        NAME "Label2"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "10" private
        y "180" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Order" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "5" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "10" private
        topWidget "rowColumn_1" private
      }
      WIDGET {
        NAME "ArrowUp"
        CLASS "XmArrowButton"
        MANAGED "TRUE"
        QUICKHELP "Move selected widget."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmArrowButton"
        height "30" private
        width "30" private
        x "10" private
        y "200" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "6" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "Label2" private
        activateCallback "moveUp" method
      }
      WIDGET {
        NAME "ArrowDown"
        CLASS "XmArrowButton"
        MANAGED "TRUE"
        QUICKHELP "Move selected widget."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmArrowButton"
        height "30" private
        width "30" private
        x "40" private
        y "200" private
        arrowDirection "XmARROW_DOWN" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "1" private
        leftWidget "ArrowUp" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "Label2" private
        activateCallback "moveDown" method
      }
      WIDGET {
        NAME "iconViewFrame"
        CLASS "XmFrame"
        MANAGED "TRUE"
        QUICKHELP "Children of the menu widget."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmFrame"
        shadowThickness "0" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomOffset "3" private
        bottomWidget "quickHelp" private
        leftAttachment "XmATTACH_WIDGET" private
        leftOffset "5" private
        leftWidget "rowColumn_1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "5" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "3" private
        topWidget "Label1" private
      }
      WIDGET {
        NAME "rowColumn_1"
        CLASS "XmRowColumn"
        MANAGED "TRUE"
        QUICKHELP "Create a new child of menu widget."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmRowColumn"
        height "183" private
        width "90" private
        x "5" private
        y "5" private
        marginHeight "0" private
        marginWidth "0" private
        numColumns "1" private
        orientation "XmVERTICAL" private
        packing "XmPACK_TIGHT" private
        resizeHeight "1" private
        resizeWidth "1" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "5" private
        resizable "0" private
        topAttachment "XmATTACH_FORM" private
        topOffset "5" private
        WIDGET {
          NAME "Label3"
          CLASS "XmLabel"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmLabel"
          x "249" private
          y "127" private
          alignment "XmALIGNMENT_BEGINNING" private
          labelString "Add item" public
        }
        WIDGET {
          NAME "addLabelButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          height "30" private
          width "100" private
          x "249" private
          y "147" private
          labelString "Label" private
          marginHeight "4" private
          marginWidth "4" private
          activateCallback "addLabel" method
        }
        WIDGET {
          NAME "addPushButtonLazy"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          height "30" private
          width "100" private
          x "249" private
          y "177" private
          labelString "PushButton" private
          marginHeight "4" private
          marginWidth "4" private
          activateCallback "addPushbutton" method
        }
        WIDGET {
          NAME "addToggleButtonButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          height "30" private
          width "100" private
          x "249" private
          y "207" private
          labelString "ToggleButton" private
          marginHeight "4" private
          marginWidth "4" private
          activateCallback "addToggleButton" method
        }
        WIDGET {
          NAME "addSeparatorButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          height "30" private
          width "100" private
          x "249" private
          y "237" private
          labelString "Separator" private
          marginHeight "4" private
          marginWidth "4" private
          activateCallback "addSeparator" method
        }
        WIDGET {
          NAME "addSubMenuButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          height "30" private
          width "100" private
          x "249" private
          y "267" private
          labelString "SubMenu" private
          marginHeight "4" private
          marginWidth "4" private
          activateCallback "addSubMenu" method
        }
      }
      WIDGET {
        NAME "quickHelp"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "10" private
        y "310" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "This is a Quick Help Line." public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "1" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
      }
    }
    WIDGET {
      NAME "widBrowseMenuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "LONG LicView width 245 LONG LicView height 421 BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XmCreateMenuBar"
      x "20" private
      y "10" private
      menuHelpWidget "helpButton" private
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
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "loadButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Load selected widget into browser."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>l" public
          acceleratorText "^L" public
          labelString "Load" public
          mnemonic "L" public
          activateCallback "do_load" method
        }
        WIDGET {
          NAME "loadParentButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>p" public
          acceleratorText "^P" public
          labelString "Load Parent" public
          mnemonic "P" private
          activateCallback "do_loadParent" method
        }
        WIDGET {
          NAME "closeButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Close this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>c" private
          acceleratorText "^C" private
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
        mnemonic "V" private
        subMenuId "viewMenu" private
      }
      WIDGET {
        NAME "viewMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "smallIconButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Display small icons in Tree View."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>s" public
          acceleratorText "^S" public
          labelString "Small Icons" public
          mnemonic "S" public
          valueChangedCallback "do_smallIcon" method
        }
        WIDGET {
          NAME "withIconButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Display icons Tree View."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>I" public
          acceleratorText "^I" public
          labelString "With Icons" public
          mnemonic "I" public
          valueChangedCallback "do_withIcon" method
        }
        WIDGET {
          NAME "withClassNameButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Display class names of widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>n" public
          acceleratorText "^N" public
          labelString "With Class Names" public
          mnemonic "N" public
          valueChangedCallback "do_withClassName" method
        }
      }
      WIDGET {
        NAME "widgetButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Widget" public
        mnemonic "W" public
        subMenuId "widgetMenu" private
      }
      WIDGET {
        NAME "widgetMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        mapCallback "do_widgetMenuMap" method
        WIDGET {
          NAME "editButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show Widget Resource Editor for selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "E" public
          labelString "Edit" public
          mnemonic "E" public
        }
        WIDGET {
          NAME "browseButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show Browser for selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "B" public
          labelString "Browse" public
          mnemonic "B" public
        }
        WIDGET {
          NAME "menuEditButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show Menu Ediotor for selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "M" public
          labelString "Menu Editor" public
          mnemonic "M" public
        }
        WIDGET {
          NAME "cutButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Copy selection to clipboard and delete selection."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "X" public
          labelString "Cut" public
          mnemonic "u" public
        }
        WIDGET {
          NAME "copyButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Copy selection to clipboard."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "C" public
          labelString "Copy" public
          mnemonic "C" public
        }
        WIDGET {
          NAME "pasteButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Paste clipboard contents to selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "V" public
          labelString "Paste" public
          mnemonic "P" public
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
          NAME "deleteButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Delete selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "DEL" public
          labelString "Delete" public
          mnemonic "D" public
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
        subMenuId "helpMenu" private
      }
      WIDGET {
        NAME "helpMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "onHelp"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help on help system."
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
          QUICKHELP "Get help after clicking in a window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Context" private
          mnemonic "C" public
          activateCallback "do_onContext" method
        }
        WIDGET {
          NAME "onWidResEditor"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help for this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>F1" public
          acceleratorText "^F1" public
          labelString "On Window" private
          mnemonic "W" private
          activateCallback "do_help" method
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
        WIDGET {
          NAME "automaticLoadButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "LONG LicView width 200 LONG LicView height 300 "
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>t" public
          acceleratorText "^T" public
          labelString "Automatic Load" public
          mnemonic "t" public
          valueChangedCallback "do_automaticLoad" method
        }
      }
    }
  }
}
