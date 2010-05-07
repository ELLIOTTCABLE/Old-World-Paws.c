#define LIST_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(LL_H)
# include "ll.h"
#endif


/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 */
struct E(list) {
E(ll)   content; /* The `ll` behind this `list` */
};


/* ### Method Declarations ### */

struct E(List) {
  /* `List` functions */
E(list)     (*create)           ( void );
E(list)     (*create_naughty)   ( void );
  
  /* `struct list` methods */
E(thing)    (*to_thing)   ( E(list) this );
  void      (*insert)     ( E(list) this, E(thing) child, E(ll_size) index );
  void      (*prefix)     ( E(list) this, E(thing) child );
  void      (*affix)      ( E(list) this, E(thing) child );
E(thing)    (*at)         ( E(list) this,                 E(ll_size) index );
};
#if !defined(EXTERNALIZE)
  struct E(List) extern const List;
#endif
