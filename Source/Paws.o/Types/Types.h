#define TYPES_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif


/* This file exists simply to forward-declare some structs and types used throughout the rest of the Paws.o
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
typedef struct E(thing) E(thing);

struct E(thing) {
  union /* thing’s */ {
    void       *nothing;
    
    E(list)       list;
    E(routine)    routine;
    E(execution)  execution;
    E(numeric)    numeric;
    E(string)     string;
  } const pointer;
  
  enum /* isa’s */ {
    E(NOTHING),
    
    E(LIST),
    E(ROUTINE),
    E(EXECUTION),
    E(NUMERIC),
    E(STRING)
  } const isa;
};
