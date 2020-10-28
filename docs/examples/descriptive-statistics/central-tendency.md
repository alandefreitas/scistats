---
layout: default
title: Central tendency
nav_order: 1
has_children: false
parent: Descriptive statistics
grand_parent: Examples
has_toc: false
---
# Central tendency

With ranges:

```cpp
mean(x); 
```

With iterators:

```cpp
mean(x.begin(), x.end()); 
```

You can any algorithm in parallel by changing the execution policy:

```cpp
mean(execution::seq, x);
mean(execution::par, x);
```

If no execution policy is provided, scistats will infer the best execution policy according to the input data.




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
