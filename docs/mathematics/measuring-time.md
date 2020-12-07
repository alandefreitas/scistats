---
layout: default
title: Measuring Time
nav_order: 4
has_children: false
parent: Mathematics
has_toc: false
---
# Measuring Time

To measure the time between two operations:

```cpp
double t1 = tic();
// your operations
double t2 = toc();
```

To measure the time it takes to run a function:

```cpp
double t = timeit([](){
    // Your function...
});
```

To create a mini-benchmark measuring the time it takes to run a function:

```cpp
std::vector<double> t = minibench([](){
    // Your function...
});
std::cout << "Mean: " << mean(t) << std::endl;
std::cout << "Standard Deviation: " << stddev(t) << std::endl;
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
