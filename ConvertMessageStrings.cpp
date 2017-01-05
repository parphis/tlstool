/*
	ConvertMessageStrings.cpp

	Purpose is to convert the TLS device answer string to the required value;
	i.e.: get_current_unit() function returns the unit index from the i50500
	command srting. See the TLS-3XX Veeder-Root serial interface manual. 
*/

#include "ConvertMessageStrings.h"

const AnsiString unknown_command = "9999FF1B";

static bool valid_command(AnsiString str)
{
	if (CompareStr(str,unknown_command)==0) return false;
	else return true;
}

static float asciihex_to_float(AnsiString str)
{
	int b0[4];
	int b1[4];
	int b2[4];
	int b3[4];
	int b4[4];
	int b5[4];
	int b6[4];
	int b7[4];
	int *sumbit[8] = {b0,b1,b2,b3,b4,b5,b6,b7};
	int signbit;
	int bin_exponent[8];
	float exponent;
	int bin_mantissa[23];
	float mantissa;
	float dec_exponent;
	float dec_mantissa;

	for (int i=0; i < 8; i++)
		char_to_bin(str[i+1], sumbit[i], 4);

	signbit = sumbit[0][3];
	if (signbit) signbit *= -1;
	else	signbit += 1;

	bin_exponent[7] = b0[2];
	bin_exponent[6] = b0[1];
	bin_exponent[5] = b0[0];
	bin_exponent[4] = b1[3];
	bin_exponent[3] = b1[2];
	bin_exponent[2] = b1[1];
	bin_exponent[1] = b1[0];
	bin_exponent[0] = b2[3];

	bin_mantissa[22] = b2[2];
	bin_mantissa[21] = b2[1];
	bin_mantissa[20] = b2[0];

	for(int m=3, n=19; m < 8; m++)
	{
		for (int j=3; j >= 0; j--, n--)
			bin_mantissa[n] = sumbit[m][j];
	}

	exponent = bin_to_int(bin_exponent, 8);
	mantissa = bin_to_int(bin_mantissa, 23);

	dec_exponent = pow(2, (exponent-127));
	dec_mantissa = 1.0+(mantissa/pow(2,23));

	return signbit*(dec_exponent*dec_mantissa);
}

