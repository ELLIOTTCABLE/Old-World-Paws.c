#include "Cest.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM) \
  strncpy(TO, FROM, sizeof(TO)); TO[sizeof(TO) - 1] = '\0'

void  cest__enroll  (cest);
bool  cest__run_all (void);

cest  cest__create  (char[], char[], bool (*)(void));
bool  cest__execute (cest);

struct Cest Cest = {
  .enroll   = cest__enroll,
  .run_all  = cest__run_all,
  
  .create   = cest__create,
  .execute  = cest__execute,
  
  .first = NULL
};

void cest__enroll(cest a_cest) {
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

bool cest__run_all(void) {
  bool return_value, failed = false;
  
  cest                current;
  struct cest_node*   current_node = Cest.first;
  for (; current_node != NULL; current_node = current_node->next) {
    current = current_node->cest;
    
    return_value = Cest.execute(current);
    printf("%s/%s: %s\n", current->namespace, current->name,
      return_value ? "pass" : "fail");
    
    failed = !return_value || failed;
  }
  
  return !failed;
}

cest cest__create(char namespace[], char name[], bool (*function)(void)) {
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
