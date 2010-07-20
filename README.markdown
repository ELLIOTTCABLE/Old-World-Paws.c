`Paws.c`
========
A (currently) naïve, slow, and *completely* unoptimized reference implementation of the
[Paws programming language][Paws] (including Paws’ <del>pre-compilation system¹ and</del> concurrency runtime),
in ISO C ’99.

  [Paws]: <http://Paws.elliottcable.name/> (The Paws Programming Language)

### Status
- **Does not, yet, actually interpret documents!** This codebase is not yet prepared for user-consumption.
- `numeric` ignored; will probably shim directly with math-stack-less native implementation of basic arithmetic
  in the short-term
- *Real* interpretation Units are completely ignored at the moment; we only implement enough for a single Unit to
  handle things within itself (such as the `label` magazine)

- **Many previously–partially-implemented things have had to be ripped out for the rewrite )-:**

- The doubly-linked-list backing every datatype is completely and robustly implemented
- The opaque AST type behind our `routine`s is also complete
- `fork`s are almost entirely implemented; probably need a few more tweaks and some new native `routine`s, but…
- `label` datatype, and the ‘uniques-store’ magazine, for the most part, are fully implemented
- Implementation infrastructure: testing framework, internal typing, and preprocessor magic, all completed

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
In addition to those specifically listed below; if contributing, please try to maintain the general feel and
style exhibited throughout the codebase. Pay attention to your indentation, whitespace, bracket and semicolon
placement and omission… and keep the code clean and beautiful. It’s appreciated.

Oh, and don’t use hard tabs. Ever.

### Externalization
Much of the `Paws.c` codebase utilizes an ‘externalization’ system to ease safe incorporation of the tools we
provide into others’ codebases. It revolves around the `E()` macro (defined and documented in `Core.h`). We
ensure all C tags, labels, variables, and function names… really, anything defined in any sort of “global
namespace” and intended for exposure to the outside world… is wrapped in this `E()` macro.

When you include any part of the `Paws.c` codebase into your own project, such names will be provided prefixed
with the tag `Paws__` (such as `Paws__thing` or `Paws__routine`). (If you wish to use the same un-prefixed names
that are utilized *within* the `Paws.c` codebase, you can `#define INTERNALIZE` prior to including the code you
plan to utilize.)

### Namespacing `struct`s
We make extensive use of `struct`s as namespacing tools. Since ISO C provides nearly no tools for namespacing, we
improvise to avoid horrible prefixed labels for every piece of data or function.

These are publicized under the external `Paws` global variable; and are often stored in sub-structs such as
`Paws->Routine`. Most C functions exposed by the `Paws.c` API are available via these structs; for example,
`Paws->Routine->allocate()`.

### Commit labels
Most commits are ‘labeled’ by space-separated words in parenthesis at the start of the commit message. You can
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

---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
  1. (Pre-compilation is not yet implemented)
