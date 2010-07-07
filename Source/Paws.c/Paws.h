/* This file is deprecated, and is simply left in for lazy people. Instead of using this file, you should use the
   following includes:
   
       #define DECLARATIONS
       # include "Paws.c/Paws.c"
       #undef  DECLARATIONS */

#if !defined(DECLARATIONS)
# define PAWS_H__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.c"
#if defined(PAWS_H__BEHEST)
# undef DECLARATIONS
#endif
