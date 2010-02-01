#include <stdlib.h>

#ifndef NUMERIC_H_INCLUDED
#  include "numeric.h"
#endif

#ifndef LIST_H_INCLUDED
#  include "../list/list.h"
#endif

/* =========================
= `infrastructure numeric` =
========================= */

/* ### Method Declarations ### */

numeric numeric__create    (int);
thing   numeric__to_thing  (numeric);

struct Numeric_methods const
Numeric = {
  numeric__create,
  numeric__to_thing
};

/* ### Method Implementations ### */

/* This method allocates a new `infrastructure numeric`, and returns a
 * C `numeric` (a pointer to a C `struct numeric`.)
 */
numeric numeric__create(int native) {
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
  thing wrapper = malloc(sizeof(struct thing)); 
  
  wrapper->isa  = NUMERIC;
  wrapper->pointer.numeric = this;
  
  return wrapper;
}
