/*
*   kernel/lib/api.c
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#include <api.h>
#include <kernel/swi.h>
#include <kernel/errors.h>

#define swi_call(SWI_NUM)                \
    ({                                   \
        register long _r0 asm("r0");     \
        asm volatile(                    \
            "stmdb sp!, {r3-r5} \n"     \
            "swi %0\n"                   \
            "ldmia sp!, {r3-r5}"        \
        :                                \
        : "i"(SWI_NUM)                   \
        : "memory");                     \
        return (long) _r0;               \
    })    

unsigned int api_getFctPtr(char * name)    { swi_call(nAPI_INIAPI); }

long __modsi3(long a, long b)  { return float_modsi3(a,b);}
long __umodsi3(long a, long b) { return float_umodsi3(a,b);}
long __divsi3(long a, long b)  { return float_divsi3(a,b);}
long __udivsi3(long a, long b) { return float_udivsi3(a,b);}
unsigned int __divdi3(unsigned int a, unsigned int b) { return float_divdi3(a,b);}

void * malloc(unsigned int size) { return do_malloc(size,1); }
void * realloc(void *buffer, unsigned int newsize) { return do_realloc(buffer,newsize,1); }

void ini_api(void)
{
    do_malloc=(void*(*)(long size, int user_flag))api_getFctPtr("do_malloc");
    do_realloc=(void*(*)(void *buffer, long newsize, int user_flag))api_getFctPtr("do_realloc");
    free=(void(*)(void *buf))api_getFctPtr("free");
    tmr_getTick=(unsigned int(*)(void))api_getFctPtr("tmr_getTick");
    rtc_getTime=(MED_RET_T(*)(struct med_tm * valTime))api_getFctPtr("rtc_getTime");
    rtc_setTime=(MED_RET_T(*)(struct med_tm * newTime))api_getFctPtr("rtc_setTime");
    udelay=(void(*)(unsigned long usecs))api_getFctPtr("udelay");
    mdelay=(void(*)(unsigned long msecs))api_getFctPtr("mdelay");
    set_timer_status=(void(*)(int timer_type, int power_mode, int status))api_getFctPtr("set_timer_status");
    set_timer_delay=(void(*)(int timer_type, int power_mode, int delay))api_getFctPtr("set_timer_delay");
    get_timer_status=(int(*)(int timer_type, int power_mode))api_getFctPtr("get_timer_status");
    get_timer_delay=(int(*)(int timer_type, int power_mode))api_getFctPtr("get_timer_delay");
    DC_isConnected=(int(*)(void))api_getFctPtr("DC_isConnected");
    batLevel=(int(*)(void))api_getFctPtr("batLevel");
    lcd_setBrightness=(void(*)(int val))api_getFctPtr("lcd_setBrightness");
    lcd_getBrightness=(int(*)(void))api_getFctPtr("lcd_getBrightness");
    usb_isConnected=(int(*)(void))api_getFctPtr("usb_isConnected");
    FW_isConnected=(int(*)(void))api_getFctPtr("FW_isConnected");
    evt_getHandler=(int(*)(unsigned int mask))api_getFctPtr("evt_getHandler");
    evt_freeHandler=(MED_RET_T(*)(int num_evt_pipe))api_getFctPtr("evt_freeHandler");
    evt_getStatus=(int(*)(int num_evt_pipe))api_getFctPtr("evt_getStatus");
    evt_getFullStatus=(MED_RET_T(*)(int num_evt_pipe, struct evt_t * evt))api_getFctPtr("evt_getFullStatus");
    btn_readState=(int(*)(void))api_getFctPtr("btn_readState");
    halt_device=(void(*)(void))api_getFctPtr("halt_device");
    reload_firmware=(void(*)(void))api_getFctPtr("reload_firmware");
    printf=(void(*)(char *fmt, ...))api_getFctPtr("printf");
    do_bkpt=(void(*)(void))api_getFctPtr("do_bkpt");
    getArch=(int(*)(void))api_getFctPtr("getArch");
    getResolution=(void(*)(int * width,int * height))api_getFctPtr("getResolution");
    float_modsi3=(long(*)(long a, long b))api_getFctPtr("float_modsi3");
    float_umodsi3=(long(*)(long a, long b))api_getFctPtr("float_umodsi3");
    float_divsi3=(long(*)(long a, long b))api_getFctPtr("float_divsi3");
    float_udivsi3=(long(*)(long a, long b))api_getFctPtr("float_udivsi3");
    float_divdi3=(unsigned int(*)(unsigned int a, unsigned int b))api_getFctPtr("float_divdi3");
    open=(int(*)(const char* pathname, int flags))api_getFctPtr("open");
    close=(int(*)(int fdesc))api_getFctPtr("close");
    fsync=(int(*)(int fdesc))api_getFctPtr("fsync");
    read=(int(*)(int fdesc, void *buf, int count))api_getFctPtr("read");
    lseek=(int(*)(int fdesc, int offset, int whence))api_getFctPtr("lseek");
    write=(int(*)(int fdesc, const void *buf, int count))api_getFctPtr("write");
    truncate=(int(*)(int fdesc, int length))api_getFctPtr("truncate");
    filesize=(int(*)(int fdesc))api_getFctPtr("filesize");
    ftell=(int(*)(int fdesc))api_getFctPtr("ftell");
    opendir=(DIR*(*)(const char* name))api_getFctPtr("opendir");
    closedir=(int(*)(DIR* dir))api_getFctPtr("closedir");
    readdir=(struct dirent*(*)(DIR* dir))api_getFctPtr("readdir");
    mkdir=(int(*)(const char *name, int mode))api_getFctPtr("mkdir");
    gfx_openGraphics=(void(*)(void))api_getFctPtr("gfx_openGraphics");
    gfx_closeGraphics=(void(*)(void))api_getFctPtr("gfx_closeGraphics");
    gfx_setPlane=(void(*)(int vplane))api_getFctPtr("gfx_setPlane");
    gfx_getPlane=(int(*)(void))api_getFctPtr("gfx_getPlane");
    gfx_planeHide=(void(*)(int vplane))api_getFctPtr("gfx_planeHide");
    gfx_planeShow=(void(*)(int vplane))api_getFctPtr("gfx_planeShow");
    gfx_planeIsShown=(int(*)(int vplane))api_getFctPtr("gfx_planeIsShown");
    gfx_planeSetState=(void(*)(int vplane,int state))api_getFctPtr("gfx_planeSetState");
    gfx_planeGetState=(int(*)(int vplane))api_getFctPtr("gfx_planeGetState");
    gfx_planeSetSize=(void(*)(int vplane,int width,int height,int bitsPerPixel))api_getFctPtr("gfx_planeSetSize");
    gfx_planeGetSize=(void(*)(int vplane,int * width,int * height,int * bitsPerPixel))api_getFctPtr("gfx_planeGetSize");
    gfx_planeSetPos=(void(*)(int vplane,int x,int y))api_getFctPtr("gfx_planeSetPos");
    gfx_planeGetPos=(void(*)(int vplane,int * x,int * y))api_getFctPtr("gfx_planeGetPos");
    gfx_planeGetBufferOffset=(void*(*)(int vplane))api_getFctPtr("gfx_planeGetBufferOffset");
    gfx_planeSetBufferOffset=(void(*)(int vplane, void * offset))api_getFctPtr("gfx_planeSetBufferOffset");
    gfx_clearScreen=(void(*)(unsigned int color))api_getFctPtr("gfx_clearScreen");
    gfx_drawPixel=(void(*)(unsigned int color,int x, int y))api_getFctPtr("gfx_drawPixel");
    gfx_readPixel=(unsigned int(*)(int x, int y))api_getFctPtr("gfx_readPixel");
    gfx_drawRect=(void(*)(unsigned int color, int x, int y, int width, int height))api_getFctPtr("gfx_drawRect");
    gfx_fillRect=(void(*)(unsigned int color, int x, int y, int width, int height))api_getFctPtr("gfx_fillRect");
    gfx_drawLine=(void(*)(unsigned int color, int x1, int y1, int x2, int y2))api_getFctPtr("gfx_drawLine");
    gfx_putS=(void(*)(unsigned int color, unsigned int bg_color, int x, int y, unsigned char *s))api_getFctPtr("gfx_putS");
    gfx_getStringSize=(void(*)(unsigned char *str, int *w, int *h))api_getFctPtr("gfx_getStringSize");
    gfx_putC=(void(*)(unsigned int color, unsigned int bg_color, int x, int y, unsigned char s))api_getFctPtr("gfx_putC");
    gfx_drawSprite=(void(*)(unsigned int * palette, SPRITE * sprite, int x, int y))api_getFctPtr("gfx_drawSprite");
    gfx_drawBitmap=(void(*)(BITMAP * bitmap, int x, int y))api_getFctPtr("gfx_drawBitmap");
    gfx_scrollWindowVert=(void(*)(unsigned int bgColor, int x, int y, int width, int height, int scroll, int UP))api_getFctPtr("gfx_scrollWindowVert");
    gfx_scrollWindowHoriz=(void(*)(unsigned int bgColor, int x, int y, int width, int height, int scroll, int RIGHT))api_getFctPtr("gfx_scrollWindowHoriz");
    gfx_setPalletteRGB=(void(*)(int r, int g, int b, int index))api_getFctPtr("gfx_setPalletteRGB");
    gfx_fontSet=(void(*)(int font_nb))api_getFctPtr("gfx_fontSet");
    gfx_fontGet=(int(*)(void))api_getFctPtr("gfx_fontGet");
}
