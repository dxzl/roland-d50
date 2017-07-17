//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("PatchForm.cpp", FormPatch);
USEFORM("SelectPatchForm.cpp", FormSelectPatch);
USEFORM("SetRandForm.cpp", FormSetRand);
USEFORM("RenameForm.cpp", FormRename);
USEFORM("MainForm.cpp", FormMain);
USEFORM("SetRandIntervalForm.cpp", FormSetRandInterval);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Aqua Graphite");
     Application->CreateForm(__classid(TFormMain), &FormMain);
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
