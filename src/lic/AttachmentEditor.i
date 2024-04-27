WIDGET {
  NAME "AttachmentEditor"
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
    HELPID "45"
    VIEWDATA ""
    DESCRIPTION "XmMainWindow"
    x "20" private
    y "10" private
    WIDGET {
      NAME "menuBar"
      CLASS "XmCreateMenuBar"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "LONG LicView width 245 LONG LicView height 421 BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmCreateMenuBar"
      x "20" private
      y "10" private
      menuHelpWidget "helpButton" private
      WIDGET {
        NAME "fileButton"
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
        subMenuId "fileMenu" private
      }
      WIDGET {
        NAME "fileMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "loadButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Load selected widget into browser."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>l" public
          acceleratorText "^L" public
          labelString "Load" public
          mnemonic "L" public
          activateCallback "do_load" method
        }
        WIDGET {
          NAME "applyButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          accelerator "Ctrl<Key>a" public
          acceleratorText "^A" public
          labelString "Apply" public
          mnemonic "A" private
          activateCallback "do_apply" method
        }
        WIDGET {
          NAME "closeButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Close this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>c" private
          acceleratorText "^C" private
          labelString "Close" public
          mnemonic "C" public
          activateCallback "do_close" method
        }
      }
      WIDGET {
        NAME "viewButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "View" public
        mnemonic "V" private
        subMenuId "viewMenu" private
      }
      WIDGET {
        NAME "viewMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "smallIconButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Display small icons in Tree View."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>s" public
          acceleratorText "^S" public
          labelString "Small Icons" public
          mnemonic "S" public
          valueChangedCallback "do_smallIcon" method
        }
        WIDGET {
          NAME "withIconButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Display icons Tree View."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>I" public
          acceleratorText "^I" public
          labelString "With Icons" public
          mnemonic "I" public
          valueChangedCallback "do_withIcon" method
        }
        WIDGET {
          NAME "withClassNameButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP "Display class names of widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>n" public
          acceleratorText "^N" public
          labelString "With Class Names" public
          mnemonic "N" public
          valueChangedCallback "do_withClassName" method
        }
      }
      WIDGET {
        NAME "widgetButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Widget" public
        mnemonic "W" public
        subMenuId "widgetMenu" private
      }
      WIDGET {
        NAME "widgetMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        mapCallback "do_widgetMenuMap" method
        WIDGET {
          NAME "editButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show Widget Resource Editor for selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "E" public
          labelString "Edit" public
          mnemonic "E" public
        }
        WIDGET {
          NAME "browseButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show Browser for selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "B" public
          labelString "Browse" public
          mnemonic "B" public
        }
        WIDGET {
          NAME "menuEditButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show Menu Ediotor for selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "M" public
          labelString "Menu Editor" public
          mnemonic "M" public
        }
        WIDGET {
          NAME "cutButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Copy selection to clipboard and delete selection."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "X" public
          labelString "Cut" public
          mnemonic "u" public
        }
        WIDGET {
          NAME "copyButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Copy selection to clipboard."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "C" public
          labelString "Copy" public
          mnemonic "C" public
        }
        WIDGET {
          NAME "pasteButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Paste clipboard contents to selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "V" public
          labelString "Paste" public
          mnemonic "P" public
        }
        WIDGET {
          NAME "separator"
          CLASS "XmSeparator"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmSeparator"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "deleteButton"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Delete selected widgets."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          acceleratorText "DEL" public
          labelString "Delete" public
          mnemonic "D" public
        }
      }
      WIDGET {
        NAME "helpButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Help" public
        mnemonic "H" public
        subMenuId "helpMenu" private
      }
      WIDGET {
        NAME "helpMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "onHelp"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help on help system."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Help" public
          mnemonic "H" public
          activateCallback "do_onHelp" method
        }
        WIDGET {
          NAME "onContext"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Get help after clicking in a window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          labelString "On Context" private
          mnemonic "C" public
          activateCallback "do_onContext" method
        }
        WIDGET {
          NAME "onWidResEditor"
          CLASS "XmPushButton"
          MANAGED "TRUE"
          QUICKHELP "Show help for this window."
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmPushButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>F1" public
          acceleratorText "^F1" public
          labelString "On Window" private
          mnemonic "W" private
          activateCallback "do_help" method
        }
      }
      WIDGET {
        NAME "optionsButton"
        CLASS "XmCascadeButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCascadeButton"
        x "0" private
        y "0" private
        labelString "Options" public
        mnemonic "O" public
        subMenuId "optionsMenu" private
      }
      WIDGET {
        NAME "optionsMenu"
        CLASS "XmCreatePulldownMenu"
        MANAGED "FALSE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmCreatePulldownMenu"
        x "0" private
        y "0" private
        WIDGET {
          NAME "automaticLoadButton"
          CLASS "XmToggleButton"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "LONG LicView width 200 LONG LicView height 300 "
          DESCRIPTION "XmToggleButton"
          x "0" private
          y "0" private
          accelerator "Ctrl<Key>t" public
          acceleratorText "^T" public
          labelString "Automatic Load" public
          mnemonic "t" public
          valueChangedCallback "do_automaticLoad" method
        }
      }
    }
    WIDGET {
      NAME "topCellTable"
      CLASS "XlCellTable"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XlCellTable"
      horizontalSpacing "0" private
      resizeColumn "0" private
      resizeRow "0" private
      verticalSpacing "0" private
      WIDGET {
        NAME "quickHelpLabel"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        alignment "XmALIGNMENT_BEGINNING" private
        labelString "Quick Help messages will appear in this line." public
        cellColumn "0" private
        cellRow "1" private
      }
      WIDGET {
        NAME "mainCellTable"
        CLASS "XlCellTable"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XlCellTable"
        horizontalSpacing "0" private
        resizeColumn "0" private
        resizeRow "0" private
        verticalSpacing "0" private
        cellColumn "0" private
        cellRow "0" private
        WIDGET {
          NAME "childrenTable"
          CLASS "XlCellTable"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
          DESCRIPTION "XlCellTable"
          resizeColumn "0" private
          resizeRow "0" private
          cellColumn "0" private
          cellRow "0" private
          WIDGET {
            NAME "childrenFrame"
            CLASS "XmFrame"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
            DESCRIPTION "XmFrame"
            marginHeight "5" private
            marginWidth "5" private
            cellColumn "0" private
            cellRow "0" private
            WIDGET {
              NAME "childrenLabel"
              CLASS "XmLabel"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmLabel"
              x "50" private
              y "20" private
              labelString "Children" public
              childType "XmFRAME_TITLE_CHILD" private
            }
          }
          WIDGET {
            NAME "buttonBox"
            CLASS "XlButtonBox"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA ""
            DESCRIPTION "XlButtonBox"
            spacing "5" private
            cellColumn "0" private
            cellRow "1" private
            WIDGET {
              NAME "pushButton_1"
              CLASS "XmPushButton"
              MANAGED "TRUE"
              QUICKHELP "Apply changes to all children."
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmPushButton"
              x "0" private
              y "0" private
              labelString "Apply" private
              activateCallback "do_apply" method
            }
            WIDGET {
              NAME "pushButton_2"
              CLASS "XmPushButton"
              MANAGED "TRUE"
              QUICKHELP "Close Attachment Editor. Changes will be lost."
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmPushButton"
              x "0" private
              y "0" private
              labelString "Close" public
              activateCallback "do_close" method
            }
            WIDGET {
              NAME "pushButton_3"
              CLASS "XmPushButton"
              MANAGED "TRUE"
              QUICKHELP "Get help for this window."
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmPushButton"
              x "0" private
              y "0" private
              labelString "Help" public
              activateCallback "do_help" method
            }
          }
        }
        WIDGET {
          NAME "attachmentCellTable"
          CLASS "XlCellTable"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
          DESCRIPTION "XlCellTable"
          cellColumn "1" private
          cellRow "0" private
          WIDGET {
            NAME "xlCellTable_1"
            CLASS "XlCellTable"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
            DESCRIPTION "XlCellTable"
            resizeColumn "1" private
            resizeRow "1" private
            cellColumn "1" private
            cellRow "1" private
            WIDGET {
              NAME "resizableToggle"
              CLASS "XmToggleButton"
              MANAGED "TRUE"
              QUICKHELP "The resource XmNresizable"
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmToggleButton"
              x "30" private
              y "40" private
              labelString "resizable" public
              cellColumn "1" private
              cellRow "1" private
              horizontalAlignment "XmCELL_ALIGNMENT_CENTER" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
            }
            WIDGET {
              NAME "separator_1"
              CLASS "XmSeparator"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmSeparator"
              width "20" private
              separatorType "XmSHADOW_ETCHED_OUT" private
              cellColumn "0" private
              cellRow "1" private
            }
            WIDGET {
              NAME "separator_1_1"
              CLASS "XmSeparator"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmSeparator"
              width "20" private
              separatorType "XmSHADOW_ETCHED_OUT" private
              cellColumn "2" private
              cellRow "1" private
            }
            WIDGET {
              NAME "separator_1_2"
              CLASS "XmSeparator"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmSeparator"
              height "20" private
              orientation "XmVERTICAL" private
              separatorType "XmSHADOW_ETCHED_OUT" private
              cellColumn "1" private
              cellRow "0" private
            }
            WIDGET {
              NAME "separator_1_1_1"
              CLASS "XmSeparator"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmSeparator"
              height "20" private
              orientation "XmVERTICAL" private
              separatorType "XmSHADOW_ETCHED_OUT" private
              cellColumn "1" private
              cellRow "2" private
            }
          }
          WIDGET {
            NAME "bottomCellTable"
            CLASS "XlCellTable"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XlCellTable"
            x "2" private
            y "20" private
            horizontalSpacing "0" private
            verticalSpacing "0" private
            cellColumn "1" private
            cellRow "2" private
            WIDGET {
              NAME "bottomAttachment"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "Attachment of the child's bottom edge. XmNbottomAttachment"
              HELPID "-1"
              VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
              DESCRIPTION "XmCreateOptionMenu"
              height "40" private
              width "110" private
              x "62" private
              y "5" private
              labelString "Bottom:" public
              marginHeight "0" private
              marginWidth "0" private
              subMenuId "bottomAttachmentMenu" private
              cellColumn "0" private
              cellRow "0" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
              WIDGET {
                NAME "bottomAttachmentMenu"
                CLASS "XmCreatePulldownMenu"
                MANAGED "FALSE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
                DESCRIPTION "XmCreatePulldownMenu"
                x "50" private
                y "10" private
                entryCallback "bottomAttachmentChanged" method
                WIDGET {
                  NAME "bottomAttachNone"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach none."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "AttachNone.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "bottomAttachForm"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach form's bottom border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "BottomAttachForm.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "bottomAttachWidget"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach another widget's top border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "BottomAttachWidget.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "bottomAttachPosition"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach a position. Depends on XmForm's fractionBase resource."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "BottomAttachPosition.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "bottomAttachSelf"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach self. "
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "BottomAttachSelf.xpm" include
                  labelType "XmPIXMAP" private
                }
              }
            }
            WIDGET {
              NAME "bottomWidget"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "The attached widget. XmNbottomWidget"
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmCreateOptionMenu"
              marginHeight "0" private
              marginWidth "0" private
              cellColumn "0" private
              cellRow "2" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
            }
            WIDGET {
              NAME "xlCellTable_5"
              CLASS "XlCellTable"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XlCellTable"
              horizontalSpacing "0" private
              cellColumn "0" private
              cellRow "1" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              WIDGET {
                NAME "bottomOffsetLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Off:" public
                cellColumn "0" private
                cellRow "0" private
              }
              WIDGET {
                NAME "bottomPositionLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Pos:" public
                cellColumn "2" private
                cellRow "0" private
              }
              WIDGET {
                NAME "bottomOffset"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "Offset to the attached point. XmNbottomOffset"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "1" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
              WIDGET {
                NAME "bottomPosition"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "The attached Position. XmNbottomPosition"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "3" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
            }
          }
          WIDGET {
            NAME "leftCellTable"
            CLASS "XlCellTable"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XlCellTable"
            x "2" private
            y "20" private
            horizontalSpacing "0" private
            verticalSpacing "2" private
            cellColumn "0" private
            cellRow "1" private
            WIDGET {
              NAME "leftAttachment"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "Attachment of the child's left edge. XmNleftAttachment"
              HELPID "-1"
              VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
              DESCRIPTION "XmCreateOptionMenu"
              height "40" private
              width "93" private
              x "62" private
              y "5" private
              labelString "Left:" public
              marginHeight "0" private
              marginWidth "0" private
              subMenuId "leftAttachmentMenu" private
              cellColumn "0" private
              cellRow "0" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
              WIDGET {
                NAME "leftAttachmentMenu"
                CLASS "XmCreatePulldownMenu"
                MANAGED "FALSE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmCreatePulldownMenu"
                x "50" private
                y "10" private
                entryCallback "leftAttachmentChanged" method
                WIDGET {
                  NAME "leftAttachNone"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach none."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "AttachNone.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "leftAttachForm"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach form's left border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "LeftAttachForm.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "leftAttachWidget"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach another widget's right border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "LeftAttachWidget.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "leftAttachPosition"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach a position. Depends on XmForm's fractionBase resource."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "LeftAttachPosition.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "leftAttachSelf"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach self. "
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "LeftAttachSelf.xpm" include
                  labelType "XmPIXMAP" private
                }
              }
            }
            WIDGET {
              NAME "leftWidget"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "The attached widget. XmNleftWidget"
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmCreateOptionMenu"
              marginHeight "0" private
              marginWidth "0" private
              cellColumn "0" private
              cellRow "2" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
            }
            WIDGET {
              NAME "xlCellTable_3"
              CLASS "XlCellTable"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XlCellTable"
              horizontalSpacing "0" private
              cellColumn "0" private
              cellRow "1" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              WIDGET {
                NAME "leftOffsetLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Off:" public
                cellColumn "0" private
                cellRow "0" private
              }
              WIDGET {
                NAME "leftPositionLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Pos:" public
                cellColumn "2" private
                cellRow "0" private
              }
              WIDGET {
                NAME "leftOffset"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "Offset to the attached point. XmNleftOffset"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "1" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
              WIDGET {
                NAME "leftPosition"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "The attached Position. XmNleftPosition"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "3" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
            }
          }
          WIDGET {
            NAME "rightCellTable"
            CLASS "XlCellTable"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XlCellTable"
            x "2" private
            y "20" private
            horizontalSpacing "0" private
            verticalSpacing "0" private
            cellColumn "2" private
            cellRow "1" private
            WIDGET {
              NAME "rightAttachment"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "Attachment of the child's right edge. XmNrightAttachment"
              HELPID "-1"
              VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
              DESCRIPTION "XmCreateOptionMenu"
              labelString "Right:" public
              marginHeight "0" private
              marginWidth "0" private
              subMenuId "rightAttachmentMenu" private
              cellColumn "0" private
              cellRow "0" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
              WIDGET {
                NAME "rightAttachmentMenu"
                CLASS "XmCreatePulldownMenu"
                MANAGED "FALSE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
                DESCRIPTION "XmCreatePulldownMenu"
                x "50" private
                y "10" private
                entryCallback "rightAttachmentChanged" method
                WIDGET {
                  NAME "rightAttachNone"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach none."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "AttachNone.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "rightAttachForm"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach form's right border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "RightAttachForm.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "rightAttachWidget"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach another widget's left border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "RightAttachWidget.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "rightAttachPosition"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach a position. Depends on XmForm's fractionBase resource."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "RightAttachPosition.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "rightAttachSelf"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach self. "
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "RightAttachSelf.xpm" include
                  labelType "XmPIXMAP" private
                }
              }
            }
            WIDGET {
              NAME "rightWidget"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "The attached widget. XmNrightWidget"
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmCreateOptionMenu"
              marginHeight "0" private
              marginWidth "0" private
              cellColumn "0" private
              cellRow "2" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
            }
            WIDGET {
              NAME "xlCellTable_4"
              CLASS "XlCellTable"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XlCellTable"
              horizontalSpacing "0" private
              cellColumn "0" private
              cellRow "1" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              WIDGET {
                NAME "rightOffsetLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Off:" public
                cellColumn "0" private
                cellRow "0" private
              }
              WIDGET {
                NAME "rightPositionLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Pos:" public
                cellColumn "2" private
                cellRow "0" private
              }
              WIDGET {
                NAME "rightOffset"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "Offset to the attached point. XmNrightOffset"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "1" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
              WIDGET {
                NAME "rightPosition"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "The attached Position. XmNrightPosition"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "3" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
            }
          }
          WIDGET {
            NAME "xlCellTable"
            CLASS "XlCellTable"
            MANAGED "TRUE"
            QUICKHELP ""
            HELPID "-1"
            VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
            DESCRIPTION "XlCellTable"
            x "2" private
            y "20" private
            horizontalSpacing "0" private
            verticalSpacing "0" private
            cellColumn "1" private
            cellRow "0" private
            WIDGET {
              NAME "topAttachment"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "Attachment of the child's top edge. XmNtopAttachment"
              HELPID "-1"
              VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
              DESCRIPTION "XmCreateOptionMenu"
              labelString "Top:" public
              marginHeight "0" private
              marginWidth "0" private
              subMenuId "topAttachmentMenu" private
              cellColumn "0" private
              cellRow "0" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
              WIDGET {
                NAME "topAttachmentMenu"
                CLASS "XmCreatePulldownMenu"
                MANAGED "FALSE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
                DESCRIPTION "XmCreatePulldownMenu"
                x "50" private
                y "10" private
                entryCallback "topAttachmentChanged" method
                WIDGET {
                  NAME "topAttachNone"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach none."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "AttachNone.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "topAttachForm"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach form's top border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  labelPixmap "TopAttachForm.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "topAttachWidget"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach another widget's bottom border."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "TopAttachWidget.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "topAttachPosition"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach a position. Depends on XmForm's fractionBase resource."
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "TopAttachPosition.xpm" include
                  labelType "XmPIXMAP" private
                }
                WIDGET {
                  NAME "topAttachSelf"
                  CLASS "XmPushButton"
                  MANAGED "TRUE"
                  QUICKHELP "Attach self. "
                  HELPID "-1"
                  VIEWDATA ""
                  DESCRIPTION "XmPushButton"
                  x "0" private
                  y "0" private
                  labelPixmap "TopAttachSelf.xpm" include
                  labelType "XmPIXMAP" private
                }
              }
            }
            WIDGET {
              NAME "topWidget"
              CLASS "XmCreateOptionMenu"
              MANAGED "TRUE"
              QUICKHELP "The attached widget. XmNtopWidget"
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XmCreateOptionMenu"
              marginHeight "0" private
              marginWidth "0" private
              cellColumn "0" private
              cellRow "2" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              verticalAlignment "XmCELL_ALIGNMENT_CENTER" private
            }
            WIDGET {
              NAME "xlCellTable_2"
              CLASS "XlCellTable"
              MANAGED "TRUE"
              QUICKHELP ""
              HELPID "-1"
              VIEWDATA ""
              DESCRIPTION "XlCellTable"
              horizontalSpacing "0" private
              cellColumn "0" private
              cellRow "1" private
              horizontalAlignment "XmCELL_ALIGNMENT_BEGINNING" private
              WIDGET {
                NAME "topPositionLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Pos:" public
                cellColumn "2" private
                cellRow "0" private
              }
              WIDGET {
                NAME "topOffsetLabel"
                CLASS "XmLabel"
                MANAGED "TRUE"
                QUICKHELP ""
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmLabel"
                x "30" private
                y "30" private
                labelString "Off:" public
                cellColumn "0" private
                cellRow "0" private
              }
              WIDGET {
                NAME "topOffset"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "Offset to the attached point. XmNtopOffset"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "1" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
              WIDGET {
                NAME "topPosition"
                CLASS "XmText"
                MANAGED "TRUE"
                QUICKHELP "The attached Position. XmNtopPosition"
                HELPID "-1"
                VIEWDATA ""
                DESCRIPTION "XmText"
                columns "3" private
                marginHeight "2" private
                marginWidth "2" private
                cellColumn "3" private
                cellRow "0" private
                valueChangedCallback "valueChanged" method
              }
            }
          }
        }
      }
    }
  }
}
