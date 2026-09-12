vector<vector<long long>> dist(n + 1, vector<long long>(max_k + 1, INF));
    priority_queue<State, vector<State>, greater<State>> pq;
    
    // Assuming 1 is the source node
    dist[1][0] = 0;
    pq.push({0, 1, 0});
    
    while (!pq.empty()) {
        auto [d, u, fast_used] = pq.top();
        pq.pop();
        
        // Skip outdated states (lazy deletion)
        if (d > dist[u][fast_used]) continue;
        
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            long long w = edge.weight;
            
            if (!edge.is_fast) {
                // Transition 1: Take a normal edge
                if (dist[u][fast_used] + w < dist[v][fast_used]) {
                    dist[v][fast_used] = dist[u][fast_used] + w;
                    pq.push({dist[v][fast_used], v, fast_used});
                }
            } else {
                // Transition 2: Take a fast edge (only if we haven't hit the limit)
                if (fast_used < max_k && dist[u][fast_used] + w < dist[v][fast_used + 1]) {
                    dist[v][fast_used + 1] = dist[u][fast_used] + w;
                    pq.push({dist[v][fast_used + 1], v, fast_used + 1});
                }
            }
        }
    }