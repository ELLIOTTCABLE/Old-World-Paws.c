#include "numeric.h"

#if !defined(LIST_H)
# include "Paws.o/list/list.h"
#endif

#include "Paws.o/Paws.h"

#include <stdlib.h>
#include <string.h>


/* =========================
= `infrastructure numeric` =
========================= */

/* ### Method Declarations ### */

numeric Numeric__create   (int);

thing   numeric__to_thing (numeric);
int     numeric__native   (numeric);

struct Numeric const Numeric = {
  .create   = Numeric__create,
  
  .to_thing = numeric__to_thing,
  .native   = numeric__native
};
void constructor Paws__register_Numeric(void) {
  Paws.Numeric = Numeric; }


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure numeric`, and returns a
 * C `numeric` (a pointer to a `struct numeric`.)
 *--
 * TODO: Global-uniqueness. We need to cache already-created `numeric`s
 *       somewhere, and retreive them when necessary.
 */
numeric Numeric__create(int native) {
  numeric this = malloc(sizeof(struct numeric));
  
  this->content = LL.create();
  LL.affix( this->content,
    Node.create(List.to_thing( List.create_naughty() )) );
  
  this->native = native;
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing numeric__to_thing(numeric this) {
  thing location = malloc(sizeof(struct thing));
  struct thing wrapper = {
    .isa = NUMERIC,
    .pointer = { .numeric = this }
  };
  
  memcpy(location, &wrapper, sizeof(struct thing));
  
  return location;
}

/* This method returns a native C `int` for a given `list`. */
int numeric__native(numeric this) {
  return this->native;
}
