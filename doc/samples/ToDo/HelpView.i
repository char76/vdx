WIDGET {
  NAME "HelpView"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 318 LONG LicView height 500 "
  DESCRIPTION "TopLevelShell"
  title "ToDo - Help View" public
  WIDGET {
    NAME "form_1"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    DESCRIPTION "XmForm"
    height "325" private
    width "400" private
    x "50" private
    y "80" private
    WIDGET {
      NAME "scrolledWindow_1"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmScrolledWindow"
      height "269" private
      width "390" private
      x "10" private
      y "10" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "5" private
      bottomWidget "separator_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      topAttachment "XmATTACH_FORM" private
      topOffset "5" private
      WIDGET {
        NAME "text"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "70" private
        y "30" private
        cursorPositionVisible "0" private
        editMode "XmMULTI_LINE_EDIT" private
        editable "0" private
        fontList "-adobe-times-medium-r-normal--14-140-75-75-p-74-iso8859-1" private
        scrollHorizontal "0" private
        wordWrap "1" private
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
      x "20" private
      y "290" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "5" private
      bottomWidget "pushButton_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
    WIDGET {
      NAME "pushButton_1"
      CLASS "XmPushButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmPushButton"
      width "100" private
      x "150" private
      y "300" private
      fontList "-adobe-new century schoolbook-bold-r-normal--12-120-75-75-p-0-iso8859-1" private
      labelString "Close" public
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "5" private
      leftAttachment "XmATTACH_POSITION" private
      leftOffset "-50" private
      leftPosition "50" private
      activateCallback "close_window" method
    }
  }
}
