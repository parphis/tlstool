object PortOptionsW: TPortOptionsW
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  ClientHeight = 393
  ClientWidth = 406
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object portname_l: TLabel
    Left = 18
    Top = 23
    Width = 27
    Height = 13
    Caption = 'Name'
  end
  object baudrate_l: TLabel
    Left = 18
    Top = 50
    Width = 47
    Height = 13
    Caption = 'Baud rate'
  end
  object parity_l: TLabel
    Left = 18
    Top = 77
    Width = 28
    Height = 13
    Caption = 'Parity'
  end
  object stopbit_l: TLabel
    Left = 18
    Top = 104
    Width = 34
    Height = 13
    Caption = 'Stopbit'
  end
  object bytesize_l: TLabel
    Left = 18
    Top = 131
    Width = 43
    Height = 13
    Caption = 'Byte size'
  end
  object OKBtn: TButton
    Left = 211
    Top = 357
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 292
    Top = 357
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object baudrate_cb: TComboBox
    Left = 78
    Top = 47
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 2
    Text = 'baudrate_cb'
    Items.Strings = (
      '110'
      '300'
      '600'
      '1200'
      '2400'
      '4800'
      '9600'
      '14400'
      '19200'
      '38400'
      '56000'
      '57600'
      '115200'
      '128000'
      '256000')
  end
  object parity_cb: TComboBox
    Left = 78
    Top = 74
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    Text = 'parity_cb'
    Items.Strings = (
      'NO'
      'ODD'
      'EVEN'
      'MARK'
      'SPACE')
  end
  object stopbit_cb: TComboBox
    Left = 78
    Top = 101
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = 'stopbit_cb'
    Items.Strings = (
      'ONE'
      'ONEANDHALF'
      'TWO')
  end
  object bytesize_cb: TComboBox
    Left = 78
    Top = 128
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 5
    Text = 'bytesize_cb'
    Items.Strings = (
      '5'
      '6'
      '7'
      '8')
  end
  object timeouts_gb: TGroupBox
    Left = 18
    Top = 167
    Width = 370
    Height = 174
    Caption = 'Time outs'
    TabOrder = 6
    object readint_l: TLabel
      Left = 21
      Top = 27
      Width = 64
      Height = 13
      Caption = 'Read interval'
    end
    object readmulti_l: TLabel
      Left = 21
      Top = 54
      Width = 62
      Height = 13
      Caption = 'Read multipl.'
    end
    object readconst_l: TLabel
      Left = 21
      Top = 81
      Width = 58
      Height = 13
      Caption = 'Read const.'
    end
    object writemulti_l: TLabel
      Left = 21
      Top = 108
      Width = 63
      Height = 13
      Caption = 'Write multipl.'
    end
    object writeconst_l: TLabel
      Left = 21
      Top = 135
      Width = 59
      Height = 13
      Caption = 'Write const.'
    end
    object writerep_l: TLabel
      Left = 188
      Top = 27
      Width = 75
      Height = 13
      Caption = 'Write repetition'
    end
    object readrep_l: TLabel
      Left = 188
      Top = 56
      Width = 74
      Height = 13
      Caption = 'Read repetition'
    end
    object readint_e: TEdit
      Left = 99
      Top = 24
      Width = 50
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object readmulti_e: TEdit
      Left = 99
      Top = 51
      Width = 50
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object readconst_e: TEdit
      Left = 99
      Top = 78
      Width = 50
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object writemulti_e: TEdit
      Left = 99
      Top = 105
      Width = 50
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object writeconst_e: TEdit
      Left = 99
      Top = 132
      Width = 50
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object writerep_e: TEdit
      Left = 278
      Top = 24
      Width = 50
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object readrep_e: TEdit
      Left = 278
      Top = 51
      Width = 50
      Height = 21
      TabOrder = 6
      Text = '0'
    end
    object readint_ud: TUpDown
      Left = 149
      Top = 24
      Width = 15
      Height = 21
      Associate = readint_e
      TabOrder = 7
    end
    object readmulti_ud: TUpDown
      Left = 149
      Top = 51
      Width = 15
      Height = 21
      Associate = readmulti_e
      TabOrder = 8
    end
    object readconst_ud: TUpDown
      Left = 149
      Top = 78
      Width = 15
      Height = 21
      Associate = readconst_e
      TabOrder = 9
    end
    object writemulti_ud: TUpDown
      Left = 149
      Top = 105
      Width = 15
      Height = 21
      Associate = writemulti_e
      TabOrder = 10
    end
    object writeconst_ud: TUpDown
      Left = 149
      Top = 132
      Width = 15
      Height = 21
      Associate = writeconst_e
      TabOrder = 11
    end
    object writerep_ud: TUpDown
      Left = 328
      Top = 24
      Width = 15
      Height = 21
      Associate = writerep_e
      TabOrder = 12
    end
    object readrep_ud: TUpDown
      Left = 328
      Top = 51
      Width = 15
      Height = 21
      Associate = readrep_e
      TabOrder = 13
    end
  end
  object portnames_e: TComboBox
    Left = 78
    Top = 20
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 7
    Text = 'portnames_e'
  end
end
