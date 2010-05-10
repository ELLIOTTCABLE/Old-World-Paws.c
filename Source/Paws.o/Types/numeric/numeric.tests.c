#include "numeric.c"
#include "Cest.h"


CEST(Numeric, create) {
  numeric   a_numeric;
  list      a_naughty;
  
  a_numeric = Numeric->create(42);
  ASSERT( a_numeric->native == 42 );
  
  a_naughty = LL->at(a_numeric->content, 0)->thing.pointer.list;
  ASSERT( LL->at(a_numeric->content, 0)->thing.isa == LIST );
  ASSERT( LL->at(a_numeric->content, 0)->thing.pointer.list == a_naughty );
  
  SUCCEED;
}

CEST(numeric, thing) {
  numeric   a_numeric = Numeric->create(42);
  
  ASSERT( Numeric->thing(a_numeric).isa             == NUMERIC   );
  ASSERT( Numeric->thing(a_numeric).pointer.numeric == a_numeric );
  
  SUCCEED;
}

CEST(numeric, native) {
  numeric   a_numeric = Numeric->create(42);
  
  ASSERT( Numeric->native(a_numeric) == 42 );
  
  SUCCEED;
}
