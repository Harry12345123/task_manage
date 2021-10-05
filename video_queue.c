#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "video_queue.h"
//include "tunnel_pack_manage.h"

BASE_QUEUE g_video_queues[MAX_VIDEO_NUM] = {0};

int init_video_queue_function()
{
    memset(g_video_queues, 0, sizeof(g_video_queues));
    for (int i = 0; i < MAX_VIDEO_NUM; i++)
    {
        init_queue(&g_video_queues[i]);
    }
    return 0;
}

int init_video_queue(unsigned int id)
{
    init_queue(&g_video_queues[id]);
    return 0;
}

int enqueue_video_queue(struct list_head *in, unsigned int id)
{
    en_queue_broadcast(in, &g_video_queues[id]);
    return 0;
}

struct list_head *dequeue_video_queue_wait(unsigned int id, struct list_head *out)
{
    return de_queue_wait(&g_video_queues[id], out);
}

struct list_head *dequeue_video_queue_timeout(unsigned int id, struct list_head *out)
{
    return de_queue_timedwait(&g_video_queues[id], out);
}

struct list_head *dequeue_video_queue(unsigned int id, struct list_head *out)
{
    return de_queue(&g_video_queues[id], out);
}

#if 0
int clear_url_video_queue(unsigned int url_id)
{
    struct list_head *list = NULL;
    S_TUNNEL_PACK *tunnel_pack = NULL;
    do
    {
        list = dequeue_url_video_queue(url_id, list);
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

int video_queue_broadcast(unsigned int id)
{	
    queue_broadcast(&g_video_queues[id]);
    return 0;
}

unsigned int video_queue_size(unsigned int id)
{
    return queue_size(&g_video_queues[id]);
}
