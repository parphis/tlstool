//---------------------------------------------------------------------------


#pragma hdrstop

#include "StandaloneCommand.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/* private */
bool TStandaloneCommand::check_checksum(AnsiString str)
{
	AnsiString tmp = str;
	AnsiString msg;
	int pos;
	int res;
	int msg_sum = 0;

	/* get the ascii-hexa formatting checksum number */
	pos = tmp.Pos('&');
	tmp.Delete(1, pos+1);
	tmp.Insert("0x", 1);

	/* try to convert the checksum-string to checksum-hexa */
	if (TryStrToInt(tmp.c_str(), res))
	{
		/* calculate the checksum */
		/* first step: negate the checksum */
		res = ~res;
		/* will positive 16 bit value */
		res = res ^ 0xFFFF0000;
		/* create string that need to sum (all characters after the parity bit
		   if parity is enabled); here should add the first <SOH> character to
		   it but without this is so good (2's complement?) */
		tmp = str;
		tmp.Delete(pos+2, tmp.Length());
		msg = tmp;

		/* the checksum of the received characters is the sum of the ascii
		   character in 8 bit binary representation */
		for (int i=1; i < msg.Length()+1; i++)
		{
			msg_sum += (int)msg[i];
		}
		/* checksum is goog if the
		   received checksum-calculated checksum = zero */
		return msg_sum - res;
	}
	/* if could not convert checksum is wrong */
	return true;
}

AnsiString TStandaloneCommand::format_answer(AnsiString str, int type)
{
	/* the device do'nt know the command => answer is 9999FF1B */
	if (CompareStr(str,UNKNOWN_ANSWER_STRING)==0)
	{
		warningCount++;
		warningType = "Az eszköz nem támogatja ezt a funkciót.";
		return str;
	}

	/* if connection to port is exists */
	if (str!="")
	{
		/* the beginning of the message char */
		char BOF[2] = {0x01,0x00};
		int str_len;
		int c_pos;

    	/* find th '&' char to determine the checksum section */
		c_pos = str.Pos("&");
		/* if no '&' char exists means perhaps checksum error */
		if (c_pos <= 0)
		{
			errorCount++;
			errorType = "Nincs ellenõrzõ érték.";
		}
		else
		{
			/* determine string length */
			str_len = str.Length();
			/* delete checksum from string */
			str.Delete(c_pos,str_len);
		}
		/* insert 's' char to the string in first position */
		str[1] = 's';
		/* insert 0x01 (<SOH>) char to the string in first position */
		str.Insert(BOF,1);

		/* command group where with parameter "00" come all information;
		   example format: i[ask type] CCC[command] 00[parameter: always "00"]
						   YYMMDDHHmm[date time stamp of get] [setting value(s)]
						   &&ChChChCh[checksum value] */
		if (type==0)
		{
        	/* delete following character count describer */
			if(commandSubType==1)	str.Delete(8,12);
			/* delete date time stamp from string */
			else	str.Delete(8,10);
		}
		else if (type==1)
		{
			if(commandSubType==1)
				str.Delete(8,10);
			else if(commandSubType==2)
				str.Delete(8,10);
			else if(commandSubType==3)
			{
				str.Delete(8,12);
				/* delete following character count describer */
				str.Delete(8,2);
			}
			else if(commandSubType==4)
			{
				/* get one more char what must send (cmd: 525) */
				str.Delete(8,13);
			}
			else if(commandSubType==5)
			{
				str.Delete(8,12);
				/* delete following character count describer */
            	str.Delete(8,4);
			}
			else if(commandSubType==6)
			{
				str.Delete(8,10);
				/* delete following character count describer (52F) */
				str.Delete(10,2);
			}
			else if(commandSubType==7)
			{
				str.Delete(8,12);
				/* delete following character count describer (680) */
				str.Delete(8,2);
				/* delete following character (product code) (680) */
				str.Delete(8,1);
			}
			else if(commandSubType==8)
			{
				str.Delete(8,10);
				/* delete following character count describer (75B) */
				str.Delete(10,7);
				/* delete following character (product code) (75B) */
				str.Delete(20,2);
			}
			else if(commandSubType==9)
			{
				str.Delete(8,12);
				/* delete following character count describer (52F) */
				str.Delete(8,2);
			}
			else	str.Delete(8,12);
		}
	}
	else
	{
    	/* answer is empty means no connection */
		errorCount++;
		errorType = "Nincs kapcsolat, vagy rossz a port beállítása.";
		return "";
	}

	return str;
}
int TStandaloneCommand::get_parameter_number_from_resource(AnsiString str)
{
	/* get the current parameter of the command string; it works only with
	   strings in the resource! */
	int res = 0;
	AnsiString par = "";

	if (str!="")
	{
		if (str.Length() >= 7)
		{
			par +=str[6];
			par += str[7];
		}
		else par = "00";

		try
		{
			res = StrToInt(par);
			if (str.Length() >= 8)
			{
				par = "";
				par += str[8];
				commandSubType = StrToInt(par);
			}
        	else commandSubType = 0;
		}
		catch(EConvertError &e)
		{
			res = 0;
        	commandSubType = 0;
		}
	}

	return res;
}

