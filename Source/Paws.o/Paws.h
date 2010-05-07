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
# if !defined(NUMERIC_H)
#   include "Paws.o/Types/numeric/numeric.h"
# endif
# if !defined(STRING_H)
#   include "Paws.o/Types/string/string.h"
# endif

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(CORE_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(INTERNALIZE)
# undef EXTERNALIZE
#endif


// It seems this is broken, at least in `clang`
// #if __has_feature(attribute_constructor)
# define constructor __attribute__((constructor))
// #endif
// #if __has_feature(attribute_packed)
# define packed      __attribute__((packed))
// #endif


/* Generally speaking, we provide *three* things for every core datatype:
 * 
 * - A `struct`, which stores the data relevant to that datatype. These can be
 *   directly allocated and referenced by their ‘struct tag’:
 *   
 *       struct list   *a_list;
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
 *       list   a_list;
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
struct Paws {
  /* Namespaces */
  struct E(Threading)   Threading;
  
  struct E(List)        List;
  struct E(Routine)     Routine;
  struct E(Numeric)     Numeric;
  struct E(String)      String;
  
  /* `Paws` functions */
  E(thing)              (*nothing)    ( void );
};
struct Paws extern Paws;
