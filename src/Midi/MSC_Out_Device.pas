{ $Header: /MidiComp/MidiOut.pas 2     10/06/97 7:33 Davec $ }

{ Written by David Churcher <dchurcher@cix.compulink.co.uk>, released to the
  public domain. GetDeviceList added 12/25/16 by Scott Swift dxzl@live.com}

{ Thanks very much to Fred Kohler for the Technology code. }

{
S.S.
WinAPI: midiOutOpen - Opens the MIDI output device
In addition to PostMessage timeGetSystemTime timeGetTime timeSetEvent timeKillEvent midiOutShortMsg midiOutLongMsg OutputDebugString, but also can not have the data in the fixed data segment; In addition to the PostMessage timeGetSystemTime timeGetTime timeKillEvent midiOutShortMsg midiOutLongMsg OutputDebugString, but also can not have other system calls
// Disclaimer: ... read more
WinAPI: midiOutCacheDrumPatches - Pre-installed drum sounds
Summary: Tip: Each parameter in the three arrays represents one of the 128 drum sounds; the MIDI channel is represented by 0-15, for example, channels 9 and 15 use the tone on the 60 key, the 60th element is the $ 8200
// declare: midiOutCacheDrumPatches (hMidiOut: HMIDIOUT; (device handle; this device should be internal synthesizer) uPatch:. UINT; (a drum ... read more
WinAPI: midiOutCachePatches - Preset sound
Summary: Tip: Each of the three parameters in a parameter array represents one of 128 tones; the MIDI channel is represented by 0..15, such as 0 and 8 for channels 0 and 8, and the 0th element of the array is $ 0101
// declare: midiOutCachePatches (hMidiOut: HMIDIOUT; (device handle; this device should be internal synthesizer) uBank: UINT; (specify tone group; lack of ... read more
WinAPI: midiOutSetVolume - Sets the volume of the MIDI output device
The lower two bits are the left channel volume, the upper two bits are the right channel volume; $ FFFF is the maximum, $ 0000 is the new volume value; the lower two bits are the left channel volume; the second two bits are the right channel volume; $ FFFF is the maximum, $ 0000 is minimum)): MMRESULT; (return 0 if successful; possible error values are as follows:) MMSYSERR_INVALHANDLE = 5; (device handle is invalid) MMSYSE ... read more
WinAPI: midiOutGetVolume - Gets the volume of the MIDI output device
PDWORD (returns the address of the volume; the lower two bits are the left channel volume, and the upper two bits are the right channel volume; $ FFFF is the maximum, $ 0000 is the audio volume of the left channel. minimum)): MMRESULT; (return 0 if successful; possible error values are as follows:) MMSYSERR_INVALHANDLE = 5; ... read more
WinAPI: midiOutGetErrorText - Get the error description based on the error number
Summary: Hint: the length of the error text is generally not more than MAXERRORLENGTH = 128; If the buffer is too small, the text will be truncated.
// Statement: midiOutGetErrorText (mmrError: MMRESULT; (error number) lpText: PChar; buffer size UINT ()): MMRESULT; (return 0 if successful ... read More
WinAPI: midiOutMessage - Sends a message to the MIDI output device
(Message) dw1: DWORD (message parameter) dw2: DWORD (message parameter)): MMRESULT; (function successfully returns the message sent) / / (message) / example: read more
WinAPI: midiOutLongMsg - Sends a system-specific MIDI message to the output device
Also call GlobalAlloc to allocate memory (using GMEM_MOVEABLE, GMEM_SHARE) to TMidiHdr and the buffer to which lpData points, and lock it with GlobalLock.
// Declarations: midiOutLongMsg (hMidiOut (hMidiOut) : HMIDIO ... read more
WinAPI: midiOutShortMsg - Send a MIDI short message to the output device
Summary: Hint: This function can send any MIDI messages other than the system-specific message; it is not returned until it has been sent to the output device.
// Declarations: midiOutShortMsg (hMidiOut: HMIDIOUT; (device handle) dwMsg: DWORD (MIDI message; byte, the first byte in the post)): MMRESULT; (return 0 if successful; possible error values below:) MMSY ... read more
WinAPI: midiOutGetDevCaps - Query output device performance
(MIDESID: UINT; (device ID) lpCaps: PMidiOutCaps; (TMidiOutCaps structure pointer) uSize: UINT (size of TMidiOutCaps structure)): MMRESULT; (return 0 successfully; Possible error values ??are listed below. :) MMSYSERR_BAD ... read more
WinAPI: midiOutReset - Resets the output device
// declaration: midiOutReset (hMidiOut: HMIDIOUT (device handle)): MMRESULT; (return 0 if successful; Possible error value (return value: 0); return the value of the return value to the program; below:) MMSYSERR_INVALHANDLE = 5; ()
// device handle is invalid example: read more
WinAPI: midiOutGetID - Gets the output device ID
(MYSESULT); (return 0 for success; Possible error values ??are as follows:) MMSYSERR_INVALHANDLE = 5;) (getIndexDetailID) (getIndicatorID) (PUMP ( ()
// device handle is invalid example: read more
WinAPI: midiOutClose - Turns off the output device
If a buffer that has been sent to the midiOutLongMsg function has not been returned to the program, the function will fail; calling midiOutReset will mark all pending buffers as executed.
// Declarations: If the buffer is not returned to the program, midiOutClose (hMidiOut: HMIDIOUT (device handle)): MMRESULT; (return 0 if successful; possible error values below:) MMSYSERR_INV ... read more
WinAPI: midiOutGetNumDevs - Gets the number of MIDI output devices
Abstract:
// Declare: midiOutGetNumDevs: UINT; (no parameters; Returns the number of MIDI output devices)
// Example: Read more
WinAPI: midiOutUnprepareHeader - Clears the preparation done by midiOutPrepareHeader
This function must be called after the device full buffer is returned to the program; this function must be called before the GlobalFree buffer is freed; canceling a buffer that is not yet ready will not work, but the function returns 0
// declaration: midiOutUnprepareHeader (hMidiOut: HMIDIOUT; (device handle) lpMidiOutHdr: PMidiHdr; (TMidiHdr structure pointer) uSize: UI ... read more
}

unit MSC_Out_Device;

{
  MIDI Output component.

  Properties from base class (TMIDI_Device):

   Error: uInt16, The error code for the last MMSYSTEM error. See the MMSYSERR_
   entries in MMSYSTEM.INT for possible values.

   DriverVersion: Int32, Version number of the driver

   DeviceList: TStringList, List of devices
    (DeviceList.Objects contains the DeviceID, DeviceList.Strings
    contains the ProductName)

   NumDevs: Int32, Number of devices

   DeviceID: Int32, Windows numeric device ID for the MIDI output device.
    Between 0 and (midiOutGetNumDevs-1), or MIDI_MAPPER (-1).
    Special value MIDI_MAPPER specifies output to the Windows MIDI mapper
    Read-only while device is open, exception if changed while open

   MID and PID: Manufacturer ID and Product ID, see
   "Manufacturer and Product IDs" in MMSYSTEM.HLP for list of possible values.

   DriverVersion: Version number of MIDI device driver. High-order uInt16 is
    major version, low-order byte is minor version.

   ProductName: Name of the output device product that corresponds to the
    DeviceID property (e.g. 'MPU 401 out').
    You can write to this while the device is closed to select a particular
    output device by name (the DeviceID property will change to match).
    Exception if this property is changed while the device is open.

  Properties:

   MIDIHandle: The output handle to the MIDI device.
    0 when device is not open
    Read-only, runtime-only

   Technology: Type of technology used by the MIDI device. You can set this
    property to one of the values listed for OutportTech (below) and the component
    will find an appropriate MIDI device. For example:
    MidiOutput.Technology := opt_FMSynth;
    will set MidiInput.DeviceID to the MIDI device ID of the FM synth, if one
    is installed. If no such device is available an exception is raised,
    see MidiOutput.SetTechnology.

   See the MIDIOUTCAPS entry in MMSYSTEM.HLP for descriptions of the
   following properties:
      DriverVersion
      Voices
      Notes
      ChannelMask
      Support

   Methods:
   Open: Open MIDI device specified by DeviceID property for output

   Close: Close device

   PutMidiEvent(Event:TMyMidiEvent): Output a note or sysex message to the
   device. This method takes a TMyMidiEvent object and transmits it.
   Notes:
     1. If the object contains a sysex event the OnMidiOutput event will
        be triggered when the sysex transmission is complete.
     2. You can queue up multiple blocks of system exclusive data for
        transmission by chucking them at this method; they will be
       transmitted as quickly as the device can manage.
     3. This method will not free the TMyMidiEvent object, the caller
        must do that. Any sysex data in the TMyMidiEvent is copied before
       transmission so you can free the TMyMidiEvent immediately after
       calling PutMidiEvent, even if output has not yet finished.

   PutShort(MidiMessage: uInt8; Data1: uInt8; Data2: uInt8): Output a short
   MIDI message. Handy when you can't be bothered to build a TMyMidiEvent.
   If the message you're sending doesn't use Data1 or Data2, set them to 0.

   PutLong(TheSysex: Pointer; msgLength: uInt16): Output sysex data.
      SysexPointer: Pointer to sysex data to send
      msgLength: Length of sysex data.
   This is handy when you don't have a TMyMidiEvent.

   SetVolume(Left: uInt16, Right: uInt16): Set the volume of the
   left and right channels on the output device (only on internal devices?).
   0xFFFF is maximum volume. If the device doesn't support separate
   left/right volume control, the value of the Left parameter will be used.
   Check the Support property to see whether the device supports volume
   control. See also other notes on volume control under midiOutSetVolume()
   in MMSYSTEM.HLP.

   Events:
   OnMidiOutput: Procedure called when output of a system exclusive block
   is completed.

   Notes:
   I haven't implemented any methods for midiOutCachePatches and
   midiOutCacheDrumpatches, mainly 'cause I don't have any way of testing
   them. Does anyone really use these?
}

interface

uses
  Classes, WinTypes, Messages, WinProcs, MMSystem, SysUtils,
  MSC_Definitions, MSC_Device, MSC_Circular_Buffer, MSC_Delphi_MIDI_Callback;

type
   midiOutputState = (mosOpen, mosClosed);
   EMSC_Device_Out_Error = class (EMSC_Device_Error);

   { These are the equivalent of constants prefixed with mod_
   as defined in MMSystem. See SetTechnology }
   OutPortTech = (
   opt_None,         { none }
   opt_MidiPort,     { output port }
   opt_Synth,        { generic internal synth }
   opt_SQSynth,      { square wave internal synth }
   opt_FMSynth,      { FM internal synth }
   opt_Mapper);      { MIDI mapper }
   TechNameMap = array [OutPortTech] of string [18];


const
   TechName : TechNameMap = (
        'None', 'MIDI Port', 'Generic Synth', 'Square Wave Synth',
        'FM Synth', 'MIDI Mapper');

{-------------------------------------------------------------------}
type
   TMIDI_Device_Output = class (TMIDI_Device)

   protected
      FState: midiOutputState;   // Current device state
      FMIDIHandle: HmidiOut;     // Handle to output device
      PCtlInfo: PMidiCtlInfo;    // Pointer to control info for DLL
      PBuffer: PCircularBuffer;  // Output queue for PutTimedEvent, set by Open

      // Stuff from midiOutCAPS
      FTechnology: OutPortTech;  // Type of MIDI output device
      FVoices: uInt16;           // Number of voices (internal synth)
      FNotes: uInt16;            // Number of notes (internal synth)
      FChannelMask: uInt16;      // Bit set for each MIDI channels that the
                                 // device responds to (internal synth)
      FSupport: uInt32;          // Technology supported (volume control,
                                 // patch caching etc.
      FVolume: Boolean;          // True if volume control is supported
      FLRVolume: Boolean;        // True if independent volume control is supported for each sereo channel
      FPatchCache: Boolean;      // True if patch caching is supported
      FStream: Boolean;          // True if opening output for streaming events
      FOnMIDIOutput: TNotifyEvent; // Sysex output finished

      function  midiOutErrorString (WError: uInt16): String;
      function GetDeviceList: TStringList; override;
      procedure SetDeviceID (DeviceID: Int32); override;
      procedure MidiOutput (var Message: TMessage);
      procedure SetProductName (NewProductName: String); override;
      procedure SetTechnology (NewTechnology : OutPortTech);
      procedure PutMidi (TheSysex: Pointer; msgLength: uInt16; bUseStream: Boolean);

  public
      constructor Create (AOwner:TComponent); override;
      destructor Destroy; override;
      function Open: Boolean; override;
      function Close: Boolean; override;
      function is_opened: Boolean; override;
      function is_closed: Boolean; override;
      function Status: midiOutputState;
      procedure PutMidiEvent (theEvent: TMIDI_Event); virtual;
      procedure PutShort (MidiMessage: uInt8; Data1: uInt8; Data2: uInt8); virtual;
      procedure PutLong (TheSysex: Pointer; msgLength: uInt16); virtual;
      procedure PutStream (TheSysex: Pointer; msgLength: uInt16); virtual;
      procedure SetVolume (Left: uInt16; Right: uInt16);
      procedure SetStreamTimeDiv (TimeDiv: Int32);
      procedure SetStreamTempo (Tempo: Int32);
      procedure StreamReStart;
      procedure StreamStop;

      property MIDIHandle: HmidiOut read FMIDIHandle;
      property Technology: OutPortTech   // Type of MIDI output device
          read FTechnology write SetTechnology default opt_Synth;
      property Voices: uInt16 read FVoices; // Number of voices (internal synth)
      property Notes: uInt16 read FNotes;   // Number of notes (internal synth)
      property ChannelMask: uInt16 read FChannelMask; // Bit set for each MIDI channels that the
                                                    // device responds to (internal synth)
      property Support: uInt32    read FSupport; // Technology supported (volume control, patch caching etc.
      property Volume: Boolean read FVolume; // True if device supports volume, else False
      property LRVolume: Boolean read FLRVolume; // True if device supports independent volume settings
                                                 // for right and left channel
      // Set Stream before calling Open()!
      // True if you are opening a stream of events for output via PutStream(), False
      // if outputting via PutLong() and PutShort(). Defaults False;
      property Stream: Boolean read FStream write FStream default False;

      property PatchCache: Boolean read FPatchCache; // True if device supports Patch caching

   published
      property OnMIDIOutput: TNotifyEvent read FOnMIDIOutput write FOnMIDIOutput;
end; // Class: mTMidiOutput //

procedure Register;

{-------------------------------------------------------------------}
implementation

{-------------------------------------------------------------------}
procedure Register;
begin
   RegisterComponents (MSC_Package_Name, [TMIDI_Device_Output]);
end; // Register

{-------------------------------------------------------------------}
constructor TMIDI_Device_Output.Create(AOwner:TComponent);
begin
  inherited Create(AOwner);

  FState := mosClosed;
  FNumdevs := midiOutGetNumDevs;
  FStream := False;

  { Create the window for callback notification }
  if not (csDesigning in ComponentState) then
  begin
     Handle := AllocateHwnd(MidiOutput);
  end; // if
end; // Create //

{-------------------------------------------------------------------}
destructor TMIDI_Device_Output.Destroy;
begin
   if FState = mosOpen then Close;
   if (PCtlInfo <> Nil) then GlobalSharedLockedFree( PCtlinfo^.hMem, PCtlInfo );
   DeallocateHwnd(Handle);
   inherited Destroy;
end; // Destroy //

{-------------------------------------------------------------------}
{ Convert the numeric return code from an MMSYSTEM function to a string
  using midiOutGetErrorText. TODO: These errors aren't very helpful
  (e.g. "an invalid parameter was passed to a system function") so
  some proper error strings would be nice. }
function TMIDI_Device_Output.midiOutErrorString (WError: uInt16): String;
var errorDesc: PChar;
begin
   errorDesc := Nil;
   try
      errorDesc := StrAlloc (MAXERRORLENGTH);
      if midiOutGetErrorText( WError, errorDesc, MAXERRORLENGTH) = 0
         then result := StrPas (errorDesc)
         else result := 'Specified error number is out of range';
   finally
      If errorDesc <> Nil Then StrDispose(errorDesc);
   end; // try
end; // midiOutErrorString //

{-------------------------------------------------------------------}
{ Set the output device ID and change the other properties to match }
procedure TMIDI_Device_Output.SetDeviceID (DeviceID: Int32);
var
   midiOutCaps: TmidiOutCaps;
begin
   if FState = mosOpen then
   begin
      raise EMSC_Device_Out_Error.Create('Change to DeviceID while device was open')
   end else
   begin
      if (DeviceID >= Int32 (midiOutGetNumDevs)) And (DeviceID <> Int32 (MIDI_MAPPER)) then
      begin
         raise EMSC_Device_Out_Error.Create('Invalid device ID')
      end else
      begin
         FDeviceID := DeviceID;

// Set the name and other midiOutCAPS properties to match the ID
         FError := midiOutGetDevCaps (DeviceID, @midiOutCaps, sizeof (TmidiOutCaps));
         if Ferror > 0 then raise EMSC_Device_Out_Error.Create (midiOutErrorString (FError));

         with midiOutCaps do
         begin
            FProductName   := string (StrPas(szPname));
            FDriverVersion := vDriverVersion;
            FTechnology    := OutPortTech (wTechnology);
            FVoices        := wVoices;
            FNotes         := wNotes;
            FChannelMask   := wChannelMask;
            FSupport       := dwSupport;
            FVolume        := boolean (dwSupport and MIDICAPS_VOLUME);
            FLRVolume      := boolean (dwSupport and MIDICAPS_LRVOLUME);
            FPatchCache    := boolean (dwSupport and MIDICAPS_CACHE);
         end; // with
      end; // if
   end; // if
end; // SetDeviceID //

{-------------------------------------------------------------------}
{ Populates FDeviceList, a TStringList handled by the base class
  This is called every time you access the read-only DeviceList property }
function TMIDI_Device_Output.GetDeviceList : TStringList;
var
  lOutCaps             : TMidiOutCaps;
  testDeviceID         : Int16;
begin
  inherited;

  Result := FDeviceList;

  if (FDeviceList = Nil) then exit;

  FDeviceList.Clear;

  TRY   // TRY..EXCEPT was adapted from file "DAV_MidiIO.pas"
    FNumDevs := midiOutGetNumDevs;
  EXCEPT
    FNumDevs := 0;
  end;

  // Iterate the MIDIMAPPER also (-1)
  if FNumDevs > 0 then
  for testDeviceID := -1 To FNumDevs-1 do
  begin
    FError := midiOutGetDevCaps(testDeviceID, @lOutCaps, sizeof(TMidiOutCaps));
    if Ferror = MMSYSERR_NOERROR then
        FDeviceList.AddObject(StrPas(lOutCaps.szPname), TObject(testDeviceID));
  end;
end;

{-------------------------------------------------------------------}
{ Set the product name property and put the matching output device number
  in FDeviceID.
  This is handy if you want to save a configured output/output device
  by device name instead of device number, because device numbers may
  change if users install or remove MIDI devices.
  Exception if output device with matching name not found,
  or if output device is open }
procedure TMIDI_Device_Output.SetProductName (NewProductName: String);
var
   midiOutCaps: TmidiOutCaps;
   testDeviceID: Int32;
   testProductName: String;
begin
   if FState = mosOpen
      then raise EMSC_Device_Out_Error.Create('Change to ProductName while device was open')
      else
      { Don't set the name if the component is reading properties because
      the saved Productname will be from the machine the application was compiled
      on, which may not be the same for the corresponding DeviceID on the user's
      machine. The FProductname property will still be set by SetDeviceID }
   if not (csLoading in ComponentState) then
   begin
      { Loop uses -1 to test for MIDI_MAPPER as well }
      for testDeviceID := -1 To (midiOutGetNumDevs-1) do
      begin
         FError := midiOutGetDevCaps(testDeviceID, @midiOutCaps, sizeof(TmidiOutCaps));
         if Ferror > 0
            then raise EMSC_Device_Out_Error.Create(midiOutErrorString(FError));
         testProductName := string (StrPas(midiOutCaps.szPname));
         if testProductName = NewProductName then
         begin
            FProductName := NewProductName;
            Break;
         end; // if
      end; // if
      if FProductName <> NewProductName
         then raise EMSC_Device_Out_Error.Create('MIDI output Device ' + NewProductName + ' not installed')
         else SetDeviceID(testDeviceID);
   end; // if
end; // SetProductName //

{-------------------------------------------------------------------}
{ Set the output technology property and put the matching output device
  number in FDeviceID.
  This is handy, for example, if you want to be able to switch between a
  sound card and a MIDI port }
procedure TMIDI_Device_Output.SetTechnology (NewTechnology: OutPortTech);
var
   midiOutCaps: TMidiOutCaps;
   testDeviceID: Int32;
   testTechnology: OutPortTech;
begin
   if FState = mosOpen
      then raise EMSC_Device_Out_Error.Create(
         'Change to Product Technology while device was open')
      else
   begin
       { Loop uses -1 to test for MIDI_MAPPER as well }
      for testDeviceID := -1 To (midiOutGetNumDevs-1) do
      begin
         FError :=
            midiOutGetDevCaps(testDeviceID,
               @midiOutCaps, sizeof(TMidiOutCaps));
         if Ferror > 0 then
            raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));
         testTechnology := OutPortTech(midiOutCaps.wTechnology);
         if testTechnology = NewTechnology then
         begin
            FTechnology := NewTechnology;
            Break;
         end; // if
      end; // for
         if FTechnology <> NewTechnology
            then raise EMSC_Device_Out_Error.Create('MIDI output technology ' +
               string (TechName [NewTechnology]) + ' not installed')
            else SetDeviceID(testDeviceID);
   end; // if
