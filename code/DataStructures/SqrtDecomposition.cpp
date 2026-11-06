// Sqrt decomposition template: point/range add, range sum and range max. O(sqrt n) per op.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Sqrt {
	int n, B; vector<ll> a, sum, add, mx;
	Sqrt(const vector<ll> &v) : n(v.size()), B(max(1, (int)sqrt(n))), a(v), sum((n + B - 1) / B), add(sum.size()), mx(sum.size(), LLONG_MIN) {
		for (int i = 0; i < n; i++) sum[i / B] += a[i], mx[i / B] = max(mx[i / B], a[i]);
	}
	void rebuild(int b) { // push lazy and recompute block
		mx[b] = LLONG_MIN;
		for (int i = b * B; i < min(n, (b + 1) * B); i++) a[i] += add[b], mx[b] = max(mx[b], a[i]);
		add[b] = 0;
	}
	void update(int l, int r, ll x) { // a[l..r] += x
		for (int b = l / B; b <= r / B; b++) {
			int lo = b * B, hi = min(n, lo + B) - 1;
			if (l <= lo && hi <= r) { add[b] += x; sum[b] += x * (hi - lo + 1); mx[b] += x; continue; }
			for (int i = max(l, lo); i <= min(r, hi); i++) a[i] += x, sum[b] += x;
			rebuild(b);
			// rebuild applied old lazy, so mx/sum stay consistent
		}
	}
	ll query(int l, int r) { // sum a[l..r]
		ll res = 0;
		for (int b = l / B; b <= r / B; b++) {
			int lo = b * B, hi = min(n, lo + B) - 1;
			if (l <= lo && hi <= r) { res += sum[b]; continue; }
			for (int i = max(l, lo); i <= min(r, hi); i++) res += a[i] + add[b];
		}
		return res;
	}
	ll qmax(int l, int r) {
		ll res = LLONG_MIN;
		for (int b = l / B; b <= r / B; b++) {
			int lo = b * B, hi = min(n, lo + B) - 1;
			if (l <= lo && hi <= r) { res = max(res, mx[b]); continue; }
			for (int i = max(l, lo); i <= min(r, hi); i++) res = max(res, a[i] + add[b]);
		}
		return res;
	}
};
