//---------------------------------------------------------------------------
#include <vcl.h>
#include "MainForm.h"
#pragma hdrstop
// Include header files common to all files before this directive!

#include "DataGridForm.h"
#include "SetRandForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPatch *FormPatch;
//---------------------------------------------------------------------------
__fastcall TFormPatch::TFormPatch(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::FormCreate(TObject *Sender)
{
    prevGridVals = new TStringList;
    origGridVals = new TStringList;

    m_enableCellEdit = false;
    m_randomizationOn = false;
    TimerOver2Sec->Enabled = false;
    TimerSendPatch->Enabled = false;

    InitDataGrid();

    FormSetRand = new TFormSetRand(this);
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::FormDestroy(TObject *Sender)
{
    if (prevGridVals) delete prevGridVals;
    if (origGridVals) delete origGridVals;

    if (FormSetRand)
    {
        delete FormSetRand;
        FormSetRand = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::FormClose(TObject *Sender, TCloseAction &Action)
{
    if (m_randomizationOn)
        SetRandomization(false); // this restores original patch
    else // if closing, put back original patch
    {
        // Restore original patch
        if (!WriteToGrid(origGridVals, false))
            return;

        // Write data-grid to D-50 Temp-area
        PutTempArea();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (FormMain->SystemBusy)
        return;

    // Using F7/F8 because we want the same buttons to do the same things in
    // SetRandForm.cpp - and we need Space to toggle the checkboxes there,
    // and Return clicks the default button
    if (Key == VK_F6)
    {
        if (m_randomizationOn)
            SetRandomization(false);

        FormMain->PatchChange(0); // silence playing sounds
    }
    else if (Key == VK_F7)
        ManualRandomize();
    else if (Key == VK_F8)
        // save column 1 for all tabs in comma-separated text-file, one line per tab
        MenuItemFormPatchWriteToFileClick(NULL);
    else if (Key == VK_ESCAPE)
    {
        if (m_randomizationOn)
            SetRandomization(false);
    }
}
//---------------------------------------------------------------------------
// Public (called from FormKeyDown() and SetRandForm()
void __fastcall TFormPatch::ManualRandomize(void)
{
    unsigned __int64 masks[TOTAL_TABS];
    for (int ii = 0; ii < TOTAL_TABS; ii++)
        masks[ii] = 0xffffffffffffffffull;
    ManualRandomize(masks);
}
//---------------------------------------------------------------------------
// Public (called from FormKeyDown() and SetRandForm()
void __fastcall TFormPatch::ManualRandomize(unsigned __int64 masks[])
{
//    bool bSaveRand = m_randomizationOn; // save entry state

    // if auto-randomization on, turn off
    if (m_randomizationOn)
        SetRandomization(false);

//    if (bSaveRand)
        // if user hits return and we are randomizing, we stop (to stop timer)
        // then start, causing immediate new values to be sent...
//        SetRandomization(true);
//    else // manual
//    {
        // randomize grid
        GenRandValues(masks);

        // transmit to the Roland D-50
        PutTempArea();
//    }
    MenuItemFormPatchPlayClick(NULL); // let's see what it sounds like!
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::TimerSendPatchTimer(TObject *Sender)
{
    // save previous values (if user hits the space-bar to save within
    // a few seconds after the timer triggered a change, we save previous
    // patch's data instead :-)
    ReadFromGrid(prevGridVals);

    // randomize grid
    GenRandValues();

    // transmit to the Roland D-50
    PutTempArea();
    FormMain->DelayGpTimer(100);

    MenuItemFormPatchPlayClick(NULL); // play it!

    TimerOver2Sec->Enabled = false;
    TimerOver2Sec->Interval = 2000;
    TimerOver2Sec->Enabled = true; // will tell us when over 2-sec into playback
}
//---------------------------------------------------------------------------
// This 2-second timer is started when TimerSendPatchTimer triggers a new
// random set of patch values to be put in the grid and sent to the D-50.
// Then if the user presses the spacebar to save the patch as a file,
// we can tell if they are actually trying to save the previous values...
void __fastcall TFormPatch::TimerOver2SecTimer(TObject *Sender)
{
    TimerOver2Sec->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuItemFormPatchSendToTempAreaClick(TObject *Sender)
{
    // transmit to the Roland D-50
    PutTempArea();
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::SGDblClick(TObject *Sender)
{
    TStringGrid *sg = (TStringGrid*)Sender;

    if (!sg)
        return;

    int col = sg->Col;
    int row = sg->Row;

    // range check - we only set "flags" for column 1 rows > 0
    if (col != rRand || row < 1 || row > D50_PATCH_SECTION_SIZE)
        return;

    if (sg->Cells[rRand][row].LowerCase() == "on")
        sg->Cells[rRand][row] = "";
    else
        sg->Cells[rRand][row] = "On";
}
//---------------------------------------------------------------------------
// called when user hits spacebar to save the randomly generated patch
// he's hearing...
void __fastcall TFormPatch::MenuItemFormPatchWriteToFileClick(TObject *Sender)
{
    WritePatchToFile(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::Exportpatchtosyxbinaryfile1Click(TObject *Sender)
{
    WritePatchToFile(true);
}
//---------------------------------------------------------------------------
// Set bSyx to write patch as binary .syx file
// Clear bSyx to write patch as custom .d50 text-file with all grid-info preserved
void __fastcall TFormPatch::WritePatchToFile(bool bSyx)
{
    // if randomization is on and we just changed the grid as the user was trying
    // to save the sound he was hearing, we want to instead save the previously
    // backed-up string-list...
    bool bSaveOldValues = m_randomizationOn && TimerSendPatch->Enabled &&
                              TimerOver2Sec->Enabled && prevGridVals->Count;

    // save as file
    String filePath;

    String sNew;
    if (bSyx)
        sNew = "D50_"; // if SYX file need to show its for a D50!

    for (int ii = 1; ii <= this->Caption.Length(); ii++)
    {
        Char c = this->Caption[ii];
        if (c != ' ')
            sNew += c;
    }

    if (sNew.IsEmpty())
        sNew = "blank";

    int ii = 0;

    do {
        filePath = FormMain->DocPath + "\\" + sNew +
            System::Sysutils::Format("%2.2d", ARRAYOFCONST((ii++)));
        if (bSyx)
            filePath += ".syx";
        else
            filePath += ".d50";
    }
    while (FileExists(filePath));

    if (bSaveOldValues)
    {
        if (prevGridVals->Count)
        {
            if (bSyx)
                SaveSyxFile(filePath, prevGridVals);
            else
                prevGridVals->SaveToFile(filePath);
            FormMain->FileListBox1->Update();
        }
    }
    else
    {
        // append all the data-grids
        TStringList *allGrids = NULL;

        try
        {
            allGrids = new TStringList();

            ReadFromGrid(allGrids);

            if (allGrids->Count)
            {
                if (bSyx)
                    SaveSyxFile(filePath, allGrids);
                else
                    allGrids->SaveToFile(filePath);
                FormMain->FileListBox1->Update();
    //        ShowMessage(allGrids->Text);
            }
        }
        __finally
        {
            if (allGrids)
                delete allGrids;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::SaveSyxFile(String filePath, TStringList *sl)
{
    if (!sl || sl->Count < TOTAL_TABS*(TOTAL_COLS-1))
    {
        ShowMessage("Incorrect string-list format!");
        return;
    }

    THandle h = NULL;
    Byte *buf = NULL;

    try
    {
        h = FileCreate(filePath);

        if (!h)
        {
            ShowMessage("Can't create file!");
            return;
        }

        int bufSize = SYSEX_PATCH_SECTION_SIZE;
        buf = new Byte[bufSize];

        buf[0] = BEX;
        buf[1] = ROLAND_ID; // roland
        buf[2] = FormMain->MidiChan; // channel
        buf[3] = D50_ID; // D-50
        buf[4] = R_DT1; // DT1 one-way data-set
        // checksum is two's compliment of the sum of the next 6 bytes...
        buf[5] = 0x00; // addr high (patch 1-1)

        buf[bufSize-1] = EEX;

        for (int tabIndex = 0; tabIndex < TOTAL_TABS; tabIndex++)
        {
            // for names, have to convert ascii to Roland string-format
            TStringGrid *sg = GetSgPtr(tabIndex);

            if (!sg)
                return;

            bool bHasCommonName = (sg == UpperCommonSG ||
                                sg == LowerCommonSG) ? true : false;

            bool bHasPatchName = (sg == PatchSG) ? true : false;

            buf[6] = (unsigned char)(ROLANDADDRESS[tabIndex] >> 8); // addr mid
            buf[7] = (unsigned char)ROLANDADDRESS[tabIndex]; // addr low

            // convert comma-seperated values in string and store sequentially
            // into buffer...
            if (sl->Strings[tabIndex].IsEmpty())
                return;

            TStringDynArray da = SplitString(sl->Strings[tabIndex], ",");

            if (da.Length != D50_PATCH_SECTION_SIZE+1)
                return;

            Byte *bp = buf + 8; // pointer to first data-byte

            // start at 1 since we don't want the column header...
            for (int ii = 1; ii <= D50_PATCH_SECTION_SIZE; ii++)
            {
                String s = da[ii];
                int len = s.Length();
                if (len >= 2 && s[1] == '"' && s[len] == '"')
                {
                    s.Delete(len, 1); // remove last quote first!
                    s.Delete(1, 1);
                }

                if ((bHasCommonName && ii < D50_COMMON_NAME_LENGTH) ||
                            (bHasPatchName && ii < D50_PATCH_NAME_LENGTH))
                    *bp = (Byte)AsciiToRolandChar((Byte)s[1]);
                else
                    *bp = (Byte)StrToIntDef(s, 0);

                bp++;
            }

            // compute checksum
            buf[bufSize-2] = FormMain->roland_checksum(buf, bufSize-2); // checksum

            if (FileWrite(h, buf, bufSize) < 0)
            {
                FormMain->printm("error writing: \"" + filePath + "\"");
                return;
            }
        }
    }
    __finally
    {
        if (h)
            FileClose(h);

        if (buf)
            delete [] buf;
    }
}
//---------------------------------------------------------------------------
// This reads all 64 patches stored on the Roland D-50 Synth and saves them
// to 64 individual patch-files in subdirectory "PatchSave"
// he's hearing...
void __fastcall TFormPatch::ReadAllD50PatchesAndSaveTo64Files(void)
{
    // append all the data-grids
    TStringList *allGrids = NULL;

    try
    {
        allGrids = new TStringList();

        String fileDir = FormMain->DocPath + "\\PatchSave\\";
        if (!DirectoryExists(fileDir))
            CreateDir(fileDir);

        for(int patchNum = 0; patchNum < TOTAL_PATCHES_ON_D50; patchNum++)
        {
            FormMain->PatchChange(patchNum);
            GetTempArea();

            // save as file
            String filePath;

            String sNew;
            for (int ii = 1; ii <= m_patchName.Length(); ii++)
            {
                Char c = m_patchName[ii];
                if (c != ' ')
                    sNew += c;
            }

            if (sNew.IsEmpty())
                sNew = "blank";

            int ii = 0;

            do {
                filePath = fileDir + sNew +
                    System::Sysutils::Format("%2.2d", ARRAYOFCONST((ii++))) + ".d50";
            }
            while (FileExists(filePath));

            // get all the tab data into a stringlist and write to patch-file
            allGrids->Clear();
            ReadFromGrid(allGrids);

            if (allGrids->Count)
            {
                allGrids->SaveToFile(filePath);
                FormMain->SetWorkingDir(fileDir);
            }
        }
    }
    __finally
    {
        if (allGrids)
            delete allGrids;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuItemFormPatchStartStopRandomClick(TObject *Sender)
{
    SetRandomization(!m_randomizationOn);
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::SetRandomization(bool flag)
{
    TimerOver2Sec->Enabled = false;
    TimerSendPatch->Enabled = false;
    FormMain->PatchChange(0); // silence playing sounds

    if(flag)
    {
        MenuItemFormPatchStartStopRandom->Checked = true;

        TimerSendPatchTimer(NULL); // start randomizing immediately
        TimerSendPatch->Interval = RAND_INTERVAL;;
        TimerSendPatch->Enabled = true;
    }
    else // off
    {
        MenuItemFormPatchStartStopRandom->Checked = false;

        // Restore original
        if (!WriteToGrid(origGridVals, false))
            return;

        // Write data-grid to D-50 Temp-area
        PutTempArea();
    }
    m_randomizationOn = flag;
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuItemFormPatchEnforceMinMaxValueClick(TObject *Sender)
{
    int idx = PageControl->TabIndex;
    if (idx >= 0 && idx <= TOTAL_TABS)
        EnforceDataRange(idx);
}
//---------------------------------------------------------------------------
// Overloaded...

// goes through all 64 parameters for this tab and sets Val to a random
// number between 0 and max if it has randFlag set and its mask-flag is 1.

bool __fastcall TFormPatch::GenRandValues(void)
{
    for (int ii = 0; ii < TOTAL_TABS; ii++)
        if (!GenRandValues(ii, 0xffffffffffffffffull))
            return false;
    return true;
}

bool __fastcall TFormPatch::GenRandValues(unsigned __int64 masks[])
{
    for (int ii = 0; ii < TOTAL_TABS; ii++)
        if (!GenRandValues(ii, masks[ii]))
            return false;
    return true;
}

bool __fastcall TFormPatch::GenRandValues(int tabIndex, unsigned __int64 mask)
{
    try
    {
        TStringGrid *sg = GetSgPtr(tabIndex);

        if (!sg)
            return false;

        bool bHasCommonName = (sg == UpperCommonSG || sg == LowerCommonSG) ? true : false;
        bool bHasPatchName = (sg == PatchSG) ? true : false;

        ::Randomize(); // seed random # gen

        for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++, mask >>= 1)
        {
            if ((bHasCommonName && ii < D50_COMMON_NAME_LENGTH) ||
                (bHasPatchName && ii < D50_PATCH_NAME_LENGTH) || !(mask & 1))
                continue;

            // generate a random value 0-max if "On" is in the rightmost
            // column and not an ascii name field
            if (sg->Cells[rRand][ii+1].LowerCase() == "on")
            {
                int max = StrToIntDef(sg->Cells[rMax][ii+1], -1);
                if (max >= 0)
                    sg->Cells[rVal][ii+1] = String(::Random(max+1));
            }
        }

        return true;
    }
    catch(...)
    {
        return false;
    }
}
//---------------------------------------------------------------------------
// goes through all 64 parameters for this tab and sets any out-of-range values
// to min, max or dash if it's an ascii name
void __fastcall TFormPatch::EnforceDataRange(int tabIndex)
{
    try
    {
        TStringGrid *sg = GetSgPtr(tabIndex);

        if (sg)
        {
            bool bHasCommonName = (sg == UpperCommonSG || sg == LowerCommonSG) ? true : false;
            bool bHasPatchName = (sg == PatchSG) ? true : false;

            for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
            {
                String s = sg->Cells[rVal][ii+1];

                if ((bHasCommonName && ii < D50_COMMON_NAME_LENGTH) ||
                            (bHasPatchName && ii < D50_PATCH_NAME_LENGTH))
                {
                    // for the patch and partial names, we show ascii chars
                    // in the string grid that only represend the roland-encoded
                    // chars (0-63), so we range-check in ascii...
                    bool charOk;
                    if (s.Length() != 1)
                        charOk = false;
                    else
                    {
                        Char val = s[1];
                        // from the roland midi implementation document that
                        // came with my D-50...
                        charOk = ((val >= 'A' && val <= 'Z') ||
                            (val >= 'a' && val <= 'z') ||
                                (val >= '1' && val <= '9') ||
                                    val == '0' || val == ' ' || val == '-');
                    }

                    if (!charOk)
                        sg->Cells[rVal][ii+1] = String('-');
                }
                else
                {
                    // will be a number 0-127
                    int val = StrToIntDef(s, -1); // default -1 is a failure
                    int max = StrToIntDef(sg->Cells[rMax][ii+1], -1);

                    // Constrain values to range 0-max
                    if (val < 0 || max < 0)
                        sg->Cells[rVal][ii+1] = "0";
                    else if (val > max)
                        sg->Cells[rVal][ii+1] = String(max);
                }
            }
        }
    }
    __finally
    {
    }
}
//---------------------------------------------------------------------------
// takes a roland character and converts it to ascii
// roland   /  ascii
// 0 = ' ' = 32
// 1-26 = A-Z = 65-90
// 27-52 = a-z = 97-122
// 53-61 = 1-9 = 49-57
// 62 = '0' = 48
// 63 = '-' = 45
Byte __fastcall TFormPatch::RolandCharToAscii(Byte rol_char)
{
    if (rol_char == 0) // space
        return 32;
    if (rol_char >= 1 && rol_char <= 26) // A-Z
        return rol_char+64;
    if (rol_char >= 27 && rol_char <= 52) // a-z
        return rol_char+70;
    if (rol_char >= 53 && rol_char <= 61) // 0-9
        return rol_char-4;
    if (rol_char == 62) // 0
        return 48;
    if (rol_char == 63) // -
        return 45;
    return 32; // return space if no match
}
//---------------------------------------------------------------------------
// takes an ascii char and converts it to a roland character
// roland   /  ascii
// 0 = ' ' = 32
// 1-26 = A-Z = 65-90
// 27-52 = a-z = 97-122
// 53-61 = 1-9 = 49-57
// 62 = '0' = 48
// 63 = '-' = 45
Byte __fastcall TFormPatch::AsciiToRolandChar(Byte ascii)
{
    if (ascii == 32) // space
        return 0;
    if (ascii >= 65 && ascii <= 90) // A-Z
        return ascii-64;
    if (ascii >= 97 && ascii <= 122) // a-z
        return ascii-70;
    if (ascii >= 49 && ascii <= 57) // 0-9
        return ascii+4;
    if (ascii == 48) // 0
        return 62;
    if (ascii == 45) // -
        return 63;
    return 0; // return space if no match
}
//---------------------------------------------------------------------------
// Public (called from SetRandForm.cpp)
// Sets the Rand column of the datagrid at tabIndex to "On" or "" for parameters
// that have their corresponding mask-bit set...
//
// tabIndex is the tab whose rand-state is to be altered
// mask is a 64-bit field representing the 64-parameters in each tab
// If bOnOff is true we set "On" for each bit in mask that is 1
// If bOnOff is false we clear the Rand flag column " " for each bit in mask that is 1
void __fastcall TFormPatch::SetRandFlags(int tabIndex, unsigned __int64 mask, bool bOnOff)
{
    TStringGrid *sg = GetSgPtr(tabIndex);
    if (!sg) return;

    int count = sizeof(mask)*8;

    if (count != D50_PATCH_SECTION_SIZE)
    {
        ShowMessage("Wrong # bits in mask, contact dxzl@live.com!");
        return;
    }

    // shift out each of 64 mask bits and if 1, set or clear its corresponding
    // parameter's rand-flag
    bool randFlags[D50_PATCH_SECTION_SIZE];
    for (int ii = 0; ii < count; ii++)
    {
        // set only flags for which mask-bit is 1
        if (mask & 1)
            sg->Cells[rRand][ii+1] = bOnOff ? "On" : "";
        mask >>= 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::InitDataGrid(void)
{
    origGridVals->Clear();
    prevGridVals->Clear();

    // set row 0 (captions) columns 0 (parameter values) and
    // column 1 (max parameter values)
    for (int ii = 0; ii < TOTAL_TABS; ii++)
        InitDataGrid(ii);

    // Give new patch a temporary name...
    TStringGrid *sg = GetSgPtr(tUC);
    Byte bUc[D50_COMMON_NAME_LENGTH] = {'S','c','0','t','t',' ',' ',' ',' ',' '};
    for (int ii = 1; ii <= D50_COMMON_NAME_LENGTH; ii++)
        sg->Cells[rVal][ii] = (char)bUc[ii-1];

    sg = GetSgPtr(tLC);
    Byte bLc[D50_COMMON_NAME_LENGTH] = {'S','w','i','f','t',' ',' ',' ',' ',' '};
    for (int ii = 1; ii <= D50_COMMON_NAME_LENGTH; ii++)
        sg->Cells[rVal][ii] = (char)bLc[ii-1];

    sg = GetSgPtr(tP);
    Byte bPatch[D50_PATCH_NAME_LENGTH] = {'N','e','w',' ','P','a','t','c','h',
                                        ' ',' ',' ',' ',' ',' ',' ',' ',' '};
    for (int ii = 1; ii <= D50_PATCH_NAME_LENGTH; ii++)
        sg->Cells[rVal][ii] = (char)bPatch[ii-1];

    SetCaptionToPatchTabCellValues();
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::InitDataGrid(int tabIndex)
{
    try
    {
        TStringGrid *sg = GetSgPtr(tabIndex);

        if (sg)
        {
            // col / row
            sg->Cells[rLabel][0] = "Name";
            sg->Cells[rVal][0] = "Value";
            sg->Cells[rMax][0] = "Max";
            sg->Cells[rRand][0] = "Random Mode";

            int mode;
            if (sg->Name == "UpperCommonSG" || sg->Name == "LowerCommonSG")
                mode = 0;
            else if (sg->Name == "PatchSG")
                mode = 1;
            else // PARTIALNAMES
                mode = 2;

            for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
            {
                String s = "(" + IntToStr(ii+1) + ") ";
                int max, val;
                bool bRandDef;
                if (mode == 0)
                {
                    s += COMMONNAMES[ii];
                    max = COMMONMAX[ii];
                    val = max/2;
                    bRandDef = COMMONRANDDEF[ii];
                }
                else if (mode == 1)
                {
                    s += PATCHNAMES[ii];
                    max = PATCHMAX[ii];
                    val = max/2;
                    bRandDef = PATCHRANDDEF[ii];
                }
                else // has to be one of the 4 partials!
                {
                    s += PARTIALNAMES[ii];
                    max = PARTIALMAX[ii];
                    val = max/2 + ::Random(max/2);
                    bRandDef = PARTIALRANDDEF[ii];
                }
                sg->Cells[rLabel][ii+1] = s; // name of this parameter
                sg->Cells[rVal][ii+1] =  String(val); // parameter initial value
                sg->Cells[rMax][ii+1] = String(max); // max limit
                sg->Cells[rRand][ii+1] = bRandDef ? "On" : ""; // randomization allowed
            }
        }
    }
    catch(...)
    {
        ShowMessage("Problem initializing grid for tab: " + String(tabIndex));
    }
}
//---------------------------------------------------------------------------
// read datagrid into stringlist
void __fastcall TFormPatch::ReadFromGrid(TStringList *sl)
{
    if (!sl)
        return;

    sl->Clear();
    for (int col = 1; col < TOTAL_COLS; col++)
        for (int ii = 0; ii < TOTAL_TABS; ii++)
            sl->Add(GetSgPtr(ii)->Cols[col]->CommaText);
}
//---------------------------------------------------------------------------
// read the specified tab's cells into Byte[] data
bool __fastcall TFormPatch::ReadBufFromGrid(int tabIndex, Byte *data, int column)
{
    try
    {
        TStringGrid *sg = GetSgPtr(tabIndex);

        if (!sg)
            return false;

        bool bHasCommonName = (sg == UpperCommonSG ||
                            sg == LowerCommonSG) ? true : false;

        bool bHasPatchName = (sg == PatchSG) ? true : false;

        for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
        {
            String s = sg->Cells[column][ii+1];

            if ((bHasCommonName && ii < D50_COMMON_NAME_LENGTH) ||
                            (bHasPatchName && ii < D50_PATCH_NAME_LENGTH))
            {
                if (s.Length() == 1)
                    data[ii] = AsciiToRolandChar((Byte)s[1]);
                else
                    data[ii] = 0; // return a space if empty cell
            }
            else
            {
                // will be a number 0-127
                int val = StrToIntDef(s, -1); // default -1 is a failure
                int max = StrToIntDef(sg->Cells[rMax][ii+1], -1);

                // Constrain values to range 0-max
                if (val < 0 || max < 0)
                    val = 0;
                else if (val > max)
                    val = max;

                data[ii] = val;
            }
        }

        return true;
    }
    catch(...)
    {
        return false;
    }
}
//---------------------------------------------------------------------------
// write stringlist into datagrid, can write 7 columns of value-only
// into column 1 from the first 7 tab-strings in the list, or go on to
// write column 2 (max values) and column 3 (random On/Off flags)
//
// sl strings 0-6 are current-values for tabs 0-6
// sl strings 7-13 are max-values for tabs 0-6
// sl strings 14-20 are random-flags (On/Off) for tabs 0-6
//
// Each string is comma-separated and has the column-header string followed
// by D50_PATCH_SECTION_SIZE (64) row-values.
bool __fastcall TFormPatch::WriteToGrid(TStringList *sl, bool bIncludeRandFlags)
{
    int count = sl->Count;

    if (!sl || count < TOTAL_TABS)
        return false;

    int offset = 0;
    for (int col = 1; col < TOTAL_COLS; col++)
    {
        // sometimes we don't want the rand-flags set!
        if (!bIncludeRandFlags && col == COL_RAND)
            continue;

        for (int tabIndex = 0; tabIndex < TOTAL_TABS; tabIndex++)
        {
            if (!WriteToGrid(tabIndex, sl->Strings[tabIndex+offset], col))
            {
                ShowMessage("Unable to write string to data-grid!");
                return false;
            }
        }

        offset += TOTAL_TABS;

        if (count < offset+TOTAL_TABS)
            break;
    }

    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFormPatch::WriteToGrid(int tabIndex, String sColVals, int column)
{
    try
    {
        TStringGrid *sg = GetSgPtr(tabIndex);

        if (!sg)
            return false;

        TStringDynArray da = SplitString(sColVals, ",");

        if (da.Length != D50_PATCH_SECTION_SIZE+1)
            return false;

        // start at 1 since we don't want the column header...
        for (int ii = 1; ii <= D50_PATCH_SECTION_SIZE; ii++)
        {
            String s = da[ii];
            int len = s.Length();
            if (len >= 2 && s[1] == '"' && s[len] == '"')
            {
                s.Delete(len, 1); // remove last quote first!
                s.Delete(1, 1);
            }
            sg->Cells[column][ii] = s;
        }

        return true;
    }
    catch(...)
    {
        return false;
    }
}
//---------------------------------------------------------------------------
// write Byte data into the specified tab's cells
bool __fastcall TFormPatch::WriteToGrid(int tabIndex, Byte *data, int column)
{
    try
    {
        TStringGrid *sg = GetSgPtr(tabIndex);
        if (!sg) return false;

        bool bHasCommonName = (sg == UpperCommonSG || sg == LowerCommonSG) ? true : false;
        bool bHasPatchName = (sg == PatchSG) ? true : false;

        for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
        {
            String s;

            if ((bHasCommonName && ii < D50_COMMON_NAME_LENGTH) ||
                            (bHasPatchName && ii < D50_PATCH_NAME_LENGTH))
            {
                s = WideChar(RolandCharToAscii(data[ii]));

                if (s.Length() != 1)
                    s = "-";
            }
            else
            {
                s = String((int)data[ii]);

                int val = StrToIntDef(s, -1);

                // -1 will print in the cell if range-error...
                if (val < 0)
                    s = "-1";
            }

            sg->Cells[column][ii+1] = s;
        }

        return true;
    }
    catch(...)
    {
        return false;
    }
}
//---------------------------------------------------------------------------
// the Patch tab has the D50_COMMON_NAME_LENGTH name of the patch in
// cell-offsets 1-18
void __fastcall TFormPatch::SetCaptionToPatchTabCellValues(void)
{
    TStringGrid *sg = GetSgPtr(6);

    if (sg)
    {
        m_patchName = "";

        for (int ii = 1; ii <= D50_PATCH_NAME_LENGTH; ii++)
        {
            // get the cell's string for each of 18 rows in column 1
            // starting at row 1 (since row 0 is the column header)
            String s = sg->Cells[rVal][ii];

            if (s.Length() == 1) // just 1 char in each cell...
                m_patchName += s[1]; // add the char to name
        }

        // set out form's caption to the name of the patch
        if (m_patchName.Length())
            this->Caption = m_patchName;
    }
}
//---------------------------------------------------------------------------
TStringGrid * __fastcall TFormPatch::GetSgPtr(int tabIndex)
{
    TStringGrid *sg;

    switch(tabIndex)
    {
        case tUP1:
            return UpperPartial1SG;
        case tUP2:
            return  UpperPartial2SG;
        case tUC:
            return UpperCommonSG;
        case tLP1:
            return LowerPartial1SG;
        case tLP2:
            return LowerPartial2SG;
        case tLC:
            return LowerCommonSG;
        case tP:
            return PatchSG;
    };

    return NULL;
}
//---------------------------------------------------------------------------
// we cal a timer delay in D50PutTempArea that calls Application->ProcessMessages()
// so we can hang the program (it won't close) if we call  this too fast... so
// we need a lock-out flag
void __fastcall TFormPatch::PutTempArea(void)
{
    while (FormMain->SystemBusy);

    Byte buf[SYSEX_PATCH_SECTION_SIZE];

    try
    {
        FormMain->CloseMidiOut(); // stop any stream being played

        FormMain->PatchChange(0); // silence playing sounds

        FormMain->OpenMidiOut();

        for (int ii = 0; ii < TOTAL_TABS; ii++)
        {
            ReadBufFromGrid(ii, &buf[8]);
            FormMain->D50PutTempArea(ROLANDADDRESS[ii], buf);
        }
    }
    __finally
    {
        FormMain->CloseMidiOut();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::GetTempArea(void)
{
    while (FormMain->SystemBusy);

    Byte buf[SYSEX_PATCH_SECTION_SIZE];

    try
    {
        FormMain->OpenMidiOut();
        FormMain->OpenMidiIn(MIDI_BUFSIZE, 2, true);

        // Clear data-grid TStringGrid(s)
        for (int tabIndex = 0; tabIndex < TOTAL_TABS; tabIndex++)
        {
            InitDataGrid(tabIndex);

            if (!FormMain->D50GetTempArea(ROLANDADDRESS[tabIndex], buf))
                return;

            if (!WriteToGrid(tabIndex, &buf[8]))
                return;
        }

        // set the caption to the first D50_PATCH_NAME_LENGTH chars in patch-tab column 1
        SetCaptionToPatchTabCellValues();

        ReadFromGrid(origGridVals); // save original vals

        this->Visible = true;
    }
    __finally
    {
        FormMain->CloseMidiOut();
        FormMain->CloseMidiIn();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::LoadPatchFileIntoD50AndDataGrid(String sPath)
{
    while (FormMain->SystemBusy);

    TStringList *sl = NULL;

    if (sPath.IsEmpty())
    {
        ShowMessage("Select a patch file in the panel to the left...");
        return;
    }

    if (!FileExists(sPath))
    {
        ShowMessage("File \"" + sPath + "\" does not exist!");
        return;
    }

    SetRandomization(false);

    bool bFileProcessed = false;

    try
    {
        try
        {
            // Read the file into a string-list
            sl = new TStringList();
            sl->LoadFromFile(sPath);

            if (sl->Count == TOTAL_TABS || sl->Count == TOTAL_TABS*3)
            {
//                ShowMessage(sl->Strings[0]);

                // reload default random-flag and max-value fields
                InitDataGrid();

                // Put strings in grid column 1 for all tabs
                if (!WriteToGrid(sl, true))
                    return;

                bFileProcessed = true;
            }
        }
        catch(...)
        {
        }
    }
    __finally
    {
        if (sl)
            delete sl;
    }

    // try to load file as a .syx file if it was not processed as a .d50 file...
    if (!bFileProcessed)
    {
        BYTE *buf = NULL;
        THandle h = NULL;

        try
        {
            try
            {
                // Read the file into a string-list
                sl = new TStringList();

                if ((h = FileOpen(sPath, fmOpenRead)) == 0)
                    return;

                int bufSize = SYSEX_PATCH_SIZE;
                buf = new Byte[bufSize];

                int count = FileRead(h, buf, SYSEX_PATCH_SIZE);

                if (count != SYSEX_PATCH_SIZE)
                    return;

                // reload default random-flag and max-value fields
                InitDataGrid();

                // Put strings in grid column 1 for all tabs

                for (int tabIndex = 0; tabIndex < TOTAL_TABS; tabIndex++)
                    if (!WriteToGrid(tabIndex, &buf[(tabIndex*SYSEX_PATCH_SECTION_SIZE)+8]))
                        return;

                bFileProcessed = true;
            }
            catch(...)
            {
            }
        }
        __finally
        {
            if (sl)
                delete sl;
            if (h)
                FileClose(h);
        }
    }

    if (!bFileProcessed)
        ShowMessage("Unable to load file!");
    else
    {
        // Write grid to D-50 Temp-area
        PutTempArea();

        // set the caption to the first D50_PATCH_NAME_LENGTH chars in
        // patch-tab column 1
        SetCaptionToPatchTabCellValues();

        ReadFromGrid(origGridVals); // save original vals

        this->Visible = true;

        FormMain->DelayGpTimer(100);
        MenuItemFormPatchPlayClick(NULL); // play it!
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuItemFormPatchAllNotesOffClick(TObject *Sender)
{
    if (m_randomizationOn)
        SetRandomization(false);

    FormMain->PatchChange(0); // silence playing sounds
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuItemFormPatchPlayClick(TObject *Sender)
{
    if (!FormMain->IsPlaying)
        FormMain->PlayStream(&SEQ1[0], SIZESEQ1, 96, 500000-(50000*4));
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuPresetsItemClick(TObject *Sender)
{
    int tabIndex = PageControl->TabIndex;
    if (tabIndex >= 0 && tabIndex <= TOTAL_TABS)
    {
        // set defaults
        TMenuItem *mi = (TMenuItem *)Sender;
        int presetNum = mi->Tag;
        //       ShowMessage("Tab index: " + String(idx) + " tag: " + String(presetNum));
        bool *p = NULL;
        switch (tabIndex)
        {
            case tUP1:
            case tUP2:
            case tLP1:
            case tLP2:
                if (presetNum == 0)
                    p = PARTIALRANDP1;
                else if (presetNum == 1)
                    p = PARTIALRANDP2;
                else if (presetNum == 2)
                    p = PARTIALRANDP3;
                else if (presetNum == 3)
                    p = PARTIALRANDP4;
                else if (presetNum == 101)
                    p = PARTIALRANDDEF;
                else
                    p = NULL;
                break;

            case tUC:
            case tLC:
                if (presetNum == 0)
                    p = COMMONRANDP1;
                else if (presetNum == 1)
                    p = COMMONRANDP2;
                else if (presetNum == 2)
                    p = COMMONRANDP3;
                else if (presetNum == 3)
                    p = COMMONRANDP4;
                else if (presetNum == 101)
                    p = COMMONRANDDEF;
                else
                    p = NULL;
                break;

            default:
                if (presetNum == 0)
                    p = PATCHRANDP1;
                else if (presetNum == 1)
                    p = PATCHRANDP2;
                else if (presetNum == 2)
                    p = PATCHRANDP3;
                else if (presetNum == 3)
                    p = PATCHRANDP4;
                else if (presetNum == 101)
                    p = PATCHRANDDEF;
                else
                    p = NULL;
                break;
        };

        TStringGrid *sg = GetSgPtr(tabIndex);
        if (sg)
        {
            if (p == NULL)
                for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
                    sg->Cells[rRand][ii+1] = "";
            else
                for (int ii = 0; ii < D50_PATCH_SECTION_SIZE; ii++)
                    sg->Cells[rRand][ii+1] = p[ii] ? "On" : "";
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormPatch::MenuPatchFormSetRandClick(TObject *Sender)
{
    FormSetRand->Visible = true;
}
//---------------------------------------------------------------------------

