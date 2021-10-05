#include "pack_handle.h"
#include "video_venc.h"
#include "task_queue.h"
#include "debug.h"


extern BASE_QUEUE g_tunnel_queue;

void *video_venc_proc(void *args)
{
    pthread_detach(pthread_self());
    debug("video_venc_start...\n");

    S_TASK_PACK_PROC_ARG_BAK  s_task_proc = *(S_TASK_PACK_PROC_ARG_BAK *)args;
    free(args);

    unsigned int total_len ;
    unsigned int header_len = sizeof (S_HEADER_DATA_BAK);
    unsigned int frame_size ;

    S_DATA_TUNNEL * data_pack = NULL;
    char buf[20];
    sprintf(buf, "task_id = %d HelloVideo", s_task_proc.task_id);
    frame_size = strlen(buf);

    while (1)
    {
       data_pack = (S_DATA_TUNNEL *)malloc(sizeof (S_DATA_TUNNEL));
       data_pack->header.seq = 12;
       data_pack->header.identify_code = 12345;
       total_len = frame_size + header_len;
       data_pack->header.total_len = total_len;
       data_pack->header.pack.frame_pack.type = VIDEO_TYPE;

       memset(data_pack->buffer, 0, MAX_BUFFER_SIZE);
       memcpy(data_pack->buffer, &(data_pack->header), header_len);
       memcpy(data_pack->buffer + header_len,buf, frame_size);
       enqueue_task_queue(&data_pack->head, s_task_proc.task_id);
    }
    return NULL;
}
