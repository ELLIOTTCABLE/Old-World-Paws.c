#include "execution.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* ===========================
= `infrastructure execution` =
=========================== */

/* ### Method Declarations ### */

execution   Execution__create     (void);

thing       execution__thing      (execution this);
void        execution__exercise   (execution this);

                               struct Execution // »
                                     *Execution   = NULL;
void Paws__register_Execution(void) { Execution   = malloc(sizeof(struct Execution));
                                Paws->Execution   = Execution;
  
  struct Execution // »
  data = {
    .create     = Execution__create,
    
    .thing      = execution__thing,
    .exercise   = execution__exercise
  };
  
  memcpy(Execution, &data, sizeof(struct Execution));
}


/* ### Method Implementations ### */

execution Execution__create(void) {
  execution this = malloc(sizeof(struct execution));
  
  this->content = LL->create();
  LL->affix( this->content,
    Element->create(List->thing( List->create_naughty() )) );
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union. */
thing execution__thing(execution this) {
  struct thing something = {
    .isa = EXECUTION,
    .pointer = { .execution = this }
  };
  
  return something;
}

void execution__exercise(execution this) {
  /* TODO: Implement me. */
}
