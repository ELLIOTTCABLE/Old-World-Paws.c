#define ROUTINE_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#if !defined(LL_H)
# include "Paws.o/list/list.h"
#endif
#if !defined(AST_H)
# include "Paws.o/Core/ast.h"
#endif


/* =========================
= `infrastructure routine` =
========================= */

/* ### Data Types & Structures ### */

/* `infrastructure routine`, the core interally-available *code* data
 * structure.
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
  E(thing)      (*to_thing)   ( E(routine) this );
  
  /* inherited `struct list` methods */
  void          (*insert)     ( E(routine) this, E(thing) child, E(ll_size) index );
  void          (*prefix)     ( E(routine) this, E(thing) child );
  void          (*affix)      ( E(routine) this, E(thing) child );
  E(thing)      (*at)         ( E(routine) this,                 E(ll_size) index );
};
#if !defined(EXTERNALIZE)
  struct E(Routine) extern const Routine;
#endif
