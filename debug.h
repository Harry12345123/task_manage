#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdarg.h>
#include <stdio.h>

#define DEBUG

#ifdef  DEBUG
  #define debug(...)  printf(__VA_ARGS__)
#else
  #define debug(...)
#endif

#endif