end; // SetTechnology //

{-------------------------------------------------------------------}
{$HINTS OFF} // Avoid warning of result never being used
function TMIDI_Device_Output.Open: Boolean;
var hMem: THandle;
begin
   Result := False;
   try
{ Create the control info for the DLL }
      if (PCtlInfo = Nil) then
      begin
         PCtlInfo := GlobalSharedLockedAlloc( Sizeof(TMidiCtlInfo), hMem );
         PctlInfo^.hMem := hMem;
      end; // if

      Pctlinfo^.hWindow := Handle;    { Control's window handle }

      if (FStream = True) then
      begin
      { MMRESULT midiStreamOpen( LPHMIDISTRM lphStream, LPUINT puDeviceID,
      DWORD cMidi, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen); }
          FError := midiStreamOpen(@FMidiHandle, @FDeviceId, 1,
                             uInt32 (@midiHandler),
                              uInt32 (PCtlInfo),
                               CALLBACK_FUNCTION);
      end else
      begin
          FError := midiOutOpen (@FMidiHandle, FDeviceId,
                              uInt32 (@midiHandler),
                              uInt32 (PCtlInfo),
                              CALLBACK_FUNCTION);
      end; //if

      If (FError <> 0) then
      begin
         raise EMSC_Device_Out_Error.Create(midiOutErrorString(FError))
      end else
      begin
         Result := True;
         FState := mosOpen;

      end; // if

   except
      if PCtlInfo <> Nil then
      begin
         GlobalSharedLockedFree(PCtlInfo^.hMem, PCtlInfo);
         PCtlInfo := Nil;
      end; // if
      raise;
   end; // try
end; // Open //
{$HINTS ON}

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.StreamStop;
begin
   if FState = mosOpen then
   begin
      FError := midiStreamStop(FMidiHandle);
      if Ferror <> MMSYSERR_NOERROR
         then raise EMSC_Device_Out_Error.Create(MidiOutErrorString (FError));
   end; // if
end; // ReStart //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.StreamReStart;
begin
   if FState = mosOpen then
   begin
      FError := midiStreamRestart(FMidiHandle);
      if Ferror <> MMSYSERR_NOERROR
         then raise EMSC_Device_Out_Error.Create(MidiOutErrorString (FError));
   end; // if
end; // ReStart //

{-------------------------------------------------------------------}
function TMIDI_Device_Output.Close: Boolean;
begin
   Result := False;
   if FState = mosOpen then
   begin

{ Note this sends a lot of fast control change messages which some synths can't handle.
 TODO: Make this optional. }
   {
      FError := midiOutReset(FMidiHandle);
      if Ferror <> 0 then
         raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));
   }
      if (Stream = True) then
      begin
          FError := midiStreamClose(FMidiHandle);
      end else
      begin
          FError := midiOutClose(FMidiHandle);
      end;

      if Ferror <> 0
         then raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError))
         else Result := True;
   end; // if

   FMidiHandle := 0;
   FState := mosClosed;
