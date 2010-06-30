#if !defined(THREAD_DECLARATIONS)
# define     THREAD_DECLARATIONS

#if !defined(DECLARATIONS)
# define THREAD_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Ancillary/Threading/Pool/Pool.c"

#   include <pthread.h>
#   include <stdbool.h>
#if defined(THREAD_C__BEHEST)
# undef DECLARATIONS
#endif


/* ==================
= Thread Management =
================== */

/* ### Data Types & Structures ### */

        struct E(thread); /* Our threading implementation’s thread object. */
typedef struct E(thread)* E(thread);

struct E(thread) {
  pthread_t     pthread; /* The underlying opaque POSIX thread-structure. (A pointer type!) */
  E(pool)       pool; /* The pool to which this thread belongs. */
  
  bool          initialized; /* Whether or not this thread is prepared to process routines */
};


/* ### Method Declarations ### */

struct E(Thread) {
  /* `Thread` functions */
  E(thread)     (*allocate)     ( E(pool) a_pool );
  void          (*initialize)   ( void *argument ); /* Actually takes a `thread` */
  E(thread)     (*current)      ( void );
  
  /* `struct thread` methods */
  void          (*work)         ( E(thread) this );
  void          (*destroy)      ( E(thread) this );
  
  /* `Thread` data */
  pthread_key_t   current_thread_key;
};
#if !defined(EXTERNALIZE)
  struct E(Thread) extern *Thread;
#endif

void    Paws__register_Thread   ( void );



#endif
#if !defined(DECLARATIONS) && !defined(THREAD_IMPLEMENTATION) /* ======================================== BODY */
# define                               THREAD_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.o/Paws.c"
#   include <stdlib.h>
#   include <string.h>
#   include <unistd.h>
# undef  DECLARATIONS


/* ### Method Declarations ### */

thread    Thread__allocate      (pool a_pool);
void      Thread__initialize    (void *argument);
thread    Thread__current       (void);

void      thread__work          (thread this);
void      thread__destroy       (thread this);

                            struct Thread // »
                                  *Thread   = NULL;
void Paws__register_Thread(void) { Thread   = malloc(sizeof(struct Thread));
                  Paws->Threading->Thread   = Thread;
  
  struct Thread // »
  data = {
    .allocate     = Thread__allocate,
    .initialize   = Thread__initialize,
    
    .work         = thread__work,
    .destroy      = thread__destroy
  };
  
  pthread_key_create(&Thread->current_thread_key, NULL);
  
  memcpy(Thread, &data, sizeof(struct Thread));
}


/* ### Method Implementations ### */

thread Thread__allocate(pool a_pool) {
  thread this     = malloc(sizeof( struct thread ));
  this->pthread   = malloc(sizeof( pthread_t     ));
  
  this->pool = a_pool;
  pthread_create(&this->pthread, NULL, (void *(*)(void *))Thread->initialize, (void *)this);
  
  return this;
}

void Thread__initialize(void *argument) {
  thread this = (thread)argument;
  
  pthread_setspecific(Thread->current_thread_key, (void *)this);
  
  this->initialized = true;
  Thread->work(this);
  Thread->destroy(this);
  
  //return; /* This can never return; `Thread->destroy()` calls `pthread_exit()`. */
}

thread Thread__current(void) {
  return (thread)pthread_getspecific(Thread->current_thread_key);
}

void thread__work(thread this) {
  /* This is the primary work loop. As long as the thread is `initialized` (meaning it hasn’t been informed that
   * it should terminate), it will wait for signals (via it’s pool’s condvar) that there is work available to be
   * done, specifically, that there are routines in the queue to be interpreted.
   * --
   * FIXME: Should we move the *loop* out of here, and just have the condition check? Perhaps move even that out,
   *        and only execute routines. */
  while (this->initialized) {
    pthread_mutex_lock  (                       this->pool->mutex);
    pthread_cond_wait   (this->pool->condition, this->pool->mutex);
    pthread_mutex_unlock(                       this->pool->mutex);
    
    /* Once the thread is woken up by a condvar signal, we check that there’s actually routines to process (if
     * not, it falls through to waiting again) */
    while (this->initialized && this->pool->size > 0)
      // Routine->execute( Pool->drip(this->pool) );
                           Pool->drip(this->pool)  ;
  }
  
  /* Usually, this is called from `Thread->initialize()`, so it’s quite likely that the thread will destroy
   * itself after this `return`s. */
  return;
}

void thread__destroy(thread this) {
  this->initialized = false;
  
  /* If `this` is the current thread, we directly kill ourselves after having cleaned up. Else, we `join` against
   * the passed `thread`, blocking until it finishes its work and terminates. We only preform the actual
   * `free`ing in the former case, because the latter case will *cause* the former, eventually. */
  if (pthread_equal( pthread_self(), this->pthread )) {
    /* FIXME: How do I deallocate the `pthread_t` structure? There’s no documented `pthread_destroy()` function. */
    /* FIXME: How do I ensure nobody else tries to access this after it is freed? Other people may still have
     *        references to it. */
    free(this);
    pthread_exit(NULL);
  } else {
    /* TODO: Find a way to signal a specific thread to wake, instead of broadcasting a pointless wake to *all*
     *       threads in the pool. Seems wasteful, if not dangerous. */
    pthread_mutex_lock    (this->pool->mutex);
    pthread_cond_broadcast(this->pool->condition);
    pthread_mutex_unlock  (this->pool->mutex);
    
    /* TODO: Replace this with an ‘is active’ mutex; prevent any destructive modifications to the `thread`
     *       structure while it’s running. Locking against that mutex would be equivalent to `join`ing, because
     *       the thread would only release the mutex while it’s shutting down. */
    pthread_join(this->pthread, NULL);
  }
  
  return; /* This will never return, if called from the thread itself */
}

#endif
