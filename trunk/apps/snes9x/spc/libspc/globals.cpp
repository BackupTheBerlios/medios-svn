/*
 * Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.
 *
 * (c) Copyright 1996 - 2000 Gary Henderson (gary@daniver.demon.co.uk) and
 *                           Jerremy Koot (jkoot@snes9x.com)
 *
 * Super FX C emulator code 
 * (c) Copyright 1997 - 1999 Ivar (Ivar@snes9x.com) and
 *                           Gary Henderson.
 * Super FX assembler emulator code (c) Copyright 1998 zsKnight and _Demo_.
 *
 * DSP1 emulator code (c) Copyright 1998 Ivar, _Demo_ and Gary Henderson.
 * DOS port code contains the works of other authors. See headers in
 * individual files.
 *
 * Snes9x homepage: www.snes9x.com
 *
 * Permission to use, copy, modify and distribute Snes9x in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Snes9x is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for Snes9x or software derived from Snes9x.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 *
 * Super NES and Super Nintendo Entertainment System are trademarks of
 * Nintendo Co., Limited and its subsidiary companies.
 */

#include <sys_def/section_types.h>

#include "snes9x.h"
#include "memmap.h"
// #include "ppu.h"
// #include "dsp1.h"
// #include "missing.h"
// #include "cpuexec.h"
// #include "debug.h"
#include "apu.h"
// #include "dma.h"
// #include "fxemu.h"
// #include "gfx.h"
#include "soundux.h"
// #include "cheats.h"
// #include "sa1.h"

START_EXTERN_C
char String[513] = {0};

// struct Missing missing = {0};

// struct SICPU ICPU = {
//     0
// };

// struct SCPUState CPU = {
//     0
// };

// struct SRegisters Registers = {
//     0
// };

__IRAM_DATA struct SAPU APU = {
    0
};

__IRAM_DATA struct SIAPU IAPU = {
    0
};

__IRAM_DATA struct SAPURegisters APURegisters = {
    0
};

__IRAM_DATA struct SSettings Settings = {
    0
};

// struct SDSP1 DSP1 = {
//     0
// };

// struct SSA1Registers SA1Registers = {
//     0
// };

// struct SSA1 SA1 = {
//     0
// };

// uint8 *SRAM = NULL;
// uint8 *ROM = NULL;
// uint8 *RegRAM = NULL;

__IRAM_DATA long OpAddress = 0;

// CMemory Memory = {0};

__IRAM_DATA uint8 A1 = 0, A2 = 0, A3 = 0, A4 = 0, W1 = 0, W2 = 0, W3 = 0, W4 = 0;
__IRAM_DATA uint8 Ans8 = 0;
__IRAM_DATA uint16 Ans16 = 0;
__IRAM_DATA uint32 Ans32 = 0;
__IRAM_DATA uint8 Work8 = 0;
__IRAM_DATA uint16 Work16 = 0;
__IRAM_DATA uint32 Work32 = 0;
__IRAM_DATA signed char Int8 = 0;
__IRAM_DATA short Int16 = 0;
__IRAM_DATA long Int32 = 0;

END_EXTERN_C

// #ifndef ZSNES_FX
// struct FxInit_s SuperFX = {0};
// #else
// EXTERN_C uint8 *SFXPlotTable = NULL;
// #endif

// struct SPPU PPU = {0};
// struct InternalPPU IPPU = {0};

// struct SDMA DMA[8] = {0};

// uint8 *HDMAMemPointers [8] = { NULL };
// uint8 *HDMABasePointers [8] = { NULL };

// struct SBG BG = {0};

// struct SGFX GFX = {0};
// struct SLineData LineData[240] = { {0} };
// struct SLineMatrixData LineMatrixData [240] = { {0} };

// uint32 StartY = 0;
// uint32 EndY = 223;
// struct ClipData *pCurrentClip = NULL;
// uint32 Mode7Mask = 255;

// NormalTileRenderer DrawTilePtr = NULL;
// ClippedTileRenderer DrawClippedTilePtr = NULL;
// NormalTileRenderer DrawHiResTilePtr = NULL;
// ClippedTileRenderer DrawHiResClippedTilePtr = NULL;
// LargePixelRenderer DrawLargePixelPtr = NULL;
// uint32 PixSize = 1;

