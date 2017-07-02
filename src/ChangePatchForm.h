//---------------------------------------------------------------------------

#ifndef ChangePatchFormH
#define ChangePatchFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormChangePatch : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TComboBox *ComboBox1;
  TRadioGroup *RadioGroup1;
  TButton *ButtonOk;
  TButton *ButtonCancel;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  int FPatch;
public:		// User declarations
  __fastcall TFormChangePatch(TComponent* Owner);

  __property int Patch = {read = FPatch, write = FPatch};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormChangePatch *FormChangePatch;
//---------------------------------------------------------------------------
#endif
