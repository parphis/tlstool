//---------------------------------------------------------------------------

#ifndef handleIniH
#define handleIniH
//---------------------------------------------------------------------------
#include <IniFiles.hpp>
#include <vcl.h>

/* module defines */
#define	MAIN_SECTION_NAME			"mainformcaption"
#define	MENU_SECTION_NAME			"mainmenu"
#define	GROUPBOX_SECTION_NAME		"maingroupbox"
#define	TOOLBUTTON_SECTION_NAME		"toolbarhints"
#define	PAGES_SECTION_NAME			"pages"
#define	PROGRAMOP_SECTION_NAME		"programoptions"
#define	PORTOP_SECTION_NAME			"portoptions"
#define	ABOUT_SECTION_NAME			"about"
#define	BACKUP_SECTION_NAME			"backup"
#define	BACKUP_PROCESS_SECTION_NAME	"backupprocess"
#define	SETUPGROUP_SECTION_NAME		"setupgroup"
#define	SYSTEMSETUP_SECTION_NAME	"systemsetup"
#define	COMMSETUP_SECTION_NAME		"commsetup"
#define	INTANKSETUP_SECTION_NAME	"intanksetup"
#define	FUELMAN_SECTION_NAME		"fuelmanagementsetup"
#define	INTANKLEAK_SECTION_NAME		"intankleaktestsetup"
#define	PRESSLEAK_SECTION_NAME		"pressurelineleaksetup"
#define	WPLLDLINELEAK_SECTION_NAME	"wplldlineleaksetup"
#define	LINELEAKDET_SECTION_NAME	"lineleakdetectorsetup"
#define	LINELEAK_SECTION_NAME		"lineleaktestsetup"
#define	LINELEAKLOCK_SECTION_NAME	"lineleaklockoutsetup"
#define	PUMPSENSOR_SECTION_NAME		"pumpsensorsetup"
#define	RECONCSETUP_SECTION_NAME	"reconciliationsetup"
#define	LIQUIDSENSOR_SECTION_NAME	"liquidsensorsetup"
#define	VAPORSENSOR_SECTION_NAME	"vaporsensorsetup"
#define	GRWATERSENSOR_SECTION_NAME	"groundwatersensorsetup"
#define	TWOWIRESENSOR_SECTION_NAME	"twowireclsensorsetup"
#define	THWIRESENSOR_SECTION_NAME	"threewireclsensorsetup"
#define	EXTERNALINPUT_SECTION_NAME	"externalinputsetup"
#define	OUTPUTRELAY_SECTION_NAME	"outputrelaysetup"
#define	PLLDLINEDIS_SECTION_NAME	"plldlinedisablesetup"
#define	WPLLDLINEDIS_SECTION_NAME	"wplldlinedisablesetup"
#define	LINEDIS_SECTION_NAME		"linedisablesetup"
#define	SMARTSENSOR_SECTION_NAME	"smartsensorsetup"
#define	ARCHIVE_SECTION_NAME		"archiveutility"
#define	SETUP_SECTION_COUNT_NAME	"count"
#define	REPORT_SECTION_NAME			"reports"
#define	MENU_ITEM_COUNT				14
#define	TOOLBUTTON_COUNT			6
#define	PAGES_COUNT					6
#define	SETUPRADIO_COUNT			24
#define	GROUPBOX_COUNT				1
#define	MAIN_FORM_NAME				"MainForm"
#define	REPORT_FORM_NAME			"ReportsW"
#define	ERRORSTRING_SECTION			"errorstrings"

#define	STR_PROGRAMSETTINGS			"programsettings"
#define	STR_MAINSTATE				"MainWindowState"
#define	MIN_MAINSTATE				0
#define	MAX_MAINSTATE				100
#define	DEF_MAINSTATE				0
#define	STR_MAINWIDTH				"MainWindowWidth"
#define	MIN_MAINWIDTH				250
#define	MAX_MAINWIDTH				65535
#define	DEF_MAINWIDTH				598
#define	STR_MAINHEIGHT				"MainWidowHeight"
#define	MIN_MAINHEIGHT				150
#define	MAX_MAINHEIGHT				65535
#define	DEF_MAINHEIGHT				600
#define	STR_MAINLEFT				"MainWindowLeft"
#define	MIN_MAINLEFT				0
#define	MAX_MAINLEFT				1200
#define	DEF_MAINLEFT				100
#define	STR_MAINTOP					"MainWindowTop"
#define	MIN_MAINTOP					0
#define	MAX_MAINTOP					1200
#define	DEF_MAINTOP					100
#define	STR_MAINTOOLBAR				"DisplayMainToolbar"
#define	MIN_MAINTOOLBAR				0
#define	MAX_MAINTOOLBAR				1
#define	DEF_MAINTOOLBAR				1
#define	STR_SAVESETTINGS			"SaveSettings"
#define	MIN_SAVESETTINGS			0
#define	MAX_SAVESETTINGS			1
#define	DEF_SAVESETTINGS			1
#define	STR_DISPONSTART				"DisplayOnStartup"
#define	MIN_DISPONSTART				0
#define	MAX_DISPONSTART				1
#define	DEF_DISPONSTART				1
#define	STR_REPORTWIDTH				"ReportWindowWidth"
#define	MIN_REPORTWIDTH				400
#define	MAX_REPORTWIDTH				800
#define	DEF_REPORTWIDTH				600
#define	STR_REPORTHEIGHT			"ReportWindowHeight"
#define	MIN_REPORTHEIGHT			100
#define	MAX_REPORTHEIGHT			65535
#define	DEF_REPORTHEIGHT			317
#define	STR_REPORTLEFT				"ReportWindowLeft"
#define	MIN_REPORTLEFT				0
#define	MAX_REPORTLEFT				1200
#define	DEF_REPORTLEFT				698
#define	STR_REPORTTOP				"ReportWindowTop"
#define	MIN_REPORTTOP				0
#define	MAX_REPORTTOP				1200
#define	DEF_REPORTTOP				100
#define	STR_REPORTBKGCOLOR			"ReportWindowBackgroundColor"
#define	STR_REPORTFONTCOLOR			"ReportWindowFontColor"
#define	STR_LANGUAGEUSED			"LastUsedLanguage"
/* these names are the language names that are in the language file in language
   section; here need to add the new languages in own language (i.e.: slovák) */
