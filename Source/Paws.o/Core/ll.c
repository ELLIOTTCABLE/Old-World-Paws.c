#include "ll.h"

#include <stdlib.h>


/* =====
= `ll` =
===== */

/* ### Method Declarations ### */

ll    LL__create  (void);

void      ll__anterior_insert   (ll this, element child, ll_size index);
void      ll__posterior_insert  (ll this, element child, ll_size index);
void      ll__prefix  (ll this, element child);
void      ll__affix   (ll this, element child);
element   ll__at      (ll this, ll_size index);

struct Element const Element;
struct LL const LL = {
  .create = LL__create,
  
  .anterior_insert  = ll__anterior_insert,
  .posterior_insert = ll__posterior_insert,
  .prefix = ll__prefix,
  .affix  = ll__affix,
  .at     = ll__at
};


/* ### Method Implementations ### */

/* This method initializes a new `ll`, with no elements. The `first` and `last`
 * are set to `NULL` pointers, and `length` is initialized to zero.
 */
ll LL__create(void) {
  ll this = malloc(sizeof(struct ll));
  
  this->first  = NULL;
  this->last   = NULL;
  this->length = 0;
  
  return this;
}

void ll__anterior_insert(ll this, element child, ll_size index) {
  if (index == 0)
    /* TODO: Error condition, cannot anterior-insert at first position */;
  else {
    Element.affix(LL.at(this, index - 1), child);
    this->length++;
  }
}

void ll__posterior_insert(ll this, element child, ll_size index) {
  if (index == this->length)
    /* TODO: Error condition, cannot posterior-insert at last position */;
  else {
    Element.prefix(LL.at(this, index), child);
    this->length++;
  }
}

/* This method prefixes a new child `element` onto an `ll`. This will ensure
 * that the first element in the `ll`, after the appending, is the new one.
 * 
 * Takes two arguments, the prefixee (`this`), and a `element` to be prefixed
 * onto it as a child.
 */
void ll__prefix(ll this, element child) {
  if (this->length < 1)
    this->last = child;
  else
    Element.prefix( this->first, child );
  this->first = child;
  this->length++;
}

/* This method affixes a new child `element` onto an `ll`. This will ensure
 * that the last element in the `ll`, after the appending, is the new one.
 * 
 * Takes two arguments, the affixee (`this`), and a `element` to be affixed
 * onto it as a child.
 */
void ll__affix(ll this, element child) {
  if (this->length < 1)
    this->first = child;
  else
    Element.affix( this->last, child );
  this->last = child;
  this->length++;
}

/* This method returns a `element` at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `index`.
 */
element ll__at(ll this, ll_size index) { element result; ll_size i;
  
  if (index >= this->length)
    return NULL;
  
  if (index <= this->length / 2) {
    result = this->first;
    
    for (i = 0; i < index; ++i)
      result = result->next;
  } else {
    result = this->last;
    
    for (i = this->length - 1; i > index; --i)
      result = result->next;
  }
  
  return result;
}


/* ==========
= `element` =
========== */

/* ### Method Declarations ### */

element   Element__create  (thing thing);

void      element__prefix  (element this, element other);
void      element__affix   (element this, element other);

struct Element const Element = {
  .create = Element__create,
  
  .prefix = element__prefix,
  .affix = element__affix
};


/* ### Method Implementations ### */

/* This method creates a new `element` for a given `thing`. `next` and
 * `previous` will also be initialized to a `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `element` as `e`.
 */
element Element__create(thing thing) {
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  element this = malloc(sizeof(struct element));
  
  this->thing    = thing;
  this->next     = NULL;
  this->previous = NULL;
  
  return this;
}

/* This method inserts another element *before* this element in the chain of a
 * linked list.
 * 
 * If there’s already a element attached before this element, and there
 * *isn’t* one attached before the element being inserted, then that next-
 * element will be affixed to our new element, thus keeping the chain intact
 * if possible.
 * 
 * Note: See the notes on `Element.affix()`.
 */
void element__prefix(element this, element other) {
  if (this->previous != NULL)
    if (other->previous == NULL)
      element__prefix(other, this->previous);
    else {
      this->previous->next = NULL;
      if (other->next != NULL)
        other->next->previous = NULL; }
  
  other->next     = this;
  this->previous  = other;
}

/* This method inserts another element *after* this element in the chain of a
 * linked list.
 * 
 * If there’s already a element attached after this element, and there *isn’t*
 * one attached after the element being inserted, then that next-element will
 * be affixed to our new element, thus keeping the chain intact if possible.
 * 
 * Note: Realize that due to that copy-next mechanic, you can splice
 *       element-strings on top of eachother, but all elements *after* this
 *       element in the original chain will be lost.
 */
void element__affix(element this, element other) {
  if (this->next != NULL)
    if (other->next == NULL)
      element__affix(other, this->next);
    else {
      this->next->previous = NULL;
      if (other->previous != NULL)
        other->previous->next = NULL; }
  
  other->previous = this;
  this->next      = other;
}
