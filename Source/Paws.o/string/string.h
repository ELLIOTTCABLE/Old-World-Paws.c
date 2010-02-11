#define STRING_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#if !defined(LL_H)
# include "Paws.o/Core/ll.h"
#endif


/* ========================
= `infrastructure string` =
======================== */

/* ### Data Types & Structures ### */

typedef  unsigned long long int  E(string_size);

/* `infrastructure string`, the immutable character-string data structure of
 * Paws, is herein implemented natively with UTF-8 byte strings.
 */
struct E(string) {
  E(ll)           content; /* The `ll` behind this `string`’s `list` interface */
  
  union {
    struct packed {
      char*           long_array;
      E(string_size)  available;
    }     otherwise;
    char  short_array[sizeof(char*) + sizeof(E(string_size))];
  }               native;
  E(string_size)  bytes;
};


/* ### Method Declarations ### */

struct E(String) {
  /* `String` functions */
  E(string)   (*create)   ( char[], E(string_size) );
  
  /* `struct numeric` methods */
  E(thing)   (*to_thing) ( E(string) );
};
#if !defined(EXTERNALIZE)
  struct E(String) extern const String;
#endif
