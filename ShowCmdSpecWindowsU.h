//---------------------------------------------------------------------------

#ifndef ShowCmdSpecWindowsUH
#define ShowCmdSpecWindowsUH

#include <vcl.h>
#include "handleIni.h"
#include "GeneralDlgW.h"
//---------------------------------------------------------------------------

/* note: check the CNT_XXX values because if it's less than the string count in
   the *.lng language file will come 'list index out of bounds' error
   (see the thandleini::StringListLoading() function) */
#define	STR_GETNUMBERDIALOG				"getnumberdialog"
#define	CNT_GETNUMBERDIALOG				4
#define	STR_SYSTEMUNITANDLANG			"setsystemtypeandsetup"
#define	CNT_SYSTEMUNITANDLANG			17
#define	STR_SYSTEMDATETIMEFORMAT		"setsystemdatetimeformat"
#define	CNT_SYSTEMDATETIMEFORMAT		10
#define	STR_TIMEOFDAY					"settimeofday"
#define	CNT_TIMEOFDAY					10
#define	STR_SETPRINTHEADERLINE			"setprintheaderline"
#define	CNT_SETPRINTHEADERLINE			7
#define	STR_SETSHIFTSTARTTIME			"setshiftstarttime"
#define	CNT_SETSHIFTSTARTTIME			7
#define	STR_SETSHIFTBIRPRINTOUTS		"setshiftbirprintouts"
#define	CNT_SETSHIFTBIRPRINTOUTS		4
#define	STR_SETDAILYBIRPRINTOUTS		"setdailybirprintouts"
#define	CNT_SETDAILYBIRPRINTOUTS		4
#define	STR_SETTICKETEDDELIVERY			"setticketeddelivery"
#define	CNT_SETTICKETEDDELIVERY			4
#define	STR_SETTCTICKETEDDELIVERY		"settcticketeddelivery"
#define	CNT_SETTCTICKETEDDELIVERY		4
#define	STR_SETTDCLOSEDAYOFWEEK			"settdclosedayofweek"
#define	CNT_SETTDCLOSEDAYOFWEEK			11
#define	STR_SETDELIVERYVARIANCEFLAG		"setdeliveryvarianceflag"
#define	CNT_SETDELIVERYVARIANCEFLAG		6
#define	STR_SETDELIVERYBOOKVARIANCEFLAG	"setdeliverybookvarianceflag"
#define	CNT_SETDELIVERYBOOKVARIANCEFLAG	6
#define	STR_SETVARIANCEANALYSISFLAG		"setvarianceanalysisflag"
#define	CNT_SETVARIANCEANALYSISFLAG		6
#define	STR_SETPERIODICTEST				"setperiodictest"
#define	CNT_SETPERIODICTEST				6
#define	STR_SETANNUALTEST				"setannualtest"
#define	CNT_SETANNUALTEST				6
#define	STR_SETLINEREENABLEMETHOD		"setlinereenablemethod"
#define	CNT_SETLINEREENABLEMETHOD		6
#define	STR_SETLINEPERIODICTEST			"setlineperiodictest"
#define	CNT_SETLINEPERIODICTEST			6
#define	STR_SETLINEANNUALTEST			"setlineannualtest"
#define	CNT_SETLINEANNUALTEST			6
#define	STR_REMOTEPRINTERPAGEEJECT		"setremoteprinterpageeject"
#define	CNT_REMOTEPRINTERPAGEEJECT		4
#define	STR_SETPRINTTC					"setprinttc"
#define	CNT_SETPRINTTC					4
#define	STR_SETTEMPERATURECOMPENSATION	"settemperaturecompensation"
#define	CNT_SETTEMPERATURECOMPENSATION	4
#define	STR_SETTANKERLOADREPORT			"settankerloadreport"
#define	CNT_SETTANKERLOADREPORT			4
#define	STR_SETSTICKHEIGHTOFFSET		"setstickheightoffsetflag"
#define	CNT_SETSTICKHEIGHTOFFSET		4
#define	STR_SETHPROTOCOLDATAFORMAT		"sethprotocoldataformat"
#define	CNT_SETHPROTOCOLDATAFORMAT		5
#define	STR_SETPRECTESTDURATION			"setprectestduration"
#define	CNT_SETPRECTESTDURATION			4
#define	STR_SET02LINETESTAUTOCONFIRM	"set02linetestautoconfirm"
#define	CNT_SET02LINETESTAUTOCONFIRM	4
#define	STR_SET01LINETESTAUTOCONFIRM	"set01linetestautoconfirm"
#define	CNT_SET01LINETESTAUTOCONFIRM	4
#define	STR_DAYLIGHTSAVINGSTIME			"setdaylightsavingstime"
#define	CNT_DAYLIGHTSAVINGSTIME			14
#define	STR_SETREDIRECTLOCALPRINTOUT	"setredirectlocalprintout"
#define	CNT_SETREDIRECTLOCALPRINTOUT	4
#define	STR_SETQPLDMONTHLYPRINTOUT		"setqpldmonthlyprintout"
#define	CNT_SETQPLDMONTHLYPRINTOUT		4
#define	STR_SETEUROPROTOCOLPREFIX		"seteuroprotocolprefix"
#define	CNT_SETEUROPROTOCOLPREFIX		5
#define	STR_SYSTEMCODE					"setsystemcode"
#define	CNT_SYSTEMCODE					4
#define	STR_PORTSETTINGS				"portsettings"
#define	CNT_PORTSETTINGS				33
#define	STR_PHONEDIRECTORYSETUP			"phonedirectorysetup"
#define	CNT_PHONEDIRECTORYSETUP			15
#define	STR_AUTODIALSETUP				"autodialsetup"
#define	CNT_AUTODIALSETUP				47
//#define	STR_SETAUTODIALONALARMS			"setautodialonalarms"
//#define	CNT_SETAUTODIALONALARMS			154
#define	STR_SETRS232ENDOFMESSAGE		"setrs232endofmessage"
#define	CNT_SETRS232ENDOFMESSAGE		5
#define	STR_SETTANKCONFIGURATION		"settankconfiguration"
#define	CNT_SETTANKCONFIGURATION		19
#define	STR_INTANKSETTINGS				"intanksettings"
#define	CNT_INTANKSETTINGS				55
#define	STR_TANKPROFILE					"tankprofile"
#define	CNT_TANKPROFILE					11
#define	STR_DISPENSERMODULE				"dispensermodule"
#define	CNT_DISPENSERMODULE				6
#define	STR_AUTODAILYCLOSING			"autodailyclosing"
#define	CNT_AUTODAILYCLOSING			4
#define	STR_SETAUTOSHIFTCLOSINGTIME		"setautoshiftclosingtime"
#define	CNT_SETAUTOSHIFTCLOSINGTIME		7
#define	STR_SETPERIODICRECONCMODE		"setperiodicreconcmode"
#define	CNT_SETPERIODICRECONCMODE		6
#define	STR_SETPERIODICRECONCALARM		"setperiodicreconcalarm"
#define	CNT_SETPERIODICRECONCALARM		6
#define	STR_SETREMOTEREPORTFORMAT		"setremotereportformat"
#define	CNT_SETREMOTEREPORTFORMAT		5
#define	STR_SETTEMPCOMPESATION			"settempcomensation"
#define	CNT_SETTEMPCOMPESATION			5
#define	STR_METERCALIBOFFSET			"metercaliboffset"
#define	CNT_METERCALIBOFFSET			4
#define	STR_MODIFYTANKMETERMAP			"modifytankmetermap"
#define	CNT_MODIFYTANKMETERMAP			9
#define	STR_SETLIQUIDSENSCONFIGURATION 	"setliquidsensconfiguration"
#define	CNT_SETLIQUIDSENSCONFIGURATION	35
#define	STR_SETLIQUIDSENSOR				"setliquidsensor"
#define	CNT_SETLIQUIDSENSOR				18
#define	STR_SETVAPORSENSCONFIGURATION	"setvaporsensconfiguration"
#define	CNT_SETVAPORSENSCONFIGURATION	23
#define	STR_SETVAPORSENSOR				"setvaporsensor"
#define	CNT_SETVAPORSENSOR				12
#define	STR_SETGRDWSENSCONFIGURATION	"setgrdwsensconfiguration"
#define	CNT_SETGRDWSENSCONFIGURATION	23
#define	STR_SETGRDWSETUP				"setgrdwsetup"
#define	CNT_SETGRDWSETUP				11
#define	STR_SETEXTINPUTCONFIGURATION	"setextinputconfiguration"
#define	CNT_SETEXTINPUTCONFIGURATION	11
#define	STR_SETEXTINPUTSETUP			"setextinputsetup"
#define	CNT_SETEXTINPUTSETUP			17
#define	STR_SETRELAYCONFIGURATION		"setrelayconfiguration"
#define	CNT_SETRELAYCONFIGURATION		19
#define	STR_SETRELAYSETUP				"setrelaysetup"
#define	CNT_SETRELAYSETUP				12
#define	STR_ARCHIVING					"archiving"
#define	CNT_ARCHIVING					4

