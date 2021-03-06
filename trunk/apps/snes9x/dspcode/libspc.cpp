extern "C" {
#include <sys_def/section_types.h>
#include "kernel/stdfs.h"

#include "profile.h"
//#include <stdio.h>

int printf(const char * fmt, ...);
}

#include "snes9x.h"
#include "port.h"
#include "apu.h"
#include "soundux.h"
#include "libspc.h"

#define RATE (400*2)

// VP ARRRRRGGGGGG ELIMINER CES TABLEAUX STATIQUES SVP !!!!!!!
SAPURegisters BackupAPURegisters;
unsigned char BackupAPURAM[65536];
unsigned char BackupAPUExtraRAM[64];
unsigned char BackupDSPRAM[128];

int samples_per_mix;


// The callback

__IRAM_CODE static void DoTimer (void)
{
  APURegisters.PC = IAPU.PC - IAPU.RAM;
//   S9xAPUPackStatus ();

//   if (IAPU.APUExecuting)
//     APU.Cycles -= 90;//Settings.H_Max;
//   else
//     APU.Cycles = 0;

  if (APU.TimerEnabled [2]) {
#if 1 // WinSPC
      APU.Timer [2] ++;
#else // snes9x
      APU.Timer [2] += 4;
#endif
      if (APU.Timer [2] >= APU.TimerTarget [2]) {
	  IAPU.RAM [0xff] = (IAPU.RAM [0xff] + 1) & 0xf;
#if 1  // WinSPC
 	  APU.Timer [2] = 0;
#else  // snes9x
	  APU.Timer [2] -= APU.TimerTarget [2];
#endif
#ifdef SPC700_SHUTDOWN          
	  IAPU.WaitCounter++;
	  IAPU.APUExecuting = TRUE;
#endif          

	}
    }
  if (IAPU.TimerErrorCounter >= 8)
    {
      IAPU.TimerErrorCounter = 0;
      if (APU.TimerEnabled [0])
	{
	  APU.Timer [0]++;
	  if (APU.Timer [0] >= APU.TimerTarget [0])
	    {
	      IAPU.RAM [0xfd] = (IAPU.RAM [0xfd] + 1) & 0xf;
	      APU.Timer [0] = 0;
#ifdef SPC700_SHUTDOWN          
	      IAPU.WaitCounter++;
	      IAPU.APUExecuting = TRUE;
#endif          

	    }
	}
      if (APU.TimerEnabled [1])
	{
	  APU.Timer [1]++;
	  if (APU.Timer [1] >= APU.TimerTarget [1])
	    {
	      IAPU.RAM [0xfe] = (IAPU.RAM [0xfe] + 1) & 0xf;
	      APU.Timer [1] = 0;
#ifdef SPC700_SHUTDOWN          
	      IAPU.WaitCounter++;
	      IAPU.APUExecuting = TRUE;
#endif          
	    }
	}
    }
}

/* ================================================================ */

START_EXTERN_C

int SPC_init(SPC_Config *cfg)
{
    return SPC_set_state(cfg);
}

void SPC_close(void)
{
    S9xDeinitAPU();
}

int SPC_set_state(SPC_Config *cfg)
{
    int i;

    Settings.DisableSampleCaching = FALSE;
    Settings.APUEnabled = TRUE;
    Settings.InterpolatedSound = (cfg->is_interpolation) ? TRUE : FALSE;
    Settings.SoundEnvelopeHeightReading = TRUE;
    Settings.DisableSoundEcho = (cfg->is_echo) ? FALSE : TRUE;
    //   Settings.EnableExtraNoise = TRUE;

    // SPC mixer information
    samples_per_mix = cfg->sampling_rate / RATE * cfg->channels;
    so.playback_rate = cfg->sampling_rate;
    so.err_rate = (uint32)(SNES_SCANLINE_TIME * 0x10000UL / (1.0 / (double) so.playback_rate));
    S9xSetEchoDelay(APU.DSP [APU_EDL] & 0xf);
    for (i = 0; i < 8; i++)
	S9xSetSoundFrequency(i, SoundData.channels [i].hertz);
    so.buffer_size = samples_per_mix;
    so.stereo = (cfg->channels == 2) ? TRUE : FALSE;

    if (cfg->resolution == 16){
        so.buffer_size *= 2;
        so.sixteen_bit = TRUE;
    } else
        so.sixteen_bit = FALSE;
    
    so.encoded = FALSE;
    so.mute_sound = FALSE;

    return so.buffer_size;
}



