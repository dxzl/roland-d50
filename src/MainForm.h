//---------------------------------------------------------------------------
//Software written by Scott Swift 2016 - This program is distributed under the
//terms of the GNU General Public License.
//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include "AdPort.hpp"
#include "OoMisc.hpp"
#include ".\Midi\MSC_In_Device.hpp"
#include ".\Midi\MSC_Out_Device.hpp"
#include "DefaultStrings.h"
#include <Vcl.FileCtrl.hpp>

// defines
//---------------------------------------------------------------------------
// Note: Use String() to wrap this for the overloaded RegHelper write method!
#define VERSION_STR "Version 1.50: July 23, 2017"
//---------------------------------------------------------------------------

#define REGISTRY_KEY "\\Software\\Discrete-Time Systems\\RolandD50"

#define DIRECTORY_NAME "\\RolandD50"

// Registry entries we save in HKEY_CURRENT_USER
#define S9_REGKEY_VERSION "Version"
#define S9_REGKEY_MIDI_INNAME "MidiInName"
#define S9_REGKEY_MIDI_OUTNAME "MidiOutName"
#define S9_REGKEY_MIDI_CHAN "MidiChan"
#define S9_REGKEY_DOC_PATH "DocPath"
#define S9_REGKEY_RAND_INTERVAL "RandInterval"
#define S9_REGKEY_CURRENT_PATCH "CurrentPatch"

#define LOAD 1
#define SAVE 2

#define NUMITEMS 4
#define GETFILE  0
#define PUTFILE  1
#define SETTINGS 2
#define CONNECT  3

#define RXTIMEOUT 3100 // 3.1 seconds
#define TXLONGTIMEOUT 3100 // 3.1 seconds
#define TXSHORTTIMEOUT 1100 // 1.1 seconds
#define TXMIDITIMEOUT 5100 // 5.1 seconds (send entire multi-byte sysex message or packet)

#define MIN_RAND_INTERVAL 3000
#define DEF_RAND_INTERVAL 7000
#define DEF_PATCH 0 // "Fantasia"


#define MAGIC_NUM_ROL 2349032123 // magic number identifies .rol file

#define ACKSIZ  4

#define UINT16SIZE ((int)sizeof(unsigned __int16))
#define UINT32SIZE ((int)sizeof(unsigned __int32))

#define BEX (0xf0)  // beginning of exclusive
#define EEX (0xf7)  // end of EXCLUSIVE

#define SYSTEM_COMMON_NON_REALTIME_ID (0x7e)
#define SYSTEM_COMMON_REALTIME_ID (0x7f)

#define ROLAND_ID (0x41)  // ROLAND I.D.
#define D50_ID (0x14)    // D-50 I.D.

#define D50_PATCH_SECTION_SIZE 64 // 64-bytes per patch-section
#define TOTAL_PATCHES_ON_D50 64 // 8 X 8 banks of patches on D-50

#define SYSEX_PATCH_SECTION_SIZE (D50_PATCH_SECTION_SIZE+10)
#define SYSEX_PATCH_SIZE (SYSEX_PATCH_SECTION_SIZE*7)

// roland exclusive
#define R_RQ1 (0x11) // one-way request data
#define R_DT1 (0x12) // one-way data-set
#define R_WSD (0x40) // want to send data
#define R_RQD (0x41) // request data
#define R_DAT (0x42) // data set
#define R_ACK (0x43) // acknowledge
#define R_EOD (0x45) // end of data
#define R_ERR (0x4e) // communication error
#define R_RJC (0x4f) // rejection

// this is used in conjunction with g_midiInputBufferPointer
#define MIDIINBUFSIZE 1024

// tabs in the data-grid (corresponds to number of sections per D-50 patch)
#define TOTAL_TABS 7
#define TOTAL_COLS 4
#define D50_PATCH_NAME_LENGTH 18
#define D50_COMMON_NAME_LENGTH 10
#define NOTECOUNT 100 // max number of test-notes
#define MINNOTE 40
#define MAXNOTE 50
#define LOCKOUT_TIME 5 // SetRandForm.cpp - time between replays

// columns
#define COL_NAME  0
#define COL_VAL   1
#define COL_MAX   2
#define COL_RAND  3

// Default strings representing the 64-parameters in Upper Partial 1, Etc.
// (this compiler won't take 0B0101010101... constants for some odd reason!)
#define PAT_00 "0000000000000000000000000000000011000000000000000000000000000000" // a00 Reverb <--(Type, Balance)
#define PAT_01 "0000000000000000000000000000001000000000000000000000000000000000" // a01 Tone Balance
#define PAT_02 "0000000000000000000000000001110000000000000000000000000000000000" // a02 Chase <--(Mode, Level, Time)

