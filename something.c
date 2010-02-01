#include <stdio.h>
#include "Source/Paws.h"

void pretty_print(thing);

void pretty_print_list(list this) { ll_size i;
  printf("(");
  for (i = 1; i < this->content->length; ++i) {
    if (i > 1) printf(", ");
    pretty_print(List.at(this, i));
  }
  printf(")");
}

void pretty_print(thing this) {
  /* TODO: Support non-`list` `thing`s */
  pretty_print_list(this->pointer.list);
}

int main(void) {
  list root_list = List.create(),
     first_child = List.create(),
        subchild = List.create(),
    second_child = List.create();
  
  List.affix(first_child, List.to_thing(subchild));
  List.affix(root_list, List.to_thing(first_child));
  List.affix(root_list, List.to_thing(second_child));
  
  pretty_print_list(root_list);
  printf("\n");
  
  if (false
  ||  List.at(root_list, 1)->pointer.list != first_child
  ||  List.at(root_list, 2)->pointer.list != second_child
  ||  List.at(root_list, 2)->pointer.list != second_child
  )
    return(1);
  
  return(0);
}
