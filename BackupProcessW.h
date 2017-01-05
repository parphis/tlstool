//----------------------------------------------------------------------------
#ifndef BackupProcessWH
#define BackupProcessWH
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
//----------------------------------------------------------------------------
#include "handleIni.h"
class TwBackupProcess : public TForm
{
__published:
	TButton *CancelBtn;
	TLabel *inprocess_l;
	TLabel *error_l;
	TProgressBar *process_pb;
	TLabel *curproc_l;
	TListBox *errors_l;
	void __fastcall CancelBtnClick(TObject *Sender);
private:
	bool cancel;

	void __fastcall LoadLanguage(void);
	void __fastcall Run(void);
public:                            
	AnsiString language;
	AnsiString languagepath;

	bool __fastcall getCancel(void);
	void __fastcall setButtonCaption(AnsiString cap);

	virtual __fastcall TwBackupProcess(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TwBackupProcess *wBackupProcess;
//----------------------------------------------------------------------------
#endif    
