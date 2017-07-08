//---------------------------------------------------------------------------
#include <vcl.h>
#include "MainForm.h"
#pragma hdrstop

#include "PatchForm.h"
#include "SetRandForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormSetRand::TFormSetRand(TComponent* Owner)
    : TForm(Owner)
{
    // our creator must be a TFormPatch!
    g_formPatch = reinterpret_cast<TFormPatch*>(Owner);

    InitializeCheckBoxMasks();

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
void __fastcall TFormSetRand::FormDestroy(TObject *Sender)
{
    if (FormMain->SystemBusy)
        return;

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
void __fastcall TFormSetRand::FormHide(TObject *Sender)
{
    if (FormMain->SystemBusy)
        return;

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
void __fastcall TFormSetRand::InitializeCheckBoxMasks(void)
{
    // set 64 mask-bits for each checkBox. each tag then represents the 64
    // parameters in a partial, common or patch section on the Roland D-50.

    m_checkPatchMasks[0] = 0;
    m_checkPatchMasks[1] = GetUInt64(PAT_00);
    m_checkPatchMasks[2] = GetUInt64(PAT_01);
    m_checkPatchMasks[3] = GetUInt64(PAT_02);
    a00->Tag = 1;
    a01->Tag = 2;
    a02->Tag = 3;

    m_checkCommonMasks[0] = 0;
    m_checkCommonMasks[1] = GetUInt64(COM_00);
    m_checkCommonMasks[2] = GetUInt64(COM_01);
    m_checkCommonMasks[3] = GetUInt64(COM_02);
    m_checkCommonMasks[4] = GetUInt64(COM_03);
    m_checkCommonMasks[5] = GetUInt64(COM_04);
    m_checkCommonMasks[6] = GetUInt64(COM_05);
    m_checkCommonMasks[7] = GetUInt64(COM_06);
    m_checkCommonMasks[8] = GetUInt64(COM_07);
    m_checkCommonMasks[9] = GetUInt64(COM_08);
    m_checkCommonMasks[10] = GetUInt64(COM_09);
    m_checkCommonMasks[11] = GetUInt64(COM_10);
    b00->Tag = 1;
    b01->Tag = 2;
    b02->Tag = 3;
    b03->Tag = 4;
    b04->Tag = 5;
    b05->Tag = 6;
    b06->Tag = 7;
    b07->Tag = 8;
    b08->Tag = 9;
    b09->Tag = 10;
    b10->Tag = 11;

    m_checkPartialMasks[0] = 0;
    m_checkPartialMasks[1] = GetUInt64(PAR_00);
    m_checkPartialMasks[2] = GetUInt64(PAR_01);
    m_checkPartialMasks[3] = GetUInt64(PAR_02);
    m_checkPartialMasks[4] = GetUInt64(PAR_03);
    m_checkPartialMasks[5] = GetUInt64(PAR_04);
    m_checkPartialMasks[6] = GetUInt64(PAR_05);
    m_checkPartialMasks[7] = GetUInt64(PAR_06);
    m_checkPartialMasks[8] = GetUInt64(PAR_07);
    m_checkPartialMasks[9] = GetUInt64(PAR_08);
    m_checkPartialMasks[10] = GetUInt64(PAR_09);
    m_checkPartialMasks[11] = GetUInt64(PAR_10);
    m_checkPartialMasks[12] = GetUInt64(PAR_11);
    m_checkPartialMasks[13] = GetUInt64(PAR_12);
    m_checkPartialMasks[14] = GetUInt64(PAR_13);
    c00->Tag = 1;
    c01->Tag = 2;
    c02->Tag = 3;
    c03->Tag = 4;
    c04->Tag = 5;
    c05->Tag = 6;
    c06->Tag = 7;
    c07->Tag = 8;
    c08->Tag = 9;
    c09->Tag = 10;
    c10->Tag = 11;
    c11->Tag = 12;
    c12->Tag = 13;
    c13->Tag = 14;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonOkClick(TObject *Sender)
{
    Hide();
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
    if (FormMain->SystemBusy)
        return;

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    DisableButtons();

    SetRandOnOff(true); // set "On" in Rand columns of datagrids

    // get masks for each of 7 tabs into an array
    UINT64 masks[TOTAL_TABS];
    masks[tUP1] =
    masks[tUP2] =
    masks[tLP1] =
    masks[tLP2] = m_checkPartialMasks[0];
    masks[tUC] =
    masks[tLC] = m_checkCommonMasks[0];
    masks[tP] = m_checkPatchMasks[0];

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
    if (FormMain->SystemBusy)
        return;

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    DisableButtons();

    SetRandOnOff(true); // set "On" in Rand columns of datagrids

    // Randomize according to the global mask flags cumulatively set/cleared
    // since this form was most-recently shown...
    FormPatch->ManualRandomize(m_masks);

    ButtonReplayClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonRandAllClick(TObject *Sender)
{
    if (FormMain->SystemBusy)
        return;

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    DisableButtons();

    SetRandOnOff(true); // set "On" in Rand columns of datagrids

    // this will randomize any parameter in any tab that's "ON"
    FormPatch->ManualRandomize();

    ButtonReplayClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::ButtonReplayClick(TObject *Sender)
{
    if (FormMain->SystemBusy)
        return;

    if (FormMain->IsPlaying)
        FormMain->CloseMidiOut();

    DisableButtons();

    FormMain->DelayGpTimer(100); // put some delay between successive calls to this!
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
UINT64 __fastcall TFormSetRand::GetUInt64(String s)
{
    int size = sizeof(UINT64)*8;

    if (size != D50_PATCH_SECTION_SIZE || s.Length() != size)
    {
        ShowMessage("Error in GetUINT64(), size is not correct!");
        return 0;
    }

    UINT64 acc, mask;

    acc = 0;
    mask = 0x08000000000000000ul;
    for (int ii = 1; ii <= size; ii++)
    {
        // s[1] is bit 63, s[2] is bit 62, Etc.
        if (s[ii] == '1')
          acc |= mask;
        mask >>= 1;
    }
    return acc;
}
//---------------------------------------------------------------------------
void __fastcall TFormSetRand::SetRandOnOff(bool bOnOff)
{
    // first collect the current On/Off rand state from each checkbox in
    // each group (it will end up in the group-box's Tag property!)
    SetGroupBoxMaskFromChecks(GbPatch);
    SetGroupBoxMaskFromChecks(GbCommon);
    SetGroupBoxMaskFromChecks(GbPartial);

    UINT64 masks[TOTAL_TABS];

    // Set enable mask bits for each tab checked
    for (int ii = 0; ii < GbTabs->ControlCount; ii++)
    {
        TCheckBox* cb = (TCheckBox*)GbTabs->Controls[ii];
        if (!cb) return;

        if (cb->Checked)
        {
            int tabIndex = cb->Tag; // checkBox tag has the tab-index

            if (tabIndex == tUP1 || tabIndex == tUP2 || tabIndex == tLP1 || tabIndex == tLP2)
                masks[tabIndex] = m_checkPartialMasks[0];
            else if (tabIndex == tUC || tabIndex == tLC)
                masks[tabIndex] = m_checkCommonMasks[0];
            else
                masks[tabIndex] = m_checkPatchMasks[0];

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
void __fastcall TFormSetRand::CopyArray(UINT64 *dest, UINT64 *source, int length)
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

    UINT64 tag = 0;

    for (int ii = 0; ii < gb->ControlCount; ii++)
    {
        TCheckBox* cb = (TCheckBox*)gb->Controls[ii];
        if (!cb) return;
        if (cb->Checked)
        {
            UINT64 cbTag;
            if (gb->Name == "GbPatch")
                cbTag = m_checkPatchMasks[cb->Tag];
            else if (gb->Name == "GbCommon")
                cbTag = m_checkCommonMasks[cb->Tag];
            else
                cbTag = m_checkPartialMasks[cb->Tag];

            tag |= cbTag;
        }
    }

    if (gb->Name == "GbPatch")
        m_checkPatchMasks[0] = tag;
    else if (gb->Name == "GbCommon")
        m_checkCommonMasks[0] = tag;
    else
        m_checkPartialMasks[0] = tag;
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
    // Using F6/F7 because we want the same buttons to do the same things in
    // SetRandForm.cpp - and we need Space to toggle the checkboxes there,
    // and Return clicks the default button
    if (Key == VK_F6)
        ButtonRandCumulativeClick(NULL);
    else if (Key == VK_F7)
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
void __fastcall TFormSetRand::MenuFormSetRandHelpClick(TObject *Sender)
{
  String sHelp =
"This tool allows you to set or clear groups of random flags all at once.\n\n"
"As an example, first clear all random flags. Click Presets->All then click the Off button. This clears the \"Random Mode\" column for every parameter.\n"
"To set the just parameters we want to modify, say just the TVA Bias for Upper Partial 1, click Presets->None, click the checkbox for Upper Partial 1 and the checkbox for TVA Bias and click the On button.\n"
"Now, each time you click the Rand On button, a new sound is generated that varies only the TVA bias for Upper Partial 1.\n\n"
"Click \"Rand Current\" to randomize only the currently checked parameters in this box.\n"
"For example, click Presets->None then set whatever checks you want. Each time you click \"Rand Current\", only the parameters checked are randomized without and the On flags in the main grid are not used.\n\n"
"Click \"Rand Cumulative\" to randomize all parameters that have been checked since this box opened.\n"
"\"Rand Cumulative\" lets you clear all the checks by clicking Presets->None and add a new set of checks without throwing away your previous ones. The memory is cleared when you close this box.\n\n"
"Click \"Rand On\" to randomize all \"On\" columns in the grid.\n"
"Click Ok to close this box and keep changes or Cancel to restore things as they were.\n\n"
"You need to spend some time and experiment...";

  ShowMessage(sHelp);
}
//---------------------------------------------------------------------------

