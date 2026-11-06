// k-th term of linear recurrence (Kitamasa): a_n = sum_{i=1..k} c[i-1]*a_{n-i}.
// O(k^2 log n). Pair with Berlekamp-Massey (gives c from first terms).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
ll kth(const vector<ll> &c, const vector<ll> &a, ll n) {
	int k = c.size();
	if (n < k) return a[n] % MOD;
	auto mul = [&](const vector<ll> &x, const vector<ll> &y) {
		vector<ll> r(2 * k - 1, 0);
		for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) r[i + j] = (r[i + j] + x[i] * y[j]) % MOD;
		for (int i = 2 * k - 2; i >= k; i--)
			for (int j = 1; j <= k; j++) r[i - j] = (r[i - j] + r[i] * c[j - 1]) % MOD;
		r.resize(k);
		return r;
	};
	vector<ll> res(k, 0), b(k, 0);
	res[0] = 1;
	if (k == 1) b[0] = c[0] % MOD; else b[1] = 1;
	for (; n; n >>= 1, b = mul(b, b)) if (n & 1) res = mul(res, b);
	ll ans = 0;
	for (int i = 0; i < k; i++) ans = (ans + res[i] * a[i]) % MOD;
	return ans;
}
