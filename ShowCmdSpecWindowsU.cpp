//---------------------------------------------------------------------------


#pragma hdrstop

#include "ShowCmdSpecWindowsU.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/* private */
TLabel* __fastcall TShowCmdSpecWindows::CreateLabel(TGenDlgW *dlg, int left,
	int top, int width, int height, AnsiString caption, TLabel *l)
{
	if (l==NULL)
	{
		TLabel *nl;
    	l = nl;
	}

	l = new TLabel(dlg);
	l->Parent = dlg;
	l->Left = left;
	l->Top = top;
	if (width > 0)	l->Width = width;
	if (height > 0)	l->Height = height;
	l->Caption = caption;

	return l;
}
TLabel* __fastcall TShowCmdSpecWindows::CreateLabel(TGroupBox *par, int left,
	int top, int width, int height, AnsiString caption, TLabel *l)
{
	if (l==NULL)
	{
		TLabel *nl;
		l = nl;
	}

	l = new TLabel(par);
	l->Parent = par;
	l->Left = left;
	l->Top = top;
	if (width > 0)	l->Width = width;
	if (height > 0)	l->Height = height;
	l->Caption = caption;

	return l;
}
TComboBox* __fastcall TShowCmdSpecWindows::CreateComboBox(TGenDlgW *dlg, int left,
	int top, int width, int height, AnsiString text, int itemidx, TComboBox *cb)
{
	if (cb==NULL)
	{
		TComboBox *ncb;
		cb = ncb;
	}

	cb = new TComboBox(dlg);
	cb->Parent = dlg;
	if (width > 0)	cb->Width = width;
	if (height > 0)	cb->Height = height;
	cb->Left = left;
	cb->Top = top;
	cb->Text = text;
	cb->ItemIndex = itemidx;

	return cb;
}
TDateTimePicker* __fastcall TShowCmdSpecWindows::CreateDateTimePicker(
	TGenDlgW *dlg, int left, int top, int width, int height, AnsiString format,
	TDateTime datetime, TDateTimeKind kind, TDateTimePicker *dtp)
{
	if (dtp==NULL)
	{
		TDateTimePicker *ndtp;
		dtp = ndtp;
	}

	dtp = new TDateTimePicker(dlg);
	dtp->Parent = dlg;
	if (width > 0)	dtp->Width = width;
	if (height > 0)	dtp->Height = height;
	dtp->Left = left;
	dtp->Top = top;
	dtp->Kind = kind;
	dtp->Format = format;
	if (kind==dtkDate)	dtp->Date = datetime;
	if (kind==dtkTime)	dtp->Time = datetime;

	return dtp;
}
TDateTimePicker* __fastcall TShowCmdSpecWindows::CreateDateTimePicker(
	TGroupBox *par, int left, int top, int width, int height, AnsiString format,
	TDateTime datetime, TDateTimeKind kind, TDateTimePicker *dtp)
{
	if (dtp==NULL)
	{
		TDateTimePicker *ndtp;
		dtp = ndtp;
	}

	dtp = new TDateTimePicker(par);
	dtp->Parent = par;
	if (width > 0)	dtp->Width = width;
	if (height > 0)	dtp->Height = height;
	dtp->Left = left;
	dtp->Top = top;
	dtp->Kind = kind;
	dtp->Format = format;
	if (kind==dtkDate)	dtp->Date = datetime;
	if (kind==dtkTime)	dtp->Time = datetime;

	return dtp;
}
TEdit* __fastcall TShowCmdSpecWindows::CreateEdit(TGenDlgW *dlg, int left,
	int top, int width, int height, AnsiString text, int maxlen, TEdit *e)
{
	if (e==NULL)
	{
		TEdit *ne;
		e = ne;
	}

	e = new TEdit(dlg);
	e->Parent = dlg;
	e->Left = left;
	e->Top = top;
	if (width > 0)	e->Width = width;
	if (height > 0)	e->Height = height;
	e->MaxLength = maxlen;
	e->Text = text;

	return e;
}
TEdit* __fastcall TShowCmdSpecWindows::CreateEdit(TGroupBox *par, int left,
	int top, int width, int height, AnsiString text, int maxlen, TEdit *e)
{
	if (e==NULL)
	{
		TEdit *ne;
		e = ne;
	}

	e = new TEdit(par);
	e->Parent = par;
	e->Left = left;
	e->Top = top;
	if (width > 0)	e->Width = width;
	if (height > 0)	e->Height = height;
	e->MaxLength = maxlen;
	e->Text = text;

	return e;
}
TCheckBox* __fastcall TShowCmdSpecWindows::CreateCheckBox(TGenDlgW *dlg, int left,
	int top, int width, int height, AnsiString caption, bool checked, int tag,
	TCheckBox *cb)
{
	if (cb==NULL)
	{
		TCheckBox *ncb;
		cb = ncb;
	}

	cb = new TCheckBox(dlg);
	cb->Parent = dlg;
	cb->Left = left;
	cb->Top = top;
	if (width > 0)	cb->Width = width;
	if (height > 0)	cb->Height = height;
	cb->Caption = caption;
	cb->Checked = checked;
	cb->Tag = tag;

	return cb;
}
TCheckBox* __fastcall TShowCmdSpecWindows::CreateCheckBox(TGroupBox *par, int left,
	int top, int width, int height, AnsiString caption, bool checked, int tag,
	TCheckBox *cb)
{
	if (cb==NULL)
	{
		TCheckBox *ncb;
		cb = ncb;
	}

	cb = new TCheckBox(par);
	cb->Parent = par;
	cb->Left = left;
	cb->Top = top;
	if (width > 0)	cb->Width = width;
	if (height > 0)	cb->Height = height;
	cb->Caption = caption;
	cb->Checked = checked;
	cb->Tag = tag;

	return cb;
}               
TUpDown* __fastcall TShowCmdSpecWindows::CreateUpDown(TGenDlgW *dlg, int left,
	int top, int width, int height, int min, int max, int pos, TWinControl *edit,
	TUpDown *ud)
{
	if (ud==NULL)
	{
		TUpDown *nud;
		ud = nud;
	}

	ud = new TUpDown(dlg);
	ud->Parent = dlg;
	if (!edit)
	{
		ud->Left = left;
		ud->Top = top;
		ud->Width = width;
		ud->Height = height;
	}
	ud->Min = min;
	ud->Max = max;
	ud->Position = pos;
	ud->Thousands = false;
	if (edit)	ud->Associate = edit;

	return ud;
}
TUpDown* __fastcall TShowCmdSpecWindows::CreateUpDown(TGroupBox *par, int left,
	int top, int width, int height, int min, int max, int pos, TWinControl *edit,
	TUpDown *ud)
{
	if (ud==NULL)
	{
		TUpDown *nud;
		ud = nud;
	}

	ud = new TUpDown(par);
	ud->Parent = par;
	if (!edit)
	{
		ud->Left = left;
		ud->Top = top;
		ud->Width = width;
		ud->Height = height;
	}
	ud->Min = min;
	ud->Max = max;
	ud->Position = pos;
	ud->Thousands = false;
	if (edit)	ud->Associate = edit;

	return ud;
}
TGroupBox* __fastcall TShowCmdSpecWindows::CreateGroupBox(TGenDlgW *dlg, int left,
	int top, int width, int height, AnsiString caption,	TGroupBox *gb)
{
	if (gb==NULL)
	{
		TGroupBox *ngb;
		gb = ngb;
	}

	gb = new TGroupBox(dlg);
	gb->Parent = dlg;
	gb->Left = left;
	gb->Top = top;
	if (width > 0)	gb->Width = width;
	if (height > 0)	gb->Height = height;
	gb->Caption = caption;

	return gb;
}
TGroupBox* __fastcall TShowCmdSpecWindows::CreateGroupBox(TGroupBox *par, int left,
	int top, int width, int height, AnsiString caption,	TGroupBox *gb)
{
	if (gb==NULL)
	{
		TGroupBox *ngb;
		gb = ngb;
	}

	gb = new TGroupBox(par);
	gb->Parent = par;
	gb->Left = left;
	gb->Top = top;
	if (width > 0)	gb->Width = width;
	if (height > 0)	gb->Height = height;
	gb->Caption = caption;

	return gb;
}
TRadioButton* __fastcall TShowCmdSpecWindows::CreateRadioButton(TGenDlgW *dlg,
	int left, int top, int width, int height, AnsiString caption,
	bool checked, TRadioButton *rb)
{
	if (rb==NULL)
	{
		TRadioButton *nrb;
		rb = nrb;
	}

	rb = new TRadioButton(dlg);
	rb->Parent = dlg;
	rb->Left = left;
	rb->Top = top;
	if (width > 0)	rb->Width = width;
	if (height > 0)	rb->Height = height;
	rb->Caption = caption;
	rb->Checked = checked;

	return rb;
}
TRadioButton* __fastcall TShowCmdSpecWindows::CreateRadioButton(TGroupBox *par,
	int left, int top, int width, int height, AnsiString caption,
	bool checked, TRadioButton *rb)
{
	if (rb==NULL)
	{
		TRadioButton *nrb;
		rb = nrb;
	}

	rb = new TRadioButton(par);
	rb->Parent = par;
	rb->Left = left;
	rb->Top = top;
	if (width > 0)	rb->Width = width;
	if (height > 0)	rb->Height = height;
	rb->Caption = caption;
	rb->Checked = checked;

	return rb;
}
TMemo* __fastcall TShowCmdSpecWindows::CreateMemo(TGenDlgW *dlg,
	int left, int top, int width, int height, AnsiString caption, TMemo *m)
{
	if (m==NULL)
	{
		TMemo *nm;
		m = nm;
	}

	m = new TMemo(dlg);
	m->Parent = dlg;
	m->Left = left;
	m->Top = top;
	if (width > 0)	m->Width = width;
	if (height > 0)	m->Height = height;
	m->Lines->Add(caption);

	return m;
}
TMemo* __fastcall TShowCmdSpecWindows::CreateMemo(TGroupBox *par,
	int left, int top, int width, int height, AnsiString caption, TMemo *m)
{
	if (m==NULL)
	{
		TMemo *nm;
		m = nm;
	}

	m = new TMemo(par);
	m->Parent = par;
	m->Left = left;
	m->Top = top;
	if (width > 0)	m->Width = width;
	if (height > 0)	m->Height = height;
	m->Lines->Add(caption);

	return m;
}
TGenDlgW* __fastcall TShowCmdSpecWindows::InitDialog(TStringList *l, char *str,
	int cnt, int caption, int okbtncap, int cancelbtncap, TGenDlgW *dlg)
{
	if (dlg==NULL)
	{
		TGenDlgW *ndlg;
		dlg = ndlg;
	}

	/* load language */
	ini = new THandleIni(language, languagepath);

	ini->StringListLoading(l, str, cnt);

	/* create dialog window */
	dlg = new TGenDlgW(Application);

	dlg->Caption = l->Strings[caption];
	dlg->OKBtn->Caption = l->Strings[okbtncap];
	dlg->CancelBtn->Caption = l->Strings[cancelbtncap];

	delete ini;

	return dlg;
}

/* create the system language and unit setup dialog window */
void __fastcall TShowCmdSpecWindows::ShowSystemLanguageAndUnit(void)
{
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SYSTEMUNITANDLANG,CNT_SYSTEMUNITANDLANG,12,15,16,GeneralDialog);

	/* create label for system unit */
	TLabel* unit_l = CreateLabel(GeneralDialog, 33, 23, 0, 0, l->Strings[13], unit_l);

	/* create combobox for system unit strings */
	TComboBox* unit_cb = CreateComboBox(GeneralDialog,30,36,200,23,"",-1,unit_cb);

	/* create label for system language */
	TLabel* lang_l = CreateLabel(GeneralDialog, 33, 83, 0, 0, l->Strings[14], lang_l);

	/* create combobox for system language strings */
	TComboBox* lang_cb = CreateComboBox(GeneralDialog,30,96,200,23,"",-1,lang_cb);

	/* load up the two combo box with the selectalbe flags */
	unit_cb->Items->Add(l->Strings[0]);
	unit_cb->Items->Add(l->Strings[1]);
	unit_cb->Items->Add(l->Strings[2]);

	lang_cb->Items->Add(l->Strings[3]);
	lang_cb->Items->Add(l->Strings[4]);
	lang_cb->Items->Add(l->Strings[5]);
	lang_cb->Items->Add(l->Strings[6]);
	lang_cb->Items->Add(l->Strings[7]);
	lang_cb->Items->Add(l->Strings[8]);
	lang_cb->Items->Add(l->Strings[9]);
	lang_cb->Items->Add(l->Strings[10]);
	lang_cb->Items->Add(l->Strings[11]);

	unit_cb->ItemIndex = unit_index-1;
	lang_cb->ItemIndex = language_index-1;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		unit_index = unit_cb->ItemIndex+1;
		language_index = lang_cb->ItemIndex+1;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}
void __fastcall TShowCmdSpecWindows::ShowSystemDateTimeDisplayFormat(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SYSTEMDATETIMEFORMAT,CNT_SYSTEMDATETIMEFORMAT,
								0,8,9,GeneralDialog);

	/* create label for system display format */
	CreateLabel(GeneralDialog, 33, 33, 0, 0, l->Strings[1],NULL);

	/* create combobox for system display format strings */
	TComboBox* disptype_cb = CreateComboBox(GeneralDialog,30,46,220,23,"",-1,disptype_cb);

	/* load up the two combo box with the selectalbe flags */
	disptype_cb->Items->Add(l->Strings[2]);
	disptype_cb->Items->Add(l->Strings[3]);
	disptype_cb->Items->Add(l->Strings[4]);
	disptype_cb->Items->Add(l->Strings[5]);
	disptype_cb->Items->Add(l->Strings[6]);
	disptype_cb->Items->Add(l->Strings[7]);

	disptype_cb->ItemIndex = date_time_format_index-1;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		date_time_format_index = disptype_cb->ItemIndex+1;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}
void __fastcall TShowCmdSpecWindows::ShowTimeOfDay(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_TIMEOFDAY,CNT_TIMEOFDAY,0,1,2,GeneralDialog);

	/* create label for date */
	CreateLabel(GeneralDialog, 33, 22, 0, 0, l->Strings[3],NULL);

	/* create date time picker for date */
	TDateTimePicker* date_dtp =
		CreateDateTimePicker(GeneralDialog,30,35,180,23,"yyyy.MM.dd.",date,dtkDate,date_dtp);

	/* create label for time */
	CreateLabel(GeneralDialog, 33, 72, 0, 0, l->Strings[4],NULL);

	/* create date time picker for time */
	TDateTimePicker* time_dtp =
		CreateDateTimePicker(GeneralDialog,30,85,180,23,"HH:mm",time,dtkTime,time_dtp);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		date = date_dtp->Date;
		time = time_dtp->Time;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}
void __fastcall TShowCmdSpecWindows::ShowPrintHeaderLines(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;   
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETPRINTHEADERLINE,CNT_SETPRINTHEADERLINE,0,5,6,GeneralDialog);

	/* create label for header #1 */
	CreateLabel(GeneralDialog, 33, 22, 0, 0, l->Strings[1],NULL);

	/* create edit box for header #1 */
	TEdit* edit1_e = CreateEdit(GeneralDialog,33,35,200,17,header1,20,edit1_e);

	/* create label for header #2 */
	CreateLabel(GeneralDialog, 33, 57, 0, 0, l->Strings[2],NULL);

	/* create edit box for header #2 */
	TEdit* edit2_e = CreateEdit(GeneralDialog,33,70,200,17,header2,20,edit2_e);

	/* create label for header #3 */
	CreateLabel(GeneralDialog, 33, 92, 0, 0, l->Strings[3],NULL);

	/* create edit box for header #3 */
	TEdit* edit3_e = CreateEdit(GeneralDialog,33,105,200,17,header3,20,edit3_e);

	/* create label for header #4 */
	CreateLabel(GeneralDialog, 33, 127, 0, 0, l->Strings[4],NULL);

	/* create edit box for header #4 */
	TEdit* edit4_e = CreateEdit(GeneralDialog,33,140,200,17,header4,20,edit4_e);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		header1 = edit1_e->Text;
		header2 = edit2_e->Text;
		header3 = edit3_e->Text;
		header4 = edit4_e->Text;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}
