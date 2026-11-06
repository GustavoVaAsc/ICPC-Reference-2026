// Minimal cyclic rotation (Booth), O(n). Returns start index of lexicographically smallest rotation.
#include <bits/stdc++.h>
using namespace std;
int minRotation(const string &s) {
	int n = s.size(), i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		char a = s[(i + k) % n], b = s[(j + k) % n];
		if (a == b) { k++; continue; }
		if (a > b) i += k + 1; else j += k + 1;
		if (i == j) j++;
		k = 0;
	}
	return min(i, j);
}
