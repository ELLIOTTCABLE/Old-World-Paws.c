#define LIST_H_INCLUDED

#ifndef TYPES_H_INCLUDED
#  include "../Types.h"
#endif
#ifndef LL_H_INCLUDED
#  include "../Core/ll.h"
#endif

/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 * 
 * For now, we’re not considering the storage of native data types, such as
 * `infrastructure string` and `infrastructure numeric`. That could get messy.
 */
struct list {
  ll      content; /* The `ll` behind this `list` */
};

/* ### Method Declarations ### */

struct List_methods {
  list  (*create)   (void);
  list  (*create_naughty) (void);
  thing (*to_thing) (list);
  void  (*insert)   (list, thing, ll_size);
  void  (*prefix)   (list, thing);
  void  (*affix)    (list, thing);
  thing (*at)       (list, ll_size);
} const List;
