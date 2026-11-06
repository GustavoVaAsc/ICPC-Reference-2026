// Prefix-function (KMP) automaton: go[i][c] = new matched length after reading c in state i.
// O(n * sigma) build, O(1) transition. Useful for DP over "number of strings avoiding/containing pattern".
#include <bits/stdc++.h>
using namespace std;
const int SIG = 26;
vector<array<int, SIG>> prefixAutomaton(const string &s) { // states 0..n
	int n = s.size();
	vector<int> pi(n, 0);
	for (int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while (j && s[i] != s[j]) j = pi[j - 1];
		pi[i] = j + (s[i] == s[j]);
	}
	vector<array<int, SIG>> go(n + 1);
	for (int i = 0; i <= n; i++) for (int c = 0; c < SIG; c++) {
		if (i < n && s[i] - 'a' == c) go[i][c] = i + 1;
		else go[i][c] = i ? go[pi[i - 1]][c] : 0;
	}
	return go;
}
