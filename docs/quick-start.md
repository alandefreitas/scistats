---
layout: default
title: Quick Start
nav_order: 2
has_children: false
has_toc: false
---
# Quick Start

Scistats extends the numeric facilities of the standard library to include statistics that work with iterators and ranges. This means you can do things like:

```cpp
std::vector<int> v{/*...*/};
float m = scistats::mean(v);
```

or 

```cpp
std::vector<int> v{/*...*/};
float s = scistats::stddev(v); // 
```

or

```cpp
std::vector<int> v1{/*...*/};
std::vector<int> v2{/*...*/};
float c = scistats::cov(v); // covariance
```

or 

```cpp
std::vector<int> v{/*...*/};
float p = scistats::t_test(v); // student's t hypothesis test
```
 
All algorithms allow execution policies and iterators. So you can do

```cpp
std::vector<int> v{/*...*/};
float m = scistats::mean(scistats::execution::par, v);
```

to calculate your average in parallel. Or 

```cpp
std::vector<int> v{/*...*/};
float m = scistats::mean(scistats::execution::seq, v);
```

to explicitly tell scistats you don't want that to be calculated in parallel. If no execution policy is provided, scistats will choose a policy according to the input size.

As usual, you can also work directly with iterators, so

```cpp
std::vector<int> v{/*...*/};
float m = scistats::mean(v.begin(), v.end();
```

also works.

Note that, when needed, the result type gets promoted to `float`. If the result for a given statistic needs to be floating point, scistats will always promote an integer input type to a corresponding floating type large enough to keep the results without losing precision.




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
