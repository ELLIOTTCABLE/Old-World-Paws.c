#if !defined(MAGAZINE_DECLARATIONS)
# define     MAGAZINE_DECLARATIONS

#if !defined(DECLARATIONS)
# define MAGAZINE_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Core.h"
#   include "Paws.o/Types/Types.h"
#if defined(MAGAZINE_C__BEHEST)
# undef DECLARATIONS
#endif


/* ### Data Types & Structures ### */

        struct E(magazine); /* Our uniques-store data structure */
        struct E(cartridge); /* A single node of our uniques-store */
typedef struct E(magazine)* E(magazine);
typedef struct E(cartridge)* E(cartridge);

// A function that, given the magazine and a key, returns a `thing` to store for that key. Is used by `get()` for
// the case of a missing result.
typedef E(thing) (*E(setter))( E(magazine) this, char key[] );

struct E(magazine) {
  E(kind)         holds;
  E(cartridge)    root;
};

struct E(cartridge) {
  // This will actually be internally cast to the appropriate type-pointer internally for an ASCII null.
  // Therefore, dereferencing the elements of this array are not guaranteed to universally return a `cartridge`
  // (that is, a pointer to a `struct cartridge`—the next node in the trie). Instead, you must test whether
  // you’re indexing into the `'\0'`th position in the array; if so, the result will be a type pointer (which you
  // will probably want to annotate into a proper `thing` using the `isa` associated with the `magazine`).
  // Otherwise, it *will* be a `cartridge`, a pointer to a `struct cartridge` (or possibly `NULL`).
  E(cartridge)   bytes[256];
};

/* ### Method Declarations ### */

struct E(Magazine) {
  /* `Magazine` functions */
  E(magazine)   (*allocate)     ( E(kind) holds );
  
  /* `struct magazine` methods */
  E(thing)      (*get)          ( E(magazine) this, char key[], E(setter) callback );
  void          (*set)          ( E(magazine) this, char key[], E(thing) value );
};
#if !defined(EXTERNALIZE)
  struct E(Magazine) extern *Magazine;
#endif

void    Paws__register_Magazine   ( void );



#endif
#if !defined(DECLARATIONS) && !defined(MAGAZINE_IMPLEMENTATION) /* ============================================ BODY */
# define                               MAGAZINE_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.o/Paws.c"
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


/* ### Method Declarations ### */

magazine    Magazine__allocate            (kind holds);

thing       magazine__get                 (magazine this, char key[], setter callback);
void        magazine__set                 (magazine this, char key[], thing value);

cartridge   static Cartridge__allocate    (void);

                              struct Magazine // »
                                    *Magazine   = NULL;
void Paws__register_Magazine(void) { Magazine   = malloc(sizeof(struct Magazine));
                               Paws->Magazine   = Magazine;
  
  struct Magazine // »
  data = {
    .allocate   = Magazine__allocate,
    
    .get        = magazine__get,
    .set        = magazine__set
  };
  
  memcpy(Magazine, &data, sizeof(struct Magazine));
}


/* ### Method Implementations ### */

magazine Magazine__allocate(kind holds) {
  magazine this         = malloc(sizeof( struct magazine ));
           this->root   = Cartridge__allocate();
  
  this->holds = holds;
  
  return this;
}

thing _magazine__get(cartridge cart, char key[], cartridge **address);
thing  magazine__get(magazine  this, char key[], setter callback) { cartridge *address; void *rv;
  if ((rv = _magazine__get(this->root, key, &address).pointer.unknown) != NULL)
                             return (thing){ {rv}, this->holds };
  else if (callback == NULL) return (thing){ {NULL} };
  
  thing result = callback(this, key);
  if (result.isa != this->holds) return (thing){ {NULL} };
  
  *address = (cartridge)result.pointer.unknown;
  return result;
}
thing _magazine__get(cartridge cart, char key[], cartridge **address) {
                       cartridge *stacked_cartridge;
  if (address == NULL) address = &stacked_cartridge;
                      *address = &cart->bytes[ ((unsigned char*)key)[0] ];
  
  if (*key == '\0') return (thing){ {**address} };
  
  if (**address == NULL) **address = Cartridge__allocate();
  return  _magazine__get(**address, ++key, address);
}

void magazine__set(magazine this, char key[], thing value) {
                        cartridge *address;
  _magazine__get(this->root, key, &address);
  if (value.isa == this->holds)   *address = (cartridge)value.pointer.unknown;
  
  return;
}

/* This doesn’t belong to any namespace struct, but it’s just utilized internally… so no biggie. */
static cartridge Cartridge__allocate(void) {
  cartridge this = malloc(sizeof( struct cartridge ));
  
  memset(this->bytes, 0, sizeof(magazine) * 256);
  
  return this;
}

#endif
