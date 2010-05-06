#include "numeric.h"

#if !defined(LIST_H)
# include "Paws.o/Types/list/list.h"
#endif

#include "Paws.o/Paws.h"

#include <stdlib.h>
#include <string.h>


/* =========================
= `infrastructure numeric` =
========================= */

/* ### Method Declarations ### */

numeric   Numeric__create     (int native);

thing     numeric__to_thing   (numeric this);
int       numeric__native     (numeric this);

void      numeric__insert     (numeric this, thing child, ll_size index);
void      numeric__prefix     (numeric this, thing child);
void      numeric__affix      (numeric this, thing child);
thing     numeric__at         (numeric this,              ll_size index);

struct Numeric const Numeric = {
  .create     = Numeric__create,
  
  .to_thing   = numeric__to_thing,
  .native     = numeric__native,
  
  .insert     = numeric__insert,
  .prefix     = numeric__prefix,
  .affix      = numeric__affix,
  .at         = numeric__at
};
void constructor Paws__register_Numeric(void) { Paws.Numeric = Numeric; }


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
    Element.create(List.to_thing( List.create_naughty() )) );
  
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

void  numeric__insert(numeric this, thing child, ll_size index) {
          List.insert(  (list)this,       child,         index); }
void  numeric__prefix(numeric this, thing child) {
          List.prefix(  (list)this,       child); }
void  numeric__affix (numeric this, thing child) {
          List.affix (  (list)this,       child); }
thing numeric__at    (numeric this,              ll_size index) { return
          List.at    (  (list)this,                      index); }
