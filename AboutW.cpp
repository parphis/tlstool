//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AboutW.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
void __fastcall TAboutBox::LoadLanguage(void)
{
	TStringList *l = new TStringList;

	ini = new THandleIni(language, languagepath);

	ini->StringListLoading(l, ABOUT_SECTION_NAME, 2);

	Caption = l->Strings[0];
	OKButton->Caption = l->Strings[1];

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::Run(void)
{
	if (FileExists(languagepath))	LoadLanguage();
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::Stop(void)
{
	;
}
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::FormShow(TObject *Sender)
{
	Run();	
}
//---------------------------------------------------------------------------
 
