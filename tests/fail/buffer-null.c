/* Inserting stack with NULL buffer */
#include "TemplateStack.h"

TemplateStack_inline(int)

int
main(void)
{
    Stack(int) stack = {0};

    stackIsEmpty(int, &stack);
    stackIsFull(int, &stack);
    stackBufferIsNull(int, &stack);
    stackSize(int, &stack);
    stackBufferSize(int, &stack);
    stackDup(int, &stack);
    stackRealloc(int, &stack, 1);
    stackClear(int, &stack);
    stackReverse(int, &stack);
    stackPush(int, &stack, 0);
    stackPop(int, &stack);
    stackPeek(int, &stack);
    stackPeekAt(int, &stack, 0);
    deleteStack(int, &stack);

    return 0;
}
