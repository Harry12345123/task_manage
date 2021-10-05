#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "audio_queue.h"
//#include "tunnel_pack_manage.h"

BASE_QUEUE g_audio_queues[MAX_AUDIO_NUM] = {0};

int init_audio_queue_function()
{
    memset(g_audio_queues, 0, sizeof(g_audio_queues));
    for (int i = 0; i < MAX_AUDIO_NUM; i++)
    {
        init_queue(&g_audio_queues[i]);
    }
    return 0;
}

int init_audio_queue(unsigned int id)
{
    init_queue(&g_audio_queues[id]);
    return 0;
}

int enqueue_audio_queue(struct list_head *in, unsigned int id)
{
    en_queue_broadcast(in, &g_audio_queues[id]);
    return 0;
}

struct list_head *dequeue_audio_queue_wait(unsigned int url_id, struct list_head *out)
{
    return de_queue_wait(&g_audio_queues[url_id], out);
}

struct list_head *dequeue_audio_queue_timeout(unsigned int url_id, struct list_head *out)
{
    return de_queue_timedwait(&g_audio_queues[url_id], out);
}

struct list_head *dequeue_audio_queue(unsigned int id, struct list_head *out)
{
    return de_queue(&g_audio_queues[id], out);
}

#if 0
int clear_url_audio_queue(unsigned int url_id)
{
    struct list_head *list = NULL;
    S_TUNNEL_PACK *tunnel_pack = NULL;
    do
    {
        list = dequeue_url_audio_queue(url_id, list);
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

int url_audio_queue_broadcast(unsigned int id)
{	
    queue_broadcast(&g_audio_queues[id]);
    return 0;
}

unsigned int audio_queue_size(unsigned int id)
{
    return queue_size(&g_audio_queues[id]);
}
