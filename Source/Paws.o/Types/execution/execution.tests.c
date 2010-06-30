#include "execution.c"

#define DECLARATIONS
# include "Cest.c"
#undef  DECLARATIONS


CEST(Execution, allocate) {
  execution   an_execution;
  
  an_execution = Execution->allocate();
  ASSERT( an_execution->content->first  == NULL );
  ASSERT( an_execution->content->last   == NULL );
  ASSERT( an_execution->content->length == 0    );
  
  ASSERT( an_execution->size  == 0    );
  ASSERT( an_execution->nodes == NULL );
  
  SUCCEED;
}

CEST(execution, thing) {
  execution   an_execution    = Execution->allocate();
  
  ASSERT( Execution->thing(an_execution).isa               == EXECUTION    );
  ASSERT( Execution->thing(an_execution).pointer.execution == an_execution );
  
  SUCCEED;
}

CEST(execution, exercise) { PEND; }
