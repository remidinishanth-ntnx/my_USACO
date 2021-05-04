## Counting Rectangles

There is an n × m rectangular grid, each cell of the grid contains a single integer: zero or one. Let's call the cell on the i-th row and the j-th column as (i, j).

Let's define a "rectangle" as four integers a, b, c, d (1 ≤ a ≤ c ≤ n; 1 ≤ b ≤ d ≤ m). Rectangle denotes a set of cells of the grid {(x, y) :  a ≤ x ≤ c, b ≤ y ≤ d}. Let's define a "good rectangle" as a rectangle that includes only the cells with zeros.

You should answer the following q queries: calculate the number of good rectangles all of which cells are in the given rectangle.

**Input**:

There are three integers in the first line: n, m and q (1 ≤ n, m ≤ 40, 1 ≤ q ≤ 3·10^5). Each of the next n lines contains m characters — the grid. Consider grid rows are numbered from top to bottom, and grid columns are numbered from left to right. Both columns and rows are numbered starting from 1.

Each of the next q lines contains a query — four integers that describe the current rectangle, a, b, c, d (1 ≤ a ≤ c ≤ n; 1 ≤ b ≤ d ≤ m).

**Output**:

For each query output an answer — a single integer in a separate line.

Example:

Input
```
5 5 5
00101
00000
00001
01000
00001
1 2 2 4
4 5 4 5
1 2 5 2
2 2 4 5
4 2 5 3
```

Output
```
10
1
7
34
5
```

![image](https://user-images.githubusercontent.com/19663316/117042997-4acb4800-ad2a-11eb-9d89-1694a24d6af6.png)

* For the first query, there are 10 good rectangles, five 1 × 1, two 2 × 1, two 1 × 2, and one 1 × 3.
* For the second query, there is only one 1 × 1 good rectangle.
* For the third query, there are 7 good rectangles, four 1 × 1, two 2 × 1, and one 3 × 1.

Solution
```cpp
int cnt[44][44][44][44];
int a[44][44], f[44][44];
 
int main() {
  int n, m, q;
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      char ch = getchar();
      while (ch != '0' && ch != '1') ch = getchar();
      a[i][j] = (ch == '1');
    }
  
  // Compute 2D prefix sums
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      if (i == 0 || j == 0) f[i][j] = 0;
      else f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + a[i][j];
  
  // Check whether Rectange with diagonal (x1,y1) and (x2,y2) contains all 0's
  for (int xa = 1; xa <= n; xa++)
    for (int ya = 1; ya <= m; ya++)
      for (int xb = xa; xb <= n; xb++)
        for (int yb = ya; yb <= m; yb++) {
          int sum = f[xb][yb] - f[xa - 1][yb] - f[xb][ya - 1] + f[xa - 1][ya - 1];
          cnt[xa][ya][xb][yb] = (sum == 0);
        }
  
  // Add subRectangles with sides as (xb, ya) and (xb, yb) to rectangle with diagonal (xa-1,ya) and (xb,yb) and so on
  for (int xa = n; xa >= 2; xa--) // Compute backwards
    for (int ya = 1; ya <= m; ya++)
      for (int xb = xa; xb <= n; xb++)
        for (int yb = ya; yb <= m; yb++) cnt[xa - 1][ya][xb][yb] += cnt[xa][ya][xb][yb];
  
  for (int xa = 1; xa <= n; xa++)
    for (int ya = m; ya >= 2; ya--)
      for (int xb = xa; xb <= n; xb++)
        for (int yb = ya; yb <= m; yb++) cnt[xa][ya - 1][xb][yb] += cnt[xa][ya][xb][yb];
  
  for (int xa = 1; xa <= n; xa++)
    for (int ya = 1; ya <= m; ya++)
      for (int xb = xa; xb <= n; xb++)
        for (int yb = ya; yb <= m; yb++) cnt[xa][ya][xb + 1][yb] += cnt[xa][ya][xb][yb];
  
  for (int xa = 1; xa <= n; xa++)
    for (int ya = 1; ya <= m; ya++)
      for (int xb = xa; xb <= n; xb++)
        for (int yb = ya; yb <= m; yb++) cnt[xa][ya][xb][yb + 1] += cnt[xa][ya][xb][yb];
  
  while (q--) {
    int xa, ya, xb, yb;
    scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
    printf("%d\n", cnt[xa][ya][xb][yb]);
  }
  return 0;
}
```