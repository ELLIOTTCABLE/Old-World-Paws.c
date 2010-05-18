#define EXECUTION_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(LIST_H)
# include "Paws.o/Types/list/list.h"
#endif
#if !defined(ROUTINE_H)
# include "Paws.o/Types/routine/routine.h"
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
  E(execution)    (*create)     ( void );
  
  /* `struct execution` methods */
  E(thing)        (*thing)      ( E(execution) this );
  void            (*exercise)   ( E(execution) this, E(routine) against );
};
#if !defined(EXTERNALIZE)
  struct E(Execution) extern *Execution;
#endif

void    Paws__register_Execution    ( void );
