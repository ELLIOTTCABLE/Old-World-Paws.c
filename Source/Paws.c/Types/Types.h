#if !defined(TYPE_DECLARATIONS)
# define     TYPE_DECLARATIONS

#include "Paws.c/Core.h"


/* This file exists simply to forward-declare some structs and types used throughout the rest of the Paws.c
 * codebase (including the `thing` union-struct).
 * 
 * You should never have a reason to include or use this file; it’s already included everywhere it is necessary.
 */

        struct E(list);
typedef struct E(list)* E(list);

        struct E(routine);
typedef struct E(routine)* E(routine);

        struct E(execution);
typedef struct E(execution)* E(execution);

        struct E(numeric);
typedef struct E(numeric)* E(numeric);

        struct E(string);
typedef struct E(string)* E(string);


        struct E(thing); /* A union representing a pointer to *any* core Paws datatype */
typedef struct E(thing) E(thing); /*
typedef   enum E(kind) E(kind); // ISO C forbids forward references to 'enum' types. YAY. >,< */

struct E(thing) {
  union /* E(thing_pointers) */ {
    void         *unknown;
    
    E(list)       list;
    E(routine)    routine;
    E(execution)  execution;
    E(numeric)    numeric;
    E(string)     string;
  } const pointer;
  
  enum E(kind) {
    E(UNKNOWN) = 0,
    
    E(LIST),
    E(ROUTINE),
    E(EXECUTION),
    E(NUMERIC),
    E(STRING)
  } const isa;
};

typedef   enum E(kind) E(kind); // See above

#endif
