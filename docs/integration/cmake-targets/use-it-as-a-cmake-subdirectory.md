---
layout: default
title: Use it as a CMake subdirectory
nav_order: 2
has_children: false
parent: CMake targets
grand_parent: Integration
has_toc: false
---
# Use it as a CMake subdirectory

You can use Scistats directly in CMake projects without installing it. Check if you have [Cmake](http://cmake.org) 3.14+ installed:

```bash
cmake -version
```

Clone the whole project
 
```bash
git clone https://github.com/alandefreitas/scistats/
```

and add the subdirectory to your CMake project:

```cmake
add_subdirectory(scistats)
```

When creating your executable, link the library to the targets you want:

```
add_executable(my_target main.cpp)
target_link_libraries(my_target PUBLIC scistats)
```

You can now add the [scistats headers](#examples) to your source files.

However, it's always recommended to look for Scistats with `find_package` before including it as a subdirectory. Otherwise, we can get [ODR errors](https://en.wikipedia.org/wiki/One_Definition_Rule) in larger projects. 




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