/*
 * VP : each time a timer is read, the SPC is slowdowned for 
 * SPC_slowdown_instructions instructions.
 * This should leverage host CPU usage without noticeable effect.
 * (the SPC get exactly 2^SPC_slowdown_cycle_shift times slower, 
 *  thus 2^SPC_slowdown_cycle_shift times faster to emulate in
 *  slowdown mode)
 *
 */

#ifdef DCPLAYA
__IRAM_DATA int SPC_debugcolor = 0;
#endif

// values used to be 6/20, but it seems more accurate like this.
__IRAM_DATA int SPC_slowdown_cycle_shift = 4;
__IRAM_DATA int SPC_slowdown_instructions = 80;


#ifdef DCPLAYA
# include <kos.h>
#endif

#ifdef DCPLAYA
inline void BCOLOR(int r, int g, int b)
{
  if (SPC_debugcolor)
    vid_border_color(r, g, b);
}
#else
# define BCOLOR(r, g, b) (void) 0
#endif

#if 1
unsigned int cpu_stats[256];
unsigned int cpu_stats2[256];
#endif

/* get samples
   ---------------------------------------------------------------- */
__IRAM_CODE void SPC_update(unsigned char *buf)
{
  // APU_LOOP
  int c, ic, oc;

  BCOLOR(255, 0, 0);

  prof(PROF_CPU);
  /* VP : rewrote this loop, it was completely wrong in original
     spcxmms-0.2.1 */
  for (c = 0; c < 2048000 / RATE; ) {
    oc = c;
    for (ic = c + 32; c < ic; ) {
      int cycles;
#if 0
      cpu_stats[*IAPU.PC]++;
      if (cpu_stats[*IAPU.PC] == 0)
	cpu_stats2[*IAPU.PC]++;
#endif
      cycles = S9xAPUCycleLengths [*IAPU.PC];
      (*S9xApuOpcodes[*IAPU.PC]) ();
      //APU_EXECUTE1();

      if (IAPU.Slowdown > 0) {
	/* VP : in slowdown mode, SPC executes 2^SPC_slowdown_cycle_shift 
	   times slower */
	c += cycles << SPC_slowdown_cycle_shift;
	IAPU.Slowdown--;
      } else {
	/* VP : no slowdown, normal speed of the SPC */
	c += cycles;
      }
    }

    /* VP : Execute timer required number of times */
    for (ic = 0; ic < (c / 32) - (oc / 32) ; ic++) {
      IAPU.TimerErrorCounter ++;
      DoTimer();
    }

  }

  prof(PROF_APU);
  BCOLOR(255, 255, 0);
  S9xMixSamples ((unsigned char *)buf, samples_per_mix);
  BCOLOR(0, 0, 0);

}

/* Restore SPC state
   ---------------------------------------------------------------- */
