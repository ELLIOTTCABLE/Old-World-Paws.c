#define TYPES_H_INCLUDED

/* This file exists simply to pre-declare some structs and types used
 * throughout the rest of the Paws.o codebase.
 * 
 * You should never have a reason to include or use this file; it’s included
 * everywhere it is necessary.
 */

        struct ll; /* Our data storage system (a doubly-linked-list) */
        struct node; /* A single node of an `ll` */
typedef struct ll*    ll;
typedef struct node*  node;

        struct list; /* The struct behind `infrastructure list`. */
typedef struct list* list;

        struct numeric; /* The struct behind `infrastructure numeric`. */
typedef struct numeric* numeric;

        struct thing; /* A union representing any core Paws datatype */
typedef struct thing* thing;

struct thing {
  
  enum /* isa’s */ {
    LIST,
    NUMERIC
  } const isa;
  
  union /* thing’s */ {
    list list;
    numeric numeric;
  } const pointer;
  
};
