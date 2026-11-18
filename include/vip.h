#ifndef VIP_H
#define VIP_H

#include "types.h"

//Virtual Boy Hardware Registers
//http://perfectkiosk.net/stsvb.html#vip_memory_map

#ifndef __ASSEMBLER__

// Left frame buffer 0
#define LFB0        ((u16*)0x00000000)
// Character table 0
#define CTB0        ((u16*)0x00006000)
// Left frame buffer 1
#define LFB1        ((u16*)0x00008000)
// Character table 1
#define CTB1        ((u16*)0x0000E000)
// Right frame buffer 0
#define RFB0        ((u16*)0x00010000)
// Character table 2
#define CTB2        ((u16*)0x00016000)
// Right frame buffer 1
#define RFB1        ((u16*)0x00018000)
// Character table 3
#define CTB3        ((u16*)0x0001E000)
// Background maps and world parameters
#define MAPS        ((u16*)0x00020000)


typedef struct ATTR_ctrl {
    u16 BG_Map_Base : 4; // The index of the first background map in the world's background.
    u16 used : 2;
    u16 END : 1; //End World Specification Flag - If set, this world and all worlds of lesser index will not be drawn to the frame buffer.
    u16 OVER : 1; //Overplane - If clear, the world's background will repeat indefinitely.
    //If set, characters beyond the background's bounds will use the character specified by Overplane Character.
    u16 SCY : 2; //Screen Y Size - Raise 2 to this power for the height of the world's background in background maps.
    u16 SCX : 2; //Screen X Size - Raise 2 to this power for the width of the world's background in background maps.
    u16 BGM : 2; //BG Modification	- Indicates the world's contents.
    u16 RON : 1; //Right Display On - If set, the world will be drawn to the right image.
    u16 LON : 1; //Left Display On - If set, the world will be drawn to the left image.

    u16 GX : 10; //BG X Destination - The signed horizontal coordinate of the left edge of the world from the left edge of the image.
    u16 used2 : 6;

    u16 GP : 10; //BG Parallax Destination - The signed parallax offset applied to the world's horizontal coordinate.
    u16 used3 : 6;

    u16 GY; //BG Y Destination - The signed vertical coordinate of the top edge of the world from the top edge of the image.

    u16 MX : 13; //BG X Source - The signed horizontal source coordinate of the pixel within the world's background,
    //relative to the top-left corner of the background, to be displayed in the top-left corner of the world.
    u16 used4 : 3;

    u16 MP : 15; //BG Parallax Source - The signed parallax offset applied to the background's horizontal source coordinate.
    u16 used5 : 1;

    u16 MY : 13; //BG Y Source - The signed vertical source coordinate of the pixel within the world's background,
    //relative to the top-left corner of the background, to be displayed in the top-left corner of the world.
    u16 used6 : 3;

    u16 W : 13; //Window Width - Add 1 to this figure to yield the width in pixels of the world. This field's format depends on BGM.
    u16 used7 : 3;

    u16 H; //Window Height - Add 1 to this figure to yield the height in pixels of the world. This value is signed.
    u16 Param_Base; //Specifies the location in world parameter memory where this world's parameters can be found.
    u16 Overplane_Character; //When OVER is set, characters beyond the background's bounds will use the cell in background map memory at the index given by this field.
    //The corresponding address is 0x00020000 + Overplane_Character × 2
    u16 used8[5];
} ATTR_ctrl;
// World attributes
#define ATTR        ((ATTR_ctrl*)0x0003D800)
// Left column table
#define LCTB        ((u16*)0x0003DC00)
// Right column table
#define RCTB        ((u16*)0x0003DE00)


typedef struct OAM {
    u16 JX : 10; // Display Pointer X
    u16 unused1 : 6;
    u16 JP : 10;  // Parallax
    u16 unused2 : 4;
    u16 JRON : 1; // Right Display On
    u16 JLON : 1; // Left Display On
    u16 JY : 8;  // Display Pointer Y
    u16 unused3 : 8;
    u16 JCA : 11; // Character Number
    u16 unused4 : 1;
    u16 JVFLP : 1; // Vertical Flip
    u16 JHFLP : 1; // Horizontal Flip
    u16 JPLTS : 2; // 	Palette Selector
} OAM;

// Object attributes
#define OBJ        ((OAM*)0x0003E000)
//0x00040000 - 0x0005DFFF	Unmapped
//0x0005E000 - 0x0005FFFF	I/O Registers (see list)
//0x00060000 - 0x00077FFF	Unmapped
//0x00078000 - 0x00079FFF	Mirror of character table 0
//0x0007A000 - 0x0007BFFF	Mirror of character table 1
//0x0007C000 - 0x0007DFFF	Mirror of character table 2
//0x0007E000 - 0x0007FFFF	Mirror of character table 3
//0x00080000 - 0x00FFFFFF	Mirroring of VIP memory map


