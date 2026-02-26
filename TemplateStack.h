#ifndef _TEMPLATE_STACK_H_
#define _TEMPLATE_STACK_H_

/* ---- Includes ---- */
#include <stddef.h>

/* ---- API functions ---- */
#define Stack(T) struct _templatestack_##T
#define newStack(T) _templatestack_newStack_##T
#define stackPush(T) _templatestack_stackPush_##T
#define stackPop(T) _templatestack_stackPop_##T
#define stackPeek(T) _templatestack_stackPeek_##T
#define stackIsEmpty(T) _templatestack_stackIsEmpty_##T
#define stackSize(T) _templatestack_stackSize##T

/* ---- Implementation macros ---- */
#define _templatestack_Stack(T) \
    Stack(T) { \
        T *buffer; \
        size_t index; \
        size_t size; \
    } \

#define _templatestack_newStack_proto(T) \
    Stack(T) \
    newStack(T)(size_t size); \

#define _templatestack_newStack_impl(T) \
    Stack(T) \
    newStack(T)(size_t size) { \
        Stack(T) stack = {0}; \
        stack.buffer = calloc(sizeof(T), size); \
        if (stack.buffer == NULL) return stack; \
        stack.size = size; \
        return stack; \
    } \

#define _templatestack_stackPush_proto(T) \
    int \
    stackPush(T)(Stack(T) *stack, T node);

#define _templatestack_stackPush_impl(T) \
    int \
    stackPush(T)(Stack(T) *stack, T node) { \
        if (stack->index >= stack->size) return 1; \
        stack->buffer[stack->index++] = node; \
        stack->size++; \
        return 0; \
    } \

#define _templatestack_stackPop_proto(T) \
    T \
    stackPop(T)(Stack(T) *stack); \

#define _templatestack_stackPop_impl(T) \
    T \
    stackPop(T)(stack(T) *stack) { \
        T empty = {0}; \
        T result; \
        if (StackIsEmpty(T)(stack)) return empty; \
        result = stack->buffer[stack->index]; \
        stack->buffer[stack->index] = empty; \
        stack->index--; \
        return result; \
    } \

#define _templatestack_stackPeek_proto(T) \
    T \
    stackPeek(T)(Stack(T) *stack); \

#define _templatestack_stackPeek_impl(T) \
    T \
    stackPeek(T)(Stack(T) *stack) { \
        T empty = {0}; \
        if (StackIsEmpty(T)(stack)) return empty; \
        return stack->buffer[stack->index]; \
    } \

#define _templatestack_stackIsEmpty_proto(T) \
    int \
    stackIsEmpty(T)(Stack(T) *stack); \

#define _templatestack_stackIsEmpty_impl(T) \
    int \
    stackIsEmpty(T)(Stack(T) *stack) { \
        return !(stack->index == 0); \
    } \

#define _templatestack_stackSize_proto(T) \
    size_t \
    stackSize(T)(Stack(T) *stack); \

#define _templatestack_stackSize_impl(T) \
    size_t \
    stackSize(T)(Stack(T) *stack) { \
        return stack->index; \
    } \

/* ---- Template Stack Prototype (for header) ---- */
#define TemplateStack_proto(T)

/* ---- Template Stack Implementation (for source file) ---- */
#define TemplateStack_impl(T)

/* ---- Template Stack Inline (all in one) ---- */
#define TemplateStack_inline(T)

/* ---- Template Stack Static (all functions are static) ---- */
#define TemplateStack_static(T)

#endif /* _TEMPLATE_STACK_H_ */
