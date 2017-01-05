//----------------------------------------------------------------------------
#ifndef ReportsWUH
#define ReportsWUH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
#include "handleIni.h"

class TReportsW : public TForm
{
__published:
	TMemo *setupanswer_m;
private:
	THandleIni *ini;

public:

	void __fastcall LoadLanguage(TForm *ireports);
	virtual __fastcall TReportsW(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TReportsW *ReportsW;
//----------------------------------------------------------------------------
#endif    
