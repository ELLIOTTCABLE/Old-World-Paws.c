#define PAWS_H_INCLUDED

typedef unsigned long int ll_size;

/* Generally speaking, we provide *three* things for every core datatype:
 * 
 * - A `struct`, which stores the data relevant to that datatype. These can be
 *   directly allocated and referenced by their ‘struct tag’:
 *   
 *       struct list*  a_list;
 *       a_list = malloc(sizeof(struct list));
 *   
 * - A `const struct` of the same name, capitalized, containing function
 *   pointers and important values (constants) relevant to that datatype:
 *   
 *       a_list = List.create();
 *   
 * - A `typedef`’d type (also of the same name), as a *reference* (pointer) to
 *   items of the original datatype `struct`. This is what most of the core
 *   API methods return:
 *   
 *       list a_list;
 *       a_list = List.create();
 *   
 * It’s important to remember that `list` is a pointer to something, while
 * `struct list` is that thing itself.
 * 
 * For convenience, we also provide a `union thing`, which is a combined type
 * for a pointer to any core datatype’s `struct`. This is typedef’d as well
 * (also to `thing`), but directly, not as a pointer (since it is intended to
 * *contain* pointers). Quite a few core API methods return this, or expect
 * one of these, instead of a particular type’s struct.
 */

        struct thing; /* A union representing any core Paws datatype */
typedef struct thing* thing;

        struct ll; /* Our data storage system (a doubly-linked-list) */
        struct node; /* A single node of an `ll` */
typedef struct ll*    ll;
typedef struct node*  node;

        struct list; /* The struct behind `infrastructure list`. */
typedef struct list* list;

struct thing {
  enum /* isa’s */ {
    LIST
  } isa;
  union /* thing’s */ {
    list list;
  } pointer;
};


/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

/* This implements a pseudo-‘doubly-linked list’ structure that is the data
 * storage system responsible for `infrastructure list`, and every other core
 * datatype based thereupon.
 * 
 * Note: This is not a traditional linked list. We don’t iterate elements
 *       until reaching a `NULL` pointer; instead, we store (and maintain) the
 *       length (in nodes) and iterate based on that. This means that
 *       ‘trailing nodes’ (or, if you’re morbid, ‘zombie nodes’) can occur -
 *       nodes appearing before/after the `node` at the last/first index (that
 *       is, according to our stored `length`). This is currently considered
 *       acceptable; they’ll simply be dropped when we affix/prefix elements
 *       (as that process replaces the pointer to the next/previous node.)
 */
struct ll {
  node    first; /* A pointer to the first `node` in this `ll` */
  node    last; /* A pointer to the last `node` in this `ll` */
  ll_size length; /* The total number of `node`s in this `ll` */
};
struct node {
  thing   thing; /* The `thing` stored at this location in the `ll` */
  node    next; /* A pointer to the next `node` in the `ll` */
  node    previous; /* A pointer to the previous `node` in the `ll` */
};

/* ### Method Declarations ### */

struct LL_methods {
  ll    (*create) (void);
  void  (*anterior_insert)  (ll, node, ll_size);
  void  (*posterior_insert) (ll, node, ll_size);
  void  (*prefix) (ll, node);
  void  (*affix)  (ll, node);
  node  (*at)     (ll, ll_size);
} const extern LL;

struct Node_methods {
  node  (*create) (thing);
  void  (*prefix) (node, node);
  void  (*affix)  (node, node);
} const extern Node;


/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 * 
 * For now, we’re not considering the storage of native data types, such as
 * `infrastructure string` and `infrastructure numeric`. That could get messy.
 */
struct list {
  ll      content; /* The `ll` behind this `list` */
};

/* ### Method Declarations ### */

struct List_methods {
  list  (*create)   (void);
  thing (*to_thing) (list);
  void  (*insert)   (list, thing, ll_size);
  void  (*prefix)   (list, thing);
  void  (*affix)    (list, thing);
  thing (*at)       (list, ll_size);
} const List;
