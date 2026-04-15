/* Size */
#include <stdio.h>
#include "TemplateStack.h"

StaticStack_inline(DOUBLE30, double, 30)

int
main(void)
{
    int i;
    Stack(DOUBLE30) stack = {0};

    if (stackSize(DOUBLE30, &stack) != 0)
        goto stackSize_error;

    stackPush(DOUBLE30, &stack, 43.22);

    if (stackSize(DOUBLE30, &stack) != 1)
        goto stackSize_error;

    stackPop(DOUBLE30, &stack);

    if (stackSize(DOUBLE30, &stack) != 0)
        goto stackSize_error;

    for (i=0; i<30; i++)
    {
        stackPush(DOUBLE30, &stack, i * 2.4582);
    }

    if (stackSize(DOUBLE30, &stack) != 30)
        goto stackSize_error;

    return 0;

stackSize_error:
    fprintf(stderr, "stackSize does not work\n");
    return 1;
}
