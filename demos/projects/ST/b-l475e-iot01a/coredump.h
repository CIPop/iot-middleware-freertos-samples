/* Copyright (c) Microsoft Corporation.
   Licensed under the MIT License. */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COREDUMP_H
#define __COREDUMP_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Configuration -------------------------------------------------------------*/
#define DEBUG_STACK_WORDS_SAVED     4       // Important: do not exceed the bottom of the stack!

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    int32_t marker;
    int32_t r4;
    int32_t r5;
    int32_t r6;
    int32_t r7;
    int32_t r8;
    int32_t r9;
    int32_t r10;
    int32_t r11;
    int32_t cfsr;
    int32_t hfsr;
    int32_t dfsr;
    int32_t mmfar;
    int32_t bfar;
    int32_t afsr;

    // The following format is fixed by the CPU
    int32_t r0;
    int32_t r1;
    int32_t r2;
    int32_t r3;
    int32_t r12;
    int32_t lr;
    int32_t pc;
    int32_t xpsr;
    int32_t stack[DEBUG_STACK_WORDS_SAVED];   
} CoreDumpStruct;

/**
 * @brief Generates the core-dump. Call only from HardFault_Handler!
 * 
 * @param registers_frame Either MSP or PSP as indicated by LR.
 */
void CoreDump(int32_t* registers_frame);

/**
 * @brief Check if a core-dump was stored.
 * 
 * @return true A core-dump is present. You must process it then call `ResetCoreDumpMarker()`.
 * @return false A core-dump is not present.
 */
bool IsCoreDumpPresent();

/**
 * @brief Get CoreDump information.
 * 
 */
const CoreDumpStruct* GetCoreDumpInfo();

/**
 * @brief Resets the core-dump marker.
 * 
 */
void ResetCoreDumpMarker();

#ifdef __cplusplus
}
#endif

#endif /* __COREDUMP_H */
