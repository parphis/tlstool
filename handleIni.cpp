//---------------------------------------------------------------------------


#pragma hdrstop

#include "handleIni.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/* private */
AnsiString THandleIni::load_main_caption(AnsiString sec_str, TIniFile *i)
{
	if (!i) return"TLStool";

	return i->ReadString(sec_str, MAIN_FORM_NAME, "TLStool");
}
void THandleIni::load_main_menu_strings(AnsiString sec_str, TIniFile *i)
{
	if (!i || !main_menu) return;

	for (int j=0; j < MENU_ITEM_COUNT; j++)
	{
		if (!main_menu[j]) continue;
		main_menu[j]->Caption = i->ReadString(sec_str, main_menu[j]->Name, "!!!Not available!!!");
	}
}
void THandleIni::load_tool_button_hints(AnsiString sec_str, TIniFile *i)
{
	if (!i || !tool_button_hints) return;

	for (int j=0; j < TOOLBUTTON_COUNT; j++)
	{
    	if (!tool_button_hints[j]) continue;
		tool_button_hints[j]->ShowHint = true;
		tool_button_hints[j]->Hint = i->ReadString(sec_str, tool_button_hints[j]->Name, "!!!Not available!!!");
	}
}
void THandleIni::load_pages_caption(AnsiString sec_str, TIniFile *i)
{
	if (!i || !pages) return;

	for (int j=0; j < PAGES_COUNT; j++)
	{
		if (!pages[j]) continue;
		pages[j]->Caption = i->ReadString(sec_str, pages[j]->Name, "!!!Not available!!!");
	}
}
void THandleIni::load_radiogroup_captions(AnsiString sec_str, TIniFile *i,
	TRadioGroup *rg)
{
	if (!i || !rg) return;

	rg->Caption = i->ReadString(sec_str, "caption", "!!!Not available!!!");
	for (int j=0; j < SETUPRADIO_COUNT; j++)
	{
		if (rg->Items->Count < j) continue;
		rg->Items->Strings[j] = i->ReadString(sec_str, j, "!!!Not available!!!");
	}
}
void THandleIni::load_group_captions(AnsiString sec_str, TIniFile *i)
{
	if (!i || !groupboxes) return;

	for (int j=0; j < GROUPBOX_COUNT; j++)
	{
    	if (!groupboxes[j]) continue;
		groupboxes[j]->Caption = i->ReadString(sec_str, groupboxes[j]->Name, "!!!Not available!!!");
	}
}
AnsiString THandleIni::load_report_caption(AnsiString sec_str, TIniFile *i)
{
	if (!i) return "Reports";

	return i->ReadString(sec_str, REPORT_FORM_NAME, "Reports");
}

/* public */
/* constructor for main form */
THandleIni::THandleIni(AnsiString ilanguage, AnsiString ifilename, TForm *iform,
	TMenuItem **imain_menu, TToolButton **itool_button_hints, TTabSheet **ipages,
	TRadioGroup *isetup_group, TGroupBox **igroupboxes)
{
	language = ilanguage;
	filename = ifilename;
	form = iform;
	main_menu = imain_menu;
	tool_button_hints = itool_button_hints;
	pages = ipages;
	setup_group = isetup_group;
	//groupboxes = igroupboxes;
}
/* constructor for report dialog */
THandleIni::THandleIni(AnsiString ilanguage, AnsiString ifilename, TForm *iform)
{
	language = ilanguage;
	filename = ifilename;
	form = iform;
}
THandleIni::THandleIni(AnsiString ilanguage, AnsiString ifilename)
{
	language = ilanguage;
	filename = ifilename;
}
THandleIni::THandleIni(AnsiString ifilename)
{
	filename = ifilename;
}

THandleIni::~THandleIni(void)
{
	;
}

void THandleIni::setFileName(AnsiString ifilename)
{
	filename = ifilename;
}
AnsiString THandleIni::getFileName(void)
{
	return filename;
}

void THandleIni::setFormPointer(TForm *iform)
{
	form = iform;
}
TForm* THandleIni::getFormPointer(void)
{
    return form;
}

void THandleIni::LoadLanguage(void)
{
	/* if no valid form */
	if (form==NULL)	return;
	/* if no valid file name to open */
	if (filename==NULL)	return;

	TIniFile *ini = new TIniFile(filename);
	
	form->Caption = load_main_caption(MAIN_SECTION_NAME, ini);
	load_main_menu_strings(MENU_SECTION_NAME, ini);
	load_tool_button_hints(TOOLBUTTON_SECTION_NAME, ini);
	load_pages_caption(PAGES_SECTION_NAME, ini);
	load_radiogroup_captions(SETUPGROUP_SECTION_NAME, ini, setup_group);
	//load_group_captions(GROUPBOX_SECTION_NAME, ini);

	delete ini;
}

