#ifndef VIP_H
#define VIP_H

#include "types.h"

//Virtual Boy System Registers
//http://perfectkiosk.net/stsvb.html#cpu_system_registers

#ifndef __ASSEMBLER__


#else

// Address Trap Register for Execution
#define ADTRE        25
// Cache Control Word
#define CHCW        24
// Exception Cause Register
#define ECR        4
// Exception/Interrupt PC
#define EIPC        0
// Exception/Interrupt PSW
#define EIPSW        1
// Fatal Error PC
#define FEPC        2

// Fatal Error PSW
#define FEPSW        3
// Processor ID Register
#define PIR        6
// Program Status Word
#define PSW        5
// Task Control Word
#define TKCW        7

#define SYS_29 29
#define SYS_30 30
#define SYS_31 31

#endif



#endif