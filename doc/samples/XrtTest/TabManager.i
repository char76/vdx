WIDGET {
  NAME "TabManager"
  CLASS "TopLevelShell"
  MANAGED "TRUE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA ""
  DESCRIPTION "TopLevelShell"
  WIDGET {
    NAME "form"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "-1"
    VIEWDATA ""
    DESCRIPTION "XmBulletinBoard"
    height "745" private
    width "815" private
    x "0" private
    y "0" private
    WIDGET {
      NAME "xrtTabManager"
      CLASS "XmXrtTabManager"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
      DESCRIPTION "XmXrtTabManager"
      x "0" private
      y "0" private
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "3" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "3" private
      resizable "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "3" private
      topAttachment "XmATTACH_FORM" private
      topOffset "3" private
      WIDGET {
        NAME "xrtTabButton1"
        CLASS "XmXrtTabButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmXrtTabButton"
        height "58" private
        width "35" private
        x "4" private
        y "6" private
        labelString "3d" public
        xrtGearStringRotation "rotate_90" private
        xrtGearChildType "child_type_tab" private
        xrtGearPageNumber "1" private
      }
      WIDGET {
        NAME "xrt3d"
        CLASS "XtXrt3d"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmText"
        x "0" private
        y "0" private
        xrt3dBackgroundColor "peachpuff" private
        xrt3dDrawMesh "1" private
        xrt3dDrawZones "1" private
        xrt3dFooterBorder "Border3dOut" private
        xrt3dFooterStrings "The World" private
        xrt3dGraphBorder "Border3dOut" private
        xrt3dLegendBorder "Border3dOut" private
        xrt3dSolidSurface "0" private
        xrt3dSurfaceData "world_spline.dat" private
        xrt3dXRotation "90" private
        xrt3dYRotation "0" private
        xrt3dZRotation "0" private
        xrtGearPageNumber "1" private
      }
      WIDGET {
        NAME "xrtTabButton2"
        CLASS "XmXrtTabButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmXrtTabButton"
        height "52" private
        width "31" private
        x "4" private
        y "6" private
        labelString "Field" public
        xrtGearStringRotation "rotate_90" private
        xrtGearPageNumber "2" private
      }
      WIDGET {
        NAME "aligner"
        CLASS "XmXrtAligner"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA "BOOLEAN TreeNodeView WithChildren TRUE "
        DESCRIPTION "XmText"
        height "675" private
        width "801" private
        x "4" private
        y "35" private
        xrtGearPageNumber "2" private
        WIDGET {
          NAME "xrtStringField"
          CLASS "XmXrtStringField"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtStringField"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "xrtDateField"
          CLASS "XmXrtDateField"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtDateField"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "xrtCurrencyField"
          CLASS "XmXrtCurrencyField"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtCurrencyField"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "xrtFloatField"
          CLASS "XmXrtFloatField"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtFloatField"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "xrtIntField"
          CLASS "XmXrtIntField"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtIntField"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "xrtComboBox"
          CLASS "XmXrtComboBox"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtComboBox"
          x "0" private
          y "0" private
        }
        WIDGET {
          NAME "xrtSpinBox"
          CLASS "XmXrtSpinBox"
          MANAGED "TRUE"
          QUICKHELP ""
          HELPID "-1"
          VIEWDATA ""
          DESCRIPTION "XmXrtSpinBox"
          x "0" private
          y "0" private
          xrtSpinArrowLayout "arrows_end" private
          xrtSpinArrowOrientation "XmVERTICAL" private
          xrtSpinFieldType "fieldtype_int" private
          xrtSpinType "type_counter" private
        }
      }
      WIDGET {
        NAME "xrtTabButton3"
        CLASS "XmXrtTabButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmXrtTabButton"
        height "52" private
        width "31" private
        x "4" private
        y "6" private
        labelString "Table" public
        xrtGearStringRotation "rotate_90" private
        xrtGearPageNumber "3" private
      }
      WIDGET {
        NAME "table"
        CLASS "XtXrtTable"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XtXrtTable"
        height "675" private
        width "801" private
        x "10" private
        y "10" private
        xrtTblAlignmentContext "alignment_middlecenter" private
        xrtTblAllowCellResize "resize_horizontal" private
        xrtTblBackgroundSeries "(ALL ALL peachpuff)" private
        xrtTblBorderTypeContext "border_frame_in" private
        xrtTblBottomShadowContext "BlanchedAlmond" private
        xrtTblColumnLabels "Hello, VDX - User" private
        xrtTblDataTypeContext "type_string" private
        xrtTblDoubleBuffer "doublebuffer_window" private
        xrtTblEditableContext "1" private
        xrtTblForegroundSeries "(ALL LABEL red)(LABEL ALL green)" private
        xrtTblFrameBorderType "border_etched_in" private
        xrtTblNumRows "40" private
        xrtTblRowLabels "Row 1, Row 2, Row 3" private
        xrtTblSelectionPolicy "select_multirange" private
        xrtTblSetTextCursorPos "1" private
        xrtTblTextInitSelect "1" private
        xrtTblValidatePolicy "validate_always" private
        xrtGearPageNumber "3" private
      }
    }
  }
}
