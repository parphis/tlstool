//----------------------------------------------------------------------------
#ifndef InprocessWH
#define InprocessWH
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
#include "cgauges.h"
//----------------------------------------------------------------------------
class TwInProcess : public TForm
{
__published:
	TCGauge *gauge_g;
private:
public:
	void __fastcall init(int maxval, bool show);
	void __fastcall init(bool show);
	void __fastcall increment(void);

	virtual __fastcall TwInProcess(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TwInProcess *wInProcess;
//----------------------------------------------------------------------------
#endif    