void THandleIni::LoadReportLanguage(void)
{
	/* if no valid form */
	if (form==NULL)	return;
	/* if no valid file name to open */
	if (filename==NULL)	return;

	TIniFile *ini = new TIniFile(filename);

	form->Caption = load_report_caption(REPORT_SECTION_NAME, ini);

	delete ini;
}

void THandleIni::SetupSubcategories(int inumber, TListBox *lb)
{
	if (!lb)	return;

	lb->Clear();

	/* if no valid file name to open */
	if (filename==NULL)	return;

	TIniFile *ini = new TIniFile(filename);


	if (inumber==0)
	{
		int cnt = ini->ReadInteger(SYSTEMSETUP_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 56;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(SYSTEMSETUP_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==1)
	{
		int cnt = ini->ReadInteger(COMMSETUP_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 6;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(COMMSETUP_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==2)
	{
		int cnt = ini->ReadInteger(INTANKSETUP_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 38;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(INTANKSETUP_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==3)
	{
		int cnt = ini->ReadInteger(FUELMAN_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(FUELMAN_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==4)
	{
		int cnt = ini->ReadInteger(INTANKLEAK_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 9;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(INTANKLEAK_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==5)
	{
		int cnt = ini->ReadInteger(PRESSLEAK_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 13;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(PRESSLEAK_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==6)
	{
		int cnt = ini->ReadInteger(WPLLDLINELEAK_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 10;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(WPLLDLINELEAK_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==7)
	{
		int cnt = ini->ReadInteger(LINELEAKDET_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 13;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(LINELEAKDET_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==8)
	{
		int cnt = ini->ReadInteger(LINELEAK_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(LINELEAK_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==9)
	{
		int cnt = ini->ReadInteger(LINELEAKLOCK_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 1;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(LINELEAKLOCK_SECTION_NAME, j, IntToStr(j)));
		}
	}

	if (inumber==10)
	{
		int cnt = ini->ReadInteger(PUMPSENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 3;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(PUMPSENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==11)
	{
		int cnt = ini->ReadInteger(RECONCSETUP_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 14;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(RECONCSETUP_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==12)
	{
		int cnt = ini->ReadInteger(LIQUIDSENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(LIQUIDSENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==13)
	{
		int cnt = ini->ReadInteger(VAPORSENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(VAPORSENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==14)
	{
		int cnt = ini->ReadInteger(GRWATERSENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 3;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(GRWATERSENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==15)
	{
		int cnt = ini->ReadInteger(TWOWIRESENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(TWOWIRESENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==16)
	{
		int cnt = ini->ReadInteger(THWIRESENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(THWIRESENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==17)
	{
		int cnt = ini->ReadInteger(EXTERNALINPUT_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 3;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(EXTERNALINPUT_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==18)
	{
		int cnt = ini->ReadInteger(OUTPUTRELAY_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 4;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(OUTPUTRELAY_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==19)
	{
		int cnt = ini->ReadInteger(PLLDLINEDIS_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 1;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(PLLDLINEDIS_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==20)
	{
		int cnt = ini->ReadInteger(WPLLDLINEDIS_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 1;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(WPLLDLINEDIS_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==21)
	{
		int cnt = ini->ReadInteger(LINEDIS_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 1;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(LINEDIS_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==22)
	{
		int cnt = ini->ReadInteger(SMARTSENSOR_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 3;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(SMARTSENSOR_SECTION_NAME, j, IntToStr(j)));
		}
	}
	if (inumber==23)
	{
		int cnt = ini->ReadInteger(ARCHIVE_SECTION_NAME, SETUP_SECTION_COUNT_NAME, 0);
		if (cnt==0)	cnt = 3;
		for (int j=0; j < cnt; j++)
		{
			lb->Items->Add(ini->ReadString(ARCHIVE_SECTION_NAME, j, IntToStr(j)));
		}
	}

	delete ini;
}

void THandleIni::StringListLoading(TStringList *l, AnsiString section, int cnt)
{
	if (!l) return;

	/* if no valid file name to open */
	if (filename==NULL)	return;

	TIniFile *ini = new TIniFile(filename);

	for (int i=0; i < cnt; i++)
	{
		l->Add(ini->ReadString(section, i, "!!!Not available!!!"));
	}

	delete ini;
}

/* it reads the language section of the language file */
AnsiString THandleIni::getLanguageString(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return "!!!not avaolable!!!";

	AnsiString result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadString(STR_LANGUAGE_SECTION_NAME, STR_LANGUAGE_NAME,
								"!!!not available!!!");

	delete ini;

	return result;
}

/* program settings */
//main window state
void THandleIni::setMainWindowState(int istate)
{
	/* if no valid file name to open */
	if (filename==NULL)	return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_MAINSTATE, istate);

	delete ini;
}
int THandleIni::getMainWindowState(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_MAINSTATE;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_MAINSTATE,DEF_MAINSTATE);

	if ( (result < MIN_MAINSTATE) || (result > MAX_MAINSTATE) )
	{
		result = DEF_MAINSTATE;
	}

	delete ini;

	return result;
}
//main window width
void THandleIni::setMainWindowWidth(int imainwidth)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_MAINWIDTH, imainwidth);

	delete ini;
}
int THandleIni::getMainWindowWidth(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_MAINWIDTH;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_MAINWIDTH,DEF_MAINWIDTH);

	if ( (result < MIN_MAINWIDTH) || (result > MAX_MAINWIDTH) )
	{
		result = DEF_MAINWIDTH;
	}

	delete ini;

	return result;
}
//main window height
void THandleIni::setMainWindowHeight(int imainheight)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_MAINHEIGHT, imainheight);

	delete ini;
}
int THandleIni::getMainWindowHeight(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_MAINHEIGHT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_MAINHEIGHT,
								DEF_MAINHEIGHT);

	if ( (result < MIN_MAINHEIGHT) || (result > MAX_MAINHEIGHT) )
	{
		result = DEF_MAINHEIGHT;
	}

	delete ini;

	return result;
}
//main window left
void THandleIni::setMainWindowLeft(int imainleft)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_MAINLEFT, imainleft);

	delete ini;
}
int THandleIni::getMainWindowLeft(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_MAINLEFT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_MAINLEFT, DEF_MAINLEFT);

	if ( (result < MIN_MAINLEFT) || (result > MAX_MAINLEFT) )
	{
		result = DEF_MAINLEFT;
	}

	delete ini;

	return result;
}
//main window top
void THandleIni::setMainWindowTop(int imaintop)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_MAINTOP, imaintop);

	delete ini;
}
int THandleIni::getMainWindowTop(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_MAINTOP;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_MAINTOP, DEF_MAINTOP);

	if ( (result < MIN_MAINTOP) || (result > MAX_MAINTOP) )
	{
		result = DEF_MAINTOP;
	}

	delete ini;

	return result;
}
//display main toolbar
void THandleIni::setMainToolbarVisibility(int ivisible)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_MAINTOOLBAR, ivisible);

	delete ini;
}
int THandleIni::getMainToolbarVisibility(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_MAINTOOLBAR;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_MAINTOOLBAR,
								DEF_MAINTOOLBAR);

	if ( (result < MIN_MAINTOOLBAR) || (result > MAX_MAINTOOLBAR) )
	{
		result = DEF_MAINTOOLBAR;
	}

	delete ini;

	return result;
}
//save settings
void THandleIni::setSaveSettingsFlag(int isaveflag)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_SAVESETTINGS, isaveflag);

	delete ini;
}
int THandleIni::getSaveSettingsFlag(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_SAVESETTINGS;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_SAVESETTINGS,
								DEF_SAVESETTINGS);

	if ( (result < MIN_SAVESETTINGS) || (result > MAX_SAVESETTINGS) )
	{
		result = DEF_SAVESETTINGS;
	}

	delete ini;

	return result;
}
//display report window on startup
void THandleIni::setDisplayReportWindowOnStartUp(int idispreport)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_DISPONSTART, idispreport);

	delete ini;
}
int THandleIni::getDisplayReportWindowOnStartUp(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_DISPONSTART;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_DISPONSTART,
								DEF_DISPONSTART);

	if ( (result < MIN_DISPONSTART) || (result > MAX_DISPONSTART) )
	{
		result = DEF_DISPONSTART;
	}

	delete ini;

	return result;
}
//report window width
void THandleIni::setReportWindowWidth(int ireportwidth)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_REPORTWIDTH, ireportwidth);

	delete ini;
}
int THandleIni::getReportWindowWidth(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_REPORTWIDTH;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_REPORTWIDTH,
								DEF_REPORTWIDTH);

	if ( (result < MIN_REPORTWIDTH) || (result > MAX_REPORTWIDTH) )
	{
		result = DEF_REPORTWIDTH;
	}

	delete ini;

	return result;
}
//report window height
void THandleIni::setReportWindowHeight(int ireportheight)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_REPORTHEIGHT, ireportheight);

	delete ini;
}
int THandleIni::getReportWindowHeight(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_REPORTHEIGHT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_REPORTHEIGHT,
								DEF_REPORTHEIGHT);

	if ( (result < MIN_REPORTHEIGHT) || (result > MAX_REPORTHEIGHT) )
	{
		result = DEF_REPORTHEIGHT;
	}

	delete ini;

	return result;
}
//report window left
void THandleIni::setReportWindowLeft(int ireportleft)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_REPORTLEFT, ireportleft);

	delete ini;
}
int THandleIni::getReportWindowLeft(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_REPORTLEFT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_REPORTLEFT,
								DEF_REPORTLEFT);

	if ( (result < MIN_REPORTLEFT) || (result > MAX_REPORTLEFT) )
	{
		result = DEF_REPORTLEFT;
	}

	delete ini;

	return result;
}
//report window top
void THandleIni::setReportWindowTop(int ireporttop)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_REPORTTOP, ireporttop);

	delete ini;
}
int THandleIni::getReportWindowTop(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_REPORTTOP;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_REPORTTOP,
								DEF_REPORTTOP);

	if ( (result < MIN_REPORTTOP) || (result > MAX_REPORTTOP) )
	{
		result = DEF_REPORTTOP;
	}

	delete ini;

	return result;
}
//report window background color
void THandleIni::setReportWindowBackgroundColor(unsigned int ireportbkgcolor)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_REPORTBKGCOLOR, ireportbkgcolor);

	delete ini;
}
unsigned int THandleIni::getReportWindowBackgroundColor(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return clBlack;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_REPORTBKGCOLOR, clBlack);

	delete ini;

	return result;
}
//report window font color
void THandleIni::setReportWindowFontColor(unsigned int ireportfontcolor)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PROGRAMSETTINGS, STR_REPORTFONTCOLOR,
						ireportfontcolor);

	delete ini;
}
unsigned int THandleIni::getReportWindowFontColor(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return clWhite;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PROGRAMSETTINGS, STR_REPORTFONTCOLOR,clWhite);

	delete ini;

	return result;
}
//last used language
void THandleIni::setUsedLanguage(AnsiString iusedlang)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteString(STR_PROGRAMSETTINGS, STR_LANGUAGEUSED, iusedlang);

	delete ini;
}
AnsiString THandleIni::getUsedLanguage(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return STR_ENGLISH;

	AnsiString result;
	bool cmp;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadString(STR_PROGRAMSETTINGS, STR_LANGUAGEUSED,STR_ENGLISH);

	delete ini;

	cmp = CompareStr(result, STR_ENGLISH);
	cmp &= CompareStr(result, STR_GERMAN);
	cmp &= CompareStr(result, STR_HUNGARIAN);
	/* here come the new languages */

	if (cmp)	return STR_ENGLISH;

	return result;
}
//language source directory
void THandleIni::setLanguageDirectory(AnsiString ilangdirectory)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteString(STR_PROGRAMSETTINGS, STR_LANGUAGEDIRECTORY,ilangdirectory);

	delete ini;
}
AnsiString THandleIni::getLanguageDirectory(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_LANGUAGEDIRECTORY;

	AnsiString result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadString(STR_PROGRAMSETTINGS, STR_LANGUAGEDIRECTORY,
								DEF_LANGUAGEDIRECTORY);

	delete ini;

	return result;
}

