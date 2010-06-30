#include "Unit.c"
#include "Cest.h"

#include "Paws.o/Types/routine/routine.h"


CEST(Unit, allocate) {
  unit a_unit;
  
  a_unit = Unit->allocate();
  
  ASSERT( a_unit->threads->size  == 0    );
  ASSERT( a_unit->threads->queue == NULL );
  
  
  SUCCEED;
}