static void RestoreSPC()
{
    int i;

    APURegisters.PC = BackupAPURegisters.PC;
    APURegisters.YA.B.A = BackupAPURegisters.YA.B.A;
    APURegisters.X = BackupAPURegisters.X;
    APURegisters.YA.B.Y = BackupAPURegisters.YA.B.Y;
    APURegisters.P = BackupAPURegisters.P;
    APURegisters.S = BackupAPURegisters.S;
    memcpy (IAPU.RAM, BackupAPURAM, 65536);
    memcpy (APU.ExtraRAM, BackupAPUExtraRAM, 64);
    memcpy (APU.DSP, BackupDSPRAM, 128);

    for (i = 0; i < 4; i ++)
    {
        APU.OutPorts[i] = IAPU.RAM[0xf4 + i];
    }
    IAPU.TimerErrorCounter = 0;

    for (i = 0; i < 3; i ++)
    {
        if (IAPU.RAM[0xfa + i] == 0)
            APU.TimerTarget[i] = 0x100;
        else
            APU.TimerTarget[i] = IAPU.RAM[0xfa + i];
    }

    S9xSetAPUControl (IAPU.RAM[0xf1]);

  /* from snaporig.cpp (ReadOrigSnapshot) */
    S9xSetSoundMute (FALSE);
    IAPU.PC = IAPU.RAM + APURegisters.PC;
    S9xAPUUnpackStatus ();
    if (APUCheckDirectPage ())
        IAPU.DirectPage = IAPU.RAM + 0x100;
    else
        IAPU.DirectPage = IAPU.RAM;
    Settings.APUEnabled = TRUE;
    IAPU.APUExecuting = TRUE;

    S9xFixSoundAfterSnapshotLoad ();

    S9xSetFrequencyModulationEnable (APU.DSP[APU_PMON]);
    S9xSetMasterVolume (APU.DSP[APU_MVOL_LEFT], APU.DSP[APU_MVOL_RIGHT]);
    S9xSetEchoVolume (APU.DSP[APU_EVOL_LEFT], APU.DSP[APU_EVOL_RIGHT]);

    uint8 mask = 1;
    int type;
    for (i = 0; i < 8; i++, mask <<= 1) {
        Channel *ch = &SoundData.channels[i];
      
        S9xFixEnvelope (i,
                        APU.DSP[APU_GAIN + (i << 4)],
                        APU.DSP[APU_ADSR1 + (i << 4)],
                        APU.DSP[APU_ADSR2 + (i << 4)]);
	APU.DSP[APU_VOL_LEFT + (i << 4)] /= 2;
	APU.DSP[APU_VOL_RIGHT + (i << 4)] /= 2;
        S9xSetSoundVolume (i,
                           APU.DSP[APU_VOL_LEFT + (i << 4)],
                           APU.DSP[APU_VOL_RIGHT + (i << 4)]);
        S9xSetSoundFrequency (i, ((APU.DSP[APU_P_LOW + (i << 4)]
                                   + (APU.DSP[APU_P_HIGH + (i << 4)] << 8))
                                  & FREQUENCY_MASK) * 8);
        if (APU.DSP [APU_NON] & mask)
            type = SOUND_NOISE;
        else
            type = SOUND_SAMPLE;
        S9xSetSoundType (i, type);
        if ((APU.DSP[APU_KON] & mask) != 0)
	{
	    APU.KeyedChannels |= mask; // VP wasn't initially cleared ??
            S9xPlaySample (i);
	}
    }

#if 0
    unsigned char temp=IAPU.RAM[0xf2];
    for(i=0;i<128;i++){
        IAPU.RAM[0xf2]=i;
        S9xSetAPUDSP(APU.DSP[i]);
    }
    IAPU.RAM[0xf2]=temp;
#endif
}

inline int my_fread(void * buffer, int a, int b, int  fd)
{
  int res = read(fd, buffer, a*b);
  //printf("READING %d bytes %d\n", b, res);
  return res / a;
}
inline int my_fwrite(void * buffer, int a, int b, int  fd)
{
  return write(fd, buffer, a*b);
}

#define fseek lseek

#ifndef EOF
# define EOF (-1)
#endif
int fgetc(int fd)
{
  char res;
  int n = read(fd, &res, 1);
  if (n<=0) return EOF;
  return res;
}

static int read_id666 (int fp, SPC_ID666 * id)
{
  int err = -1;
  int pos;

  if (id) {
    memset(id, 0, sizeof(*id));
  }

  if (fp < 0 || !id) {
    return -1;
  }

  pos = lseek(fp, 0, SEEK_CUR);
  
  lseek(fp, 0x23, SEEK_SET);
  if (fgetc(fp) == 27) {
    goto error;
  }

  lseek(fp, 0x2E, SEEK_SET);
  my_fread(id->songname, 1, 32, fp);
  id->songname[33] = '\0';

  my_fread(id->gametitle, 1, 32, fp);
  id->gametitle[33] = '\0';

  my_fread(id->dumper, 1, 16, fp);
  id->dumper[17] = '\0';

  my_fread(id->comments, 1, 32, fp);
  id->comments[33] = '\0';

  printf("songname %s\n", id->songname);
  printf("title %s\n", id->gametitle);
  printf("dumper %s\n", id->dumper);
  printf("comments %s\n", id->comments);

  fseek(fp, 0xD0, SEEK_SET);
  switch (fgetc (fp)) {
  case 1:
    id->emulator = SPC_EMULATOR_ZSNES;
    printf("ZSNES\n");
    break;
  case 2:
    id->emulator = SPC_EMULATOR_SNES9X;
    printf("SNES9x\n");
    break;
  case 0:
  default:
    id->emulator = SPC_EMULATOR_UNKNOWN;
    printf("UNKNOWN EMULATOR\n");
    break;
  }

  fseek(fp, 0xB0, SEEK_SET);
  my_fread(id->author, 1, 32, fp);
  id->author[33] = '\0';

  id->valid = 1;
  err = 0;

 error:
  fseek(fp, pos, SEEK_SET);
  return err;
}  

/* Load SPC file [CLEANUP]
   ---------------------------------------------------------------- */
