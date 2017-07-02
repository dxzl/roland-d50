//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("SetRandForm.cpp", FormSetRand);
USEFORM("PatchForm.cpp", FormPatch);
USEFORM("MainForm.cpp", FormMain);
USEFORM("ChangePatchForm.cpp", FormChangePatch);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Obsidian");
		Application->CreateForm(__classid(TFormMain), &FormMain);
     Application->CreateForm(__classid(TFormPatch), &FormPatch);
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
