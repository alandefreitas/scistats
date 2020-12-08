---
layout: default
title: Bayesian statistics
nav_order: 6
has_children: false
has_toc: false
---
# Bayesian statistics

Given (i) the probability `P(E|H)=likelihood` of the evidence `E` given the hypothesis `H`, (ii) the prior probability `p_hypothesis` of hypothesis `H`, and (iii) the prior probability `p_evidence` of evidence `E`, we can calculate the probability `P(H|E)` of a hypothesis `H` given the evidence `E` with:  

```cpp
bayes_theorem(likelihood, p_hypothesis, p_evidence)
```

Given `P(E|H)` and `P(E|not H)`, we can calculate the bayes factor:

```cpp
bayes_factor(p_evidence_given_h, p_evidence_given_not_h)
``` 




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
