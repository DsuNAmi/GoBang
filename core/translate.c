#include "translate.h"
#include <ctype.h>

/* Simple english->chinese dictionary for demo purposes */
typedef struct tagDictPair
{
    const CHAR * en;
    const CHAR * zh;
}DICT_PAIR;

static DICT_PAIR g_dict[] = {
    {"hello", "你好"},
    {"world", "世界"},
    {"i", "我"},
    {"you", "你"},
    {"love", "爱"},
    {"good", "好"},
    {"morning", "早上"},
    {"night", "晚上"},
    {"how", "怎么"},
    {"are", "是"},
    {"thank", "谢谢"},
    {"thanks", "谢谢"},
    {"yes", "是"},
    {"no", "不"},
    {NULL, NULL}
};

/* helper: lowercase copy */
static void strtolower(const CHAR * src, CHAR * dst, size_t maxlen)
{
    size_t i = 0;
    for (; i + 1 < maxlen && src[i] != '\0'; i++)
    {
        dst[i] = (CHAR)tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}


ULONG GetLanguageType(IN CHAR * pszInput, OUT T_TranslateContext * pstContext)
{
    ULONG ulRet = COMMAND_SUCCEED;
    if (NULL == pszInput || NULL == pstContext)
    {
        ulRet = COMMAND_FAILED;
        return ulRet;
    }

    /* find last token (language type) */
    size_t len = strlen(pszInput);
    if (len == 0)
    {
        ulRet = COMMAND_FAILED;
        return ulRet;
    }

    /* copy input to context first */
    GO_STRNCPY(pstContext->szPreText, pszInput, T_MAX_TEXT_LENGTH - 1);
    pstContext->szPreText[T_MAX_TEXT_LENGTH - 1] = '\0';

    /* trim trailing spaces and newline */
    while (len > 0 && (pstContext->szPreText[len - 1] == '\n' || pstContext->szPreText[len - 1] == '\r' || pstContext->szPreText[len - 1] == ' '))
    {
        pstContext->szPreText[len - 1] = '\0';
        len--;
    }

    /* find last space to split language token */
    char * last_space = strrchr(pstContext->szPreText, ' ');
    if (last_space == NULL)
    {
        pstContext->eSourceLanguageType = LANGUAGE_UNKNOWN;
        return ulRet;
    }

    CHAR szLang[T_MAX_TEXT_LENGTH] = {0};
    strncpy(szLang, last_space + 1, T_MAX_TEXT_LENGTH - 1);
    szLang[T_MAX_TEXT_LENGTH - 1] = '\0';

    /* remove language token from pretext */
    *last_space = '\0';

    /* normalize lang */
    for (size_t i = 0; szLang[i]; i++) szLang[i] = (CHAR)tolower((unsigned char)szLang[i]);

    if (0 == strcmp(szLang, "en") || 0 == strcmp(szLang, "en-us") || 0 == strcmp(szLang, "english") || 0 == strcmp(szLang, "english_us") || 0 == strcmp(szLang, "english-us") || 0 == strcmp(szLang, "us") )
    {
        pstContext->eSourceLanguageType = LANGUAGE_ENGLISH_US;
    }
    else if (0 == strcmp(szLang, "en-uk") || 0 == strcmp(szLang, "uk") || 0 == strcmp(szLang, "english_uk") || 0 == strcmp(szLang, "english-uk"))
    {
        pstContext->eSourceLanguageType = LANGUAGE_ENGLISH_UK;
    }
    else if (0 == strcmp(szLang, "zh") || 0 == strcmp(szLang, "chinese"))
    {
        pstContext->eSourceLanguageType = LANGUAGE_CHINESE;
    }
    else if (0 == strcmp(szLang, "ja") || 0 == strcmp(szLang, "japanese"))
    {
        pstContext->eSourceLanguageType = LANGUAGE_JAPANESE;
    }
    else if (0 == strcmp(szLang, "ko") || 0 == strcmp(szLang, "korean"))
    {
        pstContext->eSourceLanguageType = LANGUAGE_KOREAN;
    }
    else
    {
        pstContext->eSourceLanguageType = LANGUAGE_UNKNOWN;
    }

    return ulRet;
}


ULONG Translate(IN CHAR * pszInput, IN T_LANGUAGE_TYPE eTargetLanguageType, OUT CHAR * pszOutput)
{
    ULONG ulRet = COMMAND_SUCCEED;
    T_TranslateContext stContext;

    if (NULL == pszOutput || NULL == pszInput)
    {
        GO_Printf("Translate: Invalid pointer.\n");
        return COMMAND_FAILED;
    }

    GO_INIT_STRUC(stContext);

    stContext.eTargetLanguageType = eTargetLanguageType;
    ulRet = GetLanguageType(pszInput, &stContext);
    if (COMMAND_SUCCEED != ulRet)
    {
        GO_Printf("Translate: GetLanguageType failed.\n");
        return COMMAND_FAILED;
    }

    /* Currently only support English -> Chinese */
    if (stContext.eSourceLanguageType == LANGUAGE_ENGLISH_US || stContext.eSourceLanguageType == LANGUAGE_ENGLISH_UK)
    {
        /* word by word translation */
        CHAR tmp[T_MAX_TEXT_LENGTH] = {0};
        size_t out_len = 0;
        CHAR word[T_MAX_TEXT_LENGTH];
        size_t i = 0, w = 0;

        /* tokenize by spaces and simple punctuation */
        const CHAR * p = stContext.szPreText;
        while (*p != '\0')
        {
            /* skip spaces */
            while (*p == ' ') p++;
            if (*p == '\0') break;

            /* collect a word */
            w = 0;
            while (*p != '\0' && *p != ' ' && *p != ',' && *p != '.' && *p != '!' && *p != '?')
            {
                if (w + 1 < sizeof(word)) word[w++] = *p;
                p++;
            }
            word[w] = '\0';

            /* lowercase copy */
            CHAR lword[T_MAX_TEXT_LENGTH];
            strtolower(word, lword, sizeof(lword));

            /* lookup */
            const CHAR * zh = NULL;
            for (i = 0; g_dict[i].en != NULL; i++)
            {
                if (0 == strcmp(g_dict[i].en, lword))
                {
                    zh = g_dict[i].zh;
                    break;
                }
            }

            if (zh)
            {
                size_t need = strlen(zh);
                if (out_len + need + 2 < T_MAX_TEXT_LENGTH)
                {
                    if (out_len != 0)
                    {
                        tmp[out_len++] = ' ';
                    }
                    strncpy(&tmp[out_len], zh, need);
                    out_len += need;
                    tmp[out_len] = '\0';
                }
            }
            else
            {
                /* unknown word: copy original */
                size_t need = strlen(word);
                if (need > 0 && out_len + need + 2 < T_MAX_TEXT_LENGTH)
                {
                    if (out_len != 0) tmp[out_len++] = ' ';
                    strncpy(&tmp[out_len], word, need);
                    out_len += need;
                    tmp[out_len] = '\0';
                }
            }

            /* skip punctuation */
            while (*p == ',' || *p == '.' || *p == '!' || *p == '?') p++;
        }

        strncpy(pszOutput, tmp, T_MAX_TEXT_LENGTH - 1);
        pszOutput[T_MAX_TEXT_LENGTH - 1] = '\0';

        return ulRet;
    }
    else
    {
        GO_Printf("Translate: source language not supported yet.\n");
        return COMMAND_FAILED;
    }
}


ULONG GetSourceText(OUT CHAR * pszSourceText)
{
    ULONG ulRet = COMMAND_SUCCEED;
    CHAR * pszTemp = NULL;

    if (NULL == pszSourceText)
    {
        return COMMAND_FAILED;
    }

    GO_MALLOC(pszTemp, CHAR, T_MAX_TEXT_LENGTH);
    if (NULL == pszTemp)
    {
        GO_Printf("GetSourceText: malloc failed.\n");
        ulRet = COMMAND_FAILED;
        return ulRet;
    }

    if (NULL == GO_FGETS(pszTemp, T_MAX_TEXT_LENGTH, stdin))
    {
        GO_Printf("GetSourceText: FGETS failed.\n");
        ulRet = COMMAND_FAILED;
        GO_FREE(pszTemp);
        return ulRet;
    }

    /* remove trailing newline */
    size_t len = strlen(pszTemp);
    if (len > 0 && (pszTemp[len - 1] == '\n' || pszTemp[len - 1] == '\r'))
    {
        pszTemp[len - 1] = '\0';
    }

    strncpy(pszSourceText, pszTemp, T_MAX_TEXT_LENGTH - 1);
    pszSourceText[T_MAX_TEXT_LENGTH - 1] = '\0';

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
    CHAR szOutput[T_MAX_TEXT_LENGTH] = {0};

    /* step 1 : waiting for user's input */
    ulRet = GetSourceText(szSourceText);
    if (COMMAND_SUCCEED != ulRet)
    {
        GO_Printf("T_main: GetSourceText failed.\n");
        return ulRet;
    }

    GO_Printf("T_main: Source Text: %s\n", szSourceText);

    ulRet = Translate(szSourceText, LANGUAGE_CHINESE, szOutput);
    if (COMMAND_SUCCEED != ulRet)
    {
        GO_Printf("T_main: Translate failed.\n");
        return ulRet;
    }

    GO_Printf("T_main: Translated Text: %s\n", szOutput);
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