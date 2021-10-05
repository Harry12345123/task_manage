#ifndef _TASK_TEST_H
#define _TASK_TEST_H

#include <stdio.h>
#include <unistd.h>
#include "task_data_proc.h"
#include "video_venc.h"
#include "task_manage.h"
#include "task_queue.h"
#include "video_queue.h"
#include "audio_queue.h"
#include "pack_handle.h"
#include "pack_send.h"
#include "debug.h"

int create_task_config();
int create_task_config_pack();
int create_task1_config();
int create_task2_config();

void * dequeue_data_proc(void *args);

#endif
