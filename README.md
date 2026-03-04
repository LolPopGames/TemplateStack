# Template Stack

[![version 0.1.1-dev](https://img.shields.io/badge/version-0.1.0--dev-red)](#version)
[![license MIT](https://img.shields.io/badge/license-MIT-orange)](LICENSE.md)

## Description

**Template Stack** is a **single-header C library**
that implements a stack and allows it to be used with any type

You can create multiple stacks for different types without
writing separate stack implementations

## Requirements

**Template Stack** works with **ANSI C** and later standards

## Installation

The library consists of a **single header** (`TemplateStack.h`)

Simply copy it into your project

## Usage

### Including

To use Template Stack,
include the header either in another header or in a source file:

```C
/* If the file is in the same directory as the current */
#include "TemplateStack.h"

/* If the file is in an include path (-I) */
#include <TemplateStack.h>
```

### Adding a type

Initially, there are **no types, functions, or objects defined**

You create (template) the stack for your type by using the macros

Add one of these lines outside of any function:

```C
/* Insert instead of T type you need (e.g. `int`) */

/* Creates stack type and function prototypes *
 * (Use in header)                            */
TemplateStack_proto(T)

/* Creates full implementation of all stack functions *
 * (Use in source file)                               */
TemplateStack_impl(T)

/* Static versions (all functions are `static`) */
TemplateStack_static_proto(T)
TemplateStack_static_impl(T)

/* Inline version:                              *
 * Creates stack type and static implementation */
TemplateStack_inline(T)
```

You can create stacks for multiple types:

```C
/* Templates stack for `int`, `long`, `size_t` */
TemplateStack_inline(int)
TemplateStack_inline(long)
TemplateStack_inline(size_t)
```

> [!NOTE]
> Type T must be a single preprocessing token (no spaces or special characters)
>
> For pointers or struct/union/enum types, use a typedef first
>
> For example:
>
> ```C
> struct data
> {
>     uint8_t *buffer;
>     size_t size;
> };
>
> /* defining type first */
> typedef struct data data_t;
> TemplateStack_inline(data_t);
>
> /* defining type also for `char *` */
> typedef char **cstr;
> TemplateStack_inline(cstr);
> ```
>
> Always use this defined type in stack API functions

### Version information

The version is stored in the following 3 macros:

+ `TEMPLATE_STACK_MAJOR` (X.0.0)
+ `TEMPLATE_STACK_MINOR` (0.X.0)
+ `TEMPLATE_STACK_PATCH` (0.0.X)

You can check the version like this:

```C
/* >=0.1.0 */
#if (TEMPLATE_STACK_MAJOR > 0) || \
    (TEMPLATE_STACK_MAJOR == 0 && TEMPLATE_STACK_MINOR >= 1)
/* code ... */
#endif
```

Or use `TEMPLATE_STACK_ATLEAST` to check the version more conveniently:

```C
/* Insert numbers separated by commas */
#if TEMPLATE_STACK_ATLEAST(0,1,0) /* At least 0.1.0 */
/* code ... */
#endif
```

### How to use API

Use the stack type and functions by replacing `T` with your type

The syntax is similar to C++ templates, but uses `()` instead of `<>`
and it always requires to add your `T` type

All functions that take a stack as a parameter require a _pointer_ to the stack.

### `Stack(T)`

Stack type

---

Example:

```C
Stack(int) st;
```

### `Stack(T) newStack(T)(size_t size)`

Creates a new stack with the specified count of elements

Don't forget to delete this stack with `deleteStack(T)`

Returns a stack with `NULL` buffer if allocation failed,
check this with `stackBufferIsNull(T)`

---

Example:

```C
/* A stack with 10 int elements */
Stack(int) st = newStack(int)(10);
```

### `int deleteStack(T)(Stack(T) *stack)`

Deletes specified stack

Returns exit code
(0 if success, other codes if fail,
e.g. if you delete a stack twice,
or if stack buffer is `NULL`)

---

Example:

```C
deleteStack(int)(&st);
```

### `int stackPush(T)(Stack(T) *stack, T value)`

Pushes an element to stack

Returns exit code
(0 if success, other codes if fail,
e.g. if stack is full
or if stack buffer is `NULL`)

---

Example:

```C
stackPush(int)(&st, 107);
```

### `T stackPop(T)(Stack(T) *stack)`

Pops top element from stack and returns it

Returns zero-value if the stack is empty,
or if stack buffer is `NULL`

It is recommended to check
for empty stack (with `stackIsEmpty(T)`) first,
because a zero-value element cannot be distinguished from an empty stack

---

Example:

```C
int val = stackPop(int)(&st);
```

### `T stackPeek(T)(const Stack(T) *stack)`

Gives top element from the stack (without removing it)

Returns zero-value if the stack is empty,
or if stack buffer is `NULL`

It is recommended to check
for empty stack (with `stackIsEmpty(T)`) first,
because a zero-value element cannot be distinguished from an empty stack

---

Example:

```C
int val = stackPeek(int)(&st);
```

### `int stackIsEmpty(T)(const Stack(T) *stack)`

Checks if the stack is empty (no elements are now in the stack)

Returns a boolean value `0` (`false`) or `1` (`true`)

---

Example:

```C
if (stackIsEmpty(int)(&st))
{
    printf("Stack is empty\n");
}
```

### `int stackIsFull(T)(const Stack(T) *stack)`

Checks if the stack is full

Returns a boolean value `0` (`false`) or `1` (`true`)

---

Example:

```C
if (stackIsFull(int)(&st))
{
    printf("Stack is full\n");
}
```

### `int stackBufferIsNull(T)(const Stack(T) *stack)`

Checks if the stack buffer is null
(e.g. because memory allocation was failed)

Returns a boolean value `0` (`false`) or `1` (`true`)

---

Example:

```C
if (stackBufferIsNull(int)(&st))
{
    printf("Stack is invalid\n");
}
```

### `size_t stackSize(T)(const Stack(T) *stack)`

Returns number of elements currently in the stack

---

Example:

```C
printf("Stack contains %lu elements right now\n", stackSize(int)(&st));
```

### `size_t stackBufferSize(T)(const Stack(T) *stack)`

Returns stack buffer size (count of allocated `T` elements, capacity)

---

Example:

```C
printf("Program allocated %lu elements", stackBufferSize(int)(&st));
```

### `Stack(T) stackDup(T)(const Stack(T) *stack)`

Returns a copy of the stack, or `NULL` buffer if allocation failed

---

Example:

```C
Stack(int) st_copy = stackDup(int)(&st);
```

### `Stack(T) stackRealloc(T)(const Stack(T) *stack, size_t size)`

Reallocates stack with new size (count of `T` elements)

Deletes original stack and returns a new stack
with the contents copied (or sliced if new size is smaller)

If reallocation fails, returns a stack with `NULL` buffer
and **does not free the original stack**

---

Example:

```C
Stack(int) st_new = stackRealloc(int)(&st, 20);
```

## Version

0.1.1 dev