class TShowCmdSpecWindows
{
private:
	bool cancel_from_dialog;

	int devicenumber;
	int language_index;
	int unit_index;
	int date_time_format_index;
	TTime time;
	TDateTime date;
	AnsiString header1, header2, header3, header4;
	bool shiftstart1, shiftstart2, shiftstart3, shiftstart4;
	TDateTime shifttime1, shifttime2, shifttime3, shifttime4;
	TDateTimePicker *st1, *st2, *st3, *st4;
	bool shiftbirprintouts;
	bool dailybirprintouts;
	bool ticketeddelivery;
	bool tcticketeddelivery;
	int tdclosedayofweek;
	bool dailydelivery, weeklydelivery, periodicdelivery;
	bool dailybookdelivery, weeklybookdelivery, periodicbookdelivery;
	bool dailyanalysis, weeklyanalysis, periodicanalysis;
	bool testneededwarningflag;
	int daysbeforewarn, daysbeforealm;
	bool passlinetest;
	bool remoteprinterpageeject;
	bool printtc;
	TEdit *tc_e;
	float tempcomp;
	bool tankerloadreport;
	bool stickheightoffsetflag;
	bool hprotocolformat;
	int prectest;
	bool preclinetestauto02, preclinetestauto01;
	bool daylightsavings;
	int dlstartmonth, dlstartweekofmonth, dlstartdayofweek;
	TDateTime dlstarthour;
	int dlendmonth, dlendweekofmonth, dlenddayofweek;
	TDateTime dlendhour;
	bool redirectlocalpoflag;
	bool qpldmonthlypoflag;
	bool europrotocolprefix;
	AnsiString systemcode;
	int baud, parity, stopbit, bytesize, dialtype, answeron, modemtype,
	dialtoneinterval, dtrnormalstate;
	AnsiString syscode, setupstring;
	bool receiverconfig;
	AnsiString receiverlocation;
	AnsiString receivertelnumber;
	int receiverportnumber;
	int receivertype;
	int receiverretrynumber;
	int receiverdelaytime;
	bool receiverconfirmation;
	bool reportlist[19];
	bool autodialmethod;
	int frequencytype;
	TDateTime freqdate;
	TDateTime freqtime;
	int freqmonth;
	int freqweek;
	int freqday;
	bool birend;
	/*int SystemAlarm[18*2+1];
	int TankAlarm[29*2+1];
	int LiquidSensorAlarm[9*2+1];
	int VaporSensorAlarm[9*2+1];
	int InputAlarm[3*2+1];
	int VolumetricLineLeakAlarm[28*2+1];
	int GroundwaterSensorAlarm[9*2+1];
	int TypeASensorAlarm[9*2+1];
	int TypeBSensorAlarm[9*2+1];
	int UniversalSensorAlarm[9*2+1];
	int AutoDialFaxAlarm[5*2+1];
	int MechanicalDispenserInterfaceAlarm[3*2+1];
	int ElectronicDispenserInterfaceAlarm[3*2+1];
	int ProductAlarm[4*2+1];
	int PressureLineLeakAlarm[21*2+1];
	int WirelessPLLDAlarm[18*2+1];*/
	bool rs232eom;
	bool tankconfig[16];
	AnsiString productlabel;
	AnsiString productcode;
	TEdit *thermalcoeff_e;
	float producttermalcoeff;
	TEdit *tdiam_e;
	float tankdiameter;
	bool meterdatapresent;
	TLabel *endf_l;
	TComboBox *endf_cb;
	TLabel *endv_l;
	TEdit *endv_e;
	TUpDown *endv_ud;
	int endfactor;
	float endvalue;
	TLabel *cupd_l;
	TComboBox *cupd_cb;
	int calibrationupdate;
	int floatsize;
	TEdit *watw_e;
	float waterwarning;
	TEdit *hwatl_e;
	float highwaterlimit;
	int maxorlabelvolume;
	TEdit *morlv_e;
	int overfilllimit;
	int highproductlimit;
	int deliverylimit;
	TEdit *lproductl_e;
	int lowproductlimit;
	int leakalarmlimit;
	int suddenlosslimit;
	TEdit *suddenll_e;
	float tanktilt;
	TEdit *tankt_e;
	float probeoffset;
	TEdit *probeofs_e;
	AnsiString manifoldedtanks;
	int leakminimumperiodic;
	int leakminimumannual;
	bool periodictesttype;
	bool annualtestfail;
	bool periodictestfail;
	bool grosstestfail;
	bool annualtestaveraging;
	bool periodictestaveraging;
	bool leaktestnotify;
	bool siphonbreak;
	float stickoffset;
	TEdit *stickofs_e;
	int hrmreconcwarnlimit;
	int hrmreconcalmlimit;
	int deliveryreportdt;
	float pumpthreshold;
	TEdit *pmpth_e;
	AnsiString tankprofile[20];
	int tankprofiletype;
	AnsiString mdim_string;
	AnsiString edim_string;
	AnsiString dimversion;
	TDateTime autodailyclosing;
	bool shiftclosing1, shiftclosing2, shiftclosing3, shiftclosing4;
	int periodicreconcmode;
	int periodicreconclen;
	int perreconcalmonoff;
	float perreconcalmthreshold;
	int perreconcalmoffset;
	TEdit *prath_e;
	int remotereportformat;
	bool tempcompensation;
	float metercaliboffset;
	TEdit *mcalibofs_e;
	int bustype, slotnr, fuelpos, meter, tanknr;
	bool liquidsensconfig[32];
	AnsiString liqsenslocation;
	int liqsenstype;
	int liqsenscategory;
	bool vaporsensconfig[20];
	AnsiString vaporsenslocation;
	int vaporsensthreshold;
	int vaporsenscategory;
	bool grdwsensconfig[20];
	AnsiString grdwsenslocation;
	int grdwsenscategory;
	bool extinputconfig[8];
	AnsiString extinputname;
	int extinputtype;
	int extinputswitchtype;
	int extinputtanknr;
	int extinputdispensemode;
	bool relayconfig[16];
	AnsiString relaydesignation;
	int relaytype;
	int relayorientation;
	int relaytanknr;

