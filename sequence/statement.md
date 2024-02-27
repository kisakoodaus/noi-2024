Consider a game with $n$ players, numbered $1,2,\dots,n$. Each player $i$ has an integer $s_i$ between $1$ and $n$.

There are $n$ chairs arranged in a circle. Initially, each player sits on a chair. Then, a bell rings and each player $i$ moves $s_i$ steps clockwise.

Your task is to find an initial order for the players such that each chair has exactly one player after they move.

# Input

The first line has an integer $t$: the number of tests.

After this, each test consists of two lines. The first line has an integer $n$ and the second line has integers $s_1,s_2,\dots,s_n$.

# Output

For each test, first print `YES` if there is a valid initial order and `NO` otherwise. If the answer is `YES`, also print a possible order. If there are several orders, you can print any of them.

# Constraints

- $1 \le t \le 1000$
- $1 \le n \le 100$
- $1 \le x_i \le n$ for $i=1,2,\dots,n$

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

- $1 \le n \le 8$

# Subtask 2 ([score=2] points)

- $1 \le n \le 16$

# Subtask 3 ([score=3] points)

- $x_i \neq x_j$ if $i \neq j$ (i.e. each value is distinct)

# Subtask 4 ([score=4] points)

- $1 \le x_i \le 5$ for $i=1,2,\dots,n$

# Subtask 5 ([score=5] points)

- No restrictions.
