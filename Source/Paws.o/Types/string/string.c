#include "string.h"

#if !defined(LIST_H)
# include "Paws.o/Types/list/list.h"
#endif

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM, BYTES) \
  strncpy(TO, FROM, BYTES); TO[BYTES - 1] = '\0'//;


/* ========================
= `infrastructure string` =
======================== */

/* ### Method Declarations ### */

string  String__create    (char native[], string_size bytes);

thing   string__thing     (string this);
char*   string__native    (string this);

struct String const String = {
  .create   = String__create,
  
  .thing    = string__thing,
  .native   = string__native
};
void constructor Paws__register_String(void) { Paws.String = String; }


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure string`, and returns a
 * C `string` (a pointer to a `struct string`.)
 *--
 * TODO: Global-uniqueness. We need to cache already-created `string`s
 *       somewhere, and retreive them when necessary.
 */
string String__create(char native[], string_size bytes) {
  string this = malloc(sizeof(struct string));
  
  this->content = LL.create();
  LL.affix( this->content,
    Element.create(List.thing( List.create_naughty() )) );
  
  this->bytes = bytes;
  if (bytes <= sizeof(this->native.short_array)) {
    STRCPY(this->native.short_array, native, bytes);
  } else {
    /* FIXME: Is maintaining `available` necessary, if `string`s are
     *        immutable? If not, we can remove the entire concept. */
    this->native.otherwise.available = bytes;
    this->native.otherwise.long_array = malloc(bytes);
    STRCPY(this->native.otherwise.long_array, native, bytes);
  }
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing string__thing(string this) {
  struct thing something = {
    .isa = STRING,
    .pointer = { .string = this }
  };
  
  return something;
}

/* This method returns a pointer to a C string of UTF-8 characters for a given
 * `list`.
 * 
 * It is important to note that strings are assumed-unmodifiable, so you
 * shouldn’t modify the returned C string in any way.
 */
char* string__native(string this) {
  if (this->bytes <= sizeof(this->native.short_array))
    return this->native.short_array;
  else
    return this->native.otherwise.long_array;
}
