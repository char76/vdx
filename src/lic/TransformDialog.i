WIDGET {
  NAME "TransformDialog"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  WIDGET {
    NAME "messageBox"
    CLASS "XmMessageBox"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "47"
    VIEWDATA ""
    DESCRIPTION "XmMessageBox"
    dialogTitle "Transform Widget Class" public
    messageString "Do you want to change the widget class?" public
    okLabelString "Transform" private
    cancelCallback "do_cancel" method
    okCallback "do_ok" method
    WIDGET {
      NAME "widgetClassOptionMenu"
      CLASS "XmCreateOptionMenu"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmCreateOptionMenu"
      labelString "New Widget Class:" public
      subMenuId "pulldownMenu" private
      WIDGET {
        NAME "pulldownMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "150" private
        y "10" private
        numColumns "4" private
        orientation "XmVERTICAL" private
        packing "XmPACK_COLUMN" private
        WIDGET {
          NAME "pushButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
        }
      }
    }
  }
}
