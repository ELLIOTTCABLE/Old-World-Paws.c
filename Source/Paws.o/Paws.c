#include "Paws.h"

#include <stdlib.h>


struct Paws Paws = {
  /* This is necessary to avoid a ‘GNU empty initializer extension’ warning */
  .List = NULL
};
