#ifndef _TASK_DATA_PROC_H
#define _TASK_DATA_PROC_H

#include "config.h"

typedef struct
{
    unsigned int config_id;
    unsigned int config_random_value;
    E_CPU_TYPE cpu_type;
    unsigned int task_id;
    unsigned int task_random_value;

}S_TASK_PACK_PROC_ARG;

void *task_pack_proc(void *arg);

#endif
