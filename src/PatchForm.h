//---------------------------------------------------------------------------
/*

class PropertyExample
{
    private:

        int Fx, Fy;

        float Fcells[100][100];

    protected:

        int readX()
        {
            return (Fx);
        }

        void writeX(int newFx)
        {
            Fx = newFx;
        }

        double computeZ()
        {
            // Do some computation and return a floating-point value...
            return (0.0);
        }

        float cellValue(int row, int col)
        {
            return (Fcells[row][col]);
        }

    public:
        __property int X = {read = readX, write = writeX};
        __property int Y = {read = Fy};
        __property double Z = {read = computeZ};
        __property float Cells[int row][int col] = {read = cellValue};

};

String reference FYI:

System.AnsiToUtf8
Converts a string encoded in Ansi to UTF-8.
System.WideStrUtils.AnsiToUtf8Ex
Converts a string encoded in ANSI to UTF-8 with a given code page.
System.WideStrUtils.ConvertStreamFromAnsiToUTF8
Converts a stream from ANSI to UTF-8 encoding.
System.WideStrUtils.DetectUTF8Encoding
Detects the encoding of a given WideString.
System.WideStrUtils.HasUTF8BOM
Detects if a string or a stream contains the UTF-8 byte-order mark.
System.WideStrUtils.IsUTF8LeadByte
Checks whether a character is a valid UTF-8 lead byte.
System.WideStrUtils.IsUTF8String
Detects if a given string is UTF-8 encoded.
System.WideStrUtils.IsUTF8TrailByte
Checks whether a character is a valid UTF-8 trail byte.
System.WideStrUtils.UTF8CharLength
Returns the number of bytes that follow a lead UTF-8 byte.
System.WideStrUtils.UTF8CharSize
Returns the number of bytes that follow a lead UTF-8 byte.
System.UTF8Decode
Converts a UTF8 string to a Unicode string (WideString).
System.UTF8Encode
Converts a WideString value to a UTF8 string.
System.UTF8EncodeToShortString
Converts a string to its UTF-8 encoded representation.
System.WideStrUtils.UTF8LowerCase
Returns the UTF-8 string converted to lower case.
System.UTF8ToString
Converts an UTF-8 encoded string to a string.
System.UTF8ToUnicodeString
Converts an UTF-8 encoded string to an Unicode string.
System.UTF8ToWideString
Converts an UTF-8 encoded string to a WideString.
System.WideStrUtils.UTF8UpperCase
Returns the UTF-8 string converted to uppercase.
System.UnicodeToUtf8
Converts a string of Unicode characters into a UTF-8 string.
System.Utf8ToAnsi
Converts a UTF8 string to a string of Ansi characters.
System.WideStrUtils.Utf8ToAnsiEx
Converts a string encoded in UTF-8 to ANSI with a given code page.
System.Utf8ToUnicode
Converts a string of UTF-8 characters to a Unicode string.
*/
//---------------------------------------------------------------------------

#ifndef PatchFormH
#define PatchFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Diagnostics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
#define NOTESTATE_IDLE          0
#define NOTESTATE_WAIT_ON       1
#define NOTESTATE_WAIT_OFF      2

#define NOTETIME_TO_INITIAL_ON  100
#define NOTETIME_TO_OFF         4000
#define NOTETIME_TO_ON          4000

#define MIN_TIMER 3000
#define MAX_TIMER 12000
#define INC_TIMER 1000

// There is a universal SysEx Master-Volume message!!!!!!!!!
//

// Midi message (first word)
// (Or Midi chan into low-nibble)

#define MID_MASTER_VOL  0x70

// d1 is note # (0-127, middle C is 60)
// d2 is note volume (0-127)
#define MID_NOTE_OFF    0x80
#define MID_NOTE_ON     0x90

// d1 is control ID (0-127, )
//............7 = volume
//............8 = balance
//............33 = mod-wheel
//............37 = portamento-time
//............121 = all controllers off (resets mod-wheel, etc. to normal)
//............123 = all notes off
// d2 is control value (0-127)
#define MID_CTRL_CHNG   0xb0

// d1 is patch # (0-127)
// d2 is X
#define MID_PTCH_CHNG   0xc0

