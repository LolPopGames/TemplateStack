#ifndef _TEMPLATE_STACK_H_
#define _TEMPLATE_STACK_H_

/* ---- Macros ---- */

/* extern if C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* --- Version --- */
#define TEMPLATE_STACK_MAJOR 0
#define TEMPLATE_STACK_MINOR 1
#define TEMPLATE_STACK_PATCH 0

/* ---- Includes ---- */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ---- API functions ---- */
/* NOTE:
 * Type T must be a single preprocessing token (no spaces or special characters).
 * For pointers or struct/union/enum types, use a typedef first
 * (e.g. typedef struct some some_t; typedef char * cstr;).
 */
#define Stack(T) struct _templatestack_##T
#define stackIsEmpty(T) _templatestack_stackIsEmpty_##T
#define stackIsFull(T) _templatestack_stackIsFull_##T
#define stackBufferIsNull(T) _templatestack_stackBufferIsNull_##T
#define stackSize(T) _templatestack_stackSize_##T
#define stackBufferSize(T) _templatestack_stackBufferSize_##T
#define stackPush(T) _templatestack_stackPush_##T
#define stackPop(T) _templatestack_stackPop_##T
#define stackPeek(T) _templatestack_stackPeek_##T
#define newStack(T) _templatestack_newStack_##T
#define deleteStack(T) _templatestack_deleteStack_##T
#define stackDup(T) _templatestack_stackDup_##T
#define stackRealloc(T) _templatestack_stackRealloc_##T

/* ---- Implementation Macros ---- */

/* --- struct Stack --- */
#define _templatestack_Stack(T) \
    Stack(T) { \
        T *buffer; \
        size_t index; \
        size_t size; \
    };

/* --- stackIsEmpty() --- */
#define _templatestack_stackIsEmpty_proto(T) \
    int \
    stackIsEmpty(T)(const Stack(T) *stack);

#define _templatestack_stackIsEmpty_impl(T) \
    int \
    stackIsEmpty(T)(const Stack(T) *stack) { \
        return (stack->index == 0) ? 1 : 0; \
    }

/* --- stackIsFull() --- */
#define _templatestack_stackIsFull_proto(T) \
    int \
    stackIsFull(T)(const Stack(T) *stack);

#define _templatestack_stackIsFull_impl(T) \
    int \
    stackIsFull(T)(const Stack(T) *stack) { \
        return (stack->index >= stack->size) ? 1 : 0; \
    }

/* --- stackBufferIsNull() --- */
#define _templatestack_stackBufferIsNull_proto(T) \
    int \
    stackBufferIsNull(T)(const Stack(T) *stack);

#define _templatestack_stackBufferIsNull_impl(T) \
    int \
    stackBufferIsNull(T)(const Stack(T) *stack) { \
        return (stack->buffer == NULL) ? 1 : 0; \
    }

/* --- stackSize() --- */
#define _templatestack_stackSize_proto(T) \
    size_t \
    stackSize(T)(const Stack(T) *stack);

#define _templatestack_stackSize_impl(T) \
    size_t \
    stackSize(T)(const Stack(T) *stack) { \
        return stack->index; \
    }

/* --- stackBufferSize() --- */
#define _templatestack_stackBufferSize_proto(T) \
    size_t \
    stackBufferSize(T)(const Stack(T) *stack);

#define _templatestack_stackBufferSize_impl(T) \
    size_t \
    stackBufferSize(T)(const Stack(T) *stack) { \
        return stack->size; \
    }

/* --- stackPush() --- */
#define _templatestack_stackPush_proto(T) \
    int \
    stackPush(T)(Stack(T) *stack, T value);

#define _templatestack_stackPush_impl(T) \
    int \
    stackPush(T)(Stack(T) *stack, T value) { \
        if (stack == NULL) return 1; \
        if (stackIsFull(T)(stack)) return 1; \
        \
        stack->buffer[stack->index++] = value; \
        \
        return 0; \
    }

/* --- stackPop() --- */
#define _templatestack_stackPop_proto(T) \
    T \
    stackPop(T)(Stack(T) *stack);

#define _templatestack_stackPop_impl(T) \
    T \
    stackPop(T)(Stack(T) *stack) { \
        static const T empty[1] = {0}; \
        T result; \
        \
        if (stack == NULL) return empty[0]; \
        if (stackIsEmpty(T)(stack)) return empty[0]; \
        \
        result = stack->buffer[--(stack->index)]; \
        stack->buffer[stack->index] = empty[0]; \
        \
        return result; \
    }

/* --- stackPeek() --- */
#define _templatestack_stackPeek_proto(T) \
    T \
    stackPeek(T)(const Stack(T) *stack);

#define _templatestack_stackPeek_impl(T) \
    T \
    stackPeek(T)(const Stack(T) *stack) { \
        static const T empty[1] = {0}; \
        \
        if (stack == NULL) return empty[0]; \
        if (stackIsEmpty(T)(stack)) return empty[0]; \
        \
        return stack->buffer[stack->index-1]; \
    }

/* --- newStack() --- */
#define _templatestack_newStack_proto(T) \
    Stack(T) \
    newStack(T)(size_t size);

#define _templatestack_newStack_impl(T) \
    Stack(T) \
    newStack(T)(size_t size) { \
        Stack(T) stack = {0}; \
        \
        if (size == 0) return stack; \
        \
        stack.buffer = calloc(size, sizeof(T)); \
        if (stackBufferIsNull(T)(&stack)) return stack; \
        \
        stack.size = size; \
        return stack; \
    }

