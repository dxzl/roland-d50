I changed three very important things to make this work,

1) In MSC_Definitions "SysEx" should be a PByte midi-input data but was a PChar (wchar_t*)
2) In both MSC_In_Device and MSC_Out_Device, there is a "Move" that must be changed to "MoveMemory"

- Scott Swift