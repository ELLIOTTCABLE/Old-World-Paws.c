#define ROUTINE_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#if !defined(LL_H)
# include "Paws.o/list/list.h"
#endif


/* ========================
= `infrastructure routine` =
======================== */

/* ### Data Types & Structures ### */

/* The maximum children of a single node of a processing unit, or the maxiumum
 * characters in a node’s textual content */
typedef   unsigned long long int    E(ast_node_size);

/* `infrastructure routine`, the core interally-available *code* data
 * structure.
 * TODO: More description! */
struct E(routine) {
  E(ll)                 content; /* The `ll` behind this `routine`’s `list` interface */
  
  struct E(ast_node) {
    enum {
           E(SCOPE_TYPE),
      E(EXPRESSION_TYPE),
            E(WORD_TYPE)
    }                   type;
    
    E(ast_node_size)    size;
    void               *content;
  }                    *ast;
};


/* ### Method Declarations ### */

struct E(Routine) {
  /* `Routine` functions */
  E(routine)            (*create)     ( struct E(ast_node) *scope_node );
  
  /* `struct routine` methods */
  E(thing)              (*to_thing)   ( E(routine) this );
  struct E(ast_node)*   (*native)     ( E(routine) this );
  
  /* inherited `struct list` methods */
  void                  (*insert)     ( E(routine) this, E(thing) child, E(ll_size) index );
  void                  (*prefix)     ( E(routine) this, E(thing) child );
  void                  (*affix)      ( E(routine) this, E(thing) child );
  E(thing)              (*at)         ( E(routine) this,                 E(ll_size) index );
};
#if !defined(EXTERNALIZE)
  struct E(Routine) extern const Routine;
#endif
