//---------------------------------------------------------------------------


#pragma hdrstop

#include "TLSDevice.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/* private */

void __fastcall TTLSDevice::copy_char(char src, char *dest, int pos)
{
	dest[pos] = src;
}
void __fastcall TTLSDevice::copy_char_ex(char src, char *dest, int pos, int cnt)
{
	for (int i=pos; i < pos+cnt; i++)
	{
		dest[i] = src;
	}
}
void __fastcall TTLSDevice::copy_chars(char *src, int srcpos, char *dest,
	int pos, int cnt)
{
	if (src==NULL)	return;

	for (int i=srcpos; i < cnt; pos++, i++)
	{
		dest[pos] = src[i];
	}
}

void __fastcall TTLSDevice::init_show_dialog_window(int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	if (!ShowDialog)	return;
	if (!comm)			return;

	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");
	/* get and show current settings on the dialog window */
	get(page_idx, group_idx, item_idx, NULL, 'i', '0', "");
	/* check data integrity */
	if (check_checksum(comm->global_buffer.c_str()))
	{
		read_comm_buffer_and_show_if_error(e_checksum, m);
	}
}

void __fastcall TTLSDevice::get_computer_format_answer(char *cmdstr,
	AnsiString param, int param_pos, TMemo *m)
{
	int res = send('i',cmdstr,lenCmd,1,param,0,param_pos,param.Length(),'\0',7,param.Length());

	read_comm_buffer_and_show_if_error(res, NULL);
	/* check data integrity */
	if (check_checksum(comm->global_buffer.c_str()))
	{
		read_comm_buffer_and_show_if_error(e_checksum, m);
	}
}

bool TTLSDevice::check_checksum(AnsiString str)
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

void TTLSDevice::show_line_status(TMemo *m)
{
	if (!m) return;

	if (first_time_run)
	{
		/* check line status at first time */
		bool cts, dsr, ring, rlsd, ready = false;
		AnsiString msg = "LINE STATUS: ";

		comm->CheckModemStatus();

		cts = comm->getCTSStatus();
		dsr = comm->getDSRStatus();
		ring = comm->getRINGStatus();
		rlsd = comm->getRLSDStatus();

		if (cts)
		{
						msg += " CTS ON, ";
						ready |= false;
		}
		else
		{
						msg += " CTS OFF, ";
		}
		if (dsr)
		{
						msg += " DSR ON, ";
						ready |= true;
		}
		else
		{
						msg += " DSR OFF, ";
		}
		if (ring)
		{
						msg += " RING ON, ";
						ready |= false;
		}
		else
		{
						msg += " RING OFF, ";
		}
		if (rlsd)
		{
						msg += " RLSD ON. ";
						ready |= false;
		}
		else
		{
						msg += " RLSD OFF, ";
		}
		if (ready)
		{
						msg += ".:PORT READY:.";
		}
		else
		{
						msg += ".:NO SIGNAL:.";
		}

		m->Lines->Add(msg);
		first_time_run = false;
	}
}

AnsiString TTLSDevice::convert_date_time_string(AnsiString str)
{
	int pos = 1;
	while (pos)
	{
		pos = str.Pos(' ');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('§');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('\'');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('\"');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('+');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('!');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('%');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('/');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('=');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('(');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos(')');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('\\');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('|');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('#');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('&');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('@');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('{');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('}');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos(',');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos(';');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('?');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('.');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos(':');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('-');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('_');
		if (pos) str.Delete(pos, 1);
	}
	pos = 1;
	while (pos)
	{
		pos = str.Pos('*');
		if (pos) str.Delete(pos, 1);
	}

	return str;
}

int TTLSDevice::send(char commandtype, char *cmdstr, int commandstring_len,
	int cmdtype_pos, AnsiString string_to_send, int string_to_send_first_pos,
	int string_to_send_start_pos, int string_to_send_len,
	char emptychar, int empty_first_pos, int empty_len)
{
	int result;
	/* end of message char; first u sends a string to the tls device than the
	   device answers for this message only if the length of the command string
	   is equal or more (>=) than it requiers. if u sends a string to it, an end
	   of message (0x0D) char is required at the end of the string; it tells the
	   device that this is the end of the parameter list of the command. */
	char EOM[2] = {0x0D,0x00};

	/* check all input parameter; if fail was detected return with write failed
	   error */
	if ( (commandtype!='i') && (commandtype!='I') && (commandtype!='s') && (commandtype!='S') )
		return 6;
	if (commandstring_len < 0)	return 6;
	if ( (cmdtype_pos < 0) || (cmdtype_pos > commandstring_len) )	return 6;
	if (string_to_send=="")	return 6;
	if ( (string_to_send_first_pos < 0) || (string_to_send_first_pos > commandstring_len) )
		return 6;
	if ( (string_to_send_start_pos < 0) || (string_to_send_start_pos > commandstring_len) )
		return 6;
	if ( (string_to_send_len < 0) || (string_to_send_len > commandstring_len) )
		return 6;
	if ( (empty_first_pos < 0) || (empty_first_pos > commandstring_len) )
		return 6;
	if ( (empty_len < 0) || (empty_len > commandstring_len) )
		return 6;

	/* set up the command type:
		i: get setting in computer format;
		I: get setting in display format;
		s: set setting in computer format;
		S: set setting in diasply format */
	copy_char(commandtype,cmdstr,cmdtype_pos);

	/* string (what we want to send as parameter of the specified
	   command::source string) append to the command string */
	copy_chars(string_to_send.c_str(),		// source string
			   string_to_send_first_pos,	// source string first pos (generally: 0)
			   cmdstr,						// destination string
			   string_to_send_start_pos,	// start index in the destination string
			   string_to_send_len			// how much chars need to copy from the source string
			);

	/* append end of message char to the command string; 0x0D is the eom;
	   case 5 is that when the length of the command is only 5 not 7 because
	   u set up manually the device number (01...99) */
	switch (string_to_send_start_pos)
	{
		case 5:	copy_chars(EOM,0,cmdstr,COMMAND_LEN+string_to_send_len-2,2); break;
		case 7:	copy_chars(EOM,0,cmdstr,COMMAND_LEN+string_to_send_len,2); break;
		default:	copy_chars(EOM,0,cmdstr,COMMAND_LEN+string_to_send_len,2);
	}

	/* sending the command string */
	result = comm->sendBuffer(cmdstr,commandstring_len);

	/* empty the command string's parameter area with the given char;
	   (generally: '\0') */
	copy_char_ex(emptychar,cmdstr,empty_first_pos,empty_len);

	return result;
}

/* this functions create and show the general dialog box and place command
   specific controls on it */
