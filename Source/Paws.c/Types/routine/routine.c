#if !defined(ROUTINE_DECLARATIONS)
# define     ROUTINE_DECLARATIONS

#if !defined(DECLARATIONS)
# define ROUTINE_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.c/Core.h"
#   include "Paws.c/Types/Types.h"

#   include "ast.c"
#   include "Paws.c/Types/list/list.c"

#   include <stdbool.h>
#if defined(ROUTINE_C__BEHEST)
# undef DECLARATIONS
#endif


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
 * see `Paws.c` for a much more thorough explanation); as long as your `native` takes soemthing that is mask-safe
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
    union { E(node) scope; E(native) function; } //»
            _; /* A pointer to either a `SCOPE` `node` (this routine’s AST), or a native function */
  }       implementation;
};


/* ### Method Declarations ### */

struct E(Routine) {
  /* `Routine` functions */
  E(routine)    (*allocate)   ( E(node) implementation );
  E(routine)    (*expose)     ( E(native) implementation, bool simple );
  
  /* `struct routine` methods */
  E(thing)      (*thing)      ( E(routine) this );
  void          (*execute)    ( E(routine) this, E(thing) argument );
};
#if !defined(EXTERNALIZE)
  struct E(Routine) extern *Routine;
#endif

void    Paws__register_Routine    ( void );



#endif
#if !defined(DECLARATIONS) && !defined(ROUTINE_IMPLEMENTATION) /* ======================================= BODY */
# define                               ROUTINE_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.c/Paws.c"
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


/* ### Method Declarations ### */

routine     Routine__allocate   (node   implementation);
routine     Routine__expose     (native implementation, bool simple);

thing       routine__thing      (routine this);
void        routine__execute    (routine this, thing argument);

                             struct Routine // »
                                   *Routine   = NULL;
void Paws__register_Routine(void) { Routine   = malloc(sizeof(struct Routine));
                              Paws->Routine   = Routine;
  
  struct Routine // »
  data = {
    .allocate   = Routine__allocate,
    .expose     = Routine__expose,
    
    .thing      = routine__thing,
    .execute    = routine__execute
  };
  
  memcpy(Routine, &data, sizeof(struct Routine));
  
  Paws__register_AST();
  Paws__register_Node();
}


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure routine`, and returns a C `routine` (a pointer to a
 * `struct routine`.) It takes an either an AST’s `SCOPE` `node`, or a pointer to a native C function (the
 * signature of which is expected to match `void (*)( E(thing) exe )`, though the usual function-pointer
 * semantics apply). The second argument is a `bool` describing whether the first argument was the former or the
 * latter (to be `true` in the case of a function pointer).
 * 
 * If you pass in an AST instead of a native implementation, this copies the content of that `SCOPE`, allowing
 * you to destroy or modify the passed AST as you desire. */
routine _Routine__allocate(bool nate, bool simple) {
  routine this = malloc(sizeof(struct routine));
  
  this->content = LL->allocate();
  
  this->simple                    = simple;
  this->implementation.native     = nate;
  this->implementation._.scope    = NULL;
  
  return this;
}

routine  Routine__allocate(node implementation) {
  routine this =  _Routine__allocate(false, false);
  
  /* TODO: Check if `implementation` is actually a `SCOPE`-type `node`. */
  this->implementation.native     = false;
  this->implementation._.scope    = Node->duplicate(implementation);
  
  return this;
}
routine  Routine__expose  (native implementation, bool simple) {
  routine this = _Routine__allocate(true, simple);
  
  this->implementation.native       = true;
  this->implementation._.function   = implementation;
  
  return this;
}


/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union. */
thing routine__thing(routine this) {
  struct thing something = {
    .isa = ROUTINE,
    .pointer = { .routine = this }
  };
  
  return something;
}

/* This executes a `routine` directly, without requiring that you properly setting up an `execution`. Unless you
 * have a reason to be using this, you should probably be calling `Execution->exercise()` instead. */
void routine__execute(routine this, thing argument) {
  if (this->implementation.native) {
    if (this->simple)   ( (void (*)(thing))    this->implementation._.function )(argument                   );
                 else   ( (void (*)(execution))this->implementation._.function )(Paws->Execution->allocate());
  } else {
    /* TODO: Implement me! */
  }
  
  /* It’s important to note that this might not ever get around to `return`ing, because asynchronous routines
   * have a good chance of `pthread_exit(3)`ing (or otherwise terminating the `routine` execution early), if they
   * farm out a call to another `routine` or something. */
  return;
}

#endif
