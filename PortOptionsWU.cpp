//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PortOptionsWU.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPortOptionsW *PortOptionsW;
//---------------------------------------------------------------------
void __fastcall TPortOptionsW::LoadLanguage(void)
{
	TStringList *l = new TStringList;

	ini = new THandleIni(language, languagepath);

	ini->StringListLoading(l, PORTOP_SECTION_NAME, 16);

	Caption = l->Strings[0];
	portname_l->Caption = l->Strings[1];
	baudrate_l->Caption = l->Strings[2];
	parity_l->Caption = l->Strings[3];
	stopbit_l->Caption = l->Strings[4];
	bytesize_l->Caption = l->Strings[5];
	timeouts_gb->Caption = l->Strings[6];
	readint_l->Caption = l->Strings[7];
	readmulti_l->Caption = l->Strings[8];
	readconst_l->Caption = l->Strings[9];
	writemulti_l->Caption = l->Strings[10];
	writeconst_l->Caption = l->Strings[11];
	writerep_l->Caption = l->Strings[12];
	readrep_l->Caption = l->Strings[13];
	OKBtn->Caption = l->Strings[14];
	CancelBtn->Caption = l->Strings[15];

	delete ini;
	delete l;
}
//---------------------------------------------------------------------
void __fastcall TPortOptionsW::GetAvailablePorts(void)
{
	TRegistry *reg = new TRegistry();
	TStrings *strs = new TStringList();

	try
	{
		reg->RootKey = HKEY_LOCAL_MACHINE;

		if (reg->OpenKeyReadOnly(STR_SERIAL_KEY))
		{
			reg->GetValueNames(strs);
			for (int i=0; i < strs->Count; i++)
			{
				try
				{
					portnames_e->Items->Add(reg->ReadString(strs->Strings[i]));
				}
				catch(...)
				{
					portnames_e->Items->Add(STR_COM1);
					break;
				}
			}

			strs->Clear();
			/*reg->CloseKey();

			reg->OpenKeyReadOnly(STR_PARALLEL_KEY);
			reg->GetValueNames(strs);
			for (int i=0; i < strs->Count; i++)
			{
				try
				{
					portnames_e->Items->Add(reg->ReadString(strs->Strings[i]));
				}
				catch(...)
				{
					break;
				}
			}*/
		}
		else
		{
			portnames_e->Items->Add(STR_COM1);
			portnames_e->Items->Add(STR_COM2);
			portnames_e->Items->Add(STR_COM3);
			portnames_e->Items->Add(STR_COM4);
			portnames_e->Items->Add(STR_COM5);
			portnames_e->Items->Add(STR_COM6);
			portnames_e->Items->Add(STR_COM7);
			portnames_e->Items->Add(STR_COM8);
		}
	}
	__finally
	{
    	delete strs;
		delete reg;
	}
}
//---------------------------------------------------------------------
void __fastcall TPortOptionsW::LoadOptionValues(void)
{
	ini = new THandleIni(configpath);

	portnames_e->Text = ini->getUsedPortName();
	baudrate_cb->Text = ini->getUsedBaudRate();

	try
	{
		parity_cb->ItemIndex = StrToInt(ini->getUsedParity());
	}
	catch(EConvertError &e)
	{
		parity_cb->ItemIndex = 0;
	}
	try
	{
		stopbit_cb->ItemIndex = StrToInt(ini->getUsedStopbit());
	}
	catch(EConvertError &e)
	{
		stopbit_cb->ItemIndex = 0;
	}

	bytesize_cb->Text = ini->getUsedByteSize();

	try
	{
		readint_ud->Position = ini->getUsedReadIntervalTimeout();
	}
	catch(EConvertError &e)
	{
		readint_ud->Position = 0;
	}

	try
	{
		readmulti_ud->Position = ini->getUsedReadMultiplyTimeout();
	}
	catch(EConvertError &e)
	{
		readmulti_ud->Position = 0;
	}

	try
	{
		readconst_ud->Position = ini->getUsedReadConstantTimeout();
	}
	catch(EConvertError &e)
	{
		readconst_ud->Position = 0;
	}

	try
	{
		writemulti_ud->Position = ini->getUsedWriteMultiplyTimeout();
	}
	catch(EConvertError &e)
	{
		writemulti_ud->Position = 0;
	}

	try
	{
		writeconst_ud->Position = ini->getUsedWriteConstantTimeout();
	}
	catch(EConvertError &e)
	{
		writeconst_ud->Position = 0;
	}

	try
	{
		writerep_ud->Position = ini->getUsedWriteRepetition();
	}
	catch(EConvertError &e)
	{
		writerep_ud->Position = 0;
	}

	try
	{
		readrep_ud->Position = ini->getUsedReadRepetition();
	}
	catch(EConvertError &e)
	{
		readrep_ud->Position = 0;
	}

	delete ini;
}
void __fastcall TPortOptionsW::SaveOptionValues(void)
{
	ini = new THandleIni(configpath);

	ini->setUsedPortName(portnames_e->Text);

	try
	{
		ini->setUsedBaudRate(StrToInt(baudrate_cb->Text));
	}
	catch(EConvertError &e)
	{
    	ini->setUsedBaudRate(DEF_BAUDRATE);
	}

	if (parity_cb->ItemIndex > -1)
	{
		ini->setUsedParity(parity_cb->ItemIndex);
	}
	else
	{
		ini->setUsedParity(DEF_PARITY);
	}

	if (stopbit_cb->ItemIndex > -1)
	{
		ini->setUsedStopbit(StrToInt(stopbit_cb->ItemIndex));
	}
	else
	{
		ini->setUsedStopbit(DEF_STOPBIT);
	}

	try
	{
		ini->setUsedByteSize(StrToInt(bytesize_cb->Text));
    }
	catch(EConvertError &e)
	{
		ini->setUsedByteSize(DEF_BYTESIZE);
	}

	try
	{
		ini->setUsedReadIntervalTimeout(StrToInt(readint_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedReadIntervalTimeout(DEF_READINTTOUT);
	}

	try
	{
		ini->setUsedReadMultiplyTimeout(StrToInt(readmulti_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedReadMultiplyTimeout(DEF_READMULTITOUT);
	}

	try
	{
		ini->setUsedReadConstantTimeout(StrToInt(readconst_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedReadConstantTimeout(DEF_READCONSTTOUT);
	}

	try
	{
		ini->setUsedWriteMultiplyTimeout(StrToInt(writemulti_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedWriteMultiplyTimeout(DEF_WRITEMULTITOUT);
	}

	try
	{
		ini->setUsedWriteConstantTimeout(StrToInt(writeconst_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedWriteConstantTimeout(DEF_WRITECONSTTOUT);
	}

	try
	{
		ini->setUsedWriteRepetition(StrToInt(writerep_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedWriteRepetition(DEF_WRITEREPETITION);
	}

	try
	{
		ini->setUsedReadRepetition(StrToInt(readrep_e->Text));
	}
	catch(EConvertError &e)
	{
		ini->setUsedReadRepetition(DEF_READREPETITION);
	}

	delete ini;
}
//---------------------------------------------------------------------
void __fastcall TPortOptionsW::Run(void)
{
	if (FileExists(languagepath))	LoadLanguage();
	GetAvailablePorts();
	LoadOptionValues();
}
//---------------------------------------------------------------------
void __fastcall TPortOptionsW::Stop(void)
{
	SaveOptionValues();
}
//---------------------------------------------------------------------
__fastcall TPortOptionsW::TPortOptionsW(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TPortOptionsW::FormShow(TObject *Sender)
{
	Run();
}
//---------------------------------------------------------------------------
void __fastcall TPortOptionsW::OKBtnClick(TObject *Sender)
{
	Stop();	
}
//---------------------------------------------------------------------------
 