#define	STR_ENGLISH					"english"
#define	STR_GERMAN					"deutsch"
#define	STR_HUNGARIAN				"magyar"
/*****/
#define	STR_LANGUAGEDIRECTORY		"LanguageDirectory"
#define	DEF_LANGUAGEDIRECTORY		"C:\\Program Files\\TLStool\\"
#define	STR_LANGUAGE_SECTION_NAME	"language"
#define	STR_LANGUAGE_NAME			"lang"

#define	STR_PORTSETTINGS			"portsettings"
#define	STR_PORTNAME				"PortName"
#define	STR_COM1					"COM1"
#define	STR_COM2					"COM2"
#define	STR_COM3					"COM3"
#define	STR_COM4					"COM4"
#define	STR_COM5					"COM5"
#define	STR_COM6					"COM6"
#define	STR_COM7					"COM7"
#define	STR_COM8					"COM8"
#define	STR_BAUDRATE				"BaudRate"
#define	MIN_BAUDRATE				1200
#define	MAX_BAUDRATE				57600
#define	DEF_BAUDRATE				2400
#define	STR_PARITY					"Parity"
#define	MIN_PARITY					0
#define	MAX_PARITY					4
#define	DEF_PARITY					1
#define	STR_STOPBIT					"Stopbit"
#define	MIN_STOPBIT					0
#define	MAX_STOPBIT					2
#define	DEF_STOPBIT					0
#define	STR_BYTESIZE				"ByteSize"
#define	MIN_BYTESIZE				5
#define	MAX_BYTESIZE				8
#define	DEF_BYTESIZE				7
#define	STR_READINTTOUT				"ReadIntervalTimeout"
#define	MIN_READINTTOUT				0
#define	MAX_READINTTOUT				10000
#define	DEF_READINTTOUT				10
#define	STR_READMULTITOUT			"ReadTotalTimeoutMultiplier"
#define	MIN_READMULTITOUT			0
#define	MAX_READMULTITOUT			10000
#define	DEF_READMULTITOUT			20
#define	STR_READCONSTTOUT			"ReadTotalTimeoutConstant"
#define	MIN_READCONSTTOUT			0
#define	MAX_READCONSTTOUT			10000
#define	DEF_READCONSTTOUT			100
#define	STR_WRITEMULTITOUT			"WriteTotalTimeoutMultiplier"
#define	MIN_WRITEMULTITOUT			0
#define	MAX_WRITEMULTITOUT			10000
#define	DEF_WRITEMULTITOUT			0
#define	STR_WRITECONSTTOUT			"WriteTotalTimeoutConstant"
#define	MIN_WRITECONSTTOUT			0
#define	MAX_WRITECONSTTOUT			10000
#define	DEF_WRITECONSTTOUT			0
#define	STR_WRITEREPETITION			"WriteRepetition"
#define	MIN_WRITEREPETITION			0
#define	MAX_WRITEREPETITION			1000
#define	DEF_WRITEREPETITION			10
#define	STR_READREPETITION			"ReadRepetition"
#define	MIN_READREPETITION			0
#define	MAX_READREPETITION			1000
#define	DEF_READREPETITION			10

#define	BACKUP_FILE_COMMAND_SECTION	"SETTINGS_TLS3XX"
#define	BACKUP_AUTHORNAME			"AUTHOR"
#define	BACKUP_DATETIME				"DATE_TIME"
#define	BACKUP_STATION				"SERVICE_STATION"
#define	BACKUP_DEVICEID				"DEVICE_ID"
#define	BACKUP_BACKUPDATE			"BACKUP"
#define	BACKUP_RESTOREDATE			"RESTORE"
#define	BACKUP_OTHERNOTES			"OTHER_NOTES"

