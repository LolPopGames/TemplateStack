/* Custom Default New Size */
#define TEMPLATE_STACK_DEFAULT_NEW_SIZE 20
#include "TemplateStack.h"
#include <stdio.h>

TemplateStack_inline(int)

int
main(void)
{
    Stack(int) stack, stack2;
    int size;

    stack = newStack(int, 0);
    if (stackBufferIsNull(int, &stack))
    {
        goto failed_memory_alloc;
    }

    stack2 = newStack(int, TEMPLATE_STACK_DEFAULT_NEW_SIZE);
    if (stackBufferIsNull(int, &stack2))
    {
        deleteStack(int, &stack);
        goto failed_memory_alloc;
    }

    size = stackBufferSize(int, &stack);
    if (size != 20)
    {
        goto invalid_size_error;
    }
    printf("%lu\n", size);

    size = stackBufferSize(int, &stack);
    if (size != 20)
    {
        goto invalid_size_error;
    }
    printf("%lu\n", size);

    deleteStack(int, &stack);
    deleteStack(int, &stack2);

    return 0;

invalid_size_error:
    deleteStack(int, &stack);
    deleteStack(int, &stack2);

    fprintf(stderr, "Default new size does not work\n");
    return 1;

failed_memory_alloc:
    fprintf(stderr, "Failed Memory Allocation\n");
    return 1;
}
