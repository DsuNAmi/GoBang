#ifndef __BASIC_H__
#define __BASIC_H__

#include "revar.h"
#include <stdio.h>


#define GO_MAX_TEXT_LENGTH 1024
#define GO_MENU_LENGTH 3

#define GO_Scanf(format, ...) \
    scanf(format, ##__VA_ARGS__)

#define GO_Printf(format, ...) \
    printf(format, ##__VA_ARGS__)

#define GO_DELETE_BUFFER() \
    do { \
        int tmp; \
        while ((tmp = getchar()) != '\n' && tmp != EOF); \
    } while(0)

#define GO_SCANF_CLEAN(format, ...) \
    do { \
        GO_Scanf(format, ##__VA_ARGS__); \
        GO_DELETE_BUFFER(); \
    } while(0)


extern ULONG GO_SAFE_FGETS(OUT INT *iResult);

#endif