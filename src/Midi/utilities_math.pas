unit utilities_math;

{
   Copyright 1998-2011 Arnold Reinders

   This file is part of the MIDI Sequencer Components (MSC).

   MIDI Sequencer Components (MSC) is free software: you can redistribute it
   and/or modify it under the terms of the Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.

   MIDI Sequencer Components (MSC) is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License and the
   Lesser General Public License along with MIDI Sequencer Components (MSC).
   If not, see <http://www.gnu.org/licenses/>.

   Any changes in the MIDI Sequencer Components (MSC) should be reported
   to Arnold Reinders at musoft@musoft.com
}

interface

uses Windows;

function convert_to_cardinal (b1, b2, b3, b4: uInt8): uInt32;
function convert_to_word (b1, b2: uInt8): uInt16;
function double_to_int32 (ftVal: Double): uInt32;
function int32_to_double (dwVal: uInt32): Double;
function IntToBin (value: LongInt; digits: integer): string;
function BinToInt (Value: String): LongInt;

function limit (value: double; min, max: Int32): Int32;
function rescale (source, source_min, source_max: double; target_min, target_range: Int32): Int32; overload;
function rescale (source, source_min, source_max: Int32;  target_min, target_range: Int32): Int32; overload;
function rescale (source, source_min, source_max, target_min, target_range: double): double; overload;

implementation

function convert_to_cardinal (b1, b2, b3, b4: uInt8): uInt32;

// Convert four bytes to an unsigned 32 bit Int32 (double uInt16)

var value: uInt32;
begin
   value := (b1 and $FF);
   value := (value shl 8) + (b2 and $FF);
   value := (value shl 8) + (b3 and $FF);
   value := (value shl 8) + (b4 and $FF);
   convert_to_cardinal := value;
end; // convert_to_cardinal //

function convert_to_word (b1, b2: uInt8): uInt16;

// Convert two bytes to an unsigned 16 bit Int32 (uInt16)

begin
   convert_to_word := ((b1 and $FF ) shl 8) + (b2 and $FF);
end; // convert_to_word //

function double_to_int32 (ftVal: Double): uInt32;
var HW, LW: uInt16;
    D: Double;
    I: Integer;
begin
  HW := Trunc(ftVal);
  D  := Frac(ftVal);
  LW := 0;
  for I := 1 to 16 do
  begin
    LW := LW shl 1;
    D := 2 * D;
    if ftVal >= 1 then
    begin
      LW := LW or $0001;
      D := Frac(D);
    end;
  end;
  Result := MakeLong (LW, HW);
end; // double_to_int32 //

function int32_to_double (dwVal: uInt32): Double;
var LW: uInt16;
    D: Double;
begin
  Result := SmallInt (HiWord(dwVal));
  LW := LoWord (dwVal);
  D := 1;
  while LW <> 0 do
  begin
    D := 2 * D;
    if WordBool(LW and $8000) then
      Result := Result + (1 / D);
    LW := LW shl 1;
  end;
end; // int32_to_double //

function IntToBin (value: LongInt; digits: integer): string;
begin
   result := StringOfChar ('0', digits);
   while value > 0 do begin
      if (value and 1) = 1 then
        result [digits] := '1';
      dec (digits) ;
      value := value shr 1;
   end; // while
end; // IntToBin //

function BinToInt (Value: String): LongInt;
var i: Integer;
begin
   Result := 0;

//remove leading zeroes
   while Copy (Value,1,1) = '0'
      do Value := Copy (Value, 2, Length (Value) - 1);

//do the conversion
   for i := Length (Value) downto 1 do
      if Copy (Value, i, 1) = '1'
         then Result := Result + (1 shl (Length (Value) - i));
end; // BinToInt //

function limit (value: double; min, max: Int32): Int32;
begin
   if value < min then limit := min else
   if value > max then limit := max
                  else limit := round (value);
end; // limit //

// Rescales source (source) in the target_range [source_min..source_max]
// to integer, starting from target_min with target_range target_range.
// Source < source_min yield target_min,
// source > source_max yields target_min + target_range
// The function is overloaded: the target is an integer, input can be floating
// point or integer

function rescale
(
   source,              // source to be converted
   source_min,          // between source_min
   source_max: double;  // and source_max
   target_min,          // will be converted to a source between target_min
   target_range: Int32  // and target_min + target_range
): Int32;               // Result is integer
begin
   if source_min = source_max then Result := target_min else
   if source < source_min then Result := target_min else
   if source > source_max then Result := target_min + target_range
      else Result := target_min + round (target_range * (source - source_min) /
                                    (source_max - source_min));
end; // rescale //

function rescale
(
   source,
   source_min,
   source_max,
   target_min,
   target_range: Int32
): Int32;
begin
   if source < source_min then Result := target_min else
   if source > source_max then Result := target_min + target_range
      else Result := target_min + round (target_range * (source - source_min) /
                                  (source_max - source_min));
end; // rescale //

function rescale
(
   source,
   source_min,
   source_max,
   target_min,
   target_range: double
): double;
begin
   if source < source_min then Result := target_min else
   if source > source_max then Result := target_min + target_range
      else Result := target_min + target_range * (source - source_min) /
                                  (source_max - source_min);
end; // rescale //

end. // Unit: utilities_math //
