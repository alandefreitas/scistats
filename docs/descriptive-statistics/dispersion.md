---
layout: default
title: Dispersion
nav_order: 2
has_children: false
parent: Descriptive statistics
has_toc: false
---
# Dispersion

To calculate the standard deviation of a data set:

```cpp
stddev(x);
```

If you already know the mean `m`, you can make calculations faster with:

```cpp
stddev(x,m);
```

Other functions to measure dispersion are:

| Function          | Description                 |
| ----------------- | --------------------------- |
| `var(x)`          | Variance                    |
| `stddev(x)`       | Standard Deviation          |
| `min(x)`          | Minimum Value               |
| `max(x)`          | Maximum Value               |
| `bounds(x)`       | Minimum and Maximum Values  |
| `percentile(x,p)` | Calculate `p`-th percentile |




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
