// Mobius function sieve O(N) and Mobius inversion over divisors.
// g[n] = sum_{d|n} f[d]  =>  f[n] = sum_{d|n} mu(n/d) g[d]   (O(N log N))
// Also: #pairs(i,j<=N) with gcd=1 = sum_d mu[d] * (N/d)^2.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
int mu[N]; vector<int> primes; bool comp[N];
void sieveMu() {
	mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!comp[i]) primes.push_back(i), mu[i] = -1;
		for (int p : primes) {
			if (i * (ll)p >= N) break;
			comp[i * p] = true;
			if (i % p == 0) { mu[i * p] = 0; break; }
			mu[i * p] = -mu[i];
		}
	}
}
// recover f from g = divisor-sum of f, indices 1..n
vector<ll> invertDivisorSum(const vector<ll> &g, int n) {
	vector<ll> f(n + 1, 0);
	for (int d = 1; d <= n; d++)
		for (int m = d; m <= n; m += d) f[m] += mu[m / d] * g[d];
	return f;
}
