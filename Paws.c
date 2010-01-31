#include <stdlib.h>
#include <stdio.h>
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

        struct ll; /* Our data storage system (a doubly-linked-list) */
        struct node; /* A single node of an `ll` */
typedef struct ll*    ll;
typedef struct node*  node;

        struct list; /* The struct behind `infrastructure list`. */
typedef struct list* list;

union thing {
  list list;
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
  thing   e; /* The `thing` stored at this location in the `ll` */
  node    next; /* A pointer to the next `node` in the `ll` */
  node    previous; /* A pointer to the previous `node` in the `ll` */
};

/* ### Method Declarations ### */

ll    ll__create  ();
void  ll__anterior_insert   (ll, node, ll_size);
void  ll__posterior_insert  (ll, node, ll_size);
void  ll__prefix  (ll, node);
void  ll__affix   (ll, node);
node  ll__at      (ll, ll_size);
struct /* ll_methods */ {
  ll    (*create) ();
  void  (*anterior_insert)  (ll, node, ll_size);
  void  (*posterior_insert) (ll, node, ll_size);
  void  (*prefix) (ll, node);
  void  (*affix)  (ll, node);
  node  (*at)     (ll, ll_size);
} const LL = {
  ll__create,
  ll__anterior_insert,
  ll__posterior_insert,
  ll__prefix,
  ll__affix,
  ll__at
};

node  node__create  (thing);
void  node__prefix  (node, node);
void  node__affix   (node, node);
struct /* node_methods */ {
  node  (*create) (thing);
  void  (*prefix) (node, node);
  void  (*affix)  (node, node);
} const Node = { node__create, node__prefix, node__affix };


/* ### Method Implementations ### */

/* This method initializes a new ll, with no nodes. The `first` and `last` are
 * set to `NULL` pointers, and `length` is initialized to zero.
 */
ll ll__create() {
  ll this = malloc(sizeof(struct ll));
  
  this->first  = NULL;
  this->last   = NULL;
  this->length = 0;
  
  return this;
}

void ll__anterior_insert(ll this, node child, ll_size index) {
  if (index == this->length - 1)
    /* TODO: Error condition, cannot anterior-insert at last position */;
  else {
    Node.prefix(LL.at(this, index), child);
    this->length++;
  }
}

void ll__posterior_insert(ll this, node child, ll_size index) {
  if (index == 0)
    /* TODO: Error condition, cannot posterior-insert at first position */;
  else {
    Node.affix(LL.at(this, index - 1), child);
    this->length++;
  }
}

/* This method prefixes a new child `node` onto an `ll`. This will ensure that
 * the first element in the `ll`, after the appending, is the new node.
 * 
 * Takes two arguments, the prefixee (`this`), and a `node` to be prefixed
 * onto it as a child.
 */
void ll__prefix(ll this, node child) {
  if (this->length < 1)
    this->last = child;
  else
    Node.prefix( this->first, child );
  this->first = child;
  this->length++;
}

/* This method affixes a new child `node` onto an `ll`. This will ensure that
 * the last element in the `ll`, after the appending, is the new node.
 * 
 * Takes two arguments, the affixee (`this`), and a `node` to be affixed onto
 * it as a child.
 */
void ll__affix(ll this, node child) {
  if (this->length < 1)
    this->first = child;
  else
    Node.affix( this->last, child );
  this->last = child;
  this->length++;
}

/* This method returns a `node` at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `index`.
 */
node ll__at(ll this, ll_size index) {
  node result;
  
  if (index >= this->length)
    return NULL;
  
  if (index <= this->length / 2) {
    result = this->first;
    for (ll_size i = 0; i < index; ++i)
      result = result->next;
  } else {
    result = this->last;
    for (ll_size i = this->length - 1; i > index; --i)
      result = result->next;
  }
  
  return result;
}

/* This method creates a new `node` for a given `thing`. `next` and `previous`
 * will also be initialized to a `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `node` as `e`.
 */
node node__create(thing thing) {
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  node this = malloc(sizeof(struct node));
  
  this->e        = thing;
  this->next     = NULL;
  this->previous = NULL;
  
  return this;
}

/* This method inserts another node *before* this node in the chain of a
 * linked list.
 * 
 * If there’s already a node attached before this node, and there *isn’t* one
 * attached before the node being inserted, then that next-node will be
 * affixed to our new node, thus keeping the chain intact if possible.
 * 
 * Note: See the notes on `Node.affix()`.
 */
void node__prefix(node this, node other) {
  if (this->previous != NULL)
    if (other->previous == NULL)
      node__prefix(other, this->previous);
    else
      this->previous->next = NULL;
  
  other->next     = this;
  this->previous  = other;
}

/* This method inserts another node *after* this node in the chain of a
 * linked list.
 * 
 * If there’s already a node attached after this node, and there *isn’t* one
 * attached after the node being inserted, then that next-node will be
 * affixed to our new node, thus keeping the chain intact if possible.
 * 
 * Note: Realize that due to that copy-next mechanic, you can splice
 *       node-strings on top of eachother, but all nodes *after* this node in
 *       the original chain will be lost.
 */
void node__affix(node this, node other) {
  if (this->next != NULL)
    if (other->next == NULL)
      node__affix(other, this->next);
    else
      this->next->previous = NULL;
  
  other->previous = this;
  this->next      = other;
}


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
void  list__insert    (list, thing, ll_size);
void  list__prefix    (list, thing);
void  list__affix     (list, thing);
thing list__at        (list, ll_size);
struct /* node_methods */ {
  list  (*create)   ();
  thing (*to_thing) (list);
  void  (*insert)   (list, thing, ll_size);
  void  (*prefix)   (list, thing);
  void  (*affix)    (list, thing);
  thing (*at)       (list, ll_size);
} const List = {
  list__create,
  list__to_thing,
  list__insert,
  list__prefix,
  list__affix,
  list__at
};

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

void list__insert(list this, thing child, ll_size index) {
  LL.posterior_insert(this->content, Node.create(child), index); }

void list__prefix(list this, thing child) {
  LL.prefix(this->content, Node.create(child)); }

void list__affix(list this, thing child) {
  LL.affix(this->content, Node.create(child)); }

thing list__at(list this, ll_size index) { return
  LL.at(this->content, index)->e; }


/* =======
= main() =
======= */

void pretty_print(thing);

void pretty_print_list(list this) {
  printf("(");
  for(ll_size i = 1; i < this->content->length; ++i) {
    if (i > 1) printf(", ");
    pretty_print(List.at(this, i));
  }
  printf(")");
}

void pretty_print(thing this) {
  /* TODO: Support non-`list` `thing`s */
  pretty_print_list(this.list);
}

int main() {
  list root_list = List.create(),
     first_child = List.create(),
        subchild = List.create(),
    second_child = List.create();
  
  List.affix(first_child, List.to_thing(subchild));
  List.affix(root_list, List.to_thing(first_child));
  List.affix(root_list, List.to_thing(second_child));
  
  pretty_print_list(root_list);
  printf("\n");
  
  if (false
  ||  List.at(root_list, 1).list != first_child
  ||  List.at(root_list, 2).list != second_child
  ||  List.at(root_list, 2).list != second_child
  )
    return(1);
  
  return(0);
}
