#include "Cest.h"

#include <stdlib.h>
#include <string.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM) \
  strncpy(TO, FROM, sizeof(TO)); TO[sizeof(TO) - 1] = '\0'

void  cest__enroll  (cest);
cest  cest__create  (char[], char[], bool (*)(void));

struct Cest const Cest = {
  cest__enroll,
  cest__create,
  
  .first = NULL
};

void cest__enroll(cest a_cest) {
  
}

cest cest__create(char name[], char namespace[], bool (*function)(void)) {
  /* LEAK: All up in yo’ beeswax, leakin’ like a sieve! \m/ ^.^ \m/ */
  cest this = malloc(sizeof(struct cest));
  
  this->function        = function;
  STRCPY(this->namespace, namespace);
  STRCPY(this->name,      name);
  
  return this;
}

int main() {
  
  return 0;
}
