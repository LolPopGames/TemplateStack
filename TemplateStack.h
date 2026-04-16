/* SPDX-License-Identifier: MIT */
/**
 * @file TemplateStack.h
 * @brief A single-header C library that implements a stack
 * and allows it to be used with any type
 *
 * You can create multiple stacks for different types without
 * writing separate stack implementations
 *
 * @author LolPopGames
 * @date 2026
 * @version v1.0.0-dev
 * @copyright
 * Copyright © 2026 LolPopGames
 *
 * @license
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
#ifndef _TEMPLATE_STACK_H
#define _TEMPLATE_STACK_H

/* ---- Macros ---- */

/* extern if C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* --- Version --- */
#define TEMPLATE_STACK_MAJOR 1
#define TEMPLATE_STACK_MINOR 0
#define TEMPLATE_STACK_PATCH 0
#define TEMPLATE_STACK_ATLEAST(major,minor,patch) ( \
    (TEMPLATE_STACK_MAJOR > (major)) || \
    \
    ( \
        TEMPLATE_STACK_MAJOR == (major) && \
        \
        ( \
            (TEMPLATE_STACK_MINOR > (minor)) || \
            \
            ( \
                TEMPLATE_STACK_MINOR == (minor) && \
                TEMPLATE_STACK_PATCH >= (patch) \
            ) \
        ) \
    ) \
)

/* ---- Configuration ---- */

/* --- Memory Allocators --- */

/* -- Showing Warnings -- */

/* MALLOC && !FREE */
#if     defined(TEMPLATE_STACK_MALLOC)  && !defined(TEMPLATE_STACK_FREE)
    #if defined(__STDC_VERSION__)       &&  (__STDC_VERSION__ >= 202311L)
        #warning TEMPLATE_STACK_MALLOC is defined, \
but TEMPLATE_STACK_FREE is not
    
    #elif defined(__GNUC__) && \
        ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #pragma GCC warning "TEMPLATE_STACK_MALLOC is defined, \
but TEMPLATE_STACK_FREE is not"

    #endif
#endif

/* !MALLOC && FREE */
#if    !defined(TEMPLATE_STACK_MALLOC)  &&  defined(TEMPLATE_STACK_FREE)
    #if defined(__STDC_VERSION__)       &&  (__STDC_VERSION__ >= 202311L)
        #warning TEMPLATE_STACK_FREE is defined, \
but TEMPLATE_STACK_MALLOC is not
    
    #elif defined(__GNUC__) && \
        ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #pragma GCC warning "TEMPLATE_STACK_FREE is defined, \
but TEMPLATE_STACK_MALLOC is not"

    #endif
#endif

/* REALLOC && !MALLOC */
#if     defined(TEMPLATE_STACK_REALLOC) && !defined(TEMPLATE_STACK_MALLOC)
    #if defined(__STDC_VERSION__)       &&  (__STDC_VERSION__ >= 202311L)
        #warning TEMPLATE_STACK_REALLOC is defined, \
but TEMPLATE_STACK_MALLOC is not
    
    #elif defined(__GNUC__) && \
        ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #pragma GCC warning "TEMPLATE_STACK_REALLOC is defined, \
but TEMPLATE_STACK_MALLOC is not"

    #endif
#endif

/* REALLOC && !FREE */
#if     defined(TEMPLATE_STACK_REALLOC) && !defined(TEMPLATE_STACK_FREE)
    #if defined(__STDC_VERSION__)       &&  (__STDC_VERSION__ >= 202311L)
        #warning TEMPLATE_STACK_REALLOC is defined, \
but TEMPLATE_STACK_FREE is not
    
    #elif defined(__GNUC__) && \
        ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #pragma GCC warning "TEMPLATE_STACK_REALLOC is defined, \
but TEMPLATE_STACK_FREE is not"

    #endif
#endif

/* REALLOC && !MALLOC && !FREE */
#if     defined(TEMPLATE_STACK_REALLOC) && \
    !defined(TEMPLATE_STACK_MALLOC) && !defined(TEMPLATE_STACK_FREE)

    #if defined(__STDC_VERSION__)       &&  (__STDC_VERSION__ >= 202311L)
        #warning TEMPLATE_STACK_REALLOC is defined, \
but TEMPLATE_STACK_MALLOC and TEMPLATE_STACK_FREE are not
    
    #elif defined(__GNUC__) && \
        ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #pragma GCC warning "TEMPLATE_STACK_REALLOC is defined, \
