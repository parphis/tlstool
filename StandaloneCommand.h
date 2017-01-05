//---------------------------------------------------------------------------

#ifndef StandaloneCommandH
#define StandaloneCommandH

#include "tcommunication.h"
#include "handleIni.h"
//---------------------------------------------------------------------------
#define	ANSWER_WITH_EMPTY_PARAM_LEN		7
#define	UNKNOWN_ANSWER_STRING_WITH_SOH	"9999FF1B"
#define	UNKNOWN_ANSWER_STRING			"9999FF1B"
#define	MAX_GETNUMBER					9

class TStandaloneCommand
{
private:
	TCommunication *comm;
	THandleIni *ini;
	AnsiString commandName;
	AnsiString commName;
	AnsiString fileName;
	AnsiString commandString;
	AnsiString formattedCmdString;
	AnsiString description;
	AnsiString errorType;
	AnsiString warningType;
	int errorCount;
	int warningCount;
	int position_in_backupfile;
	int commandType;
	int commandSubType;

	bool check_checksum(AnsiString str);
	AnsiString format_answer(AnsiString str, int type);
	int get_parameter_number_from_resource(AnsiString str);
	AnsiString get_answer(AnsiString str, bool bkp);
	AnsiString increment_parameter(AnsiString str);
	AnsiString get_command_name(AnsiString str);
	AnsiString get_commandstring(AnsiString str);
	AnsiString get_parameter(AnsiString str);
public:
	TStandaloneCommand(void);
	TStandaloneCommand(TCommunication *icomm,
					   THandleIni *iini,
					   AnsiString icommName,
					   AnsiString ifileName,
					   AnsiString icommandString,
					   AnsiString idescription);
	~TStandaloneCommand(void);

	void Backup(void);
	void Restore(void);

	AnsiString getErrorString(void);
	AnsiString getWarningString(void);

	void setCommandName(AnsiString icommandName);
	AnsiString getCommandName(void);
	void setErrorCount(int ierrorCount);
	int getErrorCount(void);
	void setWarningCount(int iwarningCount);
	int getWarningCount(void);
	void setPositionInBackupFile(int iposition_in_backupfile);
	int getPositionInBackupFile(void);
	void setFileName(AnsiString ifileName);
	AnsiString getFileName(void);
	void setDescription(AnsiString idescription);
	AnsiString getDescription(void);
};

#endif
