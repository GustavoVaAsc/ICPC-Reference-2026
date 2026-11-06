// 2D sparse table (range max), build O(nm log n log m), query O(1). Memory n*m*log n*log m.
#include <bits/stdc++.h>
using namespace std;
const int N = 256, LG = 9;
int st[LG][LG][N][N], lg2[N + 1];
void build(const vector<vector<int>> &a) { // n, m <= N
	int n = a.size(), m = a[0].size();
	for (int i = 2; i <= N; i++) lg2[i] = lg2[i / 2] + 1;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) st[0][0][i][j] = a[i][j];
	for (int p = 0; p < LG; p++) for (int q = 0; q < LG; q++) {
		if (p == 0 && q == 0) continue;
		for (int i = 0; i + (1 << p) <= n; i++) for (int j = 0; j + (1 << q) <= m; j++) {
			if (q == 0) st[p][q][i][j] = max(st[p - 1][q][i][j], st[p - 1][q][i + (1 << (p - 1))][j]);
			else st[p][q][i][j] = max(st[p][q - 1][i][j], st[p][q - 1][i][j + (1 << (q - 1))]);
		}
	}
}
int query(int x1, int y1, int x2, int y2) { // inclusive, 0-indexed
	int p = lg2[x2 - x1 + 1], q = lg2[y2 - y1 + 1];
	return max({st[p][q][x1][y1], st[p][q][x2 - (1 << p) + 1][y1], st[p][q][x1][y2 - (1 << q) + 1], st[p][q][x2 - (1 << p) + 1][y2 - (1 << q) + 1]});
}
