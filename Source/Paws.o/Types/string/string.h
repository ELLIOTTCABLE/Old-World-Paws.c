#if !defined(STRING_DECLARATIONS)
# define     STRING_DECLARATIONS

#include "Paws.o/Core.h"
#include "Paws.o/Types/Types.h"

#include "Paws.o/Types/list/list.h"
#include "Paws.o/Ancillary/Magazine/Magazine.h"


/* ========================
= `infrastructure string` =
======================== */

/* ### Data Types & Structures ### */

typedef   unsigned int    E(string_size);

/* `infrastructure string`, the immutable character-string data structure of Paws, is herein implemented natively
 * with UTF-8 byte strings. */
struct E(string) {
  E(ll)             content; /* The `ll` behind this `string`’s `list` interface */
  
  /* This complex nested structure provides a very efficient storage for very short byte strings (anything less
   * than (usually) four bytes, including the `NULL` terminator). This is because those short-strings are stored
   * inline in the struct, instead of in another memory location; this also allows for a single cache entry. If
   * the string is *longer* than that, it is stored in another memory location, and a pointer is stored in the
   * equivalent space instead. */
  union {
    char             *long_array;
    char              short_array[sizeof(char*)];
  }                 native;
  E(string_size)    bytes;
};


/* ### Method Declarations ### */

struct E(String) {
  /* `String` functions */
  E(string)   (*allocate)   ( char nate[] );
  E(string)   (*embody)     ( char nate[], E(magazine) store );
  
  /* `struct numeric` methods */
  E(thing)    (*thing)      ( E(string) this );
  char*       (*native)     ( E(string) this );
};
#if !defined(EXTERNALIZE)
  struct E(String) extern *String;
#endif

void    Paws__register_String   ( void );

#endif
