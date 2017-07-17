// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'utilities_math.pas' rev: 32.00 (Windows)

#ifndef Utilities_mathHPP
#define Utilities_mathHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------

namespace Utilities_math
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE unsigned __fastcall convert_to_cardinal(System::Byte b1, System::Byte b2, System::Byte b3, System::Byte b4);
extern DELPHI_PACKAGE System::Word __fastcall convert_to_word(System::Byte b1, System::Byte b2);
extern DELPHI_PACKAGE unsigned __fastcall double_to_int32(double ftVal);
extern DELPHI_PACKAGE double __fastcall int32_to_double(unsigned dwVal);
extern DELPHI_PACKAGE System::UnicodeString __fastcall IntToBin(int value, int digits);
extern DELPHI_PACKAGE int __fastcall BinToInt(System::UnicodeString Value);
extern DELPHI_PACKAGE int __fastcall limit(double value, int min, int max);
extern DELPHI_PACKAGE int __fastcall rescale(double source, double source_min, double source_max, int target_min, int target_range)/* overload */;
extern DELPHI_PACKAGE int __fastcall rescale(int source, int source_min, int source_max, int target_min, int target_range)/* overload */;
extern DELPHI_PACKAGE double __fastcall rescale(double source, double source_min, double source_max, double target_min, double target_range)/* overload */;
}	/* namespace Utilities_math */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_UTILITIES_MATH)
using namespace Utilities_math;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Utilities_mathHPP
