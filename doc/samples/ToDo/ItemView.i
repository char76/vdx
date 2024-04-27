WIDGET {
  NAME "ItemView"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 448 LONG LicView height 379 "
  DESCRIPTION "TopLevelShell"
  buttonFontList "-adobe-new century schoolbook-bold-r-normal--12-120-75-75-p-0-iso8859-1" private
  labelFontList "-adobe-new century schoolbook-bold-r-normal--12-120-75-75-p-0-iso8859-1" private
  textFontList "-adobe-courier-medium-r-normal--12-120-75-75-m-70-iso8859-1_fmath" private
  title "ToDo Item - Detail View" public
  WIDGET {
    NAME "form_1"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
    DESCRIPTION "XmForm"
    height "330" private
    width "400" private
    x "260" private
    y "130" private
    helpCallback "help_me" method
    WIDGET {
      NAME "rowColumn_1"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmRowColumn"
      height "31" private
      width "390" private
      x "10" private
      y "270" private
      entryAlignment "XmALIGNMENT_CENTER" private
      marginHeight "5" private
      marginWidth "5" private
      orientation "XmHORIZONTAL" private
      packing "XmPACK_COLUMN" private
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "5" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      WIDGET {
        NAME "okButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "20" private
        y "0" private
        labelString "OK" public
        activateCallback "save_and_close" method
      }
      WIDGET {
        NAME "cancelButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "10" private
        y "0" private
        labelString "Cancel" public
        activateCallback "close_view" method
      }
      WIDGET {
        NAME "helpButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelString "Help" public
        activateCallback "help_me" method
      }
    }
    WIDGET {
      NAME "separator_1"
      CLASS "XmSeparator"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmSeparator"
      height "10" private
      width "398" private
      x "1" private
      y "284" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomWidget "rowColumn_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
    WIDGET {
      NAME "label_1"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmLabel"
      height "30" private
      x "10" private
      y "10" private
      labelString "Title:" public
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      topAttachment "XmATTACH_FORM" private
      topOffset "5" private
    }
    WIDGET {
      NAME "titleText"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmText"
      width "346" private
      x "90" private
      y "10" private
      maxLength "32" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "5" private
      leftWidget "label_1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_FORM" private
      topOffset "5" private
    }
    WIDGET {
      NAME "scrolledWindow_2"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmScrolledWindow"
      height "234" private
      width "269" private
      x "10" private
      y "50" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "separator_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_WIDGET" private
      rightOffset "5" private
      rightWidget "frame_1" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "titleText" private
      WIDGET {
        NAME "text"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        editMode "XmMULTI_LINE_EDIT" private
        maxLength "512" private
        scrollHorizontal "0" private
        wordWrap "1" private
      }
    }
    WIDGET {
      NAME "frame_1"
      CLASS "XmFrame"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmFrame"
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "5" private
      topWidget "titleText" private
      WIDGET {
        NAME "radioBox_1"
        CLASS "XmCreateRadioBox"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreateRadioBox"
        height "143" private
        width "103" private
        x "10" private
        y "0" private
        WIDGET {
          NAME "veryHighToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "10" private
          y "10" private
          labelString "very high" public
          set "XmSET" private
        }
        WIDGET {
          NAME "highToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "high" public
        }
        WIDGET {
          NAME "middleToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "middle" public
        }
        WIDGET {
          NAME "lowToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "low" public
        }
        WIDGET {
          NAME "niceToHaveToggle"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          labelString "nice to have" public
        }
      }
      WIDGET {
        NAME "label"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        labelString "Priority" public
        childType "XmFRAME_TITLE_CHILD" private
      }
    }
  }
}
