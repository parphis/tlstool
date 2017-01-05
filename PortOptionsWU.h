//----------------------------------------------------------------------------
#ifndef PortOptionsWUH
#define PortOptionsWUH
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
#include <Registry.hpp>
//----------------------------------------------------------------------------
#include "handleIni.h"

#define	STR_SERIAL_KEY		"HARDWARE\\DEVICEMAP\\SERIALCOMM"
#define	STR_PARALLEL_KEY	"HARDWARE\\DEVICEMAP\\PARALLEL PORTS"

class TPortOptionsW : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TLabel *portname_l;
	TLabel *baudrate_l;
	TLabel *parity_l;
	TLabel *stopbit_l;
	TLabel *bytesize_l;
	TComboBox *baudrate_cb;
	TComboBox *parity_cb;
	TComboBox *stopbit_cb;
	TComboBox *bytesize_cb;
	TGroupBox *timeouts_gb;
	TLabel *readint_l;
	TLabel *readmulti_l;
	TLabel *readconst_l;
	TLabel *writemulti_l;
	TLabel *writeconst_l;
	TLabel *writerep_l;
	TLabel *readrep_l;
	TEdit *readint_e;
	TEdit *readmulti_e;
	TEdit *readconst_e;
	TEdit *writemulti_e;
	TEdit *writeconst_e;
	TEdit *writerep_e;
	TEdit *readrep_e;
	TUpDown *readint_ud;
	TUpDown *readmulti_ud;
	TUpDown *readconst_ud;
	TUpDown *writemulti_ud;
	TUpDown *writeconst_ud;
	TUpDown *writerep_ud;
	TUpDown *readrep_ud;
	TComboBox *portnames_e;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
private:
	THandleIni *ini;

	void __fastcall LoadLanguage(void);
	void __fastcall GetAvailablePorts(void);
	void __fastcall LoadOptionValues(void);
	void __fastcall SaveOptionValues(void);
	void __fastcall Run(void);
	void __fastcall Stop(void);
public:
	AnsiString language;
	AnsiString configpath;
	AnsiString languagepath;
	virtual __fastcall TPortOptionsW(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TPortOptionsW *PortOptionsW;
//----------------------------------------------------------------------------
#endif    