	THandleIni *ini;
	TLabel* __fastcall CreateLabel(TGenDlgW *dlg, int left,
		int top, int width, int height, AnsiString caption, TLabel *l);
	TLabel* __fastcall CreateLabel(TGroupBox *par, int left,
		int top, int width, int height, AnsiString caption, TLabel *l);
	TComboBox* __fastcall CreateComboBox(TGenDlgW *dlg, int left,
		int top, int width, int height, AnsiString text, int itemidx,
		TComboBox *cb);
	TDateTimePicker* __fastcall CreateDateTimePicker(TGenDlgW *dlg, int left,
		int top, int width, int height, AnsiString format, TDateTime datetime,
		TDateTimeKind kind, TDateTimePicker *dtp);
	TDateTimePicker* __fastcall CreateDateTimePicker(TGroupBox *par, int left,
		int top, int width, int height, AnsiString format, TDateTime datetime,
		TDateTimeKind kind, TDateTimePicker *dtp);
	TEdit* __fastcall CreateEdit(TGenDlgW *dlg, int left, int top, int width,
		int height, AnsiString text, int maxlen, TEdit *e);
	TEdit* __fastcall CreateEdit(TGroupBox *par, int left, int top, int width,
		int height, AnsiString text, int maxlen, TEdit *e);
	TCheckBox* __fastcall CreateCheckBox(TGenDlgW *dlg, int left, int top,
		int width, int height, AnsiString caption, bool checked, int tag,
		TCheckBox *cb);
	TCheckBox* __fastcall CreateCheckBox(TGroupBox *par, int left, int top,
		int width, int height, AnsiString caption, bool checked, int tag,
		TCheckBox *cb);
	TUpDown* __fastcall CreateUpDown(TGenDlgW *dlg, int left, int top,
		int width, int height, int min, int max, int pos, TWinControl *edit,
		TUpDown *ud);
	TUpDown* __fastcall CreateUpDown(TGroupBox *par, int left, int top,
		int width, int height, int min, int max, int pos, TWinControl *edit,
		TUpDown *ud);
	TGroupBox* __fastcall CreateGroupBox(TGenDlgW *dlg, int left, int top,
		int width, int height, AnsiString caption,	TGroupBox *gb);
	TGroupBox* __fastcall CreateGroupBox(TGroupBox *par, int left, int top,
		int width, int height, AnsiString caption,	TGroupBox *gb);
	TRadioButton* __fastcall CreateRadioButton(TGenDlgW *dlg, int left, int top,
		int width, int height, AnsiString caption, bool checked,
		TRadioButton *rb);
	TRadioButton* __fastcall CreateRadioButton(TGroupBox *par, int left, int top,
		int width, int height, AnsiString caption, bool checked,
		TRadioButton *rb);
	TMemo* __fastcall CreateMemo(TGenDlgW *dlg, int left, int top, int width,
		int height, AnsiString caption, TMemo *m);
	TMemo* __fastcall CreateMemo(TGroupBox *par, int left, int top, int width,
		int height, AnsiString caption, TMemo *m);
	TGenDlgW* __fastcall InitDialog(TStringList *l, char *str, int cnt,
		int caption, int okbtncap, int cancelbtncap, TGenDlgW *dlg);
	void __fastcall ShowSystemLanguageAndUnit(void);
	void __fastcall ShowSystemDateTimeDisplayFormat(void);
	void __fastcall ShowTimeOfDay(void);
	void __fastcall ShowPrintHeaderLines(void);
	void __fastcall ShowShiftStartTimes(void);
	void __fastcall ShowShiftBIRPrintouts(void);
	void __fastcall ShowDailyBIRPrintouts(void);
	void __fastcall ShowTicketedDelivery(void);
	void __fastcall ShowTCTicketedDelivery(void);
	void __fastcall ShowTDCloseDayOfWeek(void);
	void __fastcall ShowVariance(char *sec, int cnt);
	void __fastcall ShowTestNeededWarnings(char *sec, int cnt);
	void __fastcall ShowLineReEnableMethod(void);
	void __fastcall ShowRemotePrinterPageEject(void);
	void __fastcall ShowPrintTC(void);
	void __fastcall ShowTemperatureCompensation(void);
	void __fastcall ShowTankerLoadReport(void);
	void __fastcall ShowStickHeightOffsetFlag(void);
	void __fastcall ShowHProtocolDataFormat(void);
	void __fastcall ShowPrecisionTestDuration(void);
	void __fastcall ShowPrecisionLineTestAutoConfirm02(void);
	void __fastcall ShowPrecisionLineTestAutoConfirm01(void);
	void __fastcall ShowDaylightSavingsTime(void);
	void __fastcall ShowReDirectLocalPrintout(void);
	void __fastcall ShowQPLDMonthlyPrintout(void);
	void __fastcall ShowEuroProtocolPrefix(void);
	void __fastcall ShowSystemSecurityCode(void);
	void __fastcall ShowPortSettings(void);
	void __fastcall ShowPhoneDirectorySetup(void);
	void __fastcall ShowAutodialSetup(void);
	void __fastcall ShowAutodialOnAlarms(void);
	void __fastcall ShowRS232EOM(void);
	void __fastcall ShowTankConfiguration(void);
	void __fastcall ShowInTankSetup(void);
	void __fastcall ShowTankProfile(void);
	void __fastcall ShowDIMString(void);
	void __fastcall ShowAutodailyClosing(void);
	void __fastcall ShowAutoShiftClosingTimes(void);
	void __fastcall ShowPeriodicreconciliationMode(void);
	void __fastcall ShowPeriodicReconciliationAlarm(void);
	void __fastcall ShowRemoteReportFormat(void);
	void __fastcall ShowTempCompensation(void);
	void __fastcall ShowMeterCalibrationOffset(void);
	void __fastcall ShowModifyTankMeterMap(void);
	void __fastcall ShowLiquidSensorConfiguration(void);
	void __fastcall ShowLiquidSensorSetup(void);
	void __fastcall ShowVaporSensorConfiguration(void);
	void __fastcall ShowVaporSensorSetup(void);
	void __fastcall ShowGroundWaterSensorConfiguration(void);
	void __fastcall ShowGroundWaterSensorSetup(void);
	void __fastcall ShowExternalInputConfiguration(void);
	void __fastcall ShowExternalInputSetup(void);
	void __fastcall ShowRelayConfiguration(void);
	void __fastcall ShowRelaySetup(void);
	void __fastcall ShowArchiveUtility(void);

