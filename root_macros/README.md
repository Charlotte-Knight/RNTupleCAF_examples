# ROOT macros

Using ROOT macros can be slightly quicker/easier than the [cpp_standalone](../cpp_standalone/) approach which requires writing a `CMakeLists.txt`. Furthermore, you can open a CAF interactively which can be great for understanding the structure of the CAFs.

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

> [!NOTE]  
> In [selection.C](selection.C), we define several helper functions like `inFV` and `isSelected` which needed to have templated types because without loading the StandardRecord library, ROOT does not know what a caf::SRInteraction (or similar) is.

## Macros with libraries

I do not see why you would want to do this, but you may want to load the StandardRecord library in your macro. In [selection_with_lib.C](selection_with_lib.C), the library in loaded by this [line](selection_with_lib.C#L5). If you already have an installation of [duneanaobj](https://github.com/DUNE/duneanaobj) then all one needs to do is add the library to `LD_LIBRARY_PATH` like
```
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/path/to/lib_directory
```
This is often found inside a directory like `lib` or `lib64` but not always. If in doubt, follow the instructions in [cpp_standalone](../cpp_standalone/) which will build `duneanaobj` for you, and then you can use (substituting `path/to/RNTupleCAF_examples`)
```
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/path/to/RNTupleCAF_examples/cpp_standalone/build/lib64
```

> [!TIP]
> At this point, you are getting quite close to the [cpp_standalone](../cpp_standalone/) approach and you may just find it easier to go down that route.