// int OBJList [129] = {0};
// uint32 Sizes [129] = {0};
// int VPositions [129] = {0};

// uint32 odd_high[4][16] = { {0} };
// uint32 odd_low[4][16] = { {0} };
// uint32 even_high[4][16] = { {0} };
// uint32 even_low[4][16] = { {0} };

// #ifdef GFX_MULTI_FORMAT

// uint32 RED_LOW_BIT_MASK = RED_LOW_BIT_MASK_RGB565;
// uint32 GREEN_LOW_BIT_MASK = GREEN_LOW_BIT_MASK_RGB565;
// uint32 BLUE_LOW_BIT_MASK = BLUE_LOW_BIT_MASK_RGB565;
// uint32 RED_HI_BIT_MASK = RED_HI_BIT_MASK_RGB565;
// uint32 GREEN_HI_BIT_MASK = GREEN_HI_BIT_MASK_RGB565;
// uint32 BLUE_HI_BIT_MASK = BLUE_HI_BIT_MASK_RGB565;
// uint32 MAX_RED = MAX_RED_RGB565;
// uint32 MAX_GREEN = MAX_GREEN_RGB565;
// uint32 MAX_BLUE = MAX_BLUE_RGB565;
// uint32 SPARE_RGB_BIT_MASK = SPARE_RGB_BIT_MASK_RGB565;
// uint32 GREEN_HI_BIT = (MAX_GREEN_RGB565 + 1) >> 1;
// uint32 RGB_LOW_BITS_MASK = (RED_LOW_BIT_MASK_RGB565 | 
// 			    GREEN_LOW_BIT_MASK_RGB565 |
// 			    BLUE_LOW_BIT_MASK_RGB565);
// uint32 RGB_HI_BITS_MASK = (RED_HI_BIT_MASK_RGB565 |
// 			   GREEN_HI_BIT_MASK_RGB565 |
// 			   BLUE_HI_BIT_MASK_RGB565);
// uint32 RGB_HI_BITS_MASKx2 = (RED_HI_BIT_MASK_RGB565 |
// 			     GREEN_HI_BIT_MASK_RGB565 |
// 			     BLUE_HI_BIT_MASK_RGB565) << 1;
// uint32 RGB_REMOVE_LOW_BITS_MASK = ~RGB_LOW_BITS_MASK;

// uint32 current_graphic_format = RGB565;
// #endif

// uint8 GetBank = 0;
// struct SCheatData Cheat;

__IRAM_DATA volatile SoundStatus so = {0};
__IRAM_DATA SSoundData SoundData = {0};
int Echo [24000] = {0};
__IRAM_DATA int DummyEchoBuffer [SOUND_BUFFER_SIZE] = {0};
__IRAM_DATA int EchoBuffer [SOUND_BUFFER_SIZE] = {0};
__IRAM_DATA int MixBuffer [SOUND_BUFFER_SIZE] = {0};
__IRAM_DATA int FilterTaps [8] = {0};
__IRAM_DATA unsigned long Z = 0;
__IRAM_DATA int Loop [16] = {0};

// uint16 SignExtend [2] = {
//     0x00, 0xff00
// };

// int HDMA_ModeByteCounts [8] = {
//     1, 2, 2, 4, 4, 0, 0, 0
// };

