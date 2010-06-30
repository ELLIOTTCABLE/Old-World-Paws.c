#if !defined(LIST_DECLARATIONS)
# define     LIST_DECLARATIONS

#if !defined(DECLARATIONS)
# define LIST_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Core.h"
#   include "Paws.o/Types/Types.h"

#   include "ll.c"
#if defined(LIST_C__BEHEST)
# undef DECLARATIONS
#endif


/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented as a linked-list, referencing 
 * `thing`s as elements.
 */
struct E(list) {
  E(ll)   content; /* The `ll` behind this `list` */
};


/* ### Method Declarations ### */

struct E(List) {
  /* `List` functions */
  E(list)     (*allocate)         ( void );
  
  /* `struct list` methods */
  E(thing)    (*thing)            ( E(list) this );
  E(list)     (*naughtify)        ( E(list) this );
  void        (*insert)           ( E(list) this, E(thing) child, E(ll_size) idx );
  void        (*prefix)           ( E(list) this, E(thing) child );
  void        (*affix)            ( E(list) this, E(thing) child );
  E(thing)    (*at)               ( E(list) this,                 E(ll_size) idx );
};
#if !defined(EXTERNALIZE)
  struct E(List) extern *List;
#endif

void    Paws__register_List   ( void );


#endif
#if !defined(DECLARATIONS) && !defined(LIST_IMPLEMENTATION) /* ===========================================BODY */
# define                               LIST_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.o/Paws.c"
#   include <stdlib.h>
#   include <string.h>
#   include <stdbool.h>
# undef  DECLARATIONS


/* ### Method Declarations ### */

list    List__allocate          (void);

list    list__naughtify         (list this);
thing   list__thing             (list this);
void    list__insert            (list this, thing child, ll_size idx);
void    list__prefix            (list this, thing child);
void    list__affix             (list this, thing child);
thing   list__at                (list this,              ll_size idx);

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

void list__insert(list this, thing child, ll_size idx) {
  if (idx == 0)
    List->prefix(this, child);
  else if(idx == this->content->length)
    List->affix (this, child);
  else
    LL->posterior_insert(this->content, Element->allocate(child), idx);
}

void list__prefix(list this, thing child) { LL->prefix(this->content, Element->allocate(child)); }

void list__affix(list this, thing child)  { LL->affix (this->content, Element->allocate(child)); }

thing list__at(list this, ll_size idx) {
  element e = LL->at(this->content, idx);
  if (e == NULL)
    return (thing){ {NULL} };
  else
    return e->thing;
}

#endif
