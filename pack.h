#ifndef _RV1126_PACK_H
#define _RV1126_PACK_H

#include <stdbool.h> 
#include "queue.h"

#define MAX_BUFFER_SIZE (2*1024 *1024)

typedef enum
{
    TASK_CONFIG_PACK = 0,
    TASK_CONFIG_ACK,
    PUSH_OPER_PACK,
    PUSH_OPER_ACK,
    FRAME_PACK,
    FRAME_ACK,
    NONE_PACK,
}S_PACK_TYPE;

typedef enum{
    PUSH_OK = 0,
    PUSH_ERROR,
}E_PUSH_OPER_STATUS;

typedef enum
{
    VIDEO_TYPE = 0,
    AUDIO_TYPE,
}E_FRAME_TYPE;

typedef struct
{
   unsigned int config_id; 
}S_TASK_CONFIG_PACK;

typedef struct
{
   unsigned int config_id; 
}S_TASK_CONFIG_ACK;

typedef struct
{
   unsigned int task_id; 
   bool enable;
}S_PUSH_OPER_PACK;

typedef struct
{
   unsigned int task_id; 
   E_PUSH_OPER_STATUS status;
}S_PUSH_OPER_ACK;

typedef struct
{
    unsigned int task_id;
    unsigned int seq;
    E_FRAME_TYPE type;
    union{
        //VENC_NALU_TYPE_E nalu_type;
        unsigned int audio_type;
    };
}S_RV1126_FRAME_PACK;

typedef struct
{
    unsigned int task_id;
    unsigned int seq;
    E_FRAME_TYPE type;
}S_FRAME_ACK;

typedef struct
{
    S_PACK_TYPE type;
    union{
        S_TASK_CONFIG_PACK config_pack;
        S_TASK_CONFIG_ACK config_ack;
        S_PUSH_OPER_PACK push_oper_pack;
        S_PUSH_OPER_ACK push_oper_ack;
        S_RV1126_FRAME_PACK frame_pack;
        S_FRAME_ACK frame_ack;
    };
}S_PACK;

typedef struct{
    unsigned int identify_code;
    unsigned int seq;
    union{
       S_PACK pack;
    };
    unsigned int total_len;
}S_HEADER_DATA_BAK;

typedef struct
{
    struct list_head head;
    S_HEADER_DATA_BAK header;
    unsigned char buffer[MAX_BUFFER_SIZE];
}S_DATA_TUNNEL;

void print_pack(S_PACK *pack);

#endif
