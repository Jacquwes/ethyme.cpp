# ethyme.cpp

A C++20 wrapper for Discord's API. Uses websocketpp and cpr.

Example available at [example.cpp](/example.cpp)

## How to use a bot

If your bot has a command "test" with arguments "bot" and "desc", it should be used this way:

`!test --bot false --desc this i a string.`

The order of the arguments doesn't matter.

Message update is treated as message create.

## Documentation

https://jacquesatan.github.io/ethyme.cpp

## Installation

### Deps

Use Vcpkg to install dependencies:

`vcpkg install websocketpp nlohmann-json cpr openssl boost-random cppcoro` ([More docs](https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md))

### Build

Doesn't work on Linux. You shouldn't use Linux in 2021 anyways.

```bash
git clone git@github.com:JacqueSatan/ethyme.cpp.git
# If you want to generate a Visual Studio Solution:
mkdir build
cd build
cmake .. -G "Visual Studio 16"
```
