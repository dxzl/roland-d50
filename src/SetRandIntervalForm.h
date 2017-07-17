//---------------------------------------------------------------------------

#ifndef SetRandIntervalFormH
#define SetRandIntervalFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSetRandInterval : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TEdit *Edit1;
  TLabel *Label1;
  TButton *ButtonOk;
  TButton *ButtonCancel;
  TUpDown *UpDown1;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  int m_randInterval;
public:		// User declarations
  __fastcall TFormSetRandInterval(TComponent* Owner);

  __property int RandInterval = {read = m_randInterval, write = m_randInterval};
};
//---------------------------------------------------------------------------
#endif
