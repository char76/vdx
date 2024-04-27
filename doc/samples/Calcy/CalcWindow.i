WIDGET {
  NAME "CalcWindow"
  CLASS "ApplicationShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  title "Calcy" public
  WIDGET {
    NAME "rowColumn_1"
    CLASS "XmRowColumn"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    height "133" private
    width "144" private
    x "290" private
    y "140" private
    WIDGET {
      NAME "number1_text"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      background "#e4b4af" private
      x "20" private
      y "10" private
    }
    WIDGET {
      NAME "number2_text"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      background "#e4b4af" private
      x "0" private
      y "0" private
    }
    WIDGET {
      NAME "add_button"
      CLASS "XmPushButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "20" private
      y "40" private
      alignment "XmALIGNMENT_BEGINNING" private
      labelString "Add" public
      activateCallback "do_addition" method
    }
    WIDGET {
      NAME "result_text"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "40" private
      cursorPositionVisible "0" private
      editable "0" private
    }
  }
}
