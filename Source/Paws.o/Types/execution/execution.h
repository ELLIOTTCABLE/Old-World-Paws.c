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
  E(ll)     content; /* The `ll` behind this `routine`’s `list` interface */
  
  E(node)  *node; /* The AST node associated with this `execution`’s `routine`’s ‘current’ state */
};


/* ### Method Declarations ### */

struct E(Execution) {
  /* `Execution` functions */
  E(execution)    (*create)     ( void );
  
  /* `struct execution` methods */
  E(thing)        (*thing)      ( E(execution) this );
  void            (*exercise)   ( E(execution) this );
};
#if !defined(EXTERNALIZE)
  struct E(Execution) extern *Execution;
#endif

void    Paws__register_Execution    ( void );
