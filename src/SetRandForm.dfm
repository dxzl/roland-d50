object FormSetRand: TFormSetRand
  Left = 0
  Top = 0
  AutoSize = True
  Caption = 'Set Rand Groups'
  ClientHeight = 329
  ClientWidth = 424
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
  Menu = MainMenu
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GbTabs: TGroupBox
    Left = 0
    Top = 0
    Width = 105
    Height = 199
    Caption = 'Tabs To Change'
    TabOrder = 0
    object CbUp1: TCheckBox
      Tag = 1
      Left = 3
      Top = 22
      Width = 97
      Height = 17
      Caption = 'Upper Partial 1'
      TabOrder = 0
      OnClick = CheckBoxTabClick
    end
    object CbUp2: TCheckBox
      Tag = 2
      Left = 3
      Top = 45
      Width = 97
      Height = 17
      Caption = 'Upper Partial 2'
      TabOrder = 1
      OnClick = CheckBoxTabClick
    end
    object CbUc: TCheckBox
      Tag = 3
      Left = 3
      Top = 68
      Width = 97
      Height = 17
      Caption = 'Upper Common'
      TabOrder = 2
      OnClick = CheckBoxTabClick
    end
    object CbLp1: TCheckBox
      Tag = 4
      Left = 3
      Top = 91
      Width = 97
      Height = 17
      Caption = 'Lower Partial 1'
      TabOrder = 3
      OnClick = CheckBoxTabClick
    end
    object CbLp2: TCheckBox
      Tag = 5
      Left = 3
      Top = 114
      Width = 97
      Height = 17
      Caption = 'Lower Partial 2'
      TabOrder = 4
      OnClick = CheckBoxTabClick
    end
    object CbLc: TCheckBox
      Tag = 6
      Left = 3
      Top = 137
      Width = 97
      Height = 17
      Caption = 'Lower Common'
      TabOrder = 5
      OnClick = CheckBoxTabClick
    end
    object CbPatch: TCheckBox
      Tag = 7
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
    Left = 318
    Top = 0
    Width = 106
    Height = 329
    Caption = 'Partial'
    TabOrder = 3
    object c00: TCheckBox
      Tag = 1
      Left = 3
      Top = 20
      Width = 97
      Height = 17
      Caption = 'WG Pitch'
      TabOrder = 0
    end
    object c01: TCheckBox
      Tag = 2
      Left = 3
      Top = 40
      Width = 97
      Height = 17
      Caption = 'WG Mod'
      TabOrder = 1
    end
    object c03: TCheckBox
      Tag = 4
      Left = 3
      Top = 83
      Width = 97
      Height = 17
      Caption = 'WG Pulse Width'
      TabOrder = 3
    end
    object c08: TCheckBox
      Tag = 9
      Left = 3
      Top = 197
      Width = 97
      Height = 17
      Caption = 'TVF Mod'
      TabOrder = 8
    end
    object c04: TCheckBox
      Tag = 5
      Left = 3
      Top = 114
      Width = 97
      Height = 17
      Caption = 'TVF Bias'
      TabOrder = 4
    end
    object c06: TCheckBox
      Tag = 7
      Left = 3
      Top = 154
      Width = 97
      Height = 17
      Caption = 'TVF Env Level'
      TabOrder = 6
    end
    object c07: TCheckBox
      Tag = 8
      Left = 3
      Top = 174
      Width = 97
      Height = 17
      Caption = 'TVF Other'
      TabOrder = 7
    end
    object c13: TCheckBox
      Tag = 14
      Left = 3
      Top = 309
      Width = 97
      Height = 17
      Caption = 'TVA Mod'
      TabOrder = 13
    end
    object c10: TCheckBox
      Tag = 11
      Left = 3
      Top = 250
      Width = 97
      Height = 17
      Caption = 'TVA Env Time'
      TabOrder = 10
    end
    object c11: TCheckBox
      Tag = 12
      Left = 3
      Top = 270
      Width = 97
      Height = 17
      Caption = 'TVA Env Level'
      TabOrder = 11
    end
    object c12: TCheckBox
      Tag = 13
      Left = 3
      Top = 290
      Width = 97
      Height = 17
      Caption = 'TVA Other'
      TabOrder = 12
    end
    object c02: TCheckBox
      Tag = 3
      Left = 3
      Top = 60
      Width = 97
      Height = 17
      Caption = 'WG Wave'
      TabOrder = 2
    end
    object c09: TCheckBox
      Tag = 10
      Left = 3
      Top = 228
      Width = 97
      Height = 17
      Caption = 'TVA Bias'
      TabOrder = 9
    end
    object c05: TCheckBox
      Tag = 6
      Left = 3
      Top = 134
      Width = 97
      Height = 17
      Caption = 'TVF Env Time'
      TabOrder = 5
    end
  end
  object GbCommon: TGroupBox
    Left = 212
    Top = 0
    Width = 106
    Height = 329
    Caption = 'Common'
    TabOrder = 2
    object b02: TCheckBox
      Tag = 3
      Left = 3
      Top = 68
      Width = 97
      Height = 17
      Caption = 'P-Env Mod'
      TabOrder = 2
    end
    object b00: TCheckBox
      Tag = 1
      Left = 3
      Top = 22
      Width = 97
      Height = 17
      Caption = 'P-Env Time'
      TabOrder = 0
    end
    object b01: TCheckBox
      Tag = 2
      Left = 3
      Top = 45
      Width = 97
      Height = 17
      Caption = 'P-Env Level'
      TabOrder = 1
    end
    object b03: TCheckBox
      Tag = 4
      Left = 3
      Top = 91
      Width = 97
      Height = 17
      Caption = 'P-Env Other'
      TabOrder = 3
    end
    object b04: TCheckBox
      Tag = 5
      Left = 3
      Top = 131
      Width = 97
      Height = 17
      Caption = 'LFO 1'
      TabOrder = 4
    end
    object b05: TCheckBox
      Tag = 6
      Left = 3
      Top = 154
      Width = 97
      Height = 17
      Caption = 'LFO 2'
      TabOrder = 5
    end
    object b06: TCheckBox
      Tag = 7
      Left = 3
      Top = 176
      Width = 97
      Height = 17
      Caption = 'LFO 3'
      TabOrder = 6
    end
    object b07: TCheckBox
      Tag = 8
      Left = 3
      Top = 211
      Width = 97
      Height = 17
      Caption = 'Low EQ'
      TabOrder = 7
    end
    object b08: TCheckBox
      Tag = 9
      Left = 3
      Top = 234
      Width = 97
      Height = 17
      Caption = 'High EQ'
      TabOrder = 8
    end
    object b09: TCheckBox
      Tag = 10
      Left = 3
      Top = 267
      Width = 97
      Height = 17
      Caption = 'Chorus'
      TabOrder = 9
    end
    object b10: TCheckBox
      Tag = 11
      Left = 3
      Top = 290
      Width = 97
      Height = 17
      Caption = 'Partial Balance'
      TabOrder = 10
    end
  end
  object GbPatch: TGroupBox
    Left = 106
    Top = 0
    Width = 106
    Height = 199
    Caption = 'Patch'
    TabOrder = 1
    object a00: TCheckBox
      Tag = 1
      Left = 3
      Top = 22
      Width = 97
      Height = 17
      Caption = 'Reverb'
      TabOrder = 0
    end
    object a01: TCheckBox
      Tag = 2
      Left = 3
      Top = 45
      Width = 97
      Height = 17
      Caption = 'Tone Balance'
      TabOrder = 1
    end
    object a02: TCheckBox
      Tag = 3
      Left = 3
      Top = 68
      Width = 97
      Height = 17
      Caption = 'Chase'
      TabOrder = 2
    end
  end
  object PannelButtons: TPanel
    Left = 0
    Top = 205
    Width = 206
    Height = 124
    TabOrder = 4
    object ButtonOff: TButton
      Left = 66
      Top = 2
      Width = 58
      Height = 25
      Caption = 'Off'
      TabOrder = 1
      OnClick = ButtonOnOffClick
    end
    object ButtonCancel: TButton
      Left = 135
      Top = 96
      Width = 58
      Height = 25
      Hint = 'Restore rand flags as they were when this dialog was opened'
      Caption = '&Cancel'
      TabOrder = 8
      OnClick = ButtonCancelClick
    end
    object ButtonReplay: TButton
      Left = 135
      Top = 2
      Width = 58
      Height = 25
      Caption = 'Replay'
      TabOrder = 5
      OnClick = ButtonReplayClick
    end
    object ButtonOn: TButton
      Tag = 1
      Left = 4
      Top = 2
      Width = 58
      Height = 25
      Caption = 'On'
      TabOrder = 0
      OnClick = ButtonOnOffClick
    end
    object ButtonRandCurrent: TButton
      Left = 4
      Top = 33
      Width = 120
      Height = 25
      Hint = 'Randomize only the checked parameters in this box.'
      Caption = 'Rand Current'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
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
      TabOrder = 7
      OnClick = ButtonOkClick
    end
    object ButtonRandCumulative: TButton
      Left = 4
      Top = 65
      Width = 120
      Height = 25
      Hint = 'Randomize only parameters set "On" since this box opened (F6)'
      Caption = 'Rand Cumulative'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = ButtonRandCumulativeClick
    end
    object ButtonRandAll: TButton
      Left = 4
      Top = 96
      Width = 120
      Height = 25
      Hint = 'Randomize all parameters that say "On" in all tabs'
      Caption = 'Rand "On"'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = ButtonRandAllClick
    end
    object ButtonSave: TButton
      Left = 135
      Top = 34
      Width = 58
      Height = 25
      Hint = 'Keep rand flags as they now appear in main grid'
      Caption = 'Save (F7)'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
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
    object MenuFormSetRandHelp: TMenuItem
      Caption = '&Help'
      OnClick = MenuFormSetRandHelpClick
    end
  end
end
