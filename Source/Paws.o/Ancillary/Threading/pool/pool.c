#include "pool.h"

#include "Paws.o/Ancillary/Threading/Threading.h"
#include "Paws.o/Paws.h"

#include <stdlib.h>


/* ==================
= Thread Management =
================== */

/* ### Method Declarations ### */

pool    Pool__create    (void);

void    pool__destroy   (pool this);

struct Pool const Pool = {
  .create     = Pool__create,
  
  .destroy    = pool__destroy
};
void constructor Paws__register_Pool(void) { Paws.Threading.Pool = Pool; }


/* ### Method Implementations ### */

pool Pool__create(void) {
  pool this = malloc(sizeof(struct pool));
  
  /* TODO: Initialize. */
  
  return this;
}

void pool__destroy(pool this) {
  /* TODO: Clean up. */
  
  free(this);
  return;
}
