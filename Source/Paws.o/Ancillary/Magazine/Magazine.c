#include "Magazine.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* ==================
= Magazine Management =
================== */

/* ### Method Declarations ### */

magazine    Magazine__allocate    (kind holds);

thing       magazine__get         (magazine this, char *key, setter callback);
void        magazine__set         (magazine this, char *key, thing value);

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
           this->root   = malloc(sizeof( struct cartridge ));
  
  memset(this->root->bytes, 0, sizeof(magazine) * 256);
  this->holds = holds;
  
  return this;
}

thing _magazine__get(cartridge cart, char *key, cartridge **address);
thing  magazine__get(magazine  this, char *key, setter callback) { cartridge *address; thing rv; if((rv =
      _magazine__get(    this->root,       key,            &address)).pointer.list != NULL)
    return (thing){ rv.pointer.list, this->holds };
  
  if (callback != NULL && (rv = callback(this, key)).isa == this->holds) {
    *address = (cartridge)rv.pointer.list; return rv; }
  else return Paws->nothing();
}
thing _magazine__get(cartridge cart, char *key, cartridge **address) {
                       cartridge *stacked_cartridge;
  if (address == NULL) address = &stacked_cartridge;
                      *address = &cart->bytes[*key];
  
  if (*key == '\0') return       (thing){ **address };
               else return _magazine__get(**address, ++key, address);
}

void magazine__set(magazine this, char *key, thing value) { return; }
