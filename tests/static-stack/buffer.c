/* Buffer Managment */
#include <stdio.h>
#include "TemplateStack.h"

StaticStack_inline(INT8, int, 8)

int
main(void)
{
    int value;
    Stack(INT8) stack = {0};

    stackPush(INT8, &stack, 10);
    stackPush(INT8, &stack, 20);
    stackPush(INT8, &stack, 30);
    stackPush(INT8, &stack, 40);

    /* Check for every value */
    value = stackPeekAt(INT8, &stack, 0);
    if (value != 40) goto stackPeekAt_error;
    printf("0: %d\n", value);

    value = stackPeekAt(INT8, &stack, 1);
    if (value != 30) goto stackPeekAt_error;
    printf("1: %d\n", value);

    value = stackPeekAt(INT8, &stack, 2);
    if (value != 20) goto stackPeekAt_error;
    printf("2: %d\n", value);

    value = stackPeekAt(INT8, &stack, 3);
    if (value != 10) goto stackPeekAt_error;
    printf("3: %d\n", value);
    
    value = stackPeekAt(INT8, &stack, 4);
    if (value != 0) goto stackPeekAt_error;
    printf("4 (out of bounce): %d\n", value);

    stackReverse(INT8, &stack);

    /* Check for every value after reversing */
    if (stackPeekAt(INT8, &stack, 0) != 10)
        goto stackReverse_error;

    if (stackPeekAt(INT8, &stack, 1) != 20)
        goto stackReverse_error;

    if (stackPeekAt(INT8, &stack, 2) != 30)
        goto stackReverse_error;

    if (stackPeekAt(INT8, &stack, 3) != 40)
        goto stackReverse_error;

    stackClear(INT8, &stack);

    /* checks for stackClear */
    if (stackSize(INT8, &stack) != 0)
        goto stackClear_error;

    if (stackPeek(INT8, &stack) != 0)
        goto stackClear_error;

    if (!stackIsEmpty(INT8, &stack))
        goto stackClear_error;

    return 0;

stackPeekAt_error:
    fprintf(stderr, "stackPeekAt does not work\n");
    return 1;

stackClear_error:
    fprintf(stderr, "stackClear does not work\n");
    return 1;

stackReverse_error:
    fprintf(stderr, "stackReverse does not work\n");
    return 1;
}
