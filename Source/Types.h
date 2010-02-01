#define TYPES_H_INCLUDED

typedef unsigned long int ll_size;

        struct ll; /* Our data storage system (a doubly-linked-list) */
        struct node; /* A single node of an `ll` */
typedef struct ll*    ll;
typedef struct node*  node;

        struct list; /* The struct behind `infrastructure list`. */
typedef struct list* list;

        struct thing; /* A union representing any core Paws datatype */
typedef struct thing* thing;

struct thing {
  
  enum /* isa’s */ {
    LIST
  } isa;
  
  union /* thing’s */ {
    list list;
  } pointer;
  
};
