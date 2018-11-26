// See LICENSE for license details.

#ifndef _ENV_PHYSICAL_SINGLE_CORE_H
#define _ENV_PHYSICAL_SINGLE_CORE_H

#include "../encoding.h"

//-----------------------------------------------------------------------
// Begin Macro
//-----------------------------------------------------------------------

// RV32I in M (Machine mode) is the only we need to comply with!

#define RVTEST_RV32M                                                    \
  .macro init;                                                          \
  RVTEST_ENABLE_MACHINE;                                                \
  .endm

#if __riscv_xlen == 64
# define CHECK_XLEN li a0, 1; slli a0, a0, 31; bgez a0, 1f; RVTEST_PASS; 1:
#else
# define CHECK_XLEN li a0, 1; slli a0, a0, 31; bltz a0, 1f; RVTEST_PASS; 1:
#endif


#define RVTEST_CODE_BEGIN                                               \
        .section .text.init;                                            \
        .align  6;                                                      \
        .globl _start;                                                  \
        .globl fail_loop;                                               \
        .globl ok_loop;                                                 \
_start:                                                                 \
        /* reset vector */                                              \
        j reset_vector;                                                 \
        .align 2;                                                       \
fail_loop:                                                              \
        j fail_loop;                                                    \
        .align 4;                                                       \
ok_loop:                                                                \
        j ok_loop;                                                      \
reset_vector:                                                           \
        li TESTNUM, 0;                                                  \
begin_testcode:


//-----------------------------------------------------------------------
// End Macro
//-----------------------------------------------------------------------

#define RVTEST_CODE_END                                                 \
end_testcode:                                                           \
        unimp

//-----------------------------------------------------------------------
// Pass/Fail Macro
//-----------------------------------------------------------------------
//#define RVTEST_SYNC fence
#define RVTEST_SYNC nop

#define RVTEST_PASS                                                     \
        la a0, begin_signature;                                         \
        la a1, end_signature;                                           \
        li a2, 0xC000;                                                  \
complience_halt_loop: \
        beq a0, a1, complience_halt_break; \
        addi a3, a0, 16; \
complience_halt_loop2: \
        addi a3, a3, -1; \
        lb a4, 0 (a3); \
        srai a5, a4, 4; \
        andi a5, a5, 0xF; \
        li a6, 10; \
        blt a5, a6, notLetter; \
        addi a5, a5, 39; \
notLetter: \
        addi a5, a5, 0x30; \
        sb a5, 0 (a2); \
        srai a5, a4, 0; \
        andi a5, a5, 0xF; \
        li a6, 10; \
        blt a5, a6, notLetter2; \
        addi a5, a5, 39; \
notLetter2: \
        addi a5, a5, 0x30; \
        sb a5, 0 (a2); \
        bne a0, a3,complience_halt_loop2;  \
        addi a0, a0, 16; \
        li a4, 0x0A; \
        sb a4, 0 (a2); \
        j complience_halt_loop; \
complience_halt_break:; \
        li a4, 0xFF; \
        sb a4, 0 (a2); \
        j ok_loop

#define TESTNUM gp
#define RVTEST_FAIL                                                     \
        j fail_loop

//-----------------------------------------------------------------------
// Data Section Macro
//-----------------------------------------------------------------------

//        .align 8; .global ok_loop; ok_loop: j ok_loop;                  \

#define EXTRA_DATA

#define RVTEST_DATA_BEGIN                                               \
        EXTRA_DATA                                                      \
        .align 4;                                                       \
        .dword 0xbbbbbbbbbbbbbbbb; .dword 0xbbbbbbbbbbbbbbbb;           \
        .global begin_signature; begin_signature:                       


#define RVTEST_DATA_END .align 4;                                       \
        .global end_signature; end_signature:                           \
        .dword 0xeeeeeeeeeeeeeeee; .dword 0xeeeeeeeeeeeeeeee;                            


#endif
