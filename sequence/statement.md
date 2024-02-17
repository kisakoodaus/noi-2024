An integer sequence $s_0,s_1,\dots,s_{n-1}$ is called a _move sequence_ if each value $(i+s_i) \bmod n$ is distinct for $i=0,1,\dots,n-1$.

For example, the sequence $[2,4,1,1,2]$ is a move sequence:
 
* $(0+2) \bmod 5 = 2$
* $(1+4) \bmod 5 = 0$
* $(2+1) \bmod 5 = 3$
* $(3+1) \bmod 5 = 4$
* $(4+2) \bmod 5 = 1$

Given $n$ integers, your task is to construct a move sequence using them or state that this is not possible.

# Input

The first line has an integer $t$: the number of tests.

After this, each test consists of two lines. The first line has an integer $n$ and the second line has $n$ integers.

# Output

For each test, first print `YES` if you can construct a move sequence and `NO` otherwise. If the answer is `YES`, also print a move sequence. If there are several solutions, you can print any of them.

# Constraints

- $1 \le t \le 200$
- $1 \le n \le 100$
- Each number is between $1$ and $n$

# Example

Input:

```
3
4
1 1 1 1
4
1 1 1 2
5
4 1 2 1 2
```

Output:

```
YES
1 1 1 1
NO
YES
2 4 1 1 2
```

# Subtask 1 ([score=1] points)

- $1 \le n \le 10$

# Subtask 2 ([score=2] points)

- $1 \le n \le 20$

# Subtask 3 ([score=3] points)

- Each number is distinct.

# Subtask 4 ([score=4] points)

- Each number is between $1$ and $5$.

# Subtask 5 ([score=5] points)

- No restrictions.
