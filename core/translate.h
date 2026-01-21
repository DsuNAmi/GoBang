#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "../formal/revar.h"

#define T_MAX_TEXT_LENGTH 1024

typedef enum tagLanguageType
{
    LANGUAGE_ENGLISH_UK = 0,
    LANGUAGE_ENGLISH_US = 1,
    LANGUAGE_CHINESE = 2,
    LANGUAGE_JAPANESE = 3,
    LANGUAGE_KOREAN = 4,
    LANGUAGE_UNKNOWN
}T_LANGUAGE_TYPE;

typedef struct tagTranslateContext
{
    T_LANGUAGE_TYPE eSourceLanguageType;
    CHAR szPreText[T_MAX_TEXT_LENGTH];
    T_LANGUAGE_TYPE eTargetLanguageType;
    CHAR szPostText[T_MAX_TEXT_LENGTH];
}T_TranslateContext;

#endif // TRANSLATE_H