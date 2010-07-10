Paws.c
======
It’s Paws, in ISO/IEC 9899:1999. That’s C99, for people too lazy to google it.

### Roadmap & Status
#### Paws.c — v1, “I can interpret an AST!”
- Threading implementation: partial, and `routine` interpreter under heavy development
- Default (native) implementation of lookups
- Expression interpreter
- Cross-platformization: Only known to compile on OS X; almost definitely will not work on Windows

#### Paws.c — v2, “I can execute a document!”
- cPaws parser

#### Paws.c — v3, “Hello, world!”
- Interpretation‐unit acquisition, ‘packaging’
- Intra–interpretation‐unit communication, `list` sharing

Building
--------
Can’t really be arsed learning `make` right now, not to mention it seems like a bit of a clusterfuck of a tool,
so… these:

    # This is just a shortcut. You can use `gcc` instead of `clang` here; it takes the same arguments.
    C() { eval local last="\$$#"; last=${last##*/}; clang -o "${last%.*}.o" "$@" }
    
    # The command-line interface’s binary, `Paws.c` itself
    clang -O0 -std=c99 -pedantic-errors -Wall -ISource \
      Source/Paws.c/Ancillary/Threading/Threading.c \
      Source/Paws.c/Ancillary/Threading/Pool/Pool.c \
      Source/Paws.c/Ancillary/Threading/Thread/Thread.c \
      Source/Paws.c/Ancillary/Magazine/Magazine.c \
      Source/Paws.c/Ancillary/Unit/Unit.c \
      Source/Paws.c/Types/list/ll.c \
      Source/Paws.c/Types/list/list.c \
      Source/Paws.c/Types/routine/ast.c \
      Source/Paws.c/Types/routine/routine.c \
      Source/Paws.c/Types/execution/execution.c \
      Source/Paws.c/Types/numeric/numeric.c \
      Source/Paws.c/Types/string/string.c \
      Source/Paws.c/Paws.c \
    Source/Paws.c/Tools/Paws.c.c -o Paws.o && ./Paws.o
    
    
    # The ‘cests’ (tests) for Paws
    C -O0 -std=c99 -pedantic-errors -Wall -ISource Source/Cest.c \
      Source/Paws.c/Ancillary/Threading/Threading.c \
      Source/Paws.c/Ancillary/Threading/Pool/Pool.tests.c \
      Source/Paws.c/Ancillary/Threading/Thread/Thread.tests.c \
      Source/Paws.c/Ancillary/Magazine/Magazine.tests.c \
      Source/Paws.c/Ancillary/Unit/Unit.tests.c \
      Source/Paws.c/Types/list/ll.tests.c \
      Source/Paws.c/Types/list/list.tests.c \
      Source/Paws.c/Types/routine/ast.tests.c \
      Source/Paws.c/Types/routine/routine.tests.c \
      Source/Paws.c/Types/execution/execution.tests.c \
      Source/Paws.c/Types/numeric/numeric.tests.c \
      Source/Paws.c/Types/string/string.tests.c \
      Source/Paws.c/Paws.tests.c && \
    ./Paws.tests.o
    
    # Run `gdb` against the tests for Paws (use `run`)
    C -O0 -std=c99 -pedantic-errors -Wall -ggdb -ISource Source/Cest.c \
      Source/Paws.c/Ancillary/Threading/Threading.c \
      Source/Paws.c/Ancillary/Threading/Pool/Pool.tests.c \
      Source/Paws.c/Ancillary/Threading/Thread/Thread.tests.c \
      Source/Paws.c/Ancillary/Magazine/Magazine.tests.c \
      Source/Paws.c/Ancillary/Unit/Unit.tests.c \
      Source/Paws.c/Types/list/ll.tests.c \
      Source/Paws.c/Types/list/list.tests.c \
      Source/Paws.c/Types/routine/ast.tests.c \
      Source/Paws.c/Types/routine/routine.tests.c \
      Source/Paws.c/Types/execution/execution.tests.c \
      Source/Paws.c/Types/numeric/numeric.tests.c \
      Source/Paws.c/Types/string/string.tests.c \
      Source/Paws.c/Paws.tests.c && \
    gdb -q -se ./Paws.tests.o
    # use `run`

Conventions
-----------
Several coding conventions used in this project:

### Commit labels
Some commits are ‘labeled’ by space-separated words in parenthesis at the start of the commit message. You can
filter the commit list by these words. Some of the more common ones:

- `minor`: A commit with little or no consequence, for instance typo fixes, tiny source-code spacing changes, and
  so forth. Filtering these out will provide you with a much cleaner commit list, with no real loss of useful
  information.
- `api`: A commit that *changes* the public API of the naming in a major way (i.e. changing the name of a public
  method or function, or re-arranging functions in some way); filtering against these will provide you a fairly
  comprehensive list of changes which will probably affect you during an upgrade.
- `new`: Adds new features, methods, or functions; *adds* to the API instead modifying anything that already
  exists.
- `fix`: Fixes a bug or mistake of some sort. Does not indicate mutation of the API, unless `api` is included as
  well.
- `refactor`: Rather than specifically fixing a known bug, or adding new features, this modifies the existing
  codebase to be cleaner, safer, or more understandable in some way.
- `tests`: Only affects the tests, does not change any implementation.
- `incomplete`: Most commits to this project are required to be ‘stand-alone’; that is, the project should at
  least compile, if not pass all tests, at any commit you decide to `git checkout`. Filtering out this label will
  provide with a list of commits that should be *somewhat* safe to compile against.
- `doc`: Only affects the documentation, does not change any implementation or the test suite.
