#include "Cest.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM) \
  strncpy(TO, FROM, sizeof(TO)); TO[sizeof(TO) - 1] = '\0'

#define CSI "\033["
#define SGR "m"
static const struct { char red[6]; char green[6]; char reset[6]; }
ANSIEscapes = {
  .red    = CSI "31" SGR,
  .green  = CSI "32" SGR,
  .reset  = CSI "0"  SGR
};

void  Cest__enroll  (cest);
bool  Cest__run_all (void);

cest  Cest__create  (char[], char[], bool (*)(void));
bool  cest__execute (cest);

struct Cest Cest = {
  .enroll   = Cest__enroll,
  .run_all  = Cest__run_all,
  
  .create   = Cest__create,
  .execute  = cest__execute,
  
  .first = NULL
};

void Cest__enroll(cest a_cest) {
  struct cest_node*   current = NULL;
  struct cest_node    this_node = { .cest = a_cest, .next = NULL };
  /* LEAK: Moar! */
  struct cest_node*   this = malloc(sizeof(struct cest_node));
  memcpy(this, &this_node, sizeof(struct cest_node));
  
  if (Cest.first == NULL)
    Cest.first = this;
  else {
    current = Cest.first;
    while (current->next != NULL)
      current = current->next;
    
    current->next = this;
  }
}

bool Cest__run_all(void) {
  bool return_value; int  total, succeeded;
  
  cest                current;
  struct cest_node*   current_node = Cest.first;
  
  for (total = 0, succeeded = 0; current_node != NULL;
       total++,                  current_node = current_node->next) {
    current = current_node->cest;
    return_value = Cest.execute(current);
    succeeded += return_value;
    
    printf("%s%s/%s%s\n",
      return_value ? ANSIEscapes.green : ANSIEscapes.red,
      current->namespace, current->name, ANSIEscapes.reset);
  }
  
  printf("%s%d successes%s (of %d)\n",
    succeeded < total ? ANSIEscapes.red : ANSIEscapes.green,
    succeeded, ANSIEscapes.reset, total);
  
  return !(succeeded < total);
}

cest Cest__create(char namespace[], char name[], bool (*function)(void)) {
  /* LEAK: All up in yo’ beeswax, leakin’ like a sieve! \m/ ^.^ \m/ */
  cest this = malloc(sizeof(struct cest));
  
  this->function        = function;
  STRCPY(this->namespace, namespace);
  STRCPY(this->name,      name);
  
  return this;
}

bool cest__execute(cest this) {
  return this->function();
}

int main() {
  return !Cest.run_all();
}
