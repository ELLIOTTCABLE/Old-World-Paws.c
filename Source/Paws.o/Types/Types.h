#define TYPES_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif


/* This file exists simply to forward-declare some structs and types used throughout the rest of the Paws.o
 * codebase.
 * 
 * You should never have a reason to include or use this file; it’s included everywhere it is necessary.
 */

        struct E(list); /* The struct behind `infrastructure list`. */
typedef struct E(list)* E(list);

        struct E(routine); /* The struct behind `infrastructure routine`. */
typedef struct E(routine)* E(routine);

        struct E(numeric); /* The struct behind `infrastructure numeric`. */
typedef struct E(numeric)* E(numeric);

        struct E(string); /* The struct behind `infrastructure string`. */
typedef struct E(string)* E(string);


        struct E(thing); /* A union representing a pointer to *any* core Paws datatype */
typedef struct E(thing) E(thing);

struct E(thing) {
  enum /* isa’s */ {
    E(NOTHING),
    
    E(LIST),
    E(ROUTINE),
    E(NUMERIC),
    E(STRING)
  } const isa;
  
  union /* thing’s */ {
    void       *nothing;
    
    E(list)     list;
    E(routine)  routine;
    E(numeric)  numeric;
    E(string)   string;
  } const pointer;
};
