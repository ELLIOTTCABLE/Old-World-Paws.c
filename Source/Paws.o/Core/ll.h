#define LL_H_INCLUDED

#include <limits.h>

#ifndef TYPES_H_INCLUDED
#  include "Paws.o/Types.h"
#endif

/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

/* We must be able to index *every* possible element of an `ll`. However,
 * various methods allow negative indicies; therefore, our signed (‘indexing’)
 * type must be able to just as many positive *and* negative integers as our
 * unsigned, actual-index type.
 */
#if defined(ULONG_MAX) && defined(LLONG_MIN) && defined(LLONG_MAX) && \
    -(LLONG_MIN+1) > (ULONG_MAX-1) && ULONG_MAX <= LLONG_MAX
  typedef   unsigned    long int   ll_usize;
  typedef   signed long long int   ll_ssize;
#elif defined(UINT_MAX) && defined(LONG_MIN) && defined(LONG_MAX) && \
      -(LONG_MIN+1) > (UINT_MAX-1) && UINT_MAX <= LONG_MAX
  typedef   unsigned    int   ll_usize;
  typedef   signed long int   ll_ssize;
#else
  /* This is (more than) a bit extreme, but as far as I can tell, necessary.
   * Unindexable elements are unacceptable.
   */
  typedef   signed int   ll_usize;
  typedef   signed int   ll_ssize;
#endif

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
  ll_usize length; /* The total number of `node`s in this `ll` */
};
struct node {
  thing   thing; /* The `thing` stored at this location in the `ll` */
  node    next; /* A pointer to the next `node` in the `ll` */
  node    previous; /* A pointer to the previous `node` in the `ll` */
};

/* ### Method Declarations ### */

struct LL_methods {
  ll    (*create) (void);
  void  (*anterior_insert)  (ll, node, ll_ssize);
  void  (*posterior_insert) (ll, node, ll_ssize);
  void  (*prefix) (ll, node);
  void  (*affix)  (ll, node);
  node  (*at)     (ll, ll_ssize);
} const extern LL;

struct Node_methods {
  node  (*create) (thing);
  void  (*prefix) (node, node);
  void  (*affix)  (node, node);
} const extern Node;
