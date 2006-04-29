/*
*   include/api.h
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#ifndef __API_H
#define __API_H

/* include needed by api fct */
#include <kernel/errors.h>
#include <sys_def/time.h>
#include <evt.h>
#include <buttons.h>
#include <sys_def/stdfs.h>
#include <sys_def/stdfs.h>
#include <sys_def/graphics.h>

/* init fct needed to get the others functions */
void ini_api(void);

/* api fct ptr declaration */
void* (*do_malloc)(long size, int user_flag);
void* (*do_realloc)(void *buffer, long newsize, int user_flag);
void (*free)(void *buf);
unsigned int (*tmr_getTick)(void);
MED_RET_T (*rtc_getTime)(struct med_tm * valTime);
MED_RET_T (*rtc_setTime)(struct med_tm * newTime);
void (*udelay)(unsigned long usecs);
void (*mdelay)(unsigned long msecs);
void (*set_timer_status)(int timer_type, int power_mode, int status);
void (*set_timer_delay)(int timer_type, int power_mode, int delay);
int (*get_timer_status)(int timer_type, int power_mode);
int (*get_timer_delay)(int timer_type, int power_mode);
int (*DC_isConnected)(void);
int (*batLevel)(void);
void (*lcd_setBrightness)(int val);
int (*lcd_getBrightness)(void);
int (*usb_isConnected)(void);
int (*FW_isConnected)(void);
int (*evt_getHandler)(unsigned int mask);
MED_RET_T (*evt_freeHandler)(int num_evt_pipe);
int (*evt_getStatus)(int num_evt_pipe);
MED_RET_T (*evt_getFullStatus)(int num_evt_pipe, struct evt_t * evt);
int (*btn_readState)(void);
void (*halt_device)(void);
void (*reload_firmware)(void);
void (*printf)(char *fmt, ...);
void (*do_bkpt)(void);
int (*getArch)(void);
void (*getResolution)(int * width,int * height);
long (*float_modsi3)(long a, long b);
long (*float_umodsi3)(long a, long b);
long (*float_divsi3)(long a, long b);
long (*float_udivsi3)(long a, long b);
unsigned int (*float_divdi3)(unsigned int a, unsigned int b);
int (*open)(const char* pathname, int flags);
int (*close)(int fdesc);
int (*fsync)(int fdesc);
int (*read)(int fdesc, void *buf, int count);
int (*lseek)(int fdesc, int offset, int whence);
int (*write)(int fdesc, const void *buf, int count);
int (*truncate)(int fdesc, int length);
int (*filesize)(int fdesc);
int (*ftell)(int fdesc);
DIR* (*opendir)(const char* name);
int (*closedir)(DIR* dir);
struct dirent* (*readdir)(DIR* dir);
int (*mkdir)(const char *name, int mode);
void (*gfx_openGraphics)(void);
void (*gfx_closeGraphics)(void);
void (*gfx_setPlane)(int vplane);
int (*gfx_getPlane)(void);
void (*gfx_planeHide)(int vplane);
void (*gfx_planeShow)(int vplane);
int (*gfx_planeIsShown)(int vplane);
void (*gfx_planeSetState)(int vplane,int state);
int (*gfx_planeGetState)(int vplane);
void (*gfx_planeSetSize)(int vplane,int width,int height,int bitsPerPixel);
void (*gfx_planeGetSize)(int vplane,int * width,int * height,int * bitsPerPixel);
void (*gfx_planeSetPos)(int vplane,int x,int y);
void (*gfx_planeGetPos)(int vplane,int * x,int * y);
void* (*gfx_planeGetBufferOffset)(int vplane);
void (*gfx_planeSetBufferOffset)(int vplane, void * offset);
void (*gfx_clearScreen)(unsigned int color);
void (*gfx_drawPixel)(unsigned int color,int x, int y);
unsigned int (*gfx_readPixel)(int x, int y);
void (*gfx_drawRect)(unsigned int color, int x, int y, int width, int height);
void (*gfx_fillRect)(unsigned int color, int x, int y, int width, int height);
void (*gfx_drawLine)(unsigned int color, int x1, int y1, int x2, int y2);
void (*gfx_putS)(unsigned int color, unsigned int bg_color, int x, int y, unsigned char *s);
void (*gfx_getStringSize)(unsigned char *str, int *w, int *h);
void (*gfx_putC)(unsigned int color, unsigned int bg_color, int x, int y, unsigned char s);
void (*gfx_drawSprite)(unsigned int * palette, SPRITE * sprite, int x, int y);
void (*gfx_drawBitmap)(BITMAP * bitmap, int x, int y);
void (*gfx_scrollWindowVert)(unsigned int bgColor, int x, int y, int width, int height, int scroll, int UP);
void (*gfx_scrollWindowHoriz)(unsigned int bgColor, int x, int y, int width, int height, int scroll, int RIGHT);
void (*gfx_setPalletteRGB)(int r, int g, int b, int index);
void (*gfx_fontSet)(int font_nb);
int (*gfx_fontGet)(void);

#endif
