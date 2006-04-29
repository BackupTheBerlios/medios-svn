/*
*   kernel/core/api_fct_list.h
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#ifndef __API_FCT_LIST_H
#define __API_FCT_LIST_H

#include <sys_def/stddef.h>
#include <kernel/swi.h>

/* include needed by api functions */
#include <kernel/errors.h>
#include <kernel/malloc.h>
#include <kernel/timer.h>
#include <kernel/rtc.h>
#include <kernel/delay.h>
#include <kernel/bat_power.h>
#include <kernel/usb_fw.h>
#include <kernel/evt.h>
#include <kernel/buttons.h>
#include <kernel/exit.h>
#include <kernel/kernel.h>
#include <kernel/libfloat.h>
#include <kernel/stdfs.h>
#include <kernel/stdfs.h>
#include <kernel/graphics.h>

struct user_fct_t fct_array[] = {
    { "do_malloc",
      (unsigned int)do_malloc
    },
    { "do_realloc",
      (unsigned int)do_realloc
    },
    { "free",
      (unsigned int)free
    },
    { "tmr_getTick",
      (unsigned int)tmr_getTick
    },
    { "rtc_getTime",
      (unsigned int)rtc_getTime
    },
    { "rtc_setTime",
      (unsigned int)rtc_setTime
    },
    { "udelay",
      (unsigned int)udelay
    },
    { "mdelay",
      (unsigned int)mdelay
    },
    { "set_timer_status",
      (unsigned int)set_timer_status
    },
    { "set_timer_delay",
      (unsigned int)set_timer_delay
    },
    { "get_timer_status",
      (unsigned int)get_timer_status
    },
    { "get_timer_delay",
      (unsigned int)get_timer_delay
    },
    { "DC_isConnected",
      (unsigned int)DC_isConnected
    },
    { "batLevel",
      (unsigned int)batLevel
    },
    { "lcd_setBrightness",
      (unsigned int)lcd_setBrightness
    },
    { "lcd_getBrightness",
      (unsigned int)lcd_getBrightness
    },
    { "usb_isConnected",
      (unsigned int)usb_isConnected
    },
    { "FW_isConnected",
      (unsigned int)FW_isConnected
    },
    { "evt_getHandler",
      (unsigned int)evt_getHandler
    },
    { "evt_freeHandler",
      (unsigned int)evt_freeHandler
    },
    { "evt_getStatus",
      (unsigned int)evt_getStatus
    },
    { "evt_getFullStatus",
      (unsigned int)evt_getFullStatus
    },
    { "btn_readState",
      (unsigned int)btn_readState
    },
    { "halt_device",
      (unsigned int)halt_device
    },
    { "reload_firmware",
      (unsigned int)reload_firmware
    },
    { "printf",
      (unsigned int)printf
    },
    { "do_bkpt",
      (unsigned int)do_bkpt
    },
    { "getArch",
      (unsigned int)getArch
    },
    { "getResolution",
      (unsigned int)getResolution
    },
    { "float_modsi3",
      (unsigned int)float_modsi3
    },
    { "float_umodsi3",
      (unsigned int)float_umodsi3
    },
    { "float_divsi3",
      (unsigned int)float_divsi3
    },
    { "float_udivsi3",
      (unsigned int)float_udivsi3
    },
    { "float_divdi3",
      (unsigned int)float_divdi3
    },
    { "open",
      (unsigned int)open
    },
    { "close",
      (unsigned int)close
    },
    { "fsync",
      (unsigned int)fsync
    },
    { "read",
      (unsigned int)read
    },
    { "lseek",
      (unsigned int)lseek
    },
    { "write",
      (unsigned int)write
    },
    { "truncate",
      (unsigned int)truncate
    },
    { "filesize",
      (unsigned int)filesize
    },
    { "ftell",
      (unsigned int)ftell
    },
    { "opendir",
      (unsigned int)opendir
    },
    { "closedir",
      (unsigned int)closedir
    },
    { "readdir",
      (unsigned int)readdir
    },
    { "mkdir",
      (unsigned int)mkdir
    },
    { "gfx_openGraphics",
      (unsigned int)gfx_openGraphics
    },
    { "gfx_closeGraphics",
      (unsigned int)gfx_closeGraphics
    },
    { "gfx_setPlane",
      (unsigned int)gfx_setPlane
    },
    { "gfx_getPlane",
      (unsigned int)gfx_getPlane
    },
    { "gfx_planeHide",
      (unsigned int)gfx_planeHide
    },
    { "gfx_planeShow",
      (unsigned int)gfx_planeShow
    },
    { "gfx_planeIsShown",
      (unsigned int)gfx_planeIsShown
    },
    { "gfx_planeSetState",
      (unsigned int)gfx_planeSetState
    },
    { "gfx_planeGetState",
      (unsigned int)gfx_planeGetState
    },
    { "gfx_planeSetSize",
      (unsigned int)gfx_planeSetSize
    },
    { "gfx_planeGetSize",
      (unsigned int)gfx_planeGetSize
    },
    { "gfx_planeSetPos",
      (unsigned int)gfx_planeSetPos
    },
    { "gfx_planeGetPos",
      (unsigned int)gfx_planeGetPos
    },
    { "gfx_planeGetBufferOffset",
      (unsigned int)gfx_planeGetBufferOffset
    },
    { "gfx_planeSetBufferOffset",
      (unsigned int)gfx_planeSetBufferOffset
    },
    { "gfx_clearScreen",
      (unsigned int)gfx_clearScreen
    },
    { "gfx_drawPixel",
      (unsigned int)gfx_drawPixel
    },
    { "gfx_readPixel",
      (unsigned int)gfx_readPixel
    },
    { "gfx_drawRect",
      (unsigned int)gfx_drawRect
    },
    { "gfx_fillRect",
      (unsigned int)gfx_fillRect
    },
    { "gfx_drawLine",
      (unsigned int)gfx_drawLine
    },
    { "gfx_putS",
      (unsigned int)gfx_putS
    },
    { "gfx_getStringSize",
      (unsigned int)gfx_getStringSize
    },
    { "gfx_putC",
      (unsigned int)gfx_putC
    },
    { "gfx_drawSprite",
      (unsigned int)gfx_drawSprite
    },
    { "gfx_drawBitmap",
      (unsigned int)gfx_drawBitmap
    },
    { "gfx_scrollWindowVert",
      (unsigned int)gfx_scrollWindowVert
    },
    { "gfx_scrollWindowHoriz",
      (unsigned int)gfx_scrollWindowHoriz
    },
    { "gfx_setPalletteRGB",
      (unsigned int)gfx_setPalletteRGB
    },
    { "gfx_fontSet",
      (unsigned int)gfx_fontSet
    },
    { "gfx_fontGet",
      (unsigned int)gfx_fontGet
    },
    { NULL,
      0
    }
};

#endif
