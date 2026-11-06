Dynamic connectivity with Top Tree

Works when the graph is guaranteed to remain a forest (only link and cut of tree edges).
Top trees support make_root, link, cut, and expose to answer connectivity/path queries.

Not viable for general graphs with cycles by itself. For fully dynamic graphs you need a
structure that maintains a spanning forest and replacement edges (e.g., Holm-de
Lichtenberg-Thorup). A top tree can be a component, but not a standalone solution.
