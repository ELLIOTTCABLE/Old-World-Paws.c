#include "string.c"

#if !defined(CEST_H)
# include "Cest.h"
#endif

CEST(String, create) {
  string  a_string;
  list    a_naughty;
  
  a_string = String.create("foo", 4);
  ASSERT( a_string->content->length == 1 );
  
  a_naughty = LL.at(a_string->content, 0)->thing->pointer.list;
  ASSERT( LL.at(a_naughty->content, 0)->thing->isa == LIST );
  ASSERT( LL.at(a_naughty->content, 0)->thing->pointer.list == a_naughty );
  
  a_string = String.create("bar", 4);
  ASSERT( strcmp(a_string->native.short_array, "bar") == 0 );
  
  a_string = String.create("A whole new world!", 19);
  ASSERT( strcmp(a_string->native.otherwise.long_array,
    "A whole new world!") == 0 );
  
  return true;
}

CEST(string, to_thing) {
  string  a_string = String.create("", 1);
  thing   a_thing;
  
  a_thing = String.to_thing(a_string);
  ASSERT( a_thing->isa            == STRING   );
  ASSERT( a_thing->pointer.string == a_string );
  
  return true;
}
