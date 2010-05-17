#include "execution.c"
#include "Cest.h"


CEST(Execution, create) {
  execution   an_execution;
  list        a_naughty;
  
  an_execution = Execution->create();
  ASSERT( an_execution->content->length == 1 );
  
  a_naughty   = LL->at(an_execution->content, 0)->thing.pointer.list;
  ASSERT(       LL->at(an_execution->content, 0)->thing.isa          == LIST      );
  ASSERT(       LL->at(an_execution->content, 0)->thing.pointer.list == a_naughty );
  
  SUCCEED;
}

CEST(execution, thing) {
  execution   an_execution    = Execution->create();
  
  ASSERT( Execution->thing(an_execution).isa               == EXECUTION    );
  ASSERT( Execution->thing(an_execution).pointer.execution == an_execution );
  
  SUCCEED;
}

CEST(execution, exercise) { PEND; }
