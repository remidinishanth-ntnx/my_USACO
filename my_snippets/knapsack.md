You are given 𝑁 ≤ 1000 items, each with some weight 𝑤𝑖. Is there a subset of items with total weight exactly 𝑊 ≤ 10<sup>6</sup>?

Standard knapsack with boolean array would be 𝑂(𝑁⋅𝑊), too slow.

```cpp
bool can[MAX_W];
int main() {
	int n, W;
	cin >> n >> W;
	can[0] = true;
	for(int id = 0; id < n; id++) {
		int x;
		cin >> x;
		for(int i = W; i >= x; i--) { // Reverse order is key
			if(can[i-x]) can[i] = true;
		}
	}
	puts(can[W] ? "YES" : "NO");
}
```