#define COM_00 "0000000000000000000000000000000000000000000000011110000000000000" // b00 P-Env Time
#define COM_01 "0000000000000000000000000000000000000000001111100000000000000000" // b01 P-Env Level
#define COM_02 "0000000000000000000000000000000000000000010000000000000000000000" // b02 P-Env Mod
#define COM_03 "0000000000000000000000000000000000000000000000000000000000000000" // b06 P-Env Other
#define COM_04 "0000000000000000000000000000000000011110000000000000000000000000" // b03 LFO1
#define COM_05 "0000000000000000000000000000000111100000000000000000000000000000" // b04 LFO2
#define COM_06 "0000000000000000000000000001111000000000000000000000000000000000" // b05 LFO3
#define COM_07 "0000000000000000000000001110000000000000000000000000000000000000" // b07 Low EQ
#define COM_08 "0000000000000000000000110000000000000000000000000000000000000000" // b08 High EQ
#define COM_09 "0000000000000000001111000000000000000000000000000000000000000000" // b09 Chorus
#define COM_10 "0000000000000000110000000000000000000000000000000000000000000000" // b10 Partial Balance

#define PAR_00 "0000000000000000000000000000000000000000000000000000000000000111" // c00 WG Pitch
#define PAR_01 "0000000000000000000000000000000000000000000000000000000000011000" // c01 WG Mod
#define PAR_02 "0000000000000000000000000000000000000000000000000000000011000000" // c02 WG Wave
#define PAR_03 "0000000000000000000000000000000000000000000000000001111100000000" // c03 WG Pulse Width
#define PAR_04 "0000000000000000000000000000000000000000000000110000000000000000" // c04 TVF Bias
#define PAR_05 "0000000000000000000000000000000000000111110000000000000000000000" // c05 TVF Env Time
#define PAR_06 "0000000000000000000000000000000011111000000000000000000000000000" // c06 TVF Env Level
#define PAR_07 "0000000000000000000000000000000000000000001111001110000000000000" // c07 TVF Other
#define PAR_08 "0000000000000000000000000000011100000000000000000000000000000000" // c08 TVF Mod
#define PAR_09 "0000000000000000000000000110000000000000000000000000000000000000" // c09 TVA Bias
#define PAR_10 "0000000000000000000011111000000000000000000000000000000000000000" // c10 TVA Env Time
#define PAR_11 "0000000000000001111100000000000000000000000000000000000000000000" // c11 TVA Env Level
#define PAR_12 "0000000000000110000000000001100000000000000000000000000000000000" // c12 TVA Other
#define PAR_13 "0000000000111000000000000000000000000000000000000000000000000000" // c13 TVA Mod

class TFormPatch;

