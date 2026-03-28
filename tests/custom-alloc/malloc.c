/* Malloc Replacement */
#include <stdio.h>
#define TEMPLATE_STACK_MALLOC malloc
#include "TemplateStack.h"

TemplateStack_inline(unsigned)
int
main(void)
{
    int i, stack_buffer_is_null, temp_buffer_is_null;
    unsigned j;
    Stack(unsigned) stack = newStack(unsigned)(5), temp_stack;
    if (stackBufferIsNull(unsigned)(&stack))
        goto memory_alloc_error;

    for (i=1; i<=5; i++)
        stackPush(unsigned)(&stack, 10*i);

    temp_stack = stackRealloc(unsigned)(&stack, 10);

    stack_buffer_is_null = stackBufferIsNull(unsigned)(&stack);
     temp_buffer_is_null = stackBufferIsNull(unsigned)(&temp_stack);

    /* if reallocation failed */
    if (temp_buffer_is_null && !stack_buffer_is_null)
    {
        deleteStack(unsigned)(&stack);
        goto memory_alloc_error;
    }
    /* if invalid stackRealloc */
    if (temp_buffer_is_null && stack_buffer_is_null)
        goto stackRealloc_error;

    stack = temp_stack;

    if (
        stackPeek(unsigned)(&stack) != 50 ||
        stackSize(unsigned)(&stack) != 5 ||
        stackBufferSize(unsigned)(&stack) != 10
    )
    {
        deleteStack(unsigned)(&stack);
        goto stackRealloc_error;
    }

    stack = stackRealloc(unsigned)(&stack, 3);
    if (
        stackPeek(unsigned)(&stack) != 30 ||
        stackSize(unsigned)(&stack) != 3 ||
        stackBufferSize(unsigned)(&stack) != 3
    )
    {
        deleteStack(unsigned)(&stack);
    }

    stackPushGrow(unsigned)(&stack, 400);
    if (stackBufferIsNull(unsigned)(&stack))
        goto memory_alloc_error;

    if (
        stackPeek(unsigned)(&stack) != 400 ||
        stackSize(unsigned)(&stack) != 4 ||
        stackBufferSize(unsigned)(&stack) != 6
    )
    {
        deleteStack(unsigned)(&stack);
        goto stackPushGrow_error;
    }

    temp_stack = stackDup(unsigned)(&stack);
    if (stackBufferIsNull(unsigned)(&temp_stack))
    {
        deleteStack(unsigned)(&stack);
        goto memory_alloc_error;
    }

    if (stackBufferIsNull(unsigned)(&stack))
    {
        deleteStack(unsigned)(&temp_stack);
        goto stackDup_error;
    }

    for (i=0, j=4; i<4; i++, j--)
    {
        if (j != 4)
        {
            if (stackPeekAt(unsigned)(&temp_stack, i) != j*10)
            {
                deleteStack(unsigned)(&temp_stack);
                deleteStack(unsigned)(&stack);
                goto stackDup_error;
            }
        }
        /* when j==4 */
        else if (stackPeekAt(unsigned)(&temp_stack, i) != j*100)
        {
            deleteStack(unsigned)(&temp_stack);
            deleteStack(unsigned)(&stack);
            goto stackDup_error;
        }
    }

    deleteStack(unsigned)(&temp_stack);
    deleteStack(unsigned)(&stack);

    return 0;

stackRealloc_error:
    fprintf(stderr, "stackRealloc does not work\n");
    return 1;

stackPushGrow_error:
    fprintf(stderr, "stackPushGrow does not work\n");
    return 1;

stackDup_error:
    fprintf(stderr, "stackDup does not work\n");
    return 1;

memory_alloc_error:
    fprintf(stderr, "Failed Memory Allocation\n");
    return 1;
}
