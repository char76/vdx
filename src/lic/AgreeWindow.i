WIDGET {
  NAME "AgreeWindow"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  title "Agreement" private
  WIDGET {
    NAME "form_1"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    DESCRIPTION "XmForm"
    height "5828" private
    width "7800" private
    x "60" private
    y "110" private
    unitType "Xm100TH_FONT_UNITS" private
    WIDGET {
      NAME "scrolledWindow_1"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmScrolledWindow"
      height "4585" private
      width "7600" private
      x "150" private
      y "557" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "200" private
      bottomWidget "pushButton_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "100" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "100" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "50" private
      topWidget "label_1" private
      WIDGET {
        NAME "text_1"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "2166" private
        y "1000" private
        autoShowCursorPosition "0" private
        cursorPositionVisible "0" private
        editMode "XmMULTI_LINE_EDIT" private
        editable "0" private
        fontList "-adobe-courier-medium-r-normal--14-*-*-*-*-*-iso8859-1" private
        scrollHorizontal "0" private
        wordWrap "1" private
      }
    }
    WIDGET {
      NAME "label_1"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmLabel"
      x "166" private
      y "142" private
      alignment "XmALIGNMENT_BEGINNING" private
      fontList "-adobe-helvetica-bold-r-normal--14-*-*-*-*-*-iso8859-1" public
      labelString "Do you agree to all the terms of following statement?" public
      leftAttachment "XmATTACH_FORM" private
      leftOffset "100" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "100" private
      topAttachment "XmATTACH_FORM" private
      topOffset "100" private
    }
    WIDGET {
      NAME "pushButton_1"
      CLASS "XmPushButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmPushButton"
      height "414" private
      width "1500" private
      x "166" private
      y "5285" private
      labelString "Agree" public
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "200" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "200" private
      activateCallback "do_agree" method
    }
    WIDGET {
      NAME "pushButton_1_1"
      CLASS "XmPushButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmPushButton"
      height "414" private
      width "1500" private
      x "6166" private
      y "5285" private
      labelString "Don't agree" public
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "200" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "200" private
      activateCallback "do_not_agree" method
    }
  }
}