end; // Close //

function TMIDI_Device_Output.is_opened: boolean;
begin
   Result := Status = mosOpen;
end; // is_opened //

function TMIDI_Device_Output.is_closed: boolean; 
begin
   Result := Status = mosClosed;
end; // is_closed //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.PutShort (MidiMessage: uInt8; Data1: uInt8; Data2: uInt8);
var thisMsg: uInt32;
begin
   thisMsg := uInt32(MidiMessage) Or
      (uInt32(Data1) shl 8) Or
      (uInt32(Data2) shl 16);

   FError := midiOutShortMsg(FMidiHandle, thisMsg);
   if Ferror > 0
      then raise EMSC_Device_Out_Error.Create(midiOutErrorString(FError));
end; // PutShort//

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.PutLong (TheSysex: Pointer; msgLength: uInt16);
begin
    PutMidi (TheSysex, msgLength, False);
end;
{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.PutStream (TheSysex: Pointer; msgLength: uInt16);
begin
    PutMidi (TheSysex, msgLength, True);
end;
{-------------------------------------------------------------------}
{S.S. err = midiStreamOut(midiOutHandle, &midiHdr, sizeof(MIDIHDR));}
procedure TMIDI_Device_Output.PutMidi (TheSysex: Pointer; msgLength: uInt16; bUseStream: Boolean);
{ Notes: This works asynchronously; you send your sysex output by
calling this function, which returns immediately. When the MIDI device
driver has finished sending the data the callback in MSC_Delphi_MIDI_Callback
sends a PostMessage Mom_Done that the VCL message-handler processes and calls
the MidiOutPut function in this component, which will in turn call the
OnMidiOutput event-handler if the component user has defined one. }

var MyMidiHdr: TMyMidiHdr;
begin
   { Initialize the header and allocate buffer memory }
   MyMidiHdr := TMyMidiHdr.Create(msgLength);

   { Copy the data over to the MidiHdr buffer
     We can't just use the caller's PByte because the buffer memory
     has to be global, shareable, and locked. }
   MoveMemory(MyMidiHdr.SysexPointer, TheSysex, msgLength); // S.S. NEED THIS for it to work!!!!!!!!!
//   Move(MyMidiHdr.SysexPointer, TheSysex, msgLength);

   { Store the MyMidiHdr address in the header so we can find it again quickly
      (see the MidiOutput proc) }
   MyMidiHdr.hdrPointer^.dwUser := uInt32(MyMidiHdr);

   { Get MMSYSTEM's blessing for this header }
   {Handle can also be the handle of a MIDI stream cast to a HMIDIOUT type.}
   FError := midiOutPrepareHeader(FMidiHandle, MyMidiHdr.hdrPointer, sizeof(TMIDIHDR));
   if Ferror > 0
      then raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));

   { Send it
     Handle to the MIDI output device. This parameter can also be the handle
      of a MIDI stream cast to HMIDIOUT. If stream, set hdrPointer to Nil.
     Pointer to a MIDIHDR structure that identifies the MIDI buffer.
     Size, in bytes, of the MIDIHDR structure. }
   if bUseStream <> True
      then FError := midiOutLongMsg(FMidiHandle, MyMidiHdr.hdrPointer, sizeof(TMIDIHDR))
      else FError := midiStreamOut(FMidiHandle, MyMidiHdr.hdrPointer, sizeof(TMIDIHDR));
   if Ferror > 0
      then raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));
