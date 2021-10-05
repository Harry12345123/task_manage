#ifndef _TASK_CONFIG_H
#define _TASK_CONFIG_H

#define MAX_TASK_NUM 20
#define MAX_DECODE_TASK_NUM 3

typedef enum
{  
    TASK_NONE = 0,
    TASK_INIT,
    TASK_STARTUP,
    TASK_RECONNECT,
}E_TASK_STATUS;

#endif
