// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSC_Circular_Buffer.pas' rev: 32.00 (Windows)

#ifndef Msc_circular_bufferHPP
#define Msc_circular_bufferHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.MMSystem.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msc_circular_buffer
{
//-- forward type declarations -----------------------------------------------
struct TMidiBufferItem;
struct TCircularBuffer;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TMidiBufferItem
{
public:
	unsigned timestamp;
	unsigned data;
	midihdr_tag *sysex;
};


typedef TMidiBufferItem *PMidiBufferItem;

struct DECLSPEC_DRECORD TCircularBuffer
{
public:
	NativeUInt RecordHandle;
	NativeUInt BufferHandle;
	TMidiBufferItem *pStart;
	TMidiBufferItem *pEnd;
	TMidiBufferItem *pNextPut;
	TMidiBufferItem *pNextGet;
	System::Word Error;
	System::Word Capacity;
	System::Word EventCount;
};


typedef TCircularBuffer *PCircularBuffer;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void * __fastcall GlobalSharedLockedAlloc(System::Word Capacity, NativeUInt &hMem);
extern DELPHI_PACKAGE void __fastcall GlobalSharedLockedFree(NativeUInt hMem, void * ptr);
extern DELPHI_PACKAGE PCircularBuffer __fastcall CircbufAlloc(System::Word Capacity);
extern DELPHI_PACKAGE void __fastcall CircbufFree(PCircularBuffer PBuffer);
extern DELPHI_PACKAGE bool __fastcall CircbufReadEvent(PCircularBuffer PBuffer, PMidiBufferItem PEvent);
extern DELPHI_PACKAGE bool __fastcall CircbufRemoveEvent(PCircularBuffer PBuffer);
}	/* namespace Msc_circular_buffer */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSC_CIRCULAR_BUFFER)
using namespace Msc_circular_buffer;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Msc_circular_bufferHPP
