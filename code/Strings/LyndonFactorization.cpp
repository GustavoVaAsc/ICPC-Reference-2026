// Lyndon factorization (Duval), O(n). s = w1 >= w2 >= ... (each wi Lyndon). Returns start indices.
#include <bits/stdc++.h>
using namespace std;
vector<int> duval(const string &s) {
	int n = s.size(), i = 0; vector<int> starts;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) k = (s[k] < s[j]) ? i : k + 1, j++;
		while (i <= k) starts.push_back(i), i += j - k;
	}
	return starts;
}
