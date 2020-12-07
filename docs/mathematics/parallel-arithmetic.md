---
layout: default
title: Parallel Arithmetic
nav_order: 1
has_children: false
parent: Mathematics
has_toc: false
---
# Parallel Arithmetic

To sum the elements of a range in parallel:

```cpp
sum(execution::parallel_policy, x)
```

Or let `scistats` infer if it is worth doing it in parallel:

```cpp
sum(x)
```

|   Function        |   Description     | 
|-------------------|-------------------|
| `sum`              | summation        |
| `prof`         | product     |





<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
