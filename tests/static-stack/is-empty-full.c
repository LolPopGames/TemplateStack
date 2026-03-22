/* Is Empty or Full */
#include <stdio.h>
#include "TemplateStack.h"

StaticStack_inline(LONG3, long, 3)

int
main(void)
{
    Stack(LONG3) stack = {0};

    if (!stackIsEmpty(LONG3)(&stack))
        goto stackIsEmpty_error;
    if (stackIsFull(LONG3)(&stack))
        goto stackIsFull_error;

    stackPush(LONG3)(&stack, 703888L);
    stackPush(LONG3)(&stack, 333444L);

    if (stackIsEmpty(LONG3)(&stack))
        goto stackIsEmpty_error;
    if (stackIsFull(LONG3)(&stack))
        goto stackIsFull_error;

    stackPush(LONG3)(&stack, 888333L);

    if (stackIsEmpty(LONG3)(&stack))
        goto stackIsEmpty_error;
    if (!stackIsFull(LONG3)(&stack))
        goto stackIsFull_error;

    return 0;

stackIsEmpty_error:
    fprintf(stderr, "stackIsEmpty does not work\n");
    return 1;

stackIsFull_error:
    fprintf(stderr, "stackIsEmpty does not work\n");
    return 1;
}
