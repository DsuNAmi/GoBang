#include <stdio.h>

#include "formal/revar.h"
#include "ui/commandline.h"
#include "formal/basic.h"
#include "core/translate.h"


VOID FunctionSelected(VOID)
{
    ULONG ulRet = COMMAND_SUCCEED;
    INT ichoice = 0;

    PRINT_MODULE_MENU();

    ulRet = GO_SAFE_FGETS(&ichoice);
    if (COMMAND_SUCCEED != ulRet)
    {
        GO_Printf("FunctionSelected: GO_SAFE_FGETS failed.\n");
        return;
    }

    switch (ichoice)
    {
        case MODULE_CHOICE_TRANSLATE:
            GO_Printf("You selected Translate module.\n");
            (VOID)TranslateFunction();
            break;
        case MODULE_CHOICE_DEFAULT1:
            GO_Printf("You selected Default1 module.\n");
            break;
        case MODULE_CHOICE_DEFAULT2:
            GO_Printf("You selected Default2 module.\n");
            break;
        case MODULE_CHOICE_EXIT:
            GO_Printf("Exiting program.\n");
            break;
        default:
            GO_Printf("Invalid choice. Please try again.\n");
            break;
    }
}

int main(int argc, char *argv[])
{
    FunctionSelected();
    return 0;
}
