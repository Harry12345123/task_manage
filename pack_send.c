#include <stdbool.h>
#include "pack_send.h"
#include "pack_handle.h"
#include "queue.h"
#include "debug.h"


int send_task_config_pack()
{
    int ret = create_task_config_pack();
    return ret;
}

