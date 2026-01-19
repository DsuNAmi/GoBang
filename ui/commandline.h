#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__

#include "../formal/basic.h"

#define PRINT_MODULE_MENU() \
    do { \
        GO_Printf("===== GoBang =====\n"); \
        GO_Printf("1. Translate\n"); \
        GO_Printf("2. Default1\n"); \
        GO_Printf("3. Default2\n"); \
        GO_Printf("0. Exit\n"); \
        GO_Printf("=======================\n"); \
    } while(0)

#endif // __COMMANDLINE_H__