#define LL_H_INCLUDED

#ifndef TYPES_H_INCLUDED
#  include "Paws.o/Types.h"
#endif

/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

typedef   unsigned long int   ll_size;

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
  node    first; /* A pointer to the first `node` in this `ll` */
  node    last; /* A pointer to the last `node` in this `ll` */
  ll_size length; /* The total number of `node`s in this `ll` */
};
struct node {
  thing   thing; /* The `thing` stored at this location in the `ll` */
  node    next; /* A pointer to the next `node` in the `ll` */
  node    previous; /* A pointer to the previous `node` in the `ll` */
};

/* ### Method Declarations ### */

struct LL_methods {
  ll    (*create) (void);
  void  (*anterior_insert)  (ll, node, ll_size);
  void  (*posterior_insert) (ll, node, ll_size);
  void  (*prefix) (ll, node);
  void  (*affix)  (ll, node);
  node  (*at)     (ll, ll_size);
} const extern LL;

struct Node_methods {
  node  (*create) (thing);
  void  (*prefix) (node, node);
  void  (*affix)  (node, node);
} const extern Node;
