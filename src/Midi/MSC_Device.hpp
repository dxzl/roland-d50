// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_Device.pas' rev: 32.00 (Windows)

#ifndef Msc_deviceHPP
#define Msc_deviceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.MMSystem.hpp>
#include <MSC_Component.hpp>
#include <MSC_Definitions.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_device
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EMSC_Device_Error;
class DELPHICLASS TMIDI_Device;
//-- type declarations -------------------------------------------------------
#pragma pack(push,4)
class PASCALIMPLEMENTATION EMSC_Device_Error : public Msc_definitions::EMSC_Error
{
	typedef Msc_definitions::EMSC_Error inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMSC_Device_Error(const System::UnicodeString Msg) : Msc_definitions::EMSC_Error(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMSC_Device_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Msc_definitions::EMSC_Error(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Device_Error(NativeUInt Ident)/* overload */ : Msc_definitions::EMSC_Error(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Device_Error(System::PResStringRec ResStringRec)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Device_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_definitions::EMSC_Error(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Device_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMSC_Device_Error(const System::UnicodeString Msg, int AHelpContext) : Msc_definitions::EMSC_Error(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMSC_Device_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Msc_definitions::EMSC_Error(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Device_Error(NativeUInt Ident, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Device_Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Device_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Device_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMSC_Device_Error(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TMIDI_Device : public Msc_component::TMSC_Component
{
	typedef Msc_component::TMSC_Component inherited;
	
protected:
	NativeUInt Handle;
	System::Word FError;
	int FDeviceID;
	int FNumdevs;
	int FDriverVersion;
	System::UnicodeString FProductName;
	System::Word FMID;
	System::Word FPID;
	System::Classes::TStringList* FDeviceList;
	virtual System::Classes::TStringList* __fastcall GetDeviceList(void) = 0 ;
	virtual void __fastcall SetDeviceID(int DeviceID) = 0 ;
	virtual void __fastcall SetProductName(System::UnicodeString ProductName) = 0 ;
	
public:
	__fastcall virtual TMIDI_Device(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TMIDI_Device(void);
	virtual bool __fastcall Open(void) = 0 ;
	virtual bool __fastcall Close(void) = 0 ;
	virtual bool __fastcall is_opened(void) = 0 ;
	virtual bool __fastcall is_closed(void) = 0 ;
	__property System::Word Error = {read=FError, nodefault};
	__property int DriverVersion = {read=FDriverVersion, nodefault};
	__property System::Word MID = {read=FMID, nodefault};
	__property System::Word PID = {read=FPID, nodefault};
	__property System::Classes::TStringList* DeviceList = {read=GetDeviceList, default=0};
	
__published:
	__property int NumDevs = {read=FNumdevs, nodefault};
	__property int DeviceID = {read=FDeviceID, write=SetDeviceID, default=0};
	__property System::UnicodeString ProductName = {read=FProductName, write=SetProductName};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Msc_device */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_DEVICE)
using namespace Msc_device;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_deviceHPP
