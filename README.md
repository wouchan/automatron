# Automatron

Tool for working with formal languages and state machines.

![](https://raw.githubusercontent.com/wouchan/automatron/master/assets/screenshot.png)

## TODO List

- [x] Generating formal languages with user-entered alphabets and grammars.

- [x] Generating state machines diagrams.

- [x] Utilities for debugging state machines.

- [ ] Tools for converting non-deterministic automatons into deterministic versions.

- [ ] Expand documentation.

## Compiling

Building with CMake is simple. You can configure the project using:

```
cmake -S . -B build
```

CMake will download all needed dependencies.

Then you can build with:

```
cmake --build build
```
