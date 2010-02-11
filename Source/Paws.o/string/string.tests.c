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
  ASSERT( a_string->bytes == 4 );
  
  a_string = String.create(
    "May the forces of evil become confused on the way to your house.", 65);
  ASSERT( strcmp(a_string->native.otherwise.long_array,
    "May the forces of evil become confused on the way to your house.") == 0 );
  ASSERT( a_string->bytes == 65 );
  
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