	void __fastcall ShiftStartTimeOnClick(TObject *Sender);
	void __fastcall meterdp_cbClick(TObject *Sender);
	void __fastcall tempcomp_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall thermalcoeff_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall tankdiam_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall waterw_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall hwaterl_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall prath_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall mcalibofs_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall maxorlv_eChange(TObject *Sender);
	void __fastcall tanktilt_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall probeoffset_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall stickoffset_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall pumpth_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall maxorlv_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall lproductl_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall suddenll_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall producttc_eChange(TObject *Sender);
	void __fastcall tankdiam_eChange(TObject *Sender);
	void __fastcall waterw_eChange(TObject *Sender);
	void __fastcall hwaterl_eChange(TObject *Sender);
	void __fastcall tanktilt_eChange(TObject *Sender);
	void __fastcall probeoffset_eChange(TObject *Sender);
	void __fastcall stickoffset_eChange(TObject *Sender);
	void __fastcall pumpth_eChange(TObject *Sender);
	void __fastcall prath_eChange(TObject *Sender);
	void __fastcall mcalibofs_eChange(TObject *Sender);
	void __fastcall lproductl_eChange(TObject *Sender);
	void __fastcall suddenll_eChange(TObject *Sender);
	void __fastcall endval_udClick(TObject *Sender, TUDBtnType Button);
	void __fastcall endfact_cbClick(TObject *Sender);
public:
	AnsiString language;
	AnsiString languagepath;

