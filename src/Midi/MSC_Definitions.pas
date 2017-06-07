unit MSC_Definitions;

{
   Copyright 1998-2011 Arnold Reinders

   This file is part of the MIDI Sequencer Components (MSC).

   MIDI Sequencer Components (MSC) is free software: you can redistribute it
   and/or modify it under the terms of the Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.

   MIDI Sequencer Components (MSC) is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License and the
   Lesser General Public License along with MIDI Sequencer Components (MSC).
   If not, see <http://www.gnu.org/licenses/>.

   Any changes in the MIDI Sequencer Components (MSC) should be reported
   to Arnold Reinders at musoft@musoft.com
}

interface

uses Classes, Wintypes, SysUtils, Messages, MMSystem, AnsiStrings,
     utilities_math, MSC_Circular_Buffer;

const
    DefMidiInCircBufSize    = 1024;
    C4bit                   = 16;
    C5bit                   = 32;
    C7bit                   = 128;
    C8bit                   = 256;
    C14bit                  = 128 * 128;
    nMidi_Channels          = 16;
    nPatches                = C7bit;
    nDrums                  = 61;
    nTracks                 = 100; // S.S. added 12/23/2016
    nMIDI_Entries           = 4;
    nEvents                 = C8bit - 1;
    nCtrls                  = C7bit;
    drum_channel            = 10;
    mspq: Int32             = 60000000;
    MSC_Package_Name        = 'MIDI Sequencer Components';
    ic_Poly_Aftertouch      = 128;
    ic_Channel_Aftertouch   = 129;
    ic_Pitch_Wheel          = 130;
    max_midi_voices         = 32;
    entry_midi_notes        =  0;
    MIDI_Resolution         = 32; // Maximum reolution of the MIDI system (1/32 note)
    C_Center                = 60; // Central C key
    no_ports_available      = -1;

// Important MIDI messages
   mc_MIDI_Reset_All_Controllers  = $79;
   mc_MIDI_All_Notes_Off          = $7B;

// MIDI status bytes
   mc_MIDI_Note_Off               = $80;
   mc_MIDI_Note_On                = $90;
   mc_MIDI_Polyphonic_Aftertouch  = $A0;
   mc_MIDI_Control_Change         = $B0;
   mc_MIDI_Program_Change         = $C0;
   mc_MIDI_Channel_Aftertouch     = $D0;
   mc_MIDI_Pitch_Bend             = $E0;
   mc_MIDI_System_Message         = $F0;
   mc_MIDI_Begin_SysEx            = $F0;
   mc_MIDI_MTC_Quarter_Frame      = $F1;
   mc_MIDI_Song_Pos_Ptr           = $F2;
   mc_MIDI_Song_Select            = $F3;
   mc_MIDI_End_SysEx              = $F7;
   mc_MIDI_Timing_Clock           = $F8;
   mc_MIDI_Start                  = $FA;
   mc_MIDI_Continue               = $FB;
   mc_MIDI_Stop                   = $FC;
   mc_MIDI_Active_Sensing         = $FE;
   mc_MIDI_Meta_Event             = $FF;

// Defined meta events
   mc_Meta_Sequence_Number        = $00;
   mc_Meta_Text_Event             = $01;
   mc_Meta_Copyright_Notice       = $02;
   mc_Meta_Track_Name             = $03;
   mc_Meta_Instrument_Name        = $04;
   mc_Meta_Lyric                  = $05;
   mc_Meta_Marker                 = $06;
   mc_Meta_Cue_Point              = $07;
   mc_Meta_Channel_Prefix         = $20;
   mc_Meta_End_Of_Track           = $2f;
   mc_Meta_Set_Tempo              = $51;
   mc_Meta_SMPTE_Offset           = $54;
   mc_Meta_Time_Signature         = $58;
   mc_Meta_Key_Signature          = $59;
   mc_Meta_Sequencer_Specific     = $7f;

