//---------------------------------------------------------------------------

#ifndef TLSDeviceH
#define TLSDeviceH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "cmds.h"
#include "tcommunication.h"
#include "msgstrs.h"
#include "handleIni.h"
#include "ShowCmdSpecWindowsU.h"
#include "ConvertMessageStrings.h"
#include "InprocessW.h"
#include "StandaloneCommand.h"
#include "BackupW.h"
#include "BackupProcessW.h"

/* module defines */
#define	STR_ANSWERSELECTOR				"====================================="

#define	CNT_MAX_COMMAND_ID				394

#define	COMMAND_LEN						7

class TTLSDevice
{
private:
	TShowCmdSpecWindows *ShowDialog;

	TCommunication *comm;
	THandleIni *ini;
	command_strings cmds;
	TStringList *cmd_str_list;
	TwInProcess *wProc;
	TList *standaloneList;
	TStandaloneCommand *sc;
	TwBackup *bkpWin;
	TwBackupProcess *bkpProcWin;

	int cmd_id_arr[CNT_MAX_COMMAND_ID];
	/* it takes that a user clicked on an OK or Cancel button on the dialog;
	   this is needed that if the user selects Cancel then do'nt display any
	   communication error on report window */
	bool cancel_from_dialog;
	/* it tells that the communication line status must write only first time
	   on the report window */
	bool first_time_run;
	/* it tells that the serial port is open or not */
	bool isPortOpened;

	void __fastcall copy_char(char src, char *dest, int pos);
	void __fastcall copy_char_ex(char src, char *dest, int pos, int cnt);
	void __fastcall copy_chars(char *src, int srcpos, char *dest, int pos,
		int cnt);
	void __fastcall init_show_dialog_window(int page_idx, int group_idx,
		int item_idx, TMemo *m);
	void __fastcall get_computer_format_answer(char *cmdstr, AnsiString param,
		int param_pos, TMemo *m);
	bool check_checksum(AnsiString str);
	void show_line_status(TMemo *m);
	AnsiString convert_date_time_string(AnsiString str);
	int send(char commandtype, char *cmdstr, int commandstring_len,
		int cmdtype_pos, AnsiString string_to_send, int string_to_send_first_pos,
		int string_to_send_start_pos, int string_to_send_len,
		char emptychar, int empty_first_pos, int empty_len);

	int showSetSystemTypeLanguageFlagsDlg(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetSystemDateTimeDisplayFormatDlg(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetTimeofday(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetPrintHeaderLine1234(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetShiftStartTime1234(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetBIRShiftPrintoutsFlagDlg(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetBIRDailyPrintoutsFlagDlg(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetTicketedDeliveryFlagEnableDlg(char cmd_type, int page_idx,
		int group_idx, int item_idx, TMemo *m);
	int showSetTicketedDeliveryTemperatureCompensationFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTicketedDeliveryCloseDayofWeekDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTicketedDeliveryVariancePrintoutFlagsDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTicketedDeliveryBookVariancePrintoutFlagsDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTicketedVarianceAnalysisPrintoutFlagsDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankPeriodicTestNeededWarningDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankAnnualTestNeededWarningDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetLineReEnableMethodDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetLinePeriodicTestNeededWarningDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetLineAnnualTestNeededWarningDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetRemotePrinterPageEjectFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetPrintTemperatureCompensationFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTemperatureCompensationValueDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankerLoadReportFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankStickHeightFunctionEnableDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetHProtocolHeightVolumeformatDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetPLLDWPLLDDurationBeforePrecisionRetestDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetPeriodicLineLeakTestAutoConfirmDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetAnnualLineLeakTestAutoConfirmDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetAutoDaylightSavingTimeDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetRedirectLocalPrintoutFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetHRMQPLDMonthlyPrintoutDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetEuroProtocolPrefixDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetSystemRS232SecurityCodeDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetCommunicationPortDataDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetReceiverConfigurationFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetReceiverReportListDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetReceiverAutoDialOnAlarmsDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetRS232EndofMessageDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankConfigurationDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankSetupDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetTankLinearCalculatedFullVolumeDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetMechanicalDispenserinterfaceStringDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetReconciliationAutoDailyClosingTimeDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetAutoShiftClosingTime1234(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetPeriodicReconciliationMode(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetPeriodicReconciliationAlarmFlag(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetRemotePrinterReconciliationReportFormat(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetBIRTemperatureCompensationFlag(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetMeterCalibrationOffset(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetBIRMeterTankmapping(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetLiquidSensorConfigurationDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetLiquidSensorSetupDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetVaporSensorConfigurationDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetVaporSensorSetupDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetGroundwaterSensorConfigurationDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showGroundWaterSensorSetupDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetInputConfiguration(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetInputSetupDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetRelayConfigurationDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showSetRelaySetupDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m);
	int showArchiveUtilityDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m, int id);
	void init_command_string_list_and_id_array(void);
	void init_command_strings(void);
	void read_comm_buffer_and_show_if_error(int res, TMemo *m);
	int create_command_id(int page_idx, int group_idx, int item_idx);
public:
	AnsiString language;
	AnsiString languagepath;

	TTLSDevice(void);
	TTLSDevice(char *portname);
	TTLSDevice(char *portname, char *filename);
	~TTLSDevice(void);

	void get(int page_idx, int group_idx, int item_idx, TMemo *disp,
		char cmd_type, char item_nr, char item_nrs[2]);
	void set(int page_idx, int group_idx, int item_idx, TMemo *disp,
		char cmd_type);
	void setPortProperties(int baud, int parity, int stopbit, int bytesize,
		int rint, int rmulti, int rconst, int wmulti, int wconst, int wrep,
		int rrep);
	void Backup(void);
	void Restore(void);
	bool getIsPortOpen(void);
	bool OpenSerialPort(char *portname);
	bool CloseSerialPort(void);
};

#endif
