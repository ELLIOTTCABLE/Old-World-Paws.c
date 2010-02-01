#include <stdlib.h>

#ifndef LL_H_INCLUDED
#  include "ll.h"
#endif

/* =====
= `ll` =
===== */

/* ### Method Declarations ### */

ll    ll__create  (void);
void  ll__anterior_insert   (ll, node, ll_size);
void  ll__posterior_insert  (ll, node, ll_size);
void  ll__prefix  (ll, node);
void  ll__affix   (ll, node);
node  ll__at      (ll, ll_size);

struct LL_methods const
LL = {
  ll__create,
  ll__anterior_insert,
  ll__posterior_insert,
  ll__prefix,
  ll__affix,
  ll__at
};

node  node__create  (thing);
void  node__prefix  (node, node);
void  node__affix   (node, node);

struct Node_methods const
Node = { node__create, node__prefix, node__affix };

/* ### Method Implementations ### */

/* This method initializes a new ll, with no nodes. The `first` and `last` are
 * set to `NULL` pointers, and `length` is initialized to zero.
 */
ll ll__create(void) {
  ll this = malloc(sizeof(struct ll));
  
  this->first  = NULL;
  this->last   = NULL;
  this->length = 0;
  
  return this;
}

void ll__anterior_insert(ll this, node child, ll_size index) {
  if (index == this->length - 1)
    /* TODO: Error condition, cannot anterior-insert at last position */;
  else {
    Node.prefix(LL.at(this, index), child);
    this->length++;
  }
}

void ll__posterior_insert(ll this, node child, ll_size index) {
  if (index == 0)
    /* TODO: Error condition, cannot posterior-insert at first position */;
  else {
    Node.affix(LL.at(this, index - 1), child);
    this->length++;
  }
}

/* This method prefixes a new child `node` onto an `ll`. This will ensure that
 * the first element in the `ll`, after the appending, is the new node.
 * 
 * Takes two arguments, the prefixee (`this`), and a `node` to be prefixed
 * onto it as a child.
 */
void ll__prefix(ll this, node child) {
  if (this->length < 1)
    this->last = child;
  else
    Node.prefix( this->first, child );
  this->first = child;
  this->length++;
}

/* This method affixes a new child `node` onto an `ll`. This will ensure that
 * the last element in the `ll`, after the appending, is the new node.
 * 
 * Takes two arguments, the affixee (`this`), and a `node` to be affixed onto
 * it as a child.
 */
void ll__affix(ll this, node child) {
  if (this->length < 1)
    this->first = child;
  else
    Node.affix( this->last, child );
  this->last = child;
  this->length++;
}

/* This method returns a `node` at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `index`.
 */
node ll__at(ll this, ll_size index) { node result; ll_size i;
  
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

/* This method creates a new `node` for a given `thing`. `next` and `previous`
 * will also be initialized to a `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `node` as `e`.
 */
node node__create(thing thing) {
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  node this = malloc(sizeof(struct node));
  
  this->thing    = thing;
  this->next     = NULL;
  this->previous = NULL;
  
  return this;
}

/* This method inserts another node *before* this node in the chain of a
 * linked list.
 * 
 * If there’s already a node attached before this node, and there *isn’t* one
 * attached before the node being inserted, then that next-node will be
 * affixed to our new node, thus keeping the chain intact if possible.
 * 
 * Note: See the notes on `Node.affix()`.
 */
void node__prefix(node this, node other) {
  if (this->previous != NULL)
    if (other->previous == NULL)
      node__prefix(other, this->previous);
    else
      this->previous->next = NULL;
  
  other->next     = this;
  this->previous  = other;
}

/* This method inserts another node *after* this node in the chain of a
 * linked list.
 * 
 * If there’s already a node attached after this node, and there *isn’t* one
 * attached after the node being inserted, then that next-node will be
 * affixed to our new node, thus keeping the chain intact if possible.
 * 
 * Note: Realize that due to that copy-next mechanic, you can splice
 *       node-strings on top of eachother, but all nodes *after* this node in
 *       the original chain will be lost.
 */
void node__affix(node this, node other) {
  if (this->next != NULL)
    if (other->next == NULL)
      node__affix(other, this->next);
    else
      this->next->previous = NULL;
  
  other->previous = this;
  this->next      = other;
}
