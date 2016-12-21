# Reentrant lex/bison parser

This is an example reentrant flex/bison parser creating an abstract syntax tree
and working with readline.  It is difficult to find full examples
of the trifecta: reentrant/flex/bison/readline all together.
Most of the problems while building this were related to the weird
documentation of lex and bison (all that legacy stuff ...).

This is working blueprint for using these tools in modern compiler
projects. Please send me a note if you find a major problem
with this.

## What to use this for?

The parser could be used to give your program an interpreter
(or multiple different interpreters).  It accepts input
from strings, files, or interactively with libedit (editline
re-imagination of readline interface).


## Why not use C++?

C++ has its own set of parsers, including boost/spirit
and better antlr support.  Even fstream makes parsing
relatively easy in C++.  This example is for people who
do things the hard way (but are wise enough to start
from a minimum working example).


## Running it

The provided Makefile relies on flex, bison, and libedit being installed.
The following will compile and run the interactive interpreter:

	make
	./run

There is an additional target for running this through valgrind (use `make
mem`) which helps to find memory leaks.
Any arguments will be treated as filenames to parse without interaction.

Please note this requires bison version 3.0.2 at least (this introduced the
union stuff). But there is a bug (fixed in version 3.0.3) that will create
duplicate type entries in the parser's header file. Let the compiler guide you
in which entries to delete. This is a dirty workaround, but sufficient.


## Resources

There are many resources to be taken into account:

* http://www.gnu.org/software/bison/manual
* http://epaperpress.com/lexandyacc/index.html
* http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
* http://www.phpcompiler.org/articles/reentrantparser.html

## Todo

Mostly missing is location tracking (which line/column did an error occur?).
This should be easily possible using other examples on the net.


## License

Copyright (c) 2015, Gereon Frey
Copyright (c) 2016, David M. Rogers

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


