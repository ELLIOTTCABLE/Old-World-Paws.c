#define LL_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif


#include <limits.h>


/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

        struct E(ll); /* Our data storage system (a doubly-linked-list) */
        struct E(element); /* A single element of an `ll` */
typedef struct E(ll)*       E(ll);
typedef struct E(element)*  E(element);

typedef   unsigned long long int    E(ll_size);

/* This implements a pseudo-‘doubly-linked list’ structure that is the data
 * storage system responsible for `infrastructure list`, and every other core
 * datatype based thereupon.
 * 
 * Note: This is not a traditional linked list. We don’t iterate elements
 *       until reaching a `NULL` pointer; instead, we store (and maintain) the
 *       length (in elements) and iterate based on that. This means that
 *       ‘trailing elements’ (or, if you’re morbid, ‘zombie elements’) can
 *       occur - elements appearing before/after the `element` at the
 *       last/first index (that is, according to our stored `length`). This is
 *       currently considered acceptable; they’ll simply be dropped when we
 *       affix/prefix elements (as that process replaces the pointer to the
 *       next/previous `element`.)
 *       
 *       In addition, this is not a ‘purist’ implementation; the `element`
 *       itself is not our sole datatype. Instead, we also define a wrapper
 *       element that stores metadata about the linked list structure; this
 *       wrapper (`ll`) is passed around as ‘a linked list,’ instead of a
 *       reference to a given node. An important side effect of this is that,
 *       unlike with a traditional linked list implementation, you can’t
 *       simply take a reference to any node in an existing list and use it as
 *       a *new* list. I consider this a feature; with doubly-linked lists, it
 *       is too dangerous to manually juggle subsets of lists’ elements;
 *       operations are much better preformed on the list *as a whole*. The
 *       `ll` datatype facilitates this.
 */
struct E(ll) {
E(element)    first; /* A pointer to the first `element` in this `ll` */
E(element)    last; /* A pointer to the last `element` in this `ll` */
E(ll_size)    length; /* The total number of `element`s in this `ll` */
};
struct E(element) {
E(thing)      thing; /* The `thing` stored at this location in the `ll` */
E(element)    next; /* A pointer to the next `element` in the `ll` */
E(element)    previous; /* A pointer to the previous `element` in the `ll` */
};


/* ### Method Declarations ### */

struct E(LL) {
  /* `LL` functions */
E(ll)         (*create)             ( void );
  
  /* `struct ll` methods */
  void        (*anterior_insert)    ( E(ll) this, E(element) child, E(ll_size) index );
  void        (*posterior_insert)   ( E(ll) this, E(element) child, E(ll_size) index );
  void        (*prefix)             ( E(ll) this, E(element) child );
  void        (*affix)              ( E(ll) this, E(element) child );
E(element)    (*at)                 ( E(ll) this,                   E(ll_size) index );
};
#if !defined(EXTERNALIZE)
  struct E(LL) extern const LL;
#endif

struct E(Element) {
  /* `Element` functions */
E(element)    (*create)   ( E(thing) thing );
  
  /* `struct element` methods */
  void        (*prefix)   ( E(element) this, E(element) other );
  void        (*affix)    ( E(element) this, E(element) other );
};
#if !defined(EXTERNALIZE)
  struct E(Element) extern const Element;
#endif
