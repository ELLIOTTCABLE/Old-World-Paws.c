#include <stdlib.h>
#include <stdbool.h>

/* ======================
= `infrastructure list` =
====================== */

/* ### Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 * 
 * For now, we’re not considering the storage of native data types, such as
 * `infrastructure string` and `infrastructure numeric`. That could get messy.
 */
struct list; /* The actual struct representing Paws’ core datatype */
struct node; /* A single node of the linked-list consisting a `list` */

#define LIST_LENGTH_TYPE unsigned long int
struct list
{
  struct node* naughty; /* A pointer to this’s root node */
  LIST_LENGTH_TYPE length; /* The current length of this linked list */
};

struct node
{
  struct list* e; /* The `list` stored at this location in the linked-list */
  struct node* next; /* A pointer to the next node in this list */
};

/* ### Declarations ### */

struct list list__create(struct list[]);
void        list__append(struct list, struct list);
struct list list__last(struct list);

struct list list__create_(struct list[], bool);
struct /* list_methods */
{
  struct list (*create)(struct list[]);
  void        (*append)(struct list, struct list);
  struct list (*last)(struct list);
} const list = { list__create, list__append, list__last };

/* ### Methods ### */

/* This method returns a new struct representing an `infrastructure list`.
 * It also initializes an empty naughty `list`, and assigns it to this `list`.
 * 
 * Takes a single argument, an array of children to add to this list once it
 * is created (as a convenience). If you don’t wish to add any children at
 * creation-time, pass a `NULL` pointer.
 */

struct list list__create(struct list children[])
  { return list__create_(children, false); }
struct list list__create_(struct list children[], bool is_naughty)
{
  struct list this;
  struct list this_naughty;
  struct node this_naughty_node;
  
  /* TODO: Use a node-creation function? */
  this_naughty = is_naughty ? this : list__create_(NULL, true);
  this_naughty_node.e    = &this_naughty;
  this_naughty_node.next = NULL;
  
  this.naughty = &this_naughty_node;
  this.length  = 1;
  
  return this;
}

/* This method affixes a new child onto our `list`.
 * 
 * Takes two arguments, the affixee, and another `list` to be appended as a
 * child.
 */
void list__append(struct list this, struct list element)
{
  list.last(this);
}

/* FIXME: This currently returns an object. `list__append()` needs a node, so
 *        it can update `next` to point to a new node.
 */
struct list list__last(struct list this)
{
  struct node* last_node = this.naughty;
  for(LIST_LENGTH_TYPE i = 1; i < this.length; ++i)
    last_node = last_node->next;
  return *last_node->e;
}


/* =======
= main() =
======= */

int main()
{
  struct list root;
  
  root = list.create(NULL);
  
  return 0;
}
