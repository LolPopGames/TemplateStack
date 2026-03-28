/* Custom Malloc, Realloc & Free Implementation */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/* blocks divisible by 16 (chunks) will be allocated for any allocated memory */

#define CHUNK_SIZE 16
#define HEAP_SIZE 256
#define MAX_CHUNKS (HEAP_SIZE / CHUNK_SIZE)

struct heap_ptr
{
    size_t pos;
    size_t chunks_count;
};

struct heap_ptr heap_ptr[MAX_CHUNKS] = {0};
size_t count_allocated = 0;
uint8_t heap[HEAP_SIZE];

int
_is_range_free(size_t start, size_t needed)
{
    size_t i;

    for (i=0; i < count_allocated; i++)
    {
        size_t start_pos = heap_ptr[i].pos;
        size_t end_pos = start_pos + heap_ptr[i].chunks_count;

        if (!(start + needed <= start_pos || start >= end_pos))
            return 0;
    }
    return 1;
}

void *
my_malloc(size_t size)
{
    size_t i, needed_chunks;

    if (size == 0 || count_allocated >= MAX_CHUNKS)
        return NULL;

    needed_chunks = (size + CHUNK_SIZE - 1) / CHUNK_SIZE;

    for (i=0; i <= MAX_CHUNKS - needed_chunks; i++)
    {
        if (_is_range_free(i, needed_chunks))
        {
            heap_ptr[count_allocated].pos = i;
            heap_ptr[count_allocated].chunks_count = needed_chunks;
            count_allocated++;

            return &heap[i * CHUNK_SIZE];
        }
    }

    return NULL;
}

int
my_free(void *memory)
{
    size_t i, j, chunk_index;
    uintptr_t offset;

    if (!memory)
        return 1;

    offset = (uint8_t *)memory - heap;

    if (offset >= HEAP_SIZE || offset % CHUNK_SIZE != 0)
        return 1;

    chunk_index = offset / CHUNK_SIZE;

    for (i=0; i<count_allocated; i++)
    {
        if (heap_ptr[i].pos == chunk_index)
        {
            for (j=i; j < count_allocated-1; j++)
                heap_ptr[j] = heap_ptr[j+1];

            count_allocated--;
            return 0;
        }
    }

    return 1;
}

void *my_realloc(void *ptr, size_t size)
{
    size_t i, old_chunks, new_chunks;
    void *new_ptr;

    if (ptr == NULL) return my_malloc(size);
    if (size == 0) return NULL;

    for (i=0; i<count_allocated; i++)
    {
        if (&heap[heap_ptr[i].pos * CHUNK_SIZE] == ptr) break;
    }

    if (i == count_allocated) return NULL;

    old_chunks = heap_ptr[i].chunks_count;
    new_chunks = (size + CHUNK_SIZE-1) / CHUNK_SIZE;

    if (new_chunks <= old_chunks)
    {
        heap_ptr[i].chunks_count = new_chunks;
        return ptr;
    }
    else
    {
        new_ptr = my_malloc(size);
        if (new_ptr == NULL) return NULL;

        memcpy(new_ptr, ptr, old_chunks * CHUNK_SIZE);
        my_free(ptr);
        return new_ptr;
    }
}

#define TEMPLATE_STACK_MALLOC my_malloc
#define TEMPLATE_STACK_REALLOC my_realloc
#define TEMPLATE_STACK_FREE my_free

#include "TemplateStack.h"

TemplateStack_inline(unsigned)
int
main(void)
{
    int i, stack_buffer_is_null, temp_buffer_is_null;
    unsigned j;
    Stack(unsigned) stack = newStack(unsigned)(5), temp_stack;
    if (stackBufferIsNull(unsigned)(&stack))
        goto memory_alloc_error;

    for (i=1; i<=5; i++)
        stackPush(unsigned)(&stack, 10*i);

    temp_stack = stackRealloc(unsigned)(&stack, 10);

    stack_buffer_is_null = stackBufferIsNull(unsigned)(&stack);
     temp_buffer_is_null = stackBufferIsNull(unsigned)(&temp_stack);

    /* if reallocation failed */
    if (temp_buffer_is_null && !stack_buffer_is_null)
    {
        deleteStack(unsigned)(&stack);
        goto memory_alloc_error;
    }
    /* if invalid stackRealloc */
    if (temp_buffer_is_null && stack_buffer_is_null)
        goto stackRealloc_error;

    stack = temp_stack;

    if (
        stackPeek(unsigned)(&stack) != 50 ||
        stackSize(unsigned)(&stack) != 5 ||
        stackBufferSize(unsigned)(&stack) != 10
    )
    {
        deleteStack(unsigned)(&stack);
        goto stackRealloc_error;
    }

    stack = stackRealloc(unsigned)(&stack, 3);
    if (
        stackPeek(unsigned)(&stack) != 30 ||
        stackSize(unsigned)(&stack) != 3 ||
        stackBufferSize(unsigned)(&stack) != 3
    )
    {
        deleteStack(unsigned)(&stack);
    }

    stackPushGrow(unsigned)(&stack, 400);
    if (stackBufferIsNull(unsigned)(&stack))
        goto memory_alloc_error;

    if (
        stackPeek(unsigned)(&stack) != 400 ||
        stackSize(unsigned)(&stack) != 4 ||
        stackBufferSize(unsigned)(&stack) != 6
    )
    {
        deleteStack(unsigned)(&stack);
        goto stackPushGrow_error;
    }

    temp_stack = stackDup(unsigned)(&stack);
    if (stackBufferIsNull(unsigned)(&temp_stack))
    {
        deleteStack(unsigned)(&stack);
        goto memory_alloc_error;
    }

    if (stackBufferIsNull(unsigned)(&stack))
    {
        deleteStack(unsigned)(&temp_stack);
        goto stackDup_error;
    }

    for (i=0, j=4; i<4; i++, j--)
    {
        if (j != 4)
        {
            if (stackPeekAt(unsigned)(&temp_stack, i) != j*10)
            {
                deleteStack(unsigned)(&temp_stack);
                deleteStack(unsigned)(&stack);
                goto stackDup_error;
            }
        }
        /* when j==4 */
        else if (stackPeekAt(unsigned)(&temp_stack, i) != j*100)
        {
            deleteStack(unsigned)(&temp_stack);
            deleteStack(unsigned)(&stack);
            goto stackDup_error;
        }
    }

    deleteStack(unsigned)(&temp_stack);
    deleteStack(unsigned)(&stack);

    return 0;

stackRealloc_error:
    fprintf(stderr, "stackRealloc does not work\n");
    return 1;

stackPushGrow_error:
    fprintf(stderr, "stackPushGrow does not work\n");
    return 1;

stackDup_error:
    fprintf(stderr, "stackDup does not work\n");
    return 1;

memory_alloc_error:
    fprintf(stderr, "Failed Memory Allocation\n");
    return 1;
}
