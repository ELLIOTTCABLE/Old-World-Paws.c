#if !defined(LL_DECLARATIONS)
# define     LL_DECLARATIONS

#if !defined(DECLARATIONS)
# define LL_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Core.h"
#   include "Paws.o/Types/Types.h"

#   include <limits.h>
#if defined(LL_C__BEHEST)
# undef DECLARATIONS
#endif


/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

        struct E(ll); /* Our data storage system (a doubly-linked-list) */
        struct E(element); /* A single element of an `ll` */
typedef struct E(ll)* E(ll);
typedef struct E(element)* E(element);

typedef   unsigned long long int    E(ll_size);

/* This implements a pseudo-‘doubly-linked list’ structure that is the data storage system responsible for
 * `infrastructure list`, and every other core datatype based thereupon.
 * 
 * Note: This is not a traditional linked list. We don’t iterate elements until reaching a `NULL` pointer;
 *       instead, we store (and maintain) the length (in elements) and iterate based on that. This means that
 *       ‘trailing elements’ (or, if you’re morbid, ‘zombie elements’) can occur - elements appearing before /
 *       after the `element` at the last/first index (that is, according to our stored `length`). This is
 *       currently considered acceptable; they’ll simply be dropped when we affix/prefix elements (as that
 *       process replaces the pointer to the next/previous `element`.)
 *       
 *       In addition, this is not a ‘purist’ implementation; the `element` itself is not our sole datatype.
 *       Instead, we also define a wrapper element that stores metadata about the linked list structure; this
 *       wrapper (`ll`) is passed around as ‘a linked list,’ instead of a reference to a given node. An important
 *       side effect of this is that, unlike with a traditional linked list implementation, you can’t simply take
 *       a reference to any node in an existing list and use it as a *new* list. I consider this a feature; with
 *       doubly-linked lists, it is too dangerous to manually juggle subsets of lists’ elements; operations are
 *       much better preformed on the list *as a whole*. The `ll` datatype facilitates this.
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
  E(ll)         (*allocate)           ( void );
  
  /* `struct ll` methods */
  void          (*anterior_insert)    ( E(ll) this, E(element) child, E(ll_size) idx );
  void          (*posterior_insert)   ( E(ll) this, E(element) child, E(ll_size) idx );
  void          (*prefix)             ( E(ll) this, E(element) child );
  void          (*affix)              ( E(ll) this, E(element) child );
  E(element)    (*at)                 ( E(ll) this,                   E(ll_size) idx );
};
#if !defined(EXTERNALIZE)
  struct E(LL) extern *LL;
#endif

struct E(Element) {
  /* `Element` functions */
  E(element)    (*allocate)   ( E(thing) thing );
  
  /* `struct element` methods */
  void          (*prefix)     ( E(element) this, E(element) other );
  void          (*affix)      ( E(element) this, E(element) other );
};
#if !defined(EXTERNALIZE)
  struct E(Element) extern *Element;
#endif

void    Paws__register_LL         ( void );
void    Paws__register_Element    ( void );



#endif
#if !defined(DECLARATIONS) && !defined(LL_IMPLEMENTATION) /* ============================================ BODY */
# define                               LL_IMPLEMENTATION
# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


struct Element *Element; // FIXME: Do we need this forward declaration?

/* ### Method Declarations ### */

ll        LL__allocate            (void);

void      ll__anterior_insert     (ll this, element child, ll_size idx);
void      ll__posterior_insert    (ll this, element child, ll_size idx);
void      ll__prefix              (ll this, element child);
void      ll__affix               (ll this, element child);
element   ll__at                  (ll this,                ll_size idx);

                        struct LL // »
                              *LL   = NULL;
void Paws__register_LL(void) { LL   = malloc(sizeof(struct LL));
  
  struct LL // »
  data = {
    .allocate           = LL__allocate,
    
    .anterior_insert    = ll__anterior_insert,
    .posterior_insert   = ll__posterior_insert,
    .prefix             = ll__prefix,
    .affix              = ll__affix,
    .at                 = ll__at
  };
  
  memcpy(LL, &data, sizeof(struct LL));
}


/* ### Method Implementations ### */

/* This method initializes a new `ll`, with no elements. The `first` and `last` are set to `NULL` pointers, and
 * `length` is initialized to zero. */