but TEMPLATE_STACK_MALLOC and TEMPLATE_STACK_FREE are not"

    #endif
#endif

/* -- Configuring -- */
#ifndef TEMPLATE_STACK_MALLOC
    #ifndef TEMPLATE_STACK_REALLOC
        #define TEMPLATE_STACK_REALLOC realloc
    #endif

    #define TEMPLATE_STACK_MALLOC malloc
#endif
#ifndef TEMPLATE_STACK_FREE
    #define TEMPLATE_STACK_FREE free
#endif

/* --- Default New Stack Size --- */
#ifndef TEMPLATE_STACK_DEFAULT_NEW_SIZE
    #define TEMPLATE_STACK_DEFAULT_NEW_SIZE 256
#endif

/* ---- Includes ---- */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ---- API functions ---- */
/* NOTE:
 * Type T must be a single preprocessing token (no spaces or special characters)
 * For pointers or struct/union/enum types, use a typedef first
 * (e.g. typedef struct some some_t; typedef char * cstr;)
 */
#define Stack(T) struct _templatestack_##T
#define stackIsEmpty(T, stack) _templatestack_stackIsEmpty_type_##T(stack)
#define stackIsFull(T, stack) _templatestack_stackIsFull_type_##T(stack)
#define stackBufferIsNull(T, stack) _templatestack_stackBufferIsNull_type_##T(stack)
#define stackSize(T, stack) _templatestack_stackSize_type_##T(stack)
#define stackBufferSize(T, stack) _templatestack_stackBufferSize_type_##T(stack)
#define stackDup(T, stack) _templatestack_stackDup_type_##T(stack)
#define stackRealloc(T, stack, size) _templatestack_stackRealloc_type_##T((stack), (size))
#define stackClear(T, stack) _templatestack_stackClear_type_##T(stack)
#define stackReverse(T, stack) _templatestack_stackReverse_type_##T(stack)
#define stackPush(T, stack, value) _templatestack_stackPush_type_##T((stack), (value))
#define stackPop(T, stack) _templatestack_stackPop_type_##T(stack)
#define stackPeek(T, stack) _templatestack_stackPeek_type_##T(stack)
#define stackPeekAt(T, stack, index) _templatestack_stackPeekAt_type_##T((stack), (index))
#define deleteStack(T, stack) _templatestack_deleteStack_type_##T(stack)

/* only C99+ supports VA macros */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define _templatestack_newStack_1arg(T) _templatestack_newStack_type_##T(0)
    #define _templatestack_newStack_2arg(T, size) _templatestack_newStack_type_##T(size)

    #define _templatestack_newStack_countArgs_(_1, _2, N, ...) N
    #define _templatestack_newStack_countArgs(...) \
        _templatestack_newStack_countArgs_(__VA_ARGS__, 2arg, 1arg, 0)

    #define _templatestack_concat_(a, b) a##b
    #define _templatestack_concat(a, b) _templatestack_concat_(a, b)

    #define newStack(...) _templatestack_concat( \
        _templatestack_newStack_, \
        _templatestack_newStack_countArgs(__VA_ARGS__) \
    )(__VA_ARGS__)
#else
    #define newStack(T, size) _templatestack_newStack_type_##T(size)
#endif

/* ---- Implementation Macros --- */

/* --- struct Stack --- */
#define _templatestack_Stack(T) \
    Stack(T) \
    { \
        T *buffer; \
        size_t index; \
        size_t size; \
    };

/* --- [static] struct Stack --- */
#define _templatestack_staticstack_Stack(name, T, size) \
    Stack(name) \
    { \
        T buffer[(size)]; \
        size_t index; \
    };

/* --- stackIsEmpty() --- */
#define _templatestack_stackIsEmpty_proto(T) \
    int \
    _templatestack_stackIsEmpty_type_##T(const Stack(T) *stack);

#define _templatestack_stackIsEmpty_impl(T) \
    int \
    _templatestack_stackIsEmpty_type_##T(const Stack(T) *stack) \
    { \
        if (stack == NULL) return 1; \
        return (stack->index == 0) ? 1 : 0; \
    }

/* --- [static] stackIsEmpty() --- */
#define _templatestack_staticstack_stackIsEmpty_proto(name, T) \
    /* same as in default stack */ \
    _templatestack_stackIsEmpty_proto(name)

