WIDGET {
  NAME "ToolBoxSample"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  WIDGET {
    NAME "mainWindow_1"
    CLASS "XmMainWindow"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    DESCRIPTION "XmMainWindow"
    height "220" private
    width "420" private
    x "450" private
    y "300" private
    WIDGET {
      NAME "menuBar_1"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMenuBar"
      x "30" private
      y "0" private
      WIDGET {
        NAME "File"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        subMenuId "pulldownMenu" private
      }
      WIDGET {
        NAME "pulldownMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "Exit"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          activateCallback "do_exit" method
        }
      }
    }
    WIDGET {
      NAME "form"
      CLASS "XmForm"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmForm"
      height "100" private
      width "180" private
      x "150" private
      y "50" private
      WIDGET {
        NAME "toolBox"
        CLASS "XfeToolBox"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XfeToolBox"
        usePreferredHeight "1" private
        usePreferredWidth "0" private
        bottomAttachment "XmATTACH_NONE" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "0" private
        resizable "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "0" private
        topAttachment "XmATTACH_FORM" private
        topOffset "0" private
        WIDGET {
          NAME "xfeToolBar"
          CLASS "XfeToolBar"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
          DESCRIPTION "XfeToolBar"
          x "0" private
          y "0" private
          buttonLayout "button_label_on_right" private
          WIDGET {
            NAME "xfeButton"
            CLASS "XfeButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XfeButton"
            x "0" private
            y "0" private
            labelString "Start" public
            pixmap "foo.xpm" include
            activateCallback "run" method
          }
          WIDGET {
            NAME "xfeButton_3"
            CLASS "XfeButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XfeButton"
            x "0" private
            y "0" private
            labelString "Stop" public
            pixmap "foo.xpm" include
            activateCallback "stop" method
          }
        }
        WIDGET {
          NAME "xfeToolBar_1"
          CLASS "XfeToolBar"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XfeToolBar"
          x "0" private
          y "0" private
          buttonLayout "button_label_on_bottom" private
          radioBehavior "1" private
          WIDGET {
            NAME "xfeButton_3_1"
            CLASS "XfeButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XfeButton"
            x "0" private
            y "0" private
            armed "1" private
            labelString "Low" public
            pixmap "foo.xpm" include
            activateCallback "lowSpeed" method
          }
          WIDGET {
            NAME "xfeButton_3_2"
            CLASS "XfeButton"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XfeButton"
            x "0" private
            y "0" private
            labelString "High" public
            pixmap "foo.xpm" include
            activateCallback "highSpeed" method
          }
        }
      }
      WIDGET {
        NAME "text"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "0" private
        y "0" private
        bottomAttachment "XmATTACH_WIDGET" private
        bottomOffset "0" private
        bottomWidget "progress" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "0" private
        resizable "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "0" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "0" private
        topWidget "toolBox" private
      }
      WIDGET {
        NAME "progress"
        CLASS "XfeProgressBar"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XfeProgressBar"
        height "15" private
        barColor "CornflowerBlue" private
        labelString " " public
        shadowType "XmSHADOW_OUT" private
        usePreferredHeight "0" private
        usePreferredWidth "0" private
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "0" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "0" private
        resizable "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "0" private
        topAttachment "XmATTACH_NONE" private
      }
    }
  }
}
