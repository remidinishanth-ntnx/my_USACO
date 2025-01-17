* First, **reread the problem statement**. Did you miss something important? Are you sure you have understood what the problem is asking for? Double-check your understanding on the sample input and output.
* Whenever you see, there is atleast `⌈N/2⌉` or `⌈N/3⌉` elements in the answer, see if you can use randomization. Say we need to have atleast `⌈N/2⌉` elements in the answer, if we choose a person at random, there is half probability that element is in the answer. So if we repeat this process say 30 times, then the probability of failure reduces to `(1/2)^30`. Hence this works most of the time.
  * Problem: https://codeforces.com/contest/1523/problem/D , Solution: https://codeforces.com/contest/1523/submission/117881477
  ![image](https://user-images.githubusercontent.com/19663316/120113940-6f380a00-c19a-11eb-8a77-b3c4c761a32d.png)
* If you see “rollbacks” in the problem statement - this is 99.9% a reference to persistence problem.
* If you can solve the problem for a chain using a segment tree, then there is a very good chance that you can solve the problem for a tree using HLD. Indeed, if you make segment trees over the heavy edges, then the answer for your path X-Y can be broken up into two paths from X to LCA(X, Y) and from Y to LCA(X, Y). Then, using that you make only logN shifts from one heavy-chain to another, you are actually making only log(N) segment-tree queries.
* All trees are bipartite, If we color them black and white, The min(number of black, number of white) nodes is ≤ ⌈n/2⌉. source: https://codeforces.com/contest/1534/problem/D

```cpp
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
```
