#ifndef _TEMPLATE_STACK_H_
#define _TEMPLATE_STACK_H_

/* ---- Includes ---- */
#include <stddef.h>

/* ---- API functions ---- */
#define Stack(T) struct _templatestack_##T
#define newStack(T) _templatestack_newStack_##T
#define stackPush(T) _templatestack_stackPush_##T

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

/* ---- Template Stack Prototype (for header) ---- */
#define TemplateStack_proto(T)

/* ---- Template Stack Implementation (for source file) ---- */
#define TemplateStack_impl(T)

/* ---- Template Stack Inline (all in one) ---- */
#define TemplateStack_inline(T)

/* ---- Template Stack Static (all functions are static) ---- */
#define TemplateStack_static(T)

#endif /* _TEMPLATE_STACK_H_ */
