Absolute minimal environment to run RISCV compliance tests.

exceptions, trap/vector, call/return, ecall, ebreak and any CSR's are not needed or used.

FAILED result is signalled with forever loop at low absolute PC address 
OK result is signalled with forever loop at PC address with some higher Address bit set.
A single LED on address bus would be sufficient to signal pass/fail results.

Special \riscv-target\absmin included configuration IO macros to for optional IO Assertion
