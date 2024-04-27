WIDGET {
  NAME "SecondInterface"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 200 LONG LicView height 300 "
  WIDGET {
    NAME "rowColumn"
    CLASS "XmRowColumn"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    WIDGET {
      NAME "burger_toggle"
      CLASS "XmToggleButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "0" private
      labelString "Burger" public
      valueChangedCallback "product_value_changed" method
    }
    WIDGET {
      NAME "pizza_toggle"
      CLASS "XmToggleButton"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "0" private
      labelString "Pizza" public
      valueChangedCallback "product_value_changed" method
    }
  }
}
