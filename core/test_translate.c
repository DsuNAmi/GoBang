#include <stdio.h>
#include <string.h>
#include "translate.h"

int main(void)
{
    CHAR out[T_MAX_TEXT_LENGTH] = {0};
    ULONG ret = Translate("hello world en", LANGUAGE_CHINESE, out);
    if (ret != COMMAND_SUCCEED)
    {
        printf("TEST FAILED: Translate returned error\n");
        return 1;
    }

    if (0 == strcmp(out, "你好 世界"))
    {
        printf("TEST PASSED: \"hello world en\" -> \"%s\"\n", out);
        return 0;
    }
    else
    {
        printf("TEST FAILED: unexpected output: %s\n", out);
        return 2;
    }
}
