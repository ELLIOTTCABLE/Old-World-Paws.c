#define CORE_H

#if !defined(TYPES_H)
#  include "Paws.o/Core/Types.h"
#endif

struct Paws {
  /* `Paws` functions */
  void  (*explode) (char[]);
} const extern Paws;
