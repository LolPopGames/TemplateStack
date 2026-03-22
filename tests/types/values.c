/* Various Values */
#include <stdio.h>
#include "TemplateStack.h"

/* Basic Type */
TemplateStack_inline(int)

/* Pointer */
typedef const char *cstr;
TemplateStack_inline(cstr)

/* Struct/Union/Enum */
union multi_size
{
    signed char s_ch;
    unsigned char u_ch;

    signed short s_sh;
    unsigned short u_sh;
    
    signed int s_int;
    unsigned int u_int;

    signed long s_long;
    unsigned long u_long;
};

typedef union multi_size multi_size_t;
TemplateStack_inline(multi_size_t)

/* Function Pointer */
void
hello_world(void)
{
    printf("Hello, World!\n");
}

void
bye_world(void)
{
    printf("Bye, World!\n");
}

typedef void (*print_func_t)(void);
TemplateStack_inline(print_func_t)

int
main(void)
{
    /* basic types has been already tested by other tests */
    /* testing pointers */
    {
        Stack(cstr) st1 = newStack(cstr)(2);
        if (stackBufferIsNull(cstr)(&st1))
            goto memory_alloc_error;

        stackPush(cstr)(&st1, "String");
        stackPush(cstr)(&st1, "OOO");

        printf("%s\n", stackPop(cstr)(&st1));
        printf("%s\n", stackPop(cstr)(&st1));

        deleteStack(cstr)(&st1);
    }

    /* testing struct/union/enum */
    {
        Stack(multi_size_t) st2 = newStack(multi_size_t)(2);
        multi_size_t temp = {0};

        if (stackBufferIsNull(multi_size_t)(&st2))
            goto memory_alloc_error;

        temp.s_ch = 'a';
        stackPush(multi_size_t)(&st2, temp);

        temp.s_long = 99999L;
        stackPush(multi_size_t)(&st2, temp);

        printf("%lu\n", stackPop(multi_size_t)(&st2).s_long);
        printf("%c\n", stackPop(multi_size_t)(&st2).s_ch);
        
        deleteStack(multi_size_t)(&st2);
    }

    /* testing function pointers */
    {
        Stack(print_func_t) st3 = newStack(print_func_t)(2);
        print_func_t temp_func = NULL;

        if (stackBufferIsNull(print_func_t)(&st3))
            goto memory_alloc_error;

        stackPush(print_func_t)(&st3, &bye_world);
        stackPush(print_func_t)(&st3, &hello_world);

        stackPop(print_func_t)(&st3)(); /* hello */
        stackPop(print_func_t)(&st3)(); /* bye */
        
        deleteStack(print_func_t)(&st3);
    }

    return 0;

memory_alloc_error:
    fprintf(stderr, "Failed Memory Allocation\n");
    return 1;
}
