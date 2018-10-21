Compiled binaries for RV32I test-suite

Compiled to location 0
Fixed trap vector not used (test use writeable mtvec only)
IO assertions enabled
Fail/pass is indicated by forever loop at locations 0x0004 or 0x0800
A single LED connected to PC bit 11 could be used pass-fail visual indicator
Signature blocks in the RAM are wrapped between 16 bytes of BB ... and EE..
Signatures can be extracted from RAM in verilator
