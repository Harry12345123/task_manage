#ifndef _VIDEO_QUEUE_H
#define _VIDEO_QUEUE_H

#include "queue.h"

#define MAX_VIDEO_NUM 30



int init_video_queue_function();
int init_video_queue(unsigned int url_id);
int enqueue_video_queue(struct list_head *in, unsigned int id);
struct list_head *dequeue_video_queue_wait(unsigned int id, struct list_head *out);
struct list_head *dequeue_video_queue_timeout(unsigned int id, struct list_head *out);
struct list_head *dequeue_video_queue(unsigned int id, struct list_head *out);
int clear_video_queue(unsigned int id);

int video_queue_broadcast(unsigned int id);
unsigned int video_queue_size(unsigned int id);

#endif