void __fastcall TShowCmdSpecWindows::ShowShiftStartTimes(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;      
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETSHIFTSTARTTIME,CNT_SETSHIFTSTARTTIME,0,5,6,GeneralDialog);

	/* create check box for start time #1 */
	TCheckBox* shiftstart1_cb =
		CreateCheckBox(GeneralDialog,30,29,120,17,l->Strings[1],shiftstart1,1,shiftstart1_cb);

	/* create date time picker for time #1 */
	TDateTimePicker* shifttime1_dtp =
		CreateDateTimePicker(GeneralDialog,150,27,100,23,"HH:mm",shifttime1,dtkTime,shifttime1_dtp);
	st1 = shifttime1_dtp;
	shiftstart1_cb->OnClick = ShiftStartTimeOnClick;

	/* create check box for start time #2 */
	TCheckBox* shiftstart2_cb =
		CreateCheckBox(GeneralDialog,30,56,120,17,l->Strings[2],shiftstart2,2,shiftstart2_cb);

	/* create date time picker for time #2 */
	TDateTimePicker* shifttime2_dtp =
		CreateDateTimePicker(GeneralDialog,150,54,100,23,"HH:mm",shifttime2,dtkTime,shifttime2_dtp);
	st2 = shifttime2_dtp;
	shiftstart2_cb->OnClick = ShiftStartTimeOnClick;

	/* create check box for start time #3 */
	TCheckBox* shiftstart3_cb =
		CreateCheckBox(GeneralDialog,30,81,120,17,l->Strings[3],shiftstart3,3,shiftstart3_cb);

	/* create date time picker for time #3 */
	TDateTimePicker* shifttime3_dtp =
		CreateDateTimePicker(GeneralDialog,150,79,100,23,"HH:mm",shifttime3,dtkTime,shifttime3_dtp);
	st3 = shifttime3_dtp;
	shiftstart3_cb->OnClick = ShiftStartTimeOnClick;

	/* create check box for start time #4 */
	TCheckBox* shiftstart4_cb =
		CreateCheckBox(GeneralDialog,30,110,120,17,l->Strings[4],shiftstart4,4,shiftstart4_cb);

	/* create date time picker for time #4 */
	TDateTimePicker* shifttime4_dtp =
		CreateDateTimePicker(GeneralDialog,150,108,100,23,"HH:mm",shifttime4,dtkTime,shifttime4_dtp);
	st4 = shifttime4_dtp;
	shiftstart4_cb->OnClick = ShiftStartTimeOnClick;

	ShiftStartTimeOnClick(shiftstart1_cb);
	ShiftStartTimeOnClick(shiftstart2_cb);
	ShiftStartTimeOnClick(shiftstart3_cb);
	ShiftStartTimeOnClick(shiftstart4_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		shiftstart1 = shiftstart1_cb->Checked;
		shiftstart2 = shiftstart2_cb->Checked;
		shiftstart3 = shiftstart3_cb->Checked;
		shiftstart4 = shiftstart4_cb->Checked;
		shifttime1 = shifttime1_dtp->Time;
		shifttime2 = shifttime2_dtp->Time;
		shifttime3 = shifttime3_dtp->Time;
		shifttime4 = shifttime4_dtp->Time;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowShiftBIRPrintouts(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETSHIFTBIRPRINTOUTS,CNT_SETSHIFTBIRPRINTOUTS,0,2,3,GeneralDialog);

	/* create check box for shift bir flag */
	TCheckBox* shiftbirprint_cb =
		CreateCheckBox(GeneralDialog,33,33,120,17,l->Strings[1],shiftbirprintouts,1,shiftbirprint_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		shiftbirprintouts = shiftbirprint_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowDailyBIRPrintouts(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;    
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETDAILYBIRPRINTOUTS,CNT_SETDAILYBIRPRINTOUTS,0,2,3,GeneralDialog);

	/* create check box for daily bir flag */
	TCheckBox* dailybirprint_cb =
		CreateCheckBox(GeneralDialog,33,33,120,17,l->Strings[1],dailybirprintouts,1,dailybirprint_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		dailybirprintouts = dailybirprint_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTicketedDelivery(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;    
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTICKETEDDELIVERY,CNT_SETTICKETEDDELIVERY,0,2,3,GeneralDialog);

	/* create check box for daily bir flag */
	TCheckBox* ticketeddel_cb =
		CreateCheckBox(GeneralDialog,33,33,120,17,l->Strings[1],ticketeddelivery,1,ticketeddel_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		ticketeddelivery = ticketeddel_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTCTicketedDelivery(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;   
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTCTICKETEDDELIVERY,CNT_SETTCTICKETEDDELIVERY,0,2,3,GeneralDialog);

	/* create check box for daily bir flag */
	TCheckBox* tcticketeddel_cb =
		CreateCheckBox(GeneralDialog,33,33,120,17,l->Strings[1],tcticketeddelivery,1,tcticketeddel_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		tcticketeddelivery = tcticketeddel_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTDCloseDayOfWeek(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTDCLOSEDAYOFWEEK,CNT_SETTDCLOSEDAYOFWEEK,0,9,10,GeneralDialog);

	/* create label for close day of week flag */
	CreateLabel(GeneralDialog, 33, 33, 0, 0, l->Strings[1],NULL);

	/* create combo box for ticketed delivery close day of week flags */
	TComboBox* tdclosedayofweek_cb = CreateComboBox(GeneralDialog,33,56,120,0,"",-1,tdclosedayofweek_cb);
	tdclosedayofweek_cb->Items->Add(l->Strings[2]);
	tdclosedayofweek_cb->Items->Add(l->Strings[3]);
	tdclosedayofweek_cb->Items->Add(l->Strings[4]);
	tdclosedayofweek_cb->Items->Add(l->Strings[5]);
	tdclosedayofweek_cb->Items->Add(l->Strings[6]);
	tdclosedayofweek_cb->Items->Add(l->Strings[7]);
	tdclosedayofweek_cb->Items->Add(l->Strings[8]);
	tdclosedayofweek_cb->ItemIndex = tdclosedayofweek-1;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		tdclosedayofweek = tdclosedayofweek_cb->ItemIndex+1;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowVariance(char *sec, int cnt)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,sec,cnt,0,4,5,GeneralDialog);

	/* create check box for daily flag */
	TCheckBox* daily_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],dailydelivery,1,daily_cb);

	/* create check box for weekly flag */
	TCheckBox* weekly_cb =
		CreateCheckBox(GeneralDialog,33,60,200,17,l->Strings[2],weeklydelivery,1,weekly_cb);

	/* create check box for periodic flag */
	TCheckBox* periodic_cb =
		CreateCheckBox(GeneralDialog,33,87,200,17,l->Strings[3],periodicdelivery,1,periodic_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		dailydelivery = daily_cb->Checked;
		weeklydelivery = weekly_cb->Checked;
		periodicdelivery = periodic_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTestNeededWarnings(char *sec, int cnt)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,sec,cnt,0,4,5,GeneralDialog);

	/* create check box for needed warning on/off flag */
	TCheckBox* needetst_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],testneededwarningflag,1,needetst_cb);

	/* create label for days before needed warning */
	CreateLabel(GeneralDialog, 48, 60, 0, 0, l->Strings[2],NULL);

	/* create edit control for days before warning */
	TEdit* befwarn_e = CreateEdit(GeneralDialog,48,73,200,0,"",0,befwarn_e);

	/* create up down control for days before warning */
	TUpDown* befwarn_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,0,0,befwarn_e,befwarn_ud);

	if ( (strcmp(sec, STR_SETPERIODICTEST)==0) ||
		 (strcmp(sec, STR_SETLINEPERIODICTEST)==0) )
	{
		befwarn_ud->Max = 30;
	}
	else if ( (strcmp(sec, STR_SETANNUALTEST)==0) ||
			  (strcmp(sec, STR_SETLINEANNUALTEST)==0) )
	{
		befwarn_ud->Max = 365;
	}
	else
	{
		befwarn_ud->Max = 30;
	}

	befwarn_ud->Position = daysbeforewarn;

	/* create label for days before needed alarm */
	CreateLabel(GeneralDialog, 48, 110, 0, 0, l->Strings[3],NULL);

	/* create edit control for days before alarm */
	TEdit* befalm_e = CreateEdit(GeneralDialog,48,123,200,0,"",0,befalm_e);

	/* create up down control for days before alarm */
	TUpDown* befalm_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,0,0,befalm_e,befalm_ud);

	if ( (strcmp(sec, STR_SETPERIODICTEST)==0) ||
		 (strcmp(sec, STR_SETLINEPERIODICTEST)==0) )
	{
		befalm_ud->Max = 30;
	}
	else if ( (strcmp(sec, STR_SETANNUALTEST)==0) ||
			  (strcmp(sec, STR_SETLINEANNUALTEST)==0) )
	{
		befalm_ud->Max = 365;
	}
	else
	{
		befalm_ud->Max = 30;
	}

	befalm_ud->Position = daysbeforealm;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		daysbeforewarn = befwarn_ud->Position;
		daysbeforealm = befalm_ud->Position;
		testneededwarningflag = needetst_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowLineReEnableMethod(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETLINEREENABLEMETHOD,CNT_SETLINEREENABLEMETHOD,0,4,5,GeneralDialog);

	/* create label for line re-enable */
	CreateLabel(GeneralDialog, 33, 33, 0, 0, l->Strings[1],NULL);

	/* create radio button for line re-enable pass line test method */
	TRadioButton* passlinetest_rb =
		CreateRadioButton(GeneralDialog,40,60,0,0,l->Strings[2],!passlinetest,passlinetest_rb);

	/* create radio button for line re-enable alarm acknowledge method */
	TRadioButton* almacknowledge_rb =
		CreateRadioButton(GeneralDialog,40,85,0,0,l->Strings[3],passlinetest,almacknowledge_rb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (passlinetest_rb->Checked)
		{
        	passlinetest = true;
		}
		else if (almacknowledge_rb->Checked)
		{
			passlinetest = false;
		}
		else
		{
			passlinetest = true;
		}
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowRemotePrinterPageEject(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_REMOTEPRINTERPAGEEJECT,CNT_REMOTEPRINTERPAGEEJECT,0,2,3,GeneralDialog);

	/* create check box for daily bir flag */
	TCheckBox* remprpagej_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],remoteprinterpageeject,1,remprpagej_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		remoteprinterpageeject = remprpagej_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPrintTC(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETPRINTTC,CNT_SETPRINTTC,0,2,3,GeneralDialog);

	/* create check box for daily bir flag */
	TCheckBox* printtc_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],printtc,1,printtc_cb);
	if (GeneralDialog->ShowModal()==ID_OK)
	{
		printtc = printtc_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTemperatureCompensation(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTEMPERATURECOMPENSATION,
			CNT_SETTEMPERATURECOMPENSATION,0,2,3,GeneralDialog);

	/* create label for temperature compensation */
	TLabel* tempcomp_l = CreateLabel(GeneralDialog, 33, 33, 0, 0, "", tempcomp_l);

	/* create edit control for temperature compensation */
	TEdit* tempcomp_e = CreateEdit(GeneralDialog,43,56,80,0,
							FloatToStrF(tempcomp, ffFixed, 5, 1),0,tempcomp_e);
	tc_e = 	tempcomp_e;

	/* create up down control for temperature compensation */
	TUpDown* tempcomp_ud = CreateUpDown(GeneralDialog,123,54,15,21,0,0,0,NULL,tempcomp_ud);
	/* if the system unit is u.s. */
	if (unit_index==1)
	{
		tempcomp_ud->Min = 0;
		tempcomp_ud->Max = 1200;
		tempcomp_l->Caption = l->Strings[1]+" [°F]";
	}
	else if (unit_index==2)
	{
		tempcomp_ud->Min = -170;
		tempcomp_ud->Max = 490;
		tempcomp_l->Caption = l->Strings[1]+" [°C]";
	}
	else
	{
		tempcomp_ud->Min = 0;
		tempcomp_ud->Max = 1200;
		tempcomp_l->Caption = l->Strings[1]+" [°F]";
	}
	tempcomp_ud->Position = tempcomp*10;
	tempcomp_ud->OnClick = tempcomp_udClick;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTankerLoadReport(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTANKERLOADREPORT,CNT_SETTANKERLOADREPORT,0,2,3,GeneralDialog);

	/* create check box for tanker report flag */
	TCheckBox* tankerloadreport_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],tankerloadreport,1,tankerloadreport_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		tankerloadreport = tankerloadreport_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowStickHeightOffsetFlag(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETSTICKHEIGHTOFFSET,CNT_SETSTICKHEIGHTOFFSET,0,2,3,GeneralDialog);

	/* create check box for stick height offset flag */
	TCheckBox* stickheightoffsetflag_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],stickheightoffsetflag,1,stickheightoffsetflag_cb);
	if (GeneralDialog->ShowModal()==ID_OK)
	{
		stickheightoffsetflag = stickheightoffsetflag_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowHProtocolDataFormat(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETHPROTOCOLDATAFORMAT,CNT_SETHPROTOCOLDATAFORMAT,0,3,4,GeneralDialog);

	/* create radio buttons for h-protocol format flag (height) */
	TRadioButton* h_rb =
		CreateRadioButton(GeneralDialog,33,33,240,17,l->Strings[1],!hprotocolformat,h_rb);

	/* create radio buttons for h-protocol format flag (value) */
	CreateRadioButton(GeneralDialog,33,56,240,17,l->Strings[2],hprotocolformat,NULL);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		hprotocolformat = h_rb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPrecisionTestDuration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETPRECTESTDURATION,CNT_SETPRECTESTDURATION,0,2,3,GeneralDialog);

	/* create label for precision test duration */
	CreateLabel(GeneralDialog, 33, 33, 0, 0, l->Strings[1],NULL);

	/* create edit control for precision test */
	TEdit* prectest_e = CreateEdit(GeneralDialog,43,56,60,0,"",0,prectest_e);

	/* create up down control for precision test */
	TUpDown* prectest_ud = CreateUpDown(GeneralDialog,0,0,0,0,12,744,prectest,prectest_e,prectest_ud);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		prectest = prectest_ud->Position;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPrecisionLineTestAutoConfirm02(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SET02LINETESTAUTOCONFIRM,
			CNT_SET02LINETESTAUTOCONFIRM,0,2,3,GeneralDialog);

	/* create check box for precision line test auto confirm 0.2gph flag */
	TCheckBox* linetestauto02_cb =
		CreateCheckBox(GeneralDialog,25,33,240,17,l->Strings[1],preclinetestauto02,1,linetestauto02_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		preclinetestauto02 = linetestauto02_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPrecisionLineTestAutoConfirm01(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SET01LINETESTAUTOCONFIRM,
			CNT_SET01LINETESTAUTOCONFIRM,0,2,3,GeneralDialog);

	/* create check box for precision line test auto confirm 0.1gph flag */
	TCheckBox* linetestauto01_cb =
		CreateCheckBox(GeneralDialog,25,33,240,17,l->Strings[1],preclinetestauto01,1,linetestauto01_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		preclinetestauto01 = linetestauto01_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowDaylightSavingsTime(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_DAYLIGHTSAVINGSTIME,CNT_DAYLIGHTSAVINGSTIME,
			0,12,13,GeneralDialog);
	GeneralDialog->Height = 330;
	GeneralDialog->Bevel1->Height = 290;

	/* create check box for daylight savings time flag */
	TCheckBox* dlsavtime_cb =
		CreateCheckBox(GeneralDialog,20,15,200,17,l->Strings[1],daylightsavings,1,dlsavtime_cb);

	/* create start date/time group box */
	TGroupBox* dlstart_gb = CreateGroupBox(GeneralDialog,20,35,220,120,l->Strings[2],dlstart_gb);

	/* create start month label */
	CreateLabel(dlstart_gb, 10, 18, 0, 0, l->Strings[3],NULL);

	/* create start month edit */
	TEdit* dlstartmonth_e = CreateEdit(dlstart_gb,120,15,50,0,"",0,dlstartmonth_e);

	/* create start month up-down */
	TUpDown* dlstartmonth_ud = CreateUpDown(dlstart_gb,0,0,0,0,1,12,dlstartmonth,dlstartmonth_e,dlstartmonth_ud);

	/* create start week of month label */
	CreateLabel(dlstart_gb, 10, 41, 0, 0, l->Strings[4],NULL);

	/* create start week of month edit */
	TEdit* dlstartwom_e = CreateEdit(dlstart_gb,120,38,50,0,"",0,dlstartwom_e);

	/* create start week of month up-down */
	TUpDown* dlstartwom_ud = CreateUpDown(dlstart_gb,0,0,0,0,1,6,dlstartweekofmonth,dlstartwom_e,dlstartwom_ud);

	/* create start day of week label */
	CreateLabel(dlstart_gb, 10, 64, 0, 0, l->Strings[5],NULL);

	/* create start day of week edit */
	TEdit* dlstartdow_e = CreateEdit(dlstart_gb,120,61,50,0,"",0,dlstartdow_e);

	/* create start day of week up-down */ 
	TUpDown* dlstartdow_ud = CreateUpDown(dlstart_gb,0,0,0,0,1,7,dlstartdayofweek,dlstartdow_e,dlstartdow_ud);

	/* create start hour label */
	CreateLabel(dlstart_gb, 10, 87, 0, 0, l->Strings[6],NULL);

	/* create start hour datetime picker */
	TDateTimePicker* dlstarthour_dtp =
		CreateDateTimePicker(dlstart_gb,120,84,68,23,"HH:mm",dlstarthour,dtkTime,dlstarthour_dtp);

	/* create end date/time group box */
	TGroupBox* dlend_gb = CreateGroupBox(GeneralDialog,20,160,220,120,l->Strings[7],dlend_gb);

	/* create end month label */
	CreateLabel(dlend_gb, 10, 18, 0, 0, l->Strings[8],NULL);

	/* create end month edit */
	TEdit* dlendmonth_e = CreateEdit(dlend_gb,120,15,50,0,"",0,dlendmonth_e);

	/* create end month up-down */
	TUpDown* dlendmonth_ud = CreateUpDown(dlend_gb,0,0,0,0,1,12,dlendmonth,dlendmonth_e,dlendmonth_ud);

	/* create end week of month label */ 
	CreateLabel(dlend_gb, 10, 41, 0, 0, l->Strings[9],NULL);

	/* create end week of month edit */
	TEdit* dlendwom_e = CreateEdit(dlend_gb,120,38,50,0,"",0,dlendwom_e);

	/* create end week of month up-down */
	TUpDown* dlendwom_ud = CreateUpDown(dlend_gb,0,0,0,0,1,6,dlendweekofmonth,dlendwom_e,dlendwom_ud);

	/* create end day of week label */
	CreateLabel(dlend_gb, 10, 64, 0, 0, l->Strings[10],NULL);

	/* create end day of week edit */
	TEdit* dlenddow_e = CreateEdit(dlend_gb,120,61,50,0,"",0,dlenddow_e);

	/* create end day of week up-down */ 
	TUpDown* dlenddow_ud = CreateUpDown(dlend_gb,0,0,0,0,1,7,dlenddayofweek,dlenddow_e,dlenddow_ud);

	/* create end hour label */
	CreateLabel(dlend_gb, 10, 87, 0, 0, l->Strings[11],NULL);

	/* create end hour datetime picker */
	TDateTimePicker* dlendhour_dtp =
		CreateDateTimePicker(dlend_gb,120,84,68,23,"HH:mm",dlendhour,dtkTime,dlendhour_dtp);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		daylightsavings = dlsavtime_cb->Checked;
		dlstartmonth = dlstartmonth_ud->Position;
		dlstartweekofmonth = dlstartwom_ud->Position;
		dlstartdayofweek = dlstartdow_ud->Position;
		dlstarthour = dlstarthour_dtp->Time;
		dlendmonth = dlendmonth_ud->Position;
		dlendweekofmonth = dlendwom_ud->Position;
		dlenddayofweek = dlenddow_ud->Position;
		dlendhour = dlendhour_dtp->Time;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowReDirectLocalPrintout(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETREDIRECTLOCALPRINTOUT,
			CNT_SETREDIRECTLOCALPRINTOUT,0,2,3,GeneralDialog);

	/* create check box for re-direct local printout flag */
	TCheckBox* redirlocpo_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],redirectlocalpoflag,1,redirlocpo_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		redirectlocalpoflag = redirlocpo_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowQPLDMonthlyPrintout(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETQPLDMONTHLYPRINTOUT,
			CNT_SETQPLDMONTHLYPRINTOUT,0,2,3,GeneralDialog);

	/* create check box for qpld monthly printout flag */
	TCheckBox* qpldmpo_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],qpldmonthlypoflag,1,qpldmpo_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		qpldmonthlypoflag = qpldmpo_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowEuroProtocolPrefix(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETEUROPROTOCOLPREFIX,
			CNT_SETEUROPROTOCOLPREFIX,0,3,4,GeneralDialog);

	/* create radio button for euro protocol prefix 'S' */
	TRadioButton* prefixS_rb =
		CreateRadioButton(GeneralDialog,33,33,240,17,l->Strings[1],!europrotocolprefix,prefixS_rb);

	/* create radio button for euro protocol prefix 'd' */
	TRadioButton* prefixd_rb =
		CreateRadioButton(GeneralDialog,33,56,240,17,l->Strings[2],europrotocolprefix,prefixd_rb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (prefixS_rb->Checked)
		{
			europrotocolprefix = true;
		}
		else if (prefixd_rb->Checked)
		{
			europrotocolprefix = false;
		}
		else
		{
			europrotocolprefix = true;
		}
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowSystemSecurityCode(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList; 
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SYSTEMCODE,CNT_SYSTEMCODE,0,2,3,GeneralDialog);

	/* create system code label */
	CreateLabel(GeneralDialog, 33, 33, 0, 0, l->Strings[1],NULL);

	/* create edit box for system security code */
	TEdit* syscode_e = CreateEdit(GeneralDialog,33,56,200,17,systemcode,6,syscode_e);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		systemcode = syscode_e->Text;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPortSettings(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_PORTSETTINGS,CNT_PORTSETTINGS,0,31,32,GeneralDialog);
	GeneralDialog->Height = 392;
	GeneralDialog->Bevel1->Height = 330;

	AnsiString cap = GeneralDialog->Caption;
	cap += " on port "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for baud rate */
	CreateLabel(GeneralDialog,20,22,0,0,l->Strings[2],NULL);
	/* create combo box for baud rate */
	TComboBox *baud_cb = CreateComboBox(GeneralDialog,125,20,150,0,"",-1,baud_cb);
	for (int i=3; i < 8; i++)	baud_cb->Items->Add(l->Strings[i]);
	if (baud==300)	baud_cb->ItemIndex = 0;
	if (baud==1200)	baud_cb->ItemIndex = 1;
	if (baud==2400)	baud_cb->ItemIndex = 2;
	if (baud==4800)	baud_cb->ItemIndex = 3;
	if (baud==9600)	baud_cb->ItemIndex = 4;

	/* create label for parity */
	CreateLabel(GeneralDialog,20,48,0,0,l->Strings[8],NULL);
	/* create combo box for parity */
	TComboBox *parity_cb = CreateComboBox(GeneralDialog,125,46,150,0,"",-1,parity_cb);
	for (int i=9; i < 12; i++)	parity_cb->Items->Add(l->Strings[i]);
	parity_cb->ItemIndex = parity;

	/* create label for stop bit */
	CreateLabel(GeneralDialog,20,74,0,0,l->Strings[12],NULL);
	/* create combo box for stop bit */
	TComboBox *stopbit_cb = CreateComboBox(GeneralDialog,125,72,150,0,"",-1,stopbit_cb);
	for (int i=13; i < 15; i++)	stopbit_cb->Items->Add(l->Strings[i]);
	if (stopbit==1)	stopbit_cb->ItemIndex = 0;
	if (stopbit==2)	stopbit_cb->ItemIndex = 1;

	/* create label for byte size */
	CreateLabel(GeneralDialog,20,100,0,0,l->Strings[15],NULL);
	/* create combo box for byte size */
	TComboBox *bytesize_cb = CreateComboBox(GeneralDialog,125,98,150,0,"",-1,bytesize_cb);
	for (int i=16; i < 18; i++)	bytesize_cb->Items->Add(l->Strings[i]);
	if (bytesize==7)	bytesize_cb->ItemIndex = 0;
	if (bytesize==8)	bytesize_cb->ItemIndex = 1;

	/* create label for dial type */
	CreateLabel(GeneralDialog,20,126,0,0,l->Strings[18],NULL);
	/* create combo box for dial type */
	TComboBox *dialtype_cb = CreateComboBox(GeneralDialog,125,124,150,0,"",-1,dialtype_cb);
	for (int i=19; i < 21; i++)	dialtype_cb->Items->Add(l->Strings[i]);
	dialtype_cb->ItemIndex = dialtype;

	/* create label for answer on time */
	CreateLabel(GeneralDialog,20,152,0,0,l->Strings[21],NULL);
	/* create edit for answer on time */
	TEdit *answeron_e = CreateEdit(GeneralDialog,125,150,50,0,"",0,answeron_e);
	/* create up down for answer on time */
	TUpDown *answeron_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,9,answeron,answeron_e,answeron_ud);

	/* create label for selection line */
	CreateLabel(GeneralDialog,25,178,0,0,
		"--------------------------------------------------------------",NULL);

	/* create check box for enable/disable security code */
	bool enabled;
	if (syscode[1]=='0')	enabled = false;
	if (syscode[1]=='1')	enabled = true;
	TCheckBox *syscode_cb = CreateCheckBox(GeneralDialog,20,204,0,0,l->Strings[22],enabled,1,syscode_cb);
	/* delete first flag character from string */
	syscode.Delete(1,1);
	/* create edit for security code */
	TEdit *syscode_e = CreateEdit(GeneralDialog,125,202,150,0,syscode,6,syscode_e);
	syscode_cb->Alignment = taLeftJustify;

	/* create label for modem type */
	CreateLabel(GeneralDialog,20,230,0,0,l->Strings[23],NULL);
	/* create combo box for modem type */
	TComboBox *modemtype_cb = CreateComboBox(GeneralDialog,125,228,150,0,"",-1,modemtype_cb);
	for (int i=24; i < 26; i++)	modemtype_cb->Items->Add(l->Strings[i]);
	modemtype_cb->ItemIndex = modemtype;

	/* create label for setup string */
	CreateLabel(GeneralDialog,20,256,0,0,l->Strings[26],NULL);
	/* create edit for setup string */
	TEdit *setupstr_e = CreateEdit(GeneralDialog,125,254,150,0,setupstring,20,setupstr_e);

	/* create label for dial tone interval */
	CreateLabel(GeneralDialog,20,282,0,0,l->Strings[27],NULL);
	/* create edit for dial tone interval */
	TEdit *dialtonint_e = CreateEdit(GeneralDialog,125,280,60,0,"",0,dialtonint_e);
	/* create up down for dial tone interval */
	TUpDown *dialtonint_ud = CreateUpDown(GeneralDialog,0,0,0,0,1,9999,
			dialtoneinterval,dialtonint_e,dialtonint_ud);

	/* create label for dtr normal style */
	CreateLabel(GeneralDialog,20,308,0,0,l->Strings[28],NULL);
	/* create combo box for dtr normal style */
	TComboBox *dtrnormstyle_cb = CreateComboBox(GeneralDialog,125,306,150,0,"",-1,dtrnormstyle_cb);
	for (int i=29; i < 31; i++)	dtrnormstyle_cb->Items->Add(l->Strings[i]);
	dtrnormstyle_cb->ItemIndex = dtrnormalstate;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (baud_cb->Text!="")	baud = StrToInt(baud_cb->Text);
		parity = parity_cb->ItemIndex;
		if (stopbit_cb->ItemIndex==0)	stopbit = 1;
		if (stopbit_cb->ItemIndex==1)	stopbit = 2;
		if (bytesize_cb->ItemIndex==0)	bytesize = 7;
		if (bytesize_cb->ItemIndex==1)	bytesize = 8;
		dialtype = dialtype_cb->ItemIndex;
		answeron = answeron_ud->Position;
		syscode = syscode_e->Text;
		if (syscode_cb->Checked) syscode.Insert("1",1);
		else syscode.Insert("0",1);
		modemtype = modemtype_cb->ItemIndex;
		setupstring = setupstr_e->Text;
		dialtoneinterval = dialtonint_ud->Position;
    	dtrnormalstate = dtrnormstyle_cb->ItemIndex;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPhoneDirectorySetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_PHONEDIRECTORYSETUP,CNT_PHONEDIRECTORYSETUP,0,13,14,GeneralDialog);
	GeneralDialog->Height = 282;
	GeneralDialog->Bevel1->Height = 240;

	AnsiString cap = GeneralDialog->Caption;
	cap += " on receiver "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create check box for receiver configuration */
	TCheckBox *recvconfig_cb = CreateCheckBox(GeneralDialog,20,25,150,0,
			l->Strings[2],receiverconfig,1,recvconfig_cb);

	/* create label for receiver location label */
	CreateLabel(GeneralDialog,20,55,0,0,l->Strings[3],NULL);
	/* create edit for receiver location label */
	TEdit *reclabel_e = CreateEdit(GeneralDialog,150,53,130,0,receiverlocation,20,reclabel_e);

	/* create label for receiver telephone number */
	CreateLabel(GeneralDialog,20,83,0,0,l->Strings[4],NULL);
	/* create edit for receiver telephone number */
	TEdit *rectelnr_e = CreateEdit(GeneralDialog,150,81,130,0,receivertelnumber,20,rectelnr_e);

	/* create label for receiver port number to dial */
	CreateLabel(GeneralDialog,20,111,0,0,l->Strings[5],NULL);
	/* create edit for receiver port number to dial */
	TEdit *recportnr_e = CreateEdit(GeneralDialog,150,109,50,0,"",0,recportnr_e);
	/* create up down for receiver port number to dial */
	TUpDown *recportnr_ud = CreateUpDown(GeneralDialog,0,0,0,0,1,6,
			receiverportnumber,recportnr_e,recportnr_ud);

	/* create label for receiver type */
	CreateLabel(GeneralDialog,20,139,0,0,l->Strings[6],NULL);
	/* create combo box for receiver type */
	TComboBox *rectype_cb = CreateComboBox(GeneralDialog,150,137,130,0,"",-1,rectype_cb);
	for (int i=7; i < 10; i++)	rectype_cb->Items->Add(l->Strings[i]);
	rectype_cb->ItemIndex = receivertype-1;

	/* create label for receiver retry number */
	CreateLabel(GeneralDialog,20,167,0,0,l->Strings[10],NULL);
	/* create edit for receiver retry number */
	TEdit *recretrynr_e = CreateEdit(GeneralDialog,150,165,50,0,"",0,recretrynr_e);
	/* create up down for receiver retry number */
	TUpDown *recretrynr_ud = CreateUpDown(GeneralDialog,0,0,0,0,3,99,
			receiverretrynumber,recretrynr_e,recretrynr_ud);

	/* create label for receiver retry delay time */
	CreateLabel(GeneralDialog,20,195,0,0,l->Strings[11],NULL);
	/* create edit for receiver retry delay time */
	TEdit *recretrydt_e = CreateEdit(GeneralDialog,150,193,50,0,"",0,recretrydt_e);
	/* create up down for receiver retry delay time */
	TUpDown *recretrydt_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,60,
			receiverdelaytime,recretrydt_e,recretrydt_ud);

	/* create check box for receiver confirmation report */
	TCheckBox *recconfrep_cb = CreateCheckBox(GeneralDialog,20,218,200,0,
			l->Strings[12],receiverconfirmation,1,recconfrep_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		receiverconfig = recvconfig_cb->Checked;
		receiverlocation = reclabel_e->Text;
		receivertelnumber = rectelnr_e->Text;
		receiverportnumber = recportnr_ud->Position;
		receivertype = rectype_cb->ItemIndex+1;
		receiverretrynumber = recretrynr_ud->Position;
		receiverdelaytime = recretrydt_ud->Position;
		receiverconfirmation = recconfrep_cb->Checked;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowAutodialSetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_AUTODIALSETUP,CNT_AUTODIALSETUP,0,44,45,GeneralDialog);
	GeneralDialog->Height = 540;
	GeneralDialog->Width = 655;
	GeneralDialog->Bevel1->Height = 498;
	GeneralDialog->Bevel1->Width = 552;
	GeneralDialog->OKBtn->Left = 567;
	GeneralDialog->CancelBtn->Left = 567;

	AnsiString cap = GeneralDialog->Caption;
	cap += " on receiver "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create report list group box */
	TGroupBox *reportlist_gb = CreateGroupBox(GeneralDialog, 17, 17, 260, 190, l->Strings[2], reportlist_gb);
	/* create check boxes for report list */
	TCheckBox *sysstat_cb = CreateCheckBox(reportlist_gb, 10, 20, 120, 0,
			l->Strings[3], reportlist[0], 1, sysstat_cb);
	TCheckBox *nonphis_cb = CreateCheckBox(reportlist_gb, 10, 38, 120, 0,
			l->Strings[4], reportlist[2], 2, nonphis_cb);
	TCheckBox *invtory_cb = CreateCheckBox(reportlist_gb, 10, 56, 120, 0,
			l->Strings[5], reportlist[5], 3, invtory_cb);
	TCheckBox *leakdet_cb = CreateCheckBox(reportlist_gb, 10, 72, 120, 0,
			l->Strings[6], reportlist[7], 4, leakdet_cb);
	TCheckBox *prlldre_cb = CreateCheckBox(reportlist_gb, 10, 90, 120, 0,
			l->Strings[7], reportlist[3], 5, prlldre_cb);
	TCheckBox *perdlvy_cb = CreateCheckBox(reportlist_gb, 10, 108, 120, 0,
			l->Strings[8], reportlist[16], 6, perdlvy_cb);
	TCheckBox *fuelman_cb = CreateCheckBox(reportlist_gb, 10, 126, 120, 0,
			l->Strings[9], reportlist[10], 7, fuelman_cb);
	TCheckBox *lastdlv_cb = CreateCheckBox(reportlist_gb, 10, 142, 120, 0, 
			l->Strings[10], reportlist[15], 8, lastdlv_cb);
	TCheckBox *prihist_cb = CreateCheckBox(reportlist_gb, 10, 160, 120, 0,
			l->Strings[11], reportlist[1], 9, prihist_cb);
	TCheckBox *perbvar_cb = CreateCheckBox(reportlist_gb, 130, 20, 120, 0,
			l->Strings[12], reportlist[17], 10, perbvar_cb);
	TCheckBox *intnkst_cb = CreateCheckBox(reportlist_gb, 130, 38, 120, 0,
			l->Strings[13], reportlist[4], 11, intnkst_cb);
	TCheckBox *delivey_cb = CreateCheckBox(reportlist_gb, 130, 56, 120, 0,
			l->Strings[14], reportlist[6], 12, delivey_cb);
	TCheckBox *shftinv_cb = CreateCheckBox(reportlist_gb, 130, 72, 120, 0,
			l->Strings[15], reportlist[8], 13, shftinv_cb);
	TCheckBox *dailyva_cb = CreateCheckBox(reportlist_gb, 130, 90, 120, 0,
			l->Strings[16], reportlist[18], 14, dailyva_cb);
	TCheckBox *perrowr_cb = CreateCheckBox(reportlist_gb, 130, 108, 120, 0,
			l->Strings[17], reportlist[12], 15, perrowr_cb);
	TCheckBox *csldrep_cb = CreateCheckBox(reportlist_gb, 130, 126, 120, 0,
			l->Strings[18], reportlist[14], 16, csldrep_cb);
	TCheckBox *lleakst_cb = CreateCheckBox(reportlist_gb, 130, 142, 120, 0,
			l->Strings[19], reportlist[11], 17, lleakst_cb);
	TCheckBox *wplldre_cb = CreateCheckBox(reportlist_gb, 130, 160, 120, 0,
			l->Strings[20], reportlist[10], 18, wplldre_cb);

	/* create auto dial method group box */
	TGroupBox *admethod_gb = CreateGroupBox(GeneralDialog, 17, 210, 260, 60, l->Strings[21], admethod_gb);
	/* create auto dial method radio buttons */
	TRadioButton *allphones_rb = CreateRadioButton(admethod_gb, 25, 15,
		120, 0, l->Strings[22], !autodialmethod, allphones_rb);
	TRadioButton *sgnphones_rb = CreateRadioButton(admethod_gb, 25, 33,
		120, 0, l->Strings[23], autodialmethod, sgnphones_rb);

	/* create auto dial frequency group box */
	TGroupBox *adfreq_gb = CreateGroupBox(GeneralDialog, 290, 17, 260, 470, l->Strings[24], adfreq_gb);
	/* create auto dial frequencies radio buttons */
	TRadioButton *ondate_rb = CreateRadioButton(adfreq_gb, 15, 15,
		100, 0, l->Strings[25], false, ondate_rb);
	TRadioButton *annually_rb = CreateRadioButton(adfreq_gb, 15, 33,
		100, 0, l->Strings[26], false, annually_rb);
	TRadioButton *monthly_rb = CreateRadioButton(adfreq_gb, 15, 51,
		100, 0, l->Strings[27], false, monthly_rb);
	TRadioButton *weekly_rb = CreateRadioButton(adfreq_gb, 145, 15,
		100, 0, l->Strings[28], false, weekly_rb);
	TRadioButton *daily_rb = CreateRadioButton(adfreq_gb, 145, 33,
		100, 0, l->Strings[29], false, daily_rb);
	TRadioButton *birend_rb = CreateRadioButton(adfreq_gb, 145, 51,
		100, 0, l->Strings[30], false, birend_rb);
	switch (frequencytype)
	{
		case 1: ondate_rb->Checked = true; break;
		case 2: annually_rb->Checked = true; break;
		case 3: monthly_rb->Checked = true; break;
		case 4: weekly_rb->Checked = true; break;
		case 5: daily_rb->Checked = true; break;
		case 6: break;
		case 7: break;
		case 8: birend_rb->Checked = true; break;
	}
	TCheckBox *timeen_cb = CreateCheckBox(adfreq_gb, 15, 69, 120, 0, l->Strings[46], false, 1, timeen_cb);
	if ((double)freqtime==-1)	timeen_cb->Checked = false;
	else	timeen_cb->Checked = true;

	/* create on date group box */
	TGroupBox *ondate_gb = CreateGroupBox(adfreq_gb, 15, 95, 225, 57, l->Strings[31], ondate_gb);
	/* create date time pickers for on date */
	TDateTimePicker *ondate_dtp = CreateDateTimePicker(ondate_gb, 10, 20, 100, 0, "yyyy.MM.dd.", freqdate,
		dtkDate, ondate_dtp);
	TDateTimePicker *ontime_dtp = CreateDateTimePicker(ondate_gb, 120, 20, 100, 0, "HH:mm", freqtime,
		dtkTime, ontime_dtp);

	/* create annually group box */
	TGroupBox *annually_gb = CreateGroupBox(adfreq_gb, 15, 152, 225, 90, l->Strings[32], annually_gb);
	/* create controls for annually frequency */
	CreateLabel(annually_gb, 20, 15, 0, 0, l->Strings[33],NULL);
	TEdit *montha_e = CreateEdit(annually_gb, 80, 15, 50, 0, "", 0, montha_e);
	TUpDown *montha_ud = CreateUpDown(annually_gb, 0, 0, 0, 0, 1, 12, freqmonth, montha_e, montha_ud);
	CreateLabel(annually_gb, 20, 38, 0, 0, l->Strings[34],NULL);
	TEdit *weeka_e = CreateEdit(annually_gb, 80, 37, 50, 0, "", 0, weeka_e);
	TUpDown *weeka_ud = CreateUpDown(annually_gb, 0, 0, 0, 0, 1, 6, freqweek, weeka_e, weeka_ud);
	CreateLabel(annually_gb, 20, 61, 0, 0, l->Strings[35],NULL);
	TEdit *daya_e = CreateEdit(annually_gb, 80, 59, 50, 0, "", 0, daya_e);
	TUpDown *daya_ud = CreateUpDown(annually_gb, 0, 0, 0, 0, 1, 7, freqday, daya_e, daya_ud);

	/* create monthly group box */
	TGroupBox *monthly_gb = CreateGroupBox(adfreq_gb, 15, 242, 225, 67, l->Strings[36], monthly_gb);
	/* create controls for monthly frequency */
	CreateLabel(monthly_gb, 20, 15, 0, 0, l->Strings[37],NULL);
	TEdit *weekm_e = CreateEdit(monthly_gb, 80, 15, 50, 0, "", 0, weekm_e);
	TUpDown *weekm_ud = CreateUpDown(monthly_gb, 0, 0, 0, 0, 1, 6, freqweek, weekm_e, weekm_ud);
	CreateLabel(monthly_gb, 20, 38, 0, 0, l->Strings[38],NULL);
	TEdit *daym_e = CreateEdit(monthly_gb, 80, 37, 50, 0, "", 0, daym_e);
	TUpDown *daym_ud = CreateUpDown(monthly_gb, 0, 0, 0, 0, 1, 7, freqday, daym_e, daym_ud);

	/* create weekly group box */
	TGroupBox *weekly_gb = CreateGroupBox(adfreq_gb, 15, 309, 225, 50, l->Strings[39], weekly_gb);
	/* create controls for weekly frequency */
	CreateLabel(weekly_gb, 20, 20, 0, 0, l->Strings[40],NULL);
	TEdit *dayw_e = CreateEdit(weekly_gb, 80, 18, 50, 0, "", 0, dayw_e);
	TUpDown *dayw_ud = CreateUpDown(weekly_gb, 0, 0, 0, 0, 1, 7, freqday, dayw_e, dayw_ud);

	/* create daily group box */
	TGroupBox *daily_gb = CreateGroupBox(adfreq_gb, 15, 359, 225, 50, l->Strings[41], daily_gb);
	/* create date time picker for daily frequency */
	TDateTimePicker *time_dtp = CreateDateTimePicker(daily_gb, 10, 20, 100, 0, "HH:mm", freqtime,
		dtkTime, time_dtp);

	/* create bir end group box */
	TGroupBox *birend_gb = CreateGroupBox(adfreq_gb, 15, 409, 225, 50, l->Strings[42], birend_gb);
	TCheckBox *birend_cb = CreateCheckBox(birend_gb, 20, 20, 200, 0, l->Strings[43], birend, 1, birend_cb);


	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (sysstat_cb->Checked)	reportlist[0] = true;
		else reportlist[0] = false;
		if (nonphis_cb->Checked)	reportlist[2] = true;
		else reportlist[2] = false;
		if (invtory_cb->Checked)	reportlist[5] = true;
		else reportlist[5] = false;
		if (leakdet_cb->Checked)	reportlist[7] = true;
		else reportlist[7] = false;
		if (prlldre_cb->Checked)	reportlist[9] = true;
		else reportlist[9] = false;
		if (perdlvy_cb->Checked)	reportlist[16] = true;
		else reportlist[16] = false;
		if (fuelman_cb->Checked)	reportlist[13] = true;
		else reportlist[13] = false;
		if (lastdlv_cb->Checked)	reportlist[15] = true;
		else reportlist[15] = false;
		if (prihist_cb->Checked)	reportlist[1] = true;
		else reportlist[1] = false;
		if (perbvar_cb->Checked)	reportlist[17] = true;
		else reportlist[17] = false;
		if (intnkst_cb->Checked)	reportlist[4] = true;
		else reportlist[4] = false;
		if (delivey_cb->Checked)	reportlist[6] = true;
		else reportlist[6] = false;
		if (shftinv_cb->Checked)	reportlist[8] = true;
		else reportlist[8] = false;
		if (dailyva_cb->Checked)	reportlist[18] = true;
		else reportlist[18] = false;
		if (perrowr_cb->Checked)	reportlist[12] = true;
		else reportlist[12] = false;
		if (csldrep_cb->Checked)	reportlist[14] = true;
		else reportlist[14] = false;
		if (lleakst_cb->Checked)	reportlist[11] = true;
		else reportlist[11] = false;
		if (wplldre_cb->Checked)	reportlist[10] = true;
		else reportlist[10] = false;

		if (allphones_rb->Checked)	autodialmethod = false;
		if (sgnphones_rb->Checked)	autodialmethod = true;

		if (ondate_rb->Checked)
		{
			frequencytype = 1;
			freqdate = ondate_dtp->Date;
		}
		if (annually_rb->Checked)
		{
			frequencytype = 2;
			freqmonth = montha_ud->Position;
			freqweek = weeka_ud->Position;
			freqday = daya_ud->Position;
		}
		if (monthly_rb->Checked)
		{
			frequencytype = 3;
			freqweek = weekm_ud->Position;
			freqday = daym_ud->Position;
		}
		if (weekly_rb->Checked)
		{
			frequencytype = 4;
			freqday = dayw_ud->Position;
		}
		if (daily_rb->Checked)
		{
			frequencytype = 5;
		}
		if (birend_rb->Checked)
		{
			frequencytype = 8;
			birend = birend_cb->Checked;
		}

		if (timeen_cb->Checked)	freqtime = ontime_dtp->Time;
		else	freqtime = -1;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowAutodialOnAlarms(void)
{
	/* not used */

	/* it takes the list of strings of the specified dialog window language 
	TStringList *l = new TStringList;*/
	/* initialze the dialog 
	GeneralDialog = InitDialog(l,STR_SETAUTODIALONALARMS,CNT_SETAUTODIALONALARMS,0,152,153,GeneralDialog);*/

	/* check boxes for system alarms 
	TCheckBox *sys; TCheckBox *sys01; TCheckBox *sys02; TCheckBox *sys03; TCheckBox *sys04;
	TCheckBox *sys05; TCheckBox *sys06; TCheckBox *sys07; TCheckBox *sys08; TCheckBox *sys09;
	TCheckBox *sys10; TCheckBox *sys11; TCheckBox *sys12; TCheckBox *sys13; TCheckBox *sys14;
	TCheckBox *sys15; TCheckBox *sys16; TCheckBox *sys17; TCheckBox *sys18;
	TCheckBox *sys_cb[19] = {sys,sys01,sys02,sys03,sys04,sys05,sys06,sys07,sys08,sys09,sys10,sys11,
							   sys12,sys13,sys14,sys15,sys16,sys17,sys18};*/
	/* check boxes for tank alarms 
	TCheckBox *tnk; TCheckBox *tnk01; TCheckBox *tnk02; TCheckBox *tnk03; TCheckBox *tnk04;
	TCheckBox *tnk05; TCheckBox *tnk06; TCheckBox *tnk07; TCheckBox *tnk08; TCheckBox *tnk09;
	TCheckBox *tnk10; TCheckBox *tnk11; TCheckBox *tnk12; TCheckBox *tnk13; TCheckBox *tnk14;
	TCheckBox *tnk15; TCheckBox *tnk16; TCheckBox *tnk17; TCheckBox *tnk18; TCheckBox *tnk19;
	TCheckBox *tnk20; TCheckBox *tnk21; TCheckBox *tnk22; TCheckBox *tnk23; TCheckBox *tnk24;
	TCheckBox *tnk25; TCheckBox *tnk26; TCheckBox *tnk27; TCheckBox *tnk28; TCheckBox *tnk29;
	TCheckBox *tnk_cb[30] = {tnk,tnk01,tnk02,tnk03,tnk04,tnk05,tnk06,tnk07,tnk08,tnk09,tnk10,tnk11,
							   tnk12,tnk13,tnk14,tnk15,tnk16,tnk17,tnk18,tnk19,tnk20,tnk21,tnk22,tnk23,
							   tnk24,tnk25,tnk26,tnk27,tnk28,tnk29};*/
	/* check boxes for liquid alarms 
	TCheckBox *liq; TCheckBox *liq01; TCheckBox *liq02; TCheckBox *liq03; TCheckBox *liq04;
	TCheckBox *liq05; TCheckBox *liq06; TCheckBox *liq07; TCheckBox *liq08; TCheckBox *liq09;
	TCheckBox *liq_cb[10] = {liq,liq01,liq02,liq03,liq04,liq05,liq06,liq07,liq08,liq09};*/
	/* check boxes for vapor alarms
	TCheckBox *vap; TCheckBox *vap01; TCheckBox *vap02; TCheckBox *vap03; TCheckBox *vap04;
	TCheckBox *vap05; TCheckBox *vap06; TCheckBox *vap07; TCheckBox *vap08; TCheckBox *vap09;
	TCheckBox *vap_cb[10] = {vap,vap01,vap02,vap03,vap04,vap05,vap06,vap07,vap08,vap09}; */
	/* check boxes for input alarms 
	TCheckBox *inp; TCheckBox *inp01; TCheckBox *inp02; TCheckBox *inp03;
	TCheckBox *inp_cb[4] = {inp,inp01,inp02,inp03}*/;
	/* check boxes for volumetric line leak alarms 
	TCheckBox *vll; TCheckBox *vll01; TCheckBox *vll02; TCheckBox *vll03; TCheckBox *vll04;
	TCheckBox *vll05; TCheckBox *vll06; TCheckBox *vll07; TCheckBox *vll08; TCheckBox *vll09;
	TCheckBox *vll10; TCheckBox *vll11; TCheckBox *vll12; TCheckBox *vll13; TCheckBox *vll14;
	TCheckBox *vll15; TCheckBox *vll16; TCheckBox *vll17; TCheckBox *vll18; TCheckBox *vll19;
	TCheckBox *vll20; TCheckBox *vll21; TCheckBox *vll22; TCheckBox *vll23; TCheckBox *vll24;
	TCheckBox *vll25; TCheckBox *vll26; TCheckBox *vll27; TCheckBox *vll28;
	TCheckBox *vll_cb[29] = {vll,vll01,vll02,vll03,vll04,vll05,vll06,vll07,vll08,vll09,vll10,vll11,
							   vll12,vll13,vll14,vll15,vll16,vll17,vll18,vll19,vll20,vll21,vll22,vll23,
							   vll24,vll25,vll26,vll27,vll28};*/
	/* check boxes for groundwater alarms 
	TCheckBox *gdw; TCheckBox *gdw01; TCheckBox *gdw02; TCheckBox *gdw03; TCheckBox *gdw04;
	TCheckBox *gdw05; TCheckBox *gdw06; TCheckBox *gdw07; TCheckBox *gdw08; TCheckBox *gdw09;
	TCheckBox *gdw_cb[10] = {gdw,gdw01,gdw02,gdw03,gdw04,gdw05,gdw06,gdw07,gdw08,gdw09};*/
	/* check boxes for type a alarms 
	TCheckBox *tya; TCheckBox *tya01; TCheckBox *tya02; TCheckBox *tya03; TCheckBox *tya04;
	TCheckBox *tya05; TCheckBox *tya06; TCheckBox *tya07; TCheckBox *tya08; TCheckBox *tya09;
	TCheckBox *tya_cb[10] = {tya,tya01,tya02,tya03,tya04,tya05,tya06,tya07,tya08,tya09};*/
	/* check boxes for type b alarms 
	TCheckBox *tyb; TCheckBox *tyb01; TCheckBox *tyb02; TCheckBox *tyb03; TCheckBox *tyb04;
	TCheckBox *tyb05; TCheckBox *tyb06; TCheckBox *tyb07; TCheckBox *tyb08; TCheckBox *tyb09;
	TCheckBox *tyb_cb[10] = {tyb,tyb01,tyb02,tyb03,tyb04,tyb05,tyb06,tyb07,tyb08,tyb09};*/
	/* check boxes for universal sensor alarms 
	TCheckBox *uni; TCheckBox *uni01; TCheckBox *uni02; TCheckBox *uni03; TCheckBox *uni04;
	TCheckBox *uni05; TCheckBox *uni06; TCheckBox *uni07; TCheckBox *uni08; TCheckBox *uni09;
	TCheckBox *uni_cb[10] = {uni,uni01,uni02,uni03,uni04,uni05,uni06,uni07,uni08,uni09};*/
	/* check boxes for auto-dial fax alarms 
	TCheckBox *adf; TCheckBox *adf01; TCheckBox *adf02; TCheckBox *adf03; TCheckBox *adf04;
	TCheckBox *adf05;
	TCheckBox *adf_cb[6] = {adf,adf01,adf02,adf03,adf04,adf05};*/
	/* check boxes for mdim alarms 
	TCheckBox *mdm; TCheckBox *mdm01; TCheckBox *mdm02; TCheckBox *mdm03;
	TCheckBox *mdm_cb[4] = {mdm,mdm01,mdm02,mdm03};*/
	/* check boxes for edim alarms 
	TCheckBox *edm; TCheckBox *edm01; TCheckBox *edm02; TCheckBox *edm03;
	TCheckBox *edm_cb[4] = {edm,edm01,edm02,edm03};*/
	/* check boxes for product alarms 
	TCheckBox *prd; TCheckBox *prd01; TCheckBox *prd02; TCheckBox *prd03; TCheckBox *prd04;
	TCheckBox *prd_cb[5] = {prd,prd01,prd02,prd03,prd04};*/
	/* check boxes for plld alarms 
	TCheckBox *pld; TCheckBox *pld01; TCheckBox *pld02; TCheckBox *pld03; TCheckBox *pld04;
	TCheckBox *pld05; TCheckBox *pld06; TCheckBox *pld07; TCheckBox *pld08; TCheckBox *pld09;
	TCheckBox *pld10; TCheckBox *pld11; TCheckBox *pld12; TCheckBox *pld13; TCheckBox *pld14;
	TCheckBox *pld15; TCheckBox *pld16; TCheckBox *pld17; TCheckBox *pld18;
	TCheckBox *pld_cb[19] = {pld,pld01,pld02,pld03,pld04,pld05,pld06,pld07,pld08,pld09,pld10,pld11,
							   pld12,pld13,pld14,pld15,pld16,pld17,pld18};*/
	/* check boxes for wplld alarms 
	TCheckBox *wld; TCheckBox *wld01; TCheckBox *wld02; TCheckBox *wld03; TCheckBox *wld04;
	TCheckBox *wld05; TCheckBox *wld06; TCheckBox *wld07; TCheckBox *wld08; TCheckBox *wld09;
	TCheckBox *wld10; TCheckBox *wld11; TCheckBox *wld12; TCheckBox *wld13; TCheckBox *wld14;
	TCheckBox *wld15; TCheckBox *wld16; TCheckBox *wld17; TCheckBox *wld18;
	TCheckBox *wld_cb[19] = {wld,wld01,wld02,wld03,wld04,wld05,wld06,wld07,wld08,wld09,wld10,wld11,
							   wld12,wld13,wld14,wld15,wld16,wld17,wld18};*/

	/*for (int i=0; i < 10; i++)
	{
		sys_cb[0] = CreateCheckBox(GeneralDialog,20,20+23*i,
		150,0,l->Strings[17+i],SystemAlarm[i],i,
		sys_cb[0]);
	}

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;*/
}

