/* VA newStack Call */
/* This is a C99+ test only, because only C99+ supports VA macros */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

#include "TemplateStack.h"
#include <stdio.h>

TemplateStack_inline(int)

int
main(void)
{
    Stack(int) stack;

    stack = newStack(int);
    if (stackBufferIsNull(int, &stack))
    {
        fprintf(stderr, "Failed Memory Allocation\n");
        return 1;
    }

    printf("%lu\n", stackBufferSize(int, &stack));

    return 0;
}

#else /* C89 */
int
main(void) { return 0; }
#endif
