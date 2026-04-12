// Deterministic Miller-Rabin primality test for unsigned 64-bit integers.
// Purpose: fast primality checks for big n (up to 1e18 / uint64 range).
// Complexity per query: O(k * log n), where k is the number of bases (here constant 7).
// Typical CP usage: primality checks in factorization, number theory tasks, random tests.

using u64 = uint64_t;
using u128 = __uint128_t;

u64 mod_mul(u64 a, u64 b, u64 mod) {
	return (u128)a * b % mod;
}

u64 mod_pow(u64 a, u64 e, u64 mod) {
	u64 r = 1;
	while (e > 0) {
		if (e & 1) r = mod_mul(r, a, mod);
		a = mod_mul(a, a, mod);
		e >>= 1;
	}
	return r;
}

bool isPrime(u64 n) {
	if (n < 2) return false;

	// Fast small-prime filter.
	for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
		if (n % p == 0) return n == p;
	}

	// Write n - 1 = d * 2^s with d odd.
	u64 d = n - 1;
	int s = 0;
	while ((d & 1) == 0) {
		d >>= 1;
		s++;
	}

	// Deterministic bases for testing all uint64 values.
	// Valid for n < 2^64.
	for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
		if (a % n == 0) continue;

		u64 x = mod_pow(a % n, d, n);
		if (x == 1 || x == n - 1) continue;

		bool witness = true;
		for (int r = 1; r < s; r++) {
			x = mod_mul(x, x, n);
			if (x == n - 1) {
				witness = false;
				break;
			}
		}

		if (witness) return false;
	}

	return true;
}

// Usage example:
// u64 n; cin >> n;
// cout << (isPrime(n) ? "YES" : "NO") << '\n';