void __fastcall TShowCmdSpecWindows::ShowRS232EOM(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETRS232ENDOFMESSAGE,CNT_SETRS232ENDOFMESSAGE,0,2,3,GeneralDialog);

	/* create check box for daily bir flag */
	TCheckBox* rs232eom_cb =
		CreateCheckBox(GeneralDialog,33,33,200,17,l->Strings[1],rs232eom,1,rs232eom_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		rs232eom = rs232eom_cb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTankConfiguration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTANKCONFIGURATION,CNT_SETTANKCONFIGURATION,0,17,18,GeneralDialog);

	GeneralDialog->Height = 390;
	GeneralDialog->Bevel1->Height = 348;

	/* create check boxes for tank configuration */
	TCheckBox* slot1pos1_cb =
		CreateCheckBox(GeneralDialog,33,23,200,0,l->Strings[1],tankconfig[0],1,slot1pos1_cb);
	TCheckBox* slot1pos2_cb =
		CreateCheckBox(GeneralDialog,33,41,200,0,l->Strings[2],tankconfig[1],2,slot1pos2_cb);
	TCheckBox* slot1pos3_cb =
		CreateCheckBox(GeneralDialog,33,59,200,0,l->Strings[3],tankconfig[2],3,slot1pos3_cb);
	TCheckBox* slot1pos4_cb =
		CreateCheckBox(GeneralDialog,33,77,200,0,l->Strings[4],tankconfig[3],4,slot1pos4_cb);
	TCheckBox* slot2pos1_cb =
		CreateCheckBox(GeneralDialog,33,100,200,0,l->Strings[5],tankconfig[4],5,slot2pos1_cb);
	TCheckBox* slot2pos2_cb =
		CreateCheckBox(GeneralDialog,33,118,200,0,l->Strings[6],tankconfig[5],6,slot2pos2_cb);
	TCheckBox* slot2pos3_cb =
		CreateCheckBox(GeneralDialog,33,136,200,0,l->Strings[7],tankconfig[6],7,slot2pos3_cb);
	TCheckBox* slot2pos4_cb =
		CreateCheckBox(GeneralDialog,33,154,200,0,l->Strings[8],tankconfig[7],8,slot2pos4_cb);
	TCheckBox* slot3pos1_cb =
		CreateCheckBox(GeneralDialog,33,177,200,0,l->Strings[9],tankconfig[8],9,slot3pos1_cb);
	TCheckBox* slot3pos2_cb =
		CreateCheckBox(GeneralDialog,33,195,200,0,l->Strings[10],tankconfig[9],10,slot3pos2_cb);
	TCheckBox* slot3pos3_cb =
		CreateCheckBox(GeneralDialog,33,213,200,0,l->Strings[11],tankconfig[10],11,slot3pos3_cb);
	TCheckBox* slot3pos4_cb =
		CreateCheckBox(GeneralDialog,33,231,200,0,l->Strings[12],tankconfig[11],12,slot3pos4_cb);
	TCheckBox* slot4pos1_cb =
		CreateCheckBox(GeneralDialog,33,254,200,0,l->Strings[13],tankconfig[12],13,slot4pos1_cb);
	TCheckBox* slot4pos2_cb =
		CreateCheckBox(GeneralDialog,33,272,200,0,l->Strings[14],tankconfig[13],14,slot4pos2_cb);
	TCheckBox* slot4pos3_cb =
		CreateCheckBox(GeneralDialog,33,290,200,0,l->Strings[15],tankconfig[14],15,slot4pos3_cb);
	TCheckBox* slot4pos4_cb =
		CreateCheckBox(GeneralDialog,33,308,200,0,l->Strings[16],tankconfig[15],16,slot4pos4_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (slot1pos1_cb->Checked) tankconfig[0] = true;
		else tankconfig[0] = false;
		if (slot1pos2_cb->Checked) tankconfig[1] = true;
		else tankconfig[1] = false;
		if (slot1pos3_cb->Checked) tankconfig[2] = true;
		else tankconfig[2] = false;
		if (slot1pos4_cb->Checked) tankconfig[3] = true;
		else tankconfig[3] = false;
		if (slot2pos1_cb->Checked) tankconfig[4] = true;
		else tankconfig[4] = false;
		if (slot2pos2_cb->Checked) tankconfig[5] = true;
		else tankconfig[5] = false;
		if (slot2pos3_cb->Checked) tankconfig[6] = true;
		else tankconfig[6] = false;
		if (slot2pos4_cb->Checked) tankconfig[7] = true;
		else tankconfig[7] = false;
		if (slot3pos1_cb->Checked) tankconfig[8] = true;
		else tankconfig[8] = false;
		if (slot3pos2_cb->Checked) tankconfig[9] = true;
		else tankconfig[9] = false;
		if (slot3pos3_cb->Checked) tankconfig[10] = true;
		else tankconfig[10] = false;
		if (slot3pos4_cb->Checked) tankconfig[11] = true;
		else tankconfig[11] = false;
		if (slot4pos1_cb->Checked) tankconfig[12] = true;
		else tankconfig[12] = false;
		if (slot4pos2_cb->Checked) tankconfig[13] = true;
		else tankconfig[13] = false;
		if (slot4pos3_cb->Checked) tankconfig[14] = true;
		else tankconfig[14] = false;
		if (slot4pos4_cb->Checked) tankconfig[15] = true;
		else tankconfig[15] = false;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowInTankSetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_INTANKSETTINGS,CNT_INTANKSETTINGS,0,53,54,GeneralDialog);

	GeneralDialog->Height = 540;
	GeneralDialog->Width = 655;
	GeneralDialog->Bevel1->Height = 498;
	GeneralDialog->Bevel1->Width = 552;
	GeneralDialog->OKBtn->Left = 567;
	GeneralDialog->CancelBtn->Left = 567;

	AnsiString cap = GeneralDialog->Caption;
	cap += " on tank "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for product label */
	CreateLabel(GeneralDialog,20,20,0,0,l->Strings[1],NULL);
	/* create edit for product label */
	TEdit *productl_e = CreateEdit(GeneralDialog,150,18,100,0,productlabel,20,productl_e);

	/* create label for product code */
	CreateLabel(GeneralDialog,20,43,0,0,l->Strings[2],NULL);
	/* create edit for product code */
	TEdit *productc_e = CreateEdit(GeneralDialog,150,41,100,0,productcode,1,productc_e);

	/* create label for product thermal coefficient */
	CreateLabel(GeneralDialog,20,66,0,0,l->Strings[3],NULL);
	/* create edit for product thermal coefficient */
	TEdit *producttc_e = CreateEdit(GeneralDialog,150,64,85,0,
			FloatToStrF(producttermalcoeff, ffFixed, 5, 5),0,producttc_e);
	/* create up down for product thermal coefficient */
	TUpDown *thermalcoeff_ud = CreateUpDown(GeneralDialog,235,64,15,21,-32767,32767,
			producttermalcoeff,NULL,thermalcoeff_ud);
	producttc_e->OnChange = producttc_eChange;
	thermalcoeff_e = producttc_e;
	thermalcoeff_ud->OnClick = thermalcoeff_udClick;

	/* create label for tank diameter */
	CreateLabel(GeneralDialog,20,89,0,0,l->Strings[4],NULL);
	/* create edit for tank diameter */
	TEdit *tankdiam_e = CreateEdit(GeneralDialog,150,87,85,0,
			FloatToStrF(tankdiameter, ffFixed, 5, 2),0,tankdiam_e);
	/* create up down for tank diameter */
	TUpDown *tankdiam_ud = CreateUpDown(GeneralDialog,235,87,15,21,-10000,10000,
			tankdiameter,NULL,tankdiam_ud);
	tankdiam_e->OnChange = tankdiam_eChange;
	tdiam_e = tankdiam_e;
	tankdiam_ud->OnClick = tankdiam_udClick;

	/* create check box for meter data present */
	TCheckBox *meterdp_cb = CreateCheckBox(GeneralDialog,20,112,150,0,l->Strings[5],
		meterdatapresent,1,meterdp_cb);
	meterdp_cb->OnClick = meterdp_cbClick;

	/* create label for end factor */ 
	endf_l = CreateLabel(GeneralDialog,50,130,0,0,l->Strings[6],endf_l);
	//endf_l = endfact_l;
	/* create combo box for end factor type */
	TComboBox *endfact_cb = CreateComboBox(GeneralDialog,150,128,102,0,"",0,endfact_cb);
	for (int i=7; i < 11; i++)	endfact_cb->Items->Add(l->Strings[i]);
	endf_cb = endfact_cb;
	endfact_cb->ItemIndex = endfactor;
	endfact_cb->OnClick = endfact_cbClick;
	/* create label for end value */
	endv_l = CreateLabel(GeneralDialog,50,153,0,0,l->Strings[11],endv_l);
	//endv_l = endval_l;
	/* create edit for end value */
	TEdit *endval_e = CreateEdit(GeneralDialog,150,151,85,0,
			FloatToStrF(endvalue, ffFixed, 5, 1),0,endval_e);
	endv_e = endval_e;
	/* create up down for end value */
	TUpDown *endval_ud = CreateUpDown(GeneralDialog,235,151,15,21,-10,10,
			endvalue,NULL,endval_ud);
	endv_ud = endval_ud;
	endval_ud->OnClick = endval_udClick;

	/* create label for calibration update */
	cupd_l = CreateLabel(GeneralDialog,50,176,0,0,l->Strings[13],cupd_l);
	//cupd_l = calupd_l;
	/* create combo box for calibration update */
	TComboBox *calupd_cb = CreateComboBox(GeneralDialog,150,174,102,0,"",0,calupd_cb);
	for (int i=14; i < 18; i++)	calupd_cb->Items->Add(l->Strings[i]);
	cupd_cb = calupd_cb;
	calupd_cb->ItemIndex = calibrationupdate-1;

	meterdp_cbClick(meterdp_cb);
	if (meterdp_cb->Checked)
	{
		endfact_cbClick(endfact_cb);
		endval_udClick(endval_ud,(TUDBtnType)2);
	}

	/* create label for float size */
	CreateLabel(GeneralDialog,20,199,0,0,l->Strings[18],NULL);
	/* create combo box for float size */
	TComboBox *floats_cb = CreateComboBox(GeneralDialog,150,197,102,0,"",0,floats_cb);
	for (int i=19; i < 24; i++)	floats_cb->Items->Add(l->Strings[i]);
	if (floatsize < 9)	floats_cb->ItemIndex = floatsize;
	else	floats_cb->ItemIndex = floats_cb->Items->Count-1;

	/* create label for water warning */
	CreateLabel(GeneralDialog,20,222,0,0,l->Strings[24],NULL);
	/* create edit for water warning */
	TEdit *waterw_e = CreateEdit(GeneralDialog,150,221,85,0,
			FloatToStrF(waterwarning, ffFixed, 5, 1),0,waterw_e);
	watw_e = waterw_e;
	waterw_e->OnChange = waterw_eChange;
	/* create up down for water warning */
	TUpDown *waterw_ud = CreateUpDown(GeneralDialog,235,221,15,21,-1990,1990,
			waterwarning,NULL,waterw_ud);
	waterw_ud->OnClick = waterw_udClick;

	/* create label for high water limit */
	CreateLabel(GeneralDialog,20,245,0,0,l->Strings[25],NULL);
	/* create edit for high water limit */
	TEdit *hwaterl_e = CreateEdit(GeneralDialog,150,244,85,0,
			FloatToStrF(highwaterlimit, ffFixed, 5, 1),0,hwaterl_e);
	hwatl_e = hwaterl_e;
	hwaterl_e->OnChange = hwaterl_eChange;
	/* create up down for high water limit */
	TUpDown *hwaterl_ud = CreateUpDown(GeneralDialog,235,244,15,21,-1990,1990,
			highwaterlimit,NULL,hwaterl_ud);
	hwaterl_ud->OnClick = hwaterl_udClick;

	/* create label for max or label volume */
	CreateLabel(GeneralDialog,20,268,0,0,l->Strings[26],NULL);
	/* create edit for max or label volume */
	AnsiString molv;
	molv.sprintf("%d",maxorlabelvolume);
	TEdit *maxorlv_e = CreateEdit(GeneralDialog,150,266,85,0,molv,6,maxorlv_e);
	morlv_e = maxorlv_e;
	maxorlv_e->OnChange = maxorlv_eChange;
	/* create up down for max or label volume */
	TUpDown *maxorlv_ud = CreateUpDown(GeneralDialog,235,266,15,21,-32767,32767,
			maxorlabelvolume,NULL,maxorlv_ud);
	maxorlv_ud->OnClick = maxorlv_udClick;

	/* create label for overfill limit */
	CreateLabel(GeneralDialog,20,291,0,0,l->Strings[27],NULL);
	/* create edit for overfill limit */
	TEdit *overfl_e = CreateEdit(GeneralDialog,150,289,85,0,"",6,overfl_e);
	/* create up down for overfill limit */
	TUpDown *overfl_ud = CreateUpDown(GeneralDialog,235,289,15,21,0,100,
			overfilllimit,overfl_e,overfl_ud);

	/* create label for high product limit */
	CreateLabel(GeneralDialog,20,314,0,0,l->Strings[28],NULL);
	/* create edit for high product limit */
	TEdit *hproductl_e = CreateEdit(GeneralDialog,150,312,85,0,"",6,hproductl_e);
	/* create up down for high product limit */
	TUpDown *hproductl_ud = CreateUpDown(GeneralDialog,235,312,15,21,0,100,
			highproductlimit,hproductl_e,hproductl_ud);

	/* create label for delivery limit */
	CreateLabel(GeneralDialog,20,337,0,0,l->Strings[29],NULL);
	/* create edit for delivery limit */
	TEdit *deliveryl_e = CreateEdit(GeneralDialog,150,335,85,0,"",6,deliveryl_e);
	/* create up down for delivery limit */
	TUpDown *deliveryl_ud = CreateUpDown(GeneralDialog,235,335,15,21,0,100,
			deliverylimit,deliveryl_e,deliveryl_ud);

	/* create label for low product */
	CreateLabel(GeneralDialog,20,360,0,0,l->Strings[30],NULL);
	/* create edit for low product */
	AnsiString lp;
	lp.sprintf("%d",lowproductlimit);
	lproductl_e = CreateEdit(GeneralDialog,150,358,85,0,lp,6,lproductl_e);
	lproductl_e->OnChange = lproductl_eChange;
	/* create up down for low product */
	TUpDown *lproductl_ud = CreateUpDown(GeneralDialog,235,358,15,21,-32767,32767,
			lowproductlimit,NULL,lproductl_ud);
	lproductl_ud->OnClick = lproductl_udClick;

	/* create label for leak alarm limit */
	CreateLabel(GeneralDialog,20,383,0,0,l->Strings[31],NULL);
	/* create edit for leak alarm limit */
	TEdit *lalarml_e = CreateEdit(GeneralDialog,150,381,85,0,"",6,lalarml_e);
	/* create up down for leak alarm limit */
	TUpDown *lalarml_ud = CreateUpDown(GeneralDialog,235,381,15,21,1,399,
			leakalarmlimit,lalarml_e,lalarml_ud);

	/* create label for sudden loss limit */
	CreateLabel(GeneralDialog,20,406,0,0,l->Strings[32],NULL);
	/* create edit for sudden loss limit */ 
	AnsiString sll;
	sll.sprintf("%d",suddenlosslimit);
	suddenll_e = CreateEdit(GeneralDialog,150,404,85,0,sll,6,suddenll_e);
	suddenll_e->OnChange = suddenll_eChange;
	/* create up down for sudden loss limit */
	TUpDown *suddenll_ud = CreateUpDown(GeneralDialog,235,404,15,21,-32767,32767,
			suddenlosslimit,NULL,suddenll_ud);
	suddenll_ud->OnClick = suddenll_udClick;

	/* create label for tank tilt */
	CreateLabel(GeneralDialog,20,429,0,0,l->Strings[33],NULL);
	/* create edit for tank tilt */
	TEdit *tanktilt_e = CreateEdit(GeneralDialog,150,427,85,0,
			FloatToStrF(tanktilt, ffFixed, 5, 2),0,tanktilt_e);
	tankt_e = tanktilt_e;
	tanktilt_e->OnChange = tanktilt_eChange;
	/* create up down for tank tilt */
	TUpDown *tanktilt_ud = CreateUpDown(GeneralDialog,235,427,15,21,-32767,32767,
			tanktilt,NULL,tanktilt_ud);
	tanktilt_ud->OnClick = tanktilt_udClick;

	/* create label for probe offset */
	CreateLabel(GeneralDialog,20,452,0,0,l->Strings[34],NULL);
	/* create edit for probe offset */
	TEdit *probeoffset_e = CreateEdit(GeneralDialog,150,450,85,0,
			FloatToStrF(probeoffset, ffFixed, 5, 2),0,probeoffset_e);
	probeofs_e = probeoffset_e;
	probeoffset_e->OnChange = probeoffset_eChange;
	/* create up down for probe offset */
	TUpDown *probeoffset_ud = CreateUpDown(GeneralDialog,235,450,15,21,-32767,32767,
			probeoffset,NULL,probeoffset_ud);
	probeoffset_ud->OnClick = probeoffset_udClick;

	/* create label for manifolded tank status */
	CreateLabel(GeneralDialog,20,475,0,0,l->Strings[35],NULL);
	/* create edit for manifolded tank status  */
	TEdit *manifoldedtanks_e = CreateEdit(GeneralDialog,150,473,300,0,
			manifoldedtanks,0,manifoldedtanks_e);

	/* create label for leak minimum periodic */
	CreateLabel(GeneralDialog,295,20,0,0,l->Strings[36],NULL);
	/* create edit for leak minimum periodic */
	TEdit *leakminp_e = CreateEdit(GeneralDialog,425,18,85,0,"",0,leakminp_e);
	/* create up down for leak minimum periodic */
	TUpDown *leakminp_ud = CreateUpDown(GeneralDialog,510,18,15,21,0,100,
			leakminimumperiodic,leakminp_e,leakminp_ud);

	/* create label for leak minimum annual */
	CreateLabel(GeneralDialog,295,43,0,0,l->Strings[37],NULL);
	/* create edit for leak minimum annual */
	TEdit *leakmina_e = CreateEdit(GeneralDialog,425,41,85,0,"",0,leakmina_e);
	/* create up down for leak minimum annual */
	TUpDown *leakmina_ud = CreateUpDown(GeneralDialog,510,41,15,21,0,100,
			leakminimumannual,leakmina_e,leakmina_ud);

	/* create label for periodic test type */
	CreateLabel(GeneralDialog,295,66,0,0,l->Strings[38],NULL);
	/* create radio buttons for periodic test type */
	TRadioButton *perteststd_rb = CreateRadioButton(GeneralDialog,425,64,100,0,
			l->Strings[39],!periodictesttype,perteststd_rb);
	TRadioButton *pertestquick_rb = CreateRadioButton(GeneralDialog,425,82,100,0,
			l->Strings[40],periodictesttype,pertestquick_rb);

	/* create checkboxes for tank leak test fail alarms */
	TCheckBox *annualtstf_cb = CreateCheckBox(GeneralDialog,295,105,200,0,
			l->Strings[41],annualtestfail,1,annualtstf_cb);
	TCheckBox *pertstf_cb = CreateCheckBox(GeneralDialog,295,128,200,0,
			l->Strings[42],periodictestfail,1,pertstf_cb);
	TCheckBox *grosststf_cb = CreateCheckBox(GeneralDialog,295,151,200,0,
			l->Strings[43],grosstestfail,1,grosststf_cb);

	/* create checkboxes for tank leak test averaging */
	TCheckBox *annualtsta_cb = CreateCheckBox(GeneralDialog,295,174,200,0,
			l->Strings[44],annualtestaveraging,1,annualtsta_cb);
	TCheckBox *pertsta_cb = CreateCheckBox(GeneralDialog,295,197,200,0,
			l->Strings[45],periodictestaveraging,1,pertsta_cb);

	/* create checkboxes for tank leak test notify */
	TCheckBox *leaktstnotify_cb = CreateCheckBox(GeneralDialog,295,220,200,0,
			l->Strings[46],leaktestnotify,1,leaktstnotify_cb);

	/* create checkboxes for tank test siphon break */
	TCheckBox *siphonbreak_cb = CreateCheckBox(GeneralDialog,295,243,200,0,
			l->Strings[47],siphonbreak,1,siphonbreak_cb);

	/* create label for stick offset */
	CreateLabel(GeneralDialog,295,266,0,0,l->Strings[48],NULL);
	/* create edit for stick offset */
	TEdit *stickoffset_e = CreateEdit(GeneralDialog,425,264,85,0,
			FloatToStrF(stickoffset, ffFixed, 5, 2),0,stickoffset_e);
	stickofs_e = stickoffset_e;
	stickoffset_e->OnChange = stickoffset_eChange;
	/* create up down for stick offset */
	TUpDown *stickoffset_ud = CreateUpDown(GeneralDialog,510,264,15,21,-32767,32767,
			stickoffset,NULL,stickoffset_ud);
	stickoffset_ud->OnClick = stickoffset_udClick;

	/* create label for hrm reconciliation warning limit */
	CreateLabel(GeneralDialog,295,289,0,0,l->Strings[49],NULL);
	/* create edit for hrm reconciliation warning limit */
	TEdit *hrmrecwl_e = CreateEdit(GeneralDialog,425,287,85,0,"",6,hrmrecwl_e);
	/* create up down for hrm reconciliation warning limit */
	TUpDown *hrmrecwl_ud = CreateUpDown(GeneralDialog,510,287,15,21,1,400,
			hrmreconcwarnlimit,hrmrecwl_e,hrmrecwl_ud);

	/* create label for hrm reconciliation alarm limit */
	CreateLabel(GeneralDialog,295,312,0,0,l->Strings[50],NULL);
	/* create edit for hrm reconciliation alarm limit */
	TEdit *hrmrecal_e = CreateEdit(GeneralDialog,425,310,85,0,"",6,hrmrecal_e);
	/* create up down for hrm reconciliation alarm limit */
	TUpDown *hrmrecal_ud = CreateUpDown(GeneralDialog,510,310,15,21,1,400,
			hrmreconcalmlimit,hrmrecal_e,hrmrecal_ud);

	/* create label for delivery report delay time */
	CreateLabel(GeneralDialog,295,335,0,0,l->Strings[51],NULL);
	/* create edit for delivery report delay time */
	TEdit *delrepdt_e = CreateEdit(GeneralDialog,425,333,85,0,"",2,delrepdt_e);
	/* create up down for delivery report delay time */
	TUpDown *delrepdt_ud = CreateUpDown(GeneralDialog,510,333,15,21,1,99,
			deliveryreportdt,delrepdt_e,delrepdt_ud);

	/* create label for pump threshold */
	CreateLabel(GeneralDialog,295,358,0,0,l->Strings[52],NULL);
	/* create edit for pump threshold */
	TEdit *pumpth_e = CreateEdit(GeneralDialog,425,356,85,0,
			FloatToStrF(pumpthreshold, ffFixed, 5, 2),0,pumpth_e);
	pmpth_e = pumpth_e;
	pumpth_e->OnChange = pumpth_eChange;
	/* create up down for pump threshold */
	TUpDown *pumpth_ud = CreateUpDown(GeneralDialog,510,356,15,21,-500,500,
			pumpthreshold,NULL,pumpth_ud);
	pumpth_ud->OnClick = pumpth_udClick;


	if (GeneralDialog->ShowModal()==ID_OK)
	{
		productlabel = productl_e->Text;
		productcode = productc_e->Text;
		meterdatapresent = meterdp_cb->Checked;
		endfactor = endfact_cb->ItemIndex;
		calibrationupdate = calupd_cb->ItemIndex+1;
		if (floats_cb->ItemIndex!=floats_cb->Items->Count-1)
			floatsize = floats_cb->ItemIndex;
		else	floatsize = 9;
		overfilllimit = overfl_ud->Position;
		highproductlimit = hproductl_ud->Position;
		deliverylimit = deliveryl_ud->Position;
		leakalarmlimit = lalarml_ud->Position;
		manifoldedtanks = manifoldedtanks_e->Text;
		leakminimumperiodic = leakminp_ud->Position;
		leakminimumannual = leakmina_ud->Position;
		if (perteststd_rb->Checked)	periodictesttype = false;
		if (pertestquick_rb->Checked)	periodictesttype = true;
		annualtestfail = annualtstf_cb->Checked;
		periodictestfail = pertstf_cb->Checked;
		grosstestfail = grosststf_cb->Checked;
		annualtestaveraging = annualtsta_cb->Checked;
		periodictestaveraging = pertsta_cb->Checked;
		leaktestnotify = leaktstnotify_cb->Checked;
		siphonbreak = siphonbreak_cb->Checked;
		hrmreconcwarnlimit = hrmrecwl_ud->Position;
		hrmreconcalmlimit = hrmrecal_ud->Position;
		deliveryreportdt = delrepdt_ud->Position;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTankProfile(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_TANKPROFILE,CNT_TANKPROFILE,0,9,10,GeneralDialog);

	GeneralDialog->Height = 540;
	GeneralDialog->Width = 655;
	GeneralDialog->Bevel1->Height = 498;
	GeneralDialog->Bevel1->Width = 552;
	GeneralDialog->OKBtn->Left = 567;
	GeneralDialog->CancelBtn->Left = 567;

	AnsiString cap = GeneralDialog->Caption;
	cap += " on tank "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create group box for tank profile */
	TGroupBox *tankprofile_gb = CreateGroupBox(GeneralDialog,30,30,300,120,
			l->Strings[1],tankprofile_gb);

	/* create radio buttons for tank profile */
	TRadioButton *linear_rb = CreateRadioButton(tankprofile_gb,20,20,
		250,0,l->Strings[2],false,linear_rb);
	TRadioButton *pts1_rb = CreateRadioButton(tankprofile_gb,20,43,
		250,0,l->Strings[3],false,pts1_rb);
	TRadioButton *pts4_rb = CreateRadioButton(tankprofile_gb,20,66,
		250,0,l->Strings[4],false,pts4_rb);
	TRadioButton *pts20_rb = CreateRadioButton(tankprofile_gb,20,89,
		250,0,l->Strings[5],false,pts20_rb);

	/* select the tank profile type ( linear and 1 point is not obvious; the
	   rs232 interface have'nt a command to get the profile type:( ) */
	/* if the 20th volume is not null, the type is 20 points */
	if (CompareStr(tankprofile[0],"0")!=0)	pts20_rb->Checked = true;
	/* if the 3th volume is not null, the type is 4 points */
	else if (CompareStr(tankprofile[9],"0")!=0)	pts4_rb->Checked = true;
	/* if the 0th volume is not null, the type is 1 point (or linear???) */
	else if (CompareStr(tankprofile[19],"0")!=0)	pts1_rb->Checked = true;
	/* if the 0th volume is null, the type is linear (or 1 point???) */
	else	linear_rb->Checked = true;

	/* create label for tank volumes */
	CreateLabel(GeneralDialog,30,163,0,0,l->Strings[6],NULL);
	TLabel *tankvolsh_l = CreateLabel(GeneralDialog,30,181,0,0,l->Strings[7],tankvolsh_l);
	tankvolsh_l->Font->Size = 7;

	/* create multiline edit for tank volumes */
	TMemo *tankvols_m = CreateMemo(GeneralDialog,30,201,200,
		280,"",tankvols_m);
	tankvols_m->Clear();
	for (int i=0; i < 20; i++)
		tankvols_m->Lines->Add(tankprofile[i]);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		int linecount = tankvols_m->Lines->Count;

		if ( (linear_rb->Checked && (linecount > 1 || linecount < 1) ) ||
			 (pts1_rb->Checked && (linecount > 1 || linecount < 1) )   ||
			 (pts4_rb->Checked && (linecount > 4 || linecount < 4 ) ) ||
			 (pts20_rb->Checked && (linecount > 20 || linecount < 20) ) )
		{
			if (Application->MessageBox(l->Strings[8].c_str(),
					GeneralDialog->Caption.c_str(),17)==IDCANCEL)
				cancel_from_dialog = true;
			else	cancel_from_dialog = false;
		}

		if (!cancel_from_dialog)
		{
			for (int i=0; (i < linecount) && (i < 20); i++)
				tankprofile[i] = tankvols_m->Lines->Strings[i];

			if (linear_rb->Checked)  tankprofiletype = 0;
			if (pts1_rb->Checked)  tankprofiletype = 1;
			if (pts4_rb->Checked)  tankprofiletype = 2;
			if (pts20_rb->Checked)  tankprofiletype = 3;
		}
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowDIMString(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_DISPENSERMODULE,CNT_DISPENSERMODULE,0,4,5,GeneralDialog);

	AnsiString cap = GeneralDialog->Caption;
	cap += " - "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for dim software version text */
	CreateLabel(GeneralDialog,20,20,0,0,l->Strings[1],NULL);
	/* create label for dim software version string */
	TLabel *dimver_l = CreateLabel(GeneralDialog,25,35,0,0,"VR: ???\tTD: ???",dimver_l);
	if (dimversion!="")	dimver_l->Caption = dimversion;

	/* create label for mdim data string */
	CreateLabel(GeneralDialog,20,71,0,0,l->Strings[2],NULL);
	/* create edit for mdim data string */
	TEdit *mdimstr_e = CreateEdit(GeneralDialog,150,69,110,0,mdim_string,12,mdimstr_e);

	/* create label for edim data string */
	CreateLabel(GeneralDialog,20,94,0,0,l->Strings[3],NULL);
	/* create edit for edim data string */
	TEdit *edimstr_e = CreateEdit(GeneralDialog,150,92,110,0,edim_string,12,edimstr_e);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		mdim_string = mdimstr_e->Text;
		edim_string = edimstr_e->Text;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowAutodailyClosing(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_AUTODAILYCLOSING,CNT_AUTODAILYCLOSING,0,2,3,GeneralDialog);

	/* create label for automatic daily closing */
	CreateLabel(GeneralDialog,30,20,0,0,l->Strings[1],NULL);

	/* create date time picker for auto daily closing time */
	TDateTimePicker *autodcl_dtp = CreateDateTimePicker(GeneralDialog,35,
		43,150,0,"HH:mm",autodailyclosing,dtkTime,autodcl_dtp);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		autodailyclosing = autodcl_dtp->Time; 
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowAutoShiftClosingTimes(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETAUTOSHIFTCLOSINGTIME,CNT_SETAUTOSHIFTCLOSINGTIME,0,5,6,GeneralDialog);

	/* create check box for closing time #1 */
	TCheckBox* shiftclosing1_cb =
		CreateCheckBox(GeneralDialog,30,29,120,17,l->Strings[1],shiftclosing1,1,shiftclosing1_cb);

	/* create date time picker for time #1 */
	TDateTimePicker* shifttime1_dtp =
		CreateDateTimePicker(GeneralDialog,150,27,100,23,"HH:mm",shifttime1,dtkTime,shifttime1_dtp);
	st1 = shifttime1_dtp;
	shiftclosing1_cb->OnClick = ShiftStartTimeOnClick;

	/* create check box for closing time #2 */
	TCheckBox* shiftclosing2_cb =
		CreateCheckBox(GeneralDialog,30,56,120,17,l->Strings[2],shiftclosing2,2,shiftclosing2_cb);

	/* create date time picker for time #2 */
	TDateTimePicker* shifttime2_dtp =
		CreateDateTimePicker(GeneralDialog,150,54,100,23,"HH:mm",shifttime2,dtkTime,shifttime2_dtp);
	st2 = shifttime2_dtp;
	shiftclosing2_cb->OnClick = ShiftStartTimeOnClick;

	/* create check box for closing time #3 */
	TCheckBox* shiftclosing3_cb =
		CreateCheckBox(GeneralDialog,30,81,120,17,l->Strings[3],shiftclosing3,3,shiftclosing3_cb);

	/* create date time picker for time #3 */
	TDateTimePicker* shifttime3_dtp =
		CreateDateTimePicker(GeneralDialog,150,79,100,23,"HH:mm",shifttime3,dtkTime,shifttime3_dtp);
	st3 = shifttime3_dtp;
	shiftclosing3_cb->OnClick = ShiftStartTimeOnClick;

	/* create check box for closing time #4 */
	TCheckBox* shiftclosing4_cb =
		CreateCheckBox(GeneralDialog,30,110,120,17,l->Strings[4],shiftclosing4,4,shiftclosing4_cb);

	/* create date time picker for time #4 */
	TDateTimePicker* shifttime4_dtp =
		CreateDateTimePicker(GeneralDialog,150,108,100,23,"HH:mm",shifttime4,dtkTime,shifttime4_dtp);
	st4 = shifttime4_dtp;
	shiftclosing4_cb->OnClick = ShiftStartTimeOnClick;

	ShiftStartTimeOnClick(shiftclosing1_cb);
	ShiftStartTimeOnClick(shiftclosing2_cb);
	ShiftStartTimeOnClick(shiftclosing3_cb);
	ShiftStartTimeOnClick(shiftclosing4_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		shiftclosing1 = shiftclosing1_cb->Checked;
		shiftclosing2 = shiftclosing2_cb->Checked;
		shiftclosing3 = shiftclosing3_cb->Checked;
		shiftclosing4 = shiftclosing4_cb->Checked;
		shifttime1 = shifttime1_dtp->Time;
		shifttime2 = shifttime2_dtp->Time;
		shifttime3 = shifttime3_dtp->Time;
		shifttime4 = shifttime4_dtp->Time;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPeriodicreconciliationMode(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETPERIODICRECONCMODE,CNT_SETPERIODICRECONCMODE,0,4,5,GeneralDialog);

	/* create radio buttons for periodic reconciliation mode */
	TRadioButton *monthly_rb = CreateRadioButton(GeneralDialog,20,20,80,17,
		l->Strings[1],false,monthly_rb);
	if (periodicreconcmode==1)	monthly_rb->Checked = true;
	else	monthly_rb->Checked = false;

	TRadioButton *rolling_rb = CreateRadioButton(GeneralDialog,110,20,80,17,
		l->Strings[2],false,rolling_rb);
	if (periodicreconcmode==2)	rolling_rb->Checked = true;
	else	rolling_rb->Checked = false;

	/* create label for periodic reconciliation length */
	CreateLabel(GeneralDialog,110,43,0,0,l->Strings[3],NULL);
	/* create edit and up down for periodic reconciliation length */
	TEdit *reconclen_e = CreateEdit(GeneralDialog,200,41,50,0,"",2,reconclen_e);
	TUpDown *reconclen_ud = CreateUpDown(GeneralDialog,0,0,0,0,1,31,
		periodicreconclen,reconclen_e,reconclen_ud);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (monthly_rb->Checked) periodicreconcmode = 1;
		else if (rolling_rb->Checked) periodicreconcmode = 2;
		else periodicreconcmode = 1;

		periodicreconclen = reconclen_ud->Position;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowPeriodicReconciliationAlarm(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETPERIODICRECONCALARM,CNT_SETPERIODICRECONCALARM,0,4,5,GeneralDialog);

	/* create check box for periodic reconciliation alarm */
	TCheckBox *ispralm_cb = CreateCheckBox(GeneralDialog,20,20,
		250,0,l->Strings[1],false,1,ispralm_cb);
	if (perreconcalmonoff==1)  ispralm_cb->Checked = false;
	else if (perreconcalmonoff==2)  ispralm_cb->Checked = true;
	else ispralm_cb->Checked = false;

	/* create label for periodic reconciliation alarm threshold */
	CreateLabel(GeneralDialog,40,43,0,0,l->Strings[2],NULL);
	/* create edit for periodic reconciliation alarm threshold */
	prath_e = CreateEdit(GeneralDialog,165,41,80,
		0,FloatToStrF(perreconcalmthreshold,ffFixed,5,2),4,prath_e);
	prath_e->OnChange = prath_eChange;
	/* create up down for periodic reconciliation alarm threshold */
	TUpDown *prath_ud = CreateUpDown(GeneralDialog,245,41,15,21,-32767,32767,
			perreconcalmthreshold,NULL,prath_ud);
	prath_ud->OnClick = prath_udClick;

	/* create label for periodic reconciliation alarm offset */
	CreateLabel(GeneralDialog,40,66,0,0,l->Strings[3],NULL);
	/* create edit for periodic reconciliation alarm offset */
	TEdit *praof_e = CreateEdit(GeneralDialog,165,64,80,0,"",6,praof_e);
	/* create up down for periodic reconciliation alarm offset */
	TUpDown *praof_ud = CreateUpDown(GeneralDialog,0,0,0,0,-32767,32767,
			perreconcalmoffset,praof_e,praof_ud);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (ispralm_cb->Checked)	perreconcalmonoff = 2;
		else	perreconcalmonoff = 1;

		perreconcalmoffset = praof_ud->Position;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowRemoteReportFormat(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETREMOTEREPORTFORMAT,CNT_SETREMOTEREPORTFORMAT,0,3,4,GeneralDialog);

	/* create radio buttons for remote report format */
	TRadioButton *rowfrmt_rb = CreateRadioButton(GeneralDialog,20,20,250,17,
		l->Strings[1],false,rowfrmt_rb);
	if (remotereportformat==1)	rowfrmt_rb->Checked = true;
	else	rowfrmt_rb->Checked = false;

	TRadioButton *columnfrmt_rb = CreateRadioButton(GeneralDialog,20,43,250,17,
		l->Strings[2],false,columnfrmt_rb);
	if (remotereportformat==2)	columnfrmt_rb->Checked = true;
	else	columnfrmt_rb->Checked = false;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (rowfrmt_rb->Checked) remotereportformat = 1;
		else if (columnfrmt_rb->Checked) remotereportformat = 2;
		else remotereportformat = 1;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowTempCompensation(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETTEMPCOMPESATION,CNT_SETTEMPCOMPESATION,0,3,4,GeneralDialog);

	/* create radio buttons for temp compensation */
	TRadioButton *tmpcompstd_rb = CreateRadioButton(GeneralDialog,20,20,250,17,
		l->Strings[1],!tempcompensation,tmpcompstd_rb);

	TRadioButton *tmpcomptcv_rb = CreateRadioButton(GeneralDialog,20,43,250,17,
		l->Strings[2],tempcompensation,tmpcomptcv_rb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		tempcompensation = !tmpcompstd_rb->Checked;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowMeterCalibrationOffset(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_METERCALIBOFFSET,CNT_METERCALIBOFFSET,0,2,3,GeneralDialog);

	/* create label for meter calibration offset */
	CreateLabel(GeneralDialog,30,30,0,0,l->Strings[1],NULL);
	/* create edit for meter calibration offset */
	mcalibofs_e = CreateEdit(GeneralDialog,165,41,80,
		0,FloatToStrF(metercaliboffset,ffFixed,5,3),5,mcalibofs_e);
	mcalibofs_e->OnChange = mcalibofs_eChange;
	/* create up down for meter calibration offset */
	TUpDown *mcalibofs_ud = CreateUpDown(GeneralDialog,245,41,15,21,-32767,32767,
			metercaliboffset,NULL,mcalibofs_ud);
	mcalibofs_ud->OnClick = mcalibofs_udClick;

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowModifyTankMeterMap(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_MODIFYTANKMETERMAP,CNT_MODIFYTANKMETERMAP,0,7,8,GeneralDialog);

	/* create radio buttons for bus type */
	TRadioButton *pwrbus_rb = CreateRadioButton(GeneralDialog,20,20,150,17,
		l->Strings[1],false,pwrbus_rb);
	TRadioButton *commbus_rb = CreateRadioButton(GeneralDialog,170,20,100,17,
		l->Strings[2],false,commbus_rb);

	/* create label for slot number */
	CreateLabel(GeneralDialog,20,43,0,0,l->Strings[3],NULL);
	/* create edit for slot number */
	TEdit *sltonr_e = CreateEdit(GeneralDialog,150,41,80,0,"",-1,sltonr_e);
	/* create up down for slot number */
	TUpDown *slotnr_ud = CreateUpDown(GeneralDialog,0,0,0,0,1,16,0,sltonr_e,slotnr_ud);

	/* create label for fuel position */
	CreateLabel(GeneralDialog,20,66,0,0,l->Strings[4],NULL);
	/* create edit for fuel position */
	TEdit *fuelp_e = CreateEdit(GeneralDialog,150,64,80,0,"",-1,fuelp_e);
	/* create up down for fuel position */
	TUpDown *fuelp_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,99,0,fuelp_e,fuelp_ud);

	/* create label for meter */
	CreateLabel(GeneralDialog,20,89,0,0,l->Strings[5],NULL);
	/* create edit for meter */
	TEdit *meter_e = CreateEdit(GeneralDialog,150,87,80,0,"",-1,meter_e);
	/* create up down for meter */
	TUpDown *meter_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,99,0,meter_e,meter_ud);

	/* create label for tank number */
	CreateLabel(GeneralDialog,20,112,0,0,l->Strings[6],NULL);
	/* create edit for tank number */
	TEdit *tanknr_e = CreateEdit(GeneralDialog,150,110,80,0,"",-1,tanknr_e);
	/* create up down for tank number */
	TUpDown *tanknr_ud = CreateUpDown(GeneralDialog,0,0,0,0,-1,99,0,tanknr_e,tanknr_ud);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (pwrbus_rb->Checked)	bustype = 2;
		else bustype = 3;

		slotnr = slotnr_ud->Position;
		fuelpos = fuelp_ud->Position;
		meter = meter_ud->Position;
    	tanknr = tanknr_ud->Position;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowLiquidSensorConfiguration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETLIQUIDSENSCONFIGURATION,
			CNT_SETLIQUIDSENSCONFIGURATION,0,33,34,GeneralDialog);

	GeneralDialog->Height = 390;
	GeneralDialog->Bevel1->Height = 348;

	/* create check boxes for tank configuration */
	TCheckBox* slot1pos1_cb =
		CreateCheckBox(GeneralDialog,33,23,120,0,l->Strings[1],liquidsensconfig[0],1,slot1pos1_cb);
	TCheckBox* slot1pos2_cb =
		CreateCheckBox(GeneralDialog,33,41,120,0,l->Strings[2],liquidsensconfig[1],2,slot1pos2_cb);
	TCheckBox* slot1pos3_cb =
		CreateCheckBox(GeneralDialog,33,59,120,0,l->Strings[3],liquidsensconfig[2],3,slot1pos3_cb);
	TCheckBox* slot1pos4_cb =
		CreateCheckBox(GeneralDialog,33,77,120,0,l->Strings[4],liquidsensconfig[3],4,slot1pos4_cb);
	TCheckBox* slot1pos5_cb =
		CreateCheckBox(GeneralDialog,155,23,120,0,l->Strings[5],liquidsensconfig[4],5,slot1pos5_cb);
	TCheckBox* slot1pos6_cb =
		CreateCheckBox(GeneralDialog,155,41,120,0,l->Strings[6],liquidsensconfig[5],6,slot1pos6_cb);
	TCheckBox* slot1pos7_cb =
		CreateCheckBox(GeneralDialog,155,59,120,0,l->Strings[7],liquidsensconfig[6],7,slot1pos7_cb);
	TCheckBox* slot1pos8_cb =
		CreateCheckBox(GeneralDialog,155,77,120,0,l->Strings[8],liquidsensconfig[7],8,slot1pos8_cb);

	TCheckBox* slot2pos1_cb =
		CreateCheckBox(GeneralDialog,33,100,120,0,l->Strings[9],liquidsensconfig[8],9,slot2pos1_cb);
	TCheckBox* slot2pos2_cb =
		CreateCheckBox(GeneralDialog,33,118,120,0,l->Strings[10],liquidsensconfig[9],10,slot2pos2_cb);
	TCheckBox* slot2pos3_cb =
		CreateCheckBox(GeneralDialog,33,136,120,0,l->Strings[11],liquidsensconfig[10],11,slot2pos3_cb);
	TCheckBox* slot2pos4_cb =
		CreateCheckBox(GeneralDialog,33,154,120,0,l->Strings[12],liquidsensconfig[11],12,slot2pos4_cb);
	TCheckBox* slot2pos5_cb =
		CreateCheckBox(GeneralDialog,155,100,120,0,l->Strings[13],liquidsensconfig[12],13,slot2pos5_cb);
	TCheckBox* slot2pos6_cb =
		CreateCheckBox(GeneralDialog,155,118,120,0,l->Strings[14],liquidsensconfig[13],14,slot2pos6_cb);
	TCheckBox* slot2pos7_cb =
		CreateCheckBox(GeneralDialog,155,136,120,0,l->Strings[15],liquidsensconfig[14],15,slot2pos7_cb);
	TCheckBox* slot2pos8_cb =
		CreateCheckBox(GeneralDialog,155,154,120,0,l->Strings[16],liquidsensconfig[15],16,slot2pos8_cb);

	TCheckBox* slot3pos1_cb =
		CreateCheckBox(GeneralDialog,33,177,120,0,l->Strings[17],liquidsensconfig[16],17,slot3pos1_cb);
	TCheckBox* slot3pos2_cb =
		CreateCheckBox(GeneralDialog,33,195,120,0,l->Strings[18],liquidsensconfig[17],18,slot3pos2_cb);
	TCheckBox* slot3pos3_cb =
		CreateCheckBox(GeneralDialog,33,213,120,0,l->Strings[19],liquidsensconfig[18],19,slot3pos3_cb);
	TCheckBox* slot3pos4_cb =
		CreateCheckBox(GeneralDialog,33,231,120,0,l->Strings[20],liquidsensconfig[19],20,slot3pos4_cb);
	TCheckBox* slot3pos5_cb =
		CreateCheckBox(GeneralDialog,155,177,120,0,l->Strings[21],liquidsensconfig[20],21,slot3pos5_cb);
	TCheckBox* slot3pos6_cb =
		CreateCheckBox(GeneralDialog,155,195,120,0,l->Strings[22],liquidsensconfig[21],22,slot3pos6_cb);
	TCheckBox* slot3pos7_cb =
		CreateCheckBox(GeneralDialog,155,213,120,0,l->Strings[23],liquidsensconfig[22],23,slot3pos7_cb);
	TCheckBox* slot3pos8_cb =
		CreateCheckBox(GeneralDialog,155,231,120,0,l->Strings[24],liquidsensconfig[23],24,slot3pos8_cb);

	TCheckBox* slot4pos1_cb =
		CreateCheckBox(GeneralDialog,33,254,120,0,l->Strings[25],liquidsensconfig[24],25,slot4pos1_cb);
	TCheckBox* slot4pos2_cb =
		CreateCheckBox(GeneralDialog,33,272,120,0,l->Strings[26],liquidsensconfig[25],26,slot4pos2_cb);
	TCheckBox* slot4pos3_cb =
		CreateCheckBox(GeneralDialog,33,290,120,0,l->Strings[27],liquidsensconfig[26],27,slot4pos3_cb);
	TCheckBox* slot4pos4_cb =
		CreateCheckBox(GeneralDialog,33,308,120,0,l->Strings[28],liquidsensconfig[27],28,slot4pos4_cb);
	TCheckBox* slot4pos5_cb =
		CreateCheckBox(GeneralDialog,155,254,120,0,l->Strings[29],liquidsensconfig[28],29,slot4pos5_cb);
	TCheckBox* slot4pos6_cb =
		CreateCheckBox(GeneralDialog,155,272,120,0,l->Strings[30],liquidsensconfig[29],30,slot4pos6_cb);
	TCheckBox* slot4pos7_cb =
		CreateCheckBox(GeneralDialog,155,290,120,0,l->Strings[31],liquidsensconfig[30],31,slot4pos7_cb);
	TCheckBox* slot4pos8_cb =
		CreateCheckBox(GeneralDialog,155,308,120,0,l->Strings[32],liquidsensconfig[31],32,slot4pos8_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (slot1pos1_cb->Checked) liquidsensconfig[0] = true;
		else liquidsensconfig[0] = false;
		if (slot1pos2_cb->Checked) liquidsensconfig[1] = true;
		else liquidsensconfig[1] = false;
		if (slot1pos3_cb->Checked) liquidsensconfig[2] = true;
		else liquidsensconfig[2] = false;
		if (slot1pos4_cb->Checked) liquidsensconfig[3] = true;
		else liquidsensconfig[3] = false;
		if (slot1pos5_cb->Checked) liquidsensconfig[4] = true;
		else liquidsensconfig[4] = false;
		if (slot1pos6_cb->Checked) liquidsensconfig[5] = true;
		else liquidsensconfig[5] = false;
		if (slot1pos7_cb->Checked) liquidsensconfig[6] = true;
		else liquidsensconfig[6] = false;
		if (slot1pos8_cb->Checked) liquidsensconfig[7] = true;
		else liquidsensconfig[7] = false;

		if (slot2pos1_cb->Checked) liquidsensconfig[8] = true;
		else liquidsensconfig[8] = false;
		if (slot2pos2_cb->Checked) liquidsensconfig[9] = true;
		else liquidsensconfig[9] = false;
		if (slot2pos3_cb->Checked) liquidsensconfig[10] = true;
		else liquidsensconfig[10] = false;
		if (slot2pos4_cb->Checked) liquidsensconfig[11] = true;
		else liquidsensconfig[11] = false;
		if (slot2pos5_cb->Checked) liquidsensconfig[12] = true;
		else liquidsensconfig[12] = false;
		if (slot2pos6_cb->Checked) liquidsensconfig[13] = true;
		else liquidsensconfig[13] = false;
		if (slot2pos7_cb->Checked) liquidsensconfig[14] = true;
		else liquidsensconfig[14] = false;
		if (slot2pos8_cb->Checked) liquidsensconfig[15] = true;
		else liquidsensconfig[15] = false;

		if (slot3pos1_cb->Checked) liquidsensconfig[16] = true;
		else liquidsensconfig[16] = false;
		if (slot3pos2_cb->Checked) liquidsensconfig[17] = true;
		else liquidsensconfig[17] = false;
		if (slot3pos3_cb->Checked) liquidsensconfig[18] = true;
		else liquidsensconfig[18] = false;
		if (slot3pos4_cb->Checked) liquidsensconfig[19] = true;
		else liquidsensconfig[19] = false;
		if (slot3pos5_cb->Checked) liquidsensconfig[20] = true;
		else liquidsensconfig[20] = false;
		if (slot3pos6_cb->Checked) liquidsensconfig[21] = true;
		else liquidsensconfig[21] = false;
		if (slot3pos7_cb->Checked) liquidsensconfig[22] = true;
		else liquidsensconfig[22] = false;
		if (slot3pos8_cb->Checked) liquidsensconfig[23] = true;
		else liquidsensconfig[23] = false;

		if (slot4pos1_cb->Checked) liquidsensconfig[24] = true;
		else liquidsensconfig[24] = false;
		if (slot4pos2_cb->Checked) liquidsensconfig[25] = true;
		else liquidsensconfig[25] = false;
		if (slot4pos3_cb->Checked) liquidsensconfig[26] = true;
		else liquidsensconfig[26] = false;
		if (slot4pos4_cb->Checked) liquidsensconfig[27] = true;
		else liquidsensconfig[27] = false;
		if (slot4pos5_cb->Checked) liquidsensconfig[28] = true;
		else liquidsensconfig[28] = false;
		if (slot4pos6_cb->Checked) liquidsensconfig[29] = true;
		else liquidsensconfig[29] = false;
		if (slot4pos7_cb->Checked) liquidsensconfig[30] = true;
		else liquidsensconfig[30] = false;
		if (slot4pos8_cb->Checked) liquidsensconfig[31] = true;
		else liquidsensconfig[31] = false;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowLiquidSensorSetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETLIQUIDSENSOR,CNT_SETLIQUIDSENSOR,0,16,17,GeneralDialog);

	AnsiString cap = GeneralDialog->Caption;
	cap += " - "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for sensor location */
	CreateLabel(GeneralDialog,20,30,0,0,l->Strings[1],NULL);
	/* create edit for sensor location */
	TEdit *sensloc_e = CreateEdit(GeneralDialog,110,28,165,0,liqsenslocation,20,sensloc_e);

	/* create label for sensor type */
	CreateLabel(GeneralDialog,20,53,0,0,l->Strings[2],NULL);
	/* create combo box for sensor type */
	TComboBox *senstype_cb = CreateComboBox(GeneralDialog,110,51,165,0,"",-1,senstype_cb);
	for (int i=3; i < 9; i++)	senstype_cb->Items->Add(l->Strings[i]);

	/* create label for sensor category */
	CreateLabel(GeneralDialog,20,76,0,0,l->Strings[9],NULL);
	/* create combo box for sensor category */
	TComboBox *senscategory_cb = CreateComboBox(GeneralDialog,110,74,165,0,"",-1,senscategory_cb);
	for (int i=10; i < 16; i++)	senscategory_cb->Items->Add(l->Strings[i]);

	switch (liqsenstype)
	{
		case 1: senstype_cb->ItemIndex = 0;
			break;
		case 2: senstype_cb->ItemIndex = 1;
			break;
		case 3: senstype_cb->ItemIndex = 2;
			break;
		case 4: senstype_cb->ItemIndex = 3;
			break;
		case 5: senstype_cb->ItemIndex = 4;
			break;
		case 6: senstype_cb->ItemIndex = 5;
			break;
	}

	switch (liqsenscategory)
	{
		case 1: senscategory_cb->ItemIndex = 0;
			break;
		case 2: senscategory_cb->ItemIndex = 1;
			break;
		case 3: senscategory_cb->ItemIndex = 2;
			break;
		case 4: senscategory_cb->ItemIndex = 3;
			break;
		case 5: senscategory_cb->ItemIndex = 4;
			break;
		case 6: senscategory_cb->ItemIndex = 5;
			break;
	}

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		liqsenslocation = sensloc_e->Text;
		liqsenstype = senstype_cb->ItemIndex+1;
		liqsenscategory = senscategory_cb->ItemIndex+1;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowVaporSensorConfiguration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETVAPORSENSCONFIGURATION,
			CNT_SETVAPORSENSCONFIGURATION,0,21,22,GeneralDialog);

	GeneralDialog->Height = 458;
	GeneralDialog->Bevel1->Height = 416;

	/* create check boxes for vapor sensor configuration */
	TCheckBox* slot1pos1_cb =
		CreateCheckBox(GeneralDialog,33,23,120,0,l->Strings[1],vaporsensconfig[0],1,slot1pos1_cb);
	TCheckBox* slot1pos2_cb =
		CreateCheckBox(GeneralDialog,33,41,120,0,l->Strings[2],vaporsensconfig[1],2,slot1pos2_cb);
	TCheckBox* slot1pos3_cb =
		CreateCheckBox(GeneralDialog,33,59,120,0,l->Strings[3],vaporsensconfig[2],3,slot1pos3_cb);
	TCheckBox* slot1pos4_cb =
		CreateCheckBox(GeneralDialog,33,77,120,0,l->Strings[4],vaporsensconfig[3],4,slot1pos4_cb);
	TCheckBox* slot1pos5_cb =
		CreateCheckBox(GeneralDialog,33,95,120,0,l->Strings[5],vaporsensconfig[4],5,slot1pos5_cb);

	TCheckBox* slot2pos1_cb =
		CreateCheckBox(GeneralDialog,33,125,120,0,l->Strings[6],vaporsensconfig[5],6,slot2pos1_cb);
	TCheckBox* slot2pos2_cb =
		CreateCheckBox(GeneralDialog,33,143,120,0,l->Strings[7],vaporsensconfig[6],7,slot2pos2_cb);
	TCheckBox* slot2pos3_cb =
		CreateCheckBox(GeneralDialog,33,161,120,0,l->Strings[8],vaporsensconfig[7],8,slot2pos3_cb);
	TCheckBox* slot2pos4_cb =
		CreateCheckBox(GeneralDialog,33,179,120,0,l->Strings[9],vaporsensconfig[8],9,slot2pos4_cb);
	TCheckBox* slot2pos5_cb =
		CreateCheckBox(GeneralDialog,33,197,120,0,l->Strings[10],vaporsensconfig[9],10,slot2pos5_cb);

	TCheckBox* slot3pos1_cb =
		CreateCheckBox(GeneralDialog,33,227,120,0,l->Strings[11],vaporsensconfig[10],11,slot3pos1_cb);
	TCheckBox* slot3pos2_cb =
		CreateCheckBox(GeneralDialog,33,245,120,0,l->Strings[12],vaporsensconfig[11],12,slot3pos2_cb);
	TCheckBox* slot3pos3_cb =
		CreateCheckBox(GeneralDialog,33,263,120,0,l->Strings[13],vaporsensconfig[12],13,slot3pos3_cb);
	TCheckBox* slot3pos4_cb =
		CreateCheckBox(GeneralDialog,33,281,120,0,l->Strings[14],vaporsensconfig[13],14,slot3pos4_cb);
	TCheckBox* slot3pos5_cb =
		CreateCheckBox(GeneralDialog,33,299,120,0,l->Strings[15],vaporsensconfig[14],15,slot3pos5_cb);

	TCheckBox* slot4pos1_cb =
		CreateCheckBox(GeneralDialog,33,329,120,0,l->Strings[16],vaporsensconfig[15],16,slot4pos1_cb);
	TCheckBox* slot4pos2_cb =
		CreateCheckBox(GeneralDialog,33,347,120,0,l->Strings[17],vaporsensconfig[16],17,slot4pos2_cb);
	TCheckBox* slot4pos3_cb =
		CreateCheckBox(GeneralDialog,33,365,120,0,l->Strings[18],vaporsensconfig[17],18,slot4pos3_cb);
	TCheckBox* slot4pos4_cb =
		CreateCheckBox(GeneralDialog,33,383,120,0,l->Strings[19],vaporsensconfig[18],19,slot4pos4_cb);
	TCheckBox* slot4pos5_cb =
		CreateCheckBox(GeneralDialog,33,401,120,0,l->Strings[20],vaporsensconfig[19],20,slot4pos5_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (slot1pos1_cb->Checked) vaporsensconfig[0] = true;
		else vaporsensconfig[0] = false;
		if (slot1pos2_cb->Checked) vaporsensconfig[1] = true;
		else vaporsensconfig[1] = false;
		if (slot1pos3_cb->Checked) vaporsensconfig[2] = true;
		else vaporsensconfig[2] = false;
		if (slot1pos4_cb->Checked) vaporsensconfig[3] = true;
		else vaporsensconfig[3] = false;
		if (slot1pos5_cb->Checked) vaporsensconfig[4] = true;
		else vaporsensconfig[4] = false;

		if (slot2pos1_cb->Checked) vaporsensconfig[5] = true;
		else vaporsensconfig[5] = false;
		if (slot2pos2_cb->Checked) vaporsensconfig[6] = true;
		else vaporsensconfig[6] = false;
		if (slot2pos3_cb->Checked) vaporsensconfig[7] = true;
		else vaporsensconfig[7] = false;
		if (slot2pos4_cb->Checked) vaporsensconfig[8] = true;
		else vaporsensconfig[8] = false;
		if (slot2pos5_cb->Checked) vaporsensconfig[9] = true;
		else vaporsensconfig[9] = false;

		if (slot3pos1_cb->Checked) vaporsensconfig[10] = true;
		else vaporsensconfig[10] = false;
		if (slot3pos2_cb->Checked) vaporsensconfig[11] = true;
		else vaporsensconfig[11] = false;
		if (slot3pos3_cb->Checked) vaporsensconfig[12] = true;
		else vaporsensconfig[12] = false;
		if (slot3pos4_cb->Checked) vaporsensconfig[13] = true;
		else vaporsensconfig[13] = false;
		if (slot3pos5_cb->Checked) vaporsensconfig[14] = true;
		else vaporsensconfig[14] = false;

		if (slot4pos1_cb->Checked) vaporsensconfig[15] = true;
		else vaporsensconfig[15] = false;
		if (slot4pos2_cb->Checked) vaporsensconfig[16] = true;
		else vaporsensconfig[16] = false;
		if (slot4pos3_cb->Checked) vaporsensconfig[17] = true;
		else vaporsensconfig[17] = false;
		if (slot4pos4_cb->Checked) vaporsensconfig[18] = true;
		else vaporsensconfig[18] = false;
		if (slot4pos5_cb->Checked) vaporsensconfig[19] = true;
		else vaporsensconfig[19] = false;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowVaporSensorSetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETVAPORSENSOR,CNT_SETVAPORSENSOR,0,10,11,GeneralDialog);

	AnsiString cap = GeneralDialog->Caption;
	cap += " - "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for vapor sensor location */
	CreateLabel(GeneralDialog,20,30,0,0,l->Strings[1],NULL);
	/* create edit for vapor sensor location */
	TEdit *sensloc_e = CreateEdit(GeneralDialog,110,28,165,0,vaporsenslocation,20,sensloc_e);

	/* create label for vapor sensor threshold */
	CreateLabel(GeneralDialog,20,53,0,0,l->Strings[2],NULL);
	/* create edit for vapor sensor threshold */
	AnsiString th;
	th.sprintf("%d",vaporsensthreshold);
	TEdit *sensth_e = CreateEdit(GeneralDialog,160,51,115,0,th,6,sensth_e);

	/* create label for vapor sensor category */
	CreateLabel(GeneralDialog,20,76,0,0,l->Strings[3],NULL);
	/* create combo box for vapor sensor category */
	TComboBox *senscategory_cb = CreateComboBox(GeneralDialog,110,74,165,0,"",-1,senscategory_cb);
	for (int i=4; i < 10; i++)	senscategory_cb->Items->Add(l->Strings[i]);

	switch (vaporsenscategory)
	{
		case 1: senscategory_cb->ItemIndex = 0;
			break;
		case 2: senscategory_cb->ItemIndex = 1;
			break;
		case 3: senscategory_cb->ItemIndex = 2;
			break;
		case 4: senscategory_cb->ItemIndex = 3;
			break;
		case 5: senscategory_cb->ItemIndex = 4;
			break;
		case 6: senscategory_cb->ItemIndex = 5;
			break;
	}

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		vaporsenslocation = sensloc_e->Text;
		try
		{
			vaporsensthreshold = StrToInt(sensth_e->Text);
		}
		catch(EConvertError &e)
		{
			;
		}
		vaporsenscategory = senscategory_cb->ItemIndex+1;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowGroundWaterSensorConfiguration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETGRDWSENSCONFIGURATION,
			CNT_SETGRDWSENSCONFIGURATION,0,21,22,GeneralDialog);

	GeneralDialog->Height = 458;
	GeneralDialog->Bevel1->Height = 416;

	/* create check boxes for water sensor configuration */
	TCheckBox* slot1pos1_cb =
		CreateCheckBox(GeneralDialog,33,23,120,0,l->Strings[1],grdwsensconfig[0],1,slot1pos1_cb);
	TCheckBox* slot1pos2_cb =
		CreateCheckBox(GeneralDialog,33,41,120,0,l->Strings[2],grdwsensconfig[1],2,slot1pos2_cb);
	TCheckBox* slot1pos3_cb =
		CreateCheckBox(GeneralDialog,33,59,120,0,l->Strings[3],grdwsensconfig[2],3,slot1pos3_cb);
	TCheckBox* slot1pos4_cb =
		CreateCheckBox(GeneralDialog,33,77,120,0,l->Strings[4],grdwsensconfig[3],4,slot1pos4_cb);
	TCheckBox* slot1pos5_cb =
		CreateCheckBox(GeneralDialog,33,95,120,0,l->Strings[5],grdwsensconfig[4],5,slot1pos5_cb);

	TCheckBox* slot2pos1_cb =
		CreateCheckBox(GeneralDialog,33,125,120,0,l->Strings[6],grdwsensconfig[5],6,slot2pos1_cb);
	TCheckBox* slot2pos2_cb =
		CreateCheckBox(GeneralDialog,33,143,120,0,l->Strings[7],grdwsensconfig[6],7,slot2pos2_cb);
	TCheckBox* slot2pos3_cb =
		CreateCheckBox(GeneralDialog,33,161,120,0,l->Strings[8],grdwsensconfig[7],8,slot2pos3_cb);
	TCheckBox* slot2pos4_cb =
		CreateCheckBox(GeneralDialog,33,179,120,0,l->Strings[9],grdwsensconfig[8],9,slot2pos4_cb);
	TCheckBox* slot2pos5_cb =
		CreateCheckBox(GeneralDialog,33,197,120,0,l->Strings[10],grdwsensconfig[9],10,slot2pos5_cb);

	TCheckBox* slot3pos1_cb =
		CreateCheckBox(GeneralDialog,33,227,120,0,l->Strings[11],grdwsensconfig[10],11,slot3pos1_cb);
	TCheckBox* slot3pos2_cb =
		CreateCheckBox(GeneralDialog,33,245,120,0,l->Strings[12],grdwsensconfig[11],12,slot3pos2_cb);
	TCheckBox* slot3pos3_cb =
		CreateCheckBox(GeneralDialog,33,263,120,0,l->Strings[13],grdwsensconfig[12],13,slot3pos3_cb);
	TCheckBox* slot3pos4_cb =
		CreateCheckBox(GeneralDialog,33,281,120,0,l->Strings[14],grdwsensconfig[13],14,slot3pos4_cb);
	TCheckBox* slot3pos5_cb =
		CreateCheckBox(GeneralDialog,33,299,120,0,l->Strings[15],grdwsensconfig[14],15,slot3pos5_cb);

	TCheckBox* slot4pos1_cb =
		CreateCheckBox(GeneralDialog,33,329,120,0,l->Strings[16],grdwsensconfig[15],16,slot4pos1_cb);
	TCheckBox* slot4pos2_cb =
		CreateCheckBox(GeneralDialog,33,347,120,0,l->Strings[17],grdwsensconfig[16],17,slot4pos2_cb);
	TCheckBox* slot4pos3_cb =
		CreateCheckBox(GeneralDialog,33,365,120,0,l->Strings[18],grdwsensconfig[17],18,slot4pos3_cb);
	TCheckBox* slot4pos4_cb =
		CreateCheckBox(GeneralDialog,33,383,120,0,l->Strings[19],grdwsensconfig[18],19,slot4pos4_cb);
	TCheckBox* slot4pos5_cb =
		CreateCheckBox(GeneralDialog,33,401,120,0,l->Strings[20],grdwsensconfig[19],20,slot4pos5_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (slot1pos1_cb->Checked) grdwsensconfig[0] = true;
		else grdwsensconfig[0] = false;
		if (slot1pos2_cb->Checked) grdwsensconfig[1] = true;
		else grdwsensconfig[1] = false;
		if (slot1pos3_cb->Checked) grdwsensconfig[2] = true;
		else grdwsensconfig[2] = false;
		if (slot1pos4_cb->Checked) grdwsensconfig[3] = true;
		else grdwsensconfig[3] = false;
		if (slot1pos5_cb->Checked) grdwsensconfig[4] = true;
		else grdwsensconfig[4] = false;

		if (slot2pos1_cb->Checked) grdwsensconfig[5] = true;
		else grdwsensconfig[5] = false;
		if (slot2pos2_cb->Checked) grdwsensconfig[6] = true;
		else grdwsensconfig[6] = false;
		if (slot2pos3_cb->Checked) grdwsensconfig[7] = true;
		else grdwsensconfig[7] = false;
		if (slot2pos4_cb->Checked) grdwsensconfig[8] = true;
		else grdwsensconfig[8] = false;
		if (slot2pos5_cb->Checked) grdwsensconfig[9] = true;
		else grdwsensconfig[9] = false;

		if (slot3pos1_cb->Checked) grdwsensconfig[10] = true;
		else grdwsensconfig[10] = false;
		if (slot3pos2_cb->Checked) grdwsensconfig[11] = true;
		else grdwsensconfig[11] = false;
		if (slot3pos3_cb->Checked) grdwsensconfig[12] = true;
		else grdwsensconfig[12] = false;
		if (slot3pos4_cb->Checked) grdwsensconfig[13] = true;
		else grdwsensconfig[13] = false;
		if (slot3pos5_cb->Checked) grdwsensconfig[14] = true;
		else grdwsensconfig[14] = false;

		if (slot4pos1_cb->Checked) grdwsensconfig[15] = true;
		else grdwsensconfig[15] = false;
		if (slot4pos2_cb->Checked) grdwsensconfig[16] = true;
		else grdwsensconfig[16] = false;
		if (slot4pos3_cb->Checked) grdwsensconfig[17] = true;
		else grdwsensconfig[17] = false;
		if (slot4pos4_cb->Checked) grdwsensconfig[18] = true;
		else grdwsensconfig[18] = false;
		if (slot4pos5_cb->Checked) grdwsensconfig[19] = true;
		else grdwsensconfig[19] = false;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowGroundWaterSensorSetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETGRDWSETUP,CNT_SETGRDWSETUP,0,9,10,GeneralDialog);

	AnsiString cap = GeneralDialog->Caption;
	cap += " - "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for groundwater sensor location */
	CreateLabel(GeneralDialog,20,30,0,0,l->Strings[1],NULL);
	/* create edit for groundwater sensor location */
	TEdit *sensloc_e = CreateEdit(GeneralDialog,110,28,165,0,grdwsenslocation,20,sensloc_e);

	/* create label for groundwater sensor category */
	CreateLabel(GeneralDialog,20,53,0,0,l->Strings[2],NULL);
	/* create combo box for groundwater sensor category */
	TComboBox *senscategory_cb = CreateComboBox(GeneralDialog,110,51,165,0,"",-1,senscategory_cb);
	for (int i=3; i < 9; i++)	senscategory_cb->Items->Add(l->Strings[i]);

	switch (grdwsenscategory)
	{
		case 1: senscategory_cb->ItemIndex = 0;
			break;
		case 2: senscategory_cb->ItemIndex = 1;
			break;
		case 3: senscategory_cb->ItemIndex = 2;
			break;
		case 4: senscategory_cb->ItemIndex = 3;
			break;
		case 5: senscategory_cb->ItemIndex = 4;
			break;
		case 6: senscategory_cb->ItemIndex = 5;
			break;
	}

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		grdwsenslocation = sensloc_e->Text;
		grdwsenscategory = senscategory_cb->ItemIndex+1;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowExternalInputConfiguration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETEXTINPUTCONFIGURATION,
			CNT_SETEXTINPUTCONFIGURATION,0,9,10,GeneralDialog);

	GeneralDialog->Height = 264;
	GeneralDialog->Bevel1->Height = 222;

	/* create check boxes for external input configuration */
	TCheckBox* slot1pos1_cb =
		CreateCheckBox(GeneralDialog,33,23,120,0,l->Strings[1],extinputconfig[0],1,slot1pos1_cb);
	TCheckBox* slot1pos2_cb =
		CreateCheckBox(GeneralDialog,33,41,120,0,l->Strings[2],extinputconfig[1],2,slot1pos2_cb);

	TCheckBox* slot2pos1_cb =
		CreateCheckBox(GeneralDialog,33,71,120,0,l->Strings[3],extinputconfig[2],3,slot2pos1_cb);
	TCheckBox* slot2pos2_cb =
		CreateCheckBox(GeneralDialog,33,94,120,0,l->Strings[4],extinputconfig[3],4,slot2pos2_cb);

	TCheckBox* slot3pos1_cb =
		CreateCheckBox(GeneralDialog,33,124,120,0,l->Strings[5],extinputconfig[4],5,slot3pos1_cb);
	TCheckBox* slot3pos2_cb =
		CreateCheckBox(GeneralDialog,33,147,120,0,l->Strings[6],extinputconfig[5],6,slot3pos2_cb);

	TCheckBox* slot4pos1_cb =
		CreateCheckBox(GeneralDialog,33,177,120,0,l->Strings[7],extinputconfig[6],7,slot4pos1_cb);
	TCheckBox* slot4pos2_cb =
		CreateCheckBox(GeneralDialog,33,200,120,0,l->Strings[8],extinputconfig[7],8,slot4pos2_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (slot1pos1_cb->Checked) extinputconfig[0] = true;
		else extinputconfig[0] = false;
		if (slot1pos2_cb->Checked) extinputconfig[1] = true;
		else extinputconfig[1] = false;

		if (slot2pos1_cb->Checked) extinputconfig[2] = true;
		else extinputconfig[2] = false;
		if (slot2pos2_cb->Checked) extinputconfig[3] = true;
		else extinputconfig[3] = false;

		if (slot3pos1_cb->Checked) extinputconfig[4] = true;
		else extinputconfig[4] = false;
		if (slot3pos2_cb->Checked) extinputconfig[5] = true;
		else extinputconfig[5] = false;

		if (slot4pos1_cb->Checked) extinputconfig[6] = true;
		else extinputconfig[6] = false;
		if (slot4pos2_cb->Checked) extinputconfig[7] = true;
		else extinputconfig[7] = false;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowExternalInputSetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETEXTINPUTSETUP,CNT_SETEXTINPUTSETUP,0,15,16,GeneralDialog);

	AnsiString cap = GeneralDialog->Caption;
	cap += " - "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for external input name */
	CreateLabel(GeneralDialog,20,20,0,0,l->Strings[1],NULL);
	/* create edit for external input name */
	TEdit *extinpn_e = CreateEdit(GeneralDialog,110,18,165,0,extinputname,20,extinpn_e);

	/* create label for external input type */
	CreateLabel(GeneralDialog,20,43,0,0,l->Strings[2],NULL);
	/* create combo box for external input type */
	TComboBox *extinptype_cb = CreateComboBox(GeneralDialog,110,41,165,0,"",-1,extinptype_cb);
	for (int i=3; i < 7; i++)	extinptype_cb->Items->Add(l->Strings[i]);

	/* create radio buttons for external input switch orientation */
	TRadioButton *extinpnc_rb = CreateRadioButton(GeneralDialog,20,66,
		100,0,l->Strings[7],false,extinpnc_rb);
	TRadioButton *extinpno_rb = CreateRadioButton(GeneralDialog,130,66,
		100,0,l->Strings[8],false,extinpno_rb);
	if (extinputswitchtype==1)	extinpno_rb->Checked = true;
	if (extinputswitchtype==2)	extinpnc_rb->Checked = true;

	/* create label for external input tank or pump number */ 
	CreateLabel(GeneralDialog,20,89,0,0,l->Strings[9],NULL);
	/* create edit and up down for external input tank or pump number */
	TEdit *extinpnr_e = CreateEdit(GeneralDialog,150,87,60,0,"",2,extinpnr_e);
	TUpDown *extinpnr_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,99,extinputtanknr,
		extinpnr_e,extinpnr_ud);

	/* create label for external input dispense mode */
	CreateLabel(GeneralDialog,20,112,0,0,l->Strings[10],NULL);
	/* create combo box for external input dispense mode */
	TComboBox *extinpdispmode_cb = CreateComboBox(GeneralDialog,110,110,165,0,"",-1,extinpdispmode_cb);
	for (int i=11; i < 15; i++)	extinpdispmode_cb->Items->Add(l->Strings[i]);

	switch (extinputtype)
	{
		case 1: extinptype_cb->ItemIndex = 0;
			break;
		case 2: extinptype_cb->ItemIndex = 1;
			break;
		case 3: extinptype_cb->ItemIndex = 2;
			break;
		case 4: extinptype_cb->ItemIndex = 3;
			break;
	}

	switch (extinputdispensemode)
	{
		case 1: extinpdispmode_cb->ItemIndex = 0;
			break;
		case 2: extinpdispmode_cb->ItemIndex = 1;
			break;
		case 3: extinpdispmode_cb->ItemIndex = 2;
			break;
		case 4: extinpdispmode_cb->ItemIndex = 3;
			break;
	}

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		extinputname = extinpn_e->Text;
		extinputtype = extinptype_cb->ItemIndex+1;
		if (extinpno_rb->Checked)	extinputswitchtype = 1;
		else if (extinpnc_rb->Checked)	extinputswitchtype = 2;
		else extinputswitchtype = 0;
		extinputtanknr = extinpnr_ud->Position;
		extinputdispensemode = extinpdispmode_cb->ItemIndex+1;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowRelayConfiguration(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETRELAYCONFIGURATION,CNT_SETRELAYCONFIGURATION,0,17,18,GeneralDialog);

	GeneralDialog->Height = 390;
	GeneralDialog->Bevel1->Height = 348;

	/* create check boxes for relay configuration */
	TCheckBox* slot1pos1_cb =
		CreateCheckBox(GeneralDialog,33,23,200,0,l->Strings[1],relayconfig[0],1,slot1pos1_cb);
	TCheckBox* slot1pos2_cb =
		CreateCheckBox(GeneralDialog,33,41,200,0,l->Strings[2],relayconfig[1],2,slot1pos2_cb);
	TCheckBox* slot1pos3_cb =
		CreateCheckBox(GeneralDialog,33,59,200,0,l->Strings[3],relayconfig[2],3,slot1pos3_cb);
	TCheckBox* slot1pos4_cb =
		CreateCheckBox(GeneralDialog,33,77,200,0,l->Strings[4],relayconfig[3],4,slot1pos4_cb);
	TCheckBox* slot2pos1_cb =
		CreateCheckBox(GeneralDialog,33,100,200,0,l->Strings[5],relayconfig[4],5,slot2pos1_cb);
	TCheckBox* slot2pos2_cb =
		CreateCheckBox(GeneralDialog,33,118,200,0,l->Strings[6],relayconfig[5],6,slot2pos2_cb);
	TCheckBox* slot2pos3_cb =
		CreateCheckBox(GeneralDialog,33,136,200,0,l->Strings[7],relayconfig[6],7,slot2pos3_cb);
	TCheckBox* slot2pos4_cb =
		CreateCheckBox(GeneralDialog,33,154,200,0,l->Strings[8],relayconfig[7],8,slot2pos4_cb);
	TCheckBox* slot3pos1_cb =
		CreateCheckBox(GeneralDialog,33,177,200,0,l->Strings[9],relayconfig[8],9,slot3pos1_cb);
	TCheckBox* slot3pos2_cb =
		CreateCheckBox(GeneralDialog,33,195,200,0,l->Strings[10],relayconfig[9],10,slot3pos2_cb);
	TCheckBox* slot3pos3_cb =
		CreateCheckBox(GeneralDialog,33,213,200,0,l->Strings[11],relayconfig[10],11,slot3pos3_cb);
	TCheckBox* slot3pos4_cb =
		CreateCheckBox(GeneralDialog,33,231,200,0,l->Strings[12],relayconfig[11],12,slot3pos4_cb);
	TCheckBox* slot4pos1_cb =
		CreateCheckBox(GeneralDialog,33,254,200,0,l->Strings[13],relayconfig[12],13,slot4pos1_cb);
	TCheckBox* slot4pos2_cb =
		CreateCheckBox(GeneralDialog,33,272,200,0,l->Strings[14],relayconfig[13],14,slot4pos2_cb);
	TCheckBox* slot4pos3_cb =
		CreateCheckBox(GeneralDialog,33,290,200,0,l->Strings[15],relayconfig[14],15,slot4pos3_cb);
	TCheckBox* slot4pos4_cb =
		CreateCheckBox(GeneralDialog,33,308,200,0,l->Strings[16],relayconfig[15],16,slot4pos4_cb);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		if (slot1pos1_cb->Checked) relayconfig[0] = true;
		else relayconfig[0] = false;
		if (slot1pos2_cb->Checked) relayconfig[1] = true;
		else relayconfig[1] = false;
		if (slot1pos3_cb->Checked) relayconfig[2] = true;
		else relayconfig[2] = false;
		if (slot1pos4_cb->Checked) relayconfig[3] = true;
		else relayconfig[3] = false;
		if (slot2pos1_cb->Checked) relayconfig[4] = true;
		else relayconfig[4] = false;
		if (slot2pos2_cb->Checked) relayconfig[5] = true;
		else relayconfig[5] = false;
		if (slot2pos3_cb->Checked) relayconfig[6] = true;
		else relayconfig[6] = false;
		if (slot2pos4_cb->Checked) relayconfig[7] = true;
		else relayconfig[7] = false;
		if (slot3pos1_cb->Checked) relayconfig[8] = true;
		else relayconfig[8] = false;
		if (slot3pos2_cb->Checked) relayconfig[9] = true;
		else relayconfig[9] = false;
		if (slot3pos3_cb->Checked) relayconfig[10] = true;
		else relayconfig[10] = false;
		if (slot3pos4_cb->Checked) relayconfig[11] = true;
		else relayconfig[11] = false;
		if (slot4pos1_cb->Checked) relayconfig[12] = true;
		else relayconfig[12] = false;
		if (slot4pos2_cb->Checked) relayconfig[13] = true;
		else relayconfig[13] = false;
		if (slot4pos3_cb->Checked) relayconfig[14] = true;
		else relayconfig[14] = false;
		if (slot4pos4_cb->Checked) relayconfig[15] = true;
		else relayconfig[15] = false;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowRelaySetup(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_SETRELAYSETUP,CNT_SETRELAYSETUP,0,10,11,GeneralDialog);

	AnsiString cap = GeneralDialog->Caption;
	cap += " - "+IntToStr(devicenumber);
	GeneralDialog->Caption = cap;

	/* create label for relay designation */
	CreateLabel(GeneralDialog,20,20,0,0,l->Strings[1],NULL);
	/* create edit for relay designation */
	TEdit *reldes_e = CreateEdit(GeneralDialog,110,18,165,0,relaydesignation,20,reldes_e);

	/* create label for relay type */
	CreateLabel(GeneralDialog,20,43,0,0,l->Strings[2],NULL);
	/* create combo box for relay type */
	TComboBox *relaytype_cb = CreateComboBox(GeneralDialog,110,41,165,0,"",-1,relaytype_cb);
	for (int i=3; i < 7; i++)	relaytype_cb->Items->Add(l->Strings[i]);

	/* create radio buttons for relay orientation */
	TRadioButton *relaync_rb = CreateRadioButton(GeneralDialog,20,66,
		100,0,l->Strings[7],false,relaync_rb);
	TRadioButton *relayno_rb = CreateRadioButton(GeneralDialog,130,66,
		100,0,l->Strings[8],false,relayno_rb);
	if (relayorientation==1)	relayno_rb->Checked = true;
	if (relayorientation==2)	relaync_rb->Checked = true;

	/* create label for relay tank number */
	CreateLabel(GeneralDialog,20,89,0,0,l->Strings[9],NULL);
	/* create edit and up down for relay tank number */
	TEdit *relaynr_e = CreateEdit(GeneralDialog,150,87,60,0,"",2,relaynr_e);
	TUpDown *relaynr_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,99,relaytanknr,
		relaynr_e,relaynr_ud);

	switch (relaytype)
	{
		case 1: relaytype_cb->ItemIndex = 0;
			break;
		case 2: relaytype_cb->ItemIndex = 1;
			break;
		case 3: relaytype_cb->ItemIndex = 2;
			break;
		case 4: relaytype_cb->ItemIndex = 3;
			break;
	}

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		relaydesignation = reldes_e->Text;
		relaytype = relaytype_cb->ItemIndex+1;
		if (relayno_rb->Checked)	relayorientation = 1;
		else if (relaync_rb->Checked)	relayorientation = 2;
		else relayorientation = 0;
		relaytanknr = relaynr_ud->Position;

		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

