#include "Unit.c"

#define DECLARATIONS
# include "Cest.c"
#undef  DECLARATIONS


#define DECLARATIONS
# include "Paws.o/Types/routine/routine.c"
#undef  DECLARATIONS


CEST(Unit, allocate) {
  unit a_unit;
  
  a_unit = Unit->allocate();
  
  ASSERT( a_unit->threads->size  == 0    );
  ASSERT( a_unit->threads->queue == NULL );
  
  
  SUCCEED;
}
