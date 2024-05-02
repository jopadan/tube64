#include "types.h"

#include <SDL2/SDL.h>

#if defined(_OPL3_)

#include "opl3.h"

#elif defined(_DBOPL_)

#include "dbopl.h"

#else

#include "fmopl.h"

#endif

#include "hmpopl.h"
#include "hmpfile.h"


#include "defs.h"
#include "misc.h"

#include "allocator.h"

#include "mpu401.c"

#include "hmp.h"
#include "sb16.h"

#define KDELTA ((double)(((double)(SB_SAMPLE*TEMPO))/((double)FS))) /* ����������� ��� ������, ����� ���������� ������ ���� ������� */

u8 MusicMode=1; //��������������� �������: 0 - � ������� MIDI(MPU401), 1 - � ������� Adlib(OPL)

#ifdef _DBOPL_

DBOPL::Handler opl;

#else

opl3_chip opl;

#endif

static hmpopl *h;
static hmp_file *hf;

static hmp_event ev;
static unsigned char msg[3];

static IO u8 TIMER_FLAG=0;
static IO u8 AUDIO_FLAG=0;

static IO int Delta=0;
static IO int DeltaAbsolute=0;

static char *INST=NULL;
static char *DRUM=NULL;
static u32 INST_Size;
static u32 DRUM_Size;

#define NM 2 /* ����� ������� � ���� */

static char *MUSIC_Base=NULL;
static char *MUSIC[NM]={NULL};
static u32 MSIZE[NM]={0};

static const int MUSIC_Delta[NM]={0x7500,0x5A00}; //�� ���� ������� ������� �������������(����� �� ����� ������� ����� � ����� � ����� ���������)
static u8 MUSIC_NUMBER=0xFF;

static void OutAdlib(int Index,int Address,int Data)
{
 #ifdef _DBOPL_

 opl.WriteReg((Index<<8)|Address,Data);

 #else

 OPL3_WriteRegBuffered(&opl,(Index<<8)|Address,Data);

 #endif
}

static void opl_noteoff(unsigned short voice)
{
 if(voice>=9) /* if voice is one of the OPL3 set, adjust it and route over secondary OPL port */
 {
  OutAdlib(0,0x1B0+voice-9,0);
  OutAdlib(1,0x1B0+voice-9,0);
 }
 else
 {
  OutAdlib(0,0xB0+voice,0);
  OutAdlib(1,0xB0+voice,0);
 }
}

static void opl_clear(void) /* turns off all notes */
{
/*
01: Test Register / Waveform Select Enable
02: Timer 1 Count
03: Timer 2 Count
004: IRQ-Reset / Mask / Start
104: Four-Operator Enable
105: OPL3 Mode Enable
08: CSW / NOTE-SEL 
20-35: Tremolo / Vibrato / Sustain / KSR / Frequency Multiplication Factor	=> ��� ���� ����� ���������!
40-55: Key Scale Level / Output Level
60-75: Attack Rate / Decay Rate
80-95: Sustain Level / Release Rate
A0-A8: Frequency Number
B0-B8: Key On / Block Number / F-Number(hi bits)				=> �����������
BD: Tremolo Depth / Vibrato Depth / Percussion Mode / BD/SD/TT/CY/HH On		=> �����������
C0-C8: FeedBack Modulation Factor / Synthesis Type
E0-F5: Waveform Select 
*/

 #define VOICECOUNT 9
 for(int i=0;i<VOICECOUNT;i++)opl_noteoff(i);

 /* reset the percussion bits at the 0xBD register */
 OutAdlib(0,0xBD,0);
 OutAdlib(1,0xBD,0);

 for(int i=0x20;i<=0x35;i++) //20-35: Tremolo / Vibrato / Sustain / KSR / Frequency Multiplication Factor
 {
  OutAdlib(0,i,0x00);
  OutAdlib(1,i,0x00);
 }
}

static void song_step(void)
{
 if(MusicMode)hmpopl_play_midi(h,msg[0]>>4,msg[0]&0x0f,msg[1],msg[2]);
 else OutMIDI(msg[0]|(msg[1]<<8)|(msg[2]<<16));

 while(1)        
 {
  if(hmp_get_event(hf,&ev))return;

  if(ev.datalen)continue;

  if((ev.msg[0]&0xf0)==0xb0 && ev.msg[1] == 7)
  {
   int vol = ev.msg[2];
   vol = (vol * 127) >> 7;
   vol = (vol * 127) >> 7;
   ev.msg[2] = vol;
  }

  if(ev.delta)
  {
   msg[0] = ev.msg[0];
   msg[1] = ev.msg[1];
   msg[2] = ev.msg[2];

   Delta+=ev.delta;
   break;
  }

  if(MusicMode)hmpopl_play_midi(h,ev.msg[0]>>4,ev.msg[0]&0x0f,ev.msg[1],ev.msg[2]);
  else OutMIDI(ev.msg[0]|(ev.msg[1]<<8)|(ev.msg[2]<<16));

 }
}

