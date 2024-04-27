WIDGET {
  NAME "MainWindow"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  iconName "Find Util - dtksh demo" private
  WIDGET {
    NAME "mainWindow"
    CLASS "XmMainWindow"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    DESCRIPTION "XmBulletinBoard"
    WIDGET {
      NAME "menuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMenuBar"
      x "0" private
      y "0" private
      WIDGET {
        NAME "cascadeButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "File" public
        mnemonic "F" public
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
          NAME "pushButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          accelerator "Ctrl<Key>x" public
          acceleratorText "Ctrl-x" public
          labelString "Exit" public
          mnemonic "x" public
          activateCallback "exit" method
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
      WIDGET {
        NAME "directory"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "0" private
        y "0" private
        bottomAttachment "XmATTACH_NONE" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "5" private
        resizable "1" private
        rightAttachment "XmATTACH_WIDGET" private
        rightOffset "5" private
        rightWidget "pushButton_1" private
        topAttachment "XmATTACH_FORM" private
        topOffset "5" private
      }
      WIDGET {
        NAME "pushButton_1"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelString "..." public
        rightAttachment "XmATTACH_FORM" private
        rightOffset "5" private
        topAttachment "XmATTACH_FORM" private
        topOffset "5" private
        activateCallback "fileSelectionDialog" manage
      }
      WIDGET {
        NAME "toFind"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "0" private
        y "0" private
        bottomAttachment "XmATTACH_NONE" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "5" private
        resizable "1" private
        rightAttachment "XmATTACH_WIDGET" private
        rightOffset "5" private
        rightWidget "pushButton_2" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "directory" private
      }
      WIDGET {
        NAME "result"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "0" private
        y "0" private
        editMode "XmMULTI_LINE_EDIT" private
        rows "10" private
        bottomAttachment "XmATTACH_FORM" private
        bottomOffset "5" private
        leftAttachment "XmATTACH_FORM" private
        leftOffset "5" private
        resizable "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "5" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "toFind" private
      }
      WIDGET {
        NAME "fileSelectionDialog"
        CLASS "XmCreateFileSelectionDialog"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
        DESCRIPTION "XmCreateFileSelectionDialog"
        x "0" private
        y "0" private
        autoUnmanage "1" private
        dialogTitle "Select Directory" public
        fileTypeMask "XmFILE_DIRECTORY" private
        okCallback "dirSelected" method
      }
      WIDGET {
        NAME "pushButton_2"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "0" private
        y "0" private
        labelString "Find" public
        bottomAttachment "XmATTACH_NONE" private
        leftAttachment "XmATTACH_NONE" private
        resizable "1" private
        rightAttachment "XmATTACH_FORM" private
        rightOffset "5" private
        topAttachment "XmATTACH_WIDGET" private
        topOffset "5" private
        topWidget "directory" private
        activateCallback "doFind" method
      }
    }
  }
}
