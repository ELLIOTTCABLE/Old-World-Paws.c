#if !defined(POOL_DECLARATIONS)
# define     POOL_DECLARATIONS

#if !defined(DECLARATIONS)
# define POOL_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Types/routine/routine.c"

#   include <pthread.h>
#if defined(POOL_C__BEHEST)
# undef DECLARATIONS
#endif


/* ==================
= Thread Management =
================== */

/* ### Data Types & Structures ### */

        struct E(pool); /* Our threading implementation’s queue pool. */
typedef struct E(pool)* E(pool);

typedef   unsigned long long int    E(pool_size); /* The maximum number of routine pointers in a pool */

struct E(pool) {
  pthread_mutex_t    *mutex; /* The mutex for this pool’s condvar */
  pthread_cond_t     *condition; /* A condvar that signals when routines are available to be interpreted */
  
  E(pool_size)        size; /* The number of `routine`s queued */
  E(routine)         *queue; /* An array of `routine` pointers */
};


/* ### Method Declarations ### */

struct E(Pool) {
  /* `Pool` functions */
  E(pool)       (*allocate)   ( void );
  
  /* `struct pool` methods */
  void          (*enqueue)    ( E(pool) this, E(routine) a_routine );
  E(routine)    (*drip)       ( E(pool) this );
  void          (*destroy)    ( E(pool) this );
};
#if !defined(EXTERNALIZE)
  struct E(Pool) extern *Pool;
#endif

void    Paws__register_Pool   ( void );



#endif
#if !defined(DECLARATIONS) && !defined(POOL_IMPLEMENTATION) /* ========================================== BODY */
# define                               POOL_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.o/Paws.c"
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


/* ### Method Declarations ### */

pool      Pool__allocate    (void);

void      pool__enqueue     (pool this, routine a_routine);
routine   pool__drip        (pool this);
void      pool__destroy     (pool this);

                          struct Pool // »
                                *Pool   = NULL;
void Paws__register_Pool(void) { Pool   = malloc(sizeof(struct Pool));
                Paws->Threading->Pool   = Pool;
  
  struct Pool // »
  data = {
    .allocate   = Pool__allocate,
    
    .enqueue    = pool__enqueue,
    .drip       = pool__drip,
    .destroy    = pool__destroy
  };
  
  memcpy(Pool, &data, sizeof(struct Pool));
}


/* ### Method Implementations ### */

pool Pool__allocate(void) {
  pool    this              = malloc(sizeof( struct pool     ));
          this->mutex       = malloc(sizeof( pthread_mutex_t ));
          this->condition   = malloc(sizeof( pthread_cond_t  ));
          
          this->size        = 0;
          this->queue       = NULL;
  
  /* We initialize the mutex, and just to be safe, lock against it. */
  pthread_mutex_init  (this->mutex,     NULL);
  pthread_mutex_lock  (this->mutex);
  pthread_cond_init   (this->condition, NULL);
  pthread_mutex_unlock(this->mutex);
  
  return this;
}

void pool__enqueue(pool this, routine a_routine) {
  this->queue                   = realloc(this->queue, sizeof(routine) * ++this->size);
  this->queue[this->size - 1]   = a_routine;
  
  pthread_mutex_lock  (this->mutex);
  pthread_cond_signal (this->condition);
  pthread_mutex_unlock(this->mutex);
}

routine pool__drip(pool this) {
  routine     first                   = this->queue[0];
  
  /* FIXME: Can I use `realloc(3)` here? How can I realloc to a *smaller* amount of memory, while cutting off the
   *        first element? */
  routine    *queue                   = malloc(sizeof(routine) * this->size - 1);
  memcpy(     queue, this->queue + 1,          sizeof(routine) * this->size - 1);
  
        this->queue                   = queue;
        this->size--;
  
  return first;
}

void pool__destroy(pool this) {
  /* TODO: Clean up. */
  
  // free(this);
  return;
}

#endif
