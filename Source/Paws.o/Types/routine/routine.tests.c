#include "routine.c"
#include "Cest.h"


CEST(Routine, create) {
  node      a_scope, an_expression, a_word, another_word;
  routine   a_routine;
  list      a_naughty;
  
  a_scope       = Node->create_scope();
  an_expression = Node->create_expression();   Node->affix(a_scope,       an_expression);
  a_word        = Node->create_word("foo", 4); Node->affix(an_expression, a_word);
  another_word  = Node->create_word("bar", 4); Node->affix(an_expression, another_word);
  
  a_routine = Routine->create(a_scope);
  ASSERT( a_routine->content->length == 1 );
  
  a_naughty = LL->at(a_routine->content, 0)->thing.pointer.list;
  ASSERT( LL->at(a_routine->content, 0)->thing.isa == LIST );
  ASSERT( LL->at(a_routine->content, 0)->thing.pointer.list == a_naughty );
  
  ASSERT( a_routine->scope != a_scope );
  ASSERT( strcmp(Node->at(Node->at(a_routine->scope, 0), 0)->content, "foo") == 0 );
  ASSERT( strcmp(Node->at(Node->at(a_routine->scope, 0), 1)->content, "bar") == 0 );
  
  SUCCEED;
}

CEST(routine, thing) {
  node      a_scope = Node->create_scope();
  routine   a_routine = Routine->create(a_scope);
  
  ASSERT( Routine->thing(a_routine).isa             == ROUTINE );
  ASSERT( Routine->thing(a_routine).pointer.routine == a_routine );
  
  SUCCEED;
}

CEST(routine, execute) { PEND; }
