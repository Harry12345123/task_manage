#include <sys/time.h>
#include "queue.h"

int init_queue(BASE_QUEUE *q)
{
    INIT_LIST_HEAD(&q->head);
    q->count = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond, NULL);

    return 0;
}

int en_queue(struct list_head *in, BASE_QUEUE *q)
{
    pthread_mutex_lock(&q->mutex);
    EN_QUEUE(in, &q->head);
    q->count++;
    pthread_mutex_unlock(&q->mutex);

    return 0;
}

void en_queue_broadcast(struct list_head *in, BASE_QUEUE *q)
{
    pthread_mutex_lock(&q->mutex);
    EN_QUEUE(in, &q->head);
    q->count++;
    pthread_cond_broadcast(&q->cond);
    pthread_mutex_unlock(&q->mutex);
}

struct list_head *de_queue(BASE_QUEUE *q, struct list_head *out)
{
    pthread_mutex_lock(&q->mutex);

    if(q->count)
    {
        DE_QUEUE(out, &q->head);
        if(out){
            q->count--;
        }else{
            q->count = 0;
        }
    }else{
        out = NULL; 
    }

    pthread_mutex_unlock(&q->mutex);

    return out;
}

struct list_head *de_queue_without_lock(BASE_QUEUE *q, struct list_head *out)
{
    if(q->count)
    {
        DE_QUEUE(out, &q->head);
        if(out){
            q->count--;
        }else{
            q->count = 0;
        }
    }else{
        out = NULL;
    }

    return out;
}

struct list_head *de_queue_timedwait(BASE_QUEUE *q, struct list_head *out)
{
    pthread_mutex_lock(&q->mutex);

    if (0 == q->count)
    {
        struct timeval timeval_now;
        struct timespec timespec_out;
        gettimeofday(&timeval_now, NULL);
        timespec_out.tv_sec = timeval_now.tv_sec + 1;
        timespec_out.tv_nsec = timeval_now.tv_usec * 1000;
        int ret = pthread_cond_timedwait(&q->cond, &q->mutex, &timespec_out);
        if (ret != 0)
        {
            pthread_mutex_unlock(&q->mutex);
            return NULL;
        }
    }

    if(q->count)
    {
        DE_QUEUE(out, &q->head);
        if(out){
            q->count--;
        }else{
            q->count = 0;
        }
    }else{
        out = NULL; 
    }

    pthread_mutex_unlock(&q->mutex);

    return out;
}

struct list_head *de_queue_wait(BASE_QUEUE *q, struct list_head *out)
{
    pthread_mutex_lock(&q->mutex);

    if(q->count == 0)
    {
        pthread_cond_wait(&q->cond, &q->mutex);
    }

    if(q->count)
    {
        DE_QUEUE(out, &q->head);
        if(out){
            q->count--;
        }else{
            q->count = 0;
        }
    }else{
        out = NULL; 
    }

    pthread_mutex_unlock(&q->mutex);

    return out;
}

int queue_broadcast(BASE_QUEUE *q)
{
    pthread_mutex_lock(&q->mutex);
    pthread_cond_broadcast(&q->cond);
    pthread_mutex_unlock(&q->mutex);

    return 0;
}

int queue_size(BASE_QUEUE *q)
{
    unsigned int count = 0;

    pthread_mutex_lock(&q->mutex);
    count = q->count;
    pthread_mutex_unlock(&q->mutex);

    return count;
}
