object FormMain: TFormMain
  Left = 0
  Top = 0
  ActiveControl = Memo1
  Caption = 'Roland D-50'
  ClientHeight = 268
  ClientWidth = 612
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
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 137
    Height = 268
    Align = alLeft
    TabOrder = 0
    ExplicitHeight = 241
    object FilterComboBox1: TFilterComboBox
      Left = 1
      Top = 1
      Width = 135
      Height = 21
      Align = alTop
      FileList = FileListBox1
      Filter = 
        'Patch file (*.d50)|*.d50|SYX File (*.syx)|*.syx|All files (*.*)|' +
        '*.*'
      TabOrder = 0
    end
    object FileListBox1: TFileListBox
      Left = 1
      Top = 22
      Width = 135
      Height = 224
      Align = alClient
      FileEdit = Edit1
      ItemHeight = 13
      Mask = '*.d50'
      PopupMenu = PopupMenuFileListBox
      TabOrder = 1
      OnDblClick = FileListBox1DblClick
      ExplicitHeight = 197
    end
    object Edit1: TEdit
      Left = 1
      Top = 246
      Width = 135
      Height = 21
      Align = alBottom
      TabOrder = 2
      Text = '*.d50'
      ExplicitTop = 219
    end
  end
  object Panel1: TPanel
    Left = 137
    Top = 0
    Width = 475
    Height = 268
    Align = alClient
    TabOrder = 1
    ExplicitHeight = 241
    object Memo1: TMemo
      Left = 1
      Top = 63
      Width = 472
      Height = 204
      Align = alCustom
      Anchors = [akLeft, akTop, akRight, akBottom]
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      ExplicitHeight = 177
    end
    object Panel3: TPanel
      Left = 6
      Top = 8
      Width = 459
      Height = 49
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      object LabelMidiInDevice: TLabel
        Left = 48
        Top = 5
        Width = 82
        Height = 13
        Caption = 'Midi Input Device'
      end
      object LabelMidiOutDevice: TLabel
        Left = 240
        Top = 5
        Width = 90
        Height = 13
        Caption = 'Midi Output Device'
      end
      object LabelMidiChan: TLabel
        Left = 392
        Top = 5
        Width = 46
        Height = 13
        Caption = 'Midi Chan'
      end
      object ComboBoxMidiOut: TComboBox
        Left = 200
        Top = 24
        Width = 169
        Height = 21
        Hint = 'Connect Midi-in on the S950 to this device'#39's midi-out'
        Style = csDropDownList
        TabOrder = 0
        OnChange = ComboBoxMidiOutChange
      end
      object ComboBoxMidiIn: TComboBox
        Left = 8
        Top = 24
        Width = 169
        Height = 21
        Hint = 'Connect Midi-out on the S950 to this device'#39's midi-in'
        Style = csDropDownList
        TabOrder = 1
        OnChange = ComboBoxMidiInChange
      end
      object ButtonRefreshDevs: TButton
        Left = 8
        Top = 5
        Width = 13
        Height = 13
        Hint = 'Refresh Devices'
        TabOrder = 2
        OnClick = ButtonRefreshDevsClick
      end
      object ComboBoxMidiChan: TComboBox
        Left = 391
        Top = 24
        Width = 50
        Height = 21
        Hint = 'This selects the common-mode channel on which to transfer data'
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 3
        Text = '1'
        OnChange = ComboBoxMidiChanChange
        Items.Strings = (
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16')
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 504
    Top = 208
  end
  object SaveDialog1: TSaveDialog
    Left = 440
    Top = 208
  end
  object MainMenu1: TMainMenu
    Left = 344
    Top = 208
    object S9001: TMenuItem
      Caption = 'Menu'
      ShortCut = 16496
      object MenuOpenFile: TMenuItem
        Caption = '&Open Selected File'
        ShortCut = 16497
        OnClick = MenuOpenFileClick
      end
      object MenuItemSetWorkingDirectoryPath: TMenuItem
        Caption = '&Working Directory Path'
        ShortCut = 16498
        OnClick = MenuItemSetWorkingDirectoryPathClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object MenuGetTempArea: TMenuItem
        Caption = '&Get temp area'
        ShortCut = 16499
        OnClick = MenuGetTempAreaClick
      end
      object MenuPutTempArea: TMenuItem
        Caption = '&Put temp area'
        ShortCut = 16500
        OnClick = MenuPutTempAreaClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object SaveAll64PatchesinPatchSave1: TMenuItem
        Caption = '&Save All 64 Patches in ./PatchSave'
        ShortCut = 16501
        OnClick = SaveAll64PatchesinPatchSave1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object MenuViewPatchGrid: TMenuItem
        Caption = '&View Patch Grid'
        ShortCut = 16506
        OnClick = MenuViewPatchGridClick
      end
      object MenuHelp: TMenuItem
        Caption = '&About'
        ShortCut = 16507
        OnClick = MenuAboutClick
      end
    end
  end
  object Timer1: TTimer
    Left = 184
    Top = 208
  end
  object PopupMenuFileListBox: TPopupMenu
    Left = 48
    Top = 192
    object PopupMenuItemOpen: TMenuItem
      Caption = '&Open'
      OnClick = PopupMenuItemOpenClick
    end
    object PopupMenuItemDelete: TMenuItem
      Caption = '&Delete'
      OnClick = PopupMenuItemDeleteClick
    end
  end
end
