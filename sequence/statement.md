The Competitive Programming Society of Iceland found themselves managing far too many tasks as both their national contest and
NOI approached rapidly. 
With everything at risk of coming crashing down, they resort to desperate measures.
One of them has the idea that juggling tasks is surely analogous to physical juggling, the kind with balls.
Willing to try anything at this point, the members start to investigate.

In order to start practicing they look for juggling patterns to perform. 
A pattern can be described by how far each ball is thrown, measured by how many catches later it lands.
We consider the pattern as repeating, so the pattern $3$ is in effect $3, 3, 3, \dots$.
For example, the pattern $1$ simply means that a single ball is thrown and caught repeatedly.
The pattern $2, 4$ means that the first ball is thrown, then the second. 
At the third step the first ball is caught and thrown again, before a third ball is thrown, and these three are then juggled.

Bjarki had found a truly incredible pattern, one so impressive that it had managed to help him become better at juggling tasks too!
But when he wanted to show this pattern to the rest of the society, he managed to drop all the numbers on the floor.
After picking them up, they were all out of order. Can you help him put the numbers he has into an order that will make a juggling pattern?

Bjarki has investigated these patterns thoroughly and has some info to give you to help you along.
One can prove that a sequence of $n$ numbers are a valid juggling pattern if and only if the balls all land at different times modulo $n$.
That is to say $s_1, s_2, \dots, s_n$ is valid if and only if $s_1 + 1, s_2 + 2, \dots, s_n + n$ are all different modulo $n$.

Beware that Bjarki may have lost a number or two when dropping them, so there might be no way to put them into a valid order!

# Input

The first line has a positive integer $t$, the number of test cases.
Then follow $t$ test cases, each consisting of two lines.
The first line contains a positive integer $n$, giving the number of numbers Bjarki picked up after dropping them.
On the second line the numbers $s_1, s_2, \dots, s_n$ Bjarki picked up are given, separated by spaces.

# Output

For each test, first print `YES` if there is a valid initial order and `NO` otherwise. 
If the answer is `YES`, print the numbers in an order that constitute a juggling pattern. 
If there are several valid orders, you can print any one of them.

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

- $1 \le n \le 16$

# Subtask 3 ([score=3] points)

- $s_i \neq s_j$ if $i \neq j$ (i.e. each value is distinct)

# Subtask 4 ([score=4] points)

- $1 \le s_i \le 5$ for $i=1,2,\dots,n$

# Subtask 5 ([score=5] points)

- No restrictions.
