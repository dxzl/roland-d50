object FormSetRandInterval: TFormSetRandInterval
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Randomization Interval'
  ClientHeight = 103
  ClientWidth = 193
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 177
    Height = 57
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 133
      Height = 13
      Caption = 'Randomization interval (ms)'
    end
    object Edit1: TEdit
      Left = 31
      Top = 29
      Width = 89
      Height = 21
      TabOrder = 0
      Text = '7,000'
    end
    object UpDown1: TUpDown
      Left = 15
      Top = 29
      Width = 17
      Height = 21
      AlignButton = udLeft
      Associate = Edit1
      Min = 3000
      Max = 500000
      Increment = 1000
      Position = 7000
      TabOrder = 1
    end
  end
  object ButtonOk: TButton
    Left = 14
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object ButtonCancel: TButton
    Left = 101
    Top = 70
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
