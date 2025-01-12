## Getting Started

This guide will help you get up and running with the project.

## Prerequisites

Before you begin, ensure that you have the following installed on your system:

- **Git**
- **CMake 3.0+**
- **Clang/GCC**

Supported OS:
- **Linux**

## Quick Start

Follow these steps to build `mld-neural-network` project and run `mld_mnist`:

*Build `mld_mnist` application:*
```shell
cmake -S. -Bbuild -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
```

*To run tests use the following commands:*
```shell
cmake -S. -Bbuild -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug -j
cmake --build build --config Debug --target test
```


