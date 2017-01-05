//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InprocessW.h"
//---------------------------------------------------------------------
#pragma link "cgauges"
#pragma resource "*.dfm"
TwInProcess *wInProcess;
//--------------------------------------------------------------------- 
__fastcall TwInProcess::TwInProcess(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TwInProcess::init(int maxval, bool show)
{
	gauge_g->MaxValue = maxval;
	gauge_g->Progress = 0;
	if	(show)	Show();
	else	Hide();
}//---------------------------------------------------------------------
void __fastcall TwInProcess::init(bool show)
{
	gauge_g->Progress = 0;
	if	(show)	Show();
	else	Hide();
}
//---------------------------------------------------------------------
void __fastcall TwInProcess::increment(void)
{
	gauge_g->Progress++;
}
