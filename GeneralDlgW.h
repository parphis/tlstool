//----------------------------------------------------------------------------
#ifndef DlgWith2ComboBoxH
#define DlgWith2ComboBoxH
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
class TGenDlgW : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
private:
public:
	virtual __fastcall TGenDlgW(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TGenDlgW *GenDlgW;
//----------------------------------------------------------------------------
#endif    
