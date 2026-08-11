#include <deque>
#include <algorithm>
typedef long long ll;

const ll INF = 1e18;

// LineContainer: deque-based Convex Hull Trick for monotonic slopes
// Maintains y = m*x + b and supports query(x) = max y at x
struct Line {
    ll m, b;  // y = m*x + b
    mutable ll p; // intersection with next line (x-coordinate)
    // Sort by slope for insertion
    bool operator<(const Line& o) const { return m < o.m; }
};

// For max query with binary search on intersection x
struct LineContainer : std::deque<Line> {
    // Intersection x-coordinate of lines l1 and l2: (b2-b1)/(m1-m2)
    // l1 has smaller slope than l2 (m1 < m2 for max hull, since m1*x+b1 > m2*x+b2 for large negative x)
    static ll intersectX(const Line& l1, const Line& l2) {
        if (l1.m == l2.m) return l1.b > l2.b ? INF : -INF;
        // floor division for ll, works correctly for positive/negative results
        return (l2.b - l1.b) / (l1.m - l2.m);
    }

    // Check if middle line l2 is unnecessary between l1 and l3
    static bool isBad(const Line& l1, const Line& l2, const Line& l3) {
        // l2 is unnecessary if intersection(l1,l3) <= intersection(l1,l2)
        // (b3-b1)/(m1-m3) <= (b2-b1)/(m1-m2)
        // cross-multiply (watch sign of denominator)
        return (l3.b - l1.b) * (l1.m - l2.m) <= (l2.b - l1.b) * (l1.m - l3.m);
    }

    // Add line y = m*x + b (slopes added in monotonic increasing order)
    void add(ll m, ll b) {
        Line line = {m, b, 0};
        // Find position based on slope
        auto it = std::lower_bound(begin(), end(), line);
        
        // If same slope exists, keep the one with larger b (higher line)
        if (it != end() && it->m == m) {
            if (b <= it->b) return; // existing line is better
            it->b = b;
            it = std::next(it);
        } else {
            it = insert(it, line);
        }

        // Remove lines made obsolete by the new line
        while (it != begin() && std::prev(it, 1) != end()) {
            auto l1 = std::prev(it, 2);
            auto l2 = std::prev(it, 1);
            if (l1->m == l2->m || l2->m == line.m) {
                // Same slope adjacent - remove the middle one with worse b
                if (l2->b < line.b) {
                    erase(l2);
                    break;
                }
            }
            if (isBad(*l1, *l2, line)) {
                erase(l2);
            } else {
                break;
            }
        }

        // Remove lines made obsolete by the new line to the right
        while (std::next(it) != end()) {
            auto l2 = it;
            auto l3 = std::next(it, 1);
            if (isBad(*l2, *l3, line)) {
                erase(l3);
            } else {
                break;
            }
        }

        // Update intersection points
        if (size() >= 2) {
            auto cur = begin();
            auto nxt = std::next(cur);
            cur->p = intersectX(*cur, *nxt);
        }
    }

    // Query maximum y at x
    ll query(ll x) {
        if (empty()) return -INF;
        // Binary search for rightmost line whose p >= x
        int l = 0, r = size() - 1;
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (at(m).p >= x) l = m;
            else r = m - 1;
        }
        Line& ln = at(l);
        return ln.m * x + ln.b;
    }
};
