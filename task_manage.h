#ifndef _TASK_MANAGE_H
#define _TASK_MANAGE_H

#include <stdbool.h>
#include "config.h"
#include "task_config.h"
#include "public.h"

typedef struct
{
    unsigned int id;
    unsigned int random_value;
    S_VI_CONFIG vi_config;
    S_AI_CONFIG ai_config;
    S_RGA_CONFIG rga_config;
    S_VENC_CONFIG venc_config;
    S_AENC_CONFIG aenc_config;
    E_TASK_STATUS status;

}S_TASK;

typedef struct
{
    unsigned int id; 
    unsigned int random_value;
    E_CPU_TYPE cpu_type;
    unsigned short task_num;
    union{
        S_TASK tasks[MAX_TASK_NUM];
    };
}S_TASK_CONFIG;



int init_task_manage_function();
int set_task_config(S_TASK_CONFIG *config);
S_TASK_CONFIG get_task_config();
unsigned int set_task_config_id(unsigned int id);
unsigned int get_task_config_id();
int set_task_config_random_value(unsigned int random_value);
unsigned int get_task_config_random_value();
unsigned int set_task_config_cpu_type(E_CPU_TYPE cpu_type);
E_CPU_TYPE get_task_config_cpu_type();

int set_task(unsigned int task_id, S_TASK *task);
int get_task(unsigned int task_id, S_TASK *task);

void print_task_config(char *message, S_TASK_CONFIG *print_config);

int init_task_resource_function();
int init_task_resource(unsigned int task_id);


#endif