// Some 7 bit controllers
    mc_Ctrl_modulation              = $01;
    mc_Ctrl_data_entry              = $06;
    mc_Ctrl_volume                  = $07;
    mc_Ctrl_panpot                  = $0a;
    mc_Ctrl_expression              = $0b;
    mc_Ctrl_damper_pedal            = $40;
    mc_Ctrl_portamento              = $41;
    mc_Ctrl_sostenuto               = $42;
    mc_Ctrl_soft_pedal              = $43;
    mc_Ctrl_general_4               = $44;
    mc_Ctrl_hold_2                  = $45;
    mc_Ctrl_general_5               = $50;
    mc_Ctrl_general_6               = $51;
    mc_Ctrl_general_7               = $52;
    mc_Ctrl_general_8               = $53;
    mc_Ctrl_reverb_depth            = $5b;
    mc_Ctrl_tremolo_depth           = $5c;
    mc_Ctrl_chorus_depth            = $5d;
    mc_Ctrl_detune                  = $5e;
    mc_Ctrl_phaser_depth            = $5f;
    mc_Ctrl_reset_all_controllers   = $79;
    mc_Ctrl_all_notes_off           = $7b;

    MIM_OVERFLOW                    = WM_USER;   // Input buffer overflow
    MOM_PLAYBACK_DONE               = WM_USER+1; // Timed playback complete

type
   T5bit                    = 0..C5bit  - 1;
   T7bit                    = 0..C7bit  - 1;
   T8bit                    = 0..C8bit  - 1;
   T14bit                   = 0..C14bit - 1;
   TMIDI_Range              = 1..nMidi_Channels;
   TTrack_Range             = 0..nTracks - 1; // S.S. added 12/23/2016
   TPort_Range              = T5bit;
   TMIDI_File               = file of uInt8;
   TMIDI_Key_Signature      = -7..+7;
   TMSC_Key                 =  0..11;
   TMIDI_Ctrl_Range         = 0..nCtrls - 1;
   TMIDI_Patch_Range        = 0..nPatches - 1;
   TMIDI_Drum_Range         = 0..nDrums - 1;
   TMIDI_Event_Range        = T8bit;
   TPort_Capability         = (pcDisabled, pcMute, pcPlay);
   TMIDI_Patch_Names        = array [TMIDI_Patch_Range] of string;
   TMIDI_Drum_Names         = array [TMIDI_Drum_Range]  of string;
   TMIDI_Event_Names        = array [TMIDI_Event_Range] of string;
   TMIDI_Controller_names   = array [T7Bit] of string;
   TPort_Array              = array [TMIDI_Range] of TPort_Range;
   TChannel_Port            = array [TMIDI_Range, TPort_Range] of TPort_Capability;

   EMSC_Error = class (EInOutError);

   TMIDI_Status             = (ms_Note_Off, ms_Note_On, ms_Polyphonic_Aftertouch,
                               ms_Controller_Change, ms_Program_Change,
                               ms_Channel_Aftertouch, ms_Pitch_Bend,
                               ms_Begin_SysEx, ms_MTC_Quarter_Frame,
                               ms_Song_Pos_Ptr, ms_Song_Select, ms_End_SysEx,
                               ms_Timing_Clock, ms_Start, ms_Continue,
                               ms_Stop, ms_Unknown, ms_Active_Sensing,
                               ms_Meta);

   TMIDI_Status_Array_Names = array [TMIDI_Status] of AnsiString;
   TMIDI_Status_Array_Bytes = array [TMIDI_Status] of uInt8;

