/* Is Empty or Full */
#include <stdio.h>
#include "TemplateStack.h"

TemplateStack_inline(long)

int
main(void)
{
    Stack(long) stack = newStack(long, 3);
    if (stackBufferIsNull(long, &stack))
    {
        fprintf(stderr, "Failed Memory Allocation\n");
        return 1;
    }

    if (!stackIsEmpty(long, &stack))
        goto stackIsEmpty_error;
    if (stackIsFull(long, &stack))
        goto stackIsFull_error;

    stackPush(long, &stack, 703888L);
    stackPush(long, &stack, 333444L);

    if (stackIsEmpty(long, &stack))
        goto stackIsEmpty_error;
    if (stackIsFull(long, &stack))
        goto stackIsFull_error;

    stackPush(long, &stack, 888333L);

    if (stackIsEmpty(long, &stack))
        goto stackIsEmpty_error;
    if (!stackIsFull(long, &stack))
        goto stackIsFull_error;

    deleteStack(long, &stack);
    return 0;

stackIsEmpty_error:
    fprintf(stderr, "stackIsEmpty does not work\n");
    goto error_exit;

stackIsFull_error:
    fprintf(stderr, "stackIsEmpty does not work\n");
    goto error_exit;

error_exit:
    deleteStack(long, &stack);
    return 1;
}
