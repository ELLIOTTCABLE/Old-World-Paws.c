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


/* =========================
= `infrastructure routine` =
========================= */

/* ### Data Types & Structures ### */

/* `infrastructure routine`, the core interally-available *code* data structure.
 *--
 * TODO: More description! */
struct E(routine) {
  E(ll)     content; /* The `ll` behind this `routine`’s `list` interface */
  
  E(node)   scope; /* A pointer to a `SCOPE` `node` (this routine’s AST) */
};


/* ### Method Declarations ### */

struct E(Routine) {
  /* `Routine` functions */
  E(routine)    (*create)     ( E(node) scope );
  
  /* `struct routine` methods */
  E(thing)      (*thing)      ( E(routine) this );
  void          (*execute)    ( E(routine) this );
};
#if !defined(EXTERNALIZE)
  struct E(Routine) extern *Routine;
#endif

void    Paws__register_Routine    ( void );
