WIDGET {
  NAME "MLXHelp"
  CLASS "TopLevelShell"
  MANAGED "FALSE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 349 LONG LicView height 585 "
  defaultFontList "-adobe-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1" public
  title "Help System" public
  WIDGET {
    NAME "form"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA "LONG LicView width 283 LONG LicView height 519 BOOLEAN TreeNodeView WithChildren TRUE "
    height "345" private
    width "585" private
    x "0" private
    y "0" private
    WIDGET {
      NAME "titleDialog"
      CLASS "XmCreatePromptDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN WidgetView showDialog FALSE "
      x "150" private
      y "340" private
      dialogStyle "XmDIALOG_FULL_APPLICATION_MODAL" private
      dialogTitle "Change Section Title" public
      selectionLabelString "Title:" public
      mapCallback "titleDialogMap" method
      okCallback "titleChanged" method
    }
    WIDGET {
      NAME "identDialog"
      CLASS "XmCreatePromptDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN unnamed showDialog FALSE BOOLEAN WidgetView showDialog FALSE "
      x "150" private
      y "340" private
      dialogStyle "XmDIALOG_FULL_APPLICATION_MODAL" private
      dialogTitle "Change Identifier" private
      selectionLabelString "Identifier:" private
      mapCallback "identDialogMap" method
      okCallback "identChanged" method
    }
    WIDGET {
      NAME "findDialog"
      CLASS "XmCreatePromptDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE BOOLEAN WidgetView showDialog FALSE "
      x "230" private
      y "60" private
      autoUnmanage "0" private
      cancelLabelString "Close" public
      childPlacement "XmPLACE_BELOW_SELECTION" private
      dialogTitle "Find Dialog" public
      okLabelString "Find" public
      selectionLabelString "Search for:" public
      cancelCallback "cancelFindDialog" method
      mapCallback "mapFindDialog" method
      okCallback "okFindDialog" method
      WIDGET {
        NAME "rowColumn_1"
        CLASS "XmRowColumn"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        height "100" private
        width "100" private
        x "110" private
        y "0" private
        WIDGET {
          NAME "findBeginToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "20" private
          y "60" private
          labelString "Search from the beginning" public
        }
        WIDGET {
          NAME "findCaseToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "10" private
          y "60" private
          labelString "Case sensitive" public
        }
      }
    }
    WIDGET {
      NAME "menuBar_1"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE LONG LicView width 313 LONG LicView height 477 "
      height "32" private
      width "583" private
      x "550" private
      y "230" private
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
        VIEWDATA "LONG LicView width 200 LONG LicView height 300 BOOLEAN TreeNodeView WithChildren TRUE "
        x "0" private
        y "0" private
        WIDGET {
          NAME "Save"
          CLASS "XmPushButton"
          MANAGED "FALSE"
          QUICKHELP "Save help file."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>s" public
          acceleratorText "^S" public
          labelString "Save" public
          mnemonic "S" public
          activateCallback "saveFile" method
        }
        WIDGET {
          NAME "exportLatex"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Export whole help document to a file."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>e" public
          acceleratorText "^e" public
          labelString "Export ..." public
          mnemonic "E" public
          activateCallback "exportDialog" manage
        }
        WIDGET {
          NAME "Exit"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Hide the help view."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "<Key>Escape" public
          acceleratorText "Esc" public
          labelString "Close" public
          mnemonic "C" public
          activateCallback "exitMLXHelp" method
        }
      }
      WIDGET {
        NAME "Edit"
        CLASS "XmCascadeButton"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        labelString "Edit" public
        mnemonic "E" public
        subMenuId "EditMenu" private
      }
      WIDGET {
        NAME "EditMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
      }
      WIDGET {
        NAME "View"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        labelString "View" public
        mnemonic "V" public
        subMenuId "ViewMenu" private
      }
      WIDGET {
        NAME "ViewMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        WIDGET {
          NAME "contentsButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show or hide the contents tree view."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>c" public
          acceleratorText "^C" public
          labelString "Contents" public
          mnemonic "C" public
          valueChangedCallback "contentsButtonChanged" method
        }
      }
      WIDGET {
        NAME "Navigate"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        labelString "Navigate" public
        mnemonic "N" public
        subMenuId "NavigateMenu" private
      }
      WIDGET {
        NAME "NavigateMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        WIDGET {
          NAME "findButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Find a specific string in the help document."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>f" public
          acceleratorText "^F" public
          labelString "Find ..." public
          mnemonic "d" private
          activateCallback "findDialog" manage
        }
        WIDGET {
          NAME "historyBack"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Back to the last section in the history."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>Left" public
          acceleratorText "^Left" public
          labelString "History Backward" public
          mnemonic "B" public
          activateCallback "do_backward" method
        }
        WIDGET {
          NAME "historyForward"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Forward in the history."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>Right" public
          acceleratorText "^Right" public
          labelString "History Forward" public
          mnemonic "F" public
          activateCallback "do_forward" method
        }
        WIDGET {
          NAME "lastSection"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "To the preceding section in the contents tree."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>Prior" public
          acceleratorText "^Page up" public
          labelString "Last Section" public
          mnemonic "L" public
          activateCallback "do_lastSection" method
        }
        WIDGET {
          NAME "nextSection"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "To the next section in the contents tree."
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>Next" public
          acceleratorText "^Page down" public
          labelString "Next Section" public
          mnemonic "N" public
          activateCallback "do_nextSection" method
        }
      }
    }
    WIDGET {
      NAME "backButton"
      CLASS "XmArrowButton"
      MANAGED "TRUE"
      QUICKHELP "Back in the history."
      HELPID "-1"
      VIEWDATA ""
      height "30" private
      width "30" private
      x "5" private
      y "40" private
      arrowDirection "XmARROW_LEFT" private
      bottomAttachment "XmATTACH_NONE" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "menuBar_1" private
      activateCallback "do_backward" method
    }
    WIDGET {
      NAME "panedWindow"
      CLASS "XmPanedWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      orientation "XmHORIZONTAL" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "quickHelp" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "backButton" private
      WIDGET {
        NAME "frame"
        CLASS "XmFrame"
        MANAGED "TRUE"
        QUICKHELP "The contents tree. Click the tree node."
        HELPID "-1"
        VIEWDATA ""
        height "244" private
        width "200" private
        x "3" private
        y "3" private
      }
      WIDGET {
        NAME "scrolledWindow"
        CLASS "XmScrolledWindow"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        x "90" private
        y "130" private
        WIDGET {
          NAME "text"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP "Help text of the selected section. Click the hypertext links."
          HELPID "-1"
          VIEWDATA ""
          x "50" private
          y "30" private
          editMode "XmMULTI_LINE_EDIT" private
          fontList "-adobe-times-medium-r-normal--14-*-*-*-*-*-iso8859-1" public
          scrollHorizontal "0" private
          wordWrap "1" private
          modifyVerifyCallback "textValueChanged" method
        }
      }
    }
    WIDGET {
      NAME "forwardButton"
      CLASS "XmArrowButton"
      MANAGED "TRUE"
      QUICKHELP "Forward in the history."
      HELPID "-1"
      VIEWDATA ""
      height "30" private
      width "30" private
      x "40" private
      y "40" private
      arrowDirection "XmARROW_RIGHT" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "5" private
      leftWidget "backButton" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "menuBar_1" private
      activateCallback "do_forward" method
    }
    WIDGET {
      NAME "titleLabel"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      height "30" private
      x "117" private
      y "40" private
      alignment "XmALIGNMENT_END" private
      labelString "Title:" public
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "10" private
      leftWidget "forwardButton" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "menuBar_1" private
    }
    WIDGET {
      NAME "titleText"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP "The title of the selected section."
      HELPID "-1"
      VIEWDATA ""
      width "469" private
      x "121" private
      y "34" private
      autoShowCursorPosition "0" private
      cursorPositionVisible "0" private
      editable "0" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "1" private
      leftWidget "titleLabel" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "2" private
      topWidget "menuBar_1" private
    }
    WIDGET {
      NAME "quickHelp"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      height "20" private
      width "583" private
      x "20" private
      y "310" private
      alignment "XmALIGNMENT_BEGINNING" private
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
    WIDGET {
      NAME "exportDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE LONG LicView width 200 LONG LicView height 300 "
      x "100" private
      y "50" private
      autoUnmanage "1" private
      dialogTitle "Export" public
      okLabelString "Export" public
      mapCallback "mapExportDialog" method
      okCallback "do_export" method
      WIDGET {
        NAME "exportType"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "70" private
        y "240" private
        labelString "Export Format:" public
        subMenuId "exportPulldown" private
      }
      WIDGET {
        NAME "exportPulldown"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "90" private
        y "10" private
        entryCallback "exportTypeChanged" method
        WIDGET {
          NAME "plainText"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          labelString "Plain Text" public
        }
        WIDGET {
          NAME "latexFormat"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          labelString "Latex" public
        }
        WIDGET {
          NAME "htmlText"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          labelString "HTML" public
        }
      }
    }
  }
}
