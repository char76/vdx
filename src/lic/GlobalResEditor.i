WIDGET {
  NAME "GlobalResEditor"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  WIDGET {
    NAME "form"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "46"
    VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
    DESCRIPTION "XmForm"
    height "247" private
    width "502" private
    x "420" private
    y "340" private
    WIDGET {
      NAME "menuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE LONG LicView width 200 LONG LicView height 300 "
      DESCRIPTION "XmCreateMenuBar"
      height "31" private
      width "500" private
      x "0" private
      y "0" private
      menuHelpWidget "helpMenuButton" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      topAttachment "XmATTACH_FORM" private
      topOffset "1" private
      WIDGET {
        NAME "fileMenuButton"
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
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "fileImport"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Import a file at cursor position."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>i" public
          acceleratorText "^I" public
          labelString "Import" public
          mnemonic "I" public
          activateCallback "fileImportDialog" manage
        }
        WIDGET {
          NAME "fileApply"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Update all WYSIWYG views."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>a" public
          acceleratorText "^A" public
          labelString "Apply" public
          mnemonic "A" public
          activateCallback "do_apply" method
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
          NAME "fileClose"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Close the window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>C" public
          acceleratorText "^C" public
          labelString "Close" public
          mnemonic "C" public
          activateCallback "doExit" method
        }
      }
      WIDGET {
        NAME "editMenuButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Edit" public
        mnemonic "E" public
        subMenuId "editMenu" private
      }
      WIDGET {
        NAME "editMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "editCut"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Move selected text to clipboard."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Shift<Key>osfDelete" public
          acceleratorText "^DEL" public
          labelString "Cut" public
          mnemonic "C" public
          activateCallback "cutText" method
        }
        WIDGET {
          NAME "editCopy"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Copy text to clipboard."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>osfInsert" public
          acceleratorText "^INS" public
          labelString "Copy" public
          mnemonic "o" public
          activateCallback "copyText" method
        }
        WIDGET {
          NAME "editPaste"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Insert text from clipboard."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Shift<Key>osfInsert" public
          acceleratorText "S-INS" public
          labelString "Paste" public
          mnemonic "P" public
          activateCallback "pasteText" method
        }
      }
      WIDGET {
        NAME "helpMenuButton"
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
          QUICKHELP "Help for the help system."
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
          QUICKHELP "Get help after a widget is clicked."
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
          QUICKHELP "Help on this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>F1" public
          acceleratorText "^F!" public
          labelString "On Window" public
          mnemonic "W" public
          activateCallback "helpMe" method
        }
      }
    }
    WIDGET {
      NAME "fileImportDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "21"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateFileSelectionDialog"
      x "140" private
      y "70" private
      autoUnmanage "1" private
      dialogTitle "Import" public
      okCallback "importFile" method
    }
    WIDGET {
      NAME "scrolledWindow"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmScrolledWindow"
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "0" private
      bottomWidget "quickHelpLabel" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "1" private
      leftWidget "toolsRowColumn" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "0" private
      topWidget "menuBar" private
      WIDGET {
        NAME "text"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Enter a text in resource file syntax."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        editMode "XmMULTI_LINE_EDIT" private
      }
    }
    WIDGET {
      NAME "quickHelpLabel"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmLabel"
      height "20" private
      width "490" private
      x "0" private
      y "210" private
      alignment "XmALIGNMENT_BEGINNING" private
      labelString "This is the Quick Help Line." public
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
    WIDGET {
      NAME "toolsRowColumn"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XmRowColumn"
      entryAlignment "XmALIGNMENT_CENTER" private
      entryVerticalAlignment "XmALIGNMENT_CENTER" private
      bottomAttachment "XmATTACH_NONE" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_NONE" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "0" private
      topWidget "menuBar" private
      WIDGET {
        NAME "fontChooserButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Open a font chooser for the selected font."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelPixmap "FontChooser.xpm" include
        labelString "F" public
        labelType "XmPIXMAP" private
        activateCallback "do_fontChooser" method
      }
      WIDGET {
        NAME "colorSelectButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Open a color selection for the selected color."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        labelPixmap "ColorSelect.xpm" include
        labelString "C" public
        labelType "XmPIXMAP" private
        activateCallback "do_ColorSelect" method
      }
      WIDGET {
        NAME "applyButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Apply changes to WYSIWYG view."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelPixmap "Apply.xpm" include
        labelString "A" public
        labelType "XmPIXMAP" private
        activateCallback "do_apply" method
      }
    }
  }
}
