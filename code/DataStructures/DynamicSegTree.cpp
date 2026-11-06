// Dynamic (sparse) segment tree over [0, N): point add, range sum. O(log N) per op, nodes created lazily.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e9;
struct Node { ll s = 0; int l = 0, r = 0; }; // 0 = null
vector<Node> t(1); // t[0] is the null node
int newNode() { t.emplace_back(); return t.size() - 1; }
void upd(int &v, ll lo, ll hi, ll p, ll x) {
	if (!v) v = newNode();
	t[v].s += x;
	if (hi - lo == 1) return;
	ll m = (lo + hi) / 2;
	if (p < m) { int c = t[v].l; upd(c, lo, m, p, x); t[v].l = c; }
	else { int c = t[v].r; upd(c, m, hi, p, x); t[v].r = c; }
}
ll qry(int v, ll lo, ll hi, ll l, ll r) { // sum over [l, r)
	if (!v || r <= lo || hi <= l) return 0;
	if (l <= lo && hi <= r) return t[v].s;
	ll m = (lo + hi) / 2;
	return qry(t[v].l, lo, m, l, r) + qry(t[v].r, m, hi, l, r);
}
// usage: int root = 0; upd(root, 0, N, p, x); qry(root, 0, N, l, r);
