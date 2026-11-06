// Hilbert curve order for Mo's algorithm: usually ~2x fewer pointer moves than block order.
// Sort queries by hilbert(l, r); then run the usual add/remove loop.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll hilbertOrder(int x, int y, int pow = 21, int rotate = 0) { // pow: grid is 2^pow
	if (pow == 0) return 0;
	int h = 1 << (pow - 1);
	int seg = (x < h) ? ((y < h) ? 0 : 3) : ((y < h) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ h), ny = y & (y ^ h);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll sub = 1LL << (2 * pow - 2);
	ll ans = seg * sub;
	ll add = hilbertOrder(nx, ny, pow - 1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (sub - add - 1);
	return ans;
}
struct Query { int l, r, id; ll ord; };
void sortQueries(vector<Query> &qs) {
	for (auto &q : qs) q.ord = hilbertOrder(q.l, q.r);
	sort(qs.begin(), qs.end(), [](const Query &a, const Query &b) { return a.ord < b.ord; });
}
