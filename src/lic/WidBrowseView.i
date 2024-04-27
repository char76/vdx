WIDGET {
  NAME "WidBrowseView"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 293 LONG LicView height 556 "
  DESCRIPTION "TopLevelShell"
  iconPixmap "BrowserLogo.xpm" load
  WIDGET {
    NAME "widBrowseMainWindow"
    CLASS "XmMainWindow"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "38"
    VIEWDATA ""
    DESCRIPTION "XmMainWindow"
    height "370" private
    width "333" private
    x "100" private
    y "80" private
    WIDGET {
      NAME "widBrowseMenuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "LONG LicView width 245 LONG LicView height 421 "
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
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
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
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
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
        NAME "createButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        labelString "Create" public
        mnemonic "C" public
        subMenuId "" private
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
    WIDGET {
      NAME "widBrowseForm"
      CLASS "XmForm"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmForm"
      height "340" private
      width "333" private
      x "10" private
      y "20" private
      WIDGET {
        NAME "quickHelp"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "20" private
        y "310" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "The quick help line." public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "1" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
      }
      WIDGET {
        NAME "treeFrame"
        CLASS "XmFrame"
        MANAGED "TRUE"
        QUICKHELP "Tree View of a widget."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmFrame"
        height "313" private
        width "325" private
        x "30" private
        y "20" private
        shadowThickness "0" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomOffset "4" private
        bottomWidget "quickHelp" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "4" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "4" private
        topAttachment "XmATTACH_FORM" private
        topOffset "4" private
      }
    }
  }
}
