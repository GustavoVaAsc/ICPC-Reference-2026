// K shortest walks from s to t (walks may repeat vertices): Dijkstra where each vertex is popped <= k times.
// O(k * E log(k E)). Returns up to k distances in increasing order.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> kShortest(const vector<vector<pair<int, ll>>> &g, int s, int t, int k) {
	vector<int> cnt(g.size(), 0); vector<ll> res;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.push({0, s});
	while (!pq.empty() && (int)res.size() < k) {
		auto [d, u] = pq.top(); pq.pop();
		if (cnt[u] >= k) continue;
		cnt[u]++;
		if (u == t) res.push_back(d);
		for (auto [v, w] : g[u]) pq.push({d + w, v});
	}
	return res;
}
