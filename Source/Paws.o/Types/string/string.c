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

/* Marks up unused parameters in callbacks */
#define _(_) (void)_


/* ========================
= `infrastructure string` =
======================== */

/* ### Method Declarations ### */

string  String__allocate    (char nate[]);
string  String__embody      (char nate[], magazine store);

thing   string__thing       (string this);
char*   string__native      (string this);

                            struct String // »
                                  *String   = NULL;
void Paws__register_String(void) { String   = malloc(sizeof(struct String));
                             Paws->String   = String;
  
  struct String // »
  data = {
    .allocate   = String__allocate,
    .embody     = String__embody,
    
    .thing      = string__thing,
    .native     = string__native
  };
  
  memcpy(String, &data, sizeof(struct String));
}


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure string`, and returns a C `string` (a pointer to a
 * `struct string`.)
 */
string String__allocate(char nate[]) {
  string this = malloc(sizeof(struct string));
  
  this->content = LL->allocate();
  
  this->bytes = strlen(nate) + 1;
  if (this->bytes <= sizeof(this->native.short_array)) {
    STRCPY(this->native.short_array, nate, this->bytes);
  } else {
    this->native.long_array = malloc(this->bytes);
    STRCPY(this->native.long_array, nate, this->bytes);
  }
  
  return this;
}
thing _String__allocate_for_magazine(magazine _, char key[]) { _(_);
  return (thing){ String->allocate(key), STRING };
}

string String__embody(char nate[], magazine store) {
  if (store->holds != STRING) return NULL;
  return Magazine->get(store, nate, _String__allocate_for_magazine).pointer.string;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union. */
thing string__thing(string this) {
  struct thing something = {
    .isa = STRING,
    .pointer = { .string = this }
  };
  
  return something;
}

/* This method returns a pointer to a C string of UTF-8 characters for a given `list`.
 * 
 * It is important to note that strings are assumed-unmodifiable, so you shouldn’t modify the returned C string
 * in any way. */
char* string__native(string this) {
  if (this->bytes <= sizeof(this->native.short_array))
    return this->native.short_array;
  else
    return this->native.long_array;
}
