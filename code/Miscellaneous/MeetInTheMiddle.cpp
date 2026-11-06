// Meet in the middle: count subsets of a (n <= ~40) with sum == T. O(2^(n/2) * n).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> sums(const vector<ll> &a) { // all subset sums, sorted
	vector<ll> s{0};
	for (ll x : a) {
		size_t m = s.size();
		for (size_t i = 0; i < m; i++) s.push_back(s[i] + x);
	}
	sort(s.begin(), s.end());
	return s;
}
ll countSubsets(const vector<ll> &a, ll T) {
	size_t h = a.size() / 2;
	auto L = sums(vector<ll>(a.begin(), a.begin() + h)), R = sums(vector<ll>(a.begin() + h, a.end()));
	ll res = 0;
	for (ll x : L) {
		auto r = equal_range(R.begin(), R.end(), T - x);
		res += r.second - r.first;
	}
	return res;
}
