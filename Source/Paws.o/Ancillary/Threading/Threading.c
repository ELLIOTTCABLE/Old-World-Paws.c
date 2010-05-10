#include "Threading.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


                               struct Threading // »
                                     *Threading   = NULL;
void Paws__register_Threading(void) { Threading   = malloc(sizeof(struct Threading));
                  Paws->Threading   = Threading;
  
  struct Threading // »
  data = {
    .Pool     = NULL,
    .Thread   = NULL
  };
  
  memcpy(Threading, &data, sizeof(struct Threading));
  
  Paws__register_Pool();
  Paws__register_Thread();
}
