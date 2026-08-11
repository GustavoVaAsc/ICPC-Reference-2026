// Biconnected Components (vertex-biconnected components)
// Uses DFS with edge stack; articulation points split components

#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int dfsTime = 0;
vector<int> disc, low;
vector<vector<int>> comps;
vector<pair<int,int>> edgeStack;
vector<vector<int>> adj;

// disc[u] = discovery time of u
// low[u] = 'low' node of u (lowest discovery time reachable from u)

void dfsBCC(int u, int parent) {
  disc[u] = low[u] = ++dfsTime;
  for (int v : adj[u]) {
    if (v == parent) continue;
    if (!disc[v]) {
      edgeStack.emplace_back(u, v);
      dfsBCC(v, u);
      low[u] = min(low[u], low[v]);
      if (disc[u] <= low[v]) {
        // u is an articulation point; pop edges to form a component
        comps.push_back({});
        while (edgeStack.back() != make_pair(u, v)) {
          int a = edgeStack.back().first, b = edgeStack.back().second;
          comps.back().push_back(a);
          comps.back().push_back(b);
          edgeStack.pop_back();
        }
        // pop the (u,v) edge
        comps.back().push_back(u);
        comps.back().push_back(v);
        edgeStack.pop_back();
      }
    } else if (disc[v] < disc[u]) {
      // back edge to ancestor (avoid duplicates in undirected graph)
      low[u] = min(low[u], disc[v]);
      edgeStack.emplace_back(u, v);
    }
  }
}

vector<vector<int>> biconnected_components(int n, const vector<vector<int>>& adj_) {
  adj = adj_;
  disc.assign(n, 0);
  low.assign(n, 0);
  comps.clear();
  edgeStack.clear();
  dfsTime = 0;

  for (int u = 0; u < n; u++) {
    if (!disc[u]) {
      dfsBCC(u, u);
      // remaining edges on stack form a component
      if (!edgeStack.empty()) {
        comps.push_back({});
        while (!edgeStack.empty()) {
          comps.back().push_back(edgeStack.back().first);
          comps.back().push_back(edgeStack.back().second);
          edgeStack.pop_back();
        }
      }
    }
  }

  // remove duplicate vertices in each component
  for (auto& comp : comps) {
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
  }

  return comps;
}