// uint8 BitShifts[8][4] =
// {
//     {2, 2, 2, 2},	// 0
//     {4, 4, 2, 0},	// 1
//     {4, 4, 0, 0},	// 2
//     {8, 4, 0, 0},	// 3
//     {8, 2, 0, 0},	// 4
//     {4, 2, 0, 0},	// 5
//     {4, 0, 0, 0},	// 6
//     {8, 0, 0, 0}	// 7
// };
// uint8 TileShifts[8][4] =
// {
//     {4, 4, 4, 4},	// 0
//     {5, 5, 4, 0},	// 1
//     {5, 5, 0, 0},	// 2
//     {6, 5, 0, 0},	// 3
//     {6, 4, 0, 0},	// 4
//     {5, 4, 0, 0},	// 5
//     {5, 0, 0, 0},	// 6
//     {6, 0, 0, 0}	// 7
// };
// uint8 PaletteShifts[8][4] =
// {
//     {2, 2, 2, 2},	// 0
//     {4, 4, 2, 0},	// 1
//     {4, 4, 0, 0},	// 2
//     {0, 4, 0, 0},	// 3
//     {0, 2, 0, 0},	// 4
//     {4, 2, 0, 0},	// 5
//     {4, 0, 0, 0},	// 6
//     {0, 0, 0, 0}	// 7
// };
// uint8 PaletteMasks[8][4] =
// {
//     {7, 7, 7, 7},	// 0
//     {7, 7, 7, 0},	// 1
//     {7, 7, 0, 0},	// 2
//     {0, 7, 0, 0},	// 3
//     {0, 7, 0, 0},	// 4
//     {7, 7, 0, 0},	// 5
//     {7, 0, 0, 0},	// 6
//     {0, 0, 0, 0}	// 7
// };
// uint8 Depths[8][4] =
// {
//     {TILE_2BIT, TILE_2BIT, TILE_2BIT, TILE_2BIT}, // 0
//     {TILE_4BIT, TILE_4BIT, TILE_2BIT, 0},         // 1
//     {TILE_4BIT, TILE_4BIT, 0, 0},                 // 2
//     {TILE_8BIT, TILE_4BIT, 0, 0},                 // 3
//     {TILE_8BIT, TILE_2BIT, 0, 0},                 // 4
//     {TILE_4BIT, TILE_2BIT, 0, 0},                 // 5
//     {TILE_8BIT, 0, 0, 0},                         // 6
//     {0, 0, 0, 0}                                  // 7
// };
// uint8 BGSizes [2] = {
//     8, 16
// };
// uint16 DirectColourMaps [8][256] = { 0 };

__IRAM_DATA long FilterValues[4][2] =
{
    {0, 0},
    {240, 0},
    {488, -240},
    {460, -208}
};

__IRAM_DATA int NoiseFreq [32] = {
    0, 16, 21, 25, 31, 42, 50, 63, 84, 100, 125, 167, 200, 250, 333,
    400, 500, 667, 800, 1000, 1300, 1600, 2000, 2700, 3200, 4000,
    5300, 6400, 8000, 10700, 16000, 32000
};

__IRAM_DATA uint32 HeadMask [4] = {
#ifdef LSB_FIRST
    0xffffffff, 0xffffff00, 0xffff0000, 0xff000000
#else
    0xffffffff, 0x00ffffff, 0x0000ffff, 0x000000ff
#endif
};

__IRAM_DATA uint32 TailMask [5] = {
#ifdef LSB_FIRST
    0x00000000, 0x000000ff, 0x0000ffff, 0x00ffffff, 0xffffffff
#else
    0x00000000, 0xff000000, 0xffff0000, 0xffffff00, 0xffffffff
#endif
};

START_EXTERN_C
uint8 APUROM [64] =
{
    0xCD,0xEF,0xBD,0xE8,0x00,0xC6,0x1D,0xD0,0xFC,0x8F,0xAA,0xF4,0x8F,
    0xBB,0xF5,0x78,0xCC,0xF4,0xD0,0xFB,0x2F,0x19,0xEB,0xF4,0xD0,0xFC,
    0x7E,0xF4,0xD0,0x0B,0xE4,0xF5,0xCB,0xF4,0xD7,0x00,0xFC,0xD0,0xF3,
    0xAB,0x01,0x10,0xEF,0x7E,0xF4,0x10,0xEB,0xBA,0xF6,0xDA,0x00,0xBA,
    0xF4,0xC4,0xF4,0xDD,0x5D,0xD0,0xDB,0x1F,0x00,0x00,0xC0,0xFF
};


// Raw SPC700 instruction cycle lengths
__IRAM_DATA int32 S9xAPUCycleLengths [256] = 
{
    /*        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f, */
    /* 00 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 5, 4, 5, 4, 6, 8, 
    /* 10 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 6, 5, 2, 2, 4, 6, 
    /* 20 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 5, 4, 5, 4, 5, 4, 
    /* 30 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 6, 5, 2, 2, 3, 8, 
    /* 40 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 4, 4, 5, 4, 6, 6, 
    /* 50 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 4, 5, 2, 2, 4, 3, 
    /* 60 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 4, 4, 5, 4, 5, 5, 
    /* 70 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 5, 5, 2, 2, 3, 6, 
    /* 80 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 5, 4, 5, 2, 4, 5, 
    /* 90 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 5, 5, 2, 2,12, 5, 
    /* a0 */  3, 8, 4, 5, 3, 4, 3, 6, 2, 6, 4, 4, 5, 2, 4, 4, 
    /* b0 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 5, 5, 2, 2, 3, 4, 
    /* c0 */  3, 8, 4, 5, 4, 5, 4, 7, 2, 5, 6, 4, 5, 2, 4, 9, 
    /* d0 */  2, 8, 4, 5, 5, 6, 6, 7, 4, 5, 4, 5, 2, 2, 6, 3, 
    /* e0 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 4, 5, 3, 4, 3, 4, 3, 
    /* f0 */  2, 8, 4, 5, 4, 5, 5, 6, 3, 4, 5, 4, 2, 2, 4, 3
};

