#pragma once

#include "types.h"

#define FS       44100 /* ������� �������������          */
#define TEMPO      120 /* ���� �������                   */
#define SB_SAMPLE  512 /* ���������� SDL: ������� ������ */

void MIXER(s16 *stream);

void MY_OpenSound(void);
void MY_FreeSound(void);
void MY_PlaySample(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, signed int a6, unsigned int a7);
void MY_FadeOutSample(short a1, short a2, short a3, short a4);
void MY_FadeInSample(short a1, short a2, short a3, short a4);
void MY_SetSamplePitch(short a1, short a2, short a3);
void MY_SetSamplePan(short a1, short a2, unsigned short a3);

