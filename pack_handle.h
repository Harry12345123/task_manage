#ifndef _PACK_HANDLE_H
#define _PACK_HANDLE_H
#include <stdbool.h>
#include "config.h"

typedef struct
{
    unsigned int config_id;
    unsigned int config_random_value;
    E_CPU_TYPE cpu_type;
    unsigned int task_id;
    unsigned int task_random_value;

}S_TASK_PACK_PROC_ARG_BAK;

int create_task_config_pack();
int create_decode_task_config_pack();
int create_push_oper_pack(unsigned int task_id, bool enable);

#endif
