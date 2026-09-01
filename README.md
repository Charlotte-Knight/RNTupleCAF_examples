# RNTupleCAF_examples

This is a repository of examples of analysing CAFs which are in RNTuple-form. If you have TTree-based CAFs, you can use the [CAFtoRNTuple](https://github.com/Charlotte-Knight/CAFtoRNTuple) converter to produce RNTuple-based ones.

I have categorised the examples into three parts:
- python
- cpp
- root macros

> [!NOTE]
> A lot of this code is applicable to analysing the TTree-based CAFs. What differs most is how you open and grab the StandardRecords from the ROOT file. The biggest difference with RNTuple is the Python support, which no longer requires pySRProxy and is much faster.

In the Python approach, we use `uproot` together with `awkward` to analyse the CAFs. This approach is fast (comparable to C++) and can be very interactive, which is ideal for exploratory work. There is a [Jupyter notebook](python/awkward.ipynb) which takes you through for some examples. 

The "cpp" approaches correspond to C++ frameworks, where there are multiple scripts and a cmake project to bring it all together. There are two directories:
- `cpp_standalone/` contains the most examples (analogous to those in the Jupyter notebook) and is a minimal approach to get things going
- `cpp_duneanasel` shows how you might extend `cpp_standalone` to bring in external libraries like [duneanasel](https://github.com/DUNE/duneanasel) 

Finally, there is the approach using root macros, again mirroring the examples from the Jupyter notebook. The advantage of this approach is that you do not have to rebuild your scripts, and you can play around with a CAF interactively in the command line. However, you do have to load the StandardRecord library that you must find or build yourself.

Feedback is very welcome! Please raise issues if you think any of the examples can be improved or more can be added.

## Environment

One should only need a relatively up-to-date version of gcc, cmake, and ROOT to run these examples. They are designed so that you do not already need an environment with `duneanaobj` installed.

In the Python-case, all you need is to open the notebook, and in the first step it installs all the required packages via pip.