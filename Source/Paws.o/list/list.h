#define LIST_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#if !defined(LL_H)
# include "Paws.o/Core/ll.h"
#endif


/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 */
struct E(list) {
  E(ll) content; /* The `ll` behind this `list` */
};


/* ### Method Declarations ### */

struct E(List) {
  /* `List` functions */
  E(list) (*create)         (void);
  E(list) (*create_naughty) (void);
  
  /* `struct list` methods */
  E(thing)  (*to_thing) ( E(list) );
    void    (*insert)   ( E(list), E(thing), E(ll_size) );
    void    (*prefix)   ( E(list), E(thing) );
    void    (*affix)    ( E(list), E(thing) );
  E(thing)  (*at)       ( E(list), E(ll_size) );
};
#if !defined(EXTERNALIZE)
  struct E(List) extern const List;
#endif
