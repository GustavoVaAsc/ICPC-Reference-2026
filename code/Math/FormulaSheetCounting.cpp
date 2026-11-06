// Counting numbers (mod p), small n tables.
// Stirling 2nd kind S(n,k) = k*S(n-1,k) + S(n-1,k-1): partitions of n into k nonempty sets.
// Stirling 1st kind (unsigned) c(n,k) = (n-1)*c(n-1,k) + c(n-1,k-1): permutations with k cycles.
// Bell B(n) = sum_k S(n,k);  B(n+1) = sum_k C(n,k) B(k).
// Burnside: #orbits = (1/|G|) sum_{g in G} fix(g). Necklaces with n beads, k colors (rotations):
//   (1/n) sum_{d=0}^{n-1} k^gcd(d,n);  with reflections add: n odd: k^((n+1)/2); n even: avg of k^(n/2+1), k^(n/2).
// Partitions p(n): Euler pentagonal, p(n) = sum_{k>=1} (-1)^(k+1) [p(n-k(3k-1)/2) + p(n-k(3k+1)/2)].
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int N = 2005;
ll S2[N][N], S1[N][N], bell[N], part[N];
void build() {
	S2[0][0] = S1[0][0] = 1;
	for (int n = 1; n < N; n++) for (int k = 1; k <= n; k++) {
		S2[n][k] = (k * S2[n - 1][k] + S2[n - 1][k - 1]) % MOD;
		S1[n][k] = ((n - 1) * S1[n - 1][k] + S1[n - 1][k - 1]) % MOD;
	}
	for (int n = 0; n < N; n++) for (int k = 0; k <= n; k++) bell[n] = (bell[n] + S2[n][k]) % MOD;
	part[0] = 1;
	for (int n = 1; n < N; n++)
		for (int k = 1; k * (3 * k - 1) / 2 <= n; k++) {
			ll s = (k & 1) ? 1 : -1;
			part[n] += s * part[n - k * (3 * k - 1) / 2];
			if (k * (3 * k + 1) / 2 <= n) part[n] += s * part[n - k * (3 * k + 1) / 2];
			part[n] = ((part[n] % MOD) + MOD) % MOD;
		}
}
