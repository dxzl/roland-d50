//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SetRandIntervalForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormSetRandInterval::TFormSetRandInterval(TComponent* Owner)
  : TForm(Owner)
{
    m_randInterval = 7000; // default
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRandInterval::FormShow(TObject *Sender)
{
    UpDown1->Position = m_randInterval;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRandInterval::FormClose(TObject *Sender, TCloseAction &Action)
{
    m_randInterval = UpDown1->Position;
}
//---------------------------------------------------------------------------
