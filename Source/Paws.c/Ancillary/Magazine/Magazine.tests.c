#include "Magazine.c"

#define DECLARATIONS
# include "Cest.c"

# include "Paws.c/Types/string/string.c"

# include <errno.h>
#undef  DECLARATIONS

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM) \
  strncpy(TO, FROM, sizeof(TO)); TO[sizeof(TO) - 1] = '\0'

/* Marks up unused parameters in callbacks */
#define _(_) (void)_


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

static thing testing_setter (magazine _, char key[]) { _(_);
  return Paws->String->thing(Paws->String->allocate(key));
}

CEST(magazine, get) {
  kind holds = STRING;
  magazine a_magazine = Magazine->allocate(holds);
  
  // Doing some tedious manual setup, to avoid dependency on `Magazine->set()`. (Since `String->create()` will
  // eventually depend on this, and apply to interpretation-unit specific `string` magazines, we’re going to
  // manually create empty `string` structs. We don’t actually care about the contents of the `string` struct
  // right now, we’re simply going to preform pointer equality on them.)
  string  tops = Paws->String->allocate("tops"),
           top = Paws->String->allocate("top"),
          taps = Paws->String->allocate("taps"),
           tap = Paws->String->allocate("tap");
  cartridge s2 = malloc(sizeof( struct cartridge ));                      s2->bytes['\0'] = (cartridge)tops;
  cartridge p2 = malloc(sizeof( struct cartridge )); p2->bytes['s'] = s2; p2->bytes['\0'] = (cartridge)top;
  cartridge  o = malloc(sizeof( struct cartridge ));  o->bytes['p'] = p2;
  cartridge s1 = malloc(sizeof( struct cartridge ));                      s1->bytes['\0'] = (cartridge)taps;
  cartridge p1 = malloc(sizeof( struct cartridge )); p1->bytes['s'] = s1; p1->bytes['\0'] = (cartridge)tap;
  cartridge  a = malloc(sizeof( struct cartridge ));  a->bytes['p'] = p1;
  cartridge  t = malloc(sizeof( struct cartridge ));  t->bytes['a'] = a;   t->bytes['o'] = o;
                                       a_magazine->root->bytes['t'] = t;
  
  ASSERT( Magazine->get(a_magazine, "tap",  NULL).isa            == holds );
  ASSERT( Magazine->get(a_magazine, "tap",  NULL).pointer.string == tap );
  ASSERT( Magazine->get(a_magazine, "taps", NULL).pointer.string == taps );
  ASSERT( Magazine->get(a_magazine, "top",  NULL).pointer.string == top );
  ASSERT( Magazine->get(a_magazine, "tops", NULL).pointer.string == tops );
  
  
  cartridge  r = malloc(sizeof( struct cartridge ));                       r->bytes['\0'] = NULL;
  cartridge p3 = malloc(sizeof( struct cartridge )); p3->bytes['r'] = r;  p3->bytes['\0'] = NULL;
  cartridge  u = malloc(sizeof( struct cartridge ));  u->bytes['p'] = p3;  u->bytes['\0'] = NULL;
                                                      t->bytes['u'] = u;
  
  thing tape = Magazine->get(a_magazine, "tup", testing_setter);
  ASSERT(        tape.isa                                == STRING );
  ASSERT( strcmp(Paws->String->native(tape.pointer.string), "tup") == 0 );
  
  thing taper = Magazine->get(a_magazine, "tupr",  NULL);
  ASSERT( taper.pointer.unknown == NULL );
  
  
  ASSERT( a_magazine->root->bytes['f'] == NULL );
  ASSERT( Magazine->get(a_magazine, "foo",  NULL).pointer.unknown == NULL );
  ASSERT( a_magazine->root->bytes['f'] != NULL );
  ASSERT( a_magazine->root->bytes['f']->bytes['o'] != NULL );
  ASSERT( a_magazine->root->bytes['f']->bytes['o']->bytes['o'] != NULL );
  
  
  ASSERT( a_magazine->root->bytes['b'] == NULL );
  thing bar = Magazine->get(a_magazine, "bar", testing_setter);
  ASSERT(        bar.isa                                == STRING );
  ASSERT( strcmp(Paws->String->native(bar.pointer.string), "bar") == 0 );
  
  ASSERT(   a_magazine->root->bytes['b']                                      != NULL );
  ASSERT(   a_magazine->root->bytes['b']->bytes['a']                          != NULL );
  ASSERT(   a_magazine->root->bytes['b']->bytes['a']->bytes['r']              != NULL );
  ASSERT(   a_magazine->root->bytes['b']->bytes['a']->bytes['r']->bytes['\0'] != NULL );
  ASSERT( strcmp(Paws->String->native(
    (string)a_magazine->root->bytes['b']->bytes['a']->bytes['r']->bytes['\0']), "bar") == 0 );
  
  SUCCEED;
}

CEST(magazine, set) {
  kind holds = STRING;
  magazine a_magazine = Magazine->allocate(holds);
  
  string other1 = Paws->String->allocate("other1"),
         other2 = Paws->String->allocate("other2"),
           tops = Paws->String->allocate("tops"),
            top = Paws->String->allocate("top"),
           taps = Paws->String->allocate("taps"),
            tap = Paws->String->allocate("tap"),
            foo = Paws->String->allocate("foo");
  list      bar = Paws->List->allocate();
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
  
  Magazine->set(a_magazine, "foo",  Paws->String->thing(foo));
  ASSERT(         a_magazine->root->bytes['f']                                      != NULL );
  ASSERT(         a_magazine->root->bytes['f']->bytes['o']                          != NULL );
  ASSERT(         a_magazine->root->bytes['f']->bytes['o']->bytes['o']              != NULL );
  ASSERT( (string)a_magazine->root->bytes['f']->bytes['o']->bytes['o']->bytes['\0'] == foo );
  
  Magazine->set(a_magazine, "bar",  Paws->List->thing(bar));
  ASSERT(         a_magazine->root->bytes['b']                                      != NULL );
  ASSERT(         a_magazine->root->bytes['b']->bytes['a']                          != NULL );
  ASSERT(         a_magazine->root->bytes['b']->bytes['a']->bytes['r']              != NULL );
  ASSERT( (string)a_magazine->root->bytes['b']->bytes['a']->bytes['r']->bytes['\0'] == NULL );
  
  SUCCEED;
}
