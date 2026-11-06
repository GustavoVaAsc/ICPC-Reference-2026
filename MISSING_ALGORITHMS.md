# Missing Algorithms

Candidate additions to the reference. ★ = high priority.

## Computational Geometry
- [x] ★ Line-line / segment intersection point, projection, reflection, point-to-segment distance (check whether `LineSegmentIntersect.cpp` already returns the point)
- [x] ★ Circle primitives: circle-line and circle-circle intersection, tangents from a point, common tangents of two circles, circle-polygon intersection area
- [x] ★ Minimum enclosing circle (Welzl, randomized expected O(n))
- [x] ★ Half-plane intersection, O(n log n)
- [x] Rotating calipers: convex polygon diameter, width, farthest pair of points
- [x] Point in convex polygon in O(log n)
- [x] Convex polygon cut / clipping
- [x] Minkowski sum of convex polygons
- [x] Polygon union area / union of circles area
- [x] Formulas: Pick's theorem, triangle circumcenter and incenter

## Graph Theory
- [x] ★ General (non-bipartite) matching: Edmonds' blossom
- [x] ★ Block-cut tree / vertex-biconnected components
- [x] ★ 0-1 BFS
- [x] Global min cut (Stoer-Wagner)
- [x] Gomory-Hu tree (all-pairs min cut)
- [x] Flow with lower bounds / circulation (reduction to Dinic)
- [x] Dominator tree (Lengauer-Tarjan)
- [x] Maximum clique (Bron-Kerbosch)
- [x] Chromatic number (n up to ~20-40)
- [x] K-th shortest path (Eppstein, or the simple k-times-Dijkstra version)
- [x] Push-relabel max flow

## Mathematics
- [x] ★ Lucas' theorem (nCk mod a small prime)
- [x] ★ Granville / nCk mod a prime power
- [x] ★ Möbius function sieve and Möbius inversion
- [x] ★ K-th term of a linear recurrence (Kitamasa / polynomial mod with NTT), to pair with Berlekamp-Massey
- [x] ★ Simplex (linear programming)
- [x] Primitive root
- [x] Tonelli-Shanks (modular square root)
- [x] Lagrange interpolation (O(n) on consecutive points, and general)
- [x] Polynomial toolkit on NTT: inverse, log, exp, sqrt, division
- [x] Gaussian elimination mod 2 with bitset
- [x] Floor sum: sum of floor((a*i + b) / m)
- [x] Lucy / Min_25 prime counting
- [x] Fraction / rational struct
- [x] Continued fractions / Stern-Brocot search
- [x] Matrix-tree theorem (Kirchhoff)
- [x] Formula sheet: Stirling numbers (both kinds), Bell numbers, Burnside / Pólya, integer partitions

## Dynamic Programming
- [x] ★ Aliens trick / WQS binary search (Lagrangian relaxation)
- [x] ★ Bitset knapsack / subset sum
- [x] Slope trick
- [x] Broken-profile DP
- [x] Monotonic queue DP (sliding-window optimization)
- [x] SMAWK / monotone minima

## Data Structures and Range Queries
- [x] ★ Monotonic deque / sliding window min-max
- [x] ★ Sqrt decomposition template
- [x] ★ Dynamic (sparse) segment tree
- [x] Segment tree beats (chmin/chmax with sum)
- [x] 2D Fenwick tree
- [x] 2D sparse table
- [x] Mo's algorithm with updates
- [x] Mo's algorithm on trees
- [x] Hilbert order for Mo's algorithm
- [x] Persistent treap
- [x] Mergeable / leftist heap

## Strings
- [x] ★ Minimal cyclic rotation (Booth)
- [x] ★ Lyndon factorization (Duval)
- [x] Prefix-function automaton
- [x] 2D hashing / 2D pattern matching
- [x] Main-Lorentz (tandem repeats)
- [x] Suffix array in O(n) (SA-IS)

## Trees
- [x] ★ Virtual / auxiliary tree
- [x] Prüfer code encode / decode
- [x] Unrooted tree hashing (check whether `Isomorphism.cpp` only handles rooted trees)

## Miscellaneous
- [x] ★ Meet in the middle template
- [x] ★ C++ contest template with fast I/O
- [x] ★ Stress-test script (brute vs. solution vs. generator)
- [x] Josephus problem
- [x] Day of week / date utilities
- [x] Hungarian algorithm, O(n^3) matrix form (check the existing `HungarianAlgorithm.cpp`)
- [x] Nim variants notes: Sprague-Grundy, staircase Nim, Green Hackenbush
