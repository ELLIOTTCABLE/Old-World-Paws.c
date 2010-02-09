#include "Paws.o/Paws.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


void pretty_print(Paws__thing);

void pretty_print_list(Paws__list this) { Paws__ll_size i;
  printf("(");
  for (i = 1; i < this->content->length; ++i) {
    if (i > 1) printf(", ");
    pretty_print(Paws.List.at(this, i));
  }
  printf(")");
}

void pretty_print(Paws__thing this) {
  /* TODO: Support non-`list` `thing`s */
  if (this->isa == Paws__LIST)
    pretty_print_list(this->pointer.list);
}


int main(void) {
  Paws__list root_list = Paws.List.create(),
           first_child = Paws.List.create(),
              subchild = Paws.List.create(),
          second_child = Paws.List.create();
  
  Paws.List.affix(first_child, Paws.List.to_thing(subchild));
  Paws.List.affix(root_list, Paws.List.to_thing(first_child));
  Paws.List.affix(root_list, Paws.List.to_thing(second_child));
  
  pretty_print_list(root_list);
  printf("\n");
  
  if (false
  ||  Paws.List.at(root_list, 1)->pointer.list != first_child
  ||  Paws.List.at(root_list, 2)->pointer.list != second_child
  ||  Paws.List.at(root_list, 2)->pointer.list != second_child
  )
    return(1);
  
  return(0);
}
