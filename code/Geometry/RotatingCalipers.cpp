#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point{
    ll x,y;
};

ll dist2(point a, point b){
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx*dx + dy*dy;
}

ll cross(point a, point b){
    return a.x*b.y - a.y*b.x;
}

point operator-(point a, point b){
    return {a.x - b.x, a.y - b.y};
}

pair<point, point> hull_diameter(const vector<point>& hull){
    int n = hull.size();
    if (n == 1) return {hull[0], hull[0]};

    ll bestd = 0;
    pair<point, point> best = {hull[0], hull[0]};

    int j = 1;
    for (int i = 0; i < n; i++){
        // edge i -> (i+1)%n
        point edge_i = hull[(i+1)%n] - hull[i];
        // advance j to antipodal point (maximizes area with edge i)
        while (cross(edge_i, hull[(j+1)%n] - hull[i]) >
               cross(edge_i, hull[j] - hull[i]))
            j = (j + 1) % n;

        ll cur = dist2(hull[i], hull[j]);
        if (cur > bestd){
            bestd = cur;
            best = {hull[i], hull[j]};
        }
    }
    return best;
}