// PutShort(msg, d1, d2); // uInt8
#define MIDI_BUFSIZE 4096
//---------------------------------------------------------------------------
enum tabConst { tUP1, tUP2, tUC, tLP1, tLP2, tLC, tP };
enum rowConst { rLabel, rVal, rMax, rRand };
//---------------------------------------------------------------------------
class TFormPatch : public TForm
{
__published:    // IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *MenuFormPatchMenu;
    TMenuItem *MenuItemFormPatchWriteToFile;
    TMenuItem *MenuItemFormPatchEnforceMinMaxValue;
    TTimer *TimerSendPatch;
    TMenuItem *MenuItemFormPatchStartStopRandom;
    TMenuItem *MenuItemFormPatchSendToTempArea;
    TMenuItem *MenuItemFormPatchAllNotesOff;
  TTimer *TimerOver10Percent;
    TMenuItem *MenuItemFormPatchPlay;
    TMenuItem *MenuFormPatchPresets;
    TMenuItem *MenuPresetsItemPreset11;
    TMenuItem *MenuPresetsItemPreset2;
    TMenuItem *MenuPresetsItemPreset3;
    TMenuItem *MenuPresetsItemPreset4;
    TMenuItem *N1;
    TMenuItem *MenuPresetsItemClearAll;
    TMenuItem *MenuPresetsItemSetAll;
    TMenuItem *MenuPatchFormSetRand;
    TMenuItem *Exportpatchtosyxbinaryfile1;
  TMenuItem *MenuItemFormPatchManualRandomize;
  TMenuItem *N2;
  TMenuItem *N3;
  TMenuItem *N4;
  TMenuItem *N5;
  TMenuItem *N6;
  TMenuItem *MenuHelp;
  TPageControl *PageControl;
  TTabSheet *UpperPartial1;
  TStringGrid *UpperPartial1SG;
  TPanel *Panel1;
  TTabSheet *UpperPartial2;
  TStringGrid *UpperPartial2SG;
  TTabSheet *UpperCommon;
  TStringGrid *UpperCommonSG;
  TTabSheet *LowerPartial1;
  TStringGrid *LowerPartial1SG;
  TTabSheet *LowerPartial2;
  TStringGrid *LowerPartial2SG;
  TTabSheet *LowerCommon;
  TStringGrid *LowerCommonSG;
  TTabSheet *Patch;
  TStringGrid *PatchSG;
  TButton *ButtonRandInterval;
  TLabel *LabelRand;
  TMenuItem *MenuItemFormPatchReload;
  TMenuItem *MenuItemFormPatchChange;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall SGDblClick(TObject *Sender);
    void __fastcall MenuItemFormPatchWriteToFileClick(TObject *Sender);
    void __fastcall MenuItemFormPatchEnforceMinMaxValueClick(TObject *Sender);
    void __fastcall TimerSendPatchTimer(TObject *Sender);
    void __fastcall MenuItemFormPatchStartStopRandomClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall MenuItemFormPatchSendToTempAreaClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall MenuItemFormPatchAllNotesOffClick(TObject *Sender);
    void __fastcall TimerOver10PercentTimer(TObject *Sender);
    void __fastcall MenuItemFormPatchPlayClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall MenuPresetsItemClick(TObject *Sender);
    void __fastcall MenuPatchFormSetRandClick(TObject *Sender);
    void __fastcall Exportpatchtosyxbinaryfile1Click(TObject *Sender);
  void __fastcall MenuItemFormPatchManualRandomizeClick(TObject *Sender);
  void __fastcall MenuHelpClick(TObject *Sender);
  void __fastcall ButtonRandIntervalClick(TObject *Sender);
  void __fastcall MenuItemFormPatchLoadClick(TObject *Sender);
  void __fastcall MenuItemFormPatchChangeClick(TObject *Sender);
private:    // User declarations
    void __fastcall Restore(void);
    void __fastcall SetRandomization(bool flag);
    void __fastcall EnforceDataRange(int tabIndex);
//    bool * __fastcall GetDefRandPtr(int tabIndex);
    TStringGrid * __fastcall GetSgPtr(int tabIndex);
    Byte __fastcall AsciiToRolandChar(Byte ascii);
    Byte __fastcall RolandCharToAscii(Byte rol_char);
    bool __fastcall ReadBufFromGrid(int tabIndex, Byte *data, int column=1);

    bool __fastcall WriteToGrid(int tabIndex, Byte *data, int column=1);
    bool __fastcall WriteToGrid(int tabIndex, String sColVals, int column=1);
    void __fastcall SaveSyxFile(String filePath, TStringList *sl);

    void __fastcall SetCaptionAndPatchNumberToTabCellValues(bool bAppendPatchNumber);
    String __fastcall GetFriendlyPatchNum(int patch);

    bool __fastcall GenRandValues(void);
    bool __fastcall GenRandValues(unsigned __int64 masks[]);
    bool __fastcall GenRandValues(int tabIndex, unsigned __int64 mask); // don't name this "Randomize()!"
    void __fastcall InitDataGrid(void);
    void __fastcall InitDataGrid(int tabIndex);

    bool m_enableCellEdit, m_EventsEnabled, m_randomizationOn;
    unsigned m_currentTimer;
    int m_patchNumber;
    String m_patchName;
    TStringList *prevGridVals;
    TStringList *origGridVals;
    TStopwatch *stopWatch;

public:     // User declarations
    __fastcall TFormPatch(TComponent* Owner);

    void __fastcall ReadFromGrid(TStringList *sl);
    bool __fastcall WriteToGrid(TStringList *sl, bool bIncludeRandFlags);
    void __fastcall ManualRandomize(void);
    void __fastcall ManualRandomize(unsigned __int64 masks[]);
    void __fastcall SetRandFlags(int tabIndex, unsigned __int64 mask, bool bOnOff);
    void __fastcall LoadPatchFileIntoD50AndDataGrid(String sPath);
    void __fastcall GetTempArea(int patchNum);
    void __fastcall PutTempArea(void);
    void __fastcall WritePatchToFile(bool bSyx);
    void __fastcall ReadPatchesAndSaveTo64Files(bool bCard);
    void __fastcall PatchChange(int newPatch);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPatch *FormPatch;
//---------------------------------------------------------------------------
#endif
