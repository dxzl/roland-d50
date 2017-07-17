// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_In_Device.pas' rev: 32.00 (Windows)

#ifndef Msc_in_deviceHPP
#define Msc_in_deviceHPP

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
#include <MSC_Device.hpp>
#include <MSC_Circular_Buffer.hpp>
#include <MSC_Delphi_MIDI_Callback.hpp>
#include <MSC_Definitions.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_in_device
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EMSC_Device_In_Error;
class DELPHICLASS TMIDI_Device_Input;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM MidiInputState : unsigned char { misOpen, misClosed, misCreating, misDestroying };

#pragma pack(push,4)
class PASCALIMPLEMENTATION EMSC_Device_In_Error : public Msc_device::EMSC_Device_Error
{
	typedef Msc_device::EMSC_Device_Error inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMSC_Device_In_Error(const System::UnicodeString Msg) : Msc_device::EMSC_Device_Error(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMSC_Device_In_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Msc_device::EMSC_Device_Error(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Device_In_Error(NativeUInt Ident)/* overload */ : Msc_device::EMSC_Device_Error(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Device_In_Error(System::PResStringRec ResStringRec)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Device_In_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_device::EMSC_Device_Error(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Device_In_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMSC_Device_In_Error(const System::UnicodeString Msg, int AHelpContext) : Msc_device::EMSC_Device_Error(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMSC_Device_In_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Msc_device::EMSC_Device_Error(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Device_In_Error(NativeUInt Ident, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Device_In_Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Device_In_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Device_In_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_device::EMSC_Device_Error(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMSC_Device_In_Error(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TMIDI_Device_Input : public Msc_device::TMIDI_Device
{
	typedef Msc_device::TMIDI_Device inherited;
	
private:
	NativeInt FMIDIHandle;
	MidiInputState FState;
	bool FSysexOnly;
	System::Word FCapacity;
	Msc_circular_buffer::TCircularBuffer *PBuffer;
	System::Classes::TNotifyEvent FOnMIDIInput;
	System::Classes::TNotifyEvent FOnOverflow;
	System::Word FSysexBufferSize;
	System::Word FSysexBufferCount;
	System::Classes::TList* MidiHdrs;
	Msc_definitions::TMidiCtlInfo *PCtlInfo;
	
protected:
	System::Word __fastcall GetEventCount(void);
	System::UnicodeString __fastcall MidiInErrorString(System::Word WError);
	virtual System::Classes::TStringList* __fastcall GetDeviceList(void);
	void __fastcall Prepareheaders(void);
	void __fastcall UnprepareHeaders(void);
	void __fastcall AddBuffers(void);
	virtual void __fastcall SetProductName(System::UnicodeString NewProductName);
	void __fastcall SetSysexBufferSize(System::Word BufferSize);
	void __fastcall SetSysexBufferCount(System::Word BufferCount);
	void __fastcall SetSysexOnly(bool bSysexOnly);
	virtual void __fastcall SetDeviceID(int DeviceID);
	
public:
	__fastcall virtual TMIDI_Device_Input(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMIDI_Device_Input(void);
	virtual bool __fastcall Open(void);
	virtual bool __fastcall Close(void);
	virtual bool __fastcall is_opened(void);
	virtual bool __fastcall is_closed(void);
	MidiInputState __fastcall Status(void);
	Msc_definitions::TMIDI_Event* __fastcall GetMidiEvent(void);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall MidiInput(Winapi::Messages::TMessage &Message);
	__property NativeInt MIDIHandle = {read=FMIDIHandle, nodefault};
	__property System::Word MessageCount = {read=GetEventCount, nodefault};
	
__published:
	__property System::Word Capacity = {read=FCapacity, write=FCapacity, default=1024};
	__property System::Word SysexBufferSize = {read=FSysexBufferSize, write=SetSysexBufferSize, default=10000};
	__property System::Word SysexBufferCount = {read=FSysexBufferCount, write=SetSysexBufferCount, default=16};
	__property bool SysexOnly = {read=FSysexOnly, write=SetSysexOnly, default=0};
	__property System::Classes::TNotifyEvent OnMidiInput = {read=FOnMIDIInput, write=FOnMIDIInput};
	__property System::Classes::TNotifyEvent OnOverflow = {read=FOnOverflow, write=FOnOverflow};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Msc_in_device */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_IN_DEVICE)
using namespace Msc_in_device;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_in_deviceHPP
