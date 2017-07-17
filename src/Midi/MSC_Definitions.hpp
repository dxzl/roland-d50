// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_Definitions.pas' rev: 32.00 (Windows)

#ifndef Msc_definitionsHPP
#define Msc_definitionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.MMSystem.hpp>
#include <System.AnsiStrings.hpp>
#include <utilities_math.hpp>
#include <MSC_Circular_Buffer.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_definitions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EMSC_Error;
struct TMidiCtlInfo;
struct TMidiOutTimerInfo;
class DELPHICLASS TMIDI_Event;
class DELPHICLASS TMeta_Event;
class DELPHICLASS TMyMidiHdr;
//-- type declarations -------------------------------------------------------
typedef System::Int8 T5bit;

typedef System::Int8 T7bit;

typedef System::Byte T8bit;

typedef System::Word T14bit;

typedef System::Int8 TMIDI_Range;

typedef System::Int8 TTrack_Range;

typedef T5bit TPort_Range;

typedef System::file TMIDI_File;

typedef System::Int8 TMIDI_Key_Signature;

typedef System::Int8 TMSC_Key;

typedef System::Int8 TMIDI_Ctrl_Range;

typedef System::Int8 TMIDI_Patch_Range;

typedef System::Int8 TMIDI_Drum_Range;

typedef T8bit TMIDI_Event_Range;

enum DECLSPEC_DENUM TPort_Capability : unsigned char { pcDisabled, pcMute, pcPlay };

typedef System::StaticArray<System::UnicodeString, 128> TMIDI_Patch_Names;

typedef System::StaticArray<System::UnicodeString, 61> TMIDI_Drum_Names;

typedef System::StaticArray<System::UnicodeString, 256> TMIDI_Event_Names;

typedef System::StaticArray<System::UnicodeString, 128> TMIDI_Controller_names;

typedef System::StaticArray<T5bit, 16> TPort_Array;

typedef System::StaticArray<System::StaticArray<TPort_Capability, 32>, 16> TChannel_Port;

