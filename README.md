# min cost solver

This is an implementation of a dynamic programming algorithm for the
following problem: Given a set of `m` numbers, find the minimum subset
sum under the following constraint: in any set of `w` consecutive
numbers, at least one number must be in the subset.

# Input

the input must contain two lines: In the first there are two
space-separated numbers `m` and `w`. In the second, there should be
`m` integer numbers representing costs.

Here is an example for `m = 20`, `w = 5`, and 20 example numbers.

```
20 5
1 129 22 158 120 28 6 199 581 12 129 12 42 433 38 15 20 6 199 8
```

# Compilation

Compile the program by running
```
make
```

# Example

```
./min-cost-solver <example_input.txt
```

The output will print the input numbers with asterisks to the left of
the numbers in the optimal subset, along with the minimum cost
solution. Here is an example for the input `example_input.txt`
```
  1
  129
* 22
  158
  120
  28
* 6
  199
  581
  12
  129
* 12
  42
  433
  38
* 15
  20
  6
  199
  8
FINAL COST: 55
```
