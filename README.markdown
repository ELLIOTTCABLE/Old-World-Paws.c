Paws.o
======
It’s Paws, in ISO/IEC 9899:1999. That’s C99, for people too lazy to google it.

Using
-----
Can’t really be arsed learning `make` right now, not to mention it seems like
a bit of a clusterfuck of a tool, so… these:

    # to compile `Paws.o`
    clang -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/Paws.o/Paws.c \
      Source/Paws.o/Core/ll.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/routine/routine.c \
      Source/Paws.o/numeric/numeric.c \
      Source/Paws.o/string/string.c \
      Source/Paws.o/Paws.o.c \
      -o Paws.o && \
    ./Paws.o
    
    
    C() { eval local last="\$$#"; last=${last##*/}; clang -o "${last%.*}.o" "$@" }
    
    # to compile `pop`
    C -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/pop/pop.c && \
    ./pop.o something.paws
    
    # Run `gdb` against `pop` (use `run something.paws`)
    C -O0 -std=c99 -pedantic-errors -Wall -ggdb -ISource \
      Source/pop/pop.c && \
    gdb -q -se ./pop.o
    # use `run something.paws`
    
    # `something.c`, an old random example
    C -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/Paws.o/Paws.c \
      Source/Paws.o/Core/ll.c \
      Source/Paws.o/list/list.c \
      Source/Paws.o/routine/routine.c \
      Source/Paws.o/numeric/numeric.c \
      Source/Paws.o/string/string.c \
      Source/something.c && \
    ./something.o
    
    
    # The ‘cests’ (tests) for Paws
    C -O0 -std=c99 -pedantic-errors -Wall -ISource Source/Cest.c \
      Source/Paws.o/Core/ll.tests.c \
      Source/Paws.o/list/list.tests.c \
      Source/Paws.o/routine/routine.tests.c \
      Source/Paws.o/numeric/numeric.tests.c \
      Source/Paws.o/string/string.tests.c \
      Source/Paws.o/Paws.tests.c && \
    ./Paws.tests.o
    
    # Run `gdb` against the tests for Paws (use `run`)
    C -O0 -std=c99 -pedantic-errors -Wall -ggdb -ISource Source/Cest.c \
      Source/Paws.o/Core/ll.tests.c \
      Source/Paws.o/list/list.tests.c \
      Source/Paws.o/routine/routine.tests.c \
      Source/Paws.o/numeric/numeric.tests.c \
      Source/Paws.o/string/string.tests.c \
      Source/Paws.o/Paws.tests.c && \
    gdb -q -se ./Paws.tests.o
    # use `run`

Conventions
-----------
Several coding conventions used in this project:

### Commit labels
Some commits are ‘labeled’ by space-seperated words in parenthesis at the
start of the commit message. You can filter the commit list by these words.
Some of the more common ones:

- `minor`: A commit with little or no consequence, for instance typo fixes,
  tiny source-code spacing changes, and so forth. Filtering these out will
  provide you with a much cleaner commit list, with no real loss of useful
  information.
- `api`: A commit that *changes* the public API of the naming in a major way
  (i.e. changing the name of a public method or function, or re-arranging
  functions in some way); filtering against these will provide you a fairly
  comprehensive list of changes which will probably affect you during an
  upgrade.
- `new`: Adds new features, methods, or functions; *adds* to the API instead
  modifying anything that already exists.
- `tests`: Only affects the tests, does not change any implementation.
- `incomplete`: Most commits to this project are required to be ‘stand-alone’;
  that is, the project should at least compile, if not pass all tests, at any
  commit you decide to `git checkout`. Filtering out this label will provide
  with a list of commits that should be *somewhat* safe to compile against.
- `doc`: Only affects the documentation, does not change any implementation or
  the test suite.
