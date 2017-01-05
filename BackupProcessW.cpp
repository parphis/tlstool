//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BackupProcessW.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TwBackupProcess *wBackupProcess;
bool __fastcall TwBackupProcess::getCancel(void)
{
	return cancel;
}

void __fastcall TwBackupProcess::setButtonCaption(AnsiString cap)
{
	CancelBtn->Caption = cap;
}
//---------------------------------------------------------------------
void __fastcall TwBackupProcess::LoadLanguage(void)
{
	TStringList *l = new TStringList;

	THandleIni *ini = new THandleIni(language, languagepath);

	ini->StringListLoading(l, BACKUP_PROCESS_SECTION_NAME, 4);

	Caption = l->Strings[0];
	inprocess_l->Caption = l->Strings[1];
	error_l->Caption = l->Strings[2];
	CancelBtn->Caption = l->Strings[3];

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TwBackupProcess::Run(void)
{
	if (FileExists(languagepath))	LoadLanguage();
}
//---------------------------------------------------------------------
__fastcall TwBackupProcess::TwBackupProcess(TComponent* AOwner)
	: TForm(AOwner)
{
	cancel = false;
	Run();
}
//---------------------------------------------------------------------
void __fastcall TwBackupProcess::CancelBtnClick(TObject *Sender)
{
	cancel = true;
}
//---------------------------------------------------------------------------
