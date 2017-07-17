// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_Out_Device.pas' rev: 32.00 (Windows)

#ifndef Msc_out_deviceHPP
#define Msc_out_deviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.MMSystem.hpp>
#include <System.SysUtils.hpp>
#include <MSC_Definitions.hpp>
#include <MSC_Device.hpp>
#include <MSC_Circular_Buffer.hpp>
#include <MSC_Delphi_MIDI_Callback.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_out_device
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EMSC_Device_Out_Error;
class DELPHICLASS TMIDI_Device_Output;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM midiOutputState : unsigned char { mosOpen, mosClosed };

#pragma pack(push,4)
class PASCALIMPLEMENTATION EMSC_Device_Out_Error : public Msc_device::EMSC_Device_Error
{
	typedef Msc_device::EMSC_Device_Error inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMSC_Device_Out_Error(const System::UnicodeString Msg) : Msc_device::EMSC_Device_Error(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMSC_Device_Out_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Msc_device::EMSC_Device_Error(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Device_Out_Error(NativeUInt Ident)/* overload */ : Msc_device::EMSC_Device_Error(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Device_Out_Error(System::PResStringRec ResStringRec)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Device_Out_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_device::EMSC_Device_Error(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Device_Out_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMSC_Device_Out_Error(const System::UnicodeString Msg, int AHelpContext) : Msc_device::EMSC_Device_Error(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMSC_Device_Out_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Msc_device::EMSC_Device_Error(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Device_Out_Error(NativeUInt Ident, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Device_Out_Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Device_Out_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Device_Out_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMSC_Device_Out_Error(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM OutPortTech : unsigned char { opt_None, opt_MidiPort, opt_Synth, opt_SQSynth, opt_FMSynth, opt_Mapper };

typedef System::StaticArray<System::SmallString<18>, 6> TechNameMap;

class PASCALIMPLEMENTATION TMIDI_Device_Output : public Msc_device::TMIDI_Device
{
	typedef Msc_device::TMIDI_Device inherited;
	
protected:
	midiOutputState FState;
	NativeInt FMIDIHandle;
	Msc_definitions::TMidiCtlInfo *PCtlInfo;
	Msc_circular_buffer::TCircularBuffer *PBuffer;
	OutPortTech FTechnology;
	System::Word FVoices;
	System::Word FNotes;
	System::Word FChannelMask;
	unsigned FSupport;
	bool FVolume;
	bool FLRVolume;
	bool FPatchCache;
	bool FStream;
	System::Classes::TNotifyEvent FOnMIDIOutput;
	System::UnicodeString __fastcall midiOutErrorString(System::Word WError);
	virtual System::Classes::TStringList* __fastcall GetDeviceList(void);
	virtual void __fastcall SetDeviceID(int DeviceID);
	void __fastcall MidiOutput(Winapi::Messages::TMessage &Message);
	virtual void __fastcall SetProductName(System::UnicodeString NewProductName);
	void __fastcall SetTechnology(OutPortTech NewTechnology);
	void __fastcall PutMidi(void * TheSysex, System::Word msgLength, bool bUseStream);
	
public:
	__fastcall virtual TMIDI_Device_Output(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMIDI_Device_Output(void);
	virtual bool __fastcall Open(void);
	virtual bool __fastcall Close(void);
	virtual bool __fastcall is_opened(void);
	virtual bool __fastcall is_closed(void);
	midiOutputState __fastcall Status(void);
	virtual void __fastcall PutMidiEvent(Msc_definitions::TMIDI_Event* theEvent);
	virtual void __fastcall PutShort(System::Byte MidiMessage, System::Byte Data1, System::Byte Data2);
	virtual void __fastcall PutLong(void * TheSysex, System::Word msgLength);
	virtual void __fastcall PutStream(void * TheSysex, System::Word msgLength);
	void __fastcall SetVolume(System::Word Left, System::Word Right);
	void __fastcall SetStreamTimeDiv(int TimeDiv);
	void __fastcall SetStreamTempo(int Tempo);
	void __fastcall StreamReStart(void);
	void __fastcall StreamStop(void);
	__property NativeInt MIDIHandle = {read=FMIDIHandle, nodefault};
	__property OutPortTech Technology = {read=FTechnology, write=SetTechnology, default=2};
	__property System::Word Voices = {read=FVoices, nodefault};
	__property System::Word Notes = {read=FNotes, nodefault};
	__property System::Word ChannelMask = {read=FChannelMask, nodefault};
	__property unsigned Support = {read=FSupport, nodefault};
	__property bool Volume = {read=FVolume, nodefault};
	__property bool LRVolume = {read=FLRVolume, nodefault};
	__property bool Stream = {read=FStream, write=FStream, default=0};
	__property bool PatchCache = {read=FPatchCache, nodefault};
	
__published:
	__property System::Classes::TNotifyEvent OnMIDIOutput = {read=FOnMIDIOutput, write=FOnMIDIOutput};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TechNameMap TechName;
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Msc_out_device */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_OUT_DEVICE)
using namespace Msc_out_device;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_out_deviceHPP