/* serial port settings */
//port name
void THandleIni::setUsedPortName(AnsiString iportname)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteString(STR_PORTSETTINGS, STR_PORTNAME, iportname);

	delete ini;
}
AnsiString THandleIni::getUsedPortName(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return STR_COM1;

	AnsiString result;
	bool cmp;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadString(STR_PORTSETTINGS, STR_PORTNAME, STR_COM1);

	delete ini;

	cmp = CompareStr(result, STR_COM1);
	cmp &= CompareStr(result, STR_COM2);
	cmp &= CompareStr(result, STR_COM3);
	cmp &= CompareStr(result, STR_COM4);
	cmp &= CompareStr(result, STR_COM5);
	cmp &= CompareStr(result, STR_COM6);
	cmp &= CompareStr(result, STR_COM7);
	cmp &= CompareStr(result, STR_COM8);

	if (cmp)	return STR_COM1;

	return result;
}
//baud rate
void THandleIni::setUsedBaudRate(int ibaudrate)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_BAUDRATE, ibaudrate);

	delete ini;
}
int THandleIni::getUsedBaudRate(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_BAUDRATE;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_BAUDRATE, DEF_BAUDRATE);

	if ( (result < MIN_BAUDRATE) || (result > MAX_BAUDRATE) )
	{
		result = DEF_BAUDRATE;
	}

	delete ini;

	return result;
}
//parity
void THandleIni::setUsedParity(int iparity)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_PARITY, iparity);

	delete ini;
}
int THandleIni::getUsedParity(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_PARITY;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_PARITY, DEF_PARITY);

	if ( (result < MIN_PARITY) || (result > MAX_PARITY) )
	{
		result = DEF_PARITY;
	}

	delete ini;

	return result;
}
//stop bit
void THandleIni::setUsedStopbit(int istopbit)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_STOPBIT, istopbit);

	delete ini;
}
int THandleIni::getUsedStopbit(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_STOPBIT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_STOPBIT, DEF_STOPBIT);

	if ( (result < MIN_STOPBIT) || (result > MAX_STOPBIT) )
	{
		result = DEF_STOPBIT;
	}

	delete ini;

	return result;
}
//byte size
void THandleIni::setUsedByteSize(int ibytesize)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_BYTESIZE, ibytesize);

	delete ini;
}
int THandleIni::getUsedByteSize(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_BYTESIZE;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_BYTESIZE, DEF_BYTESIZE);

	if ( (result < MIN_BYTESIZE) || (result > MAX_BYTESIZE) )
	{
		result = DEF_BYTESIZE;
	}

	delete ini;

	return result;
}
//read interval timeout
void THandleIni::setUsedReadIntervalTimeout(int ireadint)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_READINTTOUT, ireadint);

	delete ini;
}
int THandleIni::getUsedReadIntervalTimeout(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_READINTTOUT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_READINTTOUT, DEF_READINTTOUT);

	if ( (result < MIN_READINTTOUT) || (result > MAX_READINTTOUT) )
	{
		result = DEF_READINTTOUT;
	}

	delete ini;

	return result;
}
//read multiply timeout
void THandleIni::setUsedReadMultiplyTimeout(int ireadmulti)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_READMULTITOUT, ireadmulti);

	delete ini;
}
int THandleIni::getUsedReadMultiplyTimeout(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_READMULTITOUT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_READMULTITOUT,
								DEF_READMULTITOUT);

	if ( (result < MIN_READMULTITOUT) || (result > MAX_READMULTITOUT) )
	{
		result = DEF_READMULTITOUT;
	}

	delete ini;

	return result;
}
//read constant timeout
void THandleIni::setUsedReadConstantTimeout(int ireadconst)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_READCONSTTOUT, ireadconst);

	delete ini;
}
int THandleIni::getUsedReadConstantTimeout(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_READCONSTTOUT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_READCONSTTOUT,
								DEF_READCONSTTOUT);

	if ( (result < MIN_READCONSTTOUT) || (result > MAX_READCONSTTOUT) )
	{
		result = DEF_READCONSTTOUT;
	}

	delete ini;

	return result;
}
//write multiply timeout
void THandleIni::setUsedWriteMultiplyTimeout(int iwritemulti)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_WRITEMULTITOUT, iwritemulti);

	delete ini;
}
int THandleIni::getUsedWriteMultiplyTimeout(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_WRITEMULTITOUT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_WRITEMULTITOUT,
								DEF_WRITEMULTITOUT);

	if ( (result < MIN_WRITEMULTITOUT) || (result > MAX_WRITEMULTITOUT) )
	{
		result = DEF_WRITEMULTITOUT;
	}

	delete ini;

	return result;
}
//write constant timeout
void THandleIni::setUsedWriteConstantTimeout(int iwriteconst)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_WRITECONSTTOUT, iwriteconst);

	delete ini;
}
int THandleIni::getUsedWriteConstantTimeout(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_WRITECONSTTOUT;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_WRITECONSTTOUT,
								DEF_WRITECONSTTOUT);

	if ( (result < MIN_WRITECONSTTOUT) || (result > MAX_WRITECONSTTOUT) )
	{
		result = DEF_WRITECONSTTOUT;
	}

	delete ini;

	return result;
}
//write repetition
void THandleIni::setUsedWriteRepetition(int iwriterep)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_WRITEREPETITION, iwriterep);

	delete ini;
}
int THandleIni::getUsedWriteRepetition(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_WRITEREPETITION;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_WRITEREPETITION,
								DEF_WRITEREPETITION);

	if ( (result < MIN_WRITEREPETITION) || (result > MAX_WRITEREPETITION) )
	{
		result = DEF_WRITEREPETITION;
	}

	delete ini;

	return result;
}
//read repetition
void THandleIni::setUsedReadRepetition(int ireadrep)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteInteger(STR_PORTSETTINGS, STR_READREPETITION, ireadrep);

	delete ini;
}
int THandleIni::getUsedReadRepetition(void)
{
	/* if no valid file name to open */
	if (filename==NULL) return DEF_READREPETITION;

	int result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadInteger(STR_PORTSETTINGS, STR_READREPETITION,
								DEF_READREPETITION);

	if ( (result < MIN_READREPETITION) || (result > MAX_READREPETITION) )
	{
		result = DEF_READREPETITION;
	}

	delete ini;

	return result;
}

