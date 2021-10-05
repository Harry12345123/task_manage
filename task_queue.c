#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "task_queue.h"
//#include "tunnel_pack_manage.h"

BASE_QUEUE g_task_queues[MAX_TASK_NUM] = {0};

int init_task_queue_function()
{
    memset(g_task_queues, 0, sizeof(g_task_queues));
    for (int i = 0; i < MAX_TASK_NUM; i++)
    {
        init_queue(&g_task_queues[i]);
    }
    return 0;
}

int init_task_queue(unsigned int task_id)
{
    init_queue(&g_task_queues[task_id]);
    return 0;
}

int enqueue_task_queue(struct list_head *in, unsigned int task_id)
{
    en_queue_broadcast(in, &g_task_queues[task_id]);
    return 0;
}

struct list_head *dequeue_task_queue_wait(unsigned int task_id, struct list_head *out)
{
    return de_queue_wait(&g_task_queues[task_id], out);
}

struct list_head *dequeue_task_queue_timeout(unsigned int task_id, struct list_head *out)
{
    return de_queue_timedwait(&g_task_queues[task_id], out);
}

struct list_head *dequeue_task_queue(unsigned int task_id, struct list_head *out)
{
    return de_queue(&g_task_queues[task_id], out);
}

#if 0
int clear_task_queue(unsigned int task_id)
{
    struct list_head *list = NULL;
    S_TUNNEL_PACK *tunnel_pack = NULL;
    do
    {
        list = dequeue_task_queue(task_id, list);
        if (list != NULL)
        {
            tunnel_pack = list_entry(list, S_TUNNEL_PACK, head);
            free(tunnel_pack);
        }
        else
        {
            break;
        }
    }while(1);

    return 0;
}
#endif

int task_queue_broadcast(unsigned int task_id)
{
    queue_broadcast(&g_task_queues[task_id]);
    return 0;
}