AnsiString TStandaloneCommand::get_answer(AnsiString str, bool bkp)
{
	/* end of message char; first u sends a string to the tls device than the
	   device answers for this message only if the length of the command string
	   is equal or more (>=) than it requiers. if u sends a string to it, an end
	   of message (0x0D) char is required at the end of the string; it tells the
	   device that this is the end of the parameter list of the command. */
	char EOM[2] = {0x0D,0x00};

	if (str=="")	return "";

	/* insert \r char to string and replace 'I' char to 'i' to get the computer
	   specific answer if bkp is true */
	if (bkp)	str[2] = 'i';

	str.Insert(EOM,str.Length()+1);

	/* send command to port */
	if (comm->sendBuffer(str.c_str(), str.Length()))
	{
		errorCount++;
		errorType = "A kérdést nem sikerült elküldeni.";
	}

	/* get the answer */
	if (comm->readBuffer())
	{
		errorCount++;
		errorType = "Nem jött válasz a kérdésre.";
	}

	return comm->global_buffer.c_str();
}

AnsiString TStandaloneCommand::increment_parameter(AnsiString str)
{
	int old_par = 0;
	AnsiString par = "";
	AnsiString inc = str;

	if (inc!="")
	{
		if (inc.Length() >= 7)
		{
			par += str[6];
			par += str[7];
		}
    	else par = "00";

		try
		{
			old_par = StrToInt(par);
			old_par++;
			par.sprintf("%02d",old_par);
        	inc.Delete(6,2);
			inc.Insert(par,6);
		}
		catch(EConvertError &e)
		{
			;
		}
	}

	return inc;
}
AnsiString TStandaloneCommand::get_command_name(AnsiString str)
{
	if (str!="")
	{
		str.Delete(1,2);
		str.Delete(4,str.Length());
	}
	else
	{
		errorCount++;
		return errorType = "Nem jó a fájlban a parancsnév.";
	}
	return str;
}
AnsiString TStandaloneCommand::get_commandstring(AnsiString str)
{
	if (str!="")
	{
		str.Delete(8,str.Length());
	}
	return str;
}
AnsiString TStandaloneCommand::get_parameter(AnsiString str)
{
	if (str!="")
	{
		str.Delete(1,7);
	}
	return str;
}

/* public */
TStandaloneCommand::TStandaloneCommand(void)
{
	;
}
TStandaloneCommand::TStandaloneCommand(TCommunication *icomm,
	THandleIni *iini, AnsiString icommName, AnsiString ifileName,
	AnsiString icommandString, AnsiString idescription)
{
	comm = icomm;
	ini = iini;
	commName = icommName;
	fileName = ifileName;
	commandString = icommandString;
	description = idescription;
	errorCount = 0;
	warningCount = 0;

	/* create command name from this "I50100" (example!) string
	   and create command type */
	if (commandString!="")
	{
		int cmdlen;
		commandName = commandString;
		commandName.Delete(1,2);
		cmdlen = commandName.Length();
		commandName.Delete(6,cmdlen);

		/* get the type of the string */
		commandType = get_parameter_number_from_resource(icommandString);
		/* clear the sub type note from command string */
		if ( (commandSubType > 0) && (commandString.Length() >= 8) )
			commandString[8] = '\0';
	}
}
TStandaloneCommand::~TStandaloneCommand(void)
{
	;
}

