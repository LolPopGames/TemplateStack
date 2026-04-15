/* Buffer Managment */
#include <stdio.h>
#include "TemplateStack.h"

TemplateStack_inline(int)

int
main(void)
{
    int value;
    Stack(int) stack = newStack(int, 8);
    if (stackBufferIsNull(int, &stack))
    {
        fprintf(stderr, "Failed Memory Allocation\n");
        return 1;
    }

    stackPush(int, &stack, 10);
    stackPush(int, &stack, 20);
    stackPush(int, &stack, 30);
    stackPush(int, &stack, 40);

    /* Check for every value */
    value = stackPeekAt(int, &stack, 0);
    if (value != 40) goto stackPeekAt_error;
    printf("0: %d\n", value);

    value = stackPeekAt(int, &stack, 1);
    if (value != 30) goto stackPeekAt_error;
    printf("1: %d\n", value);

    value = stackPeekAt(int, &stack, 2);
    if (value != 20) goto stackPeekAt_error;
    printf("2: %d\n", value);

    value = stackPeekAt(int, &stack, 3);
    if (value != 10) goto stackPeekAt_error;
    printf("3: %d\n", value);
    
    value = stackPeekAt(int, &stack, 4);
    if (value != 0) goto stackPeekAt_error;
    printf("4 (out of bounce): %d\n", value);

    stackReverse(int, &stack);

    /* Check for every value after reversing */
    if (stackPeekAt(int, &stack, 0) != 10)
        goto stackReverse_error;

    if (stackPeekAt(int, &stack, 1) != 20)
        goto stackReverse_error;

    if (stackPeekAt(int, &stack, 2) != 30)
        goto stackReverse_error;

    if (stackPeekAt(int, &stack, 3) != 40)
        goto stackReverse_error;

    stackClear(int, &stack);

    /* checks for stackClear */
    if (stackSize(int, &stack) != 0)
        goto stackClear_error;

    if (stackPeek(int, &stack) != 0)
        goto stackClear_error;

    if (!stackIsEmpty(int, &stack))
        goto stackClear_error;

    deleteStack(int, &stack);
    return 0;

stackPeekAt_error:
    fprintf(stderr, "stackPeekAt does not work\n");
    goto error_exit;

stackClear_error:
    fprintf(stderr, "stackClear does not work\n");
    goto error_exit;

stackReverse_error:
    fprintf(stderr, "stackReverse does not work\n");
    goto error_exit;

error_exit:
    deleteStack(int, &stack);
    return 1;
}
