//---------------------------------------------------------------------------
// Midi Input: TMIDI_Device_Input g_midiIn
//
//public:
//  __fastcall virtual TMIDI_Device_Input(System::Classes::TComponent* AOwner);
//  __fastcall virtual ~TMIDI_Device_Input(void);
//  virtual bool __fastcall Open(void);
//  virtual bool __fastcall Close(void);
//  virtual bool __fastcall is_opened(void);
//  virtual bool __fastcall is_closed(void);
//  MidiInputState __fastcall Status(void);
//  Msc_definitions::TMIDI_Event* __fastcall GetMidiEvent(void);
//  void __fastcall Start(void);
//  void __fastcall Stop(void);
//  void __fastcall MidiInput(Winapi::Messages::TMessage &Message);
//  __property System::Word Error = {read=FError, nodefault};
//  __property int DriverVersion = {read=FDriverVersion, nodefault};
//  __property System::Word MID = {read=FMID, nodefault};
//  __property System::Word PID = {read=FPID, nodefault};
//  __property NativeInt MIDIHandle = {read=FMIDIHandle, nodefault};
//  __property System::Word MessageCount = {read=GetEventCount, nodefault};
//  __property int DeviceID = {read=FDeviceID, write=SetDeviceID, nodefault};
//  __property System::Classes::TStringList* DeviceList = {read=GetDeviceList, default=0};
//
//__published:
//  __property System::Word Capacity = {read=FCapacity, write=FCapacity, default=1024};
//  __property System::Word SysexBufferSize = {read=FSysexBufferSize, write=SetSysexBufferSize, default=10000};
//  __property System::Word SysexBufferCount = {read=FSysexBufferCount, write=SetSysexBufferCount, default=16};
//  __property bool SysexOnly = {read=FSysexOnly, write=SetSysexOnly, default=0};
//  __property int NumDevs = {read=FNumdevs, nodefault};
//  __property int DeviceID = {read=FDeviceID, write=SetDeviceID, default=0};
//  __property System::UnicodeString ProductName = {read=FProductName, write=SetProductName};
// (Events)
//  __property System::Classes::TNotifyEvent OnMidiInput = {read=FOnMIDIInput, write=FOnMIDIInput};
//  __property System::Classes::TNotifyEvent OnOverflow = {read=FOnOverflow, write=FOnOverflow};
//---------------------------------------------------------------------------
// Midi Output: TMIDI_Device_Output g_midiOut
//
//public:
//  __fastcall virtual TMIDI_Device_Output(System::Classes::TComponent* AOwner);
//  __fastcall virtual ~TMIDI_Device_Output(void);
//  virtual bool __fastcall Open(void);
//  virtual bool __fastcall Close(void);
//  virtual bool __fastcall is_opened(void);
//  virtual bool __fastcall is_closed(void);
//  midioutputState __fastcall Status(void);
//  virtual void __fastcall PutMidiEvent(Msc_definitions::TMIDI_Event* theEvent);
//  virtual void __fastcall PutShort(System::Byte MidiMessage, System::Byte Data1, System::Byte Data2);
//  virtual void __fastcall PutLong(void * TheSysex, System::Word msgLength);
//  void __fastcall SetVolume(System::Word Left, System::Word Right);
//  __property System::Word Error = {read=FError, nodefault};
//  __property int DriverVersion = {read=FDriverVersion, nodefault};
//  __property System::Word MID = {read=FMID, nodefault};
//  __property System::Word PID = {read=FPID, nodefault};
//  __property NativeInt MIDIHandle = {read=FMIDIHandle, nodefault};
//  __property OutPortTech Technology = {read=FTechnology, write=SetTechnology, default=2};
//  __property System::Word Voices = {read=FVoices, nodefault};
//  __property System::Word Notes = {read=FNotes, nodefault};
//  __property System::Word ChannelMask = {read=FChannelMask, nodefault};
//  __property unsigned Support = {read=FSupport, nodefault};
//  __property bool Volume = {read=FVolume, nodefault};
//  __property bool LRVolume = {read=FLRVolume, nodefault};
//  __property bool PatchCache = {read=FPatchCache, nodefault};
//  __property System::Classes::TStringList* DeviceList = {read=GetDeviceList, default=0};
//  __property int NumDevs = {read=FNumdevs, nodefault};
//  __property System::UnicodeString ProductName = {read=FProductName, write=SetProductName};
//
//__published:
//  __property System::Classes::TNotifyEvent OnMIDIOutput = {read=FOnMIDIOutput, write=FOnMIDIOutput};
//---------------------------------------------------------------------------
//Software written by Scott Swift 2016 - This program is distributed under the
//terms of the GNU General Public License.
//---------------------------------------------------------------------------
#include "MainForm.h"
#include <vcl.h>
#pragma hdrstop
// Include header files common to all files before this directive!

