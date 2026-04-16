# Template Stack

![Template Stack](assets/icons/build/logo-white@1.5.png)

[![Release](https://img.shields.io/github/v/release/LolPopGames/TemplateStack?label=Release&color=green)](https://github.com/LolPopGames/TemplateStack/releases/latest)
[![Commit v1.0.0-dev](https://img.shields.io/badge/Commit-v1.0.0--dev-red)](#version)
[![License MIT](https://img.shields.io/badge/License-MIT-orange)](LICENSE.md)

> [!NOTE]
> This is a part of [Template Structures](https://github.com/LolPopGames/TemplateStructures) collection

Table Of Contents:
+ [Template Stack](#template-stack)
    + [Description](#description)
    + [Requirements](#requirements)
    + [Installation](#installation)
    + [Usage](#usage)
        + [Including](#including)
        + [Adding A Type](#adding-a-type)
        + [Version Information](#version-information)
        + [How To Use API](#how-to-use-api)
        + [`Stack(T)`](#stackt)
        + [`Stack(T) newStack(T, size_t size)`](#stackt-newstackt-size_t-size)
        + [`int deleteStack(T, Stack(T) *stack)`](#int-deletestackt-stackt-stack)
        + [`int stackPush(T, Stack(T) *stack, T value)`](#int-stackpusht-stackt-stack-t-value)
        + [`T stackPop(T, Stack(T) *stack)`](#t-stackpopt-stackt-stack)
        + [`T stackPeek(T, const Stack(T) *stack)`](#t-stackpeekt-const-stackt-stack)
        + [`T stackPeekAt(T const Stack(T) *stack, size_t index)`](#t-stackpeekatt-const-stackt-stack-size_t-index)
        + [`int stackClear(T, Stack(T) *stack)`](#int-stackcleart-stackt-stack)
        + [`int stackReverse(T, Stack(T) *stack)`](#int-stackreverset-stackt-stack)
        + [`int stackIsEmpty(T, const Stack(T) *stack)`](#int-stackisemptyt-const-stackt-stack)
        + [`int stackIsFull(T, const Stack(T) *stack)`](#int-stackisfullt-const-stackt-stack)
        + [`int stackBufferIsNull(T, const Stack(T) *stack)`](#int-stackbufferisnullt-const-stackt-stack)
        + [`size_t stackSize(T, const Stack(T) *stack)`](#size_t-stacksizet-const-stackt-stack)
        + [`size_t stackBufferSize(T, const Stack(T) *stack)`](#size_t-stackbuffersizet-const-stackt-stack)
        + [`Stack(T) stackDup(T, const Stack(T) *stack)`](#stackt-stackdupt-const-stackt-stack)
        + [`Stack(T) stackRealloc(T, const Stack(T) *stack, size_t size)`](#stackt-stackrealloct-const-stackt-stack-size_t-size)
        + [Default New Stack Size](#default-new-stack-size)
        + [Custom Allocators](#custom-allocators)
        + [Static Stack](#static-stack)
            + [Adding A Type](#adding-a-type-1)
            + [Functions](#functions)
                + [Not available:](#not-available)
            + [Stack Creation](#stack-creation)
            + [Copying](#copying)
            + [Supported Functions](#supported-functions)
    + [Tests](#tests)
    + [Example](#example)
        + [Compiling](#compiling)
            + [Manually](#manually)
            + [Using Meson](#using-meson)
    + [Contributing](#contributing)
    + [License](#license)
    + [Version](#version)

## Description

**Template Stack** is a **single-header C library**
that implements a stack and allows it to be used with any type

You can create multiple stacks for different types without
writing separate stack implementations

## Requirements

**Template Stack** works with **ANSI C** and later standards,
but some features are only supported in **C99+**

## Installation

The library consists of a **single header** (`TemplateStack.h`)

Simply copy it into your project

## Usage

### Including

To use Template Stack,
include the header either in another header or in a source file:

```c
/* If the file is in the same directory as the current */
#include "TemplateStack.h"

/* If the file is in an include path (-I) */
#include <TemplateStack.h>
```

### Adding A Type

Initially, there are **no types, functions, or objects defined**

You create (template) the stack for your type by using the macros

Add one of these lines outside of any function:

```c
/* Insert instead of T type you need (e.g. `int`) */

/* Creates stack type and function prototypes *
 * (Use in header)                            */
TemplateStack_proto(T)

/* Creates full implementation of all stack functions *
 * (Use in source file)                               */
TemplateStack_impl(T)

/* Static versions (all functions have `static` keyword) */
TemplateStack_static_proto(T)
TemplateStack_static_impl(T)

/* Inline version:                              *
 * Creates stack type and static implementation */
TemplateStack_inline(T)
```

You can create stacks for multiple types:

```c
/* Templates stack for `int`, `long`, `size_t` */
TemplateStack_inline(int)
TemplateStack_inline(long)
TemplateStack_inline(size_t)
```

> [!IMPORTANT]
> _Type T_ must be a single preprocessing token (no spaces or special characters)
>
> For pointers or `struct`/`union`/`enum` types, use a typedef first
>
> For example:
>
> ```c
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
> typedef char *cstr;
> TemplateStack_inline(cstr);
> ```
>
> Always use this defined type in stack API functions

> [!WARNING]
> If _type T_ is structure or union,
> it also must not contain any `const` data members (recursively)
>
> This means that this example will **not** work:
>
> ```c
> struct A
> {
>     int x;
>     /* y is a constant member */
>     const int y;
> }
>
> typedef struct A A_t;
> TemplateStack_inline(A_t) /* Error! */
> ```

### Version Information

The version is stored in the following 3 macros:

+ `TEMPLATE_STACK_MAJOR` (**X**.0.0)
+ `TEMPLATE_STACK_MINOR` (0.**X**.0)
+ `TEMPLATE_STACK_PATCH` (0.0.**X**)

You can check the version like this:

```c
/* >=0.1.0 */
#if (TEMPLATE_STACK_MAJOR > 0) || \
    (TEMPLATE_STACK_MAJOR == 0 && TEMPLATE_STACK_MINOR >= 1)
/* code ... */
#endif
```

Or use `TEMPLATE_STACK_ATLEAST` to check the version more conveniently:

```c
/* Insert numbers separated by commas */
#if TEMPLATE_STACK_ATLEAST(0,3,0) /* At least 0.3.0 */
/* code ... */
#endif
```

### How To Use API

Use the stack type and functions by replacing `T` with your own type

All functions that take a stack as a parameter require a _pointer_ to the stack

Every function provides a code-block example after it's explanation

### `Stack(T)`

Stack type

```c
Stack(int) st;
```

### `Stack(T) newStack(T, size_t size)`

Creates a new stack with the specified count of elements

Don't forget to delete this stack with [`deleteStack()`](#int-deletestacktstackt-stack)

Returns a stack with `NULL` buffer if allocation failed,
check this with [`stackBufferIsNull()`](#int-stackbufferisnulltconst-stackt-stack)

---

You can use the default value, set by
[`TEMPLATE_STACK_DEFAULT_NEW_SIZE`](#default-new-stack-size)

If it is not defined manualy, the default value will be `255`

When you make a stack, you need to specify `0` as size to use default value

> **C99+**: You may not specify the second argument at all and it will default to `0`

```c
/* A stack with 10 int elements */
Stack(int) st = newStack(int, 10);
```

### `int deleteStack(T, Stack(T) *stack)`

Deletes specified stack

Returns exit code:
+ `0` if success
+ non-zero if fail:
    + if deleting a stack twice
    + if stack buffer is `NULL`

```c
deleteStack(int, &st);
```

### `int stackPush(T, Stack(T) *stack, T value)`

Pushes an element to stack

Doubles buffer size (capacity),
if the stack is full

Returns exit code
+ `0` if success
+ non-zero if fail
    + if growing failed
    + if stack buffer is `NULL`

```c
stackPush(int, &st, 107);
```

### `T stackPop(T, Stack(T) *stack)`

Pops top element from stack and returns it

Returns zero-value if:
+ the stack is empty,
+ stack buffer is `NULL`

It is recommended to check
for empty stack (with [`stackIsEmpty()`](#int-stackisemptytconst-stackt-stack)) first,
because a zero-value element cannot be distinguished from an empty stack

```c
int val = stackPop(int, &st);
```

### `T stackPeek(T, const Stack(T) *stack)`

Gives top element from the stack (without removing it)

Returns zero-value if:
+ the stack is empty,
+ stack buffer is `NULL`

It is recommended to check
for empty stack (with [`stackIsEmpty()`](#int-stackisemptytconst-stackt-stack)) first,
because a zero-value element cannot be distinguished from an empty stack

```c
int val = stackPeek(int, &st);
```

### `T stackPeekAt(T const Stack(T) *stack, size_t index)`

Returns the element `index` positions from the top of the stack
without removing it

`index` is zero-based:
+ `0` — top element
+ `1` — next element
+ etc.

Returns zero-value if:
+ the stack is empty
+ the stack buffer is `NULL`
+ `index` is out of range

It is recommended to check for enough elements (using
`index` ≥ [`stackSize()`](#size_t-stacksizetconst-stackt-stack))
first, because a zero-value element cannot be distinguished from an error

```c
/* pre-top element */
int val = stackPeekAt(int, &st, 1);
```

### `int stackClear(T, Stack(T) *stack)`

Removes all elements from the stack without freeing its buffer

Returns exit code:
+ `0` if success
+ non-zero if fail:
    + if the stack is `NULL`

```c
stackPush(int, &st, 10);
stackPush(int, &st, 20);
stackClear(int, &st);

/* the stack is empty now */
```

### `int stackReverse(T, Stack(T) *stack)`

Reverses the stack upside down

Returns exit code:
+ `0` if success
+ non-zero if fail:
    + if stack buffer is `NULL`

```c
stackPush(int, &st, 10);
stackPush(int, &st, 20);
stackPush(int, &st, 30);

stackReverse(int, &st);

/* the stack looks now as:
 * >> [10] <<
 *    [20]
 *    [30]
 */

/* 10, 20, 30 */
printf("%d, ", stackPop(int, &st));
printf("%d, ", stackPop(int, &st));
printf("%d\n",   stackPop(int, &st));
```

### `int stackIsEmpty(T, const Stack(T) *stack)`

Checks if the stack is empty (no elements are now in the stack)

Returns a boolean value `0` (`false`) or `1` (`true`)

```c
if (stackIsEmpty(int, &st))
{
    printf("Stack is empty\n");
}
```

### `int stackIsFull(T, const Stack(T) *stack)`

Checks if the stack is full

Returns a boolean value `0` (`false`) or `1` (`true`)

```c
if (stackIsFull(int, &st))
{
    printf("Stack is full\n");
}
```

### `int stackBufferIsNull(T, const Stack(T) *stack)`

Checks if the stack buffer is null
(e.g. because memory allocation was failed)

Returns a boolean value `0` (`false`) or `1` (`true`)

```c
if (stackBufferIsNull(int, &st))
{
    printf("Stack is invalid\n");
}
```

### `size_t stackSize(T, const Stack(T) *stack)`

Returns number of elements currently in the stack

```c
printf("Stack contains %lu elements right now\n", stackSize(int, &st));
```

### `size_t stackBufferSize(T, const Stack(T) *stack)`

Returns stack buffer size (count of allocated `T` elements, capacity)

```c
printf("Program allocated %lu elements", stackBufferSize(int, &st));
```

### `Stack(T) stackDup(T, const Stack(T) *stack)`

Returns a copy of the stack, or `NULL` buffer if allocation failed

```c
Stack(int) st_copy = stackDup(int, &st);
```

### `Stack(T) stackRealloc(T, const Stack(T) *stack, size_t size)`

Reallocates stack with new size (count of `T` elements)

Deletes original stack and returns a new stack
with the contents copied (or sliced if new size is smaller)

If reallocation fails, returns a stack with `NULL` buffer
and **does not free the original stack**

> [!NOTE]
> The behavior **can be changed** by defining [`TEMPLATE_STACK_REALLOC`](#custom-allocators)
>
> If a custom reallocator is provided:
> + **Failure**: the original stack _may be freed or remain allocated_,
> depending on the implementation of [`TEMPLATE_STACK_REALLOC`](#custom-allocators)
> + **Success**: the original stack is _always deleted_, and the new stack is returned

```c
Stack(int) st_new = stackRealloc(int, &st, 20);
```

### Default New Stack Size

Define `TEMPLATE_STACK_DEFAULT_NEW_SIZE` macro to set a custom
default size then the `0` is entered as size in [`newStack()`](#stackt-newstackt-size_t-size)

The default macro value, if you don't set it manualy is `255`

Define this macro before including **Template Stack**

```c
#define TEMPLATE_STACK_DEFAULT_NEW_SIZE 100
#include "TemplateStack.h"

/* ... in code */
Stack(int) st = newStack(int, 0);
/* or */
Stack(int) st = newStack(int);
```

### Custom Allocators

If you want, you can use a **custom memory allocator**
instead of _C standard library_ functions

To change them, define the following macros **before including the header**:

```c
/* Custom malloc */
#define TEMPLATE_STACK_MALLOC my_malloc

/* Custom free */
#define TEMPLATE_STACK_FREE my_free

/* Optional: Custom realloc                                *
 * The library will still work even if you don't define it */
#define TEMPLATE_STACK_REALLOC my_realloc
```

The behavior of [`stackRealloc()`](#stackt-stackrealloctconst-stackt-stack-size_t-size)
can be modified by providing your own

See the [**note**](#stackt-stackrealloctconst-stackt-stack-size_t-size)
for details

### Static Stack

**Static Stack** is a stack with a **statically allocated memory buffer**

It provides an API similar to the dynamic stack,
but with several differences

#### Adding A Type

Unlike [the dynamic stack](#adding-a-type):
+ `StaticStack_*` macros are used instead of `TemplateStack_*`
+ you must provide a **custom name** for the stack type
+ the buffer size must be specified **at compile time**

Both `name` and type `T` must be a **single preprocessing token**
(no spaces or special characters)

The buffer size must be **a compile-time constant**

Add one of these lines outside of any function:

```c
/* Replace:
 *  name — with your stack name (e.g. INT10)
 *  T    — with your type (e.g. int)
 *  size — with buffer size (e.g. 10)
 */

/* Creates stack type and function prototypes *
 * (Use in header)                            */
StaticStack_proto(name, T, size)

/* Creates full implementation of all stack functions *
 * (Use in source file)                               */
StaticStack_impl(name, T)

/* Static versions (all functions have `static` keyword) */
StaticStack_static_proto(name, T, size)
StaticStack_static_impl(name, T)

/* Inline version:                              *
 * Creates stack type and static implementation */
StaticStack_inline(name, T, size)
```

Use `name` instead of `T` when working with the stack API

#### Functions

The static stack supports almost the same API as the dynamic stack,
except for functions related to memory allocation

##### Not available:

+ [`newStack()`](#stackt-newstacktsize_t-size) — no dynamic allocation
+ [`deleteStack()`](#int-deletestacktstackt-stack) — no manual deallocation required
+ [`stackDup()`](#stackt-stackduptconst-stackt-stack) — can be done via assignment
+ [`stackBufferSize()`](#size_t-stackbuffersizetconst-stackt-stack) — known at compile time
+ [`stackBufferIsNull()`](#int-stackbufferisnulltconst-stackt-stack) — static buffer cannot be `NULL`
+ [`stackRealloc()`](#stackt-stackrealloctconst-stackt-stack-size_t-size) — no reallocation
+ [`stackPushGrow()`](#int-stackpushgrowtstackt-stack-t-value) — no dynamic growth

#### Stack Creation

To create a stack, use standard C initialization:

```c
Stack(INT10) st = {0};
```

No deletion is required — memory is managed automatically

#### Copying

There is no [`stackDup()`](#stackt-stackduptconst-stackt-stack) function,
because copying can be done directly:

```c
Stack(INT10) st_copy = st;
```

#### Supported Functions

The following functions are available:
+ [`stackPush()`](#int-stackpushtstackt-stack-t-value)
+ [`stackPop()`](#t-stackpoptstackt-stack)
+ [`stackPeek()`](#t-stackpeektconst-stackt-stack)
+ [`stackPeekAt()`](#t-stackpeekattconst-stackt-stack-size_t-index)
+ [`stackClear()`](#int-stackcleartstackt-stack)
+ [`stackReverse()`](#int-stackreversetstackt-stack)
+ [`stackIsEmpty()`](#int-stackisemptytconst-stackt-stack)
+ [`stackIsFull()`](#int-stackisfulltconst-stackt-stack)
+ [`stackSize()`](#size_t-stacksizetconst-stackt-stack)

## Tests

**Template Stack** has various tests

To compile they, you need **Meson** and **Ninja** Installed

```bash
$ meson setup build
$ cd build
$ meson compile
```

> [!NOTE]
> **Meson** will also compile an [example](#example) of how to use library

Then run tests with:

```bash
$ meson test
```

## Example

If you need an example of how to use **Template Stack**,
see [`example.c`](example.c), which implements a command-line interface for a stack

### Compiling

There are two ways to compile it:

#### Manually

To compile, use this command (e.g. with `gcc`):

```bash
$ gcc -o example example.c
```

Then run it with:

```bash
$ ./example
```

#### Using Meson

If you have **Meson** and **Ninja** installed, you can do this:

```bash
$ meson setup build
$ cd build
$ meson compile
```

Then run it with:

```bash
$ ./example
```

## Contributing

If you want to contribute to the project,
please read the [`CONTRIBUTING.md`](CONTRIBUTING.md) file

## License

The library is distributed under [the MIT license](LICENSE.md)

## Version

1.0.0 dev
