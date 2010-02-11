#include "Paws.o/Paws.h"

#include <stdlib.h>
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

void pretty_print_numeric(Paws__numeric this) {
  printf("%d", Paws.Numeric.native(this));
}

void pretty_print_string(Paws__string this) {
  printf("\xE2\x80\x9C"); /* U+201C, "LEFT DOUBLE QUOTATION MARK" */
  printf("%s", Paws.String.native(this));
  printf("\xE2\x80\x9D"); /* U+201D, "RIGHT DOUBLE QUOTATION MARK" */
}

void pretty_print(Paws__thing this) {
  if (this->isa == Paws__LIST)
    pretty_print_list(this->pointer.list);
  else if (this->isa == Paws__NUMERIC)
    pretty_print_numeric(this->pointer.numeric);
  else if (this->isa == Paws__STRING)
    pretty_print_string(this->pointer.string);
}


int main(void) {
  Paws__list root_list = Paws.List.create(),
           first_child = Paws.List.create(),
              subchild = Paws.List.create(),
          second_child = Paws.List.create();
  
  Paws__numeric forty_two = Paws.Numeric.create(42),
                    three = Paws.Numeric.create(3);
  
  Paws__string elliott = Paws.String.create("Elliott",  8),
              franklin = Paws.String.create("Franklin", 9),
                 cable = Paws.String.create("Cable",    6);
  
  
  Paws.List.affix(subchild, Paws.String.to_thing(elliott));
  Paws.List.affix(subchild, Paws.String.to_thing(franklin));
  Paws.List.affix(first_child, Paws.List.to_thing(subchild));
  Paws.List.affix(first_child, Paws.String.to_thing(cable));
  
  Paws.List.affix(second_child, Paws.Numeric.to_thing(forty_two));
  Paws.List.affix(second_child, Paws.Numeric.to_thing(three));
  
  Paws.List.affix(root_list, Paws.List.to_thing(first_child));
  Paws.List.affix(root_list, Paws.List.to_thing(second_child));
  
  pretty_print_list(root_list);
  printf("\n");
  
  return(0);
}
