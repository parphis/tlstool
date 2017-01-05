object wBackup: TwBackup
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  ClientHeight = 303
  ClientWidth = 594
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object filename_l: TLabel
    Left = 21
    Top = 26
    Width = 49
    Height = 13
    Caption = 'File name:'
  end
  object author_l: TLabel
    Left = 21
    Top = 51
    Width = 66
    Height = 13
    Caption = 'Author name:'
  end
  object date_l: TLabel
    Left = 362
    Top = 51
    Width = 70
    Height = 13
    Caption = 'Creation date:'
  end
  object notes_l: TLabel
    Left = 21
    Top = 209
    Width = 28
    Height = 13
    Caption = 'Notes'
  end
  object ok_btn: TButton
    Left = 424
    Top = 270
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 7
    OnClick = ok_btnClick
  end
  object filename_e: TEdit
    Left = 107
    Top = 23
    Width = 431
    Height = 21
    TabOrder = 0
  end
  object authorname_e: TEdit
    Left = 107
    Top = 48
    Width = 239
    Height = 21
    TabOrder = 2
  end
  object date_dtp: TDateTimePicker
    Left = 438
    Top = 48
    Width = 142
    Height = 21
    Date = 39115.000000000000000000
    Time = 39115.000000000000000000
    TabOrder = 3
  end
  object station_gb: TGroupBox
    Left = 21
    Top = 82
    Width = 325
    Height = 117
    Caption = 'Station'
    TabOrder = 4
    object address_l: TLabel
      Left = 12
      Top = 83
      Width = 39
      Height = 13
      Caption = 'Address'
    end
    object name_l: TLabel
      Left = 13
      Top = 56
      Width = 63
      Height = 13
      Caption = 'Station name'
    end
    object place_l: TLabel
      Left = 12
      Top = 29
      Width = 25
      Height = 13
      Caption = 'Place'
    end
    object address_e: TEdit
      Left = 110
      Top = 80
      Width = 203
      Height = 21
      TabOrder = 2
    end
    object name_e: TEdit
      Left = 110
      Top = 26
      Width = 203
      Height = 21
      TabOrder = 0
    end
    object place_e: TEdit
      Left = 110
      Top = 53
      Width = 203
      Height = 21
      TabOrder = 1
    end
  end
  object device_gb: TGroupBox
    Left = 352
    Top = 82
    Width = 228
    Height = 117
    Caption = 'Device'
    TabOrder = 5
    object serialnr_l: TLabel
      Left = 24
      Top = 56
      Width = 65
      Height = 13
      Caption = 'Serial number'
    end
    object type_l: TLabel
      Left = 24
      Top = 29
      Width = 24
      Height = 13
      Caption = 'Type'
    end
    object serialnr_e: TEdit
      Left = 95
      Top = 53
      Width = 121
      Height = 21
      TabOrder = 1
    end
    object type_e: TEdit
      Left = 94
      Top = 26
      Width = 121
      Height = 21
      TabOrder = 0
    end
  end
  object notes_e: TEdit
    Left = 21
    Top = 228
    Width = 559
    Height = 21
    TabOrder = 6
  end
  object open_btn: TButton
    Left = 543
    Top = 23
    Width = 37
    Height = 22
    Caption = '...'
    TabOrder = 1
    OnClick = open_btnClick
  end
  object cancel_btn: TButton
    Left = 505
    Top = 270
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
  end
  object open_dlg: TOpenDialog
    Filter = 'TLS Configuration Files (*.tls)|*.tls'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
  end
end
