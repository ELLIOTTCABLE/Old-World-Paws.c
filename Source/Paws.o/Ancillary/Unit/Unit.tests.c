#include "Unit.c"
#include "Cest.h"

#if !defined(STRING_H)
# include "Paws.o/Types/routine/routine.h"
#endif


CEST(Unit, allocate) {
  unit a_unit;
  
  a_unit = Unit->allocate();
  
  ASSERT( a_unit->threads->size  == 0    );
  ASSERT( a_unit->threads->queue == NULL );
  
  
  SUCCEED;
}
