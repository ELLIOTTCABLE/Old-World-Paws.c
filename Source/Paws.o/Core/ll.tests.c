#include "ll.c"

#include <stdbool.h>
/* FIXME: These shouldn’t depend on `list.c` */
#ifndef LIST_H_INCLUDED
#  include "Paws.o/list/list.h"
#endif

#ifndef CEST_H_INCLUDED
#  include "Cest.h"
#endif

#define A_LIST \
  List.to_thing(List.create())

CEST(LL, create) {
  return true;
}

CEST(LL, anterior_insert) {
  return true;
}

CEST(LL, posterior_insert) {
  return true;
}

CEST(LL, prefix) {
  return true;
}

CEST(LL, affix) {
  return true;
}

CEST(LL, at) {
  return true;
}


CEST(Node, create) {
  node a_node;
  
  a_node = Node.create( A_LIST );
  ASSERT(a_node->next == NULL);
  ASSERT(a_node->previous == NULL);
  
  return true;
}

CEST(Node, prefix) {
  return true;
}

CEST(Node, affix) {
  return true;
}
