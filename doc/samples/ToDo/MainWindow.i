WIDGET {
  NAME "MainWindow"
  CLASS "ApplicationShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 350 LONG LicView height 515 "
  DESCRIPTION "ApplicationShell"
  buttonFontList "-adobe-new century schoolbook-bold-r-normal--12-120-75-75-p-0-iso8859-1" public
  labelFontList "-adobe-new century schoolbook-bold-r-normal--12-120-75-75-p-0-iso8859-1" public
  textFontList "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1" public
  title "ToDo List - Contents View" public
  WIDGET {
    NAME "form_1"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    DESCRIPTION "XmForm"
    height "330" private
    width "400" private
    x "260" private
    y "130" private
    helpCallback "help_me" method
    WIDGET {
      NAME "scrolledWindow_1"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XmScrolledWindow"
      height "274" private
      width "390" private
      x "10" private
      y "10" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomWidget "separator_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_FORM" private
      topOffset "5" private
      WIDGET {
        NAME "list"
        CLASS "XmList"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmList"
        scrollBarDisplayPolicy "XmSTATIC" private
        defaultActionCallback "list_double_click" method
      }
    }
    WIDGET {
      NAME "rowColumn_1"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "LONG LicView width 200 LONG LicView height 300 BOOLEAN TreeNodeView WithChildren TRUE "
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
        NAME "newButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "20" private
        y "0" private
        labelString "New" public
        activateCallback "new_item" method
      }
      WIDGET {
        NAME "detailButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "20" private
        y "0" private
        labelString "Detail" public
        activateCallback "show_item" method
      }
      WIDGET {
        NAME "delButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "10" private
        y "0" private
        labelString "Delete" public
        activateCallback "delete_item" method
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
  }
}
