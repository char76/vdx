WIDGET {
  NAME "TextWindow"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 282 LONG LicView height 447 "
  buttonFontList "-adobe-helvetica-bold-r-normal--12-120-75-75-p-0-iso8859-1" public
  labelFontList "-adobe-helvetica-medium-r-normal--12-120-75-75-p-0-iso8859-1" public
  textFontList "-adobe-courier-medium-r-normal--12-120-75-75-m-0-iso8859-1_fmath" public
  WIDGET {
    NAME "mainWindow"
    CLASS "XmMainWindow"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    helpCallback "noHelpDialog" manage
    WIDGET {
      NAME "menuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "60" private
      y "10" private
      WIDGET {
        NAME "fileButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        labelString "File" public
        mnemonic "F" public
        subMenuId "fileMenu" private
      }
      WIDGET {
        NAME "fileMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        x "0" private
        y "0" private
        WIDGET {
          NAME "openButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>O" public
          acceleratorText "^O" public
          labelString "Open ..." public
          mnemonic "O" public
          activateCallback "fileOpenDialog" manage
        }
        WIDGET {
          NAME "saveButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>S" public
          acceleratorText "^S" public
          labelString "Save" public
          mnemonic "S" public
          activateCallback "do_save" method
        }
        WIDGET {
          NAME "saveAsButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>A" public
          acceleratorText "^A" public
          labelString "Save As ..." public
          mnemonic "A" public
          activateCallback "fileSaveAsDialog" manage
        }
        WIDGET {
          NAME "exitButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>E" public
          acceleratorText "^E" public
          labelString "Exit" public
          mnemonic "E" public
          activateCallback "exitDialog" manage
        }
      }
      WIDGET {
        NAME "editButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        x "0" private
        y "0" private
        labelString "Edit" public
        mnemonic "E" public
        subMenuId "editMenu" private
      }
      WIDGET {
        NAME "editMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        x "0" private
        y "0" private
        WIDGET {
          NAME "cutButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>X" public
          acceleratorText "^X" public
          labelString "Cut" public
          mnemonic "C" public
          activateCallback "do_cut" method
        }
        WIDGET {
          NAME "copyButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>C" public
          acceleratorText "^C" public
          labelString "Copy" public
          mnemonic "o" public
          activateCallback "do_copy" method
        }
        WIDGET {
          NAME "pasteButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>V" public
          acceleratorText "^V" public
          labelString "Paste" public
          mnemonic "P" public
          activateCallback "do_paste" method
        }
      }
    }
    WIDGET {
      NAME "textWidget"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      x "0" private
      y "20" private
      columns "60" private
      editMode "XmMULTI_LINE_EDIT" private
      rows "20" private
      valueChangedCallback "text_changed" method
    }
    WIDGET {
      NAME "exitDialog"
      CLASS "XmCreateQuestionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      cancelLabelString "No" public
      dialogTitle "Exit" public
      messageString "Do you wan't to exit the editor?" public
      okLabelString "Yes" public
      okCallback "do_exit" method
    }
    WIDGET {
      NAME "fileOpenDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      x "1" private
      y "1" private
      autoUnmanage "1" private
      dialogTitle "File Open" public
      okCallback "do_open" method
    }
    WIDGET {
      NAME "fileSaveAsDialog"
      CLASS "XmCreateFileSelectionDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      x "1" private
      y "1" private
      autoUnmanage "1" private
      dialogTitle "File Save" public
      okCallback "do_saveAs" method
    }
    WIDGET {
      NAME "noHelpDialog"
      CLASS "XmCreateWarningDialog"
      MANAGED "FALSE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
      dialogTitle "Sorry" public
      messageString "Sorry,
no help available!" public
    }
  }
}
