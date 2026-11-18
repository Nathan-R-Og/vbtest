#ifndef MISC_H
#define MISC_H

#include "types.h"

//Miscellaneous Hardware
//http://perfectkiosk.net/stsvb.html#misc_hardware


#ifndef __ASSEMBLER__

typedef enum SDR_ctrl {
    SDR_PWR = 1, //Low battery
    SDR_SGN = 2, //Signature
    SDR_A = 4, //A button
    SDR_B = 8, //B button
    SDR_RT = 0x10, //R button
    SDR_LT = 0x20, //L button
    SDR_RU = 0x40, //Right D-pad up
    SDR_RR = 0x80, //Right D-pad right
    SDR_LR = 0x100, //Left D-pad right
    SDR_LL = 0x200, //Left D-pad left
    SDR_LD = 0x400, //Left D-pad down
    SDR_LU = 0x800, //Left D-pad up
    SDR_STA = 0x1000, //Start button
    SDR_SEL = 0x2000, //Select button
    SDR_RL = 0x4000, //Right D-pad left
    SDR_RD = 0x8000, //Right D-pad down
} SDR_ctrl;

// Serial Data Low Register
#define SDLR        (*(vu16*)0x02000010)
//erial Data High Register
#define SDHR        (*(vu16*)0x02000014)


// Wait Control Register
#define WCR        (*(vu16*)0x02000024)

typedef enum SCR_ctrl {
    SCR_S_AbtDis = 1, //When set, any active hardware button state read is aborted.
    SCR_SI_Stat = 2, //Set while a hardware button state read is in progress.
    SCR_HW_SI = 4, //Set to initiate a hardware button state read.
    SCR_Soft_Ck = 0x10, //Sends the inverse read bit to the game pad.
    SCR_Para_Si = 0x20, //When set, a latch signal resets the game pad's read operation.
    SCR_K_Int_Inh = 0x80, //	When clear, the key input interrupt is enabled. When set, it is acknowledged and disabled.

} SCR_ctrl;
// Serial Control Register
#define SRC        (*(vu16*)0x02000028)



#else

#define WCR        0x02000024




#endif



#endif