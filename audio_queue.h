#ifndef _AUDIO_QUEUE_H
#define _AUDIO_QUEUE_H

#include <stdio.h>
#include <unistd.h>
#include "queue.h"

#define MAX_AUDIO_NUM 30

int init_audio_queue_function();
int init_audio_queue(unsigned int id);
int enqueue_audio_queue(struct list_head *in, unsigned int id);
struct list_head *dequeue_audio_queue_wait(unsigned int id, struct list_head *out);
struct list_head *dequeue_audio_queue_timeout(unsigned int id, struct list_head *out);
struct list_head *dequeue_audio_queue(unsigned int id, struct list_head *out);
int clea_audio_queue(unsigned int id);

int audio_queue_broadcast(unsigned int id);
unsigned int audio_queue_size(unsigned int id);

#endif

