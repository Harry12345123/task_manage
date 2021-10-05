#ifndef _QUEUE_H
#define _QUEUE_H

#include <pthread.h>
#include "list.h"

#define EN_QUEUE(item, head) list_add(item, head)
#define EN_QUEUE_TAIL(item, head) list_add_tail(item, head)

#define DE_QUEUE(list, head)      \
if(!list_empty(head))             \
{                                 \
    list = (head)->prev;          \
    list_del(list);               \
}                                 \
else                              \
{                                 \
    list = NULL;                  \
}                                 \

typedef struct{
    struct list_head head;
    unsigned int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}BASE_QUEUE;

int init_queue(BASE_QUEUE *q);
int en_queue(struct list_head *in, BASE_QUEUE *q);
void en_queue_broadcast(struct list_head *in, BASE_QUEUE *q);
struct list_head *de_queue(BASE_QUEUE *q, struct list_head *out);
struct list_head *de_queue_without_lock(BASE_QUEUE *q, struct list_head *out);
struct list_head *de_queue_timedwait(BASE_QUEUE *q, struct list_head *out);
struct list_head *de_queue_wait(BASE_QUEUE *q, struct list_head *out);

int queue_broadcast(BASE_QUEUE *q);
int queue_size(BASE_QUEUE *q);

#endif
