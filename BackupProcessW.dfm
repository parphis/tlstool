object wBackupProcess: TwBackupProcess
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Processing...'
  ClientHeight = 173
  ClientWidth = 596
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object inprocess_l: TLabel
    Left = 18
    Top = 13
    Width = 81
    Height = 13
    Caption = 'Current process:'
  end
  object error_l: TLabel
    Left = 18
    Top = 65
    Width = 116
    Height = 13
    Caption = 'Error(s) and warning(s):'
  end
  object curproc_l: TLabel
    Left = 131
    Top = 13
    Width = 3
    Height = 13
  end
  object CancelBtn: TButton
    Left = 260
    Top = 140
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
    OnClick = CancelBtnClick
  end
  object process_pb: TProgressBar
    Left = 18
    Top = 32
    Width = 559
    Height = 16
    TabOrder = 1
  end
  object errors_l: TListBox
    Left = 18
    Top = 80
    Width = 559
    Height = 50
    BevelKind = bkFlat
    BorderStyle = bsNone
    Color = clBtnFace
    ItemHeight = 13
    TabOrder = 2
  end
end
