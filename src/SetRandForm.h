//---------------------------------------------------------------------------

#ifndef SetRandFormH
#define SetRandFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------
class TFormSetRand : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GbTabs;
    TCheckBox *CbUp1;
    TCheckBox *CbUp2;
    TCheckBox *CbUc;
    TCheckBox *CbLp1;
    TCheckBox *CbLp2;
    TCheckBox *CbLc;
    TGroupBox *GbPartial;
    TCheckBox *c00;
    TCheckBox *c01;
    TCheckBox *c03;
    TCheckBox *c08;
    TCheckBox *c04;
    TCheckBox *c06;
    TCheckBox *CbPatch;
    TCheckBox *c07;
    TGroupBox *GbCommon;
    TCheckBox *b02;
    TCheckBox *b00;
    TCheckBox *b01;
    TCheckBox *b03;
    TGroupBox *GbPatch;
    TCheckBox *a00;
    TCheckBox *a01;
    TCheckBox *a02;
    TPanel *PannelButtons;
    TButton *ButtonOff;
    TButton *ButtonCancel;
    TButton *ButtonReplay;
    TButton *ButtonOn;
    TCheckBox *b04;
    TCheckBox *b05;
    TCheckBox *b06;
    TCheckBox *c13;
    TCheckBox *c10;
    TCheckBox *c11;
    TCheckBox *c12;
    TCheckBox *b07;
    TCheckBox *b08;
    TCheckBox *b09;
    TCheckBox *b10;
    TButton *ButtonRandCurrent;
    TMainMenu *MainMenu;
    TMenuItem *MenuFormSetRandPresets;
    TMenuItem *MenuFormSetRandAll;
    TMenuItem *MenuFormSetRandPartials;
    TMenuItem *MenuFormSetRandCommons;
    TCheckBox *c02;
    TCheckBox *c09;
    TCheckBox *c05;
    TButton *ButtonOk;
    TButton *ButtonRandCumulative;
    TButton *ButtonRandAll;
    TButton *ButtonSave;
    TMenuItem *MenuFormSetRandUndo;
    TMenuItem *MenuFormSetRandNone;
    void __fastcall ButtonCancelClick(TObject *Sender);
    void __fastcall MenuFormSetRandAllClick(TObject *Sender);
    void __fastcall ButtonOnOffClick(TObject *Sender);
    void __fastcall ButtonRandCurrentClick(TObject *Sender);
    void __fastcall ButtonReplayClick(TObject *Sender);
    void __fastcall CheckBoxTabClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonRandAllClick(TObject *Sender);
    void __fastcall ButtonRandCumulativeClick(TObject *Sender);
    void __fastcall ButtonSaveClick(TObject *Sender);
    void __fastcall MenuFormSetRandUndoClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall MenuFormSetRandPartialsClick(TObject *Sender);
    void __fastcall MenuFormSetRandCommonsClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall MenuFormSetRandNoneClick(TObject *Sender);
private:	// User declarations
    void __fastcall DisableButtons(void);
    void __fastcall EnableButtons(void);
    void __fastcall CopyArray(unsigned __int64 *dest, unsigned __int64 *source, int length);
    bool __fastcall MasksEqual();
    void __fastcall SetRandOnOff(bool bOnOff);
    void __fastcall SetGroupBoxMaskFromChecks(TGroupBox *gb);
    void __fastcall SetAll(TGroupBox *gb, bool checked);
    unsigned __int64 __fastcall GetUInt64(String s);
    void __fastcall PatchGroupBoxEnableDisable(void);
    void __fastcall CommonGroupBoxEnableDisable(void);
    void __fastcall PartialGroupBoxEnableDisable(void);

    // these are the masks for random on/off flags that are cumulative
    // from the time this form is shown. when you press "On" or "Off"
    // buttons, it sets or clears bits for the selected tabs. this
    // allows the "Rand Cumulative" button to randomize only the
    // parameters that have been set to "On" via this dialog, since it
    // was shown... and that were not set "Off" along the way...
    unsigned __int64 m_masks[TOTAL_TABS];
    unsigned __int64 m_masksOld[TOTAL_TABS];
    TStringList *slSavedState, *slUndoState;

public:		// User declarations
    __fastcall TFormSetRand(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSetRand *FormSetRand;
//---------------------------------------------------------------------------
#endif
