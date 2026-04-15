/* Push-Pop-Peek Test */
#include <stdio.h>
#include "TemplateStack.h"

TemplateStack_inline(int)

int
main(void)
{
    int value;
    Stack(int) stack = newStack(int, 5);

    if (stackBufferIsNull(int, &stack))
    {
        fprintf(stderr, "Failed Memory Allocation\n");
        return 1;
    }

    stackPush(int, &stack, 555);
    stackPush(int, &stack, 777);
    stackPush(int, &stack, -99);

    value = stackPeek(int, &stack);
    if (value != -99)
        goto stackPeek_error;

    /* testing stackPeek again */
    value = stackPeek(int, &stack);
    if (value != -99)
        goto stackPeek_error;

    printf("value == %d\n", value);

    if (stackPop(int, &stack) != -99)
        goto stackPop_error;

    value = stackPeek(int, &stack);

    if (value != 777)
        goto stackPeek_error;

    if (stackPop(int, &stack) != 777)
        goto stackPop_error;

    if (stackPop(int, &stack) != 555)
        goto stackPop_error;

    /* check for zero-value */
    if (stackPop(int, &stack) != 0)
        goto stackPop_error;

    /* another zero-value check */
    if (stackPeek(int, &stack) != 0)
        goto stackPeek_error;

    stackPush(int, &stack, 389388);

    deleteStack(int, &stack);
    return 0;

stackPeek_error:
    fprintf(stderr, "stackPeek does not work\n");
    goto error_exit;

stackPop_error:
    fprintf(stderr, "stackPop does not work\n");
    goto error_exit;

error_exit:
    deleteStack(int, &stack);
    return 1;
}
