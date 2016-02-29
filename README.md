# Hi all,

This is just my collected work on Kernighan and Pike's excellent _Practice of
Programming_, which I was first introduced to in my "Advanced Programming
Techniques" class in the spring of 2014 at Drexel University.

# Building

kp-pop is provided with a CMake buildsystem, and I recommend an out of source
build, so, assuming you already have CMake installed (>=3.0.0), then simply:

    $ mkdir build
    $ cd build
    $ cmake ..

To generate Makefiles, then build the project and run all the exercises do:

    $ make
    $ make test

If you're fancy like me, and want to use Ninja instead of Make, simply supply
the `-G Ninja` argument when calling CMake and replace the `make` commands
with `ninja`.

# Contact

Questions, comments, suggestions, corrections, or bugfixes are always
welcome! Simply open an issue or pull request or email me.

_-Nicholas_