const
// There are two types of key signature. MIDI decodes the key signature into
// TMIDI_Key_Signature which runs from -7 (7 flats), 0 (C) to +7 (7 sharps).
// The MSC Sequencer components use another format (TMSC_Key) which runs
// from 0 (C) to 11 (B). The key signature is the Tonica of the musical scale
// and as such is a property of class TMIDI_Container.
// The MSC key signature can be computed by using the translation table below, i.e.
// tonica := MIDI_Note_Translation [MIDI_Key_Signature];

   MIDI_Note_Translation: array [TMIDI_Key_Signature] of TMSC_Key =
         (11, 6, 1, 8, 3, 10, 5, 0, 7, 2, 9, 4, 11, 6, 1);
   MIDI_Note_Names: array [TMSC_Key] of AnsiString =
         ('C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B');

   MIDI_Status_Names: TMIDI_Status_Array_Names = ('Note Off', 'Note On',
                  'Polyphonic Aftertouch', 'Controller Change', 'Program Change',
                  'Channel Aftertouch', 'Pitch Wheel',
                  'Begin System Exclusive', 'MTC Quiarter Frame',
                  'Song Position Pointer', 'Song Select',
                  'End System Exclusive', 'Timing Clock', 'Start Sybchonization',
                  'Continue Synchronization', 'Stop Synchonization',
                  'Unknown', 'Active Sensing', 'Meta Event');

   MIDI_Status_Bytes: TMIDI_Status_Array_Bytes = (
                  mc_MIDI_Note_Off, mc_MIDI_Note_on, mc_MIDI_Polyphonic_Aftertouch,
                  mc_MIDI_Control_Change, mc_MIDI_Program_Change,
                  mc_MIDI_Channel_Aftertouch, mc_MIDI_Pitch_Bend,
                  mc_MIDI_System_Message, mc_MIDI_Begin_SysEx,
                  mc_MIDI_MTC_Quarter_Frame, mc_MIDI_Song_Pos_Ptr,
                  mc_MIDI_Song_Select, mc_MIDI_End_SysEx, mc_MIDI_Timing_Clock,
                  mc_MIDI_Start, mc_MIDI_Continue, mc_MIDI_Stop,
                  mc_MIDI_Active_Sensing, mc_MIDI_Meta_Event);