// Actual data used by CPU emulation, will be scaled by APUReset routine
// to be relative to the 65c816 instruction lengths.
int32 S9xAPUCycles [256] =
{
    /*        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f, */
    /* 00 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 5, 4, 5, 4, 6, 8, 
    /* 10 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 6, 5, 2, 2, 4, 6, 
    /* 20 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 5, 4, 5, 4, 5, 4, 
    /* 30 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 6, 5, 2, 2, 3, 8, 
    /* 40 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 4, 4, 5, 4, 6, 6, 
    /* 50 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 4, 5, 2, 2, 4, 3, 
    /* 60 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 4, 4, 5, 4, 5, 5, 
    /* 70 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 5, 5, 2, 2, 3, 6, 
    /* 80 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 6, 5, 4, 5, 2, 4, 5, 
    /* 90 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 5, 5, 2, 2,12, 5, 
    /* a0 */  3, 8, 4, 5, 3, 4, 3, 6, 2, 6, 4, 4, 5, 2, 4, 4, 
    /* b0 */  2, 8, 4, 5, 4, 5, 5, 6, 5, 5, 5, 5, 2, 2, 3, 4, 
    /* c0 */  3, 8, 4, 5, 4, 5, 4, 7, 2, 5, 6, 4, 5, 2, 4, 9, 
    /* d0 */  2, 8, 4, 5, 5, 6, 6, 7, 4, 5, 4, 5, 2, 2, 6, 3, 
    /* e0 */  2, 8, 4, 5, 3, 4, 3, 6, 2, 4, 5, 3, 4, 3, 4, 3, 
    /* f0 */  2, 8, 4, 5, 4, 5, 5, 6, 3, 4, 5, 4, 2, 2, 4, 3
};

#ifndef VAR_CYCLES
uint8 S9xE1M1X1 [256] = {
	8, 6, 8, 4, 5, 3, 5, 6, 3, 2, 2, 4, 6, 4, 6, 5,		/* e=1, m=1, x=1 */
	2, 5, 5, 7, 5, 4, 6, 6, 2, 4, 2, 2, 6, 4, 7, 5,
	6, 6, 8, 4, 3, 3, 5, 6, 4, 2, 2, 5, 4, 4, 6, 5,
	2, 5, 5, 7, 4, 4, 6, 6, 2, 4, 2, 2, 4, 4, 7, 5,
	7, 6, 2, 4, 0, 3, 5, 6, 3, 2, 2, 3, 3, 4, 6, 5,
	2, 5, 5, 7, 0, 4, 6, 6, 2, 4, 3, 2, 4, 4, 7, 5,
	6, 6, 6, 4, 3, 3, 5, 6, 4, 2, 2, 6, 5, 4, 6, 5,
	2, 5, 5, 7, 4, 4, 6, 6, 2, 4, 4, 2, 6, 4, 7, 5,
	2, 6, 3, 4, 3, 3, 3, 6, 2, 2, 2, 3, 4, 4, 4, 5,
	2, 5, 5, 7, 4, 4, 4, 6, 2, 4, 2, 2, 4, 4, 4, 5,
	2, 6, 2, 4, 3, 3, 3, 6, 2, 2, 2, 4, 4, 4, 4, 5,
	2, 5, 5, 7, 4, 4, 4, 6, 2, 4, 2, 2, 4, 4, 4, 5,
	2, 6, 3, 4, 3, 3, 5, 6, 2, 2, 2, 3, 4, 4, 6, 5,
	2, 5, 5, 7, 6, 4, 6, 6, 2, 4, 3, 3, 6, 4, 7, 5,
	2, 6, 3, 4, 3, 3, 5, 6, 2, 2, 2, 3, 4, 4, 6, 5,
	2, 5, 5, 7, 5, 4, 6, 6, 2, 4, 4, 2, 6, 4, 7, 5
};

