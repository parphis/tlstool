//---------------------------------------------------------------------------

#ifndef TLStoolUH
#define TLStoolUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "handleIni.h"
#include "TLSDevice.h"
#include "ReportsWU.h"
#include "PortOptionsWU.h"
#include "SoftwareOptionsWU.h"
#include "AboutW.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *main_m;
	TMenuItem *file_m;
	TMenuItem *saveconfig_m;
	TMenuItem *loadconfig_m;
	TMenuItem *N1;
	TMenuItem *exit_m;
	TMenuItem *options_m;
	TMenuItem *programop_m;
	TMenuItem *commop_m;
	TMenuItem *help_m;
	TMenuItem *index_m;
	TMenuItem *about_m;
	TToolBar *maintoolbar_tb;
	TToolButton *saveconfig_tbbtn;
	TToolButton *loadconfig_tbbtn;
	TToolButton *sep1;
	TToolButton *programop_tbbtn;
	TToolButton *commop_tbbtn;
	TToolButton *sep2;
	TToolButton *help_tbbtn;
	TImageList *toolbar_imgl;
	TPageControl *mainpage_pc;
	TTabSheet *control_pg;
	TTabSheet *reconc_pg;
	TTabSheet *variance_pg;
	TTabSheet *operation_pg;
	TTabSheet *diag_pg;
	TRadioGroup *mainsetupcategories_rg;
	TTabSheet *setup_pg;
	TListBox *setupsubcat_lb;
	TToolButton *showreportwindow_tbbtn;
	TMenuItem *N2;
	TMenuItem *viewreport_m;
	TToolButton *sep3;
	TToolButton *connect_tbbtn;
	TMenuItem *port_m;
	TMenuItem *connect_m;
	TMenuItem *disconnect_m;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall mainsetupcategories_rgClick(TObject *Sender);
	void __fastcall LoadSetupSubcategories(int number);
	void __fastcall setupsubcat_lbClick(TObject *Sender);
	void __fastcall setupsubcat_lbDblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall saveconfig_mClick(TObject *Sender);
	void __fastcall loadconfig_mClick(TObject *Sender);
	void __fastcall exit_mClick(TObject *Sender);
	void __fastcall programop_mClick(TObject *Sender);
	void __fastcall commop_mClick(TObject *Sender);
	void __fastcall index_mClick(TObject *Sender);
	void __fastcall about_mClick(TObject *Sender);
	void __fastcall viewreport_mClick(TObject *Sender);
	void __fastcall connect_mClick(TObject *Sender);
	void __fastcall disconnect_mClick(TObject *Sender);
	void __fastcall connect_tbbtnClick(TObject *Sender);
	void __fastcall setupsubcat_lbKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	THandleIni *ini;
	TTLSDevice *dev;
	TReportsW *Reports;
	TSoftwareOptionsW *Softoptions;
	TPortOptionsW *Portoptions;

	bool show_toolbar;
	bool save_options;
	bool show_reportwindow;
	AnsiString language;
	AnsiString language_source_directoy;
	AnsiString portname;
	AnsiString current_path;
	AnsiString configpath;
	AnsiString languagepath;
	AnsiString cofig_file_name;
	int baud;
	int parity;
	int stopbit;
	int bytesize;
	int rint;
	int rmulti;
	int rconst;
	int wmulti;
	int wconst;
	int wrep;
	int rrep;

	AnsiString help_path;

	void __fastcall GetCurrentPath(void);
	void __fastcall CreateConfigfilePath(void);
	void __fastcall CreateLanguagefilePath(void);
	void __fastcall LoadMainFormDimension(void);
	void __fastcall SaveMainFormDimension(void);
	void __fastcall LoadReportsWindowDimension(void);
	void __fastcall SaveReportsWindowDimension(void);
	void __fastcall LoadOtherOptions(void);
	void __fastcall SaveOtherOptions(void);
	void __fastcall LoadPortProperties(void);
	void __fastcall SavePortProperties(void);
	void __fastcall LoadLanguage(void);
	void __fastcall Run(void);
	void __fastcall Stop(void);
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