//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:  // IDE-managed Components
    TPanel *Panel2;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TMainMenu *MainMenu1;
    TPanel *Panel1;
    TMemo *Memo1;
    TTimer *Timer1;
    TMenuItem *MenuGetTempArea;
    TMenuItem *N4;
  TMenuItem *MenuAbout;
    TPanel *Panel3;
    TLabel *LabelMidiInDevice;
    TLabel *LabelMidiOutDevice;
    TComboBox *ComboBoxMidiOut;
    TComboBox *ComboBoxMidiIn;
    TButton *ButtonRefreshDevs;
    TComboBox *ComboBoxMidiChan;
    TLabel *LabelMidiChan;
    TFilterComboBox *FilterComboBox1;
    TFileListBox *FileListBox1;
    TEdit *Edit1;
    TPopupMenu *PopupMenuFileListBox;
    TMenuItem *PopupMenuItemOpen;
    TMenuItem *PopupMenuItemDelete;
    TMenuItem *MenuOpenFile;
    TMenuItem *N1;
  TMenuItem *Save64IntPatches;
    TMenuItem *MenuItemSetWorkingDirectoryPath;
  TMenuItem *Help1;
  TMenuItem *MenuLoadPatchFromD50;
  TMenuItem *Save64CrdPatches;
  TMenuItem *N3;
  TTimer *PatchFormActivatedTimer;
  TMenuItem *MenuCloseAllPatchForms;
  TMenuItem *N2;

    void __fastcall MenuGetTempAreaClick(TObject *Sender);
    void __fastcall MenuAboutClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall TimerFileDrop(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ButtonRefreshDevsClick(TObject *Sender);
    void __fastcall ComboBoxMidiInChange(TObject *Sender);
    void __fastcall ComboBoxMidiOutChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ComboBoxMidiChanChange(TObject *Sender);
    void __fastcall PopupMenuItemOpenClick(TObject *Sender);
    void __fastcall PopupMenuItemDeleteClick(TObject *Sender);
    void __fastcall FileListBox1DblClick(TObject *Sender);
    void __fastcall MenuOpenFileClick(TObject *Sender);
    void __fastcall Save64IntPatchesClick(TObject *Sender);
    void __fastcall MenuItemSetWorkingDirectoryPathClick(TObject *Sender);
  void __fastcall Help1Click(TObject *Sender);
  void __fastcall MenuSetBasePatchClick(TObject *Sender);
  void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall Save64CrdPatchesClick(TObject *Sender);
  void __fastcall PatchFormActivatedTimeout(TObject *Sender);
  void __fastcall MenuCloseAllPatchFormsClick(TObject *Sender);

private:  // User declarations
    void __fastcall FormPatchActivated(TFormPatch *f);

    void __fastcall TimerGpTimeout(TObject *Sender);
    void __fastcall TimerRxTimeout(TObject *Sender);
    void __fastcall TimerTxTimeout(TObject *Sender);
    void __fastcall TimerDemoTimeout(TObject *Sender);

    bool __fastcall IsGpTimeout(void);
    void __fastcall StopGpTimer(void);
    void __fastcall StartGpTimer(int time);

    void __fastcall OnMidiOutputHandler(TObject *Sender);
    void __fastcall OnMidiInputHandler(TObject *Sender);
    void __fastcall OnMidiDriverCircBufOverflowHandler(TObject *Sender);

    void __fastcall RemoveAllPatchForms(void);
    TFormPatch * __fastcall AddPatchForm(void);
    void __fastcall ReadPatchesAndSaveTo64Files(bool bCard);
    bool __fastcall IsD50Connected(void);
    void __fastcall DeleteSelectedFile(void);
    void __fastcall SetSysExMasterVolume(UInt16 vol);
    void __fastcall MidiDeviceListRefresh(void);
    void __fastcall SetMidiInOutToSameDevice(void);
    String __fastcall GetFileName(void);
    void __fastcall roland_d50_request_patch_1_1(void);
    void __fastcall roland_d50_send_ack(int mode);
    void __fastcall display_hex(Byte buf[]);
    void __fastcall compute_checksum(int min_index, int max_index);
    void __fastcall exmit(int samp, int mode);
    bool __fastcall comws(int count, unsigned char* ptr);
    int __fastcall receive(int count);
    void __fastcall chandshake(int mode);
    void __fastcall cxmit(int samp, int mode);
    void __fastcall WMDropFile(TWMDropFiles &Msg);

    unsigned g_rxByteCount, g_streamCount;
    int g_randInterval;
    bool g_rxTimeout, g_txTimeout, g_gpTimeout, g_inBufferFull, g_systemBusy;
    bool g_midiOutDataBeingTransmitted, g_streamPlaying, g_abort;
    TMIDI_Device_Input *g_midiIn;
    TMIDI_Device_Output *g_midiOut;
    TList* g_patchForms;

    String g_DragDropFilePath, g_docPath;

    // settings vars
    int g_midiChan, g_currentPatch;
    String g_midi_inname, g_midi_outname;

protected:

BEGIN_MESSAGE_MAP
    //add message handler for WM_DROPFILES
    // NOTE: All of the TWM* types are in messages.hpp!
    VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WMDropFile)
END_MESSAGE_MAP(TComponent)

public:    // User declarations
    __fastcall TFormMain(TComponent* Owner);

    void __fastcall RemovePatchForm(TFormPatch *p);
    void __fastcall LoadPatchFromD50(bool bAllowCard);
    void __fastcall SetWorkingDir(String sDir);
    void __fastcall printm(String message);
    void __fastcall NotesAndControllersOff(void);
    void __fastcall DelayGpTimer(int time);
    void __fastcall OpenMidiIn(int bufferSize, int bufferCount, bool sysExOnly);
    void __fastcall CloseMidiIn(void);
    void __fastcall OpenMidiOut(bool bStream=false);
    void __fastcall CloseMidiOut(void);
    void __fastcall PatchChange(void);
    void __fastcall PatchChange(int patch);
    bool __fastcall D50GetTempArea(unsigned __int16 addr,
                   Byte *buf, unsigned __int16 size=D50_PATCH_SECTION_SIZE);
    bool __fastcall D50PutTempArea(unsigned __int16 addr, Byte *buf,
                            unsigned __int16 size=D50_PATCH_SECTION_SIZE);
    void __fastcall streamws(Byte *inBuf, int inSize, int deltaTime);
    void __fastcall PlayStream(unsigned long *pSequence, int size, int timeDiv=96, int tempo=50000);
    bool __fastcall SendStream(unsigned long *pSequence, int size, int timeDiv, int tempo);
    Byte __fastcall roland_checksum(unsigned char* buf, int offsetofchecksum);

    // buffer for midi sysex messages
    Byte g_midiInputBuffer[MIDIINBUFSIZE];

    __property String DocPath = {read = g_docPath};
    __property bool IsPlaying = {read = g_streamPlaying};
    __property bool SystemBusy = {read = g_systemBusy, write = g_systemBusy};
    __property int MidiChan = {read = g_midiChan};
    __property int RandInterval = {read = g_randInterval, write = g_randInterval};
    __property int CurrentPatch = {read = g_currentPatch};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

