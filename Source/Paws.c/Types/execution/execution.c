#if !defined(EXECUTION_DECLARATIONS)
# define     EXECUTION_DECLARATIONS

#if !defined(DECLARATIONS)
# define EXECUTION_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.c/Core.h"
#   include "Paws.c/Types/Types.h"

#   include "Paws.c/Types/list/list.c"
#   include "Paws.c/Types/routine/routine.c"
#if defined(EXECUTION_C__BEHEST)
# undef DECLARATIONS
#endif


/* ===========================
= `infrastructure execution` =
=========================== */

/* ### Data Types & Structures ### */

struct E(execution) {
  E(ll)           content; /* The `ll` behind this `routine`’s `list` interface */
  
  /* Since we aren’t currently utilizing an `ast` datatype, this struct pairs a given `node` pointer with the
   * pointer to the root `node` of the tree it belongs to. This allows us to ‘look up’ which `node` pointer is to
   * be indexed into which `routine` associated with this `execution`.
   * 
   * NOTE: This is *not* friendly to homoiconicity; I’m not sure *how* to safely re-index into an AST that can
   *       change at *any time*… >,> One of the many problems with homoiconicity. */
  struct E(sourced_node) {
    E(node)         node;
    E(node)         root;
  }              *nodes; /* An array of node-pairs associated with various `routine`s’ ‘current state’ */
  E(node_size)    size;
};


/* ### Method Declarations ### */

struct E(Execution) {
  /* `Execution` functions */
  E(execution)    (*allocate)   ( void );
  
  /* `struct execution` methods */
  E(thing)        (*thing)      ( E(execution) this );
  void            (*exercise)   ( E(execution) this, E(routine) against );
};
#if !defined(EXTERNALIZE)
  struct E(Execution) extern *Execution;
#endif

void    Paws__register_Execution    ( void );



#endif
#if !defined(DECLARATIONS) && !defined(EXECUTION_IMPLEMENTATION) /* ===================================== BODY */
# define                               EXECUTION_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.c/Paws.c"
#   include <stdlib.h>
#   include <string.h>
#   include <stdbool.h>
# undef  DECLARATIONS

#define REALLOC(ptr, size) \
  ptr = realloc(ptr, size)//;


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

#endif
