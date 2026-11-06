// Main-Lorentz: find all tandem repeats (squares ww) in O(n log n) (output-sensitive: may be O(n log n) triples).
// Each result (a, b) = substring s[a..b] of even length that is a square (inclusive indices).
#include <bits/stdc++.h>
using namespace std;
vector<int> zf(const string &s) {
	int n = s.size(); vector<int> z(n, 0);
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i < r) z[i] = min(r - i, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] > r) l = i, r = i + z[i];
	}
	return z;
}
int getz(const vector<int> &z, int i) { return (0 <= i && i < (int)z.size()) ? z[i] : 0; }
vector<pair<int, int>> reps;
void convert(int shift, bool left, int cntr, int l, int k1, int k2) {
	for (int l1 = max(1, l - k2); l1 <= min(l, k1); l1++) {
		if (left && l1 == l) break;
		int pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
		reps.emplace_back(pos, pos + 2 * l - 1);
	}
}
void findReps(const string &s, int shift = 0) {
	int n = s.size();
	if (n == 1) return;
	int nu = n / 2, nv = n - nu;
	string u = s.substr(0, nu), v = s.substr(nu), ru(u.rbegin(), u.rend()), rv(v.rbegin(), v.rend());
	findReps(u, shift); findReps(v, shift + nu);
	auto z1 = zf(ru), z2 = zf(v + '#' + u), z3 = zf(ru + '#' + rv), z4 = zf(v);
	for (int cntr = 0; cntr < n; cntr++) {
		int l, k1, k2;
		if (cntr < nu) { l = nu - cntr; k1 = getz(z1, nu - cntr); k2 = getz(z2, nv + 1 + cntr); }
		else { l = cntr - nu + 1; k1 = getz(z3, nu + 1 + nv - 1 - (cntr - nu)); k2 = getz(z4, (cntr - nu) + 1); }
		if (k1 + k2 >= l) convert(shift, cntr < nu, cntr, l, k1, k2);
	}
}
