#include "list.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* ======================
= `infrastructure list` =
====================== */

/* ### Method Declarations ### */

list    List__create            (void);
list    List__create_naughty    (void);

thing   list__thing             (list this);
void    list__insert            (list this, thing child, ll_size index);
void    list__prefix            (list this, thing child);
void    list__affix             (list this, thing child);
thing   list__at                (list this,              ll_size index);

struct List const List = {
  .create           = List__create,
  .create_naughty   = List__create_naughty,
  
  .thing            = list__thing,
  .insert           = list__insert,
  .prefix           = list__prefix,
  .affix            = list__affix,
  .at               = list__at
};
void constructor Paws__register_List(void) { Paws.List = List; }


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure list`, and returns a C `list`
 * (a pointer to a `struct list`.)
 */
list _List__create        (bool);
list  List__create        (void) { return _List__create(false); }
list  List__create_naughty(void) { return _List__create(true);  }

list _List__create(bool is_naughty) {
  list this = malloc(sizeof(struct list)), naughty;
  
  this->content = LL.create();
  
  naughty = is_naughty? this:List.create_naughty();
  LL.affix( this->content, Element.create(List.thing(naughty)) );
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing list__thing(list this) {
  thing location = malloc(sizeof(struct thing));
  struct thing wrapper = {
    .isa = LIST,
    .pointer = { .list = this }
  };
  
  memcpy(location, &wrapper, sizeof(struct thing));
  
  return location;
}

void list__insert(list this, thing child, ll_size index) {
  if (index == 0)
    List.prefix(this, child);
  else if(index == this->content->length)
    List.affix (this, child);
  else
    LL.posterior_insert(this->content, Element.create(child), index);
}

void list__prefix(list this, thing child) {
  LL.prefix(this->content, Element.create(child)); }

void list__affix(list this, thing child) {
  LL.affix(this->content, Element.create(child)); }

thing list__at(list this, ll_size index) {
  element element = LL.at(this->content, index);
  if (element == NULL)
    return NULL;
  else
    return element->thing;
}
