#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

double dist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

pair<Point, double> trivial(const vector<Point>& R) {
    if (R.empty()) return {Point(0, 0), 0};
    if (R.size() == 1) return {R[0], 0};
    if (R.size() == 2) {
        Point c{(R[0].x + R[1].x) / 2, (R[0].y + R[1].y) / 2};
        return {c, dist(R[0], R[1]) / 2};
    }
    // 3 points - circumcircle
    double d = 2 * (R[0].x * (R[1].y - R[2].y) +
                    R[1].x * (R[2].y - R[0].y) +
                    R[2].x * (R[0].y - R[1].y));
    if (fabs(d) < 1e-12) return {Point(0, 0), 0}; // degenerate, shouldn't happen
    double ux = ((R[0].x * R[0].x + R[0].y * R[0].y) * (R[1].y - R[2].y) +
                 (R[1].x * R[1].x + R[1].y * R[1].y) * (R[2].y - R[0].y) +
                 (R[2].x * R[2].x + R[2].y * R[2].y) * (R[0].y - R[1].y)) / d;
    double uy = ((R[0].x * R[0].x + R[0].y * R[0].y) * (R[2].x - R[1].x) +
                 (R[1].x * R[1].x + R[1].y * R[1].y) * (R[0].x - R[2].x) +
                 (R[2].x * R[2].x + R[2].y * R[2].y) * (R[1].x - R[0].x)) / d;
    return {Point(ux, uy), dist(R[0], Point(ux, uy))};
}

pair<Point, double> welzl(const vector<Point>& pts_input) {
    vector<Point> pts = pts_input;
    shuffle(pts.begin(), pts.end(), mt19937{});
    vector<Point> R;

    function<pair<Point, double>(int)> rec = [&](int n) -> pair<Point, double> {
        if (n == 0 || R.size() == 3) {
            return trivial(R);
        }
        auto d = rec(n - 1);
        if (dist(pts[n - 1], d.first) <= d.second + 1e-9) {
            return d;
        }
        R.push_back(pts[n - 1]);
        auto ans = rec(n - 1);
        R.pop_back();
        return ans;
    };

    return rec(pts.size());
}
