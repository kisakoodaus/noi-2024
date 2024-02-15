Consider an integer sequence of length $n$ whose elements are $s_1,s_2,\dots,s_n$. Such a sequence is called a valid juggling sequence if you can juggle infinitely long following the sequence.

At each step, you must first either introduce a new ball or catch exactly one existing ball, then throw that ball and finally catch the ball $s_i$ steps later. You can introduce as many balls as needed during the process.

For example, the sequence $[2,4,1,1,2]$ is a valid juggling sequence, because you can do as follows:

* Step $1$: Introduce ball $1$ and throw it (catch it $2$ steps later)
* Step $2$: Introduce ball $2$ and throw it (catch it $4$ steps later)
* Step $3$: Catch ball $1$ and throw it (catch it $1$ steps later)
* Step $4$: Catch ball $1$ and throw it (catch it $1$ steps later)
* Step $5$: Catch ball $1$ and throw it (catch it $2$ steps later)
* Step $6$: Catch ball $2$ and throw it (catch it $2$ steps later)
* Step $7$: Catch ball $1$ and throw it (catch it $4$ steps later)
* Step $8$: Catch ball $2$ and throw it (catch it $1$ steps later)
* Step $9$: Catch ball $2$ and throw it (catch it $1$ steps later)
* Step $10$: Catch ball $2$ and throw it (catch it $2$ steps later)
* Step $11$: Catch ball $1$ and throw it (catch it $2$ steps later)
* Step $12$: Catch ball $2$ and throw it (catch it $4$ steps later)
* ...

Given an integer sequence, your task is to permute it so that it becomes a valid juggling sequence or state that this is not possible.

# Input

The first line has an integer $t$: the number of tests.

After this, each test consists of two lines. The first line has an integer $n$ and the second line has $n$ integers $s_1,s_2,\dots,s_n$.

# Output

For each test, first print `YES` or `NO`. If the answer is `YES`, also print a valid juggling sequence.

# Constraints

- $1 \le t \le 100$
- $1 \le n \le 100$
- $1 \le s_i \le n$

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
