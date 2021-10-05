#ifndef AUDIO_VENC_H
#define AUDIO_VENC_H
//#include "queue.h"
#include <pthread.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include "pack.h"

void *audio_venc_proc(void *args);

#endif // AUDIO_VENC_H
