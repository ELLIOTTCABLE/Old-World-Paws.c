#include "Magazine.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* ==================
= Magazine Management =
================== */

/* ### Method Declarations ### */

magazine    Magazine__allocate            (kind holds);

thing       magazine__get                 (magazine this, char *key, setter callback);
void        magazine__set                 (magazine this, char *key, thing value);

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

thing _magazine__get(cartridge cart, char *key, cartridge **address);
thing  magazine__get(magazine  this, char *key, setter callback) { cartridge *address; thing rv; if((rv =
      _magazine__get(    this->root,       key,            &address)).pointer.unknown != NULL)
    return (thing){ rv.pointer.unknown, this->holds };
  
  if (callback != NULL && (rv = callback(this, key)).isa == this->holds) {
    *address = (cartridge)rv.pointer.unknown; return rv; }
  else return (thing){ NULL };
}
thing _magazine__get(cartridge cart, char *key, cartridge **address) {
                       cartridge *stacked_cartridge;
  if (address == NULL) address = &stacked_cartridge;
                      *address = &cart->bytes[*key];
  
  if (*key == '\0') return       (thing){ **address };
            else { if (**address == NULL) **address = Cartridge__allocate();
                    return _magazine__get(**address, ++key, address); };
}

void magazine__set(magazine this, char *key, thing value) {
                        cartridge *address;
  _magazine__get(this->root, key, &address);
                                  *address = (cartridge)value.pointer.unknown;
  
  return;
}

/* This doesn’t belong to any namespace struct, but it’s just utilized internally… so no biggie. */
static cartridge Cartridge__allocate(void) {
  cartridge this = malloc(sizeof( struct cartridge ));
  
  memset(this->bytes, 0, sizeof(magazine) * 256);
  
  return this;
}
