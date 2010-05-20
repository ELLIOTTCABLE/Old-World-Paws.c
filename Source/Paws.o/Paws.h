#define PAWS_H


#if !defined(INTERNALIZE)
# define EXTERNALIZE
#endif

# if !defined(THREADING_H)
#   include "Paws.o/Ancillary/Threading/Threading.h"
# endif

# if !defined(LIST_H)
#   include "Paws.o/Types/list/list.h"
# endif
# if !defined(ROUTINE_H)
#   include "Paws.o/Types/routine/routine.h"
# endif
# if !defined(EXECUTION_H)
#   include "Paws.o/Types/execution/execution.h"
# endif
# if !defined(NUMERIC_H)
#   include "Paws.o/Types/numeric/numeric.h"
# endif
# if !defined(STRING_H)
#   include "Paws.o/Types/string/string.h"
# endif

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(INTERNALIZE)
# undef EXTERNALIZE
#endif


/* Generally speaking, we provide *three* things for every core datatype:
 * 
 * - A `struct`, which stores the data relevant to that datatype. These can be directly allocated and referenced
 *   by their ‘struct tag’:
 *   
 *       struct list   *a_list;
 *       a_list = malloc(sizeof(struct list));
 *   
 * - A `const struct` of the same name, capitalized, containing function pointers and important values
 *   (constants) relevant to that datatype:
 *   
 *       a_list = List->create();
 *   
 * - A `typedef`’d type (also of the same name), as a *reference* (pointer) to items of the original datatype
 *   `struct`. This is what most of the core API methods return:
 *   
 *       list   a_list;
 *       a_list = List->create();
 *   
 * It’s important to remember that `list` is a pointer to something, while `struct list` is that thing itself.
 * 
 * For convenience, we also provide a `union thing`, which is a combined type for a pointer to any core
 * datatype’s `struct`. This is typedef’d as well (also to `thing`), but directly, not as a pointer (since it is
 * intended to *contain* pointers). Quite a few core API methods return this, or expect one of these, instead of
 * a particular type’s struct, when it is possible for various datatypes to be interchangably involved in the
 * operations performed/services provided by that method.
 * 
 * By design, there’s also a bit of memory mapping consistency between the internal data types. Specifically:
 * 
 * 1. `thing`s can be safely masked out as a pointer specific to any type, which means you can immediately treat
 *    any `thing` as any other datatype’s typedef’d pointer. For instance, imagine `List->at()` returns as
 *    `thing` (which it does, because any core datatype could be stored at any index on a `list`), but you need
 *    to pass the result to another call to `List->at()` as a `list`. Because the memory behind a `thing` is
 *    interpretable as a `list` pointer, we can cast it as follows, without worrying about the fact that we
 *    are *actually* passing a `thing`:
 *    
 *        thing   result    = List->at( (list)List->at(a_list, 0), 42 );
 *    
 * 2. Every core datatype shares the same basic memory layout as the `list` datatype, allowing you to cast *any*
 *    datatype (even an unknown one, such as casting the pointer from a `thing` without bothering to check the
 *    associated `isa` field) to `list` without segfaulting. For instance, suppose we had a `numeric`, but we
 *    weren’t currently interested in the native numeric representation behind that datatype; we could cast it to
 *    a `list` to preform generic Paws `List` operations upon it thusly:
 *    
 *        thing   result    = List->at( (list)my_numeric );
 *    
 */
struct Paws {
  /* Namespaces */
  struct E(Threading)    *Threading;
  
  struct E(List)         *List;
  struct E(Routine)      *Routine;
  struct E(Execution)    *Execution;
  struct E(Numeric)      *Numeric;
  struct E(String)       *String;
  
  /* `Paws` functions */
  E(thing)              (*nothing)    ( void );
};
struct Paws extern *Paws;

void           prepare_Paws   ( void );
void    Paws__register_Paws   ( void );