type
   {-------------------------------------------------------------------}
   { This is the information about the control that must be accessed by
     the MIDI input callback function in the DLL at interrupt time }
   PMidiCtlInfo = ^TMidiCtlInfo;
   TMidiCtlInfo = record
      hMem: THandle;             { Memory handle for this record }
      PBuffer: PCircularBuffer;  { Pointer to the MIDI input data buffer }
      hWindow: HWnd;             { Control's window handle }
      SysexOnly: Boolean;        { Only process System Exclusive input }
   end;

   { Information for the output timer callback function, also required at
     interrupt time. }
   PMidiOutTimerInfo = ^TMidiOutTimerInfo;
   TMidiOutTimerInfo = record
      hMem: THandle;             { Memory handle for this record }
      PBuffer: PCircularBuffer;  { Pointer to MIDI output data buffer }
      hWindow: HWnd;             { Control's window handle }
      TimeToNextEvent: uInt32;   { Delay to next event after timer set }
      MIDIHandle: HMidiOut;      { MIDI handle to send output to
                           (copy of component's FMidiHandle property) }
      PeriodMin: uInt16;         { Multimedia timer minimum period supported }
      PeriodMax: uInt16;         { Multimedia timer maximum period supported }
      TimerId: uInt16;           { Multimedia timer ID of current event }
   end;

   {-------------------------------------------------------------------}
   { A MIDI input/output event }
   TMIDI_Event = class (TPersistent)
   private
      FMidiMessage: uInt8;            // MIDI message status uInt8
      FData1: uInt8;                  // MIDI message data 1 uInt8
      FData2: uInt8;                  // MIDI message data 2 uInt8
      FTime:  uInt32;                // Time in ms since midiInOpen
      FPort:  Int32;

   protected
      function  get_event_index: TMIDI_Status;
      function  get_text_time: AnsiString;
      function  get_text_event: AnsiString; virtual;
      function  get_text_channel: AnsiString;
      function  get_text_data_byte1: AnsiString; virtual;
      function  get_text_data_byte2: AnsiString; virtual;
      function  get_size: uInt32; virtual;
      procedure set_time (time: uInt32);
      function  get_event_type: uInt8;
      procedure set_event_type (event: uInt8);
      function  get_channel: TMIDI_Range;
      procedure set_channel (channel: TMIDI_Range);
      procedure set_data_byte_1 (b: uInt8);
      procedure set_data_byte_2 (b: uInt8);
      procedure set_port (track: Int32);
      function  get_midi_status: TMIDI_Status;
      function  get_text_text: AnsiString; virtual;
      function  get_text_translated: AnsiString; virtual;

   public
      SysexLength: uInt16;          // Length of sysex data (0 if none)
// S.S. have to make this PByte
//      Sysex: PChar;                 // Pointer to sysex data buffer
      Sysex: PByte;                 // Pointer to sysex data buffer

      constructor Create; overload;
      constructor Create (t: Int32; c: TMIDI_Range; e, v, s: uInt8); overload; virtual;
      destructor Destroy; override;
      procedure read_event (var f: TMIDI_File);
      procedure write_event (var f: TMIDI_File); virtual;
      procedure load (var input: TextFile);
      procedure save (var output: TextFile);
      function  copy_event: TMIDI_Event;

      property Size: uInt32 read get_size;
      property Time: uInt32 read FTime write set_time;
      property MIDI_Message: uInt8 read FMIDIMessage write FMIDIMessage;
      property Event_Type: uInt8 read get_event_type write set_event_type;
      property Channel: TMIDI_Range read get_channel write set_channel;
      property Data_Byte_1: uInt8 read FData1 write set_data_byte_1;
      property Data_Byte_2: uInt8 read FData2 write set_data_byte_2;
      property Port: Int32 read FPort write set_port;
      property Status: TMIDI_Status read get_midi_status;
      property Translated: AnsiString read get_text_translated;
   end; // Class: TMIDI_Event //

   TMeta_Event = class (TMIDI_Event)
   private
      FText: AnsiString;

   protected
      function  get_length: uInt32;
      function  get_size: uInt32; override;
      function  get_text_text: AnsiString; override;
      procedure set_text_text (value: AnsiString);
      function  get_text_translated: AnsiString; override;

   public
      constructor Create (meta: uInt8; text: AnsiString);
      procedure write_event (var f: TMIDI_File); override;

      property Text_Length: uInt32 read get_length;
      property Text: AnsiString read get_text_text write set_text_text;
   end; // Class: TMeta_Event //

   PMyMidiEvent = ^TMIDI_Event;

// Encapsulates the MIDIHDR with its memory handle and sysex buffer
   PMyMidiHdr = ^TMyMidiHdr;
   TMyMidiHdr = class (TObject)
   public
      hdrHandle: THandle;
      hdrPointer: PMIDIHDR;
      sysexHandle: THandle;
      sysexPointer: Pointer;

      constructor Create (BufferSize: uInt16);
      destructor Destroy; override;
   end; // Class: TMyMidiHdr //

function  is_note_off (event: TMIDI_Event): boolean;
function  is_note_on  (event: TMIDI_Event): boolean;
function  measure_to_n32 (measures, Beats, Rythm: Int32): Int32;
procedure n32_to_measures (n32, Beats, Rythm: Int32; var measures, rest: Int32);
function  n32_to_seconds (n32nds, BPM: Int32): double;
function  seconds_to_n32 (seconds: double; BPM: Int32): Int32;

implementation

// The following two routines test whether an event is a note on or a
// note off event. Beware: is_note_on is not equal to not is_note_off
// That's why two routines are provided.
function is_note_off (event: TMIDI_Event): boolean;
begin
   Result := (event.Event_Type = mc_MIDI_Note_Off) or
            ((event.Event_Type = mc_MIDI_Note_On) and (event.Data_byte_2 = 0));
end; // is_note_off //

function is_note_on (event: TMIDI_Event): boolean;
begin
   Result := (event.Event_Type = mc_MIDI_Note_On) and (event.Data_byte_2 > 0);
end; // is_note_on //

// Converts a measure to 32nd notes
function measure_to_n32
(
   measures,      // Number of measures
   Beats,         // Beats of the measure (e.g. 3/8, beats is 3)
   Rythm: Int32   // Denominatore of a measure (in above example 8)
): Int32;
begin
   Result := Measures * 32 * Beats div Rythm;
end; // measure_to_n32 //

// cimplimentary procedure
procedure n32_to_measures
(
   n32,           // Number of measures
   Beats,         // Beats of the measure (e.g. 3/8, beats is 3)
   Rythm: Int32;  // Denominatore of a measure (in above example 8)
   var measures,  // number of measures returned
   rest: Int32    // and the rest of the 32'nds
);
begin
   measures := (n32 * Rythm) div (32 * Beats);
   rest     := (n32 * Rythm) mod (32 * Beats);
end; // measure_to_n32 //

// converts a given number of 32nds to seconds
function n32_to_seconds
(
   n32nds,     // number of 32nd notes
   BPM: Int32  // number of quarter notes in a minute
): double;
begin
   Result := (60 * n32nds) / (8 * BPM);
end; // n32_to_seconds //

// Converts seconds to a rounded amount of 32nd notes
function seconds_to_n32
(
   seconds: double;  // number of seconds
   BPM: Int32        // beats per minute (=quarter notes per minute)
): Int32;
begin
   Result := Round (seconds * 8 * BPM / 60);
end; // seconds_to_n32 //

{*******************************************************************
*                                                                  *
* Class TMIDI_Event                                                *
*                                                                  *
********************************************************************}

constructor TMIDI_Event.Create;
begin
   inherited Create;

   Time        := 0;
   Channel     := 1;
   Event_Type  := 0;
   Data_Byte_1 := 0;
   Data_Byte_2 := 0;
end; // Create //

constructor TMIDI_Event.Create
(
   t: Int32;       // Time at which the event occurs
   c: TMIDI_Range; // Midi channel of the event [1..16]
   e,              // Event type (i.e. note on, patch etc...)
   v,              // Value (data uInt8 1)
   s: uInt8        // Speed (data uInt8 2)
);
begin
   inherited Create;

   Time        := t;
   Channel     := c;
   Event_Type  := e;
   Data_Byte_1 := v;
   Data_Byte_2 := s;
end; // Create //

destructor TMIDI_Event.Destroy;
// Free any sysex buffer associated with the event
begin
   if (Sysex <> Nil)
      then Freemem (Sysex, SysexLength);

   inherited Destroy;
end; // Destroy //

// Size of the raw MIDI event, used by reading and writing files
function TMIDI_Event.get_size: uInt32;
begin
   Result := 3;
   if (event_type = mc_MIDI_Program_Change) or
      (event_type = mc_MIDI_Channel_Aftertouch) then Result := 2;
end; // get_size //

procedure TMIDI_Event.set_time (time: uInt32);
begin
   FTime := time;
end; // set_time //

procedure TMIDI_Event.set_channel (channel: TMIDI_Range);
// Put channel in FMidiMessage
begin
   FMIDIMessage := ((FMIDIMessage and $F0) or (channel - 1));
end; // set_channel //

function TMIDI_Event.get_channel: TMIDI_Range;
begin
   Result := (FMIDIMessage and $0F) + 1;
end; // get_channel //

procedure TMIDI_Event.set_event_type (event: uInt8);
// Put event into FMidiMessage
begin
   FMIDIMessage := ((FMIDIMessage and $0F) or event);
end; // set_event_type //

function TMIDI_Event.get_event_type: uInt8;
begin
   Result := FMidiMessage and $F0;
end; // get_event_type //

function TMIDI_Event.get_event_index: TMIDI_Status;
var ms: TMIDI_Status;
begin
   Result := ms_Note_Off; // Avoid compiler warnings
   for ms := Low (TMIDI_Status) to High (TMIDI_Status) do
   begin
      if MIDI_Status_Bytes [ms] = Event_Type then
      begin
         Result := ms;
         Exit;
      end; // if
   end; // for
end; // get_event_index //

procedure TMIDI_Event.set_data_byte_1 (b: uInt8);
begin
   FData1 := b;
end; // set_data_byte_1 //

procedure TMIDI_Event.set_data_byte_2 (b: uInt8);
begin
   FData2 := b;
end; // set_data_byte_2 //

function TMIDI_Event.get_midi_status: TMIDI_Status;
var status_byte: uInt8;
begin
   if FMIDIMessage < $F0
      then status_byte := FMidiMessage and $F0
      else status_byte := FMIDIMessage;

   case status_byte of
      mc_MIDI_Note_off:             Result := ms_Note_Off;
      mc_MIDI_Note_On:              Result := ms_Note_On;
      mc_MIDI_Polyphonic_Aftertouch:Result := ms_Polyphonic_Aftertouch;
      mc_MIDI_Control_Change:       Result := ms_Controller_Change;
      mc_MIDI_Program_Change:       Result := ms_Program_Change;
      mc_MIDI_Channel_Aftertouch:   Result := ms_Channel_Aftertouch;
      mc_MIDI_Pitch_Bend:           Result := ms_Pitch_Bend;
      mc_MIDI_Begin_SysEx:          Result := ms_Begin_SysEx;
      mc_MIDI_MTC_Quarter_Frame:    Result := ms_MTC_Quarter_Frame;
      mc_MIDI_Song_Pos_Ptr:         Result := ms_Song_Pos_Ptr;
      mc_MIDI_Song_Select:          Result := ms_Song_Select;
      mc_MIDI_End_SysEx:            Result := ms_End_SysEx;
      mc_MIDI_Timing_Clock:         Result := ms_Timing_Clock;
      mc_MIDI_Start:                Result := ms_Start;
      mc_MIDI_Continue:             Result := ms_Continue;
      mc_MIDI_Stop:                 Result := ms_Stop;
      mc_MIDI_Active_Sensing:       Result := ms_Active_Sensing;
      mc_MIDI_Meta_Event:           Result := ms_Meta;
      else                          Result := ms_Unknown;
   end; // case
end; // get_midi_status //

procedure TMIDI_Event.set_port (track: Int32);
begin
   FPort := track;
end; // set_port //

function TMIDI_Event.get_text_time: AnsiString;
begin
   Result := AnsiStrings.Format ('%d', [time]);
end; // get_text_time //

function TMIDI_Event.get_text_channel: AnsiString;
begin
   Result := AnsiStrings.Format ('%d', [channel]);
end; // get_text_channel //

function TMIDI_Event.get_text_event: AnsiString;
var ms: TMIDI_Status;
begin
   ms := get_event_index;
   Result := MIDI_Status_Names [ms];
end; // get_text_event //

function TMIDI_Event.get_text_data_byte1: AnsiString;
begin
   Result := AnsiStrings.Format ('%d', [Data_Byte_1]);
   case Event_Type of
      mc_MIDI_Control_Change: Result := AnsiStrings.Format ('Controller %3d', [Data_Byte_1]);
      mc_MIDI_Program_Change: Result := AnsiStrings.Format ('Patch %3d', [Data_Byte_1]);
   end; // case
end; // get_text_data_byte1 //

function TMIDI_Event.get_text_data_byte2: AnsiString;
begin
   Result := AnsiStrings.Format ('%d', [Data_Byte_2]);
end; // get_text_data_byte2 //

function TMIDI_Event.get_text_text: AnsiString;
begin
   Result := '';
end; // get_text_text //

function TMIDI_Event.get_text_translated: AnsiString;
begin
   Result := AnsiStrings.Format ('%s: %s %s (%s, %s)',
                [get_text_time, get_text_event, get_text_channel,
                 get_text_data_byte1, get_text_data_byte2]);
end; // get_text_translated //

procedure TMIDI_Event.read_event (var f: TMIDI_File);
var db1, db2: uInt8;
begin
   Read (f, FMIDIMessage);
   if Size = 2 then Read (f, db1)
               else Read (f, db1, db2);
   Data_Byte_1 := db1;
   Data_Byte_2 := db2;
end; // read_event //

procedure TMIDI_Event.write_event (var f: TMIDI_File);
begin
   write (f, MIDI_Message);
   write (f, Data_Byte_1);
   if size = 3 then write (f, Data_Byte_2);
end; // write_event //

procedure TMIDI_Event.load (var input: TextFile);
var ltime: cardinal;
    lchannel: TMIDI_Range;
    let, ldb1, ldb2: uInt8;
    lport: Int32;
begin
   readln (input, ltime, lchannel, let, ldb1, ldb2, lport);
   Time        := ltime;
   Event_Type  := let;
   Channel     := lchannel;
   Data_Byte_1 := ldb1;
   Data_Byte_2 := ldb2;
   Port        := lport;
end; // load //

procedure TMIDI_Event.save (var output: TextFile);
begin
   writeln (output, Time, ' ', Channel, ' ', Event_Type, ' ',
                    Data_Byte_1, ' ', Data_Byte_2, ' ', Port);
end; // save //

function TMIDI_Event.copy_event: TMIDI_Event;
begin
   if MIDI_Message = mc_MIDI_Meta_Event
      then Result := TMeta_Event.Create (Data_Byte_1, (Self as TMeta_Event).Text)
      else Result := TMIDI_Event.Create (time, channel, event_type, Data_Byte_1, Data_Byte_2);
{
   case Event_Type of
      mc_MIDI_Note_off,
      mc_MIDI_Note_On,
      mc_MIDI_Polyphonic_Aftertouch,
      mc_MIDI_Control_Change,
      mc_MIDI_Program_Change,
      mc_MIDI_Channel_Aftertouch,
      mc_MIDI_Pitch_Bend: Result := TMIDI_Event.Create (Time, Channel, Event_Type, Data_Byte_1, Data_Byte_2);
      else
      begin
         if Event_Type = mc_MIDI_Meta_Event
            then Result := TMeta_Event.Create (event_type, (Self as TMeta_Event).Text)
            else Result := TMIDI_Event.Create (time, channel, event_type, Data_Byte_1, Data_Byte_2);
      end; // else
   end; // case
}
   Result.Port := Port;
end; // copy_event //

{*******************************************************************
*                                                                  *
* Class TMeta_Event                                                *
*                                                                  *
********************************************************************}

constructor TMeta_Event.Create (meta: uInt8; text: AnsiString);
begin
   inherited Create;

   MIDI_Message := $FF;
   Data_Byte_1  := meta;
   Data_Byte_2  := Length (text);
   Self.Text    := text;
end; // Create //

// Size of a meta event
function TMeta_Event.get_size: uInt32;
begin
   Result := 3 + Data_Byte_2;
end; // get_size //

function TMeta_Event.get_length: uInt32;
begin
   Result := Length (FText);
end; // get_length //

function TMeta_Event.get_text_text: AnsiString;
begin
   Result := FText;
end; // get_text_text //

procedure TMeta_Event.set_text_text (value: AnsiString);
begin
   FText := value;
end; // set_text_text //

function TMeta_Event.get_text_translated: AnsiString;
var s, t: AnsiString;
begin
   s := AnsiString (Text);
   Result := s;
   case Data_Byte_1 of
      mc_Meta_Sequence_Number:   if Length (s) = 2
         then t := AnsiStrings.Format ('Sequence number: %d', [convert_to_word (Ord (AnsiChar (s [1])), Ord (AnsiChar (s [2])))])
         else t := AnsiStrings.Format ('Sequence number: %s', [s]);
      mc_Meta_Text_Event:        t := AnsiStrings.Format ('Text: %s', [s]);
      mc_Meta_Copyright_Notice:  t := AnsiStrings.Format ('Copyright: %s', [s]);
      mc_Meta_Track_Name:        t := AnsiStrings.Format ('Track name: %s', [s]);
      mc_Meta_Instrument_Name:   t := AnsiStrings.Format ('Instrument name: %s', [s]);
      mc_Meta_Lyric:             t := AnsiStrings.Format ('Lyric: %s', [s]);
      mc_Meta_Marker:            t := AnsiStrings.Format ('Text marker: %s', [s]);
      mc_Meta_Cue_Point:         t := AnsiStrings.Format ('Cue point: %s', [s]);
      mc_Meta_Channel_Prefix:    t := AnsiStrings.Format ('Channel prefix: %s', [s]);
      mc_Meta_End_Of_Track:      t := AnsiStrings.Format ('EOT', []);
      mc_Meta_Set_Tempo:         t := AnsiStrings.Format ('Set tempo: %d', [convert_to_cardinal (0, Ord (s [1]), Ord (s [2]), Ord (s [3]))]);
      mc_Meta_SMPTE_Offset:      t := AnsiStrings.Format ('SMPTE offset: %2.2x %2.2x %2.2x %2.2x %2.2x', [Ord (s [1]), Ord (s [2]), Ord (s [3]), Ord (s [4]), Ord (s [5])]);
      mc_Meta_Time_Signature:    t := AnsiStrings.Format ('Time signature: %2.2d %2.2d %2.2d %2.2d', [Ord (s [1]), Ord (s [2]), Ord (s [3]), Ord (s [4])]);
      mc_Meta_Key_Signature:     t := AnsiStrings.Format ('Key signature: %2.2x %2.2x', [Ord (S [1]), Ord (s [2])]);
      mc_Meta_Sequencer_Specific:t := AnsiStrings.Format ('Sysex 7F: %s', [s]);
      else                       t := AnsiStrings.Format ('Meta (%d) %s', [Data_Byte_1, s]);
   end; // case
   Result := t;
end; // get_text_translated //

procedure TMeta_Event.write_event (var f: TMIDI_File);
var i, b: uInt8;
begin
   b := $FF;
   write (f, b);
   b := data_byte_1;//event_type;
   write (f, b);
   b := Data_Byte_2;//length (Text);
   write (f, b);
   for i := 1 to length (Text) do
   begin
      b := ord (Text [i]);
      write (f, b);
   end; // for
end; // write_event //

{*******************************************************************
*                                                                  *
* Class TMyMidiHdr                                                 *
*                                                                  *
********************************************************************}

constructor TMyMidiHdr.Create (BufferSize: uInt16);
// Allocate memory for the sysex header and buffer
begin
   inherited Create;

   if BufferSize > 0 then
   begin
      hdrPointer := GlobalSharedLockedAlloc (sizeof (TMIDIHDR), hdrHandle);
      sysexPointer := GlobalSharedLockedAlloc (BufferSize, sysexHandle);

      hdrPointer^.lpData := sysexPointer;
      hdrPointer^.dwBufferLength := BufferSize;
      hdrPointer^.dwBytesRecorded := BufferSize; // S.S. added for Stream-support
   end; // if
end; // Create //

destructor TMyMidiHdr.Destroy;
begin
   GlobalSharedLockedFree (hdrHandle, hdrPointer);
   GlobalSharedLockedFree (sysexHandle, sysexPointer);

   inherited Destroy;
end; // Destroy //

end. // Unit: MIDI_Events //
