#define UNIT_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(POOL_H)
# include "Paws.o/Ancillary/Threading/Pool/Pool.h"
#endif
#if !defined(MAGAZINE_H)
# include "Paws.o/Ancillary/Magazine/Magazine.h"
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
