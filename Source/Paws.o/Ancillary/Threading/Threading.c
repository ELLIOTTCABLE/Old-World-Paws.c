#include "Threading.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>


struct Threading Threading = {
  .Thread   = NULL,
  .Pool     = NULL
};
void constructor register_Threading(void) { Paws.Threading = Threading; }
