/* Yes, this file is named `Paws.c.c`. This is because it compiles to a binary named `Paws.c`.
   
   Yes, this file compiles to a binary named `Paws.c`. This is because that is the name of the project, and thus
   also the name of the primary command-line interface to the project’s tools.
   
   There are no include guards in this file, because it is not intended to ever be included. If you’re trying to
   include this, you’re probably Doing Something Wrong™. */

#define INTERNALIZE
#define DECLARATIONS
# include "Paws.c/Paws.c"

# include <stdlib.h>
# include <stdio.h>
#undef  DECLARATIONS


/* This currently seems fairly meaningless, as it only apes the keys defined in `stdlib.h`; however, understand
   that I intend to expand it with more possible (meaningful) error codes in the future. */
enum exit_status { FAILURE_STATUS = EXIT_FAILURE, SUCCESS_STATUS = EXIT_SUCCESS };

                 int //»
/*enum exit_status*/ main(void) {
  
  /* For the moment, we’re going to hardcode some stuff in here to execute some code, just for development /
     debugging purposes. First off, we need a hardcoded AST to work on: (this is equivalent to a Paws document
     with only `foo bar\n` inside it) */
  node _lobby = Node->scope();
  Node->affix(_lobby, Node->expression());
  Node->affix(Node->at(_lobby, 0), Node->word("foo"));
  Node->affix(Node->at(_lobby, 0), Node->word("bar"));
  
  unit this = Unit->allocate();
  
  execution lobby = Execution->allocate(Routine->allocate(_lobby));
  
  return SUCCESS_STATUS;
}
