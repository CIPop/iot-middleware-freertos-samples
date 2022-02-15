/* Copyright (c) Microsoft Corporation.
   Licensed under the MIT License. */

#include <stdint.h>
#include <memory.h>
#include <stdio.h>
#include "main.h"
#include "coredump.h"

#define DEBUG_ISR_REG_SAVED         8
#define DEBUG_REGISTERS_SAVED       14
#define DEBUG_TOTAL_WORDS_SAVED     (DEBUG_ISR_REG_SAVED + DEBUG_REGISTERS_SAVED + DEBUG_STACK_WORDS_SAVED + 1)
#define DEBUG_DUMP_MARKER           0xDEADBEEF

/**
 * @brief The following constant must be defined in the LD file.
 * @details LD File definition:
 * 
 *          _Max_Dump_Size = 0x80;
 * 
 *          .debug_dump :
 *          {
 *              . = ALIGN(8);
 *              PROVIDE ( dump_location = . );
 *              PROVIDE ( _dump_location = . );
 *              . = . + _Max_Dump_Size;
 *              . = ALIGN(8);
 *          }
 * 
 */
extern int32_t core_dump_location asm("dump_location");

__attribute__(( used )) void CoreDump(int32_t* registers_frame)
{
    // R0 - R3, R12, LR, PC and xPSR are already saved by the MCU.

    // Copy the rest of the CPU registers.
    register int r4 __asm("r4");
    register int r5 __asm("r5");
    register int r6 __asm("r6");
    register int r7 __asm("r7");
    register int r8 __asm("r8");
    register int r9 __asm("r9");
    register int r10 __asm("r10");
    register int r11 __asm("r11");

    int32_t* debug_buffer = &core_dump_location;
    *debug_buffer++ =  DEBUG_DUMP_MARKER;                //  0
    *debug_buffer++ =  r4;                               //  1
    *debug_buffer++ =  r5;                               //  2
    *debug_buffer++ =  r6;                               //  3
    *debug_buffer++ =  r7;                               //  4
    *debug_buffer++ =  r8;                               //  5
    *debug_buffer++ =  r9;                               //  6
    *debug_buffer++ =  r10;                              //  7
    *debug_buffer++ =  r11;                              //  8

    *debug_buffer++ = SCB->CFSR;                         //  9
    *debug_buffer++ = SCB->HFSR;                         // 10
    *debug_buffer++ = SCB->DFSR;                         // 11
    *debug_buffer++ = SCB->MMFAR;                        // 12
    *debug_buffer++ = SCB->BFAR;                         // 13
    *debug_buffer++ = SCB->AFSR;                         // 14

    // Note: the following code assumes that the LOCKUP condition (double-fault) will lead to a 
    //       system reset. Accessing the registers_frame may cause a double-fault.
    memcpy(
        debug_buffer, 
        registers_frame, 
        (DEBUG_ISR_REG_SAVED + DEBUG_STACK_WORDS_SAVED) * sizeof(int32_t));
    
    // R0                                                // 15
    // R1                                                // 16
    // R2                                                // 17
    // R3                                                // 18
    // R12                                               // 19
    // LR                                                // 20
    // PC                                                // 21
    // xPSR                                              // 22

    // DEBUG_STACK_WORDS_SAVED                           // 23+

    // Reset
    NVIC_SystemReset();

    // Should never reach this code:
    while(1) {}
}

void ResetCoreDumpMarker()
{
    CoreDumpStruct* dump = (CoreDumpStruct*)(&core_dump_location);
    dump->marker = 0;
}

bool IsCoreDumpPresent()
{
    CoreDumpStruct* dump = (CoreDumpStruct*)(&core_dump_location);
    return dump->marker == (int32_t)DEBUG_DUMP_MARKER;
}

const CoreDumpStruct* GetCoreDumpInfo()
{
    return (const CoreDumpStruct*)(&core_dump_location);
}

int CheckCoreDump()
{
    CoreDumpStruct* dump = (CoreDumpStruct*)(&core_dump_location);

    if (dump->marker == (int32_t)DEBUG_DUMP_MARKER)
    {
        // Clear the marker to avoid reporting it next time.
        // TODO: clear the marker _only_ after the dump has been reported to IoT.
        // dump->marker = 0;

        printf("The system rebooted: crash-dump present!\r\n");
        
        printf("\r\nR0 -  R3:\t");
        printf("%08lx\t", dump->r0);
        printf("%08lx\t", dump->r1);
        printf("%08lx\t", dump->r2);
        printf("%08lx\t", dump->r3);

        printf("\r\nR4 -  R7:\t");
        printf("%08lx\t", dump->r4);
        printf("%08lx\t", dump->r5);
        printf("%08lx\t", dump->r6);
        printf("%08lx\t", dump->r7);

        printf("\r\nR8 - R11:\t");
        printf("%08lx\t", dump->r8);
        printf("%08lx\t", dump->r9);
        printf("%08lx\t", dump->r10);
        printf("%08lx\t", dump->r11);


        printf("\r\nR12     :\t");
        printf("%08lx\t", dump->r12);


        printf("\r\n\r\nxPSR:\t%08lx", dump->xpsr);
        printf("\tPC:\t%08lx", dump->pc);
        // Note that LR will always have the last bit set for thumb mode.
        printf("\tLR:\t%08lx", dump->lr);
        
        // TODO: Preferably on the server side, disect CFSR, HFSR and DFSR registers:
        //       SCB_CFSR_*_Msk; SCB_HFSR_*_Msk; SCB_DFSR_*_Msk

        printf("\r\nCFSR\t%08lx", dump->cfsr);
        printf("\tHFSR\t%08lx", dump->hfsr);
        printf("\tDFSR\t%08lx", dump->dfsr);

        printf("\r\nMMFAR\t%08lx", dump->mmfar);
        printf("\tBFAR\t%08lx", dump->bfar);
        printf("\tAFSR\t%08lx", dump->afsr);

        printf("\r\nStack:\r\n");

        for (int i = 0; i < DEBUG_STACK_WORDS_SAVED; i++)
        {
            if (i % 4 == 0)
            {
                putchar('\r');
                putchar('\n');
            }
            else
            {
                putchar('\t');
            }
            
            printf("%08lx", dump->stack[i]);
        }

        printf("\r\n--------\r\n\r\n");
        return 1;
    }

    return 0;
}
