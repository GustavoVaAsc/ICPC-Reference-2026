// Impartial games notes.
// Sprague-Grundy: g(state) = mex{ g(next) }; sum of games: XOR of g; first player wins iff XOR != 0.
//   Normal play (last mover wins). Misere Nim: same as Nim unless all piles <= 1 (then win iff XOR == 0).
// Nim: win iff xor of piles != 0.  Subtraction game {1..k}: g(n) = n mod (k+1).
// Staircase Nim: only piles at odd positions (1-indexed from the ground) count: win iff XOR of them != 0
//   (moving coins from even step to odd step is undone by opponent).
// Moore's Nim_k (take from up to k piles): write sizes in binary; per bit, sum mod (k+1); lose iff all zero.
// Green Hackenbush: tree: g(v) = XOR over children of (g(child) + 1). Cycle (odd) -> single edge, even -> removable;
//   general graph: contract cycles of odd length to one edge, even to a vertex (Fusion principle). Ground = root.
// Wythoff (two piles, take any from one or equal from both): P-positions (floor(k*phi), floor(k*phi^2)).
#include <bits/stdc++.h>
using namespace std;
int mex(vector<int> v) { sort(v.begin(), v.end()); int m = 0; for (int x : v) if (x == m) m++; return m; }
int hackenbushTree(const vector<vector<int>> &g, int v, int p) {
	int r = 0;
	for (int u : g[v]) if (u != p) r ^= hackenbushTree(g, u, v) + 1;
	return r;
}
