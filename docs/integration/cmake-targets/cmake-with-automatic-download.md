---
layout: default
title: CMake with Automatic Download
nav_order: 3
has_children: false
parent: CMake targets
grand_parent: Integration
has_toc: false
---
# CMake with Automatic Download

Check if you have [Cmake](http://cmake.org) 3.14+ installed:

```bash
cmake -version
```

Install [CPM.cmake](https://github.com/TheLartians/CPM.cmake) and then:

```cmake
CPMAddPackage(
    NAME scistats
    GITHUB_REPOSITORY alandefreitas/scistats
    GIT_TAG origin/master # or whatever tag you want
)
# ...
target_link_libraries(my_target PUBLIC scistats)
```

You can now add the [scistats headers](#examples) to your source files.

However, it's always recommended to look for Scistats with `find_package` before including it as a subdirectory. You can use:

```
option(CPM_USE_LOCAL_PACKAGES "Try `find_package` before downloading dependencies" ON)
```

to let CPM.cmake do that for you. Otherwise, we can get [ODR errors](https://en.wikipedia.org/wiki/One_Definition_Rule) in larger projects.




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