ll LL__allocate(void) {
  ll this = malloc(sizeof(struct ll));
  
  this->first  = NULL;
  this->last   = NULL;
  this->length = 0;
  
  return this;
}

void ll__anterior_insert(ll this, element child, ll_size idx) {
  if (idx == 0)
    /* TODO: Error condition, cannot anterior-insert at first position */;
  else {
    Element->affix(LL->at(this, idx - 1), child);
    this->length++;
  }
}

void ll__posterior_insert(ll this, element child, ll_size idx) {
  if (idx == this->length)
    /* TODO: Error condition, cannot posterior-insert at last position */;
  else {
    Element->prefix(LL->at(this, idx), child);
    this->length++;
  }
}

/* This method prefixes a new child `element` onto an `ll`. This will ensure that the first element in the `ll`,
 * after the appending, is the new one.
 * 
 * Takes two arguments, the prefixee (`this`), and a `element` to be prefixed onto it as a child.
 */
void ll__prefix(ll this, element child) {
  if (this->length < 1)
    this->last = child;
  else
    Element->prefix( this->first, child );
  this->first = child;
  this->length++;
}

/* This method affixes a new child `element` onto an `ll`. This will ensure that the last element in the `ll`,
 * after the appending, is the new one.
 * 
 * Takes two arguments, the affixee (`this`), and a `element` to be affixed onto it as a child.
 */
void ll__affix(ll this, element child) {
  if (this->length < 1)
    this->first = child;
  else
    Element->affix( this->last, child );
  this->last = child;
  this->length++;
}

/* This method returns a `element` at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `idx`.
 */
element ll__at(ll this, ll_size idx) { element result; ll_size i;
  
  if (idx >= this->length)
    return NULL;
  
  if (idx <= this->length / 2) {
    result = this->first;
    for (i = 0; i < idx; ++i)
      result = result->next;
  } else {
    result = this->last;
    for (i = this->length - 1; i > idx; --i)
      result = result->next;
  }
  
  return result;
}


/* ==========
= `element` =
========== */

/* ### Method Declarations ### */

element   Element__allocate   (thing thing);

void      element__prefix     (element this, element other);
void      element__affix      (element this, element other);

                             struct Element // »
                                   *Element   = NULL;
void Paws__register_Element(void) { Element   = malloc(sizeof(struct Element));
  
  struct Element // »
  data = {
    .allocate   = Element__allocate,

    .prefix   = element__prefix,
    .affix    = element__affix
  };
  
  memcpy(Element, &data, sizeof(struct Element));
}


/* ### Method Implementations ### */

/* This method creates a new `element` for a given `thing`. `next` and `previous` will also be initialized to a
 * `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `element` as `e`.
 */
element Element__allocate(thing target) {
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  element this = malloc(sizeof(struct element));
  
  memcpy(&this->thing, &target, sizeof(struct thing));
  this->next     = NULL;
  this->previous = NULL;
  
  return this;
}

/* This method inserts another element *before* this element in the chain of a linked list.
 * 
 * If there’s already a element attached before this element, and there *isn’t* one attached before the element
 * being inserted, then that next- element will be affixed to our new element, thus keeping the chain intact if
 * possible.
 * 
 * Note: See the notes on `Element->affix()`.
 */
void element__prefix(element this, element other) {
  if (this->previous != NULL) {
    if (other->previous == NULL) {
      element__prefix(other, this->previous);
    }
    else {
      this->previous->next = NULL;
      if (other->next != NULL) {
        other->next->previous = NULL; 
      }
    }
  }
  other->next     = this;
  this->previous  = other;
}

/* This method inserts another element *after* this element in the chain of a linked list.
 * 
 * If there’s already a element attached after this element, and there *isn’t* one attached after the element
 * being inserted, then that next-element will be affixed to our new element, thus keeping the chain intact if
 * possible.
 * 
 * Note: Realize that due to that copy-next mechanic, you can splice element-strings on top of eachother, but all
 *       elements *after* this element in the original chain will be lost.
 */
void element__affix(element this, element other) {
  if (this->next != NULL) {
    if (other->next == NULL) {
      element__affix(other, this->next);
    }
    else {
      this->next->previous = NULL;
      if (other->previous != NULL) {
        other->previous->next = NULL; 
      }
    }
  }
  
  other->previous = this;
  this->next      = other;
}

#endif
