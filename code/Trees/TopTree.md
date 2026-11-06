Top Tree (dynamic forest notes)

- Maintains aggregates on paths/subtrees with link/cut in O(log n) amortized.
- Works only on forests (no cycles). For general graphs, you need a dynamic connectivity structure.
- Core operations:
  * make_root(v)    : reroot tree at v
  * link(u, v)      : connect two different trees
  * cut(u, v)       : remove an existing edge
  * expose(u, v)    : isolate the u-v path cluster for queries/updates

Cluster template:

struct Cluster {
    // Store path aggregate (sum, max, etc.) and any extra info.
    // Keep data for both orientations if you need reversals.
};

Cluster merge(const Cluster &a, const Cluster &b) {
    // Combine two adjacent clusters along a shared boundary.
}

Cluster reverse(const Cluster &c) {
    // Swap endpoints and update directional data if needed.
}

Notes:
- A Link-Cut Tree is a splay-based top tree specialization for path aggregates.
- If you only need path queries/updates, use the Link-Cut Tree template.
- For subtree aggregates, a full top tree is more flexible but longer to implement.
