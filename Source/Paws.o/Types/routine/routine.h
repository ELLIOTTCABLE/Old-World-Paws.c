#define ROUTINE_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(AST_H)
# include "ast.h"
#endif
#if !defined(LIST_H)
# include "Paws.o/Types/list/list.h"
#endif

#include <stdbool.h>


/* =========================
= `infrastructure routine` =
========================= */

/* ### Data Types & Structures ### */

/* Don’t you gotta love C’s syntax for function pointers? :D Anyway, this type represents the standard function
 * signature for a ‘native routine’ in Paws—that is, if you write a C function that is intended to be usable as
 * a `routine` from libspace, then it needs to match this signature, and then be wrapped in a `routine` object
 * with `Routine->create()`. */
//  typedef   void (*)(execution exe)         native;
    typedef   void (*native)(execution exe)         ;

/* `infrastructure routine`, the core interally-available *code* data structure.
 *--
 * TODO: More description! */
struct E(routine) {
  E(ll)   content; /* The `ll` behind this `routine`’s `list` interface */
  
  bool    native; /* Whether or not `implementation` is a pointer to a native function */ 
  void   *implementation; /* A pointer to either a `SCOPE` `node` (this routine’s AST), or a native function */
};


/* ### Method Declarations ### */

struct E(Routine) {
  /* `Routine` functions */
  E(routine)    (*create)     ( void *implementation, bool native );
  
  /* `struct routine` methods */
  E(thing)      (*thing)      ( E(routine) this );
  void          (*execute)    ( E(routine) this );
};
#if !defined(EXTERNALIZE)
  struct E(Routine) extern *Routine;
#endif

void    Paws__register_Routine    ( void );