void THandleIni::writeCommand(AnsiString cmd_name, AnsiString cmd_str)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	try
	{
		ini->WriteString(BACKUP_FILE_COMMAND_SECTION, cmd_name, cmd_str);
	}
	catch(...)
	{
		;
	}

	delete ini;
}

AnsiString THandleIni::readCommand(AnsiString cmd_name)
{
	/* if no valid file name to open */
	if (filename==NULL) return "";

	AnsiString result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadString(BACKUP_FILE_COMMAND_SECTION, cmd_name, "");

	delete ini;

	return result;
}

void THandleIni::writeBackupDetails(TStringList *l)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	ini->WriteString(BACKUP_AUTHORNAME, "Name", l->Strings[0]);
	ini->WriteString(BACKUP_DATETIME, "Date", l->Strings[1]);
	ini->WriteString(BACKUP_DATETIME, "Time", l->Strings[2]);
	ini->WriteString(BACKUP_STATION, "Name", l->Strings[3]);
	ini->WriteString(BACKUP_STATION, "Placename", l->Strings[4]);
	ini->WriteString(BACKUP_STATION, "Address", l->Strings[5]);
	ini->WriteString(BACKUP_DEVICEID, "Type", l->Strings[6]);
	ini->WriteString(BACKUP_DEVICEID, "Serialnumber", l->Strings[7]);
	if (l->Strings[8]!="") ini->WriteString(BACKUP_BACKUPDATE, "StoredOn", l->Strings[8]);
	if (l->Strings[9]!="") ini->WriteString(BACKUP_RESTOREDATE, "RestoredOn", l->Strings[9]);
	ini->WriteString(BACKUP_OTHERNOTES, "Note", l->Strings[10]);

	delete ini;
}

