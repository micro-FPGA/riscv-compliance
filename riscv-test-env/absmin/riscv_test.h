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
_start:                                                                 \
        /* reset vector */                                              \
        j reset_vector;                                                 \
        .align 2;                                                       \
fail_loop:                                                              \
        j fail_loop;                                                    \
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
        j ok_loop

#define TESTNUM gp
#define RVTEST_FAIL                                                     \
        j fail_loop

//-----------------------------------------------------------------------
// Data Section Macro
//-----------------------------------------------------------------------

#define EXTRA_DATA

#define RVTEST_DATA_BEGIN                                               \
        EXTRA_DATA                                                      \
        .pushsection .tohost,"aw",@progbits;                            \
        .align 8; .global ok_loop; ok_loop: j ok_loop;                  \
        .popsection;                                                    \
        .align 4;                                                       \
        .global begin_signature; begin_signature:                       \
        .dword 0xbbbbbbbbbbbbbbbb; .dword 0xbbbbbbbbbbbbbbbb;

#define RVTEST_DATA_END .align 4;                                       \
        .global end_signature; end_signature:                           \
        .dword 0xeeeeeeeeeeeeeeee; .dword 0xeeeeeeeeeeeeeeee;                            


#endif
