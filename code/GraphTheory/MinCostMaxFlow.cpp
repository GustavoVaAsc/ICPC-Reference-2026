using ll = long long;

// Min-Cost Max-Flow (successive shortest augmenting path with potentials)
// Main use cases:
// 1) Assignment / matching with costs.
// 2) K disjoint paths with minimum total cost.
// 3) Flow with capacities and optimization objective (minimize total cost).
// Complexity: O(F * M log N), F = total sent flow.
// Precondition: all initial edge costs must be non-negative; otherwise the returned cost may be wrong
// (potentials start at 0, so Dijkstra requires the reduced costs to stay non-negative; e.g. for
// s->a(0), s->b(0), a->b(-5), a->t(0), b->t(0) it returns cost -10 instead of the correct -5). To
// support negative costs, replace the vector<ll> pot(n, 0) initialisation with Bellman-Ford/SPFA
// potentials; note that a negative-cost cycle in the residual graph makes the flow unbounded and
// this solver does not terminate.

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        ll cap, cost;
    };

    int n;
    vector<vector<Edge>> g;

    explicit MinCostMaxFlow(int n_) : n(n_), g(n_) {}

    void addEdge(int s, int t, ll cap, ll cost) {
        Edge a{t, (int)g[t].size(), cap, cost};
        Edge b{s, (int)g[s].size(), 0, -cost};
        g[s].push_back(a);
        g[t].push_back(b);
    }

    // Returns {flow, min_cost}.
    pair<ll, ll> minCostMaxFlow(int s, int t, ll maxf = (ll)4e18) {
        const ll INF = (ll)4e18;

        ll flow = 0, flowCost = 0;
        vector<ll> pot(n, 0), dist(n);
        vector<int> pvNode(n), pvEdge(n);

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;

            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[u]) continue;

                for (int i = 0; i < (int)g[u].size(); i++) {
                    const Edge& e = g[u][i];
                    if (e.cap <= 0) continue;

                    ll nd = d + e.cost + pot[u] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pvNode[e.to] = u;
                        pvEdge[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }

            if (dist[t] == INF) break;
            for (int v = 0; v < n; v++) {
                if (dist[v] < INF) pot[v] += dist[v];
            }

            ll add = maxf - flow;
            for (int v = t; v != s; v = pvNode[v]) {
                const Edge& e = g[pvNode[v]][pvEdge[v]];
                add = min(add, e.cap);
            }

            for (int v = t; v != s; v = pvNode[v]) {
                Edge& e = g[pvNode[v]][pvEdge[v]];
                Edge& r = g[v][e.rev];
                e.cap -= add;
                r.cap += add;
                flowCost += add * e.cost;
            }

            flow += add;
        }

        return {flow, flowCost};
    }
};

// Example of use:
// MinCostMaxFlow mcmf(N);
// mcmf.addEdge(u, v, cap, cost);
// auto [flow, cost] = mcmf.minCostMaxFlow(source, sink);
