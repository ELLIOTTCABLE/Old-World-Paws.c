#include "numeric.c"
#include "Cest.h"


CEST(Numeric, allocate) {
  numeric   a_numeric;
  
  a_numeric = Numeric->allocate(42);
  ASSERT( a_numeric->content->first  == NULL );
  ASSERT( a_numeric->content->last   == NULL );
  ASSERT( a_numeric->content->length == 0    );
  
  ASSERT( a_numeric->native == 42 );
  
  SUCCEED;
}

CEST(numeric, thing) {
  numeric   a_numeric   = Numeric->allocate(42);
  
  ASSERT( Numeric->thing(a_numeric).isa             == NUMERIC   );
  ASSERT( Numeric->thing(a_numeric).pointer.numeric == a_numeric );
  
  SUCCEED;
}

CEST(numeric, native) {
  int       number      = 42;
  numeric   a_numeric   = Numeric->allocate(number);
  
  ASSERT( Numeric->native(a_numeric) == number );
  
  SUCCEED;
}
