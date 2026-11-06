// Persistent implicit treap (sequence): split/merge copy O(log n) nodes. Balance by sizes (no priorities).
// root[v] = version v. Ops: insert, erase, concatenation of versions, kth. Memory O(log n) per op.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 4000000;
struct Node { int l, r, sz; ll val; } t[MX]; int tot;
mt19937 rng(712367);
int newNode(ll v) { t[++tot] = {0, 0, 1, v}; return tot; }
int cp(int o) { t[++tot] = t[o]; return tot; }
int sz(int o) { return o ? t[o].sz : 0; }
void upd(int o) { t[o].sz = sz(t[o].l) + sz(t[o].r) + 1; }
int merge(int a, int b) {
	if (!a || !b) return a ? a : b;
	if ((int)(rng() % (sz(a) + sz(b))) < sz(a)) { int o = cp(a); t[o].r = merge(t[o].r, b); upd(o); return o; }
	int o = cp(b); t[o].l = merge(a, t[o].l); upd(o); return o;
}
void split(int o, int k, int &a, int &b) { // a = first k elements
	if (!o) { a = b = 0; return; }
	int c = cp(o);
	if (sz(t[c].l) >= k) { b = c; split(t[c].l, k, a, t[c].l); upd(c); }
	else { a = c; split(t[c].r, k - sz(t[c].l) - 1, t[c].r, b); upd(c); }
}
ll kth(int o, int k) { // 0-indexed
	while (true) {
		if (k < sz(t[o].l)) o = t[o].l;
		else if (k == sz(t[o].l)) return t[o].val;
		else k -= sz(t[o].l) + 1, o = t[o].r;
	}
}
int insertAt(int root, int pos, ll v) { int a, b; split(root, pos, a, b); return merge(merge(a, newNode(v)), b); }
int eraseAt(int root, int pos) { int a, b, c, d; split(root, pos, a, b); split(b, 1, c, d); return merge(a, d); }
