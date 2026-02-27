#ifndef _TEMPLATE_STACK_H_
#define _TEMPLATE_STACK_H_

/* ---- Includes ---- */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ---- API functions ---- */
#define Stack(T) struct _templatestack_##T
#define newStack(T) _templatestack_newStack_##T
#define stackIsEmpty(T) _templatestack_stackIsEmpty_##T
#define stackIsFull(T) _templatestack_stackIsFull_##T
#define stackNull(T) _templatestack_stackNull_##T
#define stackSize(T) _templatestack_stackSize_##T
#define stackBufferSize(T) _templatestack_stackBufferSize_##T
#define stackPush(T) _templatestack_stackPush_##T
#define stackPop(T) _templatestack_stackPop_##T
#define stackPeek(T) _templatestack_stackPeek_##T
#define deleteStack(T) _templatestack_deleteStack_##T
#define stackDup(T) _templatestack_stackDup_##T
#define stackRealloc(T) _templatestack_stackRealloc_##T
/* ---- Implementation macros ---- */

/* --- struct Stack --- */
#define _templatestack_Stack(T) \
    Stack(T) { \
        T *buffer; \
        size_t index; \
        size_t size; \
    };

/* --- newStack() --- */
#define _templatestack_newStack_proto(T) \
    Stack(T) \
    newStack(T)(size_t size);

#define _templatestack_newStack_impl(T) \
    Stack(T) \
    newStack(T)(size_t size) { \
        Stack(T) stack = {0}; \
        stack.buffer = calloc(size, sizeof(T)); \
        if (stack.buffer == NULL) return stack; \
        stack.size = size; \
        return stack; \
    }

/* --- stackIsEmpty() --- */
#define _templatestack_stackIsEmpty_proto(T) \
    int \
    stackIsEmpty(T)(Stack(T) stack);

#define _templatestack_stackIsEmpty_impl(T) \
    int \
    stackIsEmpty(T)(Stack(T) stack) { \
        return (stack.index == 0) ? 1 : 0; \
    }

/* --- stackIsFull() --- */
#define _templatestack_stackIsFull_proto(T) \
    int \
    stackIsFull(T)(Stack(T) stack);

#define _templatestack_stackIsFull_impl(T) \
    int \
    stackIsFull(T)(Stack(T) stack) { \
        return (stack.index >= stack.size) ? 1 : 0; \
    }

/* --- stackNull() --- */
#define _templatestack_stackNull_proto(T) \
    int \
    stackNull(T)(Stack(T) stack);

#define _templatestack_stackNull_impl(T) \
    int \
    stackNull(T)(Stack(T) stack) { \
        return (stack.buffer == NULL) ? 1 : 0; \
    }

/* --- stackSize() --- */
#define _templatestack_stackSize_proto(T) \
    size_t \
    stackSize(T)(Stack(T) stack);

#define _templatestack_stackSize_impl(T) \
    size_t \
    stackSize(T)(Stack(T) stack) { \
        return stack.index; \
    }

/* --- stackBufferSize() --- */
#define _templatestack_stackBufferSize_proto(T) \
    size_t \
    stackBufferSize(T)(Stack(T) stack);

#define _templatestack_stackBufferSize_impl(T) \
    size_t \
    stackBufferSize(T)(Stack(T) stack) { \
        return stack.size; \
    }

/* --- stackPush() --- */
#define _templatestack_stackPush_proto(T) \
    int \
    stackPush(T)(Stack(T) *stack, T node);

#define _templatestack_stackPush_impl(T) \
    int \
    stackPush(T)(Stack(T) *stack, T node) { \
        if (stackIsFull(T)(*stack)) return 1; \
        stack->buffer[stack->index++] = node; \
        return 0; \
    }

/* --- stackPop() --- */
#define _templatestack_stackPop_proto(T) \
    T \
    stackPop(T)(Stack(T) *stack);