/* --- deleteStack() --- */
#define _templatestack_deleteStack_proto(T) \
    int \
    deleteStack(T)(Stack(T) *stack);

#define _templatestack_deleteStack_impl(T) \
    int \
    deleteStack(T)(Stack(T) *stack) { \
        if (stack == NULL) return 1; \
        if (stackBufferIsNull(T)(stack)) return 1; \
        \
        free(stack->buffer); \
        \
        stack->buffer = NULL; \
        stack->size = 0; \
        stack->index = 0; \
        return 0; \
    }

/* --- stackDup() --- */
#define _templatestack_stackDup_proto(T) \
    Stack(T) \
    stackDup(T)(const Stack(T) *stack);

#define _templatestack_stackDup_impl(T) \
    Stack(T) \
    stackDup(T)(const Stack(T) *stack) { \
        static const Stack(T) empty = {0}; \
        Stack(T) dup = *stack; \
        \
        dup.buffer = malloc(dup.size * sizeof(T)); \
        if (stackBufferIsNull(T)(&dup)) return empty; \
        \
        memcpy(dup.buffer, stack->buffer, dup.index * sizeof(T)); \
        \
        return dup; \
    }

/* --- stackRealloc() --- */
#define _templatestack_stackRealloc_proto(T) \
    Stack(T) \
    stackRealloc(T)(const Stack(T) *stack, size_t size);

#define _templatestack_stackRealloc_impl(T) \
    Stack(T) \
    stackRealloc(T)(Stack(T) *stack, size_t size) { \
        static const Stack(T) empty = {0}; \
        Stack(T) new_stack = {0}; \
        \
        if (size == 0) { \
            return empty; \
        } \
        new_stack.buffer = realloc(stack->buffer, size * sizeof(T)); \
        if (stackBufferIsNull(T)(&new_stack)) return empty; \
        \
        /* Setting 0 to all new elements (if new size is bigger) */ \
        if (size > stack->size) \
        { \
            memset( \
                new_stack.buffer + stack->size, \
                0, (size - stack->size) * sizeof(T) \
            ); \
        } \
        \
        new_stack.size = size; \
        if (stack->index >= size) \
        { \
            new_stack.index = size; \
        } \
        else \
        { \
            new_stack.index = stack->index; \
        } \
        \
        *stack = empty; \
        \
        return new_stack; \
    }

/* ---- Template Stack Prototype (for header) ---- */
#define TemplateStack_proto(T) \
    _templatestack_Stack(T) \
    _templatestack_stackIsEmpty_proto(T) \
    _templatestack_stackIsFull_proto(T) \
    _templatestack_stackBufferIsNull_proto(T) \
    _templatestack_stackSize_proto(T) \
    _templatestack_stackBufferSize_proto(T) \
    _templatestack_stackPush_proto(T) \
    _templatestack_stackPop_proto(T) \
    _templatestack_stackPeek_proto(T) \
    _templatestack_newStack_proto(T) \
    _templatestack_deleteStack_proto(T) \
    _templatestack_stackDup_proto(T) \
    _templatestack_stackRealloc_proto(T)

/* ---- Static Template Stack Prototype (for header inline part) ---- */
#define TemplateStack_static_proto(T) \
    _templatestack_Stack(T) \
    static _templatestack_stackIsEmpty_proto(T) \
    static _templatestack_stackIsFull_proto(T) \
    static _templatestack_stackBufferIsNull_proto(T) \
    static _templatestack_stackSize_proto(T) \
    static _templatestack_stackBufferSize_proto(T) \
    static _templatestack_stackPush_proto(T) \
    static _templatestack_stackPop_proto(T) \
    static _templatestack_stackPeek_proto(T) \
    static _templatestack_newStack_proto(T) \
    static _templatestack_deleteStack_proto(T) \
    static _templatestack_stackDup_proto(T) \
    static _templatestack_stackRealloc_proto(T)

/* ---- Template Stack Implementation (for source file) ---- */
#define TemplateStack_impl(T) \
    _templatestack_stackIsEmpty_impl(T) \
    _templatestack_stackIsFull_impl(T) \
    _templatestack_stackBufferIsNull_impl(T) \
    _templatestack_stackSize_impl(T) \
    _templatestack_stackBufferSize_impl(T) \
    _templatestack_stackPush_impl(T) \
    _templatestack_stackPop_impl(T) \
    _templatestack_stackPeek_impl(T) \
    _templatestack_newStack_impl(T) \
    _templatestack_deleteStack_impl(T) \
    _templatestack_stackDup_impl(T) \
    _templatestack_stackRealloc_impl(T)

/* ---- Static Template Stack Implementation (for source inline part) ---- */
#define TemplateStack_static_impl(T) \
    static _templatestack_stackIsEmpty_impl(T) \
    static _templatestack_stackIsFull_impl(T) \
    static _templatestack_stackBufferIsNull_impl(T) \
    static _templatestack_stackSize_impl(T) \
    static _templatestack_stackBufferSize_impl(T) \
    static _templatestack_stackPush_impl(T) \
    static _templatestack_stackPop_impl(T) \
    static _templatestack_stackPeek_impl(T) \
    static _templatestack_newStack_impl(T) \
    static _templatestack_deleteStack_impl(T) \
    static _templatestack_stackDup_impl(T) \
    static _templatestack_stackRealloc_impl(T)

/* ---- Template Stack Inline (all in one) ---- */
#define TemplateStack_inline(T) \
    _templatestack_Stack(T) \
    TemplateStack_static_impl(T)

/* ---- Closing extern if C++ --- */
#ifdef __cplusplus
}
#endif

#endif /* _TEMPLATE_STACK_H_ */
