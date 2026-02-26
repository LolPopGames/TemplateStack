#ifndef _TEMPLATE_STACK_H_
#define _TEMPLATE_STACK_H_

/* ---- Includes ---- */
#include <stddef.h>

/* ---- API functions ---- */
#define Stack(T) struct _templatestack_##T

/* ---- Implementation macros ---- */
#define _templatestack_Stack(T) \
    Stack(T) { \
        T *buffer; \
        size_t index; \
        size_t size; \
    }; \

/* ---- Template Stack Prototype (for header) ---- */
#define TemplateStack_proto(T)

/* ---- Template Stack Implementation (for source file) ---- */
#define TemplateStack_impl(T)

/* ---- Template Stack Inline (all in one) ---- */
#define TemplateStack_inline(T)

/* ---- Template Stack Static (all functions are static) ---- */
#define TemplateStack_static(T)

#endif /* _TEMPLATE_STACK_H_ */
