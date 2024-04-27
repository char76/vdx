WIDGET {
  NAME "FontSelect"
  CLASS "TopLevelShell"
  MANAGED "FALSE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 397 LONG LicView height 390 "
  DESCRIPTION "TopLevelShell"
  iconPixmap "FontChooser.xpm" load
  title "Font Chooser" private
  WIDGET {
    NAME "fontCellTable"
    CLASS "XlCellTable"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "11"
    VIEWDATA "LONG LicView width 341 LONG LicView height 392 "
    DESCRIPTION "XmForm"
    resizeColumn "0" private
    resizeRow "1" private
    WIDGET {
      NAME "fontFilterRowColumn"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XmRowColumn"
      orientation "XmHORIZONTAL" private
      cellColumn "0" private
      cellRow "0" private
      WIDGET {
        NAME "companyMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "40" private
        y "10" private
        entryCallback "companyChanged" method
        WIDGET {
          NAME "companyDontCare"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "*" private
        }
      }
      WIDGET {
        NAME "companyOptionMenu"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateOptionMenu"
        x "10" private
        y "10" private
        subMenuId "companyMenu" private
      }
      WIDGET {
        NAME "familyMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "40" private
        y "10" private
        entryCallback "familyChanged" method
        WIDGET {
          NAME "familyDontCare"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "*" private
        }
      }
      WIDGET {
        NAME "familyOptionMenu"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateOptionMenu"
        x "70" private
        y "10" private
        subMenuId "familyMenu" private
      }
      WIDGET {
        NAME "sizeMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "40" private
        y "10" private
        entryCallback "sizeChanged" method
        WIDGET {
          NAME "sizeDontCare"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "*" private
        }
      }
      WIDGET {
        NAME "sizeOptionMenu"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateOptionMenu"
        height "30" private
        width "50" private
        x "120" private
        y "10" private
        subMenuId "sizeMenu" private
      }
    }
    WIDGET {
      NAME "listScrolledWindow"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmScrolledWindow"
      cellColumn "0" private
      cellRow "1" private
      WIDGET {
        NAME "fontList"
        CLASS "XmList"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmList"
        height "160" private
        width "392" private
        x "0" private
        y "20" private
        browseSelectionCallback "fontSelected" method
      }
    }
    WIDGET {
      NAME "sampleText"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmText"
      editMode "XmMULTI_LINE_EDIT" private
      rows "4" private
      value "Pferde essen keinen Gurkensalat.
abcdefgeijklmnopqrstuvwxyz
ABCDEFGEIJKLMNOPQRSTUVWXYZ
\"!§$%&/()=?+-*#~" public
      cellColumn "0" private
      cellRow "2" private
    }
    WIDGET {
      NAME "fontSelection"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "LONG LicView width 200 LONG LicView height 300 BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmText"
      cellColumn "0" private
      cellRow "3" private
      activateCallback "fontTextChanged" method
    }
    WIDGET {
      NAME "separator"
      CLASS "XmSeparator"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmSeparator"
      cellColumn "0" private
      cellRow "4" private
    }
    WIDGET {
      NAME "buttonBox"
      CLASS "XlButtonBox"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XlButtonBox"
      spacing "6" private
      cellColumn "0" private
      cellRow "5" private
      WIDGET {
        NAME "okButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "10" private
        y "314" private
        labelString "OK" public
        activateCallback "fontSelectOk" method
      }
      WIDGET {
        NAME "cancelButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "210" private
        y "314" private
        labelString "Cancel" public
        activateCallback "fontSelectCancel" method
      }
      WIDGET {
        NAME "helpButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "30" private
        width "80" private
        x "410" private
        y "314" private
        labelString "Help" public
        activateCallback "fontSelectHelp" method
      }
    }
    WIDGET {
      NAME "quickHelp"
      CLASS "XmLabel"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmLabel"
      alignment "XmALIGNMENT_BEGINNING" private
      labelString "This is the Quick Help Line." public
      cellColumn "0" private
      cellRow "6" private
    }
  }
}
