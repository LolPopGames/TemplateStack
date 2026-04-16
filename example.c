/**
 * @brief Stack "Command Line"
 */
#include "TemplateStack.h"
#include <stdio.h>
#include <string.h>

/* Disabling unused function warning */
#if defined(__GNUC__) && /* gcc version >=4.2 */ \
    ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-function"
#endif

/* Templating Stack for int */
TemplateStack_inline(int)

#if defined(__GNUC__) && /* gcc version >=4.2 */ \
    ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
#   pragma GCC diagnostic pop
#endif

int
main(void)
{
    /* --- Variables --- */
    char buffer[256] = {0};
    Stack(int) stack;

    /* --- Intro --- */
    printf(
        "Hello, This is a stack command line!\n"
        "Type \"help\" to see commands\n"
    );

    /* Initializing Stack */
    stack = newStack(int);
    if (stackBufferIsNull(int, &stack))
    {
        printf("Failed memory allocation, exiting program...\n");
        return 0;
    }
    
    /* --- Main Loop --- */
    while (1)
    {
        /* --- Getting Command --- */
        printf("-> ");
        fflush(stdout);
        fgets(buffer, sizeof(buffer), stdin);

        /* --- Searching Command --- */
        if (strncmp(buffer, "push", 4) == 0)
        {
            int value = atoi(buffer+4);
            size_t buf_size = stackBufferSize(int, &stack);

            /* 0 - success, other codes - fail */
            if (stackPush(int, &stack, value) != 0)
            {
                printf("Push failed\n");
            }

            if (stackBufferSize(int, &stack) != buf_size)
            {
                printf("Doubling stack buffer size...\n");
            }
            continue;
        }

        if (strncmp(buffer, "pop", 3) == 0)
        {
            if (stackIsEmpty(int, &stack))
            {
                printf("Stack is empty\n");
                continue;
            }

            printf("%d\n", stackPop(int, &stack));
            continue;
        }

        if (
            /* peek or top */
            strncmp(buffer, "peek", 4) == 0 ||
            strncmp(buffer, "top", 3) == 0
        )
        {
            if (stackIsEmpty(int, &stack))
            {
                printf("Stack is empty\n");
                continue;
            }

            printf("%d\n", stackPeek(int, &stack));
            continue;
        }

        /* realloction */
        if (strncmp(buffer, "resize", 6) == 0)
        {
            int size = atoi(buffer+6);
            Stack(int) new_stack;

            if (size <= 0)
            {
                printf("Invalid resize value\n");
                continue;
            }

            new_stack = stackRealloc(int, &stack, size);
            if (stackBufferIsNull(int, &new_stack))
            {
                printf("Failed memory allocation, exiting program...\n");

                /* deleting original stack, because if realloction failed, *
                 * the original stack will not be freed                    */
                deleteStack(int, &stack);
                return 0;
            }

            stack = new_stack;

            continue;
        }

        if (strncmp(buffer, "clear", 5) == 0)
        {
            stackClear(int, &stack);
            continue;
        }

        if (strncmp(buffer, "reverse", 7) == 0)
        {
            stackReverse(int, &stack);
            continue;
        }

        if (strncmp(buffer, "size", 4) == 0)
        {
            printf("%lu\n", stackSize(int, &stack));
            continue;
        }

        if (strncmp(buffer, "bufsize", 7) == 0)
        {
            printf("%lu\n", stackBufferSize(int, &stack));
            continue;
        }

        if (strncmp(buffer, "help", 4) == 0)
        {
            printf(
                "help - print help\n"
                "push NUM - push to stack\n"
                "pop - pop from stack\n"
                "peek - get top element\n"
                "top - same as peek\n"
                "resize NUM - resize stack buffer\n"
                "clear - removes all elements from the stack\n"
                "reverse - reverses stack upside down\n"
                "size - get how many elements are now in stack\n"
                "bufsize - size of the stack buffer\n"
                "exit - exit the program\n"
            );
            continue;
        }

        if (strncmp(buffer, "exit", 4) == 0)
        {
            /* It is needed to delete stack before exit */
            deleteStack(int, &stack);
            return 0;
        }

        /* if other (not empty) command */
        if (buffer[0] != '\n')
        {
            /* \n will be printed automaticaly */
            printf("Command not found: %s", buffer);
        }
    }

    return 0;
}
