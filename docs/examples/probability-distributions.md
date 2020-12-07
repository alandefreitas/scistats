---
layout: default
title: Probability Distributions
nav_order: 2
has_children: false
parent: Examples
has_toc: false
---
# Probability Distributions

To get the probability of `x` in a normal distribution:

```cpp
norm_pdf(x);
```

To get the cumulative probability of `x` in a normal distribution:

```cpp
norm_cdf(x);
```

To get the value `x` that has a cumulative probability `p` in a normal distribution:

```cpp
norm_inv(p);
```

| Probability  | Cumulative |  Inverse    | Description     |
|--------------|-----------------|--------------|-----------------|
| `norm_pdf(x)`   | `norm_cdf(x)`   | `norm_inv(p)`   | Normal distribution  |
| `t_pdf(x,df)`   | `t_cdf(x,df)`   | `t_inv(p,df)`   | Student's T distribution  |

where `df` is the degrees of freedom in the probability distribution.




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
