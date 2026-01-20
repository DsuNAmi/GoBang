#ifndef __COMMANDLINE_H__
#define __COMMANDLINE_H__

#include "../formal/basic.h"


enum MODULE_CHOICE_T
{
    MODULE_CHOICE_EXIT = 0,
    MODULE_CHOICE_TRANSLATE = 1,
    MODULE_CHOICE_DEFAULT1 = 2,
    MODULE_CHOICE_DEFAULT2 = 3
};

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