int SPC_load (const char *fname, SPC_ID666 * id)
{
  int fp;
  char temp[64];

  if (id) {
    memset(id, 0, sizeof(*id));
  }

  fp = open (fname, O_RDONLY/*"r"*/);
  if (fp < 0) {
    printf("Could not open '%s' for reading\n", fname);
    return FALSE;
  }

  read_id666(fp, id);

  IAPU.OneCycle = ONE_APU_CYCLE; /* VP : moved this before call to S9xResetAPU !! */

  S9xInitAPU();
  S9xResetAPU();

  fseek(fp, 0x25, SEEK_SET);
  my_fread(&BackupAPURegisters.PC, 1, 2, fp);
  my_fread(&BackupAPURegisters.YA.B.A, 1, 1, fp);
  my_fread(&BackupAPURegisters.X, 1, 1, fp);
  my_fread(&BackupAPURegisters.YA.B.Y, 1, 1, fp);
  my_fread(&BackupAPURegisters.P, 1, 1, fp);
  my_fread(&BackupAPURegisters.S, 1, 1, fp);

  fseek(fp, 0x100, SEEK_SET);
  my_fread(BackupAPURAM, 1, 0x10000, fp);
  my_fread(BackupDSPRAM, 1, 128, fp);
  my_fread(temp, 1, 64, fp);
  my_fread(BackupAPUExtraRAM, 1, 64, fp);

  close(fp);

  RestoreSPC();

  return TRUE;
}

/* ID666
   ---------------------------------------------------------------- */
int SPC_get_id666 (const char *filename, SPC_ID666 * id)
{
  int err;
  int fp;
  SPC_ID666 dummyid;

  if (id == NULL) {
    id = &dummyid;
  }

  fp = open(filename, O_RDONLY);
  if (fp < 0) {
    return FALSE;
  }

  err = read_id666(fp, id);

  close(fp);

  return err ? FALSE : TRUE;
}

int SPC_write_id666 (SPC_ID666 *id, const char *filename)
{
  int fp;
  int spc_size;
  unsigned char *spc_buf;

  if (id == NULL)
    return FALSE;

  fp = open (filename, O_RDONLY);
  if (fp < 0)
    return FALSE;

  spc_size = fseek(fp, 0, SEEK_END);
  //spc_size = lseek(fp, 0, SEEK_CUR));

  spc_buf = (unsigned char *)malloc(spc_size);
  if (spc_buf == NULL) {
      close (fp);
      return FALSE;
  }

  my_fread(spc_buf, 1, spc_size, fp);
  close(fp);

  if (*(spc_buf + 0x23) == 27)
    {
      free(spc_buf);
      return FALSE;
    }
  
  memset(spc_buf + 0x2E, 0, 119);
  memset(spc_buf + 0xA9, 0, 38);
  memset(spc_buf + 0x2E, 0, 36);
  
  memcpy(spc_buf + 0x2E, id->songname, 32);
  memcpy(spc_buf + 0x4E, id->gametitle, 32);
  memcpy(spc_buf + 0x6E, id->dumper, 16);
  memcpy(spc_buf + 0x7E, id->comments, 32);
  memcpy(spc_buf + 0xB0, id->author, 32);

  spc_buf[0xD0] = 0;
  
  switch (id->emulator) {
  case SPC_EMULATOR_UNKNOWN:
      *(spc_buf + 0xD1) = 0;
      break;
  case SPC_EMULATOR_ZSNES:
      *(spc_buf + 0xD1) = 1;
      break;
  case SPC_EMULATOR_SNES9X:
      *(spc_buf + 0xD1) = 2;
      break;
  }
  
  fp = open(filename, O_WRONLY);
  if (fp < 0) {
      free(spc_buf);
      return FALSE;
  }

  my_fwrite(spc_buf, 1, spc_size, fp);
  close(fp);

  return TRUE;
}

END_EXTERN_C


// define new/delete operators

void * operator new (unsigned int bytes) {
//   SDDEBUG("[%s] : %u\n", __FUNCTION__, bytes);
  return malloc(bytes);
}

void operator delete (void *addr) {
//   SDDEBUG("[%s] : %p\n", __FUNCTION__, addr);
  free (addr);
}

void * operator new[] (unsigned int bytes) {
//   SDDEBUG("[%s] : %u\n", __FUNCTION__, bytes);
  return malloc(bytes);
}

void operator delete[] (void *addr) {
//   SDDEBUG("[%s] : %p\n", __FUNCTION__, addr);
  free (addr);
}
