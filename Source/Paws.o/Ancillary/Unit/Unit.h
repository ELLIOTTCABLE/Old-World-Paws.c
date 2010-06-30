#if !defined(UNIT_DECLARATIONS)
# define     UNIT_DECLARATIONS

#include "Paws.o/Core.h"
#include "Paws.o/Types/Types.h"

#include "Paws.o/Ancillary/Threading/Pool/Pool.h"
#include "Paws.o/Ancillary/Magazine/Magazine.h"


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
