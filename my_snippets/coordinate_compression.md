Coordinate compression is a procedure that takes some points and reassigns their coordinates to remove "gaps". 
For example, if point P1 is located at x = 5, point P2 is located at x = 27, and point P3 is located at x = 65, 
then, after coordinate compression, P1 may be located at x = 0, P2 may be located at x = 1, and P3 may be located at x = 2. 

The reason we compress coordinates is to get rid of all the "empty space" between points. 
This makes it easier to, say, use the coordinates as indices into an array. If we used the original numbers, we'd waste a lot of entries.

Performing coordinate compression is easy. You just make a list of all the coordinates and sort them in ascending order. 
This gives you the rank of each coordinate. You then replace each coordinate by its rank. This takes `O(N log N)` time, so it's pretty efficient.

A simple problem that can be solved using coordinate compression is the problem of finding the volume of the union of N axis-aligned(every box is aligned 
with the same `x`, `y` and `z` axis) boxes in three dimensions `(1 <= N <= 100)`. The coordinates can be arbitrary real numbers between `0` and `10^9`.

The shape of this union can be complicated, but observe that if we compress the coordinates, then all coordinates will lie between `0` and `199`, 
since each box has two coordinates along each dimension. In the compressed coordinate system, the unit cube `[x, x+1] × [y, y+1] × [z, z+1]` will either 
be completely full or completely empty, since each box's coordinates are integers. 

So the idea is to compute a `200 x 200 x 200` array, in which each entry is `1` if the corresponding unit cube is full, or `0` of it's empty. 
To actually compute this array in linear time can be done by first forming the difference array and then integrating. After that, 
iterate through each filled cube, and map it back to the original coordinates, and add its volume to the total volume. The overall running time is `O(N^3)`.

(Follow-up problem: find the surface area.)

Quora: Brian Bi https://qr.ae/pGs3Mn


If we need to compress an array A, than we can do that in three steps:

```cpp
int A[N];
// ...blah-blah-blah, A is filled with some big numbers
map<int, int> M;

for (int i = 0; i < n; i++) 
    M[A[i]]; // 1. Creating a key A[i] in M
 
int pt = 0;
for (map<int, int>::iterator it = M.begin(); it != M.end(); it++) 
    it->second = pt++; // 2. Assigning unique value for each key keeping order in set of values

for (int i = 0; i < n; i++)
    A[i] = M[A[i]]; // 3. Compressing source array
```

That's good way because if we need to put points in some special cases, like they are ends of some segments, 
we can just call something like `M[A[i] — 1]`, `M[A[i]]`, `M[A[i] + 1]` instead of thinking what we should put as `A[i]`, what as `A[i] + 1` etc...

source: https://codeforces.com/blog/entry/3976?#comment-80407

### TODO: https://qr.ae/pGs3Wi