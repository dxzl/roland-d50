// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_Component.pas' rev: 32.00 (Windows)

#ifndef Msc_componentHPP
#define Msc_componentHPP

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
#include <MSC_Definitions.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_component
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EMSC_Component_Error;
class DELPHICLASS TMSC_Component;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TTime_Change_Event)(System::TObject* Sender, int time, int current_event);

#pragma pack(push,4)
class PASCALIMPLEMENTATION EMSC_Component_Error : public Msc_definitions::EMSC_Error
{
	typedef Msc_definitions::EMSC_Error inherited;
	
public:
	/* Exception.Create */ inline __fastcall EMSC_Component_Error(const System::UnicodeString Msg) : Msc_definitions::EMSC_Error(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EMSC_Component_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Msc_definitions::EMSC_Error(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Component_Error(NativeUInt Ident)/* overload */ : Msc_definitions::EMSC_Error(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMSC_Component_Error(System::PResStringRec ResStringRec)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Component_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_definitions::EMSC_Error(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSC_Component_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMSC_Component_Error(const System::UnicodeString Msg, int AHelpContext) : Msc_definitions::EMSC_Error(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMSC_Component_Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Msc_definitions::EMSC_Error(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Component_Error(NativeUInt Ident, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSC_Component_Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Component_Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSC_Component_Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Msc_definitions::EMSC_Error(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMSC_Component_Error(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TMSC_Component : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	/* TComponent.Create */ inline __fastcall virtual TMSC_Component(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TMSC_Component(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Msc_component */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_COMPONENT)
using namespace Msc_component;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_componentHPP
