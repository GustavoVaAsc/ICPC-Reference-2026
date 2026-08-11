#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const long double EPS = 1e-12;

struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Point& o) const { return !(*this == o); }
};

Point operator+(const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
Point operator*(const Point& a, ll k) { return Point(a.x * k, a.y * k); }

ll cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
ll dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }

// Half-plane: the left side of directed line (p, p+v) is the valid region
struct HalfPlane {
    Point p;      // point on the line
    Point v;      // direction vector
    long double a; // angle for sorting

    HalfPlane() {}
    HalfPlane(const Point& _p, const Point& _v) : p(_p), v(_v) {
        a = atan2((long double)v.y, (long double)v.x);
    }

    // Positive if q is in the half-plane (left of line)
    ll eval(const Point& q) const {
        return cross(v, q - p);
    }

    bool contains(const Point& q) const {
        return eval(q) >= 0;
    }
};

// Angle comparison for sorting
bool hpAngleCmp(const HalfPlane& hp1, const HalfPlane& hp2) {
    return hp1.a < hp2.a;
}

// Check if two half-planes are parallel
bool parallel(const HalfPlane& hp1, const HalfPlane& hp2) {
    return cross(hp1.v, hp2.v) == 0;
}

// Line intersection: p1 + t*v1 = p2 + s*v2
Point lineIntersect(const Point& p1, const Point& v1, const Point& p2, const Point& v2) {
    Point u = p2 - p1;
    ll d = cross(v1, v2);
    if (d == 0) return Point(0, 0);  // parallel - caller should handle
    long double t = (long double)cross(u, v2) / (long double)d;
    return Point(p1.x + (ll)(v1.x * t), p1.y + (ll)(v1.y * t));
}

// Intersection of two half-plane boundary lines
Point hpIntersect(const HalfPlane& hp1, const HalfPlane& hp2) {
    return lineIntersect(hp1.p, hp1.v, hp2.p, hp2.v);
}

// S&I Algorithm: O(N log N) half-plane intersection
vector<Point> half_plane_intersection(vector<HalfPlane>& hps) {
    if (hps.empty()) return {};

    // Sort by angle
    sort(hps.begin(), hps.end(), hpAngleCmp);

    // Remove half-planes with duplicate angles (keep the more restrictive one)
    vector<HalfPlane> filtered;
    for (size_t i = 0; i < hps.size(); i++) {
        if (i + 1 < hps.size() && fabs(hps[i].a - hps[i + 1].a) < EPS) {
            // Same angle: keep the one that contains the other's point
            if (hps[i].contains(hps[i + 1].p)) {
                continue;  // hps[i+1] is redundant
            }
        }
        filtered.push_back(hps[i]);
    }
    hps.swap(filtered);

    if (hps.empty()) return {};

    // Deque for the algorithm
    deque<HalfPlane> dq;

    for (const auto& hp : hps) {
        // Skip if parallel and on same side as last
        if (!dq.empty() && parallel(dq.back(), hp)) {
            if (dq.back().contains(hp.p)) {
                continue;  // hp is redundant
            } else {
                dq.pop_back();  // hp is more restrictive
            }
        }

        // Remove from back while intersection with new hp is outside
        while (dq.size() >= 2) {
            Point inter = hpIntersect(dq[dq.size() - 2], dq.back());
            if (hp.contains(inter)) break;
            dq.pop_back();
        }

        // Remove from front while intersection with new hp is outside
        while (dq.size() >= 2) {
            Point inter = hpIntersect(dq[0], dq[1]);
            if (hp.contains(inter)) break;
            dq.pop_front();
        }

        dq.push_back(hp);
    }

    // Final cleanup: remove last half-plane if it becomes redundant
    while (dq.size() > 2) {
        Point inter = hpIntersect(dq[0], dq[dq.size() - 2]);
        if (dq.back().contains(inter)) {
            dq.pop_back();
        } else {
            break;
        }
    }

    // Remove first if redundant
    while (dq.size() > 2) {
        Point inter = hpIntersect(dq[dq.size() - 1], dq[1]);
        if (dq[0].contains(inter)) {
            dq.pop_front();
        } else {
            break;
        }
    }

    if (dq.size() < 3) return {};  // Empty or unbounded

    // Extract polygon vertices
    vector<Point> result;
    for (size_t i = 0; i < dq.size(); i++) {
        size_t j = (i + 1) % dq.size();
        result.push_back(hpIntersect(dq[i], dq[j]));
    }

    return result;
}

// Legacy compatibility
struct point {
    ll x, y;
    point() {}
    point(ll _x, ll _y) : x(_x), y(_y) {}
    explicit operator Point() const { return Point(x, y); }
};