int get_current_unit(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	/* select unit id from this string: i50500061130140621&&FBF7 */
	int unit_idx;

	answer.Delete(1, 16);
	answer.Delete(2, 7);

	if (answer.Length() <= 0)
	{
    	/* if the str as input parameter empty set item index to default */
		return -1;
	}

	try
	{
		unit_idx = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
        unit_idx = -1;
	}

	return unit_idx;
}
int get_current_lang(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	/* select language id from this string: i50500061130140621&&FBF7 */
	int lang_idx;

	answer.Delete(1, 17);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		/* if the str as input parameter empty set item index to default */
		return -1;
	}

	try
	{
		lang_idx = StrToInt(answer);
    }
	catch(EConvertError &e)
	{
        lang_idx = -1;
	}

	return lang_idx;
}
int get_current_datetime_format(AnsiString answer)
{                       
	if (!valid_command(answer))	return -1;
	/* select display format id from this string: i50f00061130140706&&FBC2 */
	int disp_idx;

	answer.Delete(1, 17);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		disp_idx = StrToInt(answer);
    }
	catch(EConvertError &e)
	{
		disp_idx = -1;
	}

	return disp_idx;
}
TDateTime get_current_date(AnsiString answer)
{                      
	if (!valid_command(answer))	return 0;

	/* select display format id from this string:
	   i5010006113013520611301352&&FA68 */
	AnsiString tmp = answer;
	AnsiString date_str = "", year, month, day;
	TDateTime date;
	int date_str_len;

	tmp.Delete(1, 16);
	tmp.Delete(7, 10);

	if (tmp.Length() < 6) return 0;

	try
	{
		AnsiString y_str = "";
		int y_int;

		y_str += tmp[1];
		y_str += tmp[2];

		y_int = StrToInt(y_str);

		if (y_int > 50)	date_str = "19";
		if (y_int <= 50) date_str = "20";
	}
	catch(EConvertError &e)
	{
    	date_str = "20";
	}

	date_str += tmp;
	date_str_len = date_str.Length();

	for (int i=1; i < 5; i++)
	{
		if (date_str_len > i) year += date_str[i];
	}
	year += ".";

	for (int i=5; i < 7; i++)
	{
		if (date_str_len > i) month += date_str[i];
	}
	month += ".";

	for (int i=7; i < 9; i++)
	{
		if (date_str_len+1 > i) day += date_str[i];
	}
	day += ".";

	try
	{
		/* hungarian format */
		date = StrToDate(year+month+day);
	}
	catch(EConvertError &e)
	{
		try
		{
			/* german format */
			date = StrToDate(day+month+year);
		}
		catch(EConvertError &e)
		{
			try
			{
            	/* english format */
				date = StrToDate(month+day+year);
			}
			catch(EConvertError &e)
			{
				/* in another cases the date is the system date */
                date = Now();
			}
        }
	}

	return date;
}
TDateTime get_current_time(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	/* select display format id from this string:
	   i5010006113013520611301352&&FA68 */
	AnsiString tmp = answer;
	AnsiString time_str;
	TDateTime time;

	tmp.Delete(1, 22);
	tmp.Delete(5, 6);

	if (tmp.Length() < 4) return 0;

	time_str = tmp;
	time_str.Insert(":", 3);

	try
	{
		time = StrToTime(time_str);
	}
	catch(EConvertError &e)
	{
		time = Now();
	}

	return time;
}
AnsiString get_current_header(AnsiString answer)
{                
	if (!valid_command(answer))	return "";

	answer.Delete(1, 16);
	answer.Delete(21, 7);

	if (answer.Length() <= 0)
	{
		return "";
	}

	return answer;
}
TDateTime get_current_shifttime(AnsiString answer)
{             
	if (!valid_command(answer))	return 0;

	TDateTime shifttime;
	const AnsiString shifttime_disabled = "EE00";

	//i502010612011227EE00&&FB72 string if time is disabled
	//i5020106120112281200&&FB98 string if time is set
	answer.Delete(1, 16);
	answer.Delete(5, 7);

	if (answer.Length() <= 0)
	{
		return 0;
	}

	answer.Insert(":", 3);

	try
	{
		/* if the answer can be convert to time */
		shifttime = StrToTime(answer);
	}
	catch(EConvertError &e)
	{
		answer.Delete(3, 1);
		/* if the shift time is disabled */
		if (CompareStr(answer, shifttime_disabled)==0)
		{
			shifttime = -1.0;
		}
		/* if the answer can not be convert to time */
		else
		{
			shifttime = StrToTime("23:00");
		}
	}

	return shifttime;
}
bool get_current_shiftbirprintouts(AnsiString answer)
{                  
	if (!valid_command(answer))	return false;

	bool shiftbirprintouts;

	/* select shift bir printouts flag from string i5110006120408460&&FC24 */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		shiftbirprintouts = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		shiftbirprintouts = false;
	}

	return shiftbirprintouts;
}
bool get_current_dailybirprintouts(AnsiString answer)
{                  
	if (!valid_command(answer))	return false;

	bool dailybirprintouts;

	/* select daily bir printouts flag from string i5120006120410330&&FC2E */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		dailybirprintouts = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dailybirprintouts = false;
	}

	return dailybirprintouts;
}
bool get_current_ticketeddelivery(AnsiString answer)
{                 
	if (!valid_command(answer))	return false;

	bool ticketeddelivery;

	/* select ticketed delivery flag from string i51C0006120411120&&FC1F */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		ticketeddelivery = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		ticketeddelivery = false;
	}

	return ticketeddelivery;
}
bool get_current_tcticketeddelivery(AnsiString answer)
{                
	if (!valid_command(answer))	return false;

	bool tcticketeddelivery;

	/* select ticketed delivery temp. comp. flag from string
	   i51d000612041227&&FC27 --- this command is'nt good??? it has not any
	   value!!! it operates only when the user set the ticketed delivery
	   flag to enabled but i tested with this and came nothing:( */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		tcticketeddelivery = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		tcticketeddelivery = false;
	}

	return tcticketeddelivery;
}
int get_current_tdclosedayofweek(AnsiString answer)
{                   
	if (!valid_command(answer))	return -1;

	int tdclosedayofweek;

	/* select ticketed delivery temp. comp. flag from string
	   i51E000612041459&&FC3F --- this command is'nt good??? it has not any
	   value!!! it operates only when the user set the ticketed delivery
	   flag to enabled but i tested with this and came nothing:( */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		tdclosedayofweek = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		tdclosedayofweek = -1;
	}

	return tdclosedayofweek;
}
bool get_current_dailyvariance(AnsiString answer)
{                  
	if (!valid_command(answer))	return false;

	bool dailydelivery;

	/* select ticketed delivery temp. comp. flag from string
	   i534000612041702 'PWD - this is not here' &&FC57 --- this command is'nt
	   good??? it has not any value!!! it operates only when the user set the
	   ticketed delivery flag to enabled but i tested with this and came
	   nothing:( */
	answer.Delete(1, 18);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		dailydelivery = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dailydelivery = false;
	}

	return dailydelivery;
}
bool get_current_weeklyvariance(AnsiString answer)
{                  
	if (!valid_command(answer))	return false;

	bool weeklydelivery;

	/* select ticketed delivery temp. comp. flag from string
	   i534000612041702 'PWD - this is not here' &&FC57 --- this command is'nt
	   good??? it has not any value!!! it operates only when the user set the
	   ticketed delivery flag to enabled but i tested with this and came
	   nothing:( */
	answer.Delete(1, 17);
	answer.Delete(2, 7);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		weeklydelivery = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		weeklydelivery = false;
	}

	return weeklydelivery;
}
bool get_current_periodicvariance(AnsiString answer)
{                
	if (!valid_command(answer))	return false;

	bool periodicdelivery;

	/* select ticketed delivery temp. comp. flag from string
	   i534000612041702 'PWD - this is not here' &&FC57 --- this command is'nt
	   good??? it has not any value!!! it operates only when the user set the
	   ticketed delivery flag to enabled but i tested with this and came
	   nothing:( */
	answer.Delete(1, 16);
	answer.Delete(2, 8);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		periodicdelivery = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		periodicdelivery = false;
	}

	return periodicdelivery;
}
bool get_current_testneededwarningflag(AnsiString answer)
{                        
	if (!valid_command(answer))	return false;

	bool testneededwarningflag;

	/* select tank needed warning flag from
	   i5460006120511081&&FC22 and
	   i5490006120511080&&FC20 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		testneededwarningflag = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		testneededwarningflag = false;
	}

	return testneededwarningflag;
}
int get_current_daysbeforewarn(AnsiString answer)
{                   
	if (!valid_command(answer))	return 0;

	int daysbeforewarn;

	/* select days before tank test needed warning flag from
	   i54700061205110825&&FBEB and
	   i54A000612051109355&&FBAA string */
	answer.Delete(1, 16);

	int len = answer.Length();

	if (len <= 2)
	{
		return 0;
	}

	/* if the days parameter has two digits (periodic) */
	if (len==8)	answer.Delete(3, 6);
	/* if the days parameter has three digits (annual) */
	else if (len==9)	answer.Delete(4, 6);
	else	answer.Delete(3, 6);

	if (len <= 2)
	{
		return 0;
	}

	/* if the days parameter less than 10 than delete the zero character */
	if (answer[1]=='0')	answer.Delete(1,1);

	try
	{
		/* if the answer can be convert to int */
		daysbeforewarn = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		daysbeforewarn = 0;
	}

	return daysbeforewarn;
}
int get_current_daysbeforealm(AnsiString answer)
{                    
	if (!valid_command(answer))	return 0;
	int daysbeforealm;

	/* select days before tank test needed alarm flag from
	   i54800061205111030&&FBF5 and
	   i54B000612051110365&&FBB0 string */
	answer.Delete(1, 16);

	int len = answer.Length();

	if (len <= 2)
	{
		return 0;
	}

	/* if the days parameter has two digits (periodic) */
	if (len==8)	answer.Delete(3, 6);
	/* if the days parameter has three digits (annual) */
	else if (len==9)	answer.Delete(4, 6);
	else	answer.Delete(3, 6);

	if (len <= 2)
	{
		return 0;
	}

	/* if the days parameter less than 10 than delete the zero character */
	if (answer[1]=='0')	answer.Delete(1,1);

	try
	{
		/* if the answer can be convert to int */
		daysbeforealm = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		daysbeforealm = 0;
	}

	return daysbeforealm;
}
bool get_current_passlinetest(AnsiString answer)
{                            
	if (!valid_command(answer))	return false;

	bool passlinetest;

	/* select line re-enable method from i5530006120512090&&FC23 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		passlinetest = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		passlinetest = true;
	}

	return passlinetest;
}
bool get_current_remoteprinterpageeject(AnsiString answer)
{                         
	if (!valid_command(answer))	return false;

	bool remoteprinterpageeject;

	/* select remote printer page eject flag from
	   i50c0006120513450&&FBF7 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		remoteprinterpageeject = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		remoteprinterpageeject = true;
	}

	return remoteprinterpageeject;
}
bool get_current_printtc(AnsiString answer)
{                     
	if (!valid_command(answer))	return false;

	bool printtc;

	/* select print temperature compensation flag from
	   i50d0006120514231&&FBF8 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		printtc = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		printtc = true;
	}

	return printtc;
}
float get_current_tempcomp(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float tempcomp;

	/* select temperature compensation value from
	   i50e000612060746 42733333 &&FA84 or
	   i50e000612060805 41800000 &&FA97 stirng */
	answer.Delete(1, 16);
	answer.Delete(9, 6);

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		tempcomp = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		tempcomp = 0.00;
	}

	return tempcomp;
}
bool get_current_tankerloadreport(AnsiString answer)
{                         
	if (!valid_command(answer))	return false;

	bool tankerloadreport;

	/* select tanker load report flag from
	   i5130006120712141&&FC28 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		tankerloadreport = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		tankerloadreport = true;
	}

	return tankerloadreport;
}
bool get_current_stickheightoffsetflag(AnsiString answer)
{                      
	if (!valid_command(answer))	return false;

	bool stickheightoffsetflag;

	/* select stick height offset flag from
	   i60B0006120808070&&FC12 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		stickheightoffsetflag = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		stickheightoffsetflag = true;
	}

	return stickheightoffsetflag;
}
bool get_current_hprotocolformat(AnsiString answer)
{                      
	if (!valid_command(answer))	return false;

	bool hprotocolformat;

	/* select h-protocol data format flag from
	   i5140006120808270&&FC1E stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		hprotocolformat = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		hprotocolformat = true;
	}

	return hprotocolformat;
}
int get_current_prectest(AnsiString answer)
{                     
	if (!valid_command(answer))	return 12;

	int prectest;

	/* select precision test duration value from
	   i519000612080856012&&FBB4 stirng */
	answer.Delete(1, 16);
	answer.Delete(4, 6);

	if (answer.Length() <= 0)
	{
		return 12;
	}

	try
	{
		/* if the answer can be convert to int */
		prectest = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		prectest = 12;
	}

	return prectest;
}
bool get_current_preclinetestauto02(AnsiString answer)
{                      
	if (!valid_command(answer))	return false;

	bool preclinetestauto02;

	/* select precision line test auto confirm flag from
	   i554000612081024 'NULL is not in the answer yet' &&FC54 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		preclinetestauto02 = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		preclinetestauto02 = false;
	}

	return preclinetestauto02;
}
bool get_current_preclinetestauto01(AnsiString answer)
{                    
	if (!valid_command(answer))	return false;

	bool preclinetestauto01;

	/* select precision line test auto confirm flag from
	   i555000612081027 'NULL is not in the answer yet' &&FC50 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		preclinetestauto01 = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		preclinetestauto01 = false;
	}

	return preclinetestauto01;
}
bool get_current_daylightsavings(AnsiString answer)
{                         
	if (!valid_command(answer))	return false;

	bool daylightsavings;

	/* select daylight savings flag from
	   i51a0006120812581&&FBF1 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		daylightsavings = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		daylightsavings = true;
	}

	return daylightsavings;
}
int get_current_dlmonth(AnsiString answer)
{                        
	if (!valid_command(answer))	return 4;

	int dlstartmonth;

	/* select daylight savings start month value from
	   i51b010612081455 04 1 7 0200 &&FA93 stirng */
	answer.Delete(1, 16);
	answer.Delete(3, 12);

	if (answer.Length() <= 0)
	{
		return 4;
	}

	try
	{
		/* if the answer can be convert to int */
		dlstartmonth = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dlstartmonth = 4;
	}

	return dlstartmonth;
}
int get_current_dlweekofmonth(AnsiString answer)
{                         
	if (!valid_command(answer))	return 1;

	int dlstartweekofmonth;

	/* select daylight savings start month value from
	   i51b010612081455 04 1 7 0200 &&FA93 stirng */
	answer.Delete(1, 18);
	answer.Delete(2, 11);

	if (answer.Length() <= 0)
	{
		return 1;
	}

	try
	{
		/* if the answer can be convert to int */
		dlstartweekofmonth = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dlstartweekofmonth = 1;
	}

	return dlstartweekofmonth;
}
int get_current_dldayofweek(AnsiString answer)
{
	if (!valid_command(answer))	return 7;

	int dlstartdayofweek;

	/* select daylight savings start month value from
	   i51b010612081455 04 1 7 0200 &&FA93 stirng */
	answer.Delete(1, 19);
	answer.Delete(2, 10);

	if (answer.Length() <= 0)
	{
		return 7;
	}

	try
	{
		/* if the answer can be convert to int */
		dlstartdayofweek = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dlstartdayofweek = 7;
	}

	return dlstartdayofweek;
}
TDateTime get_current_dlhour(AnsiString answer)
{                            
	if (!valid_command(answer))	return 0.166666666667;

	TDateTime dlstarthour;

	/* select daylight savings start month value from
	   i51b010612081455 04 1 7 0200 &&FA93 stirng */
	answer.Delete(1, 20);
	answer.Delete(5, 6);

	if (answer.Length() <= 0)
	{
		return 0.166666666667;
	}

	answer.Insert(":",3);

	try
	{
		/* if the answer can be convert to int */
		dlstarthour = StrToTime(answer);
	}
	catch(EConvertError &e)
	{
		dlstarthour = 0.166666666667;
	}

	return dlstarthour;
}
bool get_current_redirectlocalpoflag(AnsiString answer)
{                           
	if (!valid_command(answer))	return false;

	bool redirectlocalpoflag;

	/* select local printout flag from
	   i5160006121108210&&FC28 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		redirectlocalpoflag = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		redirectlocalpoflag = true;
	}

	return redirectlocalpoflag;
}
bool get_current_qpldmonthlypoflag(AnsiString answer)
{                          
	if (!valid_command(answer))	return false;

	bool qpldmonthlypoflag;

	/* select qpld monthly printout flag from
	   i515000612110841&&FC57 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		qpldmonthlypoflag = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		qpldmonthlypoflag = false;
	}

	return qpldmonthlypoflag;
}
bool get_current_europrotocolprefix(AnsiString answer)
{                         
	if (!valid_command(answer))	return false;

	bool europrotocolprefix;

	/* select euro protocol prefix flag from
	   i51f0006121208141&&FBF4 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		europrotocolprefix = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		europrotocolprefix = false;
	}

	return europrotocolprefix;
}
AnsiString get_current_systemcode(AnsiString answer)
{                     
	if (!valid_command(answer))	return "000000";

	AnsiString systemcode;

	/* select system security code string from
	   i504000612121001000000&&FB43 stirng */
	answer.Delete(1, 16);
	answer.Delete(7, 6);
 
	if (answer.Length() <= 0)
	{
		return "000000";
	}

	systemcode = answer;

	return systemcode;
}
int get_current_baud(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int baud;

	/* select baud rate value from
	   i881010612141456 02400 1 1 7 0 01 &&FA2A	stirng */
	answer.Delete(1, 16);
	answer.Delete(6, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		baud = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		baud = -1;
	}

	return baud;
}
int get_current_parity(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int parity;

	/* select parity value from
	   i881010612141456 02400 1 1 7 0 01 &&FA2A	stirng */
	answer.Delete(1, 21);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		parity = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		parity = -1;
	}

	return parity;
}
int get_current_stopbit(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int stopbit;

	/* select stop bit value from
	   i881010612141456 02400 1 1 7 0 01 &&FA2A	stirng */
	answer.Delete(1, 22);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		stopbit = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		stopbit = -1;
	}

	return stopbit;
}
int get_current_bytesize(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int bytesize;

	/* select byte size value from
	   i881010612141456 02400 1 1 7 0 01 &&FA2A	stirng */
	answer.Delete(1, 23);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		bytesize = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		bytesize = -1;
	}

	return bytesize;
}
int get_current_dialtype(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int dialtype;

	/* select dial type value from
	   i881010612141456 02400 1 1 7 0 01 &&FA2A	stirng */
	answer.Delete(1, 24);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		dialtype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dialtype = -1;
	}

	return dialtype;
}
int get_current_answeron(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int answeron;

	/* select answer on value from
	   i881010612141456 02400 1 1 7 0 01 &&FA2A	stirng */
	answer.Delete(1, 25);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		answeron = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		answeron = -1;
	}

	return answeron;
}
int get_current_modemtype(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int modemtype;

	/* select modem type value from
	   i88501061214151400&&FBEB	stirng */
	answer.Delete(1, 16);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		modemtype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		modemtype = -1;
	}

	return modemtype;
}
int get_current_dialtoneinterval(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int dialtoneinterval;

	/* select dial tone interval value from
	   i8870106121415160032&&FB82	stirng */
	answer.Delete(1, 16);
	answer.Delete(5, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		dialtoneinterval = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dialtoneinterval = -1;
	}

	return dialtoneinterval;
}
int get_current_dtrnormalstate(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int dtrnormalstate;

	/* select dtr normal state value from
	   i889010612141517&&FC44	stirng */
	answer.Delete(1, 16);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		dtrnormalstate = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		dtrnormalstate = -1;
	}

	return dtrnormalstate;
}
AnsiString get_current_syscode(AnsiString answer)
{
	if (!valid_command(answer))	return "0";

	/* select system code value from
	   i536010612141519 1 000000 &&FAFC	stirng */
	answer.Delete(1, 16);
	answer.Delete(8, answer.Length());

	if (answer.Length() <= 0)	return "0";
	if (answer[1]=='&')			return "0";

	return answer;
}
AnsiString get_current_setupstring(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select modem setup string value from
	   i886010612141523                    &&F9CA	stirng */
	answer.Delete(1, 16);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";
	if (answer[1]=='&')			return "";

	return answer;
}
bool get_current_receiverconfig(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool receiverconfig;

	/* select receiver configuration flag from
	   i521010612201426 01 0 &&FBC8 stirng */
	answer.Delete(1, 16);
	answer.Delete(4, 6);

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		receiverconfig = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		receiverconfig = false;
	}

	return receiverconfig;
}
AnsiString get_current_receiverlocation(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select receiver location label from
	   i52201061220143001                    &&F97C	stirng */
	answer.Delete(1, 18);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";
	if (answer[1]=='&')			return "";

	return answer;
}
AnsiString get_current_receivertelnumber(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select receiver tlephone number from
	   i52301061220151401                    &&F978	stirng */
	answer.Delete(1, 18);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";
	if (answer[1]=='&')			return "";

	return answer;
}
int get_current_receiverportnumber(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int receiverportnumber;

	/* select receiver port number from
	   i5250106122114200101&&FB98 stirng */
	answer.Delete(1, 18);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		receiverportnumber = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		receiverportnumber = -1;
	}

	return receiverportnumber;
}
int get_current_receivertype(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int receivertype;

	/* select receiver type from
	   i5240106122114220102&&FB96 stirng */
	answer.Delete(1, 18);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		receivertype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		receivertype = -1;
	}

	return receivertype;
}
int get_current_receiverretrynumber(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int receiverretrynumber;

	/* select receiver retry number from
	   i5260106122114230103&&FB92 stirng */
	answer.Delete(1, 18);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		receiverretrynumber = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		receiverretrynumber = -1;
	}

	return receiverretrynumber;
}
int get_current_receiverdelaytime(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int receiverdelaytime;

	/* select receiver delay time from
	   i5270106122114240103&&FB90 stirng */
	answer.Delete(1, 18);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		receiverdelaytime = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		receiverdelaytime = -1;
	}

	return receiverdelaytime;
}
bool get_current_receiverconfirmation(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool receiverconfirmation;

	/* select receiver confirmation from
	   i528010612211426010&&FBC0 stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		receiverconfirmation = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		receiverconfirmation = false;
	}

	return receiverconfirmation;;
}
void get_current_reportlist(AnsiString answer, bool* replst)
{
	if (!valid_command(answer))	return;

	AnsiString tmp_str = "";
	int nr;

	/* select report list configuration from
	   i52a0106122621490119 0101020003000400050006000700080009001000110012001300
							140015001600170018001900 &&ECB0 stirng */
	answer.Delete(1, 20);

	for (int i=1; (i < 20) && (answer.Length() > 3); i++)
	{
		tmp_str = "";
		tmp_str += answer[1];
		tmp_str += answer[2];

		if (CompareStr(tmp_str, "04")==0)
		{
			answer.Delete(1, 4);
			continue;
		}

		try
		{
			nr = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			return;
		}
		tmp_str = "";
		tmp_str += answer[3];
		tmp_str += answer[4];
		try
		{
			/* if the answer can be convert to int */
			if ( (nr > -1) && (nr < 21) ) replst[nr-1] = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			replst[nr] = false;
		}
		answer.Delete(1, 4);
	}
}
bool get_current_autodialmethod(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool autodialmethod;

	/* select auto dial method from
	   i5290106122809370&&FC13 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		autodialmethod = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		autodialmethod = false;
	}

	return autodialmethod;
}
int get_current_frequencytype(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int frequencytype;

	/* select auto dial frequency type from
	   i520010612280953 01 0B 1 06 07 30 EE00 &&F930 stirng */
	answer.Delete(1, 20);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		frequencytype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		frequencytype = -1;
	}

	return frequencytype;
}
TDateTime get_current_freqdate(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	TDateTime freqdate;
	AnsiString tmp = answer;
	AnsiString date_str = "20", year, month, day;
	int date_str_len;

	/* select auto dial frequency ondate date from
	   i520010612280953 01 0B 1 06 07 30 EE00 &&F930 stirng */
	tmp.Delete(1, 21);
	tmp.Delete(7, tmp.Length());

	if (tmp.Length() < 6)
	{
		return 0;
	}

	try
	{
		AnsiString y_str = "";
		int y_int;

		y_str += tmp[1];
		y_str += tmp[2];

		y_int = StrToInt(y_str);

		if (y_int > 50)	date_str = "19";
		if (y_int <= 50) date_str = "20";
	}
	catch(EConvertError &e)
	{
    	date_str = "20";
	}

	date_str += tmp;
	date_str_len = date_str.Length();

	for (int i=1; i < 5; i++)
	{
		if (date_str_len > i) year += date_str[i];
	}
	year += ".";

	for (int i=5; i < 7; i++)
	{
		if (date_str_len > i) month += date_str[i];
	}
	month += ".";

	for (int i=7; i < 9; i++)
	{
		if (date_str_len+1 > i) day += date_str[i];
	}
	day += ".";

	try
	{
		/* hungarian format */
		freqdate = StrToDate(year+month+day);
	}
	catch(EConvertError &e)
	{
		try
		{
			/* german format */
			freqdate = StrToDate(day+month+year);
		}
		catch(EConvertError &e)
		{
			try
			{
            	/* english format */
				freqdate = StrToDate(month+day+year);
			}
			catch(EConvertError &e)
			{
				/* in another cases the date is the system date */
				freqdate = 0;
			}
        }
	}

	return freqdate;
}
TDateTime get_current_freqtime(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	/* select auto dial frequency time from
	   on date: i520010612281125 01 0B 1 061228 EE00&&F935
	   annually: i520010612281126 01 09 2 0111 EE00&&F9AC
	   monthly: i520010612281127 01 07 3 11 EE00&&FA0D
	   weekly: i520010612281127 01 06 4 1 EE00&&FA3E
	   daily: i520010612281128 01 05 5 EE00&&FA6E
	   bir end: i520010612281128 01 02 8 0&&FB28 stirng */
	int type = get_current_frequencytype(answer);
	AnsiString tmp = answer;
	AnsiString time_str;
	TDateTime time;

	switch (type)
	{
		case 1:	tmp.Delete(1, 27);
				tmp.Delete(5, tmp.Length());
				break;
		case 2:	tmp.Delete(1, 25);
				tmp.Delete(5, tmp.Length());
				break;
		case 3:	tmp.Delete(1, 23);
				tmp.Delete(5, tmp.Length());
				break;
		case 4:	tmp.Delete(1, 22);
				tmp.Delete(5, tmp.Length());
				break;
		case 5:	tmp.Delete(1, 21);
				tmp.Delete(5, tmp.Length());
				break;
		case 6:	return 0;
		case 7:	return 0;
		case 8:	return 0;
		default: return 0;
	}

	if (answer.Length() < 4) return -1;

	time_str = tmp;
	time_str.Insert(":", 3);

	try
	{
		time = StrToTime(time_str);
	}
	catch(EConvertError &e)
	{
		time = -1;
	}

	return time;
}
int get_current_freqmonth(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int freqmonth;

	/* select auto dial frequency time from
	   on date: i520010612281125 01 0B 1 061228 EE00&&F935
	   annually: i520010612281126 01 09 2 0111 EE00&&F9AC
	   monthly: i520010612281127 01 07 3 11 EE00&&FA0D
	   weekly: i520010612281127 01 06 4 1 EE00&&FA3E
	   daily: i520010612281128 01 05 5 EE00&&FA6E
	   bir end: i520010612281128 01 02 8 0&&FB28 stirng */
	answer.Delete(1, 21);
	answer.Delete(3, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		freqmonth = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		freqmonth = -1;
	}

	return freqmonth;
}
int get_current_freqweek(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int freqweek;
	int type = get_current_frequencytype(answer);

	/* select auto dial frequency time from
	   on date: i520010612281125 01 0B 1 061228 EE00&&F935
	   annually: i520010612281126 01 09 2 01 1 1 EE00&&F9AC
	   monthly: i520010612281127 01 07 3 1 1 EE00&&FA0D
	   weekly: i520010612281127 01 06 4 1 EE00&&FA3E
	   daily: i520010612281128 01 05 5 EE00&&FA6E
	   bir end: i520010612281128 01 02 8 0&&FB28 stirng */
	switch (type)
	{
		case 1:	return 0;
		case 2:	answer.Delete(1, 23);
				answer.Delete(2, answer.Length());
				break;
		case 3:	answer.Delete(1, 21);
				answer.Delete(2, answer.Length());
				break;
		case 4:	return 0;
		case 5:	return 0;
		case 6:	return 0;
		case 7:	return 0;
		case 8:	return 0;
		default: return 0;
	}

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		freqweek = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		freqweek = -1;
	}

	return freqweek;
}
int get_current_freqday(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int freqday;
	int type = get_current_frequencytype(answer);

	/* select auto dial frequency time from
	   on date: i520010612281125 01 0B 1 061228 EE00&&F935
	   annually: i520010612281126 01 09 2 01 1 1 EE00&&F9AC
	   monthly: i520010612281127 01 07 3 1 1 EE00&&FA0D
	   weekly: i520010612281127 01 06 4 1 EE00&&FA3E
	   daily: i520010612281128 01 05 5 EE00&&FA6E
	   bir end: i520010612281128 01 02 8 0&&FB28 stirng */
	switch (type)
	{
		case 1:	return 0;
		case 2:	answer.Delete(1, 24);
				answer.Delete(2, answer.Length());
				break;
		case 3:	answer.Delete(1, 22);
				answer.Delete(2, answer.Length());
				break;
		case 4:	answer.Delete(1, 21);
				answer.Delete(2, answer.Length());
				break;
		case 5:	return 0;
		case 6:	return 0;
		case 7:	return 0;
		case 8:	return 0;
		default: return 0;
	}

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		freqday = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		freqday = -1;
	}

	return freqday;
}
bool get_current_birend(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool birend;
	int type = get_current_frequencytype(answer);

	/* select auto dial frequency time from
	   on date: i520010612281125 01 0B 1 061228 EE00&&F935
	   annually: i520010612281126 01 09 2 01 1 1 EE00&&F9AC
	   monthly: i520010612281127 01 07 3 1 1 EE00&&FA0D
	   weekly: i520010612281127 01 06 4 1 EE00&&FA3E
	   daily: i520010612281128 01 05 5 EE00&&FA6E
	   bir end: i520010612281128 01 02 8 0&&FB28 stirng */
	switch (type)
	{
		case 1:	return false;
		case 2:	return false;
		case 3:	return false;
		case 4:	return false;
		case 5:	return false;
		case 6:	return false;
		case 7:	return false;
		case 8:	answer.Delete(1, 21);
				answer.Delete(2, answer.Length());
				break;;
		default: return false;
	}

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		birend = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		birend = false;
	}

	return birend;
}
bool get_current_rs232eom(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool rs232eom;

	/* select rs232 end of message from
	   i5310006122908290&&FC1A stirng */
	answer.Delete(1, 16);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		rs232eom = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		rs232eom = false;
	}

	return rs232eom;
}
void get_current_tankconfig(AnsiString answer, bool *tankconfig)
{
	if (!valid_command(answer))	return;

	AnsiString tmp_str = "";
	int nr;

	/* select tank configuration from
	   i601000612291121 010 020 030 040 050 060 070 080 &&F7B6 stirng */
	answer.Delete(1, 16);

	for (int i=1; (i < 17) && (answer.Length() > 3); i++)
	{
		tmp_str = "";
		tmp_str += answer[1];
		tmp_str += answer[2];

		try
		{
			nr = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			return;
		}
		tmp_str = "";
		tmp_str += answer[3];
		try
		{
			/* if the answer can be convert to int */
			if ( (nr > -1) && (nr < 17) ) tankconfig[nr-1] = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			tankconfig[nr] = false;
		}
		answer.Delete(1, 3);
	}
}
AnsiString get_current_productlabel(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select product label from
	   i6020107010213090195                  &&F94B	stirng */
	answer.Delete(1, 18);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";
	if (answer[1]=='&')			return "";

	return answer;
}
AnsiString get_current_productcode(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select product code from
	   i60301070102145701 1&&FBC3	stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)	return "";
	if (answer[1]=='&')			return "";

	return answer;
}
float get_current_producttermalcoeff(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float producttermalcoeff;

	/* select thermal coefficient value from
	   i609010701021516 01 3AA3D70A &&FA1E stirng */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		producttermalcoeff = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		producttermalcoeff = 0.00;
	}

	return producttermalcoeff;
}
float get_current_tankdiameter(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float tankdiameter;

	/* select tank diameter from
	   i607010701030751 01 451C4000 &&FA52 [metric unit] string or
	   i607010701030751 01 42C4D9B3 &&FA24 [u.s. unit] stirng */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		tankdiameter = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		tankdiameter = 0.00;
	}

	return tankdiameter;
}
bool get_current_meterdatapresent(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool meterdatapresent;

	/* select meter data present from
	   i615010701031032 01 0&&FBCB stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		meterdatapresent = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		meterdatapresent = false;
	}

	return meterdatapresent;
}
int get_current_endfactor(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int endfactor;

	/* select end factor from
	   i639010701031047 01 0 00000000 &&FA3F string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		endfactor = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		endfactor = -1;
	}

	return endfactor;
}
float get_current_endvalue(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float endvalue;

	/* select end value from
	   i639010701031047 01 0 00000000 &&FA3F string */
	answer.Delete(1, 19);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		endvalue = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		endvalue = 0.00;
	}

	return endvalue;
}
int get_current_calibrationupdate(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int calibrationupdate;

	/* select calibration update type from
	   i616010701031406 01 1&&FBC4 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		calibrationupdate = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		calibrationupdate = -1;
	}

	return calibrationupdate;
}
int get_current_floatsize(AnsiString answer)
{
	if (!valid_command(answer))	return -1;

	int floatsize;

	/* select float size from
	   i62f010701031450 &&FC26 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 8)
	{
		return -1;
	}

	try
	{
		/* if the answer can be convert to int */
		floatsize = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		floatsize = -1;
	}

	return floatsize;
}
float get_current_waterwarning(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float waterwarning;

	/* select water warning from
	   i627010701031546 &&FC4F string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		waterwarning = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		waterwarning = 0.00;
	}

	return waterwarning;
}
float get_current_highwaterlimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float highwaterlimit;

	/* select high water limit from
	   i624010701040832 &&FC54 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		highwaterlimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		highwaterlimit = 0.00;
	}

	return highwaterlimit;
}
int get_current_maxorlabelvolume(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int maxorlabelvolume;

	/* select max or label volmue from
	   i628010701050844 01 00000000 &&FA6B string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		maxorlabelvolume = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		maxorlabelvolume = 0;
	}

	return maxorlabelvolume;
}
int get_current_overfilllimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int overfilllimit;

	/* select overfill limit from
	   i623010701081247 01 00000000&&FA6F string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		overfilllimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		overfilllimit = 0;
	}

	return overfilllimit;
}
int get_current_highproductlimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int highproductlimit;

	/* select high product limit from
	   i622010701081247 01 40800001&&FA63 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		highproductlimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		highproductlimit = 0;
	}

	return highproductlimit;
}
int get_current_deliverylimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int deliverylimit;

	/* select delivery limit from
	   i629010701081248 01 3F800001&&FA46 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		deliverylimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		deliverylimit = 0;
	}

	return deliverylimit;
}
int get_current_lowproductlimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int lowproductlimit;

	/* select low product limit from
	   i621010701081248 01 40000001&&FA6B string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		lowproductlimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		lowproductlimit = 0;
	}

	return lowproductlimit;
}
int get_current_leakalarmlimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int leakalarmlimit;

	/* select leak alarm limit from
	   i626010701081249 01 41100000&&FA64 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		leakalarmlimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		leakalarmlimit = 0;
	}

	return leakalarmlimit;
}
int get_current_suddenlosslimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int suddenlosslimit;

	/* select leak alarm limit from
	   i625010701081249 01 43BB0000&&FA40 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		suddenlosslimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		suddenlosslimit = 0;
	}

	return suddenlosslimit;
}
float get_current_tanktilt(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float tanktilt;

	/* select tank tilt from
	   i608010701081249 01 00000000&&FA6A string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		tanktilt = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		tanktilt = 0.00;
	}

	return tanktilt;
}
float get_current_probeoffset(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float probeoffset;

	/* select probe offset from
	   i60F010701081250 01 80000000&&FA5C string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		probeoffset = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		probeoffset = 0.00;
	}

	return probeoffset;
}
AnsiString get_current_manifoldedtanks(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select manifolded tank status from
	   i612000701081246 01000200030004000500060007000800 &&F630	stirng */
	int and_pos;
	answer.Delete(1, 16);
	and_pos = answer.Pos("&");
	answer.Delete(and_pos, 7);

	if (answer.Length() <= 0)	return "";
	if (answer[1]=='&')			return "";

	if (answer.Length() >= 4)
	{
		int i = 3;
		while (i < answer.Length())
		{
			answer.Insert(",",i);
			i += 3;
		}
	}

	return answer;
}
int get_current_leakminimumperiodic(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int leakminimumperiodic;

	/* select leak minimum periodic from
	   i636010701081417 01 00000000&&FA6C string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		leakminimumperiodic = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		leakminimumperiodic = 0;
	}

	return leakminimumperiodic;
}
int get_current_leakminimumannual(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int leakminimumannual;

	/* select leak minimum annual from
	   i62A010701081458 01 00000000&&FA5D string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		leakminimumannual = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		leakminimumannual = 0;
	}

	return leakminimumannual;
}
bool get_current_periodictesttype(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool periodictesttype;

	/* select periodic test type from
	   i62C010701081519 01 0&&FBAD stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		periodictesttype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		periodictesttype = false;
	}

	return periodictesttype;
}
bool get_current_annualtestfail(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool annualtestfail;

	/* select annual test fail from
	   i62D010701081550 01 0 0 0&&FB51 stirng */
	answer.Delete(1, 20);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		annualtestfail = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		annualtestfail = false;
	}

	return annualtestfail;
}
bool get_current_periodictestfail(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool periodictestfail;

	/* select periodic test fail from
	   i62D010701081550 01 0 0 0&&FB51 stirng */
	answer.Delete(1, 19);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		periodictestfail = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		periodictestfail = false;
	}

	return periodictestfail;
}
bool get_current_grosstestfail(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool grosstestfail;

	/* select gross test fail from
	   i62D010701081550 01 0 0 0&&FB51 stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		grosstestfail = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		grosstestfail = false;
	}

	return grosstestfail;
}
bool get_current_annualtestaveraging(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool annualtestaveraging;

	/* select annual test averaging from
	   i631010701090818 01 0 0&&FB8C stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		annualtestaveraging = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		annualtestaveraging = false;
	}

	return annualtestaveraging;
}
bool get_current_periodictestaveraging(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool periodictestaveraging;

	/* select periodic test averaging from
	   i631010701090818 01 0 0&&FB8C stirng */
	answer.Delete(1, 19);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		periodictestaveraging = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		periodictestaveraging = false;
	}

	return periodictestaveraging;
}
bool get_current_leaktestnotify(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool leaktestnotify;

	/* select leak test notify from
	   i630010701090922 01 0&&FBC1 stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		leaktestnotify = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		leaktestnotify = false;
	}

	return leaktestnotify;
}
bool get_current_siphonbreak(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool siphonbreak;

	/* select leak test siphon break from
	   i632010701090933 01 0&&FBBD stirng */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		siphonbreak = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		siphonbreak = false;
	}

	return siphonbreak;
}
float get_current_stickoffset(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float stickoffset;

	/* select stick offset from
	   i60C010701090943 01 00000000&&FA5E string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		stickoffset = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		stickoffset = 0.00;
	}

	return stickoffset;
}
int get_current_hrmreconcwarnlimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int hrmreconcwarnlimit;

	/* select hrm reconciliation warning limit from
	   i634010701091008 01 40400000&&FA69 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		hrmreconcwarnlimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		hrmreconcwarnlimit = 0;
	}

	return hrmreconcwarnlimit;
}
int get_current_hrmreconcalmlimit(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int hrmreconcalmlimit;

	/* select hrm reconciliation alarm limit from
	   i635010701091032 01 40800001&&FA66 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		hrmreconcalmlimit = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		hrmreconcalmlimit = 0;
	}

	return hrmreconcalmlimit;
}
int get_current_deliveryreportdt(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int deliveryreportdt;

	/* select delivery report delay time from
	   i610010701091046 01 03&&FB92 string */
	answer.Delete(1, 18);
	answer.Delete(3, answer.Length());

	if (answer.Length() < 2)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		deliveryreportdt = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		deliveryreportdt = 0;
	}

	return deliveryreportdt;
}
float get_current_pumpthreshold(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float pumpthreshold;

	/* select pump threshold from
	   i63A010701091055 01 4124CCCD&&FA0A string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		pumpthreshold = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		pumpthreshold = 0.00;
	}

	return pumpthreshold;
}
void get_current_tankprofile(AnsiString answer, AnsiString *tankprofile)
{
	if (!valid_command(answer))	return;

	/* asciihex_to_float() returns a float but here the tmpVolume is an integer
	   because the tank volumes are always integers */
	int tmpVolume;
	AnsiString tmpAsciihex;

	/* get tank volumes from
	   i606010701110950 01 46985800 00000000 00000000 00000000 00000000 00000000
						   00000000 00000000 00000000 00000000 00000000 00000000
						   00000000 00000000 00000000 00000000 00000000 00000000
						   00000000 00000000 &&DDCC
	   string */

	answer.Delete(1, 18);

	if (answer.Length() < 8)
	{
		return;
	}

	for (int i=19; i >= 0; i--)
	{
		tmpAsciihex = "";

		for (int j=1; j <= 8; j++)
		{
			if (answer[j]=='&')	return;
			tmpAsciihex += answer[j];
		}

    	answer.Delete(1, 8);

		try
		{
			/* if the answer can be convert to int */
			tmpVolume = asciihex_to_float(tmpAsciihex);
		}
		catch(EConvertError &e)
		{
			tmpVolume = 0;
		}

		tankprofile[i].sprintf("%d", tmpVolume);
	}
}
AnsiString get_current_dimversion(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select dim version string from ??? stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(41, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
AnsiString get_current_mdimstring(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select mechanical dim string from ??? stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(41, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
AnsiString get_current_edimstring(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select electronic dim string from ??? stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(41, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
TDateTime get_current_autodailyclosing(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	/* select auto daily closing time from
	   i793000701220925 0200&&FB89 string */
	AnsiString tmp = answer;
	AnsiString time_str;
	TDateTime time;

	tmp.Delete(1, 16);
	tmp.Delete(5, tmp.Length());

	if (tmp.Length() < 4) return 0;

	time_str = tmp;
	time_str.Insert(":", 3);

	try
	{
		time = StrToTime(time_str);
	}
	catch(EConvertError &e)
	{
		time = Now();
	}

	return time;
}
int get_current_periodicreconcmode(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int periodicreconcmode;

	/* select periodic reconciliation mode from
	   i795000701221214 02&&FBEF string */
	answer.Delete(1, 16);
	answer.Delete(3, answer.Length());

	if (answer.Length() < 2)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		periodicreconcmode = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		periodicreconcmode = 0;
	}

	return periodicreconcmode;
}
int get_current_periodicreconclen(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int periodicreconclen;

	/* select periodic reconciliation length from
	   i796000701221214 15&&FBEA string */
	answer.Delete(1, 16);
	answer.Delete(3, answer.Length());

	if (answer.Length() < 2)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		periodicreconclen = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		periodicreconclen = 0;
	}

	return periodicreconclen;
}
int get_current_perreconcalmonoff(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int perreconcalmonoff;

	/* select periodic reconciliation alarm flag from
	   i797000701240748 01&&FBE1 string */
	answer.Delete(1, 16);
	answer.Delete(3, answer.Length());

	if (answer.Length() < 2)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		perreconcalmonoff = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		perreconcalmonoff = 0;
	}

	return perreconcalmonoff;
}
float get_current_perreconcalmthreshold(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float perreconcalmthreshold;

	/* select periodic recinciliation alarm threshold from
	   i798000701240826 3F800000&&FAA3 string */
	answer.Delete(1, 16);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		perreconcalmthreshold = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		perreconcalmthreshold = 0.00;
	}

	return perreconcalmthreshold;
}
int get_current_perreconcalmoffset(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int perreconcalmoffset;

	/* select periodic reconciliation alarm offset from
	   i799000701240831 43F60667&&FA91 string */
	answer.Delete(1, 16);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		perreconcalmoffset = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		perreconcalmoffset = 0;
	}

	return perreconcalmoffset;
}
int get_current_remotereportformat(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int remotereportformat;

	/* select remote report format from
	   i79A000701240926 01&&FBD9 string */
	answer.Delete(1, 16);
	answer.Delete(3, answer.Length());

	if (answer.Length() < 2)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		remotereportformat = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		remotereportformat = 0;
	}

	return remotereportformat;
}
bool get_current_tempcompensation(AnsiString answer)
{
	if (!valid_command(answer))	return false;

	bool tempcompensation;

	/* select temp compensation from
	   i79F000701240945 0&&FC04 stirng */
	answer.Delete(1, 16);
	answer.Delete(2, answer.Length());

	if (answer.Length() <= 0)
	{
		return false;
	}

	try
	{
		/* if the answer can be convert to int */
		tempcompensation = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		tempcompensation = false;
	}

	return tempcompensation;
}
float get_current_metercaliboffset(AnsiString answer)
{
	if (!valid_command(answer))	return 0.00;

	float metercaliboffset;

	/* select meter calibration offset from
	   i7B2000701241032 00000000&&FACB string */
	answer.Delete(1, 16);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 0.00;
	}

	try
	{
		/* if the answer can be convert to int */
		metercaliboffset = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		metercaliboffset = 0.00;
	}

	return metercaliboffset;
}
void get_current_liquidsensorconfig(AnsiString answer, bool *sensorconfig)
{
	if (!valid_command(answer))	return;

	AnsiString tmp_str = "";
	int nr;

	/* select liquid sensor configuration from
	   i701000701250848 ??? &&FC4F stirng */
	answer.Delete(1, 16);

	for (int i=1; (i < 33) && (answer.Length() > 3); i++)
	{
		tmp_str = "";
		tmp_str += answer[1];
		tmp_str += answer[2];

		try
		{
			nr = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			return;
		}
		tmp_str = "";
		tmp_str += answer[3];
		try
		{
			/* if the answer can be convert to int */
			if ( (nr > -1) && (nr < 33) ) sensorconfig[nr-1] = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			sensorconfig[nr] = false;
		}
		answer.Delete(1, 3);
	}
}
AnsiString get_current_liqsenslocation(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select liquid sensor location from i702010701251033 &&FC5A stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
int get_current_liqsenstype(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int liqsenstype;

	/* select liquid sensor type from
	   i703010701251035 &&FC57 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		liqsenstype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		liqsenstype = 0;
	}

	return liqsenstype;
}
int get_current_liqsenscategory(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int liqsenscategory;

	/* select liquid sensor category from
	   i704010701251036 &&FC55 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		liqsenscategory = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		liqsenscategory = 0;
	}

	return liqsenscategory;
}
void get_current_vaporsensorconfig(AnsiString answer, bool *sensorconfig)
{
	if (!valid_command(answer))	return;

	AnsiString tmp_str = "";
	int nr;

	/* select vapor sensor configuration from
	   i706000701251202 ???&&FC59 stirng */
	answer.Delete(1, 16);

	for (int i=1; (i < 21) && (answer.Length() > 3); i++)
	{
		tmp_str = "";
		tmp_str += answer[1];
		tmp_str += answer[2];

		try
		{
			nr = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			return;
		}
		tmp_str = "";
		tmp_str += answer[3];
		try
		{
			/* if the answer can be convert to int */
			if ( (nr > -1) && (nr < 21) ) sensorconfig[nr-1] = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			sensorconfig[nr] = false;
		}
		answer.Delete(1, 3);
	}
}
AnsiString get_current_vaporsenslocation(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select vapor sensor location from i707010701251359 &&FC4A stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
int get_current_vaporsensthreshold(AnsiString answer)
{
	if (!valid_command(answer))	return 1000;

	int vaporsensthreshold;

	/* select vapor sensor threshold from
	   i708010701251401 &&FC55 string */
	answer.Delete(1, 18);
	answer.Delete(9, answer.Length());

	if (answer.Length() < 8)
	{
		return 1000;
	}

	try
	{
		/* if the answer can be convert to int */
		vaporsensthreshold = asciihex_to_float(answer);
	}
	catch(EConvertError &e)
	{
		vaporsensthreshold = 1000;
	}

	return vaporsensthreshold;
}
int get_current_vaporsenscategory(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int vaporsenscategory;

	/* select vapor sensor category from
	   i709010701251402 &&FC53 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		vaporsenscategory = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		vaporsenscategory = 0;
	}

	return vaporsenscategory;
}
void get_current_grdwsensorconfig(AnsiString answer, bool *sensorconfig)
{
	if (!valid_command(answer))	return;

	AnsiString tmp_str = "";
	int nr;

	/* select groundwater sensor configuration from
	   i711000701251500 &&FC5C stirng */
	answer.Delete(1, 16);

	for (int i=1; (i < 21) && (answer.Length() > 3); i++)
	{
		tmp_str = "";
		tmp_str += answer[1];
		tmp_str += answer[2];

		try
		{
			nr = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			return;
		}
		tmp_str = "";
		tmp_str += answer[3];
		try
		{
			/* if the answer can be convert to int */
			if ( (nr > -1) && (nr < 21) ) sensorconfig[nr-1] = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			sensorconfig[nr] = false;
		}
		answer.Delete(1, 3);
	}
}
AnsiString get_current_grdwsenslocation(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select grundwater sensor location from i712010701251532 &&FC55 stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
int get_current_grdwsenscategory(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int grdwsenscategory;

	/* select groundwater sensor category from
	   i713010701251534 &&FC52 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		grdwsenscategory = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		grdwsenscategory = 0;
	}

	return grdwsenscategory;
}
void get_current_extinputconfig(AnsiString answer, bool *sensorconfig)
{
	if (!valid_command(answer))	return;

	AnsiString tmp_str = "";
	int nr;

	/* select external input configuration from
	   i801000701260811 &&FC57 stirng */
	answer.Delete(1, 16);

	for (int i=1; (i < 9) && (answer.Length() > 3); i++)
	{
		tmp_str = "";
		tmp_str += answer[1];
		tmp_str += answer[2];

		try
		{
			nr = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			return;
		}
		tmp_str = "";
		tmp_str += answer[3];
		try
		{
			/* if the answer can be convert to int */
			if ( (nr > -1) && (nr < 9) ) sensorconfig[nr-1] = StrToInt(tmp_str);
		}
		catch(EConvertError &e)
		{
			sensorconfig[nr] = false;
		}
		answer.Delete(1, 3);
	}
}
AnsiString get_current_extinputname(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select external input location from i802010701260953 &&FC4E stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
int get_current_extinputtype(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int extinputtype;

	/* select external input type from
	   i803010701260955 &&FC4B string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		extinputtype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		extinputtype = 0;
	}

	return extinputtype;
}
int get_current_extinputswitchtype(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int extinputswitchtype;

	/* select external input switch orientation from
	   i803010701260955 &&FC4B string */
	answer.Delete(1, 19);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		extinputswitchtype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		extinputswitchtype = 0;
	}

	return extinputswitchtype;
}
int get_current_extinputtanknr(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int extinputtanknr;

	/* select external input tank or pump nuber from
	   i803010701260955 &&FC4B string */
	answer.Delete(1, 22);
	answer.Delete(3, answer.Length());

	if (answer.Length() < 2)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		extinputtanknr = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		extinputtanknr = 0;
	}

	return extinputtanknr;
}
int get_current_extinputdispensemode(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int extinputdispensemode;

	/* select external input dispense mode from
	   i804010701260959 &&FC46 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		extinputdispensemode = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		extinputdispensemode = 0;
	}

	return extinputdispensemode;
}
AnsiString get_current_relaydesignation(AnsiString answer)
{
	if (!valid_command(answer))	return "";

	/* select relay designation from i807010701261624 &&FC4D stirng */
	answer.Delete(1, 16);
	if (answer[1]=='&')			return "";
	else	answer.Delete(1, 2);
	answer.Delete(21, answer.Length());

	if (answer.Length() <= 0)	return "";

	return answer;
}
int get_current_relaytype(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int relaytype;

	/* select relay type from
	   i80A010701261625 &&FC42 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		relaytype = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		relaytype = 0;
	}

	return relaytype;
}
int get_current_relayorientation(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int relayorientation;

	/* select relay orientation from
	   i809010701261626 &&FC49 string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		relayorientation = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		relayorientation = 0;
	}

	return relayorientation;
}
int get_current_relaytanknr(AnsiString answer)
{
	if (!valid_command(answer))	return 0;

	int relaytanknr;

	/* select relay tank assignment from
	   i80B010701261627 &&FC3F string */
	answer.Delete(1, 18);
	answer.Delete(2, answer.Length());

	if (answer.Length() < 1)
	{
		return 0;
	}

	try
	{
		/* if the answer can be convert to int */
		relaytanknr = StrToInt(answer);
	}
	catch(EConvertError &e)
	{
		relaytanknr = 0;
	}

	return relaytanknr;
}