/* system type and language flags */
int TTLSDevice::showSetSystemTypeLanguageFlagsDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	int unit, lang;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get the current settings */
	unit = get_current_unit(comm->global_buffer.c_str());
	lang = get_current_lang(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setLanguageIndex(lang);
	ShowDialog->setUnitIndex(unit);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_systemlanguageandunit);
	/* get new settings */
	lang = ShowDialog->getLanguageIndex();
	unit = ShowDialog->getUnitIndex();
	cancel_from_dialog = ShowDialog->getModalResult();

	/* if the user has clicked on the ok button than set new values */
	if (!cancel_from_dialog)
	{
		AnsiString unitlang;

		wProc->init(true);
		unitlang.sprintf("%d%d",unit,lang);
		result = send(cmd_type,cmds.cmdSetSystemTypeLanguageFlags1,lenCmd,1,unitlang,0,7,2,'\0',7,2);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetSystemDateTimeDisplayFormatDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	int format;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get the current settings */
	format = get_current_datetime_format(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDateTimeFormatIndex(format);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_systemdatetimedisplayformat);
	/* get new settings */
	format = ShowDialog->getDateTimeFormatIndex();
	cancel_from_dialog = ShowDialog->getModalResult();

	/* if the user has clicked on the ok button than set new values */
	if (!cancel_from_dialog)
	{
		AnsiString disp_type; 
		wProc->init(true);
		wProc->increment();
		disp_type.sprintf("%02d",format);
		result = send(cmd_type,cmds.cmdSetSystemDateTimeDisplayFormat,
			lenCmd,1,disp_type,0,7,2,'\0',7,2);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTimeofday(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	TDateTime date, time;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	date = get_current_date(comm->global_buffer.c_str());
	time = get_current_time(comm->global_buffer.c_str());
	wProc->init(false);
	/* display current settings */
	ShowDialog->setDate(date);
	ShowDialog->setTime(time);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_timeofday);
	/* get new settings */
	date = ShowDialog->getDate();
	time = ShowDialog->getTime();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString timeformat = Sysutils::LongTimeFormat;
		Sysutils::LongTimeFormat = "HH:mm";
		AnsiString datestr = date.DateString();
		AnsiString timestr = time.TimeString();
		Sysutils::LongTimeFormat = timeformat;
		AnsiString send_str;

		wProc->init(true);
		wProc->increment();

		if (datestr.Length() > 0)
		{
			/* we need only the last two chars from the date string */
			datestr.Delete(1, 2);
			datestr = convert_date_time_string(datestr);
		}
		else
		{
			datestr = "000101";
		}
		if (timestr.Length() > 0)
		{
			timestr = convert_date_time_string(timestr);
		}
		else
		{
			timestr = "2359";
		}

		send_str = datestr+timestr;

		result = send(cmd_type,cmds.cmdSetTimeofday,lenCmd,1,send_str,0,7,10,'\0',7,10);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetPrintHeaderLine1234(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString header_index;
	AnsiString header1, header2, header3, header4;

	wProc->init(4,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();

	if (m)
	{
		/* get and display current settings */
		for (int i=1; i < 5; i++)
		{
			header_index.sprintf("%02d",i);
			get(page_idx, group_idx, item_idx, m, 'I', '0', header_index.c_str());
		}
	}
	/* get and show current settings */
	for (int i=1; i < 5; i++)
	{
		header_index.sprintf("%02d",i);
		get(page_idx, group_idx, item_idx, NULL, 'i', '0', header_index.c_str());
    	/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}

		if (i==1)	header1 = get_current_header(comm->global_buffer.c_str());
		if (i==2)	header2 = get_current_header(comm->global_buffer.c_str());
		if (i==3)	header3 = get_current_header(comm->global_buffer.c_str());
		if (i==4)	header4 = get_current_header(comm->global_buffer.c_str());

		wProc->increment();
	}               
	wProc->init(false);
	/* display current settings */
	ShowDialog->setHeader1(header1);
	ShowDialog->setHeader2(header2);
	ShowDialog->setHeader3(header3);
	ShowDialog->setHeader4(header4);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_printheaderlines);
	/* get new settings */
	header1 = ShowDialog->getHeader1();
	header2 = ShowDialog->getHeader2();
	header3 = ShowDialog->getHeader3();
	header4 = ShowDialog->getHeader4();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString line;

		wProc->init(true);
		wProc->increment();

		for (int i=1; i < 5; i++)
		{
			header_index.sprintf("%02d",i);

			if (i==1)	line = header1;
			if (i==2)	line = header2;
			if (i==3)	line = header3;
			if (i==4)	line = header4;

			line.Insert(header_index,1);

			result = send(cmd_type,cmds.cmdSetPrintHeaderLine1234,
				lenCmd,1,line,0,5,line.Length(),'\0',5,20);
			wProc->increment();
		}       
		wProc->init(false);

    	if (m)
		{
			/* get and display current settings */
			for (int i=1; i < 5; i++)
			{
				header_index.sprintf("%02d",i);
				get(page_idx, group_idx, item_idx, m, 'I', '0', header_index.c_str());
			}
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetShiftStartTime1234(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString shifttime_index;
	bool shiftstart1, shiftstart2, shiftstart3, shiftstart4;
	TDateTime shifttime1, shifttime2, shifttime3, shifttime4;
	const AnsiString shifttime_disabled = "EE00";

	wProc->init(4,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();

	if (m)
	{
		/* get and display current settings */
		for (int i=1; i < 5; i++)
		{
			shifttime_index.sprintf("%02d",i);
			get(page_idx, group_idx, item_idx, m, 'I', '0', shifttime_index.c_str());
		}
	}
	/* get and show current settings */
	for (int i=1; i < 5; i++)
	{
		shifttime_index.sprintf("%02d",i);
		get(page_idx, group_idx, item_idx, NULL, 'i', '0', shifttime_index.c_str());
    	/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}

		if (i==1)
		{
			shifttime1 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime1 > -1.0)	shiftstart1 = true;
			else	shiftstart1 = false;
		}
		if (i==2)
		{
			shifttime2 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime2 > -1.0)	shiftstart2 = true;
			else	shiftstart2 = false;
		}
		if (i==3)
		{
			shifttime3 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime3 > -1.0)	shiftstart3 = true;
			else	shiftstart3 = false;
		}
		if (i==4)
		{
			shifttime4 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime4 > -1.0)	shiftstart4 = true;
			else	shiftstart4 = false;
		}    
		wProc->increment();
	}   
	wProc->init(false);
	/* display current settings */
	ShowDialog->setShifttime1(TimeToStr(shifttime1));
	ShowDialog->setShifttime2(TimeToStr(shifttime2));
	ShowDialog->setShifttime3(TimeToStr(shifttime3));
	ShowDialog->setShifttime4(TimeToStr(shifttime4));
	ShowDialog->setShiftstart1(shiftstart1);
	ShowDialog->setShiftstart2(shiftstart2);
	ShowDialog->setShiftstart3(shiftstart3);
	ShowDialog->setShiftstart4(shiftstart4);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_shiftstarttimes);
	/* get new settings */
	shifttime1 = ShowDialog->getShifttime1();
	shifttime2 = ShowDialog->getShifttime2();
	shifttime3 = ShowDialog->getShifttime3();
	shifttime4 = ShowDialog->getShifttime4();
	shiftstart1 = ShowDialog->getShiftstart1();
	shiftstart2 = ShowDialog->getShiftstart2();
	shiftstart3 = ShowDialog->getShiftstart3();
	shiftstart4 = ShowDialog->getShiftstart4();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
    	AnsiString timeformat = Sysutils::LongTimeFormat;
		Sysutils::LongTimeFormat = "HH:mm";
		AnsiString new_time;

		wProc->init(true);
		wProc->increment();

		for (int i=1; i < 5; i++)
		{
			shifttime_index.sprintf("%02d",i);

			if (i==1)
			{
				if (shiftstart1)
				{
					new_time = shifttime1.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}
			if (i==2)
			{
				if (shiftstart2)
				{
					new_time = shifttime2.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}
			if (i==3)
			{
				if (shiftstart3)
				{
					new_time = shifttime3.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}
			if (i==4)
			{
				if (shiftstart4)
				{
					new_time = shifttime4.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}

			new_time.Insert(shifttime_index,1);

			result = send(cmd_type,cmds.cmdSetShiftStartTime1234,
				lenCmd,1,new_time,0,5,new_time.Length(),'\0',5,8);
			wProc->increment();
		}
         
		wProc->init(false);
		Sysutils::LongTimeFormat = timeformat;

		if (m)
		{
			/* get and display current settings */
			for (int i=1; i < 5; i++)
			{
				shifttime_index.sprintf("%02d",i);
				get(page_idx, group_idx, item_idx, m, 'I', '0', shifttime_index.c_str());
			}
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetBIRShiftPrintoutsFlagDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool shiftbirprintouts;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	shiftbirprintouts = get_current_shiftbirprintouts(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setShiftBIRPrintouts(shiftbirprintouts);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_shiftbirprintouts);
	/* get new settings */
	shiftbirprintouts = ShowDialog->getShiftBIRPrintouts();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (shiftbirprintouts)
			result = send(cmd_type,cmds.cmdSetBIRShiftPrintoutsFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetBIRShiftPrintoutsFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetBIRDailyPrintoutsFlagDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool dailybirprintouts;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	dailybirprintouts = get_current_dailybirprintouts(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDailyBIRPrintouts(dailybirprintouts);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_dailybirprintouts);
	/* get new settings */
	dailybirprintouts = ShowDialog->getDailyBIRPrintouts();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (dailybirprintouts)
			result = send(cmd_type,cmds.cmdSetBIRDailyPrintoutsFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetBIRDailyPrintoutsFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTicketedDeliveryFlagEnableDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool ticketeddelivery;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	ticketeddelivery = get_current_ticketeddelivery(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTicketedDelivery(ticketeddelivery);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_ticketeddelivery);
	/* get new settings */
	ticketeddelivery = ShowDialog->getTicketedDelivery();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (ticketeddelivery)
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryFlagEnable,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryFlagEnable,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTicketedDeliveryTemperatureCompensationFlagDlg(
	char cmd_type, int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool tcticketeddelivery;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	tcticketeddelivery = get_current_tcticketeddelivery(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTCTicketedDelivery(tcticketeddelivery);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tcticketeddelivery);
	/* get new settings */
	tcticketeddelivery = ShowDialog->getTCTicketedDelivery();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{             
		wProc->init(true);
		wProc->increment();

		if (tcticketeddelivery)
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryTemperatureCompensationFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryTemperatureCompensationFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTicketedDeliveryCloseDayofWeekDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	int tdclosedayofweek;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	tdclosedayofweek = get_current_tdclosedayofweek(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTDCloseDayOfWeek(tdclosedayofweek);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tdclosedayofweek);
	/* get new settings */
	tdclosedayofweek = ShowDialog->getTDCloseDayOfWeek();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{       
		wProc->init(true);
		wProc->increment();

		if (tdclosedayofweek==-1)
		{
			tdclosedayofweek = 0;            
		}

		AnsiString tdcdow;
		tdcdow.sprintf("%d",tdclosedayofweek);

		result = send(cmd_type,cmds.cmdSetTicketedDeliveryCloseDayofWeek,
			lenCmd,1,tdcdow,0,7,tdcdow.Length(),'\0',7,tdcdow.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTicketedDeliveryVariancePrintoutFlagsDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool daily, weekly, periodic;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	daily = get_current_dailyvariance(comm->global_buffer.c_str());
	weekly = get_current_weeklyvariance(comm->global_buffer.c_str());
	periodic = get_current_periodicvariance(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDailyDelivery(daily);
	ShowDialog->setWeeklyDelivery(weekly);
	ShowDialog->setPeriodicDelivery(periodic);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_deliveryvariance);
	/* get new settings */
	daily = ShowDialog->getDailyDelivery();
	weekly = ShowDialog->getWeeklyDelivery();
	periodic = ShowDialog->getPeriodicDelivery();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString cpwd = "";

		wProc->init(true); 
		wProc->increment();

		if (periodic) cpwd += '1';
		else cpwd += '0';
		if (weekly) cpwd += '1';
		else cpwd += '0';
		if (daily) cpwd += '1';
		else cpwd += '0';

		result = send(cmd_type,cmds.cmdSetTicketedDeliveryVariancePrintoutFlags,
			lenCmd,1,cpwd,0,7,cpwd.Length(),'\0',7,cpwd.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTicketedDeliveryBookVariancePrintoutFlagsDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool daily, weekly, periodic;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	daily = get_current_dailyvariance(comm->global_buffer.c_str());
	weekly = get_current_weeklyvariance(comm->global_buffer.c_str());
	periodic = get_current_periodicvariance(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDailyBookDelivery(daily);
	ShowDialog->setWeeklyBookDelivery(weekly);
	ShowDialog->setPeriodicBookDelivery(periodic);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_deliverybookvariance);
	/* get new settings */
	daily = ShowDialog->getDailyBookDelivery();
	weekly = ShowDialog->getWeeklyBookDelivery();
	periodic = ShowDialog->getPeriodicBookDelivery();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString cpwd = "";

		wProc->init(true);
		wProc->increment();

		if (periodic) cpwd += '1';
		else cpwd += '0';
		if (weekly) cpwd += '1';
		else cpwd += '0';
		if (daily) cpwd += '1';
		else cpwd += '0';

		result = send(cmd_type,cmds.cmdSetTicketedDeliveryBookVariancePrintoutFlags,
			lenCmd,1,cpwd,0,7,cpwd.Length(),'\0',7,cpwd.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTicketedVarianceAnalysisPrintoutFlagsDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool daily, weekly, periodic;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	daily = get_current_dailyvariance(comm->global_buffer.c_str());
	weekly = get_current_weeklyvariance(comm->global_buffer.c_str());
	periodic = get_current_periodicvariance(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDailyAnalysis(daily);
	ShowDialog->setWeeklyAnalysis(weekly);
	ShowDialog->setPeriodicAnalysis(periodic);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_varianceanalysis);
	/* get new settings */
	daily = ShowDialog->getDailyAnalysis();
	weekly = ShowDialog->getWeeklyAnalysis();
	periodic = ShowDialog->getPeriodicAnalysis();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString cpwd = "";

		wProc->init(true);
		wProc->increment();

		if (periodic) cpwd += '1';
		else cpwd += '0';
		if (weekly) cpwd += '1';
		else cpwd += '0';
		if (daily) cpwd += '1';
		else cpwd += '0';

		result = send(cmd_type,cmds.cmdSetTicketedVarianceAnalysisPrintoutFlags,
			lenCmd,1,cpwd,0,7,cpwd.Length(),'\0',7,cpwd.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTankPeriodicTestNeededWarningDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool testneededwarningflag;
	int daysbeforewarn, daysbeforealm;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();

	for (int i=27; i < 30; i++)
	{
		/* get and display current settings */
		if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");

		/* get and show current settings */
		get(page_idx, group_idx, i, NULL, 'i', '0', "");
		/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}
		if	(i==27)
			testneededwarningflag = get_current_testneededwarningflag(
													comm->global_buffer.c_str());
		if	(i==28)
			daysbeforewarn = get_current_daysbeforewarn(comm->global_buffer.c_str());
		if	(i==29)
			daysbeforealm = get_current_daysbeforealm(comm->global_buffer.c_str());
		wProc->increment();
	}        
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTestNeededWarningFlag(testneededwarningflag);
	ShowDialog->setDaysBeforeWarn(daysbeforewarn);
	ShowDialog->setDaysBeforeAlm(daysbeforealm);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_periodictestneededwarn);
	/* get new settings */
	testneededwarningflag = ShowDialog->getTestNeededWarningFlag();
	daysbeforewarn = ShowDialog->getDaysBeforeWarn();
	daysbeforealm = ShowDialog->getDaysBeforeAlm();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{            
		wProc->init(true);
		wProc->increment();
		if (testneededwarningflag)
		{
			AnsiString befwarn;
			AnsiString befalm;

			befwarn.sprintf("%02d",daysbeforewarn);
			befalm.sprintf("%02d",daysbeforealm);

			result = send(cmd_type,cmds.cmdSetTankPeriodicTestNeededWarning,
				lenCmd,1,"1",0,7,1,'\0',7,1);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeTankPeriodicTestNeededWarning,
				lenCmd,1,befwarn,0,7,befwarn.Length(),'\0',7,befwarn.Length());
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeTankPeriodicTestNeededAlarm,
				lenCmd,1,befalm,0,7,befalm.Length(),'\0',7,befalm.Length());
			wProc->increment();
		}
		else
		{
			result = send(cmd_type,cmds.cmdSetTankPeriodicTestNeededWarning,
				lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		}    
		wProc->init(false);

    	for (int i=27; i < 30; i++)
		{
			/* get and display current settings */
			if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTankAnnualTestNeededWarningDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool testneededwarningflag;
	int daysbeforewarn, daysbeforealm;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	
	for (int i=30; i < 33; i++)
	{
		/* get and display current settings */
		if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");

		/* get and show current settings */
		get(page_idx, group_idx, i, NULL, 'i', '0', "");
		/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}
		if	(i==30)
			testneededwarningflag = get_current_testneededwarningflag(
													comm->global_buffer.c_str());
		if	(i==31)
			daysbeforewarn = get_current_daysbeforewarn(comm->global_buffer.c_str());
		if	(i==32)
			daysbeforealm = get_current_daysbeforealm(comm->global_buffer.c_str()); 
		wProc->increment();
	}           
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTestNeededWarningFlag(testneededwarningflag);
	ShowDialog->setDaysBeforeWarn(daysbeforewarn);
	ShowDialog->setDaysBeforeAlm(daysbeforealm);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_annualtestneededwarn);
	/* get new settings */
	testneededwarningflag = ShowDialog->getTestNeededWarningFlag();
	daysbeforewarn = ShowDialog->getDaysBeforeWarn();
	daysbeforealm = ShowDialog->getDaysBeforeAlm();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{                  
		wProc->init(true);
		wProc->increment();
		if (testneededwarningflag)
		{
			AnsiString befwarn;
			AnsiString befalm;

			befwarn.sprintf("%03d",daysbeforewarn);
			befalm.sprintf("%03d",daysbeforealm);

			result = send(cmd_type,cmds.cmdSetTankAnnualTestNeededWarning,
				lenCmd,1,"1",0,7,1,'\0',7,1);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeTankAnnualTestNeededWarning,
				lenCmd,1,befwarn,0,7,befwarn.Length(),'\0',7,befwarn.Length());
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeTankAnnualTestNeededAlarm,
				lenCmd,1,befalm,0,7,befalm.Length(),'\0',7,befalm.Length());
			wProc->increment();
		}
		else
		{
			result = send(cmd_type,cmds.cmdSetTankAnnualTestNeededWarning,
				lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		}
		wProc->init(false);

		for (int i=30; i < 33; i++)
		{
			/* get and display current settings */
			if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetLineReEnableMethodDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool passlinetest;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	passlinetest = get_current_passlinetest(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setPassLineTest(passlinetest);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_linereenablemethod);
	/* get new settings */
	passlinetest = ShowDialog->getPassLineTest();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (passlinetest)
			result = send(cmd_type,cmds.cmdSetLineReEnableMethod,lenCmd,1,"0",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetLineReEnableMethod,lenCmd,1,"1",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetLinePeriodicTestNeededWarningDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool testneededwarningflag;
	int daysbeforewarn, daysbeforealm;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();

	for (int i=34; i < 37; i++)
	{
		/* get and display current settings */
		if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");

		/* get and show current settings */
		get(page_idx, group_idx, i, NULL, 'i', '0', "");
		/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}
		if	(i==34)
			testneededwarningflag = get_current_testneededwarningflag(
													comm->global_buffer.c_str());
		if	(i==35)
			daysbeforewarn = get_current_daysbeforewarn(comm->global_buffer.c_str());
		if	(i==36)
			daysbeforealm = get_current_daysbeforealm(comm->global_buffer.c_str());
		wProc->increment();
	}      
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTestNeededWarningFlag(testneededwarningflag);
	ShowDialog->setDaysBeforeWarn(daysbeforewarn);
	ShowDialog->setDaysBeforeAlm(daysbeforealm);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_lineperiodictestneededwarn);
	/* get new settings */
	testneededwarningflag = ShowDialog->getTestNeededWarningFlag();
	daysbeforewarn = ShowDialog->getDaysBeforeWarn();
	daysbeforealm = ShowDialog->getDaysBeforeAlm();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{                    
		wProc->init(true);
		wProc->increment();
		if (testneededwarningflag)
		{
			AnsiString befwarn;
			AnsiString befalm;

			befwarn.sprintf("%02d",daysbeforewarn);
			befalm.sprintf("%02d",daysbeforealm);

			result = send(cmd_type,cmds.cmdSetLinePeriodicTestNeededWarning,
				lenCmd,1,"1",0,7,1,'\0',7,1);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeLinePeriodicTestNeededWarning,
				lenCmd,1,befwarn,0,7,befwarn.Length(),'\0',7,befwarn.Length());
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeLinePeriodicTestNeededAlarm,
				lenCmd,1,befalm,0,7,befalm.Length(),'\0',7,befalm.Length());
			wProc->increment();
		}
		else
		{
			result = send(cmd_type,cmds.cmdSetLinePeriodicTestNeededWarning,
				lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		} 
		wProc->init(false);

		for (int i=34; i < 37; i++)
		{
			/* get and display current settings */
			if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetLineAnnualTestNeededWarningDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool testneededwarningflag;
	int daysbeforewarn, daysbeforealm;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	
	for (int i=37; i < 40; i++)
	{
		/* get and display current settings */
		if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");

		/* get and show current settings */
		get(page_idx, group_idx, i, NULL, 'i', '0', "");
		/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}
		if	(i==37)
			testneededwarningflag = get_current_testneededwarningflag(
													comm->global_buffer.c_str());
		if	(i==38)
			daysbeforewarn = get_current_daysbeforewarn(comm->global_buffer.c_str());
		if	(i==39)
			daysbeforealm = get_current_daysbeforealm(comm->global_buffer.c_str());
		wProc->increment();
	}         
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTestNeededWarningFlag(testneededwarningflag);
	ShowDialog->setDaysBeforeWarn(daysbeforewarn);
	ShowDialog->setDaysBeforeAlm(daysbeforealm);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_lineannualtestneededwarn);
	/* get new settings */
	testneededwarningflag = ShowDialog->getTestNeededWarningFlag();
	daysbeforewarn = ShowDialog->getDaysBeforeWarn();
	daysbeforealm = ShowDialog->getDaysBeforeAlm();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{                
		wProc->init(true);
		wProc->increment();
		if (testneededwarningflag)
		{
			AnsiString befwarn;
			AnsiString befalm;

			befwarn.sprintf("%03d",daysbeforewarn);
			befalm.sprintf("%03d",daysbeforealm);

			result = send(cmd_type,cmds.cmdSetLineAnnualTestNeededWarning,
				lenCmd,1,"1",0,7,1,'\0',7,1);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeLineAnnualTestNeededWarning,
				lenCmd,1,befwarn,0,7,befwarn.Length(),'\0',7,befwarn.Length());
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetDaysBeforeLineAnnualTestNeededAlarm,
				lenCmd,1,befalm,0,7,befalm.Length(),'\0',7,befalm.Length());
			wProc->increment();
		}
		else
		{
			result = send(cmd_type,cmds.cmdSetLineAnnualTestNeededWarning,
				lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		}
		wProc->init(false);

		for (int i=37; i < 40; i++)
		{
			/* get and display current settings */
			if (m)	get(page_idx, group_idx, i, m, 'I', '0', "");
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetRemotePrinterPageEjectFlagDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool remoteprinterpageeject;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	remoteprinterpageeject = get_current_remoteprinterpageeject(
												comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setRemotePrinterPageEject(remoteprinterpageeject);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_remoteprinterpageeject);
	/* get new settings */
	remoteprinterpageeject = ShowDialog->getRemotePrinterPageEject();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (remoteprinterpageeject)
			result = send(cmd_type,cmds.cmdSetRemotePrinterPageEjectFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetRemotePrinterPageEjectFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetPrintTemperatureCompensationFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool printtc;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	printtc = get_current_printtc(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setPrintTC(printtc);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_printtc);
	/* get new settings */
	printtc = ShowDialog->getPrintTC();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true); 
		wProc->increment();

		if (printtc)
			result = send(cmd_type,cmds.cmdSetPrintTemperatureCompensationFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetPrintTemperatureCompensationFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTemperatureCompensationValueDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	float tempcomp;
	int unit;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();

	/* get the system unit; this need to set up the max and min value for the
	   settings of the temperature compensation value (us: 0-120 °F;
	   metric: -17-49°C) */
	get(0, 0, 0, NULL, 'i', '0', "");
	/* check data integrity */
	if (check_checksum(comm->global_buffer.c_str()))
	{
		read_comm_buffer_and_show_if_error(e_checksum, m);
	}
	/* get the current settings */
	unit = get_current_unit(comm->global_buffer.c_str());
	ShowDialog->setUnitIndex(unit);

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");
	get(page_idx, group_idx, item_idx, NULL, 'i', '0', "");
	/* check data integrity */
	if (check_checksum(comm->global_buffer.c_str()))
	{
		read_comm_buffer_and_show_if_error(e_checksum, m);
	}
	/* get and show current settings */
	tempcomp = get_current_tempcomp(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTemperatureCompensation(tempcomp);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tempcomp);
	/* get new settings */
	tempcomp = ShowDialog->getTemperatureCompensation();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString tc;

		wProc->init(true);
		wProc->increment();

		tc.sprintf("%3.2f", tempcomp);

		result = send(cmd_type,cmds.cmdSetTemperatureCompensationValue,
				lenCmd,1,tc,0,7,tc.Length(),'\0',7,tc.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTankerLoadReportFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool tankerloadreport;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	tankerloadreport = get_current_tankerloadreport(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTankerLoadReport(tankerloadreport);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tankerloadreport);
	/* get new settings */
	tankerloadreport = ShowDialog->getTankerLoadReport();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (tankerloadreport)
			result = send(cmd_type,cmds.cmdSetTankerLoadReportFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetTankerLoadReportFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTankStickHeightFunctionEnableDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool stickheightoffsetflag;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows(); 
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	stickheightoffsetflag = get_current_stickheightoffsetflag(
												comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setStickHeightOffsetFlag(stickheightoffsetflag);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_stickheightoffsetflag);
	/* get new settings */
	stickheightoffsetflag = ShowDialog->getStickHeightOffsetFlag();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (stickheightoffsetflag)
			result = send(cmd_type,cmds.cmdSetTankStickHeightFunctionEnable,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetTankStickHeightFunctionEnable,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetHProtocolHeightVolumeformatDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool hprotocolformat;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows(); 
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	hprotocolformat = get_current_hprotocolformat(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setHProtocolFormat(hprotocolformat);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_hprotocoldataformat);
	/* get new settings */
	hprotocolformat = ShowDialog->getHProtocolFormat();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (hprotocolformat)
			result = send(cmd_type,cmds.cmdSetHProtocolHeightVolumeformat,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetHProtocolHeightVolumeformat,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetPLLDWPLLDDurationBeforePrecisionRetestDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	int prectest; 

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	prectest = get_current_prectest(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setPrecisionTestDuration(prectest);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_prectestduration);
	/* get new settings */
	prectest = ShowDialog->getPrecisionTestDuration();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString pt;

		wProc->init(true); 
		wProc->increment();

		pt.sprintf("%03d",prectest);

		result = send(cmd_type,cmds.cmdSetPLLDWPLLDDurationBeforePrecisionRetest,
				lenCmd,1,pt,0,7,pt.Length(),'\0',7,pt.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetPeriodicLineLeakTestAutoConfirmDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool preclinetestauto02;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	preclinetestauto02 = get_current_preclinetestauto02(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setPrecisionLineTestAutoConfirm02(preclinetestauto02);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_preclinetestauto02);
	/* get new settings */
	preclinetestauto02 = ShowDialog->getPrecisionLineTestAutoConfirm02();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true); 
		wProc->increment();

		if (preclinetestauto02)
			result = send(cmd_type,cmds.cmdSetPeriodicLineLeakTestAutoConfirm,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetPeriodicLineLeakTestAutoConfirm,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetAnnualLineLeakTestAutoConfirmDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool preclinetestauto01;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows(); 
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	preclinetestauto01 = get_current_preclinetestauto01(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setPrecisionLineTestAutoConfirm02(preclinetestauto01);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_preclinetestauto01);
	/* get new settings */
	preclinetestauto01 = ShowDialog->getPrecisionLineTestAutoConfirm01();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (preclinetestauto01)
			result = send(cmd_type,cmds.cmdSetAnnualLineLeakTestAutoConfirm,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetAnnualLineLeakTestAutoConfirm,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetAutoDaylightSavingTimeDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool daylightsavings;
	int dlstartmonth, dlstartweekofmonth, dlstartdayofweek;
	TDateTime dlstarthour;
	int dlendmonth, dlendweekofmonth, dlenddayofweek;
	TDateTime dlendhour;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");

	/* get current enabled settings */
	get_computer_format_answer(cmds.cmdSetEnableDisableAutoDaylightSavingTime,"00",5,m);
	daylightsavings = get_current_daylightsavings(comm->global_buffer.c_str());
	wProc->increment();

	/* get current start date/time settings */
	get_computer_format_answer(cmds.cmdSetStartEndDaylightSavingDateandTime,"1",6,m);
	dlstartmonth = get_current_dlmonth(comm->global_buffer.c_str());
	dlstartweekofmonth = get_current_dlweekofmonth(comm->global_buffer.c_str());
	dlstartdayofweek = get_current_dldayofweek(comm->global_buffer.c_str());
	dlstarthour = get_current_dlhour(comm->global_buffer.c_str());
	wProc->increment();

	/* get current start date/time settings */
	get_computer_format_answer(cmds.cmdSetStartEndDaylightSavingDateandTime,"2",6,m);
	dlendmonth = get_current_dlmonth(comm->global_buffer.c_str());
	dlendweekofmonth = get_current_dlweekofmonth(comm->global_buffer.c_str());
	dlenddayofweek = get_current_dldayofweek(comm->global_buffer.c_str());
	dlendhour = get_current_dlhour(comm->global_buffer.c_str());
	wProc->increment(); 
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDaylightSavingsTime(daylightsavings);
	ShowDialog->setDLStartMonth(dlstartmonth);
	ShowDialog->setDLStartWeekOfMonth(dlstartweekofmonth);
	ShowDialog->setDLStartDayOfWeek(dlstartdayofweek);
	ShowDialog->setDLStartHour(dlstarthour);
	ShowDialog->setDLEndMonth(dlendmonth);
	ShowDialog->setDLEndWeekOfMonth(dlendweekofmonth);
	ShowDialog->setDLEndDayOfWeek(dlenddayofweek);
	ShowDialog->setDLEndHour(dlendhour);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_daylightsavingstime);
	/* get new settings */
	daylightsavings = ShowDialog->getDaylightSavingsTime();
	dlstartmonth = ShowDialog->getDLStartMonth();
	dlstartweekofmonth = ShowDialog->getDLStartWeekOfMonth();
	dlstartdayofweek = ShowDialog->getDLStartDayOfWeek();
	dlstarthour = ShowDialog->getDLStartHour();
	dlendmonth = ShowDialog->getDLEndMonth();
	dlendweekofmonth = ShowDialog->getDLEndWeekOfMonth();
	dlenddayofweek = ShowDialog->getDLEndDayOfWeek();
	dlendhour = ShowDialog->getDLEndHour();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();
		if (daylightsavings)
		{
			result = send(cmd_type,cmds.cmdSetEnableDisableAutoDaylightSavingTime,
				lenCmd,1,"1",0,7,1,'\0',7,1);
			wProc->increment();

			AnsiString dlsm, dlswom, dlsdow, dlsh, str = "";
			AnsiString dlem, dlewom, dledow, dleh;

			dlsm.sprintf("%02d",dlstartmonth);

			dlswom.sprintf("%d",dlstartweekofmonth);

			dlsdow.sprintf("%d",dlstartdayofweek);

			AnsiString timeformat = Sysutils::LongTimeFormat;
			Sysutils::LongTimeFormat = "HH:mm";
			dlsh = TimeToStr(dlstarthour);
			Sysutils::LongTimeFormat = timeformat;
			dlsh.Delete(3,1);

			str += "01";
			str += dlsm;
			str += dlswom;
			str += dlsdow;
			str += dlsh;

			result |= send(cmd_type,cmds.cmdSetStartEndDaylightSavingDateandTime,
				lenCmd,1,str,0,5,str.Length(),'\0',7,str.Length());
			wProc->increment();

			str = "";

			dlem.sprintf("%02d",dlendmonth);

			dlewom.sprintf("%d",dlendweekofmonth);

			dledow.sprintf("%d",dlenddayofweek);

			Sysutils::LongTimeFormat = "HH:mm";
			dleh = TimeToStr(dlendhour); 
        	Sysutils::LongTimeFormat = timeformat;
			dleh.Delete(3,1);

			str += "02";
			str += dlem;
			str += dlewom;
			str += dledow;
			str += dleh;

			result |= send(cmd_type,cmds.cmdSetStartEndDaylightSavingDateandTime,
				lenCmd,1,str,0,5,str.Length(),'\0',7,str.Length());
			wProc->increment();
		}
		else
		{
			result = send(cmd_type,cmds.cmdSetEnableDisableAutoDaylightSavingTime,
				lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		}       
		wProc->init(false);

    	/* get and display current settings */
		if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetRedirectLocalPrintoutFlagDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool redirectlocalpoflag; 

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	redirectlocalpoflag = get_current_redirectlocalpoflag(
												comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setReDirectLocalPrintout(redirectlocalpoflag);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_redirectlocalpo);
	/* get new settings */
	redirectlocalpoflag = ShowDialog->getReDirectLocalPrintout();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (redirectlocalpoflag)
			result = send(cmd_type,cmds.cmdSetRedirectLocalPrintoutFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetRedirectLocalPrintoutFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetHRMQPLDMonthlyPrintoutDlg(char cmd_type,
		int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool qpldmonthlypoflag; 

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	qpldmonthlypoflag = get_current_qpldmonthlypoflag(
												comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setQPLDMonthlyPrintout(qpldmonthlypoflag);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_qpldmonthlypo);
	/* get new settings */
	qpldmonthlypoflag = ShowDialog->getQPLDMonthlyPrintout();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (qpldmonthlypoflag)
			result = send(cmd_type,cmds.cmdSetHRMQPLDMonthlyPrintout,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetHRMQPLDMonthlyPrintout,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetEuroProtocolPrefixDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool europrotocolprefix;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows(); 
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	europrotocolprefix = get_current_europrotocolprefix(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setEuroProtocolPrefix(europrotocolprefix);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_europrotocolprefix);
	/* get new settings */
	europrotocolprefix = ShowDialog->getEuroProtocolPrefix();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (europrotocolprefix)
			result = send(cmd_type,cmds.cmdSetEuroProtocolPrefix,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetEuroProtocolPrefix,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetSystemRS232SecurityCodeDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString systemcode;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	systemcode = get_current_systemcode(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setSystemSecurityCode(systemcode);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_systemcode);
	/* get new settings */
	systemcode = ShowDialog->getSystemSecurityCode();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (systemcode=="")
		{
			systemcode.Insert(" ",1);
			systemcode.sprintf("%06s",systemcode);
    	}

		result = send(cmd_type,cmds.cmdSetSystemRS232SecurityCode,
				lenCmd,1,systemcode,0,7,systemcode.Length(),'\0',7,systemcode.Length());
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetCommunicationPortDataDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString devnumber = "1";
	AnsiString systemcode;
	int baud, parity, stopbit, bytesize, dialtype, answeron, modemtype,
	dialtoneinterval, dtrnormalstate;
	AnsiString syscode, setupstring;

	wProc->init(6,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d",ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	/* get and display current port settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get baud rate, parity, stop bit, bytesize, dial type and answer on time */
	get_computer_format_answer(cmds.cmdSetCommunicationPortData,devnumber,5,m);
	baud = get_current_baud(comm->global_buffer.c_str());
	parity = get_current_parity(comm->global_buffer.c_str());
	stopbit = get_current_stopbit(comm->global_buffer.c_str());
	bytesize = get_current_bytesize(comm->global_buffer.c_str());
	dialtype = get_current_dialtype(comm->global_buffer.c_str());
	answeron = get_current_answeron(comm->global_buffer.c_str());
	wProc->increment();

	/* get modem type */
	get_computer_format_answer(cmds.cmdSetSiteLinkModemType,devnumber,5,m);
	modemtype = get_current_modemtype(comm->global_buffer.c_str());
	wProc->increment();

	/* get dial tone interval */
	get_computer_format_answer(cmds.cmdSetDialToneValidationInterval,devnumber,5,m);
	dialtoneinterval = get_current_dialtoneinterval(comm->global_buffer.c_str()); 
	wProc->increment();

	/* get dtr normal state */
	get_computer_format_answer(cmds.cmdDTRNormalStateforSerialSatelliteBoards,devnumber,5,m);
	dtrnormalstate = get_current_dtrnormalstate(comm->global_buffer.c_str());
	wProc->increment();

	/* get security code */
	get_computer_format_answer(cmds.cmdSetRS232SecurityCodeperPort,devnumber,5,m);
	syscode = get_current_syscode(comm->global_buffer.c_str());
	wProc->increment();
                                                                 
	/* get mode setup string */
	get_computer_format_answer(cmds.cmdSetModemSetupString,devnumber,5,m);
	setupstring = get_current_setupstring(comm->global_buffer.c_str());
	wProc->increment(); 
	wProc->init(false);

	/* set all port values */
	ShowDialog->setBaudRate(baud);
	ShowDialog->setParity(parity);
	ShowDialog->setStopbit(stopbit);
	ShowDialog->setByteSize(bytesize);
	ShowDialog->setDialType(dialtype);
	ShowDialog->setAnswerOn(answeron);
	ShowDialog->setModemType(modemtype);
	ShowDialog->setDialToneInterval(dialtoneinterval);
	ShowDialog->setDTRNormalState(dtrnormalstate);
	ShowDialog->setSystemCode(syscode);
	ShowDialog->setSetupString(setupstring);

	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_portsettings);

	/* get all port values */
	baud = ShowDialog->getBaudRate();
	parity = ShowDialog->getParity();
	stopbit = ShowDialog->getStopbit();
	bytesize = ShowDialog->getByteSize();
	dialtype = ShowDialog->getDialType();
	answeron = ShowDialog->getAnswerOn();
	modemtype = ShowDialog->getModemType();
	dialtoneinterval = ShowDialog->getDialToneInterval();
	dtrnormalstate = ShowDialog->getDTRNormalState();
	syscode = ShowDialog->getSystemCode();
	setupstring = ShowDialog->getSetupString();

	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString settings = "";
		AnsiString dialtoneint = "";
		AnsiString modemt = "";
		AnsiString dtrns = "";

		wProc->init(true);
		wProc->increment();

		settings.printf("%05d",baud);
		settings.cat_printf("%d",parity);
		settings.cat_printf("%d",stopbit);
		settings.cat_printf("%d",bytesize);
		settings.cat_printf("%d",dialtype);
		settings.cat_printf("%02d",answeron);

		modemt.printf("%02d",modemtype);

		dialtoneint.printf("%04d",dialtoneinterval);

		dtrns.printf("%d",dtrnormalstate);

		if (syscode=="")
		{
			syscode.Insert(" ",1);
			syscode.printf("%07s",syscode);
    	}

		result = send(cmd_type,cmds.cmdSetCommunicationPortData,
				lenCmd,1,settings,0,7,settings.Length(),'\0',7,settings.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetSiteLinkModemType,
				lenCmd,1,modemt,0,7,settings.Length(),'\0',7,settings.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetDialToneValidationInterval,
				lenCmd,1,dialtoneint,0,7,settings.Length(),'\0',7,settings.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdDTRNormalStateforSerialSatelliteBoards,
				lenCmd,1,dtrns,0,7,settings.Length(),'\0',7,settings.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetRS232SecurityCodeperPort,
				lenCmd,1,syscode,0,7,settings.Length(),'\0',7,settings.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetModemSetupString,
				lenCmd,1,setupstring,0,7,settings.Length(),'\0',7,settings.Length());
		wProc->increment();

		copy_chars(devnumber.c_str(),0,cmds.cmdInitializeCommunicationPortData,5,2);
		result |= send(cmd_type,cmds.cmdInitializeCommunicationPortData,lenCmd,1,"0",0,100,10,'\0',0,0);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetReceiverConfigurationFlagDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString devnumber = "1";
	bool receiverconfig;
	AnsiString receiverlocation, receivertelnumber;
	int receiverportnumber, receivertype, receiverretrynumber, receiverdelaytime;
	bool receiverconfirmation;

	wProc->init(7,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d",ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	/* get and display current port settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get receiver configuration flag */
	get_computer_format_answer(cmds.cmdSetReceiverConfigurationFlag,devnumber,5,m);
	receiverconfig = get_current_receiverconfig(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver location label */
	get_computer_format_answer(cmds.cmdSetReceiverLocationLabel,devnumber,5,m);
	receiverlocation = get_current_receiverlocation(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver telephone number */
	get_computer_format_answer(cmds.cmdSetReceiverTelephoneNumber,devnumber,5,m);
	receivertelnumber = get_current_receivertelnumber(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver modem number */
	get_computer_format_answer(cmds.cmdSetReceiverPortNumbertoDial,devnumber,5,m);
	receiverportnumber = get_current_receiverportnumber(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver type */
	get_computer_format_answer(cmds.cmdSetReceiverDialingDestinationType,devnumber,5,m);
	receivertype = get_current_receivertype(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver retry number */
	get_computer_format_answer(cmds.cmdSetReceiverRetryNumber,devnumber,5,m);
	receiverretrynumber = get_current_receiverretrynumber(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver retry delay time */
	get_computer_format_answer(cmds.cmdSetReceiverRetryDelayTime,devnumber,5,m);
	receiverdelaytime = get_current_receiverdelaytime(comm->global_buffer.c_str());
	wProc->increment();

	/* get receiver confirmation report */
	get_computer_format_answer(cmds.cmdSetReceiverConfirmationReportFlag,devnumber,5,m);
	receiverconfirmation = get_current_receiverconfirmation(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* set */
	ShowDialog->setReceiverConfiguration(receiverconfig);
	ShowDialog->setReceiverLocation(receiverlocation);
	ShowDialog->setReceiverTelephoneNumber(receivertelnumber);
	ShowDialog->setReceiverPortNumber(receiverportnumber);
	ShowDialog->setReceiverType(receivertype);
	ShowDialog->setReceiverRetryNumber(receiverretrynumber);
	ShowDialog->setReceiverDelayTime(receiverdelaytime);
	ShowDialog->setReceiverConfirmation(receiverconfirmation);

	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_phonedirectory);

	/* get */
	receiverconfig = ShowDialog->getReceiverConfiguration();
	receiverlocation = ShowDialog->getReceiverLocation();
	receivertelnumber = ShowDialog->getReceiverTelephoneNumber();
	receiverportnumber = ShowDialog->getReceiverPortNumber();
	receivertype = ShowDialog->getReceiverType();
	receiverretrynumber = ShowDialog->getReceiverRetryNumber();
	receiverdelaytime = ShowDialog->getReceiverDelayTime();
	receiverconfirmation = ShowDialog->getReceiverConfirmation();

	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();
		if (receiverconfig)
		{
			AnsiString recportnr, rectype, recrnr, recdt;

			if (receiverlocation=="")
			{
				receiverlocation.Insert(" ",1);
				receiverlocation.sprintf("%020s",receiverlocation);
			}

			if (receivertelnumber=="")
			{
				receivertelnumber.Insert(" ",1);
				receivertelnumber.sprintf("%020s",receivertelnumber);
			}

			recportnr.sprintf("%d",receiverportnumber);
			rectype.sprintf("%02d",receivertype);
			recrnr.sprintf("%02d",receiverretrynumber);
			recdt.sprintf("%02d",receiverdelaytime);

			result |= send(cmd_type,cmds.cmdSetReceiverConfigurationFlag,
				lenCmd,1,"1",0,7,1,'\0',7,1);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetReceiverLocationLabel,
				lenCmd,1,receiverlocation,0,7,receiverlocation.Length(),'\0',5,receiverlocation.Length()+2);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetReceiverTelephoneNumber,
				lenCmd,1,receivertelnumber,0,7,receivertelnumber.Length(),'\0',5,receivertelnumber.Length()+2);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetReceiverDialingDestinationType,
				lenCmd,1,rectype,0,7,rectype.Length(),'\0',5,rectype.Length()+2);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetReceiverPortNumbertoDial,
				lenCmd,1,recportnr,0,7,recportnr.Length(),'\0',5,recportnr.Length()+2);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetReceiverRetryNumber,
				lenCmd,1,recrnr,0,7,recrnr.Length(),'\0',5,recrnr.Length()+2);
			wProc->increment();
			result |= send(cmd_type,cmds.cmdSetReceiverRetryDelayTime,
				lenCmd,1,recdt,0,7,recdt.Length(),'\0',5,recdt.Length()+2);
			wProc->increment();
			if (receiverconfirmation)
				result |= send(cmd_type,cmds.cmdSetReceiverConfirmationReportFlag,
					lenCmd,1,"1",0,7,1,'\0',7,1);
        	else
				result |= send(cmd_type,cmds.cmdSetReceiverConfirmationReportFlag,
					lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		}
		else
		{
			result |= send(cmd_type,cmds.cmdSetReceiverConfigurationFlag,
				lenCmd,1,"0",0,7,1,'\0',7,1);
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetReceiverReportListDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString devnumber = "1";
	bool reportlist[19] = {false,false,false,false,false,false,false,false,
						   false,false,false,false,false,false,false,false,
						   false,false,false};
	bool autodialmethod;
	int frequencytype = 1;
	TDateTime freqdate = 0, freqtime = 0;
	int freqmonth = 1;
	int freqweek = 1;
	int freqday = 1;
	bool birend = false; 

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d",ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	/* get and display current receiver report list */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get receiver configuration flag */
	get_computer_format_answer(cmds.cmdSetReceiverReportList,devnumber,5,m);
	get_current_reportlist(comm->global_buffer.c_str(), reportlist);
	wProc->increment();

	/* get and display current auti dial method */
	get_computer_format_answer(cmds.cmdSetFaxAutoDialMethod,devnumber,5,m);
	autodialmethod = get_current_autodialmethod(comm->global_buffer.c_str());
	wProc->increment();

	/* get and display auto dial frequency */
	get_computer_format_answer(cmds.cmdSetReceiverAutoDialTypeandStartTimeII,devnumber,5,m);
	frequencytype = get_current_frequencytype(comm->global_buffer.c_str());
	/* get and display frequency time */
	freqtime = get_current_freqtime(comm->global_buffer.c_str());

	/*on date: i520010612281125 01 0B 1 061228 EE00&&F935
	annually: i520010612281126 01 09 2 0111 EE00&&F9AC
	monthly: i520010612281127 01 07 3 11 EE00&&FA0D
	weekly: i520010612281127 01 06 4 1 EE00&&FA3E
	daily: i520010612281128 01 05 5 EE00&&FA6E
	bir end: i520010612281128 01 02 8 0&&FB28*/
	switch (frequencytype)
	{
		case 1:
			freqdate = get_current_freqdate(comm->global_buffer.c_str()); break;
		case 2:
			freqmonth = get_current_freqmonth(comm->global_buffer.c_str());
			freqweek = get_current_freqweek(comm->global_buffer.c_str());
			freqday = get_current_freqday(comm->global_buffer.c_str()); break;
		case 3:
			freqweek = get_current_freqweek(comm->global_buffer.c_str());
			freqday = get_current_freqday(comm->global_buffer.c_str()); break;
		case 4:
			freqday = get_current_freqday(comm->global_buffer.c_str()); break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8:
			birend = get_current_birend(comm->global_buffer.c_str()); break;
		default:;
	}          
	wProc->increment();
	wProc->init(false);

	/* set */
	ShowDialog->setReportList(reportlist);
	ShowDialog->setAutoDialMethod(autodialmethod);
	ShowDialog->setFrequencyType(frequencytype);
	ShowDialog->setFrequencyDate(freqdate);
	ShowDialog->setFrequencyTime(freqtime);
	ShowDialog->setFrequencyMonth(freqmonth);
	ShowDialog->setFrequencyWeek(freqweek);
	ShowDialog->setFrequencyDay(freqday);
	ShowDialog->setBIRend(birend);

	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_autodialsetup);

	/* get */
	ShowDialog->getReportList(reportlist);
	autodialmethod = ShowDialog->getAutoDialMethod();
	frequencytype = ShowDialog->getFrequencyType();
	freqdate = ShowDialog->getFrequencyDate();
	freqtime = ShowDialog->getFrequencyTime();
	freqmonth = ShowDialog->getFrequencyMonth();
	freqweek = ShowDialog->getFrequencyWeek();
	freqday = ShowDialog->getFrequencyDay();
	birend = ShowDialog->getBIRend();

	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString nrofreports = "19";
		AnsiString one_report_str = "";
		AnsiString method = "";
		AnsiString time;
		AnsiString freq_str = "";

		wProc->init(true);
		wProc->increment();

		copy_chars(devnumber.c_str(),0,cmds.cmdSetReceiverReportList,5,2);
		copy_chars(devnumber.c_str(),0,cmds.cmdSetFaxAutoDialMethod,5,2);
		copy_chars(devnumber.c_str(),0,cmds.cmdSetReceiverAutoDialTypeandStartTimeII,5,2);

		/* receiver report list */
		//19 0101 0201 0301 0400 0501 0601 0701 0801 0901 1000 1100 1201 1301
		//1400 1500 1601 1700 1801 1901
		for (int i=1; i < 20; i++)
		{
			AnsiString nr, state;
			nr.sprintf("%02d",i);
			state.sprintf("%02d",(int)reportlist[i-1]);
			one_report_str += nr;
			one_report_str += state;
		}
		one_report_str.Insert(nrofreports,1);

		/* auto dial method */
		method.sprintf("%d", autodialmethod);

		/* auto dial frequency */
		if ((double)freqtime==-1)	time = "EE00";
		else
		{
			try
			{
				AnsiString tfrm = Sysutils::LongTimeFormat;
				Sysutils::LongTimeFormat = "HH:mm";
				time = TimeToStr(freqtime);
				Sysutils::LongTimeFormat = tfrm;
				time.Delete(3,1);
			}
			catch(EConvertError &e)
			{
				time = "EE00";
			}
		}

		AnsiString fdate;
		AnsiString m, w, d;
		AnsiString dfrm = Sysutils::ShortDateFormat;
    	switch (frequencytype)
		{
			case 1:
				freq_str += "1";
				Sysutils::ShortDateFormat = "yyyy.mm.dd.";
				fdate = convert_date_time_string(freqdate.DateString());
				Sysutils::ShortDateFormat = dfrm;
				fdate.Delete(1,2);
				freq_str += fdate;
				freq_str += time;
				break;
			case 2:
				freq_str += "2";
				m.sprintf("%02d", freqmonth);
				w.sprintf("%d", freqweek);
				d.sprintf("%d", freqday);
				freq_str += m;
				freq_str += w;
				freq_str += d;
				freq_str += time;
				break;
			case 3:
				freq_str += "3";
				w.sprintf("%d", freqweek);
				d.sprintf("%d", freqday);
				freq_str += w;
				freq_str += d;
				freq_str += time;
				break;
			case 4:
				freq_str += "4";
				d.sprintf("%d", freqday);
				freq_str += d;
				freq_str += time;
				break;
			case 5:
				freq_str += "5";
				freq_str += time;
				break;
			case 6: break;
			case 7: break;
			case 8:
				freq_str += "8";
				if (birend)	freq_str += "1";
				else freq_str += "0";
				break;
			default:;
		}

		result |= send(cmd_type,cmds.cmdSetReceiverReportList,
				lenCmd,1,one_report_str,0,7,one_report_str.Length(),'\0',5,one_report_str.Length()+2);
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetFaxAutoDialMethod,
				lenCmd,1,method,0,7,method.Length(),'\0',5,method.Length()+2);
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetReceiverAutoDialTypeandStartTimeII,
				lenCmd,1,freq_str,0,7,freq_str.Length(),'\0',5,freq_str.Length()+2);
		wProc->increment();
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetReceiverAutoDialOnAlarmsDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;

	//ShowDialog = new TShowCmdSpecWindows();
	//ShowDialog->language = language;
	//ShowDialog->languagepath = languagepath;

	//cancel_from_dialog = ShowDialog->getModalResult();
	//if (cancel_from_dialog)	return 0;

	/* get and display current receiver report list */
	cancel_from_dialog = false;
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	/* get receiver configuration flag 
	get(page_idx, group_idx, item_idx, NULL, 'i', '0', devnumber.c_str());*/
	/* check data integrity 
	if (check_checksum(comm->global_buffer.c_str()))
	{
		read_comm_buffer_and_show_if_error(e_checksum, m);
	}*/

	/* set */

	/* display the dialog window */
	//ShowDialog->ShowDialogWindow(ShowDialog->dlg_autodialonalarms);

	/* get */

	//cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		;
	}

	/* free resources 
	delete ShowDialog;*/

	return result;
}

int TTLSDevice::showSetRS232EndofMessageDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	bool rs232eom; 

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	rs232eom = get_current_rs232eom(comm->global_buffer.c_str());
	wProc->init(false);

	/* display current settings */
	ShowDialog->setRS232EOM(rs232eom);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_rs232eom);
	/* get new settings */
	rs232eom = ShowDialog->getRS232EOM();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true); 
		wProc->increment();

		if (rs232eom)
			result |= send(cmd_type,cmds.cmdSetRS232EndofMessage,
				lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result |= send(cmd_type,cmds.cmdSetRS232EndofMessage,
				lenCmd,1,"0",0,7,1,'\0',7,1);
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetTankConfigurationDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool tankconfig[16] = {false,false,false,false,false,false,false,false,
						   false,false,false,false,false,false,false,false};

	wProc->init(16,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	/* get and show current settings */
	get_computer_format_answer(cmds.cmdSetTankConfiguration,"00",5,m);
	get_current_tankconfig(comm->global_buffer.c_str(), tankconfig);
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTankConfiguration(tankconfig);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tankconfig);
	/* get new settings */
	ShowDialog->getTankConfiguration(tankconfig);
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		char c;
		AnsiString cfg_str;

		wProc->init(true);
		wProc->increment();

		for (int i=0; i < 16; i++)
		{
        	cfg_str = "";
			cfg_str.sprintf("%02d",i+1);
			if (tankconfig[i])	c = '1';
			else c = '0';
			cfg_str += c;

			result |= send(cmd_type,cmds.cmdSetTankConfiguration,
				lenCmd,1,cfg_str,0,5,cfg_str.Length(),'\0',5,cfg_str.Length());
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetTankSetupDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	int unit;
	AnsiString productlabel;
	AnsiString productcode;
	float producttermalcoeff;
	float tankdiameter;
	bool meterdatapresent;
	int endfactor;
	float endvalue;
	int calibrationupdate;
	int floatsize;
	float waterwarning;
	float highwaterlimit;
	int maxorlabelvolume;
	int overfilllimit;
	float overfillprocent = 0;
	int highproductlimit;
	float highproductprocent = 0;
	int deliverylimit;
	float deliveryprocent = 0;
	int lowproductlimit;
	int leakalarmlimit;
	int suddenlosslimit;
	float tanktilt;
	float probeoffset;
	AnsiString manifoldedtanks;
	int leakminimumperiodic;
	float leakminprocent = 0;
	int leakminimumannual;
	float leakannprocent = 0;
	bool periodictesttype;
	bool annualtestfail;
	bool periodictestfail;
	bool grosstestfail;
	bool annualtestaveraging;
	bool periodictestaveraging;
	bool leaktestnotify;
	bool siphonbreak;
	float stickoffset;
	int hrmreconcwarnlimit;
	int hrmreconcalmlimit;
	int deliveryreportdt;
	float pumpthreshold;

	wProc->init(31,true);

	/* get current unit setting */
	get_computer_format_answer(cmds.cmdSetSystemTypeLanguageFlags1,"00",5,m);
	unit = get_current_unit(comm->global_buffer.c_str());

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d",ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}
	wProc->increment();

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get product label */
	get_computer_format_answer(cmds.cmdSetTankProductLabel,devnumber,5,m);
	productlabel = get_current_productlabel(comm->global_buffer.c_str());
	wProc->increment();

	/* get product code */
	get_computer_format_answer(cmds.cmdSetTankProductCode,devnumber,5,m);
	productcode = get_current_productcode(comm->global_buffer.c_str());
	wProc->increment();

	/* get product thermal coefficient */
	get_computer_format_answer(cmds.cmdSetTankThermalExpansionCoefficient,devnumber,5,m);
	producttermalcoeff = get_current_producttermalcoeff(comm->global_buffer.c_str());
	wProc->increment();

	/* get product tank diameter */
	get_computer_format_answer(cmds.cmdSetTankDiameter,devnumber,5,m);
	tankdiameter = get_current_tankdiameter(comm->global_buffer.c_str());
	wProc->increment();

	/* get meter data present */
	get_computer_format_answer(cmds.cmdSetBIRMeterDataPresent,devnumber,5,m);
	meterdatapresent = get_current_meterdatapresent(comm->global_buffer.c_str());
	wProc->increment();

	/* get end factor and end volume */
	get_computer_format_answer(cmds.cmdSetTankAccuChartEndShapeTypeandFactor,devnumber,5,m);
	endfactor = get_current_endfactor(comm->global_buffer.c_str());
	endvalue = get_current_endvalue(comm->global_buffer.c_str());
	wProc->increment();

	/* get calibration update */
	get_computer_format_answer(cmds.cmdSetAccuChartUpdateScheduling,devnumber,5,m);
	calibrationupdate = get_current_calibrationupdate(comm->global_buffer.c_str()); 
	wProc->increment();

	/* get float size */
	get_computer_format_answer(cmds.cmdSetMagProbeFloatSize,devnumber,5,m);
	floatsize = get_current_floatsize(comm->global_buffer.c_str());
	wProc->increment();

	/* get water warning */
	get_computer_format_answer(cmds.cmdSetTankHighWaterWarningLimit,devnumber,5,m);
	waterwarning = get_current_waterwarning(comm->global_buffer.c_str());
	wProc->increment();

	/* get high water limit */
	get_computer_format_answer(cmds.cmdSetTankHighWaterLevelLimit,devnumber,5,m);
	highwaterlimit = get_current_highwaterlimit(comm->global_buffer.c_str());
	wProc->increment();

	/* get max or label volume */
	get_computer_format_answer(cmds.cmdSetTankMaximumVolumeLimit,devnumber,5,m);
	maxorlabelvolume = get_current_maxorlabelvolume(comm->global_buffer.c_str());
	wProc->increment();

	/* get overfill limit */
	get_computer_format_answer(cmds.cmdSetTankOverfillLevelLimit,devnumber,5,m);
	overfilllimit = get_current_overfilllimit(comm->global_buffer.c_str());
	if (maxorlabelvolume > 0)	overfillprocent = ((float)overfilllimit/(float)maxorlabelvolume)*100;
	wProc->increment();

	/* get high product limit */
	get_computer_format_answer(cmds.cmdSetTankHighLevelLimit,devnumber,5,m);
	highproductlimit = get_current_highproductlimit(comm->global_buffer.c_str());
	if (maxorlabelvolume > 0)	highproductprocent = ((float)highproductlimit/(float)maxorlabelvolume)*100;
	wProc->increment();

	/* get delivery limit */
	get_computer_format_answer(cmds.cmdSetTankDeliveryRequiredLimit,devnumber,5,m);
	deliverylimit = get_current_deliverylimit(comm->global_buffer.c_str());
	if (maxorlabelvolume > 0)	deliveryprocent = ((float)deliverylimit/(float)maxorlabelvolume)*100;
	wProc->increment();

	/* get high product limit */
	get_computer_format_answer(cmds.cmdSetTankLowLevelLimit,devnumber,5,m);
	lowproductlimit = get_current_lowproductlimit(comm->global_buffer.c_str());
	wProc->increment();

	/* get leak alarm limit */
	get_computer_format_answer(cmds.cmdSetTankLeakAlarmLimit,devnumber,5,m);
	leakalarmlimit = get_current_leakalarmlimit(comm->global_buffer.c_str());
	wProc->increment();

	/* get sudden loss limit */
	get_computer_format_answer(cmds.cmdSetTankSuddenLossLimit,devnumber,5,m);
	suddenlosslimit = get_current_suddenlosslimit(comm->global_buffer.c_str());
	wProc->increment();

	/* get tank tilt */
	get_computer_format_answer(cmds.cmdSetTankTilt,devnumber,5,m);
	tanktilt = get_current_tanktilt(comm->global_buffer.c_str());
	wProc->increment();

	/* get probe offset */
	get_computer_format_answer(cmds.cmdSetTankProbeOffset,devnumber,5,m);
	probeoffset = get_current_probeoffset(comm->global_buffer.c_str());
	wProc->increment();

	/* get manifolded tank status (device number is "00" to get all tank
	   setting) */
	get_computer_format_answer(cmds.cmdSetTankManifoldedPartners,"00",5,m);
	manifoldedtanks = get_current_manifoldedtanks(comm->global_buffer.c_str());
	wProc->increment();

	/* get leak minimum periodic */
	get_computer_format_answer(cmds.cmdSetTankPeriodicLeakTestMinimumVolume,devnumber,5,m);
	leakminimumperiodic = get_current_leakminimumperiodic(comm->global_buffer.c_str());
	if (maxorlabelvolume > 0)	leakminprocent = ((float)leakminimumperiodic/(float)maxorlabelvolume)*100;
	wProc->increment();

	/* get leak minimum annual */
	get_computer_format_answer(cmds.cmdSetTankAnnualLeakTestMinimumVolume,devnumber,5,m);
	leakminimumannual = get_current_leakminimumannual(comm->global_buffer.c_str());
	if (maxorlabelvolume > 0)	leakannprocent = ((float)leakminimumannual/(float)maxorlabelvolume)*100;
	wProc->increment();

	/* get periodic test type */
	get_computer_format_answer(cmds.cmdSetTankPeriodicTestType,devnumber,5,m);
	periodictesttype = get_current_periodictesttype(comm->global_buffer.c_str());
	wProc->increment();

	/* get tank leak test fail alarms */
	get_computer_format_answer(cmds.cmdSetEnableDisableTankLeakTestFailAlarms,devnumber,5,m);
	annualtestfail = get_current_annualtestfail(comm->global_buffer.c_str());
	periodictestfail = get_current_periodictestfail(comm->global_buffer.c_str());
	grosstestfail = get_current_grosstestfail(comm->global_buffer.c_str());
	wProc->increment();

	/* get tank leak test averaging */
	get_computer_format_answer(cmds.cmdSetTankLeakTestAveraging,devnumber,5,m);
	annualtestaveraging = get_current_annualtestaveraging(comm->global_buffer.c_str());
	periodictestaveraging = get_current_periodictestaveraging(comm->global_buffer.c_str());
	wProc->increment();

	/* get tank test notify */
	get_computer_format_answer(cmds.cmdSetTankLeakTestNotify,devnumber,5,m);
	leaktestnotify = get_current_leaktestnotify(comm->global_buffer.c_str());
	wProc->increment();

	/* get tank test siphon break */
	get_computer_format_answer(cmds.cmdSetTankTestSiphonBreak,devnumber,5,m);
	siphonbreak = get_current_siphonbreak(comm->global_buffer.c_str());
	wProc->increment();

	/* get stick offset */
	get_computer_format_answer(cmds.cmdSetTankStickHeightOffset,devnumber,5,m);
	stickoffset = get_current_stickoffset(comm->global_buffer.c_str());
	wProc->increment();

	/* get hrm reconcilitation warning limit */
	get_computer_format_answer(cmds.cmdSetTankHRMReconciliationWarningLimit,devnumber,5,m);
	hrmreconcwarnlimit = get_current_hrmreconcwarnlimit(comm->global_buffer.c_str());
	wProc->increment();

	/* get hrm reconcilitation alarm limit */
	get_computer_format_answer(cmds.cmdSetTankHRMReconciliationAlarmLimit,devnumber,5,m);
	hrmreconcalmlimit = get_current_hrmreconcalmlimit(comm->global_buffer.c_str());
	wProc->increment();

	/* get delivery report delay time */
	get_computer_format_answer(cmds.cmdSetTankDeliveryDelay,devnumber,5,m);
	deliveryreportdt = get_current_deliveryreportdt(comm->global_buffer.c_str());
	wProc->increment();

	/* get pump threshold */
	get_computer_format_answer(cmds.cmdSetTankLowLevelThresholdforSequentialLineManifold,devnumber,5,m);
	pumpthreshold = get_current_pumpthreshold(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setProductLabel(productlabel);
	ShowDialog->setProductCode(productcode);
	ShowDialog->setProductThermalCoefficient(producttermalcoeff);
	ShowDialog->setTankDiameter(tankdiameter);
	ShowDialog->setMeterDataPresent(meterdatapresent);
	ShowDialog->setEndFactor(endfactor);
	ShowDialog->setEndValue(endvalue);
	ShowDialog->setCalibrationUpdate(calibrationupdate);
	ShowDialog->setFloatSize(floatsize);
	ShowDialog->setWaterWarning(waterwarning);
	ShowDialog->setHighWaterLimit(highwaterlimit);
	ShowDialog->setMaxOrLabelVolume(maxorlabelvolume);
	ShowDialog->setOverfillLimit(overfillprocent);
	ShowDialog->setHighProduct(highproductprocent);
	ShowDialog->setDeliveryLimit(deliveryprocent);
	ShowDialog->setLowProduct(lowproductlimit);
	ShowDialog->setLeakAlarmLimit(leakalarmlimit);
	ShowDialog->setSuddenLossLimit(suddenlosslimit);
	ShowDialog->setTankTilt(tanktilt);
	ShowDialog->setProbeOffset(probeoffset);
	ShowDialog->setManifoldedTanks(manifoldedtanks);
	ShowDialog->setLeakMinimumPeriodic(leakminprocent);
	ShowDialog->setLeakMinimumAnnual(leakannprocent);
	ShowDialog->setPeriodicTestType(periodictesttype);
	ShowDialog->setAnnualTestFail(annualtestfail);
	ShowDialog->setPeriodicTestFail(periodictestfail);
	ShowDialog->setGrossTestFail(grosstestfail);
	ShowDialog->setAnnualTestAveraging(annualtestaveraging);
	ShowDialog->setPeriodicTestAveraging(periodictestaveraging);
	ShowDialog->setLeakTestNotify(leaktestnotify);
	ShowDialog->setSiphonBreak(siphonbreak);
	ShowDialog->setStickOffset(stickoffset);
	ShowDialog->setHRMReconciliationWarnLimit(hrmreconcwarnlimit);
	ShowDialog->setHRMReconciliationAlarmLimit(hrmreconcalmlimit);
	ShowDialog->setDeliveryReportDelayTime(deliveryreportdt);
	ShowDialog->setPumpThreshold(pumpthreshold);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_intanksetup);
	/* get new settings */
	productlabel = ShowDialog->getProductLabel();
	productcode = ShowDialog->getProductCode();
	producttermalcoeff = ShowDialog->getProductThermalCoefficient();
	tankdiameter = ShowDialog->getTankDiameter(); 
	meterdatapresent = ShowDialog->getMeterDataPresent(); 
	endfactor = ShowDialog->getEndFactor();
	endvalue = ShowDialog->getEndValue();
	calibrationupdate = ShowDialog->getCalibrationUpdate();
	floatsize = ShowDialog->getFloatSize();  
	waterwarning = ShowDialog->getWaterWarning();
	highwaterlimit = ShowDialog->getHighWaterLimit(); 
	maxorlabelvolume = ShowDialog->getMaxOrLabelVolume();
	overfillprocent = ShowDialog->getOverfillLimit();
	highproductprocent = ShowDialog->getHighProduct();
	deliveryprocent = ShowDialog->getDeliveryLimit();
	lowproductlimit = ShowDialog->getLowProduct();
	leakalarmlimit = ShowDialog->getLeakAlarmLimit();
	suddenlosslimit = ShowDialog->getSuddenLossLimit();
	tanktilt = ShowDialog->getTankTilt();
	probeoffset = ShowDialog->getProbeOffset();
	manifoldedtanks = ShowDialog->getManifoldedTanks();
	leakminprocent = ShowDialog->getLeakMinimumPeriodic();
	leakannprocent = ShowDialog->getLeakMinimumAnnual();
	periodictesttype = ShowDialog->getPeriodicTestType();
	annualtestfail = ShowDialog->getAnnualTestFail();
	periodictestfail = ShowDialog->getPeriodicTestFail();
	grosstestfail = ShowDialog->getGrossTestFail();
	annualtestaveraging = ShowDialog->getAnnualTestAveraging();
	periodictestaveraging = ShowDialog->getPeriodicTestAveraging();
	leaktestnotify = ShowDialog->getLeakTestNotify();
	siphonbreak = ShowDialog->getSiphonBreak();
	stickoffset = ShowDialog->getStickOffset();
	hrmreconcwarnlimit = ShowDialog->getHRMReconciliationWarnLimit();
	hrmreconcalmlimit = ShowDialog->getHRMReconciliationAlarmLimit();
	deliveryreportdt = ShowDialog->getDeliveryReportDelayTime();
	pumpthreshold = ShowDialog->getPumpThreshold();

	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString formatted_str = "";

		wProc->init(true);
		wProc->increment();

		/* product label */
		if (productlabel=="")
		{
			productlabel.Insert(" ",1);
			productlabel.sprintf("%20s",productlabel);
		}
		result |= send(cmd_type,cmds.cmdSetTankProductLabel,
				lenCmd,1,productlabel,0,7,productlabel.Length(),'\0',5,productlabel.Length()+2);
		wProc->increment();

		/* product code */
		if (productcode=="")	productcode.Insert(" ",1);
		result |= send(cmd_type,cmds.cmdSetTankProductCode,
				lenCmd,1,productcode,0,7,productcode.Length(),'\0',5,productcode.Length()+2);
		wProc->increment();

		/* thermal coefficient */
		formatted_str = "";
		formatted_str.sprintf("%7.5f", producttermalcoeff);

		result |= send(cmd_type,cmds.cmdSetTankThermalExpansionCoefficient,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* tank diameter */
		formatted_str = "";
		if ( (unit==1) || (unit==3) )	formatted_str.sprintf("%06.2f", tankdiameter);
		if (unit==2)	formatted_str.sprintf("%07.2f", tankdiameter);

		result |= send(cmd_type,cmds.cmdSetTankDiameter,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* meter data present */
		if (!meterdatapresent)
			result |= send(cmd_type,cmds.cmdSetBIRMeterDataPresent,
				lenCmd,1,"0",0,7,1,'\0',5,3);
		else
			result |= send(cmd_type,cmds.cmdSetBIRMeterDataPresent,
				lenCmd,1,"1",0,7,1,'\0',5,3);
		wProc->increment();

		/* end factor and end value */
		formatted_str = "";
		formatted_str.sprintf("%d", endfactor);
		formatted_str.cat_sprintf("%3.1f", endvalue);
		result |= send(cmd_type,cmds.cmdSetTankAccuChartEndShapeTypeandFactor,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* calibration update */
		formatted_str = "";
		formatted_str.sprintf("%d", calibrationupdate);

		result |= send(cmd_type,cmds.cmdSetAccuChartUpdateScheduling,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* float size */
		formatted_str = "";
		formatted_str.sprintf("%d", floatsize);

		result |= send(cmd_type,cmds.cmdSetMagProbeFloatSize,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* water warning */
		formatted_str = "";
		if ( (unit==1) || (unit==3) )	formatted_str.sprintf("%04.1f", waterwarning);
		if (unit==2)	formatted_str.sprintf("%05.1f", waterwarning);

		result |= send(cmd_type,cmds.cmdSetTankHighWaterWarningLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* high water limit */
		formatted_str = "";
		if ( (unit==1) || (unit==3) )	formatted_str.sprintf("%04.1f", highwaterlimit);
		if (unit==2)	formatted_str.sprintf("%05.1f", highwaterlimit);

		result |= send(cmd_type,cmds.cmdSetTankHighWaterLevelLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* max or label volume */
		formatted_str = "";
		formatted_str.sprintf("%06d", maxorlabelvolume);

		result |= send(cmd_type,cmds.cmdSetTankMaximumVolumeLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* overfill limit */
    	overfilllimit = maxorlabelvolume*(overfillprocent/100);
		formatted_str = "";
		formatted_str.sprintf("%06d", overfilllimit);

		result |= send(cmd_type,cmds.cmdSetTankOverfillLevelLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* high product limit */
		highproductlimit = maxorlabelvolume*(highproductprocent/100);
		formatted_str = "";
		formatted_str.sprintf("%06d", highproductlimit);

		result |= send(cmd_type,cmds.cmdSetTankHighLevelLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* delivery limit */  
		deliverylimit = maxorlabelvolume*(deliveryprocent/100);
		formatted_str = "";
		formatted_str.sprintf("%06d", deliverylimit);

		result |= send(cmd_type,cmds.cmdSetTankDeliveryRequiredLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* low product limit */
		formatted_str = "";
		formatted_str.sprintf("%06d", lowproductlimit);

		result |= send(cmd_type,cmds.cmdSetTankLowLevelLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* leak alarm limit */
		formatted_str = "";
		formatted_str.sprintf("%06d", leakalarmlimit);

		result |= send(cmd_type,cmds.cmdSetTankLeakAlarmLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* sudden loss limit */
		formatted_str = "";
		formatted_str.sprintf("%06d", suddenlosslimit);

		result |= send(cmd_type,cmds.cmdSetTankSuddenLossLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* tank tilt */
		formatted_str = "";
		if ( (unit==1) || (unit==3) )	formatted_str.sprintf("%+06.2f", tanktilt);
		if (unit==2)	formatted_str.sprintf("%+06.1f", tanktilt);

		result |= send(cmd_type,cmds.cmdSetTankTilt,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* probe offset */
		formatted_str = "";
		if ( (unit==1) || (unit==3) )	formatted_str.sprintf("%+06.2f", probeoffset);
		if (unit==2)	formatted_str.sprintf("%+06.1f", probeoffset);

		result |= send(cmd_type,cmds.cmdSetTankProbeOffset,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* manifolded tanks */
		formatted_str = "";
		int comma_pos = manifoldedtanks.Pos(",");
		while (comma_pos > 1)
		{
			manifoldedtanks.Delete(comma_pos,1);
        	comma_pos = manifoldedtanks.Pos(",");
		}

		result |= send(cmd_type,cmds.cmdSetTankManifoldedPartners,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* leak minimum periodic */
		leakminimumperiodic = maxorlabelvolume*(leakminprocent/100);
		formatted_str = "";
		formatted_str.sprintf("%06d", leakminimumperiodic);

		result |= send(cmd_type,cmds.cmdSetTankPeriodicLeakTestMinimumVolume,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* leak minimum annual */
		leakminimumannual = maxorlabelvolume*(leakannprocent/100);
		formatted_str = "";
		formatted_str.sprintf("%06d", leakminimumannual);

		result |= send(cmd_type,cmds.cmdSetTankAnnualLeakTestMinimumVolume,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* periodic test type */
		if (!periodictesttype)
			result |= send(cmd_type,cmds.cmdSetTankPeriodicTestType,
				lenCmd,1,"0",0,7,1,'\0',5,3);
		else
			result |= send(cmd_type,cmds.cmdSetTankPeriodicTestType,
				lenCmd,1,"1",0,7,1,'\0',5,3); 
		wProc->increment();

		/* annual, periodic and gross test fail alarms */
		formatted_str = "";
		if (!grosstestfail)	formatted_str += "0";
		else	formatted_str += "1";

		if (!periodictestfail)	formatted_str += "0";
		else	formatted_str += "1";

		if (!annualtestfail)	formatted_str += "0";
		else	formatted_str += "1";

		result |= send(cmd_type,cmds.cmdSetEnableDisableTankLeakTestFailAlarms,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* annual and periodic test averaging */
		formatted_str = "";
		if (!annualtestaveraging)	formatted_str += "0";
		else	formatted_str += "1";

		if (!periodictestaveraging)	formatted_str += "0";
		else	formatted_str += "1";
		result |= send(cmd_type,cmds.cmdSetTankLeakTestAveraging,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* leak test notify */
		if (!leaktestnotify)
			result |= send(cmd_type,cmds.cmdSetTankLeakTestNotify,
				lenCmd,1,"0",0,7,1,'\0',5,3);
		else
			result |= send(cmd_type,cmds.cmdSetTankLeakTestNotify,
				lenCmd,1,"1",0,7,1,'\0',5,3);
		wProc->increment();

		/* tank test siphon break */
		if (!siphonbreak)
			result |= send(cmd_type,cmds.cmdSetTankTestSiphonBreak,
				lenCmd,1,"0",0,7,1,'\0',5,3);
		else
			result |= send(cmd_type,cmds.cmdSetTankTestSiphonBreak,
				lenCmd,1,"1",0,7,1,'\0',5,3);
		wProc->increment();

		/* stick offset */
		formatted_str = "";
		formatted_str.sprintf("%+06.2f", stickoffset);

		result |= send(cmd_type,cmds.cmdSetTankStickHeightOffset,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* hrm reconciliation warning limit */
		formatted_str = "";
		formatted_str.sprintf("%06d", hrmreconcwarnlimit);

		result |= send(cmd_type,cmds.cmdSetTankHRMReconciliationWarningLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* hrm reconciliation alarm limit */
		formatted_str = "";
		formatted_str.sprintf("%06d", hrmreconcalmlimit);

		result |= send(cmd_type,cmds.cmdSetTankHRMReconciliationAlarmLimit,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* delivery report delay time */
		formatted_str = "";
		formatted_str.sprintf("%02d", deliveryreportdt);
		result |= send(cmd_type,cmds.cmdSetTankDeliveryDelay,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		/* pump threshold */
		formatted_str = "";
		formatted_str.sprintf("%05.2f", pumpthreshold);

		result |= send(cmd_type,cmds.cmdSetTankLowLevelThresholdforSequentialLineManifold,
				lenCmd,1,formatted_str,0,7,formatted_str.Length(),'\0',5,formatted_str.Length()+2);
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */

	return result;
}
int TTLSDevice::showSetTankLinearCalculatedFullVolumeDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString tankprofile[20];
	int tankprofiletype;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get tank profile volumes with the command tank 20 point volumes */
	get_computer_format_answer(cmds.cmdSetTank20PointFull,devnumber,5,m);
	get_current_tankprofile(comm->global_buffer.c_str(), tankprofile);
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTankProfile(tankprofile);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tankprofile);
	/* get new settings */
	ShowDialog->getTankProfile(tankprofile);
	tankprofiletype = ShowDialog->getTankProfileType();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		AnsiString volumes = "";

		wProc->init(true);
		wProc->increment();

		switch (tankprofiletype)
		{
			case 0:
				copy_chars(devnumber.c_str(),0,cmds.cmdSetTankLinearCalculatedFullVolume,5,devnumber.Length());
				volumes += tankprofile[0];
				result |= send(cmd_type,cmds.cmdSetTankLinearCalculatedFullVolume,
					lenCmd,1,volumes,0,7,volumes.Length(),'\0',5,volumes.Length()+2);
				break;
			case 1:
				copy_chars(devnumber.c_str(),0,cmds.cmdSetTank1PointFullHeightVolume,5,devnumber.Length());
				volumes += tankprofile[0];
				result |= send(cmd_type,cmds.cmdSetTank1PointFullHeightVolume,
					lenCmd,1,volumes,0,7,volumes.Length(),'\0',5,volumes.Length()+2);
				break;
			case 2:
				copy_chars(devnumber.c_str(),0,cmds.cmdSetTank4PointFull,5,devnumber.Length());
				for (int j=3; j >= 0; j--)
				{
					volumes += tankprofile[j];
					if (j > 0)	volumes += ",";
				}
				result |= send(cmd_type,cmds.cmdSetTank4PointFull,
					lenCmd,1,volumes,0,7,volumes.Length(),'\0',5,volumes.Length()+2);
				break;
			case 3:
				copy_chars(devnumber.c_str(),0,cmds.cmdSetTank20PointFull,5,devnumber.Length());
				for (int j=19; j >= 0; j--)
				{
					volumes += tankprofile[j];
                	if (j > 0)	volumes += ",";
				}
				result |= send(cmd_type,cmds.cmdSetTank20PointFull,
					lenCmd,1,volumes,0,7,volumes.Length(),'\0',5,volumes.Length()+2);
				break;
			default:;
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	return result;
}

int TTLSDevice::showSetMechanicalDispenserinterfaceStringDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString dimversion;
	AnsiString mdim_string, edim_string;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get mechanical dim string */
	get_computer_format_answer(cmds.cmdDIMSoftwareRevision,devnumber,5,m);
	dimversion = get_current_dimversion(comm->global_buffer.c_str());
	wProc->increment();

	/* get mechanical dim string */
	get_computer_format_answer(cmds.cmdSetMechanicalDispenserInterfaceString,devnumber,5,m);
	mdim_string = get_current_mdimstring(comm->global_buffer.c_str());
	wProc->increment();

	/* get electronic dim string */
	get_computer_format_answer(cmds.cmdSetElectronicDispenserInterfaceString,devnumber,5,m);
	edim_string = get_current_edimstring(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setDIMVersion(dimversion);
	ShowDialog->setMDIMString(mdim_string);
	ShowDialog->setEDIMString(edim_string);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_dimstring);
	/* get new settings */
	mdim_string = ShowDialog->getMDIMString();
	edim_string = ShowDialog->getEDIMString();
	cancel_from_dialog = ShowDialog->getModalResult();


	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		result = send(cmd_type,cmds.cmdSetMechanicalDispenserInterfaceString,
					lenCmd,1,mdim_string,0,7,mdim_string.Length(),'\0',5,mdim_string.Length()+2);
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetElectronicDispenserInterfaceString,
					lenCmd,1,mdim_string,0,7,mdim_string.Length(),'\0',5,mdim_string.Length()+2);

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	return result;
}

int TTLSDevice::showSetReconciliationAutoDailyClosingTimeDlg(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	TDateTime autodailyclosing;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	autodailyclosing = get_current_autodailyclosing(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setAutoDailyClosing(autodailyclosing);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_autodailyclosing);
	/* get new settings */
	autodailyclosing = ShowDialog->getAutoDailyClosing();
	cancel_from_dialog = ShowDialog->getModalResult();


	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString timeformat = Sysutils::LongTimeFormat;
		Sysutils::LongTimeFormat = "HH:mm";
		AnsiString timestr = autodailyclosing.TimeString();
		Sysutils::LongTimeFormat = timeformat;

		timestr.Delete(3,1);

		result = send(cmd_type,cmds.cmdSetReconciliationAutoDailyClosingTime,
					lenCmd,1,timestr,0,7,timestr.Length(),'\0',7,timestr.Length());

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");

	return result;
}

int TTLSDevice::showSetAutoShiftClosingTime1234(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result;
	AnsiString shifttime_index;
	bool shiftclosing1, shiftclosing2, shiftclosing3, shiftclosing4;
	TDateTime shifttime1, shifttime2, shifttime3, shifttime4;
	const AnsiString shifttime_disabled = "EE00";

	wProc->init(4,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();

	if (m)
	{
		/* get and display current settings */
		for (int i=1; i < 5; i++)
		{
			shifttime_index.sprintf("%02d",i);
			get(page_idx, group_idx, item_idx, m, 'I', '0', shifttime_index.c_str());
		}
	}
	/* get and show current settings */
	for (int i=1; i < 5; i++)
	{
		shifttime_index.sprintf("%02d",i);
		get(page_idx, group_idx, item_idx, NULL, 'i', '0', shifttime_index.c_str());
		/* check data integrity */
		if (check_checksum(comm->global_buffer.c_str()))
		{
			read_comm_buffer_and_show_if_error(e_checksum, m);
		}

		if (i==1)
		{
			shifttime1 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime1 > -1.0)	shiftclosing1 = true;
			else	shiftclosing1 = false;
		}
		if (i==2)
		{
			shifttime2 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime2 > -1.0)	shiftclosing2 = true;
			else	shiftclosing2 = false;
		}
		if (i==3)
		{
			shifttime3 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime3 > -1.0)	shiftclosing3 = true;
			else	shiftclosing3 = false;
		}
		if (i==4)
		{
			shifttime4 = get_current_shifttime(comm->global_buffer.c_str());
			if ((double)shifttime4 > -1.0)	shiftclosing4 = true;
			else	shiftclosing4 = false;
		}    
		wProc->increment();
	}
	wProc->init(false);
	/* display current settings */
	ShowDialog->setShifttime1(TimeToStr(shifttime1));
	ShowDialog->setShifttime2(TimeToStr(shifttime2));
	ShowDialog->setShifttime3(TimeToStr(shifttime3));
	ShowDialog->setShifttime4(TimeToStr(shifttime4));
	ShowDialog->setShiftclosing1(shiftclosing1);
	ShowDialog->setShiftclosing2(shiftclosing2);
	ShowDialog->setShiftclosing3(shiftclosing3);
	ShowDialog->setShiftclosing4(shiftclosing4);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_shiftclosingtimes);
	/* get new settings */
	shifttime1 = ShowDialog->getShifttime1();
	shifttime2 = ShowDialog->getShifttime2();
	shifttime3 = ShowDialog->getShifttime3();
	shifttime4 = ShowDialog->getShifttime4();
	shiftclosing1 = ShowDialog->getShiftclosing1();
	shiftclosing2 = ShowDialog->getShiftclosing2();
	shiftclosing3 = ShowDialog->getShiftclosing3();
	shiftclosing4 = ShowDialog->getShiftclosing4();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
    	AnsiString timeformat = Sysutils::LongTimeFormat;
		Sysutils::LongTimeFormat = "HH:mm";
		AnsiString new_time;

		wProc->init(true);
		wProc->increment();

		for (int i=1; i < 5; i++)
		{
			shifttime_index.sprintf("%02d",i);

			if (i==1)
			{
				if (shiftclosing1)
				{
					new_time = shifttime1.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}
			if (i==2)
			{
				if (shiftclosing2)
				{
					new_time = shifttime2.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}
			if (i==3)
			{
				if (shiftclosing3)
				{
					new_time = shifttime3.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}
			if (i==4)
			{
				if (shiftclosing4)
				{
					new_time = shifttime4.TimeString();

					new_time = convert_date_time_string(new_time);
				}
				else	new_time = shifttime_disabled;
			}

			new_time.Insert(shifttime_index,1);

			result = send(cmd_type,cmds.cmdSetAutoShiftClosingTime1234,
				lenCmd,1,new_time,0,5,new_time.Length(),'\0',5,8);
			wProc->increment();
		}

		wProc->init(false);
		Sysutils::LongTimeFormat = timeformat;

		if (m)
		{
			/* get and display current settings */
			for (int i=1; i < 5; i++)
			{
				shifttime_index.sprintf("%02d",i);
				get(page_idx, group_idx, item_idx, m, 'I', '0', shifttime_index.c_str());
			}
		}
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetPeriodicReconciliationMode(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	int periodicreconcmode;
	int periodicreconclen;

	wProc->init(2,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;
	wProc->increment();

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");

	/* get periodic reconciliation mode */
	get_computer_format_answer(cmds.cmdSetPeriodicReconciliationMode,"00",5,m);
	periodicreconcmode = get_current_periodicreconcmode(comm->global_buffer.c_str());
	wProc->increment();

	/* get periodic recinciliation length */
	get_computer_format_answer(cmds.cmdSetPeriodicReconciliationReportLength,"00",5,m);
	periodicreconclen = get_current_periodicreconclen(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setPeriodicReconciliationMode(periodicreconcmode);
	ShowDialog->setPeriodicRecinciliationLength(periodicreconclen);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_periodicreconcmode);
	/* get new settings */
	periodicreconcmode = ShowDialog->getPeriodicReconciliationMode();
	periodicreconclen = ShowDialog->getPeriodicReconciliationLength();
	cancel_from_dialog = ShowDialog->getModalResult();


	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();
		AnsiString mode, len;

		mode.sprintf("%02d",periodicreconcmode);
		len.sprintf("%02d",periodicreconclen);

		result = send(cmd_type,cmds.cmdSetPeriodicReconciliationMode,
					lenCmd,1,mode,0,7,mode.Length(),'\0',7,mode.Length());

		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetPeriodicReconciliationReportLength,
					lenCmd,1,len,0,7,len.Length(),'\0',7,len.Length());

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");

	return result;
}

int TTLSDevice::showSetPeriodicReconciliationAlarmFlag(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	int perreconcalmonoff;
	float perreconcalmthreshold;
	int perreconcalmoffset;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;
	wProc->increment();

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");

	/* get periodic reconciliation mode */
	get_computer_format_answer(cmds.cmdSetPeriodicReconciliationAlarmFlag,"00",5,m);
	perreconcalmonoff = get_current_perreconcalmonoff(comm->global_buffer.c_str());
	wProc->increment();

	/* get periodic recinciliation length */
	get_computer_format_answer(cmds.cmdSetPeriodicReconciliationAlarmThreshold,"00",5,m);
	perreconcalmthreshold = get_current_perreconcalmthreshold(comm->global_buffer.c_str());
	wProc->increment();

	/* get periodic recinciliation length */
	get_computer_format_answer(cmds.cmdSetPeriodicReconciliationAlarmOffset,"00",5,m);
	perreconcalmoffset = get_current_perreconcalmoffset(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setIsPerReconcAlm(perreconcalmonoff);
	ShowDialog->setPerReconcAlmThreshold(perreconcalmthreshold);
	ShowDialog->setPerReconcAlmOffset(perreconcalmoffset);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_perreconcalm);
	/* get new settings */
	perreconcalmonoff = ShowDialog->getIsPerReconcAlm();
	perreconcalmthreshold = ShowDialog->getPerReconcAlmThreshold();
	perreconcalmoffset = ShowDialog->getPerReconcAlmOffset();
	cancel_from_dialog = ShowDialog->getModalResult();


	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();
		AnsiString praf, prath, praof;

		praf.sprintf("%02d",perreconcalmonoff);
		prath.sprintf("%04.2f",perreconcalmthreshold);
		praof.sprintf("%06d",perreconcalmoffset);

		result = send(cmd_type,cmds.cmdSetPeriodicReconciliationAlarmFlag,
					lenCmd,1,praf,0,7,praf.Length(),'\0',7,praf.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetPeriodicReconciliationAlarmThreshold,
					lenCmd,1,prath,0,7,prath.Length(),'\0',7,prath.Length());
		wProc->increment();
    	result |= send(cmd_type,cmds.cmdSetPeriodicReconciliationAlarmOffset,
					lenCmd,1,praof,0,7,praof.Length(),'\0',7,praof.Length());
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "");

	return result;
}

int TTLSDevice::showSetRemotePrinterReconciliationReportFormat(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	int remotereportformat;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	remotereportformat = get_current_remotereportformat(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setRemoteReportFormat(remotereportformat);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_remotereportformat);
	/* get new settings */
	remotereportformat = ShowDialog->getRemoteReportFormat();
	cancel_from_dialog = ShowDialog->getModalResult();


	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString rrfrmt;

		rrfrmt.sprintf("%02d",remotereportformat);

		result = send(cmd_type,cmds.cmdSetRemotePrinterReconciliationReportFormat,
					lenCmd,1,rrfrmt,0,7,rrfrmt.Length(),'\0',7,rrfrmt.Length());

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetBIRTemperatureCompensationFlag(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool tempcompensation;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	tempcompensation = get_current_tempcompensation(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setTempCompensation(tempcompensation);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_tempcompensation);
	/* get new settings */
	tempcompensation = ShowDialog->getTempCompensation();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		if (tempcompensation)
			result = send(cmd_type,cmds.cmdSetBIRTemperatureCompensationFlag,
					lenCmd,1,"1",0,7,1,'\0',7,1);
		else
			result = send(cmd_type,cmds.cmdSetBIRTemperatureCompensationFlag,
					lenCmd,1,"0",0,7,1,'\0',7,1);

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetMeterCalibrationOffset(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	float metercaliboffset;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	metercaliboffset = get_current_metercaliboffset(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setMeterCalibrationOffset(metercaliboffset);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_metercaliboffset);
	/* get new settings */
	metercaliboffset = ShowDialog->getMeterCalibrationOffset();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString metcalofs;

		metcalofs.sprintf("%+05.3f",metercaliboffset);
		result = send(cmd_type,cmds.cmdSetMeterCalibrationOffset,
			lenCmd,1,metcalofs,0,7,metcalofs.Length(),'\0',7,metcalofs.Length());

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetBIRMeterTankmapping(char cmd_type,
	int page_idx, int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	int bustype, slotnr, fuelpos, meter, tanknr;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);
	/* get and show current settings */
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_modifytankmetermap);
	/* get new settings */
	bustype = ShowDialog->getBusType();
	slotnr = ShowDialog->getSlotNumber();
	fuelpos = ShowDialog->getFuelPosition();
	meter = ShowDialog->getMeter();
	tanknr = ShowDialog->getTankNumber();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString bust, slotn, fuelp, mtr, tankn, str = "";

		bust.sprintf("%d",bustype);
		str += bust+" ";
		slotn.sprintf("%d",slotnr);
		str += slotn+" ";
		fuelp.sprintf("%02d",fuelpos);
		str += fuelp+" ";
		mtr.sprintf("%d",meter);
		str += mtr+" ";
		tankn.sprintf("%02d",tanknr);
    	str += tankn;

		result = send(cmd_type,cmds.cmdSetBIRMeterTankmapping,
			lenCmd,1,str,0,7,str.Length(),'\0',7,str.Length());

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	return result;
}

int TTLSDevice::showSetLiquidSensorConfigurationDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool liquidsensorconfig[32] = {false,false,false,false,false,false,false,false,
							 false,false,false,false,false,false,false,false,
							 false,false,false,false,false,false,false,false,
							 false,false,false,false,false,false,false,false};

	wProc->init(32,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");
	/* get and show current settings on the dialog window */
	get_computer_format_answer(cmds.cmdSetLiquidSensorConfiguration,"00",5,m);
	get_current_liquidsensorconfig(comm->global_buffer.c_str(), liquidsensorconfig);
	wProc->init(false);

	/* display current settings */
	ShowDialog->setLiquidSensorConfiguration(liquidsensorconfig);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_liquidsensorconfig);
	/* get new settings */
	ShowDialog->getLiquidSensorConfiguration(liquidsensorconfig);
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		char c;
		AnsiString cfg_str;

		wProc->init(true);
		wProc->increment();

		for (int i=0; i < 32; i++)
		{
        	cfg_str = "";
			cfg_str.sprintf("%02d",i+1);
			if (liquidsensorconfig[i])	c = '1';
			else c = '0';
			cfg_str += c;

			result |= send(cmd_type,cmds.cmdSetLiquidSensorConfiguration,
				lenCmd,1,cfg_str,0,5,cfg_str.Length(),'\0',5,cfg_str.Length());
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetLiquidSensorSetupDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString liqsenslocation;
	int liqsenstype;
	int liqsenscategory;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get sensor location string */
	get_computer_format_answer(cmds.cmdSetLiquidSensorLocationLabel,devnumber,5,m);
	liqsenslocation = get_current_liqsenslocation(comm->global_buffer.c_str());
	wProc->increment();

	/* get sensor type */
	get_computer_format_answer(cmds.cmdSetLiquidSensorType,devnumber,5,m);
	liqsenstype = get_current_liqsenstype(comm->global_buffer.c_str());
	wProc->increment();

	/* get sensor category */
	get_computer_format_answer(cmds.cmdSetLiquidSensorCategory,devnumber,5,m);
	liqsenscategory = get_current_liqsenscategory(comm->global_buffer.c_str());
	wProc->increment();

	wProc->init(false);

	/* display current settings */
	ShowDialog->setLiquidSensorLocation(liqsenslocation);
	ShowDialog->setLiquidSensorType(liqsenstype);
	ShowDialog->setLiquidSensorCategory(liqsenscategory);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_liqsenssetup);
	/* get new settings */
	liqsenslocation = ShowDialog->getLiquidSensorLocation();
	liqsenstype = ShowDialog->getLiquidSensorType();
	liqsenscategory = ShowDialog->getLiquidSensorCategory();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{                       
		wProc->init(true);
		wProc->increment();

		AnsiString styp, scat;

		if (liqsenslocation=="")
		{
			liqsenslocation.Insert(" ",1);
			liqsenslocation.sprintf("%020s",liqsenslocation);
    	}
		styp.sprintf("%d",liqsenstype);
		scat.sprintf("%d",liqsenscategory);

		result = send(cmd_type,cmds.cmdSetLiquidSensorLocationLabel,lenCmd,1,
			liqsenslocation,0,7,liqsenslocation.Length(),'\0',7,liqsenslocation.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetLiquidSensorType,lenCmd,1,
			styp,0,7,styp.Length(),'\0',7,styp.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetLiquidSensorCategory,lenCmd,1,
			scat,0,7,scat.Length(),'\0',7,scat.Length());
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetVaporSensorConfigurationDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool vaporsensorconfig[20] = {false,false,false,false,false,
								  false,false,false,false,false,
								  false,false,false,false,false,
								  false,false,false,false,false};

	wProc->init(20,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");
	/* get and show current settings on the dialog window */
	get_computer_format_answer(cmds.cmdSetVaporSensorConfiguration,"00",5,m);
	get_current_vaporsensorconfig(comm->global_buffer.c_str(), vaporsensorconfig);
	wProc->init(false);

	/* display current settings */
	ShowDialog->setVaporSensorConfiguration(vaporsensorconfig);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_vaporsensconfig);
	/* get new settings */
	ShowDialog->getVaporSensorConfiguration(vaporsensorconfig);
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		char c;
		AnsiString cfg_str;

		wProc->init(true);
		wProc->increment();

		for (int i=0; i < 20; i++)
		{
        	cfg_str = "";
			cfg_str.sprintf("%02d",i+1);
			if (vaporsensorconfig[i])	c = '1';
			else c = '0';
			cfg_str += c;

			result |= send(cmd_type,cmds.cmdSetVaporSensorConfiguration,
				lenCmd,1,cfg_str,0,5,cfg_str.Length(),'\0',5,cfg_str.Length());
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetVaporSensorSetupDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString vaporsenslocation;
	int vaporsensthreshold;
	int vaporsenscategory;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get sensor location string */
	get_computer_format_answer(cmds.cmdSetVaporSensorLocationLabel,devnumber,5,m);
	vaporsenslocation = get_current_vaporsenslocation(comm->global_buffer.c_str());
	wProc->increment();

	/* get sensor type */
	get_computer_format_answer(cmds.cmdSetVaporSensorAlarmThreshold,devnumber,5,m);
	vaporsensthreshold = get_current_vaporsensthreshold(comm->global_buffer.c_str());
	wProc->increment();

	/* get sensor category */
	get_computer_format_answer(cmds.cmdSetVaporSensorCategory,devnumber,5,m);
	vaporsenscategory = get_current_vaporsenscategory(comm->global_buffer.c_str());
	wProc->increment();

	wProc->init(false);

	/* display current settings */
	ShowDialog->setVaporSensorLocation(vaporsenslocation);
	ShowDialog->setVaporSensorThreshold(vaporsensthreshold);
	ShowDialog->setVaporSensorCategory(vaporsenscategory);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_vaporsenssetup);
	/* get new settings */
	vaporsenslocation = ShowDialog->getVaporSensorLocation();
	vaporsensthreshold = ShowDialog->getVaporSensorThreshold();
	vaporsenscategory = ShowDialog->getVaporSensorCategory();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{                       
		wProc->init(true);
		wProc->increment();

		AnsiString sth, scat;

		if (vaporsenslocation=="")
		{
			vaporsenslocation.Insert(" ",1);
			vaporsenslocation.sprintf("%020s",vaporsenslocation);
    	}
		sth.sprintf("%06d",vaporsensthreshold);
		scat.sprintf("%d",vaporsenscategory);

		result = send(cmd_type,cmds.cmdSetVaporSensorLocationLabel,lenCmd,1,
			vaporsenslocation,0,7,vaporsenslocation.Length(),'\0',7,vaporsenslocation.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetVaporSensorAlarmThreshold,lenCmd,1,
			sth,0,7,sth.Length(),'\0',7,sth.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetVaporSensorCategory,lenCmd,1,
			scat,0,7,scat.Length(),'\0',7,scat.Length());
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetGroundwaterSensorConfigurationDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool grdwsensconfig[20] = {false,false,false,false,false,
							   false,false,false,false,false,
							   false,false,false,false,false,
							   false,false,false,false,false};

	wProc->init(20,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");
	/* get and show current settings on the dialog window */
	get_computer_format_answer(cmds.cmdSetGroundwaterSensorConfiguration,"00",5,m);
	get_current_grdwsensorconfig(comm->global_buffer.c_str(), grdwsensconfig);
	wProc->init(false);

	/* display current settings */
	ShowDialog->setGroundWaterSensorConfiguration(grdwsensconfig);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_grdwsensconfig);
	/* get new settings */
	ShowDialog->getGroundWaterSensorConfiguration(grdwsensconfig);
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		char c;
		AnsiString cfg_str;

		wProc->init(true);
		wProc->increment();

		for (int i=0; i < 20; i++)
		{
			cfg_str = "";
			cfg_str.sprintf("%02d",i+1);
			if (grdwsensconfig[i])	c = '1';
			else c = '0';
			cfg_str += c;

			result |= send(cmd_type,cmds.cmdSetGroundwaterSensorConfiguration,
				lenCmd,1,cfg_str,0,5,cfg_str.Length(),'\0',5,cfg_str.Length());
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showGroundWaterSensorSetupDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString grdwsenslocation;
	int grdwsenscategory;

	wProc->init(2,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get sensor location string */
	get_computer_format_answer(cmds.cmdSetGroundwaterSensorLocationLabel,devnumber,5,m);
	grdwsenslocation = get_current_grdwsenslocation(comm->global_buffer.c_str());
	wProc->increment();

	/* get sensor category */
	get_computer_format_answer(cmds.cmdSetGroundwaterSensorCategory,devnumber,5,m);
	grdwsenscategory = get_current_grdwsenscategory(comm->global_buffer.c_str());
	wProc->increment();

	wProc->init(false);

	/* display current settings */
	ShowDialog->setGroundWaterSensorLocation(grdwsenslocation);
	ShowDialog->setGroundWaterSensorCategory(grdwsenscategory);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_gdrwsenssetup);
	/* get new settings */
	grdwsenslocation = ShowDialog->getGroundWaterSensorLocation();
	grdwsenscategory = ShowDialog->getGroundWaterSensorCategory();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString scat;

		if (grdwsenslocation=="")
		{
			grdwsenslocation.Insert(" ",1);
			grdwsenslocation.sprintf("%020s",grdwsenslocation);
		}
		scat.sprintf("%d",grdwsenscategory);

		result = send(cmd_type,cmds.cmdSetGroundwaterSensorLocationLabel,lenCmd,1,
			grdwsenslocation,0,7,grdwsenslocation.Length(),'\0',7,grdwsenslocation.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetGroundwaterSensorCategory,lenCmd,1,
			scat,0,7,scat.Length(),'\0',7,scat.Length());
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetInputConfiguration(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool extinputconfig[8] = {false,false,false,false,false,false,false,false};

	wProc->init(8,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");
	/* get and show current settings on the dialog window */
	get_computer_format_answer(cmds.cmdSetInputConfiguration,"00",5,m);
	get_current_extinputconfig(comm->global_buffer.c_str(), extinputconfig);
	wProc->init(false);

	/* display current settings */
	ShowDialog->setExternalInputConfiguration(extinputconfig);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_extinputconfig);
	/* get new settings */
	ShowDialog->getExternalInputConfiguration(extinputconfig);
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		char c;
		AnsiString cfg_str;

		wProc->init(true);
		wProc->increment();

		for (int i=0; i < 8; i++)
		{
			cfg_str = "";
			cfg_str.sprintf("%02d",i+1);
			if (extinputconfig[i])	c = '1';
			else c = '0';
			cfg_str += c;

			result |= send(cmd_type,cmds.cmdSetInputConfiguration,
				lenCmd,1,cfg_str,0,5,cfg_str.Length(),'\0',5,cfg_str.Length());
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetInputSetupDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString extinputname;
	int extinputtype;
	int extinputswitchtype;
	int extinputtanknr;
	int extinputdispensemode;

	wProc->init(3,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get external input location label */
	get_computer_format_answer(cmds.cmdSetInputLocationLabel,devnumber,5,m);
	extinputname = get_current_extinputname(comm->global_buffer.c_str());
	wProc->increment();

	/* get external input type-orientation-tnak or pump number */
	get_computer_format_answer(cmds.cmdSetInputType,devnumber,5,m);
	extinputtype = get_current_extinputtype(comm->global_buffer.c_str());
	extinputswitchtype = get_current_extinputswitchtype(comm->global_buffer.c_str());
	extinputtanknr = get_current_extinputtanknr(comm->global_buffer.c_str());
	wProc->increment();

	/* get external input dispense mode */
	get_computer_format_answer(cmds.cmdSetInputDispenseMode,devnumber,5,m);
	extinputdispensemode = get_current_extinputdispensemode(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setExternalInputName(extinputname);
	ShowDialog->setExternalInputType(extinputtype);
	ShowDialog->setExternalInputSwitchType(extinputswitchtype);
	ShowDialog->setExternalInputTankNumber(extinputtanknr);
	ShowDialog->setExternalInputDispenseMode(extinputdispensemode);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_extinputsetup);
	/* get new settings */
	extinputname = ShowDialog->getExternalInputName();
	extinputtype = ShowDialog->getExternalInputType();
	extinputswitchtype = ShowDialog->getExternalInputSwitchType();
	extinputtanknr = ShowDialog->getExternalInputTankNumber();
	extinputdispensemode = ShowDialog->setExternalInputDispenseMode();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString sty, ssty, stnr, sdm, stype = "";

		if (extinputname=="")
		{
			extinputname.Insert(" ",1);
			extinputname.sprintf("%020s",extinputname);
		}
		sty.sprintf("%d",extinputtype);
		stype += sty;
		ssty.sprintf("%d",extinputswitchtype);
		stype += ssty;
		stnr.sprintf("%02d",extinputtanknr);
		stype += stnr;
		sdm.sprintf("%d",extinputdispensemode);

		result = send(cmd_type,cmds.cmdSetInputLocationLabel,lenCmd,1,
			extinputname,0,7,extinputname.Length(),'\0',7,extinputname.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetInputType,lenCmd,1,
			stype,0,7,stype.Length(),'\0',7,stype.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetInputDispenseMode,lenCmd,1,
			sdm,0,7,sdm.Length(),'\0',7,sdm.Length());
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetRelayConfigurationDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;
	bool relayconfig[16] = {false,false,false,false,false,false,false,false,
						   false,false,false,false,false,false,false,false};

	wProc->init(16,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");
	/* get and show current settings on the dialog window */
	get_computer_format_answer(cmds.cmdSetRelayConfiguration,"00",5,m);
	get_current_tankconfig(comm->global_buffer.c_str(), relayconfig);
	wProc->init(false);

	/* display current settings */
	ShowDialog->setRelayConfiguration(relayconfig);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_relayconfig);
	/* get new settings */
	ShowDialog->getRelayConfiguration(relayconfig);
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		char c;
		AnsiString cfg_str;

		wProc->init(true);
		wProc->increment();

		for (int i=0; i < 16; i++)
		{
        	cfg_str = "";
			cfg_str.sprintf("%02d",i+1);
			if (relayconfig[i])	c = '1';
			else c = '0';
			cfg_str += c;

			result |= send(cmd_type,cmds.cmdSetRelayConfiguration,
				lenCmd,1,cfg_str,0,5,cfg_str.Length(),'\0',5,cfg_str.Length());
			wProc->increment();
		}
		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showSetRelaySetupDlg(char cmd_type, int page_idx,
	int group_idx, int item_idx, TMemo *m)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	AnsiString devnumber = "1";
	int result = 0;
	AnsiString relaydesignation;
	int relaytype;
	int relayorientation;
	int relaytanknr;

	wProc->init(4,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	ShowDialog->language = language;
	ShowDialog->languagepath = languagepath;

	/* get the number of the port from user (01...99) */
	ShowDialog->setDeviceNumber(StrToInt(devnumber));
	ShowDialog->ShowGetNumber();
	devnumber.sprintf("%02d", ShowDialog->getDeviceNumber());

	cancel_from_dialog = ShowDialog->getModalResult();
	if (cancel_from_dialog)
	{
		wProc->init(false);
		delete ShowDialog;
		return 0;
	}

	cancel_from_dialog = ShowDialog->getModalResult();
	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', devnumber.c_str());

	/* get relay designation */
	get_computer_format_answer(cmds.cmdSetRelayLocationLabel,devnumber,5,m);
	relaydesignation = get_current_relaydesignation(comm->global_buffer.c_str());
	wProc->increment();

	/* get relay type */
	get_computer_format_answer(cmds.cmdSetRelayType,devnumber,5,m);
	relaytype = get_current_relaytype(comm->global_buffer.c_str());
	wProc->increment();

	/* get relay orientation */
	get_computer_format_answer(cmds.cmdSetRelayOrientation,devnumber,5,m);
	relayorientation = get_current_relayorientation(comm->global_buffer.c_str());
	wProc->increment();

	/* get relay tank assigment */
	get_computer_format_answer(cmds.cmdSetRelayTankAssignment,devnumber,5,m);
	relaytanknr = get_current_relaytanknr(comm->global_buffer.c_str());
	wProc->increment();
	wProc->init(false);

	/* display current settings */
	ShowDialog->setRelayDesignation(relaydesignation);
	ShowDialog->setRelayType(relaytype);
	ShowDialog->setRelayOrientation(relayorientation);
	ShowDialog->setRelayTankNumber(relaytanknr);
	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_relaysetup);
	/* get new settings */
	relaydesignation = ShowDialog->getRelayDesignation();
	relaytype = ShowDialog->getRelayType();
	relayorientation = ShowDialog->getRelayOrientation();
	relaytanknr = ShowDialog->getRelayTankNumber();
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		AnsiString sty, sor, stnr;

		if (relaydesignation=="")
		{
			relaydesignation.Insert(" ",1);
			relaydesignation.sprintf("%020s",relaydesignation);
		}
		sty.sprintf("%d",relaytype);
		sor.sprintf("%d",relayorientation);
		stnr.sprintf("%02d",relaytanknr);

		result = send(cmd_type,cmds.cmdSetRelayLocationLabel,lenCmd,1,
			relaydesignation,0,7,relaydesignation.Length(),'\0',7,relaydesignation.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetRelayType,lenCmd,1,
			sty,0,7,sty.Length(),'\0',7,sty.Length());
		wProc->increment();
		result |= send(cmd_type,cmds.cmdSetRelayOrientation,lenCmd,1,
			sor,0,7,sor.Length(),'\0',7,sor.Length());
		result |= send(cmd_type,cmds.cmdSetRelayTankAssignment,lenCmd,1,
			stnr,0,7,stnr.Length(),'\0',7,stnr.Length());
		wProc->increment();

		wProc->init(false);
	}

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

int TTLSDevice::showArchiveUtilityDlg(char cmd_type, int page_idx, int group_idx,
	int item_idx, TMemo *m, int id)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return 0;

	int result = 0;

	wProc->init(1,true);

	ShowDialog = new TShowCmdSpecWindows();
	wProc->increment();
	init_show_dialog_window(page_idx,group_idx,item_idx,m);

	/* display the dialog window */
	ShowDialog->ShowDialogWindow(ShowDialog->dlg_archive);
	
	cancel_from_dialog = ShowDialog->getModalResult();

	if (!cancel_from_dialog)
	{
		wProc->init(true);
		wProc->increment();

		switch (id)
		{
			case 0: result = send(cmd_type,cmds.cmdRestoreAllSetupDatafromEEPROM,lenCmd,1,
						"149",0,7,3,'\0',7,3);
					break;
			case 1: result = send(cmd_type,cmds.cmdSaveAllSetupDatatoEEPROM,lenCmd,1,
						"149",0,7,3,'\0',7,3);
					break;
			case 2: result = send(cmd_type,cmds.cmdClearAllSetupDatafromEEPROM,lenCmd,1,
						"149",0,7,3,'\0',7,3);
					break;
		}

		wProc->init(false);
	}
	wProc->init(false);

	/* free resources */
	delete ShowDialog;

	/* get and display current settings */
	if (m)	get(page_idx, group_idx, item_idx, m, 'I', '0', "00");

	return result;
}

/* init functions */
void TTLSDevice::init_command_string_list_and_id_array(void)
{
	cmd_str_list = new TStringList;

/* system setup */
	cmd_str_list->Add("0,0,0");
	cmd_id_arr[0] = 0x505;
	cmd_str_list->Add("0,0,1");
	cmd_id_arr[1] = 0x505;
	cmd_str_list->Add("0,0,2");
	cmd_id_arr[2] = 0x50f;
	cmd_str_list->Add("0,0,3");
	cmd_id_arr[3] = 0x501;
	cmd_str_list->Add("0,0,4");
	cmd_id_arr[4] = 0x501;
	cmd_str_list->Add("0,0,5");
	cmd_id_arr[5] = 0x503;
	cmd_str_list->Add("0,0,6");
	cmd_id_arr[6] = 0x503;
	cmd_str_list->Add("0,0,7");
	cmd_id_arr[7] = 0x503;
	cmd_str_list->Add("0,0,8");
	cmd_id_arr[8] = 0x503;
	cmd_str_list->Add("0,0,9");
	cmd_id_arr[9] = 0x502;
	cmd_str_list->Add("0,0,10");
	cmd_id_arr[10] = 0x502;
	cmd_str_list->Add("0,0,11");
	cmd_id_arr[11] = 0x502;
	cmd_str_list->Add("0,0,12");
	cmd_id_arr[12] = 0x502;
	cmd_str_list->Add("0,0,13");
	cmd_id_arr[13] = 0x511;
	cmd_str_list->Add("0,0,14");
	cmd_id_arr[14] = 0x512;
	cmd_str_list->Add("0,0,15");
	cmd_id_arr[15] = 0x51c;
	cmd_str_list->Add("0,0,16");
	cmd_id_arr[16] = 0x51d;
	cmd_str_list->Add("0,0,17");
	cmd_id_arr[17] = 0x51e;
	cmd_str_list->Add("0,0,18");
	cmd_id_arr[18] = 0x534;
	cmd_str_list->Add("0,0,19");
	cmd_id_arr[19] = 0x534;
	cmd_str_list->Add("0,0,20");
	cmd_id_arr[20] = 0x534;
	cmd_str_list->Add("0,0,21");
	cmd_id_arr[21] = 0x533;
	cmd_str_list->Add("0,0,22");
	cmd_id_arr[22] = 0x533;
	cmd_str_list->Add("0,0,23");
	cmd_id_arr[23] = 0x533;
	cmd_str_list->Add("0,0,24");
	cmd_id_arr[24] = 0x532;
	cmd_str_list->Add("0,0,25");
	cmd_id_arr[25] = 0x532;
	cmd_str_list->Add("0,0,26");
	cmd_id_arr[26] = 0x532;
	cmd_str_list->Add("0,0,27");
	cmd_id_arr[27] = 0x546;
	cmd_str_list->Add("0,0,28");
	cmd_id_arr[28] = 0x547;
	cmd_str_list->Add("0,0,29");
	cmd_id_arr[29] = 0x548;
	cmd_str_list->Add("0,0,30");
	cmd_id_arr[30] = 0x549;
	cmd_str_list->Add("0,0,31");
	cmd_id_arr[31] = 0x54a;
	cmd_str_list->Add("0,0,32");
	cmd_id_arr[32] = 0x54b;
	cmd_str_list->Add("0,0,33");
	cmd_id_arr[33] = 0x553;
	cmd_str_list->Add("0,0,34");
	cmd_id_arr[34] = 0x556;
	cmd_str_list->Add("0,0,35");
	cmd_id_arr[35] = 0x557;
	cmd_str_list->Add("0,0,36");
	cmd_id_arr[36] = 0x558;
	cmd_str_list->Add("0,0,37");
	cmd_id_arr[37] = 0x559;
	cmd_str_list->Add("0,0,38");
	cmd_id_arr[38] = 0x55a;
	cmd_str_list->Add("0,0,39");
	cmd_id_arr[39] = 0x55b;
	cmd_str_list->Add("0,0,40");
	cmd_id_arr[40] = 0x50c;
	cmd_str_list->Add("0,0,41");
	cmd_id_arr[41] = 0x50d;
	cmd_str_list->Add("0,0,42");
	cmd_id_arr[42] = 0x50e;
	cmd_str_list->Add("0,0,43");
	cmd_id_arr[43] = 0x513;
	cmd_str_list->Add("0,0,44");
	cmd_id_arr[44] = 0x60b;
	cmd_str_list->Add("0,0,45");
	cmd_id_arr[45] = 0x514;
	cmd_str_list->Add("0,0,46");
	cmd_id_arr[46] = 0x519;
	cmd_str_list->Add("0,0,47");
	cmd_id_arr[47] = 0x554;
	cmd_str_list->Add("0,0,48");
	cmd_id_arr[48] = 0x555;
	cmd_str_list->Add("0,0,49");
	cmd_id_arr[49] = 0x51a;
	cmd_str_list->Add("0,0,50");
	cmd_id_arr[50] = 0x515;
	cmd_str_list->Add("0,0,51");
	cmd_id_arr[51] = 0x516;
	cmd_str_list->Add("0,0,52");
	cmd_id_arr[52] = 0x51f;
	cmd_str_list->Add("0,0,53");
	cmd_id_arr[53] = 0x000;
	cmd_str_list->Add("0,0,54");
	cmd_id_arr[54] = 0x504;
	cmd_str_list->Add("0,0,55");
	cmd_id_arr[55] = 0x000;
/* communication setup */
	cmd_str_list->Add("0,1,0");
	cmd_id_arr[56] = 0x881;
	cmd_str_list->Add("0,1,1");
	cmd_id_arr[57] = 0x000;
	cmd_str_list->Add("0,1,2");
	cmd_id_arr[58] = 0x521;
	cmd_str_list->Add("0,1,3");
	cmd_id_arr[59] = 0x52A;
	cmd_str_list->Add("0,1,4");
	cmd_id_arr[60] = 0x52c;
	cmd_str_list->Add("0,1,5");
	cmd_id_arr[61] = 0x531;
/* in-tank setup */
	cmd_str_list->Add("0,2,0");
	cmd_id_arr[62] = 0x601;
	cmd_str_list->Add("0,2,1");
	cmd_id_arr[63] = 0x602;
	cmd_str_list->Add("0,2,2");
	cmd_id_arr[64] = 0x603;
	cmd_str_list->Add("0,2,3");
	cmd_id_arr[65] = 0x609;
	cmd_str_list->Add("0,2,4");
	cmd_id_arr[66] = 0x607;
	cmd_str_list->Add("0,2,5");
	cmd_id_arr[67] = 0x60A;
	cmd_str_list->Add("0,2,6");
	cmd_id_arr[68] = 0x60A;
	cmd_str_list->Add("0,2,7");
	cmd_id_arr[69] = 0x615;
	cmd_str_list->Add("0,2,8");
	cmd_id_arr[70] = 0x639;
	cmd_str_list->Add("0,2,9");
	cmd_id_arr[71] = 0x639;
	cmd_str_list->Add("0,2,10");
	cmd_id_arr[72] = 0x616;
	cmd_str_list->Add("0,2,11");
	cmd_id_arr[73] = 0x62F;
	cmd_str_list->Add("0,2,12");
	cmd_id_arr[74] = 0x627;
	cmd_str_list->Add("0,2,13");
	cmd_id_arr[75] = 0x624;
	cmd_str_list->Add("0,2,14");
	cmd_id_arr[76] = 0x628;
	cmd_str_list->Add("0,2,15");
	cmd_id_arr[77] = 0x623;
	cmd_str_list->Add("0,2,16");
	cmd_id_arr[78] = 0x622;
	cmd_str_list->Add("0,2,17");
	cmd_id_arr[79] = 0x629;
	cmd_str_list->Add("0,2,18");
	cmd_id_arr[80] = 0x621;
	cmd_str_list->Add("0,2,19");
	cmd_id_arr[81] = 0x626;
	cmd_str_list->Add("0,2,20");
	cmd_id_arr[82] = 0x625;
	cmd_str_list->Add("0,2,21");
	cmd_id_arr[83] = 0x608;
	cmd_str_list->Add("0,2,22");
	cmd_id_arr[84] = 0x60F;
	cmd_str_list->Add("0,2,23");
	cmd_id_arr[85] = 0x612;
	cmd_str_list->Add("0,2,24");
	cmd_id_arr[86] = 0x612;
	cmd_str_list->Add("0,2,25");
	cmd_id_arr[87] = 0x636;
	cmd_str_list->Add("0,2,26");
	cmd_id_arr[88] = 0x62A;
	cmd_str_list->Add("0,2,27");
	cmd_id_arr[89] = 0x62C;
	cmd_str_list->Add("0,2,28");
	cmd_id_arr[90] = 0x62D;
	cmd_str_list->Add("0,2,29");
	cmd_id_arr[91] = 0x62D;
	cmd_str_list->Add("0,2,30");
	cmd_id_arr[92] = 0x62D;
	cmd_str_list->Add("0,2,31");
	cmd_id_arr[93] = 0x631;
	cmd_str_list->Add("0,2,32");
	cmd_id_arr[94] = 0x631;
	cmd_str_list->Add("0,2,33");
	cmd_id_arr[95] = 0x630;
	cmd_str_list->Add("0,2,34");
	cmd_id_arr[96] = 0x632;
	cmd_str_list->Add("0,2,35");
	cmd_id_arr[97] = 0x60C;
	cmd_str_list->Add("0,2,36");
	cmd_id_arr[98] = 0x634;
	cmd_str_list->Add("0,2,37");
	cmd_id_arr[99] = 0x635;
	cmd_str_list->Add("0,2,38");
	cmd_id_arr[100] = 0x610;
	cmd_str_list->Add("0,2,39");
	cmd_id_arr[101] = 0x63A;
/* fuel management */
	cmd_str_list->Add("0,3,0");
	cmd_id_arr[102] = 0x681;
	cmd_str_list->Add("0,3,1");
	cmd_id_arr[103] = 0x682;
	cmd_str_list->Add("0,3,2");
	cmd_id_arr[104] = 0x683;
/* in-tank leak tests */
	cmd_str_list->Add("0,4,0");
	cmd_id_arr[105] = 0x611;
	cmd_str_list->Add("0,4,1");
	cmd_id_arr[106] = 0x611;
	cmd_str_list->Add("0,4,2");
	cmd_id_arr[107] = 0x61B;
	cmd_str_list->Add("0,4,3");
	cmd_id_arr[108] = 0x611;
	cmd_str_list->Add("0,4,4");
	cmd_id_arr[109] = 0x611;
	cmd_str_list->Add("0,4,5");
	cmd_id_arr[110] = 0x611;
	cmd_str_list->Add("0,4,6");
	cmd_id_arr[111] = 0x61A;
	cmd_str_list->Add("0,4,7");
	cmd_id_arr[112] = 0x61C;
	cmd_str_list->Add("0,4,8");
	cmd_id_arr[113] = 0x633;
/* pressure line leak setup */
	cmd_str_list->Add("0,5,0");
	cmd_id_arr[114] = 0x781;
	cmd_str_list->Add("0,5,1");
	cmd_id_arr[115] = 0x782;
	cmd_str_list->Add("0,5,2");
	cmd_id_arr[116] = 0x788;
	cmd_str_list->Add("0,5,3");
	cmd_id_arr[117] = 0x789;
	cmd_str_list->Add("0,5,4");
	cmd_id_arr[118] = 0x78C;
	cmd_str_list->Add("0,5,5");
	cmd_id_arr[119] = 0x783;//78E
	cmd_str_list->Add("0,5,6");
	cmd_id_arr[120] = 0x784;
	cmd_str_list->Add("0,5,7");
	cmd_id_arr[121] = 0x77C;
	cmd_str_list->Add("0,5,8");
	cmd_id_arr[122] = 0x78F;
	cmd_str_list->Add("0,5,9");
	cmd_id_arr[123] = 0x785;
	cmd_str_list->Add("0,5,10");
	cmd_id_arr[124] = 0x786;
	cmd_str_list->Add("0,5,11");
	cmd_id_arr[125] = 0x78A;
	cmd_str_list->Add("0,5,12");
	cmd_id_arr[126] = 0x77D;
/* WPLLD line leak setup */
	cmd_str_list->Add("0,6,0");
	cmd_id_arr[127] = 0x7A1;
	cmd_str_list->Add("0,6,1");
	cmd_id_arr[128] = 0x7A2;
	cmd_str_list->Add("0,6,2");
	cmd_id_arr[129] = 0x7A8;
	cmd_str_list->Add("0,6,3");
	cmd_id_arr[130] = 0x7A9;
	cmd_str_list->Add("0,6,4");
	cmd_id_arr[131] = 0x7A3;
	cmd_str_list->Add("0,6,5");
	cmd_id_arr[132] = 0x7AA;//7AC
	cmd_str_list->Add("0,6,6");
	cmd_id_arr[133] = 0x7A4;
	cmd_str_list->Add("0,6,7");
	cmd_id_arr[134] = 0x7A5;
	cmd_str_list->Add("0,6,8");
	cmd_id_arr[135] = 0x7A6;
	cmd_str_list->Add("0,6,9");
	cmd_id_arr[136] = 0x7AF;
/* line leak detection setup */
	cmd_str_list->Add("0,7,0");
	cmd_id_arr[137] = 0x751;
	cmd_str_list->Add("0,7,1");
	cmd_id_arr[138] = 0x760;
	cmd_str_list->Add("0,7,2");
	cmd_id_arr[139] = 0x752;
	cmd_str_list->Add("0,7,3");
	cmd_id_arr[140] = 0x75D;
	cmd_str_list->Add("0,7,4");
	cmd_id_arr[141] = 0x75E;
	cmd_str_list->Add("0,7,5");
	cmd_id_arr[142] = 0x753;
	cmd_str_list->Add("0,7,6");
	cmd_id_arr[143] = 0x754;
	cmd_str_list->Add("0,7,7");
	cmd_id_arr[144] = 0x756;
	cmd_str_list->Add("0,7,8");
	cmd_id_arr[145] = 0x755;
	cmd_str_list->Add("0,7,9");
	cmd_id_arr[146] = 0x757;
	cmd_str_list->Add("0,7,10");
	cmd_id_arr[147] = 0x758;
	cmd_str_list->Add("0,7,11");
	cmd_id_arr[148] = 0x75F;
	cmd_str_list->Add("0,7,12");
	cmd_id_arr[149] = 0x761;
/* line leak tests setup */
	cmd_str_list->Add("0,8,0");
	cmd_id_arr[150] = 0x759;
	cmd_str_list->Add("0,8,1");
	cmd_id_arr[151] = 0x759;
	cmd_str_list->Add("0,8,2");
	cmd_id_arr[152] = 0x759;
	cmd_str_list->Add("0,8,3");
	cmd_id_arr[153] = 0x759;
/* line leak lockout setup */
	cmd_str_list->Add("0,9,0");
	cmd_id_arr[154] = 0x75A;
/* pump sensor setup */
	cmd_str_list->Add("0,10,0");
	cmd_id_arr[155] = 0x771;
	cmd_str_list->Add("0,10,1");
	cmd_id_arr[156] = 0x772;
	cmd_str_list->Add("0,10,2");
	cmd_id_arr[157] = 0x773;
/* reconciliation setup */
	cmd_str_list->Add("0,11,0");
	cmd_id_arr[158] = 0x791;//792
	cmd_str_list->Add("0,11,1");
	cmd_id_arr[159] = 0x793;
	cmd_str_list->Add("0,11,2");
	cmd_id_arr[160] = 0x794;//79D
	cmd_str_list->Add("0,11,3");
	cmd_id_arr[161] = 0x794;
	cmd_str_list->Add("0,11,4");
	cmd_id_arr[162] = 0x794;
	cmd_str_list->Add("0,11,5");
	cmd_id_arr[163] = 0x794;
	cmd_str_list->Add("0,11,6");
	cmd_id_arr[164] = 0x795;
	cmd_str_list->Add("0,11,7");
	cmd_id_arr[165] = 0x797;
	cmd_str_list->Add("0,11,8");
	cmd_id_arr[166] = 0x798;
	cmd_str_list->Add("0,11,9");
	cmd_id_arr[167] = 0x799;
	cmd_str_list->Add("0,11,10");
	cmd_id_arr[168] = 0x79A;
	cmd_str_list->Add("0,11,11");
	cmd_id_arr[169] = 0x79F;
	cmd_str_list->Add("0,11,12");
	cmd_id_arr[170] = 0x7B2;
	cmd_str_list->Add("0,11,13");
	cmd_id_arr[171] = 0x7B1;
/* liquod sensor setup */
	cmd_str_list->Add("0,12,0");
	cmd_id_arr[172] = 0x701;
	cmd_str_list->Add("0,12,1");
	cmd_id_arr[173] = 0x702;
	cmd_str_list->Add("0,12,2");
	cmd_id_arr[174] = 0x703;
	cmd_str_list->Add("0,12,3");
	cmd_id_arr[175] = 0x704;
/* vapor senosr setup */
	cmd_str_list->Add("0,13,0");
	cmd_id_arr[176] = 0x706;
	cmd_str_list->Add("0,13,1");
	cmd_id_arr[177] = 0x707;
	cmd_str_list->Add("0,13,2");
	cmd_id_arr[178] = 0x708;
	cmd_str_list->Add("0,13,3");
	cmd_id_arr[179] = 0x709;
/* groundwater senosr setup */
	cmd_str_list->Add("0,14,0");
	cmd_id_arr[180] = 0x711;
	cmd_str_list->Add("0,14,1");
	cmd_id_arr[181] = 0x712;
	cmd_str_list->Add("0,14,2");
	cmd_id_arr[182] = 0x713;
/* 2-wire sensor setup */
	cmd_str_list->Add("0,15,0");
	cmd_id_arr[183] = 0x741;
	cmd_str_list->Add("0,15,1");
	cmd_id_arr[184] = 0x742;
	cmd_str_list->Add("0,15,2");
	cmd_id_arr[185] = 0x743;
	cmd_str_list->Add("0,15,3");
	cmd_id_arr[186] = 0x744;
/* 3-wire sensor setup */
	cmd_str_list->Add("0,16,0");
	cmd_id_arr[187] = 0x746;
	cmd_str_list->Add("0,16,1");
	cmd_id_arr[188] = 0x747;
	cmd_str_list->Add("0,16,2");
	cmd_id_arr[189] = 0x748;
	cmd_str_list->Add("0,16,3");
	cmd_id_arr[190] = 0x749;
/* external input setup */
	cmd_str_list->Add("0,17,0");
	cmd_id_arr[191] = 0x801;
	cmd_str_list->Add("0,17,1");
	cmd_id_arr[192] = 0x802;
	cmd_str_list->Add("0,17,2");
	cmd_id_arr[193] = 0x803;
/* output relay setup */
	cmd_str_list->Add("0,18,0");
	cmd_id_arr[194] = 0x806;
	cmd_str_list->Add("0,18,1");
	cmd_id_arr[195] = 0x807;
	cmd_str_list->Add("0,18,2");
	cmd_id_arr[196] = 0x80A;
	cmd_str_list->Add("0,18,3");
	cmd_id_arr[197] = 0x808;
/* PLLD line disable setup */
	cmd_str_list->Add("0,19,0");
	cmd_id_arr[198] = 0x000;
/* WPLLD line disable setup */
	cmd_str_list->Add("0,20,0");
	cmd_id_arr[199] = 0x000;
/* line disable setup */
	cmd_str_list->Add("0,21,0");
	cmd_id_arr[200] = 0x000;
/* smart senosr setup */
	cmd_str_list->Add("0,22,0");
	cmd_id_arr[201] = 0x74B;
	cmd_str_list->Add("0,22,1");
	cmd_id_arr[202] = 0x74C;
	cmd_str_list->Add("0,22,2");
	cmd_id_arr[203] = 0x74E;
/* archive utility */
	cmd_str_list->Add("0,23,0");
	cmd_id_arr[204] = 0x852;
	cmd_str_list->Add("0,23,1");
	cmd_id_arr[205] = 0x851;
	cmd_str_list->Add("0,23,2");
	cmd_id_arr[206] = 0x853;
}

void TTLSDevice::init_command_strings(void)
{
	/* control functions */
	LoadString(NULL,0,cmds.cmdSystemReset,lenCmd);
	LoadString(NULL,1,cmds.cmdClearPowerResetFlag,lenCmd);
	LoadString(NULL,2,cmds.cmdRemoteAlarmReset,lenCmd);
	LoadString(NULL,3,cmds.cmdConfirmClearFunction,lenCmd);
	LoadString(NULL,4,cmds.cmdClearInTankDeliveryReports,lenCmd);
	LoadString(NULL,5,cmds.cmdStartInTankLeakDetectTest,lenCmd);
	LoadString(NULL,6,cmds.cmdStopInTankLeakDetectTest,lenCmd);
	LoadString(NULL,7,cmds.cmdDeleteCSLDRateTable,lenCmd);
	LoadString(NULL,8,cmds.cmdStartPressureLineLeakTest,lenCmd);
	LoadString(NULL,9,cmds.cmdStopPressureLineLeakTest,lenCmd);
	LoadString(NULL,10,cmds.cmdStartWPLLDLineLeakTest,lenCmd);
	LoadString(NULL,11,cmds.cmdStopWPLLDLineLeakTest,lenCmd);
	LoadString(NULL,12,cmds.cmdStartPressureLineLeakTestbyType,lenCmd);
	LoadString(NULL,13,cmds.cmdStartWPLLDLineLeakTestbyType,lenCmd);
	LoadString(NULL,14,cmds.cmdPressureLineLeakPressureOffsetReset,lenCmd);
	LoadString(NULL,15,cmds.cmdWPLLDLineLeakPressureOffsetReset,lenCmd);
	LoadString(NULL,16,cmds.cmdCloseCurrentShift,lenCmd);
/* operational reports */
	/* system reports */
	LoadString(NULL,17,cmds.cmdSystemStatusReport,lenCmd);
	LoadString(NULL,18,cmds.cmdSystemConfigurationReport,lenCmd);
	LoadString(NULL,19,cmds.cmdPriorityAlarmHistoryReport,lenCmd);
	LoadString(NULL,20,cmds.cmdNonPriorityAlarmHistoryReport,lenCmd);
	LoadString(NULL,21,cmds.cmdActiveAlarmReport,lenCmd);
	LoadString(NULL,22,cmds.cmdClearedAlarmReport,lenCmd);
	LoadString(NULL,23,cmds.cmdServiceReportHistory,lenCmd);
	/* in-tank reports */
	LoadString(NULL,24,cmds.cmdInTankInventoryReport,lenCmd);
	LoadString(NULL,25,cmds.cmdInTankDeliveryReport,lenCmd);
	LoadString(NULL,26,cmds.cmdInTankLeakDetectReport,lenCmd);
	LoadString(NULL,27,cmds.cmdInTankShiftInventoryReport,lenCmd);
	LoadString(NULL,28,cmds.cmdInTankStatusReport,lenCmd);
	LoadString(NULL,29,cmds.cmdInTankAlarmHistoryReport,lenCmd);
	LoadString(NULL,30,cmds.cmdInTankLeakTestHistoryReport,lenCmd);
	LoadString(NULL,31,cmds.cmdInTankLeakTestResultsReport,lenCmd);
	LoadString(NULL,32,cmds.cmdHRMAdjustedDeliveryReport,lenCmd);
	LoadString(NULL,33,cmds.cmdBIRAdjustedDeliveryReport,lenCmd);
	LoadString(NULL,34,cmds.cmdInTankMostRecentDeliveryReport,lenCmd);
	LoadString(NULL,35,cmds.cmdInTankStickHeightReport,lenCmd);
	LoadString(NULL,36,cmds.cmdTankChartReport,lenCmd);
	LoadString(NULL,37,cmds.cmdTicketedDeliveryReport,lenCmd);
	LoadString(NULL,38,cmds.cmdPeriodicDeliveryVarianceReport,lenCmd);
	LoadString(NULL,39,cmds.cmdWeeklyDeliveryVarianceReport,lenCmd);
	LoadString(NULL,40,cmds.cmdDailyDeliveryVarianceReport,lenCmd);
	LoadString(NULL,41,cmds.cmdCSLDResultsReport,lenCmd);
	LoadString(NULL,42,cmds.cmdFuelManagementReport,lenCmd);
	LoadString(NULL,43,cmds.cmdFLSDiagnosticVolumeHistoryTable,lenCmd);
	LoadString(NULL,44,cmds.cmdInTankStoredInventoryReport,lenCmd);
	/* sensor reports */
	LoadString(NULL,45,cmds.cmdLiquidSensorStatusReport,lenCmd);
	LoadString(NULL,46,cmds.cmdLiquidSensorAlarmHistoryReport,lenCmd);
	LoadString(NULL,47,cmds.cmdVaporSensorStatusReport,lenCmd);
	LoadString(NULL,48,cmds.cmdVaporSensorAlarmHistoryReport,lenCmd);
	LoadString(NULL,49,cmds.cmdGroundwaterSensorStatusReport,lenCmd);
	LoadString(NULL,50,cmds.cmdGroundwaterSensorAlarmHistoryReport,lenCmd);
	LoadString(NULL,51,cmds.cmdTypeASensorStatusReport,lenCmd);
	LoadString(NULL,52,cmds.cmdTypeASensorAlarmHistoryReport,lenCmd);
	LoadString(NULL,53,cmds.cmdTypeBSensorStatusReport,lenCmd);
	LoadString(NULL,54,cmds.cmdTypeBSensorAlarmHistoryReport,lenCmd);
	LoadString(NULL,55,cmds.cmdUniversalSensorStatusReport,lenCmd);
	LoadString(NULL,56,cmds.cmdUniversalSensorAlarmHistoryReport,lenCmd);
	/* line leak reports */
	LoadString(NULL,57,cmds.cmdVolumetricLineLeakResultReport,lenCmd);
	LoadString(NULL,58,cmds.cmdVolumetricLineLeakAlarmHistoryReport,lenCmd);
	LoadString(NULL,59,cmds.cmdVolumetricLineLeakPumpStatus,lenCmd);
	LoadString(NULL,60,cmds.cmdPressureLineLeakTestResults020,lenCmd);
	LoadString(NULL,61,cmds.cmdPressureLineLeakTestHistory020,lenCmd);
	LoadString(NULL,62,cmds.cmdPressureLineLeakStatus,lenCmd);
	LoadString(NULL,63,cmds.cmdPressureLineLeakAlarmHistoryReport,lenCmd);
	LoadString(NULL,64,cmds.cmdPressureLineLeakTestResults010,lenCmd);
	LoadString(NULL,65,cmds.cmdPressureLineLeakTestHistory010,lenCmd);
	LoadString(NULL,66,cmds.cmdWPLLDLineLeakStatus,lenCmd);
	LoadString(NULL,67,cmds.cmdWPLLDLineLeakAlarmHistoryReport,lenCmd);
	LoadString(NULL,68,cmds.cmdWPLLDLineLeakTestResults,lenCmd);
	LoadString(NULL,69,cmds.cmdWPLLDLineLeakTestHistory,lenCmd);
	/* misc reports */
	LoadString(NULL,70,cmds.cmdTankerLoadReport,lenCmd);
	/* i/o device reports */
	LoadString(NULL,71,cmds.cmdInputStatusReport,lenCmd);
	LoadString(NULL,72,cmds.cmdInputAlarmHistoryReport,lenCmd);
	LoadString(NULL,73,cmds.cmdInputGeneratorAlarmHistoryReport,lenCmd);
	LoadString(NULL,74,cmds.cmdRelayStatusReport,lenCmd);
/* setup functions */
	/* system setup */
	LoadString(NULL,75,cmds.cmdSetTimeofday,lenCmd);
	LoadString(NULL,76,cmds.cmdSetShiftStartTime1234,lenCmd);
	LoadString(NULL,77,cmds.cmdSetPrintHeaderLine1234,lenCmd);
	LoadString(NULL,78,cmds.cmdSetSystemRS232SecurityCode,lenCmd);
	LoadString(NULL,79,cmds.cmdSetSystemTypeLanguageFlags1,lenCmd);
	LoadString(NULL,80,cmds.cmdSetPeriodicTestNeededWarning,lenCmd);
	LoadString(NULL,81,cmds.cmdSetDaysBeforePeriodicTestNeededWarning,lenCmd);
	LoadString(NULL,82,cmds.cmdSetDaysBeforePeriodicTestNeededAlarm,lenCmd);
	LoadString(NULL,83,cmds.cmdSetAnnualTestNeededWarning,lenCmd);
	LoadString(NULL,84,cmds.cmdSetDaysBeforeAnnualTestNeededWarning,lenCmd);
	LoadString(NULL,85,cmds.cmdSetDaysBeforeAnnualTestNeededAlarm,lenCmd);
	LoadString(NULL,86,cmds.cmdSetRemotePrinterPageEjectFlag,lenCmd);
	LoadString(NULL,87,cmds.cmdSetPrintTemperatureCompensationFlag,lenCmd);
	LoadString(NULL,88,cmds.cmdSetTemperatureCompensationValue,lenCmd);
	LoadString(NULL,89,cmds.cmdSetSystemDateTimeDisplayFormat,lenCmd);
	LoadString(NULL,90,cmds.cmdSetBIRShiftPrintoutsFlag,lenCmd);
	LoadString(NULL,91,cmds.cmdSetBIRDailyPrintoutsFlag,lenCmd);
	LoadString(NULL,92,cmds.cmdSetTankerLoadReportFlag,lenCmd);
	LoadString(NULL,93,cmds.cmdSetHProtocolHeightVolumeformat,lenCmd);
	LoadString(NULL,94,cmds.cmdSetHRMQPLDMonthlyPrintout,lenCmd);
	LoadString(NULL,95,cmds.cmdSetRedirectLocalPrintoutFlag,lenCmd);
	LoadString(NULL,96,cmds.cmdSetSystemTypeLanguageFlags15,lenCmd);
	LoadString(NULL,97,cmds.cmdSetSecondaryLanguageCodePageOutput,lenCmd);
	LoadString(NULL,98,cmds.cmdSetPLLDWPLLDDurationBeforePrecisionRetest,lenCmd);
	LoadString(NULL,99,cmds.cmdSetEnableDisableAutoDaylightSavingTime,lenCmd);
	LoadString(NULL,100,cmds.cmdSetStartEndDaylightSavingDateandTime,lenCmd);
	LoadString(NULL,101,cmds.cmdSetTicketedDeliveryFlagEnable,lenCmd);
	LoadString(NULL,102,cmds.cmdSetTicketedDeliveryTemperatureCompensationFlag,lenCmd);
	LoadString(NULL,103,cmds.cmdSetTicketedDeliveryCloseDayofWeek,lenCmd);
	LoadString(NULL,104,cmds.cmdSetEuroProtocolPrefix,lenCmd);
	/* communication setup */
	LoadString(NULL,105,cmds.cmdSetReceiverAutoDialTypeandStartTimeII,lenCmd);
	LoadString(NULL,106,cmds.cmdSetReceiverConfigurationFlag,lenCmd);
	LoadString(NULL,107,cmds.cmdSetReceiverLocationLabel,lenCmd);
	LoadString(NULL,108,cmds.cmdSetReceiverTelephoneNumber,lenCmd);
	LoadString(NULL,109,cmds.cmdSetReceiverDialingDestinationType,lenCmd);
	LoadString(NULL,110,cmds.cmdSetReceiverPortNumbertoDial,lenCmd);
	LoadString(NULL,111,cmds.cmdSetReceiverRetryNumber,lenCmd);
	LoadString(NULL,112,cmds.cmdSetReceiverRetryDelayTime,lenCmd);
	LoadString(NULL,113,cmds.cmdSetReceiverConfirmationReportFlag,lenCmd);
	LoadString(NULL,114,cmds.cmdSetFaxAutoDialMethod,lenCmd);
	LoadString(NULL,115,cmds.cmdSetReceiverReportList,lenCmd);
	LoadString(NULL,116,cmds.cmdSetReceiverAutoDialTypeandStartTime,lenCmd);
	LoadString(NULL,117,cmds.cmdSetReceiverAutoDialOnAlarms,lenCmd);
	LoadString(NULL,118,cmds.cmdAutodialAlarmStatus,lenCmd);
	LoadString(NULL,119,cmds.cmdSetDelayforAutodialonAlarmClear,lenCmd);
	LoadString(NULL,120,cmds.cmdSetReceiverAlarmStatus,lenCmd);
	LoadString(NULL,121,cmds.cmdSetRS232EndofMessage,lenCmd);
	/* warning, alarm, auto-print setup */
	LoadString(NULL,122,cmds.cmdSetTicketedVarianceAnalysisPrintoutFlags,lenCmd);
	LoadString(NULL,123,cmds.cmdSetTicketedDeliveryBookVariancePrintoutFlags,lenCmd);
	LoadString(NULL,124,cmds.cmdSetTicketedDeliveryVariancePrintoutFlags,lenCmd);
	LoadString(NULL,125,cmds.cmdSetRS232SecurityCodeperPort,lenCmd);
	LoadString(NULL,126,cmds.cmdSetDisplayFormatRS232ETXperPort,lenCmd);
	LoadString(NULL,127,cmds.cmdSetComputerFormatRS232ETXperPort,lenCmd);
	LoadString(NULL,128,cmds.cmdSetTankPeriodicTestNeededWarning,lenCmd);
	LoadString(NULL,129,cmds.cmdSetDaysBeforeTankPeriodicTestNeededWarning,lenCmd);
	LoadString(NULL,130,cmds.cmdSetDaysBeforeTankPeriodicTestNeededAlarm,lenCmd);
	LoadString(NULL,131,cmds.cmdSetTankAnnualTestNeededWarning,lenCmd);
	LoadString(NULL,132,cmds.cmdSetDaysBeforeTankAnnualTestNeededWarning,lenCmd);
	LoadString(NULL,133,cmds.cmdSetDaysBeforeTankAnnualTestNeededAlarm,lenCmd);
	LoadString(NULL,134,cmds.cmdSetCSLDEvaporationReidVaporPressureChart,lenCmd);
	LoadString(NULL,135,cmds.cmdSetLineReEnableMethod,lenCmd);
	LoadString(NULL,136,cmds.cmdSetPeriodicLineLeakTestAutoConfirm,lenCmd);
	LoadString(NULL,137,cmds.cmdSetAnnualLineLeakTestAutoConfirm,lenCmd);
	LoadString(NULL,138,cmds.cmdSetLinePeriodicTestNeededWarning,lenCmd);
	LoadString(NULL,139,cmds.cmdSetDaysBeforeLinePeriodicTestNeededWarning,lenCmd);
	LoadString(NULL,140,cmds.cmdSetDaysBeforeLinePeriodicTestNeededAlarm,lenCmd);
	LoadString(NULL,141,cmds.cmdSetLineAnnualTestNeededWarning,lenCmd);
	LoadString(NULL,142,cmds.cmdSetDaysBeforeLineAnnualTestNeededWarning,lenCmd);
	LoadString(NULL,143,cmds.cmdSetDaysBeforeLineAnnualTestNeededAlarm,lenCmd);
	LoadString(NULL,144,cmds.cmdSetReceiverAutoDialonAlarmII,lenCmd);
	LoadString(NULL,145,cmds.cmdSetInventoryRecordTime1234,lenCmd);
	/* in-tank setup */
	LoadString(NULL,146,cmds.cmdSetTankConfiguration,lenCmd);
	LoadString(NULL,147,cmds.cmdSetTankProductLabel,lenCmd);
	LoadString(NULL,148,cmds.cmdSetTankProductCode,lenCmd);
	LoadString(NULL,149,cmds.cmdSetTank1PointFullHeightVolume,lenCmd);
	LoadString(NULL,150,cmds.cmdSetTank4PointFull,lenCmd);
	LoadString(NULL,151,cmds.cmdSetTank20PointFull,lenCmd);
	LoadString(NULL,152,cmds.cmdSetTankDiameter,lenCmd);
	LoadString(NULL,153,cmds.cmdSetTankTilt,lenCmd);
	LoadString(NULL,154,cmds.cmdSetTankThermalExpansionCoefficient,lenCmd);
	LoadString(NULL,155,cmds.cmdSetTankLinearCalculatedFullVolume,lenCmd);
	LoadString(NULL,156,cmds.cmdSetTankStickHeightFunctionEnable,lenCmd);
	LoadString(NULL,157,cmds.cmdSetTankStickHeightOffset,lenCmd);
	LoadString(NULL,158,cmds.cmdSetTankProgrammableFloatParameters,lenCmd);
	LoadString(NULL,159,cmds.cmdSetTankProbeOffset,lenCmd);
	LoadString(NULL,160,cmds.cmdSetTankDeliveryDelay,lenCmd);
	LoadString(NULL,161,cmds.cmdSetTankLeakTestTypeStartTime,lenCmd);
	LoadString(NULL,162,cmds.cmdSetTankManifoldedPartners,lenCmd);
	LoadString(NULL,163,cmds.cmdSetCSLDProbabilityofDetection,lenCmd);
	LoadString(NULL,164,cmds.cmdSetCSLDClimateFactor,lenCmd);
	LoadString(NULL,165,cmds.cmdSetBIRMeterDataPresent,lenCmd);
	LoadString(NULL,166,cmds.cmdSetAccuChartUpdateScheduling,lenCmd);
	LoadString(NULL,167,cmds.cmdSetTankCSLDEvaporationCompensation,lenCmd);
	LoadString(NULL,168,cmds.cmdSetTankStageIIVaporRecovery,lenCmd);
	LoadString(NULL,169,cmds.cmdSetInTankLeakTestEarlyStop,lenCmd);
	LoadString(NULL,170,cmds.cmdSetInTankStaticGrossTestAutoConfirm,lenCmd);
	LoadString(NULL,171,cmds.cmdSetCSLDReportOnlyMode,lenCmd);
	LoadString(NULL,172,cmds.cmdSetTankLowLevelLimit,lenCmd);
	LoadString(NULL,173,cmds.cmdSetTankHighLevelLimit,lenCmd);
	LoadString(NULL,174,cmds.cmdSetTankOverfillLevelLimit,lenCmd);
	LoadString(NULL,175,cmds.cmdSetTankHighWaterLevelLimit,lenCmd);
	LoadString(NULL,176,cmds.cmdSetTankSuddenLossLimit,lenCmd);
	LoadString(NULL,177,cmds.cmdSetTankLeakAlarmLimit,lenCmd);
	LoadString(NULL,178,cmds.cmdSetTankHighWaterWarningLimit,lenCmd);
	LoadString(NULL,179,cmds.cmdSetTankMaximumVolumeLimit,lenCmd);
	LoadString(NULL,180,cmds.cmdSetTankDeliveryRequiredLimit,lenCmd);
	LoadString(NULL,181,cmds.cmdSetTankAnnualLeakTestMinimumVolume,lenCmd);
	LoadString(NULL,182,cmds.cmdSetTankLastAnnualTest,lenCmd);
	LoadString(NULL,183,cmds.cmdSetTankPeriodicTestType,lenCmd);
	LoadString(NULL,184,cmds.cmdSetEnableDisableTankLeakTestFailAlarms,lenCmd);
	LoadString(NULL,185,cmds.cmdSetCAP0ProbeConductiveBootFlag,lenCmd);
	LoadString(NULL,186,cmds.cmdSetMagProbeFloatSize,lenCmd);
	LoadString(NULL,187,cmds.cmdSetTankLeakTestNotify,lenCmd);
	LoadString(NULL,188,cmds.cmdSetTankLeakTestAveraging,lenCmd);
	LoadString(NULL,189,cmds.cmdSetTankTestSiphonBreak,lenCmd);
	LoadString(NULL,190,cmds.cmdSetLeakTestReportType,lenCmd);
	LoadString(NULL,191,cmds.cmdSetTankHRMReconciliationWarningLimit,lenCmd);
	LoadString(NULL,192,cmds.cmdSetTankHRMReconciliationAlarmLimit,lenCmd);
	LoadString(NULL,193,cmds.cmdSetTankPeriodicLeakTestMinimumVolume,lenCmd);
	LoadString(NULL,194,cmds.cmdSetTankAccuChartEndShapeTypeandFactor,lenCmd);
	LoadString(NULL,195,cmds.cmdSetTankLowLevelThresholdforSequentialLineManifold,lenCmd);
	LoadString(NULL,196,cmds.cmdFuelManagementGeneralSetupInquiry,lenCmd);
	LoadString(NULL,197,cmds.cmdSetFuelManagementDeliveryNeededWarning,lenCmd);
	LoadString(NULL,198,cmds.cmdSetFuelManagementAutomaticReportPrintTime,lenCmd);
	LoadString(NULL,199,cmds.cmdSetFuelManagementAverageDailySales,lenCmd);
	/* sensor setup */
	LoadString(NULL,200,cmds.cmdSetLiquidSensorConfiguration,lenCmd);
	LoadString(NULL,201,cmds.cmdSetLiquidSensorLocationLabel,lenCmd);
	LoadString(NULL,202,cmds.cmdSetLiquidSensorType,lenCmd);
	LoadString(NULL,203,cmds.cmdSetLiquidSensorCategory,lenCmd);
	LoadString(NULL,204,cmds.cmdSetVaporSensorConfiguration,lenCmd);
	LoadString(NULL,205,cmds.cmdSetVaporSensorLocationLabel,lenCmd);
	LoadString(NULL,206,cmds.cmdSetVaporSensorAlarmThreshold,lenCmd);
	LoadString(NULL,207,cmds.cmdSetVaporSensorCategory,lenCmd);
	LoadString(NULL,208,cmds.cmdSetGroundwaterSensorConfiguration,lenCmd);
	LoadString(NULL,209,cmds.cmdSetGroundwaterSensorLocationLabel,lenCmd);
	LoadString(NULL,210,cmds.cmdSetGroundwaterSensorCategory,lenCmd);
	LoadString(NULL,211,cmds.cmdSetTypeASensorConfiguration,lenCmd);
	LoadString(NULL,212,cmds.cmdSetTypeASensorLocationLabel,lenCmd);
	LoadString(NULL,213,cmds.cmdSetTypeASensorType,lenCmd);
	LoadString(NULL,214,cmds.cmdSetTypeASensorCategory,lenCmd);
	LoadString(NULL,215,cmds.cmdSetTypeBSensorConfiguration,lenCmd);
	LoadString(NULL,216,cmds.cmdSetTypeBSensorLocationLabel,lenCmd);
	LoadString(NULL,217,cmds.cmdSetTypeBSensorType,lenCmd);
	LoadString(NULL,218,cmds.cmdSetTypeBSensorCategory,lenCmd);
	LoadString(NULL,219,cmds.cmdSetUniversalSensorConfiguration,lenCmd);
	LoadString(NULL,220,cmds.cmdSetUniversalSensorLocationLabel,lenCmd);
	LoadString(NULL,221,cmds.cmdSetUniversalSensorType,lenCmd);
	LoadString(NULL,222,cmds.cmdSetUniversalSensorCategory,lenCmd);
	/* volumetric line leak setup */
	LoadString(NULL,223,cmds.cmdSetVolumetricLineLeakConfiguration,lenCmd);
	LoadString(NULL,224,cmds.cmdSetVolumetricLineLeakTankNumber,lenCmd);
	LoadString(NULL,225,cmds.cmdSetVolumetricLineLeak2InchPipeLength,lenCmd);
	LoadString(NULL,226,cmds.cmdSetVolumetricLineLeak3InchPipeLength,lenCmd);
	LoadString(NULL,227,cmds.cmdSetVolumetricLineLeakPumpPSI,lenCmd);
	LoadString(NULL,228,cmds.cmdSetVolumetricLineLeakPipingMaterial,lenCmd);
	LoadString(NULL,229,cmds.cmdSetVolumetricLineLeakShutdownRate,lenCmd);
	LoadString(NULL,230,cmds.cmdSetVolumetricLineLeakPumpSideTest,lenCmd);
	LoadString(NULL,231,cmds.cmdSetVolumetricLineLeakTestTypeStartTime,lenCmd);
	LoadString(NULL,232,cmds.cmdSetLineLeakLockoutSchedule,lenCmd);
	LoadString(NULL,233,cmds.cmdSetLineDisableAlarmAssignments,lenCmd);
	LoadString(NULL,234,cmds.cmdSetVolumetricLineLeakLastAnnualTest,lenCmd);
	LoadString(NULL,235,cmds.cmdSetVolumetricLineLeakDispenseMode,lenCmd);
	LoadString(NULL,236,cmds.cmdSetVolumetricLineLeakFuelType,lenCmd);
	LoadString(NULL,237,cmds.cmdSetVolumetricLineLeakWaitMethod,lenCmd);
	LoadString(NULL,238,cmds.cmdSetVolumetricLineLeakLocationLabel,lenCmd);
	LoadString(NULL,239,cmds.cmdSetVolumetricLineLeakBlendPartner,lenCmd);
	/* pump sensor setup */
	LoadString(NULL,240,cmds.cmdSetPumpSensorConfiguration,lenCmd);
	LoadString(NULL,241,cmds.cmdSetPumpSensorTankNumber,lenCmd);
	LoadString(NULL,242,cmds.cmdSetPumpSensorDispenseMode,lenCmd);
	/* pressure line leak setup */
	LoadString(NULL,243,cmds.cmdSetPressureLineLeakLowPressureShutoff,lenCmd);
	LoadString(NULL,244,cmds.cmdSetPressureLineLeakAltitudePressureOffset,lenCmd);
	LoadString(NULL,245,cmds.cmdSetPressureLineLeakSecondaryPipeLength,lenCmd);
	LoadString(NULL,246,cmds.cmdPressureLineLeakGeneralSetupInquiry,lenCmd);
	LoadString(NULL,247,cmds.cmdSetPressureLineLeakConfiguration,lenCmd);
	LoadString(NULL,248,cmds.cmdSetPressureLineLeakLabel,lenCmd);
	LoadString(NULL,249,cmds.cmdSetPressureLineLeak010GPHTestSchedule7,lenCmd);
	LoadString(NULL,250,cmds.cmdSetPressureLineLeakShutdownRate,lenCmd);
	LoadString(NULL,251,cmds.cmdSetPressureLineLeakTankNumber,lenCmd);
	LoadString(NULL,252,cmds.cmdSetPressureLineLeakDispenseMode,lenCmd);
	LoadString(NULL,253,cmds.cmdSetPressureLineLeakDisableAlarmAssignments,lenCmd);
	LoadString(NULL,254,cmds.cmdSetPressureLineLeakPipingMaterial,lenCmd);
	LoadString(NULL,255,cmds.cmdSetPressureLineLeakPrimaryPipeLength,lenCmd);
	LoadString(NULL,256,cmds.cmdSetPressureLineLeakSensorType,lenCmd);
	LoadString(NULL,257,cmds.cmdSetPressureLineLeak010GPHTestSchedule16,lenCmd);
	LoadString(NULL,258,cmds.cmdSetPressureLineLeak020GPHTestSchedule,lenCmd);
	LoadString(NULL,259,cmds.cmdSetPressureLineLeak01GPHAutoTestEnable,lenCmd);
	LoadString(NULL,260,cmds.cmdSetPressureLineLeakDispenseThreshold,lenCmd);
	/* reconciliation setup */
	LoadString(NULL,261,cmds.cmdDIMSoftwareRevision,lenCmd);
	LoadString(NULL,262,cmds.cmdSetMechanicalDispenserInterfaceString,lenCmd);
	LoadString(NULL,263,cmds.cmdSetElectronicDispenserInterfaceString,lenCmd);
	LoadString(NULL,264,cmds.cmdSetReconciliationAutoDailyClosingTime,lenCmd);
	LoadString(NULL,265,cmds.cmdSetAutoShiftClosingTime1234,lenCmd);
	LoadString(NULL,266,cmds.cmdSetPeriodicReconciliationMode,lenCmd);
	LoadString(NULL,267,cmds.cmdSetPeriodicReconciliationReportLength,lenCmd);
	LoadString(NULL,268,cmds.cmdSetPeriodicReconciliationAlarmFlag,lenCmd);
	LoadString(NULL,269,cmds.cmdSetPeriodicReconciliationAlarmThreshold,lenCmd);
	LoadString(NULL,270,cmds.cmdSetPeriodicReconciliationAlarmOffset,lenCmd);
	LoadString(NULL,271,cmds.cmdSetRemotePrinterReconciliationReportFormat,lenCmd);
	LoadString(NULL,272,cmds.cmdSetShiftManualAdjustmentValue,lenCmd);
	LoadString(NULL,273,cmds.cmdSetDailyManualAdjustmentValue,lenCmd);
	LoadString(NULL,274,cmds.cmdCloseCurrentReconciliationShift,lenCmd);
	LoadString(NULL,275,cmds.cmdClearTankMapTable,lenCmd);
	LoadString(NULL,276,cmds.cmdSetBIRTemperatureCompensationFlag,lenCmd);
	/* wireless plld setup */
	LoadString(NULL,277,cmds.cmdWPLLDLineLeakGeneralSetup,lenCmd);
	LoadString(NULL,278,cmds.cmdSetWPLLDLineLeakConfiguration,lenCmd);
	LoadString(NULL,279,cmds.cmdSetWPLLDLineLeakLabel,lenCmd);
	LoadString(NULL,280,cmds.cmdSetWPLLDLineLeak020GPHTestSchedule,lenCmd);
	LoadString(NULL,281,cmds.cmdSetWPLLDLineLeakShutdownRate,lenCmd);
	LoadString(NULL,282,cmds.cmdSetWPLLDLineLeakTankNumber,lenCmd);
	LoadString(NULL,283,cmds.cmdSetWPLLDLineLeakDispenseMode,lenCmd);
	LoadString(NULL,284,cmds.cmdSetWPLLDLineDisableAlarmAssignments,lenCmd);
	LoadString(NULL,285,cmds.cmdSetWPLLDLineLeakPipeType,lenCmd);
	LoadString(NULL,286,cmds.cmdSetWPLLDLineLeakPipeLength,lenCmd);
	LoadString(NULL,287,cmds.cmdSetWPLLDLineLeak010GPHTestSchedule,lenCmd);
	LoadString(NULL,288,cmds.cmdSetWPLLDLineLeak010GPHTestScheduleEnable,lenCmd);
	LoadString(NULL,289,cmds.cmdSetWPLLDLineLeakSecondaryPipeLength,lenCmd);
	LoadString(NULL,290,cmds.cmdSetWPLLDLineLeakAltitudePressureOffset,lenCmd);
	/* meter map & delivery ticket setup */
	LoadString(NULL,291,cmds.cmdSetBIRMeterTankmapping,lenCmd);
	LoadString(NULL,292,cmds.cmdSetMeterCalibrationOffset,lenCmd);
	LoadString(NULL,293,cmds.cmdSetTicketedDelivery,lenCmd);
	/* i/o device setup */
	LoadString(NULL,294,cmds.cmdSetLineDisableAlarmAssignmentsII,lenCmd);
	LoadString(NULL,295,cmds.cmdSetPressureLineDisableAlarmAssignmentsII,lenCmd);
	LoadString(NULL,296,cmds.cmdSetWPLLDLineDisableAlarmAssignmentsII,lenCmd);
	LoadString(NULL,297,cmds.cmdSetInputConfiguration,lenCmd);
	LoadString(NULL,298,cmds.cmdSetInputLocationLabel,lenCmd);
	LoadString(NULL,299,cmds.cmdSetInputType,lenCmd);
	LoadString(NULL,300,cmds.cmdSetInputDispenseMode,lenCmd);
	LoadString(NULL,301,cmds.cmdSetRelayConfiguration,lenCmd);
	LoadString(NULL,302,cmds.cmdSetRelayLocationLabel,lenCmd);
	LoadString(NULL,303,cmds.cmdSetRelayAlarmAssignments,lenCmd);
	LoadString(NULL,304,cmds.cmdSetRelayOrientation,lenCmd);
	LoadString(NULL,305,cmds.cmdSetRelayType,lenCmd);
	LoadString(NULL,306,cmds.cmdSetRelayTankAssignment,lenCmd);
	/* eeprom setup */
	LoadString(NULL,307,cmds.cmdRestoreAllSetupDatafromEEPROM,lenCmd);
	LoadString(NULL,308,cmds.cmdSaveAllSetupDatatoEEPROM,lenCmd);
	LoadString(NULL,309,cmds.cmdClearAllSetupDatafromEEPROM,lenCmd);
	/* misc setup */
	LoadString(NULL,310,cmds.cmdSetCommunicationPortData,lenCmd);
	LoadString(NULL,311,cmds.cmdInitializeCommunicationPortData,lenCmd);
	LoadString(NULL,312,cmds.cmdSetSiteLinkModemType,lenCmd);
	LoadString(NULL,313,cmds.cmdSetModemSetupString,lenCmd);
	LoadString(NULL,314,cmds.cmdSetDialToneValidationInterval,lenCmd);
	LoadString(NULL,315,cmds.cmdCommunicationStatusInformation,lenCmd);
	LoadString(NULL,316,cmds.cmdDTRNormalStateforSerialSatelliteBoards,lenCmd);
	LoadString(NULL,317,cmds.cmdSetAccuChartCalibrationRestart,lenCmd);
	LoadString(NULL,318,cmds.cmdSetRelayAlarmAssignmentsII,lenCmd);
/* diagnostic reports */
	/* system diagnostic reports */
	LoadString(NULL,319,cmds.cmdSelfTestResultsReport,lenCmd);
	LoadString(NULL,320,cmds.cmdSystemRevisionLevelReport,lenCmd);
	LoadString(NULL,321,cmds.cmdPCDiagnosticReport,lenCmd);
	LoadString(NULL,322,cmds.cmdSystemRevisionLevelReportII,lenCmd);
	/* in-tank diagnostic reports */
	LoadString(NULL,323,cmds.cmdProbeTypeandSerialNumber,lenCmd);
	LoadString(NULL,324,cmds.cmdProbeFactoryDryCalibrationValues,lenCmd);
	LoadString(NULL,325,cmds.cmdProbeFactoryWetCalibrationValues,lenCmd);
	LoadString(NULL,326,cmds.cmdProbeUpdatedDryCalibrationValues,lenCmd);
	LoadString(NULL,327,cmds.cmdProbeUpdatedWetCalibrationValues,lenCmd);
	LoadString(NULL,328,cmds.cmdProbeSegmentSensitivityRatios,lenCmd);
	LoadString(NULL,329,cmds.cmdProbeLastSampleBuffers,lenCmd);
	LoadString(NULL,330,cmds.cmdProbeFastAverageBuffers,lenCmd);
	LoadString(NULL,331,cmds.cmdProbeStandardAverageBuffers,lenCmd);
	LoadString(NULL,332,cmds.cmdProbeLongTermAverageBuffers,lenCmd);
	LoadString(NULL,333,cmds.cmdMagProbeOptionTable,lenCmd);
	LoadString(NULL,334,cmds.cmdProbeLeakTestFlagsPresentTest,lenCmd);
	LoadString(NULL,335,cmds.cmdProbeLeakTestFlagsStoredTest,lenCmd);
	LoadString(NULL,336,cmds.cmdProbeLeakTestFlagsGrossTest,lenCmd);
	LoadString(NULL,337,cmds.cmdTankLeakTestAveragingBuffers,lenCmd);
	LoadString(NULL,338,cmds.cmdCSLDDiagnosticsRateTable,lenCmd);
	LoadString(NULL,339,cmds.cmdCSLDDiagnosticsRateTest,lenCmd);
	LoadString(NULL,340,cmds.cmdCSLDDiagnosticsVolumeHistoryTable,lenCmd);
	LoadString(NULL,341,cmds.cmdCSLDDiagnosticsMovingAverageTable,lenCmd);
	LoadString(NULL,342,cmds.cmdCSLDDiagnosticsLeakTestStatus,lenCmd);
	LoadString(NULL,343,cmds.cmdCSLDMonthlyReport,lenCmd);
	LoadString(NULL,344,cmds.cmdHRMDiagnosticReport,lenCmd);
	LoadString(NULL,345,cmds.cmdHRMDailyHistory,lenCmd);
	LoadString(NULL,346,cmds.cmdFuelManagementDiagnosticReport,lenCmd);
	LoadString(NULL,347,cmds.cmdPowerOutageDiagnosticReport,lenCmd);
	/* sensor diagnostic reports */
	LoadString(NULL,348,cmds.cmdLiquidSensorDiagnosticReport,lenCmd);
	LoadString(NULL,349,cmds.cmdVaporSensorDiagnosticReport,lenCmd);
	LoadString(NULL,350,cmds.cmdVaporSensorConcentrationReport,lenCmd);
	LoadString(NULL,351,cmds.cmdGroundwaterSensorDiagnosticReport,lenCmd);
	LoadString(NULL,352,cmds.cmdGroundTemperatureSensorDiagnosticReport,lenCmd);
	LoadString(NULL,353,cmds.cmdTypeASensorDiagnosticReport,lenCmd);
	LoadString(NULL,354,cmds.cmdTypeBSensorDiagnosticReport,lenCmd);
	LoadString(NULL,355,cmds.cmdUniversalSensorDiagnosticReport,lenCmd);
	/* line leak diagnostic reports */
	LoadString(NULL,356,cmds.cmdVolumetricLineLeakStatus,lenCmd);
	LoadString(NULL,357,cmds.cmdVolumetricLineLeakDiagnosticGrossTestHistory,lenCmd);
	LoadString(NULL,358,cmds.cmdVolumetricLineLeak0102GPHDiagnosticHistory,lenCmd);
	LoadString(NULL,359,cmds.cmdPumpSensorDiagnostic,lenCmd);
	LoadString(NULL,360,cmds.cmdPressureLineLeakPressureOffsetTest,lenCmd);
	LoadString(NULL,361,cmds.cmdWPPLDLineLeakPressureOffsetTest,lenCmd);
	LoadString(NULL,362,cmds.cmdPressureLineLeakPressureOffsetMonitorReport,lenCmd);
	LoadString(NULL,363,cmds.cmdWPLLDLineLeakPressureOffsetMonitorReport,lenCmd);
	LoadString(NULL,364,cmds.cmdPressureLineLeakDiagnosticReport,lenCmd);
	LoadString(NULL,365,cmds.cmdWPLLDLineLeakDiagnosticReport,lenCmd);
	LoadString(NULL,366,cmds.cmdWPLLDLineLeakCommunicationDiagnosticReport,lenCmd);
	LoadString(NULL,367,cmds.cmdPressureLineLeak30GPHTestDiagnostic,lenCmd);
	LoadString(NULL,368,cmds.cmdPressureLineLeakMidrangeTestDiagnostic,lenCmd);
	LoadString(NULL,369,cmds.cmdPressureLineLeak02GPHTestDiagnostic,lenCmd);
	LoadString(NULL,370,cmds.cmdPressureLineLeak01GPHTestDiagnostic,lenCmd);
	LoadString(NULL,371,cmds.cmdWPLLDLineLeak30GPHTestDiagnostic,lenCmd);
	LoadString(NULL,372,cmds.cmdWPLLDLineLeakMidrangeTestDiagnostic,lenCmd);
	LoadString(NULL,373,cmds.cmdWPLLDLineLeak02GPHTestDiagnostic,lenCmd);
	LoadString(NULL,374,cmds.cmdWPLLDLineLeak01GPHTestDiagnostic,lenCmd);
	/* reconciliation diagnostic reports */
	LoadString(NULL,375,cmds.cmdAccuChartDiagnosticsReport,lenCmd);
	LoadString(NULL,376,cmds.cmdAccuChartStatusReport,lenCmd);
	LoadString(NULL,377,cmds.cmdAccuChartCalibrationHistoryReport,lenCmd);
	LoadString(NULL,378,cmds.cmdMDIMTotalizerReport,lenCmd);
	/* reconciliation reports */
	LoadString(NULL,379,cmds.cmdBasicInventoryReconciliationDailyRowReport,lenCmd);
	LoadString(NULL,380,cmds.cmdBasicInventoryReconciliationDailyColumnReport,lenCmd);
	LoadString(NULL,381,cmds.cmdBasicInventoryReconciliationShiftRowReport,lenCmd);
	LoadString(NULL,382,cmds.cmdBasicInventoryReconciliationShiftColumnReport,lenCmd);
	LoadString(NULL,383,cmds.cmdBasicInventoryReconciliationPeriodicRowReport106,lenCmd);
	LoadString(NULL,384,cmds.cmdBasicInventoryReconciliationPeriodicColumnReport106,lenCmd);
	LoadString(NULL,385,cmds.cmdBasicInventoryReconciliationPeriodicRowReport114,lenCmd);
	LoadString(NULL,386,cmds.cmdBasicInventoryReconciliationPeriodicColumnReport114,lenCmd);
	LoadString(NULL,387,cmds.cmdIndividualBasicReconciliationDailyHistoryDiagnostic,lenCmd);
	/* variance alaysis reports */
	LoadString(NULL,388,cmds.cmdPeriodicBookVariance,lenCmd);
	LoadString(NULL,389,cmds.cmdWeeklyBookVariance,lenCmd);
	LoadString(NULL,390,cmds.cmdDailyBookVariance,lenCmd);
	LoadString(NULL,391,cmds.cmdPeriodicVarianceAnalysisReport,lenCmd);
	LoadString(NULL,392,cmds.cmdWeeklyVarianceAnalysisReport,lenCmd);
	LoadString(NULL,393,cmds.cmdDailyVarianceAnalysisReport,lenCmd);
	LoadString(NULL,394,cmds.cmdPeriodicVarianceAnalysisDailyReport,lenCmd);
}

void TTLSDevice::read_comm_buffer_and_show_if_error(int res, TMemo *m)
{
	ini->setFileName(languagepath);

	/* if the ttlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return;

	/* show port line status */
	show_line_status(m);

	/* if write operation is success */
	if (!res)
	{
		/* if the user clicked on the ok button on the form; this means that
		   can read the communication class's global_buffer */
		if (!cancel_from_dialog)	res = comm->readBuffer();
		/* if read operation is success */
		if (!res)
		{
			/* get the buffer contain */
			std::string answer;
			if (!cancel_from_dialog)	answer = comm->global_buffer;
			/* show it in a multiline edit control on the main form */
			if (m)
			{
				if (!cancel_from_dialog)
				{
					m->Lines->Add(STR_ANSWERSELECTOR);
					m->Lines->Add(answer.c_str());
				}
			}
		}
		else
		{
			/* read fails */
			switch (res)
			{
				case e_noserialdevice:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(1));
					}
					break;
				case e_readfailed:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(2));
					}
					break;
				case e_nothingtoread:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(3));
					}
					break;
				default:;
			}
        }
	}
	else
	{
    	/* write fails */
		switch (res)
		{
			case e_noserialdevice:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(4));
					}
				break;
			case e_writecount_msgtodev:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(5));
					}
				break;
			case e_writefailed:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(6));
					}
				break;
			case e_writebytes:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(7));
					}
				break;
			case e_clearing:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(8));
                    }
				break;
			case e_checksum:
					if (m)
					{
						m->Lines->Add(STR_ANSWERSELECTOR);
						m->Lines->Add(ini->LoadErrorString(9));
					}
				break;
			default:;
		}
	}
	cancel_from_dialog = false;
}

int TTLSDevice::create_command_id(int page_idx, int group_idx, int item_idx)
{
	AnsiString id_str;
	int list_index;

	try
	{
		id_str = IntToStr(page_idx)+","+IntToStr(group_idx)+","+IntToStr(item_idx);
	}
	catch(EConvertError &e)
	{
		/* if any input parameter is not an integer value set string to
		   default */
        id_str = "000";
    }

	/* get the position of the string from the cmd_str_list */
	list_index = cmd_str_list->IndexOf(id_str);

	if ( (list_index < 0) || (list_index > CNT_MAX_COMMAND_ID-1) )
	{
    	/* if the string not exists in the string list set index to default */
		list_index = 0;        
	}

	return cmd_id_arr[list_index];
}


/* public */
TTLSDevice::TTLSDevice(void)
{
	cancel_from_dialog = false;
	first_time_run = true;

	init_command_strings();

	wProc = new TwInProcess(Application);
}
TTLSDevice::TTLSDevice(char *portname)
{
	standaloneList = NULL;
	ini = new THandleIni("");

	cancel_from_dialog = false;
	first_time_run = true;

	/* it loads the command buffers */
	init_command_strings();

	/* this is a string list and an integer array; in the string list are
	   strings with the following format: "0112"; this means that the user
	   selected and clicked on the main form: the first page
	   (mainsetupcategories_rg) and Communication item from Setup functions
	   radio group (first item) and the 12. item from the list box; in the integer array
	   in the same position is the command id what makes the selected command. */
	init_command_string_list_and_id_array();

	/* show the data transmitting status */
	wProc = new TwInProcess(Application);

	/* create communication object and open the specified port */
	comm = new TCommunication();

	int result = comm->OpenPort(portname);

	/* show if it was error on open port */
	if (result==e_noserialdevice)
	{
		/* could not find the specified port */
		AnsiString msg = "Could not open ";
		msg += portname;
		Application->MessageBox(msg.c_str(), "TLStool", 16);
    	isPortOpened = false;
	}
	else	isPortOpened = true;
	if (result==e_initsettings)
	{
		/* could not get dcb and timeouts structure from the port */
		AnsiString msg = "Could not set properties on ";
		msg += portname;
		Application->MessageBox(msg.c_str(), "TLStool", 16);
	}
	if (result==e_updatesettings)
	{
		/* could not set port properties */
		AnsiString msg = "Could not set properties on ";
		msg += portname;
		Application->MessageBox(msg.c_str(), "TLStool", 16);
	}
	if (result==e_settimeout)
	{
    	/* could not set port timeouts */
		AnsiString msg = "Could not set time outs on ";
		msg += portname;
		Application->MessageBox(msg.c_str(), "TLStool", 16);
	}
}

TTLSDevice::TTLSDevice(char *portname, char *filename)
{
	wProc = NULL;
	cmd_str_list = NULL;
	isPortOpened = false;

	/* create list for standalonecommand objects */
	standaloneList = new TList;

	/* create communication object */
	comm = new TCommunication();

	/* create ini object */
	ini = new THandleIni(filename);

	/* load list with standalonecommand objects */
	for (int i=75; i < 319; i++)
	{
		char cmdstr[lenCmd];
    	char desc[lenCmd];
		LoadString(NULL,i,cmdstr,lenCmd);
		LoadString(NULL,i+325,desc,lenCmd);
		sc = new TStandaloneCommand(comm,ini,portname,filename,cmdstr,desc);
		standaloneList->Add(sc);
	}
}

TTLSDevice::~TTLSDevice(void)
{
	if (standaloneList)
	{
		for (int i=0; i < standaloneList->Count; i++)
		{
			TStandaloneCommand *tmp_sc = reinterpret_cast<TStandaloneCommand*>(standaloneList->Items[i]);
			delete tmp_sc;
        	tmp_sc = NULL;
		}
		delete standaloneList;
		standaloneList = NULL;
	}

	if (ini)
	{
		delete ini;
		ini = NULL;
	}

	if (wProc)
	{
		delete wProc;
		wProc = NULL;
	}

	delete cmd_str_list;

	if (comm)
	{
		/* close the specified port and free resource */
		comm->ClosePort();

		delete comm;
		comm = NULL;
	}
}

void TTLSDevice::get(int page_idx, int group_idx, int item_idx, TMemo *disp,
	char cmd_type, char item_nr, char item_nrs[2])
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return;

	/* it takes the communication function errors */
	int result;
	/* calculate the command ids from the main form::page control-radio group-
	   -list box item idexes */
	int cmd_id = create_command_id(page_idx, group_idx, item_idx);

	/* check and if fail, set the command type because get() function can have
	   only the i or I chars */
	if ( (cmd_type=='s') || (cmd_type=='S') )
	{
		cmd_type = 'I';
	}

	/* select the command to send */
	switch (cmd_id)
	{
		case SystemResetID:
			//copy_char(cmd_type,cmds.cmdSystemReset,1);
			//result = comm->sendBuffer(cmds.cmdSystemReset, lenGetCmd);
			break;
		/*
		...
		*/
		case SystemStatusReportID: 
			result = send(cmd_type,cmds.cmdSystemStatusReport,
				lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		/*
		...
		*/
		case SetTimeofdayID:
			result = send(cmd_type,cmds.cmdSetTimeofday,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetShiftStartTime1234ID:
			result = send(cmd_type,cmds.cmdSetShiftStartTime1234,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetPrintHeaderLine1234ID:
			result = send(cmd_type,cmds.cmdSetPrintHeaderLine1234,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetSystemRS232SecurityCodeID:
			result = send(cmd_type,cmds.cmdSetSystemRS232SecurityCode,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetSystemTypeLanguageFlagsID1:
		case SetSystemTypeLanguageFlagsID15:
			result = send(cmd_type,cmds.cmdSetSystemTypeLanguageFlags1,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetPLLDWPLLDDurationBeforePrecisionRetestID:
			result = send(cmd_type,cmds.cmdSetPLLDWPLLDDurationBeforePrecisionRetest,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetEnableDisableAutoDaylightSavingTimeID:
			result = send(cmd_type,cmds.cmdSetEnableDisableAutoDaylightSavingTime,lenCmd,1,"00",0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetStartEndDaylightSavingDateandTime,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetRemotePrinterPageEjectFlagID:
			result = send(cmd_type,cmds.cmdSetRemotePrinterPageEjectFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetPrintTemperatureCompensationFlagID:
			result = send(cmd_type,cmds.cmdSetPrintTemperatureCompensationFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTemperatureCompensationValueID:
			result = send(cmd_type,cmds.cmdSetTemperatureCompensationValue,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetSystemDateTimeDisplayFormatID: 
			result = send(cmd_type,cmds.cmdSetSystemDateTimeDisplayFormat,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetBIRShiftPrintoutsFlagID:
			result = send(cmd_type,cmds.cmdSetBIRShiftPrintoutsFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetBIRDailyPrintoutsFlagID:
			result = send(cmd_type,cmds.cmdSetBIRDailyPrintoutsFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTankerLoadReportFlagID:
			result = send(cmd_type,cmds.cmdSetTankerLoadReportFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetHProtocolHeightVolumeformatID:
			result = send(cmd_type,cmds.cmdSetHProtocolHeightVolumeformat,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetHRMQPLDMonthlyPrintoutID:
			result = send(cmd_type,cmds.cmdSetHRMQPLDMonthlyPrintout,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetRedirectLocalPrintoutFlagID:
			result = send(cmd_type,cmds.cmdSetRedirectLocalPrintoutFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTicketedDeliveryFlagEnableID:
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryFlagEnable,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTicketedDeliveryTemperatureCompensationFlagID: 
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryTemperatureCompensationFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTicketedDeliveryCloseDayofWeekID:
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryCloseDayofWeek,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetEuroProtocolPrefixID:
			result = send(cmd_type,cmds.cmdSetEuroProtocolPrefix,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetReceiverConfigurationFlagID:
			result = send(cmd_type,cmds.cmdSetReceiverConfigurationFlag,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverLocationLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverTelephoneNumber,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverDialingDestinationType,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverPortNumbertoDial,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverRetryNumber,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverRetryDelayTime,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			read_comm_buffer_and_show_if_error(result, disp);
			result = send(cmd_type,cmds.cmdSetReceiverConfirmationReportFlag,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetReceiverReportListID:
			result = send(cmd_type,cmds.cmdSetReceiverReportList,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetReceiverAutoDialOnAlarmsID:
			result = send(cmd_type,cmds.cmdSetReceiverAutoDialOnAlarms,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;    
		case SetRS232EndofMessageID:
			result = send(cmd_type,cmds.cmdSetRS232EndofMessage,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTicketedVarianceAnalysisPrintoutFlagsID:
			result = send(cmd_type,cmds.cmdSetTicketedVarianceAnalysisPrintoutFlags,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTicketedDeliveryBookVariancePrintoutFlagsID:
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryBookVariancePrintoutFlags,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTicketedDeliveryVariancePrintoutFlagsID:
			result = send(cmd_type,cmds.cmdSetTicketedDeliveryVariancePrintoutFlags,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTankPeriodicTestNeededWarningID:
			result = send(cmd_type,cmds.cmdSetTankPeriodicTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeTankPeriodicTestNeededWarningID: 
			result = send(cmd_type,cmds.cmdSetDaysBeforeTankPeriodicTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeTankPeriodicTestNeededAlarmID:
			result = send(cmd_type,cmds.cmdSetDaysBeforeTankPeriodicTestNeededAlarm,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTankAnnualTestNeededWarningID:
			result = send(cmd_type,cmds.cmdSetTankAnnualTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeTankAnnualTestNeededWarningID:
			result = send(cmd_type,cmds.cmdSetDaysBeforeTankAnnualTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeTankAnnualTestNeededAlarmID:
			result = send(cmd_type,cmds.cmdSetDaysBeforeTankAnnualTestNeededAlarm,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetLineReEnableMethodID:   
			result = send(cmd_type,cmds.cmdSetLineReEnableMethod,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetLinePeriodicTestNeededWarningID:
			result = send(cmd_type,cmds.cmdSetLinePeriodicTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeLinePeriodicTestNeededWarningID:
			result = send(cmd_type,cmds.cmdSetDaysBeforeLinePeriodicTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeLinePeriodicTestNeededAlarmID:
			result = send(cmd_type,cmds.cmdSetDaysBeforeLinePeriodicTestNeededAlarm,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetLineAnnualTestNeededWarningID: 
			result = send(cmd_type,cmds.cmdSetLineAnnualTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeLineAnnualTestNeededWarningID:
			result = send(cmd_type,cmds.cmdSetDaysBeforeLineAnnualTestNeededWarning,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetDaysBeforeLineAnnualTestNeededAlarmID: 
			result = send(cmd_type,cmds.cmdSetDaysBeforeLineAnnualTestNeededAlarm,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetPeriodicLineLeakTestAutoConfirmID: 
			result = send(cmd_type,cmds.cmdSetPeriodicLineLeakTestAutoConfirm,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetAnnualLineLeakTestAutoConfirmID:
			result = send(cmd_type,cmds.cmdSetAnnualLineLeakTestAutoConfirm,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTankConfigurationID:
			result = send(cmd_type,cmds.cmdSetTankConfiguration,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankProductLabelID:
			result = send(cmd_type,cmds.cmdSetTankProductLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankProductCodeID:
			result = send(cmd_type,cmds.cmdSetTankProductCode,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankDiameterID: 
			result = send(cmd_type,cmds.cmdSetTankDiameter,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankTiltID:    
			result = send(cmd_type,cmds.cmdSetTankTilt,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankThermalExpansionCoefficientID:
			result = send(cmd_type,cmds.cmdSetTankThermalExpansionCoefficient,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankLinearCalculatedFullVolumeID: 
			result = send(cmd_type,cmds.cmdSetTankLinearCalculatedFullVolume,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankStickHeightFunctionEnableID: 
			result = send(cmd_type,cmds.cmdSetTankStickHeightFunctionEnable,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetTankStickHeightOffsetID:
			result = send(cmd_type,cmds.cmdSetTankStickHeightOffset,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankProbeOffsetID:
			result = send(cmd_type,cmds.cmdSetTankProbeOffset,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankDeliveryDelayID:
			result = send(cmd_type,cmds.cmdSetTankDeliveryDelay,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankManifoldedPartnersID:
			result = send(cmd_type,cmds.cmdSetTankManifoldedPartners,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetBIRMeterDataPresentID:
			result = send(cmd_type,cmds.cmdSetBIRMeterDataPresent,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetAccuChartUpdateSchedulingID: 
			result = send(cmd_type,cmds.cmdSetAccuChartUpdateScheduling,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankLowLevelLimitID:  
			result = send(cmd_type,cmds.cmdSetTankLowLevelLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankHighLevelLimitID:
			result = send(cmd_type,cmds.cmdSetTankHighLevelLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankOverfillLevelLimitID:
			result = send(cmd_type,cmds.cmdSetTankOverfillLevelLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankHighWaterLevelLimitID:
			result = send(cmd_type,cmds.cmdSetTankHighWaterLevelLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankSuddenLossLimitID:  
			result = send(cmd_type,cmds.cmdSetTankSuddenLossLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankLeakAlarmLimitID:
			result = send(cmd_type,cmds.cmdSetTankLeakAlarmLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankHighWaterWarningLimitID:
			result = send(cmd_type,cmds.cmdSetTankHighWaterWarningLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankMaximumVolumeLimitID: 
			result = send(cmd_type,cmds.cmdSetTankMaximumVolumeLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankDeliveryRequiredLimitID:
			result = send(cmd_type,cmds.cmdSetTankDeliveryRequiredLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankAnnualLeakTestMinimumVolumeID:
			result = send(cmd_type,cmds.cmdSetTankAnnualLeakTestMinimumVolume,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankPeriodicTestTypeID: 
			result = send(cmd_type,cmds.cmdSetTankPeriodicTestType,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetEnableDisableTankLeakTestFailAlarmsID: 
			result = send(cmd_type,cmds.cmdSetEnableDisableTankLeakTestFailAlarms,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetMagProbeFloatSizeID:
			result = send(cmd_type,cmds.cmdSetMagProbeFloatSize,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankLeakTestNotifyID:
			result = send(cmd_type,cmds.cmdSetTankLeakTestNotify,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankLeakTestAveragingID:
			result = send(cmd_type,cmds.cmdSetTankLeakTestAveraging,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankTestSiphonBreakID:
			result = send(cmd_type,cmds.cmdSetTankTestSiphonBreak,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankHRMReconciliationWarningLimitID:
			result = send(cmd_type,cmds.cmdSetTankHRMReconciliationWarningLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankHRMReconciliationAlarmLimitID:
			result = send(cmd_type,cmds.cmdSetTankHRMReconciliationAlarmLimit,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankPeriodicLeakTestMinimumVolumeID:
			result = send(cmd_type,cmds.cmdSetTankPeriodicLeakTestMinimumVolume,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankAccuChartEndShapeTypeandFactorID:
			result = send(cmd_type,cmds.cmdSetTankAccuChartEndShapeTypeandFactor,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetTankLowLevelThresholdforSequentialLineManifoldID:
			result = send(cmd_type,cmds.cmdSetTankLowLevelThresholdforSequentialLineManifold,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetLiquidSensorConfigurationID:
			result = send(cmd_type,cmds.cmdSetLiquidSensorConfiguration,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetLiquidSensorLocationLabelID:
			result = send(cmd_type,cmds.cmdSetLiquidSensorLocationLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetLiquidSensorTypeID: 
			result = send(cmd_type,cmds.cmdSetLiquidSensorType,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetLiquidSensorCategoryID:   
			result = send(cmd_type,cmds.cmdSetLiquidSensorCategory,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetVaporSensorConfigurationID:
			result = send(cmd_type,cmds.cmdSetVaporSensorConfiguration,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetVaporSensorLocationLabelID: 
			result = send(cmd_type,cmds.cmdSetVaporSensorLocationLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetVaporSensorAlarmThresholdID:
			result = send(cmd_type,cmds.cmdSetVaporSensorAlarmThreshold,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetVaporSensorCategoryID:
			result = send(cmd_type,cmds.cmdSetVaporSensorCategory,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetGroundwaterSensorConfigurationID:
			result = send(cmd_type,cmds.cmdSetGroundwaterSensorConfiguration,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetGroundwaterSensorLocationLabelID: 
			result = send(cmd_type,cmds.cmdSetGroundwaterSensorLocationLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetGroundwaterSensorCategoryID:
			result = send(cmd_type,cmds.cmdSetGroundwaterSensorCategory,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetMechanicalDispenserinterfaceStringID:
			result = send(cmd_type,cmds.cmdSetMechanicalDispenserInterfaceString,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetReconciliationAutoDailyClosingTimeID: 
			result = send(cmd_type,cmds.cmdSetReconciliationAutoDailyClosingTime,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetAutoShiftClosingTime1234ID:
			result = send(cmd_type,cmds.cmdSetAutoShiftClosingTime1234,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetPeriodicReconciliationModeID:
			result = send(cmd_type,cmds.cmdSetPeriodicReconciliationMode,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetPeriodicReconciliationAlarmFlagID:
			result = send(cmd_type,cmds.cmdSetPeriodicReconciliationAlarmFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetPeriodicReconciliationAlarmThresholdID:
			result = send(cmd_type,cmds.cmdSetPeriodicReconciliationAlarmThreshold,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetPeriodicReconciliationAlarmOffsetID:
			result = send(cmd_type,cmds.cmdSetPeriodicReconciliationAlarmOffset,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetRemotePrinterReconciliationReportFormatID:
			result = send(cmd_type,cmds.cmdSetRemotePrinterReconciliationReportFormat,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetBIRTemperatureCompensationFlagID:
			result = send(cmd_type,cmds.cmdSetBIRTemperatureCompensationFlag,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetBIRMeterTankmappingID: 
			result = send(cmd_type,cmds.cmdSetBIRMeterTankmapping,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetMeterCalibrationOffsetID:
			result = send(cmd_type,cmds.cmdSetMeterCalibrationOffset,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetInputConfigurationID:
			result = send(cmd_type,cmds.cmdSetInputConfiguration,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetInputLocationLabelID:
			result = send(cmd_type,cmds.cmdSetInputLocationLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetInputTypeID:
			result = send(cmd_type,cmds.cmdSetInputType,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetInputDispenseModeID:
			result = send(cmd_type,cmds.cmdSetInputDispenseMode,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetRelayConfigurationID:
			result = send(cmd_type,cmds.cmdSetRelayConfiguration,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetRelayLocationLabelID:
			result = send(cmd_type,cmds.cmdSetRelayLocationLabel,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetRelayAlarmAssignmentsID:  
			result = send(cmd_type,cmds.cmdSetRelayAlarmAssignments,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetRelayOrientationID:
			result = send(cmd_type,cmds.cmdSetRelayOrientation,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetRelayTypeID:
			result = send(cmd_type,cmds.cmdSetRelayType,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case SetRelayTankAssignmentID: 
			result = send(cmd_type,cmds.cmdSetRelayTankAssignment,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		case RestoreAllSetupDatafromEEPROMID:
			result = send(cmd_type,cmds.cmdRestoreAllSetupDatafromEEPROM,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SaveAllSetupDatatoEEPROMID:
			result = send(cmd_type,cmds.cmdSaveAllSetupDatatoEEPROM,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case ClearAllSetupDatafromEEPROMID:
			result = send(cmd_type,cmds.cmdClearAllSetupDatafromEEPROM,lenCmd,1,"00",0,5,2,'\0',7,1);
			break;
		case SetCommunicationPortDataID:
			result = send(cmd_type,cmds.cmdSetCommunicationPortData,lenCmd,1,item_nrs,0,5,2,'\0',7,1);
			break;
		default:;
	}

	/* get comm buffer and show error if it exists */
	read_comm_buffer_and_show_if_error(result, disp);
}

void TTLSDevice::set(int page_idx, int group_idx, int item_idx, TMemo *disp,
	char cmd_type)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return;

	/* it takes the communication function errors */
	int result;
	/* if this is false the setXXX function make self to get the answer */
	bool need_answer;
	/* calculate the command ids from the main form::page control-radio group-
	   -list box item idexes */
	int cmd_id = create_command_id(page_idx, group_idx, item_idx);

	/* check and if fail, set the command type because set() function can have
	   only the s or S chars */
	if ( (cmd_type=='i') || (cmd_type=='I') )
	{
		cmd_type = 'S';
	}

	/* select the command to send */
	switch (cmd_id)
	{
		case SystemResetID:                  
			copy_char(cmd_type,cmds.cmdSystemReset,1);
			result = comm->sendBuffer(cmds.cmdSystemReset, lenGetCmd);
			need_answer = true;
			break;
		/*
		...
		*/
		case SetTimeofdayID:
			result = showSetTimeofday(cmd_type, page_idx, group_idx, item_idx,
										disp);
			need_answer = true;
			break;
		case SetShiftStartTime1234ID:
			result = showSetShiftStartTime1234(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetPrintHeaderLine1234ID:
			result = showSetPrintHeaderLine1234(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetSystemRS232SecurityCodeID:
			result = showSetSystemRS232SecurityCodeDlg(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = true;
			break;
		case SetSystemTypeLanguageFlagsID1:
		case SetSystemTypeLanguageFlagsID15:
			result = showSetSystemTypeLanguageFlagsDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetPLLDWPLLDDurationBeforePrecisionRetestID:
			result = showSetPLLDWPLLDDurationBeforePrecisionRetestDlg(cmd_type,
														page_idx, group_idx,
														item_idx, disp);
			need_answer = true;
			break;
		case SetEnableDisableAutoDaylightSavingTimeID:
			result = showSetAutoDaylightSavingTimeDlg(cmd_type,
														page_idx, group_idx,
														item_idx, disp);
			need_answer = false;
			break;
		case SetRemotePrinterPageEjectFlagID:
			result = showSetRemotePrinterPageEjectFlagDlg(cmd_type, page_idx,
															group_idx, item_idx,
															disp);
			need_answer = true;
			break;
		case SetPrintTemperatureCompensationFlagID:
			result = showSetPrintTemperatureCompensationFlagDlg(cmd_type, page_idx,
															group_idx, item_idx,
															disp);
			need_answer = true;
			break;
		case SetTemperatureCompensationValueID:
			result = showSetTemperatureCompensationValueDlg(cmd_type, page_idx,
															group_idx, item_idx,
															disp);
			need_answer = true;
			break;
		case SetSystemDateTimeDisplayFormatID:
			result = showSetSystemDateTimeDisplayFormatDlg(cmd_type, page_idx,
															group_idx, item_idx,
															disp);
			need_answer = true;
			break;
		case SetBIRShiftPrintoutsFlagID:
			result = showSetBIRShiftPrintoutsFlagDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetBIRDailyPrintoutsFlagID:
			result = showSetBIRDailyPrintoutsFlagDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTankerLoadReportFlagID:
			result = showSetTankerLoadReportFlagDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetHProtocolHeightVolumeformatID:
			result = showSetHProtocolHeightVolumeformatDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetHRMQPLDMonthlyPrintoutID:
			result = showSetHRMQPLDMonthlyPrintoutDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetRedirectLocalPrintoutFlagID:
			result = showSetRedirectLocalPrintoutFlagDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTicketedDeliveryFlagEnableID:
			result = showSetTicketedDeliveryFlagEnableDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTicketedDeliveryTemperatureCompensationFlagID:
			result = showSetTicketedDeliveryTemperatureCompensationFlagDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTicketedDeliveryCloseDayofWeekID:
			result = showSetTicketedDeliveryCloseDayofWeekDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetEuroProtocolPrefixID:
			result = showSetEuroProtocolPrefixDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetReceiverConfigurationFlagID:
			result = showSetReceiverConfigurationFlagDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetReceiverReportListID:
			result = showSetReceiverReportListDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetReceiverAutoDialOnAlarmsID:
			result = showSetReceiverAutoDialOnAlarmsDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetRS232EndofMessageID:
			result = showSetRS232EndofMessageDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTicketedVarianceAnalysisPrintoutFlagsID:
			result = showSetTicketedVarianceAnalysisPrintoutFlagsDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTicketedDeliveryBookVariancePrintoutFlagsID:
			result = showSetTicketedDeliveryBookVariancePrintoutFlagsDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTicketedDeliveryVariancePrintoutFlagsID:
			result = showSetTicketedDeliveryVariancePrintoutFlagsDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTankPeriodicTestNeededWarningID:
		case SetDaysBeforeTankPeriodicTestNeededWarningID:
		case SetDaysBeforeTankPeriodicTestNeededAlarmID:
			result = showSetTankPeriodicTestNeededWarningDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetTankAnnualTestNeededWarningID:
		case SetDaysBeforeTankAnnualTestNeededWarningID:
		case SetDaysBeforeTankAnnualTestNeededAlarmID:
			result = showSetTankAnnualTestNeededWarningDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetLineReEnableMethodID:
			result = showSetLineReEnableMethodDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetLinePeriodicTestNeededWarningID:
		case SetDaysBeforeLinePeriodicTestNeededWarningID:
		case SetDaysBeforeLinePeriodicTestNeededAlarmID:
			result = showSetLinePeriodicTestNeededWarningDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetLineAnnualTestNeededWarningID:
		case SetDaysBeforeLineAnnualTestNeededWarningID:
		case SetDaysBeforeLineAnnualTestNeededAlarmID:
			result = showSetLineAnnualTestNeededWarningDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetPeriodicLineLeakTestAutoConfirmID:
			result = showSetPeriodicLineLeakTestAutoConfirmDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetAnnualLineLeakTestAutoConfirmID:
			result = showSetAnnualLineLeakTestAutoConfirmDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTankConfigurationID:
			result = showSetTankConfigurationDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetTankStickHeightFunctionEnableID:
			result = showSetTankStickHeightFunctionEnableDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = true;
			break;
		case SetTankProductLabelID:
		case SetTankProductCodeID:
		case SetTankDiameterID:
		case SetTankTiltID:
		case SetTankThermalExpansionCoefficientID:
		case SetTankStickHeightOffsetID:
		case SetTankProbeOffsetID:
		case SetTankDeliveryDelayID:
		case SetTankManifoldedPartnersID:
		case SetBIRMeterDataPresentID:
		case SetAccuChartUpdateSchedulingID:
		case SetTankLowLevelLimitID:
		case SetTankHighLevelLimitID:
		case SetTankOverfillLevelLimitID:
		case SetTankHighWaterLevelLimitID:
		case SetTankSuddenLossLimitID:
		case SetTankLeakAlarmLimitID:
		case SetTankHighWaterWarningLimitID:
		case SetTankMaximumVolumeLimitID:
		case SetTankDeliveryRequiredLimitID:
		case SetTankAnnualLeakTestMinimumVolumeID:
		case SetTankPeriodicTestTypeID:
		case SetEnableDisableTankLeakTestFailAlarmsID:
		case SetMagProbeFloatSizeID:
		case SetTankLeakTestNotifyID:
		case SetTankLeakTestAveragingID:
		case SetTankTestSiphonBreakID:
		case SetTankHRMReconciliationWarningLimitID:
		case SetTankHRMReconciliationAlarmLimitID:
		case SetTankPeriodicLeakTestMinimumVolumeID:
		case SetTankAccuChartEndShapeTypeandFactorID:
		case SetTankLowLevelThresholdforSequentialLineManifoldID:
			result = showSetTankSetupDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetLiquidSensorConfigurationID:
			result = showSetLiquidSensorConfigurationDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetLiquidSensorLocationLabelID:
		case SetLiquidSensorTypeID:
		case SetLiquidSensorCategoryID:
			result = showSetLiquidSensorSetupDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetVaporSensorConfigurationID:
			result = showSetVaporSensorConfigurationDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetVaporSensorLocationLabelID:
		case SetVaporSensorAlarmThresholdID:
		case SetVaporSensorCategoryID:
			result = showSetVaporSensorSetupDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetGroundwaterSensorConfigurationID:
			result = showSetGroundwaterSensorConfigurationDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;               
		case SetGroundwaterSensorLocationLabelID:
		case SetGroundwaterSensorCategoryID:
			result = showGroundWaterSensorSetupDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
        	break;
		case SetTankLinearCalculatedFullVolumeID:
			result = showSetTankLinearCalculatedFullVolumeDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetMechanicalDispenserinterfaceStringID:
			result = showSetMechanicalDispenserinterfaceStringDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetReconciliationAutoDailyClosingTimeID:
			result = showSetReconciliationAutoDailyClosingTimeDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;
		case SetAutoShiftClosingTime1234ID:
			result = showSetAutoShiftClosingTime1234(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetPeriodicReconciliationModeID:
			result = showSetPeriodicReconciliationMode(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetPeriodicReconciliationAlarmFlagID:
		case SetPeriodicReconciliationAlarmThresholdID:
		case SetPeriodicReconciliationAlarmOffsetID:
			result = showSetPeriodicReconciliationAlarmFlag(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetRemotePrinterReconciliationReportFormatID:
			result = showSetRemotePrinterReconciliationReportFormat(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = true;
			break;
		case SetBIRTemperatureCompensationFlagID:
			result = showSetBIRTemperatureCompensationFlag(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = true;
			break;
		case SetBIRMeterTankmappingID:
			result = showSetBIRMeterTankmapping(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = true;
			break;
		case SetMeterCalibrationOffsetID:
			result = showSetMeterCalibrationOffset(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = true;
			break;
		case SetInputConfigurationID:
			result = showSetInputConfiguration(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetInputLocationLabelID:
		case SetInputTypeID:
		case SetInputDispenseModeID:
			result = showSetInputSetupDlg(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetRelayConfigurationID:
			result = showSetRelayConfigurationDlg(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case SetRelayLocationLabelID:
		case SetRelayAlarmAssignmentsID:
		case SetRelayOrientationID:
		case SetRelayTypeID:
		case SetRelayTankAssignmentID:
			result = showSetRelaySetupDlg(cmd_type, page_idx, group_idx,
												item_idx, disp);
			need_answer = false;
			break;
		case RestoreAllSetupDatafromEEPROMID:
			result = showArchiveUtilityDlg(cmd_type, page_idx, group_idx,
												item_idx, disp, 0);
			need_answer = true;
			break;
		case SaveAllSetupDatatoEEPROMID:
			result = showArchiveUtilityDlg(cmd_type, page_idx, group_idx,
												item_idx, disp, 1);
			need_answer = true;
			break;
		case ClearAllSetupDatafromEEPROMID:
			result = showArchiveUtilityDlg(cmd_type, page_idx, group_idx,
												item_idx, disp, 2);
			need_answer = true;
			break;
		case SetCommunicationPortDataID:
			result = showSetCommunicationPortDataDlg(cmd_type, page_idx,
														group_idx, item_idx,
														disp);
			need_answer = false;
			break;

		default:;
	}

	/* get comm buffer and show error if it exists */
	if ( (need_answer) && (disp) )
	{
		if (!cancel_from_dialog)
			read_comm_buffer_and_show_if_error(result, disp);
	}
}

void TTLSDevice::setPortProperties(int baud, int parity, int stopbit,
	int bytesize, int rint, int rmulti, int rconst, int wmulti, int wconst,
	int wrep, int rrep)
{
	/* if the tlsdevice class was created with the default constructor than
	   is'nt communication class */
	if (!comm) return;

	comm->setBaudRate(baud);
	comm->setParity(parity);
	comm->setStopBit(stopbit);
	comm->setDataBits(bytesize);
	comm->setReadIntervalTimeout(rint);
	comm->setReadTotalTimeoutMultiplier(rmulti);
	comm->setReadTotalTimeoutConstant(rconst);
	comm->setWriteTotalTimeoutMultiplier(wmulti);
	comm->setWriteTotalTimeoutConstant(wconst);
	comm->setsettableWriteRepetition(wrep);
	comm->setsettableReadRepetition(rrep);

	comm->UpdateSerialSettings();
}

void TTLSDevice::Backup(void)
{
	/* show backup configuration dialog */
	/*
		from here comes for example the configuration file path and name...
	*/
	AnsiString filename = "";

	bkpWin = new TwBackup(Application);
	bkpWin->language = language;
	bkpWin->languagepath = languagepath;
	/* set dialog to backup */
	bkpWin->setType(0);

	if (bkpWin->ShowModal()==ID_OK)
	{
		filename = bkpWin->filename_e->Text;

		if ( (filename=="") || (filename.Length() <= 7) )
		{
			ini->setFileName(languagepath);
			Application->MessageBox(ini->LoadErrorString(0).c_str(), "TLStool",16);
		}
	}

	if (bkpWin)
	{
		delete bkpWin;
		bkpWin = NULL;
		if ( (filename=="") || (filename.Length() <= 7) )	return;
	}

	/* temporarly class pointer for standalonecommand class from get the list */
	TStandaloneCommand *temp_sc;
	/* how many class are in the list */
	int item_count = standaloneList->Count;
	/* error and warning count from backup() method of the standalonecommand class */
	int errorcount = 0, warningcount = 0;
	/* error and warning count value before new error count is asked */
	int temp_errorcount = 0, temp_warningcount = 0;
	/* it takes the current position in the backup file */
	int cur_pos = 0;

	/* show process window */
	bkpProcWin = new TwBackupProcess(Application);
	bkpProcWin->language = language;
	bkpProcWin->languagepath = languagepath;
	bkpProcWin->process_pb->Position = 0;
	bkpProcWin->process_pb->Max = item_count;
	bkpProcWin->Show();

	for (int i=0; (i < item_count) && (!bkpProcWin->getCancel()); i++)
	{
		/* get the standalone class from list */
		temp_sc = reinterpret_cast<TStandaloneCommand*>(standaloneList->Items[i]);

    	AnsiString proc = temp_sc->getDescription();
		bkpProcWin->curproc_l->Caption = proc;
		Application->ProcessMessages();

		/* set configuration file name */
		temp_sc->setFileName(filename);
		/* set position in backup file */
		temp_sc->setPositionInBackupFile(cur_pos);
		/* send please backup message to standalonecommand */
		temp_sc->Backup();
		/* get position in backup file */
		cur_pos = temp_sc->getPositionInBackupFile();

		/* get error and warning count */
		errorcount += temp_sc->getErrorCount();
		warningcount += temp_sc->getWarningCount();

		/* show current state of the process */
		bkpProcWin->process_pb->Position++;

		if (errorcount > temp_errorcount)
		{
			bkpProcWin->errors_l->Items->Add(temp_sc->getErrorString());
    	}
		if (warningcount > temp_warningcount)
		{
			bkpProcWin->errors_l->Items->Add(temp_sc->getWarningString());
		}

		Application->ProcessMessages();

		temp_errorcount = errorcount;
		temp_warningcount = warningcount;
	}

	bkpProcWin->setButtonCaption("OK");
	bkpProcWin->process_pb->Position = 0;
	bkpProcWin->curproc_l->Caption = "";
	bkpProcWin->Hide();

	bkpProcWin->ShowModal();

	if (bkpProcWin)
	{
		delete bkpProcWin;
		bkpProcWin = NULL;
	}
}

void TTLSDevice::Restore(void)
{
	/* show restore configuration dialog */
	/*
		from here comes for example the configuration file path and name...
	*/
	AnsiString filename = "";

	bkpWin = new TwBackup(Application);
	bkpWin->language = language;
	bkpWin->languagepath = languagepath;
	/* set dialog to backup */
	bkpWin->setType(1);

	if (bkpWin->ShowModal()==ID_OK)
	{
		filename = bkpWin->filename_e->Text;

		if ( (filename=="") || (filename.Length() <= 7) )
		{
			ini->setFileName(languagepath);
			Application->MessageBox(ini->LoadErrorString(0).c_str(), "TLStool",16);
		}
	}

	if (bkpWin)
	{
		delete bkpWin;
		bkpWin = NULL;
		if ( (filename=="") || (filename.Length() <= 7) )	return;
	}

	/* temporarly class pointer for standalonecommand class from get the list */
	TStandaloneCommand *temp_sc;
	/* how many class are in the list */
	int item_count = standaloneList->Count;
	/* error and warning count from backup() method of the standalonecommand class */
	int errorcount = 0, warningcount = 0;
	/* error and warning count value before new error count is asked */
	int temp_errorcount = 0, temp_warningcount;
	/* it takes the current position in the backup file */
	int cur_pos = 0;

	/* show process window */
	bkpProcWin = new TwBackupProcess(Application);
	bkpProcWin->language = language;
	bkpProcWin->languagepath = languagepath;
	bkpProcWin->process_pb->Position = 0;
	bkpProcWin->process_pb->Max = item_count;
	bkpProcWin->Show();

	for (int i=0; (i < item_count) && (!bkpProcWin->getCancel()); i++)
	{
		/* get the standalone class from list */
		temp_sc = reinterpret_cast<TStandaloneCommand*>(standaloneList->Items[i]);

    	AnsiString proc = temp_sc->getDescription();
		bkpProcWin->curproc_l->Caption = proc;
		Application->ProcessMessages();

		/* set configuration file name */
		temp_sc->setFileName(filename);
		/* set position in backup file */
		temp_sc->setPositionInBackupFile(cur_pos);
		/* send please backup message to standalonecommand */
		temp_sc->Restore();
		/* get position in backup file */
		cur_pos = temp_sc->getPositionInBackupFile();

		/* get error and warning count */
		errorcount += temp_sc->getErrorCount();
		warningcount += temp_sc->getWarningCount();

		/* show current state of the process */
		bkpProcWin->process_pb->Position++;

		if (errorcount > temp_errorcount)
		{
			bkpProcWin->errors_l->Items->Add(temp_sc->getErrorString());
    	}
		if (warningcount > temp_warningcount)
		{
			bkpProcWin->errors_l->Items->Add(temp_sc->getWarningString());
		}

		Application->ProcessMessages();

    	temp_errorcount = errorcount;
		temp_warningcount = warningcount;
	}

	bkpProcWin->setButtonCaption("OK");
	bkpProcWin->process_pb->Position = 0;
	bkpProcWin->curproc_l->Caption = "";
	bkpProcWin->Hide();

	bkpProcWin->ShowModal();

	if (bkpProcWin)
	{
		delete bkpProcWin;
		bkpProcWin = NULL;
	}
}

bool TTLSDevice::getIsPortOpen(void)
{
	return isPortOpened;
}

bool TTLSDevice::OpenSerialPort(char *portname)
{
	if (comm)
	{
		int result = comm->OpenPort(portname);

		/* show if it was error on open port */
		if (result==e_noserialdevice)
		{
			/* could not find the specified port */
			AnsiString msg = "Could not open ";
			msg += portname;
			Application->MessageBox(msg.c_str(), "TLStool", 16);
			isPortOpened = false;
		}
		else	isPortOpened = true;
		if (result==e_initsettings)
		{
			/* could not get dcb and timeouts structure from the port */
			AnsiString msg = "Could not set properties on ";
			msg += portname;
			Application->MessageBox(msg.c_str(), "TLStool", 16);
		}
		if (result==e_updatesettings)
		{
			/* could not set port properties */
			AnsiString msg = "Could not set properties on ";
			msg += portname;
			Application->MessageBox(msg.c_str(), "TLStool", 16);
		}
		if (result==e_settimeout)
		{
			/* could not set port timeouts */
			AnsiString msg = "Could not set time outs on ";
			msg += portname;
			Application->MessageBox(msg.c_str(), "TLStool", 16);
		}
	}

	return isPortOpened;
}

bool TTLSDevice::CloseSerialPort(void)
{
	/* close the specified port and free resource */
	if (comm->ClosePort())	isPortOpened = false;
	else isPortOpened = true;

	return isPortOpened;
}
