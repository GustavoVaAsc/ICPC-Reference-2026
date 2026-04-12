// C++ compiler optimizations for competitive programming.
// Use in submission files when heavy loops / math / bit operations are bottlenecks.
// Avoid for interactive/debug-heavy tasks because aggressive optimizations can make debugging harder.

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// Optional fast I/O toggle:
// ios::sync_with_stdio(false);
// cin.tie(nullptr);

// Notes:
// - O3 + unroll-loops: usually safe and useful in most non-interactive problems.
// - target(...): can speed up bitset/popcount-heavy code, but may fail on judges without these CPU features.
// - If unsure about judge hardware, remove target(...) and keep O3 only.
