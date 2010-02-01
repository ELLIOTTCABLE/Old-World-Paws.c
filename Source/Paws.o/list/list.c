#include <stdlib.h>
#include <stdbool.h>

#ifndef LIST_H_INCLUDED
#  include "list.h"
#endif

/* ======================
= `infrastructure list` =
====================== */

/* ### Method Declarations ### */

list  list__create    (void);
thing list__to_thing  (list);
void  list__insert    (list, thing, ll_size);
void  list__prefix    (list, thing);
void  list__affix     (list, thing);
thing list__at        (list, ll_size);

struct List_methods const
List = {
  list__create,
  list__to_thing,
  list__insert,
  list__prefix,
  list__affix,
  list__at
};

/* ### Method Implementations ### */

/* This method allocates a new `infrastructure list`, and returns a pointer to
 * a `struct list`.
 */
list _list__create(bool);
list  list__create(void) { return
     _list__create(false); }
list _list__create(bool is_naughty) {
  list this = malloc(sizeof(struct list)), naughty;
  
  this->content = LL.create();
  
  naughty = is_naughty? this:_list__create(true);
  LL.affix( this->content, Node.create(List.to_thing(naughty)) );
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing list__to_thing(list this) {
  thing wrapper = malloc(sizeof(struct thing)); 
  
  wrapper->isa  = LIST;
  wrapper->pointer.list = this;
  
  return wrapper;
}

void list__insert(list this, thing child, ll_size index) {
  LL.posterior_insert(this->content, Node.create(child), index); }

void list__prefix(list this, thing child) {
  LL.prefix(this->content, Node.create(child)); }

void list__affix(list this, thing child) {
  LL.affix(this->content, Node.create(child)); }

thing list__at(list this, ll_size index) { return
  LL.at(this->content, index)->thing; }
