#include "basic.h"

ULONG GO_SAFE_FGETS(OUT INT *iResult)
{
    ULONG ulRet = COMMAND_SUCCEED;
    CHAR szBuffer[GO_MAX_TEXT_LENGTH];
    ULONG ulNumberLength = 0;
    CHAR szNumber[GO_MENU_LENGTH + 1];

    GO_FGETS(szBuffer, GO_MAX_TEXT_LENGTH, stdin);
    if (ZERO_INT == strlen(szBuffer))
    {
        GO_Printf("GO_SAFE_FGETS: FGETS failed.\n");
        ulRet = COMMAND_FAILED;
        return ulRet;
    }

    while (szBuffer[ulNumberLength] >= '0' && 
           szBuffer[ulNumberLength] <= '9')
    {
        ulNumberLength++;
    }

    if (ulNumberLength <= GO_MENU_LENGTH)
    {
        GO_STRNCPY(szNumber, szBuffer, ulNumberLength);
        szNumber[ulNumberLength] = '\0';
        *iResult = atoi(szNumber);
    }
    else
    {
        GO_Printf("GO_SAFE_FGETS: Input number too large.\n");
        ulRet = COMMAND_FAILED;
        return ulRet;
    }

    return ulRet;
}