class THandleIni
{
private:
	AnsiString language;
	AnsiString filename;
	TForm *form;
	TMenuItem **main_menu;
	TToolButton **tool_button_hints;
	TTabSheet **pages;
	TRadioGroup *setup_group;
	TGroupBox **groupboxes;

	AnsiString load_main_caption(AnsiString sec_str, TIniFile *i);
	void load_main_menu_strings(AnsiString sec_str, TIniFile *i);
	void load_tool_button_hints(AnsiString sec_str, TIniFile *i);
	void load_pages_caption(AnsiString sec_str, TIniFile *i);
	void load_radiogroup_captions(AnsiString sec_str, TIniFile *i,
		TRadioGroup *rg);
	void load_group_captions(AnsiString sec_str, TIniFile *i);
	AnsiString load_report_caption(AnsiString sec_str, TIniFile *i);
public:
	THandleIni(AnsiString ilanguage, AnsiString ifilename, TForm *iform,
		TMenuItem **imain_menu, TToolButton **itool_button_hints,
		TTabSheet **ipages, TRadioGroup *isetup_group, TGroupBox **igroupboxes);
	THandleIni(AnsiString ilanguage, AnsiString ifilename, TForm *iform);
	THandleIni(AnsiString ilanguage, AnsiString ifilename);
	THandleIni(AnsiString ifilename);
	~THandleIni(void);

	void setFileName(AnsiString ifilename);
	AnsiString getFileName(void);
	void setFormPointer(TForm *iform);
	TForm* getFormPointer(void);
	void LoadLanguage();
	void LoadReportLanguage(void);
	void SetupSubcategories(int inumber, TListBox *lb);
	void StringListLoading(TStringList *l, AnsiString section, int cnt);
	AnsiString getLanguageString(void);
	void setMainWindowState(int istate);
	int getMainWindowState(void);
	void setMainWindowWidth(int imainwidth);
	int getMainWindowWidth(void);
	void setMainWindowHeight(int imainheight);
	int getMainWindowHeight(void);
	void setMainWindowLeft(int imainleft);
	int getMainWindowLeft(void);
	void setMainWindowTop(int imaintop);
	int getMainWindowTop(void);
	void setMainToolbarVisibility(int ivisible);
	int getMainToolbarVisibility(void);
	void setSaveSettingsFlag(int isaveflag);
	int getSaveSettingsFlag(void);
	void setDisplayReportWindowOnStartUp(int idispreport);
	int getDisplayReportWindowOnStartUp(void);
	void setReportWindowWidth(int ireportwidth);
	int getReportWindowWidth(void);
	void setReportWindowHeight(int ireportheight);
	int getReportWindowHeight(void);
	void setReportWindowLeft(int ireportleft);
	int getReportWindowLeft(void);
	void setReportWindowTop(int ireporttop);
	int getReportWindowTop(void);
	void setReportWindowBackgroundColor(unsigned int ireportbkgcolor);
	unsigned int getReportWindowBackgroundColor(void);
	void setReportWindowFontColor(unsigned int ireportfontcolor);
	unsigned int getReportWindowFontColor(void);
	void setUsedLanguage(AnsiString iusedlang);
	AnsiString getUsedLanguage(void);
	void setLanguageDirectory(AnsiString ilangdirectory);
	AnsiString getLanguageDirectory(void);
	void setUsedPortName(AnsiString iportname);
	AnsiString getUsedPortName(void);
	void setUsedBaudRate(int ibaudrate);
	int getUsedBaudRate(void);
	void setUsedParity(int iparity);
	int getUsedParity(void);
	void setUsedStopbit(int istopbit);
	int getUsedStopbit(void);
	void setUsedByteSize(int ibytesize);
	int getUsedByteSize(void);
	void setUsedReadIntervalTimeout(int ireadint);
	int getUsedReadIntervalTimeout(void);
	void setUsedReadMultiplyTimeout(int ireadmulti);
	int getUsedReadMultiplyTimeout(void);
	void setUsedReadConstantTimeout(int ireadconst);
	int getUsedReadConstantTimeout(void);
	void setUsedWriteMultiplyTimeout(int iwritemulti);
	int getUsedWriteMultiplyTimeout(void);
	void setUsedWriteConstantTimeout(int iwriteconst);
	int getUsedWriteConstantTimeout(void);
	void setUsedWriteRepetition(int iwriterep);
	int getUsedWriteRepetition(void);
	void setUsedReadRepetition(int ireadrep);
	int getUsedReadRepetition(void);

	void writeCommand(AnsiString cmd_name, AnsiString cmd_str);
	AnsiString readCommand(AnsiString cmd_name);
	void writeBackupDetails(TStringList *l);
	void readBackupDetails(TStringList *l);

	AnsiString LoadErrorString(int nr);
};
#endif
