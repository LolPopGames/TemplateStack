/* Initialization Test */
#include <stdio.h>
#include "TemplateStack.h"

TemplateStack_inline(int)

int
main(void)
{
    Stack(int) stack = newStack(int, 5);
    if (stackBufferIsNull(int, &stack))
    {
        fprintf(stderr, "Failed Memory Allocation\n");
        return 1;
    }

    deleteStack(int, &stack);
    return 0;
}
