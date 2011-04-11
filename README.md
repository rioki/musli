musli
=====

About
-----

musli is a serialisation library that aims to be simple to use and put as little
burden on the client code as possible. Despite it's simplicity the design of
musli tries to serialize as many data setups as feasible. In addition to 
simplicity musli is designed to produce a compact binary format that is optimal
for quick loading and transport over a network.

Building
--------

Currently only a CodeLite workspace and projects exist, that are configured 
for windows. The code should build on basically any setup. It is planed to
add configure and make support (via the GNU autotools).

Documentation
-------------

A quick introduction can be found in INTRODUCTION.md. Additional documentation 
can be found at http://github.com/rioki/musli/wiki.

Copying
-------

See COPYING.txt for details.

Hacking
-------

Development is coordinated at http://github.com/rioki/musli. There you 
will find a wiki, issue tracker and the "master" git repository. Contributions
are preferably submitted though git pull request.  

Things to do:

* Endianness conversion.
* Specific Ids for Factorlets

