//---------------------------------------------------------------------------

#ifndef SelectPatchFormH
#define SelectPatchFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSelectPatch : public TForm
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
  bool FAllowCard;
public:		// User declarations
  __fastcall TFormSelectPatch(TComponent* Owner);

  __property int Patch = {read = FPatch, write = FPatch};
  __property bool AllowCard = {read = FAllowCard, write = FAllowCard};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSelectPatch *FormSelectPatch;
//---------------------------------------------------------------------------
#endif
