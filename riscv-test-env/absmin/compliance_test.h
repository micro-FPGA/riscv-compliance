// RISC-V Compliance Test Header File
// Copyright (c) 2017, Codasip Ltd. All Rights Reserved.
// See LICENSE for license details.
//
// Description: Common header file for RV32I tests

#ifndef _COMPLIANCE_TEST_H
#define _COMPLIANCE_TEST_H

#include "riscv_test.h"

//-----------------------------------------------------------------------
// RV Compliance Macros
//-----------------------------------------------------------------------

#define RV_COMPLIANCE_HALT                                                    \
        la a0, codasip_signature_start;                                        \
        la a1, codasip_signature_end; \
        li a2, 0xF0000; \
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
//        lw a4, 0 (a2); \
//        bne x0, a4, complience_halt_break;\
        li a4, 0xFF; \
        sb a4, 0 (a2); \
//        j complience_halt_break; \


#define RV_COMPLIANCE_RV32M                                                   \

//Nops are for RVC JAL test which require offset
#ifdef RVC
#define RV_COMPLIANCE_CODE_BEGIN                                              \
        .section .text.init;                                                  \
        .align  4;                                                            \
        .globl _start;                                                        \
        _start:                                                               \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop;nop; \
        nop;nop;nop;nop;nop;nop;nop; 
#else
#define RV_COMPLIANCE_CODE_BEGIN                                              \
        .section .text.init;                                                  \
        .align  4;                                                            \
        .globl _start;                                                        \
        _start:                                                               
#endif


#define RV_COMPLIANCE_CODE_END                                                \


#define RV_COMPLIANCE_DATA_BEGIN                                              \
        .align 4;                                                             \
        .global codasip_signature_start;                                      \
        codasip_signature_start:                                              \

#define RV_COMPLIANCE_DATA_END                                                \
        .align 4;                                                             \
        .global codasip_signature_end;                                        \
        codasip_signature_end:                                                 \

#endif
