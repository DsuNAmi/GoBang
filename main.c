#include <stdio.h>

#include "formal/revar.h"
#include "ui/commandline.h"
#include "formal/basic.h"


VOID FunctionSelected(VOID)
{
    INT ichoice = 0;

    PRINT_MODULE_MENU();

    GO_Scanf("%d", &ichoice);



}

INT main(int argc, char *argv[])
{
    return 0;
}
