/* Inserting NULL instead of &stack */
#include "TemplateStack.h"

TemplateStack_inline(int)

int
main(void)
{
    stackIsEmpty(int, NULL);
    stackIsFull(int, NULL);
    stackBufferIsNull(int, NULL);
    stackSize(int, NULL);
    stackBufferSize(int, NULL);
    stackDup(int, NULL);
    stackRealloc(int, NULL, 1);
    stackClear(int, NULL);
    stackReverse(int, NULL);
    stackPush(int, NULL, 0);
    stackPop(int, NULL);
    stackPeek(int, NULL);
    stackPeekAt(int, NULL, 0);
    deleteStack(int, NULL);

    return 0;
}
