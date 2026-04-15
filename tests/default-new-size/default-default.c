/* Default Definition Of Default New Size */
#include "TemplateStack.h"
#include <stdio.h>

TemplateStack_inline(int)

int
main(void)
{
    Stack(int) stack, stack2;
    int size1, size2;

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

    size1 = stackBufferSize(int, &stack);
    size2 = stackBufferSize(int, &stack2);

    if (size1 != size2)
    {
        fprintf(stderr, "Default new size does not work\n");

        deleteStack(int, &stack);
        deleteStack(int, &stack2);
        return 1;
    }

    printf("%lu\n", size1);
    printf("%lu\n", size2);

    deleteStack(int, &stack);
    deleteStack(int, &stack2);

    return 0;

failed_memory_alloc:
    fprintf(stderr, "Failed Memory Allocation\n");
    return 1;
}
