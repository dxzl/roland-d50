//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectPatch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSelectPatch *FormSelectPatch;
//---------------------------------------------------------------------------
__fastcall TFormSelectPatch::TFormSelectPatch(TComponent* Owner)
  : TForm(Owner)
{
  FPatch = 0; // can change after creating form but before showmodal...
  FAllowCard = true; // allow card to be selected
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectPatch::FormClose(TObject *Sender, TCloseAction &Action)
{
  FPatch = ComboBox1->ItemIndex; // 0-63
  if (RadioGroup1->ItemIndex == 1)
    FPatch += 64;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectPatch::FormShow(TObject *Sender)
{
  RadioGroup1->Enabled = FAllowCard;
  RadioGroup1->ItemIndex = (FPatch > 63 && FAllowCard) ? 1 : 0;
  ComboBox1->ItemIndex = (FPatch > 63) ? FPatch-64 : FPatch;
}
//---------------------------------------------------------------------------