#pragma pack(push,4)
class PASCALIMPLEMENTATION EMSC_Error : public System::Sysutils::EInOutError
{
	typedef System::Sysutils::EInOutError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMSC_Error(const System::UnicodeString Msg) : System::Sysutils::EInOutError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMSC_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EInOutError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Error(NativeUInt Ident)/* overload */ : System::Sysutils::EInOutError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Error(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EInOutError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EInOutError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EInOutError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMSC_Error(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EInOutError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMSC_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EInOutError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Error(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EInOutError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EInOutError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EInOutError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EInOutError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMSC_Error(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TMIDI_Status : unsigned char { ms_Note_Off, ms_Note_On, ms_Polyphonic_Aftertouch, ms_Controller_Change, ms_Program_Change, ms_Channel_Aftertouch, ms_Pitch_Bend, ms_Begin_SysEx, ms_MTC_Quarter_Frame, ms_Song_Pos_Ptr, ms_Song_Select, ms_End_SysEx, ms_Timing_Clock, ms_Start, ms_Continue, ms_Stop, ms_Unknown, ms_Active_Sensing, ms_Meta };

typedef System::StaticArray<System::AnsiString, 19> TMIDI_Status_Array_Names;

typedef System::StaticArray<System::Byte, 19> TMIDI_Status_Array_Bytes;

typedef System::StaticArray<System::AnsiString, 12> Msc_definitions__2;

typedef TMidiCtlInfo *PMidiCtlInfo;

struct DECLSPEC_DRECORD TMidiCtlInfo
{
public:
	NativeUInt hMem;
	Msc_circular_buffer::TCircularBuffer *PBuffer;
	HWND hWindow;
	bool SysexOnly;
};


typedef TMidiOutTimerInfo *PMidiOutTimerInfo;

struct DECLSPEC_DRECORD TMidiOutTimerInfo
{
public:
	NativeUInt hMem;
	Msc_circular_buffer::TCircularBuffer *PBuffer;
	HWND hWindow;
	unsigned TimeToNextEvent;
	NativeInt MIDIHandle;
	System::Word PeriodMin;
	System::Word PeriodMax;
	System::Word TimerId;
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TMIDI_Event : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Byte FMidiMessage;
	System::Byte FData1;
	System::Byte FData2;
	unsigned FTime;
	int FPort;
	
protected:
	TMIDI_Status __fastcall get_event_index(void);
	System::AnsiString __fastcall get_text_time(void);
	virtual System::AnsiString __fastcall get_text_event(void);
	System::AnsiString __fastcall get_text_channel(void);
	virtual System::AnsiString __fastcall get_text_data_byte1(void);
	virtual System::AnsiString __fastcall get_text_data_byte2(void);
	virtual unsigned __fastcall get_size(void);
	void __fastcall set_time(unsigned time);
	System::Byte __fastcall get_event_type(void);
	void __fastcall set_event_type(System::Byte event);
	TMIDI_Range __fastcall get_channel(void);
	void __fastcall set_channel(TMIDI_Range channel);
	void __fastcall set_data_byte_1(System::Byte b);
	void __fastcall set_data_byte_2(System::Byte b);
	void __fastcall set_port(int track);
	TMIDI_Status __fastcall get_midi_status(void);
	virtual System::AnsiString __fastcall get_text_text(void);
	virtual System::AnsiString __fastcall get_text_translated(void);
	
public:
	System::Word SysexLength;
	System::Byte *Sysex;
	__fastcall TMIDI_Event(void)/* overload */;
	__fastcall virtual TMIDI_Event(int t, TMIDI_Range c, System::Byte e, System::Byte v, System::Byte s)/* overload */;
	__fastcall virtual ~TMIDI_Event(void);
	void __fastcall read_event(TMIDI_File &f);
	virtual void __fastcall write_event(TMIDI_File &f);
	void __fastcall load(System::TextFile &input);
	void __fastcall save(System::TextFile &output);
	TMIDI_Event* __fastcall copy_event(void);
	__property unsigned Size = {read=get_size, nodefault};
	__property unsigned Time = {read=FTime, write=set_time, nodefault};
	__property System::Byte MIDI_Message = {read=FMidiMessage, write=FMidiMessage, nodefault};
	__property System::Byte Event_Type = {read=get_event_type, write=set_event_type, nodefault};
	__property TMIDI_Range Channel = {read=get_channel, write=set_channel, nodefault};
	__property System::Byte Data_Byte_1 = {read=FData1, write=set_data_byte_1, nodefault};
	__property System::Byte Data_Byte_2 = {read=FData2, write=set_data_byte_2, nodefault};
	__property int Port = {read=FPort, write=set_port, nodefault};
	__property TMIDI_Status Status = {read=get_midi_status, nodefault};
	__property System::AnsiString Translated = {read=get_text_translated};
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TMeta_Event : public TMIDI_Event
{
	typedef TMIDI_Event inherited;
	
private:
	System::AnsiString FText;
	
protected:
	unsigned __fastcall get_length(void);
	virtual unsigned __fastcall get_size(void);
	virtual System::AnsiString __fastcall get_text_text(void);
	void __fastcall set_text_text(System::AnsiString value);
	virtual System::AnsiString __fastcall get_text_translated(void);
	
public:
	__fastcall TMeta_Event(System::Byte meta, System::AnsiString text);
	virtual void __fastcall write_event(TMIDI_File &f);
	__property unsigned Text_Length = {read=get_length, nodefault};
	__property System::AnsiString Text = {read=get_text_text, write=set_text_text};
public:
	/* TMIDI_Event.Destroy */ inline __fastcall virtual ~TMeta_Event(void) { }
	
};

#pragma pack(pop)

typedef TMIDI_Event* *PMyMidiEvent;

typedef TMyMidiHdr* *PMyMidiHdr;

#pragma pack(push,4)
class PASCALIMPLEMENTATION TMyMidiHdr : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	NativeUInt hdrHandle;
	midihdr_tag *hdrPointer;
	NativeUInt sysexHandle;
	void *sysexPointer;
	__fastcall TMyMidiHdr(System::Word BufferSize);
	__fastcall virtual ~TMyMidiHdr(void);
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const System::Word DefMidiInCircBufSize = System::Word(0x400);
static const System::Int8 C4bit = System::Int8(0x10);
static const System::Int8 C5bit = System::Int8(0x20);
static const System::Byte C7bit = System::Byte(0x80);
static const System::Word C8bit = System::Word(0x100);
static const System::Word C14bit = System::Word(0x4000);
static const System::Int8 nMidi_Channels = System::Int8(0x10);
static const System::Byte nPatches = System::Byte(0x80);
static const System::Int8 nDrums = System::Int8(0x3d);
static const System::Int8 nTracks = System::Int8(0x64);
static const System::Int8 nMIDI_Entries = System::Int8(0x4);
static const System::Byte nEvents = System::Byte(0xff);
static const System::Byte nCtrls = System::Byte(0x80);
static const System::Int8 drum_channel = System::Int8(0xa);
extern DELPHI_PACKAGE int mspq;
#define MSC_Package_Name L"MIDI Sequencer Components"
static const System::Byte ic_Poly_Aftertouch = System::Byte(0x80);
static const System::Byte ic_Channel_Aftertouch = System::Byte(0x81);
static const System::Byte ic_Pitch_Wheel = System::Byte(0x82);
static const System::Int8 max_midi_voices = System::Int8(0x20);
static const System::Int8 entry_midi_notes = System::Int8(0x0);
static const System::Int8 MIDI_Resolution = System::Int8(0x20);
static const System::Int8 C_Center = System::Int8(0x3c);
static const System::Int8 no_ports_available = System::Int8(-1);
static const System::Int8 mc_MIDI_Reset_All_Controllers = System::Int8(0x79);
static const System::Int8 mc_MIDI_All_Notes_Off = System::Int8(0x7b);
static const System::Byte mc_MIDI_Note_Off = System::Byte(0x80);
static const System::Byte mc_MIDI_Note_On = System::Byte(0x90);
static const System::Byte mc_MIDI_Polyphonic_Aftertouch = System::Byte(0xa0);
static const System::Byte mc_MIDI_Control_Change = System::Byte(0xb0);
static const System::Byte mc_MIDI_Program_Change = System::Byte(0xc0);
static const System::Byte mc_MIDI_Channel_Aftertouch = System::Byte(0xd0);
static const System::Byte mc_MIDI_Pitch_Bend = System::Byte(0xe0);
static const System::Byte mc_MIDI_System_Message = System::Byte(0xf0);
static const System::Byte mc_MIDI_Begin_SysEx = System::Byte(0xf0);
static const System::Byte mc_MIDI_MTC_Quarter_Frame = System::Byte(0xf1);
static const System::Byte mc_MIDI_Song_Pos_Ptr = System::Byte(0xf2);
static const System::Byte mc_MIDI_Song_Select = System::Byte(0xf3);
static const System::Byte mc_MIDI_End_SysEx = System::Byte(0xf7);
static const System::Byte mc_MIDI_Timing_Clock = System::Byte(0xf8);
static const System::Byte mc_MIDI_Start = System::Byte(0xfa);
static const System::Byte mc_MIDI_Continue = System::Byte(0xfb);
static const System::Byte mc_MIDI_Stop = System::Byte(0xfc);
static const System::Byte mc_MIDI_Active_Sensing = System::Byte(0xfe);
static const System::Byte mc_MIDI_Meta_Event = System::Byte(0xff);
static const System::Int8 mc_Meta_Sequence_Number = System::Int8(0x0);
static const System::Int8 mc_Meta_Text_Event = System::Int8(0x1);
static const System::Int8 mc_Meta_Copyright_Notice = System::Int8(0x2);
static const System::Int8 mc_Meta_Track_Name = System::Int8(0x3);
static const System::Int8 mc_Meta_Instrument_Name = System::Int8(0x4);
static const System::Int8 mc_Meta_Lyric = System::Int8(0x5);
static const System::Int8 mc_Meta_Marker = System::Int8(0x6);
static const System::Int8 mc_Meta_Cue_Point = System::Int8(0x7);
static const System::Int8 mc_Meta_Channel_Prefix = System::Int8(0x20);
static const System::Int8 mc_Meta_End_Of_Track = System::Int8(0x2f);
static const System::Int8 mc_Meta_Set_Tempo = System::Int8(0x51);
static const System::Int8 mc_Meta_SMPTE_Offset = System::Int8(0x54);
static const System::Int8 mc_Meta_Time_Signature = System::Int8(0x58);
static const System::Int8 mc_Meta_Key_Signature = System::Int8(0x59);
static const System::Int8 mc_Meta_Sequencer_Specific = System::Int8(0x7f);
static const System::Int8 mc_Ctrl_modulation = System::Int8(0x1);
static const System::Int8 mc_Ctrl_data_entry = System::Int8(0x6);
static const System::Int8 mc_Ctrl_volume = System::Int8(0x7);
static const System::Int8 mc_Ctrl_panpot = System::Int8(0xa);
static const System::Int8 mc_Ctrl_expression = System::Int8(0xb);
static const System::Int8 mc_Ctrl_damper_pedal = System::Int8(0x40);
static const System::Int8 mc_Ctrl_portamento = System::Int8(0x41);
static const System::Int8 mc_Ctrl_sostenuto = System::Int8(0x42);
static const System::Int8 mc_Ctrl_soft_pedal = System::Int8(0x43);
static const System::Int8 mc_Ctrl_general_4 = System::Int8(0x44);
static const System::Int8 mc_Ctrl_hold_2 = System::Int8(0x45);
static const System::Int8 mc_Ctrl_general_5 = System::Int8(0x50);
static const System::Int8 mc_Ctrl_general_6 = System::Int8(0x51);
static const System::Int8 mc_Ctrl_general_7 = System::Int8(0x52);
static const System::Int8 mc_Ctrl_general_8 = System::Int8(0x53);
static const System::Int8 mc_Ctrl_reverb_depth = System::Int8(0x5b);
static const System::Int8 mc_Ctrl_tremolo_depth = System::Int8(0x5c);
static const System::Int8 mc_Ctrl_chorus_depth = System::Int8(0x5d);
static const System::Int8 mc_Ctrl_detune = System::Int8(0x5e);
static const System::Int8 mc_Ctrl_phaser_depth = System::Int8(0x5f);
static const System::Int8 mc_Ctrl_reset_all_controllers = System::Int8(0x79);
static const System::Int8 mc_Ctrl_all_notes_off = System::Int8(0x7b);
static const System::Word MIM_OVERFLOW = System::Word(0x400);
static const System::Word MOM_PLAYBACK_DONE = System::Word(0x401);
extern DELPHI_PACKAGE System::StaticArray<TMSC_Key, 15> MIDI_Note_Translation;
extern DELPHI_PACKAGE Msc_definitions__2 MIDI_Note_Names;
extern DELPHI_PACKAGE TMIDI_Status_Array_Names MIDI_Status_Names;
extern DELPHI_PACKAGE TMIDI_Status_Array_Bytes MIDI_Status_Bytes;
extern DELPHI_PACKAGE bool __fastcall is_note_off(TMIDI_Event* event);
extern DELPHI_PACKAGE bool __fastcall is_note_on(TMIDI_Event* event);
extern DELPHI_PACKAGE int __fastcall measure_to_n32(int measures, int Beats, int Rythm);
extern DELPHI_PACKAGE void __fastcall n32_to_measures(int n32, int Beats, int Rythm, int &measures, int &rest);
extern DELPHI_PACKAGE double __fastcall n32_to_seconds(int n32nds, int BPM);
extern DELPHI_PACKAGE int __fastcall seconds_to_n32(double seconds, int BPM);
}	/* namespace Msc_definitions */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_DEFINITIONS)
using namespace Msc_definitions;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_definitionsHPP
