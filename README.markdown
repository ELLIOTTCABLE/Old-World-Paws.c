Paws.o
======
It’s Paws, in ISO/IEC 9899:1999. That’s C99, for people too lazy to google it.

### Status
- Only known to compile on OS X; almost definitely will not work on Windows
- cPaws Parser not written, cannot run source files
- Threading implementation partial, and routine interpreter under heavy
  development

Using
-----
Can’t really be arsed learning `make` right now, not to mention it seems like
a bit of a clusterfuck of a tool, so… these:

    # This is just a shortcut. You can use `gcc` instead of `clang` here; it
    # takes the same command-line arguments. (Mind you, I’m not sure if Paws
    # compiles under `gcc` right now…)
    C() { eval local last="\$$#"; last=${last##*/}; clang -o "${last%.*}.o" "$@" }
    
    # to compile `Paws.o`
    C -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/Paws.o/Paws.c \
      Source/Paws.o/Ancillary/Threading/Threading.c \
      Source/Paws.o/Ancillary/Threading/pool/pool.c \
      Source/Paws.o/Ancillary/Threading/thread/thread.c \
      Source/Paws.o/Types/list/ll.c \
      Source/Paws.o/Types/list/list.c \
      Source/Paws.o/Types/routine/ast.c \
      Source/Paws.o/Types/routine/routine.c \
      Source/Paws.o/Types/numeric/numeric.c \
      Source/Paws.o/Types/string/string.c \
      Source/Paws.o/Paws.o.c && \
    ./Paws.o
    
    
    # to compile `pop`
    C -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/pop/pop.c && \
    ./pop.o something.paws
    
    # Run `gdb` against `pop` (use `run something.paws`)
    C -O0 -std=c99 -pedantic-errors -Wall -ggdb -ISource \
      Source/pop/pop.c && \
    gdb -q -se ./pop.o
    # use `run something.paws`
    
    
    # The ‘cests’ (tests) for Paws
    C -O0 -std=c99 -pedantic-errors -Wall -ISource Source/Cest.c \
      Source/Paws.o/Ancillary/Threading/Threading.c \
      Source/Paws.o/Ancillary/Threading/pool/pool.tests.c \
      Source/Paws.o/Ancillary/Threading/thread/thread.tests.c \
      Source/Paws.o/Types/list/ll.tests.c \
      Source/Paws.o/Types/list/list.tests.c \
      Source/Paws.o/Types/routine/ast.tests.c \
      Source/Paws.o/Types/routine/routine.tests.c \
      Source/Paws.o/Types/numeric/numeric.tests.c \
      Source/Paws.o/Types/string/string.tests.c \
      Source/Paws.o/Paws.tests.c && \
    ./Paws.tests.o
    
    # Run `gdb` against the tests for Paws (use `run`)
    C -O0 -std=c99 -pedantic-errors -Wall -ggdb -ISource Source/Cest.c \
      Source/Paws.o/Ancillary/Threading/Threading.c \
      Source/Paws.o/Ancillary/Threading/pool/pool.tests.c \
      Source/Paws.o/Ancillary/Threading/thread/thread.tests.c \
      Source/Paws.o/Types/list/ll.tests.c \
      Source/Paws.o/Types/list/list.tests.c \
      Source/Paws.o/Types/routine/ast.tests.c \
      Source/Paws.o/Types/routine/routine.tests.c \
      Source/Paws.o/Types/numeric/numeric.tests.c \
      Source/Paws.o/Types/string/string.tests.c \
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
