#ifndef __BASIC_H__
#define __BASIC_H__

#include <stdio.h>

#define GO_Scanf(format, ...) \
    scanf(format, ##__VA_ARGS__)

#define GO_Printf(format, ...) \
    printf(format, ##__VA_ARGS__)

#endif