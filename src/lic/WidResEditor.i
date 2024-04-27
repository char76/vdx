WIDGET {
  NAME "WidResEditor"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 353 LONG LicView height 573 "
  DESCRIPTION "TopLevelShell"
  WIDGET {
    NAME "widResMainWindow"
    CLASS "XmMainWindow"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "3"
    VIEWDATA ""
    DESCRIPTION "XmMainWindow"
    height "446" private
    width "537" private
    x "330" private
    y "330" private
    WIDGET {
      NAME "widResMenuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE LONG LicView width 346 LONG LicView height 572 "
      DESCRIPTION "XmCreateMenuBar"
      x "0" private
      y "0" private
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
          QUICKHELP "Load selected widget into editor."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>l" public
          acceleratorText "^L" private
          labelString "Load" public
          mnemonic "L" public
          activateCallback "do_load" method
        }
        WIDGET {
          NAME "applyButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Apply changes to Wysiwyg View."
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
          NAME "applyToButton"
          CLASS "XmCascadeButton"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmCascadeButton"
          x "0" private
          y "0" private
          labelString "Apply To" public
          mnemonic "T" public
          subMenuId "applyToMenu" private
        }
        WIDGET {
          NAME "applyToMenu"
          CLASS "XmCreatePulldownMenu"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XmCreatePulldownMenu"
          x "0" private
          y "0" private
          WIDGET {
            NAME "selectedButton"
            CLASS "XmPushButton"
            MANAGED "TRUE"
            QUICKHELP "Apply changes to selected widgets."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmPushButton"
            x "0" private
            y "0" private
            labelString "Selected Widgets" public
            mnemonic "S" public
          }
          WIDGET {
            NAME "meAndSiblingsButton"
            CLASS "XmPushButton"
            MANAGED "TRUE"
            QUICKHELP "Apply to current widget and its siblings."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmPushButton"
            x "0" private
            y "0" private
            labelString "Me And Siblings" public
            mnemonic "i" public
          }
          WIDGET {
            NAME "meAndChildrenButton"
            CLASS "XmPushButton"
            MANAGED "TRUE"
            QUICKHELP "Apply to current widget and its children."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmPushButton"
            x "0" private
            y "0" private
            labelString "Me And Children" public
            mnemonic "C" public
          }
          WIDGET {
            NAME "meAndAllButton"
            CLASS "XmPushButton"
            MANAGED "TRUE"
            QUICKHELP "Apply to all widgets of the interface."
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmPushButton"
            x "0" private
            y "0" private
            labelString "All Widgets of Interface" public
            mnemonic "A" public
          }
        }
        WIDGET {
          NAME "unhandledResources"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Other Resources ..." public
          mnemonic "U" public
          activateCallback "messageDialog" manage
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
          NAME "closeButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Close this window."
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
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        radioBehavior "1" private
        entryCallback "do_viewChanged" method
        WIDGET {
          NAME "coreButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show core resources of the current widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>1" public
          acceleratorText "^1" private
          labelString "Core" public
          mnemonic "C" public
          set "XmSET" private
        }
        WIDGET {
          NAME "specificButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show widget specific resources."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>2" public
          acceleratorText "^2" public
          labelString "Specific" public
          mnemonic "S" public
        }
        WIDGET {
          NAME "constraintButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show parent depending contraint resources."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>3" public
          acceleratorText "^3" public
          labelString "Constraints" public
          mnemonic "o" public
        }
        WIDGET {
          NAME "callbackButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Show callback resources of current widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>4" public
          acceleratorText "^4" public
          labelString "Callbacks" public
          mnemonic "b" public
        }
        WIDGET {
          NAME "extraButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Extra settings for current widget."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>5" public
          acceleratorText "^5" public
          labelString "Extra" public
          mnemonic "E" public
        }
        WIDGET {
          NAME "userButton"
          CLASS "XmToggleButton"
          MANAGED "FALSE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>6" private
          acceleratorText "^6" private
          labelString "User" private
          mnemonic "U" private
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
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "automaticLoad"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Mark this editor as automatic loader."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>t" public
          acceleratorText "^T" public
          labelString "Automatic Load" public
          mnemonic "t" private
          valueChangedCallback "do_automaticLoad" method
        }
        WIDGET {
          NAME "withSource"
          CLASS "XmToggleButton"
          MANAGED "FALSE"
          QUICKHELP "Show source of resource value (private/public/..)."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "With Source" public
          mnemonic "S" private
          valueChangedCallback "do_withSource" method
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
          QUICKHELP "Get help by clicking in a window."
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
    }
    WIDGET {
      NAME "widResForm"
      CLASS "XmForm"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmForm"
      height "415" private
      width "537" private
      x "0" private
      y "16" private
      WIDGET {
        NAME "xlButtonBox_1"
        CLASS "XlButtonBox"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XlButtonBox"
        entryMarginHeight "5" private
        entryMarginWidth "10" private
        spacing "5" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomOffset "0" private
        bottomWidget "quickHelp" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
        WIDGET {
          NAME "applyButton2"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Apply changes to Wysiwyg View."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "Apply" public
          activateCallback "do_apply" method
        }
        WIDGET {
          NAME "closeButton2"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Close this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "20" private
          y "20" private
          labelString "Close" public
          activateCallback "do_close" method
        }
        WIDGET {
          NAME "helpButton2"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help for this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "50" private
          y "20" private
          labelString "Help" public
          activateCallback "do_help" method
        }
      }
      WIDGET {
        NAME "scrolledWindow_1"
        CLASS "XmScrolledWindow"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmScrolledWindow"
        height "336" private
        width "527" private
        x "20" private
        y "10" private
        scrollingPolicy "XmAUTOMATIC" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomWidget "xlButtonBox_1" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "5" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "5" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "1" private
        topWidget "categoryLabel" private
      }
      WIDGET {
        NAME "categoryLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "260" private
        y "0" private
        labelString "Category:" public
        leftAttachment "XmATTACH_FORM" private
        leftOffset "7" private
        topAttachment "XmATTACH_FORM" private
        topOffset "4" private
      }
      WIDGET {
        NAME "currentCategoryLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP "Display current view of widget resources."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "17" private
        width "120" private
        x "65" private
        y "4" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Core" private
        leftAttachment "XmATTACH_WIDGET" private
        leftWidget "categoryLabel" private
        topAttachment "XmATTACH_FORM" private
        topOffset "4" private
      }
      WIDGET {
        NAME "automaticLoadLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP "Display automatic load state of this editor."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "260" private
        y "0" private
        labelString "Automatic Load: On" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "5" private
        topAttachment "XmATTACH_FORM" private
        topOffset "4" private
      }
      WIDGET {
        NAME "quickHelp"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "260" private
        y "0" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "The quick help line." public
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "1" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "1" private
      }
    }
    WIDGET {
      NAME "messageDialog"
      CLASS "XmCreateMessageDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "48"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      DESCRIPTION "XmCreateMessageDialog"
      x "0" private
      y "0" private
      dialogTitle "Other Resources" public
      messageString "This list displays resources which are
not editable by VDX." private
      WIDGET {
        NAME "scrolledWindow"
        CLASS "XmScrolledWindow"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmScrolledWindow"
        x "0" private
        y "0" private
        WIDGET {
          NAME "list"
          CLASS "XmList"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmList"
          x "0" private
          y "0" private
          visibleItemCount "10" private
        }
      }
    }
  }
}