	enum dialog_types
		{
			dlg_systemlanguageandunit = 0,
			dlg_systemdatetimedisplayformat,
			dlg_timeofday,
			dlg_printheaderlines,
			dlg_shiftstarttimes,
			dlg_shiftbirprintouts,
			dlg_dailybirprintouts,
			dlg_ticketeddelivery,
			dlg_tcticketeddelivery,
			dlg_tdclosedayofweek,
			dlg_deliveryvariance,
			dlg_deliverybookvariance,
			dlg_varianceanalysis,
			dlg_periodictestneededwarn,
			dlg_annualtestneededwarn,
			dlg_linereenablemethod,
			dlg_lineperiodictestneededwarn,
			dlg_lineannualtestneededwarn,
			dlg_remoteprinterpageeject,
			dlg_printtc,
			dlg_tempcomp,
			dlg_tankerloadreport,
			dlg_stickheightoffsetflag,
			dlg_hprotocoldataformat,
			dlg_prectestduration,
			dlg_preclinetestauto02,
			dlg_preclinetestauto01,
			dlg_daylightsavingstime,
			dlg_redirectlocalpo,
			dlg_qpldmonthlypo,
			dlg_europrotocolprefix,
			dlg_systemcode,
			dlg_portsettings,
			dlg_phonedirectory,
			dlg_autodialsetup,
			dlg_autodialonalarms,
			dlg_rs232eom,
			dlg_tankconfig,
			dlg_intanksetup,
			dlg_tankprofile,
			dlg_dimstring,
			dlg_autodailyclosing,
			dlg_shiftclosingtimes,
			dlg_periodicreconcmode,
			dlg_perreconcalm,
			dlg_remotereportformat,
			dlg_tempcompensation,
			dlg_metercaliboffset,
			dlg_modifytankmetermap,
			dlg_liquidsensorconfig,
			dlg_liqsenssetup,
			dlg_vaporsensconfig,
			dlg_vaporsenssetup,
			dlg_grdwsensconfig,
			dlg_gdrwsenssetup,
			dlg_extinputconfig,
			dlg_extinputsetup,
			dlg_relayconfig,
			dlg_relaysetup,
        	dlg_archive
		};

	TGenDlgW *GeneralDialog;

	TShowCmdSpecWindows(void);
	~TShowCmdSpecWindows(void);

	void ShowDialogWindow(dialog_types dt);
	TForm* getDialogPointer(void);
	bool getModalResult(void); 
	void __fastcall ShowGetNumber(void);

