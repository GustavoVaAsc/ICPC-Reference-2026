#include <vector>
#include <functional>
#include <unordered_map>
using namespace std;

int mex(vector<int>& s) {
    if (s.empty()) return 0;
    int n = s.size();
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int cnt = 0;
        for (int x : s) if (x <= mid) cnt++;
        if (cnt > mid) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int grundy(int state, function<vector<int>(int)> moves) {
    static unordered_map<int, int> memo;
    if (memo.count(state)) return memo[state];
    vector<int> g;
    for (int nxt : moves(state))
        g.push_back(grundy(nxt, moves));
    return memo[state] = mex(g);
}
