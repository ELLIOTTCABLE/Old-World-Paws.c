#if !defined(LIST_DECLARATIONS)
# define     LIST_DECLARATIONS

#include "Paws.o/Core.h"
#include "Paws.o/Types/Types.h"

#include "ll.h"


/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented as a linked-list, referencing 
 * `thing`s as elements.
 */
struct E(list) {
  E(ll)   content; /* The `ll` behind this `list` */
};


/* ### Method Declarations ### */

struct E(List) {
  /* `List` functions */
  E(list)     (*allocate)         ( void );
  
  /* `struct list` methods */
  E(thing)    (*thing)            ( E(list) this );
  E(list)     (*naughtify)        ( E(list) this );
  void        (*insert)           ( E(list) this, E(thing) child, E(ll_size) idx );
  void        (*prefix)           ( E(list) this, E(thing) child );
  void        (*affix)            ( E(list) this, E(thing) child );
  E(thing)    (*at)               ( E(list) this,                 E(ll_size) idx );
};
#if !defined(EXTERNALIZE)
  struct E(List) extern *List;
#endif

void    Paws__register_List   ( void );

#endif
