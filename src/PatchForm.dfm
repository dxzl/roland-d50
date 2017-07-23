object FormPatch: TFormPatch
  Left = 0
  Top = 0
  Caption = 'Roland D-50 Temporary Area'
  ClientHeight = 240
  ClientWidth = 601
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Icon.Data = {
    000001000200101010000000000028010000260000002020100000000000E802
    00004E0100002800000010000000200000000100040000000000C00000000000
    0000000000000000000000000000000000000000800000800000008080008000
    00008000800080800000C0C0C000808080000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00999AAACCCBBB5555999AAACCCBBB5555999A
    AACCCBBB5555999AAACCCBBB5555999AAACCCBBB5555999AAACCCBBB5555999A
    AACCCBBB5555999AAACCCBBB5555999AAACCCBBB5555999AAACCCBBB5555999A
    AACCCBBB5555999AAACCCBBB5555999AAACCCBBB5555999AAACCCBBB5555999A
    AACCCBBB5555999AAACCCBBB5555000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000280000002000000040000000010004000000
    0000800200000000000000000000000000000000000000000000000080000080
    000000808000800000008000800080800000C0C0C000808080000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00CCCCDDDDDD0099990000
    000000444400CCCCCDDDDD0009999900000004000040CCCCCCCDDD000A999999
    000040000004CC55CCCCDD000AAA9999900040000004CC55CCCCDDD00AAAA999
    990040000004CC5555CCCCD00AAAAAA9999040000004CCC5555CCCC000AAAAAA
    999904000040CCC55555CCC000AAAAAAA999004444000CC5555555CC00AAAAAA
    A999000000000CC5555555CC00AAAAAAA999000000000CCC5555555CC00AAAAA
    A999000000000CCC5555555CC00AAAAA99900000000000CC5555555CC00AAAA9
    99900000000000CC55555555CC0AAAA999000000000000CCC5555555CC00AA99
    90000000000000CCC5555555CC00AA99000000000000000CC5555555CC00A999
    000000000000000CC5555555CC000999000000000000000CC5555555CC000999
    000000000000000CCC55555CCC000B99000000000000000CCC55555CC2000B99
    9000000000000000CC55555CC2000BB99900000000000000CC5555CCC2200BB9
    9990000000000000CCC555CCC22000BB9999000000000000CCC55CCC222000BB
    B9999000000000000CC5CCCC222200BBBBB99990000000000CCCCCC2222200BB
    BBBB9999900000000CCCCC222222000BBBBBBB999900000000CCC00000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000FFC300003F910000
    0F46000007420000035A00000142000000BD000000C3800000FF800000FF8000
    00FF800001FFC00001FFC00003FFC00007FFC0000FFFE0000FFFE0000FFFE000
    0FFFE0000FFFE00007FFF00003FFF00001FFF00000FFF000007FF800001FF800
    0007F8000003F8000003F8000003FFFFFFFFFFFFFFFF}
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Tag = 6
    Left = 0
    Top = 0
    Width = 601
    Height = 216
    ActivePage = UpperPartial1
    Align = alClient
    PopupMenu = PopupMenu1
    TabOrder = 0
    ExplicitHeight = 200
    object UpperPartial1: TTabSheet
      Caption = 'Upper Partial 1'
      ExplicitHeight = 172
      object UpperPartial1SG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 188
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ExplicitHeight = 172
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object UpperPartial2: TTabSheet
      Caption = 'Upper Partial 2'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object UpperPartial2SG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 205
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object UpperCommon: TTabSheet
      Caption = 'Upper Common'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object UpperCommonSG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 205
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object LowerPartial1: TTabSheet
      Caption = 'Lower Partial 1'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object LowerPartial1SG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 205
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object LowerPartial2: TTabSheet
      Caption = 'Lower Partial 2'
      ImageIndex = 4
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object LowerPartial2SG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 205
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor, goThumbTracking]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object LowerCommon: TTabSheet
      Caption = 'Lower Common'
      ImageIndex = 5
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object LowerCommonSG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 205
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object Patch: TTabSheet
      Caption = 'Patch'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object PatchSG: TStringGrid
        Left = 0
        Top = 0
        Width = 593
        Height = 205
        Align = alClient
        ColCount = 4
        DefaultColWidth = 135
        RowCount = 65
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goEditing, goAlwaysShowEditor]
        ScrollBars = ssVertical
        TabOrder = 0
        OnDblClick = SGDblClick
        ColWidths = (
          135
          135
          135
          135)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 216
    Width = 601
    Height = 24
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 200
    object LabelRand: TLabel
      Left = 24
      Top = 6
      Width = 93
      Height = 13
      Caption = 'Randomization: Off'
      OnClick = LabelRandClick
    end
    object ButtonRandInterval: TButton
      Left = 8
      Top = 8
      Width = 10
      Height = 10
      Hint = 'Click to change randomization interval'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = ButtonRandIntervalClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 512
    object MenuFormPatchMenu: TMenuItem
      Caption = '&Menu'
      ShortCut = 119
      object MenuItemFormPatchAllNotesOff: TMenuItem
        Caption = '&All notes off'
        ShortCut = 113
        OnClick = MenuItemFormPatchAllNotesOffClick
      end
      object MenuItemFormPatchRename: TMenuItem
        Caption = 'Re&name patch'
        ShortCut = 114
        OnClick = MenuItemFormRenamePatchClick
      end
      object MenuItemFormPatchChange: TMenuItem
        Caption = '&Change patch number'
        ShortCut = 115
        OnClick = MenuItemFormPatchChangeClick
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object MenuItemFormPatchStartStopRandom: TMenuItem
        Caption = 'Randomization (start/stop)'
        ShortCut = 116
        OnClick = MenuItemFormPatchStartStopRandomClick
      end
      object MenuItemFormPatchManualRandomize: TMenuItem
        Caption = '&Manual randomize (one-shot)'
        ShortCut = 117
        OnClick = MenuItemFormPatchManualRandomizeClick
      end
      object MenuItemFormPatchSetRandInterval: TMenuItem
        Caption = 'Set Randomization &Interval'
        OnClick = MenuItemFormPatchSetRandIntervalClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object MenuItemFormPatchWriteToFile: TMenuItem
        Caption = '&Save as .d50 patch file'
        ShortCut = 118
        OnClick = MenuItemFormPatchWriteFileClick
      end
      object Exportpatchtosyxbinaryfile1: TMenuItem
        Caption = '&Export as .syx binary patch file'
        OnClick = MenuItemFormPatchWriteSYXFileClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object MenuItemFormPatchPlay: TMenuItem
        Caption = '&Play patch'
        ShortCut = 120
        OnClick = MenuItemFormPatchPlayClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object MenuItemFormPatchRead: TMenuItem
        Caption = '&Read D-50 temp area'
        ShortCut = 121
        OnClick = MenuItemFormPatchReadTempClick
      end
      object MenuItemFormPatchWrite: TMenuItem
        Caption = '&Write D-50 temp area'
        ShortCut = 122
        OnClick = MenuItemFormPatchWriteTempClick
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object MenuItemFormPatchEnforceMinMaxValue: TMenuItem
        Caption = '&Limit to min/max values'
        ShortCut = 123
        OnClick = MenuItemFormPatchLimitToMinMaxValueClick
      end
    end
    object MenuFormPatchPresets: TMenuItem
      Caption = '&Presets'
      object MenuPresetsItemPreset11: TMenuItem
        Caption = 'Preset 1'
        OnClick = MenuPresetsItemClick
      end
      object MenuPresetsItemPreset2: TMenuItem
        Tag = 1
        Caption = 'Preset 2'
        OnClick = MenuPresetsItemClick
      end
      object MenuPresetsItemPreset3: TMenuItem
        Tag = 2
        Caption = 'Preset 3'
        OnClick = MenuPresetsItemClick
      end
      object MenuPresetsItemPreset4: TMenuItem
        Tag = 3
        Caption = 'Preset 4'
        OnClick = MenuPresetsItemClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object MenuPresetsItemSetAll: TMenuItem
        Tag = 101
        Caption = '&Set All (Default)'
        OnClick = MenuPresetsItemClick
      end
      object MenuPresetsItemClearAll: TMenuItem
        Tag = 100
        Caption = '&Clear All'
        OnClick = MenuPresetsItemClick
      end
    end
    object MenuPatchFormSetRand: TMenuItem
      Caption = '&Rand'
      OnClick = MenuPatchFormSetRandClick
    end
    object MenuHelp: TMenuItem
      Caption = '&Help'
      OnClick = MenuHelpClick
    end
  end
  object TimerSendPatch: TTimer
    Enabled = False
    Interval = 5000
    OnTimer = TimerSendPatchTimer
    Left = 340
    Top = 152
  end
  object TimerOver10Percent: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = TimerOver10PercentTimer
    Left = 236
    Top = 152
  end
  object PopupMenu1: TPopupMenu
    Left = 428
    Top = 152
    object ManuPopupCopyVals: TMenuItem
      Caption = '&Copy'
      OnClick = ManuPopupCopyValsClick
    end
    object ManuPopupPasteVals: TMenuItem
      Caption = '&Paste'
      OnClick = ManuPopupPasteValsClick
    end
  end
end
