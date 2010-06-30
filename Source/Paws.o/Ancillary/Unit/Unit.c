#if !defined(UNIT_DECLARATIONS)
# define     UNIT_DECLARATIONS

#if !defined(DECLARATIONS)
# define UNIT_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Core.h"
#   include "Paws.o/Types/Types.h"

#   include "Paws.o/Ancillary/Threading/Pool/Pool.c"
#   include "Paws.o/Ancillary/Magazine/Magazine.c"
#if defined(UNIT_C__BEHEST)
# undef DECLARATIONS
#endif


/* ### Data Types & Structures ### */

        struct E(unit); /* A “unit of interpretation” */
typedef struct E(unit)* E(unit);

struct E(unit) {
  E(pool)       threads;
  E(magazine)   strings;
};

/* ### Method Declarations ### */

struct E(Unit) {
  /* `Unit` functions */
  E(unit)   (*allocate)   ( void );
  
  /* `struct unit` methods */
};
#if !defined(EXTERNALIZE)
  struct E(Unit) extern *Unit;
#endif

void    Paws__register_Unit   ( void );



#endif
#if !defined(DECLARATIONS) && !defined(UNIT_IMPLEMENTATION) /* ========================================== BODY */
# define                               UNIT_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.o/Paws.c"
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


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

#endif
