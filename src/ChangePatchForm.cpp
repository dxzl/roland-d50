//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChangePatchForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormChangePatch *FormChangePatch;
//---------------------------------------------------------------------------
__fastcall TFormChangePatch::TFormChangePatch(TComponent* Owner)
  : TForm(Owner)
{
  FPatch = 0; // can change after creating form but before showmodal...
}
//---------------------------------------------------------------------------
void __fastcall TFormChangePatch::FormClose(TObject *Sender, TCloseAction &Action)
{
  FPatch = ComboBox1->ItemIndex; // 0-63
  if (RadioGroup1->ItemIndex == 1)
    FPatch += 64;
}
//---------------------------------------------------------------------------
void __fastcall TFormChangePatch::FormShow(TObject *Sender)
{
  if (FPatch < 64)
  {
    ComboBox1->ItemIndex = FPatch;
    RadioGroup1->ItemIndex = 0;
  }
  else if (FPatch < 128)
  {
    ComboBox1->ItemIndex = FPatch-64;
    RadioGroup1->ItemIndex = 1;
  }
}
//---------------------------------------------------------------------------
