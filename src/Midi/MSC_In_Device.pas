{ $Header: /MidiComp/MSC_In_Device.pas 2     10/06/97 7:33 Davec $ }

{ Written by David Churcher <dchurcher@cix.compulink.co.uk>, released to the
  public domain. GetDeviceList added 12/25/16 by Scott Swift dxzl@live.com}

{
S.S.
WinAPI: midiInGetNumDevs - Gets the number of MIDI input devices
Abstract:
// Declare: midiInGetNumDevs: UINT; (no parameters; Returns the number of MIDI input device)
// Example: Read more
WinAPI: midiInUnprepareHeader - Clears the preparation done by midiInPrepareHeader
This function must be called after the device full buffer is returned to the program;
this function must be called before the GlobalFree buffer is freed; canceling a buffer
that is not yet ready will not work, but the function returns 0
// declaration: midiInUnprepareHeader (hMidiIn: HMIDIIN; (device handle) lpMidiInHdr:
PMidiHdr; (TMidiHdr structure pointer) uSize: UINT ... read more
WinAPI: midiOutPrepareHeader - Prepares a buffer for MIDI output
Summary: Note: You must call GlobalAlloc to allocate memory (using GMEM_MOVEABLE,
GMEM_SHARE) to TWaveHdr and the buffer pointed to by lpData in it and lock it with GlobalLock.
// Declarations: midiOutPrepareHeader (hMidiOut: HMIDIOUT; (device handle) lpMidiOutHdr:
PMidiHdr; (TMidiH ... read more
WinAPI: midiInOpen - Opens the MIDI input device
In addition to PostMessage timeGetSystemTime timeGetTime timeSetEvent timeKillEvent
midiOutShortMsg midiOutLongMsg OutputDebugString, but also can not have the data in the
fixed data segment; In addition to the PostMessage timeGetSystemTime timeGetTime
timeKillEvent midiOutShortMsg midiOutLongMsg OutputDebugString, but also can not
have other system calls
// Disclaimer: ... read more
WinAPI: midiInAddBuffer - Sends an input buffer to the MIDI input device
Input buffer for system exclusive messages only; in the buffer passed to the
midiInAddBuffer before the first call midiInPrepareHeader preparation; also call
GlobalAlloc to TMidiHdr and lpData which point to the input buffer is only used
for system mutex message; . the memory buffer allocation (use GMEM_MOVEABLE, GMEM_SHARE),
with locking GlobalLock
// declare: ... read more
WinAPI: midiInGetErrorText - Get the error description based on the error number
Summary: Hint: The length of the error text is generally not more than
MAXERRORLENGTH = 128; If the buffer is too small, the text will be truncated.
// Statement: midiInGetErrorText (mmrError: MMRESULT; (error number)
lpText: PChar; buffer size UINT ()): MMRESULT; (return 0 if successful; ... read More
WinAPI: midiInMessage - Sends a message to the MIDI input device
(Message) dw1: DWORD (message parameter) dw2: DWORD (message argument)): MMRESULT;
(function successfully returns the message sent)) / (message (message)) ( / example: read more
WinAPI: midiInGetDevCaps - Query input device performance
Summary:
// Declaration: midiInGetDevCaps (DeviceID: UINT; (device ID) lpCaps: PMidiInCaps;
(TMidiInCaps structure pointer) uSize: UINT (size of TMidiInCaps structure)): MMRESULT;
(return 0; Possible error values ​​below :) MMSYSERR_BADDEVICE ... read more
WinAPI: midiInClose - Closes the input device
If the buffer sent by midiInAddBuffer does not return to the program, the function will fail;
calling midiInReset marks all pending buffers as executed.
// Declarations: midiInClose (hMidiIn) : HMIDIIN (device handle)): MMRESULT; (return 0 if successful;
possible error values below:) MMSYSERR_INVALHANDLE ... read more
WinAPI: midiInReset - Reset input
The dwBytesRecorded in the TWaveHdr structure will contain the actual length of the data.
// Declarations: midiInReset (hMidiIn: HMIDIIN (device handle))); The dwBytesRecorded in
the TWaveHdr structure will contain the actual data length. : MMRESULT; (return 0 if successful;
possible error values below:) MMSYSERR_INVALHANDLE = 5; (device handle is invalid ... read more
WinAPI: midiInStop - Stops typing
Summary: Hint: The function marks the current buffer as executed, but leaves
any empty buffers in the queue.
// Declarations: midiInStop (hMidiIn: HMIDIIN (device handle)): MMRESULT; (return 0;
error values below:) MMSYSERR_INVALHANDLE = 5; ()
// device handle is invalid example: read more
WinAPI: midiInStart - Starts the input
The system-specific message is placed in the buffer provided by the midiInAddBuffer function.
If there is no buffer in the queue, the data will be discarded. When the buffer is buffered,
the system will send the message to the user. area is full, or receive a complete system dedicated
message, or call midiInReset when the buffer is returned to the user;
TMidiHdr dwBytesRecorded will return the actual length of the received data
// declare: midiInS .... read more
WinAPI: midiInGetID - Gets the input device ID
(MYSESULT); (return 0 for success; Possible error values ​​are as follows:)
MMSYSERR_INVALHANDLE = 5; (getIndicatorIntervalID) (getIndicatorID) (PUMP ( ()
// device handle is invalid example: read more
WinAPI: midiInPrepareHeader - Prepares a buffer for MIDI input
Summary: Tip: Buffer is filled back to the application. In the buffer to midiInAddBuffer before,
first call midiInPrepareHeader preparation; also called GlobalAlloc to TWaveHdr and lpData in which
the buffer is allocated memory (using GMEM_MOVEABLE, GMEM_SHARE) and locking GlobalLock
// declare:. midiInPrepareHeader (... read more
}

unit MSC_In_Device;

{
  Properties from base class (TMIDI_Device):

   Error: uInt16, The error code for the last MMSYSTEM error. See the MMSYSERR_
   entries in MMSYSTEM.INT for possible values.

   DriverVersion: Int32, Version number of the driver

   DeviceList: TStringList, List of devices
    (DeviceList.Objects contains the DeviceID, DeviceList.Strings
    contains the ProductName)

   NumDevs: Int32, Number of devices

   DeviceID: Int32, Windows numeric device ID for the MIDI input device.
    Between 0 and NumDevs-1. Read-only while device is open, exception
    when changed while open

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

   MIDIHandle: The input handle to the MIDI device.
   0 when device is not open
   Read-only, runtime-only

   MessageCount: Number of input messages waiting in input buffer

   Capacity: Number of messages input buffer can hold
   Defaults to 1024
   Limited to (64K/event size)
   Read-only when device is open (exception when changed while open)

   SysexBufferSize: Size in bytes of each sysex buffer
   Defaults to 10K
   Minimum 0K (no buffers), Maximum 64K-1

   S.S.To receive sysex blocks that you need before the EEX comes in, you
   set the SysexBufferSize property to the size of the block you expect,
   and you will get a normal input-event generated when the buffer is full.
   Set this size prior to opening. Then you have to close/re-open to change
   the size...

   SysexBufferCount: Number of sysex buffers
   Defaults to 16
   Minimum 0 (no buffers), Maximum (avail mem/SysexBufferSize)
   Check where these buffers are allocated?

   SysexOnly: True to ignore all non-sysex input events. May be changed while
   device is open. Handy for patch editors where you have lots of short MIDI
   events on the wire which you are always going to ignore anyway.

   Methods:
   GetMidiEvent: Read Midi event at the head of the FIFO input buffer.
   Returns a TMyMidiEvent object containing MIDI message data, timestamp,
   and sysex data if applicable.
   This method automatically removes the event from the input buffer.
   It makes a copy of the received sysex buffer and puts the buffer back
   on the input device.
   The TMyMidiEvent object must be freed by calling MyMidiEvent.Free.

   Open: Opens device. Note no input will appear until you call the Start
   method.

   Close: Closes device. Any pending system exclusive output will be cancelled.

   Start: Starts receiving MIDI input.

   Stop: Stops receiving MIDI input.

   Events:
   OnMidiInput: Called when MIDI input data arrives. Use the GetMidiEvent to
   get the MIDI input data.

   OnOverflow: Called if the MIDI input buffer overflows. The caller must
   clear the buffer before any more MIDI input can be received.

   Notes:
   Buffering: Uses a circular buffer, separate pointers for next location
   to fill and next location to empty because a MIDI input interrupt may
   be adding data to the buffer while the buffer is being read. Buffer
   pointers wrap around from end to start of buffer automatically. If
   buffer overflows then the OnBufferOverflow event is triggered and no
   further input will be received until the buffer is emptied by calls
   to GetMidiEvent.

   Sysex buffers: There are (SysexBufferCount) buffers on the input device.
   When sysex events arrive these buffers are removed from the input device and
   added to the circular buffer by the interrupt handler in the DLL.  When the sysex events
   are removed from the circular buffer by the GetMidiEvent method the buffers are
   put back on the input. If all the buffers are used up there will be no
   more sysex input until at least one sysex event is removed from the input buffer.
   In other    words if you're expecting lots of sysex input you need to set the
   SysexBufferCount property high enough so that you won't run out of
   input buffers before you get a chance to read them with GetMidiEvent.

   If the synth sends a block of sysex that's longer than SysexBufferSize it
   will be received as separate events.
   TODO: Component derived from this one that handles >64K sysex blocks cleanly
   and can stream them to disk.

   Midi Time Code (MTC) and Active Sensing: The DLL is currently hardcoded
   to filter these short events out, so that we don't spend all our time
   processing them.
   TODO: implement a filter property to select the events that will be filtered
   out.
}

interface

uses Classes, WinTypes, Messages, WinProcs, MMSystem, SysUtils,
     MSC_Device, MSC_Circular_Buffer, MSC_Delphi_MIDI_Callback,
     MSC_Definitions;

type
   MidiInputState = (misOpen, misClosed, misCreating, misDestroying);
   EMSC_Device_In_Error = class (EMSC_Device_Error);

   {-------------------------------------------------------------------}
   TMIDI_Device_Input = class (TMIDI_Device)
   private
      FMIDIHandle: HMIDIIn;   // Handle to input device }
      FState: MidiInputState; // Current device state }
      FSysexOnly: Boolean;

// Queue
      FCapacity: uInt16; // Buffer capacity
      PBuffer: PCircularBuffer; // Low-level MIDI input buffer created by Open method

// Events
      FOnMIDIInput: TNotifyEvent;   // MIDI Input arrived
      FOnOverflow: TNotifyEvent;    // Input buffer overflow
// TODO: Some sort of error handling event for MIM_ERROR

// Sysex
      FSysexBufferSize:  uInt16;
      FSysexBufferCount: uInt16;
      MidiHdrs: Tlist;
      PCtlInfo: PMidiCtlInfo; // Pointer to control info for DLL

   protected
      function  GetEventCount: uInt16;
      function  MidiInErrorString (WError: uInt16): String;
      function GetDeviceList: TStringList; override;
      procedure Prepareheaders;
      procedure UnprepareHeaders;
      procedure AddBuffers;
      procedure SetProductName (NewProductName: String); override;
      procedure SetSysexBufferSize (BufferSize: uInt16);
      procedure SetSysexBufferCount (BufferCount: uInt16);
      procedure SetSysexOnly (bSysexOnly: Boolean);
      procedure SetDeviceID (DeviceID: Int32); override;

  public
      constructor Create(AOwner:TComponent); override;
      destructor Destroy; override;
      function Open: boolean; override;
      function Close: boolean; override;
      function is_opened: boolean; override;
      function is_closed: boolean; override;
      function Status: MidiInputState;
      function GetMidiEvent: TMIDI_Event; // Get first message in input queue
      procedure Start;
      procedure Stop;
      procedure MidiInput (var Message: TMessage);

      property MIDIHandle: HMIDIIn read FMIDIHandle;
      property MessageCount: uInt16 read GetEventCount;

// Some functions to decode and classify incoming messages would be good

   published
      property Capacity: uInt16 read FCapacity write FCapacity default DefMidiInCircBufSize;
      property SysexBufferSize: uInt16 read FSysexBufferSize write SetSysexBufferSize default 10000;
      property SysexBufferCount: uInt16 read FSysexBufferCount write SetSysexBufferCount default 16;
      property SysexOnly: Boolean read FSysexOnly write SetSysexOnly default False;

// Events
      property OnMidiInput: TNotifyEvent read FOnMidiInput write FOnMidiInput;
      property OnOverflow: TNotifyEvent read FOnOverflow write FOnOverflow;
end; // Class: TMIDI_Device_Input //

procedure Register;

{====================================================================}
implementation

Uses  Graphics, Controls, Forms, Dialogs;

{-------------------------------------------------------------------}
procedure Register;
begin
  RegisterComponents(MSC_Package_Name, [TMIDI_Device_Input]);
end;

{-------------------------------------------------------------------}
constructor TMIDI_Device_Input.Create (AOwner:TComponent);
begin
  inherited Create(AOwner);

  FState     := misCreating;
  FSysexOnly := False;
  FNumDevs   := midiInGetNumDevs;
  MidiHdrs   := Nil;

  { Set defaults }
  FCapacity := DefMidiInCircBufSize;
  FSysexBufferSize := 4096;
  FSysexBufferCount := 16;

  { Create the window for callback notification }
  if not (csDesigning in ComponentState) then
  begin
     Handle := AllocateHwnd(MidiInput);
  end;

  if FNumDevs > 0 then SetDeviceID (0);
  FState := misClosed;
 end; // Create //

{-------------------------------------------------------------------}
{ Close the device if it's open }
destructor TMIDI_Device_Input.Destroy;
begin
    if (FMidiHandle <> 0) then
    begin
        Close;
        FMidiHandle := 0;
    end;

    if (PCtlInfo <> Nil) then
        GlobalSharedLockedFree( PCtlinfo^.hMem, PCtlInfo );

    DeallocateHwnd(Handle);
    inherited Destroy;
end; // Destroy //

function TMIDI_Device_Input.Status: MidiInputState;
begin
   Result := FState;
end; // Status //

{-------------------------------------------------------------------}
{ Convert the numeric return code from an MMSYSTEM function to a string
  using midiInGetErrorText. TODO: These errors aren't very helpful
  (e.g. "an invalid parameter was passed to a system function") so
  sort out some proper error strings. }
function TMIDI_Device_Input.MidiInErrorString (WError: uInt16): String;
var errorDesc: PChar;
begin
   errorDesc := Nil;
   try
      errorDesc := StrAlloc (MAXERRORLENGTH);
      if midiInGetErrorText (WError, errorDesc, MAXERRORLENGTH) = 0
         then result := StrPas (errorDesc)
         else result := 'Specified error number is out of range';
   finally
      if errorDesc <> Nil then StrDispose(errorDesc);
   end;
end; // MidiInErrorString //

{-------------------------------------------------------------------}
{ Set the sysex buffer size, fail if device is already open }
procedure TMIDI_Device_Input.SetSysexBufferSize (BufferSize: uInt16);
begin
   if FState = misOpen
      then raise EMSC_Device_In_Error.Create ('Change to SysexBufferSize while device was open')
      else FSysexBufferSize := BufferSize;
end; // SetSysexBufferSize //

{-------------------------------------------------------------------}
{ Set the sysex buffer count, fail if device is already open }
procedure TMIDI_Device_Input.SetSysexBuffercount (Buffercount: uInt16);
begin
   if FState = misOpen
      then raise EMSC_Device_In_Error.Create('Change to SysexBuffercount while device was open')
      else FSysexBuffercount := Buffercount;{ TODO: Validate the sysex buffer count}
end; // SetSysexBuffercount //

{-------------------------------------------------------------------}
{ Set the Sysex Only flag to eliminate unwanted short MIDI input messages }
procedure TMIDI_Device_Input.SetSysexOnly (bSysexOnly: Boolean);
begin
   FSysexOnly := bSysexOnly;
   { Update the interrupt handler's copy of this property }
   if PCtlInfo <> nil
      then PCtlInfo^.SysexOnly := bSysexOnly;
end; // SetSysexOnly //

{-------------------------------------------------------------------}
{ Set the Device ID to select a new MIDI input device
  Note: If no MIDI devices are installed, throws an 'Invalid Device ID' exception }
procedure TMIDI_Device_Input.SetDeviceID (DeviceID: Int32);
var MidiInCaps: TMidiInCaps;
begin
   if FState = misOpen then
   begin
      raise EMSC_Device_In_Error.Create('Change to DeviceID while device was open')
   end else if (DeviceID < 0) or (DeviceID >= Int32 (midiInGetNumDevs)) then
   begin
      raise EMSC_Device_In_Error.Create ('Invalid device ID')
   end else
   begin
      FDeviceID := DeviceID;

      { Set the name and other MIDIINCAPS properties to match the ID }
      FError := midiInGetDevCaps (DeviceID, @MidiInCaps, sizeof (TMidiInCaps));
      if Ferror <> MMSYSERR_NOERROR
         then raise EMSC_Device_In_Error.Create (MidiInErrorString (FError));

      FProductName := string (StrPas(MidiInCaps.szPname));
      FDriverVersion := MidiInCaps.vDriverVersion;
      FMID := MidiInCaps.wMID;
      FPID := MidiInCaps.wPID;
   end; // if
end; // SetDeviceID //

{-------------------------------------------------------------------}
{ Populates FDeviceList, a TStringList handled by the base class
  This is called every time you access the read-only DeviceList property }
function TMIDI_Device_Input.GetDeviceList : TStringList;
var
  lInCaps             : TMidiInCaps;
  testDeviceID        : Int16;
begin
  inherited;

  Result := FDeviceList;

  if (FDeviceList = Nil) then exit;

  FDeviceList.Clear;

  TRY   // TRY..EXCEPT was adapted from file "DAV_MidiIO.pas"
    FNumDevs := midiInGetNumDevs;
  EXCEPT
    FNumDevs := 0;
  end;

  if FNumDevs > 0 then
  for testDeviceID := 0 To FNumDevs-1 do
  begin
    FError := midiInGetDevCaps(testDeviceID, @lInCaps, sizeof(TMidiInCaps));
    if Ferror = MMSYSERR_NOERROR then
        FDeviceList.AddObject(StrPas(lInCaps.szPname), TObject(testDeviceID));
  end;

end;

{-------------------------------------------------------------------}
{ Set the product name and put the matching input device number in FDeviceID.
  This is handy if you want to save a configured input/output device
  by device name instead of device number, because device numbers may
  change if users add or remove MIDI devices.
  Exception if input device with matching name not found,
  or if input device is open }
procedure TMIDI_Device_Input.SetProductName (NewProductName: String);
var MidiInCaps: TMidiInCaps;
    testDeviceID: uInt16;
    testProductName: String;
begin
   if FState = misOpen
      then raise EMSC_Device_In_Error.Create('Change to ProductName while device was open')
      else
   { Don't set the name if the component is reading properties because
   the saved Productname will be from the machine the application was compiled
   on, which may not be the same for the corresponding DeviceID on the user's
   machine. The FProductname property will still be set by SetDeviceID }
   if not (csLoading in ComponentState) then
   begin
      for testDeviceID := 0 To (midiInGetNumDevs-1) do
      begin
         FError := midiInGetDevCaps(testDeviceID, @MidiInCaps, sizeof(TMidiInCaps));
         if Ferror <> MMSYSERR_NOERROR
            then raise EMSC_Device_In_Error.Create(MidiInErrorString(FError));
         testProductName := string (StrPas (MidiInCaps.szPname));
         if testProductName = NewProductName then
         begin
            FProductName := NewProductName;
            Break;
         end; // if
      end; // for
      if FProductName <> NewProductName
         then raise EMSC_Device_In_Error.Create('MIDI Input Device ' +
                              NewProductName + ' not installed ')
         else SetDeviceID(testDeviceID);
   end; // if
end; // SetProductName //


{-------------------------------------------------------------------}
{ Get the sysex buffers ready }
procedure TMIDI_Device_Input.PrepareHeaders;
var
   ctr: uInt16;
   MyMidiHdr: TMyMidiHdr;
begin
   if (FSysexBufferCount > 0) And (FSysexBufferSize > 0)
      And (FMidiHandle <> 0) then
      begin
      Midihdrs := TList.Create;
      for ctr := 1 to FSysexBufferCount do
         begin
         { Initialize the header and allocate buffer memory }
         MyMidiHdr := TMyMidiHdr.Create(FSysexBufferSize);

         { Store the address of the MyMidiHdr object in the contained MIDIHDR
              structure so we can get back to the object when a pointer to the
              MIDIHDR is received.
              E.g. see TMidiOutput.Output method }
         MyMidiHdr.hdrPointer^.dwUser := uInt32(MyMidiHdr);

         { Get MMSYSTEM's blessing for this header }
         FError := midiInPrepareHeader(FMidiHandle,MyMidiHdr.hdrPointer,
            sizeof(TMIDIHDR));
         if Ferror <> MMSYSERR_NOERROR then
            raise EMSC_Device_In_Error.Create(MidiInErrorString(FError));

         { Save it in our list }
         MidiHdrs.Add(MyMidiHdr);
         end;
      end;
end;

{-------------------------------------------------------------------}
{ Clean up from PrepareHeaders }
procedure TMIDI_Device_Input.UnprepareHeaders;
var ctr: uInt16;
begin
   if (MidiHdrs <> Nil) then    { will be Nil if 0 sysex buffers }
   begin
      for ctr := 0 To MidiHdrs.Count-1 do
      begin
         FError := midiInUnprepareHeader (FMidiHandle,
            TMyMidiHdr(MidiHdrs.Items [ctr]).hdrPointer, sizeof (TMIDIHDR));
         if Ferror <> MMSYSERR_NOERROR
            then raise EMSC_Device_In_Error.Create (MidiInErrorString (FError));
         TMyMidiHdr(MidiHdrs.Items [ctr]).Free;
      end; // for
      MidiHdrs.Free;
      MidiHdrs := Nil;
   end; // if
end; // UnprepareHeaders //

{-------------------------------------------------------------------}
{ Add sysex buffers, if required, to input device }
procedure TMIDI_Device_Input.AddBuffers;
var ctr: uInt16;
begin
   if MidiHdrs <> Nil then { will be Nil if 0 sysex buffers }
   begin
      if MidiHdrs.Count > 0 Then
      begin
         for ctr := 0 To MidiHdrs.Count-1 do
         begin
            FError := midiInAddBuffer(FMidiHandle,
                      TMyMidiHdr(MidiHdrs.Items[ctr]).hdrPointer, sizeof(TMIDIHDR));
            If FError <> MMSYSERR_NOERROR then
               raise EMSC_Device_In_Error.Create(MidiInErrorString(FError));
         end; // for
      end; // if
   end; // if
end; // AddBuffers //

{-------------------------------------------------------------------}
function TMIDI_Device_Input.Open: boolean;
var hMem: THandle;
begin
   Result := True;
   try
      { Create the buffer for the MIDI input messages }
      If (PBuffer = Nil)
         then PBuffer := CircBufAlloc (FCapacity);

      { Create the control info for the DLL }
      if (PCtlInfo = Nil) then
      begin
         PCtlInfo := GlobalSharedLockedAlloc( Sizeof(TMidiCtlInfo), hMem);
         PctlInfo^.hMem := hMem;
      end;
      PctlInfo^.pBuffer := PBuffer;
      Pctlinfo^.hWindow := Handle; //  Control's window handle
      PCtlInfo^.SysexOnly := FSysexOnly;
      FError := midiInOpen(@FMidiHandle, FDeviceId, uInt32 (@midiHandler),
                                         uInt32 (PCtlInfo), CALLBACK_FUNCTION);

      If (FError <> MMSYSERR_NOERROR)
         then raise EMSC_Device_In_Error.Create (MidiInErrorString (FError));

      PrepareHeaders;      // Get sysex buffers ready
      AddBuffers;          // Add them to the input
      FState := misOpen;   // device is opened

   except
      Result := False;
      if PBuffer <> Nil then
      begin
         CircBufFree(PBuffer);
         PBuffer := Nil;
      end;

      if PCtlInfo <> Nil then
      begin
         GlobalSharedLockedFree(PCtlInfo^.hMem, PCtlInfo);
         PCtlInfo := Nil;
      end; // if
   end; // try
end; // Open //

{-------------------------------------------------------------------}
function TMIDI_Device_Input.Close: boolean;
begin
   Result := True;
   if FState = misOpen then
   begin
      FState := misClosed;

      { MidiInReset cancels any pending output.
      Note that midiInReset causes an MIM_LONGDATA callback for each sysex
      buffer on the input, so the callback function and Midi input buffer
      should still be viable at this stage.
      All the resulting MIM_LONGDATA callbacks will be completed by the time
      MidiInReset returns, though. }

      FError := MidiInReset(FMidiHandle);
      if Ferror <> MMSYSERR_NOERROR then
      begin
         raise EMSC_Device_In_Error.Create(MidiInErrorString(FError));
      end; // if

      { Remove sysex buffers from input device and free them }
      UnPrepareHeaders;

      { Close the device (finally!) }
      FError := MidiInClose(FMidiHandle);
      if Ferror <> MMSYSERR_NOERROR then
      begin
         raise EMSC_Device_In_Error.Create(MidiInErrorString(FError));
      end; // if

      FMidiHandle := 0;

      If (PBuffer <> Nil) then
      begin
         CircBufFree( PBuffer );
         PBuffer := Nil;
      end; // if
   end; // if
end; // Close //

function TMIDI_Device_Input.is_opened: boolean;
begin
   Result := Status = misOpen;
end; // is_opened //

function TMIDI_Device_Input.is_closed: boolean;
begin
   Result := Status = misClosed;
end; // is_closed //

{-------------------------------------------------------------------}
function TMIDI_Device_Input.GetMidiEvent: TMIDI_Event;
var thisItem: TMidiBufferItem;
begin
   if (FState = misOpen) and CircBufReadEvent (PBuffer, @thisItem) then
   begin
      Result := TMIDI_Event.Create;
      with thisItem Do
      begin
         Result.Time := Timestamp;
         if (Sysex = Nil) then // Short Message
         begin
            Result.MIDI_Message := LoByte(LoWord(Data));
            Result.Data_Byte_1 := HiByte(LoWord(Data));
            Result.Data_Byte_2 := LoByte(HiWord(Data));
            Result.Sysex := Nil;
            Result.SysexLength := 0;
         end else // Long Sysex message
         begin
            Result.MIDI_Message := mc_MIDI_Begin_SysEx;
            Result.Data_Byte_1 := 0;
            Result.Data_Byte_2 := 0;
            Result.SysexLength := Sysex^.dwBytesRecorded;
            if Sysex^.dwBytesRecorded <> 0 then
            begin
               { Put a copy of the sysex buffer in the object }
               GetMem(Result.Sysex, Sysex^.dwBytesRecorded);
// S.S.
//               Move (Result.Sysex, Sysex^.lpData, Sysex^.dwBytesRecorded);
               MoveMemory (Result.Sysex, Sysex^.lpData, Sysex^.dwBytesRecorded);
            end; // if

            { Put the header back on the input buffer }
            FError := midiInPrepareHeader (FMidiHandle,Sysex, sizeof (TMIDIHDR));
            If Ferror = 0
               then FError := midiInAddBuffer (FMidiHandle, Sysex, sizeof (TMIDIHDR));
            if Ferror <> MMSYSERR_NOERROR
               then raise EMSC_Device_In_Error.Create (MidiInErrorString (FError));
         end; // if
      end; // with
      CircbufRemoveEvent(PBuffer);
   end else Result := nil; // Device isn't open, return a nil event
end; // GetMidiEvent //

{-------------------------------------------------------------------}
function TMIDI_Device_Input.GetEventCount: uInt16;
begin
   if FState = misOpen
      then Result := PBuffer^.EventCount
      else Result := 0;
end; // GetEventCount //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Input.Start;
begin
   if FState = misOpen then
   begin
      FError := midiInStart (FMidiHandle);
      if Ferror <> MMSYSERR_NOERROR
         then raise EMSC_Device_In_Error.Create (MidiInErrorString (FError));
   end; // if
end; // Start //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Input.Stop;
begin
   if FState = misOpen then
   begin
      FError := midiInStop (FMidiHandle);
      if Ferror <> MMSYSERR_NOERROR
         then raise EMSC_Device_In_Error.Create (MidiInErrorString (FError));
   end; // if
end; // Stop //

{-------------------------------------------------------------------}
procedure TMIDI_Device_Input.MidiInput (var Message: TMessage);
{ Triggered by incoming message from DLL.
  Note DLL has already put the message in the queue }
// S.S. http://www.bass.radio42.com/help/html/7237d143-02f9-cf27-63b2-f9bef9c693a7.htm
// https://msdn.microsoft.com/en-us/library/dd757370(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/dd798498(v=vs.85).aspx
//
// MIM_CLOSE MIM_DATA MIM_ERROR MIM_LONGDATA MIM_LONGERROR MIM_MOREDATA MIM_OPEN MM_MIM_CLOSE MM_MIM_DATA
// MM_MIM_ERROR MM_MIM_LONGDATA MM_MIM_LONGERROR MM_MIM_MOREDATA MM_MIM_OPEN MM_MOM_CLOSE MM_MOM_DONE
// MM_MOM_OPEN MM_MOM_POSITIONCB MOM_CLOSE MOM_DONE MOM_OPEN MOM_POSITIONCB
//
// MIM_OPEN    961    The MIM_OPEN message is sent to a MIDI input callback function when a MIDI input device
//  is opened.
// Parameters:
// param1    Not used.
// param2    Not used.
// MIM_CLOSE    962    The MIM_CLOSE message is sent to a MIDI input callback function when a MIDI input
//  device is closed.
// Parameters:
// param1    Not used.
// param2    Not used.
// The device handle is no longer valid after this message has been sent.
//
// MIM_DATA    963    The MIM_DATA message is sent to a MIDI input callback function when a MIDI message
//  is received by a MIDI input device.
// Parameters:
// param1    MIDI message that was received. The message is packed into a doubleword value as follows:
// High word: High-order byte: Not used. Low-order byte: Contains a second byte of MIDI data (when needed).
//
// Low word: High-order byte: Contains the first byte of MIDI data (when needed). Low-order byte: Contains
//  the MIDI status.
//
// The two MIDI data bytes are optional, depending on the MIDI status byte.
//
// param2    Time that the message was received by the input device driver. The time stamp is specified
//  in milliseconds,
//  beginning at zero when
//   the MIDI_InStart(IntPtr) function was called.
// MIDI messages received from a MIDI input port have running status disabled; each message is expanded
//  to include the MIDI status byte.
//
// This message is not sent when a MIDI system-exclusive message is received.
//
// You might used the MidiShortMessage class to construct and or unpack the message into it's components.
//
// MIM_LONGDATA    964    The MIM_LONGDATA message is sent to a MIDI input callback function when a
//  system-exclusive buffer has been filled with data and is being returned to the application.
// Parameters:
// param1    Pointer to a MIDI_HEADER structure identifying the input buffer.
// param2    Time that the message was received by the input device driver. The time stamp is specified
//  in milliseconds, beginning at zero when the MIDI_InStart(IntPtr) function was called.
// The returned buffer might not be full. To determine the number of bytes recorded into the returned
//  buffer, use the Data member of the MIDI_HEADER structure specified by param1.
//
// MIM_ERROR    965    The MIM_ERROR message is sent to a MIDI input callback function when an
//  invalid MIDI message is received.
// Parameters:
// param1    Invalid MIDI message that was received. The message is packed into a doubleword value
//  with the first byte of the message in the low-order byte.
// param2    Time that the message was received by the input device driver. The time stamp is
//  specified in milliseconds, beginning at zero when the MIDI_InStart(IntPtr) function was called.
// MIM_LONGERROR    966    The MIM_LONGERROR message is sent to a MIDI input callback function when an
//  invalid or incomplete MIDI system-exclusive message is received.
// Parameters:
// param1    Pointer to a MIDI_HEADER structure identifying the buffer containing the invalid message.
// param2    Time that the message was received by the input device driver. The time stamp is specified
//  in milliseconds, beginning at zero when the MIDI_InStart(IntPtr) function was called.
// The returned buffer might not be full. To determine the number of bytes recorded into the returned
//  buffer, use the Data member of the MIDI_HEADER structure specified by param1.
//
// MIM_MOREDATA    972    The MIM_MOREDATA message is sent to a MIDI input callback function when a MIDI
//  message is received by a MIDI input device but the application is not processing MIM_DATA messages
//  fast enough to keep up with the input device driver. The callback function receives this message only
//  when the application specifies MIDI_IO_STATUS in the call to the
//  MIDI_InOpen(IntPtr, Int32, MIDIINPROC, IntPtr, MIDIFlags) function.
// Parameters:
// param1    MIDI message that was received. The message is packed into a doubleword value as follows:
// High word: High-order byte: Not used. Low-order byte: Contains a second byte of MIDI data (when needed).
//
// Low word: High-order byte: Contains the first byte of MIDI data (when needed). Low-order byte: Contains
//  the MIDI status.
//
// The two MIDI data bytes are optional, depending on the MIDI status byte.
//
// param2    Time that the message was received by the input device driver. The time stamp is specified
//  in milliseconds, beginning at zero when the MIDI_InStart(IntPtr) function was called.
// An application should do only a minimal amount of processing of MIM_MOREDATA messages. (In particular,
//  applications should not call the PostMessage function while processing MIM_MOREDATA.) Instead, the
//  application should place the event data into a buffer and then return.
//
// When an application receives an MIM_DATA message after a series of MIM_MOREDATA messages, it has caught
//  up with incoming MIDI events and can safely call time-intensive functions.
//
// MIDI messages received from a MIDI input port have running status disabled; each message is expanded to
//  include the MIDI status byte. This message is not sent when a MIDI system-exclusive message is received.
//
// You might used the MidiShortMessage class to construct and or unpack the message into it's components.
//
// MOM_OPEN    967    The MOM_OPEN message is sent to a MIDI output callback function when a MIDI output
//  device is opened.
// Parameters:
// param1    Not used.
// param2    Not used.
// MOM_CLOSE    968    The MOM_CLOSE message is sent to a MIDI output callback function when a MIDI output
//  device is closed.
// Parameters:
// param1    Not used.
// param2    Not used.
// The device handle is no longer valid after this message has been sent.
//
// MOM_DONE    969    The MOM_DONE message is sent to a MIDI output callback function when the specified
//  system-exclusive or stream buffer has been played and is being returned to the application.
// Parameters:
// param1    Pointer to a MIDI_HEADER structure identifying the input buffer.
// param2    Not used.
//
begin
   case Message.Msg of

   mim_data:
      { Trigger the user's MIDI input event, if they've specified one and
      we're not in the process of closing the device. The check for
      GetEventCount > 0 prevents unnecessary event calls where the user has
      already cleared all the events from the input buffer using a GetMidiEvent
      loop in the OnMidiInput event handler }
      if Assigned(FOnMIDIInput) and (FState = misOpen)
         and (GetEventCount > 0) then
         FOnMIDIInput(Self);

   // S.S. this happens in a catastrophic situation wher the low-lwvel
   // circular buffer the driver-dll is writing to overflows.
   //
   // To receive sysex blocks that you need before the EEX comes in, you
   // set the SysexBufferSize property to the size of the block you expect,
   // and you get a normal input-event generated (above). Set this size prior
   // to opening. Then you have to close/re-open to change the size...
   mim_Overflow: { input circular buffer overflow }
      if Assigned (FOnOverflow) and (FState = misOpen) then
         FOnOverflow (Self);
   end;
end; // MidiInput //

end. // Unit: MIDI_Device_In //
