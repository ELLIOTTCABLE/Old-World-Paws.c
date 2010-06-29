#include "Pool.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>


/* ==================
= Thread Management =
================== */

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
