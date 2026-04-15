/* Module */
#include <stdio.h>
#include "module.h"

int
main(void)
{
    Stack(int) stack = newStack(int, 1);
    deleteStack(int, &stack);

    return 0;
}

TemplateStack_impl(int)
