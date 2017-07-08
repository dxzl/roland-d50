//---------------------------------------------------------------------------

#ifndef RenameFormH
#define RenameFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormRename : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TEdit *Edit1;
  TLabel *Label1;
  TButton *ButtonOk;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall ButtonOkClick(TObject *Sender);
private:	// User declarations
  int m_maxLength;
  String m_newName;
public:		// User declarations
  __fastcall TFormRename(TComponent* Owner);

  __property String NewName = {read = m_newName, write = m_newName};
  __property int MaxLength = {read = m_maxLength, write = m_maxLength};
};
//---------------------------------------------------------------------------
#endif
