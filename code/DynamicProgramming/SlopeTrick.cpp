// Slope trick: maintain convex piecewise-linear f(x), O(log n) per op.
// add_a_minus_x(a): f += max(0,a-x); add_x_minus_a(a): f += max(0,x-a); add_abs(a): both.
// minf = min f. prefMin(): f(x)=min_{y<=x} f(y) (drop right part).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct SlopeTrick {
	const ll INF = 4e18;
	ll minf = 0, addL = 0, addR = 0;
	priority_queue<ll> L; priority_queue<ll, vector<ll>, greater<ll>> R;
	ll topL() { return L.empty() ? -INF : L.top() + addL; }
	ll topR() { return R.empty() ? INF : R.top() + addR; }
	void pushL(ll a) { L.push(a - addL); }
	void pushR(ll a) { R.push(a - addR); }
	void add_x_minus_a(ll a) {
		minf += max(0LL, topL() - a); pushL(a);
		ll x = topL(); L.pop(); pushR(x);
	}
	void add_a_minus_x(ll a) {
		minf += max(0LL, a - topR()); pushR(a);
		ll x = topR(); R.pop(); pushL(x);
	}
	void add_abs(ll a) { add_x_minus_a(a); add_a_minus_x(a); }
	void prefMin() { R = decltype(R)(); }
	void slideMin(ll a, ll b) { addL += a; addR += b; } // g(x) = min_{x-b<=y<=x-a} f(y)
};
// Example: min total |a_i - b_i| with b non-decreasing:  for x in a: { st.prefMin(); st.add_abs(x); }  answer st.minf.
