There is a rooted tree that has $n$ nodes, numbered $1,2,\dots,n$.

You are given the results of $m$ lca queries, and your task is to reconstruct the tree (or any tree that matches the results).

# Input

The first line has two integers $n$ and $m$: the number of nodes and the number of lca results.

After this, there are $m$ lines that describe the results. Each line has three integers $a$, $b$ and $c$: the lca of $a$ and $b$ is $c$.

# Output

First print `YES` if you can construct a tree and `NO` otherwise. If the answer is `YES`, also print $n$ integers that describe one possible tree: for each node, the parent node or $0$ if the node is the root.

# Constraints

- $1 \le n \le 100$

# Example

Input:

```
5 3
3 5 1
3 2 4
5 2 4
```

Output:

```
YES
4 4 1 0 1
```

# Subtask 1 ([score=1] points)

- $1 \le n \le 8$

# Subtask 2 ([score=2] points)

- Each node has at most one child.

# Subtask 3 ([score=3] points)

- $1 \le n \le 500$

# Subtask 4 ([score=4] points)

- $1 \le n \le 2 \cdot 10^5$

TODO: find out if the problem can be solved
