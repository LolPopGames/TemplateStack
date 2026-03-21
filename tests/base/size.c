/* Size & Buffer Size */
#include <stdio.h>
#include "TemplateStack.h"

TemplateStack_inline(double)

int
main(void)
{
    int i;
    Stack(double) stack = newStack(double)(30);

    if (stackBufferIsNull(double)(&stack))
    {
        fprintf(stderr, "Failed Memory Allocation");
        return 1;
    }

    if (stackBufferSize(double)(&stack) != 30)
        goto stackBufferSize_error;

    if (stackSize(double)(&stack) != 0)
        goto stackSize_error;

    stackPush(double)(&stack, 43.22);

    if (stackBufferSize(double)(&stack) != 30)
        goto stackBufferSize_error;

    if (stackSize(double)(&stack) != 1)
        goto stackSize_error;

    stackPop(double)(&stack);

    if (stackBufferSize(double)(&stack) != 30)
        goto stackBufferSize_error;

    if (stackSize(double)(&stack) != 0)
        goto stackSize_error;

    for (i=0; i<30; i++)
    {
        stackPush(double)(&stack, i * 2.4582);
    }

    if (stackBufferSize(double)(&stack) != 30)
        goto stackBufferSize_error;

    if (stackSize(double)(&stack) != 30)
        goto stackSize_error;

    deleteStack(double)(&stack);

    return 0;

stackSize_error:
    fprintf(stderr, "stackSize does not work\n");
    goto error_exit;

stackBufferSize_error:
    fprintf(stderr, "stackBufferSize does not work\n");
    goto error_exit;

error_exit:
    deleteStack(double)(&stack);
    return 1;
}
