//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BackupW.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TwBackup *wBackup;
void TwBackup::setType(int itype)
{
	type = itype;
}
int TwBackup::getType(void)
{
	return type;
}
//---------------------------------------------------------------------
void __fastcall TwBackup::LoadLanguage(void)
{
	TStringList *l = new TStringList;

	THandleIni *ini = new THandleIni(language, languagepath);

	ini->StringListLoading(l, BACKUP_SECTION_NAME, 15);

	switch (type)
	{
		case 0:	Caption = l->Strings[0]; break; //backup
		case 1: Caption = l->Strings[1]; break; //restore
		default: Caption = l->Strings[0]+"//"+l->Strings[1];
	}
	filename_l->Caption = l->Strings[2];
	author_l->Caption = l->Strings[3];
	date_l->Caption = l->Strings[4];
	station_gb->Caption = l->Strings[5];
	name_l->Caption = l->Strings[6];
	place_l->Caption = l->Strings[7];
	address_l->Caption = l->Strings[8];
	device_gb->Caption = l->Strings[9];
	type_l->Caption = l->Strings[10];
	serialnr_l->Caption = l->Strings[11];
	notes_l->Caption = l->Strings[12];
	ok_btn->Caption = l->Strings[13];
	cancel_btn->Caption = l->Strings[14];

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TwBackup::LoadOptions(void)
{
	TStringList *l = new TStringList;

	THandleIni *ini = new THandleIni(language, languagepath);

	ini->setFileName(filename_e->Text);

	ini->readBackupDetails(l);

	authorname_e->Text = l->Strings[0];
	//->Caption = l->Strings[1]; not used
	//->Caption = l->Strings[2]; not used
	name_e->Text = l->Strings[3];
	place_e->Text = l->Strings[4];
	address_e->Text = l->Strings[5];
	type_e->Text = l->Strings[6];
	serialnr_e->Text = l->Strings[7];
	try
	{
    	switch (type)
		{
			case 0:	date_dtp->Date = StrToDate(l->Strings[8]); break; //backup
			case 1: date_dtp->Date = StrToDate(l->Strings[9]); break; //restore
			default: date_dtp->Date = StrToDate("1899.01.01.");
		}
	}
	catch(EConvertError &e)
	{
    	date_dtp->Date = StrToDate("1899.01.01.");
	}
	notes_e->Text = l->Strings[10];

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TwBackup::SaveOptions(void)
{
	TStringList *l = new TStringList;

	THandleIni *ini = new THandleIni(language, languagepath);
	ini->setFileName(filename_e->Text);

	l->Add(authorname_e->Text);
	l->Add(DateToStr(Now()));
	l->Add(TimeToStr(Now()));
	l->Add(name_e->Text);
	l->Add(place_e->Text);
	l->Add(address_e->Text);
	l->Add(type_e->Text);
	l->Add(serialnr_e->Text);
	try
	{
    	switch (type)
		{
			case 0:	l->Add(date_dtp->Date.DateString()); 
					l->Add("");
					break; //backup
			case 1:	l->Add("");
					l->Add(date_dtp->Date.DateString());
					break; //restore
			default: l->Add(date_dtp->Date.DateString());
		}
	}
	catch(EConvertError &e)
	{
		l->Add(date_dtp->Date.DateString());
	}
	l->Add(notes_e->Text);

	try
	{
		ini->writeBackupDetails(l);
	}
	catch(...)
	{
    	;
	}

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TwBackup::Run(void)
{
	if (FileExists(languagepath))	LoadLanguage();
	if (type==1)
	{
		authorname_e->Enabled = false;
		name_e->Enabled = false;
		place_e->Enabled = false;
		address_e->Enabled = false;
		type_e->Enabled = false;
		serialnr_e->Enabled = false;
		notes_e->Enabled = false;
	}
}
//---------------------------------------------------------------------
void __fastcall TwBackup::Stop(void)
{
	SaveOptions();
}
//---------------------------------------------------------------------
__fastcall TwBackup::TwBackup(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TwBackup::FormShow(TObject *Sender)
{
	Run();
}
//---------------------------------------------------------------------------
void __fastcall TwBackup::open_btnClick(TObject *Sender)
{
	if (open_dlg->Execute())
	{
		AnsiString fname = open_dlg->FileName;
		if (!FileExists(fname))	fname += ".tls";
    	filename_e->Text = fname;
    	LoadOptions();
	}
}
//---------------------------------------------------------------------------
void __fastcall TwBackup::ok_btnClick(TObject *Sender)
{
	Stop();
}
//---------------------------------------------------------------------------
 
