# C++ framework with duneanasel

This extends [cpp_standalone](../cpp_standalone/) by including [duneanasel](https://github.com/DUNE/duneanasel) in the cmake project, and using a selection from `duneanasel` in [selection_duneanasel.cpp](selection_duneanasel.cpp).

First let's build
```
mkdir build && cd build
cmake .. && make install
```
and then from within the build directory (substituting the path to the rntuple)
```
./selection_duneanasel <path/to/rntuple.root>
```