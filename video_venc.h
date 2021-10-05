#ifndef VIDEO_VENC_H
#define VIDEO_VENC_H
#include "pack.h"
#include "queue.h"
#include <pthread.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>



void *video_venc_proc(void *args);

#endif // VIDEO_VENC_H