uint8 S9xE0M1X1 [256] = {
	8, 6, 8, 4, 5, 3, 5, 6, 3, 2, 2, 4, 6, 4, 6, 5,		/* e=0, m=1, x=1 */
	2, 5, 5, 7, 5, 4, 6, 6, 2, 4, 2, 2, 6, 4, 7, 5,
	6, 6, 8, 4, 3, 3, 5, 6, 4, 2, 2, 5, 4, 4, 6, 5,
	2, 5, 5, 7, 4, 4, 6, 6, 2, 4, 2, 2, 4, 4, 7, 5,
	7, 6, 2, 4, 0, 3, 5, 6, 3, 2, 2, 3, 3, 4, 6, 5,
	2, 5, 5, 7, 0, 4, 6, 6, 2, 4, 3, 2, 4, 4, 7, 5,
	6, 6, 6, 4, 3, 3, 5, 6, 4, 2, 2, 6, 5, 4, 6, 5,
	2, 5, 5, 7, 4, 4, 6, 6, 2, 4, 4, 2, 6, 4, 7, 5,
	2, 6, 3, 4, 3, 3, 3, 6, 2, 2, 2, 3, 4, 4, 4, 5,
	2, 5, 5, 7, 4, 4, 4, 6, 2, 4, 2, 2, 4, 4, 4, 5,
	2, 6, 2, 4, 3, 3, 3, 6, 2, 2, 2, 4, 4, 4, 4, 5,
	2, 5, 5, 7, 4, 4, 4, 6, 2, 4, 2, 2, 4, 4, 4, 5,
	2, 6, 3, 4, 3, 3, 5, 6, 2, 2, 2, 3, 4, 4, 6, 5,
	2, 5, 5, 7, 6, 4, 6, 6, 2, 4, 3, 3, 6, 4, 7, 5,
	2, 6, 3, 4, 3, 3, 5, 6, 2, 2, 2, 3, 4, 4, 6, 5,
	2, 5, 5, 7, 5, 4, 6, 6, 2, 4, 4, 2, 6, 4, 7, 5
};

uint8 S9xE0M0X1 [256] = {
	8, 7, 8, 5, 7, 4, 7, 7, 3, 3, 2, 4, 8, 5, 8, 6,		/* e=0, m=0, x=1 */
	2, 6, 6, 8, 7, 5, 8, 7, 2, 5, 2, 2, 8, 5, 9, 6,
	6, 7, 8, 5, 4, 4, 7, 7, 4, 3, 2, 5, 5, 5, 8, 6,
	2, 6, 6, 8, 5, 5, 8, 7, 2, 5, 2, 2, 5, 5, 9, 6,
	7, 7, 2, 5, 0, 4, 7, 7, 4, 3, 2, 3, 3, 5, 8, 6,
	2, 6, 6, 8, 0, 5, 8, 7, 2, 5, 3, 2, 4, 5, 9, 6,
	6, 7, 6, 5, 4, 4, 7, 7, 5, 3, 2, 6, 5, 5, 8, 6,
	2, 6, 6, 8, 5, 5, 8, 7, 2, 5, 4, 2, 6, 5, 9, 6,
	2, 7, 3, 5, 3, 4, 3, 7, 2, 3, 2, 3, 4, 5, 4, 6,
	2, 6, 6, 8, 4, 5, 4, 7, 2, 5, 2, 2, 5, 5, 5, 6,
	2, 7, 2, 5, 3, 4, 3, 7, 2, 3, 2, 4, 4, 5, 4, 6,
	2, 6, 6, 8, 4, 5, 4, 7, 2, 5, 2, 2, 4, 5, 4, 6,
	2, 7, 3, 5, 3, 4, 7, 7, 2, 3, 2, 3, 4, 5, 8, 6,
	2, 6, 6, 8, 6, 5, 8, 7, 2, 5, 3, 3, 6, 5, 9, 6,
	2, 7, 3, 5, 3, 4, 7, 7, 2, 3, 2, 3, 4, 5, 8, 6,
	2, 6, 6, 8, 5, 5, 8, 7, 2, 5, 4, 2, 6, 5, 9, 6
};

