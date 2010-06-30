#if !defined(CORE_DECLARATIONS)
# define     CORE_DECLARATIONS

/* This file is included to nearly every other header in the Paws codebase; it
 * provides macros and definitions necessary throughout the codebase.
 * 
 * You should never have a reason to include or use this file; it’s included
 * everywhere it is necessary.
 */


/* This macro is defined in one of two ways: if one or more Paws headers are
 * included manually, or if `INTERNALIZE` is defiend (see `Paws.c`), then the
 * `E()` macro has no effect (the name is not transformed.) However, if one
 * includes the entire Paws header-set at once (via `#include "Paws.c"`), then
 * `EXTERNALIZE` will be set, thus causing `E()` to, well, make names safe for
 * externalization. */
#if defined(EXTERNALIZE)
# define E(NAME) \
    Paws__ ## NAME
#else
# define E(NAME) \
    NAME
#endif

// FIXME: It seems this is broken, at least in `clang`
// #if __has_feature(attribute_constructor)
# define constructor __attribute__((constructor))
// #endif
// #if __has_feature(attribute_packed)
# define packed      __attribute__((packed))
// #endif

#endif
