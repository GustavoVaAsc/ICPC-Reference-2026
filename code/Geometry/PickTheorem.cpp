#include <vector>
#include <utility>
#include <cmath>
using namespace std;
#define ll long long

struct Point {
    ll x, y;
};

ll CrossP(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Pick's Theorem: A = I + B/2 - 1
// Returns (interior, boundary)
pair<long long, long long> lattice_points(const vector<Point>& poly) {
    int n = poly.size();
    if (n < 3) return {0, 0};

    // Compute signed area via shoelace
    ll area2 = 0;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        area2 += CrossP(p1, p2);
    }
    ll area = llabs(area2) / 2;

    // Compute boundary points B = sum of gcd(|dx|, |dy|) for each edge
    ll B = 0;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        ll dx = p2.x - p1.x;
        ll dy = p2.y - p1.y;
        B += gcd(dx, dy);
    }

    // I = area - B/2 + 1
    ll I = area - B / 2 + 1;

    return {I, B};
}
