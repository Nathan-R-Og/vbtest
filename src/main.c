#include "types.h"
#include "vip.h"
#include "misc.h"

extern u16 my_tiles[];

s16 keyread();
s16 key_input;

int main(void) {
	u16 i;
    //Set LED brightness levels
    BRTA = 32;
    BRTB = 64;
	//c == brta+brtb+brtc
	//basically, BRTC = 32+64+32 = 128
    BRTC = 32;

	//Set all eight palettes to: 11, 10, 01, 00
	//dark to light
	GPLT0 = 0xE4;
	GPLT1 = 0xE4;
	GPLT2 = 0xE4;
	GPLT3 = 0xE4;
	JPLT0 = 0xE4;
	JPLT1 = 0xE4;
	JPLT2 = 0xE4;
	JPLT3 = 0xE4;

    //reset display functions
    DPCTRL = DPSTTS_DPRST;
	//reset drawing functions
	XPCTRL = XPSTTS_XPRST;

	//draw tiles to character ram
    for (i = 0; i < 8; i++) {
        CTB0[i] = my_tiles[i];
    }

	//make funny object
	OBJ[0].JX = 188;
	OBJ[0].JY = 108;
	OBJ[0].JP = 0;
	OBJ[0].JRON = TRUE;
	OBJ[0].JLON = TRUE;
	OBJ[0].JCA = 0;

	//make world
	ATTR[31].LON = TRUE;
	ATTR[31].RON = TRUE;
	ATTR[31].BGM = 3;
	//end point
	ATTR[30].END = TRUE;

	// Set the first SPT pointer (SPT3) to point to the first 12 Objects
	SPT3 = 0;
	SPT2 = -1;
	SPT1 = -1;
	SPT0 = -1;

	//do diplsay
    DPCTRL = DPSTTS | DPSTTS_DISP | DPSTTS_SYNCE;
	//do drawing
	XPCTRL = XPSTTS | XPSTTS_XPEN;

	f32 float_test_x = OBJ[0].JX;
	f32 float_test_y = OBJ[0].JY;
	#define SPEED 0.030f
	//main loop
    while (1) {
		key_input = keyread();
		if (key_input & SDR_RR){
			float_test_x += SPEED;
		}
		if (key_input & SDR_RL){
			float_test_x -= SPEED;
		}
		if (key_input & SDR_RD){
			float_test_y += SPEED;
		}
		if (key_input & SDR_RU){
			float_test_y -= SPEED;
		}
		OBJ[0].JX = float_test_x;
		OBJ[0].JY = float_test_y;
    }

    return 0;
}

void vip_int(void) {

}


s16 keyread(void) {
	s16 input;

	//wait for input parsing to finish
	while(SRC & SCR_SI_Stat) {}

	//grab input
	input = ((SDHR & 0xff) << 8) | (SDLR & 0xff);

	//acknowledge
	SRC = SCR_K_Int_Inh | SCR_HW_SI;

	return input;
}