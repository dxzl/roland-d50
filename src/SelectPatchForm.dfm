object FormSelectPatch: TFormSelectPatch
  Left = 0
  Top = 0
  ActiveControl = ComboBox1
  BorderStyle = bsDialog
  Caption = 'Select Patch'
  ClientHeight = 176
  ClientWidth = 189
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
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 16
    Top = 8
    Width = 156
    Height = 121
    TabOrder = 0
    object ComboBox1: TComboBox
      Left = 41
      Top = 85
      Width = 72
      Height = 21
      ItemIndex = 0
      TabOrder = 0
      Text = '11'
      Items.Strings = (
        '11'
        '12'
        '13'
        '14'
        '15'
        '16'
        '17'
        '18'
        '21'
        '22'
        '23'
        '24'
        '25'
        '26'
        '27'
        '28'
        '31'
        '32'
        '33'
        '34'
        '35'
        '36'
        '37'
        '38'
        '41'
        '42'
        '43'
        '44'
        '45'
        '46'
        '47'
        '48'
        '51'
        '52'
        '53'
        '54'
        '55'
        '56'
        '57'
        '58'
        '61'
        '62'
        '63'
        '64'
        '65'
        '66'
        '67'
        '68'
        '71'
        '72'
        '73'
        '74'
        '75'
        '76'
        '77'
        '78'
        '81'
        '82'
        '83'
        '84'
        '85'
        '86'
        '87'
        '88')
    end
    object RadioGroup1: TRadioGroup
      Left = 9
      Top = 11
      Width = 137
      Height = 68
      Caption = 'D-50 Patch Source'
      ItemIndex = 0
      Items.Strings = (
        'Internal'
        'Memory Card')
      TabOrder = 1
    end
  end
  object ButtonOk: TButton
    Left = 16
    Top = 135
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object ButtonCancel: TButton
    Left = 97
    Top = 135
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
