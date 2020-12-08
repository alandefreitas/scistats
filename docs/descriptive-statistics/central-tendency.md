---
layout: default
title: Central Tendency
nav_order: 1
has_children: false
parent: Descriptive statistics
has_toc: false
---
# Central Tendency

With ranges:

```cpp
using namespace scistats;
// ...
mean(x); 
```

With iterators:

```cpp
mean(x.begin(), x.end()); 
```

You can run any algorithm in parallel by changing the execution policy:

```cpp
mean(execution::seq, x);
mean(execution::par, x);
```

If no execution policy is provided, scistats will infer the best execution policy according to the input data.

Other functions to measure central tendency are:

| Function    | Description     |
| ----------- | --------------- |
| `mean(x)`   | Arithmetic mean |
| `median(x)` | Median          |
| `mode(x)`   | Mode            |




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