#define _templatestack_stackPop_impl(T) \
    T \
    stackPop(T)(Stack(T) *stack) { \
        T empty = {0}; \
        T result; \
        if (stackIsEmpty(T)(*stack)) return empty; \
        result = stack->buffer[--(stack->index)]; \
        stack->buffer[stack->index] = empty; \
        return result; \
    }

/* --- stackPeek() --- */
#define _templatestack_stackPeek_proto(T) \
    T \
    stackPeek(T)(Stack(T) stack);

#define _templatestack_stackPeek_impl(T) \
    T \
    stackPeek(T)(Stack(T) stack) { \
        T empty = {0}; \
        if (stackIsEmpty(T)(stack)) return empty; \
        return stack.buffer[stack.index-1]; \
    }

/* --- deleteStack() --- */
#define _templatestack_deleteStack_proto(T) \
    int \
    deleteStack(T)(Stack(T) stack);

#define _templatestack_deleteStack_impl(T) \
    int \
    deleteStack(T)(Stack(T) stack) { \
        if (stackNull(T)(stack)) return 1; \
        free(stack.buffer); \
        return 0; \
    }

/* --- stackDup() --- */
#define _templatestack_stackDup_proto(T) \
    Stack(T) \
    stackDup(T)(Stack(T) stack);

#define _templatestack_stackDup_impl(T) \
    Stack(T) \
    stackDup(T)(Stack(T) stack) { \
        Stack(T) dup = stack; \
        Stack(T) empty = {0}; \
        dup.buffer = malloc(dup.size * sizeof(T)); \
        if (dup.buffer == NULL) return empty; \
        memcpy(dup.buffer, stack.buffer, stack.size * sizeof(T)); \
        return dup; \
    }

/* --- stackRealloc() --- */
#define _templatestack_stackRealloc_proto(T) \
    Stack(T) \
    stackRealloc(T)(Stack(T) stack, size_t size);

#define _templatestack_stackRealloc_impl(T) \
    Stack(T) \
    stackRealloc(T)(Stack(T) stack, size_t size) { \
        Stack(T) empty = {0}; \
        if (size == 0) { \
            free(stack.buffer); \
            return empty; \
        } \
        stack.buffer = realloc(stack.buffer, size * sizeof(Stack(T))); \
        if (stackNull(stack)) return empty; \
        stack.size = size; \
        if (stack.index >= size) \
            stack.index = size; \
        return stack; \
    }

/* ---- Template Stack Prototype (for header) ---- */
#define TemplateStack_proto(T) \
    _templatestack_Stack(T) \
    _templatestack_newStack_proto(T) \
    _templatestack_stackIsEmpty_proto(T) \
    _templatestack_stackIsFull_proto(T) \
    _templatestack_stackNull_proto(T) \
    _templatestack_stackSize_proto(T) \
    _templatestack_stackBufferSize_proto(T) \
    _templatestack_stackPush_proto(T) \
    _templatestack_stackPop_proto(T) \
    _templatestack_stackPeek_proto(T) \
    _templatestack_deleteStack_proto(T) \
    _templatestack_stackDup_proto(T) \
    _templatestack_stackRealloc_proto(T)

/* ---- Template Stack Implementation (for source file) ---- */
#define TemplateStack_impl(T) \
    _templatestack_newStack_impl(T) \
    _templatestack_stackIsEmpty_impl(T) \
    _templatestack_stackIsFull_impl(T) \
    _templatestack_stackNull_impl(T) \
    _templatestack_stackSize_impl(T) \
    _templatestack_stackBufferSize_impl(T) \
    _templatestack_stackPush_impl(T) \
    _templatestack_stackPop_impl(T) \
    _templatestack_stackPeek_impl(T) \
    _templatestack_deleteStack_impl(T) \
    _templatestack_stackDup_impl(T) \
    _templatestack_stackRealloc_impl(T)

/* ---- Template Stack Inline (all in one) ---- */
#define TemplateStack_inline(T) \
    TemplateStack_proto(T) \
    TemplateStack_impl(T)

#endif /* _TEMPLATE_STACK_H_ */
