// (reset tot = 0 between tests) Mergeable (leftist) min-heap: push/pop/merge in O(log n). Heaps are root indices (0 = empty).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
struct Node { int l, r, d; ll key; } t[N]; int tot;
int newNode(ll k) { t[++tot] = {0, 0, 1, k}; return tot; }
int dist(int o) { return o ? t[o].d : 0; }
int merge(int a, int b) {
	if (!a || !b) return a | b;
	if (t[a].key > t[b].key) swap(a, b);
	t[a].r = merge(t[a].r, b);
	if (dist(t[a].l) < dist(t[a].r)) swap(t[a].l, t[a].r);
	t[a].d = dist(t[a].r) + 1;
	return a;
}
int push(int root, ll k) { return merge(root, newNode(k)); }
int pop(int root) { return merge(t[root].l, t[root].r); } // top = t[root].key
