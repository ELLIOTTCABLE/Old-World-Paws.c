#define LL_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#include <limits.h>

/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

typedef  unsigned long long int  ll_size;

/* This implements a pseudo-‘doubly-linked list’ structure that is the data
 * storage system responsible for `infrastructure list`, and every other core
 * datatype based thereupon.
 * 
 * Note: This is not a traditional linked list. We don’t iterate elements
 *       until reaching a `NULL` pointer; instead, we store (and maintain) the
 *       length (in nodes) and iterate based on that. This means that
 *       ‘trailing nodes’ (or, if you’re morbid, ‘zombie nodes’) can occur -
 *       nodes appearing before/after the `node` at the last/first index (that
 *       is, according to our stored `length`). This is currently considered
 *       acceptable; they’ll simply be dropped when we affix/prefix elements
 *       (as that process replaces the pointer to the next/previous node.)
 */
struct ll {
  node      first; /* A pointer to the first `node` in this `ll` */
  node      last; /* A pointer to the last `node` in this `ll` */
  ll_size  length; /* The total number of `node`s in this `ll` */
};
struct node {
  thing thing; /* The `thing` stored at this location in the `ll` */
  node  next; /* A pointer to the next `node` in the `ll` */
  node  previous; /* A pointer to the previous `node` in the `ll` */
};

/* ### Method Declarations ### */

struct Paws__LL {
  /* `LL` functions */
  ll    (*create) (void);
  
  /* `struct ll` methods */
  void  (*anterior_insert)  (ll, node, ll_size);
  void  (*posterior_insert) (ll, node, ll_size);
  void  (*prefix) (ll, node);
  void  (*affix)  (ll, node);
  node  (*at)     (ll, ll_size);
};
#if !defined(EXTERNALIZE)
  struct Paws__LL extern const LL;
#endif

struct Paws__Node {
  /* `Node` functions */
  node  (*create) (thing);
  
  /* `struct node` methods */
  void  (*prefix) (node, node);
  void  (*affix)  (node, node);
};
#if !defined(EXTERNALIZE)
  struct Paws__Node extern const Node;
#endif
