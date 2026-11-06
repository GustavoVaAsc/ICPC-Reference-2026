// Minkowski sum of two convex polygons (CCW, no collinear triples), O(n + m).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct P { ll x, y; };
P operator+(P a, P b) { return {a.x + b.x, a.y + b.y}; }
P operator-(P a, P b) { return {a.x - b.x, a.y - b.y}; }
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
void reorder(vector<P> &p) { // start at lowest (y, then x)
	rotate(p.begin(), min_element(p.begin(), p.end(), [](P a, P b) { return make_pair(a.y, a.x) < make_pair(b.y, b.x); }), p.end());
}
vector<P> minkowski(vector<P> a, vector<P> b) {
	reorder(a); reorder(b);
	int n = a.size(), m = b.size(), i = 0, j = 0;
	a.push_back(a[0]); a.push_back(a[1]); b.push_back(b[0]); b.push_back(b[1]);
	vector<P> res;
	while (i < n || j < m) {
		res.push_back(a[i] + b[j]);
		ll c = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
		if (c >= 0 && i < n) i++;
		if (c <= 0 && j < m) j++;
	}
	return res;
}
