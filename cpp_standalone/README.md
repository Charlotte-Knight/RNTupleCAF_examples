# Standalone C++ framework

This is for those who like to code in C++, but dislike ROOT macros/want to extend their project beyond that. There is a `CMakeLists.txt` that pulls in `duneanaobj` including fetching and building it if it does not already exist, and then a bunch of scripts that run various examples. 

To run, first build the project
```
mkdir build && cd build
cmake .. && make install
```
and then from within the build directory (substituting the path to the rntuple)
```
export RNTUPLE_PATH=<path/to/rntuple.root>
./track_lengths $RNTUPLE_PATH
./neutrino_vertices $RNTUPLE_PATH
./selection $RNTUPLE_PATH
```

This will produce `track_lengths.root` and `neutrino_vertcies.root` which contain histograms of track lengths and neutrino vertices. And in the command line, there will be a print out which shows the efficiency of the selection implemented in [selection.cpp](selection.cpp).