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

                             struct Routine // »
                                   *Routine   = NULL;
void Paws__register_Routine(void) { Routine   = malloc(sizeof(struct Routine));
                              Paws->Routine   = Routine;
  
  struct Routine // »
  data = {
    .create   = Routine__create,
    
    .thing    = routine__thing
  };
  
  memcpy(Routine, &data, sizeof(struct Routine));
  
  Paws__register_AST();
  Paws__register_Node();
}


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure routine`, and returns a
 * C `routine` (a pointer to a `struct routine`.) It takes an AST `SCOPE`
 * `node` as an argument, and copies the content of that `SCOPE`.wan
 */
routine Routine__create(node scope) {
  routine this = malloc(sizeof(struct routine));
  
  this->content = LL->create();
  LL->affix( this->content,
    Element->create(List->thing( List->create_naughty() )) );
  
  /* TODO: Check if `scope` is actually a `SCOPE` `node`. */
  this->scope = Node->duplicate(scope);
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing routine__thing(routine this) {
  struct thing something = {
    .isa = ROUTINE,
    .pointer = { .routine = this }
  };
  
  return something;
}
