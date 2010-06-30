#if !defined(ROUTINE_DECLARATIONS)
# define     ROUTINE_DECLARATIONS

#include "Paws.o/Core.h"
#include "Paws.o/Types/Types.h"

#include "ast.h"
#include "Paws.o/Types/list/list.h"

#include <stdbool.h>


/* =========================
= `infrastructure routine` =
========================= */

/* ### Data Types & Structures ### */

/* Don’t you gotta love C’s syntax for function pointers? :D Anyway, this type represents the standard function
 * signature for a ‘native routine’ in Paws—that is, if you write a C function that is intended to be usable as
 * a `routine` from libspace, then it needs to match this signature (or something which will mask out *against*
 * this signature—examples below), and then be wrapped in a `routine` object with `Routine->expose()`. */
//typedef   void          (*)( E(thing) exe )   E(native);
  typedef   void (*E(native))( E(thing) exe )            ;

/* It’s important to note that Paws types ‘collapse’ (that is, you can mask one ‘down’ to another with a C cast;
 * see `Paws.h` for a much more thorough explanation); as long as your `native` takes soemthing that is mask-safe
 * against the above signature, it is supported. Some examples:
 * 
 *    void my_func(thing something);
 *    void my_func(execution exe); // Only for complex natives
 *    void my_func(list something);
 * 
 */

/* `infrastructure routine`, the core interally-available *code* data structure.
 *--
 * TODO: More description! */
struct E(routine) {
  E(ll)   content; /* The `ll` behind this `routine`’s `list` interface */
  
  bool    simple; /* Whether or not `implementation` (if `native`) is to be treated ‘simply.’ */
  struct {
    bool    native; /* Whether or not `implementation` is a pointer to a native function */
    union { node scope; native function; } //»
            _; /* A pointer to either a `SCOPE` `node` (this routine’s AST), or a native function */
  }       implementation;
};


/* ### Method Declarations ### */

struct E(Routine) {
  /* `Routine` functions */
  E(routine)    (*allocate)   ( node implementation );
  E(routine)    (*expose)     ( native implementation, bool simple );
  
  /* `struct routine` methods */
  E(thing)      (*thing)      ( E(routine) this );
  void          (*execute)    ( E(routine) this, E(thing) argument );
};
#if !defined(EXTERNALIZE)
  struct E(Routine) extern *Routine;
#endif

void    Paws__register_Routine    ( void );

#endif
