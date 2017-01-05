//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ReportsWU.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TReportsW *ReportsW;
//---------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TReportsW::LoadLanguage(TForm *ireports)
{
	ini = new THandleIni("english", "D:\\vigist\\current_sw\\eng.lng", ireports);

	ini->LoadReportLanguage();

	delete ini;
}
//---------------------------------------------------------------------------
__fastcall TReportsW::TReportsW(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
