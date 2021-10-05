#include <stdlib.h>
#include <pthread.h>
#include "task_test.h"


int create_task_config()
{
    set_task_config_id(0);
    set_task_config_random_value(0);
    set_task_config_cpu_type(HISI_3519AV100);
    create_task1_config();
    create_task2_config();

    return 0;
}

int create_task1_config()
{
    S_TASK task = {0};
    task.id = 0;
    task.random_value = 0;
    task.status = TASK_INIT;

    task.vi_config.id = 0;
    task.vi_config.type = VI_HDMI;

    task.venc_config.id =0;
    task.venc_config.enable = true;

    task.aenc_config.id = 0;
    task.aenc_config.enable = true;

    set_task(task.id, &task);
    return 0;
}

int create_task2_config()
{
    S_TASK task = {0};
    task.id = 1;
    task.random_value = 1;
    task.status = TASK_INIT;

    task.vi_config.id = 1;
    task.vi_config.type = VI_HDMI;

    task.venc_config.id =1;
    task.venc_config.enable = true;

    task.aenc_config.id = 1;
    task.aenc_config.enable = true;

    set_task(task.id, &task);

    return 0;
}




void * dequeue_data_proc(void *args)
{
    pthread_detach(pthread_self());
    S_TASK_PACK_PROC_ARG s_task_proc = *(S_TASK_PACK_PROC_ARG *) args;
    free(args);

    S_DATA_TUNNEL * tunnel_pack = NULL;
    struct list_head * list = NULL;

    while (1)
    {
        list = dequeue_task_queue_timeout(s_task_proc.task_id, list);
        if (list != NULL)
        {
            tunnel_pack = list_entry(list, S_DATA_TUNNEL, head);
        }
        else
        {
            debug("[SEND] dequeue tunnel packet == NULL error\n");
            usleep(10 * 1000);
            continue;
        }

        if(tunnel_pack->header.pack.frame_pack.type == VIDEO_TYPE)
        {

            printf("task_id = %d video \n", s_task_proc.task_id);

#if 0
             for (int i = 0 ; i < s_task_proc.url_map.url_count; i++)
             {
                 S_FFMPEG_PACK * video_pack = makeup_ffmpeg_video_pack(tunnel_pack);

                 if(video_pack == NULL)
                 {
                    debug("[TASK][RV1126] makeup ffmpeg video pack error\n");
                 }
                 enqueue_url_video_queue(&video_pack->list, s_task_proc.url_map.url_id_arr[i]);
             }
#endif
        }

        else if (tunnel_pack->header.pack.frame_pack.type == AUDIO_TYPE)
        {
            printf("task_id = %d audio \n", s_task_proc.task_id);
#if 0
             for (int i = 0 ; i < s_task_proc.url_map.url_id_arr[i]; i++)
             {
                 S_FFMPEG_PACK * audio_pack = makeup_ffmpeg_video_pack(tunnel_pack);

                 if(audio_pack == NULL)
                 {
                    debug("[TASK][RV1126] makeup ffmpeg video pack error\n");
                 }
                 enqueue_url_audio_queue(&audio_pack->list, s_task_proc.url_map.url_id_arr[i]);
             }
#endif
        }

        if(tunnel_pack != NULL)
        {
            free(tunnel_pack);
            tunnel_pack = NULL;
        }
    }
    return NULL;
}

#if 0
void * handle_url_video_data_proc(void *args)
{
    pthread_detach(pthread_self());
    S_GROUP group = *(S_GROUP *) args;
    free(args);

    struct list_head * list_head = NULL;
    S_FFMPEG_PACK * ffmpeg_video_pack = NULL;

    while (1)
    {
       list_head = dequeue_url_video_queue_wait(group.url_id, list_head);
       if(list_head != NULL)
       {
           ffmpeg_video_pack = list_entry(list_head, S_FFMPEG_PACK, list);
       }
       else
       {
           return NULL;
       }

       printf("url_id = %d, url_addr =%s, ffmpeg_buffer = %s\n", group.url_id, group.url_addr, ffmpeg_video_pack->buffer);

       if(ffmpeg_video_pack != NULL)
       {
         free(ffmpeg_video_pack);
         ffmpeg_video_pack = NULL;
       }
    }
    return NULL;
}
#endif



