WIDGET {
  NAME "ColorSelect"
  CLASS "TopLevelShell"
  MANAGED "FALSE"
  QUICKHELP ""
  HELPID "-1"
  VIEWDATA "LONG LicView width 200 LONG LicView height 300 "
  DESCRIPTION "TopLevelShell"
  iconPixmap "ColorSelect.xpm" load
  title "Color Selection" private
  WIDGET {
    NAME "form_1"
    CLASS "XmForm"
    MANAGED "TRUE"
    QUICKHELP ""
    HELPID "10"
    VIEWDATA ""
    DESCRIPTION "XmForm"
    height "358" private
    width "330" private
    x "0" private
    y "0" private
    WIDGET {
      NAME "colorText"
      CLASS "XmText"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmText"
      x "316" private
      y "3414" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "5" private
      bottomWidget "separator_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "5" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "5" private
      activateCallback "textValueChanged" method
    }
    WIDGET {
      NAME "separator_1"
      CLASS "XmSeparator"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmSeparator"
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "xlButtonBox_1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
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
      bottomAttachment "XmATTACH_FORM" private
      bottomOffset "1" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
    }
    WIDGET {
      NAME "rowColumn_1"
      CLASS "XmRowColumn"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XmRowColumn"
      x "333" private
      y "142" private
      orientation "XmVERTICAL" private
      packing "XmPACK_TIGHT" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "10" private
      topAttachment "XmATTACH_FORM" private
      topOffset "8" private
      WIDGET {
        NAME "redScale"
        CLASS "XmScale"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmScale"
        height "56" private
        width "140" private
        x "3" private
        y "3" private
        maximum "255" private
        orientation "XmHORIZONTAL" private
        showValue "XmNEAR_SLIDER" private
        titleString "Red" private
        dragCallback "valueChanged" method
        valueChangedCallback "valueChanged" method
      }
      WIDGET {
        NAME "greenScale"
        CLASS "XmScale"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmScale"
        x "1666" private
        y "142" private
        maximum "255" private
        orientation "XmHORIZONTAL" private
        showValue "XmNEAR_SLIDER" private
        titleString "Green" private
        dragCallback "valueChanged" method
        valueChangedCallback "valueChanged" method
      }
      WIDGET {
        NAME "blueScale"
        CLASS "XmScale"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmScale"
        x "2500" private
        y "0" private
        maximum "255" private
        orientation "XmHORIZONTAL" private
        showValue "XmNEAR_SLIDER" private
        titleString "Blue" private
        dragCallback "valueChanged" method
        valueChangedCallback "valueChanged" method
      }
    }
    WIDGET {
      NAME "xlButtonBox_1"
      CLASS "XlButtonBox"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA "BOOLEAN TreeNodeView WithChildren FALSE "
      DESCRIPTION "XlButtonBox"
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "1" private
      bottomWidget "quickHelp" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "1" private
      WIDGET {
        NAME "okButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "150" private
        y "4414" private
        labelString "OK" public
        activateCallback "colorSelectOk" method
      }
      WIDGET {
        NAME "cancelButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "1500" private
        y "4428" private
        labelString "Cancel" public
        activateCallback "colorSelectCancel" method
      }
      WIDGET {
        NAME "helpButton"
        CLASS "XmPushButton"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmPushButton"
        x "2833" private
        y "4428" private
        labelString "Help" private
        activateCallback "colorSelectHelp" method
      }
    }
    WIDGET {
      NAME "scrolledWindow_1"
      CLASS "XmScrolledWindow"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmScrolledWindow"
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "10" private
      bottomWidget "colorText" private
      leftAttachment "XmATTACH_WIDGET" private
      leftOffset "10" private
      leftWidget "rowColumn_1" private
      rightAttachment "XmATTACH_FORM" private
      rightOffset "10" private
      topAttachment "XmATTACH_FORM" private
      topOffset "10" private
      WIDGET {
        NAME "colorList"
        CLASS "XmList"
        MANAGED "TRUE"
        QUICKHELP "Contents of rgb.txt."
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmList"
        scrollBarDisplayPolicy "XmSTATIC" private
        browseSelectionCallback "do_browseSelection" method
      }
    }
    WIDGET {
      NAME "frame_1"
      CLASS "XmFrame"
      MANAGED "TRUE"
      QUICKHELP ""
      HELPID "-1"
      VIEWDATA ""
      DESCRIPTION "XmFrame"
      height "47" private
      width "146" private
      x "0" private
      y "180" private
      bottomAttachment "XmATTACH_WIDGET" private
      bottomOffset "10" private
      bottomWidget "colorText" private
      leftAttachment "XmATTACH_FORM" private
      leftOffset "10" private
      rightAttachment "XmATTACH_WIDGET" private
      rightOffset "10" private
      rightWidget "scrolledWindow_1" private
      topAttachment "XmATTACH_WIDGET" private
      topOffset "10" private
      topWidget "rowColumn_1" private
      WIDGET {
        NAME "sampleColor"
        CLASS "XmLabel"
        MANAGED "TRUE"
        QUICKHELP ""
        HELPID "-1"
        VIEWDATA ""
        DESCRIPTION "XmLabel"
        x "316" private
        y "2414" private
        labelString " " private
      }
    }
  }
}
