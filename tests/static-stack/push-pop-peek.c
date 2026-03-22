/* Push-Pop-Peek Test */
#include <stdio.h>
#include "TemplateStack.h"

StaticStack_inline(INT5, int, 5)

int
main(void)
{
    int value;
    Stack(INT5) stack = {0};

    stackPush(INT5)(&stack, 555);
    stackPush(INT5)(&stack, 777);
    stackPush(INT5)(&stack, -99);

    value = stackPeek(INT5)(&stack);
    if (value != -99)
        goto stackPeek_error;

    /* testing stackPeek again */
    value = stackPeek(INT5)(&stack);
    if (value != -99)
        goto stackPeek_error;

    printf("value == %d\n", value);

    if (stackPop(INT5)(&stack) != -99)
        goto stackPop_error;

    value = stackPeek(INT5)(&stack);

    if (value != 777)
        goto stackPeek_error;

    if (stackPop(INT5)(&stack) != 777)
        goto stackPop_error;

    if (stackPop(INT5)(&stack) != 555)
        goto stackPop_error;

    /* check for zero-value */
    if (stackPop(INT5)(&stack) != 0)
        goto stackPop_error;

    /* another zero-value check */
    if (stackPeek(INT5)(&stack) != 0)
        goto stackPeek_error;

    stackPush(INT5)(&stack, 389388);

    return 0;

stackPeek_error:
    fprintf(stderr, "stackPeek does not work\n");
    return 1;

stackPop_error:
    fprintf(stderr, "stackPop does not work\n");
    return 1;
}
