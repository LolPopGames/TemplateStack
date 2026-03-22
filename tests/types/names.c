/* Names */
#include <stdio.h>
#include "TemplateStack.h"

TemplateStack_inline(int)
TemplateStack_inline(long)

typedef unsigned long ulong;
TemplateStack_inline(ulong)

typedef signed char some__chType_;
TemplateStack_inline(some__chType_)

typedef int stackPush_int;
TemplateStack_inline(stackPush_int)

/* C89 Does not support mixed declarations, *
 * because of that we make test for C99+    */
#if defined(__STDC__) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    typedef int stackPush;
    TemplateStack_inline(stackPush)
#endif

int
main(void)
{
    /* testing for stackPush_int type */
    Stack(stackPush_int) st = newStack(stackPush_int)(10);
    if (stackBufferIsNull(stackPush_int)(&st))
        goto memory_alloc_error;

    stackPush(stackPush_int)(&st, 33);
    
    deleteStack(stackPush_int)(&st);

    /* testing for stackPush type */
    #if defined(__STDC__) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
        Stack(stackPush) st2 = newStack(stackPush)(10);
        if (stackBufferIsNull(stackPush)(&st2))
            goto memory_alloc_error;

        stackPush(stackPush)(&st2, 77);
        
        deleteStack(stackPush)(&st2);
    #endif

    return 0;

memory_alloc_error:
    fprintf(stderr, "Failed Memory Allocation");
    return 1;
}
