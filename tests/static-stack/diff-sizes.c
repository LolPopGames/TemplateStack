/* Different Sizes For One Type */
#include <stdio.h>
#include "TemplateStack.h"

StaticStack_inline(INT10, int, 10)
StaticStack_inline(INT5, int, 5)

int
main(void)
{
    int i;
    Stack(INT10) st10 = {0}, st10_copy;
    Stack(INT5) st5 = {0};

    for (i=0; i<5; i++)
    {
        stackPush(INT5, &st5, i*10);
        stackPush(INT10, &st10, i*10);
    }

    if (!stackIsFull(INT5, &st5) || stackIsFull(INT10, &st10))
        return 1;

    st10_copy = st10;

    if (stackIsFull(INT10, &st10_copy))
        return 1;

    return 0;
}