static void song_init(void)
{
 FILE *f=NULL;
 u8 nanobuf[16];

 if(MusicMode)
 {
  f=fopen("SOUND/INST.BNK","rb");
  INST_Size=FileSize(f);
  INST=(char*)Malloc(INST_Size);
  fread(INST,1,INST_Size,f);
  fclose(f);

  f=fopen("SOUND/DRUM.BNK","rb");
  DRUM_Size=FileSize(f);
  DRUM=(char*)Malloc(DRUM_Size);
  fread(DRUM,1,DRUM_Size,f);
  fclose(f);
 }

 f=fopen("SOUND/MUSICF-0.TAB","rb");

 fread(nanobuf,1,sizeof(nanobuf),f);
 fread(nanobuf,1,sizeof(nanobuf),f);
 fread(nanobuf,1,sizeof(nanobuf),f);

 fread(nanobuf,1,sizeof(nanobuf),f);
 MUSIC[0]=(char*)(uintptr_t)(*(UA<u32>*)(nanobuf+0x2));
 MSIZE[0]=*(UA<u32>*)(nanobuf+0xA);

 fread(nanobuf,1,sizeof(nanobuf),f);

 fread(nanobuf,1,sizeof(nanobuf),f);
 MUSIC[1]=(char*)(uintptr_t)(*(UA<u32>*)(nanobuf+0x2));
 MSIZE[1]=*(UA<u32>*)(nanobuf+0xA);

 fclose(f);

 f=fopen("SOUND/MUSICF-0.DAT","rb");
 int s=FileSize(f);
 MUSIC_Base=(char*)Malloc(s);
 fread(MUSIC_Base,1,s,f);
 fclose(f);

 MUSIC[0]+=(uintptr_t)MUSIC_Base;
 MUSIC[1]+=(uintptr_t)MUSIC_Base;

 if(MusicMode)
 {
  h=hmpopl_new();

  hmpopl_set_bank(h,INST,INST_Size,0);
  hmpopl_set_bank(h,DRUM,DRUM_Size,1);

  hmpopl_set_write_callback(h,OutAdlib);
 }
 else MIDI_Open();
}

static void song_start(u8 sn)
{
 memset(&msg,0,sizeof(msg));
 memset(&ev,0,sizeof(hmp_event));

 if(!(hf=hmp_open(MUSIC[sn],MSIZE[sn],0xA009,1)))
 {
  printf("read failed\n");

  if(MusicMode)hmpopl_done(h);
  else MIDI_Close();

  return;
 }

 hmp_reset_tracks(hf);

 if(MusicMode)
 {
  hmpopl_start(h);

  //hmpopl_reset(h);
  opl_clear();
 }
 else MIDI_Clear();

 Delta=0;
 DeltaAbsolute=0;
}

static void mySDL_AudioCallback(void*, Uint8 *stream, int len) //������ ����������� ���������� �������� �������
{
 asm volatile ("" ::: "memory");
 AUDIO_FLAG=0;

 asm volatile ("" ::: "memory");
 if(TIMER_FLAG)
 {
  if(Delta>=MUSIC_Delta[MUSIC_NUMBER])
  {
   hmp_reset_tracks(hf);

   if(MusicMode)
   {
    //hmpopl_reset(h);
    opl_clear();
   }
   else MIDI_Clear();

   DeltaAbsolute=0;
   Delta=0;
  }

  MIXER((s16*)stream);

  DeltaAbsolute++;
  while(Delta<=(int)(((double)DeltaAbsolute)*KDELTA))song_step();
 }
 else memset(stream,0,len);

 asm volatile ("" ::: "memory");
 AUDIO_FLAG=1;
}

void MY_OpenMusic(unsigned int a4)
{
 TIMER_FLAG=0;

 if(SDL_Init(SDL_INIT_AUDIO)<0)
 {
  printf("error!\n");
  exit(-1);
 }

 SDL_AudioSpec spec={};

 spec.freq     = FS;                  //������� �������������
 spec.format   = AUDIO_S16SYS;        //16 ���, ��������
 spec.channels = 1;                   //1 �����
 spec.samples  = SB_SAMPLE;           //������� ������
 spec.callback = mySDL_AudioCallback;
 spec.userdata = NULL;

 if(SDL_OpenAudio(&spec,NULL)<0)
 {
  printf("error!\n");
  exit(-1);
 }

 if(MusicMode)
       #ifdef _DBOPL_
           opl.Init(FS);
       #else
           OPL3_Reset(&opl,FS);
       #endif

 song_init();

 SDL_PauseAudio(0); //��������� ���������� ������
}

void MY_FreeMusic(void)
{
 TIMER_FLAG=0;

 SDL_PauseAudio(1); //���������� ���������� ������

 SDL_CloseAudio();

 if(hf)
 {
  hmp_close(hf);
  hf=NULL;
 }

 if(MusicMode)
 {
  //hmpopl_reset(h);
  opl_clear();

  hmpopl_done(h);
 }
 else
 {
  MIDI_Clear();
  MIDI_Close();
 }

 if(INST)Free(INST);
 if(DRUM)Free(DRUM);
 if(MUSIC_Base)Free(MUSIC_Base);
}

void MY_StartMusic(short a1, unsigned char a2)
{
 if(((a1-1)==MUSIC_NUMBER)&&TIMER_FLAG)return;

 MY_StopMusic();

 if(!TIMER_FLAG)
 {
  MUSIC_NUMBER=a1-1;
  song_start(MUSIC_NUMBER);
  TIMER_FLAG=1;
 }
}

void MY_StopMusic(void)
{
 if(TIMER_FLAG)
 {
  asm volatile ("" ::: "memory");
  while(!AUDIO_FLAG);             //prevent broken audio callback

  asm volatile ("" ::: "memory");
  AUDIO_FLAG=0;
  TIMER_FLAG=0;

  asm volatile ("" ::: "memory");
  if(hf)
  {
   hmp_close(hf);
   hf=NULL;
  }

  asm volatile ("" ::: "memory");
  if(MusicMode)
  {
   //hmpopl_reset(h);
   opl_clear();
  }
  else MIDI_Clear();

 }
}
