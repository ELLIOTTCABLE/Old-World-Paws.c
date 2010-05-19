#include "routine.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* =========================
= `infrastructure routine` =
========================= */

/* ### Method Declarations ### */

routine   Routine__create     (void *implementation, bool native);

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

/* This method allocates a new `infrastructure routine`, and returns a C `routine` (a pointer to a
 * `struct routine`.) It takes an either an AST’s `SCOPE` `node`, or a pointer to a native C function (the
 * signature of which is expected to match `void (*)(E(execution) exe)`, though the usual function-pointer
 * semantics apply). The second argument is a `bool` describing whether the first argument was the former or the
 * latter (to be `true` in the case of a function pointer).
 * 
 * If you pass in an AST instead of a native implementation, this copies the content of that `SCOPE`, allowing
 * you to destroy or modify the passed AST as you desire. */
routine Routine__create(void *implementation, bool native) {
  routine this = malloc(sizeof(struct routine));
  
  this->content = LL->create();
  LL->affix( this->content,
    Element->create(List->thing( List->create_naughty() )) );
  
  /* TODO: Check if `implementation` is actually a `SCOPE`-type `node`. */
  this->native         = native;
  this->implementation = native ? implementation : Node->duplicate(implementation);
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union. */
thing routine__thing(routine this) {
  struct thing something = {
    .isa = ROUTINE,
    .pointer = { .routine = this }
  };
  
  return something;
}
