#include "routine.h"

#if !defined(LIST_H)
# include "Paws.o/list/list.h"
#endif

#include "Paws.o/Paws.h"

#include <stdlib.h>
#include <string.h>


/* =========================
= `infrastructure routine` =
========================= */

/* ### Method Declarations ### */

routine             Routine__create     (struct ast_node *scope_node);

thing               routine__to_thing   (routine this);
struct ast_node*    routine__native     (routine this);

void                routine__insert     (routine this, thing child, ll_size index);
void                routine__prefix     (routine this, thing child);
void                routine__affix      (routine this, thing child);
thing               routine__at         (routine this,              ll_size index);

struct Routine const Routine = {
  .create     = Routine__create,
  
  .to_thing   = routine__to_thing,
  .native     = routine__native,
  
  .insert     = routine__insert,
  .prefix     = routine__prefix,
  .affix      = routine__affix,
  .at         = routine__at
};
void constructor Paws__register_Routine(void) { Paws.Routine = Routine; }


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure routine`, and returns a
 * C `routine` (a pointer to a `struct routine`.)
 */
routine Routine__create(struct ast_node *scope_node) {
  routine this = malloc(sizeof(struct routine));
  
  this->content = LL.create();
  LL.affix( this->content,
    Element.create(List.to_thing( List.create_naughty() )) );
  
  /* TODO: Create separate files with ast-manipulation functions; and copy the
   *       parameter node into our data structure. */
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing routine__to_thing(routine this) {
  thing location = malloc(sizeof(struct thing));
  struct thing wrapper = {
    .isa = ROUTINE,
    .pointer = { .routine = this }
  };
  
  memcpy(location, &wrapper, sizeof(struct thing));
  
  return location;
}

/* This method returns a pointer to the AST struct for a given `routine`. */
struct ast_node* routine__native(routine this) {
  return this->ast;
}

void  routine__insert(routine this, thing child, ll_size index) {
          List.insert(  (list)this,       child,         index); }
void  routine__prefix(routine this, thing child) {
          List.prefix(  (list)this,       child); }
void  routine__affix (routine this, thing child) {
          List.affix (  (list)this,       child); }
thing routine__at    (routine this,              ll_size index) { return
          List.at    (  (list)this,                      index); }
