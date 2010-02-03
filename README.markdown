Paws.o
======
It’s Paws, in ANSI (…usually) C89.

Using
-----
Can’t really be arsed learning `make` right now, not to mention it seems like
a bit of a clusterfuck of a tool, so… these:

    C() { eval local last="\$$#"; last=${last##*/}; clang -o "${last%.*}.o" "$@" }
    
    # `something.c`, an old random example
    C -std=c89 -O0 -Wall -pedantic-errors -ISource \
      Source/Paws.o/Core/ll.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/numeric/numeric.c \
      Source/something.c && ./something.o
    
    # The cests (‘tests’) for `ll`
    C -std=c89 -O0 -Wall -pedantic-errors -ISource Source/Cest.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/Core/ll.tests.c && ./ll.tests.o
