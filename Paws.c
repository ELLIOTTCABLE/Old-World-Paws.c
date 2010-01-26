#include <stdlib.h>
#include <stdbool.h>

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

        union thing; /* A union representing any core Paws datatype */
typedef union thing thing;

        struct ll; /* The data storage system (a linked-list) behind `list` */
        struct node; /* A single node of the linked-list consisting a `ll` */
typedef struct ll*    ll;
typedef struct node*  node;

        struct list; /* The type behind `infrastructure list`. */
typedef struct list* list;

union thing {
  list list;
};

/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

/* This implements a pseudo-linked-list structure that is the data storage
 * system responsible for `infrastructure list`, and every other core
 * datatype based thereupon.
 * 
 * NOTE: This is not a traditional linked-list. We don’t iterate elements
 *       until reaching a NULL pointer; instead, we store (and maintain) the
 *       length (in nodes) and iterate based on that. This means that
 *       ‘trailing nodes’ (or, if you’re morbid, ‘zombie nodes’) can occur -
 *       nodes appearing *after* the node at the last index (as according to
 *       our stored length). This is acceptable; they’ll simply be dropped
 *       when we append elements by adding a new link to the last node.
 */
struct ll {
  node    root; /* A pointer to the first `node` in this `ll` */
  ll_size length; /* The total number of `node`s in this `ll` */
};
struct node {
  thing   e; /* The `thing` stored at this location in the `ll` */
  node    next; /* A pointer to the next `node` in the `ll` */
};

/* ### Method Declarations ### */

ll    ll__create  ();
void  ll__affix   (ll, node);
node  ll__at      (ll, ll_size);
struct /* ll_methods */ {
  ll    (*create)   ();
  void  (*affix)    (ll, node);
  node  (*at)       (ll, ll_size);
} const LL = { ll__create, ll__affix, ll__at };

node  node__create  (thing);
void  node__affix   (node, node);
struct /* node_methods */ {
  node  (*create) (thing);
  void  (*affix)  (node, node);
} const Node = { node__create, node__affix };


/* ### Method Implementations ### */

/* This method initializes a new ll, with no nodes. The `root` is set to a
 * `NULL` pointer.
 */
ll ll__create() {
  ll this = malloc(sizeof(struct ll));
  
  this->root   = NULL;
  this->length = 0;
  
  return this;
}

/* This method affixes a new child onto a ll.
 * 
 * Takes two arguments, the affixee (`this`), and a node to be appended as
 * a child.
 *--
 * FIXME: Wouldn’t this be ridiculously slow? It has to iterate through the
 * *entire* `ll` before it can affix something.
 */
void ll__affix(ll this, node child) {
  Node.affix( LL.at(this, this->length-1), child ); }

/* This method returns a pointer to the node at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `index`.
 */
node ll__at(ll this, ll_size index) {
  /* This will give us either a `NULL` pointer (if this has no root, i.e. is
   * an empty list), or the first `node` (if this *has* a `root`, i.e. is
   * *not* an empty list). */
  node last = this->root;
  
  for(ll_size i = 0; i < index; ++i)
    last = last->next;
  
  return last;
}

/* This method creates a new `node` for a given `thing`. `next` will also be
 * initialized to a `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `node` as `e`.
 */
node node__create(thing thing) {
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  node this = malloc(sizeof(struct node));
  
  this->e    = thing;
  this->next = NULL;
  
  return this;
}

void node__affix(node this, node other) {
  this->next = other; }


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

list  list__create    ();
thing list__to_thing  (list);
void  list__affix     (list, thing);
struct /* node_methods */ {
  list  (*create)   ();
  thing (*to_thing) (list);
  void  (*affix) (list, thing);
} const List = { list__create, list__to_thing, list__affix };

/* ### Method Implementations ### */

/* This method allocates a new `infrastructure list`, and returns a pointer to
 * a `struct list`.
 */
list _list__create(bool);
list  list__create() { return
     _list__create(false); }
list _list__create(bool is_naughty) {
  list this = malloc(sizeof(struct list)), naughty;
  
  this->content = LL.create();
  
  naughty = is_naughty? this:_list__create(true);
  LL.affix( this->content, Node.create(List.to_thing(naughty)) );
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union,
 * and returns that union.
 */
thing list__to_thing(list this) {
  /* FIXME: Do we need to `malloc()` this? We’re returning-by-value, not
   *        by-reference… but I’m still not sure. */
  /* thing wrapper = malloc(sizeof(union thing)); */
  thing wrapper;
  wrapper.list = this;
  
  return wrapper;
}

void list__affix(list this, thing child) {
  LL.affix(this->content, Node.create(child));
}


/* =======
= main() =
======= */

int main() {
  
  
  return 0;
}
