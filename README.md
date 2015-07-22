# Reentrant lex/bison parser

This is an example reentrant lex/bison parser creating an abstract syntax tree.
Most of the problems while building this were related to the weird
documentation of lex and bison (all that legacy stuff ...).

This is working in a sense that it might well be suitable as a blueprint for
starting such endeavours. Please send me a note if you find a major problem
with this.

_Disclaimer_: I haven't done a lot of C/C++ in the last recent years, so this
most probably has lots of non idiomatic stuff in it.


## What to use this for?

This could be used as syntax tree for integration with an LLVM backend, for
example. I didn't follow this path as learning everything necessary about LLVM
is not something I currently want to do.


## Why not use C++?

I tried, but C++ support in lex/bison is pretty rough. I failed to properly use
the variants stuff they integrated. I looked into boost/spirit when having
trouble with this but compilation times of more than 10 seconds for a minimal
example is nothing I want to handle any more.

And C++ anyway. I remember so many pitfalls from back in the day when I used
this language, that I fear every single step leading to disaster.


## Running it

The provided Makefile relies on llvm, flex and bison being installed. The
following will compile and run the code:

	make
	./run

There is an additional target for running this through valgrind (use `make
mem`) which helps to find memory leaks.

Please note this requires bison version 3.0.2 at least (this introduced the
union stuff). But there is a bug (fixed in version 3.0.3) that will create
duplicate type entries in the parser's header file. Let the compiler guide you
in which entries to delete. This is a dirty workaround, but sufficient.


## Resources

There are many resources to be taken into account:

* http://www.gnu.org/software/bison/manual
* http://epaperpress.com/lexandyacc/index.html
* http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/


## Todo

Mostly missing is location tracking (which line/column did an error occur?).
This should be easily possible using other examples on the net.


## License

Copyright (c) 2015, Gereon Frey

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


