WIDGET {
  NAME "OrderWindow"
  CLASS "ApplicationShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 305 LONG LicView height 430 "
  title "Are you hungry?" public
  WIDGET {
    NAME "rowColumn_1"
    CLASS "XmRowColumn"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    height "137" private
    width "217" private
    x "10" private
    y "10" private
    helpCallback "helpDialog" manage
    WIDGET {
      NAME "rowColumn_2"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      height "16" private
      width "66" private
      x "20" private
      y "10" private
      orientation "XmHORIZONTAL" private
      WIDGET {
        NAME "product_link"
        CLASS "@SecondInterface"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "130" private
        y "40" private
      }
      WIDGET {
        NAME "credit_card_link"
        CLASS "@FirstInterface"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "10" private
        y "0" private
      }
    }
    WIDGET {
      NAME "rowColumn"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      orientation "XmHORIZONTAL" private
      packing "XmPACK_COLUMN" private
      WIDGET {
        NAME "apply_button"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        labelString "Apply" public
        activateCallback "do_order" method
      }
      WIDGET {
        NAME "close_button"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        labelString "Close" public
        activateCallback "do_close" method
      }
      WIDGET {
        NAME "help_button"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        labelString "Help" public
        activateCallback "helpDialog" manage
      }
    }
    WIDGET {
      NAME "helpDialog"
      CLASS "XmCreateInformationDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      dialogTitle "A little help." public
      messageString "If you want a Burger, click the Burger button.
To order a Pizza, click the Pizza button.
Choose a credit card and press Apply to order.
Click on Close button to exit the application." public
      okLabelString "Close" public
    }
  }
}
