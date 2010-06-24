#include "execution.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REALLOC(ptr, size) \
  ptr = realloc(ptr, size)//;


/* ===========================
= `infrastructure execution` =
=========================== */

/* ### Method Declarations ### */

execution   Execution__allocate   (void);

thing       execution__thing      (execution this);
void        execution__exercise   (execution this, routine against);

node*       execution__node_for   (execution this, routine target);

                               struct Execution // »
                                     *Execution   = NULL;
void Paws__register_Execution(void) { Execution   = malloc(sizeof(struct Execution));
                                Paws->Execution   = Execution;
  
  struct Execution // »
  data = {
    .allocate   = Execution__allocate,
    
    .thing      = execution__thing,
    .exercise   = execution__exercise
  };
  
  memcpy(Execution, &data, sizeof(struct Execution));
}


/* ### Method Implementations ### */

execution Execution__allocate(void) {
  execution this = malloc(sizeof(struct execution));
  
  this->content = LL->allocate();
  
  this->nodes = NULL;
  this->size  = 0;
  
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

void execution__exercise(execution this, routine against) {
  /* Descriptive fucking name, amirite? */
  node   *pointer     = execution__node_for(this, against);
  bool    executing   = false;
  
  /* http://tau.pe/14252438483 */
  if (*pointer == NULL)
    executing++;
  
  /* TODO: Implement (the rest of) me. */
  /* Before we can continue with actual interpretation, here, we have to have native routines; that way, we can
   * iterate the words in an expression and throw them directly at a synchronous lookup somewhere. */
}

/* This private method returns a pointer to the latest AST `node` having been executed for a given `routine`
 * against this `execution`. */
node* execution__node_for(execution this, routine target) {
  node    scope   = target->implementation._.scope;
  
  /* I don’t like having to add 1 and then subtract 1 here any more than you, my beautiful, beautiful reader,
   * probably do… but it’s a necessity, as `node_size` is an *unsigned* integer type. If we decrement below zero,
   * it will shat brix. */
  for (node_size l = this->size + 1; l >= 1; --l) {
    if (this->nodes[l - 1].root == scope)
      return &this->nodes[l - 1].node; }
  
  REALLOC(this->nodes, ++this->size);
  this->nodes[this->size - 1].node = NULL;
  this->nodes[this->size - 1].root = scope;
  
  return &this->nodes[this->size - 1].node;
}
