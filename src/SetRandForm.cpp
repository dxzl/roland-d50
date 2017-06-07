//---------------------------------------------------------------------------
#include <vcl.h>
#include "MainForm.h"
#pragma hdrstop

#include "DataGridForm.h"
#include "SetRandForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSetRand *FormSetRand;
//---------------------------------------------------------------------------
__fastcall TFormSetRand::TFormSetRand(TComponent* Owner)
    : TForm(Owner)
{
    // set 64 mask-bits for each checkBox. each tag then represents the 64
    // parameters in a partial, common or patch section on the Roland D-50.
    a00->Tag = GetUInt64(PAT_00);
    a01->Tag = GetUInt64(PAT_01);
    a02->Tag = GetUInt64(PAT_02);

    b00->Tag = GetUInt64(COM_00);
    b01->Tag = GetUInt64(COM_01);
    b02->Tag = GetUInt64(COM_02);
    b03->Tag = GetUInt64(COM_03);
    b04->Tag = GetUInt64(COM_04);
    b05->Tag = GetUInt64(COM_05);
    b06->Tag = GetUInt64(COM_06);
    b07->Tag = GetUInt64(COM_07);
    b08->Tag = GetUInt64(COM_08);
    b09->Tag = GetUInt64(COM_09);
    b10->Tag = GetUInt64(COM_10);

    c00->Tag = GetUInt64(PAR_00);
    c01->Tag = GetUInt64(PAR_01);
    c02->Tag = GetUInt64(PAR_02);
    c03->Tag = GetUInt64(PAR_03);
    c04->Tag = GetUInt64(PAR_04);
    c05->Tag = GetUInt64(PAR_05);
    c06->Tag = GetUInt64(PAR_06);
    c07->Tag = GetUInt64(PAR_07);
    c08->Tag = GetUInt64(PAR_08);
    c09->Tag = GetUInt64(PAR_09);
    c10->Tag = GetUInt64(PAR_10);
    c11->Tag = GetUInt64(PAR_11);
    c12->Tag = GetUInt64(PAR_12);
    c13->Tag = GetUInt64(PAR_13);

    // set tags for tab checkboxes to the tab-index in FormPatch!
    CbUp1->Tag = tUP1;
    CbUp2->Tag = tUP2;
    CbUc->Tag = tUC;
    CbLp1->Tag = tLP1;
    CbLp2->Tag = tLP2;
    CbLc->Tag = tLC;
    CbPatch->Tag = tP;

    ButtonOff->Tag = 0;
    ButtonOn->Tag = 1;

    slSavedState = NULL;
    slUndoState = NULL;

    MenuFormSetRandUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::FormClose(TObject *Sender, TCloseAction &Action)
{
    // close
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::FormHide(TObject *Sender)
{
    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    if (slSavedState)
    {
        delete slSavedState;
        slSavedState = NULL;
    }
    if (slUndoState)
    {
        delete slUndoState;
        slUndoState = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::FormShow(TObject *Sender)
{
    PatchGroupBoxEnableDisable();
    CommonGroupBoxEnableDisable();
    PartialGroupBoxEnableDisable();

    if (!slSavedState)
        slSavedState = new TStringList();
    if (!slUndoState)
        slUndoState = new TStringList();

    // Save snapshot of grid (to restore if we Cancel)
    FormPatch->ReadFromGrid(slSavedState);
    slUndoState->Assign(slSavedState); // copy

    for (int ii = 0; ii < TOTAL_TABS; ii++)
    {
        m_masks[ii] = 0;
        m_masksOld[ii] = 0;
    }
    m_masksOld[0] = 1; // set "different" from m_masks

//    ShowMessage(IntToHex(m_partialTags[0], 16));
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonCancelClick(TObject *Sender)
{
    if (slSavedState && slSavedState->Count > 0)
        FormPatch->WriteToGrid(slSavedState, true);

    Hide();
//    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::MenuFormSetRandUndoClick(TObject *Sender)
{
    if (slUndoState)
    {
        FormPatch->WriteToGrid(slUndoState, true);
        CopyArray(m_masksOld, m_masks, TOTAL_TABS);
        MenuFormSetRandUndo->Enabled = false;
    }
}
//---------------------------------------------------------------------------
// sets the m_masks[] array in DataGridForm as well as the corresponding
// Rand column label in each DataGrid to "On" or blank based on the
// User's checked selections in this form.
void __fastcall TFormSetRand::ButtonOnOffClick(TObject *Sender)
{
    if (!Sender) return;
    bool bOnOff = ((TButton*)Sender)->Tag == 0 ? false : true;

    SetRandOnOff(bOnOff);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonRandCurrentClick(TObject *Sender)
{
    DisableButtons();

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    SetRandOnOff(true); // set "On" in Rand columns of datagrids

    // get masks for each of 7 tabs into an array
    unsigned __int64 masks[TOTAL_TABS];
    masks[tUP1] =
    masks[tUP2] =
    masks[tLP1] =
    masks[tLP2] = GbPartial->Tag;
    masks[tUC] =
    masks[tLC] = GbCommon->Tag;
    masks[tP] = GbPatch->Tag;

    // clear the masks for the tabs that are not checked
    if (!CbUp1->Checked)
        masks[tUP1] = 0;
    if (!CbUp2->Checked)
        masks[tUP2] = 0;
    if (!CbUc->Checked)
        masks[tUC] = 0;
    if (!CbLp1->Checked)
        masks[tLP1] = 0;
    if (!CbLp2->Checked)
        masks[tLP2] = 0;
    if (!CbLc->Checked)
        masks[tLC] = 0;
    if (!CbPatch->Checked)
        masks[tP] = 0;

    // Randomize each tab that's checked according to the mask flags
    // in its associated groupbox tag
    FormPatch->ManualRandomize(masks);

    ButtonReplayClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonRandCumulativeClick(TObject *Sender)
{
    DisableButtons();

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    SetRandOnOff(true); // set "On" in Rand columns of datagrids

    // Randomize according to the global mask flags cumulatively set/cleared
    // since this form was most-recently shown...
    FormPatch->ManualRandomize(m_masks);

    ButtonReplayClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonRandAllClick(TObject *Sender)
{
    DisableButtons();

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    SetRandOnOff(true); // set "On" in Rand columns of datagrids

    // this will randomize any parameter in any tab that's "ON"
    FormPatch->ManualRandomize();

    ButtonReplayClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonReplayClick(TObject *Sender)
{
    DisableButtons();
    while (FormMain->SystemBusy);

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    FormMain->DelayGpTimer(35); // put some delay between successive calls to this!
    FormMain->PlayStream(&SEQ1[0], SIZESEQ1, 96, 500000-(50000*4));

    EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::CheckBoxTabClick(TObject *Sender)
{
    PatchGroupBoxEnableDisable();
    CommonGroupBoxEnableDisable();
    PartialGroupBoxEnableDisable();
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonSaveClick(TObject *Sender)
{
    // Save as file
    FormPatch->WritePatchToFile(false); // write as .d50 file
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::PartialGroupBoxEnableDisable(void)
{
    GbPartial->Enabled = CbLp1->Checked || CbLp2->Checked ||
                                    CbUp1->Checked || CbUp2->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::CommonGroupBoxEnableDisable(void)
{
    GbCommon->Enabled = CbLc->Checked || CbUc->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::PatchGroupBoxEnableDisable(void)
{
    GbPatch->Enabled = CbPatch->Checked;
}
//---------------------------------------------------------------------------
unsigned __int64 __fastcall TFormSetRand::GetUInt64(String s)
{
    int size = sizeof(unsigned __int64)*8;

    if (size != D50_PATCH_SECTION_SIZE || s.Length() != size)
    {
        ShowMessage("Error in GetUInt64(), size is not correct!");
        return 0;
    }

    unsigned __int64 val, x;

    x = 0;
    for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
    {
        val = s[D50_PATCH_SECTION_SIZE-ii] == '1' ? 1 : 0;
        x |= (val << ii);
    }
    return x;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::SetRandOnOff(bool bOnOff)
{
    // first collect the current On/Off rand state from each checkbox in
    // each group (it will end up in the group-box's Tag property!)
    SetGroupBoxMaskFromChecks(GbPatch);
    SetGroupBoxMaskFromChecks(GbCommon);
    SetGroupBoxMaskFromChecks(GbPartial);

    unsigned __int64 masks[TOTAL_TABS];

    // Set enable mask bits for each tab checked
    for (int ii = 0; ii < GbTabs->ControlCount; ii++)
    {
        TCheckBox* cb = (TCheckBox*)GbTabs->Controls[ii];
        if (!cb) return;

        if (cb->Checked)
        {
            int tabIndex = cb->Tag; // checkBox tag has the tab-index

            if (tabIndex == tUP1 || tabIndex == tUP2 || tabIndex == tLP1 || tabIndex == tLP2)
                masks[tabIndex] = GbPartial->Tag;
            else if (tabIndex == tUC || tabIndex == tLC)
                masks[tabIndex] = GbCommon->Tag;
            else
                masks[tabIndex] = GbPatch->Tag;

            // Set our global, cumulative On/Off operations on each
            // tab's rand-flags since this dialog was most-recently shown...
            if (bOnOff)
                m_masks[tabIndex] |= masks[tabIndex];
            else
                m_masks[tabIndex] &= ~masks[tabIndex];
        }
    }

    // here, we facilitate a single-level "Undo" by detecting a change
    // in the mask-patterns and backing-up the grid so Undo can restore
    // it...
    if (!MenuFormSetRandUndo->Enabled || !MasksEqual())
    {
        FormPatch->ReadFromGrid(slUndoState); // back up main grid

        // make the masks equal
        CopyArray(m_masksOld, m_masks, TOTAL_TABS);
        MenuFormSetRandUndo->Enabled = true;
    }

    // Now actually set the "On" or " " column 3 states for
    // each datagrid (only if the corresponding mask bit is set!)
    for (int ii = 0; ii < GbTabs->ControlCount; ii++)
    {
        TCheckBox* cb = (TCheckBox*)GbTabs->Controls[ii];
        if (!cb) return;

        if (cb->Checked)
        {
            int tabIndex = cb->Tag; // checkBox tag has the tab-index

            // NOTE: checkboxes for tabs have to have the tab-index in the Tag!
            FormPatch->SetRandFlags(tabIndex, masks[tabIndex], bOnOff);
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormSetRand::MasksEqual()
{
    for (int ii = 0; ii < TOTAL_TABS; ii++)
        if (m_masks[ii] != m_masksOld[ii])
            return false;
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::CopyArray(unsigned __int64 *dest, unsigned __int64 *source, int length)
{
    for (int ii = 0; ii < length; ii++)
        *dest++ = *source++;
}
//---------------------------------------------------------------------------
// set all checkboxes in a groupbox either checked or unchecked
void __fastcall TFormSetRand::SetAll(TGroupBox *gb, bool checked)
{
    if (!gb) return;

    for (int ii = 0; ii < gb->ControlCount; ii++)
    {
        TCheckBox* cb = (TCheckBox*)gb->Controls[ii];
        if (!cb) return;
        cb->Checked = checked;
    }
    SetGroupBoxMaskFromChecks(gb);
}
//---------------------------------------------------------------------------
// set the tag property of the groupbox to represent the collectively ored
// parameters inferred by the checked boxes via their individual 64-bit tags
void __fastcall TFormSetRand::SetGroupBoxMaskFromChecks(TGroupBox *gb)
{
    if (!gb) return;

    unsigned __int64 tag = 0;

    for (int ii = 0; ii < gb->ControlCount; ii++)
    {
        TCheckBox* cb = (TCheckBox*)gb->Controls[ii];
        if (!cb) return;
        if (cb->Checked)
            tag |= cb->Tag;
    }
    gb->Tag = tag;
}
//---------------------------------------------------------------------------
// If we don't do this and click a bunch of times, the program won't ever close!
void __fastcall TFormSetRand::DisableButtons(void)
{
    ButtonReplay->Enabled = false;
    ButtonRandCurrent->Enabled = false;
    ButtonRandCumulative->Enabled = false;
    ButtonRandAll->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::EnableButtons(void)
{
    ButtonReplay->Enabled = true;
    ButtonRandCurrent->Enabled = true;
    ButtonRandCumulative->Enabled = true;
    ButtonRandAll->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::MenuFormSetRandNoneClick(TObject *Sender)
{
    // set all checkboxes in all groupboxes "checked"
    SetAll(GbTabs, false);
    SetAll(GbPatch, false);
    SetAll(GbCommon, false);
    SetAll(GbPartial, false);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::MenuFormSetRandPartialsClick(TObject *Sender)
{
    // set all checkboxes in all groupboxes "checked"
    SetAll(GbTabs, false);

    CbUp1->Checked = true;
    CbUp2->Checked = true;
    CbLp1->Checked = true;
    CbLp2->Checked = true;

    SetAll(GbPatch, false);
    SetAll(GbCommon, false);
    SetAll(GbPartial, true);

    // turn off time/level for TVF/TVA
    c05->Checked = false;
    c06->Checked = false;
    c10->Checked = false;
    c11->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::MenuFormSetRandCommonsClick(TObject *Sender)
{
    // set all checkboxes in all groupboxes "checked"
    SetAll(GbTabs, false);

    CbUc->Checked = true;
    CbLc->Checked = true;

    SetAll(GbPatch, false);
    SetAll(GbCommon, true);
    SetAll(GbPartial, false);

    // turn off time/level for P-Enc
    b00->Checked = false;
    b01->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::MenuFormSetRandAllClick(TObject *Sender)
{
    // set all checkboxes in all groupboxes "checked"
    SetAll(GbTabs, true);
    SetAll(GbPatch, true);
    SetAll(GbCommon, true);
    SetAll(GbPartial, true);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    // Using F7/F8 because we want the same buttons to do the same things in
    // SetRandForm.cpp - and we need Space to toggle the checkboxes there,
    // and Return clicks the default button
    if (Key == VK_F7)
        ButtonRandCurrentClick(NULL);
    else if (Key == VK_F8)
        ButtonSaveClick(NULL);
    else if (Key == VK_ESCAPE)
        ButtonCancelClick(NULL);
//    if (Key == VK_SPACE)
//    {
//        if (Shift.Contains(ssCtrl))
//        else
//    }
}
//---------------------------------------------------------------------------

