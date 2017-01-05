//----------------------------------------------------------------------------
#ifndef SoftwareOptionsWH
#define SoftwareOptionsWH
//----------------------------------------------------------------------------
#include <CheckLst.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <FileCtrl.hpp>
//----------------------------------------------------------------------------
#include "handleIni.h"


class TSoftwareOptionsW : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TGroupBox *mainform_gb;
	TGroupBox *language_gb;
	TCheckBox *saveoptions_cb;
	TCheckBox *showtoolbar_cb;
	TCheckBox *showreport_cb;
	TGroupBox *reportcolors_gb;
	TColorBox *background_colb;
	TColorBox *font_colb;
	TLabel *background_l;
	TLabel *font_l;
	TLabel *selectlang_l;
	TEdit *languagepath_e;
	TLabel *languagepath_l;
	TButton *selectsource_btn;
	TListBox *languages_lb;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall selectsource_btnClick(TObject *Sender);
	void __fastcall showreport_cbClick(TObject *Sender);
private:
	THandleIni *ini;

	AnsiString __fastcall FileLanguageName(AnsiString fname);
	void __fastcall FindLanguageFiles(void);
	void __fastcall LoadLanguage(void);
	void __fastcall LoadOptionValues(void);
	void __fastcall SaveOptionValues(void);
	void __fastcall Run(TObject *Sender);
	void __fastcall Stop(void);
public:
	AnsiString language;
	AnsiString configpath;
	AnsiString languagepath;
	virtual __fastcall TSoftwareOptionsW(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TSoftwareOptionsW *SoftwareOptionsW;
//----------------------------------------------------------------------------
#endif    