#include "RegHelper.h"
#include "PatchForm.h"
#include "SelectPatchForm.h"
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// Event handlers
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    Timer1->OnTimer = NULL;
    Timer1->Enabled = false;

    g_streamCount = 0;
    g_streamPlaying = false;
    g_midiOutDataBeingTransmitted = false;

    g_randInterval = 0;
    g_rxByteCount = 0;
    g_DragDropFilePath = "";
    g_rxTimeout = false;
    g_txTimeout = false;
    g_gpTimeout = false;
    g_inBufferFull = false;
    g_abort = false;
    g_systemBusy = false;
    g_currentPatch = -1;

    // read settings from registry HKEY_CURRENT_USER
    // \\Software\\Discrete-Time Systems\\AkaiS950
    TRegHelper* pReg = NULL;

    try
    {
        try
        {
            pReg = new TRegHelper(true);

            if (pReg != NULL)
            {
                // tell user how to delete reg key if this is first use...
                if (pReg->ReadSetting(S9_REGKEY_VERSION).IsEmpty())
                {
                    pReg->WriteSetting(S9_REGKEY_VERSION, String(VERSION_STR));

                    // cmd reg delete "HKCU\Software\Discrete-Time Systems\AkaiS950" /f
                    printm("This app stores its settings in the windows registry.\r\n"
                        "To delete settings, go to Start => Run and type \"cmd\"\r\n"
                        "In the window type the line below and press enter:\r\n\r\n"
                        "reg delete \"HKCU\\Software\\Discrete-Time Systems\\RolandD50\" /f\r\n"
                        "(or: Start => Run, \"regedit\" and search for \"RolandD50\")\r\n");
                }

                pReg->ReadSetting(S9_REGKEY_MIDI_CHAN, g_midiChan, 0);
                g_midi_inname = pReg->ReadSetting(S9_REGKEY_MIDI_INNAME);
                g_midi_outname = pReg->ReadSetting(S9_REGKEY_MIDI_OUTNAME);
                g_docPath = pReg->ReadSetting(S9_REGKEY_DOC_PATH);
                pReg->ReadSetting(S9_REGKEY_RAND_INTERVAL, g_randInterval, DEF_RAND_INTERVAL);
                pReg->ReadSetting(S9_REGKEY_CURRENT_PATCH, g_currentPatch, DEF_PATCH);

            }
            else
            {
                ShowMessage("Unable to read settings from the registry!");
                g_midiChan = 0;
                g_midi_inname = "";
                g_midi_outname = "";
                g_docPath = "";
                g_randInterval = DEF_RAND_INTERVAL;
                g_currentPatch = DEF_PATCH;
            }
        }
        catch (...)
        {
            ShowMessage("Unable to read settings from the registry!");
            g_midiChan = 0;
            g_midi_inname = "";
            g_midi_outname = "";
            g_docPath = "";
            g_randInterval = DEF_RAND_INTERVAL;
            g_currentPatch = DEF_PATCH;
        }

        if (g_docPath.IsEmpty() || !DirectoryExists(g_docPath))
        {
            // get our ExePath property so we can easily write files when the
            // user presses the spacebar in DataGridForm
            String exePath = ExtractFileDir(Application->ExeName);

            // get DocPath
            TPath *p = new TPath;
            if (p)
            {
                g_docPath = p->GetDocumentsPath();
                delete p;
                if (!DirectoryExists(g_docPath))
                    g_docPath = exePath;

                g_docPath += DIRECTORY_NAME;

                if (!DirectoryExists(g_docPath))
                {
                    try
                    {
                       CreateDir(g_docPath);
                    }
                    catch(...)
                    {
                    }

                    if (!DirectoryExists(g_docPath))
                        g_docPath = exePath;
                }
            }
            else
                g_docPath = exePath;
        }
    }
    __finally
    {
        try { if (pReg != NULL) delete pReg; }
        catch (...) {}
    }

    g_patchForms = new TList; // list of pointers to patch-forms

    SetWorkingDir(g_docPath);

    printm(VERSION_STR);
    printm("Click \"Menu\" and select \"Help\"...\r\n\r\n");
    printm("(Note: This program writes to your D-50's temp-area only and will never overwrite your saved patches!)\n");

    // Create midi In/Out objects and populate device combo-boxes
    MidiDeviceListRefresh();

    //enable drag&drop files
    ::DragAcceptFiles(this->Handle, true);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    if (g_patchForms)
      delete g_patchForms;
    if (g_midiIn)
        delete g_midiIn;
    if (g_midiOut)
        delete g_midiOut;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject *Sender)
{
    Memo1->SetFocus();

    // Try to get temp values from D-50 in 1 second...
    Timer1->Enabled = false;
    Timer1->OnTimer = TimerDemoTimeout;
    Timer1->Interval = 1000;
    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    // save settings to registry HKEY_CURRENT_USER
    // \\Software\\Discrete-Time Systems\\AkaiS950
    TRegHelper* pReg = NULL;

    try
    {
        // delete all the patch forms
        RemoveAllPatchForms();

        CloseMidiIn();
        CloseMidiOut();

        pReg = new TRegHelper(false);

        if (pReg != NULL)
        {
            pReg->WriteSetting(S9_REGKEY_MIDI_CHAN, g_midiChan);
            pReg->WriteSetting(S9_REGKEY_MIDI_INNAME, g_midi_inname);
            pReg->WriteSetting(S9_REGKEY_MIDI_OUTNAME, g_midi_outname);
            pReg->WriteSetting(S9_REGKEY_DOC_PATH, g_docPath);
            pReg->WriteSetting(S9_REGKEY_RAND_INTERVAL, g_randInterval);
            pReg->WriteSetting(S9_REGKEY_CURRENT_PATCH, g_currentPatch);
        }
    }
    __finally
    {
        try { if (pReg != NULL) delete pReg; }
        catch (...) {}
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_ESCAPE)
        g_abort = true;
    else if (Key == VK_DELETE && FileListBox1->Focused())
        DeleteSelectedFile();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Save64IntPatchesClick(TObject *Sender)
{
    ReadPatchesAndSaveTo64Files(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Save64CrdPatchesClick(TObject *Sender)
{
    ReadPatchesAndSaveTo64Files(true);
}
//---------------------------------------------------------------------------
// This reads all 64 patches stored on the Roland D-50 Synth and saves them
// to 64 individual patch-files in subdirectory "PatchSave"
// he's hearing...
void __fastcall TFormMain::ReadPatchesAndSaveTo64Files(bool bCard)
{
    // append all the data-grids
    TStringList* allGrids = NULL;
    TFormPatch* pFormPatch = NULL;

    try
    {
        try
        {
            RemoveAllPatchForms();

            pFormPatch = AddPatchForm(); // make a TPatchForm to use as a scratchpad

            if (!pFormPatch)
            {
                ShowMessage("Unable to add new patch form...");
                return;
            }

            allGrids = new TStringList();

            String fileDir = this->DocPath;

            int pos = fileDir.LowerCase().Pos("\\patchsave\\");

            if (pos <= 0)
                fileDir += "\\PatchSave\\";

            if (!DirectoryExists(fileDir))
                CreateDir(fileDir);

            SetWorkingDir(fileDir);

            // Note: to xfer mmemory-card patches, on D-50 press Data Transfer
            // Crd->Int
            for(int ii = 0; ii < TOTAL_PATCHES_ON_D50; ii++)
            {
                int patchNum = bCard ? ii+TOTAL_PATCHES_ON_D50 : ii;

                PatchChange(patchNum);

                // load D-50 temp-area into data grid and save original values
                if (pFormPatch->GetTempArea(patchNum))
                  Memo1->Clear();
                else
                {
                  RemovePatchForm(pFormPatch);
                  ShowMessage("Problem getting temp-area...");
                  return;
                }

                // save as file
                String filePath;

                String sNew;

                String sName = pFormPatch->PatchName;

                // PatchName is trimmed and set in SetCaptionAndPatchNumberToTabCellValues()

                for (int ii = 1; ii <= sName.Length(); ii++)
                {
                    Char c = sName[ii];
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
                pFormPatch->ReadFromGrid(allGrids);

                if (allGrids->Count)
                {
                    allGrids->SaveToFile(filePath);
                    FileListBox1->Update();
                }
            }
        }
        catch(...)
        {
           ShowMessage("Exception thrown while processing...");
        }
    }
    __finally
    {
        RemovePatchForm(pFormPatch);

        if (allGrids)
            delete allGrids;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuItemSetWorkingDirectoryPathClick(TObject *Sender)
{
    String sDir = g_docPath;
    if (SelectDirectory(sDir,
     (TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt), 0))
        SetWorkingDir(sDir);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerGpTimeout(TObject *Sender)
{
    // used for midi-diagnostic function
    Timer1->Enabled = false;
    g_gpTimeout = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerRxTimeout(TObject *Sender)
{
    Timer1->Enabled = false;
    g_rxTimeout = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerTxTimeout(TObject *Sender)
{
    Timer1->Enabled = false;
    g_txTimeout = true;
}
//---------------------------------------------------------------------------
// this is triggered when the main form is shown
void __fastcall TFormMain::TimerDemoTimeout(TObject *Sender)
{
    Timer1->Enabled = false;

    if (!IsD50Connected())
        printm("\r\nDid not detect your D-50 - is it on and hooked-up?"
                     "\r\nAre the midi devices and channel correct?"
                     "\r\n(Click \"Menu->Read temp area\" to retry!)\r\n");
    else
    {
        MenuSetBasePatchClick(NULL);
//        Memo1->Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerFileDrop(TObject *Sender)
{
    if (SystemBusy)
        return;

    if (IsPlaying)
        CloseMidiOut();

    Timer1->Enabled = false;
    if (!g_DragDropFilePath.IsEmpty())
    {
        // Do something with file-path here...
        g_DragDropFilePath = "";
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonRefreshDevsClick(TObject *Sender)
{
    // clear global strings so we start fresh...
    g_midi_outname = "";
    g_midi_inname = "";

    MidiDeviceListRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBoxMidiInChange(TObject *Sender)
{
    if (g_midiIn)
    {
        // g_midiIn->DeviceList->Objects[x] has our actual ID (could be -1 for
        // MIDI_MAPPER)
        int idx = ComboBoxMidiIn->ItemIndex;
        if (idx >= 0 && idx < g_midiIn->DeviceList->Count)
        {
            int id = (int)g_midiIn->DeviceList->Objects[idx];
            g_midiIn->DeviceID = id;
            g_midi_inname = g_midiIn->DeviceList->Strings[idx];
            Memo1->SetFocus();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBoxMidiOutChange(TObject *Sender)
{
    if (g_midiOut)
    {
        // g_midiIn->DeviceList->Objects[x] has our actual ID (could be -1 for
        // MIDI_MAPPER)
        int idx = ComboBoxMidiOut->ItemIndex;
        if (idx >= 0 && idx < g_midiOut->DeviceList->Count)
        {
            int id = (int)g_midiOut->DeviceList->Objects[idx];
            g_midiOut->DeviceID = id;
            g_midi_outname = g_midiOut->DeviceList->Strings[idx];
            Memo1->SetFocus();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBoxMidiChanChange(TObject *Sender)
{
    g_midiChan = ComboBoxMidiChan->ItemIndex;
    Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PopupMenuItemOpenClick(TObject *Sender)
{
    MenuOpenFileClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FileListBox1DblClick(TObject *Sender)
{
    MenuOpenFileClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuOpenFileClick(TObject *Sender)
{
    TFormPatch* pPatchForm = AddPatchForm();

    if (pPatchForm)
        pPatchForm->LoadPatchFileIntoD50AndDataGrid(FileListBox1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PopupMenuItemDeleteClick(TObject *Sender)
{
    DeleteSelectedFile();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuSetBasePatchClick(TObject *Sender)
{
    LoadPatchFromD50(true); // allow memory card
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadPatchFromD50(bool bAllowCard)
{
  // Send Patch Change control-message to the D-50
  Application->CreateForm(__classid(TFormSelectPatch), &FormSelectPatch);
  FormSelectPatch->AllowCard = bAllowCard;
  FormSelectPatch->Patch = g_currentPatch;
  int patch = -1;
  if (FormSelectPatch->ShowModal() == mrOk)
    patch = FormSelectPatch->Patch;
  FormSelectPatch->Release();

  if (patch >= 0)
  {
    TFormPatch* pFormPatch = AddPatchForm();

    if (pFormPatch)
    {
      PatchChange(patch);

      // load D-50 temp-area into data grid and save original values
      if (pFormPatch->GetTempArea(patch))
        Memo1->Clear();
      else
      {
        RemovePatchForm(pFormPatch);
        return;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RemoveAllPatchForms(void)
{
    if (!g_patchForms) return;

    int count = g_patchForms->Count;

    // delete each form in the list
    for (int ii = 0; ii < count; ii++)
    {
      TFormPatch* f = reinterpret_cast<TFormPatch*>(g_patchForms->Items[ii]);
      if (f)
        delete f; // delete the form
    }

    // delete the pointers in the list
    g_patchForms->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RemovePatchForm(TFormPatch *p)
{
    if (!p || !g_patchForms || g_patchForms->Count == 0)
      return;

    int idx = g_patchForms->IndexOf(p);
    if (idx >= 0)
    {
        TFormPatch* f = reinterpret_cast<TFormPatch*>(g_patchForms->Items[idx]);
        if (f)
          delete f; // delete the form
//          f->Release(); // delete the form
        g_patchForms->Delete(idx); // remove its pointer from list
    }
}
//---------------------------------------------------------------------------
TFormPatch * __fastcall TFormMain::AddPatchForm(void)
{
    // create a new patch form
    TFormPatch* f = NULL;
    try
    {
      f = new TFormPatch(this);

      // add new form's pointer to our list
      if (f)
        g_patchForms->Add(f);
    }
    catch(...){}

    return f;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuGetTempAreaClick(TObject *Sender)
{
    TFormPatch* pFormPatch = AddPatchForm();
    if (pFormPatch)
    {
      // load D-50 temp-area into data grid and save original values
      if (pFormPatch->GetTempArea(g_currentPatch))
        Memo1->Clear();
      else
        RemovePatchForm(pFormPatch);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuAboutClick(TObject *Sender)
{
    Memo1->Lines->Clear();
    printm("Roland D-50 Designer by Scott Swift (dxzl@live.com)");
}
//---------------------------------------------------------------------------
//System::Classes::TNotifyEvent OnMIDIOutput
void __fastcall TFormMain::OnMidiOutputHandler(TObject *Sender)
{
    // NOTE: don't want to do this when streaming out sysex as multiple
    // SendStream() calls!
    if(g_streamCount)
        if (--g_streamCount == 0)
            CloseMidiOut();

    g_streamPlaying = false;
    g_midiOutDataBeingTransmitted = false;
}
//---------------------------------------------------------------------------
//System::Classes::TNotifyEvent OnMidiInput
void __fastcall TFormMain::OnMidiInputHandler(TObject *Sender)
{
    if (!g_midiIn)
        return;
    try
    {
        int messageCount = g_midiIn->MessageCount;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//        printm("MessageCount: " + String(messageCount));

        int byteCount = g_rxByteCount; // start with what we have so-far from previous packets

        Byte *destptr = g_midiInputBuffer+byteCount;

        for (int ii = 0; ii < messageCount; ii++)
        {
            TMIDI_Event* midiEvent = g_midiIn->GetMidiEvent();

            //    printm("Type: 0x" + IntToHex(midiEvent->Event_Type, 2) +
            //        ", Data1: 0x" + IntToHex(midiEvent->Data_Byte_1, 2) +
            //        ", Data2: 0x" + IntToHex(midiEvent->Data_Byte_2, 2));

            int tempLength = midiEvent->SysexLength;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//            printm("SysExLen: " + String(midiEvent->SysexLength));

            if (byteCount+tempLength > MIDIINBUFSIZE)
            {
                g_inBufferFull = true;
                printm("Combined message-length too large for TempArray! (Combined SysExLen: " +
                    String(tempLength+byteCount) + ", MIDIINBUFSIZE: " + String(MIDIINBUFSIZE) + ")");
            }
            else
            {
                Byte *sourceptr = midiEvent->Sysex;

                // concatenate divided-sysex messages together
                for (int jj = 0; jj < tempLength; jj++)
                    *destptr++ = *sourceptr++;

                midiEvent->Free();

                // set the global receive byte-count
                // (waiting for this in receive() and
                // calling Application->ProcessMessages())
                byteCount += tempLength;
            }
        }
        g_rxByteCount = byteCount;
    }
    catch(...)
    {
        g_inBufferFull = true;
        printm("error in OnMidiInputHandler()!");
    }
}
//---------------------------------------------------------------------------
//System::Classes::TNotifyEvent OnOverflow
void __fastcall TFormMain::OnMidiDriverCircBufOverflowHandler(TObject *Sender)
{
    // this event occurs when the low-level circular-buffer overflows
    // it has nothing to do with buf or g_byteCount
    printm("MIDI driver circular-buffer overflow!");
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::WMDropFile(TWMDropFiles &Msg)
{
    try
    {
        //get dropped files count
        int cnt = ::DragQueryFileW((HDROP)Msg.Drop, -1, NULL, 0);

        if (cnt != 1)
            return; // only one file!

        wchar_t wBuf[MAX_PATH];

        // Get first file-name
        if (::DragQueryFileW((HDROP)Msg.Drop, 0, wBuf, MAX_PATH) > 0)
        {
            // Load and convert file as per the file-type (either plain or rich text)
            WideString wFile(wBuf);

            // don't process this drag-drop until previous one sets g_DragDropFilePath = ""
            if (g_DragDropFilePath.IsEmpty() && !wFile.IsEmpty())
            {
                String sFile = String(wFile);
                if (FileExists(sFile))
                {
                    g_DragDropFilePath = sFile;
                    Timer1->Interval = 50;
                    Timer1->OnTimer = TimerFileDrop; // set handler
                    Timer1->Enabled = true; // fire event to send file
                }
            }
        }
    }
    catch (...) {}
}
//---------------------------------------------------------------------------
// End of event handlers
//---------------------------------------------------------------------------
// public
void __fastcall TFormMain::SetWorkingDir(String sDir)
{
    String sCap = "Roland D-50: \"";
    int len = sDir.Length();

    if (len > 60)
        sCap += "..." + sDir.SubString(len-60+1, 60);
    else
        sCap += sDir;

    sCap += "\"";

    this->Caption = sCap;

    g_docPath = sDir;
    FileListBox1->Directory = g_docPath; // populate our files box
    FileListBox1->Update();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DeleteSelectedFile(void)
{
    int idx = FileListBox1->ItemIndex;
    int count = FileListBox1->Count;

    if (!count || idx < 0 || idx >= count)
        return;

    String sName = FileListBox1->Items->Strings[idx];
    if (FileExists(sName))
    {
        if (DeleteFile(sName))
        {
            FileListBox1->DeleteSelected();

            if (FileListBox1->Count > 0)
            {
                if (idx >= FileListBox1->Count)
                    idx--;

                FileListBox1->ItemIndex = idx;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    TEdit* p = reinterpret_cast<TEdit*>(Sender);
    if (!p)
      return;

    if (Key == VK_RETURN)
    {
      int idx = FileListBox1->ItemIndex;
      int count = FileListBox1->SelCount;

      if (count != 1 || idx < 0 || idx >= count)
          return;

      String newName = p->Text;
      String sName = FileListBox1->Items->Strings[idx];
      if (FileExists(sName) && !FileExists(newName))
      {
        if (!RenameFile(sName, newName))
          ShowMessage("Invalid name...");
        else
          FileListBox1->Items->Strings[idx] = newName;
      }
    }
}
//---------------------------------------------------------------------------
// sysExOnly defaults true
// set bufferSize and/or bufferCount 0 to allow the defaults and receive normal SysEx
// complete messages (16 buffers of 4096 bytes each)
void __fastcall TFormMain::OpenMidiIn(int bufferSize, int bufferCount, bool sysExOnly)
{
    if (g_midiIn->is_opened())
        g_midiIn->Close();

    // S.S.To receive sysex blocks that you need before the EEX comes in, you
    // set the SysexBufferSize property to the size of the block you expect,
    // and you will get a normal input-event generated when the buffer is full.
    // Set this size prior to opening. Then you have to close/re-open to change
    // the size...
    if (bufferSize != 0)
        g_midiIn->SysexBufferSize = bufferSize;
    if (bufferCount != 0)
        g_midiIn->SysexBufferCount = bufferCount;

    g_midiIn->Capacity = DefMidiInCircBufSize; // default is 1024

    g_midiIn->SysexOnly = sysExOnly;

    g_midiIn->Open();

    g_rxTimeout = false;
    g_inBufferFull = false;
    g_abort = false;

    g_rxByteCount = 0; // clear the receive byte-count

    g_midiIn->Start();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CloseMidiIn(void)
{
    if (g_midiIn->is_opened())
    {
        g_midiIn->Stop();
        g_midiIn->Close();
        g_rxTimeout = false;
        g_inBufferFull = false;
        g_abort = false;
    }
}
//---------------------------------------------------------------------------
// bStream defaults false
void __fastcall TFormMain::OpenMidiOut(bool bStream)
{
    if (!g_midiOut)
        return;
      
    if (g_midiOut->is_opened())
        CloseMidiOut(); // stop old stream and close...

    // start fresh
    g_midiOut->Stream = bStream;
    g_midiOut->Open();
    g_txTimeout = false;
    g_midiOutDataBeingTransmitted = false;
    g_streamPlaying = false;
    g_streamCount = 0;
    g_abort = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CloseMidiOut(void)
{
    if (!g_midiOut || !g_midiOut->is_opened())
        return;

    if (g_streamPlaying)
    {
        g_midiOut->StreamStop();
        g_streamPlaying = false;
        g_streamCount = 0;
    }

    g_midiOut->Close();
    g_txTimeout = false;
    g_midiOutDataBeingTransmitted = false;
    g_abort = false;
}
//---------------------------------------------------------------------------
// overloaded...

void __fastcall TFormMain::PatchChange(void)
{
    PatchChange(g_currentPatch);
}

void __fastcall TFormMain::PatchChange(int patch)
{
    if (!g_midiOut || SystemBusy)
        return;

    bool bWasOpen = g_midiOut->is_opened();

    if (!bWasOpen)
        OpenMidiOut(g_streamPlaying);

    if (g_streamPlaying)
    {
        g_midiOut->StreamStop();
        g_streamPlaying = false;
    }

    g_midiOut->PutShort(0xC0 | g_midiChan, patch, 0);

    if (!bWasOpen)
        CloseMidiOut();

    if (g_currentPatch != patch)
        g_currentPatch = patch;

    // put some delay between successive calls to this!
    // 35ms was too little...
    DelayGpTimer(100);
}
//---------------------------------------------------------------------------
// Master Volume
// controller 7
void __fastcall TFormMain::SetSysExMasterVolume(UInt16 vol)
{
    if (!g_midiOut)
        return;

    g_midiOut->PutShort(0x07, (Byte)((vol>>7) & 0x7f), (Byte)(vol & 0x7f));
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::printm(String message)
{
    Memo1->Lines->Add(message);
}
//---------------------------------------------------------------------------
String __fastcall TFormMain::GetFileName(void)
{
    OpenDialog1->Title = "Send .wav or .aki file to S900/S950";
    OpenDialog1->DefaultExt = "aki";
    OpenDialog1->Filter = "Aki files (*.aki)|*.aki|" "Wav files (*.wav)|*.wav|"
        "All files (*.*)|*.*";
    OpenDialog1->FilterIndex = 3; // start the dialog showing all files
    OpenDialog1->Options.Clear();
    OpenDialog1->Options << ofHideReadOnly
        << ofPathMustExist << ofFileMustExist << ofEnableSizing;

    if (!OpenDialog1->Execute())
        return ""; // Cancel

    String sFileName = OpenDialog1->FileName;

    return sFileName;
}
//---------------------------------------------------------------------------
// chan defaults to 0 (midi channel 1)
void __fastcall TFormMain::exmit(int samp, int mode)
{
    Byte midistr[8];

    midistr[0] = BEX;
    midistr[1] = ROLAND_ID;
    midistr[2] = g_midiChan; // midi channel
    midistr[3] = (Byte)mode;
    midistr[4] = D50_ID;
    midistr[5] = (Byte)samp;
    midistr[6] = 0;
    midistr[7] = EEX;

    comws(8, midistr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::comws(int count, unsigned char* ptr)
{
#if !TESTING

    try
    {
        Timer1->Enabled = false; // stop timeout timer (should already be stopped)
        Timer1->OnTimer = TimerTxTimeout; // set handler
        this->g_txTimeout = false;

        // NOTE: In the case of sending midi, the driver buffers what we send
        // with PutLong() - an event handler in this file clears g_midiOutDataBeingTransmitted
        // after the data is sent. So then we wait up to 4 seconds for that flag
        // to clear when we try sending the next batch of output data...
        if (!g_midiOut)
            return false;

        Timer1->Interval = TXMIDITIMEOUT; // 5.1 seconds (timeout for all the bytes to be sent!)
        Timer1->Enabled = true; // start timeout timer

        while(g_midiOutDataBeingTransmitted)
        {
            Application->ProcessMessages();

            if (g_txTimeout)
            {
                printm("midi transmit timeout!");
                return false;
            }
        }

        try
        {
            g_midiOutDataBeingTransmitted = true; // this is reset to false in OnMidiOutputHandler()

            // clear g_rxByteCount before requesting data because for midi,
            // OnMidiInput() could set it any time, but we want to clear the
            // previous data received count before calling receive().
            g_rxByteCount = 0;

            g_midiOut->PutLong(ptr, count);
        }
        catch(...)
        {
            printm("error sending midi system-exclusive message!");
            return false;
        }
    }
    __finally
    {
        Timer1->Enabled = false;
        Timer1->OnTimer = NULL; // clear handler
        g_txTimeout = false;
// don't want to do this!!!!!!!!!!!
//        g_midiOutDataBeingTransmitted = false;
    }

#endif

    return true;
}
//---------------------------------------------------------------------------
int __fastcall TFormMain::receive(int count)
// set count 0 to receive a complete message (EEX required)
// set count -1 to receive a partial message of unknown size
// set "count" to return either when a specific # bytes is received
//  or when EEX is received
//
// returns 0 if success, 1 if failure, 2 if buffer overrun
{
    // don't want to clear g_rxByteCount here for midi-in since at this point,
    // we have already sent a request to the remote midi device and it may be
    // responding as we speak, and setting g_rxByteCount...
    //
    // So where do we clear it?
    //
    // Best place is just before calling g_midiOut->PutLong(ptr, count) in comws,
    // set g_rxByteCount = 0! This is ok since everything we do is "ask first
    // then listen".
    //
    // g_rxByteCount = 0;

    g_rxTimeout = false;
    g_abort = false;
    g_inBufferFull = false;

    Timer1->Enabled = false; // stop timer (just in-case!)
    Timer1->Interval = RXTIMEOUT; // 3.1 seconds
    Timer1->OnTimer = TimerRxTimeout; // set handler
    Timer1->Enabled = true; // start timeout timer

    try
    {
        for (;;)
        {
            if (g_abort)
            {
                printm("receive aborted by user!");
                break;
            }

            Application->ProcessMessages(); // need this to detect the timeout

            // g_inBufferFull is set in OnMidiInputHandler
            if (g_inBufferFull)
            {
                printm("midi receive buffer full!");
                return 2;
            }

            // for midi-in we wait for OnMidiInputHandler to store a sysex message
            // (or part of one) in TempArray
            //
            // we return 0 (success) if the user set count to 0 (to receive
            // a complete sysex message) and we got 1 or more bytes
            // and the last byte is EEX or...
            //
            // if count was set to -1, accept whatever came in, but only after the
            // timeout
            if (g_rxByteCount > 0)
            {
                // last byte in buffer is EEX, we have our message!
                if ((count == 0 && g_midiInputBuffer[g_rxByteCount-1] == EEX) ||
                       (count > 0 && g_rxByteCount >= (UInt32)count) ||
                                (count == -1 && g_rxTimeout))
                {
#if TESTING_DISPLAY_RX_HEX
                    display_hex(TempArray, g_rxByteCount);
#endif

                    return 0;
                }
            }

            if (g_rxTimeout)
                break;
        }
    }
    __finally
    {
        Timer1->Enabled = false;
        Timer1->OnTimer = NULL; // clear handler
    }

    return 1; // timeout
}
//---------------------------------------------------------------------------
Byte __fastcall TFormMain::roland_checksum(unsigned char* buf, int offsetofchecksum)
{
    int sum = 0;

    for (int ii = 5; ii < offsetofchecksum; ii++)
        sum += buf[ii];
    return ((~sum + 1) & 0x7f);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::roland_d50_send_ack(int mode)
{
    Byte midistr[6];

    midistr[0] = BEX;
    midistr[1] = ROLAND_ID; // roland
    midistr[2] = g_midiChan; // channel
    midistr[3] = D50_ID; // D-50
    midistr[4] = (unsigned char)mode;
    midistr[5] = EEX;

    comws(6, midistr);
}
//---------------------------------------------------------------------------
//void __fastcall TFormMain::roland_d50_request_patch_1_1(void)
//{
//    Byte midistr[13];
//
//    midistr[0] = 0xf0;
//    midistr[1] = 0x41; // roland
//    midistr[2] = g_midiChan; // channel
//    midistr[3] = 0x14; // D-50
//    midistr[4] = 0x41; // RQD request data command (WSD want to send data is 0x40)
//    // checksum is two's compliment of the sum of the next 6 bytes...
//    midistr[5] = 0x02; // addr high (patch 1-1)
//    midistr[6] = 0x00; // addr mid
//    midistr[7] = 0x00; // addr low
//    midistr[8] = 0x00; // size high (448 bytes)
//    midistr[9] = 0x03; // size mid
//    midistr[10] = 0x40; // size low
//    // to here...
//    midistr[11] = roland_checksum(midistr, 11); // 0x3B; // checksum
//    midistr[12] = 0xf7;
//
//    comws(13, midistr);
//}
//---------------------------------------------------------------------------
// display data obtained via receive()
void __fastcall TFormMain::display_hex(Byte buf[])
{
    String sTemp;
    for (unsigned int ii = 0; ii < g_rxByteCount; ii++)
    {
        if ((ii % 16) == 0)
        {
            if (!sTemp.IsEmpty())
            {
                printm(sTemp);
                sTemp = "";
            }
        }
        sTemp += IntToHex((int)buf[ii], 2) + " ";
    }
    // print what remains...
    if (!sTemp.IsEmpty())
        printm(sTemp);
}
//---------------------------------------------------------------------------
//void __fastcall TFormMain::GetTempArea()
//{
//    Memo1->Clear();
//
//    // Midi input standard-event (note on/off Etc.) Rx test
//    // Select get list of catalog entries in the main menu - press ESC key to quit
//    if (!g_midiIn || !g_midiOut)
//    {
//        printm("no midi device!");
//        return;
//    }
//
//    try
//    {
//        OpenMidiOut();
//        OpenMidiIn(4096, 2, true);
//
//        // Clear data-grid TStringGrid(s)
//        for (int ii = 0; ii < TOTAL_TABS; ii++)
//            FormPatch->InitDataGrid(ii);
//
//        // roland sends back a partial sysex block with 256 data bytes and 10 head/tail bytes
//        // BEX, Roland ID, midi chan, D-50 ID, command, 3-byte address
//        //roland_d50_request_patch_1_1(); // request sysex patch 1-1 from Roland D-50
//
////        // -----------------------------------------------------------------
////        // this prints out all the temp data sending ACK after first 256+10
////        // bytes to get the remaining data...
////        // -----------------------------------------------------------------
////        if (roland_d50_get_temp_area(0x0000, 0x0340)) // all temp data
////        {
////            printm("upper partial 1");
////            display_hex();
////        }
////
////        // to get 448+10+10 total bytes, call this
////        roland_d50_send_ack(R_ACK);
////        receive(0);
////        display_hex();
//        // -----------------------------------------------------------------
//
//        // -----------------------------------------------------------------
//        // this prints out all the temp data in 64+10 byte segments, no ACK
//        // needed since requested size, 64, is <= 256
//        // -----------------------------------------------------------------
//        if (roland_d50_get_temp_area(ROLANDADDRESS[0])) // upper partial 1
//        {
//            printm("upper partial 1");
//            display_hex();
//            FormPatch->WriteToGrid(0, &TempArray[8]);
//        }
//        else
//            return;
//
//        if (roland_d50_get_temp_area(ROLANDADDRESS[1])) // upper partial 2
//        {
//            printm("upper partial 2");
//            display_hex();
//            FormPatch->WriteToGrid(1, &TempArray[8]);
//        }
//        else
//            return;
//
//        if (roland_d50_get_temp_area(ROLANDADDRESS[2])) // upper common
//        {
//            printm("upper common");
//            display_hex();
//            FormPatch->WriteToGrid(2, &TempArray[8]);
//        }
//        else
//            return;
//
//        if (roland_d50_get_temp_area(ROLANDADDRESS[3])) // lower partial 1
//        {
//            printm("lower partial 1");
//            display_hex();
//            FormPatch->WriteToGrid(3, &TempArray[8]);
//        }
//        else
//            return;
//
//        if (roland_d50_get_temp_area(ROLANDADDRESS[4])) // lower partial 2
//        {
//            printm("lower partial 2");
//            display_hex();
//            FormPatch->WriteToGrid(4, &TempArray[8]);
//        }
//        else
//            return;
//
//        if (roland_d50_get_temp_area(ROLANDADDRESS[5])) // lower common
//        {
//            printm("lower common");
//            display_hex();
//            FormPatch->WriteToGrid(5, &TempArray[8]);
//        }
//        else
//            return;
//
//        if (roland_d50_get_temp_area(ROLANDADDRESS[6])) // patch
//        {
//            printm("patch");
//            display_hex();
//            FormPatch->WriteToGrid(6, &TempArray[8]);
//
//            // Test of read/write
////            FormPatch->ReadData(6, &TempArray[8]);
////            display_hex();
////            FormPatch->ClearTab(6);
////            FormPatch->WriteData(6, &TempArray[8]);
//        }
//
//        FormPatch->Visible = true;
//    }
//    __finally
//    {
//        CloseMidiIn();
//        CloseMidiOut();
//    }
//}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::D50GetTempArea(unsigned __int16 addr,
                                   Byte *buf, unsigned __int16 size)
{
    try
    {
        Byte midistr[13];

        midistr[0] = BEX;
        midistr[1] = ROLAND_ID; // roland
        midistr[2] = g_midiChan; // channel
        midistr[3] = D50_ID; // D-50
        midistr[4] = R_RQ1; // RQ1 request data command
        // checksum is two's compliment of the sum of the next 6 bytes...
        midistr[5] = 0x00; // addr high (patch 1-1)
        midistr[6] = (unsigned char)(addr >> 8); // addr mid
        midistr[7] = (unsigned char)addr; // addr low

        midistr[8] = 0x00; // size high (448 bytes)
        midistr[9] = (unsigned char)(size >> 8); // addr mid
        midistr[10] = (unsigned char)size; // addr low

        // to here...
        midistr[11] = roland_checksum(midistr, 11); // 0x3D; // checksum
        midistr[12] = EEX;

        if (!comws(13, midistr))
        {
            printm("error sending midi!");
            return false;
        }

        if (receive(0))
        {
            printm("error receiving midi!");
            return false;
        }

        // copy data
        if (g_rxByteCount)
            memmove(buf, g_midiInputBuffer, g_rxByteCount);

        return true;
    }
    catch(...)
    {
        return false;
    }
}
////---------------------------------------------------------------------------
//void __fastcall TFormMain::PutTempArea(void)
//{
//    // Midi input standard-event (note on/off Etc.) Rx test
//    // Select get list of catalog entries in the main menu - press ESC key to quit
//    if (!g_midiIn || !g_midiOut)
//    {
//        printm("no midi device!");
//        return;
//    }
//
//    try
//    {
//        OpenMidiOut();
//
//        FormPatch->ReadDataFromGrid(0, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[0])) // upper partial 1
//        {
//            printm("wrote upper partial 1");
//            display_hex();
//        }
//        else
//            return;
//
//        FormPatch->ReadDataFromGrid(1, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[1])) // upper partial 2
//        {
//            printm("wrote upper partial 2");
//            display_hex();
//        }
//        else
//            return;
//
//        FormPatch->ReadDataFromGrid(2, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[2])) // upper common
//        {
//            printm("wrote upper common");
//            display_hex();
//        }
//        else
//            return;
//
//        FormPatch->ReadDataFromGrid(3, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[3])) // lower partial 1
//        {
//            printm("wrote lower partial 1");
//            display_hex();
//        }
//        else
//            return;
//
//        FormPatch->ReadDataFromGrid(4, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[4])) // lower partial 2
//        {
//            printm("wrote lower partial 2");
//            display_hex();
//        }
//        else
//            return;
//
//        FormPatch->ReadDataFromGrid(5, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[5])) // lower common
//        {
//            printm("wrote lower common");
//            display_hex();
//        }
//        else
//            return;
//
//        FormPatch->ReadDataFromGrid(6, &TempArray[8]);
//        if (roland_d50_put_temp_area(ROLANDADDRESS[6])) // patch
//        {
//            printm("wrote patch");
//            display_hex();
//
//            // Test of read/write
////            FormPatch->ReadData(&TempArray[8], 6);
////            display_hex();
////            FormPatch->ClearTab(6);
////            FormPatch->WriteData(&TempArray[8], 6);
//        }
//        else
//            return;
//    }
//    __finally
//    {
//        CloseMidiOut();
//    }
//}
//---------------------------------------------------------------------------
// adds midi header and does checksum around "size" data bytes for buf
// then transmits the sysex message (up to 256 bytes max starting at "addr")
//
// we generally send the default 64-bytes which corresponds to the
// section-length in a D-50 patch
bool __fastcall TFormMain::D50PutTempArea(unsigned __int16 addr, Byte *buf,
                                                    unsigned __int16 size)
{
    try
    {
        buf[0] = BEX;
        buf[1] = ROLAND_ID; // roland
        buf[2] = g_midiChan; // channel
        buf[3] = D50_ID; // D-50
        buf[4] = R_DT1; // DT1 one-way data-set
        // checksum is two's compliment of the sum of the next 6 bytes...
        buf[5] = 0x00; // addr high (patch 1-1)
        buf[6] = (unsigned char)(addr >> 8); // addr mid
        buf[7] = (unsigned char)addr; // addr low
        //
        // "data" of "size" bytes should be located here in buf already!
        //
        // now, on to the sysex footer...
        size += 8;
        buf[size] = roland_checksum(buf, size); // 0x3D; // checksum
        size++;
        buf[size] = EEX;
        size++;

        if (!comws(size, buf))
        {
            printm("error sending midi!");
            return false;
        }
    }
    __finally
    {
    }

    DelayGpTimer(35); // put some delay between successive calls to this!

    return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MidiDeviceListRefresh(void)
{
    if ( (g_midiOut && g_midiOut->is_opened()) ||
                    (g_midiIn && g_midiIn->is_opened()) )
        return;
        
    int foundOutIndex = -1;
    int foundInIndex = -1;

    // Get midi devices
    if (!g_midiOut)
        g_midiOut = new TMIDI_Device_Output(this);

    if (!g_midiOut)
    {
        ShowMessage("Unable to create TMidiOutput class!");
        return;
    }

    if (!g_midiIn)
        g_midiIn = new TMIDI_Device_Input(this);

    if (!g_midiIn)
    {
        ShowMessage("Unable to create TMidiInput class!");
        return;
    }

    g_rxTimeout = false;
    g_inBufferFull = false;

    g_midiIn->OnMidiInput = OnMidiInputHandler;
    g_midiIn->OnOverflow = OnMidiDriverCircBufOverflowHandler;

    // note: list-object are deleted when "delete g_midiOut" is called
    // when FormDestroy is called
    TStringList *slIn = g_midiIn->DeviceList;

    ComboBoxMidiIn->Clear();

    if (slIn->Count > 0)
    {
        // add items to input combobox
        for (int ii = 0; ii < slIn->Count; ii++)
        {
            String s = slIn->Strings[ii];
            ComboBoxMidiIn->Items->Add(s);
            if (s == g_midi_inname)
                foundInIndex = ii;
        }
    }
    else
    {
        //g_midiIn->DeviceID = 0; leave at default????

        ComboBoxMidiIn->ItemIndex = -1;

        printm("no midi input device was found!");
    }

    g_txTimeout = false;
    g_midiOutDataBeingTransmitted = false;
    g_streamPlaying = false;

    g_midiOut->OnMIDIOutput = OnMidiOutputHandler;

    // note: list-object are deleted when "delete g_midiOut" is called
    // when FormDestroy is called
    TStringList *slOut = g_midiOut->DeviceList;

    ComboBoxMidiOut->Clear();

    if (slOut->Count > 0)
    {
        // add items to output combobox
        for (int ii = 0; ii < slOut->Count; ii++)
        {
            String s = slOut->Strings[ii];
            ComboBoxMidiOut->Items->Add(s);
            if (s == g_midi_outname)
                foundOutIndex = ii;
        }
    }
    else
    {
        // g_midiOut->DeviceID = 0; leave at default????

        ComboBoxMidiOut->ItemIndex = -1;

        printm("no midi output device was found!");
    }

    // try to set same device for in/out of either of user's saved strings not
    // in the registry
    if (foundInIndex == -1 || foundOutIndex == -1)
        SetMidiInOutToSameDevice();
    else
    {
        if (slIn->Count)
        {
            // use first item in list if user's old setting not found
            foundInIndex = 0;

            // try to find our user's stored registry string in the in-list
            g_midiIn->DeviceID = (Int32)slIn->Objects[foundInIndex];
            ComboBoxMidiIn->ItemIndex = foundInIndex;
        }

        if (slOut->Count)
        {
            // use middi-mapper if user's old setting not found and
            // only one item to choose from
            if (foundOutIndex == -1)
                foundOutIndex = slOut->Count > 1 ? 1 : 0;

            g_midiOut->DeviceID = (Int32)slOut->Objects[foundOutIndex];
            ComboBoxMidiOut->ItemIndex = foundOutIndex;
        }
    }

    // set global registry vars
    g_midi_inname = (ComboBoxMidiIn->ItemIndex >= 0) ? ComboBoxMidiIn->Text : String("");
    g_midi_outname = (ComboBoxMidiOut->ItemIndex >= 0) ? ComboBoxMidiOut->Text : String("");

    ComboBoxMidiChan->ItemIndex = g_midiChan;

    g_abort = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetMidiInOutToSameDevice(void)
{
    // set first midi-in/midi-out devices that are the same
    // unless
    if (g_midiOut && g_midiIn)
    {
        int inCount = g_midiIn->DeviceList->Count;
        int outCount = g_midiOut->DeviceList->Count;

        if (inCount && outCount)
        {
            String sIn, sOut;

            for (int ii = 0; ii < inCount; ii++)
            {
                sIn = g_midiIn->DeviceList->Strings[ii];
                for (int jj = 0; jj < outCount; jj++)
                {
                    sOut = g_midiOut->DeviceList->Strings[jj];

                    if (sIn == sOut)
                    {
                        g_midiIn->DeviceID = (Int32)g_midiIn->DeviceList->Objects[ii];
                        ComboBoxMidiIn->ItemIndex = ii;
                        g_midiOut->DeviceID = (Int32)g_midiOut->DeviceList->Objects[jj];
                        ComboBoxMidiOut->ItemIndex = jj;
                        break;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DelayGpTimer(int time)
{
    g_systemBusy = true;
    StartGpTimer(time);
    while (!IsGpTimeout())
        Application->ProcessMessages();
    StopGpTimer();
    g_systemBusy = false;
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::IsGpTimeout(void)
{
    return g_gpTimeout;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::StopGpTimer(void)
{
    Timer1->Enabled = false;
    Timer1->OnTimer = NULL;
    g_gpTimeout = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::StartGpTimer(int time)
{
    Timer1->Enabled = false;
    Timer1->OnTimer = TimerGpTimeout;
    Timer1->Interval = time;
    Timer1->Enabled = true;
    g_gpTimeout = false;
}
//---------------------------------------------------------------------------
// default timeDiv = 96 ticks/beat (a beat is a quarter-note), default tempo = 500000,
// the time signature is 4/4 and the tempo is 120 beats per minute,
// tempo is expressed as a 24-bit number that designates microseconds per quarter-note,
// a tempo of 100 bpm would be 600000 microseconds per quarter note.
//
// so in a midi-sequence, the delta-time value for 1 beat = 96,
// a dotted quarter-note is 1.5 beats = 144, etc.
// (the ticks/beat in newer sequencer software is 480 ticks/beat, not 96)
//
// (60*1000000)/120 = 500000 (default tempo or "time between events")
//
// So to get delta-time units in ms, we set timeDiv 1000 and tempo 1000000.
void __fastcall TFormMain::PlayStream(unsigned long *pSequence, int size,
                                                    int timeDiv, int tempo)
{
    if (!g_midiOut)
        return;

    // if already playing stop
    if (g_streamPlaying)
    {
        g_midiOut->StreamStop();
        g_streamPlaying = false;
        g_streamCount = 0;
    }

    // put the sequence in a buffer so we can change the midi-channel on
    // all note evenes
    unsigned long *buf = NULL;
    try
    {
        // put the sequence in a buffer so we can change the midi-channel on
        // all note evenes
        int ulCount = size/sizeof(unsigned long);
        buf = new unsigned long[ulCount];
        unsigned long val;

        for (int ii = 0; ii < ulCount; ii++)
        {
            val = pSequence[ii];

            if (ii >= 8 && (ii % 3) == 1)
                buf[ii] = val | g_midiChan;
            else
                buf[ii] = val;
        }

        g_streamCount = 1;
        SendStream(buf, size, timeDiv, tempo);
    }
    __finally
    {
        if (buf) delete [] buf;
    }
}
//---------------------------------------------------------------------------
// size is the size of the entite sequence in bytes
// NOTE: prior to calling this, set g_streamCount = total # parts in the stream
// (set 0 if you don't want to call CloseMidiOut() from end-of-stream
// event-handler)
bool __fastcall TFormMain::SendStream(unsigned long *pSequence, int size,
                                                    int timeDiv, int tempo)
{
    if (!g_midiOut || SystemBusy)
        return false;

    if (IsPlaying)
        CloseMidiOut();

    try
    {
        // if opened in the wrong mode, close (then re-open)
        if (g_midiOut->is_opened() && !g_midiOut->Stream)
            CloseMidiOut();

        if (!g_midiOut->is_opened())
        {
            OpenMidiOut(true); // open for streaming

            // clear g_rxByteCount before requesting data because for midi,
            // OnMidiInput() could set it any time, but we want to clear the
            // previous data received count before calling receive().
            //
            // NOTE do not clear this here if (as in the case of the Akai S950
            // we need to send a single SysEx message over multiple calls to
            // SendStream()!
            g_rxByteCount = 0;

            g_midiOut->SetStreamTimeDiv(timeDiv); // ticks per beat

            // tempo can be changed in real-time as the sequence plays
            g_midiOut->SetStreamTempo(tempo); // 0x0007A120 default
        }

        g_midiOutDataBeingTransmitted = true; // this is reset to false in OnMidiOutputHandler()
        g_streamPlaying = true;
        g_abort = false;
        g_midiOut->PutStream(pSequence, size);
        g_midiOut->StreamReStart(); // only need this once...
        return true;
    }
    catch(...)
    {
        printm("error in SendStream()!");
        return false;
    }
}
//---------------------------------------------------------------------------
// MEVT_F_SHORT        0x00000000L
// MEVT_F_LONG         0x80000000L
// MEVT_F_CALLBACK     0x40000000L
//
// MEVT_EVENTTYPE(x)   ((BYTE)(((x)>>24)&0xFF))
// MEVT_EVENTPARM(x)   ((DWORD)((x)&0x00FFFFFFL))
//
// MEVT_SHORTMSG       ((BYTE)0x00)    parm = shortmsg for midiOutShortMsg
// MEVT_TEMPO          ((BYTE)0x01)    parm = new tempo in microsec/qn
// MEVT_NOP            ((BYTE)0x02)    parm = unused; does nothing
//
// 0x04-0x7F reserved
//
// MEVT_LONGMSG        ((BYTE)0x80)    parm = bytes to send verbatim
// MEVT_COMMENT        ((BYTE)0x82)    parm = comment data
// MEVT_VERSION        ((BYTE)0x84)    parm = MIDISTRMBUFFVER struct
//
// 0x81-0xFF reserved
//
//Information Switch Switch
//The topic you requested is included in another documentation set. For convenience, it's displayed below. Choose Switch to see the topic in its original location.
//MIDIEVENT structure
//The MIDIEVENT structure describes a MIDI event in a stream buffer.
//Syntax
//
//C++
//
//typedef struct {
//  DWORD dwDeltaTime;
//  DWORD dwStreamID;
//  DWORD dwEvent;
//  DWORD dwParms[];
//} MIDIEVENT;
//
//Members
//
//dwDeltaTime
//Time, in MIDI ticks, between the previous event and the current event. The length of a tick is defined
// by the time format and possibly the tempo associated with the stream. (The definition is identical to
// the specification for a tick in a standard MIDI file.)
//dwStreamID
//Reserved; must be zero.
//dwEvent
//Event code and event parameters or length. To parse this information, use the MEVT_EVENTTYPE and
// MEVT_EVENTPARM macros. See Remarks.
//dwParms
//If dwEvent specifies MEVT_F_LONG and the length of the buffer, this member contains parameters for
// the event. This parameter data must be padded with zeros so that an integral number of DWORD values
// are stored. For example, if the event data is five bytes long, three pad bytes must follow the data
// for a total of eight bytes. In this case, the low 24 bits of dwEvent would contain the value 5.
//If dwEvent specifies MEVT_F_SHORT, do not use this member in the stream buffer.
//Remarks
//
//The high byte of dwEvent contains flags and an event code. Either the MEVT_F_LONG or MEVT_F_SHORT flag
// must be specified. The MEVT_F_CALLBACK flag is optional. The following table describes these flags.
//Flag Meaning
//MEVT_F_CALLBACK The system generates a callback when the event is about to be executed.
//MEVT_F_LONG The event is a long event. The low 24 bits of dwEvent contain the length of the event
// parameters included in dwParms.
//MEVT_F_SHORT The event is a short event. The event parameters are contained in the low 24 bits of dwEvent.
//
//The remainder of the high byte contains one of the following event codes:
//Event Code Meaning
//MEVT_COMMENT Long event. The event data will be ignored. This event is intended to store commentary
// information about the stream that might be useful to authoring programs or sequencers if the stream
// data were to be stored in a file in stream format. In a buffer of this data, the zero byte identifies
// the comment class and subsequent bytes contain the comment data.
//MEVT_LONGMSG Long event. The event data is transmitted verbatim. The event data is assumed to be
// system-exclusive data; that is, running status will be cleared when the event is executed and running
// status from any previous events will not be applied to any channel events in the event data. Using
// this event to send a group of channel messages at the same time is not recommended; a set of
// MEVT_SHORTMSG events with zero delta times should be used instead.
//MEVT_NOP Short event. This event is a placeholder; it does nothing. The low 24 bits are ignored. This
// event will still generate a callback if MEVT_F_CALLBACK is set in dwEvent.
//MEVT_SHORTMSG Short event. The data in the low 24 bits of dwEvent is a MIDI short message. (For a
// description of how a short message is packed into a DWORD value, see the midiOutShortMsg function.)
//MEVT_TEMPO Short event. The data in the low 24 bits of dwEvent contain the new tempo for following
// events. The tempo is specified in the same format as it is for the tempo change meta-event in a
// MIDI file — that is, in microseconds per quarter note. (This event will have no affect if the time
// format specified for the stream is SMPTE time.)
//MEVT_VERSION Long event. The event data must contain a MIDISTRMBUFFVER structure.
//
// NOTE: prior to calling this, set g_streamCount = total # parts in the stream
void __fastcall TFormMain::streamws(Byte *inBuf, int inSize, int deltaTime)
{
    Byte *outBuf = NULL;

    try
    {
        int uls = sizeof(unsigned long); // (4)

        // how many unsigned longs are needed to represent inBuf?
        int outUlCount = inSize / uls;
        if ((inSize % uls) > 0)
            outUlCount++;

        // add the lead-in words and MEVT_NOP...
        int totalUlCount = outUlCount+3+3;

        // allocate byte-buffer for ULs
        int outSize = totalUlCount*uls;

        // create buffer
        outBuf = new Byte[outSize];

        // clear it...
        for (int ii = 0; ii < outSize; ii++)
            outBuf[ii] = 0;

        // point to the first byte in the first data DWORD
        Byte *outPtr = outBuf + (3*uls);

        // byte data in Windows xfers as-is to each unsigned long (little endian)
        for (int ii = 0; ii < inSize; ii++)
            *outPtr++ = *inBuf++;

        // get a UL pointer
        unsigned long *ulP = (unsigned long*)outBuf;

        // set the time and event-code
        ulP[0] = 0;
        ulP[1] = 0; // device-id (must be 0) FYI, is already 0!
        // left-shift event by 24 and or-in # midi sysex bytes
        ulP[2] = ((unsigned long)MEVT_LONGMSG<<24) | inSize;
        //ulP[2] = MEVT_F_LONG | inSize; // This will work ok too! (S.S.)

        // add the MEVT_NOP event and delta-time
        ulP[totalUlCount-3] = (unsigned long)deltaTime;
        ulP[totalUlCount-2] = 0;
        ulP[totalUlCount-1] = ((unsigned long)MEVT_NOP<<24);

        // queue the stream
        SendStream(ulP, outSize, 1000, 1000000); // set up so delta-times are in ms!
    }
    __finally
    {
        if (outBuf)
            delete [] outBuf;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::IsD50Connected(void)
{
    if (SystemBusy)
        return false;

    if (IsPlaying)
        CloseMidiOut();

    Byte buf[8+D50_PATCH_SECTION_SIZE+2];

    try
    {
        FormMain->OpenMidiOut();
        FormMain->OpenMidiIn(MIDI_BUFSIZE, 1, true);

        DelayGpTimer(35); // put some delay between successive calls to this!

        try
        {
            Byte midistr[13];

            midistr[0] = BEX;
            midistr[1] = ROLAND_ID; // roland
            midistr[2] = g_midiChan; // channel
            midistr[3] = D50_ID; // D-50
            midistr[4] = R_RQ1; // RQ1 request data command
            // checksum is two's compliment of the sum of the next 6 bytes...
            midistr[5] = 0; // addr high (patch 1-1)
            midistr[6] = 0; // addr mid
            midistr[7] = 0; // addr low

            midistr[8] = 0; // size high (448 bytes)
            midistr[9] = 0; // size mid
            midistr[10] = 1; // size low (1 byte)

            // to here...
            midistr[11] = roland_checksum(midistr, 11); // 0x3D; // checksum
            midistr[12] = EEX;

            if (!comws(13, midistr))
                return false;

            if (receive(1))
                return false;

            // copy data
            if (g_rxByteCount)
                return true;
        }
        catch(...)
        {
        }
    }
    __finally
    {
        FormMain->CloseMidiOut();
        FormMain->CloseMidiIn();
    }
    return false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Help1Click(TObject *Sender)
{
  String sHelp =
"Roland D-50 FM Synthesis Patch Generator Instructions\n\n"
"1. Set up your USB midi interface on your computer. The Patch Generator program will try to locate the midi ports automatically when you start it, but you can also set them from the boxes at the top of the program.\n"
"2. Connect both In and Out midi cables directly between the D-50 and your USB interface.\n"
"3. Run the patch generator program. It will detect your D-50 automatically and pop up a new window with data from the selected patch on your D-50. If there is a connection problem you will see an error message in a few seconds.\n"
"4. Click \"Menu->Set patch files storage path\" to set the location where you want to store your patch files. The program will create a folder for you called \"RolandD50\" in Documents.\n"
"5. To Save all 64 patches presently on your D-50, click \"Menu->Save all 64 patches\". This will place 64 individual patch files in a folder called RolandD50\\PatchSave.\n"
"6. To start generating new sounds, first select a patch on your D-50 which will be the \"starting point\" for new, modified sounds.\n"
"   Click Menu->Remotely Change Patch and chose a base patch to use as a starting point.\n"
"7. Make sure you sound from you D-50 is turned up so you can hear it ok.\n"
"8. In the menu for the patch's window (not the main window) click \"Menu->Randomization\" to start/stop new sound creation. A new patch will be generated every 5-10 seconds and a test-note sequence will be played. When you hear something interesting, you can save the new patch to a file in your RolandD50 folder by pressing F7.\n\n"
"The left panel shows a list of patches that you have generated. Patch file-names are generated automatically.\n"
"To delete a patch, click it and press the Del key, or right-click and choose Delete in the pop-up menu.\n"
"To rename a patch, click it and change the name in the lower box then press Enter.\n"
"To send a patch to your D-50, double-click it or right-click and choose Play from the pop-up menu.\n"
"NOTE: This program writes to your D-50's temp-area only and will never overwrite your saved patches!\n";

  ShowMessage(sHelp);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PatchFormActivatedTimeout(TObject *Sender)
{
    PatchFormActivatedTimer->Enabled = false;

    // find the active FormPatch...
    int count = g_patchForms->Count;
    
    TFormPatch* fActive = NULL;
    
    // turn off timers on inactive forms and save a pointer to the
    // active form
    for (int ii = 0; ii < count; ii++)
    {
        TFormPatch* f = reinterpret_cast<TFormPatch*>(g_patchForms->Items[ii]);
        if (f)
        {
          if (!f->Active)
          {
              if (f->TimerOver10Percent->Enabled)
                  f->TimerOver10Percent->Enabled = false;
              if (f->TimerSendPatch->Enabled)
                  f->TimerSendPatch->Enabled = false;

          }
          else // form is active, save pointer
            fActive = f;
        }  
    }
    
    // now change patch to the active form
    if (fActive)
        FormPatchActivated(fActive);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormPatchActivated(TFormPatch *f)
{
    if (CurrentPatch != f->PatchNumber)
    {
        PatchChange(f->PatchNumber); // change patch on the D-50
        f->PutTempArea(); // write grid to D-50 temp-area
    }

    // restart randomization
    if (f->RandomizationOn)
    {
        f->TimerSendPatch->Enabled = false;
        f->TimerSendPatch->Interval = f->CurrentTimer;
        f->TimerSendPatch->Enabled = true;
    }
}
//---------------------------------------------------------------------------

