//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RenameForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormRename::TFormRename(TComponent* Owner)
  : TForm(Owner)
{
    m_maxLength = -1;
    m_newName = "NoName";
    this->ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormRename::FormShow(TObject *Sender)
{
   this->Label1->Caption = "Name (" + String(m_maxLength) + " characters)";
   this->Edit1->Text = m_newName;
}
//---------------------------------------------------------------------------
void __fastcall TFormRename::FormClose(TObject *Sender, TCloseAction &Action)
{
   m_newName = this->Edit1->Text.SubString(1, m_maxLength);
   m_maxLength = m_newName.Length();
}
//---------------------------------------------------------------------------
void __fastcall TFormRename::ButtonOkClick(TObject *Sender)
{
    this->ModalResult = mrOk; // Close()
}
//---------------------------------------------------------------------------
