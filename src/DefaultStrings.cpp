#include <vcl.h>
#include "MainForm.h"
#pragma hdrstop
// Include header files common to all files before this directive!

#include <Controls.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool PARTIALRANDP1[D50_PATCH_SECTION_SIZE] =
{
    //--------------------
    // set to 0 or 1
    1,1,1,1,1,0,1,1, // 0-7
    1,1,1,1,0,1,1,1, // 8-15
    1,1,0,0,0,0,0,0, // 16-23
    0,0,0,0,0,0,0,0, // 24-31
    1,1,1,1,1,1,1,1, // 32-39
    1,1,1,1,1,1,1,1, // 40-47
    1,1,1,1,1,0,     // 49-53
    //--------------------
    // last 10 always set 0!
                0,0,
    0,0,0,0,0,0,0,0
};
bool PARTIALRANDP2[D50_PATCH_SECTION_SIZE] =
{
    //--------------------
    // set to 0 or 1
    1,1,1,1,1,0,1,1, // 0-7
    1,1,1,1,0,1,1,1, // 8-15
    1,1,0,0,0,0,0,0, // 16-23
    0,0,0,0,0,0,0,0, // 24-31
    1,1,1,1,1,1,1,1, // 32-39
    1,1,1,1,1,1,1,1, // 40-47
    1,1,1,1,1,0,     // 49-53
    //--------------------
    // last 10 always set 0!
                0,0,
    0,0,0,0,0,0,0,0
};
bool PARTIALRANDP3[D50_PATCH_SECTION_SIZE] =
{
    //--------------------
    // set to 0 or 1
    1,1,1,1,1,0,1,1, // 0-7
    1,1,1,1,0,1,1,1, // 8-15
    1,1,0,0,0,0,0,0, // 16-23
    0,0,0,0,0,0,0,0, // 24-31
    1,1,1,1,1,1,1,1, // 32-39
    1,1,1,1,1,1,1,1, // 40-47
    1,1,1,1,1,0,     // 49-53
    //--------------------
    // last 10 always set 0!
                0,0,
    0,0,0,0,0,0,0,0
};
bool PARTIALRANDP4[D50_PATCH_SECTION_SIZE] =
{
    //--------------------
    // set to 0 or 1
    1,1,1,1,1,0,1,1, // 0-7
    1,1,1,1,0,1,1,1, // 8-15
    1,1,0,0,0,0,0,0, // 16-23
    0,0,0,0,0,0,0,0, // 24-31
    1,1,1,1,1,1,1,1, // 32-39
    1,1,1,1,1,1,1,1, // 40-47
    1,1,1,1,1,0,     // 49-53
    //--------------------
    // last 10 always set 0!
                0,0,
    0,0,0,0,0,0,0,0
};
bool PARTIALRANDDEF[D50_PATCH_SECTION_SIZE] =
{
    //--------------------
    // set to 0 or 1
    1,1,1,1,1,0,1,1, // 0-7
    1,1,1,1,0,1,1,1, // 8-15
    1,1,0,0,0,0,0,0, // 16-23
    0,0,0,0,0,0,0,0, // 24-31
    1,1,1,1,1,1,1,1, // 32-39
    1,1,1,1,1,1,1,1, // 40-47
    1,1,1,1,1,0,     // 49-53
    //--------------------
    // last 10 always set 0!
                0,0,
    0,0,0,0,0,0,0,0
};
bool COMMONRANDP1[D50_PATCH_SECTION_SIZE] =
{
    // first 10 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 16 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool COMMONRANDP2[D50_PATCH_SECTION_SIZE] =
{
    // first 10 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 16 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool COMMONRANDP3[D50_PATCH_SECTION_SIZE] =
{
    // first 10 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 16 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool COMMONRANDP4[D50_PATCH_SECTION_SIZE] =
{
    // first 10 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 16 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool COMMONRANDDEF[D50_PATCH_SECTION_SIZE] =
{
    // first 10 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 16 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool PATCHRANDP1[D50_PATCH_SECTION_SIZE] =
{
    // first 18 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 24 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool PATCHRANDP2[D50_PATCH_SECTION_SIZE] =
{
    // first 18 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 24 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool PATCHRANDP3[D50_PATCH_SECTION_SIZE] =
{
    // first 18 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 24 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool PATCHRANDP4[D50_PATCH_SECTION_SIZE] =
{
    // first 18 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 24 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
bool PATCHRANDDEF[D50_PATCH_SECTION_SIZE] =
{
    // first 18 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,
    //--------------------
    // set to 0 or 1
        0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    //--------------------
    // last 24 always set 0!
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
const _TCHAR *COMMONNAMES[D50_PATCH_SECTION_SIZE] =
{
  _T("Tone Name:"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"),
  _T("*"), _T("*"), _T("Structure No."), _T("P-ENV Velocity Range"), _T("P-ENV Time Keyfollow"), _T("P-ENV Time 1"), _T("P-ENV Time 2"), _T("P-ENV Time 3"),
  _T("P-ENV Time 4"), _T("P-ENV Level 0"), _T("P-ENV Level 1"), _T("P-ENV Level 2"), _T("P-ENV Sustain Level"), _T("P-ENV End Level"), _T("P-Mod LFO Depth"), _T("P-Mod Lever"),
  _T("P-Mod After-Touch"), _T("LFO-1 Wave-Form"), _T("LFO-1 Rate"), _T("LFO-1 Delay-Time"), _T("LFO-1 Sync"), _T("LFO-2 Wave-Form"), _T("LFO-2 Rate"), _T("LFO-2 Delay-Time"),
  _T("LFO-2 Sync"), _T("LFO-3 Wave-Form"), _T("LFO-3 Rate"), _T("LFO-3 Delay-Time"), _T("LFO-3 Sync"), _T("Low EQ Frequency"), _T("Low EQ Gain"), _T("Low EQ Frequency"),
  _T("High EQ Q"), _T("High EQ Gain"), _T("Chorus Type"), _T("Chorus Rate"), _T("Chorus Depth"), _T("Chorus Balance"), _T("Partial Mute"), _T("Partial Balance"),
  _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"),
  _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext")
};
Byte COMMONMAX[D50_PATCH_SECTION_SIZE] =
{
    63,63,63,63,63,63,63,63,
    63,63,6,2,4,50,50,50,
    50,100,100,100,100,100,100,100,
    100,3,100,100,2,3,100,100,
    1,3,100,100,1,15,24,21,
    8,24,7,100,100,100,3,100,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
const _TCHAR *PATCHNAMES[D50_PATCH_SECTION_SIZE] =
{
  _T("Patch Name:"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"),
  _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"), _T("*"),
  _T("*"), _T("*"), _T("Key Mode"), _T("Split Point"), _T("Portamento Mode"), _T("Hold Mode"), _T("Upper Tone Key Shift"), _T("Lower Tone Key Shift"),
  _T("Upper Tone Fine Tune"), _T("Lower Tone Fine Tune"), _T("Bender Range"), _T("After-Touch Bend Range"), _T("Portamento Time"), _T("Output Mode"), _T("Reverb Type"), _T("Reverb Balance"),
  _T("Total Volume"), _T("Tone Balance"), _T("Chase Mode"), _T("Chase Level"), _T("Chase Time"), _T("MIDI Transmit Channel"), _T("MIDI Seperate Rev Time"), _T("MIDI Transmit Prog Change"),
  _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"),
  _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"),
  _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext")
};
Byte PATCHMAX[D50_PATCH_SECTION_SIZE] =
{
    63,63,63,63,63,63,63,63,
    63,63,63,63,63,63,63,63,
    63,63,8,60,2,2,48,48,
    100,100,12,24,100,3,31,100,
    100,100,2,100,100,16,16,100,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
const _TCHAR *PARTIALNAMES[D50_PATCH_SECTION_SIZE] =
{
  _T("WG Pitch (Coarse)"), _T("WG Pitch (Fine)"), _T("WG Pitch (Keyfollow)"), _T("WG Mod (LFO Mode)"), _T("WG Mod (P-ENV Mode)"), _T("WG Mod (Bend Mode)"), _T("WG Wave (Form)"), _T("WG PCM (Wave #)"),
  _T("WG Pulse Width"), _T("WG PW Velocity Range"), _T("WG PW LFO Select"), _T("WG PW LFO Depth"), _T("WG PW After Touch Range"), _T("TVF Cutoff Frequency"), _T("TVF Resonance"), _T("TVF Keyfollow"),
  _T("TVF Bias Point/Dir"), _T("TVF Bias Level"), _T("TVF ENV Depth"), _T("TVF ENV Velocity Range"), _T("TVF ENV Depth Keyfollow"), _T("TVF ENV Time Keyfollow"), _T("TVF ENV Time 1"), _T("TVF ENV Time 2"),
  _T("TVF ENV Time 3"), _T("TVF ENV Time 4"), _T("TVF ENV Time 5"), _T("TVF ENV Level 1"), _T("TVF ENV Level 2"), _T("TVF ENV Level 3"), _T("TVF ENV Sustain Level"), _T("TVF ENV End Level"),
  _T("TVF Mod LFO Select"), _T("TVF Mod LFO Depth"), _T("TVF Mod After-Touch Range"), _T("TVA Level"), _T("TVA Velocity-Range"), _T("TVA Bias Point"), _T("TVA Bias Level"), _T("TVA ENV Time 1"),
  _T("TVA ENV Time 2"), _T("TVA ENV Time 3"), _T("TVA ENV Time 4"), _T("TVA ENV Time 5"), _T("TVA ENV Level 1"), _T("TVA ENV Level 2"), _T("TVA ENV Level 3"), _T("TVA ENV Sustain Level"),
  _T("TVA ENV End Level"), _T("TVA ENV Velocity Follow"), _T("TVA ENV Time Keyfollow"), _T("TVA Mod LFO Select"), _T("TVA Mod LFO Depth"), _T("TVA Mod After-Touch Range"), _T("ext"), _T("ext"),
  _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext"), _T("ext")
};
Byte PARTIALMAX[D50_PATCH_SECTION_SIZE] =
{
    72,100,16,3,2,2,1,99,
    100,14,5,100,14,100,30,14,
    127,14,100,100,4,4,100,100,
    100,100,100,100,100,100,100,1,
    5,100,14,100,100,127,12,100,
    100,100,100,100,100,100,100,100,
    1,4,4,5,100,14,0,0,
    0,0,0,0,0,0,0,0
};

// addresses for the 7 sections of a patch in the temp-area
// of the Roland D-50
UInt16 ROLANDADDRESS[TOTAL_TABS] =
{
    0x0000, 0x0040, 0x0100, 0x0140, 0x0200, 0x0240, 0x0300
};

// Test midi sequence we stream after sending a new patch...
//
// From: http://midi.teragonaudio.com/tech/stream.htm (no name to give attribution
// but his example allowed me to adapt streaming into MSC_Out_Device.pas (S.S.))
// Here's an array of MIDI Note-On and Note-Off events to play our musical phrase. We declare the
// array as an array of unsigned longs. Makes it easier to statically declare the MIDIEVENT structures
// in an array.
//
// I've set the timing fields in terms of PPQN clocks, as they would be found in MIDI File using
// 96 PPQN Time Division.
//
// NOTES: The first event is a System Exclusive event to set Master Volume to full. Note that the high
// byte of the dwEvent field (ie, the 3rd unsigned long) must be MEVT_LONGMSG, and the remaining bytes
// must be the count of how many SysEx bytes follow. Also note that the data must be padded out to a
// doubleword boundary. That's implicit in our declaration of this as an unsigned long array.
//
// The second event is a Tempo event which sets tempo to 500,000 microseconds per quarter
// note. I put this event at the start of the array so that I don't have to use midiStreamProperty()
// to set tempo prior to playback. Note that the high byte of dwEvent must be MEVT_TEMPO to tell the
// stream device that this is a Tempo event.
//
// Also, note that the MIDI event is packed into a long the same way that it would be to send to
// midiOutShortMsg().
//

// ALL THE NOTES ARE FIXED AT CHANNEL '0' (1), SysEx is in reverse-order!

// Twinkle twinkle little star...
unsigned long SEQ1[] =
{
    0, 0, ((unsigned long)MEVT_LONGMSG<<24) | 8, 0x047F7FF0, 0xF77F7F01,
    0, 0, ((unsigned long)MEVT_TEMPO<<24) | 0x0007A120,

    0, 0, 0x000079B0, // all controllers off (data byte 1, 79 hex)
    0, 0, 0x00007BB0, // all notes off (data byte 1, 7B hex)

    0, 0, 0x007F3C90, // data byte 1, hex 3C (4th ovtave C), data byte 2 is velocity 7F (note on)
    48, 0, 0x00003C90, // (note off - velocity is 00)
    0, 0, 0x007F3C90, // twice...
    48, 0, 0x00003C90,

    0, 0, 0x007F4390,  // 4th octave G
    48, 0, 0x00004390,
    0, 0, 0x007F4390,
    48, 0, 0x00004390,

    0, 0, 0x007F4590, // 4th octave A
    48, 0, 0x00004590,
    0, 0, 0x007F4590,
    48, 0, 0x00004590,

    0, 0, 0x007F4390, // back to G for longer time
    86, 0, 0x00004390,

    10, 0, 0x007F4190, // 41 hex is a 4th ovtive F
    48, 0, 0x00004190,
    0, 0, 0x007F4190,
    48, 0, 0x00004190,

    0, 0, 0x007F4090, // E
    48, 0, 0x00004090,
    0, 0, 0x007F4090,
    48, 0, 0x00004090,

    0, 0, 0x007F3E90, // D
    48, 0, 0x00003E90,
    0, 0, 0x007F3E90,
    48, 0, 0x00003E90,

    0, 0, 0x007F3C90, // C
    150, 0, 0x00003C90
//    350, 0, 0x00003C90
};
int SIZESEQ1 = sizeof(SEQ1);
//---------------------------------------------------------------------------

