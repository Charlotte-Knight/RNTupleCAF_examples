# ROOT macros

Using ROOT macros can be slightly quicker/easier than the [cpp_standalone](../cpp_standalone/) approach which requires writing a `CMakeLists.txt`. Furthermore, you can open a CAF interactively which can be great for understanding the structure of the CAFs.

To run the macro, we need to add the StandardRecord library from `duneanaobj` to our path. This may be called `libStandardRecord.so` or similar. If you have `duneanaobj` installed somewhere, find out where this library lives (often under a directory called `lib` or `lib64`), and then do:
```
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/path/to/lib_directory
```
Or if you are unsure, follow the instructions in [cpp_standalone](../cpp_standalone/) which will build `duneanaobj` for you, and then you can use (substituting `path/to/RNTupleCAF_examples`)
```
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/path/to/RNTupleCAF_examples/cpp_standalone/build/lib64
```

To run the ROOT macro example, edit [selection.C](selection.C#L37) to change the path to the CAF file, and then do
```
root selection.C
```

## Interactive ROOT

To open a CAF file interactively, we can follow some of the steps in [selection.C](selection.C). First run
```
root 
```
and then (substituting `<path/to/rntuple.root>`)
```
auto reader = ROOT::RNTupleReader::Open("caf", "<path/to/rntuple.root>")
auto srView = reader->GetView<caf::StandardRecord>("rec")
const auto sr = srView(0)
```

This gives you `sr` which is the first StandardRecord in the rntuple, i.e. the first spill. Then you can, for example, look at the x coordinate for the neutrino vertex in the first interaction with
```
sr.common.ixn.dlp[0].vtx.x
```