void TStandaloneCommand::setCommandName(AnsiString icommandName)
{
	commandName = icommandName;
}
AnsiString TStandaloneCommand::getCommandName(void)
{
	return commandName;
}
void TStandaloneCommand::setErrorCount(int ierrorCount)
{
	errorCount = ierrorCount;
}
int TStandaloneCommand::getErrorCount(void)
{
	return errorCount;
}
void TStandaloneCommand::setWarningCount(int iwarningCount)
{
	errorCount = iwarningCount;
}
int TStandaloneCommand::getWarningCount(void)
{
	return warningCount;
}
void TStandaloneCommand::setPositionInBackupFile(int iposition_in_backupfile)
{
	position_in_backupfile = iposition_in_backupfile;
}
int TStandaloneCommand::getPositionInBackupFile(void)
{
	return position_in_backupfile;
}
void TStandaloneCommand::setFileName(AnsiString ifileName)
{
	fileName = ifileName;
}
AnsiString TStandaloneCommand::getFileName(void)
{
	return fileName;
}
void TStandaloneCommand::setDescription(AnsiString idescription)
{
	description = idescription;
}
AnsiString TStandaloneCommand::getDescription(void)
{
	return description;
}

void TStandaloneCommand::Backup(void)
{
	/* the parameter number */
	int parameter;
	/* it takes the command string of case that no answer */
	AnsiString tmpCmdString = commandString;
	/* short command name */
	AnsiString shortCommandName = commandName.Delete(4,2);

	/* set the name of the configuraton file */
	ini->setFileName(fileName);

	/* open the serial port */
	if (comm->OpenPort(commName.c_str()))
	{
		errorCount++;
		errorType = "A port nem elérhetõ.";
    	return;
	}

	/* set parameter to init(default)value */
	parameter = commandType;

	/* select process append to command type:
	   - 0 means: with sending parameter "00" the answer contains all available
		 information that we need and must send (that is: must to store) this
		 setting with "00" also.
	   - 1 means: with sending parameter "00" come or not (egal) answer; we need
		 ask with parameter from "01" to "16(or another but max. 99)" until the
		 length of the answer is bigger as 7 (while come setting value in
		 answer). */
	if (commandType==0)
	{
		/* it takes the position in the backup file in string format */
		AnsiString nr;
    	/* convert position number integer value to string */
		nr.sprintf("%d",position_in_backupfile);

		/* send ask and get answer from device */
		commandString = get_answer(commandString,true);
		/* format answer to its store-format */
		commandString = format_answer(commandString,commandType);
		/* if the last char of the string is 'space' convert it to '*' becasue
		   inifile->readstring method not read more space from the end of the
		   string (example in 522 command where come generaly 20 space) */
		if (commandString!="")
		{
			if (commandString[commandString.Length()]==' ')
				commandString.Insert("*",commandString.Length()+1);
    	}
		if (commandString.Length()!=ANSWER_WITH_EMPTY_PARAM_LEN)
		{
			/* write the formatted string in the backup file */
			ini->writeCommand(nr, commandString);
        	/* increment the position */
			position_in_backupfile++;
    	}
		/* close serial port */
		if (comm->ClosePort())
		{
			errorCount++;
			errorType = "A portot nem lehet bezárni.";
		}
	}
	else if (commandType==1)
	{
    	/* it takes the position in the backup file in string format */
		AnsiString nr;

		/* get settings with parameter incrementing */
		for (parameter; parameter < MAX_GETNUMBER; parameter++)
		{
			/* increment the parameter number with 1 */
			if (parameter > 1)	tmpCmdString = increment_parameter(tmpCmdString);
        	/* set incremented command to send */
			commandString = tmpCmdString;
			/* convert position number integer value to string */
			nr.sprintf("%d",position_in_backupfile);
        	/* send ask and get answer from device */
			commandString = get_answer(commandString,true);
			/* format answer to its store-format */
			commandString = format_answer(commandString,commandType);

			if ( (commandString.Length()==ANSWER_WITH_EMPTY_PARAM_LEN) &&
				 (commandSubType!=2) )
			{
				/* close serial port */
				if (comm->ClosePort())
				{
					errorCount++;
					errorType = "A portot nem lehet bezárni.";
				}
				break;
			}
                    
			/* if the last char of the string is 'space' convert it to '*' becasue
			   inifile->readstring method not read more space from the end of the
			   string (example in 522 command where come generaly 20 space) */
        	if (commandString!="")
			{
				if (commandString[commandString.Length()]==' ')
					commandString.Insert("*",commandString.Length()+1);
        	}
			/* write the formatted string in the backup file */
			ini->writeCommand(nr, commandString);
			/* increment the position */
			position_in_backupfile++;
		}
    	/* close serial port */
		if (comm->ClosePort())
		{
			errorCount++;
			errorType = "A portot nem lehet bezárni.";
		}
	}
	else if (commandType==2)
	{
		/* do'nt definied command type yet */
		/* close serial port */
		if (comm->ClosePort())
		{
			errorCount++;
			errorType = "A portot nem lehet bezárni.";
		}
	}
	else if (commandType==3)
	{
		/* the computer format answer is not supported */
		/* close serial port */
		if (comm->ClosePort())
		{
			errorCount++;
			errorType = "A portot nem lehet bezárni.";
		}
	}
	else if (commandType==4)
	{
		/* the computer format answer is supported but do'nt need to set
		   (to store); i.e: 851,852,853 */
		/* close serial port */
		if (comm->ClosePort())
		{
			errorCount++;
			errorType = "A portot nem lehet bezárni.";
		}
	}
	else
	{
		/* unknown command type */
		/* close serial port */
		if (comm->ClosePort())
		{
			errorCount++;
			errorType = "A portot nem lehet bezárni.";
		}
	}
}
void TStandaloneCommand::Restore(void)
{
	/* used to save the original readed string */
	AnsiString tmpCmdString;
	/* it takes the current readed and the following command name */
	AnsiString curCommandName, nextCommandName;
	/* it takes the formatted command name of (this) */
	AnsiString thisCommandName = commandName.Delete(4,commandName.Length());
	/* it takes the original readed command string (with <SOH> and 's') */
	AnsiString tmpCommandString;
	/* it takes the original and aksed (after set up) parameter of the readed command */
	AnsiString originalParameter, answerParameter;
	/* position in backup file with string */
	AnsiString nr;
	/* the beginning of the message char */
	char BOF[2] = {0x01,0x00};

	/* set the name of the configuraton file */
	ini->setFileName(fileName);

	for (int i=0; i < MAX_GETNUMBER; i++)
	{
		/* convert position integer to string */
		nr.sprintf("%d",position_in_backupfile);

		if (position_in_backupfile > -1)	commandString = ini->readCommand(nr);
		else
		{
			/* the row number in the backup file could not -1 */
			errorCount++;
			errorType = "Ez a parancs nincs benne a fájlban (rossz pozíció).";
			/* increment the backup file pointer */
			position_in_backupfile++;
			return;
		}
		/* if the last char of the string is '*' delet it becasue
		   inifile->readstring method not read more space from the end of the
		   string (example in 522 command where come generaly 20 space) */
		if (commandString!="")
		{
			if (commandString[commandString.Length()]=='*')
				commandString.Delete(commandString.Length(),1);
    	}

		/* insert <SOH> in the readed command */
		commandString.Insert(BOF,1);

		/* save the original command string to send */
		tmpCmdString = commandString;

		/* get readed command name */
		curCommandName = get_command_name(commandString);

		/* wrong command name was stored */
		if (curCommandName.Length() < 3)
		{
        	/* increment the backup file pointer */
			position_in_backupfile++;
			return;
		}

		/* this command must not send because will system lockout!!! */
		if	( (commandType==3) || (commandType==4) )
		{
            /* increment the backup file pointer 
			position_in_backupfile++;*/
			return;
		}

		/* the readed command name is not matches to this->commandName */
		if (CompareStr(curCommandName,thisCommandName)!=0)
		{
			/* if readed (current) command name is NULL than step to next
			   position in backup file and nothing send */
			if (curCommandName=="")
			{
				/* increment the backup file pointer */
				position_in_backupfile++;
				return;
			}
			/* readed (current) command name is 9999FF1B that is unknown command
			   step to the next position in the backup file */
			if (CompareStr(commandString,UNKNOWN_ANSWER_STRING_WITH_SOH)==0)
			{
				/* increment the backup file pointer */
				position_in_backupfile++;
				return;
			}
			/* if readed (current) command name is valid but not matches to
			   this->commandName than no stop to next position only return */
			return;
		}

		/* get command with <SOH> and 's' */
		tmpCommandString = get_commandstring(commandString);
		/* get parameter */
		originalParameter = get_parameter(commandString);

		/* check command */
		if (tmpCommandString.Length()==7)
		{
			if ( (tmpCommandString.Length() >= 2) && (tmpCommandString[1]==0x01) )
			{
				if (tmpCommandString[2]=='s')
				{
					/* open the serial port */
					if (comm->OpenPort(commName.c_str()))
					{
						errorCount++;
						errorType = "A port nem elérhetõ.";
                    	/* increment the backup file pointer */
						position_in_backupfile++;
						return;
					}
					else
					{
						/* get answer from device */
						commandString = get_answer(commandString,false);
						/* close serial port */
						if (comm->ClosePort())
						{
							errorCount++;
							errorType = "A portot nem lehet bezárni.";
						}
					}
				}
				else
				{
					warningCount++;
					warningType = "Hibás parancsormátum (nincs 's').";
					/* increment the backup file pointer */
					position_in_backupfile++;
					return;
				}
			}
			else
			{
				warningCount++;
				warningType = "Hibás parancsormátum (nincs <SOH>).";
            	/* increment the backup file pointer */
				position_in_backupfile++;
				return;
			}
		}
		else
		{
			warningCount++;
			warningType = "Hibás parancsormátum (hosszúság nem hét).";
        	/* increment the backup file pointer */
			position_in_backupfile++;
			return;
		}

		/* check answer */
		if ( (commandString=="") || (CompareStr(commandString,UNKNOWN_ANSWER_STRING)==0) )
		{
			errorCount++;
			errorType = "Nem jött válasz a beállítás sikerességérõl.";
        	/* increment the backup file pointer */
			position_in_backupfile++;
			return;
		}

		/* format answer */
		commandString = format_answer(commandString,commandType);

    	/* get parameter */
		answerParameter = get_parameter(commandString);

		/* the readed (from file) and the answer (after set up) parameter not equal */
		if (CompareStr(answerParameter,originalParameter)!=0)
		{
			warningCount++;
			warningType = "Nem az lett beállítva, ami a fájlban van elmentve.";
		}

		/* increment the backup file pointer */
		position_in_backupfile++;
		/* convert position integer to string */
		nr.sprintf("%d",position_in_backupfile);
		/* get the next command */
		commandString = ini->readCommand(nr);
		/* insert <SOH> in the readed command */
		commandString.Insert(BOF,1);
		/* get next command name */
		nextCommandName = get_command_name(commandString);

		if (CompareStr(nextCommandName,curCommandName)!=0)	break;
	}
}

AnsiString TStandaloneCommand::getErrorString(void)
{
	AnsiString estr = "";

	if (errorCount)	estr.sprintf("%d hiba: %s - %s",errorCount,description,errorType);

	return estr;
}

AnsiString TStandaloneCommand::getWarningString(void)
{
	AnsiString wstr = "";

	if (warningCount)	wstr.sprintf("%d jelzés: %s - %s",warningCount,description,warningType);

	return wstr;
}
