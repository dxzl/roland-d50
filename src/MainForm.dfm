object FormMain: TFormMain
  Left = 0
  Top = 0
  ActiveControl = Memo1
  Caption = 'Roland D-50'
  ClientHeight = 272
  ClientWidth = 612
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
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
    Height = 272
    Align = alLeft
    TabOrder = 0
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
      Height = 228
      Align = alClient
      FileEdit = Edit1
      ItemHeight = 13
      Mask = '*.d50'
      PopupMenu = PopupMenuFileListBox
      TabOrder = 1
      OnDblClick = FileListBox1DblClick
    end
    object Edit1: TEdit
      Left = 1
      Top = 250
      Width = 135
      Height = 21
      Align = alBottom
      TabOrder = 2
      Text = '*.d50'
    end
  end
  object Panel1: TPanel
    Left = 137
    Top = 0
    Width = 475
    Height = 272
    Align = alClient
    TabOrder = 1
    object Memo1: TMemo
      Left = 1
      Top = 63
      Width = 472
      Height = 208
      Align = alCustom
      Anchors = [akLeft, akTop, akRight, akBottom]
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
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
