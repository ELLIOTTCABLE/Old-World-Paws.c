#include "routine.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* =========================
= `infrastructure routine` =
========================= */

/* ### Method Declarations ### */

routine     Routine__allocate   (node   implementation);
routine     Routine__expose     (native implementation, bool simple);

thing       routine__thing      (routine this);
void        routine__execute    (routine this, thing argument);

                             struct Routine // »
                                   *Routine   = NULL;
void Paws__register_Routine(void) { Routine   = malloc(sizeof(struct Routine));
                              Paws->Routine   = Routine;
  
  struct Routine // »
  data = {
    .allocate   = Routine__allocate,
    .expose     = Routine__expose,
    
    .thing      = routine__thing,
    .execute    = routine__execute
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
routine _Routine__allocate(void  *implementation, bool nate, bool simple);
routine  Routine__allocate(node   implementation) { return _Routine__allocate((void *)implementation, false, false); }
routine  Routine__expose  (native implementation,            bool simple) //»
                                                  { return _Routine__allocate((void *)implementation, true, simple); }
routine _Routine__allocate(void  *implementation, bool nate, bool simple) {
  routine this = malloc(sizeof(struct routine));
  
  this->content = LL->allocate();
  
  /* TODO: Check if `implementation` is actually a `SCOPE`-type `node`. */
  this->simple            = simple;
  this->native            = nate;
  this->implementation    = nate ? implementation : Node->duplicate(implementation);
  
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

/* This executes a `routine` directly, without requiring that you properly setting up an `execution`. Unless you
 * have a reason to be using this, you should probably be calling `Execution->exercise()` instead. */
void routine__execute(routine this, thing argument) {
  if (this->native) {
    if (this->simple)   ( (void (*)(thing))    this->implementation )(argument                   );
                 else   ( (void (*)(execution))this->implementation )(Paws->Execution->allocate());
  } else {
    /* TODO: Implement me! */
  }
  
  /* It’s important to note that this might not ever get around to `return`ing, because asynchronous routines
   * have a good chance of `pthread_exit(3)`ing (or otherwise terminating the `routine` execution early), if they
   * farm out a call to another `routine` or something. */
  return;
}
