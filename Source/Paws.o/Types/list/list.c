#include "list.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* ======================
= `infrastructure list` =
====================== */

/* ### Method Declarations ### */

list    List__allocate          (void);

list    list__naughtify         (list this);
thing   list__thing             (list this);
void    list__insert            (list this, thing child, ll_size index);
void    list__prefix            (list this, thing child);
void    list__affix             (list this, thing child);
thing   list__at                (list this,              ll_size index);

                          struct List // »
                                *List   = NULL;
void Paws__register_List(void) { List   = malloc(sizeof(struct List));
                           Paws->List   = List;
  
  struct List // »
  data = {
    .allocate         = List__allocate,
    
    .naughtify        = list__naughtify,
    .thing            = list__thing,
    .insert           = list__insert,
    .prefix           = list__prefix,
    .affix            = list__affix,
    .at               = list__at
  };
  
  memcpy(List, &data, sizeof(struct List));
  
  Paws__register_LL();
  Paws__register_Element();
}


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure list`, and returns a C `list` (a pointer to a `struct list`.) */
list List__allocate(void) {
  list this = malloc(sizeof(struct list));
  
  this->content = LL->allocate();
  
  return this;
}

list list__naughtify(list this) {
  list naughty = List->allocate();
  
  List->insert(naughty, List->thing(naughty), 0);
  List->insert(   this, List->thing(naughty), 0);
  
  return naughty;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union. */
thing list__thing(list this) {
  struct thing something = {
    .isa = LIST,
    .pointer = { .list = this }
  };
  
  return something;
}

void list__insert(list this, thing child, ll_size index) {
  if (index == 0)
    List->prefix(this, child);
  else if(index == this->content->length)
    List->affix (this, child);
  else
    LL->posterior_insert(this->content, Element->allocate(child), index);
}

void list__prefix(list this, thing child) { LL->prefix(this->content, Element->allocate(child)); }

void list__affix(list this, thing child)  { LL->affix (this->content, Element->allocate(child)); }

thing list__at(list this, ll_size index) {
  element element = LL->at(this->content, index);
  if (element == NULL)
    return (thing){ NULL };
  else
    return element->thing;
}
