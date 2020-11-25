# ethyme.cpp

A C++17 wrapper for Discord's API. Uses websocketpp and cpr.

Example available at [example.cpp](/example.cpp)

## Installation

### Deps

Use Vcpkg to install dependencies:

`vcpkg install websocketpp nlohmann-json cpr openssl boost-random` ([More docs](https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md))

### Build

I didn't test it on Linux. You may have to modify
```
find_library(BOOST_RANDOM_LIBRARY boost_random-vc140-mt.lib)
```
for it to work.

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
# on windows you can use -G "Visual Studio 16"
```