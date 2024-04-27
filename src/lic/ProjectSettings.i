WIDGET {
  NAME "ProjectSettings"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  title "Project Settings" public
  WIDGET {
    NAME "form"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "44"
    VIEWDATA ""
    DESCRIPTION "XmForm"
    height "550" private
    width "400" private
    x "0" private
    y "0" private
    WIDGET {
      NAME "xlCellTable_1"
      CLASS "XlCellTable"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XlCellTable"
      x "10" private
      y "0" private
      resizeColumn "1" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "separator" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      topAttachment "XmATTACH_FORM" private
      topOffset "1" private
      WIDGET {
        NAME "PSNameLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "10" private
        y "10" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Project File:" public
        cellColumn "0" private
        cellRow "0" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "PSNameText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Name of project file."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "90" private
        y "10" private
        maxLength "1024" private
        cellColumn "1" private
        cellRow "0" private
        losingFocusCallback "do_loseFocus" method
      }
      WIDGET {
        NAME "applClassLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "10" private
        y "50" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Application Class:" public
        cellColumn "0" private
        cellRow "1" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "applClassText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Application class of executable determines the resource file name."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "125" private
        y "50" private
        maxLength "1024" private
        cellColumn "1" private
        cellRow "1" private
      }
      WIDGET {
        NAME "PSLangMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "30" private
        y "10" private
      }
      WIDGET {
        NAME "langLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "10" private
        y "130" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Generation Model:" public
        cellColumn "0" private
        cellRow "2" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "PSLangOptionMenu"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP "Programming languages for code generation."
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateOptionMenu"
        x "10" private
        y "130" private
        cellColumn "1" private
        cellRow "2" private
        horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
      }
      WIDGET {
        NAME "PSStartLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "10" private
        y "130" private
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Startup Interface:" public
        cellColumn "0" private
        cellRow "3" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "PSSourceDirLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Source Path:" public
        cellColumn "0" private
        cellRow "4" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "PSSourceDirText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Directory in which the source code is generated."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "125" private
        y "90" private
        maxLength "1024" private
        cellColumn "1" private
        cellRow "4" private
      }
      WIDGET {
        NAME "moreSourceFilesButton"
        CLASS "XmDrawnButton"
        MANAGED "TRUE"
        QUICKHELP "Open a selection box for source file selection."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmDrawnButton"
        labelString "..." public
        pushButtonEnabled "1" private
        cellColumn "2" private
        cellRow "6" private
        horizontalAlignment "XmCELL_ALIGNMENT_CENTER" private
        verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
        activateCallback "moreSourceFilesDialog" manage
      }
      WIDGET {
        NAME "sourcePathButton"
        CLASS "XmDrawnButton"
        MANAGED "TRUE"
        QUICKHELP "Open a file selection box."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmDrawnButton"
        labelString "..." public
        pushButtonEnabled "1" private
        cellColumn "2" private
        cellRow "4" private
        horizontalAlignment "XmCELL_ALIGNMENT_CENTER" private
        verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
        activateCallback "PSSourceDirFileSB" manage
      }
      WIDGET {
        NAME "PSSourceDirFileSB"
        CLASS "XmCreateFileSelectionDialog"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
        DESCRIPTION "XmCreateFileSelectionDialog"
        x "250" private
        y "180" private
        autoUnmanage "1" private
        dialogTitle "Source directory" public
        fileTypeMask "XmFILE_DIRECTORY" private
        okCallback "PSSourceDirChanged" method
      }
      WIDGET {
        NAME "execFileLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        labelString "Executable:" public
        cellColumn "0" private
        cellRow "5" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "execFileText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "File name of the executable."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "70" private
        y "170" private
        maxLength "1024" private
        cellColumn "1" private
        cellRow "5" private
        horizontalAlignment "XmCELL_ALIGNMENT_JUSTIFY" private
      }
      WIDGET {
        NAME "moreSourceLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "80" private
        y "180" private
        labelString "More Source Files:" public
        cellColumn "0" private
        cellRow "6" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "moreSourceText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "More source files e.g. for application logic code."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "80" private
        y "170" private
        cellColumn "1" private
        cellRow "6" private
      }
      WIDGET {
        NAME "extraCompilerOptionLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "50" private
        y "260" private
        labelString "Extra Compiler Options:" public
        cellColumn "0" private
        cellRow "7" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "extraCompilerOptionText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Compiler options e.g. -g -I/opt/yard/include"
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "100" private
        y "290" private
        cellColumn "1" private
        cellRow "7" private
      }
      WIDGET {
        NAME "extraLinkerOptionLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "50" private
        y "250" private
        labelString "Extra Linker Options:" public
        cellColumn "0" private
        cellRow "8" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "extraLinkerOptionText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Extra linker options e.g. -g -L/opt/yard/lib"
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "60" private
        y "260" private
        cellColumn "1" private
        cellRow "8" private
      }
      WIDGET {
        NAME "descriptionLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        height "30" private
        x "53" private
        y "333" private
        labelString "Description:" public
        cellColumn "0" private
        cellRow "10" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
        verticalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
      }
      WIDGET {
        NAME "descriptionScrolledWindow"
        CLASS "XmScrolledWindow"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmScrolledWindow"
        x "70" private
        y "280" private
        cellColumn "1" private
        cellRow "10" private
        WIDGET {
          NAME "descriptionText"
          CLASS "XmText"
          MANAGED "TRUE"
          QUICKHELP "Any comment that describes the project."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmText"
          x "20" private
          y "10" private
          editMode "XmMULTI_LINE_EDIT" private
          scrollHorizontal "0" private
          wordWrap "1" private
        }
      }
      WIDGET {
        NAME "selectStartupInterface"
        CLASS "XmCreateSelectionDialog"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN WidgetView showDialog FALSE "
        DESCRIPTION "XmCreateSelectionDialog"
        dialogTitle "Select Startup Interface" private
        listLabelString "Interfaces:" private
        selectionLabelString "Startup Interface" private
        okCallback "do_setStartupInterface" method
      }
      WIDGET {
        NAME "moreSourceFilesDialog"
        CLASS "XmCreateMessageDialog"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN WidgetView showDialog FALSE BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreateMessageDialog"
        height "270" private
        width "260" private
        x "0" private
        y "0" private
        dialogTitle "Select Additional Source Files" private
        messageString "Sources in Source Directory:" private
        mapCallback "do_mapMoreSourceFiles" method
        okCallback "do_moreSourceFiles" method
        WIDGET {
          NAME "scrolledWindow_1"
          CLASS "XmScrolledWindow"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmScrolledWindow"
          height "100" private
          width "100" private
          x "50" private
          y "0" private
          WIDGET {
            NAME "sourceFilesList"
            CLASS "XmList"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XmList"
            height "90" private
            width "200" private
            x "0" private
            y "0" private
            selectionPolicy "XmMULTIPLE_SELECT" private
          }
        }
      }
      WIDGET {
        NAME "extraLibrariesText"
        CLASS "XmText"
        MANAGED "TRUE"
        QUICKHELP "Extra libraries e.g. -lsql -lm"
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "150" private
        y "300" private
        cellColumn "1" private
        cellRow "9" private
      }
      WIDGET {
        NAME "extraLibrariesLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "50" private
        y "250" private
        labelString "Extra Libraries:" public
        cellColumn "0" private
        cellRow "9" private
        horizontalAlignment "XmCELL_ALIGNMENT_END" private
      }
      WIDGET {
        NAME "startupOptionMenu"
        CLASS "XmCreateOptionMenu"
        MANAGED "TRUE"
        QUICKHELP "Programming languages for code generation."
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreateOptionMenu"
        x "160" private
        y "100" private
        cellColumn "1" private
        cellRow "3" private
        horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
      }
    }
    WIDGET {
      NAME "separator"
      CLASS "XmSeparator"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmSeparator"
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "xlButtonBox" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
    WIDGET {
      NAME "xlButtonBox"
      CLASS "XlButtonBox"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XlButtonBox"
      entryMarginWidth "10" private
      spacing "5" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "quickHelp" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "10" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "10" private
      WIDGET {
        NAME "psOkButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Apply changes and close this window."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        height "29" private
        width "80" private
        x "5" private
        y "5" private
        labelString "OK" public
        activateCallback "do_ok" method
      }
      WIDGET {
        NAME "psCancelButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Close this window without saving changes."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        labelString "Cancel" public
        activateCallback "do_cancel" method
      }
      WIDGET {
        NAME "psHelpButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP "Show help for this window."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        labelString "Help" public
        activateCallback "do_help" method
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
      labelString "This is the quick help line." public
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
  }
}
