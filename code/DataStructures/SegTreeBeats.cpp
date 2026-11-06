// Segment tree beats: range chmin(l,r,x), range sum, range max. O(log n) amortized (O(log^2) with add).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 2;
struct Beats {
	int n; vector<ll> sum, mx, se; vector<int> cnt;
	Beats(const vector<ll> &a) : n(a.size()), sum(4 * n), mx(4 * n), se(4 * n), cnt(4 * n) { build(1, 0, n - 1, a); }
	void pull(int o) {
		int l = 2 * o, r = 2 * o + 1;
		sum[o] = sum[l] + sum[r];
		if (mx[l] > mx[r]) mx[o] = mx[l], cnt[o] = cnt[l], se[o] = max(se[l], mx[r]);
		else if (mx[l] < mx[r]) mx[o] = mx[r], cnt[o] = cnt[r], se[o] = max(mx[l], se[r]);
		else mx[o] = mx[l], cnt[o] = cnt[l] + cnt[r], se[o] = max(se[l], se[r]);
	}
	void build(int o, int l, int r, const vector<ll> &a) {
		if (l == r) { sum[o] = mx[o] = a[l]; se[o] = NEG; cnt[o] = 1; return; }
		int m = (l + r) / 2;
		build(2 * o, l, m, a); build(2 * o + 1, m + 1, r, a); pull(o);
	}
	void apply(int o, ll x) { if (x < mx[o]) sum[o] -= (mx[o] - x) * cnt[o], mx[o] = x; }
	void push(int o) { apply(2 * o, mx[o]); apply(2 * o + 1, mx[o]); }
	void chmin(int o, int l, int r, int ql, int qr, ll x) {
		if (qr < l || r < ql || x >= mx[o]) return;
		if (ql <= l && r <= qr && se[o] < x) { apply(o, x); return; }
		push(o); int m = (l + r) / 2;
		chmin(2 * o, l, m, ql, qr, x); chmin(2 * o + 1, m + 1, r, ql, qr, x); pull(o);
	}
	ll qsum(int o, int l, int r, int ql, int qr) {
		if (qr < l || r < ql) return 0;
		if (ql <= l && r <= qr) return sum[o];
		push(o); int m = (l + r) / 2;
		return qsum(2 * o, l, m, ql, qr) + qsum(2 * o + 1, m + 1, r, ql, qr);
	}
	ll qmax(int o, int l, int r, int ql, int qr) {
		if (qr < l || r < ql) return NEG;
		if (ql <= l && r <= qr) return mx[o];
		push(o); int m = (l + r) / 2;
		return max(qmax(2 * o, l, m, ql, qr), qmax(2 * o + 1, m + 1, r, ql, qr));
	}
	void chmin(int l, int r, ll x) { chmin(1, 0, n - 1, l, r, x); }
	ll sumQ(int l, int r) { return qsum(1, 0, n - 1, l, r); }
	ll maxQ(int l, int r) { return qmax(1, 0, n - 1, l, r); }
};
