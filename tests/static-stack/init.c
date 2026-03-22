/* Initialization Test */
#include <stdio.h>
#include "TemplateStack.h"

StaticStack_inline(INT10, int, 10)

int
main(void)
{
    Stack(INT10) stack = {0};

    return 0;
}
