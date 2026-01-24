#include "translate.h"


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


ULONG GetSourceText(OUT CHAR * pszSourceText)
{
    ULONG ulRet = COMMAND_SUCCEED;
    CHAR * pszTemp = NULL;

    GO_MALLOC(pszTemp, CHAR, T_MAX_TEXT_LENGTH);
    if (NULL == pszTemp)
    {
        GO_Printf("GetSourceText: malloc failed.\n");
        ulRet = COMMAND_FAILED;
        return ulRet;
    }

    /* how to handle the input over size T_MAX_TEX_LENGTH? */
    GO_FGETS(pszTemp, T_MAX_TEXT_LENGTH, stdin);

    if (NULL == pszTemp)
    {
        GO_Printf("GetSourceText: FGETS failed.\n");
        ulRet = COMMAND_FAILED;
        GO_FREE(pszTemp);
        return ulRet;
    }

    GO_STRNCPY(pszSourceText, pszTemp, strlen(pszTemp) - 1);
    pszSourceText[strlen(pszTemp) - 1] = '\0';

    GO_FREE(pszTemp);
    return ulRet;
}





/**
 * @brief Translate功能的主函数入口
 *
 * @param 无参数 
 * @return ULONG ulRet 提示主控模块该翻译模块是否正常运行与退出
 */
ULONG T_main(VOID)
{
    ULONG ulRet = COMMAND_SUCCEED;
    CHAR szSourceText[T_MAX_TEXT_LENGTH] = {0};

    /* step 1 : waiting for user's input */
    ulRet = GetSourceText(szSourceText);
    if (COMMAND_SUCCEED != ulRet)
    {
        GO_Printf("T_main: GetSourceText failed.\n");
        return ulRet;
    }

    GO_Printf("T_main: Source Text: %s\n", szSourceText);
    
    return COMMAND_SUCCEED;
}

/**
 * @brief 对外接口
 *
 * @param 无 参数描述
 * @return ULONG ulRet 函数状态返回值
 */
ULONG TranslateFunction(VOID)
{
    return T_main();
}