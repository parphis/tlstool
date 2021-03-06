#ifndef	CONVERTMESSAGESTRINGSH
#define	CONVERTMESSAGESTRINGSH

#include <vcl.h>
#include <math.h>
#include "convert_tools.h"

static bool valid_command(AnsiString str);
static float asciihex_to_float(AnsiString str);

int get_current_unit(AnsiString answer);
int get_current_lang(AnsiString answer);
int get_current_datetime_format(AnsiString answer);
TDateTime get_current_date(AnsiString answer);
TDateTime get_current_time(AnsiString answer);
AnsiString get_current_header(AnsiString answer);
TDateTime get_current_shifttime(AnsiString answer);
bool get_current_shiftbirprintouts(AnsiString answer);
bool get_current_dailybirprintouts(AnsiString answer);
bool get_current_ticketeddelivery(AnsiString answer);
bool get_current_tcticketeddelivery(AnsiString answer);
int get_current_tdclosedayofweek(AnsiString answer);
bool get_current_dailyvariance(AnsiString answer);
bool get_current_weeklyvariance(AnsiString answer);
bool get_current_periodicvariance(AnsiString answer);
bool get_current_testneededwarningflag(AnsiString answer);
int get_current_daysbeforewarn(AnsiString answer);
int get_current_daysbeforealm(AnsiString answer);
bool get_current_passlinetest(AnsiString answer);
bool get_current_remoteprinterpageeject(AnsiString answer);
bool get_current_printtc(AnsiString answer);
float get_current_tempcomp(AnsiString answer);
bool get_current_tankerloadreport(AnsiString answer);
bool get_current_stickheightoffsetflag(AnsiString answer);
bool get_current_hprotocolformat(AnsiString answer);
int get_current_prectest(AnsiString answer);
bool get_current_preclinetestauto02(AnsiString answer);
bool get_current_preclinetestauto01(AnsiString answer);
bool get_current_daylightsavings(AnsiString answer);
int get_current_dlmonth(AnsiString answer);
int get_current_dlweekofmonth(AnsiString answer);
int get_current_dldayofweek(AnsiString answer);
TDateTime get_current_dlhour(AnsiString answer);
bool get_current_redirectlocalpoflag(AnsiString answer);
bool get_current_qpldmonthlypoflag(AnsiString answer);
bool get_current_europrotocolprefix(AnsiString answer);
AnsiString get_current_systemcode(AnsiString answer);
int get_current_baud(AnsiString answer);
int get_current_parity(AnsiString answer);
int get_current_stopbit(AnsiString answer);
int get_current_bytesize(AnsiString answer);
int get_current_dialtype(AnsiString answer);
int get_current_answeron(AnsiString answer);
int get_current_modemtype(AnsiString answer);
int get_current_dialtoneinterval(AnsiString answer);
int get_current_dtrnormalstate(AnsiString answer);
AnsiString get_current_syscode(AnsiString answer);
AnsiString get_current_setupstring(AnsiString answer);
bool get_current_receiverconfig(AnsiString answer);
AnsiString get_current_receiverlocation(AnsiString answer);
AnsiString get_current_receivertelnumber(AnsiString answer);
int get_current_receiverportnumber(AnsiString answer);
int get_current_receivertype(AnsiString answer);
int get_current_receiverretrynumber(AnsiString answer);
int get_current_receiverdelaytime(AnsiString answer);
bool get_current_receiverconfirmation(AnsiString answer);
void get_current_reportlist(AnsiString answer, bool* replst);
bool get_current_autodialmethod(AnsiString answer);
int get_current_frequencytype(AnsiString answer);
TDateTime get_current_freqdate(AnsiString answer);
TDateTime get_current_freqtime(AnsiString answer);
int get_current_freqmonth(AnsiString answer);
int get_current_freqweek(AnsiString answer);
int get_current_freqday(AnsiString answer);
bool get_current_birend(AnsiString answer);
bool get_current_rs232eom(AnsiString answer);
void get_current_tankconfig(AnsiString answer, bool *tankconfig);
AnsiString get_current_productlabel(AnsiString answer);
AnsiString get_current_productcode(AnsiString answer);
float get_current_producttermalcoeff(AnsiString answer);
float get_current_tankdiameter(AnsiString answer);
bool get_current_meterdatapresent(AnsiString answer);
int get_current_endfactor(AnsiString answer);
float get_current_endvalue(AnsiString answer);
int get_current_calibrationupdate(AnsiString answer);
int get_current_floatsize(AnsiString answer);
float get_current_waterwarning(AnsiString answer);
float get_current_highwaterlimit(AnsiString answer);
int get_current_maxorlabelvolume(AnsiString answer);
int get_current_overfilllimit(AnsiString answer);
int get_current_highproductlimit(AnsiString answer);
int get_current_deliverylimit(AnsiString answer);
int get_current_lowproductlimit(AnsiString answer);
int get_current_leakalarmlimit(AnsiString answer);
int get_current_suddenlosslimit(AnsiString answer);
float get_current_tanktilt(AnsiString answer);
float get_current_probeoffset(AnsiString answer);
AnsiString get_current_manifoldedtanks(AnsiString answer);
int get_current_leakminimumperiodic(AnsiString answer);
int get_current_leakminimumannual(AnsiString answer);
bool get_current_periodictesttype(AnsiString answer);
bool get_current_annualtestfail(AnsiString answer);
bool get_current_periodictestfail(AnsiString answer);
bool get_current_grosstestfail(AnsiString answer);
bool get_current_annualtestaveraging(AnsiString answer);
bool get_current_periodictestaveraging(AnsiString answer);
bool get_current_leaktestnotify(AnsiString answer);
bool get_current_siphonbreak(AnsiString answer);
float get_current_stickoffset(AnsiString answer);
int get_current_hrmreconcwarnlimit(AnsiString answer);
int get_current_hrmreconcalmlimit(AnsiString answer);
int get_current_deliveryreportdt(AnsiString answer);
float get_current_pumpthreshold(AnsiString answer);
void get_current_tankprofile(AnsiString answer, AnsiString *tankprofile);
AnsiString get_current_dimversion(AnsiString answer);
AnsiString get_current_mdimstring(AnsiString answer);
AnsiString get_current_edimstring(AnsiString answer);
TDateTime get_current_autodailyclosing(AnsiString answer);
int get_current_periodicreconcmode(AnsiString answer);
int get_current_periodicreconclen(AnsiString answer);
int get_current_perreconcalmonoff(AnsiString answer);
float get_current_perreconcalmthreshold(AnsiString answer);
int get_current_perreconcalmoffset(AnsiString answer);
int get_current_remotereportformat(AnsiString answer);
bool get_current_tempcompensation(AnsiString answer);
float get_current_metercaliboffset(AnsiString answer);
void get_current_liquidsensorconfig(AnsiString answer, bool *sensorconfig);
AnsiString get_current_liqsenslocation(AnsiString answer);
int get_current_liqsenstype(AnsiString answer);
int get_current_liqsenscategory(AnsiString answer);
void get_current_vaporsensorconfig(AnsiString answer, bool *sensorconfig);
AnsiString get_current_vaporsenslocation(AnsiString answer);
int get_current_vaporsensthreshold(AnsiString answer);
int get_current_vaporsenscategory(AnsiString answer);
void get_current_grdwsensorconfig(AnsiString answer, bool *sensorconfig);
AnsiString get_current_grdwsenslocation(AnsiString answer);
int get_current_grdwsenscategory(AnsiString answer);
void get_current_extinputconfig(AnsiString answer, bool *sensorconfig);
AnsiString get_current_extinputname(AnsiString answer);
int get_current_extinputtype(AnsiString answer);
int get_current_extinputswitchtype(AnsiString answer);
int get_current_extinputtanknr(AnsiString answer);
int get_current_extinputdispensemode(AnsiString answer);
AnsiString get_current_relaydesignation(AnsiString answer);
int get_current_relaytype(AnsiString answer);
int get_current_relayorientation(AnsiString answer);
int get_current_relaytanknr(AnsiString answer);
#endif
