#ifndef _TEMPLATE_STACK_H_
#define _TEMPLATE_STACK_H_

/* ---- Includes ---- */
#include <stddef.h>

/* ---- Implementation macros ---- */
#define _templatestack_struct(T) \
    struct _templatestack_##T { \
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