	void setDeviceNumber(int idevicenumber);
	int getDeviceNumber(void);
	void setLanguageIndex(int ilanguage_index);
	int getLanguageIndex(void);
	void setUnitIndex(int iunit_index);
	int getUnitIndex(void);
	void setDateTimeFormatIndex(int idate_time_format_index);
	int getDateTimeFormatIndex(void);
	void setDate(TDateTime idate);
	TDateTime getDate(void);
	void setTime(TDateTime itime);
	TDateTime getTime(void);
	void setHeader1(AnsiString iheader1);
	AnsiString getHeader1(void);
	void setHeader2(AnsiString iheader2);
	AnsiString getHeader2(void);
	void setHeader3(AnsiString iheader3);
	AnsiString getHeader3(void);
	void setHeader4(AnsiString iheader4);
	AnsiString getHeader4(void);
	void setShifttime1(AnsiString iShifttime1);
	TDateTime getShifttime1(void);
	void setShifttime2(AnsiString iShifttime2);
	TDateTime getShifttime2(void);
	void setShifttime3(AnsiString iShifttime3);
	TDateTime getShifttime3(void);
	void setShifttime4(AnsiString iShifttime4);
	TDateTime getShifttime4(void);
	void setShiftstart1(bool iShiftstart1);
	bool getShiftstart1(void);
	void setShiftstart2(bool iShiftstart2);
	bool getShiftstart2(void);
	void setShiftstart3(bool iShiftstart3);
	bool getShiftstart3(void);
	void setShiftstart4(bool iShiftstart4);
	bool getShiftstart4(void);
	void setShiftBIRPrintouts(bool ishiftbirprintouts);
	bool getShiftBIRPrintouts(void);
	void setDailyBIRPrintouts(bool idailybirprintouts);
	bool getDailyBIRPrintouts(void);
	void setTicketedDelivery(bool iticketeddelivery);
	bool getTicketedDelivery(void);
	void setTCTicketedDelivery(bool itcticketeddelivery);
	bool getTCTicketedDelivery(void);
	void setTDCloseDayOfWeek(int itdclosedayofweek);
	int getTDCloseDayOfWeek(void);
	void setDailyDelivery(int idailydelivery);
	int getDailyDelivery(void);
	void setWeeklyDelivery(int iweeklydelivery);
	int getWeeklyDelivery(void);
	void setPeriodicDelivery(int iperiodicdelivery);
	int getPeriodicDelivery(void);
	void setDailyBookDelivery(int idailybookdelivery);
	int getDailyBookDelivery(void);
	void setWeeklyBookDelivery(int iweeklybookdelivery);
	int getWeeklyBookDelivery(void);
	void setPeriodicBookDelivery(int iperiodicbookdelivery);
	int getPeriodicBookDelivery(void);
	void setDailyAnalysis(int idailyanalysis);
	int getDailyAnalysis(void);
	void setWeeklyAnalysis(int iweeklyanalysis);
	int getWeeklyAnalysis(void);
	void setPeriodicAnalysis(int iperiodicanalysis);
	int getPeriodicAnalysis(void);
	void setTestNeededWarningFlag(bool itestneededwarningflag);
	bool getTestNeededWarningFlag(void);
	void setDaysBeforeWarn(int idaysbeforewarn);
	int getDaysBeforeWarn(void);
	void setDaysBeforeAlm(int idaysbeforealm);
	int getDaysBeforeAlm(void);
	void setPassLineTest(bool ipasslinetest);
	bool getPassLineTest(void);
	void setRemotePrinterPageEject(bool iremoteprinterpageeject);
	bool getRemotePrinterPageEject(void);
	void setPrintTC(bool iprinttc);
	bool getPrintTC(void);
	void setTemperatureCompensation(float itempcomp);
	float getTemperatureCompensation(void);
	void setTankerLoadReport(bool itankerloadreport);
	bool getTankerLoadReport(void);
	void setStickHeightOffsetFlag(bool istickheightoffsetflag);
	bool getStickHeightOffsetFlag(void);
	void setHProtocolFormat(bool ihprotocolformat);
	bool getHProtocolFormat(void);
	void setPrecisionTestDuration(int iprectest);
	int getPrecisionTestDuration(void);
	void setPrecisionLineTestAutoConfirm02(bool ipreclinetestauto02);
	bool getPrecisionLineTestAutoConfirm02(void);
	void setPrecisionLineTestAutoConfirm01(bool ipreclinetestauto1);
	bool getPrecisionLineTestAutoConfirm01(void);
	void setDaylightSavingsTime(bool idaylightsavings);
	bool getDaylightSavingsTime(void);
	void setDLStartMonth(int idlstartmonth);
	int getDLStartMonth(void);
	void setDLStartWeekOfMonth(int idlstartweekofmonth);
	int getDLStartWeekOfMonth(void);
	void setDLStartDayOfWeek(int idlstartdayofweek);
	int getDLStartDayOfWeek(void);
	void setDLStartHour(TDateTime idlstarthour);
	TDateTime getDLStartHour(void);
	void setDLEndMonth(int idlendmonth);
	int getDLEndMonth(void);
	void setDLEndWeekOfMonth(int idlendweekofmonth);
	int getDLEndWeekOfMonth(void);
	void setDLEndDayOfWeek(int idlenddayofweek);
	int getDLEndDayOfWeek(void);
	void setDLEndHour(TDateTime idlendhour);
	TDateTime getDLEndHour(void);
	void setReDirectLocalPrintout(bool iredirectlocalpoflag);
	bool getReDirectLocalPrintout(void);
	void setQPLDMonthlyPrintout(bool iqpldmonthlypoflag);
	bool getQPLDMonthlyPrintout(void);
	void setEuroProtocolPrefix(bool ieuroprotocolprefix);
	bool getEuroProtocolPrefix(void);
	void setSystemSecurityCode(AnsiString isystemcode);
	AnsiString getSystemSecurityCode(void);
	void setBaudRate(int ibaud);
	int getBaudRate(void);
	void setParity(int iparity);
	int getParity(void);
	void setStopbit(int istopbit);
	int getStopbit(void);
	void setByteSize(int ibytesize);
	int getByteSize(void);
	void setDialType(int idialtype);
	int getDialType(void);
	void setAnswerOn(int iansweron);
	int getAnswerOn(void);
	void setModemType(int imodemtype);
	int getModemType(void);
	void setDialToneInterval(int idialtoneinterval);
	int getDialToneInterval(void);
	void setDTRNormalState(int idtrnormalstate);
	int getDTRNormalState(void);
	void setSystemCode(AnsiString isyscode);
	AnsiString getSystemCode(void);
	void setSetupString(AnsiString isetupstring);
	AnsiString getSetupString(void);
	void setReceiverConfiguration(bool ireceiverconfig);
	bool getReceiverConfiguration(void);
	void setReceiverLocation(AnsiString ireceiverlocation);
	AnsiString getReceiverLocation(void);
	void setReceiverTelephoneNumber(AnsiString ireceivertelnumber);
	AnsiString getReceiverTelephoneNumber(void);
	void setReceiverPortNumber(int ireceiverportnumber);
	int getReceiverPortNumber(void);
	void setReceiverType(int ireceivertype);
	int getReceiverType(void);
	void setReceiverRetryNumber(int ireceiverretrynumber);
	int getReceiverRetryNumber(void);
	void setReceiverDelayTime(int ireceiverdelaytime);
	int getReceiverDelayTime(void);
	void setReceiverConfirmation(bool ireceiverconfirmation);
	bool getReceiverConfirmation(void);
	void setReportList(bool *ireportlist);
	void getReportList(bool* ireportlist);
	void setAutoDialMethod(bool iautodialmethod);
	bool getAutoDialMethod(void);
	void setFrequencyType(int ifrequencytype);
	int getFrequencyType(void);
	void setFrequencyDate(TDateTime ifreqdate);
	TDateTime getFrequencyDate(void);
	void setFrequencyTime(TDateTime ifreqtime);
	TDateTime getFrequencyTime(void);
	void setFrequencyMonth(int ifreqmonth);
	int getFrequencyMonth(void);
	void setFrequencyWeek(int ifreqweek);
	int getFrequencyWeek(void);
	void setFrequencyDay(int ifreqday);
	int getFrequencyDay(void);
	void setBIRend(bool ibirend);
	bool getBIRend(void);
	/*void setSystemAlarm(int *iSystemAlarm);
	void getSystemAlarm(int *iSystemAlarm);
	void setTankAlarm(int *iTankAlarm);
	void getTankAlarm(int *iTankAlarm);
	void setLiquidSensorAlarm(int *iLiquidSensorAlarm);
	void getLiquidSensorAlarm(int *iLiquidSensorAlarm);
	void setVaporSensorAlarm(int *iVaporSensorAlarm);
	void getVaporSensorAlarm(int *iVaporSensorAlarm);
	void setInputAlarm(int *iInputAlarm);
	void getInputAlarm(int *iInputAlarm);
	void setVolumetricLineLeakAlarm(int *iVolumetricLineLeakAlarm);
	void getVolumetricLineLeakAlarm(int *iVolumetricLineLeakAlarm);
	void setGroundwaterSensorAlarm(int *iGroundwaterSensorAlarm);
	void getGroundwaterSensorAlarm(int *iGroundwaterSensorAlarm);
	void setTypeASensorAlarm(int *iTypeASensorAlarm);
	void getTypeASensorAlarm(int *iTypeASensorAlarm);
	void setTypeBSensorAlarm(int *iTypeBSensorAlarm);
	void getTypeBSensorAlarm(int *iTypeBSensorAlarm);
	void setUniversalSensorAlarm(int *iUniversalSensorAlarm);
	void getUniversalSensorAlarm(int *iUniversalSensorAlarm);
	void setAutoDialFaxAlarm(int *iAutoDialFaxAlarm);
	void getAutoDialFaxAlarm(int *iAutoDialFaxAlarm);
	void setMechanicalDispenserInterfaceAlarm(int *iMechanicalDispenserInterfaceAlarm);
	void getMechanicalDispenserInterfaceAlarm(int *iMechanicalDispenserInterfaceAlarm);
	void setElectronicDispenserInterfaceAlarm(int *iElectronicDispenserInterfaceAlarm);
	void getElectronicDispenserInterfaceAlarm(int *iElectronicDispenserInterfaceAlarm);
	void setProductAlarm(int *iProductAlarm);
	void getProductAlarm(int *iProductAlarm);
	void setPressureLineLeakAlarm(int *iPressureLineLeakAlarm);
	void getPressureLineLeakAlarm(int *iPressureLineLeakAlarm);
	void setWirelessPLLDAlarm(int *iWirelessPLLDAlarm);
	void getWirelessPLLDAlarm(int *iWirelessPLLDAlarm);*/
	void setRS232EOM(bool irs232eom);
	bool getRS232EOM(void);
	void setTankConfiguration(bool *itankconfig);
	void getTankConfiguration(bool* itankconfig);
	void setProductLabel(AnsiString iproductlabel);
	AnsiString getProductLabel(void);
	void setProductCode(AnsiString iproductcode);
	AnsiString getProductCode(void);
	void setProductThermalCoefficient(float iproducttermalcoeff);
	float getProductThermalCoefficient(void);
	void setTankDiameter(float itankdiameter);
	float getTankDiameter(void);
	void setMeterDataPresent(bool imeterdatapresent);
	bool getMeterDataPresent(void);
	void setEndFactor(int iendfactor);
	int getEndFactor(void);
	void setEndValue(float iendvalue);
	float getEndValue(void);
	void setCalibrationUpdate(int icalibrationupdate);
	int getCalibrationUpdate(void);
	void setFloatSize(int ifloatsize);
	int getFloatSize(void);
	void setWaterWarning(float iwaterwarning);
	float getWaterWarning(void);
	void setHighWaterLimit(float ihighwaterlimit);
	float getHighWaterLimit(void);
	void setMaxOrLabelVolume(int imaxorlabelvolume);
	int getMaxOrLabelVolume(void);
	void setOverfillLimit(int ioverfilllimit);
	int getOverfillLimit(void);
	void setHighProduct(int ihighproductlimit);
	int getHighProduct(void);
	void setDeliveryLimit(int ideliverylimit);
	int getDeliveryLimit(void);
	void setLowProduct(int ilowproductlimit);
	int getLowProduct(void);
	void setLeakAlarmLimit(int ileakalarmlimit);
	int getLeakAlarmLimit(void);
	void setSuddenLossLimit(int isuddenlosslimit);
	int getSuddenLossLimit(void);
	void setTankTilt(float itanktilt);
	float getTankTilt(void);
	void setProbeOffset(float iprobeoffset);
	float getProbeOffset(void);
	void setManifoldedTanks(AnsiString imanifoldedtanks);
	AnsiString getManifoldedTanks(void);
	void setLeakMinimumPeriodic(int ileakminimumperiodic);
	int getLeakMinimumPeriodic(void);
	void setLeakMinimumAnnual(int ileakminimumannual);
	int getLeakMinimumAnnual(void);
	void setPeriodicTestType(bool iperiodictesttype);
	bool getPeriodicTestType(void);
	void setAnnualTestFail(bool iannualtestfail);
	bool getAnnualTestFail(void);
	void setPeriodicTestFail(bool iperiodictestfail);
	bool getPeriodicTestFail(void);
	void setGrossTestFail(bool igrosstestfail);
	bool getGrossTestFail(void);
	void setAnnualTestAveraging(bool iannualtestaveraging);
	bool getAnnualTestAveraging(void);
	void setPeriodicTestAveraging(bool iperiodictestaveraging);
	bool getPeriodicTestAveraging(void);
	void setLeakTestNotify(bool ileaktestnotify);
	bool getLeakTestNotify(void);
	void setSiphonBreak(bool isiphonbreak);
	bool getSiphonBreak(void);
	void setStickOffset(float istickoffset);
	float getStickOffset(void);
	void setHRMReconciliationWarnLimit(int ihrmreconcwarnlimit);
	int getHRMReconciliationWarnLimit(void);
	void setHRMReconciliationAlarmLimit(int ihrmreconcalmlimit);
	int getHRMReconciliationAlarmLimit(void);
	void setDeliveryReportDelayTime(int ideliveryreportdt);
	int getDeliveryReportDelayTime(void);
	void setPumpThreshold(float ipumpthreshold);
	float getPumpThreshold(void);
	void setTankProfile(AnsiString *itankprofile);
	void getTankProfile(AnsiString *itankprofile);
	void setTankProfileType(int itankprofiletype);
	int getTankProfileType(void);
	void setDIMVersion(AnsiString idimversion);
	AnsiString getDIMVersion(void);
	void setMDIMString(AnsiString imdim_string);
	AnsiString getMDIMString(void);
	void setEDIMString(AnsiString iedim_string);
	AnsiString getEDIMString(void);
	void setAutoDailyClosing(TDateTime iautodailyclosing);
	TDateTime getAutoDailyClosing(void);
	void setShiftclosing1(bool iShiftclosing1);
	bool getShiftclosing1(void);
	void setShiftclosing2(bool iShiftclosing2);
	bool getShiftclosing2(void);
	void setShiftclosing3(bool iShiftclosing3);
	bool getShiftclosing3(void);
	void setShiftclosing4(bool iShiftclosing4);
	bool getShiftclosing4(void);
	void setPeriodicReconciliationMode(int iperiodicreconcmode);
	int getPeriodicReconciliationMode(void);
	void setPeriodicRecinciliationLength(int iperiodicreconclen);
	int getPeriodicReconciliationLength(void);
	void setIsPerReconcAlm(int iperreconcalmonoff);
	int getIsPerReconcAlm(void);
	void setPerReconcAlmThreshold(float iperreconcalmthreshold);
	float getPerReconcAlmThreshold(void);
	void setPerReconcAlmOffset(int iperreconcalmoffset);
	int getPerReconcAlmOffset(void);
	void setRemoteReportFormat(int iremotereportformat);
	int getRemoteReportFormat(void);
	void setTempCompensation(bool itempcompensation);
	bool getTempCompensation(void);
	void setMeterCalibrationOffset(float imetercaliboffset);
	float getMeterCalibrationOffset(void);
	void setBusType(int ibustype);
	int getBusType(void);
	void setSlotNumber(int islotnr);
	int getSlotNumber(void);
	void setFuelPosition(int ifuelpos);
	int getFuelPosition(void);
	void setMeter(int imeter);
	int getMeter(void);
	void setTankNumber(int itanknr);
	int getTankNumber(void);
	void setLiquidSensorConfiguration(bool *iliquidsensconfig);
	void getLiquidSensorConfiguration(bool *iliquidsensconfig);
	void setLiquidSensorLocation(AnsiString iliqsenslocation);
	AnsiString getLiquidSensorLocation(void);
	void setLiquidSensorType(int iliqsenstype);
	int getLiquidSensorType(void);
	void setLiquidSensorCategory(int iliqsenscategory);
	int getLiquidSensorCategory(void);
	void setVaporSensorConfiguration(bool *ivaporsensconfig);
	void getVaporSensorConfiguration(bool *ivaporsensconfig);
	void setVaporSensorLocation(AnsiString ivaporsenslocation);
	AnsiString getVaporSensorLocation(void);
	void setVaporSensorThreshold(int ivaporsensthreshold);
	int getVaporSensorThreshold(void);
	void setVaporSensorCategory(int ivaporsenscategory);
	int getVaporSensorCategory(void);
	void setGroundWaterSensorConfiguration(bool *igrdwsensconfig);
	void getGroundWaterSensorConfiguration(bool *igrdwsensconfig);
	void setGroundWaterSensorLocation(AnsiString igrdwsenslocation);
	AnsiString getGroundWaterSensorLocation(void);
	void setGroundWaterSensorCategory(int igrdwsenscategory);
	int getGroundWaterSensorCategory(void);
	void setExternalInputConfiguration(bool *iextinputconfig);
	void getExternalInputConfiguration(bool *iextinputconfig);
	void setExternalInputName(AnsiString iextinputname);
	AnsiString getExternalInputName(void);
	void setExternalInputType(int iextinputtype);
	int getExternalInputType(void);
	void setExternalInputSwitchType(int iextinputswitchtype);
	int getExternalInputSwitchType(void);
	void setExternalInputTankNumber(int iextinputtanknr);
	int getExternalInputTankNumber(void);
	void setExternalInputDispenseMode(int iextinputdispensemode);
	int setExternalInputDispenseMode(void);
	void setRelayConfiguration(bool *irelayconfig);
	void getRelayConfiguration(bool *irelayconfig);
	void setRelayDesignation(AnsiString irelaydesignation);
	AnsiString getRelayDesignation(void);
	void setRelayType(int irelaytype);
	int getRelayType(void);
	void setRelayOrientation(int irelayorientation);
	int getRelayOrientation(void);
	void setRelayTankNumber(int irelaytanknr);
	int getRelayTankNumber(void);
};

#endif
