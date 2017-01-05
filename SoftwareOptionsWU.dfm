object SoftwareOptionsW: TSoftwareOptionsW
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  ClientHeight = 261
  ClientWidth = 725
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OKBtn: TButton
    Left = 546
    Top = 228
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 627
    Top = 228
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object mainform_gb: TGroupBox
    Left = 8
    Top = 8
    Width = 332
    Height = 206
    Caption = 'Main window'
    TabOrder = 2
    object saveoptions_cb: TCheckBox
      Left = 45
      Top = 36
      Width = 241
      Height = 17
      Caption = 'Save options'
      TabOrder = 0
    end
    object showtoolbar_cb: TCheckBox
      Left = 45
      Top = 59
      Width = 241
      Height = 17
      Caption = 'Show toolbar'
      TabOrder = 1
    end
    object showreport_cb: TCheckBox
      Left = 45
      Top = 82
      Width = 241
      Height = 17
      Caption = 'Show report window on startup'
      TabOrder = 2
      OnClick = showreport_cbClick
    end
    object reportcolors_gb: TGroupBox
      Left = 45
      Top = 105
      Width = 241
      Height = 82
      Caption = 'Report window colors'
      TabOrder = 3
      object background_l: TLabel
        Left = 21
        Top = 24
        Width = 56
        Height = 13
        Caption = 'Background'
      end
      object font_l: TLabel
        Left = 21
        Top = 51
        Width = 22
        Height = 13
        Caption = 'Font'
      end
      object background_colb: TColorBox
        Left = 83
        Top = 19
        Width = 145
        Height = 22
        ItemHeight = 16
        TabOrder = 0
      end
      object font_colb: TColorBox
        Left = 83
        Top = 47
        Width = 145
        Height = 22
        ItemHeight = 16
        TabOrder = 1
      end
    end
  end
  object language_gb: TGroupBox
    Left = 346
    Top = 8
    Width = 371
    Height = 206
    Caption = 'Language'
    TabOrder = 3
    object selectlang_l: TLabel
      Left = 30
      Top = 37
      Width = 80
      Height = 13
      Caption = 'Select language:'
    end
    object languagepath_l: TLabel
      Left = 30
      Top = 129
      Width = 79
      Height = 13
      Caption = 'Source directory'
    end
    object languagepath_e: TEdit
      Left = 30
      Top = 148
      Width = 295
      Height = 21
      TabOrder = 0
    end
    object selectsource_btn: TButton
      Left = 331
      Top = 148
      Width = 28
      Height = 21
      Caption = '...'
      TabOrder = 1
      OnClick = selectsource_btnClick
    end
    object languages_lb: TListBox
      Left = 30
      Top = 56
      Width = 139
      Height = 67
      ItemHeight = 13
      TabOrder = 2
    end
  end
end
