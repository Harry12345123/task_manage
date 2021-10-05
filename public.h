#ifndef _PUBLIC_H
#define _PUBLIC_H

#include <stdbool.h>

typedef enum
{
    VI_HDMI = 0,
    VI_SDI,
}E_VI_TYPE;

typedef enum
{
    AI_HDMI = 0,
    AI_SDI,
    AI_CANON,
}E_AI_TYPE;

typedef struct
{
    int scan_type;
    unsigned int num;
    unsigned int den;
}S_VI_IOCTL_ATTR;

typedef struct
{
    unsigned int id;
    E_VI_TYPE type; 
    //VI_CHN_ATTR_S attr;
    S_VI_IOCTL_ATTR ioctl_attr;
    bool enable;
}S_VI_CONFIG;

typedef struct
{
    unsigned int id;
    E_AI_TYPE type;  
    //AI_CHN_ATTR_S attr;
    bool enable;
}S_AI_CONFIG;

typedef struct
{
    unsigned int id;
    //RGA_ATTR_S attr;
    bool enable;
}S_RGA_CONFIG;

typedef struct
{
    unsigned int id;
    //VENC_CHN_ATTR_S attr;
    bool enable;
}S_VENC_CONFIG;

typedef struct
{
    unsigned int id;
    //AENC_CHN_ATTR_S attr;
    bool enable;
}S_AENC_CONFIG;

typedef enum
{
    P_SCAN_TYPE,
    I_SCAN_TYPE,
    PSF_SCAN_TYPE
}E_VIDEO_SCAN_TYPE;

#endif
