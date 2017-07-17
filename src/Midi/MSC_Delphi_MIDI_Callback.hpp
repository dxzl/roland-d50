// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_Delphi_MIDI_Callback.pas' rev: 32.00 (Windows)

#ifndef Msc_delphi_midi_callbackHPP
#define Msc_delphi_midi_callbackHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.MMSystem.hpp>
#include <MSC_Definitions.hpp>
#include <MSC_Circular_Buffer.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_delphi_midi_callback
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __stdcall CircbufPutEvent(Msc_circular_buffer::PCircularBuffer PBuffer, Msc_circular_buffer::PMidiBufferItem PTheEvent);
extern DELPHI_PACKAGE void __stdcall midiHandler(NativeInt hMidiIn, unsigned wMsg, unsigned dwInstance, unsigned dwParam1, unsigned dwParam2);
}	/* namespace Msc_delphi_midi_callback */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_DELPHI_MIDI_CALLBACK)
using namespace Msc_delphi_midi_callback;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_delphi_midi_callbackHPP
