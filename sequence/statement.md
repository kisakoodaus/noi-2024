Consider a game with $n$ players and $n$ chairs. The chairs will be arranged in a circle, and each player will sit on a chair. There is also a bell which will ring some number of times during the game.

Each chair has an integer between $1$ and $n$: the number of steps the player who sits on that chair must move clockwise when the bell rings. A chair arrangement is valid if each chair will have exactly one player after the bell rings.

Your task is to find a valid chair arrangement or state that there are no such arrangement.

# Input

The first line has an integer $t$: the number of tests.

After this, each test consists of two lines. The first line has an integer $n$. The second line has integers $s_1,s_2,\dots,s_n$: the numbers in the chairs.

# Output

For each test, first print `YES` if there is a valid chair arrangement and `NO` otherwise. If the answer is `YES`, also print a possible arrangement clockwise. If there are several valid arrangements, you can print any of them.

# Constraints

- $1 \le t \le 1000$
- $1 \le n \le 100$
- $1 \le s_i \le n$ for $i=1,2,\dots,n$

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

- $s_i \neq s_j$ if $i \neq j$ (i.e. each value is distinct)

# Subtask 3 ([score=3] points)

- $1 \le s_i \le 2$ for $i=1,2,\dots,n$

# Subtask 4 ([score=4] points)

- $1 \le s_i \le 3$ for $i=1,2,\dots,n$

# Subtask 5 ([score=5] points)

- $1 \le s_i \le 4$ for $i=1,2,\dots,n$

# Subtask 6 ([score=6] points)

- $1 \le s_i \le 5$ for $i=1,2,\dots,n$

# Subtask 7 ([score=7] points)

- $1 \le n \le 16$

# Subtask 8 ([score=8] points)

- No restrictions.
