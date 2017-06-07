object FormSetRand: TFormSetRand
  Left = 0
  Top = 0
  Caption = 'Set Rand Groups'
  ClientHeight = 345
  ClientWidth = 435
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GbTabs: TGroupBox
    Left = 8
    Top = 8
    Width = 105
    Height = 199
    Caption = 'Tabs To Change'
    TabOrder = 0
    object CbUp1: TCheckBox
      Left = 3
      Top = 22
      Width = 97
      Height = 17
      Caption = 'Upper Partial 1'
      TabOrder = 0
      OnClick = CheckBoxTabClick
    end
    object CbUp2: TCheckBox
      Tag = 1
      Left = 3
      Top = 45
      Width = 97
      Height = 17
      Caption = 'Upper Partial 2'
      TabOrder = 1
      OnClick = CheckBoxTabClick
    end
    object CbUc: TCheckBox
      Tag = 2
      Left = 3
      Top = 68
      Width = 97
      Height = 17
      Caption = 'Upper Common'
      TabOrder = 2
      OnClick = CheckBoxTabClick
    end
    object CbLp1: TCheckBox
      Tag = 3
      Left = 3
      Top = 91
      Width = 97
      Height = 17
      Caption = 'Lower Partial 1'
      TabOrder = 3
      OnClick = CheckBoxTabClick
    end
    object CbLp2: TCheckBox
      Tag = 4
      Left = 3
      Top = 114
      Width = 97
      Height = 17
      Caption = 'Lower Partial 2'
      TabOrder = 4
      OnClick = CheckBoxTabClick
    end
    object CbLc: TCheckBox
      Tag = 5
      Left = 3
      Top = 137
      Width = 97
      Height = 17
      Caption = 'Lower Common'
      TabOrder = 5
      OnClick = CheckBoxTabClick
    end
    object CbPatch: TCheckBox
      Tag = 6
      Left = 3
      Top = 160
      Width = 97
      Height = 17
      Caption = 'Patch'
      TabOrder = 6
      OnClick = CheckBoxTabClick
    end
  end
  object GbPartial: TGroupBox
    Left = 326
    Top = 8
    Width = 106
    Height = 329
    Caption = 'Partial'
    TabOrder = 3
    object c00: TCheckBox
      Left = 3
      Top = 20
      Width = 97
      Height = 17
      Caption = 'WG Pitch'
      TabOrder = 0
    end
    object c01: TCheckBox
      Tag = 1
      Left = 3
      Top = 40
      Width = 97
      Height = 17
      Caption = 'WG Mod'
      TabOrder = 1
    end
    object c03: TCheckBox
      Tag = 2
      Left = 3
      Top = 80
      Width = 97
      Height = 17
      Caption = 'WG Pulse Width'
      TabOrder = 2
    end
    object c08: TCheckBox
      Tag = 3
      Left = 3
      Top = 203
      Width = 97
      Height = 17
      Caption = 'TVF Mod'
      TabOrder = 3
    end
    object c04: TCheckBox
      Tag = 4
      Left = 3
      Top = 123
      Width = 97
      Height = 17
      Caption = 'TVF Bias'
      TabOrder = 4
    end
    object c06: TCheckBox
      Tag = 5
      Left = 3
      Top = 163
      Width = 97
      Height = 17
      Caption = 'TVF Env Level'
      TabOrder = 5
    end
    object c07: TCheckBox
      Tag = 6
      Left = 3
      Top = 183
      Width = 97
      Height = 17
      Caption = 'TVF Other'
      TabOrder = 6
    end
    object c13: TCheckBox
      Tag = 7
      Left = 3
      Top = 309
      Width = 97
      Height = 17
      Caption = 'TVA Mod'
      TabOrder = 7
    end
    object c10: TCheckBox
      Tag = 8
      Left = 3
      Top = 250
      Width = 97
      Height = 17
      Caption = 'TVA Env Time'
      TabOrder = 8
    end
    object c11: TCheckBox
      Tag = 9
      Left = 3
      Top = 270
      Width = 97
      Height = 17
      Caption = 'TVA Env Level'
      TabOrder = 9
    end
    object c12: TCheckBox
      Tag = 10
      Left = 3
      Top = 290
      Width = 97
      Height = 17
      Caption = 'TVA Other'
      TabOrder = 10
    end
    object c02: TCheckBox
      Tag = 1
      Left = 3
      Top = 60
      Width = 97
      Height = 17
      Caption = 'WG Wave'
      TabOrder = 11
    end
    object c09: TCheckBox
      Tag = 4
      Left = 3
      Top = 228
      Width = 97
      Height = 17
      Caption = 'TVA Bias'
      TabOrder = 12
    end
    object c05: TCheckBox
      Tag = 4
      Left = 3
      Top = 143
      Width = 97
      Height = 17
      Caption = 'TVF Env Time'
      TabOrder = 13
    end
  end
  object GbCommon: TGroupBox
    Left = 220
    Top = 8
    Width = 106
    Height = 329
    Caption = 'Common'
    TabOrder = 2
    object b02: TCheckBox
      Left = 3
      Top = 68
      Width = 97
      Height = 17
      Caption = 'P-Env Mod'
      TabOrder = 0
    end
    object b00: TCheckBox
      Tag = 1
      Left = 3
      Top = 22
      Width = 97
      Height = 17
      Caption = 'P-Env Time'
      TabOrder = 1
    end
    object b01: TCheckBox
      Tag = 2
      Left = 3
      Top = 45
      Width = 97
      Height = 17
      Caption = 'P-Env Level'
      TabOrder = 2
    end
    object b03: TCheckBox
      Tag = 3
      Left = 3
      Top = 91
      Width = 97
      Height = 17
      Caption = 'P-Env Other'
      TabOrder = 3
    end
    object b04: TCheckBox
      Tag = 4
      Left = 3
      Top = 114
      Width = 97
      Height = 17
      Caption = 'LFO 1'
      TabOrder = 4
    end
    object b05: TCheckBox
      Tag = 5
      Left = 3
      Top = 137
      Width = 97
      Height = 17
      Caption = 'LFO 2'
      TabOrder = 5
    end
    object b06: TCheckBox
      Tag = 6
      Left = 3
      Top = 159
      Width = 97
      Height = 17
      Caption = 'LFO 3'
      TabOrder = 6
    end
    object b07: TCheckBox
      Tag = 7
      Left = 3
      Top = 182
      Width = 97
      Height = 17
      Caption = 'Low EQ'
      TabOrder = 7
    end
    object b08: TCheckBox
      Tag = 8
      Left = 3
      Top = 205
      Width = 97
      Height = 17
      Caption = 'High EQ'
      TabOrder = 8
    end
    object b09: TCheckBox
      Tag = 9
      Left = 3
      Top = 228
      Width = 97
      Height = 17
      Caption = 'Chorus'
      TabOrder = 9
    end
    object b10: TCheckBox
      Tag = 10
      Left = 3
      Top = 251
      Width = 97
      Height = 17
      Caption = 'Partial Balance'
      TabOrder = 10
    end
  end
  object GbPatch: TGroupBox
    Left = 114
    Top = 8
    Width = 106
    Height = 199
    Caption = 'Patch'
    TabOrder = 1
    object a00: TCheckBox
      Left = 3
      Top = 22
      Width = 97
      Height = 17
      Caption = 'Reverb'
      TabOrder = 0
    end
    object a01: TCheckBox
      Tag = 1
      Left = 3
      Top = 45
      Width = 97
      Height = 17
      Caption = 'Tone Balance'
      TabOrder = 1
    end
    object a02: TCheckBox
      Tag = 2
      Left = 3
      Top = 68
      Width = 97
      Height = 17
      Caption = 'Chase'
      TabOrder = 2
    end
  end
  object PannelButtons: TPanel
    Left = 8
    Top = 213
    Width = 206
    Height = 124
    TabOrder = 4
    object ButtonOff: TButton
      Left = 66
      Top = 2
      Width = 58
      Height = 25
      Caption = 'Off'
      TabOrder = 0
      OnClick = ButtonOnOffClick
    end
    object ButtonCancel: TButton
      Left = 135
      Top = 96
      Width = 58
      Height = 25
      Hint = 'Restore rand flags as they were when this dialog was opened'
      Caption = '&Cancel'
      TabOrder = 1
      OnClick = ButtonCancelClick
    end
    object ButtonReplay: TButton
      Left = 135
      Top = 2
      Width = 58
      Height = 25
      Caption = 'Replay'
      TabOrder = 2
      OnClick = ButtonReplayClick
    end
    object ButtonOn: TButton
      Tag = 1
      Left = 4
      Top = 2
      Width = 58
      Height = 25
      Caption = 'On'
      TabOrder = 3
      OnClick = ButtonOnOffClick
    end
    object ButtonRandCurrent: TButton
      Left = 4
      Top = 33
      Width = 120
      Height = 25
      Hint = 'Randomize just the parameters most recently set to "On"'
      Caption = 'Rand Current'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = ButtonRandCurrentClick
    end
    object ButtonOk: TButton
      Left = 135
      Top = 65
      Width = 58
      Height = 25
      Hint = 'Keep rand flags as they now appear in main grid'
      Caption = 'OK'
      Default = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = ButtonCancelClick
    end
    object ButtonRandCumulative: TButton
      Left = 4
      Top = 65
      Width = 120
      Height = 25
      Caption = 'Rand Cumulative'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      OnClick = ButtonRandCumulativeClick
    end
    object ButtonRandAll: TButton
      Left = 4
      Top = 96
      Width = 120
      Height = 25
      Hint = 'Randomize all parameters that say "On" in all tabs'
      Caption = 'Rand Everything "On"'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      OnClick = ButtonRandAllClick
    end
    object ButtonSave: TButton
      Left = 135
      Top = 34
      Width = 58
      Height = 25
      Hint = 'Keep rand flags as they now appear in main grid'
      Caption = 'Save'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
      OnClick = ButtonSaveClick
    end
  end
  object MainMenu: TMainMenu
    Left = 128
    Top = 136
    object MenuFormSetRandPresets: TMenuItem
      Caption = '&Presets'
      object MenuFormSetRandNone: TMenuItem
        Caption = 'None'
        OnClick = MenuFormSetRandNoneClick
      end
      object MenuFormSetRandPartials: TMenuItem
        Caption = 'Partials'
        OnClick = MenuFormSetRandPartialsClick
      end
      object MenuFormSetRandCommons: TMenuItem
        Caption = 'Commons'
        OnClick = MenuFormSetRandCommonsClick
      end
      object MenuFormSetRandAll: TMenuItem
        Caption = 'All'
        OnClick = MenuFormSetRandAllClick
      end
    end
    object MenuFormSetRandUndo: TMenuItem
      Caption = '&Undo'
      Enabled = False
      OnClick = MenuFormSetRandUndoClick
    end
  end
end
