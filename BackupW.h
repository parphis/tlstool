//----------------------------------------------------------------------------
#ifndef BackupWH
#define BackupWH
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
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//----------------------------------------------------------------------------
#include "handleIni.h"

class TwBackup : public TForm
{
__published:
	TButton *ok_btn;
	TLabel *filename_l;
	TLabel *author_l;
	TLabel *date_l;
	TLabel *name_l;
	TLabel *place_l;
	TLabel *address_l;
	TLabel *type_l;
	TLabel *serialnr_l;
	TLabel *notes_l;
	TEdit *filename_e;
	TEdit *authorname_e;
	TEdit *name_e;
	TEdit *place_e;
	TEdit *address_e;
	TEdit *type_e;
	TEdit *serialnr_e;
	TEdit *notes_e;
	TDateTimePicker *date_dtp;
	TGroupBox *station_gb;
	TGroupBox *device_gb;
	TButton *open_btn;
	TOpenDialog *open_dlg;
	TButton *cancel_btn;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall open_btnClick(TObject *Sender);
	void __fastcall ok_btnClick(TObject *Sender);
private:
	int type;

	void __fastcall LoadLanguage(void);
	void __fastcall LoadOptions(void);
	void __fastcall SaveOptions(void);
	void __fastcall Run(void);
	void __fastcall Stop(void);
public:
	AnsiString language;
	AnsiString languagepath;

	void setType(int itype);
	int getType(void);
	virtual __fastcall TwBackup(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TwBackup *wBackup;
//----------------------------------------------------------------------------
#endif    