void THandleIni::readBackupDetails(TStringList *l)
{
	/* if no valid file name to open */
	if (filename==NULL) return;

	TIniFile *ini = new TIniFile(filename);

	l->Add(ini->ReadString(BACKUP_AUTHORNAME, "Name", ""));
	l->Add(ini->ReadString(BACKUP_DATETIME, "Date", ""));
	l->Add(ini->ReadString(BACKUP_DATETIME, "Time", ""));
	l->Add(ini->ReadString(BACKUP_STATION, "Name", ""));
	l->Add(ini->ReadString(BACKUP_STATION, "Placename", ""));
	l->Add(ini->ReadString(BACKUP_STATION, "Address", ""));
	l->Add(ini->ReadString(BACKUP_DEVICEID, "Type", ""));
	l->Add(ini->ReadString(BACKUP_DEVICEID, "Serialnumber", ""));
	l->Add(ini->ReadString(BACKUP_BACKUPDATE, "StoredOn", ""));
	l->Add(ini->ReadString(BACKUP_RESTOREDATE, "RestoredOn", ""));
	l->Add(ini->ReadString(BACKUP_OTHERNOTES, "Note", ""));

	delete ini;
}

AnsiString THandleIni::LoadErrorString(int nr)
{
	/* if no valid file name to open */
	if (filename==NULL) return "";

	AnsiString result;

	TIniFile *ini = new TIniFile(filename);

	result = ini->ReadString(ERRORSTRING_SECTION, IntToStr(nr), "");

	delete ini;

	return result;
}