void __fastcall TShowCmdSpecWindows::ShowArchiveUtility(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_ARCHIVING,CNT_ARCHIVING,0,2,3,GeneralDialog);

	/* create label for archive utility question */
	CreateLabel(GeneralDialog,20,50,0,0,l->Strings[1],NULL);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}

/* event handlers */
void __fastcall TShowCmdSpecWindows::ShiftStartTimeOnClick(TObject *Sender)
{
	if (dynamic_cast<TCheckBox*>(Sender)->Tag==1)
	{
		if (dynamic_cast<TCheckBox*>(Sender)->Checked)
			st1->Enabled = true;
		else	st1->Enabled = false;
	}
	if (dynamic_cast<TCheckBox*>(Sender)->Tag==2)
	{
		if (dynamic_cast<TCheckBox*>(Sender)->Checked)
			st2->Enabled = true;
		else	st2->Enabled = false;
	}
	if (dynamic_cast<TCheckBox*>(Sender)->Tag==3)
	{
		if (dynamic_cast<TCheckBox*>(Sender)->Checked)
			st3->Enabled = true;
		else	st3->Enabled = false;
	}
	if (dynamic_cast<TCheckBox*>(Sender)->Tag==4)
	{
		if (dynamic_cast<TCheckBox*>(Sender)->Checked)
			st4->Enabled = true;
		else	st4->Enabled = false;
	}
}
void __fastcall TShowCmdSpecWindows::meterdp_cbClick(TObject *Sender)
{
	if (dynamic_cast<TCheckBox*>(Sender)->Checked)
	{
		endf_l->Enabled = true;
		endf_cb->Enabled = true;
    	endv_l->Enabled = true;
		endv_e->Enabled = true;
		endv_ud->Enabled = true;
		endfact_cbClick(endf_cb);
		cupd_l->Enabled = true;
		cupd_cb->Enabled = true;
	}
	else
	{
		endf_l->Enabled = false;
		endf_cb->Enabled = false;
		endv_l->Enabled = false;
		endv_e->Enabled = false;
		endv_ud->Enabled = false;
		cupd_l->Enabled = false;
		cupd_cb->Enabled = false;
	}
}
void __fastcall TShowCmdSpecWindows::tempcomp_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		tempcomp -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		tempcomp += 0.1;
	}

	if (unit_index==1)
	{
		if (tempcomp < 0.00)	tempcomp = -0.00;
		if (tempcomp > 120.00)	tempcomp = 120.00;
	}
	else if (unit_index==2)
	{
		if (tempcomp < -17.00)	tempcomp = -17.00;
		if (tempcomp > 49.00)	tempcomp = 49.00;
	}
	else
	{
		if (tempcomp < 0.00)	tempcomp = -0.00;
		if (tempcomp > 120.00)	tempcomp = 120.00;
	}

	if (tc_e)	tc_e->Text = FloatToStrF(tempcomp, ffFixed, 5, 1);
}
void __fastcall TShowCmdSpecWindows::thermalcoeff_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		producttermalcoeff -= 0.00001;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		producttermalcoeff += 0.00001;
	}

	if (thermalcoeff_e)	thermalcoeff_e->Text = FloatToStrF(producttermalcoeff,
		ffFixed, 5, 5);
}
void __fastcall TShowCmdSpecWindows::tankdiam_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		tankdiameter -= 0.01;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		tankdiameter += 0.01;
	}

	if (tankdiameter < 0.00)	tankdiameter = 0.00;

	if (tdiam_e)	tdiam_e->Text = FloatToStrF(tankdiameter, ffFixed, 7, 2);
}
void __fastcall TShowCmdSpecWindows::waterw_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		waterwarning -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		waterwarning += 0.1;
	}

	if (waterwarning < 0.00)	waterwarning = 0.00;

	if (watw_e)	watw_e->Text = FloatToStrF(waterwarning, ffFixed, 5, 1);
}
void __fastcall TShowCmdSpecWindows::hwaterl_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		highwaterlimit -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		highwaterlimit += 0.1;
	}

	if (highwaterlimit < 0.00)	highwaterlimit = 0.00;

	if (hwatl_e)	hwatl_e->Text = FloatToStrF(highwaterlimit, ffFixed, 5, 1);
}
void __fastcall TShowCmdSpecWindows::prath_udClick(TObject *Sender, TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		perreconcalmthreshold -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		perreconcalmthreshold += 0.1;
	}

	if (perreconcalmthreshold < 0.00)	perreconcalmthreshold = 0.00;
	if (perreconcalmthreshold > 5.00)	perreconcalmthreshold = 5.00;

	if (prath_e)	prath_e->Text = FloatToStrF(perreconcalmthreshold, ffFixed, 5, 2);
}
void __fastcall TShowCmdSpecWindows::mcalibofs_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		metercaliboffset -= 0.001;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		metercaliboffset += 0.001;
	}

	if (metercaliboffset < -1.000)	metercaliboffset = -1.000;
	if (metercaliboffset > 1.000)	metercaliboffset = 1.000;

	if (mcalibofs_e)	mcalibofs_e->Text = FloatToStrF(metercaliboffset, ffFixed, 5, 3);
}
void __fastcall TShowCmdSpecWindows::tanktilt_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		tanktilt -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		tanktilt += 0.1;
	}

	if (tankt_e)	tankt_e->Text = FloatToStrF(tanktilt, ffFixed, 5, 2);
}
void __fastcall TShowCmdSpecWindows::probeoffset_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		probeoffset -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		probeoffset += 0.1;
	}

	if (probeoffset < -3657.6)	probeoffset = -3657.6;
	if (probeoffset > 3657.6)	probeoffset = 3657.6;

	if (probeofs_e)	probeofs_e->Text = FloatToStrF(probeoffset, ffFixed, 5, 2);
}
void __fastcall TShowCmdSpecWindows::stickoffset_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		stickoffset -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		stickoffset += 0.1;
	}

	if (stickoffset < -144.00)	stickoffset = -144.00;
	if (stickoffset > 144.00)	stickoffset = 144.00;

	if (stickofs_e)	stickofs_e->Text = FloatToStrF(stickoffset, ffFixed, 5, 2);
}
void __fastcall TShowCmdSpecWindows::pumpth_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		pumpthreshold -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		pumpthreshold += 0.1;
	}

	if (pumpthreshold < 0.00)	pumpthreshold = 0.00;
	if (pumpthreshold > 50.00)	pumpthreshold = 50.00;

	if (pmpth_e)	pmpth_e->Text = FloatToStrF(pumpthreshold, ffFixed, 5, 2);
}
void __fastcall TShowCmdSpecWindows::maxorlv_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		maxorlabelvolume -= 1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		maxorlabelvolume += 1;
	}

	if (maxorlabelvolume < 0)	maxorlabelvolume = 0;
	if (maxorlabelvolume > 999999)	maxorlabelvolume = 999999;

	AnsiString molv;
	molv.sprintf("%d",maxorlabelvolume);
	if (morlv_e)	morlv_e->Text = molv;
}
void __fastcall TShowCmdSpecWindows::lproductl_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		lowproductlimit -= 1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		lowproductlimit += 1;
	}

	if (lowproductlimit < 0)	lowproductlimit = 0;
	if (lowproductlimit > 999999)	lowproductlimit = 999999;

	AnsiString lp;
	lp.sprintf("%d",lowproductlimit);
	if (lproductl_e)	lproductl_e->Text = lp;
}
void __fastcall TShowCmdSpecWindows::suddenll_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		suddenlosslimit -= 1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		suddenlosslimit += 1;
	}

	if (suddenlosslimit < 0)	suddenlosslimit = 0;
	if (suddenlosslimit > 999999)	suddenlosslimit = 999999;

	AnsiString sll;
	sll.sprintf("%d",suddenlosslimit);
	if (suddenll_e)	suddenll_e->Text = sll;
}
void __fastcall TShowCmdSpecWindows::producttc_eChange(TObject *Sender)
{
	try
	{
		producttermalcoeff = StrToFloat(thermalcoeff_e->Text);
	}
	catch(EConvertError &e)
	{
    	;
	}
}
void __fastcall TShowCmdSpecWindows::tankdiam_eChange(TObject *Sender)
{
	try
	{
		tankdiameter = StrToFloat(tdiam_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::waterw_eChange(TObject *Sender)
{
	try
	{
		waterwarning = StrToFloat(watw_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::hwaterl_eChange(TObject *Sender)
{
	try
	{
		highwaterlimit = StrToFloat(hwatl_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::maxorlv_eChange(TObject *Sender)
{
	try
	{
		maxorlabelvolume = StrToInt(morlv_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::tanktilt_eChange(TObject *Sender)
{
	try
	{
		tanktilt = StrToFloat(tankt_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::probeoffset_eChange(TObject *Sender)
{
	try
	{
		probeoffset = StrToFloat(probeofs_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::stickoffset_eChange(TObject *Sender)
{
	try
	{
		stickoffset = StrToFloat(stickofs_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::pumpth_eChange(TObject *Sender)
{
	try
	{
		pumpthreshold = StrToFloat(pmpth_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::prath_eChange(TObject *Sender)
{
	try
	{
		perreconcalmthreshold = StrToFloat(prath_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::mcalibofs_eChange(TObject *Sender)
{
	try
	{
		metercaliboffset = StrToFloat(mcalibofs_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::lproductl_eChange(TObject *Sender)
{
	try
	{
		lowproductlimit= StrToInt(lproductl_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::suddenll_eChange(TObject *Sender)
{
	try
	{
		suddenlosslimit = StrToInt(suddenll_e->Text);
	}
	catch(EConvertError &e)
	{
		;
	}
}
void __fastcall TShowCmdSpecWindows::endval_udClick(TObject *Sender,
	TUDBtnType Button)
{
	/* click on the down arrow */
	if (Button==Comctrls::btPrev)
	{
		endvalue -= 0.1;
	}
	/* click on the up arrow */
	if (Button==Comctrls::btNext)
	{
		endvalue += 0.1;
	}

	if (endvalue > 1.0)	endvalue = 1.0;
	if (endvalue < 0)	endvalue = 0.0;

	if (endv_e)	endv_e->Text = FloatToStrF(endvalue, ffFixed, 5, 1);
}
void __fastcall TShowCmdSpecWindows::endfact_cbClick(TObject *Sender)
{
	if (dynamic_cast<TComboBox*>(Sender)->ItemIndex==3)
	{
		endv_l->Enabled = true;
		endv_e->Enabled = true;
		endv_ud->Enabled = true;
	}
	else
	{
		endv_l->Enabled = false;
		endv_e->Enabled = false;
		endv_ud->Enabled = false;
	}
}

/* public */

/* constructor */
TShowCmdSpecWindows::TShowCmdSpecWindows(void)
{
	cancel_from_dialog = false;

	devicenumber = 0;
	language_index = -1;
	unit_index = -1;
	date_time_format_index = -1;
	date = 0;
	time = 0;
	header1 = "";
	header2 = "";
	header3 = "";
	header4 = "";
	shiftstart1 = false;
	shiftstart2 = false;
	shiftstart3 = false;
	shiftstart4 = false;
	shifttime1 = 0;
	shifttime2 = 0;
	shifttime3 = 0;
	shifttime4 = 0;
	shiftbirprintouts = false;
	ticketeddelivery = false;
	tdclosedayofweek = -1;
	dailydelivery = false;
	weeklydelivery = false;
	periodicdelivery = false;
	dailybookdelivery = false;
	weeklybookdelivery = false;
	periodicbookdelivery = false;
	dailyanalysis = false;
	weeklyanalysis = false;
	periodicanalysis = false;
	testneededwarningflag = false;
	daysbeforewarn = 0;
	daysbeforealm = 0;
	passlinetest = true;
	remoteprinterpageeject = false;
	printtc = false;
	tempcomp = 0.00;
	tankerloadreport = true;
	stickheightoffsetflag = false;
	hprotocolformat = false; //HEIGHT
	prectest = 12;
	preclinetestauto02 = false;
	preclinetestauto01 = false;
	daylightsavings = false;
	dlstartmonth = 4;
	dlstartweekofmonth = 1;
	dlstartdayofweek = 7;
	dlstarthour = 0.166666666667;
	dlendmonth = 10;
	dlendweekofmonth = 6;
	dlenddayofweek = 7;
	dlendhour = 0.166666666667;
	redirectlocalpoflag = false;
	qpldmonthlypoflag = true;
	europrotocolprefix = true;
	systemcode = "000000";
	baud = 1;
	parity = 0;
	stopbit = 0;
	bytesize = 0;
	dialtype = 0;
	answeron = 1;
	modemtype = 0;
	dialtoneinterval = 32;
	dtrnormalstate = 1;
	syscode = "000000";
	setupstring = "";    
	receiverconfig = false;
	receiverlocation = "";
	receivertelnumber = "";
	receiverportnumber = 0;
	receivertype = 0;
	receiverretrynumber = 0;
	receiverdelaytime = 0;
	receiverconfirmation = 0;
	autodialmethod = false;
	frequencytype = 1;
	freqdate = 0;
	freqtime = 0;
	freqmonth = 1;
	freqweek = 1;
	freqday = 1;
	birend = false;
	productlabel = "";
	productcode = "";
	producttermalcoeff = 0.00;
	tankdiameter = 0.00;
	meterdatapresent = false;
	endfactor = 0;
	endvalue = 0.0;
	calibrationupdate = 0;
	floatsize = 0;
	waterwarning = 0.0;
	highwaterlimit = 0.0;
	maxorlabelvolume = 0;
	overfilllimit = 0;
	highproductlimit = 0;
	deliverylimit = 0;
	lowproductlimit = 0;
	leakalarmlimit = 0;
	suddenlosslimit = 0;
	tanktilt = 0.00;
	probeoffset = 0.00;
	manifoldedtanks = "";
	leakminimumperiodic = 0;
	leakminimumannual = 0;
	periodictesttype = false;
	annualtestfail = false;
	periodictestfail = false;
	grosstestfail = false;
	annualtestaveraging = false;
	periodictestaveraging = false;
	leaktestnotify = false;
	siphonbreak = false;
	stickoffset = 0.00;
	hrmreconcwarnlimit = 0;
	hrmreconcalmlimit = 0;
	deliveryreportdt = 0;
	for (int i=0; i < 20; i++)	tankprofile[i] = "0";
	tankprofiletype = 0;
	mdim_string = "";
	edim_string = "";
	autodailyclosing = 0;
	shiftclosing1 = false;
	shiftclosing2 = false;
	shiftclosing3 = false;
	shiftclosing4 = false;
	periodicreconcmode = 1;
	periodicreconclen = 1;
	perreconcalmonoff = 1;
	perreconcalmthreshold = 1.00;
	perreconcalmoffset = 130;
	remotereportformat = 1;
	tempcompensation = 0;
	metercaliboffset = 0.000;
	bustype = slotnr = fuelpos = meter = tanknr = 0;
	liqsenslocation = "";
	liqsenstype = 1;
	liqsenscategory = 1;
	vaporsenslocation = "";
	vaporsensthreshold = 1000;
	vaporsenscategory = 1;
	grdwsenslocation = "";
	grdwsenscategory = 1;
	extinputname = "";
	extinputtype = 1;
	extinputswitchtype = 1;
	extinputtanknr = 0;
	extinputdispensemode = 1;
	relaydesignation = "";
	relaytype = 1;
	relayorientation = 1;
	relaytanknr = 0;
}
/* destructor */
TShowCmdSpecWindows::~TShowCmdSpecWindows(void)
{
	;
}

void TShowCmdSpecWindows::ShowDialogWindow(dialog_types dt)
{
	switch (dt)
	{
		case dlg_systemlanguageandunit:
			ShowSystemLanguageAndUnit();
			break;
		case dlg_systemdatetimedisplayformat:
			ShowSystemDateTimeDisplayFormat();
			break;
		case dlg_timeofday:
			ShowTimeOfDay();
			break;
		case dlg_printheaderlines:
			ShowPrintHeaderLines();
			break;
		case dlg_shiftstarttimes:
        	ShowShiftStartTimes();
			break;
		case dlg_shiftbirprintouts:
			ShowShiftBIRPrintouts();
			break;
		case dlg_dailybirprintouts:
			ShowDailyBIRPrintouts();
			break;
		case dlg_ticketeddelivery:
			ShowTicketedDelivery();
			break;
		case dlg_tcticketeddelivery:
			ShowTCTicketedDelivery();
			break;
		case dlg_tdclosedayofweek:
			ShowTDCloseDayOfWeek();
			break;
		case dlg_deliveryvariance:
			ShowVariance(STR_SETDELIVERYVARIANCEFLAG, CNT_SETDELIVERYVARIANCEFLAG);
			break;
		case dlg_deliverybookvariance:
			ShowVariance(STR_SETDELIVERYBOOKVARIANCEFLAG, CNT_SETDELIVERYBOOKVARIANCEFLAG);
			break;
		case dlg_varianceanalysis:
			ShowVariance(STR_SETVARIANCEANALYSISFLAG, CNT_SETVARIANCEANALYSISFLAG);
			break;
		case dlg_periodictestneededwarn:
			ShowTestNeededWarnings(STR_SETPERIODICTEST, CNT_SETPERIODICTEST);
			break;
		case dlg_annualtestneededwarn:
			ShowTestNeededWarnings(STR_SETANNUALTEST, CNT_SETANNUALTEST);
			break;
		case dlg_linereenablemethod:
			ShowLineReEnableMethod();
			break;
		case dlg_lineperiodictestneededwarn:
			ShowTestNeededWarnings(STR_SETLINEPERIODICTEST, CNT_SETLINEPERIODICTEST);
			break;
		case dlg_lineannualtestneededwarn:
			ShowTestNeededWarnings(STR_SETLINEANNUALTEST, CNT_SETLINEANNUALTEST);
			break;
		case dlg_remoteprinterpageeject:
        	ShowRemotePrinterPageEject();
			break;
		case dlg_printtc:
			ShowPrintTC();
			break;
		case dlg_tempcomp:
			ShowTemperatureCompensation();
			break;
		case dlg_tankerloadreport:
			ShowTankerLoadReport();
			break;
		case dlg_stickheightoffsetflag:
			ShowStickHeightOffsetFlag();
			break;
		case dlg_hprotocoldataformat:
			ShowHProtocolDataFormat();
			break;
		case dlg_prectestduration:
			ShowPrecisionTestDuration();
			break;
		case dlg_preclinetestauto02:
			ShowPrecisionLineTestAutoConfirm02();
			break;
		case dlg_preclinetestauto01:
			ShowPrecisionLineTestAutoConfirm01();
			break;
		case dlg_daylightsavingstime:
			ShowDaylightSavingsTime();
			break;
		case dlg_redirectlocalpo:
			ShowReDirectLocalPrintout();
			break;
		case dlg_qpldmonthlypo:
			ShowQPLDMonthlyPrintout();
			break;
		case dlg_europrotocolprefix:
			ShowEuroProtocolPrefix();
			break;
		case dlg_systemcode:
			ShowSystemSecurityCode();
			break;
		case dlg_portsettings:
			ShowPortSettings();
			break;
		case dlg_phonedirectory:
			ShowPhoneDirectorySetup();
			break;
		case dlg_autodialsetup:
			ShowAutodialSetup();
			break;
		case dlg_autodialonalarms:
        	ShowAutodialOnAlarms();
			break;
		case dlg_rs232eom:
			ShowRS232EOM();
			break;
		case dlg_tankconfig:
			ShowTankConfiguration();
        	break;
		case dlg_intanksetup:
			ShowInTankSetup();
			break;
		case dlg_tankprofile:
			ShowTankProfile();
			break;
		case dlg_dimstring:
			ShowDIMString();
			break;
		case dlg_autodailyclosing:
			ShowAutodailyClosing();
			break;
		case dlg_shiftclosingtimes:
			ShowAutoShiftClosingTimes();
			break;
		case dlg_periodicreconcmode:
			ShowPeriodicreconciliationMode();
			break;
		case dlg_perreconcalm:
			ShowPeriodicReconciliationAlarm();
			break;
		case dlg_remotereportformat:
			ShowRemoteReportFormat();
			break;
		case dlg_tempcompensation:
			ShowTempCompensation();
			break;
		case dlg_metercaliboffset:
			ShowMeterCalibrationOffset();
			break;
		case dlg_modifytankmetermap:
			ShowModifyTankMeterMap();
			break;
		case dlg_liquidsensorconfig:
			ShowLiquidSensorConfiguration();
			break;
		case dlg_liqsenssetup:
			ShowLiquidSensorSetup();
			break;
		case dlg_vaporsensconfig:
			ShowVaporSensorConfiguration();
        	break;
		case dlg_vaporsenssetup:
			ShowVaporSensorSetup();
			break;
		case dlg_grdwsensconfig:
			ShowGroundWaterSensorConfiguration();
			break;
		case dlg_gdrwsenssetup:
			ShowGroundWaterSensorSetup();
			break;
		case dlg_extinputconfig:
			ShowExternalInputConfiguration();
			break;
		case dlg_extinputsetup:
			ShowExternalInputSetup();
			break;
		case dlg_relayconfig:
			ShowRelayConfiguration();
			break;
		case dlg_relaysetup:
			ShowRelaySetup();
			break;
		case dlg_archive:
			ShowArchiveUtility();
        	break;
		default:;
	}
}

TForm* TShowCmdSpecWindows::getDialogPointer(void)
{
	return GeneralDialog;
}

bool TShowCmdSpecWindows::getModalResult(void)
{
	return cancel_from_dialog;
}

/* dialog window to get number of ...port or ...tank or ...sensor etc. */
void __fastcall TShowCmdSpecWindows::ShowGetNumber(void)
{
	/* it takes the list of strings of the specified dialog window language */
	TStringList *l = new TStringList;
	/* initialze the dialog */
	GeneralDialog = InitDialog(l,STR_GETNUMBERDIALOG,CNT_GETNUMBERDIALOG,0,2,3,GeneralDialog);

	/* create label for days before needed warning */
	TLabel* select_l = CreateLabel(GeneralDialog, 20, 33, 0, 0, l->Strings[1], select_l);

	/* create edit control for days before warning */
	TEdit* select_e = CreateEdit(GeneralDialog,130,30,40,0,"",0,select_e);

	/* create up down control for days before warning */
	TUpDown* select_ud = CreateUpDown(GeneralDialog,0,0,0,0,0,99,devicenumber,select_e,select_ud);

	if (GeneralDialog->ShowModal()==ID_OK)
	{
		devicenumber = select_ud->Position;
		cancel_from_dialog = false;
	}
	else	cancel_from_dialog = true;

	if (GeneralDialog)
	{
		delete GeneralDialog;
		GeneralDialog = NULL;
	}

	delete l;
}
                                 
void TShowCmdSpecWindows::setDeviceNumber(int idevicenumber)
{
	devicenumber = idevicenumber;
}
int TShowCmdSpecWindows::getDeviceNumber(void)
{
	return devicenumber;
}
void TShowCmdSpecWindows::setLanguageIndex(int ilanguage_index)
{
	language_index = ilanguage_index;
}
int TShowCmdSpecWindows::getLanguageIndex(void)
{
	return language_index;
}
void TShowCmdSpecWindows::setUnitIndex(int iunit_index)
{
	unit_index = iunit_index;
}
int TShowCmdSpecWindows::getUnitIndex(void)
{
	return unit_index;
}
void TShowCmdSpecWindows::setDateTimeFormatIndex(int idate_time_format_index)
{
	date_time_format_index = idate_time_format_index;
}
int TShowCmdSpecWindows::getDateTimeFormatIndex(void)
{
	return date_time_format_index;
}
void TShowCmdSpecWindows::setDate(TDateTime idate)
{
	date = idate;
}
TDateTime TShowCmdSpecWindows::getDate(void)
{
	return date;
}
void TShowCmdSpecWindows::setTime(TDateTime itime)
{
	time = itime;
}
TDateTime TShowCmdSpecWindows::getTime(void)
{
	return time;
}
void TShowCmdSpecWindows::setHeader1(AnsiString iheader1)
{
	header1 = iheader1;
}
AnsiString TShowCmdSpecWindows::getHeader1(void)
{
	return header1;
}
void TShowCmdSpecWindows::setHeader2(AnsiString iheader2)
{
	header2 = iheader2;
}
AnsiString TShowCmdSpecWindows::getHeader2(void)
{
	return header2;
}
void TShowCmdSpecWindows::setHeader3(AnsiString iheader3)
{
	header3 = iheader3;
}
AnsiString TShowCmdSpecWindows::getHeader3(void)
{
	return header3;
}
void TShowCmdSpecWindows::setHeader4(AnsiString iheader4)
{
	header4 = iheader4;
}
AnsiString TShowCmdSpecWindows::getHeader4(void)
{
	return header4;
}
void TShowCmdSpecWindows::setShifttime1(AnsiString ishifttime1)
{
	shifttime1 = ishifttime1;
}
TDateTime TShowCmdSpecWindows::getShifttime1(void)
{
	return shifttime1;
}
void TShowCmdSpecWindows::setShifttime2(AnsiString ishifttime2)
{
	shifttime2 = ishifttime2;
}
TDateTime TShowCmdSpecWindows::getShifttime2(void)
{
	return shifttime2;
}
void TShowCmdSpecWindows::setShifttime3(AnsiString ishifttime3)
{
	shifttime3 = ishifttime3;
}
TDateTime TShowCmdSpecWindows::getShifttime3(void)
{
	return shifttime3;
}
void TShowCmdSpecWindows::setShifttime4(AnsiString ishifttime4)
{
	shifttime4 = ishifttime4;
}
TDateTime TShowCmdSpecWindows::getShifttime4(void)
{
	return shifttime4;
}
void TShowCmdSpecWindows::setShiftstart1(bool ishiftstart1)
{
	shiftstart1 = ishiftstart1;
}
bool TShowCmdSpecWindows::getShiftstart1(void)
{
	return shiftstart1;
}
void TShowCmdSpecWindows::setShiftstart2(bool ishiftstart2)
{
	shiftstart2 = ishiftstart2;
}
bool TShowCmdSpecWindows::getShiftstart2(void)
{
	return shiftstart2;
}
void TShowCmdSpecWindows::setShiftstart3(bool ishiftstart3)
{
	shiftstart3 = ishiftstart3;
}
bool TShowCmdSpecWindows::getShiftstart3(void)
{
	return shiftstart3;
}
void TShowCmdSpecWindows::setShiftstart4(bool ishiftstart4)
{
	shiftstart4 = ishiftstart4;
}
bool TShowCmdSpecWindows::getShiftstart4(void)
{
	return shiftstart4;
}
void TShowCmdSpecWindows::setShiftBIRPrintouts(bool ishiftbirprintouts)
{
	shiftbirprintouts = ishiftbirprintouts;
}
bool TShowCmdSpecWindows::getShiftBIRPrintouts(void)
{
	return shiftbirprintouts;
}
void TShowCmdSpecWindows::setDailyBIRPrintouts(bool idailybirprintouts)
{
	dailybirprintouts = idailybirprintouts;
}
bool TShowCmdSpecWindows::getDailyBIRPrintouts(void)
{
	return dailybirprintouts;
}
void TShowCmdSpecWindows::setTicketedDelivery(bool iticketeddelivery)
{
	ticketeddelivery = iticketeddelivery;
}
bool TShowCmdSpecWindows::getTicketedDelivery(void)
{
	return ticketeddelivery;
}
void TShowCmdSpecWindows::setTCTicketedDelivery(bool itcticketeddelivery)
{
	tcticketeddelivery = itcticketeddelivery;
}
bool TShowCmdSpecWindows::getTCTicketedDelivery(void)
{
	return tcticketeddelivery;
}
void TShowCmdSpecWindows::setTDCloseDayOfWeek(int itdclosedayofweek)
{
	tdclosedayofweek = itdclosedayofweek;
}
int TShowCmdSpecWindows::getTDCloseDayOfWeek(void)
{
	return tdclosedayofweek;
}
void TShowCmdSpecWindows::setDailyDelivery(int idailydelivery)
{
	dailydelivery = idailydelivery;
}
int TShowCmdSpecWindows::getDailyDelivery(void)
{
	return dailydelivery;
}
void TShowCmdSpecWindows::setWeeklyDelivery(int iweeklydelivery)
{
	weeklydelivery = iweeklydelivery;
}
int TShowCmdSpecWindows::getWeeklyDelivery(void)
{
	return weeklydelivery;
}
void TShowCmdSpecWindows::setPeriodicDelivery(int iperiodicdelivery)
{
	periodicdelivery = iperiodicdelivery;
}
int TShowCmdSpecWindows::getPeriodicDelivery(void)
{
	return periodicdelivery;
}
void TShowCmdSpecWindows::setDailyBookDelivery(int idailybookdelivery)
{
	dailydelivery = idailybookdelivery;
}
int TShowCmdSpecWindows::getDailyBookDelivery(void)
{
	return dailydelivery;
}
void TShowCmdSpecWindows::setWeeklyBookDelivery(int iweeklybookdelivery)
{
	weeklydelivery = iweeklybookdelivery;
}
int TShowCmdSpecWindows::getWeeklyBookDelivery(void)
{
	return weeklydelivery;
}
void TShowCmdSpecWindows::setPeriodicBookDelivery(int iperiodicbookdelivery)
{
	periodicdelivery = iperiodicbookdelivery;
}
int TShowCmdSpecWindows::getPeriodicBookDelivery(void)
{
	return periodicdelivery;
}
void TShowCmdSpecWindows::setDailyAnalysis(int idailyanalysis)
{
	dailydelivery = idailyanalysis;
}
int TShowCmdSpecWindows::getDailyAnalysis(void)
{
	return dailydelivery;
}
void TShowCmdSpecWindows::setWeeklyAnalysis(int iweeklyanalysis)
{
	weeklydelivery = iweeklyanalysis;
}
int TShowCmdSpecWindows::getWeeklyAnalysis(void)
{
	return weeklydelivery;
}
void TShowCmdSpecWindows::setPeriodicAnalysis(int iperiodicanalysis)
{
	periodicdelivery = iperiodicanalysis;
}
int TShowCmdSpecWindows::getPeriodicAnalysis(void)
{
	return periodicdelivery;
}
void TShowCmdSpecWindows::setTestNeededWarningFlag(bool itestneededwarningflag)
{
	testneededwarningflag = itestneededwarningflag;
}
bool TShowCmdSpecWindows::getTestNeededWarningFlag(void)
{
	return testneededwarningflag;
}
void TShowCmdSpecWindows::setDaysBeforeWarn(int idaysbeforewarn)
{
	daysbeforewarn = idaysbeforewarn;
}
int TShowCmdSpecWindows::getDaysBeforeWarn(void)
{
	return daysbeforewarn;
}
void TShowCmdSpecWindows::setDaysBeforeAlm(int idaysbeforealm)
{
	daysbeforealm = idaysbeforealm;
}
int TShowCmdSpecWindows::getDaysBeforeAlm(void)
{
	return daysbeforealm;
}
void TShowCmdSpecWindows::setPassLineTest(bool ipasslinetest)
{
	passlinetest = ipasslinetest;
}
bool TShowCmdSpecWindows::getPassLineTest(void)
{
	return passlinetest;
}
void TShowCmdSpecWindows::setRemotePrinterPageEject(bool iremoteprinterpageeject)
{
	remoteprinterpageeject = iremoteprinterpageeject;
}
bool TShowCmdSpecWindows::getRemotePrinterPageEject(void)
{
	return remoteprinterpageeject;
}
void TShowCmdSpecWindows::setPrintTC(bool iprinttc)
{
	printtc = iprinttc;
}
bool TShowCmdSpecWindows::getPrintTC(void)
{
	return printtc;
}
void TShowCmdSpecWindows::setTemperatureCompensation(float itempcomp)
{
	tempcomp = itempcomp;
}
float TShowCmdSpecWindows::getTemperatureCompensation(void)
{
	return tempcomp;
}
void TShowCmdSpecWindows::setTankerLoadReport(bool itankerloadreport)
{
	tankerloadreport = itankerloadreport;
}
bool TShowCmdSpecWindows::getTankerLoadReport(void)
{
	return tankerloadreport;
}
void TShowCmdSpecWindows::setStickHeightOffsetFlag(bool istickheightoffsetflag)
{
	stickheightoffsetflag = istickheightoffsetflag;
}
bool TShowCmdSpecWindows::getStickHeightOffsetFlag(void)
{
	return stickheightoffsetflag;
}
void TShowCmdSpecWindows::setHProtocolFormat(bool ihprotocolformat)
{
	hprotocolformat = ihprotocolformat;
}
bool TShowCmdSpecWindows::getHProtocolFormat(void)
{
	return hprotocolformat;
}
void TShowCmdSpecWindows::setPrecisionTestDuration(int iprectest)
{
	prectest = iprectest;
}
int TShowCmdSpecWindows::getPrecisionTestDuration(void)
{
	return prectest;
}
void TShowCmdSpecWindows::setPrecisionLineTestAutoConfirm02(bool ipreclinetestauto02)
{
	preclinetestauto02 = ipreclinetestauto02;
}
bool TShowCmdSpecWindows::getPrecisionLineTestAutoConfirm02(void)
{
	return preclinetestauto02;
}
void TShowCmdSpecWindows::setPrecisionLineTestAutoConfirm01(bool ipreclinetestauto01)
{
	preclinetestauto01 = ipreclinetestauto01;
}
bool TShowCmdSpecWindows::getPrecisionLineTestAutoConfirm01(void)
{
	return preclinetestauto01;
}
void TShowCmdSpecWindows::setDaylightSavingsTime(bool idaylightsavings)
{
	daylightsavings = idaylightsavings;
}
bool TShowCmdSpecWindows::getDaylightSavingsTime(void)
{
	return daylightsavings;
}
void TShowCmdSpecWindows::setDLStartMonth(int idlstartmonth)
{
	dlstartmonth = idlstartmonth;
}
int TShowCmdSpecWindows::getDLStartMonth(void)
{
	return dlstartmonth;
}
void TShowCmdSpecWindows::setDLStartWeekOfMonth(int idlstartweekofmonth)
{
	dlstartweekofmonth = idlstartweekofmonth;
}
int TShowCmdSpecWindows::getDLStartWeekOfMonth(void)
{
	return dlstartweekofmonth;
}
void TShowCmdSpecWindows::setDLStartDayOfWeek(int idlstartdayofweek)
{
	dlstartdayofweek = idlstartdayofweek;
}
int TShowCmdSpecWindows::getDLStartDayOfWeek(void)
{
	return dlstartdayofweek;
}
void TShowCmdSpecWindows::setDLStartHour(TDateTime idlstarthour)
{
	dlstarthour = idlstarthour;
}
TDateTime TShowCmdSpecWindows::getDLStartHour(void)
{
	return dlstarthour;
}
void TShowCmdSpecWindows::setDLEndMonth(int idlendmonth)
{
	dlendmonth = idlendmonth;
}
int TShowCmdSpecWindows::getDLEndMonth(void)
{
	return dlendmonth;
}
void TShowCmdSpecWindows::setDLEndWeekOfMonth(int idlendweekofmonth)
{
	dlendweekofmonth = idlendweekofmonth;
}
int TShowCmdSpecWindows::getDLEndWeekOfMonth(void)
{
	return dlendweekofmonth;
}
void TShowCmdSpecWindows::setDLEndDayOfWeek(int idlenddayofweek)
{
	dlenddayofweek = idlenddayofweek;
}
int TShowCmdSpecWindows::getDLEndDayOfWeek(void)
{
	return dlenddayofweek;
}
void TShowCmdSpecWindows::setDLEndHour(TDateTime idlendhour)
{
	dlendhour = idlendhour;
}
TDateTime TShowCmdSpecWindows::getDLEndHour(void)
{
	return dlendhour;
}
void TShowCmdSpecWindows::setReDirectLocalPrintout(bool iredirectlocalpoflag)
{
	redirectlocalpoflag = iredirectlocalpoflag;
}
bool TShowCmdSpecWindows::getReDirectLocalPrintout(void)
{
	return redirectlocalpoflag;
}
void TShowCmdSpecWindows::setQPLDMonthlyPrintout(bool iqpldmonthlypoflag)
{
	qpldmonthlypoflag = iqpldmonthlypoflag;
}
bool TShowCmdSpecWindows::getQPLDMonthlyPrintout(void)
{
	return qpldmonthlypoflag;
}
void TShowCmdSpecWindows::setEuroProtocolPrefix(bool ieuroprotocolprefix)
{
	europrotocolprefix = ieuroprotocolprefix;
}
bool TShowCmdSpecWindows::getEuroProtocolPrefix(void)
{
	return europrotocolprefix;
}
void TShowCmdSpecWindows::setSystemSecurityCode(AnsiString isystemcode)
{
	systemcode = isystemcode;
}
AnsiString TShowCmdSpecWindows::getSystemSecurityCode(void)
{
	return systemcode;
}
void TShowCmdSpecWindows::setBaudRate(int ibaud)
{
	baud = ibaud;
}
int TShowCmdSpecWindows::getBaudRate(void)
{
	return baud;
}
void TShowCmdSpecWindows::setParity(int iparity)
{
	parity = iparity;
}
int TShowCmdSpecWindows::getParity(void)
{
	return parity;
}
void TShowCmdSpecWindows::setStopbit(int istopbit)
{
	stopbit = istopbit;
}
int TShowCmdSpecWindows::getStopbit(void)
{
	return stopbit;
}
void TShowCmdSpecWindows::setByteSize(int ibytesize)
{
	bytesize = ibytesize;
}
int TShowCmdSpecWindows::getByteSize(void)
{
	return bytesize;
}
void TShowCmdSpecWindows::setDialType(int idialtype)
{
	dialtype = idialtype;
}
int TShowCmdSpecWindows::getDialType(void)
{
	return dialtype;
}
void TShowCmdSpecWindows::setAnswerOn(int iansweron)
{
	answeron = iansweron;
}
int TShowCmdSpecWindows::getAnswerOn(void)
{
	return answeron;
}
void TShowCmdSpecWindows::setModemType(int imodemtype)
{
	modemtype = imodemtype;
}
int TShowCmdSpecWindows::getModemType(void)
{
	return modemtype;
}
void TShowCmdSpecWindows::setDialToneInterval(int idialtoneinterval)
{
	dialtoneinterval = idialtoneinterval;
}
int TShowCmdSpecWindows::getDialToneInterval(void)
{
	return dialtoneinterval;
}
void TShowCmdSpecWindows::setDTRNormalState(int idtrnormalstate)
{
	dtrnormalstate = idtrnormalstate;
}
int TShowCmdSpecWindows::getDTRNormalState(void)
{
	return dtrnormalstate;
}
void TShowCmdSpecWindows::setSystemCode(AnsiString isyscode)
{
	syscode = isyscode;
}
AnsiString TShowCmdSpecWindows::getSystemCode(void)
{
	return syscode;
}
void TShowCmdSpecWindows::setSetupString(AnsiString isetupstring)
{
	setupstring = isetupstring;
}
AnsiString TShowCmdSpecWindows::getSetupString(void)
{
	return setupstring;
}
void TShowCmdSpecWindows::setReceiverConfiguration(bool ireceiverconfig)
{
	receiverconfig = ireceiverconfig;
}
bool TShowCmdSpecWindows::getReceiverConfiguration(void)
{
	return receiverconfig;
}
void TShowCmdSpecWindows::setReceiverLocation(AnsiString ireceiverlocation)
{
	receiverlocation = ireceiverlocation;
}
AnsiString TShowCmdSpecWindows::getReceiverLocation(void)
{
	return receiverlocation;
}
void TShowCmdSpecWindows::setReceiverTelephoneNumber(AnsiString ireceivertelnumber)
{
	receivertelnumber = ireceivertelnumber;
}
AnsiString TShowCmdSpecWindows::getReceiverTelephoneNumber(void)
{
	return receivertelnumber;
}
void TShowCmdSpecWindows::setReceiverPortNumber(int ireceiverportnumber)
{
	receiverportnumber = ireceiverportnumber;
}
int TShowCmdSpecWindows::getReceiverPortNumber(void)
{
	return receiverportnumber;
}
void TShowCmdSpecWindows::setReceiverType(int ireceivertype)
{
	receivertype = ireceivertype;
}
int TShowCmdSpecWindows::getReceiverType(void)
{
	return receivertype;
}
void TShowCmdSpecWindows::setReceiverRetryNumber(int ireceiverretrynumber)
{
	receiverretrynumber = ireceiverretrynumber;
}
int TShowCmdSpecWindows::getReceiverRetryNumber(void)
{
	return receiverretrynumber;
}
void TShowCmdSpecWindows::setReceiverDelayTime(int ireceiverdelaytime)
{
	receiverdelaytime = ireceiverdelaytime;
}
int TShowCmdSpecWindows::getReceiverDelayTime(void)
{
	return receiverdelaytime;
}
void TShowCmdSpecWindows::setReceiverConfirmation(bool ireceiverconfirmation)
{
	receiverconfirmation = ireceiverconfirmation;
}
bool TShowCmdSpecWindows::getReceiverConfirmation(void)
{
	return receiverconfirmation;
}
void TShowCmdSpecWindows::setReportList(bool *ireportlist)
{
	for (int i=0; i < 19; i++)	reportlist[i] = ireportlist[i];
}
void TShowCmdSpecWindows::getReportList(bool* ireportlist)
{
	for (int i=0; i < 19; i++)	ireportlist[i] = reportlist[i];
}
void TShowCmdSpecWindows::setAutoDialMethod(bool iautodialmethod)
{
	autodialmethod = iautodialmethod;
}
bool TShowCmdSpecWindows::getAutoDialMethod(void)
{
	return autodialmethod;
}
void TShowCmdSpecWindows::setFrequencyType(int ifrequencytype)
{
	frequencytype = ifrequencytype;
}
int TShowCmdSpecWindows::getFrequencyType(void)
{
	return frequencytype;
}
void TShowCmdSpecWindows::setFrequencyDate(TDateTime ifreqdate)
{
	freqdate = ifreqdate;
}
TDateTime TShowCmdSpecWindows::getFrequencyDate(void)
{
	return freqdate;
}
void TShowCmdSpecWindows::setFrequencyTime(TDateTime ifreqtime)
{
	freqtime = ifreqtime;
}
TDateTime TShowCmdSpecWindows::getFrequencyTime(void)
{
	return freqtime;
}
void TShowCmdSpecWindows::setFrequencyMonth(int ifreqmonth)
{
	freqmonth = ifreqmonth;
}
int TShowCmdSpecWindows::getFrequencyMonth(void)
{
	return freqmonth;
}
void TShowCmdSpecWindows::setFrequencyWeek(int ifreqweek)
{
	freqweek = ifreqweek;
}
int TShowCmdSpecWindows::getFrequencyWeek(void)
{
	return freqweek;
}
void TShowCmdSpecWindows::setFrequencyDay(int ifreqday)
{
	freqday = ifreqday;
}
int TShowCmdSpecWindows::getFrequencyDay(void)
{
	return freqday;
}
void TShowCmdSpecWindows::setBIRend(bool ibirend)
{
	birend = ibirend;
}
bool TShowCmdSpecWindows::getBIRend(void)
{
	return birend;
}
/*void TShowCmdSpecWindows::setSystemAlarm(int *iSystemAlarm)
{
	for (int i=0; i < 18*2+1; i++)	SystemAlarm[i] = iSystemAlarm[i];
}
void TShowCmdSpecWindows::getSystemAlarm(int *iSystemAlarm)
{
	for (int i=0; i < 18*2+1; i++)	iSystemAlarm[i] = SystemAlarm[i];
}
void TShowCmdSpecWindows::setTankAlarm(int *iTankAlarm)
{
	for (int i=0; i < 29*2+1; i++)	TankAlarm[i] = iTankAlarm[i];
}
void TShowCmdSpecWindows::getTankAlarm(int *iTankAlarm)
{
	for (int i=0; i < 29*2+1; i++)	iTankAlarm[i] = TankAlarm[i];
}
void TShowCmdSpecWindows::setLiquidSensorAlarm(int *iLiquidSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	LiquidSensorAlarm[i] = iLiquidSensorAlarm[i];
}
void TShowCmdSpecWindows::getLiquidSensorAlarm(int *iLiquidSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	iLiquidSensorAlarm[i] = LiquidSensorAlarm[i];
}
void TShowCmdSpecWindows::setVaporSensorAlarm(int *iVaporSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	VaporSensorAlarm[i] = iVaporSensorAlarm[i];
}
void TShowCmdSpecWindows::getVaporSensorAlarm(int *iVaporSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	iVaporSensorAlarm[i] = VaporSensorAlarm[i];
}
void TShowCmdSpecWindows::setInputAlarm(int *iInputAlarm)
{
	for (int i=0; i < 3*2+1; i++)	InputAlarm[i] = iInputAlarm[i];
}
void TShowCmdSpecWindows::getInputAlarm(int *iInputAlarm)
{
	for (int i=0; i < 3*2+1; i++)	iInputAlarm[i] = InputAlarm[i];
}
void TShowCmdSpecWindows::setVolumetricLineLeakAlarm(int *iVolumetricLineLeakAlarm)
{
	for (int i=0; i < 28*2+1; i++)	VolumetricLineLeakAlarm[i] = iVolumetricLineLeakAlarm[i];
}
void TShowCmdSpecWindows::getVolumetricLineLeakAlarm(int *iVolumetricLineLeakAlarm)
{
	for (int i=0; i < 28*2+1; i++)	iVolumetricLineLeakAlarm[i] = VolumetricLineLeakAlarm[i];
}
void TShowCmdSpecWindows::setGroundwaterSensorAlarm(int *iGroundwaterSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	GroundwaterSensorAlarm[i] = iGroundwaterSensorAlarm[i];
}
void TShowCmdSpecWindows::getGroundwaterSensorAlarm(int *iGroundwaterSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	iGroundwaterSensorAlarm[i] = GroundwaterSensorAlarm[i];
}
void TShowCmdSpecWindows::setTypeASensorAlarm(int *iTypeASensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	TypeASensorAlarm[i] = iTypeASensorAlarm[i];
}
void TShowCmdSpecWindows::getTypeASensorAlarm(int *iTypeASensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	iTypeASensorAlarm[i] = TypeASensorAlarm[i];
}
void TShowCmdSpecWindows::setTypeBSensorAlarm(int *iTypeBSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	TypeBSensorAlarm[i] = iTypeBSensorAlarm[i];
}
void TShowCmdSpecWindows::getTypeBSensorAlarm(int *iTypeBSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	iTypeBSensorAlarm[i] = TypeBSensorAlarm[i];
}
void TShowCmdSpecWindows::setUniversalSensorAlarm(int *iUniversalSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	UniversalSensorAlarm[i] = iUniversalSensorAlarm[i];
}
void TShowCmdSpecWindows::getUniversalSensorAlarm(int *iUniversalSensorAlarm)
{
	for (int i=0; i < 9*2+1; i++)	iUniversalSensorAlarm[i] = UniversalSensorAlarm[i];
}
void TShowCmdSpecWindows::setAutoDialFaxAlarm(int *iAutoDialFaxAlarm)
{
	for (int i=0; i < 5*2+1; i++)	AutoDialFaxAlarm[i] = iAutoDialFaxAlarm[i];
}
void TShowCmdSpecWindows::getAutoDialFaxAlarm(int *iAutoDialFaxAlarm)
{
	for (int i=0; i < 5*2+1; i++)	iAutoDialFaxAlarm[i] = AutoDialFaxAlarm[i];
}
void TShowCmdSpecWindows::setMechanicalDispenserInterfaceAlarm(int *iMechanicalDispenserInterfaceAlarm)
{
	for (int i=0; i < 3*2+1; i++)	MechanicalDispenserInterfaceAlarm[i] = iMechanicalDispenserInterfaceAlarm[i];
}
void TShowCmdSpecWindows::getMechanicalDispenserInterfaceAlarm(int *iMechanicalDispenserInterfaceAlarm)
{
	for (int i=0; i < 3*2+1; i++)	iMechanicalDispenserInterfaceAlarm[i] = MechanicalDispenserInterfaceAlarm[i];
}
void TShowCmdSpecWindows::setElectronicDispenserInterfaceAlarm(int *iElectronicDispenserInterfaceAlarm)
{
	for (int i=0; i < 3*2+1; i++)	ElectronicDispenserInterfaceAlarm[i] = iElectronicDispenserInterfaceAlarm[i];
}
void TShowCmdSpecWindows::getElectronicDispenserInterfaceAlarm(int *iElectronicDispenserInterfaceAlarm)
{
	for (int i=0; i < 3*2+1; i++)	iElectronicDispenserInterfaceAlarm[i] = ElectronicDispenserInterfaceAlarm[i];
}
void TShowCmdSpecWindows::setProductAlarm(int *iProductAlarm)
{
	for (int i=0; i < 4*2+1; i++)	ProductAlarm[i] = iProductAlarm[i];
}
void TShowCmdSpecWindows::getProductAlarm(int *iProductAlarm)
{
	for (int i=0; i < 4*2+1; i++)	iProductAlarm[i] = ProductAlarm[i];
}
void TShowCmdSpecWindows::setPressureLineLeakAlarm(int *iPressureLineLeakAlarm)
{
	for (int i=0; i < 21*2+1; i++)	PressureLineLeakAlarm[i] = iPressureLineLeakAlarm[i];
}
void TShowCmdSpecWindows::getPressureLineLeakAlarm(int *iPressureLineLeakAlarm)
{
	for (int i=0; i < 21*2+1; i++)	iPressureLineLeakAlarm[i] = PressureLineLeakAlarm[i];
}
void TShowCmdSpecWindows::setWirelessPLLDAlarm(int *iWirelessPLLDAlarm)
{
	for (int i=0; i < 18*2+1; i++)	WirelessPLLDAlarm[i] = iWirelessPLLDAlarm[i];
}
void TShowCmdSpecWindows::getWirelessPLLDAlarm(int *iWirelessPLLDAlarm)
{
	for (int i=0; i < 18*2+1; i++)	iWirelessPLLDAlarm[i] = WirelessPLLDAlarm[i];
}*/
void TShowCmdSpecWindows::setRS232EOM(bool irs232eom)
{
	rs232eom = irs232eom;
}
bool TShowCmdSpecWindows::getRS232EOM(void)
{
	return rs232eom;
}
void TShowCmdSpecWindows::setTankConfiguration(bool *itankconfig)
{
	for (int i=0; i < 16; i++)	tankconfig[i] = itankconfig[i];
}
void TShowCmdSpecWindows::getTankConfiguration(bool* itankconfig)
{
	for (int i=0; i < 16; i++)	itankconfig[i] = tankconfig[i];
}
void TShowCmdSpecWindows::setProductLabel(AnsiString iproductlabel)
{
	productlabel = iproductlabel;
}
AnsiString TShowCmdSpecWindows::getProductLabel(void)
{
	return productlabel;
}
void TShowCmdSpecWindows::setProductCode(AnsiString iproductcode)
{
	productcode = iproductcode;
}
AnsiString TShowCmdSpecWindows::getProductCode(void)
{
	return productcode;
}
void TShowCmdSpecWindows::setProductThermalCoefficient(float iproducttermalcoeff)
{
	producttermalcoeff = iproducttermalcoeff;
}
float TShowCmdSpecWindows::getProductThermalCoefficient(void)
{
	return producttermalcoeff;
}
void TShowCmdSpecWindows::setTankDiameter(float itankdiameter)
{
	tankdiameter = itankdiameter;
}
float TShowCmdSpecWindows::getTankDiameter(void)
{
	return tankdiameter;
}
void TShowCmdSpecWindows::setMeterDataPresent(bool imeterdatapresent)
{
	meterdatapresent = imeterdatapresent;
}
bool TShowCmdSpecWindows::getMeterDataPresent(void)
{
	return meterdatapresent;
}
void TShowCmdSpecWindows::setEndFactor(int iendfactor)
{
	endfactor = iendfactor;
}
int TShowCmdSpecWindows::getEndFactor(void)
{
	return endfactor;
}
void TShowCmdSpecWindows::setEndValue(float iendvalue)
{
	endvalue = iendvalue;
}
float TShowCmdSpecWindows::getEndValue(void)
{
	return endvalue;
}
void TShowCmdSpecWindows::setCalibrationUpdate(int icalibrationupdate)
{
	calibrationupdate = icalibrationupdate;
}
int TShowCmdSpecWindows::getCalibrationUpdate(void)
{
	return calibrationupdate;
}
void TShowCmdSpecWindows::setFloatSize(int ifloatsize)
{
	floatsize = ifloatsize;
}
int TShowCmdSpecWindows::getFloatSize(void)
{
	return floatsize;
}
void TShowCmdSpecWindows::setWaterWarning(float iwaterwarning)
{
	waterwarning = iwaterwarning;
}
float TShowCmdSpecWindows::getWaterWarning(void)
{
	return waterwarning;
}
void TShowCmdSpecWindows::setHighWaterLimit(float ihighwaterlimit)
{
	highwaterlimit = ihighwaterlimit;
}
float TShowCmdSpecWindows::getHighWaterLimit(void)
{
	return highwaterlimit;
}
void TShowCmdSpecWindows::setMaxOrLabelVolume(int imaxorlabelvolume)
{
	maxorlabelvolume = imaxorlabelvolume;
}
int TShowCmdSpecWindows::getMaxOrLabelVolume(void)
{
	return maxorlabelvolume;
}
void TShowCmdSpecWindows::setOverfillLimit(int ioverfilllimit)
{
	overfilllimit = ioverfilllimit;
}
int TShowCmdSpecWindows::getOverfillLimit(void)
{
	return overfilllimit;
}
void TShowCmdSpecWindows::setHighProduct(int ihighproductlimit)
{
	highproductlimit = ihighproductlimit;
}
int TShowCmdSpecWindows::getHighProduct(void)
{
	return highproductlimit;
}
void TShowCmdSpecWindows::setDeliveryLimit(int ideliverylimit)
{
	deliverylimit = ideliverylimit;
}
int TShowCmdSpecWindows::getDeliveryLimit(void)
{
	return deliverylimit;
}
void TShowCmdSpecWindows::setLowProduct(int ilowproductlimit)
{
	lowproductlimit = ilowproductlimit;
}
int TShowCmdSpecWindows::getLowProduct(void)
{
	return lowproductlimit;
}
void TShowCmdSpecWindows::setLeakAlarmLimit(int ileakalarmlimit)
{
	leakalarmlimit = ileakalarmlimit;
}
int TShowCmdSpecWindows::getLeakAlarmLimit(void)
{
	return leakalarmlimit;
}
void TShowCmdSpecWindows::setSuddenLossLimit(int isuddenlosslimit)
{
	suddenlosslimit = isuddenlosslimit;
}
int TShowCmdSpecWindows::getSuddenLossLimit(void)
{
	return suddenlosslimit;
}
void TShowCmdSpecWindows::setTankTilt(float itanktilt)
{
	tanktilt = itanktilt;
}
float TShowCmdSpecWindows::getTankTilt(void)
{
	return tanktilt;
}
void TShowCmdSpecWindows::setProbeOffset(float iprobeoffset)
{
	probeoffset = iprobeoffset;
}
float TShowCmdSpecWindows::getProbeOffset(void)
{
	return probeoffset;
}
void TShowCmdSpecWindows::setManifoldedTanks(AnsiString imanifoldedtanks)
{
	manifoldedtanks = imanifoldedtanks;
}
AnsiString TShowCmdSpecWindows::getManifoldedTanks(void)
{
	return manifoldedtanks;
}
void TShowCmdSpecWindows::setLeakMinimumPeriodic(int ileakminimumperiodic)
{
	leakminimumperiodic = ileakminimumperiodic;
}
int TShowCmdSpecWindows::getLeakMinimumPeriodic(void)
{
	return leakminimumperiodic;
}
void TShowCmdSpecWindows::setLeakMinimumAnnual(int ileakminimumannual)
{
	leakminimumannual = ileakminimumannual;
}
int TShowCmdSpecWindows::getLeakMinimumAnnual(void)
{
	return leakminimumannual;
}
void TShowCmdSpecWindows::setPeriodicTestType(bool iperiodictesttype)
{
	periodictesttype = iperiodictesttype;
}
bool TShowCmdSpecWindows::getPeriodicTestType(void)
{
	return periodictesttype;
}
void TShowCmdSpecWindows::setAnnualTestFail(bool iannualtestfail)
{
	annualtestfail = iannualtestfail;
}
bool TShowCmdSpecWindows::getAnnualTestFail(void)
{
	return annualtestfail;
}
void TShowCmdSpecWindows::setPeriodicTestFail(bool iperiodictestfail)
{
	periodictestfail = iperiodictestfail;
}
bool TShowCmdSpecWindows::getPeriodicTestFail(void)
{
	return periodictestfail;
}
void TShowCmdSpecWindows::setGrossTestFail(bool igrosstestfail)
{
	grosstestfail = igrosstestfail;
}
bool TShowCmdSpecWindows::getGrossTestFail(void)
{
	return grosstestfail;
}
void TShowCmdSpecWindows::setAnnualTestAveraging(bool iannualtestaveraging)
{
	annualtestaveraging = iannualtestaveraging;
}
bool TShowCmdSpecWindows::getAnnualTestAveraging(void)
{
	return annualtestaveraging;
}
void TShowCmdSpecWindows::setPeriodicTestAveraging(bool iperiodictestaveraging)
{
	periodictestaveraging = iperiodictestaveraging;
}
bool TShowCmdSpecWindows::getPeriodicTestAveraging(void)
{
	return periodictestaveraging;
}
void TShowCmdSpecWindows::setLeakTestNotify(bool ileaktestnotify)
{
	leaktestnotify = ileaktestnotify;
}
bool TShowCmdSpecWindows::getLeakTestNotify(void)
{
	return leaktestnotify;
}
void TShowCmdSpecWindows::setSiphonBreak(bool isiphonbreak)
{
	siphonbreak = isiphonbreak;
}
bool TShowCmdSpecWindows::getSiphonBreak(void)
{
	return siphonbreak;
}
void TShowCmdSpecWindows::setStickOffset(float istickoffset)
{
	stickoffset = istickoffset;
}
float TShowCmdSpecWindows::getStickOffset(void)
{
	return stickoffset;
}
void TShowCmdSpecWindows::setHRMReconciliationWarnLimit(int ihrmreconcwarnlimit)
{
	hrmreconcwarnlimit = ihrmreconcwarnlimit;
}
int TShowCmdSpecWindows::getHRMReconciliationWarnLimit(void)
{
	return hrmreconcwarnlimit;
}
void TShowCmdSpecWindows::setHRMReconciliationAlarmLimit(int ihrmreconcalmlimit)
{
	hrmreconcalmlimit = ihrmreconcalmlimit;
}
int TShowCmdSpecWindows::getHRMReconciliationAlarmLimit(void)
{
	return hrmreconcalmlimit;
}
void TShowCmdSpecWindows::setDeliveryReportDelayTime(int ideliveryreportdt)
{
	deliveryreportdt = ideliveryreportdt;
}
int TShowCmdSpecWindows::getDeliveryReportDelayTime(void)
{
	return deliveryreportdt;
}
void TShowCmdSpecWindows::setPumpThreshold(float ipumpthreshold)
{
	pumpthreshold = ipumpthreshold;
}
float TShowCmdSpecWindows::getPumpThreshold(void)
{
	return pumpthreshold;
}
void TShowCmdSpecWindows::setTankProfile(AnsiString *itankprofile)
{
	for (int i=0; i < 20; i++)	tankprofile[i] = itankprofile[i];
}
void TShowCmdSpecWindows::getTankProfile(AnsiString *itankprofile)
{
	for (int i=0; i < 20; i++)
	{
    	try
		{
			itankprofile[i].sprintf("%06d", StrToInt(tankprofile[i]));
		}
		catch(EConvertError &e)
		{
			itankprofile[i].sprintf("%06d",0);
		}
	}
}
void TShowCmdSpecWindows::setTankProfileType(int itankprofiletype)
{
	tankprofiletype = itankprofiletype;
}
int TShowCmdSpecWindows::getTankProfileType(void)
{
	return tankprofiletype;
}
void TShowCmdSpecWindows::setMDIMString(AnsiString imdim_string)
{
	mdim_string = imdim_string;
}
AnsiString TShowCmdSpecWindows::getMDIMString(void)
{
	return mdim_string;
}
void TShowCmdSpecWindows::setEDIMString(AnsiString iedim_string)
{
	edim_string = iedim_string;
}
AnsiString TShowCmdSpecWindows::getEDIMString(void)
{
	return edim_string;
}
void TShowCmdSpecWindows::setDIMVersion(AnsiString idimversion)
{
	dimversion = idimversion;
}
AnsiString TShowCmdSpecWindows::getDIMVersion(void)
{
	return dimversion;
}
void TShowCmdSpecWindows::setAutoDailyClosing(TDateTime iautodailyclosing)
{
	autodailyclosing = iautodailyclosing;
}
TDateTime TShowCmdSpecWindows::getAutoDailyClosing(void)
{
	return autodailyclosing;
}
void TShowCmdSpecWindows::setShiftclosing1(bool ishiftclosing1)
{
	shiftclosing1 = ishiftclosing1;
}
bool TShowCmdSpecWindows::getShiftclosing1(void)
{
	return shiftclosing1;
}
void TShowCmdSpecWindows::setShiftclosing2(bool ishiftclosing2)
{
	shiftclosing2 = ishiftclosing2;
}
bool TShowCmdSpecWindows::getShiftclosing2(void)
{
	return shiftclosing2;
}
void TShowCmdSpecWindows::setShiftclosing3(bool ishiftclosing3)
{
	shiftclosing3 = ishiftclosing3;
}
bool TShowCmdSpecWindows::getShiftclosing3(void)
{
	return shiftclosing3;
}
void TShowCmdSpecWindows::setShiftclosing4(bool ishiftclosing4)
{
	shiftclosing4 = ishiftclosing4;
}
bool TShowCmdSpecWindows::getShiftclosing4(void)
{
	return shiftclosing4;
}
void TShowCmdSpecWindows::setPeriodicReconciliationMode(int iperiodicreconcmode)
{
	periodicreconcmode = iperiodicreconcmode;
}
int TShowCmdSpecWindows::getPeriodicReconciliationMode(void)
{
	return periodicreconcmode;
}
void TShowCmdSpecWindows::setPeriodicRecinciliationLength(int iperiodicreconclen)
{
	periodicreconclen = iperiodicreconclen;
}
int TShowCmdSpecWindows::getPeriodicReconciliationLength(void)
{
	return periodicreconclen;
}
void TShowCmdSpecWindows::setIsPerReconcAlm(int iperreconcalmonoff)
{
	perreconcalmonoff = iperreconcalmonoff;
}
int TShowCmdSpecWindows::getIsPerReconcAlm(void)
{
	return perreconcalmonoff;
}
void TShowCmdSpecWindows::setPerReconcAlmThreshold(float iperreconcalmthreshold)
{
	perreconcalmthreshold = iperreconcalmthreshold;
}
float TShowCmdSpecWindows::getPerReconcAlmThreshold(void)
{
	return perreconcalmthreshold;
}
void TShowCmdSpecWindows::setPerReconcAlmOffset(int iperreconcalmoffset)
{
	perreconcalmoffset = iperreconcalmoffset;
}
int TShowCmdSpecWindows::getPerReconcAlmOffset(void)
{
	return perreconcalmoffset;
}
void TShowCmdSpecWindows::setRemoteReportFormat(int iremotereportformat)
{
	remotereportformat = iremotereportformat;
}
int TShowCmdSpecWindows::getRemoteReportFormat(void)
{
	return remotereportformat;
}
void TShowCmdSpecWindows::setTempCompensation(bool itempcompensation)
{
	tempcompensation = itempcompensation;
}
bool TShowCmdSpecWindows::getTempCompensation(void)
{
	return tempcompensation;
}
void TShowCmdSpecWindows::setMeterCalibrationOffset(float imetercaliboffset)
{
	metercaliboffset = imetercaliboffset;
}
float TShowCmdSpecWindows::getMeterCalibrationOffset(void)
{
	return metercaliboffset;
}
void TShowCmdSpecWindows::setBusType(int ibustype)
{
	bustype = ibustype;
}
int TShowCmdSpecWindows::getBusType(void)
{
	return bustype;
}
void TShowCmdSpecWindows::setSlotNumber(int islotnr)
{
	slotnr = islotnr;
}
int TShowCmdSpecWindows::getSlotNumber(void)
{
	return slotnr;
}
void TShowCmdSpecWindows::setFuelPosition(int ifuelpos)
{
	fuelpos = ifuelpos;
}
int TShowCmdSpecWindows::getFuelPosition(void)
{
	return fuelpos;
}
void TShowCmdSpecWindows::setMeter(int imeter)
{
	meter = imeter;
}
int TShowCmdSpecWindows::getMeter(void)
{
	return meter;
}
void TShowCmdSpecWindows::setTankNumber(int itanknr)
{
	tanknr = itanknr;
}
int TShowCmdSpecWindows::getTankNumber(void)
{
	return tanknr;
}
void TShowCmdSpecWindows::setLiquidSensorConfiguration(bool *iliquidsensconfig)
{
	for (int i=0; i < 32; i++)	liquidsensconfig[i] = iliquidsensconfig[i];
}
void TShowCmdSpecWindows::getLiquidSensorConfiguration(bool *iliquidsensconfig)
{
	for (int i=0; i < 32; i++)	iliquidsensconfig[i] = liquidsensconfig[i];
}
void TShowCmdSpecWindows::setLiquidSensorLocation(AnsiString iliqsenslocation)
{
	liqsenslocation = iliqsenslocation;
}
AnsiString TShowCmdSpecWindows::getLiquidSensorLocation(void)
{
	return liqsenslocation;
}
void TShowCmdSpecWindows::setLiquidSensorType(int iliqsenstype)
{
	liqsenstype = iliqsenstype;
}
int TShowCmdSpecWindows::getLiquidSensorType(void)
{
	return liqsenstype;
}
void TShowCmdSpecWindows::setLiquidSensorCategory(int iliqsenscategory)
{
	liqsenscategory = iliqsenscategory;
}
int TShowCmdSpecWindows::getLiquidSensorCategory(void)
{
	return liqsenscategory;
}
void TShowCmdSpecWindows::setVaporSensorConfiguration(bool *ivaporsensconfig)
{
	for (int i=0; i < 20; i++)	vaporsensconfig[i] = ivaporsensconfig[i];
}
void TShowCmdSpecWindows::getVaporSensorConfiguration(bool *ivaporsensconfig)
{
	for (int i=0; i < 20; i++)	ivaporsensconfig[i] = vaporsensconfig[i];
}
void TShowCmdSpecWindows::setVaporSensorLocation(AnsiString ivaporsenslocation)
{
	vaporsenslocation = ivaporsenslocation;
}
AnsiString TShowCmdSpecWindows::getVaporSensorLocation(void)
{
	return vaporsenslocation;
}
void TShowCmdSpecWindows::setVaporSensorThreshold(int ivaporsensthreshold)
{
	vaporsensthreshold = ivaporsensthreshold;
}
int TShowCmdSpecWindows::getVaporSensorThreshold(void)
{
	return vaporsensthreshold;
}
void TShowCmdSpecWindows::setVaporSensorCategory(int ivaporsenscategory)
{
	vaporsenscategory = ivaporsenscategory;
}
int TShowCmdSpecWindows::getVaporSensorCategory(void)
{
	return vaporsenscategory;
}
void TShowCmdSpecWindows::setGroundWaterSensorConfiguration(bool *igrdwsensconfig)
{
	for (int i=0; i < 20; i++)	grdwsensconfig[i] = igrdwsensconfig[i];
}
void TShowCmdSpecWindows::getGroundWaterSensorConfiguration(bool *igrdwsensconfig)
{
	for (int i=0; i < 20; i++)	igrdwsensconfig[i] = grdwsensconfig[i];
}
void TShowCmdSpecWindows::setGroundWaterSensorLocation(AnsiString igrdwsenslocation)
{
	grdwsenslocation = igrdwsenslocation;
}
AnsiString TShowCmdSpecWindows::getGroundWaterSensorLocation(void)
{
	return grdwsenslocation;
}
void TShowCmdSpecWindows::setGroundWaterSensorCategory(int igrdwsenscategory)
{
	grdwsenscategory = igrdwsenscategory;
}
int TShowCmdSpecWindows::getGroundWaterSensorCategory(void)
{
	return grdwsenscategory;
}
void TShowCmdSpecWindows::setExternalInputConfiguration(bool *iextinputconfig)
{
	for (int i=0; i < 8; i++)	extinputconfig[i] = iextinputconfig[i];
}
void TShowCmdSpecWindows::getExternalInputConfiguration(bool *iextinputconfig)
{
	for (int i=0; i < 8; i++)	iextinputconfig[i] = extinputconfig[i];
}
void TShowCmdSpecWindows::setExternalInputName(AnsiString iextinputname)
{
	extinputname = iextinputname;
}
AnsiString TShowCmdSpecWindows::getExternalInputName(void)
{
	return extinputname;
}
void TShowCmdSpecWindows::setExternalInputType(int iextinputtype)
{
	extinputtype = iextinputtype;
}
int TShowCmdSpecWindows::getExternalInputType(void)
{
	return extinputtype;
}
void TShowCmdSpecWindows::setExternalInputSwitchType(int iextinputswitchtype)
{
	extinputswitchtype = iextinputswitchtype;
}
int TShowCmdSpecWindows::getExternalInputSwitchType(void)
{
	return extinputswitchtype;
}
void TShowCmdSpecWindows::setExternalInputTankNumber(int iextinputtanknr)
{
	extinputtanknr = iextinputtanknr;
}
int TShowCmdSpecWindows::getExternalInputTankNumber(void)
{
	return extinputtanknr;
}
void TShowCmdSpecWindows::setExternalInputDispenseMode(int iextinputdispensemode)
{
	extinputdispensemode = iextinputdispensemode;
}
int TShowCmdSpecWindows::setExternalInputDispenseMode(void)
{
	return extinputdispensemode;
}
void TShowCmdSpecWindows::setRelayConfiguration(bool *irelayconfig)
{
	for (int i=0; i < 16; i++)	relayconfig[i] = irelayconfig[i];
}
void TShowCmdSpecWindows::getRelayConfiguration(bool *irelayconfig)
{
	for (int i=0; i < 16; i++)	irelayconfig[i] = relayconfig[i];
}
void TShowCmdSpecWindows::setRelayDesignation(AnsiString irelaydesignation)
{
	relaydesignation = irelaydesignation;
}
AnsiString TShowCmdSpecWindows::getRelayDesignation(void)
{
	return relaydesignation;
}
void TShowCmdSpecWindows::setRelayType(int irelaytype)
{
	relaytype = irelaytype;
}
int TShowCmdSpecWindows::getRelayType(void)
{
	return relaytype;
}
void TShowCmdSpecWindows::setRelayOrientation(int irelayorientation)
{
	relayorientation = irelayorientation;
}
int TShowCmdSpecWindows::getRelayOrientation(void)
{
	return relayorientation;
}
void TShowCmdSpecWindows::setRelayTankNumber(int irelaytanknr)
{
	relaytanknr = irelaytanknr;
}
int TShowCmdSpecWindows::getRelayTankNumber(void)
{
	return relaytanknr;
}
