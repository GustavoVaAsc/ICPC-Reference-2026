int n, m;
vector<vector<int>> g;
vector<int> in, out, path;

// Undirected

int n, m;
vector<vector<pair<int, int>>> g;
vector<int> path;
vector<bool> seen;

void dfs(int node) {
	while (!g[node].empty()) {
		auto [son, idx] = g[node].back();
		g[node].pop_back();
		if (seen[idx]) { continue; }
		seen[idx] = true;
		dfs(son);
	}
	path.push_back(node);
}

// Directed
void dfs(int node) {
	while (!g[node].empty()) {
		int son = g[node].back();
		g[node].pop_back();
		dfs(son);
	}
	path.push_back(node);
}