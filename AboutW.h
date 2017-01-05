//----------------------------------------------------------------------------
#ifndef AboutWH
#define AboutWH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
#include "handleIni.h"

class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TButton *OKButton;
	void __fastcall FormShow(TObject *Sender);
private:
	THandleIni *ini;

	void __fastcall LoadLanguage(void);
	void __fastcall Run(void);
	void __fastcall Stop(void);
public:
	AnsiString language;
	AnsiString languagepath;
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
