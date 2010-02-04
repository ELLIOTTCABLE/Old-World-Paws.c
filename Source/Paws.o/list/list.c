#include "list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* ======================
= `infrastructure list` =
====================== */

/* ### Method Declarations ### */

list  List__create    (void);
list  List__create_naughty  (void);
thing list__to_thing  (list);
void  list__insert    (list, thing, ll_usize);
void  list__prefix    (list, thing);
void  list__affix     (list, thing);
thing list__at        (list, ll_usize);

struct List_methods const
List = {
  List__create,
  List__create_naughty,
  list__to_thing,
  list__insert,
  list__prefix,
  list__affix,
  list__at
};

/* ### Method Implementations ### */

/* This method allocates a new `infrastructure list`, and returns a C `list`
 * (a pointer to a C `struct list`.)
 */
list _List__create(bool);

list  List__create(void) { return
     _List__create(false); }

list  List__create_naughty(void) { return
     _List__create(true); }

list _List__create(bool is_naughty) {
  list this = malloc(sizeof(struct list)), naughty;
  
  this->content = LL.create();
  
  naughty = is_naughty? this:List.create_naughty();
  LL.affix( this->content, Node.create(List.to_thing(naughty)) );
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing list__to_thing(list this) {
  thing location = malloc(sizeof(struct thing));
  struct thing wrapper = {
    .isa = LIST,
    .pointer = { .list = this }
  };
  
  memcpy(location, &wrapper, sizeof(struct thing));
  
  return location;
}

void list__insert(list this, thing child, ll_usize index) {
  LL.posterior_insert(this->content, Node.create(child), index); }

void list__prefix(list this, thing child) {
  LL.prefix(this->content, Node.create(child)); }

void list__affix(list this, thing child) {
  LL.affix(this->content, Node.create(child)); }

thing list__at(list this, ll_usize index) { return
  LL.at(this->content, index)->thing; }
