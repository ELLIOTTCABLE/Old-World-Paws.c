#define PAWS_H_INCLUDED

#ifndef TYPES_H_INCLUDED
#  include "Paws.o/Types.h"
#endif

#ifndef LIST_H_INCLUDED
#  include "list/list.h"
#endif
#ifndef NUMERIC_H_INCLUDED
#  include "numeric/numeric.h"
#endif

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