uint8 S9xE0M1X0 [256] = {
	8, 6, 8, 4, 5, 3, 5, 6, 3, 2, 2, 4, 6, 4, 6, 5,		/* e=0, m=1, x=0 */
	2, 6, 5, 7, 5, 4, 6, 6, 2, 5, 2, 2, 6, 5, 7, 5,
	6, 6, 8, 4, 3, 3, 5, 6, 4, 2, 2, 5, 4, 4, 6, 5,
	2, 6, 5, 7, 4, 4, 6, 6, 2, 5, 2, 2, 5, 5, 7, 5,
	7, 6, 2, 4, 0, 3, 5, 6, 4, 2, 2, 3, 3, 4, 6, 5,
	2, 6, 5, 7, 0, 4, 6, 6, 2, 5, 4, 2, 4, 5, 7, 5,
	6, 6, 6, 4, 3, 3, 5, 6, 5, 2, 2, 6, 5, 4, 6, 5,
	2, 6, 5, 7, 4, 4, 6, 6, 2, 5, 5, 2, 6, 5, 7, 5,
	2, 6, 3, 4, 4, 3, 4, 6, 2, 2, 2, 3, 5, 4, 5, 5,
	2, 6, 5, 7, 5, 4, 5, 6, 2, 5, 2, 2, 4, 5, 5, 5,
	3, 6, 3, 4, 4, 3, 4, 6, 2, 2, 2, 4, 5, 4, 5, 5,
	2, 6, 5, 7, 5, 4, 5, 6, 2, 5, 2, 2, 5, 5, 5, 5,
	3, 6, 3, 4, 4, 3, 6, 6, 2, 2, 2, 3, 5, 4, 6, 5,
	2, 6, 5, 7, 6, 4, 8, 6, 2, 5, 4, 3, 6, 5, 7, 5,
	3, 6, 3, 4, 4, 3, 6, 6, 2, 2, 2, 3, 5, 4, 6, 5,
	2, 6, 5, 7, 5, 4, 8, 6, 2, 5, 5, 2, 6, 5, 7, 5
};

uint8 S9xE0M0X0 [256] = {
	8, 7, 8, 5, 7, 4, 7, 7, 3, 3, 2, 4, 8, 5, 8, 6,		/* e=0, m=0, x=0 */
	2, 7, 6, 8, 7, 5, 8, 7, 2, 6, 2, 2, 8, 6, 9, 6,
	6, 7, 8, 5, 4, 4, 7, 7, 4, 3, 2, 5, 5, 5, 8, 6,
	2, 7, 6, 8, 5, 5, 8, 7, 2, 6, 2, 2, 6, 6, 9, 6,
	7, 7, 2, 5, 0, 4, 7, 7, 3, 3, 2, 3, 3, 5, 8, 6,
	2, 7, 6, 8, 0, 5, 8, 7, 2, 6, 4, 2, 4, 6, 9, 6,
	6, 7, 6, 5, 4, 4, 7, 7, 4, 3, 2, 6, 5, 5, 8, 6,
	2, 7, 6, 8, 5, 5, 8, 7, 2, 6, 5, 2, 6, 6, 9, 6,
	2, 7, 3, 5, 4, 4, 4, 7, 2, 3, 2, 3, 5, 5, 5, 6,
	2, 7, 6, 8, 5, 5, 5, 7, 2, 6, 2, 2, 5, 6, 6, 6,
	3, 7, 3, 5, 4, 4, 4, 7, 2, 3, 2, 4, 5, 5, 5, 6,
	2, 7, 6, 8, 5, 5, 5, 7, 2, 6, 2, 2, 5, 6, 5, 6,
	3, 7, 3, 5, 4, 4, 7, 7, 2, 3, 2, 3, 5, 5, 8, 6,
	2, 7, 6, 8, 6, 5, 8, 7, 2, 6, 4, 3, 6, 6, 9, 6,
	3, 7, 3, 5, 4, 4, 7, 7, 2, 3, 2, 3, 5, 5, 8, 6,
	2, 7, 6, 8, 5, 5, 8, 7, 2, 6, 5, 2, 6, 6, 9, 6
};
#endif

END_EXTERN_C
