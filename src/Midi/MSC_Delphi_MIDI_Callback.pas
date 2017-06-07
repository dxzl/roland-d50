{ $Header: /MidiComp/DELPHMCB.PAS 2     10/06/97 7:33 Davec $ }

{MIDI callback for Delphi}

unit MSC_Delphi_MIDI_Callback;

{ These segment options required for the MIDI callback functions }
{$C PRELOAD FIXED PERMANENT}

interface

uses WinProcs, WinTypes, MMsystem,
     MSC_Definitions, MSC_Circular_Buffer;

procedure midiHandler
(
   hMidiIn: HMidiIn;
   wMsg: UINT;
   dwInstance: DWORD;
   dwParam1: DWORD;
   dwParam2: DWORD
); stdcall export;

function CircbufPutEvent(PBuffer: PCircularBuffer; PTheEvent: PMidiBufferItem): Boolean; stdcall; export;

implementation

{ Add an event to the circular input buffer. }
function CircbufPutEvent (PBuffer: PCircularBuffer; PTheEvent: PMidiBufferItem): Boolean;
begin
   If (PBuffer^.EventCount < PBuffer^.Capacity) Then
   begin
      Inc(Pbuffer^.EventCount);

// Copy buffer
      with PBuffer^.PNextput^ do
      begin
         Timestamp := PTheEvent^.Timestamp;
         Data := PTheEvent^.Data;
         Sysex := PTheEvent^.Sysex;
      end; // with

// Move to next put location, with wrap }
      Inc(Pbuffer^.PNextPut);
      If (PBuffer^.PNextPut = PBuffer^.PEnd)
         then PBuffer^.PNextPut := PBuffer^.PStart;

      CircbufPutEvent := True;
   end else
   begin
      CircbufPutEvent := False;
   end; // if
end; // CircbufPutEvent //

{ This is the callback function specified when the MIDI device was opened
  by midiInOpen. It's called at interrupt time when MIDI input is seen
  by the MIDI device driver(s). See the docs for midiInOpen for restrictions
  on the Windows functions that can be called in this interrupt.

  S.S. Also handles midiOutOpen's MOM_DONE message (MOM_OPEN/MOM_CLOSE not
  used }
procedure midiHandler
(
   hMidiIn: HMidiIn;
   wMsg: UINT;
   dwInstance: DWORD;
   dwParam1: DWORD;
   dwParam2: DWORD
);

var thisEvent: TMidiBufferItem;
    thisCtlInfo: PMidiCtlInfo;
    thisBuffer: PCircularBuffer;

Begin
   case wMsg of

      mim_Open: {nothing};

      mim_Error: ; // nothing, handle (message to trigger exception?

      mim_Data, mim_Longdata, mim_Longerror:
         { Note: mim_Longerror included because there's a bug in the Maui
         input driver that sends MIM_LONGERROR for subsequent buffers when
         the input buffer is smaller than the sysex block being received }

         begin
         if (dwParam1 <> mc_MIDI_Active_Sensing) and
                     (dwParam1 <> mc_MIDI_Timing_Clock) then
            begin

            { The device driver passes us the instance data pointer we
            specified for midiInOpen. Use this to get the buffer address
            and window handle for the MIDI control }
            thisCtlInfo := PMidiCtlInfo(dwInstance);
            thisBuffer := thisCtlInfo^.PBuffer;

            { Screen out short messages if we've been asked to }
            if ((wMsg <> mim_Data) or (thisCtlInfo^.SysexOnly = False))
               and (thisCtlInfo <> Nil) and (thisBuffer <> Nil) then
               begin
               with thisEvent do
                  begin
                  timestamp := dwParam2;
                  if (wMsg = mim_Longdata) or
                     (wMsg = mim_Longerror) then
                     begin
                     data := 0;
                     sysex := PMidiHdr(dwParam1);
                     end
                  else
                     begin
                     data := dwParam1;
                     sysex := Nil;
                     end;
                  end;
               if CircbufPutEvent( thisBuffer, @thisEvent ) then
                  { Send a message to the control to say input's arrived }
                  PostMessage(thisCtlInfo^.hWindow, mim_Data, 0, 0)
               else
                  { Buffer overflow }
                  PostMessage(thisCtlInfo^.hWindow, mim_Overflow, 0, 0);
               end;
            end;
         end;

      mom_Done: { Sysex output complete, dwParam1 is pointer to MIDIHDR }
         begin
         { Notify the control that its sysex output is finished.
           The control should call midiOutUnprepareHeader before freeing the buffer }
         PostMessage(PMidiCtlInfo(dwInstance)^.hWindow, mom_Done, 0, dwParam1);
         end;

   end; { Case }
end; // midiHandler //

end. // Unit: MSC_Delphi_MIDI_Callback //
