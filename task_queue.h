#ifndef _TASK_QUEUE_H
#define _TASK_QUEUE_H

#include "queue.h"
#include "task_config.h"

int init_task_queue_function();
int init_task_queue(unsigned int task_id);
int enqueue_task_queue(struct list_head *in, unsigned int task_id);
struct list_head *dequeue_task_queue_wait(unsigned int task_id, struct list_head *out);
struct list_head *dequeue_task_queue_timeout(unsigned int task_id, struct list_head *out);
struct list_head *dequeue_task_queue(unsigned int task_id, struct list_head *out);
int clear_task_queue(unsigned int task_id);
int task_queue_broadcast(unsigned int task_id);

#endif