//VIP io registers
//Interrupt Pending
#define INTPND      (*(vu16*)0x0005F800)
//Interrupt Enable
#define INTENB      (*(vu16*)0x0005F802)
//Interrupt Clear
#define INTCLR      (*(vu16*)0x0005F804)

typedef struct DPSTTS_ctrl {
    vu16 DPRST : 1; //When set, display functions are reset. When clear, no action occurs.
    vu16 DISP : 1; //When set, the display is enabled.
    vu16 L0BSY : 1; //Left frame buffer 0 is being displayed.
    vu16 R0BSY : 1; //Right frame buffer 0 is being displayed.
    vu16 L1BSY : 1; //Left frame buffer 1 is being displayed.
    vu16 R1BSY : 1; //Right frame buffer 1 is being displayed.
    vu16 SCANRDY : 1; //When set, the mirrors are stable.
    vu16 FCLK : 1; //The display frame clock signal is high.
    vu16 RE : 1; //When clear, memory refresh signals will not be issued on VIP memory.
    vu16 SYNCE : 1; //When clear, display sync signals are not sent to the display servo, preventing images from being displayed.
    vu16 LOCK : 1; //When set, CTA is prevented from updating.
    vu16 unused : 5;
} DPSTTS_ctrl;

typedef enum DPSTTS_enum {
    DPSTTS_DPRST = 1,
    DPSTTS_DISP = 2,
    DPSTTS_L0BSY = 4,
    DPSTTS_R0BSY = 8,
    DPSTTS_L1BSY = 0x10,
    DPSTTS_R1BSY = 0x20,
    DPSTTS_SCANRDY = 0x40,
    DPSTTS_FCLK = 0x80,
    DPSTTS_RE = 0x100,
    DPSTTS_SYNCE = 0x200,
    DPSTTS_LOCK = 0x400,
    DPSTTS_unused = 0x800,
} DPSTTS_enum;
//Display Control Read Register
#define DPSTTS      (*(vu16*)0x0005F820)
//Display Control Write Register
#define DPCTRL      (*(vu16*)0x0005F822)

//Brightness Control Register A
#define BRTA        (*(vu16*)0x0005F824)
//Brightness Control Register B
#define BRTB        (*(vu16*)0x0005F826)
//Brightness Control Register C
#define BRTC        (*(vu16*)0x0005F828)
//Rest Control Register
#define REST      (*(vu16*)0x0005F82A)
//Game Frame Control Register
#define FRMCYC      (*(vu16*)0x0005F82E)
//Column Table Read Start Address
#define CTA      (*(vu16*)0x0005F830)

typedef struct XPSTTS_ctrl {
    vu16 XPRST : 1; //When set, drawing functions are reset. When clear, no action occurs.
    vu16 XPEN : 1; //When set, drawing is enabled.
    vu16 F0BSY : 1; //Frame buffer 0 is being drawn to.
    vu16 F1BSY : 1; //Frame buffer 1 is being drawn to.
    vu16 OVERTIME : 1; //The drawing procedure has taken longer than the allotted time.
    vu16 unused : 3;
    vu16 SBCOUNT : 5; //The group of 8 rows of pixels, relative to the top of the image, to compare with while drawing.
    vu16 unused2 : 2;
    vu16 SBOUT : 1; //Set when a group of 8 rows of pixels begins to draw. (See below)
} XPSTTS_ctrl;

typedef enum XPSTTS_enum {
    XPSTTS_XPRST = 1,
    XPSTTS_XPEN = 2,
    XPSTTS_F0BSY = 4,
    XPSTTS_F1BSY = 8,
    XPSTTS_OVERTIME = 0x10,
    XPSTTS_unused = 0x20,
    XPSTTS_SBCOUNT = 0x100,
    XPSTTS_unused2 = 0x2000,
    XPSTTS_SBOUT = 0x8000,
} XPSTTS_enum;

//Drawing Control Read Register
#define XPSTTS      (*(vu16*)0x0005F840)
//Drawing Control Write Register
#define XPCTRL      (*(vu16*)0x0005F842)
//VIP Version Register
#define VER      (*(vu16*)0x0005F844)
//OBJ Control Register 0
#define SPT0      (*(vu16*)0x0005F848)
//OBJ Control Register 1
#define SPT1      (*(vu16*)0x0005F84A)
//OBJ Control Register 2
#define SPT2      (*(vu16*)0x0005F84C)
//OBJ Control Register 3
#define SPT3      (*(vu16*)0x0005F84E)
//BG Palette Control Register 0
#define GPLT0      (*(vu16*)0x0005F860)
//BG Palette Control Register 1
#define GPLT1      (*(vu16*)0x0005F862)
//BG Palette Control Register 2
#define GPLT2      (*(vu16*)0x0005F864)
//BG Palette Control Register 3
#define GPLT3      (*(vu16*)0x0005F866)
//OBJ Palette Control Register 0
#define JPLT0      (*(vu16*)0x0005F868)
//OBJ Palette Control Register 1
#define JPLT1      (*(vu16*)0x0005F86A)
//OBJ Palette Control Register 2
#define JPLT2      (*(vu16*)0x0005F86C)
//OBJ Palette Control Register 3
#define JPLT3      (*(vu16*)0x0005F86E)
//BG Color Palette Control Register
#define BKCOL      (*(vu16*)0x0005F870)

