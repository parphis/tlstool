//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TLStoolU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
void __fastcall TMainForm::GetCurrentPath(void)
{
	current_path = GetCurrentDir();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateConfigfilePath(void)
{
	configpath = current_path+cofig_file_name;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateLanguagefilePath(void)
{
	if (!CompareStr(language, STR_ENGLISH))
		languagepath = language_source_directoy + "\\eng.lng";
	if (!CompareStr(language, STR_GERMAN))
		languagepath = language_source_directoy + "\\ger.lng";
	if (!CompareStr(language, STR_HUNGARIAN))
		languagepath = language_source_directoy + "\\hun.lng";
	/* here need write the new language file name; this name come in design
	   time */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadMainFormDimension(void)
{
	ini = new THandleIni(configpath);

	WindowState = (TWindowState)ini->getMainWindowState();
	if (WindowState==0)
	{
		Width = ini->getMainWindowWidth();
		Height = ini->getMainWindowHeight();
		Left = ini->getMainWindowLeft();
		Top = ini->getMainWindowTop();
	}

	delete ini;
}
void __fastcall TMainForm::SaveMainFormDimension(void)
{
	if (!save_options)	return;

	ini = new THandleIni(configpath);

	ini->setMainWindowState((TWindowState)WindowState);
	ini->setMainWindowWidth(Width);
	ini->setMainWindowHeight(Height);
	ini->setMainWindowLeft(Left);
	ini->setMainWindowTop(Top);

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadReportsWindowDimension(void)
{
	ini = new THandleIni(configpath);

	if (show_reportwindow)
	{
		Reports = new TReportsW(Application);

		Reports->Width = ini->getReportWindowWidth();
		Reports->Height = ini->getReportWindowHeight();
		Reports->Left = ini->getReportWindowLeft();
		Reports->Top = ini->getReportWindowTop();
		Reports->setupanswer_m->Color = (TColor)ini->getReportWindowBackgroundColor();
		Reports->setupanswer_m->Font->Color = (TColor)ini->getReportWindowFontColor();

		Reports->Show();
		Reports->LoadLanguage(Reports);
	}

	delete ini;
}
void __fastcall TMainForm::SaveReportsWindowDimension(void)
{
	if (!save_options)	return;

	ini = new THandleIni(configpath);

	if (Reports)
	{
		ini->setReportWindowWidth(Reports->Width);
		ini->setReportWindowHeight(Reports->Height);
		ini->setReportWindowLeft(Reports->Left);
		ini->setReportWindowTop(Reports->Top);
		ini->setReportWindowBackgroundColor((TColor)Reports->setupanswer_m->Color);
		ini->setReportWindowFontColor((TColor)Reports->setupanswer_m->Font->Color);
	}

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadOtherOptions(void)
{
	ini = new THandleIni(configpath);

	show_toolbar = ini->getMainToolbarVisibility();
	save_options = ini->getSaveSettingsFlag();
	show_reportwindow = ini->getDisplayReportWindowOnStartUp();
	language = ini->getUsedLanguage();
	language_source_directoy = ini->getLanguageDirectory();
	CreateLanguagefilePath();

	delete ini;
}
void __fastcall TMainForm::SaveOtherOptions(void)
{
	if (!save_options)	return;

	ini = new THandleIni(configpath);

	ini->setMainToolbarVisibility(show_toolbar);
	ini->setSaveSettingsFlag(save_options);
	ini->setDisplayReportWindowOnStartUp(show_reportwindow);
	ini->setUsedLanguage(language);
	ini->setLanguageDirectory(language_source_directoy);

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadPortProperties(void)
{
	ini = new THandleIni(configpath);

	portname = ini->getUsedPortName();

	baud = ini->getUsedBaudRate();
	parity = ini->getUsedParity();
	stopbit = ini->getUsedStopbit();
	bytesize = ini->getUsedByteSize();
	rint = ini->getUsedReadIntervalTimeout();
	rmulti = ini->getUsedReadMultiplyTimeout();
	rconst = ini->getUsedReadConstantTimeout();
	wmulti = ini->getUsedWriteMultiplyTimeout();
	wconst = ini->getUsedWriteConstantTimeout();
	wrep = ini->getUsedWriteRepetition();
	rrep = ini->getUsedReadRepetition();

	delete ini;
}
void __fastcall TMainForm::SavePortProperties(void)
{
	if (!save_options)	return;

	ini = new THandleIni(configpath);

	ini->setUsedPortName(portname);

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadLanguage(void)
{
	TMenuItem *main_menu_arr[MENU_ITEM_COUNT] = {file_m, saveconfig_m,
												 loadconfig_m, exit_m,
												 options_m, programop_m,
												 commop_m, help_m,
												 index_m, about_m, viewreport_m,
												 port_m, connect_m, disconnect_m};

	TToolButton *tool_button_hints[TOOLBUTTON_COUNT] = {commop_tbbtn, help_tbbtn,
										loadconfig_tbbtn, programop_tbbtn,
										saveconfig_tbbtn, showreportwindow_tbbtn};

	TTabSheet *pages[PAGES_COUNT] = {setup_pg, control_pg, reconc_pg,
									 variance_pg, operation_pg, diag_pg};

	//TGroupBox *groupboxes[GROUPBOX_COUNT] = {};

	ini = new THandleIni(language, languagepath, MainForm,
						main_menu_arr, tool_button_hints, pages,
						mainsetupcategories_rg, NULL);
	ini->LoadLanguage();

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadSetupSubcategories(int number)
{
	ini = new THandleIni(language, languagepath);

	ini->SetupSubcategories(number, setupsubcat_lb);

	delete ini;
} 
//---------------------------------------------------------------------------
void __fastcall TMainForm::Run(void)
{
	/* it sets the application current directory */
	GetCurrentPath();

	/* it creates the configuration file name and path of the application */
	CreateConfigfilePath();

	/* it loads the option flags (always save, show toolbar...) and language
	   specific options (last used language, source directory) */
	LoadOtherOptions();

	/* it loads the report window dimension and create it if the flag is true */
	LoadReportsWindowDimension();

	/* it loads the main form dimensions */
	LoadMainFormDimension();

	/* it loads the language */
	if (FileExists(languagepath))	LoadLanguage();

	/* it loads the subcategories to the list box */
	LoadSetupSubcategories(mainsetupcategories_rg->ItemIndex);

	/* it loads the port properties */
	LoadPortProperties();

	/* create the tlsdevice object */
	dev = new TTLSDevice(portname.c_str());
	dev->language = language;
	dev->languagepath = languagepath;
	dev->setPortProperties(baud, parity, stopbit, bytesize, rint, rmulti,
								rconst, wmulti, wconst, wrep, rrep);
	if (!dev->getIsPortOpen())
	{
		connect_tbbtn->ImageIndex = 7;
		connect_m->Enabled = true;
		disconnect_m->Enabled = false;
	}
	else
	{
		connect_tbbtn->ImageIndex = 6;
		connect_m->Enabled = false;
		disconnect_m->Enabled = true;
	}

	/* get current directory to load the help if required */
	help_path = GetCurrentDir();
	help_path.Insert("\\tlstool_help.html",help_path.Length()+1);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Stop(void)
{
	/* it saves the option flags (always save, show toolbar...) and language
	   specific options (last used language, source directory) */
	SaveOtherOptions();

	/* it saves the report window dimension and create it if the flag is true */
	SaveReportsWindowDimension();

	/* it saves the main form dimensions */
	SaveMainFormDimension();

	/* it saves the port properties; currently is the port name only */
	SavePortProperties();
}
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	cofig_file_name = "\\tlscnfg.ini";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	Run();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mainsetupcategories_rgClick(TObject *Sender)
{
	setupsubcat_lb->Clear();
	LoadSetupSubcategories(mainsetupcategories_rg->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::setupsubcat_lbClick(TObject *Sender)
{
	/*dev->get(mainpage_pc->TabIndex, mainsetupcategories_rg->ItemIndex,
			 setupsubcat_lb->ItemIndex, setupanswer_m, 'I');*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::setupsubcat_lbDblClick(TObject *Sender)
{
	if (Reports)
	{
		if (Reports->Visible)
			dev->set(mainpage_pc->TabIndex, mainsetupcategories_rg->ItemIndex,
						setupsubcat_lb->ItemIndex, Reports->setupanswer_m, 'S');
		else
			dev->set(mainpage_pc->TabIndex, mainsetupcategories_rg->ItemIndex,
						setupsubcat_lb->ItemIndex, NULL, 'S');
	}
	else
	{
		dev->set(mainpage_pc->TabIndex, mainsetupcategories_rg->ItemIndex,
				setupsubcat_lb->ItemIndex, NULL, 'S');
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::setupsubcat_lbKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
	if (Key==VK_RETURN)	setupsubcat_lbDblClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Stop();

	if (Reports)
	{
		delete Reports;
		Reports = NULL;
	}

	delete dev;	
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::saveconfig_mClick(TObject *Sender)
{
	/* restart the tlsdevice class */
	if (dev)
	{
		delete dev;
		dev = NULL;
	}

	dev = new TTLSDevice(portname.c_str(),"");
	dev->language = language;
	dev->languagepath = languagepath;
	dev->setPortProperties(baud, parity, stopbit, bytesize, rint, rmulti,
								rconst, wmulti, wconst, wrep, rrep);

	dev->Backup();
                         
	/* restart the tlsdevice class with 'normal' mode */
	if (dev)
	{
		delete dev;
		dev = NULL;
	}

	dev = new TTLSDevice(portname.c_str());
	dev->language = language;
	dev->languagepath = languagepath;
	dev->setPortProperties(baud, parity, stopbit, bytesize, rint, rmulti,
								rconst, wmulti, wconst, wrep, rrep);
	if (!dev->getIsPortOpen())
	{
		connect_tbbtn->ImageIndex = 7;
		connect_m->Enabled = true;
		disconnect_m->Enabled = false;
	}
	else
	{
		connect_tbbtn->ImageIndex = 6;
		connect_m->Enabled = false;
		disconnect_m->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::loadconfig_mClick(TObject *Sender)
{
	/* restart the tlsdevice class */
	if (dev)
	{
		delete dev;
		dev = NULL;
	}

	dev = new TTLSDevice(portname.c_str(),"");
	dev->language = language;
	dev->languagepath = languagepath;
	dev->setPortProperties(baud, parity, stopbit, bytesize, rint, rmulti,
								rconst, wmulti, wconst, wrep, rrep);

	dev->Restore();
                         
	/* restart the tlsdevice class with 'normal' mode */
	if (dev)
	{
		delete dev;
		dev = NULL;
	}

	dev = new TTLSDevice(portname.c_str());
	dev->language = language;
	dev->languagepath = languagepath;
	dev->setPortProperties(baud, parity, stopbit, bytesize, rint, rmulti,
								rconst, wmulti, wconst, wrep, rrep);
	if (!dev->getIsPortOpen())
	{
		connect_tbbtn->ImageIndex = 7;
		connect_m->Enabled = true;
		disconnect_m->Enabled = false;
	}
	else
	{
		connect_tbbtn->ImageIndex = 6;
		connect_m->Enabled = false;
		disconnect_m->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::exit_mClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::programop_mClick(TObject *Sender)
{
	Softoptions = new TSoftwareOptionsW(Application);

	Softoptions->configpath = configpath;
	Softoptions->languagepath = languagepath;

	if (Softoptions->ShowModal()==ID_OK)
	{
		show_toolbar = Softoptions->showtoolbar_cb->Checked;
		maintoolbar_tb->Visible = show_toolbar;

		save_options = Softoptions->saveoptions_cb->Checked;

		show_reportwindow = Softoptions->showreport_cb->Checked;
		if (Reports)
		{
			if (!show_reportwindow)
					Reports->Visible = false;
			else	Reports->Visible = true;
    	}

		language = Softoptions->language;
		language_source_directoy = Softoptions->languagepath_e->Text;
		CreateLanguagefilePath();
		if (FileExists(languagepath))	LoadLanguage();
		if (FileExists(languagepath))	LoadSetupSubcategories(0);

    	dev->language = language;
		dev->languagepath = languagepath;

		if (Reports)
		{
			Reports->setupanswer_m->Color = Softoptions->background_colb->Selected;
			Reports->setupanswer_m->Font->Color = Softoptions->font_colb->Selected;
		}

    	mainsetupcategories_rg->ItemIndex = 0;
	}

	if (Softoptions)
	{
		delete Softoptions;
    	Softoptions = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::commop_mClick(TObject *Sender)
{
	Portoptions = new TPortOptionsW(Application);

	Portoptions->configpath = configpath;
	Portoptions->languagepath = languagepath;

	if (Portoptions->ShowModal()==ID_OK)
	{
		LoadPortProperties();

		delete dev;

		dev = new TTLSDevice(portname.c_str());

    	dev->setPortProperties(baud, parity, stopbit, bytesize, rint, rmulti,
								rconst, wmulti, wconst, wrep, rrep);

		if (!dev->getIsPortOpen())
		{
			connect_tbbtn->ImageIndex = 7;
			connect_m->Enabled = true;
			disconnect_m->Enabled = false;
		}
		else
		{
			connect_tbbtn->ImageIndex = 6;
			connect_m->Enabled = false;
			disconnect_m->Enabled = true;
		}

		dev->language = language;
		dev->languagepath = languagepath;
	}

	if (Portoptions)
	{
		delete Portoptions;
		Portoptions = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::index_mClick(TObject *Sender)
{
	;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::about_mClick(TObject *Sender)
{
	AboutBox = new TAboutBox(Application);
	AboutBox->language = language;
	AboutBox->languagepath = languagepath;

	AboutBox->ShowModal();

	if (AboutBox)
	{
		delete AboutBox;
		AboutBox = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewreport_mClick(TObject *Sender)
{
	if (!Reports)
	{
		Reports = new TReportsW(Application);
		Reports->Show();
		Reports->LoadLanguage(Reports);
    	show_reportwindow = true;
    	return;
	}
	if (Reports->Visible)
	{
		Reports->Hide();
		show_reportwindow = false;
	}
	else
	{
		Reports->Show();
		show_reportwindow = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::connect_mClick(TObject *Sender)
{
	if (dev->OpenSerialPort(portname.c_str()))
	{
		connect_tbbtn->ImageIndex = 6;
		connect_m->Enabled = false;
		disconnect_m->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::disconnect_mClick(TObject *Sender)
{
	if (dev->CloseSerialPort())
	{
		connect_tbbtn->ImageIndex = 7;
		connect_m->Enabled = true;
    	disconnect_m->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::connect_tbbtnClick(TObject *Sender)
{
	if (connect_tbbtn->ImageIndex==6)
	{
		if (dev->CloseSerialPort())
		{
			connect_tbbtn->ImageIndex = 7;
			connect_m->Enabled = true;
			disconnect_m->Enabled = false;
		}
	}
	else if (connect_tbbtn->ImageIndex==7)
	{
		if (dev->OpenSerialPort(portname.c_str()))
    	{
			connect_tbbtn->ImageIndex = 6;
			connect_m->Enabled = false;
			disconnect_m->Enabled = true;
		}
	}
	else
	{
		connect_m->Enabled = false;
		disconnect_m->Enabled = false;
	}
}
//---------------------------------------------------------------------------
