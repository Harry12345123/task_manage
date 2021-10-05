#include <pthread.h>
#include <string.h>
#include "task_manage.h"
#include "video_queue.h"
#include "audio_queue.h"
#include "debug.h"
#include "video_venc.h"
#include "audio_venc.h"
#include "pack_handle.h"
#include "task_test.h"
#include "task_data_proc.h"

S_TASK_CONFIG g_task_config;
pthread_mutex_t g_task_config_mutex;


int init_task_manage_function()
{
    pthread_mutex_init(&g_task_config_mutex, NULL);
    memset(&g_task_config, 0, sizeof(g_task_config));
    return 0;
}

int set_task_config(S_TASK_CONFIG *config)
{
    pthread_mutex_lock(&g_task_config_mutex);
    g_task_config = *config;
    pthread_mutex_unlock(&g_task_config_mutex);
    return 0;
}

S_TASK_CONFIG get_task_config()
{
    S_TASK_CONFIG config = {0};
    pthread_mutex_lock(&g_task_config_mutex);
    config = g_task_config;
    pthread_mutex_unlock(&g_task_config_mutex);

    return config;
}

unsigned int set_task_config_id(unsigned int id)
{
    pthread_mutex_lock(&g_task_config_mutex);
    g_task_config.id = id;
    pthread_mutex_unlock(&g_task_config_mutex);

    return 0;
}

unsigned int get_task_config_id()
{
    unsigned int id = 0;

    pthread_mutex_lock(&g_task_config_mutex);
    id = g_task_config.id;
    pthread_mutex_unlock(&g_task_config_mutex);

    return id;
}

int set_task_config_random_value(unsigned int random_value)
{
    pthread_mutex_lock(&g_task_config_mutex);
    g_task_config.random_value = random_value;
    pthread_mutex_unlock(&g_task_config_mutex);

    return 0;
}

unsigned int get_task_config_random_value()
{
    unsigned int random_value = 0;

    pthread_mutex_lock(&g_task_config_mutex);
    random_value = g_task_config.random_value;
    pthread_mutex_unlock(&g_task_config_mutex);

    return random_value;
}

unsigned int set_task_config_cpu_type(E_CPU_TYPE cpu_type)
{
    pthread_mutex_lock(&g_task_config_mutex);
    g_task_config.cpu_type = cpu_type;
    pthread_mutex_unlock(&g_task_config_mutex);

    return 0;
}

E_CPU_TYPE get_task_config_cpu_type()
{
    E_CPU_TYPE cpu_type = CPU_NONE;

    pthread_mutex_lock(&g_task_config_mutex);
    cpu_type = g_task_config.cpu_type;
    pthread_mutex_unlock(&g_task_config_mutex);

    return cpu_type;
}

int set_task(unsigned int task_id, S_TASK *task)
{
    pthread_mutex_lock(&g_task_config_mutex);
    g_task_config.tasks[task_id] = *task;
    pthread_mutex_unlock(&g_task_config_mutex);

    return 0; 
}

int get_task(unsigned int task_id, S_TASK *task)
{
    pthread_mutex_lock(&g_task_config_mutex);
    *task = g_task_config.tasks[task_id];
    pthread_mutex_unlock(&g_task_config_mutex);

    return 0; 
}

int reset_task_config()
{
    pthread_mutex_lock(&g_task_config_mutex);
    memset(&g_task_config, 0, sizeof(g_task_config));
    pthread_mutex_unlock(&g_task_config_mutex);

    return 0;
}



void print_task_config(char *message, S_TASK_CONFIG *print_config)
{
    S_TASK_CONFIG config = *print_config;

}

int init_task_resource_function()
{
    unsigned int task_id1 = 0;
    unsigned int task_id2 = 1;

    init_task_resource(task_id1);
    init_task_resource(task_id2);

    return 0;
}

int init_task_resource(unsigned int task_id)
{
    int ret ;
    pthread_t pid;
    S_TASK task = {0};

    get_task(task_id, &task);

    if(task.venc_config.enable == true)
    {
        S_TASK_PACK_PROC_ARG_BAK * s_task_proc = (S_TASK_PACK_PROC_ARG_BAK *)malloc(sizeof (S_TASK_PACK_PROC_ARG_BAK));
        if(s_task_proc == NULL)
        {
            debug("s_task_proc is Null\n");
        }
        s_task_proc->task_id = task.id;
        ret = pthread_create(&pid, NULL, video_venc_proc, (void*)s_task_proc);
        if(ret !=0)
        {
            return -1;
        }
    }

    if(task.aenc_config.enable == true)
    {
        S_TASK_PACK_PROC_ARG_BAK * s_task_proc = (S_TASK_PACK_PROC_ARG_BAK *)malloc(sizeof (S_TASK_PACK_PROC_ARG_BAK));
        if(s_task_proc == NULL)
        {
            debug("s_task_proc is Null\n");
        }
        s_task_proc->task_id = task.id;
        ret = pthread_create(&pid, NULL, audio_venc_proc, (void*)s_task_proc);
        if(ret !=0)
        {
            return -1;
        }
    }

    S_TASK_PACK_PROC_ARG *task_pack_proc_arg = (S_TASK_PACK_PROC_ARG *)malloc(sizeof(S_TASK_PACK_PROC_ARG));
    if (task_pack_proc_arg == NULL)
    {
        debug("[TASK TEST] malloc task pack proc arg error\n");
        return -1;
    }
    task_pack_proc_arg->task_id = task_id;
    ret = pthread_create(&pid, NULL, dequeue_data_proc, (void *)task_pack_proc_arg);
    if (ret != 0)
    {
        debug("pthread_create tcp_tunnel_accept_proc error");
        return -1;
    }

#if 0
    for (int i = 0; i < task.url_map.url_count ; i++)
    {
        S_GROUP *group1 = (S_GROUP *)malloc(sizeof (S_GROUP));
        if(group1 == NULL)
        {
            debug("malloc group1 error\n");
            return -1;
        }
        group1->url_id = task.url_map.url_id_arr[i];
        get_url_addr(group1->url_id, group1->url_addr);
        group1->url_type = get_url_type(group1->url_id);
        ret = pthread_create(&pid, NULL, handle_url_video_data_proc, (void *)group1);
        if(ret != 0)
        {
            debug("[handle_url_data_proc] malloc task pack proc arg error\n");
            return -1;
        }

        S_GROUP *group2 = (S_GROUP *)malloc(sizeof (S_GROUP));
        if(group2 == NULL)
        {

        }

#if 1
        S_TASK_PACK_PROC_ARG *task_pack_proc_arg = (S_TASK_PACK_PROC_ARG *)malloc(sizeof(S_TASK_PACK_PROC_ARG));
        if (task_pack_proc_arg == NULL)
        {
            debug("[TASK TEST] malloc task pack proc arg error\n");
            return -1;
        }
        task_pack_proc_arg->task_id = task_id;
        task_pack_proc_arg->url_map = task.url_map;
        ret = pthread_create(&pid, NULL, dequeue_data_proc, (void *)task_pack_proc_arg);
        if (ret != 0)
        {
            debug("pthread_create tcp_tunnel_accept_proc error");
            return -1;
        }
#endif
    }
#endif

    return 0;
}

















