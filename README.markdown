Paws.o
======
It’s Paws, in ISO/IEC 9899:1999. That’s C99, for people too lazy to google it.

Using
-----
Can’t really be arsed learning `make` right now, not to mention it seems like
a bit of a clusterfuck of a tool, so… these:

    C() { eval local last="\$$#"; last=${last##*/}; clang -o "${last%.*}.o" "$@" }
    
    # `something.c`, an old random example
    C -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/Paws.o/Paws.c \
      Source/Paws.o/Core/ll.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/numeric/numeric.c \
      Source/something.c && \
    ./something.o
    
    # The cests (‘tests’) for `ll`
    C -O0 -std=c99 -pedantic-errors -Wall -ISource Source/Cest.c \
      Source/Paws.o/Paws.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/Core/ll.tests.c && \
    ./ll.tests.o
    
    # Run `gdb` against the tests for `ll`
    C -O0 -std=c99 -pedantic-errors -Wall -ggdb -ISource Source/Cest.c \
      Source/Paws.o/Paws.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/Core/ll.tests.c && \
    gdb -q -se ./ll.tests.o
