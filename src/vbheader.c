#include "types.h"

typedef struct HEADER {
    char title[20];
    u8 reserved[5];
    char maker_code[2];
    char game_code[4];
    u8 version;
} HEADER;

__attribute__((section(".vbheader"), used))
HEADER game_header = {
    "VIRTUAL BOY TEST GAM",
    {0,0,0,0,0},
    "11",
    "HAHA",
    0
};