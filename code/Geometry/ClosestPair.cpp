#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll MAX = 8e18;

inline ll dist(const pair<ll,ll>& a, const pair<ll,ll>& b){
    ll dx = a.first - b.first;
    ll dy = a.second - b.second;
    return dx*dx + dy*dy;
}

pair<pair<ll,ll>, pair<ll,ll>> bruteForce(const vector<pair<ll,ll>>& pts, int left, int right){
    ll bestd = MAX;
    pair<pair<ll,ll>, pair<ll,ll>> best = {pts[left], pts[left+1]};
    for(int i = left; i < right; i++){
        for(int j = i + 1; j < right; j++){
            ll d = dist(pts[i], pts[j]);
            if(d < bestd){
                bestd = d;
                best = {pts[i], pts[j]};
            }
        }
    }
    return best;
}

struct cmpY {
    bool operator()(const pair<ll,ll>& a, const pair<ll,ll>& b) const {
        return a.second < b.second;
    }
};

pair<pair<ll,ll>, pair<ll,ll>> closestPairRecursive(const vector<pair<ll,ll>>& pts, int left, int right){
    if(right - left <= 3){
        return bruteForce(pts, left, right);
    }
    int mid = left + (right - left) / 2;
    ll midX = pts[mid].first;
    
    auto leftPair = closestPairRecursive(pts, left, mid);
    auto rightPair = closestPairRecursive(pts, mid, right);
    ll d = min(dist(leftPair.first, leftPair.second), dist(rightPair.first, rightPair.second));
    pair<pair<ll,ll>, pair<ll,ll>> best = leftPair;
    if(dist(rightPair.first, rightPair.second) < dist(best.first, best.second)){
        best = rightPair;
    }
    
    vector<pair<ll,ll>> strip;
    strip.reserve(right - left);
    for(int i = left; i < right; i++){
        if(abs(pts[i].first - midX) < d){
            strip.push_back(pts[i]);
        }
    }
    sort(strip.begin(), strip.end(), cmpY());
    
    for(size_t i = 0; i < strip.size(); i++){
        for(size_t j = i + 1; j < strip.size() && (strip[j].second - strip[i].second) < d; j++){
            ll d2 = dist(strip[i], strip[j]);
            if(d2 < d){
                d = d2;
                best = {strip[i], strip[j]};
            }
        }
    }
    return best;
}

pair<pair<ll,ll>, pair<ll,ll>> closest_pair(vector<pair<ll,ll>>& pts){
    sort(pts.begin(), pts.end());
    return closestPairRecursive(pts, 0, (int)pts.size());
}
