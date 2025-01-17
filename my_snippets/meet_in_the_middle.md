### 4sum (popular interview question)

Given A, an array of integers, find out if there are any four numbers in the array that sum up to zero (the same element can be used multiple times). 

For example given `A = [2, 3, 1, 0, -4, -1]` a solution is `3 + 1 + 0 - 4 = 0` or `0 + 0 + 0 + 0` = 0.

#### Solution

The naive algorithm checks all four number combinations. This solution takes `O(n^4)`.

A slightly improved algorithm brute forces through all `n^3` three number combinations and efficiently checks if `-(a + b + c)` is in the original array using a hash table. This algorithm is `O(n^3)`.

If `a + b + c + d = 0`, then `a + b = -(c + d)` this is what meet in the middle does. Now we store n^2 sums `a + b` in a hash set S. Then iterate through all `n^2` combinations for `c` and `d` and check if S contains `-(c + d)`.

```cpp
def 4sum(A):
  sums = {}
  for a in A:
    for b in A:
      sums[a + b] = (a, b)
 
  for c in A:
    for d in A:
      if -(c + d) in sums:
        print(sums[-(c + d)][0], sums[-(c + d)][1], c, d)
        return
 
  print("No solution.")
```

source: https://www.infoarena.ro/blog/meet-in-the-middle


### Card Groups (CS Academy)
source: https://csacademy.com/contest/round-60/task/card-groups/statement/

You are given N cards, each of them has one side painted red and the other one blue, and each side has a number written on it.

You should divide the cards in two groups: for the first group you compute the sum of the numbers written on the red sides, for the second group the sum of the numbers written on the blue sides. The goal is to divide the cards in such a way that the two sums are equal. Every card should be part of a group.

If the solution is not unique, you want to minimize the absolute difference between the number of cards in the groups.

**Input**:

The first line contains a single integer N. Each of the next N lines contains two integers, representing the numbers written on the red and on the blue faces of a card.

**Output:**

If there is no solution such that the two sums are equal, output -1. Otherwise, print N binary values, each corresponding to a card: 0 if the card is in the red group, 1 if it's in the blue group.

**Constraints and notes**
* `1 ≤ N ≤ 40`
* The numbers on the cards are integers between 0 and 10^9 
* If there are more solutions with equal sum and minimum absolute difference of group sizes, you can output any of them.

Examples:

Input
```
3
1 2
1 1
1 1
```
Output
```
100
```

#### Solution

If `N ≤ 20`, we could've brute forced.

Since `N ≤ 40` We can solve the problem with meet in the middle. We will split the cards in two groups, the first ⌊N/2⌋ and the last ⌈N/2⌉.

*	let b0 be the sum of blue cards in the first group
*	let b1 be the sum of blue cards in the second group
*	let r0 be the sum of red cards in the first group
* let r1 be the sum of red cards int he seond group

We want to have
`b0 + b1 = r0 + r1` ⟹ `b0 - r0 = r1 - b1`

We've re-written the condition from the statement so that the two groups are independent. For each group we will insert all possible subset sums in an associative array, in O(N * 2^{N/2}) time. Some additional care must be taken to satisfy the minimum absolute difference constraint.

```cpp
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <array>
using namespace std;

void BuildTable(const vector<pair<int, int>>& els, vector<pair<int64_t, int>>& table, 
                const function<int64_t(int64_t, int64_t)>& f) {
    int n = (int)els.size();
    table.resize(1 << n);
    for (int mask = 0; mask < (1 << n); mask += 1) {
        int64_t sum_blue = 0, sum_red = 0; 
        for (int iter = 0; iter < n; iter += 1) {
            if ((mask >> iter) & 1) {
                sum_blue += els[iter].second;
            } else {
                sum_red += els[iter].first;
            }
        }

        table[mask] = make_pair(f(sum_red, sum_blue), mask);
    }
    sort(table.begin(), table.end());
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    int n; cin >> n;
    vector<pair<int, int>> cards(n);
    for (auto& card : cards) {
        cin >> card.first >> card.second;
    }

    array<vector<pair<int64_t, int>>, 2> table;
    BuildTable(vector<pair<int, int>>(cards.begin(), cards.begin() + n / 2), table[0], [](const int64_t r, const int64_t b) { return b - r; });
    BuildTable(vector<pair<int, int>>(cards.begin() + n / 2, cards.end()), table[1], [](const int64_t r, const int64_t b) { return r - b; });

    vector<int> have((n + 3) / 2);
    int answer = n + 1; uint64_t answer_mask;
    for (int i = 0, j = 0; i < (int)table[0].size(); ) {
        while (j < (int)table[1].size() and table[1][j].first < table[0][i].first) {
            j += 1;
        }
        if (j == (int)table[1].size() or table[1][j].first > table[0][i].first) {
            i += 1;
            continue;
        }
        
        fill(have.begin(), have.end(), -1);
        while (j < (int)table[1].size() and table[1][j].first == table[0][i].first) {
            have[__builtin_popcount(table[1][j].second)] = table[1][j].second;
            j += 1;
        }

        int nxt = i;
        while (nxt < (int)table[0].size() and table[0][nxt].first == table[0][i].first) {
            int num_blues = __builtin_popcount(table[0][nxt].second);
            for (int oth_blues = 0; oth_blues < (int)have.size(); oth_blues += 1) {
                if (have[oth_blues] != -1 and abs(n - 2 * num_blues - 2 * oth_blues) < answer) {
                    answer = abs(n - 2 * num_blues - 2 * oth_blues);
                    answer_mask = ((uint64_t)(have[oth_blues]) << (n / 2)) | table[0][nxt].second;
                }
            }

            nxt += 1;
        }
        i = nxt;
    }
    
    if (answer == n + 1) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < n; i += 1) {
            cout.put('0' + ((answer_mask >> i) & 1));
        }
        cout << '\n';
    }

    return 0;
}
```
