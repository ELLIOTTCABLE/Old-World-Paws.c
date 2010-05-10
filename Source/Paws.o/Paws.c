#define INTERNALIZE
# include "Paws.h"
#undef INTERNALIZE

#include <stdlib.h>
#include <string.h>


thing   nothing   (void);

                          struct Paws // »
                                *Paws   = NULL;
void Paws__register_Paws(void) { Paws   = malloc(sizeof(struct Paws));
  
  struct Paws // »
  data = {
    .Threading    = NULL,
    
    .List         = NULL,
    .Routine      = NULL,
    .Numeric      = NULL,
    .String       = NULL,
    
    .nothing    = nothing
  };
  
  memcpy(Paws, &data, sizeof(struct Paws));
  
  Paws__register_Threading();
  
  Paws__register_List();
  Paws__register_Numeric();
  Paws__register_Routine();
  Paws__register_String();
}


/* FIXME: Find a way to run this with the tests without `constructor`, for `gcc` compatibility. */
void constructor prepare_Paws(void) { Paws__register_Paws(); }

thing nothing(void) {
  struct thing nothing = {
    .isa = NOTHING,
    .pointer = { .nothing = NULL }
  };
  
  return nothing;
}
