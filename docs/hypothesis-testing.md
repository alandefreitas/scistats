---
layout: default
title: Hypothesis Testing
nav_order: 4
has_children: false
has_toc: false
---
# Hypothesis Testing

To test the hypothesis that the values in `x` come from a distribution with `mean(x)` is zero:

```cpp
t_test(x);
```

To test the hypothesis that the values in `x` and `y` have the same mean:

```cpp
t_test(x,y);
```

For a paired test:

```cpp
t_test_paired(x,y);
```

To get a confidence interval for these tests:

```cpp
t_test_interval(x);
t_test_interval(x,y);
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
