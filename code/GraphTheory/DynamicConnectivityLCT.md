Dynamic connectivity with Link-Cut Tree

Works when the graph is guaranteed to remain a forest (only link and cut of tree edges).

- link(u, v): connect two different trees
- cut(u, v): remove an existing tree edge
- connected(u, v): check if find_root(u) == find_root(v)

Not viable for general graphs with cycles by itself. For fully dynamic graphs you need a
structure that maintains a spanning forest and replacement edges (e.g., Holm-de
Lichtenberg-Thorup). LCT is a useful component inside such algorithms, but not a
standalone solution.