// Character table 0 Mirror
#define M_CTB0        ((u16*)0x00078000)
// Character table 1 Mirror
#define M_CTB1        ((u16*)0x0007A000)
// Character table 2 Mirror
#define M_CTB2        ((u16*)0x0007C000)
// Character table 3 Mirror
#define M_CTB3        ((u16*)0x0007E000)


#else

// Left frame buffer 0
#define LFB0        0x00000000
// Character table 0
#define CTB0        0x00006000
// Left frame buffer 1
#define LFB1        0x00008000
// Character table 1
#define CTB1        0x0000E000
// Right frame buffer 0
#define RFB0        0x00010000
// Character table 2
#define CTB2        0x00016000
// Right frame buffer 1
#define RFB1        0x00018000
// Character table 3
#define CTB3        0x0001E000
// Background maps and world parameters
#define MAPS        0x00020000
// World attributes
#define ATTR        0x0003D800
// Left column table
#define LCTB        0x0003DC00
// Right column table
#define RCTB        0x0003DE00
// Object attributes
#define OBJ        0x0003E000
//0x00040000 - 0x0005DFFF	Unmapped
//0x0005E000 - 0x0005FFFF	I/O Registers (see list)
//0x00060000 - 0x00077FFF	Unmapped
//0x00078000 - 0x00079FFF	Mirror of character table 0
//0x0007A000 - 0x0007BFFF	Mirror of character table 1
//0x0007C000 - 0x0007DFFF	Mirror of character table 2
//0x0007E000 - 0x0007FFFF	Mirror of character table 3
//0x00080000 - 0x00FFFFFF	Mirroring of VIP memory map


//VIP io registers
//Interrupt Pending
#define INTPND      0x0005F800
//Interrupt Enable
#define INTENB      0x0005F802
//Interrupt Clear
#define INTCLR      0x0005F804

#define DPSTTS_DPRST 1
#define DPSTTS_DISP 2
#define DPSTTS_L0BSY 4
#define DPSTTS_R0BSY 8
#define DPSTTS_L1BSY 0x10
#define DPSTTS_R1BSY 0x20
#define DPSTTS_SCANRDY 0x40
#define DPSTTS_FCLK 0x80
#define DPSTTS_RE 0x100
#define DPSTTS_SYNCE 0x200
#define DPSTTS_LOCK 0x400
#define DPSTTS_unused 0x800

//Display Control Read Register
#define DPSTTS      0x0005F820
//Display Control Write Register
#define DPCTRL      0x0005F822

//Brightness Control Register A
#define BRTA        0x0005F824
//Brightness Control Register B
#define BRTB        0x0005F826
//Brightness Control Register C
#define BRTC        0x0005F828
//Rest Control Register
#define REST      0x0005F82A
//Game Frame Control Register
#define FRMCYC      0x0005F82E
//Column Table Read Start Address
#define CTA      0x0005F830

#define XPSTTS_XPRST 1
#define XPSTTS_XPEN 2
#define XPSTTS_F0BSY 4
#define XPSTTS_F1BSY 8
#define XPSTTS_OVERTIME 0x10
#define XPSTTS_unused 0x20
#define XPSTTS_SBCOUNT 0x100
#define XPSTTS_unused2 0x2000
#define XPSTTS_SBOUT 0x8000

//Drawing Control Read Register
#define XPSTTS      0x0005F840
//Drawing Control Write Register
#define XPCTRL      0x0005F842
//VIP Version Register
#define VER      0x0005F844
//OBJ Control Register 0
#define SPT0      0x0005F848
//OBJ Control Register 1
#define SPT1      0x0005F84A
//OBJ Control Register 2
#define SPT2      0x0005F84C
//OBJ Control Register 3
#define SPT3      0x0005F84E
//BG Palette Control Register 0
#define GPLT0      0x0005F860
//BG Palette Control Register 1
#define GPLT1      0x0005F862
//BG Palette Control Register 2
#define GPLT2      0x0005F864
//BG Palette Control Register 3
#define GPLT3      0x0005F866
//OBJ Palette Control Register 0
#define JPLT0      0x0005F868
//OBJ Palette Control Register 1
#define JPLT1      0x0005F86A
//OBJ Palette Control Register 2
#define JPLT2      0x0005F86C
//OBJ Palette Control Register 3
#define JPLT3      0x0005F86E
//BG Color Palette Control Register
#define BKCOL      0x0005F870

// Character table 0 Mirror
#define M_CTB0        0x00078000
// Character table 1 Mirror
#define M_CTB1        0x0007A000
// Character table 2 Mirror
#define M_CTB2        0x0007C000
// Character table 3 Mirror
#define M_CTB3        0x0007E000


#endif



#endif