unit MSC_Component;

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

uses Classes, Wintypes, SysUtils, MSC_Definitions;

type
   TTime_Change_Event = procedure (Sender: Tobject; time, current_event: Int32) of object;

   EMSC_Component_Error = class (EMSC_Error);

   TMSC_Component = class (TComponent)
   end; // Class: TMSC_Component //

implementation

end. // Unit: MSC_Component //
