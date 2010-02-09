#define LL_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#include <limits.h>

/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

typedef  unsigned long long int  E(ll_size);

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
struct E(ll) {
  E(node)     first; /* A pointer to the first `node` in this `ll` */
  E(node)     last; /* A pointer to the last `node` in this `ll` */
  E(ll_size)  length; /* The total number of `node`s in this `ll` */
};
struct node {
  E(thing)  thing; /* The `thing` stored at this location in the `ll` */
  E(node)   next; /* A pointer to the next `node` in the `ll` */
  E(node)   previous; /* A pointer to the previous `node` in the `ll` */
};

/* ### Method Declarations ### */

struct E(LL) {
  /* `LL` functions */
  E(ll)   (*create) (void);
  
  /* `struct ll` methods */
    void  (*anterior_insert)  ( E(ll), E(node), E(ll_size) );
    void  (*posterior_insert) ( E(ll), E(node), E(ll_size) );
    void  (*prefix) ( E(ll), E(node) );
    void  (*affix)  ( E(ll), E(node) );
  E(node) (*at)     ( E(ll), E(ll_size) );
};
#if !defined(EXTERNALIZE)
  struct E(LL) extern const LL;
#endif

struct E(Node) {
  /* `Node` functions */
  E(node) (*create) ( E(thing) );
  
  /* `struct node` methods */
    void  (*prefix) ( E(node), E(node) );
    void  (*affix)  ( E(node), E(node) );
};
#if !defined(EXTERNALIZE)
  struct E(Node) extern const Node;
#endif
