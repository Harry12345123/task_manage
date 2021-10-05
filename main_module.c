#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "task_manage.h"
#include "task_queue.h"
#include "debug.h"
#include "task_test.h"
#include "task_queue.h"
#include "video_queue.h"
#include "audio_queue.h"

int main()
{
    init_task_manage_function();
    init_task_queue_function();

#if 0
    init_video_queue_function();
    init_audio_queue_function();
#endif

    create_task_config();

    init_task_resource_function();

#if 1
    while(1)
    {
       sleep(50);
    }
#endif
    return 0;
}
