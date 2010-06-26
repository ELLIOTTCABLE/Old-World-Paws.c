#include "Unit.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* ================
= Unit Management =
================ */

/* ### Method Declarations ### */

unit    Unit__allocate    (void);

                          struct Unit // »
                                *Unit   = NULL;
void Paws__register_Unit(void) { Unit   = malloc(sizeof(struct Unit));
                           Paws->Unit   = Unit;
  
  struct Unit // »
  data = {
    .allocate   = Unit__allocate
  };
  
  memcpy(Unit, &data, sizeof(struct Unit));
}


/* ### Method Implementations ### */

unit Unit__allocate(void) {
  unit this       = malloc(sizeof( struct unit ));
  
  this->threads   = Pool->allocate();
  this->strings   = Magazine->allocate(STRING);
  
  return this;
}
