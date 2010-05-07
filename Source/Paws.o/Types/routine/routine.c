#include "routine.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* =========================
= `infrastructure routine` =
========================= */

/* ### Method Declarations ### */

routine   Routine__create     (node scope);

thing     routine__thing      (routine this);
void      routine__execute    (routine this);

struct Routine const Routine = {
  .create   = Routine__create,
  
  .thing    = routine__thing
};
void constructor Paws__register_Routine(void) { Paws.Routine = Routine; }


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure routine`, and returns a
 * C `routine` (a pointer to a `struct routine`.) It takes an AST `SCOPE`
 * `node` as an argument, and copies the content of that `SCOPE`.wan
 */
routine Routine__create(node scope) {
  routine this = malloc(sizeof(struct routine));
  
  this->content = LL.create();
  LL.affix( this->content,
    Element.create(List.thing( List.create_naughty() )) );
  
  /* TODO: Check if `scope` is actually a `SCOPE` `node`. */
  this->scope = Node.duplicate(scope);
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing routine__thing(routine this) {
  thing location = malloc(sizeof(struct thing));
  struct thing wrapper = {
    .isa = ROUTINE,
    .pointer = { .routine = this }
  };
  
  memcpy(location, &wrapper, sizeof(struct thing));
  
  return location;
}