#define _templatestack_staticstack_stackIsEmpty_impl(name, T) \
    /* same as in default stack */ \
    _templatestack_stackIsEmpty_impl(name)

/* --- stackIsFull() --- */
#define _templatestack_stackIsFull_proto(T) \
    int \
    _templatestack_stackIsFull_type_##T(const Stack(T) *stack);

#define _templatestack_stackIsFull_impl(T) \
    int \
    _templatestack_stackIsFull_type_##T(const Stack(T) *stack) \
    { \
        if (stack == NULL) return 0; \
        return (stack->index >= stack->size) ? 1 : 0; \
    }

/* --- [static] stackIsFull() --- */
#define _templatestack_staticstack_stackIsFull_proto(name, T) \
    int \
    _templatestack_stackIsFull_type_##name(const Stack(name) *stack);

#define _templatestack_staticstack_stackIsFull_impl(name, T) \
    int \
    _templatestack_stackIsFull_type_##name(const Stack(name) *stack) \
    { \
        if (stack == NULL) return 0; \
        return (stack->index >= (  \
            sizeof(stack->buffer) / sizeof(stack->buffer[0]) \
        )) ? 1 : 0; \
    }

/* --- stackBufferIsNull() --- */
#define _templatestack_stackBufferIsNull_proto(T) \
    int \
    _templatestack_stackBufferIsNull_type_##T(const Stack(T) *stack);

#define _templatestack_stackBufferIsNull_impl(T) \
    int \
    _templatestack_stackBufferIsNull_type_##T(const Stack(T) *stack) \
    { \
        if (stack == NULL) return 1; \
        return (stack->buffer == NULL) ? 1 : 0; \
    }

/* --- stackSize() --- */
#define _templatestack_stackSize_proto(T) \
    size_t \
    _templatestack_stackSize_type_##T(const Stack(T) *stack);

#define _templatestack_stackSize_impl(T) \
    size_t \
    _templatestack_stackSize_type_##T(const Stack(T) *stack) \
    { \
        if (stack == NULL) return 0; \
        return stack->index; \
    }

/* --- [static] stackSize() --- */
#define _templatestack_staticstack_stackSize_proto(name, T) \
    /* same as in default stack */ \
    _templatestack_stackSize_proto(name)

#define _templatestack_staticstack_stackSize_impl(name, T) \
    /* same as in default stack */ \
    _templatestack_stackSize_impl(name)

/* --- stackBufferSize() --- */
#define _templatestack_stackBufferSize_proto(T) \
    size_t \
    _templatestack_stackBufferSize_type_##T(const Stack(T) *stack);

#define _templatestack_stackBufferSize_impl(T) \
    size_t \
    _templatestack_stackBufferSize_type_##T(const Stack(T) *stack) \
    { \
        if (stack == NULL) return 0; \
        return stack->size; \
    }

/* --- stackDup() --- */
#define _templatestack_stackDup_proto(T) \
    Stack(T) \
    _templatestack_stackDup_type_##T(const Stack(T) *stack);

#define _templatestack_stackDup_impl(T) \
    Stack(T) \
    _templatestack_stackDup_type_##T(const Stack(T) *stack) \
    { \
        static const Stack(T) empty = {0}; \
        Stack(T) dup; \
        \
        if (stack == NULL) return empty; \
        \
        dup = *stack; \
        \
        if (!stackBufferIsNull(T, stack)) \
        { \
            dup.buffer = (TEMPLATE_STACK_MALLOC)(dup.size * sizeof(T)); \
            \
            if (stackBufferIsNull(T, &dup)) return empty; \
            \
            memcpy(dup.buffer, stack->buffer, dup.index * sizeof(T)); \
        } \
        \
        return dup; \
    }

/* --- stackRealloc() --- */
#define _templatestack_stackRealloc_proto(T) \
    Stack(T) \
    _templatestack_stackRealloc_type_##T(Stack(T) *stack, size_t size);

