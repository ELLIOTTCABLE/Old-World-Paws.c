#include "string.c"
#include "Cest.h"


CEST(String, allocate) {
  string  a_string;
  
  a_string = String->allocate("foo");
  ASSERT( a_string->content->first  == NULL );
  ASSERT( a_string->content->last   == NULL );
  ASSERT( a_string->content->length == 0    );
  
  a_string = String->allocate("bar");
  ASSERT( strcmp(a_string->native.short_array, "bar") == 0 );
  ASSERT( a_string->bytes == 4 );
  
  a_string = String->allocate(
    "May the forces of evil become confused on the way to your house.");
  ASSERT( strcmp(a_string->native.long_array,
    "May the forces of evil become confused on the way to your house.") == 0 );
  ASSERT( a_string->bytes == 65 );
  
  SUCCEED;
}

CEST(String, embody) {
  magazine    a_magazine = Magazine->allocate(STRING);
  string      a_string;
  
  a_string = String->embody("foo", a_magazine);
  ASSERT( a_string->content->first  == NULL );
  ASSERT( a_string->content->last   == NULL );
  ASSERT( a_string->content->length == 0    );
  
  a_string = String->embody("bar", a_magazine);
  ASSERT( strcmp(a_string->native.short_array, "bar") == 0 );
  ASSERT( a_string->bytes == 4 );
  
  a_string = String->embody(
    "May the forces of evil become confused on the way to your house.", a_magazine);
  ASSERT( strcmp(a_string->native.long_array,
    "May the forces of evil become confused on the way to your house.") == 0 );
  ASSERT( a_string->bytes == 65 );
  
              a_magazine = Magazine->allocate(STRING);
  string      first_foo, second_foo, first_bar, second_bar;
  
  first_foo     = String->embody("foo", a_magazine);
  second_foo    = String->embody("foo", a_magazine);
  ASSERT( first_foo == second_foo );
  
  first_bar     = String->embody("bar", a_magazine);
  second_bar    = String->embody("bar", a_magazine);
  ASSERT( first_bar == second_bar );
  
  ASSERT( first_foo != first_bar );
  
  PEND;
  
  /* TODO: Use current `thread`’s IU’s `string`-uniques store if `NULL` is passed as the `magazine` argument */
  
  SUCCEED;
}

CEST(string, thing) {
  string  a_string = String->allocate("");
  
  ASSERT( String->thing(a_string).isa            == STRING   );
  ASSERT( String->thing(a_string).pointer.string == a_string );
  
  SUCCEED;
}

CEST(string, native) {
  string  a_string;
  
  a_string = String->allocate("foo");
  ASSERT( strcmp(String->native(a_string), "foo") == 0 );
  
  a_string = String->allocate(
    "May the forces of evil become confused on the way to your house.");
  ASSERT( strcmp(String->native(a_string),
    "May the forces of evil become confused on the way to your house.") == 0 );
  
  SUCCEED;
}
