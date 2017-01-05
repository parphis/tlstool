//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("TLStoolU.cpp", MainForm);
USEFORM("GeneralDlgW.cpp", GenDlgW);
USEFORM("ReportsWU.cpp", ReportsW);
USEFORM("PortOptionsWU.cpp", PortOptionsW);
USEFORM("SoftwareOptionsWU.cpp", SoftwareOptionsW);
USEFORM("AboutW.cpp", AboutBox);
USEFORM("InprocessW.cpp", wInProcess);
USEFORM("BackupW.cpp", wBackup);
USEFORM("BackupProcessW.cpp", wBackupProcess);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TwBackupProcess), &wBackupProcess);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
