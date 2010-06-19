#define MAGAZINE_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
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
