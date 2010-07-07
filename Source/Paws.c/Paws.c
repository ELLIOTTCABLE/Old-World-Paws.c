#if !defined(PAWS_DECLARATIONS)
# define     PAWS_DECLARATIONS

#if defined(DECLARATIONS) && !defined(INTERNALIZE)
# define PAWS_C__BEHEST__EXTERNALIZE
# define EXTERNALIZE
#endif
# if !defined(DECLARATIONS)
#   define PAWS_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Paws.c/Ancillary/Threading/Threading.c"
#     include "Paws.c/Ancillary/Magazine/Magazine.c"
#     include "Paws.c/Ancillary/Unit/Unit.c"

#     include "Paws.c/Types/list/list.c"
#     include "Paws.c/Types/routine/routine.c"
#     include "Paws.c/Types/execution/execution.c"
#     include "Paws.c/Types/numeric/numeric.c"
#     include "Paws.c/Types/string/string.c"

#     include "Paws.c/Core.h"
#     include "Paws.c/Types/Types.h"
# if defined(PAWS_C__BEHEST)
#   undef DECLARATIONS
# endif
#if defined(PAWS_C__BEHEST__EXTERNALIZE)
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
 *       a_list = List->allocate();
 *   
 * - A `typedef`’d type (also of the same name), as a *reference* (pointer) to items of the original datatype
 *   `struct`. This is what most of the core API methods return:
 *   
 *       list   a_list;
 *       a_list = List->allocate();
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
  struct E(Magazine)     *Magazine;
  struct E(Unit)         *Unit;
  
  struct E(List)         *List;
  struct E(Routine)      *Routine;
  struct E(Execution)    *Execution;
  struct E(Numeric)      *Numeric;
  struct E(String)       *String;
  
  /* `Paws` functions */
  // None
};
struct Paws extern *Paws;

void           prepare_Paws   ( void );
void    Paws__register_Paws   ( void );



#endif
#if !defined(DECLARATIONS) && !defined(PAWS_IMPLEMENTATION) /* ========================================== BODY */
# define                               PAWS_IMPLEMENTATION
# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


                          struct Paws // »
                                *Paws   = NULL;
void Paws__register_Paws(void) { Paws   = malloc(sizeof(struct Paws));
  
  struct Paws // »
  data = {
    .Threading    = NULL,
    .Magazine     = NULL,
    .Unit         = NULL,
    
    .List         = NULL,
    .Routine      = NULL,
    .Execution    = NULL,
    .Numeric      = NULL,
    .String       = NULL
  };
  
  memcpy(Paws, &data, sizeof(struct Paws));
  
  Paws__register_Threading();
  Paws__register_Magazine();
  Paws__register_Unit();
  
  Paws__register_List();
  Paws__register_Routine();
  Paws__register_Execution();
  Paws__register_Numeric();
  Paws__register_String();
}


/* FIXME: Find a way to run this with the tests without `constructor`, for `gcc` compatibility. */
void constructor prepare_Paws(void) { Paws__register_Paws(); }

#endif
