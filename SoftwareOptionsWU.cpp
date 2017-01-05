//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SoftwareOptionsWU.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TSoftwareOptionsW *SoftwareOptionsW;
//---------------------------------------------------------------------
AnsiString __fastcall TSoftwareOptionsW::FileLanguageName(AnsiString fname)
{
	ini = new THandleIni(fname);

	AnsiString result = ini->getLanguageString();

	delete ini;

	return result;
}
//---------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::FindLanguageFiles(void)
{
	TSearchRec s_rec;
	AnsiString find_path = "", res_path = "";

	if (languagepath_e->Text[languagepath_e->Text.Length()]=='\\')
	{
		find_path = languagepath_e->Text+"*.lng";
		res_path = languagepath_e->Text;
	}
	else
	{
		find_path = languagepath_e->Text+"\\*.lng";
    	res_path = languagepath_e->Text+"\\";
	}

	if (!FindFirst(find_path, faAnyFile, s_rec))
	{
		do
		{
			languages_lb->Items->Add(FileLanguageName(res_path+s_rec.Name));
		}while (!FindNext(s_rec));
    	FindClose(s_rec);
	}
}
//---------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::LoadLanguage(void)
{
	TStringList *l = new TStringList;

	ini = new THandleIni(language, languagepath);

	ini->StringListLoading(l, PROGRAMOP_SECTION_NAME, 16);

	Caption = l->Strings[0];
	mainform_gb->Caption = l->Strings[1];
	saveoptions_cb->Caption = l->Strings[2];
	showtoolbar_cb->Caption = l->Strings[3];
	showreport_cb->Caption = l->Strings[4];
	reportcolors_gb->Caption = l->Strings[5];
	background_l->Caption = l->Strings[6];
	font_l->Caption = l->Strings[7];
	language_gb->Caption = l->Strings[8];
	selectlang_l->Caption = l->Strings[9];
	//languages_lb->Items->Add(l->Strings[10]);
	//languages_lb->Items->Add(l->Strings[11]);
	//languages_lb->Items->Add(l->Strings[12]);
	languagepath_l->Caption = l->Strings[13];
	OKBtn->Caption = l->Strings[14];
	CancelBtn->Caption = l->Strings[15];

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::LoadOptionValues(void)
{
	ini = new THandleIni(configpath);

	saveoptions_cb->Checked = ini->getSaveSettingsFlag();
	showtoolbar_cb->Checked = ini->getMainToolbarVisibility();
	showreport_cb->Checked = ini->getDisplayReportWindowOnStartUp();
	background_colb->Selected = (TColor)ini->getReportWindowBackgroundColor();
	font_colb->Selected = (TColor)ini->getReportWindowFontColor();
	language = ini->getUsedLanguage();

	languagepath_e->Text = ini->getLanguageDirectory();

	delete ini;

	FindLanguageFiles();
	for (int i=0; i < languages_lb->Items->Count; i++)
	{
		if (!CompareStr(language, languages_lb->Items->Strings[i]))
		{
			languages_lb->ItemIndex = i;
			break;
    	}
	}
}
void __fastcall TSoftwareOptionsW::SaveOptionValues(void)
{
	ini = new THandleIni(configpath);

	ini->setSaveSettingsFlag(saveoptions_cb->Checked);
	ini->setMainToolbarVisibility(showtoolbar_cb->Checked);
	ini->setDisplayReportWindowOnStartUp(showreport_cb->Checked);
	ini->setReportWindowBackgroundColor(background_colb->Selected);
	ini->setReportWindowFontColor(font_colb->Selected);
	ini->setLanguageDirectory(languagepath_e->Text);

	int idx = languages_lb->ItemIndex;
	if (idx > -1)	ini->setUsedLanguage(languages_lb->Items->Strings[idx]);

	language = ini->getUsedLanguage();

	delete ini;
}
//---------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::Run(TObject *Sender)
{
	if (FileExists(languagepath))	LoadLanguage();
	LoadOptionValues();
	showreport_cbClick(Sender);
}
//---------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::Stop(void)
{
	SaveOptionValues();
}
//---------------------------------------------------------------------
__fastcall TSoftwareOptionsW::TSoftwareOptionsW(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::FormShow(TObject *Sender)
{
	Run(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::OKBtnClick(TObject *Sender)
{
	Stop();
}
//---------------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::selectsource_btnClick(TObject *Sender)
{
	AnsiString root_dir = "";

	if (SelectDirectory("", "", root_dir))
	{
    	languages_lb->Items->Clear();
		languagepath_e->Text = root_dir;
    	FindLanguageFiles();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSoftwareOptionsW::showreport_cbClick(TObject *Sender)
{
	if (showreport_cb->Checked)
	{
		reportcolors_gb->Enabled = true;
		background_l->Enabled = true;
		background_colb->Enabled = true;
		font_l->Enabled = true;
		font_colb->Enabled = true;
	}
	else
	{
		reportcolors_gb->Enabled = false;
		background_l->Enabled = false;
		background_colb->Enabled = false;
		font_l->Enabled = false;
		font_colb->Enabled = false;
	}
}
//---------------------------------------------------------------------------