end; // PutLong //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.PutMidiEvent (theEvent: TMIDI_Event);
begin
   if FState <> mosOpen then
      raise EMSC_Device_Out_Error.Create('MIDI Output device not open');

   with theEvent do
   begin
      if Sysex = Nil
         then PutShort (MIDI_Message, Data_Byte_1, Data_Byte_2)
         else PutLong (Sysex, SysexLength);
   end; // with
end; // PutMidiEvent //

function TMIDI_Device_Output.Status: midiOutputState;
begin
   Result := FState;
end; // Status //

{-------------------------------------------------------------------}
// S.S.
procedure TMIDI_Device_Output.SetStreamTimeDiv (TimeDiv: Int32);
var
   prop: TMIDIPROPTIMEDIV;
begin
   prop.cbStruct := sizeof(TMIDIPROPTIMEDIV);
   prop.dwTimeDiv := TimeDiv;
   FError := midiStreamProperty(FMidiHandle, @prop, MIDIPROP_SET Or MIDIPROP_TIMEDIV);
   if Ferror <> 0 then
      raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));
end; // SetStreamTimeDiv //

{-------------------------------------------------------------------}
// S.S.
procedure TMIDI_Device_Output.SetStreamTempo (Tempo: Int32);
var
   prop: TMIDIPROPTEMPO;
