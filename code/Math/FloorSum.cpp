// floor_sum(n, m, a, b) = sum_{i=0}^{n-1} floor((a*i + b) / m), O(log m). Needs a,b >= 0, result fits ull.
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull floorSum(ull n, ull m, ull a, ull b) {
	ull ans = 0;
	for (;;) {
		if (a >= m) ans += n * (n - 1) / 2 * (a / m), a %= m;
		if (b >= m) ans += n * (b / m), b %= m;
		ull y = a * n + b;
		if (y < m) break;
		n = y / m; b = y % m;
		swap(m, a);
	}
	return ans;
}
