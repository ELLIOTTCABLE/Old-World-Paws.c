#include <stdlib.h>
#include <stdbool.h>

union  thing; /* A union representing any core Paws datatype */
struct list; /* The actual struct representing Paws’ core datatype */
struct ll; /* The data storage system (a linked-list) behind `list` */
struct node; /* A single node of the linked-list consisting a ll */

union thing
{
  struct list*  list;
};

/* ======================
= `infrastructure list` =
====================== */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 * 
 * For now, we’re not considering the storage of native data types, such as
 * `infrastructure string` and `infrastructure numeric`. That could get messy.
 */
struct list
{
  struct ll*  naughty; /* The ll behind this `list` */
};

/* NOTE: This is not a traditional linked-list. We don’t iterate elements
 *       until reaching a NULL pointer; instead, we store (and maintain) the
 *       length (in nodes) and iterate based on that. This means that
 *       ‘trailing nodes’ (or, if you’re morbid, ‘zombie nodes’) can occur -
 *       nodes appearing *after* the node at the last index (as according to
 *       our stored length). This is acceptable; they’ll simply be dropped
 *       when we append elements by adding a new link to the last node.
 */
typedef unsigned long int ll_size;
struct ll
{
  struct node*  root; /* The first node in this ll */
  ll_size       length; /* The total number of nodes in this ll */
};
struct node
{
  union thing*  e; /* The thing stored at this location */
  struct node*  next; /* A pointer to the next node in this list */
};

/* ### Declarations ### */

struct ll   ll__create(union thing[]);
void        ll__affix(struct ll, union thing);

struct /* ll_methods */
{
  struct ll   (*create)(union thing[]);
  void        (*affix)(struct ll, union thing);
} const ll = { ll__create, ll__affix };

/* ### Methods ### */

/* This method initializes a new ll, with no nodes.
 * 
 * Takes a single argument, an array of children to add to this list once it
 * is created (as a convenience). If you don’t wish to add any children at
 * creation-time, pass a `NULL` pointer.
 */
struct ll ll__create_(union thing[], bool);
struct ll ll__create(union thing children[])
  { return ll__create_(children, false); }
struct ll ll__create_(union thing children[], bool is_naughty)
{
  struct ll this;
  
  this.root   = NULL;
  this.length = 0;
  
  return this;
}

/* This method affixes a new child onto a ll.
 * 
 * Takes two arguments, the affixee, and something to be appended as a child.
 */
void ll__affix(struct ll this, union thing thing)
{
  
}


/* =======
= main() =
======= */

int main()
{
  struct ll root;
  
  root = ll.create(NULL);
  
  return 0;
}
