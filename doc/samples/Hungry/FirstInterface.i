WIDGET {
  NAME "FirstInterface"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 200 LONG LicView height 300 "
  WIDGET {
    NAME "radioBox"
    CLASS "XmCreateRadioBox"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    WIDGET {
      NAME "amex_toggle"
      CLASS "XmToggleButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "0" private
      labelString "American Express" public
      valueChangedCallback "cc_value_changed" method
    }
    WIDGET {
      NAME "visa_toggle"
      CLASS "XmToggleButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "0" private
      labelString "Visa Card" public
      valueChangedCallback "cc_value_changed" method
    }
    WIDGET {
      NAME "master_toggle"
      CLASS "XmToggleButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "0" private
      labelString "Master Card" public
      valueChangedCallback "cc_value_changed" method
    }
  }
}