#ifdef TEMPLATE_STACK_REALLOC
    #define _templatestack_stackRealloc_impl(T) \
        Stack(T) \
        _templatestack_stackRealloc_type_##T(Stack(T) *stack, size_t size) \
        { \
            static const Stack(T) empty = {0}; \
            Stack(T) new_stack = {0}; \
            \
            if (stack == NULL) return empty; \
            \
            if (stackBufferIsNull(T, stack)) return *stack; \
            \
            if (size == 0) { \
                return empty; \
            } \
            new_stack.buffer = \
                (TEMPLATE_STACK_REALLOC)(stack->buffer, size * sizeof(T)); \
            \
            if (stackBufferIsNull(T, &new_stack)) return empty; \
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
#else /* TEMPLATE_STACK_REALLOC */
    #define _templatestack_stackRealloc_impl(T) \
        Stack(T) \
        _templatestack_stackRealloc_type_##T(Stack(T) *stack, size_t size) \
        { \
            static const Stack(T) empty = {0}; \
            Stack(T) new_stack = {0}; \
            \
            if (stack == NULL) return empty; \
            \
            if (stackBufferIsNull(T, stack)) return *stack; \
            \
            if (size == 0) { \
                return empty; \
            } \
            \
            new_stack.buffer = (TEMPLATE_STACK_MALLOC)(size * sizeof(T)); \
            if (stackBufferIsNull(T, &new_stack)) return empty; \
            \
            new_stack.size = size; \
            if (stack->index >= size) \
            { \
                memcpy( \
                    new_stack.buffer, stack->buffer, \
                    size * sizeof(T) \
                ); \
                new_stack.index = size; \
            } \
            else \
            { \
                memcpy( \
                    new_stack.buffer, stack->buffer, \
                    stack->index * sizeof(T) \
                ); \
                new_stack.index = stack->index; \
            } \
            \
            (TEMPLATE_STACK_FREE)(stack->buffer); \
            *stack = empty; \
            \
            return new_stack; \
        }
#endif /* TEMPLATE_STACK_REALLOC */

/* --- stackClear() --- */
#define _templatestack_stackClear_proto(T) \
    int \
    _templatestack_stackClear_type_##T(Stack(T) *stack);

#define _templatestack_stackClear_impl(T) \
    int \
    _templatestack_stackClear_type_##T(Stack(T) *stack) \
    { \
        if (stack == NULL) return 1; \
        \
        stack->index = 0; \
        \
        return 0; \
    }

/* --- [static] stackClear() --- */
#define _templatestack_staticstack_stackClear_proto(name, T) \
    int \
    _templatestack_stackClear_type_##name(Stack(name) *stack);

#define _templatestack_staticstack_stackClear_impl(name, T) \
    int \
    _templatestack_stackClear_type_##name(Stack(name) *stack) \
    { \
        if (stack == NULL) return 1; \
        \
        stack->index = 0; \
        \
        return 0; \
    }

/* --- stackReverse() --- */
#define _templatestack_stackReverse_proto(T) \
    int \
    _templatestack_stackReverse_type_##T(Stack(T) *stack);

#define _templatestack_stackReverse_impl(T) \
    int \
    _templatestack_stackReverse_type_##T(Stack(T) *stack) \
    { \
        size_t i; \
        \
        if ( \
            stack == NULL || \
            stackBufferIsNull(T, stack) \
        ) return 1; \
        \
        for (i=0; i < (stack->index / 2); i++) \
        { \
            T temp = stack->buffer[i]; \
            stack->buffer[i] = stack->buffer[ stack->index -i -1 ]; \
            stack->buffer[ stack->index -i -1 ] = temp; \
        } \
        \
        return 0; \
    }

/* --- [static] stackReverse() --- */
#define _templatestack_staticstack_stackReverse_proto(name, T) \
    int \
    _templatestack_stackReverse_type_##name(Stack(name) *stack);

#define _templatestack_staticstack_stackReverse_impl(name, T) \
    int \
    _templatestack_stackReverse_type_##name(Stack(name) *stack) \
    { \
        size_t i; \
        \
        if (stack == NULL) return 1; \
        \
        for (i=0; i < (stack->index / 2); i++) \
        { \
            T temp = stack->buffer[i]; \
            stack->buffer[i] = stack->buffer[ stack->index -i -1 ]; \
            stack->buffer[ stack->index -i -1 ] = temp; \
        } \
        \
        return 0; \
    }

/* --- stackPush() --- */
#define _templatestack_stackPush_proto(T) \
    int \
    _templatestack_stackPush_type_##T(Stack(T) *stack, T value);

#define _templatestack_stackPush_impl(T) \
    int \
    _templatestack_stackPush_type_##T(Stack(T) *stack, T value) \
    { \
        if ( \
            stack == NULL || \
            stackBufferIsNull(T, stack) \
        ) return 1; \
        \
        if (stackIsFull(T, stack)) \
        { \
            Stack(T) new_stack = stackRealloc(T, stack, stack->size * 2); \
            if (stackBufferIsNull(T, &new_stack)) return 1; \
            \
            *stack = new_stack; \
        } \
        \
        stack->buffer[stack->index++] = value; \
        \
        return 0; \
    }

/* --- [static] stackPush() --- */
#define _templatestack_staticstack_stackPush_proto(name, T) \
    int \
    _templatestack_stackPush_type_##name(Stack(name) *stack, T value);

#define _templatestack_staticstack_stackPush_impl(name, T) \
    int \
    _templatestack_stackPush_type_##name(Stack(name) *stack, T value) \
    { \
        if ( \
            stack == NULL || \
            stackIsFull(name, stack) \
        ) return 1; \
        \
        stack->buffer[stack->index++] = value; \
        \
        return 0; \
    }

/* --- stackPop() --- */
#define _templatestack_stackPop_proto(T) \
    T \
    _templatestack_stackPop_type_##T(Stack(T) *stack);

#define _templatestack_stackPop_impl(T) \
    T \
    _templatestack_stackPop_type_##T(Stack(T) *stack) \
    { \
        static const T empty = {0}; \
        T result; \
        \
        if ( \
            stack == NULL || \
            stackBufferIsNull(T, stack) || \
            stackIsEmpty(T, stack) \
        ) return empty; \
        \
        result = stack->buffer[--(stack->index)]; \
        \
        return result; \
    }

/* --- [static] stackPop() --- */
#define _templatestack_staticstack_stackPop_proto(name, T) \
    T \
    _templatestack_stackPop_type_##name(Stack(name) *stack);

#define _templatestack_staticstack_stackPop_impl(name, T) \
    T \
    _templatestack_stackPop_type_##name(Stack(name) *stack) \
    { \
        static const T empty = {0}; \
        T result; \
        \
        if ( \
            stack == NULL || \
            stackIsEmpty(name, stack) \
        ) return empty; \
        \
        result = stack->buffer[--(stack->index)]; \
        \
        return result; \
    }

/* --- stackPeek() --- */
#define _templatestack_stackPeek_proto(T) \
    T \
    _templatestack_stackPeek_type_##T(const Stack(T) *stack);

#define _templatestack_stackPeek_impl(T) \
    T \
    _templatestack_stackPeek_type_##T(const Stack(T) *stack) \
    { \
        static const T empty = {0}; \
        \
        if ( \
            stack == NULL || \
            stackBufferIsNull(T, stack) || \
            stackIsEmpty(T, stack) \
        ) return empty; \
        \
        return stack->buffer[stack->index-1]; \
    }

/* --- [static] stackPeek() --- */
#define _templatestack_staticstack_stackPeek_proto(name, T) \
    T \
    _templatestack_stackPeek_type_##name(const Stack(name) *stack);

#define _templatestack_staticstack_stackPeek_impl(name, T) \
    T \
    _templatestack_stackPeek_type_##name(const Stack(name) *stack) \
    { \
        static const T empty = {0}; \
        \
        if ( \
            stack == NULL || \
            stackIsEmpty(name, stack) \
        ) return empty; \
        \
        return stack->buffer[stack->index-1]; \
    }

/* --- stackPeekAt() --- */
#define _templatestack_stackPeekAt_proto(T) \
    T \
    _templatestack_stackPeekAt_type_##T(const Stack(T) *stack, size_t index);

#define _templatestack_stackPeekAt_impl(T) \
    T \
    _templatestack_stackPeekAt_type_##T(const Stack(T) *stack, size_t index) \
    { \
        static const T empty = {0}; \
        \
        if ( \
            stack == NULL || \
            stackBufferIsNull(T, stack) || \
            stackIsEmpty(T, stack) || \
            index >= stack->index \
        ) return empty; \
        \
        return stack->buffer[stack->index -index -1]; \
    }

/* --- [static] stackPeekAt() --- */
#define _templatestack_staticstack_stackPeekAt_proto(name, T) \
    T \
    _templatestack_stackPeekAt_type_##name(const Stack(name) *stack, size_t index);

#define _templatestack_staticstack_stackPeekAt_impl(name, T) \
    T \
    _templatestack_stackPeekAt_type_##name(const Stack(name) *stack, size_t index) \
    { \
        static const T empty = {0}; \
        \
        if ( \
            stack == NULL || \
            stackIsEmpty(name, stack) || \
            index >= stack->index \
        ) return empty; \
        \
        return stack->buffer[stack->index -index -1]; \
    }

/* --- newStack() --- */
#define _templatestack_newStack_proto(T) \
    Stack(T) \
    _templatestack_newStack_type_##T(size_t size);

#define _templatestack_newStack_impl(T) \
    Stack(T) \
    _templatestack_newStack_type_##T(size_t size) \
    { \
        Stack(T) stack = {0}; \
        \
        if (size == 0) size = (TEMPLATE_STACK_DEFAULT_NEW_SIZE); \
        \
        stack.buffer = (TEMPLATE_STACK_MALLOC)(size * sizeof(T)); \
        if (stackBufferIsNull(T, &stack)) return stack; \
        \
        stack.size = size; \
        return stack; \
    }

/* --- deleteStack() --- */
#define _templatestack_deleteStack_proto(T) \
    int \
    _templatestack_deleteStack_type_##T(Stack(T) *stack);

#define _templatestack_deleteStack_impl(T) \
    int \
    _templatestack_deleteStack_type_##T(Stack(T) *stack) \
    { \
        if ( \
            stack == NULL || \
            stackBufferIsNull(T, stack) \
        ) return 1; \
        \
        (TEMPLATE_STACK_FREE)(stack->buffer); \
        \
        stack->buffer = NULL; \
        stack->size = 0; \
        stack->index = 0; \
        return 0; \
    }

/* ---- Template Stack Prototype (for header) ---- */
#define TemplateStack_proto(T) \
    _templatestack_Stack(T) \
    _templatestack_stackIsEmpty_proto(T) \
    _templatestack_stackIsFull_proto(T) \
    _templatestack_stackBufferIsNull_proto(T) \
    _templatestack_stackSize_proto(T) \
    _templatestack_stackBufferSize_proto(T) \
    _templatestack_stackDup_proto(T) \
    _templatestack_stackRealloc_proto(T) \
    _templatestack_stackClear_proto(T) \
    _templatestack_stackReverse_proto(T) \
    _templatestack_stackPush_proto(T) \
    _templatestack_stackPop_proto(T) \
    _templatestack_stackPeek_proto(T) \
    _templatestack_stackPeekAt_proto(T) \
    _templatestack_newStack_proto(T) \
    _templatestack_deleteStack_proto(T)

/* ---- Template Stack with Static Prototype (for header inline part) ---- */
#define TemplateStack_static_proto(T) \
    _templatestack_Stack(T) \
    static _templatestack_stackIsEmpty_proto(T) \
    static _templatestack_stackIsFull_proto(T) \
    static _templatestack_stackBufferIsNull_proto(T) \
    static _templatestack_stackSize_proto(T) \
    static _templatestack_stackBufferSize_proto(T) \
    static _templatestack_stackDup_proto(T) \
    static _templatestack_stackRealloc_proto(T) \
    static _templatestack_stackClear_proto(T) \
    static _templatestack_stackReverse_proto(T) \
    static _templatestack_stackPush_proto(T) \
    static _templatestack_stackPop_proto(T) \
    static _templatestack_stackPeek_proto(T) \
    static _templatestack_stackPeekAt_proto(T) \
    static _templatestack_newStack_proto(T) \
    static _templatestack_deleteStack_proto(T)

/* ---- Template Stack Implementation (for source file) ---- */
#define TemplateStack_impl(T) \
    _templatestack_stackIsEmpty_impl(T) \
    _templatestack_stackIsFull_impl(T) \
    _templatestack_stackBufferIsNull_impl(T) \
    _templatestack_stackSize_impl(T) \
    _templatestack_stackBufferSize_impl(T) \
    _templatestack_stackDup_impl(T) \
    _templatestack_stackRealloc_impl(T) \
    _templatestack_stackClear_impl(T) \
    _templatestack_stackReverse_impl(T) \
    _templatestack_stackPush_impl(T) \
    _templatestack_stackPop_impl(T) \
    _templatestack_stackPeek_impl(T) \
    _templatestack_stackPeekAt_impl(T) \
    _templatestack_newStack_impl(T) \
    _templatestack_deleteStack_impl(T)

/* ---- Template Stack with Static Implement. (for source inline part) ---- */
#define TemplateStack_static_impl(T) \
    static _templatestack_stackIsEmpty_impl(T) \
    static _templatestack_stackIsFull_impl(T) \
    static _templatestack_stackBufferIsNull_impl(T) \
    static _templatestack_stackSize_impl(T) \
    static _templatestack_stackBufferSize_impl(T) \
    static _templatestack_stackDup_impl(T) \
    static _templatestack_stackRealloc_impl(T) \
    static _templatestack_stackClear_impl(T) \
    static _templatestack_stackReverse_impl(T) \
    static _templatestack_stackPush_impl(T) \
    static _templatestack_stackPop_impl(T) \
    static _templatestack_stackPeek_impl(T) \
    static _templatestack_stackPeekAt_impl(T) \
    static _templatestack_newStack_impl(T) \
    static _templatestack_deleteStack_impl(T)

/* ---- Template Stack Inline (all in one) ---- */
#define TemplateStack_inline(T) \
    _templatestack_Stack(T) \
    TemplateStack_static_impl(T)

/* ---- Static Stack Prototype (with static memory, for header) ---- */
#define StaticStack_proto(name, T, size) \
    _templatestack_staticstack_Stack(name, T, size) \
    _templatestack_staticstack_stackIsEmpty_proto(name, T) \
    _templatestack_staticstack_stackIsFull_proto(name, T) \
    _templatestack_staticstack_stackSize_proto(name, T) \
    _templatestack_staticstack_stackClear_proto(name, T) \
    _templatestack_staticstack_stackReverse_proto(name, T) \
    _templatestack_staticstack_stackPush_proto(name, T) \
    _templatestack_staticstack_stackPop_proto(name, T) \
    _templatestack_staticstack_stackPeek_proto(name, T) \
    _templatestack_staticstack_stackPeekAt_proto(name, T)

/* ---- Static Stack with Static Prototype
 * (with static memory, for header inline part) ---- */
#define StaticStack_static_proto(name, T, size) \
    _templatestack_staticstack_Stack(name, T, size) \
    static _templatestack_staticstack_stackIsEmpty_proto(name, T) \
    static _templatestack_staticstack_stackIsFull_proto(name, T) \
    static _templatestack_staticstack_stackSize_proto(name, T) \
    static _templatestack_staticstack_stackClear_proto(name, T) \
    static _templatestack_staticstack_stackReverse_proto(name, T) \
    static _templatestack_staticstack_stackPush_proto(name, T) \
    static _templatestack_staticstack_stackPop_proto(name, T) \
    static _templatestack_staticstack_stackPeek_proto(name, T) \
    static _templatestack_staticstack_stackPeekAt_proto(name, T)

/* ---- Static Stack Implementation
 * (with static memory, for source file) ---- */
#define StaticStack_impl(name, T) \
    _templatestack_staticstack_stackIsEmpty_impl(name, T) \
    _templatestack_staticstack_stackIsFull_impl(name, T) \
    _templatestack_staticstack_stackSize_impl(name, T) \
    _templatestack_staticstack_stackClear_impl(name, T) \
    _templatestack_staticstack_stackReverse_impl(name, T) \
    _templatestack_staticstack_stackPush_impl(name, T) \
    _templatestack_staticstack_stackPop_impl(name, T) \
    _templatestack_staticstack_stackPeek_impl(name, T) \
    _templatestack_staticstack_stackPeekAt_impl(name, T)

/* ---- Static Stack with Static Implementation
 * (with static memory, for source inline part) ---- */
#define StaticStack_static_impl(name, T) \
    static _templatestack_staticstack_stackIsEmpty_impl(name, T) \
    static _templatestack_staticstack_stackIsFull_impl(name, T) \
    static _templatestack_staticstack_stackSize_impl(name, T) \
    static _templatestack_staticstack_stackClear_impl(name, T) \
    static _templatestack_staticstack_stackReverse_impl(name, T) \
    static _templatestack_staticstack_stackPush_impl(name, T) \
    static _templatestack_staticstack_stackPop_impl(name, T) \
    static _templatestack_staticstack_stackPeek_impl(name, T) \
    static _templatestack_staticstack_stackPeekAt_impl(name, T)

/* ---- Static Stack Inline (with static memory, all in one) ---- */
#define StaticStack_inline(name, T, size) \
    _templatestack_staticstack_Stack(name, T, size) \
    StaticStack_static_impl(name, T)

/* ---- Closing extern if C++ --- */
#ifdef __cplusplus
}
#endif

#endif /* _TEMPLATE_STACK_H */
