---
layout: default
title: Other build systems
nav_order: 3
has_children: false
parent: Integration
has_toc: false
---
# Other build systems

If you want to use it in another build system you can either install the library (Section [*Binary Packages*](#binary-packages) or Section [Installing Scistats from Source](build-from-source/installing-scistats-from-source.md) or you have to somehow rewrite the build script.

If you want to rewrite the build script, your project needs to 1) include the headers, and 2) link with the dependencies described in [`source/CMakeLists.txt`](https://github.com/alandefreitas/scistats/blob/master/source/CMakeLists.txt).




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
