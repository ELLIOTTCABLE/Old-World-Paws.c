#include "Magazine.c"
#include "Cest.h"

#include <errno.h>


CEST(Magazine, allocate) {
  magazine a_magazine;
  
  a_magazine = Magazine->allocate(NOTHING);
  ASSERT( a_magazine->holds            == NOTHING );
  ASSERT( a_magazine->root->bytes[  0] == NULL );
  ASSERT( a_magazine->root->bytes[128] == NULL );
  ASSERT( a_magazine->root->bytes[255] == NULL );
  ASSERT( a_magazine->root->bytes[256] == NULL );
  
  SUCCEED;
}

CEST(magazine, get) {
  magazine a_magazine = Magazine->allocate(STRING);
  
  // Doing some tedious manual setup, to avoid dependency on `Magazine->set()`. (Since `String->create()` will
  // eventually depend on this, and apply to interpretation-unit specific `string` magazines, we’re going to
  // manually create empty `string` structs. We don’t actually care about the contents of the `string` struct
  // right now, we’re simply going to preform pointer equality on them.)
  string  tops = malloc(sizeof( struct string ));
  string  top  = malloc(sizeof( struct string ));
  string  taps = malloc(sizeof( struct string ));
  string  tap  = malloc(sizeof( struct string ));
  cartridge s2 = malloc(sizeof( struct cartridge ));                      s2->bytes['\0'] = (cartridge)tops;
  cartridge p2 = malloc(sizeof( struct cartridge )); p2->bytes['s'] = s2; p2->bytes['\0'] = (cartridge)top;
  cartridge o  = malloc(sizeof( struct cartridge ));  o->bytes['p'] = p2;
  cartridge s1 = malloc(sizeof( struct cartridge ));                      s1->bytes['\0'] = (cartridge)taps;
  cartridge p1 = malloc(sizeof( struct cartridge )); p1->bytes['s'] = s1; p1->bytes['\0'] = (cartridge)tap;
  cartridge a  = malloc(sizeof( struct cartridge ));  a->bytes['p'] = p1;
  cartridge t  = malloc(sizeof( struct cartridge ));  t->bytes['a'] = a;   t->bytes['o'] = o;
                                       a_magazine->root->bytes['t'] = t;
  
  ASSERT( Magazine->get(a_magazine, "tap").pointer.string  == tap );
  ASSERT( Magazine->get(a_magazine, "taps").pointer.string == taps );
  ASSERT( Magazine->get(a_magazine, "top").pointer.string  == top );
  ASSERT( Magazine->get(a_magazine, "tops").pointer.string == tops );
  
  SUCCEED;
}

CEST(magazine, set) { PEND; }
