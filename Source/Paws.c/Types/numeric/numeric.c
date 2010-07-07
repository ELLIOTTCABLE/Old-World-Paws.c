#if !defined(NUMERIC_DECLARATIONS)
# define     NUMERIC_DECLARATIONS

#if !defined(DECLARATIONS)
# define NUMERIC_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.c/Core.h"
#   include "Paws.c/Types/Types.h"

#   include "Paws.c/Types/list/list.c"
#if defined(NUMERIC_C__BEHEST)
# undef DECLARATIONS
#endif


/* =========================
= `infrastructure numeric` =
========================= */

/* ### Data Types & Structures ### */

/* `infrastructure numeric`, the numeric data structure of Paws, is herein implemented natively with C `int`
 * types. It provides no recourse for floating-point arithmetic. */
struct E(numeric) {
  E(ll)   content; /* The `ll` behind this `numeric`’s `list` interface */
  
  /* TODO: Support floating-point values. */
  int     native;
};


/* ### Method Declarations ### */

struct E(Numeric) {
  /* `Numeric` functions */
  E(numeric)    (*allocate)   ( int native );
  
  /* `struct numeric` methods */
  E(thing)      (*thing)      ( E(numeric) this );
  int           (*native)     ( E(numeric) this );
};
#if !defined(EXTERNALIZE)
  struct E(Numeric) extern *Numeric;
#endif

void    Paws__register_Numeric    ( void );



#endif
#if !defined(DECLARATIONS) && !defined(NUMERIC_IMPLEMENTATION) /* ======================================= BODY */
# define                               NUMERIC_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.c/Paws.c"
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


/* ### Method Declarations ### */

numeric   Numeric__allocate   (int native);

thing     numeric__thing      (numeric this);
int       numeric__native     (numeric this);

                             struct Numeric // »
                                   *Numeric   = NULL;
void Paws__register_Numeric(void) { Numeric   = malloc(sizeof(struct Numeric));
                              Paws->Numeric   = Numeric;
  
  struct Numeric // »
  data = {
    .allocate   = Numeric__allocate,
      
    .thing      = numeric__thing,
    .native     = numeric__native
  };
  
  memcpy(Numeric, &data, sizeof(struct Numeric));
}


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure numeric`, and returns a C `numeric` (a pointer to a
 * `struct numeric`.)
 *--
 * TODO: Global-uniqueness. We need to cache already-created `numeric`s somewhere, and retreive them when
 *       necessary.
 */
numeric Numeric__allocate(int nate) {
  numeric this = malloc(sizeof(struct numeric));
  
  this->content = LL->allocate();
  
  this->native = nate;
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union.
 */
thing numeric__thing(numeric this) {
  struct thing something = {
    .isa = NUMERIC,
    .pointer = { .numeric = this }
  };
  
  return something;
}

/* This method returns a native C `int` for a given `list`. */
int numeric__native(numeric this) {
  return this->native;
}

#endif