begin
   prop.cbStruct := sizeof(TMIDIPROPTEMPO);
   prop.dwTempo := Tempo;
   FError := midiStreamProperty(FMidiHandle, @prop, MIDIPROP_SET Or MIDIPROP_TEMPO);
   if Ferror <> 0 then
      raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));
end; // SetStreamTempo //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.SetVolume (Left: uInt16; Right: uInt16);
var
   dwVolume: uInt32;
begin
   dwVolume := (uInt32(Left) shl 16) Or Right;
   FError := midiOutSetVolume(DeviceID, dwVolume);
   if Ferror <> 0 then
      raise EMSC_Device_Out_Error.Create(MidiOutErrorString(FError));
end; // SetVolume //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Output.midiOutput (var Message: TMessage);
{ Triggered when sysex output from PutLong or PutStream is complete }
var MyMidiHdr: TMyMidiHdr;
    thisHdr: PMidiHdr;
begin
   if Message.Msg = Mom_Done then
      begin
      { Find the MIDIHDR we used for the output. Message.lParam is its address }
      thisHdr := PMidiHdr(Message.lParam);

      { Remove it from the output device }
      midiOutUnprepareHeader(FMidiHandle, thisHdr, sizeof(TMIDIHDR));

      { Get the address of the MyMidiHdr object containing this MIDIHDR structure.
         We stored this address in the PutLong procedure }
      MyMidiHdr := TMyMidiHdr(thisHdr^.dwUser);

      { Header and copy of sysex data no longer required since output is complete }
      MyMidiHdr.Free;

      { Call the user's event handler if any }
      if Assigned(OnMIDIOutput) then
         OnMIDIOutput(Self);
      end;
// there is no case for MOM_PLAYBACK_DONE
end; // midiOutput //

end. // Unit: MIDI_IO_Output //
