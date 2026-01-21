#include "../formal/revar.h"
#include "../formal/basic.h"
#include "translate.h"
#include <stdio.h>


ULONG GetLanguageType(IN CHAR * pszInput, OUT T_TranslateContext * pstContext)
{
    ULONG ulRet = COMMAND_SUCCEED;
    // check the input language type
    return ulRet;
}


ULONG Translate(IN CHAR * pszInput, IN T_LANGUAGE_TYPE eTargetLanguageType, OUT CHAR * pszOutput)
{
    ULONG ulRet = COMMAND_SUCCEED;
    T_TranslateContext stContext;

    if (NULL == pszOutput)
    {
        GO_Printf("Translate: Output pointer is NULL.\n");
        ulRet = COMMAND_FAILED;
        return ulRet;
    }
    
    GO_INIT_STRUC(stContext);

    stContext.eTargetLanguageType = eTargetLanguageType;
    ulRet = GetLanguageType(pszInput, &stContext);
    if (COMMAND_SUCCEED != ulRet)
    {
        GO_Printf("Translate: GetLanguageType failed.\n");
        ulRet = COMMAND_FAILED;
        return ulRet;
    }
    

    // Fake translation logic
    pszOutput = "There is your translated text.";
    return ulRet;
}