#include "Magazine.c"
#include "Cest.h"

#if !defined(STRING_H)
# include "Paws.o/Types/string/string.h"
#endif

#include <errno.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM) \
  strncpy(TO, FROM, sizeof(TO)); TO[sizeof(TO) - 1] = '\0'


CEST(Magazine, allocate) {
  magazine a_magazine;
  
  a_magazine = Magazine->allocate(UNKNOWN);
  ASSERT( a_magazine->holds            == UNKNOWN );
  ASSERT( a_magazine->root->bytes[  0] == NULL );
  ASSERT( a_magazine->root->bytes[128] == NULL );
  ASSERT( a_magazine->root->bytes[255] == NULL );
  ASSERT( a_magazine->root->bytes[256] == NULL );
  
  SUCCEED;
}

static thing testing_setter (magazine this, char *key) {
  // We’re going to manually create a faux-`string`. Don’t ever do this, it’s horridly evil! ;D
  string it = malloc(sizeof( struct string ));
  STRCPY(it->native.short_array, key);
  
  return Paws->String->thing(it);
}

CEST(magazine, get) {
  kind kind = STRING;
  magazine a_magazine = Magazine->allocate(kind);
  
  // Doing some tedious manual setup, to avoid dependency on `Magazine->set()`. (Since `String->create()` will
  // eventually depend on this, and apply to interpretation-unit specific `string` magazines, we’re going to
  // manually create empty `string` structs. We don’t actually care about the contents of the `string` struct
  // right now, we’re simply going to preform pointer equality on them.)
  string  tops = malloc(sizeof( struct string )),
           top = malloc(sizeof( struct string )),
          taps = malloc(sizeof( struct string )),
           tap = malloc(sizeof( struct string ));
  cartridge s2 = malloc(sizeof( struct cartridge ));                      s2->bytes['\0'] = (cartridge)tops;
  cartridge p2 = malloc(sizeof( struct cartridge )); p2->bytes['s'] = s2; p2->bytes['\0'] = (cartridge)top;
  cartridge  o = malloc(sizeof( struct cartridge ));  o->bytes['p'] = p2;
  cartridge s1 = malloc(sizeof( struct cartridge ));                      s1->bytes['\0'] = (cartridge)taps;
  cartridge p1 = malloc(sizeof( struct cartridge )); p1->bytes['s'] = s1; p1->bytes['\0'] = (cartridge)tap;
  cartridge  a = malloc(sizeof( struct cartridge ));  a->bytes['p'] = p1;
  cartridge  t = malloc(sizeof( struct cartridge ));  t->bytes['a'] = a;   t->bytes['o'] = o;
                                       a_magazine->root->bytes['t'] = t;
  
  ASSERT( Magazine->get(a_magazine, "tap",  NULL).isa            == kind );
  ASSERT( Magazine->get(a_magazine, "tap",  NULL).pointer.string == tap );
  ASSERT( Magazine->get(a_magazine, "taps", NULL).pointer.string == taps );
  ASSERT( Magazine->get(a_magazine, "top",  NULL).pointer.string == top );
  ASSERT( Magazine->get(a_magazine, "tops", NULL).pointer.string == tops );
  
  
  cartridge  r = malloc(sizeof( struct cartridge ));                       r->bytes['\0'] = NULL;
  cartridge  e = malloc(sizeof( struct cartridge ));  e->bytes['r'] = r;   e->bytes['\0'] = NULL;
                                                     p1->bytes['e'] = e;
  
  thing tape = Magazine->get(a_magazine, "tape", testing_setter);
  ASSERT(        tape.isa                              == STRING );
  ASSERT( strcmp(tape.pointer.string->native.short_array, "tape") == 0 );
  
  thing taper = Magazine->get(a_magazine, "taper",  NULL);
  ASSERT( taper.pointer.unknown == NULL );
  
  
  ASSERT( a_magazine->root->bytes['f'] == NULL );
  ASSERT( Magazine->get(a_magazine, "foo",  NULL).pointer.unknown == NULL );
  ASSERT( a_magazine->root->bytes['f'] != NULL );
  ASSERT( a_magazine->root->bytes['f']->bytes['o'] != NULL );
  ASSERT( a_magazine->root->bytes['f']->bytes['o']->bytes['o'] != NULL );
  
  
  ASSERT( a_magazine->root->bytes['b'] == NULL );
  thing bar = Magazine->get(a_magazine, "bar", testing_setter);
  ASSERT(        bar.isa                              == STRING );
  ASSERT( strcmp(bar.pointer.string->native.short_array, "bar") == 0 );
  
  ASSERT(                 a_magazine->root->bytes['b']                                           != NULL );
  ASSERT(                 a_magazine->root->bytes['b']->bytes['a']                               != NULL );
  ASSERT(                 a_magazine->root->bytes['b']->bytes['a']->bytes['r']                   != NULL );
  ASSERT(                 a_magazine->root->bytes['b']->bytes['a']->bytes['r']->bytes['\0']      != NULL );
  ASSERT( strcmp(((string)a_magazine->root->bytes['b']->bytes['a']->bytes['r']->bytes['\0'])
    ->native.short_array, "bar") == 0 );
  
  SUCCEED;
}

CEST(magazine, set) {
  kind kind = STRING;
  magazine a_magazine = Magazine->allocate(kind);
  
  string other1 = malloc(sizeof( struct string )),
         other2 = malloc(sizeof( struct string )),
           tops = malloc(sizeof( struct string )),
            top = malloc(sizeof( struct string )),
           taps = malloc(sizeof( struct string )),
            tap = malloc(sizeof( struct string )),
            bar = malloc(sizeof( struct string ));
  cartridge s2 = malloc(sizeof( struct cartridge ));                      s2->bytes['\0'] = NULL;
  cartridge p2 = malloc(sizeof( struct cartridge )); p2->bytes['s'] = s2; p2->bytes['\0'] = (cartridge)other1;
  cartridge o  = malloc(sizeof( struct cartridge ));  o->bytes['p'] = p2;
  cartridge s1 = malloc(sizeof( struct cartridge ));                      s1->bytes['\0'] = (cartridge)other2;
  cartridge p1 = malloc(sizeof( struct cartridge )); p1->bytes['s'] = s1; p1->bytes['\0'] = (cartridge)tap;
  cartridge a  = malloc(sizeof( struct cartridge ));  a->bytes['p'] = p1;
  cartridge t  = malloc(sizeof( struct cartridge ));  t->bytes['a'] = a;   t->bytes['o'] = o;
                                       a_magazine->root->bytes['t'] = t;
  
  Magazine->set(a_magazine, "tap",  Paws->String->thing(tap));  ASSERT( (string)p1->bytes['\0'] == tap );
  Magazine->set(a_magazine, "taps", Paws->String->thing(taps)); ASSERT( (string)s1->bytes['\0'] == taps );
  Magazine->set(a_magazine, "top",  Paws->String->thing(top));  ASSERT( (string)p2->bytes['\0'] == top );
  Magazine->set(a_magazine, "tops", Paws->String->thing(tops)); ASSERT( (string)s2->bytes['\0'] == tops );
  
  Magazine->set(a_magazine, "bar",  Paws->String->thing(bar));
  ASSERT( (string)a_magazine->root->bytes['b']->bytes['a']->bytes['r']->bytes['\0'] == bar );
  
  SUCCEED;
}
