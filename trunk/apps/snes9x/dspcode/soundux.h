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

#ifndef _SOUND_H_
#define _SOUND_H_

enum { SOUND_SAMPLE = 0, SOUND_NOISE, SOUND_EXTRA_NOISE, SOUND_MUTE };
enum { SOUND_SILENT, SOUND_ATTACK, SOUND_DECAY, SOUND_SUSTAIN,
       SOUND_RELEASE, SOUND_GAIN, SOUND_INCREASE_LINEAR,
       SOUND_INCREASE_BENT_LINE, SOUND_DECREASE_LINEAR,
       SOUND_DECREASE_EXPONENTIAL};

enum { MODE_NONE = SOUND_SILENT, MODE_ADSR, MODE_RELEASE = SOUND_RELEASE,
       MODE_GAIN, MODE_INCREASE_LINEAR, MODE_INCREASE_BENT_LINE,
       MODE_DECREASE_LINEAR, MODE_DECREASE_EXPONENTIAL};

#define MAX_ENVELOPE_HEIGHT 127
#define ENVELOPE_SHIFT 7
#define MAX_VOLUME 127
#define VOLUME_SHIFT 7
#define VOL_DIV 128
#define SOUND_DECODE_LENGTH 16

#define NUM_CHANNELS    8
#define SOUND_BUFFER_SIZE (128)
#define MAX_BUFFER_SIZE SOUND_BUFFER_SIZE
#define SOUND_BUFFER_SIZE_MASK (SOUND_BUFFER_SIZE - 1)

#define SOUND_BUFS      4

#ifdef __sgi
#  include <audio.h>
#endif /* __sgi */

typedef struct {
    int sound_fd;
    int sound_switch;
    unsigned int playback_rate;
    int buffer_size;
    int32 noise_gen;
    short mute_sound;
    int stereo;
    short sixteen_bit;
    short encoded;
#ifdef __sun
    int last_eof;
#endif
#ifdef __sgi
    ALport al_port;
#endif /* __sgi */
    uint32 samples_mixed_so_far;
    uint32 play_position;
    uint32 err_counter;
    uint32 err_rate;
} SoundStatus;

EXTERN_C volatile SoundStatus so;

typedef struct {
    int state;
    int type;
    short volume_left;
    short volume_right;
    uint32 hertz;
    uint32 frequency;
    short count;
    short loop;
    short envx;
    short left_vol_level;
    short right_vol_level;
    short envx_target;
    unsigned long env_error;
    unsigned long erate;
    int direction;
    unsigned long attack_rate;
    unsigned long decay_rate;
    unsigned long sustain_rate;
    unsigned long release_rate;
    unsigned long sustain_level;
    signed short decoded [16+3];
    signed short *block;
    uint16 sample_number;
    short last_block;
    short needs_decode;
    uint16 block_pointer;
    uint32 sample_pointer;
    long *echo_buf_ptr;
    int mode;
    int32 envxx;
    //int32 interpolate;
    short latch_noise;
} Channel;

typedef struct
{
    short master_volume_left;
    short master_volume_right;
    short echo_volume_left;
    short echo_volume_right;
    int echo_enable;
    int echo_feedback;
    int echo_ptr;
    int echo_buffer_size;
    int echo_write_enabled;
    int echo_channel_enable;
    int pitch_mod;
    // Just incase they are needed in the future, for snapshot compatibility.
    Channel channels [NUM_CHANNELS];
    short no_filter;
    int master_volume [2];
    int echo_volume [2];
    uint32 noise_hertz;
} SSoundData;

EXTERN_C SSoundData SoundData;

START_EXTERN_C
void S9xSetSoundVolume (int channel, short volume_left, short volume_right);
void S9xSetSoundFrequency (int channel, uint32 hertz);
void S9xSetSoundHertz (int channel, uint32 hertz);
void S9xSetSoundType (int channel, int type_of_sound);
void S9xSetMasterVolume (short master_volume_left, short master_volume_right);
void S9xSetEchoVolume (short echo_volume_left, short echo_volume_right);
void S9xSetSoundControl (int sound_switch);
bool8 S9xSetSoundMute (bool8 mute);
void S9xSetEnvelopeHeight (int channel, int height);
void S9xSetSoundADSR (int channel, int attack, int decay, int sustain,
		      int sustain_level, int release);
void S9xSetSoundKeyOff (int channel);
void S9xSetSoundDecayMode (int channel);
void S9xSetSoundAttachMode (int channel);
void S9xSoundStartEnvelope (Channel *);
void S9xSetSoundSample (int channel, uint16 sample_number);
void S9xSetEchoFeedback (int echo_feedback);
void S9xSetEchoEnable (uint8 byte);
void S9xSetEchoDelay (int byte);
void S9xSetEchoWriteEnable (uint8 byte);
void S9xSetFilterCoefficient (int tap, int value);
void S9xSetFrequencyModulationEnable (uint8 byte);
void S9xSetEnvelopeRate (int channel, unsigned long rate, int direction,
			 int target);
bool8 S9xSetSoundMode (int channel, int mode);
int S9xGetEnvelopeHeight (int channel);
void S9xResetSound (bool8 full);
void S9xFixSoundAfterSnapshotLoad ();
void S9xPlaybackSoundSetting (int channel);
void S9xPlaySample (int channel);
void S9xFixEnvelope (int channel, uint8 gain, uint8 adsr1, uint8 adsr2);
void S9xStartSample (int channel);

EXTERN_C void S9xMixSamples (uint8 *buffer, int sample_count);
EXTERN_C void S9xMixSamplesO (uint8 *buffer, int sample_count, int byte_offset);
bool8 S9xOpenSoundDevice (int, bool8, int);
void S9xSetPlaybackRate (uint32 rate);
END_EXTERN_C
#endif
