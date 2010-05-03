#include "thread.h"

#include "Paws.o/Ancillary/Threading/Threading.h"
#include "Paws.o/Paws.h"

#include <stdlib.h>


/* ==================
= Thread Management =
================== */

/* ### Method Declarations ### */

thread    Thread__create    (void);

void      thread__destroy   (thread this);

struct Thread const Thread = {
  .create     = Thread__create,
  
  .destroy    = thread__destroy
};
void constructor Paws__register_Thread(void) { Paws.Threading.Thread = Thread; }


/* ### Method Implementations ### */

thread Thread__create(void) {
  thread this = malloc(sizeof(struct thread));
  
  /* TODO: Initialize. */
  
  return this;
}

void thread__destroy(thread this) {
  /* TODO: Clean up. */
  
  free(this);
  return;
}
